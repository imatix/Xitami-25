/*===========================================================================*
 *                                                                           *
 *  brocgi.c - CGI broker functions                                          *
 *                                                                           *
 *  Copyright (c) 1991-2003 iMatix Corporation                               *
 *                                                                           *
 *  ------------------ GPL Licensed Source Code ------------------           *
 *  iMatix makes this software available under the GNU General               *
 *  Public License (GPL) license for open source projects.  For              *
 *  details of the GPL license please see www.gnu.org or read the            *
 *  file license.gpl provided in this package.                               *
 *                                                                           *
 *  This program is free software; you can redistribute it and/or            *
 *  modify it under the terms of the GNU General Public License as           *
 *  published by the Free Software Foundation; either version 2 of           *
 *  the License, or (at your option) any later version.                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public                *
 *  License along with this program in the file 'license.gpl'; if            *
 *  not, write to the Free Software Foundation, Inc., 59 Temple              *
 *  Place - Suite 330, Boston, MA 02111-1307, USA.                           *
 *                                                                           *
 *  You can also license this software under iMatix's General Terms          *
 *  of Business (GTB) for commercial projects.  If you have not              *
 *  explicitly licensed this software under the iMatix GTB you may           *
 *  only use it under the terms of the GNU General Public License.           *
 *                                                                           *
 *  For more information, send an email to info@imatix.com.                  *
 *  --------------------------------------------------------------           *
 *===========================================================================*/

#define USE_CGI_BROKER 1

#include "sfl.h"                        /*  SFL prototypes & definitions     */
#include "stupriv.h"                    /*  Studio project definitions       */
#include "brocgi.h"                     /*  Broker definitions               */
#include "brocgi.d"                     /*  Include dialog data              */


/*- Local function prototypes -----------------------------------------------*/

static char   *context_filename (long session_id, int key);
static int     context_load     (int scope, long session_id, int key);
static int     context_save     (int scope, long session_id, int key);
static int     fputnetw         (FILE *output, word value);
static int     fgetnetw         (FILE *input, word *value);
static void    html_header      (void);
static void    html_footer      (void);
static void    set_symbols      (SYMTAB *symbols);


/*- Constants ---------------------------------------------------------------*/

#define CUTOFF_TIME     15              /*  Context-cutoff time, minutes     */
#define BUFFER_MAX      32000           /*  Max in/out buffer size           */
#define SESSION_ID      "_sid"          /*  Session id string                */
#define SESSION_STEP    "_sstep"        /*  Session step string              */


/*- Global variables used in this source file only --------------------------*/

static SESSION
    session;                            /*  Current session context block    */
static VDESCR                           /*  Descriptor for form_put()        */
    buffer = { BUFFER_MAX, 0, NULL };

static char
    *uri_data,                          /*  Arguments to URI (session key)   */
    *form_data,                         /*  Posted form data, if any         */
    *main_uri;                          /*  Return URL for form data         */
static int
    feedback;                           /*  Feedback for calling program     */


/********************************   M A I N   ********************************/

int cgi_broker (
    char *p_uri_data,
    char *p_form_data,
    char *p_main_uri)
{
    uri_data  = p_uri_data;             /*  Set argument addressability      */
    form_data = p_form_data;
    main_uri  = p_main_uri;

    feedback = 0;                       /*  No errors so far                 */
#   include "brocgi.i"                  /*  Include dialog interpreter       */
}


/*************************   INITIALISE THE PROGRAM   ************************/

MODULE initialise_the_program (void)
{
    context_init (SCOPE_GLOBAL);
    buffer.data = mem_alloc (BUFFER_MAX + 1);
    if (buffer.data)
        the_next_event = ok_event;
    else
        the_next_event = error_event;
}


/**************************   CLEANUP OLD SESSIONS   *************************/

MODULE cleanup_old_sessions (void)
{
    DIRST
        dir;                            /*  Current directory listing        */
    Bool
        rc;                             /*  Return code from read_dir()      */
    long
        cutoff_date,                    /*  Calculated cut-off date          */
        cutoff_time;                    /*    and time                       */
    int
        name_size,
        level;                          /*  Each context level, 01..99       */
    time_t
        cutoff;                         /*  Cut-off date/time for contexts   */

    cutoff_date = 0;
    cutoff_time = 0;
    past_date (&cutoff_date, &cutoff_time, 0, CUTOFF_TIME * 6000L);
    cutoff = date_to_timer (cutoff_date, cutoff_time);

    rc = open_dir (&dir, NULL);
    while (rc)
      {
        /*  We check only the 'c99' file, which is the main session context
         *  block.  If this is out-of-date, all context blocks are deleted
         *  starting from c00.
         */
        if (file_matches (dir.file_name, "*.c99")
        &&  dir.file_time < cutoff)
          {
            name_size = strlen (dir.file_name);
            for (level = 0; level < 99; level++)
              {
                if (file_delete (dir.file_name))
                    break;
                dir.file_name [name_size - 2] = level / 10 + '0';
                dir.file_name [name_size - 1] = level % 10 + '0';
              }
          }
        rc = read_dir (&dir);
      }
    close_dir (&dir);
}


/************************   INITIALISE SESSION DATA   ************************/

MODULE initialise_session_data (void)
{
    /*  We work with this static block; initialise it nicely                 */
    memset (&session, 0, sizeof (session));

    /*  By default we show disabled actions; the programmer can override
     *  this in the program if desired.
     */
    session.disable_actions = DISABLE_HIDDEN;

    /*  We'll set debug_mode if the query data contains a field 'debug=1'.   */
    session.debug_mode_ = FALSE;

    /*  These private fields must not be modified by the user                */
    session.stack_ptr_ = 0;
    session.buffer_    = &buffer;
}


/*************************   PARSE ARGUMENTS IF ANY   ************************/

MODULE parse_arguments_if_any (void)
{
    SYMTAB
        *symtab;                        /*  Parsed query variables           */

    /*  If the URI was invoked with arguments, we look for our session key.
     *  Otherwise we start a new session.
     */
    if (uri_data)
      {
        if ((symtab = http_query2symb (uri_data)) == NULL)
          {
            /*  Not enough memory to work                                    */
            raise_exception (exception_event);
            return;
          }
        session.debug_mode_   = sym_get_boolean (symtab, "debug",  FALSE);
        session.session_id_   = sym_get_number  (symtab, SESSION_ID,   0);
        session.session_step_ = sym_get_number  (symtab, SESSION_STEP, 0);
        sym_delete_table (symtab);
      }
}


/**************************   CHECK IF NEW SESSION   *************************/

MODULE check_if_new_session (void)
{
    if (session.session_id_ > 0)
        the_next_event = in_progress_event;
    else
        the_next_event = new_session_event;
}


/**************************   PREPARE NEW SESSION   **************************/

MODULE prepare_new_session (void)
{
    /*  Get random, unique, non-zero session id                              */
    FOREVER
      {
        randomize ();
        session.session_id_ = random (1000);
        if (session.session_id_ == 0)
            continue;
        if (!file_exists (context_filename (session.session_id_, 99)))
            break;
      }
}


/*  -------------------------------------------------------------------------
 *  context_filename
 *
 *  Returns a context filename for the current session.
 */

static char *
context_filename (long session_id, int key)
{
    static char
        filename [13];

    sprintf (filename, "FX%06ld.c%02d", session_id, key);
    return (filename);
}


/**************************   SET INITIAL PROGRAM   **************************/

MODULE set_initial_program (void)
{
    char
        *root_program;

    root_program = cgi_root ();
    ASSERT (root_program);
    strcpy (session.program_name, root_program);
}


/*************************   TRY TO RESTORE CONTEXT   ************************/

MODULE try_to_restore_context (void)
{
    long
        session_step;                   /*  Required session step            */

    if (context_load (SCOPE_GLOBAL, session.session_id_, 99))
      {
        session_step = session.session_step_;
        CONTEXT_GETG ("_sess", &session, sizeof (session));

        /*  If we're in step, okay -- get query data into buffer             */
        if (session_step == session.session_step_)
          {
            session.buffer_ = &buffer;
            strncpy ((char *) buffer.data, form_data, BUFFER_MAX);
            buffer.data [BUFFER_MAX] = 0;
          }
        else
            raise_exception (out_of_step_event);
      }
    else
        /*  Context file not found - was presumably cleaned-up               */
        raise_exception (timed_out_event);
}


/*  --------------------------------------------------------------------------
 *  context_load -- internal
 *
 *  Loads a context symbol table from the specified file.  Returns 1 if okay,
 *  0 if the file was not found.  Deletes the context file after loading it.
 */

static int
context_load (
    int  scope,
    long id,
    int  key)
{
    FILE
        *input;
    static char
        block_name [255 + 1];           /*  Name is up to 255 chars long     */
    word
        cur_size;
    SYMTAB
        *table;
    SYMBOL
        *symbol;                        /*  Symbol we create in table        */

    input = fopen (context_filename (id, key), FOPEN_READ_BINARY);
    if (!input)
        return (0);                     /*  Not found                        */

    table = context_addr (scope);
    FOREVER
      {
        /*  Read context key from file                                       */
        if (fgetnetw (input, &cur_size))
            break;
        fread (block_name, cur_size, 1, input);
        block_name [cur_size] = '\0';

        /*  Get context block from file                                      */
        fgetnetw (input, &cur_size);
        symbol = sym_assume_symbol (table, block_name, NULL);
        if (symbol-> data)
            mem_free (symbol-> data);

        symbol-> data = mem_descr (NULL, cur_size);
        if (symbol-> data)
            fread (((DESCR *) symbol-> data)-> data, cur_size, 1, input);
        else
            sym_delete_symbol (table, symbol);
      }
    fclose (input);
    remove (context_filename (id, key));
    return (1);
}


/*  --------------------------------------------------------------------------
 *  fgetnetw -- internal
 *
 *  Reads a word in network order to a file.  Returns 0 if okay, else -1.
 */

static int
fgetnetw (FILE *input, word *value)
{
    byte
        word_hi,
        word_lo;

    ASSERT (input);
    if (fread (&word_hi, sizeof (byte), 1, input) == 0
    ||  fread (&word_lo, sizeof (byte), 1, input) == 0)
        return (-1);
    else
      {
        *value = (word_hi << 8) + word_lo;
        return (0);
      }
}


/**************************   SAVE SESSION CONTEXT   *************************/

MODULE save_session_context (void)
{
    CONTEXT_PUTG ("_sess", &session, sizeof (session));
    if (!context_save (SCOPE_GLOBAL, session.session_id_, 99))
        raise_exception (file_io_error_event);
}


/*  --------------------------------------------------------------------------
 *  context_save -- internal
 *
 *  Saves a context symbol table into the specified file.  Returns 1 if okay,
 *  0 if there was an error writing the file.
 */

static int
context_save (
    int  scope,
    long id,
    int  key)
{
    FILE
        *output;
    SYMBOL
        *symbol;                        /*  Next symbol in table             */
    SYMTAB
        *table;
    DESCR
        *descr;                         /*  Symbol block descriptor          */

    output = fopen (context_filename (id, key), FOPEN_WRITE_BINARY);
    if (!output)
        return (0);

    table = context_addr (scope);
    for (symbol = table-> symbols; symbol; symbol = symbol-> next)
      {
        /*  Write context key to file                                        */
        fputnetw (output, (word) strlen (symbol-> name));
        fwrite   (symbol-> name, strlen (symbol-> name), 1, output);

        /*  Write context block to file                                      */
        descr = symbol-> data;
        fputnetw (output, (word) descr-> size);
        fwrite   (descr-> data, descr-> size, 1, output);
      }
    fclose (output);
    return (1);
}


/*  --------------------------------------------------------------------------
 *  fputnetw -- internal
 *
 *  Writes a word in network order to a file.  Returns 0 if okay, -1 if error.
 */

static int
fputnetw (FILE *output, word value)
{
    byte
        size_hi,
        size_lo;

    size_hi = value >> 8;
    size_lo = value & 255;
    if (fwrite (&size_hi, sizeof (byte), 1, output) == 0
    ||  fwrite (&size_lo, sizeof (byte), 1, output) == 0)
        return (-1);
    else
        return (0);
}


/*************************   DELETE SESSION CONTEXT   ************************/

MODULE delete_session_context (void)
{
    remove (context_filename (session.session_id_, 99));
}


/*************************   START THE TRANSACTION   *************************/

MODULE start_the_transaction (void)
{
    /*  If debug mode is in force, output a dummy HTTP header so that any    */
    /*  text output by the program is correctly displayed.                   */
    if (session.debug_mode_)
      {
        html_header ();
        puts ("<H3>*** FX/CGI Debugging Mode ***</H3>");
        html_footer ();
      }
}

static void
html_header (void)
{
    puts ("Content-Type: text/html\n");
    puts ("<HTML><BODY>");
}

static void
html_footer (void)
{
    puts ("</BODY></HTML>");
}


/**************************   INIT PROGRAM CONTEXT   *************************/

MODULE init_program_context (void)
{
    /*  Load program context as far as possible                              */
    context_init (SCOPE_LOCAL);
    session.symbols = sym_create_table ();
    set_symbols (session.symbols);
}


/*  -------------------------------------------------------------------------
 *  set_symbols - internal
 *
 *  Stores session symbols into the form symbol table:
 *      uri - CGI program URI plus session key
 */

static void
set_symbols (SYMTAB *symbols)
{
    static char
        symbol_value [LINE_MAX];

    ASSERT (symbols);
    sprintf (symbol_value, "%s?%s=%ld&%s=%ld", main_uri,
             SESSION_ID,     session.session_id_,
             SESSION_STEP, ++session.session_step_);

    sym_assume_symbol (symbols, "uri", symbol_value);
}


/**************************   LOAD PROGRAM CONTEXT   *************************/

MODULE load_program_context (void)
{
    /*  Load program context as far as possible                              */
    context_init   (SCOPE_LOCAL);
    context_load   (SCOPE_LOCAL, session.session_id_, session.stack_ptr_);
    context_getsym (SCOPE_LOCAL, "_sym", &session.symbols);
    set_symbols    (session.symbols);
}


/**************************   SAVE PROGRAM CONTEXT   *************************/

MODULE save_program_context (void)
{
    context_putsym (SCOPE_LOCAL, "_sym", session.symbols);
    if (!context_save (SCOPE_LOCAL, session.session_id_, session.stack_ptr_))
        raise_exception (file_io_error_event);
    close_program_context ();
}


/*************************   CLOSE PROGRAM CONTEXT   *************************/

MODULE close_program_context (void)
{
    sym_delete_table (session.symbols);
    context_term (SCOPE_LOCAL);
}


/************************   CHECK PROGRAM NOT ACTIVE   ***********************/

MODULE check_program_not_active (void)
{
    int
        prognbr;                        /*  Index into program list          */

    for (prognbr = 0; prognbr < session.stack_ptr_; prognbr++)
      {
        if (streq (session.stack_ [prognbr], session.program_name))
          {
            raise_exception (call_failed_event);
            session.program_callcode = CALLCODE_ACTIVE;
          }
      }
}


/*************************   INVOKE ACTIVE PROGRAM   *************************/

MODULE invoke_active_program (void)
{
    int
        prognbr,                        /*  Index into program list          */
        rc;

    strlwc (session.program_name);      /*  Compare lwc with lwc             */
    rc = FEEDBACK_UNKNOWN;              /*  Assume not found                 */
    for (prognbr = 0; cgi_broker_map [prognbr].name; prognbr++)
      {
        if (streq (session.program_name, cgi_broker_map [prognbr].name))
          {
            session.program_callcode = CALLCODE_OKAY;
            rc = ((ATP_FCT) cgi_broker_map [prognbr].function) (&session);
            break;
          }
      }
    switch (rc)
      {
        case FEEDBACK_SHOW:
            the_next_event = show_event;
            break;
        case FEEDBACK_CALL:
            the_next_event = call_event;
            break;
        case FEEDBACK_RETURN:
            the_next_event = return_event;
            break;
        case FEEDBACK_ERROR:
            the_next_event = finished_event;
            break;
        case FEEDBACK_UNKNOWN:
            the_next_event = call_failed_event;
            session.program_callcode = CALLCODE_UNKNOWN;
            break;
        default:
            the_next_event = finished_event;
            break;
      }
}


/**************************   END THE TRANSACTION   **************************/

MODULE end_the_transaction (void)
{
}


/************************   PUSH NEW ACTIVE PROGRAM   ************************/

MODULE push_new_active_program (void)
{
    if (session.stack_ptr_ < STACK_MAX)
      {
        strcpy (session.stack_ [session.stack_ptr_++], session.program_name);
        strcpy (session.program_name, session.program_to_call);
      }
}


/*************************   POP OLD ACTIVE PROGRAM   ************************/

MODULE pop_old_active_program (void)
{
    if (session.stack_ptr_ > 0)
        strcpy (session.program_name, session.stack_ [--session.stack_ptr_]);
    else
        raise_exception (finished_event);
}


/************************   SEND HTML FORM TO CLIENT   ***********************/

MODULE send_html_form_to_client (void)
{
    puts ("Content-Type: text/html\n");
    puts ((char *) buffer.data);
}


/************************   SIGNAL SESSION TIMED OUT   ***********************/

MODULE signal_session_timed_out (void)
{
    html_header ();
    printf ("<H1>Session Timed-Out</H1>\n");
    printf ("<P>The session timed-out; work in progress was cancelled.\n");
    printf ("<P><A HREF=\"%s\">Restart the application.</A>\n", main_uri);
    html_footer ();
}


/*************************   SIGNAL INVALID SESSION   ************************/

MODULE signal_invalid_session (void)
{
    html_header ();
    printf ("<H1>Invalid Session</H1>\n");
    printf ("<P>Out-of-sequence form was sent.\n");
    printf ("<P><A HREF=\"%s\">Restart the application.</A>\n", main_uri);
    html_footer ();
}


/**************************   SIGNAL FILE IO ERROR   *************************/

MODULE signal_file_io_error (void)
{
    html_header ();
    puts ("<H1>File Access Error</H1>");
    puts ("<P>Cannot write context files - check file permissions.");
    html_footer ();
}


/***************************   GET EXTERNAL EVENT   **************************/

MODULE get_external_event (void)
{
}


/*************************   TERMINATE THE PROGRAM    ************************/

MODULE terminate_the_program (void)
{
    if (buffer.data)
        mem_free (buffer.data);

    the_next_event = terminate_event;
    context_term (SCOPE_GLOBAL);
}

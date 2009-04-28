/*===========================================================================*
 *                                                                           *
 *  browtp.c - WTP broker functions                                          *
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
/*
    Synopsis:   WTP broker functions

*/
#define USE_WTP_BROKER 1

#include "sfl.h"                        /*  SFL prototypes & definitions     */
#include "studio.h"                     /*  WTP definitions                  */

#include "browtp.d"                     /*  Include dialog data              */


/*- Constants ---------------------------------------------------------------*/

#define BUFFER_MAX      65534           /*  Max in/out buffer size           */


/*- Local function prototypes -----------------------------------------------*/

static void context_load (int scope, qbyte size, byte *data);
static int  context_save (int scope, qbyte *ret_size, byte **ret_buffer);


/*- Global variables used in this source file only --------------------------*/

static SESSION
    session;                            /*  Current session context block    */
static VDESCR                           /*  Descriptor for form_put()        */
    buffer = { BUFFER_MAX, 0, NULL };

static struct_wtp_msg_do
    *msg_do = NULL;                     /*  Request from WTP manager         */

static int
    feedback;                           /*  Feedback for this program        */


/********************************   M A I N   ********************************/

int wtp_broker (void)
{
    feedback = 0;                       /*  No errors so far                 */
#   include "browtp.i"                  /*  Include dialog interpreter       */
}


/*************************   INITIALISE THE PROGRAM   ************************/

MODULE initialise_the_program (void)
{
    char
        *db_name,
        *db_user,
        *db_pwd,
        *db_type,
        *db_extra;
    dbyte
        type;

    db_name  = env_get_string ("db_name",   NULL);
    db_user  = env_get_string ("db_user",   NULL);
    db_pwd   = env_get_string ("db_pwd",    NULL);
    db_type  = env_get_string ("db_type",   NULL);
    db_extra = env_get_string ("db_extra",  NULL);
    type = get_db_type (db_type);
    dbio_connect (db_name, db_user, db_pwd, db_extra, TRUE, type);

    buffer.data = mem_alloc (BUFFER_MAX + 1);
    if (buffer.data)
        the_next_event = ok_event;
    else
        the_next_event = error_event;
}


/***************************   WTP GET DO REQUEST   **************************/

MODULE wtp_get_do_request (void)
{
    byte
        *buffer = NULL;                 /*  Message buffer from wtpman       */

    if (wtp_read (&buffer) == 0 || buffer == NULL)
      {
        raise_exception (exception_event);
        return;
      }
    ASSERT (msg_do == NULL);
    get_wtp_msg_do (buffer, &msg_do);

    if (msg_do-> type == WTP_DO)
        the_next_event = ok_event;
    else
        the_next_event = error_event;

    mem_free (buffer);
}


/**************************   WTP FREE DO REQUEST   **************************/

MODULE wtp_free_do_request (void)
{
    free_wtp_msg_do (&msg_do);
}


/**************************   SAVE SESSION CONTEXT   *************************/

MODULE save_session_context (void)
{
    context_putsym (SCOPE_GLOBAL, "_sym",  session.symbols);
    context_put    (SCOPE_GLOBAL, "_sess", &session, sizeof (session));

    /*  Save global context block back into DO message buffer                */
    mem_free (msg_do-> global_data);
    context_save (SCOPE_GLOBAL, &msg_do-> global_size, &msg_do-> global_data);
    context_term (SCOPE_GLOBAL);

    /*  Save local context block back into DO message buffer                 */
    mem_free (msg_do-> local_data);
    context_save (SCOPE_LOCAL, &msg_do-> local_size, &msg_do-> local_data);
    context_term (SCOPE_LOCAL);
}


/*  --------------------------------------------------------------------------
 *  context_save
 *
 *  Saves the specified symbol table as a block of memory, and returns the
 *  size and contents of the memory block.  When finished with the block of
 *  memory you should use mem_free() to deallocate it.
 */

static int
context_save (int scope, qbyte *ret_size, byte **ret_buffer)
{
    size_t
        bufsize;
    qbyte
        portable_size;                  /*  Block size in network order      */
    byte
        *buffer;
    SYMTAB
        *table;                         /*  Symbol table to work with        */
    SYMBOL
        *symbol;                        /*  Next symbol in table             */
    DESCR
        *descr;                         /*  Symbol block descriptor          */

    /*  Calculate required size for context block                            */
    bufsize = 0;
    table = context_addr (scope);
    for (symbol = table-> symbols; symbol; symbol = symbol-> next)
      {
        descr = symbol-> data;          /*  Symbol data is always a DESCR    */
        bufsize += strlen (symbol-> name) + 1;
                                        /*  Store name + terminator          */
        bufsize += 4;                   /*    and a 4-byte size              */
        bufsize += descr-> size;        /*    and the symbol data            */
      }

    buffer = mem_alloc (bufsize);
    if (buffer == NULL)
        return (-1);                    /*  Error - insufficient memory      */

    *ret_buffer = buffer;
    *ret_size   = bufsize;
    for (symbol = table-> symbols; symbol; symbol = symbol-> next)
      {
        /*  Save context key to buffer                                       */
        strcpy ((char *) buffer, symbol-> name);
        buffer += strlen (symbol-> name) + 1;

        /*  Save context data to buffer                                      */
        descr = symbol-> data;          /*  Symbol data is always a DESCR    */
        portable_size = htonl (descr-> size);
        *buffer++ = ((byte *) &portable_size) [0];
        *buffer++ = ((byte *) &portable_size) [1];
        *buffer++ = ((byte *) &portable_size) [2];
        *buffer++ = ((byte *) &portable_size) [3];
        memcpy (buffer, descr-> data, descr-> size);
        buffer += descr-> size;
      }
    return (0);
}


/**************************   LOAD SESSION CONTEXT   *************************/

MODULE load_session_context (void)
{
    DESCR
        symbols;                        /*  Symbol descriptor                */

    context_load (SCOPE_GLOBAL, msg_do-> global_size, msg_do-> global_data);
    context_load (SCOPE_LOCAL,  msg_do-> local_size,  msg_do-> local_data);

    /*  Normally if either of these two blocks are not found, we're
     *  starting a new session.  The form symbol table is populated
     *  with all the HTTP environment symbols passed from WTPMAN at
     *  the start of the session.
     */
    if (!context_get (SCOPE_GLOBAL, "_sess", &session, sizeof (session)))
      {
        memset (&session, 0, sizeof (session));
        session.disable_actions = DISABLE_HIDDEN;
      }
    if (!context_getsym (SCOPE_GLOBAL, "_sym", &session.symbols))
      {
        symbols.size = msg_do-> env_size;
        symbols.data = msg_do-> env_data;
        session.symbols = descr2symb (&symbols);
      }
    session.buffer_ = &buffer;
    session.program_callcode = msg_do-> call_result;
    session.back_used = FALSE;
    if (strlen (msg_do-> http_data) == 7
    &&   streq (msg_do-> http_data, "refresh"))
      {
        session.back_used = TRUE;
        msg_do-> http_data [0] = '\0';
      }
    strcpy  (session.program_name, msg_do-> program);
    strncpy ((char *) buffer.data, msg_do-> http_data, BUFFER_MAX);
    buffer.data [BUFFER_MAX] = 0;

    sym_assume_symbol (session.symbols, "uri", msg_do-> http_uri);
}


static void
context_load (int scope, qbyte bufsize, byte *buffer)
{
    size_t
        block_size;
    qbyte
        portable_size;                  /*  Block size in network order      */
    SYMTAB
        *table;
    SYMBOL
        *symbol;                        /*  Symbol we create in table        */

    table = context_init (scope);       /*  Initialise new symbol table      */
    while (bufsize)                     /*    and fill-up from buffer        */
      {
        symbol = sym_assume_symbol (table, (char *) buffer, NULL);
        bufsize -= (strlen ((char *) buffer) + 1);
        buffer  += (strlen ((char *) buffer) + 1);

        ((byte *) &portable_size) [0] = *buffer++;
        ((byte *) &portable_size) [1] = *buffer++;
        ((byte *) &portable_size) [2] = *buffer++;
        ((byte *) &portable_size) [3] = *buffer++;
        block_size = ntohl (portable_size);

        symbol-> data = mem_descr (buffer, block_size);
        bufsize -= 4;
        bufsize -= block_size;
        buffer  += block_size;
      }
}


/**************************   WTP REPLY DONE SHOW   **************************/

MODULE wtp_reply_done_show (void)
{
    wtp_doneshow ((char *) buffer.data,
                  msg_do-> global_size, msg_do-> global_data,
                  msg_do-> local_size,  msg_do-> local_data);
}


/**************************   WTP REPLY DONE CALL   **************************/

MODULE wtp_reply_done_call (void)
{
    wtp_donecall (session.program_to_call, 0, NULL,
                  msg_do-> global_size, msg_do-> global_data,
                  msg_do-> local_size,  msg_do-> local_data);
}


/*************************   WTP REPLY DONE RETURN   *************************/

MODULE wtp_reply_done_return (void)
{
    wtp_donereturn (0, NULL, msg_do-> global_size, msg_do-> global_data);
}


/**************************   WTP REPLY DONE EXIT   **************************/

MODULE wtp_reply_done_exit (void)
{
    wtp_doneexit ();
}


/**************************   WTP REPLY DONE ERROR   *************************/

MODULE wtp_reply_done_error (void)
{
    wtp_doneexit ();
}


/***************************   WTP ERROR INVALID   ***************************/

MODULE wtp_error_invalid (void)
{
    wtp_error (WTP_ERRORINVALID, "");
}


/**************************   WTP ERROR NOT FOUND   **************************/

MODULE wtp_error_not_found (void)
{
    wtp_error (WTP_ERRORNOTFOUND, "");
}


/*************************   INVOKE ACTIVE PROGRAM   *************************/

MODULE invoke_active_program (void)
{
    int
        prognbr,                        /*  Index into program list          */
        rc;

    strlwc (session.program_name);      /*  Compare lwc with lwc             */

    rc = FEEDBACK_UNKNOWN;              /*  Assume not found                 */
    for (prognbr = 0; wtp_broker_map [prognbr].name; prognbr++)
      {
        if (streq (session.program_name, wtp_broker_map [prognbr].name))
          {
            rc = ((ATP_FCT) wtp_broker_map [prognbr].function) (&session);
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
        case FEEDBACK_UNKNOWN:
            the_next_event = not_found_event;
            break;
        case FEEDBACK_ERROR:
            the_next_event = error_event;
            break;
        default:
            the_next_event = exit_event;
            break;
      }
     if (dbio_commit () != TRUE)
       {
         fprintf (stderr, "Error on commit: %d: %s",
                           dbio_error_code    (),
                           dbio_error_message ());
       }
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
    if (session.symbols)
        sym_delete_table (session.symbols);

    dbio_disconnect ();
    the_next_event = terminate_event;
}

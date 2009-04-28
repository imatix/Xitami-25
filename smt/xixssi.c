/*===========================================================================*
 *                                                                           *
 *  xixssi.c -                                                               *
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
    Synopsis:   Parse HTML page with SSI tags.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP definitions             */

/*- Definitions -------------------------------------------------------------*/

#ifdef AGENT_NAME
#  undef AGENT_NAME
#endif

#define AGENT_NAME   "xixssi"           /*  Our public name                  */

#define BUFFER_SIZE  1024

#define SSI_CONFIG(val, def)  sym_get_value (tcb-> config, val, def)

/* Default SSI parameters                                                    */
#define SSI_ERR_FORMAT  "<P>[Xitami SSI: \"%s\" produced errors]"
#define SSI_TIME_FORMAT "%A, %d-%b-%Y %H:%M:%S %Z"
#define SSI_SIZEFMT     "bytes"
#define SSI_EXEC        "0"
#define SSI_TIMEOUT     "30"
#define SSI_CGI_MONITOR "200"

/* Default SSI error message                                                 */
#define SSI_MSG_EXEC_PROTECT "#exec command not permitted for security reasons;"

/* SSI syntax                                                                */
#define BEGIN_TOKEN         "<!--#"
#define END_TOKEN           "-->"
#define ECHO_VARIABLE_TOKEN "var=\""

#define BEGIN_SIZE          5
#define END_SIZE            3
#define ECHO_VAR_SIZE       5

/* Strftime format
    %a   Abbreviated weekday name
    %A   Full weekday name
    %b   Abbreviated month name
    %B   Full month name
    %c   Date and time representation appropriate for locale
    %d   Day of month as decimal number (01 - 31)
    %H   Hour in 24-hour format (00 - 23)
    %I   Hour in 12-hour format (01 - 12)
    %j   Day of year as decimal number (001 - 366)
    %m   Month as decimal number (01 - 12)
    %M   Minute as decimal number (00 - 59)
    %p   Current locale’s A.M./P.M. indicator for 12-hour clock
    %S   Second as decimal number (00 - 59)
    %U   Week of year as decimal number, with Sunday as first day of week (00 - 51)
    %w   Weekday as decimal number (0 - 6; Sunday is 0)
    %W   Week of year as decimal number, with Monday as first day of week (00 - 51)
    %x   Date representation for current locale
    %X   Time representation for current locale
    %y   Year without century, as decimal number (00 - 99)
    %Y   Year with century, as decimal number
    %z, %Z   Time-zone name or abbreviation; no characters if time zone is unknown
    %%   Percent sign
*/

/*- Structures --------------------------------------------------------------*/

typedef struct _ssi_command             /*  SSI Command structure            */
{
    struct _ssi_command
         *next, *prev;                  /*    Pointer for linked list        */
    char *command;                      /*    SSI command                    */
    char *param;                        /*    Command parameters             */
    long begin_pos;                     /*    Position of command begin      */
    long end_pos;                       /*    Position of command end        */
    char *result;                       /*    Result of command execution    */
    long result_size;                   /*    Size of result                 */
} SSICMD;


typedef struct                          /*  Thread context block:            */
{
    event_t
        thread_type;                    /*    Thread type indicator          */
    struct_smt_wsx_request
        *request;                       /*    Incoming smt_wsx request       */
    SYMTAB
        *open_file,                     /*    Table of opened file           */
        *config,                        /*    Configuration value            */
        *environ;                       /*    Environement value             */
    QID
        sender_qid;                     /*    Sender thread QID              */
    char
        *cgi_stdout,                    /*    File name of CGI stdout        */
        **cgi_environ,                  /*    CGI environment buffer         */
        *result,                        /*    HTML result buffer             */
        *buffer,                        /*    Working buffer                 */
        *file_name;                     /*    SSI file name                  */
    long
        timeout,                        /*    SSI time out                   */
        result_size,                    /*    Size of result                 */
        file_date,                      /*    SSI file date                  */
        file_time,                      /*    SSI file time                  */
        file_size;                      /*    SSI file size                  */
    FILE
        *file;                          /*    SSI file handle                */
    LIST
        cmd_list;                       /*    List of SSI command structure  */
    SSICMD
        *command;                       /*    Current command structure      */
    dbyte
        command_count;                  /*    Number of SSI command          */
    Bool
        file_name_to_delete;            /*    Need free for file name        */
    PROCESS
        cgi_process_id;                 /*    ID of CGI process              */
} SSI_TCB;

#define TCB SSI_TCB

/*- Function prototypes -----------------------------------------------------*/

static SSICMD *ssi_command_alloc    (char *command, long begin, long end);
static void    ssi_command_free     (SSICMD *command);
static char   *get_parsed_file_name (TCB *tcb, char *file_name, Bool virtual);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    timeq,                              /*  Timer agent event queue          */
    operq;                              /*  Operator console event queue     */
static char
    error  [LINE_MAX    + 1],           /*  Error buffer                     */
    buffer [BUFFER_SIZE + 1];           /*  Working buffer                   */


#include "xixssi.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int xixssi_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */
#   include "xixssi.i"                  /*  Include dialog interpreter       */

    /*                      Method name   Event value     Priority          */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "WSX_REQUEST",    request_event,         0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",     time_out_event, SMT_PRIORITY_LOW);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",        master_event,          0);
    method_declare (agent, "_FILE",          file_event,            0);
    method_declare (agent, "_COMMAND",       command_event,         0);
    method_declare (agent, "_INCLUDE",       include_event,         0);

    method_declare (agent, "_CMD_END",       end_of_command_event,  0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create initial thread to manage master port                          */
    if ((thread = thread_create (AGENT_NAME, "main")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
      }
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> file                = NULL;
    tcb-> buffer              = NULL;
    tcb-> result              = NULL;
    tcb-> command_count       = 0;
    tcb-> cgi_stdout          = NULL;
    tcb-> cgi_environ         = NULL;
    tcb-> cgi_process_id      = NULL_PROCESS;
    tcb-> file_name_to_delete = FALSE;
    tcb-> timeout             = 0;
    list_reset (&tcb-> cmd_list);

    if (tcb-> thread_type == master_event
    ||  tcb-> thread_type == file_event)
      {
        tcb-> file_name = NULL;
        tcb-> environ   = NULL;
        tcb-> config    = NULL;
        tcb-> command   = NULL; 
        tcb-> open_file = NULL;
      }
    if (tcb-> thread_type == file_event) /* Used to check file already opened*/
        tcb-> open_file = sym_create_table ();
}


/***************************   CHECK THREAD TYPE   ***************************/

MODULE check_thread_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = tcb-> thread_type;
}


/*************************   CREATE COMMAND THREAD   *************************/

MODULE create_command_thread (THREAD *thread)
{
    SSICMD
        *cmd,                           /*  Current SSI command              */
        *next;                          /*  Next SSI command                 */
    THREAD
        *child_thread;                  /*  Handle to child threads          */
    
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    for (cmd = tcb-> cmd_list.next;
         cmd && cmd != (SSICMD *)&tcb-> cmd_list;
         cmd = next)
      {
        next = cmd-> next;

        /* If is config command, don't create thread                         */
        if (lexcmp (cmd-> command, "config") == 0)
            continue;

        child_thread = thread_create (AGENT_NAME, "");
        if (child_thread)
          {
            /* Create a include thread                                       */
            if (lexcmp (cmd-> command, "include") == 0)
              {
                SEND (&child_thread-> queue-> qid, "_INCLUDE", "");
                ((TCB *) child_thread-> tcb)-> thread_type = include_event;
                ((TCB *) child_thread-> tcb)-> open_file   = tcb-> open_file;
              }
            /* Create a command thread                                       */
            else
              {
                SEND (&child_thread-> queue-> qid, "_COMMAND", "");
                ((TCB *) child_thread-> tcb)-> thread_type = command_event;
              }
            ((TCB *) child_thread-> tcb)-> request     = tcb-> request;
            ((TCB *) child_thread-> tcb)-> sender_qid  = thread-> queue-> qid;
            ((TCB *) child_thread-> tcb)-> command     = cmd;
            ((TCB *) child_thread-> tcb)-> config      = tcb-> config;
            ((TCB *) child_thread-> tcb)-> environ     = tcb-> environ;
            ((TCB *) child_thread-> tcb)-> file_name   = tcb-> file_name;
            ((TCB *) child_thread-> tcb)-> file_size   = tcb-> file_size;
          }
       }
}


/***********************   CREATE MASTER FILE THREAD   ***********************/

MODULE create_master_file_thread (THREAD *thread)
{
    THREAD
        *child_thread;                  /*  Handle to child threads          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    child_thread = thread_create (AGENT_NAME, "file");
    if (child_thread)
      {
        SEND (&child_thread-> queue-> qid, "_FILE", "");
        ((TCB *) child_thread-> tcb)-> thread_type = file_event;
        ((TCB *) child_thread-> tcb)-> request     = tcb-> request;
        ((TCB *) child_thread-> tcb)-> sender_qid  = tcb-> sender_qid;
        tcb-> request = NULL;
      }
}


/**************************   GET ALL SSI COMMAND   **************************/

MODULE get_all_ssi_command (THREAD *thread)
{
    char
        *begin,                         /*  Begin of SSI command string      */
        *end;                           /*  End of SSI command string        */
    SSICMD
        *command;                       /*  SSI command structure            */
    Bool
        alloc_error = FALSE;            /*  Indicate allocation error        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> command_count = 0;

    begin = strstr (tcb-> buffer, BEGIN_TOKEN);
    while (begin)
      {
        end = strstr (begin + BEGIN_SIZE, END_TOKEN);
        if (end)
          {
             *begin = '\0';
             *end   = '\0';
             command = ssi_command_alloc (begin + BEGIN_SIZE,
                                   (long)(begin - tcb-> buffer),
                                   (long)(end + END_SIZE - tcb-> buffer));            
             if (command)
               {
                 tcb-> command_count++;
                 list_relink_after (&tcb-> cmd_list, command);
               }
             else
                 alloc_error = TRUE;

             begin = strstr (end + END_SIZE + 1, BEGIN_TOKEN);
          }
        else                            /* Missing end of command           */
          {
            begin = NULL;
            strcpy (error, "Syntax error: Missing end of SSI command");
            raise_exception (error_event);
            return;
          }
      }

    if (alloc_error)
      {
        strcpy (error, "Memory allocattion error in command allocation");
        the_next_event = error_event;
      }
    else
        the_next_event = tcb-> command_count? ok_event: no_command_event;
}


/*  -------------------------------------------------------------------------
    Function: ssi_command_alloc - internal

    Synopsis: Allocate a SSI command structure and initialise values
    -------------------------------------------------------------------------*/

static SSICMD *
ssi_command_alloc (char *command, long begin, long end)
{
    SSICMD
        *cmd = NULL;                    /*  Command structure                */
    char
        *parameter;                     /*  Parameter pointer                */

    ASSERT (command);

    cmd = mem_alloc (sizeof (SSICMD));
    if (cmd)
      {
        memset (cmd, 0, sizeof (SSICMD));
        list_reset (cmd);               /*  Reset pointer to linked list     */
        cmd-> command   = mem_strdup (command);
        cmd-> begin_pos = begin;
        cmd-> end_pos   = end;

        if (cmd-> command == NULL)
          {
            mem_free (cmd);
            cmd = NULL;
          }
        else
          {
            parameter = strchr (cmd-> command, ' ');
            *parameter++ = '\0';
            cmd-> param = parameter;
          }
      }
    return (cmd);
}


/****************************   GET WSX REQUEST   ****************************/

MODULE get_wsx_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> request = NULL;
    get_smt_wsx_request (thread-> event-> body, &tcb-> request);

    if (tcb-> request == NULL)
      {
        /*  The request can only be null if there is no memory left          */
        send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_NOTFOUND);
        the_next_event = exception_event;
      }

    /* Get QID of HTTP thread                                                */
    tcb-> sender_qid = thread-> event-> sender;
}


/****************************   MAKE RETURN FILE   ***************************/

MODULE make_return_file (THREAD *thread)
{
    long
        result_size;                    /*  Size of result page              */
    SSICMD
        *cmd,                           /*  Current command                  */
        *next;                          /*  Next command                     */
    char
        *next_string,                   /*  Point to next block              */
        *last;                          /*  Point to current end of result   */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Calculate size of result page                                        */
    result_size = tcb-> file_size;
    for (cmd = tcb-> cmd_list.next;
         cmd && cmd != (SSICMD *) &tcb-> cmd_list;
         cmd = next)
      {
        next = cmd-> next;
        result_size += cmd-> result_size - (cmd-> end_pos - cmd-> begin_pos);
      }

    tcb-> result_size = result_size;
    tcb-> result      = mem_alloc (result_size + 1);
    if (tcb-> result == NULL)
      {
        strcpy (error, "Insufficient memory");
        raise_exception (error_event);
        return;
      }    

    strcpy (tcb-> result, tcb-> buffer);
    last = &strlast (tcb-> result);

    for (cmd = tcb-> cmd_list.next;
         cmd && cmd != (SSICMD *)&tcb-> cmd_list;
         cmd = next)
      {
        next = cmd-> next;

        /*  If command has result                                            */
        if (cmd-> result 
        &&  cmd-> result_size)
          {
            strcpy (last, cmd-> result);
            last += cmd-> result_size;
          }

        /*  If not end of file                                               */
        if (cmd-> end_pos < tcb-> file_size - 1)
          {
            next_string = tcb-> buffer + cmd-> end_pos;
            if (*next_string != '\0')   /*  If you have text between command */
              {
                strcpy (last, next_string);
                last += strlen (next_string);
              }
          }
      }
}


/***************************   SEND WSX RESPONSE   ***************************/

MODULE send_wsx_response (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_wsx_ok (&tcb-> sender_qid, tcb-> result);
}


/***************************   MAKE CONFIG TABLE   ***************************/

MODULE make_config_table (THREAD *thread)
{
    DESCR
        symbols;                        /*  Symbol descriptor                */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    symbols.size  = tcb-> request-> symbols_size;
    symbols.data  = tcb-> request-> symbols_data;
    tcb-> environ = descr2symb (&symbols);

    symbols.size  = tcb-> request-> config_size;
    symbols.data  = tcb-> request-> config_data;
    tcb-> config = descr2symb (&symbols);

    /*  Sort configuration table, http library need sorted table             */
    if (tcb-> config)
        sym_sort_table (tcb-> config, NULL);

    tcb-> file_name = tcb-> request-> filename;
}


/*****************************   OPEN SSI FILE   *****************************/

MODULE open_ssi_file (THREAD *thread)
{
    time_t
        file_time;
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT (tcb-> file_name);

    /* Check if file is not already open                                     */
    if (sym_get_value (tcb-> open_file, tcb-> file_name, NULL) != NULL)
      {
        sprintf (error, "%s is already open", tcb-> file_name);
        raise_exception (command_error_event);
        return;
      }

    tcb-> file = fopen (tcb-> file_name, "rb");
    if (tcb-> file == NULL)
      {
        sprintf (error, "Can't open ssi file %s", tcb-> file_name);
        raise_exception (error_event);
      }
    else
      {
        sym_assume_symbol (tcb-> open_file, tcb-> file_name, "");

        file_time = get_file_time (tcb-> file_name);
        tcb-> file_date = timer_to_date (file_time);
        tcb-> file_time = timer_to_time (file_time);
      }
}


/*****************************   READ SSI FILE   *****************************/

MODULE read_ssi_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get File size                                                        */
    fseek (tcb-> file, 0, SEEK_END);
    tcb-> file_size = ftell (tcb-> file);
    fseek (tcb-> file, 0, SEEK_SET);

    /*  Allocate a buffer to get entire content of file                      */
    tcb-> buffer = mem_alloc (tcb-> file_size + 1);
    if (tcb-> buffer == NULL)
      {
        strcpy (error, "Insufficient memory");
        raise_exception (error_event);
        return;
      }

    *tcb-> buffer = '\0';
    tcb-> file_size = (long)fread (tcb-> buffer, 1, (size_t) tcb-> file_size,
                                   tcb-> file);
    tcb-> buffer [tcb-> file_size] = '\0';
}


/***********************   SET NO COMMAND RETURN FILE   **********************/

MODULE set_no_command_return_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  If file does not have any SSI commands, the result is the file       */
    tcb-> result = tcb-> buffer;
    tcb-> buffer = NULL;
}


/*********************   CHECK IF ALL COMMAND COMPLETE   *********************/

MODULE check_if_all_command_complete (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = (tcb-> command_count <= 0)? ok_event: more_event;
}


/****************************   GET COMMAND TYPE   ***************************/

MODULE get_command_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (lexcmp (tcb-> command-> command, "echo")     == 0)
        the_next_event = echo_event;
    else
    if (lexcmp (tcb-> command-> command, "exec")     == 0)
        the_next_event = exec_event;
    else
    if (lexcmp (tcb-> command-> command, "fsize")    == 0)
        the_next_event = fsize_event;
    else
    if (lexcmp (tcb-> command-> command, "flastmod") == 0)
        the_next_event = flastmod_event;

    else
        the_next_event = command_error_event;
}


/**********************   INCREMENT COMMAND END COUNT   **********************/

MODULE increment_command_end_count (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> command_count--;
}


/***************************   GET VARIABLE VALUE   **************************/

MODULE get_variable_value (THREAD *thread)
{
    char
        *var;                           /*  Variable of echo command         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    var = tcb-> command-> param;

    if (var)
      {
        var = strstr (var, ECHO_VARIABLE_TOKEN);
        if (var)
          {
            var += ECHO_VAR_SIZE;
            tcb-> command-> param = var;

            /* Remove char '"' at end of variable                            */
            var = strchr (var, '"');
            if (var)
                *var = '\0';

            if (lexcmp (tcb-> command-> param, "DOCUMENT_NAME") == 0)
                the_next_event = doc_name_event;
            else
            if (lexcmp (tcb-> command-> param, "DOCUMENT_URI")  == 0)
                the_next_event = doc_uri_event;
            else
            if (lexcmp (tcb-> command-> param, "DATE_GMT")      == 0)
                the_next_event = date_gmt_event;
            else
            if (lexcmp (tcb-> command-> param, "DATE_LOCAL")    == 0)
                the_next_event = date_local_event;
            else
            if (lexcmp (tcb-> command-> param, "LAST_MODIFIED") == 0)
                the_next_event = last_modified_event;
            else
            if (lexcmp (tcb-> command-> param, "QUERY_STRING_UNESCAPED") == 0)
                the_next_event = query_string_event;
            else
            if (sym_lookup_symbol (tcb-> environ,
                                   tcb-> command-> param) != NULL)
                the_next_event = environ_event;
            else
              {
                sprintf (error, "Unrecognised #echo variable %s",
                                tcb-> command-> param);
                the_next_event = command_error_event;
              }
          }
        else
          {
            strcpy (error, "syntax error in #echo variable");
            the_next_event = command_error_event;
          }
      }
    else
      {
        strcpy (error, "#echo variable missing");
        the_next_event = command_error_event;
      }
}


/*************************   SIGNAL END OF COMMAND   *************************/

MODULE signal_end_of_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&tcb-> sender_qid, "_CMD_END", "");
}


/************************   STORE DATE GMT IN RESULT   ***********************/

MODULE store_date_gmt_in_result (THREAD *thread)
{
    time_t
        ltime;                          /*  Current date and time            */
    char
        *timefmt;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    time (&ltime);

    timefmt = SSI_CONFIG ("ssi:timefmt", SSI_TIME_FORMAT);
    tcb-> command-> result_size = strftime (buffer, BUFFER_SIZE,
                                            timefmt, safe_gmtime (&ltime));
    if (tcb-> command-> result_size)
        tcb-> command-> result = mem_strdup (buffer);
}


/***********************   STORE DATE LOCAL IN RESULT   **********************/

MODULE store_date_local_in_result (THREAD *thread)
{
    time_t
        ltime;                          /*  Current date and time            */
    char
        *timefmt;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    time (&ltime);

    timefmt = SSI_CONFIG ("ssi:timefmt", SSI_TIME_FORMAT);
    tcb-> command-> result_size = strftime (buffer, BUFFER_SIZE,
                                            timefmt, safe_localtime (&ltime));
    if (tcb-> command-> result_size)
        tcb-> command-> result = mem_strdup (buffer);
}


/*********************   STORE DOCUMENT NAME IN RESULT   *********************/

MODULE store_document_name_in_result (THREAD *thread)
{
    char
        *file;                          /*  File name                        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /* Get simple file name (remove full path)                               */
    file = strrchr (tcb-> file_name, '/');
    if (file)
        file++;
    else
        file = tcb-> file_name;

    tcb-> command-> result = mem_strdup (file);
    if (tcb-> command-> result)
        tcb-> command-> result_size = strlen (tcb-> command-> result);
}


/**********************   STORE DOCUMENT URI IN RESULT   *********************/

MODULE store_document_uri_in_result (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> request-> request_url)
        tcb-> command-> result = mem_strdup (tcb-> request-> request_url);
    if (tcb-> command-> result)
        tcb-> command-> result_size = strlen (tcb-> command-> result);
  
}


/*********************   STORE LAST MOD DATE IN RESULT   *********************/

MODULE store_last_mod_date_in_result (THREAD *thread)
{
    time_t
        file_time;                      /*  Current file time                */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    file_time = get_file_time (tcb-> file_name);
    tcb-> command-> result_size =
        strftime (buffer, BUFFER_SIZE, SSI_TIME_FORMAT,
                  safe_localtime (&file_time));

    if (tcb-> command-> result_size > 0)
        tcb-> command-> result = mem_strdup (buffer);
}


/***********************   STORE SSI ERROR IN RESULT   ***********************/

MODULE store_ssi_error_in_result (THREAD *thread)
{
    char
        *errmsg;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    errmsg = SSI_CONFIG ("ssi:errmsg", SSI_ERR_FORMAT);
    sprintf (buffer, errmsg, error);

    tcb-> command-> result = mem_strdup (buffer);
    if (tcb-> command-> result)
        tcb-> command-> result_size = strlen (buffer);

    /*  Send error to console                                                */
    sendfmt (&operq, "ERROR", "xixssi: %s", buffer);
}


/*********************   STORE ENVIRON VALUE IN RESULT   *********************/

MODULE store_environ_value_in_result (THREAD *thread)
{
    SYMBOL
        *symbol;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    symbol = sym_lookup_symbol (tcb-> environ, tcb-> command -> param);
    if (symbol)
      {
        tcb-> command-> result = mem_strdup (symbol-> value);
        if (tcb-> command-> result)
            tcb-> command-> result_size = strlen (tcb-> command-> result);
      }
}


/***********************   STORE FILE SIZE IN RESULT   ***********************/

MODULE store_file_size_in_result (THREAD *thread)
{
    char
        *sizefmt;
    double
        size;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> file_size = get_file_size (tcb-> file_name);

    sizefmt = SSI_CONFIG ("ssi:sizefmt", SSI_SIZEFMT);

    /*  If size format is 'bytes'                                            */
    if (lexcmp (sizefmt, "bytes") == 0)
        sprintf (buffer, "%ld bytes", tcb-> file_size);
    /*  If size format is abbrev, calculate size in Kbyte or Mbyte           */ 
    else
      {
        size = (double)tcb-> file_size / 1024.0;
        if (size > 1024.0)              /* If size > 1024 Kb -> size in Mb   */
          {
            size /= 1024.0; 
            sprintf (buffer, "%.2f Mbytes", size);
          }
        else
            sprintf (buffer, "%.2f Kbytes", size);
      }

    tcb-> command-> result = mem_strdup (buffer);
    if (tcb-> command-> result)
        tcb-> command-> result_size = strlen (tcb-> command-> result);
}


/**********************   STORE QUERY STRING IN RESULT   *********************/

MODULE store_query_string_in_result (THREAD *thread)
{
    char
        *value;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    
    value = sym_get_value (tcb-> environ, "QUERY_STRING", NULL);
    if (value)
      {
        tcb-> command-> result = mem_strdup (value);
        if (tcb-> command-> result)
            tcb-> command-> result_size = strlen (tcb-> command-> result);
      }
}


/*************************   FREE INCLUDE RESOURCE   *************************/

MODULE free_include_resource (THREAD *thread)
{
    SSICMD
        *cmd,
        *next;
    SYMBOL
        *symbol;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> file)
        fclose (tcb-> file);

    /*  Free symbol for include open file                                    */
    symbol = sym_lookup_symbol (tcb-> open_file, tcb-> file_name);
    if (symbol)
        sym_delete_symbol (tcb-> open_file, symbol);

    if (tcb-> buffer)
        mem_free(tcb-> buffer);
    if (tcb-> result)
        mem_free(tcb-> result);

    /*  Free included SSI command                                            */
    for (cmd = tcb-> cmd_list.next;
         cmd && cmd != (SSICMD *)&tcb-> cmd_list;
         cmd = next)
      {
        next = cmd-> next;
        ssi_command_free (cmd);
      }
}


/*****************   STORE CURRENT LAST MOD DATE IN RESULT   *****************/

MODULE store_current_last_mod_date_in_result (THREAD *thread)
{
    time_t
        file_time;                      /*  Current file time                */
    char
        *timefmt;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    file_time = get_file_time (tcb-> file_name);
    timefmt = SSI_CONFIG ("ssi:timefmt", SSI_TIME_FORMAT);
    tcb-> command-> result_size = strftime (buffer, BUFFER_SIZE,
                                            timefmt, safe_localtime (&file_time));
    if (tcb-> command-> result_size > 0)
        tcb-> command-> result = mem_strdup (buffer);
}


/*************************   GET FILE NAME FROM URI   ************************/

MODULE get_file_name_from_uri (THREAD *thread)
{
    char
        *last,
        *uri;
    Bool
        virtual = FALSE;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> file_name = NULL;

    /*  Virtual file name, need to resolve alias and virtual host            */
    uri = strstr (tcb-> command-> param, "virtual=\"");
    if (uri)
      {
        virtual = TRUE;
        uri += 9;
      }
    else
      {
        /*  Absolute file name relative to document root                     */
        uri = strstr (tcb-> command-> param, "file=\"");
        if (uri)
            uri += 6;
        else
          {
            /*  CGI file name, need to resolve cgi alias                     */
            uri = strstr (tcb-> command-> param, "cgi=\"");
            if (uri == NULL)
                uri = strstr (tcb-> command-> param, "cmd=\"");
            if (uri)
              {
                uri += 5;
                virtual = TRUE;
              }
          }
      }  

    if (uri)
      {
        /*  Remove caracter '"' at end of file name                          */
        last = strchr (uri, '"');
        if (last)
            *last = '\0';

        tcb-> file_name = get_parsed_file_name (tcb, uri, virtual);
        tcb-> file_name_to_delete = TRUE;
      }
}


/*  -------------------------------------------------------------------------
    Function: get_parsed_file_name - internal

    Synopsis: make true file name. If is virtual, resolve alias and use root
    directory value. If is not virtual check if file name don't content '..'
    and force to be relative to document directory.
    -------------------------------------------------------------------------*/

static char *
get_parsed_file_name (TCB *tcb, char *file_name, Bool virtual)
{
    static char
        *file;                          /* File name                         */
    char
        *cgi_url,                       /* CGI url                           */ 
        *cgi_root,                      /* CGI root directory                */
        *document_root;                 /* Document root directory           */

    ASSERT (file_name);
    ASSERT (tcb);

    file = NULL;
 
    document_root = sym_get_value (tcb-> environ, "DOCUMENT_ROOT",  "./");
    if (virtual)
      {
        cgi_url   = sym_get_value (tcb-> config,  "server:cgi-url", NULL);
        cgi_root  = sym_get_value (tcb-> environ, "CGI_ROOT",       NULL);
        file = http_map_uri (tcb-> config, document_root, cgi_root,
                             file_name, cgi_url, 0);
      }
    else
      {
        /* If file name is not virtual, is relative to document root         */
        if (strstr (file_name, "..") != NULL)
            return (NULL);
        xstrcpy (buffer, document_root, "/", file_name, NULL);
        file = mem_strdup (buffer);
      }
    return (file);
}


/************************   MAKE INCLUDE RETURN FILE   ***********************/

MODULE make_include_return_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Move result of include into command structure                        */
    tcb-> command-> result      = tcb-> result;
    tcb-> command-> result_size = tcb-> result_size;
    tcb-> result = NULL;
}


/**********************   SET NO COMMAND INCLUDE FILE   **********************/

MODULE set_no_command_include_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Move include file into command structure                             */
    tcb-> command-> result      = tcb-> buffer;
    tcb-> command-> result_size = tcb-> file_size;
    tcb-> buffer = NULL;
}


/************************   CHECK FILE OR DIRECTORY   ************************/

MODULE check_file_or_directory (THREAD *thread)
{
    char
        *param;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Remove URL parameter from file name                                  */
    param = strchr (tcb-> file_name, '?');
    if (param)
        *param = '\0';

    if (file_is_executable (tcb-> file_name))
        the_next_event = executable_event;
    else
        the_next_event = command_error_event;

    if (param)
        *param = '?';
}


/**************************   CLOSE CHILD PROCESS   **************************/

MODULE close_child_process (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> cgi_process_id != NULL_PROCESS)
      {
        if (process_status (tcb-> cgi_process_id) == PROCESS_RUNNING)
            process_kill  (tcb-> cgi_process_id);
        else
            process_close (tcb-> cgi_process_id);

        tcb-> cgi_process_id = NULL_PROCESS;
      }
}


/***************************   CREATE CGI PROCESS   **************************/

MODULE create_cgi_process (THREAD *thread)
{
    static HTTP_CONTEXT
        http;                           /*  Temporary HTTP context           */
    char
        *param,
        *escaped,                       /*  CGI filename, escaped            */
        *command,                       /*  CGI command to execute           */
        *workdir;                       /*  CGI working directory            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    memset (&http, 0, sizeof (HTTP_CONTEXT));

    /*  Extract URL parameters                                               */
    param = strchr (tcb-> file_name, '?');
    if (param)
      {
        *param++ = '\0';
        http.url_param = mem_strdup (param);
      }
    http.config    = tcb-> config;
    http.file_name = mem_strdup (tcb-> file_name);

    tcb-> cgi_stdout = http_pipe (&http, "cgo");
    /*  Remove old stdout file if any                                        */
    if (file_exists (tcb-> cgi_stdout))
        file_delete (tcb-> cgi_stdout);

    /*  Set CGI input/output filename symbols                                */
    strcpy (buffer, tcb-> cgi_stdout);
    if (*SSI_CONFIG ("cgi:msdos-style", "0") == '1')
        strconvch (buffer, '/', '\\');
    sym_assume_symbol (tcb-> environ, "Cgi-Stdout", buffer);
    sym_assume_symbol (tcb-> environ, "Cgi-Stderr", SSI_CONFIG ("cgi:errlog", ""));

    tcb-> cgi_environ = symb2env (tcb-> environ);
    if (tcb-> cgi_environ == NULL)
      {
        mem_strfree (&tcb-> cgi_stdout);
        if (http.url_param)
            mem_free (http.url_param);
        if (http.file_name)
            mem_free (http.file_name);
        strcpy (error, "Insufficient memory");
        raise_exception (command_error_event);
        return;
      }

    /*  Get the working directory                                            */
    workdir = SSI_CONFIG ("cgi:workdir", "-");
    if (streq (workdir, "-"))           /*  '-' means use script directory   */
      {
        if (strrchr (http.file_name, '/'))
          {
            http.script_path = mem_strdup (http.file_name);
            *strrchr (http.script_path, '/') = '\0';
          }
        workdir = http.script_path;
      }
    /*  Create the process                                                   */
    escaped = process_esc (NULL, http.file_name);

    /*  If URL arguments contain '=' we pass them in the QUERY_STRING only;
     *  if they do not contain '=' then we split on '+' and pass as args to
     *  the CGI process.
     */
    if (http.url_param && strchr (http.url_param, '='))
        command = mem_strdup (escaped);
    else
      {
        xstrcpy_debug ();
        command = xstrcpy (NULL, escaped, " ", http.url_param, NULL);
        strconvch (command, '+', ' ');
      }
    /*  Set sflproc flag for separate virtual machines                       */
    /*  This only affects 32-bit Windows systems                             */
    process_compatible = *SSI_CONFIG ("win32:16bit-cgi", "0") == '1';

    if (*SSI_CONFIG ("cgi:stdio", "1") == '1')
        tcb-> cgi_process_id = process_create (
            command,                    /*  Command to run                   */
            NULL,                       /*  Arguments for command            */
            workdir,                    /*  Working directory                */
            NULL,                       /*  Redirect stdin from here         */
            tcb-> cgi_stdout,           /*  Redirect stdout to here          */
            SSI_CONFIG ("cgi:errlog", NULL),/*  Redirect stderr to here      */
            tcb-> cgi_environ,          /*  Environment table                */
            FALSE);                     /*  Wait until finished?             */
    else
        tcb-> cgi_process_id = process_create (
            command,                    /*  Command to run                   */
            NULL,                       /*  Arguments for command            */
            workdir,                    /*  Working directory                */
            NULL,                       /*  Redirect stdin from here         */
            NULL,                       /*  Redirect stdout to here          */
            NULL,                       /*  Redirect stderr to here          */
            tcb-> cgi_environ,          /*  Environment table                */
            FALSE);                     /*  Wait until finished?             */

    mem_free (command);
    mem_free (escaped);

    if (http.url_param)
        mem_free (http.url_param);
    if (http.file_name)
        mem_free (http.file_name);
    if (http.script_path)
        mem_free (http.script_path);

    if (tcb-> cgi_process_id == NULL_PROCESS)
      {
        strcpy (error, "Error in CGI execution");
        raise_exception (command_error_event);
      }
}


/***********************   STORE CGI OUTPUT IN RESULT   **********************/

MODULE store_cgi_output_in_result (THREAD *thread)
{
    FILE
        *out;                           /*  Output file of CGI               */
    char
        *body;                          /*  Pointer to end of header         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> command-> result_size = get_file_size (tcb-> cgi_stdout);
    if (tcb-> command-> result_size > 0)
      {
        out = fopen (tcb-> cgi_stdout, "rb");
        if (out)
          {
            tcb-> command-> result = mem_alloc (tcb-> command-> result_size);
            if (tcb-> command-> result)
                fread (tcb-> command-> result, 1,
                       tcb-> command-> result_size, out);

            /*  Remove CGI header                                            */
            body = strstr (tcb-> command-> result, "<html>");
            if (body == NULL)
                body = strstr (tcb-> command-> result, "<HTML>");
            if (body)
              {
                if (body != tcb-> command-> result)
                  {
                    tcb-> command-> result_size -=
                                        (long)(body - tcb-> command-> result);
                    memmove (tcb-> command-> result, body,
                                                 tcb-> command-> result_size);
                    tcb-> command-> result [tcb-> command-> result_size] = '\0';
                  }
              }
            fclose (out);
          }
      }
}


/****************************   WAIT PROCESS END   ***************************/

MODULE wait_process_end (THREAD *thread)
{
    int
       state;
    HTTP_CONTEXT
       http;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    http.cgi_process_id = tcb-> cgi_process_id;

    state = http_process_state (&http);
    if (state == CGI_STATE_END)         /*  CGI finished okay                */
        the_next_event = finished_event;
    else
    if (state == CGI_STATE_ERROR)       /*  CGI aborted                      */
      {
        strcpy (error, "CGI aborted");
        raise_exception (command_error_event);
      }
    else                                /*  CGI ran out of time              */
        /*  Ask timer to send us an event after the monitor timeout          */
        send_alarm (&timeq, 0,
             atol (SSI_CONFIG ("cgi:monitor", SSI_CGI_MONITOR)) / 10, 0, NULL);
}


/***********************   EXECUTE ALL CONFIG COMMAND   **********************/

MODULE execute_all_config_command (THREAD *thread)
{
    SSICMD
        *cmd,
        *next;
    char
        *end,
        *value,
        *format;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    for (cmd = tcb-> cmd_list.next;
         cmd && cmd != (SSICMD *)&tcb-> cmd_list;
         cmd = next)
      {
        next = cmd-> next;

        /*  If is a config command                                           */
        if (lexcmp (cmd-> command, "config") == 0)
          {
            format = NULL;
            /*  Error Message format                                         */
            if (lexncmp (cmd-> param, "errmsg=", 7) == 0)
              {
                format = "ssi:errmsg";
                value = cmd-> param + 7;
              }
            else
            /*  Time format                                                  */
            if (lexncmp (cmd-> param, "timefmt=", 8) == 0)
              {
                format = "ssi:timefmt";
                value = cmd-> param + 8;
              }
            else
            /*  Size format (bytes or abbrev)                                */
            if (lexncmp (cmd-> param, "sizefmt=", 8) == 0)
              {
                format = "ssi:sizefmt";
                value = cmd-> param + 8;
              }
            else  
              {
                sprintf (error, "Invalid config value %s", cmd-> param);
                store_ssi_error_in_result (thread);
                value = "";
              }
            if (format)
              {
                end = strrchr (value, '"');
                if (end)
                    *(++end) = '\0';
                sym_assume_symbol (tcb-> config, format, value);   
              }
            tcb-> command_count--;
          }
      }
}


/*************************   CHECK IF CGI PROTECTED   ************************/

MODULE check_if_cgi_protected (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (*SSI_CONFIG ("ssi:exec", SSI_EXEC) == '0')
      {      
        strcpy (error, SSI_MSG_EXEC_PROTECT);
        the_next_event = command_error_event;
      }
    else
        the_next_event = ok_event;
}


/*****************************   FLUSH TIME OUT   ****************************/

MODULE flush_time_out (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> timeout > 0)
        event_send (
            &timeq,                     /*  Send to specified queue          */
            &thread-> queue-> qid,      /*  Queue for reply                  */
            "FLUSH",                    /*  Name of event to send            */
            NULL, 0,                    /*  No event body                    */
            NULL, NULL, NULL,           /*  No response events               */
            0);                         /*  No timeout                       */
}


/******************************   SET TIME OUT   *****************************/

MODULE set_time_out (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> timeout = atol (SSI_CONFIG ("ssi:timeout", SSI_TIMEOUT));
    if (tcb-> timeout > 0)
        send_alarm (&timeq, 0, tcb-> timeout * 100, 0, NULL);
}


/*****************************   SIGNAL TIMEOUT   ****************************/

MODULE signal_timeout (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR", "xixssi: timeout for file %s", tcb-> file_name);
}


/****************************   SIGNAL SSI ERROR   ***************************/

MODULE signal_ssi_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR", "xixssi: %s", error);
}


/****************************   RETURN WSX ERROR   ***************************/

MODULE return_wsx_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> thread_type == file_event)
        send_wsx_error (&tcb-> sender_qid, HTTP_RESPONSE_NOTFOUND);
}


/***************************   FREE ALL RESOURCES   **************************/

MODULE free_all_resources (THREAD *thread)
{
    SSICMD
        *cmd,
        *next;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> request)
        free_smt_wsx_request (&tcb-> request);
    if (tcb-> environ)
        sym_delete_table (tcb-> environ);
    if (tcb-> config)
        sym_delete_table (tcb-> config);
    if (tcb-> open_file)
        sym_delete_table (tcb-> open_file);
    if (tcb-> file)
        fclose (tcb-> file);
    if (tcb-> buffer)
        mem_free(tcb-> buffer);
    if (tcb-> result)
        mem_free(tcb-> result);

    /* Free all command structure                                            */
    for (cmd = tcb-> cmd_list.next;
         cmd && cmd != (SSICMD *)&tcb-> cmd_list;
         cmd = next)
      {
        next = cmd-> next;
        ssi_command_free (cmd);
      }
}

/*  -------------------------------------------------------------------------
    Function: ssi_command_free - internal

    Synopsis: Free a SSI command structure
    -------------------------------------------------------------------------*/

static void
ssi_command_free  (SSICMD *cmd)
{
    ASSERT (cmd);

    if (cmd-> command)
        mem_free (cmd-> command);
    if (cmd-> result)
        mem_free (cmd-> result);

    mem_free (cmd);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> file_name_to_delete
    &&  tcb-> file_name)
        mem_strfree (&tcb-> file_name);

    if (tcb-> cgi_process_id != NULL_PROCESS)
        close_child_process (thread);
    if (tcb-> cgi_stdout)
        mem_strfree (&tcb-> cgi_stdout);
    if (tcb-> cgi_environ)
      {
        strtfree (tcb-> cgi_environ);
        tcb-> cgi_environ = NULL;
      }
    the_next_event = terminate_event;
}


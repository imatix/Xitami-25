/*===========================================================================*
 *                                                                           *
 *  smtupmd.c -                                                              *
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
    Synopsis:   Stops and starts unattended tasks in various ways.  See
                SMT documentation for a full description.  Creates a single
                unnamed thread automatically, monitoring port 5050.
                Sends errors and information messages to the SMTOPER agent.

*/
#include "smtdefn.h"                    /*  SMT agent definitions            */
#include "smtupm.h"                     /*  SMT UPM definitions              */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   SMT_UPMD           /*  Our public name                  */
#define UPM_VERSION  "1.0"              /*  UPM daemon version               */

typedef struct _TASK {                  /*  Task descriptor                  */
    struct _TASK                        /*                                   */
           *next, *prev;                /*    Doubly-linked list             */
    QID     qid;                        /*    Task thread queue id           */
    QID     slotq;                      /*    Time slot queue id             */
    char   *name;                       /*    Name of task                   */
    char   *workdir;                    /*    Working directory, if any      */
    char   *std_in;                     /*    Desired stdin device           */
    char   *std_out;                    /*    Desired stdout device          */
    char   *std_err;                    /*    Desired stderr device          */
    char   *run_idle;                   /*    Execute when task idles        */
    char   *run_startup;                /*    Execute to run task            */
    char   *run_cancel;                 /*    Execute when cancelling task   */
    char   **env_list;                  /*    Environment symbol list        */
    PROCESS pid;                        /*    Running process ID             */
} TASK;

static NODE
    tasks;                              /*  Task list header                 */

typedef struct {                        /*  Thread context block:            */
    event_t thread_type;                /*    Thread type indicator          */
    sock_t  handle;                     /*    Handle for i/o, if used        */
    dbyte   message_id;                 /*    Message identifier code        */
    char    message_body [LINE_MAX];    /*    Message body string            */
    TASK   *task;                       /*    For task threads               */
} TCB;


/*- Function prototypes -----------------------------------------------------*/

static void    smtupmd_term      (void);
static TASK   *task_create       (char *name);
static void    task_destroy      (TASK *task);
static void    free_task_values  (TASK *task);
static void    canonise_name     (char *name);
static void    put_upm_message   (THREAD *thread, dbyte ident, void *body);
static dbyte   get_upm_message   (THREAD *thread, char *body);
static PROCESS run_command       (THREAD *thread, char *command, Bool wait);

/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    operq,                              /*  Operator console event queue     */
    sockq,                              /*  Socket agent event queue         */
    tranq,                              /*  Transfer agent event queue       */
    timeq,                              /*  Timer agent event queue          */
    logq;                               /*  Logging agent event queue        */

static byte
    msg_body [LINE_MAX];                /*  Message to transfer agent        */
static DESCR                            /*  Descriptor for exdr_writed       */
    msg = { LINE_MAX, msg_body };
static int
    msg_size;                           /*  Size of formatted msg_body       */


/*- Global variables set from ini file or filled with default values --------*/

static char
    *inifile,                           /*  Ini file, '.ini' assumed         */
    *portname,                          /*  Port number as ASCII string      */
    *logfile_name;                      /*  Main log file                    */


#include "smtupmd.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int smtupmd_init (char *p_inifile, char *p_portname)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to various threads        */
#   include "smtupmd.i"                 /*  Include dialog interpreter       */

    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN", shutdown_event, SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  ok_event,          0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,          0);
    method_declare (agent, "SOCK_READ_OK",   ok_event,          0);
    method_declare (agent, "SOCK_WRITE_OK",  ok_event,          0);
    method_declare (agent, "SOCK_CLOSED",    sock_closed_event, 0);
    method_declare (agent, "SOCK_ERROR",     sock_error_event,  0);
    method_declare (agent, "SOCK_TIMEOUT",   sock_error_event,  0);

    /*  Reply events from transfer agent                                     */
    method_declare (agent, "TRAN_GETF_OK",   ok_event,          0);
    method_declare (agent, "TRAN_PUTF_OK",   SMT_NULL_EVENT,    0);
    method_declare (agent, "TRAN_CLOSED",    sock_closed_event, 0);
    method_declare (agent, "TRAN_ERROR",     sock_error_event,  0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",     task_alarm_event,  0);

    /*  Reply events from time slot agent                                    */
    method_declare (agent, "SWITCH_ON",      start_auto_event,  0);
    method_declare (agent, "SWITCH_OFF",     stop_auto_event,   0);

    /*  Private methods used to pass initial thread arguments                */
    method_declare (agent, "_MASTER",        master_event,      0);
    method_declare (agent, "_CONTROL",       control_event,     0);
    method_declare (agent, "_TASK",          task_event,        0);

    /*  Private methods used between control and task threads                */
    method_declare (agent, "_TASK_START",    start_event,       0);
    method_declare (agent, "_TASK_STOP",     stop_event,        0);
    method_declare (agent, "_TASK_STATUS",   status_event,      0);
    method_declare (agent, "_TASK_OK",       ok_event,          0);
    method_declare (agent, "_TASK_RUNNING",  running_event,     0);
    method_declare (agent, "_TASK_STOPPED",  stopped_event,     0);
    method_declare (agent, "_TASK_ERROR",    error_event,       0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket agent is running, else start it up                */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that transfer agent is running, else start it up              */
    smttran_init ();
    if ((thread = thread_lookup (SMT_TRANSFER, "")) != NULL)
        tranq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that logging agent is running, and create new thread          */
    smtlog_init ();
    if ((thread = thread_create (SMT_LOGGING, "")) != NULL)
        logq = thread-> queue-> qid;        /*  Get logging queue id         */
    else
        return (-1);

    /*  Ensure that slot agent is running, else start it up                  */
    smtslot_init ();

    /*  Create initial thread to manage master port                          */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
        ((TCB *) thread-> tcb)-> handle      = 0;
      }
    else
        return (-1);

    node_reset (&tasks);                /*  Reset task list                  */
    smt_atexit (smtupmd_term);
    inifile  = p_inifile;               /*  Get main arguments               */
    portname = p_portname;

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}

/*  We always come here when the application shuts down; if there are any
    tasks still running (normally impossible, but we want to be certain)
    then this is a good time to kill them.                                   */

static void
smtupmd_term (void)
{
    TASK
        *task;                          /*  Task in list                     */

    for (task  = tasks.next;
         task != (TASK *) &tasks;
         task  = task-> next)
        if (task-> pid != NULL_PROCESS
        &&  process_status (task-> pid) == PROCESS_RUNNING)
            process_kill (task-> pid);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    /*  We don't set the_next_event because we expect an argument event      */
    /*  to supply the initial event for the dialog state machine.            */
}


/**************************   CREATE TASK THREADS   **************************/

MODULE create_task_threads (THREAD *thread)
{
    char
        *keyword,                       /*  Keyword or section name          */
        *value;                         /*  Keyword value                    */
    FILE
        *instream;                      /*  Stream for opened ini file       */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    instream = file_locate ("PATH", inifile, "ini");
    if (instream == NULL)
      {
        sendfmt (&operq, "ERROR", "smtupmd: can't locate '%s.ini'", inifile);
        raise_exception (exception_event);
      }
    else
      {
        /*  Find [Setup] section and parse it                                */
        /*  Each line should contain "keyword=somevalue"                     */

        logfile_name = mem_strdup ("upm.log");
        if (ini_find_section (instream, "general", TRUE))
            while (ini_scan_section (instream, &keyword, &value))
              {
                if (streq (keyword, "logfile"))
                  {
                    mem_strfree (&logfile_name);
                    logfile_name = mem_strdup (value);
                  }
                else
                    sendfmt (&operq, "WARNING",
                             "smtupmd: bad keyword '%s' in upm.ini", keyword);
              }

        /*  Find [Tasks] section and parse it                                */
        /*  Each line should contain "Name=somevalue"                        */

        if (ini_find_section (instream, "tasks", TRUE))
            while (ini_scan_section (instream, &keyword, &value))
              {
                if (streq (keyword, "name"))
                    task_create (value);
                else
                    sendfmt (&operq, "WARNING",
                             "smtupmd: bad keyword '%s' in upm.ini", keyword);
              }
        file_close (instream);
      }
}


/*  -------------------------------------------------------------------------
 *  task_create
 *
 *  Creates a new task entry and attaches it to the tasks list.  The
 *  new entry is initialised with the task name and other arguments.
 *  Creates a new thread to manage the task, and sends a _TASK event
 *  to the new thread.  Returns a pointer to the fresh task entry, or
 *  NULL if there was an error.  In the latter case, sends an error message
 *  to the console.  Task names are canonised as follows:
 *    - letters are converted to uppercase;
 *    - whitespace is replaced by underlines.
 */

static TASK *
task_create (char *name)
{
    TCB
        *tcb;                           /*  Address thread context block     */
    TASK
        *task;                          /*  Freshly created task             */
    THREAD
        *task_thread,                   /*  Thread that manages task         */
        *slot_thread;                   /*  Thread managing time slots       */

    canonise_name (name);
    if ((task = node_create (tasks.prev, sizeof (TASK))) != NULL)
      {
        slot_thread = thread_create (SMT_SLOT,   name);
        task_thread = thread_create (AGENT_NAME, name);
        if (slot_thread && task_thread)
          {
            /*  Send initial event to task thread and initialise task TCB    */
            SEND (&task_thread-> queue-> qid, "_TASK", "");
            tcb = task_thread-> tcb;
            tcb-> thread_type  = task_event;
            tcb-> handle       = 0;
            tcb-> task         = task;

            task-> name        = mem_strdup (name);
            task-> qid         = task_thread-> queue-> qid;
            task-> slotq       = slot_thread-> queue-> qid;
            task-> workdir     = NULL;
            task-> std_in      = NULL;
            task-> std_out     = NULL;
            task-> std_err     = NULL;
            task-> run_idle    = NULL;
            task-> run_startup = NULL;
            task-> run_cancel  = NULL;
            task-> env_list    = NULL;
            task-> pid         = 0;     /*  Not running                      */
          }
        else
          {
            task_destroy (task);
            task = NULL;                /*  Could not create thread          */
          }
      }
    if (!task)
      {
        sendfmt (&operq, "ERROR", "smtupmd: out of memory");
        raise_exception (exception_event);
      }
    return (task);
}


/*  -------------------------------------------------------------------------
 *  task_destroy
 *
 *  Destroys the specified task.
 */

static void
task_destroy (TASK *task)
{
    free_task_values (task);
    mem_strfree (&task-> name);
    node_destroy (task);
}

/*  Free any allocated fields in the task block                              */
/*  except name, which is not reloaded from task .ini file                   */

static void
free_task_values (TASK *task)
{
    mem_strfree (&task-> workdir);
    mem_strfree (&task-> std_in);
    mem_strfree (&task-> std_out);
    mem_strfree (&task-> std_err);
    mem_strfree (&task-> run_idle);
    mem_strfree (&task-> run_startup);
    mem_strfree (&task-> run_cancel);
    strtfree (task-> env_list);
    task-> env_list = NULL;
}


static void
canonise_name (char *name)
{
    while (*name)
      {
        if (isalpha (*name))
            *name = toupper (*name);
        else
        if (isspace (*name))
            *name = '_';
        name++;
      }
}


/*************************   OPEN MANAGER LOG FILE   *************************/

MODULE open_manager_log_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    SEND (&logq, "APPEND", logfile_name);
}


/***************************   OPEN MASTER SOCKET   **************************/

MODULE open_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> handle = passive_TCP (portname, 5);
    if (tcb-> handle == INVALID_SOCKET)
      {
        sendfmt (&operq, "ERROR",
                 "smtupmd: couldn't open UPM port %s", portname);
        sendfmt (&operq, "ERROR",
                 "smtupmd: %s", connect_errlist [connect_error ()]);
        raise_exception (fatal_event);
      }
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    msg_size = exdr_writed (&msg, SMT_SOCK_INPUT, 0, tcb-> handle, (qbyte) 0);
    event_send (
        &sockq,                         /*  Send to socket agent             */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "INPUT",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/***********************   ACCEPT CONTROL CONNECTION   ***********************/

MODULE accept_control_connection (THREAD *thread)
{
    sock_t
        slave_socket;                   /*  Connected socket                 */
    THREAD
        *child_thread;                  /*  Handle to child threads          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    slave_socket = accept_socket (tcb-> handle);
    if (slave_socket != INVALID_SOCKET)
      {
        child_thread = thread_create (AGENT_NAME, "");
        if (child_thread)
          {
            SEND (&child_thread-> queue-> qid, "_CONTROL", "");
            ((TCB *) child_thread-> tcb)-> thread_type = control_event;
            ((TCB *) child_thread-> tcb)-> handle      = slave_socket;
          }
      }
    else
    if (errno != EAGAIN)
      {
        sendfmt (&operq, "ERROR",
                 "smtupmd: could not accept connection: %s", sockmsg ());
        raise_exception (exception_event);
      }
}


/**************************   READ CONTROL MESSAGE   *************************/

MODULE read_control_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Ask the transfer agent to read a block from the socket               */
    msg_size = exdr_writed (&msg, SMT_TRAN_GETB, tcb-> handle, NULL);

    event_send (
        &tranq,                         /*  Send to transfer agent           */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "GET_BLOCK",                    /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    event_wait ();                      /*  Wait for reply event             */
}


/*************************   CHECK CONTROL MESSAGE   *************************/

MODULE check_control_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (the_external_event == ok_event)
      {
        tcb-> message_id = get_upm_message (thread, tcb-> message_body);
        switch (tcb-> message_id)
          {
            case UPM_LIST:   the_next_event = list_event;   break;
            case UPM_HALT:   the_next_event = halt_event;   break;
            case UPM_START:  the_next_event = start_event;  break;
            case UPM_STOP:   the_next_event = stop_event;   break;
            case UPM_STATUS: the_next_event = status_event; break;
            default:         the_next_event = error_event;  break;
          }
      }
    else
        raise_exception (the_external_event);
}


/*  -------------------------------------------------------------------------
 *  get_upm_message -- local
 *
 *  Decodes the thread body to give a message id and a message body.  Puts
 *  the message body in the specified string and returns the message id.
 */

static dbyte
get_upm_message (THREAD *thread, char *body)
{
    byte
       *msg_body_addr = msg_body;
    dbyte
        upm_ident;

    /*  Get buffer from transfer agent                                       */
    exdr_read (thread-> event-> body, SMT_TRAN_GETB_OK,
               NULL, &msg_body_addr);

    /*  Decode UPM message                                                   */
    exdr_read (msg_body, SMT_UPM_MESSAGE, &upm_ident, &body);
    return (upm_ident);
}


/************************   GET FIRST AFFECTED TASK   ************************/

MODULE get_first_affected_task (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  The tcb-> message_body contains the task name or "ALL"; put it       */
    /*  into a canonical form (upper case and no whitespace).                */
    canonise_name (tcb-> message_body);
    if (tcb-> message_body [0] == '\0')
        strcpy (tcb-> message_body, "ALL");

    the_next_event = not_found_event;   /*  Assume no tasks found            */
    for (tcb-> task  = tasks.next;
         tcb-> task != (TASK *) &tasks;
         tcb-> task  = tcb-> task-> next)
      {
        if (streq (tcb-> message_body, tcb-> task-> name)
        ||  streq (tcb-> message_body, "ALL"))
          {
            the_next_event = ok_event;
            break;
          }
      }
}


/*************************   GET NEXT AFFECTED TASK   ************************/

MODULE get_next_affected_task (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = no_more_event;     /*  Assume no tasks found            */
    for (tcb-> task  = tcb-> task-> next;
         tcb-> task != (TASK *) &tasks;
         tcb-> task  = tcb-> task-> next)
      {
        if (streq (tcb-> message_body, tcb-> task-> name)
        ||  streq (tcb-> message_body, "ALL"))
          {
            the_next_event = ok_event;
            break;
          }
      }
}


/***********************   PASS START TO TASK THREAD   ***********************/

MODULE pass_start_to_task_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    event_send (
        &tcb-> task-> qid,              /*  Send to task's thread queue      */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "_TASK_START",                  /*  Name of event to send            */
        thread-> event-> body,          /*  Event body contents              */
        thread-> event-> body_size,     /*  Event body size                  */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/************************   PASS STOP TO TASK THREAD   ***********************/

MODULE pass_stop_to_task_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    event_send (
        &tcb-> task-> qid,              /*  Send to task's thread queue      */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "_TASK_STOP",                   /*  Name of event to send            */
        thread-> event-> body,          /*  Event body contents              */
        thread-> event-> body_size,     /*  Event body size                  */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/***********************   PASS STATUS TO TASK THREAD   **********************/

MODULE pass_status_to_task_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    event_send (
        &tcb-> task-> qid,              /*  Send to task's thread queue      */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "_TASK_STATUS",                 /*  Name of event to send            */
        thread-> event-> body,          /*  Event body contents              */
        thread-> event-> body_size,     /*  Event body size                  */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/**************************   LOAD TASK TIME SLOTS   *************************/

MODULE load_task_time_slots (THREAD *thread)
{
    static char
        buffer [LINE_MAX];              /*  Input line from file             */
    FILE
        *slotfile;                      /*  Stream for opened slots file     */
    TASK
        *task;                          /*  Task control block               */

    tcb  = thread-> tcb;                /*  Point to thread's context        */
    task = tcb-> task;

    /*  Look for time slot file; if found, load specified values             */
    /*  A slot specification is a string, in the format: "name value ...".   */
    /*  The name field is a day name ("mon"-"sun"), a date in MD order       */
    /*  ("12/31") or a date in YMD order ("95/12/31").  The value is a list  */
    /*  of times in 24 hour HH:MM-HH:MM format ("7:30-12:30 13:30-17:30").   */
    /*  The time slot accuracy is SLOT_TICK csecs.  Any day that does not    */
    /*  have specified values is switched 'off'                              */

    slotfile = file_locate ("PATH", task-> name, "tim");
    if (slotfile)
      {
        while (file_read (slotfile, buffer))
          {
            strcrop (buffer);           /*  Remove trailing spaces           */
            if (*buffer == '#' || *buffer == '\0')
                continue;               /*  Ignore comments & blank lines    */

            /*  Send specification to slot agent                             */
            event_send (
                &task-> slotq,          /*  Send to time slot agent          */
                &thread-> queue-> qid,  /*  Queue for reply                  */
                "SPECIFY",              /*  Name of event to send            */
                (byte *) buffer,        /*  Event body                       */
                strlen (buffer),        /*  Event body size                  */
                NULL, NULL, NULL,       /*  No response events               */
                0);                     /*  No timeout                       */
          }
       file_close (slotfile);
      }
    /*  Tell slot thread that we are switched off now                        */
    SEND (&task-> slotq, "OFF", buffer);
}


/****************************   LOAD TASK VALUES   ***************************/

MODULE load_task_values (THREAD *thread)
{
    char
        *keyword,                       /*  Keyword or section name          */
        *value;                         /*  Keyword value                    */
    FILE
        *instream;                      /*  Stream for opened ini file       */
    TASK
        *task;                          /*  Task control block               */
    int
        section;                        /*  Current section                  */
    SYMTAB
        *symtab;                        /*  Environment variables            */

#   define SECTION_NONE         0       /*  Values for section               */
#   define SECTION_SETUP        1
#   define SECTION_ENVIRONMENT  2
#   define SECTION_RUN          3

    tcb  = thread-> tcb;                /*  Point to thread's context        */
    task = tcb-> task;

    instream = file_locate ("PATH", task-> name, "ini");
    if (instream == NULL)
      {
        /*  Send message to console, and copy to message_body                */
        sprintf (tcb-> message_body, "can't locate '%s.ini'", task-> name);
        sendfmt (&operq, "ERROR", "smtupmd: %s", tcb-> message_body);
        raise_exception (exception_event);
      }
    else
      {
        free_task_values (task);
        symtab  = env2symb ();          /*  Load current environment         */
        section = SECTION_NONE;

        FOREVER
          {
            if (ini_scan_section (instream, &keyword, &value))
              {
                if (section == SECTION_SETUP)
                  {
                    if (streq (keyword, "workdir"))
                        task-> workdir = mem_strdup (value);
                    else
                    if (streq (keyword, "stdin"))
                        task-> std_in = mem_strdup (value);
                    else
                    if (streq (keyword, "stdout"))
                        task-> std_out = mem_strdup (value);
                    else
                    if (streq (keyword, "stderr"))
                        task-> std_err = mem_strdup (value);
                    else
                        sendfmt (&operq, "WARNING",
                                 "smtupmd: bad keyword '%s=%s' in '%s.ini'",
                                  keyword, value, task-> name);
                  }
                else
                if (section == SECTION_ENVIRONMENT)
                  {
                    strupc (keyword);
                    sym_assume_symbol (symtab, keyword, value);
                  }
                else
                if (section == SECTION_RUN)
                  {
                    if (streq (keyword, "idle"))
                        task-> run_idle = mem_strdup (value);
                    else
                    if (streq (keyword, "startup"))
                        task-> run_startup = mem_strdup (value);
                    else
                    if (streq (keyword, "cancel"))
                        task-> run_cancel = mem_strdup (value);
                    else
                        sendfmt (&operq, "WARNING",
                                 "smtupmd: bad keyword '%s=%s' in '%s.ini'",
                                  keyword, value, task-> name);
                  }
              }
            else
            if (keyword == NULL)
                break;                  /*  End of file                      */
            else
            if (streq (keyword, "setup"))
                section = SECTION_SETUP;
            else
            if (streq (keyword, "environment"))
                section = SECTION_ENVIRONMENT;
            else
            if (streq (keyword, "run"))
                section = SECTION_RUN;
            else
                section = SECTION_NONE;
          }
        task-> env_list = symb2strt (symtab);
        sym_delete_table (symtab);

        /*  Task startup command is mandatory                                */
        if (!task-> run_startup)
          {
            sprintf (tcb-> message_body, "no [Run] startup= in '%s.ini'",
                     task-> name);
            sendfmt (&operq, "ERROR", "smtupmd: %s", tcb-> message_body);
            raise_exception (exception_event);
          }
       file_close (instream);
      }
}


/************************   REPLY READY FOR COMMAND   ************************/

MODULE reply_ready_for_command (THREAD *thread)
{
    put_upm_message (thread, UPM_READY, UPM_VERSION);
}


static void
put_upm_message (THREAD *thread, dbyte ident, void *body)
{
    static byte
        upm_body [LINE_MAX];            /*  Message to UPM client agent      */
    static DESCR                        /*  Descriptor for exdr_writed       */
        upm = { LINE_MAX, upm_body };
    int
        upm_size;                       /*  Size of formatted upm_body       */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    upm_size = exdr_writed (&upm, SMT_UPM_MESSAGE, ident, body);
    msg_size = exdr_writed (&msg, SMT_TRAN_PUTB,
                            tcb-> handle, upm_size, upm_body, NULL);
    event_send (
        &tranq,                         /*  Send to transfer agent           */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "PUT_BLOCK",                    /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/**************************   REPLY LIST OF TASKS   **************************/

MODULE reply_list_of_tasks (THREAD *thread)
{
    TASK
        *task;                          /*  Task in list                     */

    /*  Send a UPM_TASK_ID message for each task in the list                 */
    for (task  = tasks.next;
         task != (TASK *) &tasks;
         task  = task-> next)
        put_upm_message (thread, UPM_TASK_ID, task-> name);
}


/*****************************   REPLY HALTING   *****************************/

MODULE reply_halting (THREAD *thread)
{
    put_upm_message (thread, UPM_HALTING, "");
}


/*************************   REPLY TASK STARTED OK   *************************/

MODULE reply_task_started_ok (THREAD *thread)
{
    put_upm_message (thread, UPM_START_OK, thread-> event-> body);
}


/************************   REPLY TASK STARTED ERROR   ***********************/

MODULE reply_task_started_error (THREAD *thread)
{
    /*  We've received an error from the task thread; the event body is      */
    /*  the error message.  Send it through to the client.                   */
    put_upm_message (thread, UPM_START_ERROR, thread-> event-> body);
}


/*************************   REPLY TASK STOPPED OK   *************************/

MODULE reply_task_stopped_ok (THREAD *thread)
{
    put_upm_message (thread, UPM_STOP_OK, thread-> event-> body);
}


/************************   REPLY TASK STOPPED ERROR   ***********************/

MODULE reply_task_stopped_error (THREAD *thread)
{
    /*  We've received an error from the task thread; the event body is      */
    /*  the error message.  Send it through to the client.                   */
    put_upm_message (thread, UPM_STOP_ERROR, thread-> event-> body);
}


/***************************   REPLY TASK RUNNING   **************************/

MODULE reply_task_running (THREAD *thread)
{
    put_upm_message (thread, UPM_TASK_RUNNING, thread-> event-> body);
}


/***************************   REPLY TASK STOPPED   **************************/

MODULE reply_task_stopped (THREAD *thread)
{
    put_upm_message (thread, UPM_TASK_STOPPED, thread-> event-> body);
}


/***********************   REPLY UNRECOGNISED CONTROL   **********************/

MODULE reply_unrecognised_control (THREAD *thread)
{
    put_upm_message (thread, UPM_ERROR, "Invalid control command");
}


/*************************   RUN TASK IDLE COMMAND   *************************/

MODULE run_task_idle_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Run the idle command.  Any errors are sent to the console but for    */
    /*  the rest we ignore them.                                             */
    run_command (thread, tcb-> task-> run_idle, TRUE);
}


/*  -------------------------------------------------------------------------
 *  run_command -- local
 *
 *  Runs a command for the current thread task, and returns the PROCESS id
 *  for the created command.  Optionally waits until the command has
 *  completed.  If there is an error, formats an error message in the tcb
 *  message_body, and sends it to the console.  Returns -1 if there was an
 *  error.  If the command argument is NULL, returns 0.
 */

static PROCESS
run_command (THREAD *thread, char *command, Bool wait)
{
    TASK
        *task;                          /*  Task control block               */
    PROCESS
        pid;                            /*  ID of created process            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    task = tcb-> task;

    /*  Run idle command, send error to the console only                     */
    if (!command)
        return (0);

    pid = process_create (command, NULL, task-> workdir,
                          task-> std_in, task-> std_out, task-> std_err,
                          task-> env_list, wait);
    if (pid == 0)
      {
        /*  Send message to console, and copy to message_body                */
        sprintf (tcb-> message_body, "cannot run '%s': %s",
                 command, strerror (errno));
        sendfmt (&operq, "ERROR", "smtupmd: %s", tcb-> message_body);
      }
    else
      {
        /*  process_create() should have waited long enough for any          */
        /*  immediate error or abort to have come back.                      */
        switch (process_status (pid))
          {
            case PROCESS_ENDED_OK:
                if (!wait)
                  {
                    sprintf (tcb-> message_body,
                             "'%s' ended normally", command);
                    pid = 0;            /*  Process ended                    */
                  }
                break;
            case PROCESS_ENDED_ERROR:
                sprintf (tcb-> message_body, "'%s' failed: %s", command,
                         strerror (process_errno));
                pid = 0;                /*  Process ended                    */
                break;
            case PROCESS_INTERRUPTED:
                sprintf (tcb-> message_body, "'%s' was killed", command);
                pid = 0;                /*  Process ended                    */
                break;
          }
        if (pid == 0)
            sendfmt (&operq, "ERROR", "smtupmd: %s", tcb-> message_body);
      }
    return (pid);
}


/************************   RUN TASK STARTUP COMMAND   ***********************/

MODULE run_task_startup_command (THREAD *thread)
{
    TASK
        *task;                          /*  Task control block               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    task = tcb-> task;

    /*  Run startup command; if there is an error, send to the console and   */
    /*  copy the message to message_body.                                    */
    ASSERT (task-> run_startup);
    task-> pid = run_command (thread, tcb-> task-> run_startup, FALSE);
    if (task-> pid)
        sendfmt (&operq, "INFO",
                 "smtupmd: started process %s", tcb-> task-> run_startup);
    else
        raise_exception (exception_event);
}


/************************   RUN TASK CANCEL COMMAND   ************************/

MODULE run_task_cancel_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Run the cancel command.  Any errors are sent to the console but      */
    /*  but the rest we ignore them.                                         */
    run_command (thread, tcb-> task-> run_cancel, TRUE);
}


/***********************   MONITOR ACTIVE TASK STATUS   **********************/

MODULE monitor_active_task_status (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Ask timer to send us an event after one second                       */
    msg_size = exdr_writed (&msg, SMT_TIME_ALARM, (qbyte) 0, (qbyte) 100,
                            0, (void *) NULL);
    event_send (
        &timeq,                         /*  Send to timer queue              */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "ALARM",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/************************   CHECK TASK STILL RUNNING   ***********************/

MODULE check_task_still_running (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (process_status (tcb-> task-> pid) != PROCESS_RUNNING)
      {
        sendfmt (&operq, "INFO",
                 "smtupmd: process %s halted", tcb-> task-> run_startup);
        raise_exception (task_stopped_event);
        tcb-> task-> pid = 0;           /*  Not running                      */
      }
}


/************************   COMMIT OUTGOING REPLIES   ************************/

MODULE commit_outgoing_replies (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    event_send (
        &tranq,                         /*  Send to transfer agent           */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "COMMIT",                       /*  Name of event to send            */
        NULL, 0,                        /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    event_wait ();                      /*  ...and wait for reply            */
}


/**************************   SHUT DOWN CHILD TASK   *************************/

MODULE shut_down_child_task (THREAD *thread)
{
    TASK
        *task;                          /*  Task control block               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    task = tcb-> task;

    if (task-> pid != NULL_PROCESS      /*  Process must be running          */
    &&  process_status (task-> pid) == PROCESS_RUNNING
    &&  process_kill   (task-> pid))
      {
        /*  Send message to console, and copy to message_body                */
        sprintf (tcb-> message_body, "cannot halt process %ld: %s",
                 (long) task-> pid, strerror (errno));
        sendfmt (&operq, "ERROR", "smtupmd: %s", tcb-> message_body);
        raise_exception (exception_event);
      }
    else
        sendfmt (&operq, "INFO",
                 "smtupmd: stopped process %s", tcb-> task-> run_startup);
    task-> pid = 0;                     /*  Not running                      */
}


/**************************   SIGNAL TASK RUNNING   **************************/

MODULE signal_task_running (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell control thread that task is running                             */
    SEND (&thread-> event-> sender, "_TASK_RUNNING", tcb-> task-> name);
}


/**************************   SIGNAL TASK STOPPED   **************************/

MODULE signal_task_stopped (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell control thread that task is not running                         */
    SEND (&thread-> event-> sender, "_TASK_STOPPED", tcb-> task-> name);
}


/************************   SIGNAL TASK STARTED OKAY   ***********************/

MODULE signal_task_started_okay (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell control thread that task was started okay                       */
    SEND (&thread-> event-> sender, "_TASK_OK", tcb-> task-> name);
}


/************************   SIGNAL TASK STOPPED OKAY   ***********************/

MODULE signal_task_stopped_okay (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell control thread that task was stopped okay                       */
    SEND (&thread-> event-> sender, "_TASK_OK", tcb-> task-> name);
}


/***********************   SIGNAL TASK STARTED ERROR   ***********************/

MODULE signal_task_started_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell control thread that task was not stopped due to an error        */
    SEND (&thread-> event-> sender, "_TASK_ERROR", tcb-> message_body);
}


/************************   SIGNAL TASK NOT RUNNING   ************************/

MODULE signal_task_not_running (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell control thread that task was not stopped because it is idle     */
    sendfmt (&thread-> event-> sender, "_TASK_ERROR",
             "Task '%s' is not running", tcb-> task-> name);
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR",
             "smtupmd: error on socket: %s", thread-> event-> body);
}


/***************************   CHECK THREAD TYPE   ***************************/

MODULE check_thread_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = tcb-> thread_type;
}


/****************************   DESTROY THE TASK   ***************************/

MODULE destroy_the_task (THREAD *thread)
{
    TASK
        *task;                          /*  Task control block               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    task = tcb-> task;

    SEND (&task-> slotq, "FINISH", ""); /*  Tell time slot thread to end     */
    task_destroy (task);                /*  Destroy task block               */
}


/*************************   CLOSE MANAGER LOG FILE   ************************/

MODULE close_manager_log_file (THREAD *thread)
{
    SEND (&logq, "CLOSE", "");
    mem_strfree (&logfile_name);
}


/************************   SHUTDOWN THE APPLICATION   ***********************/

MODULE shutdown_the_application (THREAD *thread)
{
    smt_shutdown ();                    /*  Halt the application             */
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)
        close_socket (tcb-> handle);

    the_next_event = terminate_event;
}

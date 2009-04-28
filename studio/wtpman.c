/*===========================================================================*
 *                                                                           *
 *  wtpman.c - WTP manager WSX agent                                         *
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

#include "sfl.h"                        /*  SFL library header file          */
#include "smtlib.h"                     /*  SMT kernel functions             */
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP definitions             */
#include "smtmsg.h"                     /*  SMT message API                  */
#include "wtplib.h"                     /*  WTP definitions                  */
#include "wtpmsg.h"                     /*  WTP message functions            */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   "wtpman"           /*  Our public name                  */
#define STACK_MAX    32                 /*  Max depth of program stack       */
#define FORM_MAX     48000L             /*  Max size of form output data     */

#define APPLIC_STOPPED      0           /*  Application is off-line          */
#define APPLIC_RUNNING      1           /*  Application is on-line           */
#define APPLIC_LOCKED       2           /*  Application is on-line, locked   */

/*  Structure of server table; one entry per server process                  */
/*  This table is allocated when the application starts-up.                  */
/*  Current implementation always creates max. processes at start.           */
typedef struct {
    int      atp;                       /*  Application ATP number, 1..n     */
    THREAD  *thread;                    /*  Server thread for this process   */
    Bool     ready;                     /*  Is server process ready?         */
    PROCESS  pid;                       /*  Server process ID, or zero       */
    time_t   started;                   /*  Time process was started         */
    long     callback;                  /*  Callback key                     */
    qbyte    signature;                 /*  Signature CRC-32                 */
} SERVER;


/*  This structures define tables that are shared between multiple threads;  */
/*  the last thread to leave the room switches-off the light.                */

typedef struct {
    SYMTAB *table;                      /*  Symbol table,...                 */
    int     users;                      /*  Number of threads using it       */
} SHRSYM;

typedef struct {
    SERVER *table;                      /*  Server table,...                 */
    int     users;                      /*  Number of threads using it       */
} SHRSRV;

typedef struct {                        /*  Shared application info          */
    qbyte   cur_sessions;               /*    Current session count          */
    qbyte   peak_sessions;              /*    Highest session count          */
    qbyte   trans_count;                /*    Number transactions            */
    qbyte   trans_cost;                 /*    And total time, 1/100s         */
    qbyte   fatal_errors;               /*    Fatal error count              */
    int     users;                      /*  Number of threads using it       */
} SHRINF;


typedef struct _TCB {                   /*  Thread context block:            */
    /*  Used by all threads                                                  */
    event_t  thread_type;               /*    Thread type indicator          */
    sock_t   handle;                    /*    Handle for i/o, if used        */
    char    *config_file;               /*    Thread config file, if any     */
    SYMTAB  *config_table;              /*    Thread config table if any     */

    /*  Used by MASTER and APPLIC threads                                    */
    QID      http_qid;                  /*    Incoming HTTP thread QID       */
    WSXREQ  *request;                   /*    Decoded WTP request            */
    char    *http_data;                 /*    HTTP post data                 */

    /*  Used only by APPLIC threads                                          */
    int      applic_port;               /*    Callback port                  */
    int      applic_state;              /*    Application state              */
    qbyte    session_count;             /*    Number of sessions created     */
    long     start_time;                /*    Application starting time      */
    long     start_date;                /*    Application starting time      */

    /*  Used by APPLIC and SERVER and SESSION threads                        */
    char    *applic_uri;                /*    Application URI                */
    char    *applic_name;               /*    Application name               */
    QUEUE   *do_queue;                  /*    Queued Do requests             */
    SHRSYM  *programs;                  /*    Program look-up table          */
    SHRSRV  *servers;                   /*    Server table                   */
    SHRINF  *info;                      /*    Application info table         */
    int      nbr_servers;               /*    Size of server table           */

    /*  Used only by SERVER threads                                          */
    char    *server_msg;                /*    Message data from server       */
    char    *server_name;               /*    Server executable name         */
    qbyte    server_msgsize;            /*    Size of this message           */
    int      server_index;              /*    Index into servers table       */
    Bool     server_ready;              /*    Idle, waiting for work         */
    QID      applic_qid;                /*    Application thread QID         */
    QID      session_qid;               /*    Client session thread QID      */
    byte     message_type;              /*    Last incoming message type     */
    long     entry_time;                /*    Time message sent to server    */

    /*  Used only by SESSION threads                                         */
    int      stack_ptr;                 /*    Size of call stack             */
    char   **call_stack;                /*    Program call stack             */
    dbyte    session_step;              /*    Sequential session step        */
    char    *session_program;           /*    Current active program         */
    byte    *session_request;           /*    WTP message, encoded           */
    int      session_reqsize;           /*    Size of encoded wtp message    */
    qbyte    session_envsize;           /*    Session environment size       */
    byte    *session_envdata;           /*    Session environment data       */
    SYMTAB  *session_context;           /*    Session context blocks         */
    char    *session_screen;            /*    Last HTML screen we showed     */

} TCB;


#define TCONFIG(s,d)      sym_get_value (tcb-> config_table, (s), (d))
#define TCONFIG_SET(s)  *(sym_get_value (tcb-> config_table, (s), "1")) == '1'


/*- Function prototypes -----------------------------------------------------*/

static THREAD *new_thread         (char *name, char *method, event_t type);
static int   atp_max_value        (int atp_nbr);
static char *atp_name_value       (int atp_nbr);
static long  get_callback_key     (int index);
static void  use_applic_values    (TCB *applic_tcb, TCB *child_tcb);
static void  create_new_session   (THREAD *thread, char *arguments);
static char *get_session_id       (char *arguments);
static dbyte get_session_step     (char *arguments);
static void  http_reply_html      (THREAD *thread, char *header, char *msg);
static void  wtp_send_msg_ok      (THREAD *thread);
static void  wtp_send_msg_error   (THREAD *thread, dbyte code);
static void  alloc_programs_table (TCB *tcb);
static void  alloc_servers_table  (TCB *tcb);
static void  alloc_info_table     (TCB *tcb);
static void  start_required_atps  (TCB *tcb);
static void  start_atp            (SERVER *server, char *file, char *workdir,
                                   char *user, char *group, char **environment,
                                   int port, char *protocol, qbyte callback);
static void  unuse_programs_table (TCB *tcb);
static void  unuse_servers_table  (TCB *tcb);
static void  unuse_info_table     (TCB *tcb);
static char *session_root_program (TCB *tcb);
static int   session_set_program  (TCB *tcb, char *program);
static char *session_uri          (THREAD *thread);
static Bool  program_is_active    (TCB *tcb, char *program);
static void  put_context          (int local_block, qbyte size, byte *data);
static void  get_context          (qbyte *global_size, byte **global_data,
                                   qbyte *local_size,  byte **local_data);


/*- Global variables used in this source file only --------------------------*/

static AGENT
    *this_agent;                        /*  Handle to ourselves...           */
static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    operq,                              /*  Operator console event queue     */
    logq,                               /*  Server log queue                 */
    sockq,                              /*  Socket agent event queue         */
    timeq,                              /*  Timer agent event queue          */
    tranq;                              /*  Transfer agent event queue       */

#include "wtpman.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int wtpman_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */
#   include "wtpman.i"                  /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "WSX_REQUEST",    request_event,        0);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  ok_event,             0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,             0);
    method_declare (agent, "SOCK_READ_OK",   ok_event,             0);
    method_declare (agent, "SOCK_WRITE_OK",  SMT_NULL_EVENT,       0);
    method_declare (agent, "SOCK_CLOSED",    sock_closed_event,    0);
    method_declare (agent, "SOCK_ERROR",     sock_error_event,     0);
    method_declare (agent, "SOCK_TIMEOUT",   sock_error_event,     0);

    /*  Reply events from transfer agent                                     */
    method_declare (agent, "TRAN_PUTH_OK",   SMT_NULL_EVENT,       0);
    method_declare (agent, "TRAN_GETH_OK",   ok_event,             0);
    method_declare (agent, "TRAN_CLOSED",    sock_closed_event,    0);
    method_declare (agent, "TRAN_ERROR",     sock_error_event,     0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",     timeout_event,        0);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",        master_event,         0);
    method_declare (agent, "_APPLIC",        applic_event,         0);
    method_declare (agent, "_SESSION",       session_event,        0);
    method_declare (agent, "_SERVER",        server_event,         0);

    /*  Private methods used between various threads                         */
    method_declare (agent, "_CONTROL",       control_event,        0);
    method_declare (agent, "_REQUEST",       request_event,        0);
    method_declare (agent, "_CONTINUE",      continue_event,       0);
    method_declare (agent, "_REFRESH",       refresh_event,        0);

    /*  These are reply events from server to session thread                 */
    method_declare (agent, "_SESSION_SHOW",   session_show_event,   0);
    method_declare (agent, "_SESSION_CALL",   session_call_event,   0);
    method_declare (agent, "_SESSION_RETURN", session_return_event, 0);
    method_declare (agent, "_SESSION_EXIT",   session_exit_event,   0);
    method_declare (agent, "_SESSION_ERROR",  session_error_event,  0);
    method_declare (agent, "_SERVER_TIMEOUT", server_timeout_event, 0);
    method_declare (agent, "_SERVER_ABORT",   server_abort_event,   0);

    /*  Ensure that logging agent is running, else start it up               */
    smtlog_init ();
    if ((thread = thread_create (SMT_LOGGING, "")) != NULL)
        logq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket i/o agent is running, else start it up            */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that transfer agent is running, else start it up              */
    smttran_init ();
    if ((thread = thread_lookup (SMT_TRANSFER, "")) != NULL)
        tranq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create initial thread to manage master port                          */
    new_thread ("main", "_MASTER", master_event);
    this_agent = agent;                 /*  Handle to ourselves...           */

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


static THREAD *
new_thread (char *name, char *method, event_t thread_type)
{
    static QID
        null_qid = { 0, 0 };
    THREAD *thread;                     /*  Handle to new thread             */
    TCB    *tcb;                        /*  Thread context block             */

    if ((thread = thread_create (AGENT_NAME, name)) != NULL)
      {
        if (method)
            SEND (&thread-> queue-> qid, method, "");
        tcb = thread-> tcb;

        /*  Initialise all fields                                            */
        tcb-> thread_type       = thread_type;
        tcb-> handle            = 0;
        tcb-> config_file       = NULL;
        tcb-> config_table      = NULL;
        tcb-> http_qid          = null_qid;
        tcb-> request           = NULL;
        tcb-> applic_port       = 0;
        tcb-> applic_state      = 0;
        tcb-> start_time        = 0;
        tcb-> start_date        = 0;
        tcb-> session_count     = 0;
        tcb-> applic_uri        = NULL;
        tcb-> applic_name       = NULL;
        tcb-> nbr_servers       = 0;
        tcb-> do_queue          = NULL;
        tcb-> servers           = NULL;
        tcb-> programs          = NULL;
        tcb-> info              = NULL;
        tcb-> server_msg        = NULL;
        tcb-> server_name       = NULL;
        tcb-> server_msgsize    = 0;
        tcb-> server_index      = 0;
        tcb-> server_ready      = FALSE;
        tcb-> applic_qid        = null_qid;
        tcb-> session_qid       = null_qid;
        tcb-> message_type      = 0;
        tcb-> entry_time        = 0;
        tcb-> stack_ptr         = 0;
        tcb-> call_stack        = NULL;
        tcb-> session_step      = 0;
        tcb-> session_program   = NULL;
        tcb-> session_request   = NULL;
        tcb-> session_reqsize   = 0;
        tcb-> session_envdata   = NULL;
        tcb-> session_context   = NULL;
        tcb-> session_screen    = NULL;
      }
    return (thread);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  We don't set the_next_event because we expect an argument event      */
    /*  to supply the initial event for the dialog state machine.            */
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                          M A S T E R   T H R E A D
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


/************************   LOAD MASTER CONFIG FILE   ************************/

MODULE load_master_config_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Load configuration data, if any, into the config_table               */
    tcb-> config_table = ini_dyn_load (NULL, "wtpcfg.ini");
}


/**************************   OPEN MASTER LOG FILE   *************************/

MODULE open_master_log_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&logq, "APPEND", TCONFIG ("general:logfile", "wtpman.log"));
}


/*************************   CLOSE MANAGER LOG FILE   ************************/

MODULE close_manager_log_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&logq, "CLOSE", "");
}


/*************************   CREATE APPLIC THREADS   *************************/

MODULE create_applic_threads (THREAD *thread)
{
    int
        applic_nbr;                     /*  Cardinal applic, 1..n            */
    char
        applic_key [30],                /*  Applic number as string          */
        *uri,                           /*  Applic URI string                */
        *config_file;                   /*  Applic configuration file        */
    SYMTAB
        *config_table;                  /*  Applic config values             */
    THREAD
        *applic_thread;                 /*  Thread that manages applic       */
    TCB
        *applic_tcb;                    /*  Applic thread context block      */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Create applications 1 to N as specified in wtpman config file        */
    for (applic_nbr = 1;; applic_nbr++)
      {
        sprintf (applic_key, "applications:%d", applic_nbr);
        if ((config_file = TCONFIG (applic_key, NULL)) == NULL)
            break;                      /*  No more applications defined     */

        /*  Load config file information                                     */
        config_table = ini_dyn_load (NULL, config_file);
        if (config_table)
          {
            uri = sym_get_value (config_table, "general:uri", NULL);
            if (uri)
              {
                applic_thread = new_thread (uri, "_APPLIC", applic_event);
                if (applic_thread)
                  {
                    applic_tcb = applic_thread-> tcb;
                    applic_tcb-> config_table = config_table;
                    applic_tcb-> config_file  = mem_strdup (config_file);
                    applic_tcb-> applic_uri   = mem_strdup (uri);
                  }
                else
                  {
                    sym_delete_table (config_table);
                    sendfmt (&operq, "ERROR",
                             "wtpman: could not create thread for %s: %s",
                              config_file, smt_errlist [smt_errno]);
                  }
              }
            else
              {
                sym_delete_table (config_table);
                sendfmt (&operq, "ERROR",
                         "wtpman: no URI defined in %s", config_file);
              }
          }
        else
            sendfmt (&operq, "ERROR",
                     "wtpman: could not read config file %s: %s",
                      config_file, strerror (errno));
      }
}


/***************************   DECODE WTP REQUEST   **************************/

MODULE decode_wtp_request (THREAD *thread)
{
    char
        *url_args,                      /*  If &data supplied in arguments   */
        *post_data,                     /*  Posted data string               */
        *post_name;
    FILE
        *post_file;
    DESCR
        *data_descr = NULL;
    qbyte
        file_nbr = 0;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Decode WTP request into structure                                    */
    ASSERT (tcb-> request == NULL);
    get_smt_wsx_request (thread-> event-> body, &tcb-> request);

    ASSERT (tcb-> request-> arguments);
    ASSERT (tcb-> request-> post_data);

    /*  We always allocate a string to tcb-> http_data                       */

    /*  This code sucks, and should be changed... http_multipart_decode
     *  makes too many assumptions, and can't handle data in a buffer...
     */
    post_data = tcb-> request-> post_data;

    /*  Content type : Multipart/form-data                                   */
    if (memfind (tcb-> request-> symbols_data,
                 tcb-> request-> symbols_size,
                 "CONTENT_TYPE=multipart/form-data", 32, FALSE) != NULL)
      {
        if (*post_data == '@')
            data_descr = http_multipart_decode (
                         post_data + 1, TCONFIG ("general:workdir", ""),
                         "%s_tmp");
        else
          {
            post_name = mem_strdup (get_tmp_file_name (".", &file_nbr, "pos"));
            post_file = fopen (post_name, FOPEN_WRITE_BINARY);
            fwrite (post_data, strlen (post_data), 1, post_file);
            fclose (post_file);
            data_descr = http_multipart_decode (
                         post_name, TCONFIG ("general:workdir", ""), "%s_tmp");
            file_delete (post_name);
            mem_free    (post_name);
          }
      }
    else
    if (*post_data == '@')
        /*  Content type: application/x-www-form-urlencoded                  */
        data_descr = file_slurp (post_data + 1);

    if (data_descr)
        post_data = (char *) data_descr-> data;

    /*  If arguments contain &... data, then append to posted data           */
    url_args = strchr (tcb-> request-> arguments, '&');
    tcb-> http_data = xstrcpy (NULL, post_data, url_args, NULL);

    if (data_descr)
        mem_free (data_descr);

    /*  Set reply QID for all HTTP responses                                 */
    tcb-> http_qid = thread-> event-> sender;
}


/***********************   PARTIAL DECODE WTP REQUEST   **********************/

MODULE partial_decode_wtp_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT (tcb-> request == NULL);
    get_smt_wsx_request (thread-> event-> body, &tcb-> request);
    tcb-> http_data = NULL;

    /*  Set reply QID for all HTTP responses                                 */
    tcb-> http_qid = thread-> event-> sender;
}


/**********************   ROUTE WTP REQUEST TO APPLIC   **********************/

MODULE route_wtp_request_to_applic (THREAD *thread)
{
    char
        *method,                        /*  Method to deliver                */
        *uri;                           /*  URI from request URL             */
    THREAD
        *applic_thread;                 /*  Applic thread for request        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Look for a URL that we recognise, and parse it                       */
    if ((uri = strdefix (tcb-> request-> request_url, "/wtp/control")) != NULL)
        method = "_CONTROL";
    else
    if ((uri = strdefix (tcb-> request-> request_url, "/wtp")) != NULL)
        method = "_REQUEST";

    /*  If we parsed URL okay, look for thread, and pass request             */
    if (uri)
      {
        applic_thread = thread_lookup (AGENT_NAME, uri);
        if (applic_thread)
          {
            /*  Route event body to applic thread, keeping original sender   */
            /*  so that replies go to HTTP agent, not this thread.           */
            event_send (
                &applic_thread-> queue-> qid,
                &thread-> event-> sender,
                method,
                thread-> event-> body,
                thread-> event-> body_size,
                NULL, NULL, NULL, 0);
          }
        else
            raise_exception (not_found_event);
      }
    else
        raise_exception (not_found_event);
}


/****************************   FREE WTP REQUEST   ***************************/

MODULE free_wtp_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT (tcb-> request != NULL);

    free_smt_wsx_request (&tcb-> request);
    mem_strfree (&tcb-> http_data);
}


/**************************   HTTP REPLY NOT FOUND   *************************/

MODULE http_reply_not_found (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_wsx_error (&tcb-> http_qid, HTTP_RESPONSE_NOTFOUND);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                          A P P L I C   T H R E A D
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


/*********************   INITIALISE APPLICATION THREAD   *********************/

MODULE initialise_application_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> applic_name = mem_strdup (sym_get_value (tcb-> config_table,
                                    "general:name", tcb-> applic_uri));
    tcb-> do_queue = queue_create (this_agent, 0);
}


/***********************   CHECK APPLICATION AUTORUN   ***********************/

MODULE check_application_autorun (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (TCONFIG_SET ("general:autorun"))
        the_next_event = ok_event;
    else
        the_next_event = suspended_event;
}


/**********************   CHECK APPLIC CONTROL COMMAND   *********************/

MODULE check_applic_control_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (streq (tcb-> request-> arguments, "start"))
        the_next_event = control_start_event;
    else
    if (streq (tcb-> request-> arguments, "stop"))
        the_next_event = control_stop_event;
    else
    if (streq (tcb-> request-> arguments, "report"))
        the_next_event = control_report_event;
    else
    if (streq (tcb-> request-> arguments,  "lock"))
        the_next_event = control_lock_event;
    else
    if (streq (tcb-> request-> arguments, "unlock"))
        the_next_event = control_unlock_event;
    else
        the_next_event = error_event;
}


/************************   OPEN APPLICATION SOCKET   ************************/

MODULE open_application_socket (THREAD *thread)
{
    static char
        service [10];                   /*  Formatted port number            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Find an available socket starting at general:first_port              */
    tcb-> applic_port = atoi (TCONFIG ("general:first_port", "5500"))
                      - ip_portbase;
    if (tcb-> applic_port < 0)
        tcb-> applic_port = 0;

    sprintf (service, "%d", (int) tcb-> applic_port);
    tcb-> handle = passive_TCP (service, 5);
    while (connect_error () == IP_BINDERROR)
      {
        tcb-> applic_port++;           /*  Port in use - try next one        */
        sprintf (service, "%d", (int) tcb-> applic_port);
        tcb-> handle = passive_TCP (service, 5);
      }
    if (tcb-> handle == INVALID_SOCKET)
      {
        tcb-> handle = 0;               /*  0 means 'not open'               */
        sendfmt (&operq, "ERROR",
                 "wtpman: could not open WTP port");
        sendfmt (&operq, "ERROR",
                 "wtpman: %s", connect_errlist [connect_error ()]);
        sendfmt (&operq, "ERROR",
                 "wtpman: %s", sockmsg ());
        raise_exception (fatal_error_event);
        sprintf (server_message, "Could not open WTP port - %s (%s)",
                 connect_errlist [connect_error ()], sockmsg ());
      }
    else
        sendfmt (&operq, "INFO", "wtpman: opened WTP port %d for %s",
                          tcb-> applic_port + ip_portbase, tcb-> applic_name);
}


/************************   CLOSE APPLICATION SOCKET   ***********************/

MODULE close_application_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    close_socket (tcb-> handle);
    tcb-> handle = 0;
}


/***********************   START APPLICATION SERVERS   ***********************/

MODULE start_application_servers (THREAD *thread)
{
    int
        atp_nbr;                        /*  ATP index, 1..n                  */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get the total of the server max= values                              */
    tcb-> nbr_servers = 0;
    for (atp_nbr = 1; atp_max_value (atp_nbr); atp_nbr++)
        tcb-> nbr_servers += atp_max_value (atp_nbr);

    /*  Fail if no servers are defined                                       */
    if (tcb-> nbr_servers == 0)
      {
        sendfmt (&operq, "ERROR",
                 "wtpman: zero ATPs defined for %s", tcb-> applic_name);
        raise_exception (exception_event);
      }
    else
      {
        /*  Allocate application tables                                      */
        alloc_programs_table (tcb);
        alloc_servers_table  (tcb);
        alloc_info_table     (tcb);
        start_required_atps  (tcb);
      }
    if (!exception_raised)
      {
        tcb-> start_time   = time_now ();
        tcb-> start_date   = date_now ();
        tcb-> applic_state = APPLIC_RUNNING;
      }
}


/*  -------------------------------------------------------------------------
 *  atp_max_value
 *
 *  Get max number of server processes for an application server process.
 *  Returns 0 if ATP is not defined, or is badly defined.  Assumes tcb is
 *  set to application TCB.
 */

static int
atp_max_value (int atp_nbr)
{
    static char
        atp_key [15];                   /*  AtpNNNNN:max                     */

    sprintf (atp_key, "atp%d:max", atp_nbr);
    if (atp_name_value (atp_nbr))       /*  If atp defined, default is 1     */
        return (atoi (TCONFIG (atp_key, "1")));
    else
        return (0);                     /*  Else we return zero              */
}


/*  -------------------------------------------------------------------------
 *  atp_name_value
 *
 *  Get executable filename for an application server process.
 *  Returns NULL if ATP is not defined, or is badly defined. Assumes
 *  tcb is set to application TCB.
 */

static char *
atp_name_value (int atp_nbr)
{
    static char
        atp_key [15];                   /*  AtpNNNNN:name                    */

    sprintf (atp_key, "atp%d:name", atp_nbr);
    return (TCONFIG (atp_key, NULL));
}


/*  -------------------------------------------------------------------------
 *  get_callback_key
 *
 *  Generate a callback key by hashing the current time and the specified
 *  server index.  This is used at connect time to check that the server is
 *  valid and permitted to connect.
 */

static long
get_callback_key (int index)
{
    return (time_now () + index);
}


/*  -------------------------------------------------------------------------
 *  alloc_programs_table
 *
 *  Create new program symbol table, set usage count to 1.
 */

static void
alloc_programs_table (TCB *tcb)
{
    ASSERT (tcb-> programs == NULL);

    tcb-> programs = mem_alloc (sizeof (*tcb-> programs));
    if (tcb-> programs == NULL)
        raise_exception (out_of_memory_event);
    else
      {
        tcb-> programs-> table = sym_create_table ();
        tcb-> programs-> users = 1;
        if (tcb-> programs-> table == NULL)
            raise_exception (out_of_memory_event);
      }
}


/*  -------------------------------------------------------------------------
 *  alloc_servers_table
 *
 *  Create new application server table, set usage count to 1.
 */

static void
alloc_servers_table (TCB *tcb)
{
    size_t
        server_table_size;

    tcb-> servers = mem_alloc (sizeof (*tcb-> servers));
    if (tcb-> servers == NULL)
        raise_exception (out_of_memory_event);
    else
      {
        server_table_size = tcb-> nbr_servers * sizeof (SERVER);
        tcb-> servers-> table = mem_alloc (server_table_size);
        tcb-> servers-> users = 1;
        if (tcb-> servers-> table == NULL)
            raise_exception (out_of_memory_event);
        else
            memset (tcb-> servers-> table, 0, server_table_size);
      }
}


/*  -------------------------------------------------------------------------
 *  alloc_info_table
 *
 *  Create new application information table, set usage count to 1.
 */

static void
alloc_info_table (TCB *tcb)
{
    ASSERT (tcb-> info == NULL);

    tcb-> info = mem_alloc (sizeof (*tcb-> info));
    if (tcb-> info == NULL)
        raise_exception (out_of_memory_event);
    else
      {
        memset (tcb-> info, 0, sizeof (*tcb-> info));
        tcb-> info-> users = 1;
      }
}


/*  -------------------------------------------------------------------------
 *  start_required_atps
 *
 *  Starts all application server processes that are not yet running, as
 *  specified in the server table.
 */

static void
start_required_atps (TCB *tcb)
{
    char
        *atp_path,                      /*  Executable program path          */
        *work_dir,                      /*  Executable working directory     */
        *filename,                      /*  Executable program filename      */
        **environment;                  /*  Environment symbols              */
    int
        atp_nbr,                        /*  ATP index, 1..n                  */
        atp_max,                        /*  Max. servers for this ATP        */
        atp_server,                     /*  ATP server, 0..max-1             */
        server_nbr;                     /*  Server number, 0..max-1          */
    SERVER
        *server;                        /*  Entry into server table          */
    SYMTAB
        *symtab;                        /*  Environment symbols              */
    SYMBOL
        *symbol,                        /*  Config symbols                   */
        *symnew;                        /*  Newly-inserted env. symbol       */

    atp_path = TCONFIG ("general:binpath", "wtp-bin");
    work_dir = TCONFIG ("general:workdir", "");

    /*  Build environment symbols table                                      */
    if (TCONFIG_SET ("general:environment"))
        symtab = env2symb ();           /*  Load current environment         */
    else
        symtab = sym_create_table ();

    for (symbol = tcb-> config_table-> symbols; symbol; symbol = symbol-> next)
        if (strprefixed (symbol-> name, "environment:"))
          {
            symnew = sym_assume_symbol (
                symtab, 
                symbol-> name + strlen ("environment:"), 
                symbol-> value);
            if (symnew)
                strupc (symnew-> name);
          }

    environment = symb2strt (symtab);
    sym_delete_table (symtab);

    /*  Launch any processes that have a zero process-id entry               */
    server_nbr = 0;
    for (atp_nbr = 1; atp_max_value (atp_nbr); atp_nbr++)
      {
        /*  Check that executable file exists and is accessible              */
        filename = file_where ('r', atp_path, atp_name_value (atp_nbr), NULL);
        if (filename == NULL || !file_is_executable (filename))
          {
            sendfmt (&operq, "ERROR", "wtpman: '%s' not executable on '%s'",
                     atp_name_value (atp_nbr), atp_path);
            raise_exception (exception_event);
          }
        else
          {
            atp_max = atp_max_value (atp_nbr);
            for (atp_server = 0; atp_server < atp_max; atp_server++)
              {
                server = &tcb-> servers-> table [server_nbr];
                server-> atp = atp_nbr;
                if (server-> pid == 0)
                    start_atp (server, 
                               filename, 
                               work_dir, 
                               TCONFIG ("general:user",  NULL),
                               TCONFIG ("general:group", NULL),
                               environment,
                               tcb-> applic_port + ip_portbase,
                              "tcp", 
                               get_callback_key (atp_server));
                server_nbr++;
              }
          }
      }
    strtfree (environment);
}


static void
start_atp (
    SERVER *server, 
    char   *filename, 
    char   *workdir, 
    char   *user,
    char   *group,
    char  **environment,
    int     port,  
    char   *protocol, 
    qbyte   callback)
{
    static char
        arguments [30];                 /*  "WTP/1.0 tcp nnnn nnnnnnnn"      */
    char
        *command;                       /*  Program + arguments to run       */
    PROCESS_DATA
        procinfo = PROCESS_DATA_INIT;
    PROCESS
        pid;                            /*  ID of created process            */

    sprintf (arguments, "WTP/1.0 %s %d %ld", protocol, port, callback);
    command = xstrcpy (NULL, filename, " ", arguments, NULL);

    process_compatible = FALSE;
    procinfo.filename  = command;
    procinfo.workdir   = workdir;
    procinfo.envv      = environment;
    procinfo.username  = user;
    procinfo.groupname = group;
    procinfo.password  = NULL;

    if (process_setinfo (&procinfo, NULL,
                         "wtpout.log", FALSE,
                         "wtperr.log", FALSE) == 0)
      {
        pid = process_create_full (&procinfo);
        process_close_io (&procinfo);
        if (pid == NULL_PROCESS)
          {
            sendfmt (&operq, "ERROR", "wtpman: can't run '%s' in '%s': %s",
                                       filename, workdir,
                                       strerror (procinfo.error));
            raise_exception (exception_event);
          }
      }
    else
      {
        sendfmt (&operq, "ERROR", "wtpman: can't redirect output: %s",
                                   strerror (errno));
        raise_exception (exception_event);
        pid = NULL_PROCESS;
      }
    mem_strfree (&command);

    server-> thread    = NULL;
    server-> ready     = FALSE;
    server-> pid       = pid;
    server-> started   = time (NULL);
    server-> callback  = callback;
    server-> signature = 0;
}


/***********************   CHECK APPLICATION SERVERS   ***********************/

MODULE check_application_servers (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    start_required_atps (tcb);          /*  Restart any halted servers       */
}


/************************   STOP APPLICATION SERVERS   ***********************/

MODULE stop_application_servers (THREAD *thread)
{
    int
        server_nbr;                     /*  Index into application servers   */
    THREAD
        *server_thread;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Application is running if servers table is (still) allocated         */
    if (tcb-> servers)
      {
        /*  Send _SHUTDOWN to all server threads for this application        */
        for (server_nbr = 0; server_nbr < tcb-> nbr_servers; server_nbr++)
          {
            server_thread = tcb-> servers-> table [server_nbr].thread;
            if (server_thread != NULL)
                SEND (&server_thread-> queue-> qid, "SHUTDOWN", "");
          }
        unuse_programs_table (tcb);
        unuse_servers_table  (tcb);
        unuse_info_table     (tcb);
      }
    tcb-> applic_state = APPLIC_STOPPED;
}


/*  -------------------------------------------------------------------------
 *  unuse_programs_table
 *
 *  Decrement usage count; if zero, delete programs table.
 */

static void
unuse_programs_table (TCB *tcb)
{
    ASSERT (tcb-> programs);
    ASSERT (tcb-> programs-> users > 0);

    if (--tcb-> programs-> users == 0)
      {
        sym_delete_table (tcb-> programs-> table);
        mem_free (tcb-> programs);
      }
    tcb-> programs = NULL;              /*  We're finished with the table    */
}


/*  -------------------------------------------------------------------------
 *  unuse_servers_table
 *
 *  Decrement usage count; if zero, delete servers table.
 */

static void
unuse_servers_table (TCB *tcb)
{
    ASSERT (tcb-> servers-> users > 0);
    if (--tcb-> servers-> users == 0)
      {
        mem_free (tcb-> servers-> table);
        mem_free (tcb-> servers);
      }
    tcb-> servers = NULL;               /*  We're finished with the table    */
}


/*  -------------------------------------------------------------------------
 *  unuse_info_table
 *
 *  Decrement usage count; if zero, delete info table.
 */

static void
unuse_info_table (TCB *tcb)
{
    ASSERT (tcb-> info-> users > 0);
    if (--tcb-> info-> users == 0)
        mem_free (tcb-> info);
    tcb-> info = NULL;                  /*  We're finished with the table    */
}


/***********************   LOCK APPLICATION SESSIONS   ***********************/

MODULE lock_application_sessions (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> applic_state = APPLIC_LOCKED;
}


/**********************   UNLOCK APPLICATION SESSIONS   **********************/

MODULE unlock_application_sessions (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> applic_state = APPLIC_RUNNING;
}


/************************   ACCEPT SERVER CONNECTION   ***********************/

MODULE accept_server_connection (THREAD *thread)
{
    sock_t
        slave_socket;                   /*  Connected socket                 */
    THREAD
        *child_thread;                  /*  Handle to child threads          */
    TCB
        *child_tcb;                     /*  Handle to child TCB              */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    slave_socket = accept_socket (tcb-> handle);
    if (slave_socket != INVALID_SOCKET)
      {
        child_thread = new_thread ("", "_SERVER", server_event);
        if (child_thread)
          {
            child_tcb = child_thread-> tcb;
            child_tcb-> handle = slave_socket;
            child_tcb-> applic_qid = thread-> queue-> qid;
            use_applic_values (tcb, child_tcb);
          }
      }
    else
    if (sockerrno != EAGAIN)
      {
        sprintf (server_message, "Network problem: %s", sockmsg ());
        sendfmt (&operq, "ERROR",
                 "wtpman: could not accept connection: %s", sockmsg ());
        raise_exception (fatal_error_event);
      }
}


/*  -------------------------------------------------------------------------
 *  use_applic_values
 *
 *  Server and session threads share the parent application tables: we set
 *  the applic_tcb pointer to the application TCB in these threads.
 */

static void
use_applic_values (TCB *applic_tcb, TCB *child_tcb)
{
    child_tcb-> config_table = applic_tcb-> config_table;
    child_tcb-> config_file  = applic_tcb-> config_file;
    child_tcb-> applic_uri   = applic_tcb-> applic_uri;
    child_tcb-> applic_name  = applic_tcb-> applic_name;
    child_tcb-> do_queue     = applic_tcb-> do_queue;
    child_tcb-> nbr_servers  = applic_tcb-> nbr_servers;

    child_tcb-> programs     = applic_tcb-> programs;
    child_tcb-> servers      = applic_tcb-> servers;
    child_tcb-> info         = applic_tcb-> info;

    child_tcb-> programs-> users++;
    child_tcb-> servers-> users++;
    child_tcb-> info-> users++;
}


/**********************   ROUTE WTP REQUEST TO SESSION   *********************/

MODULE route_wtp_request_to_session (THREAD *thread)
{
    char
        *session_id,                    /*  URL session id/thread name       */
        *arguments;                     /*  URL arguments, if any            */
    dbyte
        session_step;                   /*  URL session step                 */
    THREAD
        *session_thread;                /*  Session thread found or created  */
    TCB
        *session_tcb;                   /*  Session thread's context block   */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  a)  request-> arguments are empty or unrecognised:
     *      create new session thread, pass _SESSION method, event body are
     *      arguments.  Pass original sender queue to thread.
     *
     *  b)  As (a), only application is locked - reject user.
     *
     *  c)  request-> arguments refer to expired thread:
     *      create new session thread, pass _SESSION method, event body is
     *      "-restart".  Pass original sender queue to thread.
     *
     *  d)  request-> arguments refer to wrong thread step:
     *      pass _REFRESH method, with "refresh" as event body.
     *      Pass original sender queue to thread.
     *
     *  e)  request-> arguments refer to existing session thread:
     *      pass _CONTINUE method, with request-> query_data as event body.
     *      Pass original sender queue to thread.
     */

    session_id   = get_session_id   (tcb-> request-> arguments);
    session_step = get_session_step (tcb-> request-> arguments);

    if (session_id == NULL)
      {
        if (tcb-> applic_state == APPLIC_RUNNING)
          {
            /*  (a) Create new session thread, with a unique name            */
            /*  Any URL arguments will be HTTP MIME encoded - decode them    */
            arguments = tcb-> request-> arguments;
            http_unescape (arguments, NULL);
            create_new_session (thread, arguments);
          }
        else
            /*  (b) application is locked                                    */
            http_reply_html (thread,
                "New sessions not permitted at present", NULL);
      }
    else
      {
        session_thread = thread_lookup (AGENT_NAME, session_id);
        if (session_thread == NULL)
            /*  (c) thread has expired                                       */
            create_new_session (thread, "-restart");
        else
          {
            session_tcb = session_thread-> tcb;
            if (session_tcb-> session_step != session_step)
                /*  (d) bad session step - ask for refresh, keeping          */
                /*  original sender, for HTTP replies.                       */
                event_send (
                    &session_thread-> queue-> qid,
                    &thread-> event-> sender,
                    "_REFRESH",
                    (byte *) "refresh",
                    strlen  ("refresh") + 1,
                    NULL, NULL, NULL, 0);
            else
              {
                /*  (e) send query data to session thread, keeping           */
                /*  original sender, for HTTP replies.                       */
                event_send (
                    &session_thread-> queue-> qid,
                    &thread-> event-> sender,
                    "_CONTINUE",
                    (byte *) tcb-> http_data,
                    strlen  (tcb-> http_data) + 1,
                    NULL, NULL, NULL, 0);
              }
          }
      }
}


/*  -------------------------------------------------------------------------
 *  create_new_session
 *
 *  Creates a new session thread and passes it a _SESSION event.
 */
#define SESSID_SIZE      12             /*  Exactly 12 characters long       */

static void
create_new_session (THREAD *thread, char *arguments)
{
    static char
        session_name [SESSID_SIZE + 1]; /*  Formatted session name           */
    static word
        session_count = 0;              /*  Global uniquifier                */
    THREAD
        *session_thread;                /*  Session thread found or created  */
    TCB
        *session_tcb;                   /*  Session thread's context block   */

    session_count++;
    sprintf (session_name, "%04X%08lX",
             session_count,
             (long) (tcb-> session_count++ ^ tcb-> start_time));

    session_thread = new_thread (session_name, NULL, session_event);
    
    if (session_thread)
      {
        session_tcb = session_thread-> tcb;
        use_applic_values (tcb, session_tcb);
        session_tcb-> applic_qid = thread-> queue-> qid;
        if (tcb-> info-> peak_sessions < ++tcb-> info-> cur_sessions)
            tcb-> info-> peak_sessions =   tcb-> info-> cur_sessions;

        /*  Copy HTTP environment                                            */
        session_tcb-> session_envsize = tcb-> request-> symbols_size;
        session_tcb-> session_envdata = mem_alloc (tcb-> request-> symbols_size);
        memcpy (session_tcb-> session_envdata,
                tcb-> request-> symbols_data,
                tcb-> request-> symbols_size);
                
        /*  Any URL arguments will be HTTP MIME encoded - decode them        */
        arguments = tcb-> request-> arguments;
        http_unescape (arguments, NULL);

        /*  Send initial event to session thread, keeping original           */
        /*  sender, for HTTP replies.                                        */
        event_send (
            &session_thread-> queue-> qid,
            &thread-> event-> sender,
            "_SESSION",                 /*  Event name to send               */
            (byte *) arguments,
            strlen  (arguments),        /*  Event body is argument data      */
            NULL, NULL, NULL, 0);       /*  No reply events                  */
      }
    else
        raise_exception (out_of_memory_event);
}


/*  -------------------------------------------------------------------------
 *  get_session_id
 *
 *  Returns session id from URL arguments if valid. Else returns NULL.
 *  URL argument is encoded as '+xxxxxxxx:yyyy" where xxxxxxxx is the
 *  thread name (SESSID_SIZE chars) and yyyy is the session step (4 digits).
 */

static char *
get_session_id (char *arguments)
{
    static char
        session_id [SESSID_SIZE + 1];   /*  Session id plus null             */

    ASSERT (arguments);
    if (strlen (arguments) >= SESSID_SIZE + 6
    &&  arguments [0] == '+' && arguments [SESSID_SIZE + 1] == ':')
      {
        memcpy (session_id, arguments + 1, SESSID_SIZE);
        session_id [SESSID_SIZE] = '\0';
        return (session_id);
      }
    else
        return (NULL);
}


/*  -------------------------------------------------------------------------
 *  get_session_step
 *
 *  Returns session step from URL arguments if valid.  Else returns 0.
 *  URL argument is encoded as '+xxxxxxxx:yyyy" where xxxxxxxx is the
 *  thread name (SESSID_SIZE chars) and yyyy is the session step (4 digits).
 */

static dbyte
get_session_step (char *arguments)
{
    int
        session_step;

    ASSERT (arguments);
    if (strlen (arguments) >= SESSID_SIZE + 6
    &&  arguments [0] == '+' && arguments [SESSID_SIZE + 1] == ':')
      {
        sscanf (arguments + SESSID_SIZE + 2, "%x", &session_step);
        return ((dbyte) session_step);
      }
    else
        return (0);
}


/*  -------------------------------------------------------------------------
 *  http_reply_html
 *
 *  Returns a formatted HTML message to the user.
 */

static void
http_reply_html (THREAD *thread, char *header, char *message)
{
    char
        *reply_text;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    reply_text = xstrcpy (NULL,
        "<HTML><BODY>",
        "<H4>", tcb-> applic_name, ":</H4><HR>",
        "<H2><EM>", header, "</EM></H2>",
        "<P>", message? message: "",
        "<H4><A HREF=\"/wtp", tcb-> applic_uri, "\">Connect Here</A></H4>",
        "<HR><P><FONTSIZE=-2>",
         TCONFIG ("general:copyright",
        "iMatix Studio - Copyright &#169 1997-2004 iMatix Corporation"),
        "</BODY></HTML>",
         NULL);

    send_wsx_ok (&tcb-> http_qid, reply_text);
    mem_free (reply_text);
}


/***********************   HTTP REPLY STARTING APPLIC   **********************/

MODULE http_reply_starting_applic (THREAD *thread)
{
    http_reply_html (thread, "Starting application...", NULL);
}


/***********************   HTTP REPLY APPLIC RUNNING   ***********************/

MODULE http_reply_applic_running (THREAD *thread)
{
    http_reply_html (thread, "Application is already running", NULL);
}


/***********************   HTTP REPLY STOPPING APPLIC   **********************/

MODULE http_reply_stopping_applic (THREAD *thread)
{
    http_reply_html (thread, "Shutting-down application...", NULL);
}


/*********************   HTTP REPLY APPLIC NOT RUNNING   *********************/

MODULE http_reply_applic_not_running (THREAD *thread)
{
    http_reply_html (thread, "Application is not running", NULL);
}


/************************   HTTP REPLY APPLIC REPORT   ***********************/

MODULE http_reply_applic_report (THREAD *thread)
{
#   define REPORT_TEXT                          \
    "<PRE>"                                     \
    "Application is  . . . . .: %s\n"           \
    "Started at date/time  . .: %s %s\n"        \
    "Active server processes .: %d\n"           \
    "Total transaction steps .: %ld\n"          \
    "Average transaction cost : %ld msecs\n"    \
    "Current user sessions . .: %ld\n"          \
    "Peak user sessions  . . .: %ld\n"          \
    "Total sessions handled  .: %ld\n"          \
    "Total fatal errors  . . .: %ld\n"          \
    "</PRE>"

    static char
        report [sizeof (REPORT_TEXT) + 100];
    char
        *state,
        *fmtdate,
        *fmttime;
    qbyte
        cur_sessions  = 0,
        peak_sessions = 0,
        trans_count   = 0,
        trans_cost    = 0,
        fatal_errors  = 0;

    if (tcb-> applic_state == APPLIC_STOPPED)
     {
        state   = "stopped";
        fmtdate = "-";
        fmttime = "";
      }
    else
      {
        fmtdate = conv_date_pict (tcb-> start_date, "d mmm, yy");
        fmttime = conv_time_pict (tcb-> start_time, "hh:mm:ss");
        cur_sessions  = tcb-> info-> cur_sessions;
        peak_sessions = tcb-> info-> peak_sessions;
        trans_count   = tcb-> info-> trans_count;
        trans_cost    = tcb-> info-> trans_cost;
        if (trans_count > 0)
            trans_cost = trans_cost / trans_count * 10;

        fatal_errors  = tcb-> info-> fatal_errors;
        if (tcb-> applic_state == APPLIC_RUNNING)
            state = "running";
        else
        if (tcb-> applic_state == APPLIC_LOCKED)
            state = "running, locked";
        else
            state = "?";
      }

    sprintf (report, REPORT_TEXT,
             state,
             fmtdate, fmttime,
             tcb-> nbr_servers,
             trans_count, trans_cost,
             cur_sessions, peak_sessions,
             tcb-> session_count,
             fatal_errors);

    http_reply_html (thread, "Application report:", report);
}


/************************   HTTP REPLY APPLIC LOCKED   ***********************/

MODULE http_reply_applic_locked (THREAD *thread)
{
    http_reply_html (thread, "Application is now locked", NULL);
}


/***********************   HTTP REPLY APPLIC UNLOCKED   **********************/

MODULE http_reply_applic_unlocked (THREAD *thread)
{
    http_reply_html (thread, "Application is now unlocked", NULL);
}


/*********************   HTTP REPLY APPLIC UNAVAILABLE   *********************/

MODULE http_reply_applic_unavailable (THREAD *thread)
{
    http_reply_html (thread, "Application not available",
                             "You can try to reconnect at a later time.");
}


/***********************   HTTP REPLY INVALID CONTROL   **********************/

MODULE http_reply_invalid_control (THREAD *thread)
{
    http_reply_html (thread, "Error", "Invalid control command.");
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_input (&sockq, 0, tcb-> handle, 0);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                        S E S S I O N   T H R E A D
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


/************************   INITIALISE SESSION DATA   ************************/

MODULE initialise_session_data (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Allocate empty program stack                                         */
    tcb-> call_stack      = mem_alloc (STACK_MAX * sizeof (char *));
    tcb-> session_context = sym_create_table ();
    if (tcb-> call_stack == NULL
    ||  tcb-> session_context == NULL)
        raise_exception (out_of_memory_event);
}


/**********************   SESSION USE INITIAL PROGRAM   **********************/

MODULE session_use_initial_program (THREAD *thread)
{
    char
        *root_program;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Set reply QID for all HTTP responses                                 */
    tcb-> http_qid = thread-> event-> sender;

    /*  Use application root program as defined in program table.  Entry
     *  code is WTP_DOINIT.  Build WTP_DO message with empty HTML stream.
     *  Thread event body contains initial program arguments (from URL).
     */
    root_program = session_root_program (tcb);
    if (root_program)
      {
        ASSERT (tcb-> session_program == NULL);
        tcb-> session_program = mem_strdup (root_program);

        ASSERT (tcb-> session_request == NULL);
        tcb-> session_reqsize = put_wtp_msg_do (
            &tcb-> session_request, 
            WTP_DO,                     /*  Message type                     */
            0,                          /*  ATP signature                    */
            tcb-> session_program,      /*  Program to execute               */
            WTP_DOINIT,                 /*  Program entry code               */
            session_uri (thread),       /*  URL for hyperlinks               */
            NULL,                       /*  Encoded HTTP data                */
            thread-> event-> body_size,
            thread-> event-> body,      /*  Call arguments size & data       */
            0,                          /*  Result of last call              */
            tcb-> session_envsize,      /*  HTTP environment block size      */
            tcb-> session_envdata,      /*    and contents                   */
            0, NULL,                    /*  Global context block             */
            0, NULL);                   /*  Local context block              */
      }
    else
      {
        raise_exception (exception_event);
        http_reply_html (thread, "Application root program not found", NULL);
      }
}


/*  -------------------------------------------------------------------------
 *  session_root_program
 *
 *  Locates the root program for the application.  If no root program is
 *  defined, returns NULL, else returns the name of the root program.
 */

static char *
session_root_program (TCB *tcb)
{
    SYMBOL
        *symbol;                        /*  Program symbol                   */

    symbol = tcb-> programs-> table-> symbols;
    while (symbol)
      {
        if (symbol-> value && streq (symbol-> value, "ROOT"))
            return (symbol-> name);
        symbol = symbol-> next;
      }
    return (NULL);
}


/*  -------------------------------------------------------------------------
 *  session_uri
 *
 *  Formats and returns URL for session.  URL argument is encoded as
 *  '+xxxxxxxx:yyyy" where xxxxxxxx is the thread name (SESSID_SIZE chars)
 *  and yyyy is the session step (4 digits).
 */

static char *
session_uri (THREAD *thread)
{
    static char
        uri [LINE_MAX];

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> session_step++;               /*  Cycles from 1 to n and around    */
    sprintf (uri, "/wtp%s?+%s:%04X",
        tcb-> applic_uri, thread-> name, tcb-> session_step);
    return (uri);
}


/**********************   SESSION USE CURRENT PROGRAM   **********************/

MODULE session_use_current_program (THREAD *thread)
{
    qbyte
        global_size,
        local_size;
    byte
        *global_data,
        *local_data;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Set reply QID for all HTTP responses                                 */
    tcb-> http_qid = thread-> event-> sender;

    /*  Current program is already okay - entry code is WTP_DOGET
     *  Build WTP_DO message using thread event body for HTML data
     */
    get_context (&global_size, &global_data, &local_size, &local_data);

    ASSERT (tcb-> session_request == NULL);
    tcb-> session_reqsize = put_wtp_msg_do (
        &tcb-> session_request,
        WTP_DO,                         /*  Message type                     */
        0,                              /*  ATP signature                    */
        tcb-> session_program,          /*  Program to execute               */
        WTP_DOGET,                      /*  Program entry code               */
        session_uri (thread),           /*  URL for hyperlinks               */
        (char *) thread-> event-> body, /*  Encoded HTTP data                */
        0, NULL,                        /*  Call arguments size & data       */
        0,                              /*  Result of last call              */
        0, NULL,                        /*  Environment data block           */
        global_size, global_data,       /*  Global context block             */
        local_size, local_data);        /*  Local context block              */
}

static void
get_context (qbyte *global_size, byte **global_data,
             qbyte *local_size,  byte **local_data)
{
    SYMBOL
        *symbol;

    symbol = sym_lookup_symbol (tcb-> session_context, "$global");
    if (symbol)
      {
        *global_size = ((DESCR *) symbol-> data)-> size;
        *global_data = ((DESCR *) symbol-> data)-> data;
      }
    else
      {
        *global_size = 0;
        *global_data = NULL;
      }
    symbol = sym_lookup_symbol (tcb-> session_context, tcb-> session_program);
    if (symbol)
      {
        *local_size = ((DESCR *) symbol-> data)-> size;
        *local_data = ((DESCR *) symbol-> data)-> data;
      }
    else
      {
        *local_size = 0;
        *local_data = NULL;
      }
}


/***********************   SESSION USE CALLED PROGRAM   **********************/

MODULE session_use_called_program (THREAD *thread)
{
    struct_wtp_msg_donecall
        *wtp_msg = NULL;
    byte
        entry_code,                     /*  WTP_DO entry code                */
        call_result;                    /*  If call failed                   */
    qbyte
        global_size,
        local_size;
    byte
        *global_data,
        *local_data;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Unpack WTP_DONECALL message into usable structure                    */
    get_wtp_msg_donecall (thread-> event-> body, &wtp_msg);

    /*  Save global and local context blocks, since we stay in program       */
    put_context (0, wtp_msg-> global_size, wtp_msg-> global_data);
    put_context (1, wtp_msg-> local_size,  wtp_msg-> local_data);

    /*  Push current program, use called program - entry code is WTP_DOINIT
     *  Build WTP_DO message, with empty HTML data, and pass arguments as
     *  supplied in wtp_donecall message.
     */
    strupc (wtp_msg-> program);         /*  Normalise the program name       */

    /*  Check various errors first of all                                    */
    if (tcb-> stack_ptr == STACK_MAX - 1)
        call_result = WTP_ERROROVERFLOW;
    else
    if (!sym_lookup_symbol (tcb-> programs-> table, wtp_msg-> program))
        call_result = WTP_ERRORNOTFOUND;
    else
    if (program_is_active (tcb, wtp_msg-> program))
        call_result = WTP_ERRORWOULDLOOP;
    else                                /*  Else stack new program           */
      {
        call_result = WTP_NOERROR;
        tcb-> call_stack [tcb-> stack_ptr++] = tcb-> session_program;
        tcb-> session_program = NULL;
        session_set_program (tcb, wtp_msg-> program);
      }
    if (call_result == WTP_NOERROR)
        entry_code = WTP_DOINIT;
    else
        entry_code = WTP_DOCONTINUE;

    get_context (&global_size, &global_data, &local_size, &local_data);

    ASSERT (tcb-> session_request == NULL);
    tcb-> session_reqsize = put_wtp_msg_do (
        &tcb-> session_request,
        WTP_DO,                         /*  Message type                     */
        0,                              /*  ATP signature                    */
        tcb-> session_program,          /*  Program to execute               */
        entry_code,                     /*  Program entry code               */
        session_uri (thread),           /*  URL for hyperlinks               */
        NULL,                           /*  Encoded HTTP data                */
        wtp_msg-> args_size,            /*  Call arguments size              */
        wtp_msg-> args_data,            /*  Call arguments data              */
        call_result,                    /*  Result of last call              */
        0, NULL,                        /*  Environment data block           */
        global_size, global_data,       /*  Global context block             */
        local_size, local_data);        /*  Local context block              */

    /*  Free areas used by message structure                                 */
    free_wtp_msg_donecall (&wtp_msg);
}


/*  -------------------------------------------------------------------------
 *  program_is_active
 *
 *  Returns TRUE if the program name is already active; the supplied name
 *  must have been normalised (put into uppercase) beforehand.
 */

static Bool
program_is_active (TCB *tcb, char *program)
{
    int
        prog_nbr;                       /*  Program on active stack          */

    for (prog_nbr = 0; prog_nbr < tcb-> stack_ptr; prog_nbr++)
        if (streq (tcb-> call_stack [prog_nbr], program))
             return (TRUE);

    return (FALSE);
}


static void
put_context (int local_block, qbyte size, byte *data)
{
    char
        *context_key;
    SYMBOL
        *symbol;

    if (local_block)
        context_key = tcb-> session_program;
    else
        context_key = "$global";

    /*  Delete context block if it already exists                            */
    symbol = sym_lookup_symbol (tcb-> session_context, context_key);
    if (symbol)
      {
        mem_free (symbol-> data);
        sym_delete_symbol (tcb-> session_context, symbol);
      }

    /*  Now store new block if wanted                                        */
    if (data)
      {
        symbol = sym_create_symbol (tcb-> session_context, context_key, NULL);
        if (symbol)
            symbol-> data = mem_descr (data, size);
        else
            raise_exception (out_of_memory_event);
      }
}


/*  -------------------------------------------------------------------------
 *  session_set_program
 *
 *  Sets a new tcb-> sesssion_program.  If the specified program does not
 *  exist, or is already active, leaves the session_program unchanged.
 *  Returns one of: WTP_NOERROR or WTP_ERRORNOTFOUND.
 */

static int
session_set_program (TCB *tcb, char *program)
{
    char
        *normalised;

    normalised = mem_strdup (program);
    strupc (normalised);
    if (sym_lookup_symbol (tcb-> programs-> table, normalised))
      {
        mem_strfree (&tcb-> session_program);
        tcb-> session_program = normalised;
        return (WTP_NOERROR);
      }
    else
      {
        mem_strfree (&normalised);
        return (WTP_ERRORNOTFOUND);
      }
}


/***********************   SESSION USE PARENT PROGRAM   **********************/

MODULE session_use_parent_program (THREAD *thread)
{
    struct_wtp_msg_donereturn
        *wtp_msg = NULL;
    qbyte
        global_size,
        local_size;
    byte
        *global_data,
        *local_data;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pop parent program - entry code is WTP_DOCONTINUE.  If stack was
     *  empty, raise session_exit exception.  Otherwise, build WTP_DO
     *  message with empty HTML data and return code from called program.
     */
    if (tcb-> stack_ptr == 0)
      {
        raise_exception (session_exit_event);
        return;
      }
    /*  Unpack WTP_DONERETURN message into usable structure                  */
    get_wtp_msg_donereturn (thread-> event-> body, &wtp_msg);

    /*  Save global context blocks, since we leave in program                */
    put_context (0, wtp_msg-> global_size, wtp_msg-> global_data);
    put_context (1, 0, NULL);           /*  Wipe local context block         */

    mem_strfree (&tcb-> session_program);
    tcb-> session_program = tcb-> call_stack [--tcb-> stack_ptr];

    get_context (&global_size, &global_data, &local_size, &local_data);

    ASSERT (tcb-> session_request == NULL);
    tcb-> session_reqsize = put_wtp_msg_do (
        &tcb-> session_request,
        WTP_DO,                         /*  Message type                     */
        0,                              /*  ATP signature                    */
        tcb-> session_program,          /*  Program to execute               */
        WTP_DOCONTINUE,                 /*  Program entry code               */
        session_uri (thread),           /*  URL for hyperlinks               */
        NULL,                           /*  Encoded HTTP data                */
        wtp_msg-> args_size,            /*  Call arguments size              */
        wtp_msg-> args_data,            /*  Call arguments data              */
        WTP_NOERROR,                    /*  Result of last call              */
        0, NULL,                        /*  Environment data block           */
        global_size, global_data,       /*  Global context block             */
        local_size, local_data);        /*  Local context block              */

    /*  Free areas used by message structure                                 */
    free_wtp_msg_donereturn (&wtp_msg);
}


/*************************   SESSION SHOW HTML DATA   ************************/

MODULE session_show_html_data (THREAD *thread)
{
    struct_wtp_msg_doneshow
        *wtp_msg = NULL;
    char
        *html_data;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Unpack WTP_DONESHOW message into usable structure                    */
    get_wtp_msg_doneshow (thread-> event-> body, &wtp_msg);

    /*  Save global and local context blocks, since we stay in program       */
    put_context (0, wtp_msg-> global_size, wtp_msg-> global_data);
    put_context (1, wtp_msg-> local_size,  wtp_msg-> local_data);

    /*  Save HTML data in session TCB, for refreshing if necessary           */
    /*  We translate accented characters into SGML metacharacters            */
    if (tcb-> session_screen == NULL)
        tcb-> session_screen = mem_alloc (FORM_MAX + 1);

    html_data = wtp_msg-> html_data;
    http_encode_meta (tcb-> session_screen, &html_data, FORM_MAX, TRUE); 

    /*  Send HTML data back to HTTP agent and thence on to the browser       */
    send_wsx_ok (&tcb-> http_qid, tcb-> session_screen);

    /*  Free areas used by message structure                                 */
    free_wtp_msg_doneshow (&wtp_msg);
}


/*************************   SESSION RESYNCHRONIZE   *************************/

MODULE session_resynchronize (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  We have received a new request for a session that is already busy.
        This typically happens when users click twice or are impatient for
        a slow response to finish.  The browser behavior is to close the
        first active socket and open a new one with the second click.  In
        Xitami this is two threads.  We handle this by discarding the old
        http_qid and taking the new one, but we do not send anything back
        to the browser - it has to wait until the server is correctly done
        with its work and sends the reply back.
     */
    tcb-> http_qid = thread-> event-> sender;
}


/**********************   ROUTE WTP REQUEST TO SERVER   **********************/

MODULE route_wtp_request_to_server (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Program symbol                   */
    THREAD
        *server_thread;                 /*  Symbol refers to thread          */
    TCB
        *server_tcb;
    QID
        target_qid;                     /*  Where do we send the request?    */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Look for available server based on program symbol table and server
     *  ready flags...  If none available, add do message to request queue.
     */
    target_qid = tcb-> do_queue-> qid;  /*  By default                       */
    symbol = sym_lookup_symbol (tcb-> programs-> table, tcb-> session_program);
    while (symbol)
      {
        if (streq (symbol-> name, tcb-> session_program))
          {
            server_thread = symbol-> data;
            server_tcb    = server_thread-> tcb;
            if (server_tcb-> server_ready)
              {
                server_tcb-> server_ready = FALSE;
                target_qid = server_thread-> queue-> qid;
                break;
              }
          }
        symbol = symbol-> next;
      }
    event_send (
        &target_qid,
        &thread-> queue-> qid,
        "_REQUEST",
        tcb-> session_request,
        tcb-> session_reqsize,
        NULL, NULL, NULL, 0);

    mem_free (tcb-> session_request);
    tcb-> session_request = NULL;
}


/**************************   SESSION SET TIMEOUT   **************************/

MODULE session_set_timeout (THREAD *thread)
{
    long
        timeout;                        /*  Timeout in seconds               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    timeout = atol (TCONFIG ("general:session_timeout", "60"));
    timeout = timeout * 60 * 100;       /*  Minutes => 1/100th seconds       */
    send_alarm (&timeq, 0, timeout, 0, NULL);
}


/*********************   SESSION SHOW APPLICATION ENDED   ********************/

MODULE session_show_application_ended (THREAD *thread)
{
    char
        *goodbye;                       /*  Sign-off message or URL          */

    goodbye = TCONFIG ("general:goodbye", "Goodbye");
    if (*goodbye == '@')
        send_wsx_redirect (&tcb-> http_qid, goodbye + 1);
    else
        http_reply_html (thread, "Finished", goodbye);
}


/*********************   SESSION SHOW APPLICATION ERROR   ********************/

MODULE session_show_application_error (THREAD *thread)
{
    struct_wtp_msg_doneerror
        *wtp_msg = NULL;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_wtp_msg_doneerror (thread-> event-> body, &wtp_msg);
    http_reply_html (thread, "Error", wtp_msg-> error_text);
    free_wtp_msg_doneerror (&wtp_msg);
}


/**********************   HTTP REPLY SERVER TIMED OUT   **********************/

MODULE http_reply_server_timed_out (THREAD *thread)
{
    http_reply_html (thread, "Application program was looping", NULL);
}


/***********************   HTTP REPLY SERVER ABORTED   ***********************/

MODULE http_reply_server_aborted (THREAD *thread)
{
    http_reply_html (thread, "Application program aborted", NULL);
}


/*******************   HTTP REPLY INSUFFICIENT RESOURCES   *******************/

MODULE http_reply_insufficient_resources (THREAD *thread)
{
    http_reply_html (thread, "Application under stress - try later", NULL);
}


/*************************   SESSION END PROCESSING   ************************/

MODULE session_end_processing (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in context table          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> info-> cur_sessions--;        /*  Update info block                */

    /*  Go through context table, and delete symbol context blocks.          */
    symbol = tcb-> session_context-> symbols;
    while (symbol)
      {
        mem_free (symbol-> data);
        symbol = symbol-> next;
      }
    sym_delete_table (tcb-> session_context);

    /*  Free program call stack and other areas                             */
    while (tcb-> stack_ptr > 0)
      {
        tcb-> stack_ptr--;
        mem_free (tcb-> call_stack [tcb-> stack_ptr]);
      }
    mem_free (tcb-> call_stack);
    mem_free (tcb-> session_screen);

    unuse_programs_table (tcb);
    unuse_servers_table  (tcb);
    unuse_info_table     (tcb);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                          S E R V E R   T H R E A D
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


/**************************   READ SERVER MESSAGE   **************************/

MODULE read_server_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  WTP messages are compatible with the GET_BLOCK method of SMTTRAN     */
    send_get_huge (&tranq, tcb-> handle, NULL);
    event_wait ();                      /*  Wait for transfer agent reply    */
}


/*************************   DECODE SERVER MESSAGE   *************************/

MODULE decode_server_message (THREAD *thread)
{
    struct_wtp_msg
        *wtp_msg = NULL;
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (the_external_event == ok_event)
      {
        /*  Free any previous message, then get new one from event body      */
        mem_strfree (&tcb-> server_msg);
        exdr_read   (thread-> event-> body, SMT_TRAN_GETH_OK,
                     &tcb-> server_msgsize, &tcb-> server_msg);

        /*  Get just the message type                                        */
        get_wtp_msg ((byte *) tcb-> server_msg, &wtp_msg);
        tcb-> message_type = wtp_msg-> type;
        free_wtp_msg (&wtp_msg);

        switch (tcb-> message_type)
          {
            case WTP_CONNECT:
                the_next_event = wtp_connect_event;
                break;
            case WTP_REGISTER:
                the_next_event = wtp_register_event;
                break;
            case WTP_READY:
                the_next_event = wtp_ready_event;
                break;
            case WTP_DISCONNECT:
                the_next_event = wtp_disconnect_event;
                break;
            case WTP_OK:
                the_next_event = wtp_ok_event;
                break;
            case WTP_ERROR:
                the_next_event = wtp_error_event;
                break;
            case WTP_DO:
                the_next_event = wtp_do_event;
                break;
            case WTP_DONESHOW:          /*  We handle these in much the      */
            case WTP_DONECALL:          /*    way; reply to session thread   */
            case WTP_DONERETURN:
            case WTP_DONEEXIT:
            case WTP_DONEERROR:
                the_next_event = wtp_done_event;
                break;
            default:
                the_next_event = error_event;
          }
      }
    else
        raise_exception (the_external_event);
}


/************************   HANDLE SERVER CONNECTION   ***********************/

MODULE handle_server_connection (THREAD *thread)
{
    struct_wtp_msg_connect
        *wtp_msg = NULL;
    int
        server_nbr;                     /*  Index into application servers   */
    long
        callback;
    SERVER
        *server;                        /*  Entry into servers table         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_wtp_msg_connect ((byte *) tcb-> server_msg, &wtp_msg);

    /*  Look for server with matching callback key                           */
    callback = atol (wtp_msg-> callback_key);
    for (server_nbr = 0; server_nbr < tcb-> nbr_servers; server_nbr++)
      {
        server = &tcb-> servers-> table [server_nbr];
        if (server-> callback == callback)
            break;
      }
    /*  Did we find it okay?                                                 */
    if (server_nbr < tcb-> nbr_servers)
      {
        ASSERT (server-> thread == NULL);
        tcb-> server_name  = mem_strdup (atp_name_value (server-> atp));
        tcb-> server_index = server_nbr;
        server-> thread    = thread;
        server-> signature = wtp_msg-> signature;
      }
    else
      {
        sendfmt (&operq, "ERROR",
                 "wtpman: unauthorised server callback: %s",
                  wtp_msg-> callback_key);
        raise_exception (error_event);
      }
    free_wtp_msg_connect (&wtp_msg);
}


/***********************   HANDLE SERVER REGISTRATION   **********************/

MODULE handle_server_registration (THREAD *thread)
{
    struct_wtp_msg_register
        *wtp_msg = NULL;
    SYMBOL
        *symbol;                        /*  Newly-created symbol             */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_wtp_msg_register ((byte *) tcb-> server_msg, &wtp_msg);
    strupc (wtp_msg-> program);

    /*  Create new entry in program lookup table; don't check duplicates
     *  If the program is a root program, its value is set to "ROOT", else
     *  to null.
     */
    symbol = sym_create_symbol (tcb-> programs-> table, wtp_msg-> program, NULL);
    if (symbol == NULL)
      {
        wtp_send_msg_error (thread, WTP_ERRORFATAL);
        raise_exception (out_of_memory_event);
      }
    else
      {
        wtp_send_msg_ok (thread);
        symbol-> data = thread;
        if (wtp_msg-> is_root)
            symbol-> value = mem_strdup ("ROOT");
      }
    free_wtp_msg_register (&wtp_msg);
}


static void
wtp_send_msg_error (THREAD *thread, dbyte code)
{
    byte
        *buffer;                        /*  Buffer holds formatted WTP msg   */
    qbyte
        size;                           /*  Size of formatted message        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    size = put_wtp_msg_error (&buffer, WTP_ERROR, code, "Error");
    send_put_huge (&tranq, tcb-> handle, size, buffer, NULL);
    mem_free (buffer);
}


static void
wtp_send_msg_ok (THREAD *thread)
{
    byte
        *buffer;                        /*  Buffer holds formatted WTP msg   */
    qbyte
        size;                           /*  Size of formatted message        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    size = put_wtp_msg_ok (&buffer, WTP_OK);
    send_put_huge (&tranq, tcb-> handle, size, buffer, NULL);
    mem_free (buffer);
}


/**************************   HANDLE SERVER READY   **************************/

MODULE handle_server_ready (THREAD *thread)
{
    wtp_send_msg_ok (thread);
}


/**************************   WTP SEND DO PROGRAM   **************************/

MODULE wtp_send_do_program (THREAD *thread)
{
    struct_wtp_msg_do
        *wtp_msg = NULL;
    byte
        *buffer;                        /*  Buffer holds formatted WTP msg   */
    qbyte
        size;                           /*  Size of formatted message        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Set reply QID for all eventual responses                             */
    tcb-> session_qid = thread-> event-> sender;

    /*  Event body holds a DO message complete except for the signature.
     *  We have to decode it, sign it, rebuild it, and send it to the
     *  server process.
     */
    get_wtp_msg_do (thread-> event-> body, &wtp_msg);

    size = put_wtp_msg_do (&buffer, WTP_DO,
        tcb-> servers-> table [tcb-> server_index].signature,
        wtp_msg-> program,
        wtp_msg-> entry_code,
        wtp_msg-> http_uri,
        wtp_msg-> http_data,
        wtp_msg-> args_size,
        wtp_msg-> args_data,
        wtp_msg-> call_result,
        wtp_msg-> env_size,
        wtp_msg-> env_data,
        wtp_msg-> global_size,
        wtp_msg-> global_data,
        wtp_msg-> local_size,
        wtp_msg-> local_data);
    send_put_huge (&tranq, tcb-> handle, size, buffer, NULL);
    mem_free (buffer);

    free_wtp_msg_do (&wtp_msg);
    tcb-> server_ready = FALSE;
    tcb-> entry_time   = time_now ();
}


/***************************   HANDLE SERVER DONE   **************************/

MODULE handle_server_done (THREAD *thread)
{
    char
        *method = NULL;                 /*  Method to send to session        */
    int
        elapsed_time;                   /*  Transaction elapsed time         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    switch (tcb-> message_type)
      {
        case WTP_DONESHOW:
            method = "_SESSION_SHOW";
            break;
        case WTP_DONECALL:
            method = "_SESSION_CALL";
            break;
        case WTP_DONERETURN:
            method = "_SESSION_RETURN";
            break;
        case WTP_DONEEXIT:
            method = "_SESSION_EXIT";
            break;
        case WTP_DONEERROR:
            method = "_SESSION_ERROR";
            break;
        default:
            sendfmt (&operq, "ERROR", "wtpman: handle_server_done() failed");
      }
    /*  Unless there was a screw-up, send the ATP message through as-is to
     *  the session thread.  The contents of the message depend on the type
     *  of the message.
     */
    if (method)
        event_send (
            &tcb-> session_qid,
            NULL,
            method,
            (byte *) tcb-> server_msg,
            tcb-> server_msgsize,
            NULL, NULL, NULL, 0);

    /*  Compute elapsed time and total so far                                */
    elapsed_time = time_to_csecs (time_now ())
                 - time_to_csecs (tcb-> entry_time);
    if (elapsed_time < 0)               /*  Passed over midnight             */
        elapsed_time += INTERVAL_DAY;

    tcb-> info-> trans_count += 1;
    tcb-> info-> trans_cost  += elapsed_time;;
}


/***************************   SERVER SET TIMEOUT   **************************/

MODULE server_set_timeout (THREAD *thread)
{
    long
        timeout;                        /*  Timeout in seconds               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    timeout = atol (TCONFIG ("general:program_timeout", "60"));
    timeout = timeout * 100;            /*  Seconds => 1/100th seconds       */
    send_alarm (&timeq, 0, timeout, 0, NULL);
}


/*************************   WTP SEND NOT EXPECTED   *************************/

MODULE wtp_send_not_expected (THREAD *thread)
{
    wtp_send_msg_error (thread, WTP_ERRORUNEXPECTED);
}


/*************************   WTP SEND NOT CONNECTED   ************************/

MODULE wtp_send_not_connected (THREAD *thread)
{
    wtp_send_msg_error (thread, WTP_ERRORUNCONNECTED);
}


/************************   WTP SEND NOT AUTHORISED   ************************/

MODULE wtp_send_not_authorised (THREAD *thread)
{
    wtp_send_msg_error (thread, WTP_ERRORUNAUTHORISED);
}


/****************************   WTP SEND INVALID   ***************************/

MODULE wtp_send_invalid (THREAD *thread)
{
    wtp_send_msg_error (thread, WTP_ERRORINVALID);
}


/*************************   TAKE DO REQUEST IF ANY   ************************/

MODULE take_do_request_if_any (THREAD *thread)
{
    EVENT
        *event;                         /*  Event information block          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get next event off queue                                             */
    event = event_iterate (tcb-> do_queue, NULL);
    if (event)
      {
        if (thread-> event)             /*  Release any thread event         */
            event_destroy (thread-> event);

        /*  Get event off queue; it now belongs to the thread                */
        thread-> event = event_accept (tcb-> do_queue, event);
        the_next_event = ok_event;
      }
    else
        the_next_event = not_found_event;
}


/************************   SERVER PROCESS IS READY   ************************/

MODULE server_process_is_ready (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> server_ready = TRUE;
}


/************************   SIGNAL SERVER TIMED OUT   ************************/

MODULE signal_server_timed_out (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell application thread to check & refresh its server table          */
    sendfmt (&tcb-> applic_qid, "_REFRESH", "");
    sendfmt (&operq, "ERROR", "wtpman: server '%s' looping", tcb-> server_name);

    /*  Tell session thread to forget it, and inform the user                */
    sendfmt (&tcb-> session_qid, "_SERVER_TIMEOUT", "");
}


/*************************   SIGNAL SERVER ABORTED   *************************/

MODULE signal_server_aborted (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Tell application thread to check & refresh its server table          */
    sendfmt (&tcb-> applic_qid, "_REFRESH", "");
    sendfmt (&operq, "ERROR", "wtpman: server '%s' aborted", tcb-> server_name);

    /*  Tell session thread to forget it, and inform the user                */
    sendfmt (&tcb-> session_qid, "_SERVER_ABORT", "");
}


/*************************   SERVER END PROCESSING   *************************/

MODULE server_end_processing (THREAD *thread)
{
    PROCESS
        *pid;
    SYMBOL
        *symbol,
        *next;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Kill server process if it is still running                           */
    pid = &tcb-> servers-> table [tcb-> server_index].pid;
    if (*pid != NULL_PROCESS)
      {
        if (process_status (*pid) == PROCESS_RUNNING)
            process_kill (*pid);
        else
            process_close (*pid);

        *pid = NULL_PROCESS;
      }

    /*  Go through program symbol table, and delete any symbols that refer
     *  to this thread.
     */
    symbol = tcb-> programs-> table-> symbols;
    while (symbol)
      {
        next = symbol-> next;
        if (symbol-> data == thread)
            sym_delete_symbol (tcb-> programs-> table, symbol);

        symbol = next;
      }
    /*  As far as the applic thread is concerned, we're gone                 */
    tcb-> servers-> table [tcb-> server_index].thread = NULL;
    unuse_programs_table (tcb);
    unuse_servers_table  (tcb);
    unuse_info_table     (tcb);
}


/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                              A L L   T H R E A D S
  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


/************************   CLEAR ALARMS FOR THREAD   ************************/

MODULE clear_alarms_for_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    event_send (
        &timeq,
        &thread-> queue-> qid,
        "FLUSH",
        NULL, 0,
        NULL, NULL, NULL, 0);
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR",
             "wtpman: error on socket: %s", thread-> event-> body);
}


/**************************   SIGNAL OUT OF MEMORY   *************************/

MODULE signal_out_of_memory (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR", "wtpman: no memory available");
    sprintf (server_message, "Insufficient memory");
}


/**************************   SIGNAL INVALID EVENT   *************************/

MODULE signal_invalid_event (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR", "wtpman: invalid dialog event detected");
}


/***************************   CHECK THREAD TYPE   ***************************/

MODULE check_thread_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = tcb-> thread_type;
}


/************************   SHUTDOWN THE APPLICATION   ***********************/

MODULE shutdown_the_application (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    smt_shutdown ();                    /*  Halt the application             */
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)
        close_socket (tcb-> handle);

    /*  Potentially used in each thread                                      */
    mem_free (tcb-> server_msg);
    mem_free (tcb-> server_name);
    mem_free (tcb-> session_program);
    mem_free (tcb-> session_request);
    mem_free (tcb-> session_envdata);

    /*  Allocated by applic thread but shared by server & session threads:   */
    if (tcb-> thread_type == master_event)
      {
        sym_delete_table (tcb-> config_table);
        mem_free         (tcb-> config_file);
      }
    else
    if (tcb-> thread_type == applic_event)
      {
        if (tcb-> do_queue)
            queue_destroy (tcb-> do_queue);
        sym_delete_table (tcb-> config_table);
        mem_free (tcb-> config_file);
        mem_free (tcb-> applic_uri);
        mem_free (tcb-> applic_name);
      }
    the_next_event = terminate_event;
}


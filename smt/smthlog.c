/*===========================================================================*
 *                                                                           *
 *  smthlog.c -                                                              *
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

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smtrdnsl.h"


/*- Messages ----------------------------------------------------------------*/

#define CUR_VERSION "1.0"

#define PROGRAM_NAME                                                         \
    "Xixlat logfile address translator v" CUR_VERSION " (c) 1997-2000 iMatix"

#define COPYRIGHT                                                            \
    PROGRAM_NAME "\n"                                                        \
    "Xixlat is free software and comes with ABSOLUTELY NO WARRANTY.\n"       \
    "You may redistribute this software under certain conditions;\n"         \
    "read the file LICENSE.TXT for details. Type xixlat -h for help.\n"

#define USAGE                                                                \
    "Syntax: xixlat [-d] [-v] [-r] [-s DNS-server] [-h] logfile\n"           \
    "Options:\n"                                                             \
    "  -d              Debug DNS lookups into xixlat.log.\n"                 \
    "  -v              Verbose mode.\n"                                      \
    "  -r              Use recursive DNS lookups - off by default.\n"        \
    "                  Recursive DNS lookups are less work, but slower.\n"   \
    "  -s DNS-server   Use this DNS server.  Specify the address as a\n"     \
    "                  name or string address (xxx.xxx.xxx.xxx).\n"          \
    "                  Defaults to 127.0.0.1.\n"                             \
    "  -h              Show summary of command-line options.\n"              \
    "  logfile         Name of logfile to resolve.  The resolved log file\n" \
    "                  has the same name and the extension '.hlo'.\n"        \
    "\nThe order of arguments is not important. Switches and filenames\n"    \
    "are case sensitive. See documentation for detailed information.\n"

#define NO_SERVER                                                            \
    "No default DNS server is defined or could be located.  You must use\n"  \
    "the '-s' option to specify a DNS server."


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME   "smthlog"          /*  Our public name                  */
#define BUFFER_SIZE  2048

#define HREQ_STATE_REQ       1
#define HREQ_STATE_OK        2
#define HREQ_STATE_ERROR     3
#define HREQ_STATE_TIMEOUT   4
#define HREQ_STATE_NOT_FOUND 5

#define STACK_SIZE           20


/*- Structures---------------------------------------------------------------*/

typedef struct _HREQ                    /*  Host Request structure           */
{
    struct _HREQ
         *next, *prev;                  /*    Linked list pointer            */
    qbyte id;                           /*    Request id                     */
    char *log_line;                     /*    Log line value                 */
    char *ip_value;                     /*    IP address of host             */
    char *host_name;                    /*    Host name                      */
    byte state;                         /*    State of request               */
} HREQ;

typedef struct                          /*  Thread context block:            */
{
    /* Common data                                                           */
    event_t
        thread_type;                    /*    Thread type indicator          */

    /* Master thread data                                                    */
    LIST
        hrequest;                       /*    Host Request List head         */
    short
        nb_request;                     /*    Number of request in list      */
    FILE
        *in_log,                        /*    Input  log file handle         */
        *out_log,                       /*    Output log file handle         */
        *err_log;                       /*    Error  log file handle         */
    qbyte
        write_nbr,                      /*    Number of line writen to log   */
        read_nbr;                       /*    Number of line read from log   */
    Bool
        end_of_file;                    /*    End of file marker             */

    /* Request thread data                                                   */
    HREQ
        *hreq;                          /*    Request to execute             */
    QID
        reply_to;                       /*    Message Queue to reply         */
} TCB;


/*- Function prototypes -----------------------------------------------------*/

static HREQ *create_hreq (char *log_line, qbyte read_nbr);
static void  delete_hreq (HREQ *hreq);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread contect block     */
static QID
    operq,                              /*  Operator console event queue     */
    rdnsq;                              /*  Reverse DNS agent event queue    */

#define MSG_MAX BUFFER_SIZE + 64

static Bool
    verbose_mode = FALSE;               /*  Show all messages                */
static qbyte
    lines_processed;                    /*  Number of lines processed        */
static time_t
    time_started;                       /*  Time that processing started     */
static byte
    msg_body [MSG_MAX];                 /*  Messages sent to other agents    */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed()     */
    msg = { MSG_MAX,  msg_body };
static char
    buffer [BUFFER_SIZE],               /*  General-use string buffer        */
    *arg_server,                        /*  Name of DNS server               */
    **argv;                             /*  Command-line arguments           */
static int
    arg_index = 1,
    argc;

#include "smthlog.d"                    /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int smthlog_init (int v_argc, char *v_argv [])
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */

#   include "smthlog.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event,
                                             SMT_PRIORITY_MAX);

    /*  Reply events from reverse DNS agent                                  */
    method_declare (agent, "HOST_NAME",       host_event,             0);
    method_declare (agent, "HOST_IP",         ip_event,               0);
    method_declare (agent, "HOST_ERROR",      error_event,            0);
    method_declare (agent, "HOST_END",        end_event,              0);
    method_declare (agent, "HOST_TIMEOUT",    timeout_event,          0);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",         master_event,           0);
    method_declare (agent, "_REQUEST",        request_event,          0);
    method_declare (agent, "_COMPLETE",       request_complete_event, 0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that RDNS agent is running, else start it up                  */
    smtrdns_init ();
    if ((thread = thread_lookup (SMT_RDNS, "")) != NULL)
        rdnsq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create initial, unnamed thread                                       */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
        argc = v_argc;
        argv = v_argv;
      }

    puts (COPYRIGHT);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    list_reset (&tcb-> hrequest);       /*    Resest request list            */
    tcb-> in_log      = NULL;
    tcb-> out_log     = NULL;
    tcb-> err_log     = NULL;
    tcb-> read_nbr    = 0;
    tcb-> write_nbr   = 0;
    tcb-> nb_request  = 0;
    tcb-> end_of_file = FALSE;
}


/*************************   INITIALISE DNS LIBRARY   ************************/

MODULE initialise_dns_library (THREAD *thread)
{
    rdns_init (&server_list);
}


/***************************   GET NEXT ARGUMENT   ***************************/

MODULE get_next_argument (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (argc < 2)
        the_next_event = help_event;    /*  No arguments - show help         */
    else
    if (arg_index < argc)               /*  Get and check next argument      */
      {
        strcpy (buffer, argv [arg_index++]);
        strcrop (buffer);
        if (strprefixed (buffer, "-s"))
            if (arg_index < argc)
              {
                the_next_event = server_ip_event;
                arg_server = argv [arg_index++];
              }
            else
                the_next_event = help_event;
        else
        if (strprefixed (buffer, "-d"))
            the_next_event = debug_mode_event;
        else
        if (strprefixed (buffer, "-v"))
            the_next_event = verbose_mode_event;
        else
        if (strprefixed (buffer, "-r"))
            the_next_event = recursive_mode_event;
        else
        if (buffer [0] == '-')          /*  -h or any unknown switch         */
            the_next_event = help_event;
        else
            the_next_event = log_file_event;
      }
    else
        the_next_event = end_event;
}


/*******************************   SHOW HELP   *******************************/

MODULE show_help (THREAD *thread)
{
    int
        index;
    struct in_addr
        inaddr;                         /*  Used to format IP address        */

    puts (USAGE);
    if (server_list.ns_count > 0)
      {
        printf ("Current DNS configuration:\n");
        for (index = 0; index < server_list.ns_count; index++)
          {
            inaddr.s_addr = server_list.ns_addr [index].sin_addr.s_addr;
            printf ("    %s\n", inet_ntoa (inaddr));
          }
      }
    else
        puts (NO_SERVER);
}


/**************************   SET SERVER IP VALUE   **************************/

MODULE set_server_ip_value (THREAD *thread)
{
    int
        index;
    struct in_addr
        inaddr;                         /*  Used to format IP address        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    inaddr.s_addr = inet_addr (strskp (arg_server));
    if (inaddr.s_addr != 0xFFFFFFFFUL
    &&  inaddr.s_addr != 0)
      {
        if (server_list.ns_count == MAX_NS)
            server_list.ns_count--;
        for (index = server_list.ns_count - 1; index >= 0; index--)
          {
            server_list.ns_addr [index + 1].sin_addr.s_addr =
                server_list.ns_addr [index].sin_addr.s_addr;
            server_list.ns_addr [index + 1].sin_port =
                server_list.ns_addr [index].sin_port;
            server_list.recursive_accept [index + 1] =
                server_list.recursive_accept [index];
          }
        server_list.ns_addr [0].sin_addr.s_addr = inaddr.s_addr;
        server_list.ns_addr [0].sin_port = htons (DNS_PORT);
        server_list.recursive_accept [0] = dns_recursive;
        server_list.ns_count++;
      }
    else
      {
        coprintf ("%s: Invalid DNS IP address !!!", arg_server);
        raise_exception (fatal_event);
      }
}


/*****************************   SET DEBUG MODE   ****************************/

MODULE set_debug_mode (THREAD *thread)
{
    dns_debug_mode = TRUE;
    console_set_mode (CONSOLE_DATETIME);
    console_capture  ("xixlat.log", 'a');
}


/****************************   SET VERBOSE MODE   ***************************/

MODULE set_verbose_mode (THREAD *thread)
{
    verbose_mode = TRUE;                /*  Show all messages                */
}


/***************************   SET RECURSIVE MODE   **************************/

MODULE set_recursive_mode (THREAD *thread)
{
    int
       index;

    dns_recursive = TRUE;
    for (index = 0; index < server_list.ns_count; index++)
        server_list.recursive_accept [index] = TRUE;
}


/****************************   CHECK DNS CONFIG   ***************************/

MODULE check_dns_config (THREAD *thread)
{
    /*  If no DNS server was specified, use the local host information       */
    if (server_list.ns_count == 0)
      {
        arg_server = "127.0.0.1";
        set_server_ip_value (thread);
      }
}


/*****************************   OPEN LOG FILE   *****************************/

MODULE open_log_file (THREAD *thread)
{
    char
        *delim;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> in_log = file_open (buffer, 'r');
    if (tcb-> in_log)
      {
        sendfmt (&operq, "INFO", "processing %s...", buffer);
        delim = strrchr (buffer, '.');
        if (delim)
            strcpy (++delim, "hlo");
        else
            strcat (buffer, ".hlo");
        tcb-> out_log = file_open (buffer, 'w');
        if (tcb-> out_log)
            the_next_event = ok_event;
        else
          {
            sendfmt (&operq, "ERROR", "can't create %s", buffer);
            the_next_event = error_event;
          }
      }
    else
      {
        sendfmt (&operq, "ERROR", "can't open %s", buffer);
        the_next_event = error_event;
      }
    lines_processed = 0;                /*  Number of lines processed        */
    time_started = time (NULL);         /*  Time that processing started     */
}


/********************   CHECK IF FIRST REQUEST COMPLETE   ********************/

MODULE check_if_first_request_complete (THREAD *thread)
{
    HREQ
        *request;
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    request = tcb-> hrequest.next;      /*  Get first request in list        */
    if (request
    &&  request != (HREQ *) &tcb-> hrequest)
      {
        if (request-> state != HREQ_STATE_REQ)
            the_next_event = first_request_event;
        else
            the_next_event = not_first_event;
      }
    else
    if (tcb-> end_of_file)
        the_next_event = end_of_file_event;
    else
        the_next_event = empty_stack_event;
}


/*****************************   READ NEXT LINE   ****************************/

MODULE read_next_line (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (fgets (buffer, BUFFER_SIZE, tcb-> in_log) == NULL)
        buffer [0] = '\0';
    else
      {
        tcb-> read_nbr++;
        lines_processed++;
      }
}


/***********************   REMOVE REQUEST FORM STACK   ***********************/

MODULE remove_request_form_stack (THREAD *thread)
{
    HREQ
        *request;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    request = tcb-> hrequest.next;
    list_unlink (request);
    delete_hreq (request);
    tcb-> nb_request--;
}

static void
delete_hreq (HREQ *hreq)
{
    if (hreq == NULL)
        return;
    if (hreq-> host_name)
        mem_free (hreq-> host_name);
    if (hreq-> log_line)
        mem_free (hreq-> log_line);
    if (hreq-> ip_value)
        mem_free (hreq-> ip_value);
    mem_free (hreq);
}


/*************************   SEND REQUEST COMPLETE   *************************/

MODULE send_request_complete (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    SEND (&tcb-> reply_to, "_COMPLETE", "");
}


/************************   SEND REQUEST TO RESOLVER   ***********************/

MODULE send_request_to_resolver (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    if (tcb-> hreq == NULL
    ||  tcb-> hreq-> ip_value == NULL)
      {
        the_next_event = error_event;
        return;
      }

    msg_size = exdr_writed (&msg, SMT_GET_HOST_NAME, (qbyte) 0,
                            tcb-> hreq-> ip_value, tcb-> hreq-> id);

    event_send (
        &rdnsq,                         /*  Send to specified queue          */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "GET_HOST_NAME",                /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*************************   SET FEEDBACK TO ERROR   *************************/

MODULE set_feedback_to_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> hreq-> state = HREQ_STATE_ERROR;
}


/****************************   STORE HOST NAME   ****************************/

MODULE store_host_name (THREAD *thread)
{
    qbyte
         id;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    exdr_read (thread-> event-> body, SMT_HOST_NAME,
               NULL, &tcb-> hreq-> host_name, &id);
    if (id == tcb-> hreq-> id
    &&  tcb-> hreq-> host_name)
        tcb-> hreq-> state = HREQ_STATE_OK;
    else
        tcb-> hreq-> state = HREQ_STATE_ERROR;

}


/**************************   STORE LINE TO OUTPUT   *************************/

MODULE store_line_to_output (THREAD *thread)
{
    HREQ
        *request;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    request = tcb-> hrequest.next;
    if (request-> state == HREQ_STATE_OK
    &&  request-> host_name)
        fwrite (request-> host_name, 1, strlen (request-> host_name),
               tcb-> out_log);
    else
        fwrite (request-> ip_value, 1, strlen (request-> ip_value),
               tcb-> out_log);
    fwrite (request-> log_line, 1, strlen (request-> log_line),
               tcb-> out_log);
    fflush (tcb-> out_log);
}


/*****************************   CREATE REQUEST   ****************************/

MODULE create_request (THREAD *thread)
{
    HREQ
        *request;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (strnull (buffer))
        the_next_event = end_of_file_event;
    else
      {
         request = create_hreq (buffer, tcb-> read_nbr);
         if (request)
           {
             list_relink_before (&tcb-> hrequest, request);
             tcb-> nb_request++;
             the_next_event = ok_event;
           }
         else
             the_next_event = error_event;
      }
}


static HREQ *
create_hreq (char *log_line, qbyte read_nbr)
{
    HREQ
        *request = NULL;
    char
        *end;
    struct in_addr
        inaddr;                         /*  Used to format IP address        */

    /*  Check if first word is a IP address                                  */
    end = strchr (log_line, ' ');
    if (end == NULL)
        return (NULL);
    *end = '\0';
    inaddr.s_addr = inet_addr (log_line);
    if (inaddr.s_addr == 0xFFFFFFFFUL
    ||  inaddr.s_addr == 0)
      {
        *end = ' ';                     /* Restore previous value in buffer  */
        return (NULL);
      }

    request = mem_alloc (sizeof (HREQ));
    if (request)
      {
         request-> host_name = NULL;
         request-> ip_value  = mem_strdup (log_line);
         *end = ' ';                    /* Restore previous value in buffer  */
         request-> log_line  = mem_strdup (end);
         request-> id        = read_nbr;
         request-> state     = HREQ_STATE_REQ;
         list_reset (request);
      }
    return (request);
}


/*************************   CREATE REQUEST THREAD   *************************/

MODULE create_request_thread (THREAD *thread)
{
    THREAD
        *child;                         /*  Handle to child thread           */
    TCB
        *main_tcb;

    main_tcb = thread-> tcb;

    if ((child = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&child-> queue-> qid, "_REQUEST", "");
        tcb = (TCB *) child-> tcb;

        tcb-> thread_type   = request_event;
        list_reset (&tcb-> hrequest);
        if ((void *)main_tcb-> hrequest. prev != &main_tcb-> hrequest)
            tcb-> hreq = main_tcb-> hrequest. prev;
        else
            tcb-> hreq = NULL;

        tcb-> reply_to = thread-> queue-> qid;
      }
}


/**********************   WRITE CURRENT LINE TO OUTPUT   *********************/

MODULE write_current_line_to_output (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    fwrite (buffer , 1, strlen (buffer), tcb-> out_log);
}


/***************************   SET END FILE FLAG   ***************************/

MODULE set_end_file_flag (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> end_of_file = TRUE;
}


/***********************   SHOW PROCESSING STATISTICS   **********************/

MODULE show_processing_statistics (THREAD *thread)
{
    sendfmt (&operq, "INFO", "processed %ld lines in %ld seconds",
        lines_processed, time (NULL) - time_started);
}


/***************************   CHECK STACK LEVEL   ***************************/

MODULE check_stack_level (THREAD *thread)
{

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    switch (tcb-> nb_request)
      {
        case 0:
             the_next_event = empty_event;
             break;
        case STACK_SIZE:
             the_next_event = full_event;
             break;
        default:
             if (tcb-> end_of_file)
                 the_next_event = full_event;
             else
                 the_next_event = not_full_event;
             break;
      }
}


/*************************   PARTIAL INITIALISATION   ************************/

MODULE partial_initialisation (THREAD *thread)
{
    HREQ
        *next,
        *hreq;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> in_log)
        file_close (tcb-> in_log);
    if (tcb-> out_log)
        file_close (tcb-> out_log);
    if (tcb-> err_log)
        file_close (tcb-> err_log);
    hreq = tcb-> hrequest.next;
    while ((void *)hreq != (void *)&tcb-> hrequest)
      {
        next = hreq-> next;
        delete_hreq (hreq);
        hreq = next;
      }
    list_reset (&tcb-> hrequest);       /*    Resest request list            */
    tcb-> in_log      = NULL;
    tcb-> out_log     = NULL;
    tcb-> err_log     = NULL;
    tcb-> read_nbr    = 0;
    tcb-> write_nbr   = 0;
    tcb-> nb_request  = 0;
    tcb-> end_of_file = FALSE;
}


/***********************   SET FEEDBACK TO NOT FOUND   ***********************/

MODULE set_feedback_to_not_found (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> hreq-> state = HREQ_STATE_NOT_FOUND;
}


/************************   SET FEEDBACK TO TIMEOUT   ************************/

MODULE set_feedback_to_timeout (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> hreq-> state = HREQ_STATE_TIMEOUT;
}


/***********************   DISPLAY RESULT TO CONSOLE   ***********************/

MODULE display_result_to_console (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (verbose_mode)
        switch (tcb-> hreq-> state)
          {
            case HREQ_STATE_OK:
                coprintf ("line %6ld: %-15s -> %s",
                           tcb-> hreq-> id,
                           tcb-> hreq-> ip_value,
                           tcb-> hreq-> host_name);
                break;
            case HREQ_STATE_TIMEOUT:
            case HREQ_STATE_NOT_FOUND:
                coprintf ("line %6ld: %-15s -> not found",
                           tcb-> hreq-> id,
                           tcb-> hreq-> ip_value);
                break;
            default:
                coprintf ("line %6ld: %-15s -> error",
                           tcb-> hreq-> id,
                           tcb-> hreq-> ip_value);
                break;
          }
}


/**************************   SHUTDOWN APPLICATION   *************************/

MODULE shutdown_application (THREAD *thread)
{
    smt_shutdown ();
}


/***************************   CHECK THREAD TYPE   ***************************/

MODULE check_thread_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = tcb-> thread_type;
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    HREQ
        *next,
        *hreq;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> thread_type == master_event)
      {
        if (tcb-> in_log)
            file_close (tcb-> in_log);
        if (tcb-> out_log)
            file_close (tcb-> out_log);
        if (tcb-> err_log)
            file_close (tcb-> err_log);

        hreq = tcb-> hrequest.next;
        while ((void *)hreq != (void *)&tcb-> hrequest)
          {
            next = hreq-> next;
            delete_hreq (hreq);
            hreq = next;
          }
      }
    the_next_event = terminate_event;
}

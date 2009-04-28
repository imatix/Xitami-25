/*===========================================================================*
 *                                                                           *
 *  smtsock.c -                                                              *
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
    Synopsis:   Waits, reads, writes socket data.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME      SMT_SOCKET      /*  Our public name                  */
#define SINGLE_THREADED TRUE            /*  Single-threaded agent            */
#define WRITE_TIMEOUT   10              /*  Default write timeout            */

typedef struct _SOCKREQ {               /*  Request descriptor               */
    struct _SOCKREQ                     /*                                   */
           *next, *prev;                /*    Doubly-linked list             */
    QID     reply_to;                   /*    Who sent the request event     */
    sock_t  input;                      /*    Socket for input               */
    sock_t  output;                     /*    Socket for output              */
    byte   *buffer;                     /*    Buffer for i/o, or NULL        */
    qbyte   max_size;                   /*    Maximum size of buffer         */
    qbyte   cur_size;                   /*    Current size of buffer         */
    qbyte   min_size;                   /*    Minimum data to process        */
    dbyte   timeout;                    /*    Expiry time in seconds         */
    time_t  expires;                    /*    Expiry time, or 0              */
    qbyte   tag;                        /*    User-defined request tag       */
    Bool    repeat;                     /*    Repeated request?              */
    Bool    huge_block;                 /*    Huge blocks?                   */
} SOCKREQ;


/*- Function prototypes -----------------------------------------------------*/

static SOCKREQ *request_create    (THREAD *thread,
                                   dbyte timeout, sock_t handle, qbyte tag);
static sock_t   request_handle    (SOCKREQ *request);
static void     request_destroy   (SOCKREQ *request);
static void     handle_partial_io (SOCKREQ *request, int bytes_done);
static void     reply_error       (QID *qid, sock_t handle, char *message,
                                   qbyte tag);
static void     reply_normal      (SOCKREQ *request, char *event_name);
static void     purge_old_request (sock_t input, sock_t output);


/*- Global variables used in this source file only --------------------------*/

static Bool
    had_activity = FALSE,
    trace_flag = FALSE;                 /*  Trace socket activity?           */
static NODE
    requests;                           /*  Request list header              */
static fd_set
    read_set,                           /*  Sockets to check for input       */
    write_set,                          /*  Sockets to check for output      */
    error_set;                          /*  Sockets to check for errors      */
static QID
    operq;                              /*  Operator console event queue     */
static SOCKREQ
    *request,                           /*  Pointer to request (in list)     */
    *active_request;                    /*  Request we're processing         */

static byte
    msg_body [LINE_MAX];                /*  Message sent to requestors       */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_write        */
    msg = { LINE_MAX, msg_body };


#include "smtsock.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtsock_init

    Synopsis: Initialises the SMT socket agent.  Returns 0 if initialised
    okay, -1 if there was an error.  The socket agent manages all sockets
    (TCP and UPD) used by an SMT application.  Creates an unnamed thread
    automatically: send events to that thread.  Initialises the sflsock
    socket interface automatically.  Supports these public methods:
    <Table>
    READ      Read a specified amount of input data (use SMT_SOCK_READ).
    WRITE     Write a specified amount of output data (use SMT_SOCK_WRITE).
    READR     Read input data, repeatedly (use SMT_SOCK_READ).
    READH     As for READ, but for blocks > 64k (use SMT_SOCK_READH).
    WRITEH    As for WRITE, but for blocks > 64k (use SMT_SOCK_WRITEH).
    READRH    As for READR, but for blocks > 64k (use SMT_SOCK_READH).
    INPUT     Wait for any input ready on socket (use SMT_SOCK_INPUT).
    INPUTR    Wait for any input, repeatedly (use SMT_SOCK_INPUT).
    OUTPUT    Wait for any output ready on socket (use SMT_SOCK_OUTPUT).
    CONNECT   Make socket connection to host & port (use SMT_SOCK_CONNECT).
    FLUSH     Delete all requests for specified socket (use SMT_SOCK_FLUSH).
    </Table>
    Sends errors to the SMTOPER agent; see doc for reply events.
    ---------------------------------------------------------------------[>]-*/

int
smtsock_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smtsock.i"                 /*  Include dialog interpreter       */

    /*  We give this agent a low priority, so that it will only run after    */
    /*  all other threads.  This is important, since it blocks on select().  */
    agent-> priority = SMT_PRIORITY_LOW;

    /*                      Method name     Event value      Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",      shutdown_event,  SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "READ",          read_event,      0);
    method_declare (agent, "READR",         readr_event,     0);
    method_declare (agent, "READH",         readh_event,     0);
    method_declare (agent, "READRH",        readrh_event,    0);
    method_declare (agent, "WRITE",         write_event,     0);
    method_declare (agent, "WRITEH",        writeh_event,    0);
    method_declare (agent, "INPUT",         input_event,     0);
    method_declare (agent, "INPUTR",        inputr_event,    0);
    method_declare (agent, "OUTPUT",        output_event,    0);
    method_declare (agent, "CONNECT",       connect_event,   0);
    method_declare (agent, "FLUSH",         flush_event,     0);

    /*  Private method used to cycle on select() call                        */
    method_declare (agent, "_TIMEOUT",      timeout_event,   0);

    /*  Ensure that operator console is running, else start it up            */
    if (agent_lookup (SMT_OPERATOR) == NULL)
        smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Initialise the socket interface and register sock_term()             */
    if (sock_init () == 0)
        smt_atexit ((function) sock_term);
    else
      {
        sendfmt (&operq, "ERROR",
                 "smtsock: could not initialise socket interface");
        sendfmt (&operq, "ERROR",
                 "smtsock: %s", connect_errlist [connect_error ()]);
        return (-1);
      }

    ip_nonblock = TRUE;                  /*  Want nonblocking sockets        */

    /*  Create initial, unnamed thread                                       */
    thread_create (AGENT_NAME, "");

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}

/*  ---------------------------------------------------------------------[<]-
    Function: smtsock_trace

    Synopsis: Enables/disables socket tracing: to enable, call with TRUE as
    argument; to disable call with FALSE as argument.  Socket trace data is
    sent to the console.
    ---------------------------------------------------------------------[>]-*/

void smtsock_trace (Bool trace_value)
{
    trace_flag = trace_value;
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    node_reset (&requests);             /*  Initialise requests list         */
    the_next_event = ok_event;
}


/***********************   GET NEXT EVENT FROM QUEUE   ***********************/

MODULE get_next_event_from_queue (THREAD *thread)
{
    AGENT   *agent;                     /*  This agent                       */
    QUEUE   *queue;                     /*  Thread's event queue             */
    EVENT   *event;                     /*  Event information block          */
    METHOD  *method;                    /*  Method information block         */

    /*  Get next event off queue                                             */
    queue = thread-> queue;
    agent = queue-> agent;
    event = event_iterate (queue, NULL);
    if (event)
      {
        method = method_lookup (agent, event-> name);
        if (method == NULL)             /*  Not a method we accept           */
          {
            event_reject (queue, event);
            the_next_event = invalid_event;
          }
        else
          {
            if (thread-> event)         /*  If thread was sitting on an      */
              {                         /*    event, release it              */
                event_destroy (thread-> event);
                thread-> event = NULL;
              }
            /*  Get event off queue; it now belongs to the thread            */
            thread-> event = event_accept (queue, event);
            the_next_event = method-> event_number;
          }
      }
    else
        the_next_event = empty_event;
}


/**************************   CREATE READ REQUEST   **************************/

MODULE create_read_request (THREAD *thread)
{
    dbyte
        timeout,                        /*  Timeout, in seconds, or zero     */
        read_size,                      /*  Size of data buffer, bytes       */
        min_size;                       /*  Minimum amount of data to read   */
    sock_t
        handle;                         /*  Socket handle                    */
    qbyte
        tag;                            /*  User-defined request tag         */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_READ,
               &timeout, &handle, &read_size, &min_size, &tag);

    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: READ min=%d max=%d socket=%ld timeout=%d",
                  min_size, read_size, handle, timeout);

    if (read_size == 0 || handle == 0)
        reply_error (&thread-> event-> sender, handle,
                     "Null read request", tag);
    else
    if ((request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        purge_old_request (handle, 0);
        request-> input    = handle;
        request-> max_size = read_size;
        request-> min_size = min_size? min_size: read_size;
        request-> buffer   = mem_alloc (read_size);
        if (request-> buffer == NULL)
            raise_exception (exception_event);
      }
}


/*  -------------------------------------------------------------------------
 *  request_create
 *
 *  Creates a new request, and initialises it to empty.  If the request
 *  could not be created, sends an SOCK_ERROR event to the caller, and
 *  returns null.  Otherwise returns the address of the created request.
 */

static SOCKREQ *
request_create (THREAD *thread, dbyte timeout, sock_t handle, qbyte tag)
{
    SOCKREQ
        *request;                       /*  Request we create                */

    if ((request = node_create (requests.prev, sizeof (SOCKREQ))) == NULL)
        reply_error (&thread-> event-> sender, handle, "Out of memory", tag);
    else
      {
        /*  Initialise the request with default values                       */
        request-> reply_to   = thread-> event-> sender;
        request-> input      = 0;
        request-> output     = 0;
        request-> buffer     = NULL;
        request-> max_size   = 0;
        request-> cur_size   = 0;
        request-> min_size   = 0;
        request-> tag        = tag;
        request-> repeat     = FALSE;
        request-> huge_block = FALSE;
        request-> timeout    = timeout;

        /*  It's really not correct ANSI C to compute with timevals; this    */
        /*  will just have to do for now.  It may break on weird systems.    */
        request-> expires = timeout? time (NULL) + timeout: 0;
      }
    had_activity = TRUE;
    return (request);
}


/*  -------------------------------------------------------------------------
 *  reply_error
 *
 *  Formats and sends a message containing the socket number and an error
 *  message.
 */

static void
reply_error (QID *qid, sock_t handle, char *message, qbyte tag)
{
    msg_size = exdr_writed (&msg, SMT_SOCK_ERROR, message, handle, tag);
    event_send (
        qid,                            /*  Send to specified queue          */
        NULL,                           /*  No queue for reply               */
        "SOCK_ERROR",                   /*  Name of event to send            */
        msg_body,                       /*  Event body contents              */
        msg_size,                       /*  Event body size                  */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*  -------------------------------------------------------------------------
 *  purge_old_request
 *
 *  Removes any existing requests for the specified input or output handles.
 *  Specify either or both handles, or zero.
 */

static void
purge_old_request (sock_t input, sock_t output)
{
    SOCKREQ
        *request;                       /*  Find request in list             */

    for (request = requests.next;
         request != (SOCKREQ *) &requests;
         request  = request-> next)
      {
        if ((input  && request-> input  == input)
        ||  (output && request-> output == output))
          {
            request = request-> prev;
            request_destroy (request-> next);
          }
      }
}


/*  -------------------------------------------------------------------------
 *  request_destroy
 *
 *  Destroys the specified request.
 */

static void
request_destroy (SOCKREQ *request)
{
    /*  Free dynamically-allocated fields in the request block, as reqd.     */
    mem_free (request-> buffer);
    node_destroy (request);
}


/***********************   CREATE READ REPEAT REQUEST   **********************/

MODULE create_read_repeat_request (THREAD *thread)
{
    create_read_request (thread);
    if (request)
        request-> repeat = TRUE;
}


/************************   CREATE HUGE READ REQUEST   ***********************/

MODULE create_huge_read_request (THREAD *thread)
{
    dbyte
        timeout;                        /*  Timeout, in seconds, or zero     */
    qbyte
        read_size,                      /*  Size of data buffer, bytes       */
        min_size,                       /*  Minimum amount of data to read   */
        tag;                            /*  User-defined request tag         */
    sock_t
        handle;                         /*  Socket handle                    */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_READH,
               &timeout, &handle, &read_size, &min_size, &tag);

    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: READH min=%ld max=%ld socket=%ld timeout=%d",
                  min_size, read_size, handle, timeout);

    if (read_size == 0 || handle == 0)
        reply_error (&thread-> event-> sender, handle,
                     "Null read request", tag);
    else
    if (read_size > UINT_MAX)
        reply_error (&thread-> event-> sender, handle,
                     "Read request too large for memory model", tag);
    else
    if ((request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        purge_old_request (handle, 0);
        request-> input      = handle;
        request-> max_size   = read_size;
        request-> min_size   = min_size? min_size: read_size;
        request-> buffer     = mem_alloc ((size_t) read_size);
        request-> huge_block = TRUE;
        if (request-> buffer == NULL)
            raise_exception (exception_event);
      }
}


/********************   CREATE HUGE READ REPEAT REQUEST   ********************/

MODULE create_huge_read_repeat_request (THREAD *thread)
{
    create_huge_read_request (thread);
    if (request)
        request-> repeat = TRUE;
}


/**************************   CREATE WRITE REQUEST   *************************/

MODULE create_write_request (THREAD *thread)
{
    dbyte
        timeout,                        /*  Timeout, in seconds, or zero     */
        write_size;                     /*  Amount of data to write          */
    sock_t
        handle;                         /*  Socket handle                    */
    byte
        *buffer = NULL;                 /*  Buffer to write                  */
    qbyte
        tag;                            /*  User-defined request tag         */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_WRITE,
               &timeout, &handle, &write_size, &buffer, &tag);

    /*  For write requests we do not want to allow a zero timeout, it makes
        no sense and on some bogus OSes (Solaris) it can cause socket leaks.
     */
    if (timeout == 0)
        timeout = WRITE_TIMEOUT;
        
    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: WRITE size=%d socket=%ld timeout=%d data=%x %x %x %x",
                  write_size, handle, timeout,
                  (byte) buffer [0], (byte) buffer [1],
                  (byte) buffer [2], (byte) buffer [3]);

    if (write_size == 0 || handle == 0)
      {
        mem_free (buffer);
        reply_error (&thread-> event-> sender, handle,
                     "Null write request", tag);
      }
    else
    if (write_size > UINT_MAX)
      {
        mem_free (buffer);
        reply_error (&thread-> event-> sender, handle,
                     "Write request too large for memory model", tag);
      }
    else
    if (buffer == NULL)                 /*  Not enough memory                */
        raise_exception (exception_event);
    else
    if ((request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        request-> output   = handle;
        request-> max_size = write_size;
        request-> min_size = write_size;
        request-> buffer   = buffer;
      }
}


/***********************   CREATE HUGE WRITE REQUEST   ***********************/

MODULE create_huge_write_request (THREAD *thread)
{
    dbyte
        timeout;                        /*  Timeout, in seconds, or zero     */
    qbyte
        write_size,                     /*  Amount of data to write          */
        tag;                            /*  User-defined request tag         */
    sock_t
        handle;                         /*  Socket handle                    */
    byte
        *buffer = NULL;                 /*  Buffer to write                  */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_WRITEH,
               &timeout, &handle, &write_size, &buffer, &tag);

    /*  For write requests we do not want to allow a zero timeout, it makes
        no sense and on some bogus OSes (Solaris) it can cause socket leaks.
     */
    if (timeout == 0)
        timeout = WRITE_TIMEOUT;
        
    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: WRITEH size=%ld socket=%ld timeout=%d data=%x%x%x%x",
                  write_size, handle, timeout,
                  (byte) buffer [0], (byte) buffer [1],
                  (byte) buffer [2], (byte) buffer [3]);

    if (write_size == 0 || handle == 0)
      {
        mem_free (buffer);
        reply_error (&thread-> event-> sender, handle,
                     "Null write request", tag);
      }
    else
    if (buffer == NULL)                 /*  Not enough memory                */
        raise_exception (exception_event);
    else
    if ((request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        request-> output     = handle;
        request-> max_size   = write_size;
        request-> min_size   = write_size;
        request-> buffer     = buffer;
        request-> huge_block = TRUE;
      }
}


/**************************   CREATE INPUT REQUEST   *************************/

MODULE create_input_request (THREAD *thread)
{
    dbyte
        timeout;                        /*  Timeout, in seconds, or zero     */
    sock_t
        handle;                         /*  Socket handle                    */
    qbyte
        tag;                            /*  User-defined request tag         */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_INPUT,
               &timeout, &handle, &tag);

    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: INPUT socket=%ld timeout=%d", handle, timeout);

    if (handle == 0)
        reply_error (&thread-> event-> sender, handle,
                     "Null input request", tag);
    else
    if ((request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        purge_old_request (handle, 0);
        request-> input = handle;
      }
}


/**********************   CREATE INPUT REPEAT REQUEST   **********************/

MODULE create_input_repeat_request (THREAD *thread)
{
    create_input_request (thread);
    if (request)
        request-> repeat = TRUE;
}


/*************************   CREATE OUTPUT REQUEST   *************************/

MODULE create_output_request (THREAD *thread)
{
    dbyte
        timeout;                        /*  Timeout, in seconds, or zero     */
    sock_t
        handle;                         /*  Socket handle                    */
    qbyte
        tag;                            /*  User-defined request tag         */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_OUTPUT,
               &timeout, &handle, &tag);

    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: OUTPUT socket=%ld timeout=%d", handle, timeout);

    if (handle == 0)
        reply_error (&thread-> event-> sender, handle,
                     "Null output request", tag);
    else
    if ((request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        purge_old_request (0, handle);
        request-> output = handle;
      }
}


/*************************   CREATE CONNECT REQUEST   ************************/

MODULE create_connect_request (THREAD *thread)
{
    dbyte
        timeout,                        /*  Timeout, in seconds, or zero     */
        port_nbr;                       /*  Literal port number              */
    char
        *type = NULL,                   /*  Type of connection to make       */
        *host = NULL,                   /*  Host to connect to               */
        *service = NULL;                /*  Service or port number           */
    qbyte
        host_nbr;                       /*  Literal host number              */
    struct sockaddr_in
        host_addr;                      /*  Structure for connection         */
    sock_t
        handle;                         /*  Handle for connection            */
    qbyte
        tag;                            /*  User-defined request tag         */

    /*  Get arguments from message                                           */
    exdr_read (thread-> event-> body, SMT_SOCK_CONNECT,
               &timeout, &type, &host, &service, &port_nbr, &host_nbr, &tag);

    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: CONNECT type=%s to=%s/%s nbr=%lx/%d timeout=%d",
                  type, host, service, host_nbr, port_nbr, timeout);

    /*  Build socket address structure and connect to host.  Either of the   */
    /*  information pairs (host, service) (host_nbr, port_nbr) will be used  */
    /*  by the connect function.                                             */
    build_sockaddr (&host_addr, host_nbr, port_nbr);
    handle = connect_socket (host, service, type, &host_addr, 3, 0);

    /*  The connect call can fail, in which case we return the socket error  */
    /*  message.  If the call succeeds, we need to wait until the socket is  */
    /*  ready for use, since we use non-blocking sockets.  We generate a     */
    /*  write request; when this is true we'll send an ok event plus the     */
    /*  socket handle to the calling program.                                */

    if (handle == INVALID_SOCKET)
        reply_error (&thread-> event-> sender, 0, (char *) sockmsg (), tag);
    else
    if (handle > 0                      /*  Else wait until ready to write   */
    && (request = request_create (thread, timeout, handle, tag)) != NULL)
      {
        purge_old_request (0, handle);
        request-> output = handle;
      }
    mem_free (type);                    /*  Release allocated memory         */
    mem_free (host);
    mem_free (service);
}


/*************************   FLUSH SOCKET REQUESTS   *************************/

MODULE flush_socket_requests (THREAD *thread)
{
    sock_t
        handle;                         /*  Socket handle                    */

    exdr_read (thread-> event-> body, SMT_SOCK_FLUSH, &handle);
    purge_old_request (handle, handle);
}


/***********************   CHECK FOR EXPIRED REQUESTS   **********************/

MODULE check_for_expired_requests (THREAD *thread)
{
    time_t
        time_now;                       /*  Current time                     */

    time_now = time (NULL);
    for (request  = requests.next;
         request != (SOCKREQ *) &requests;
         request  = request-> next)
      {
        /*  If the request timed-out, reply SOCK_TIMEOUT and delete it       */
        if (request-> expires && request-> expires < time_now)
          {
            send_sock_timeout (&request-> reply_to, request-> timeout,
                               request_handle (request),
                               (dbyte) request-> cur_size,
                               request-> buffer, request-> tag);

            request = request-> prev;   /*  We want to continue in list      */
            request_destroy (request-> next);
          }
        else
        /*  If request socket is dead, reply SOCK_CLOSED and delete it       */
        if (!socket_is_alive (request_handle (request)))
          {
            send_sock_closed (&request-> reply_to, request-> timeout,
                              request_handle (request),
                              (dbyte) request-> cur_size,
                              request-> buffer, request-> tag);

            request = request-> prev;   /*  We want to continue in list      */
            request_destroy (request-> next);
          }
      }
    if (requests.next == &requests)
        raise_exception (no_requests_event);
}


/*  -------------------------------------------------------------------------
 *  request_handle
 *
 *  Returns the request handle (input or output, but not both).  Returns 0
 *  if neither is set; this cannot normally happen.
 */

static sock_t
request_handle (SOCKREQ *request)
{
    if (request-> input)
        return (request-> input);
    else
    if (request-> output)
        return (request-> output);
    else
        return (0);
}


/************************   WAIT FOR SOCKET ACTIVITY   ***********************/

MODULE wait_for_socket_activity (THREAD *thread)
{
    struct timeval
#if (defined (__WINDOWS__))             /*  Windows select() never unblocks  */
        timeout = { 0, 200000 };        /*  Timeout for select() = 1/5s      */
#else
        timeout = { 1, 0 };             /*  Timeout for select() = 1s        */
#endif
    sock_t
        top_socket = 0;                 /*  Highest socket number            */
    int
        rc;                             /*  Return code from select()        */

    smt_set_step ("prepare fd_sets");
    memset (&read_set,  0, sizeof (fd_set));
    memset (&write_set, 0, sizeof (fd_set));
    memset (&error_set, 0, sizeof (fd_set));
    for (request  = requests.next;
         request != (SOCKREQ *) &requests;
         request  = request-> next)
      {
        if (request-> input)
          {
            FD_SET ((int) request-> input, &read_set);
            FD_SET ((int) request-> input, &error_set);
            top_socket = max (request-> input, top_socket);
            if (trace_flag && had_activity)
                sendfmt (&operq, "INFO",
                         "smtsock: wait for input on %d", request-> input);
          }
        else
        if (request-> output)
          {
            FD_SET ((int) request-> output, &write_set);
            FD_SET ((int) request-> output, &error_set);
            top_socket = max (request-> output, top_socket);
            if (trace_flag && had_activity)
                sendfmt (&operq, "INFO",
                         "smtsock: wait for output on %d", request-> output);
          }
      }
    smt_set_step ("sock_select");
    rc = sock_select (
        (int) top_socket + 1,           /*  Handles to check                 */
        &read_set,                      /*  Check for input                  */
        &write_set,                     /*  Check for output                 */
        &error_set,                     /*  Check for errors                 */
        &timeout);                      /*  Timeout                          */

    smt_set_step ("after select");
    if (trace_flag && had_activity)
        sendfmt (&operq, "INFO",
                 "smtsock: return code from select() = %d", rc);

    /*  If select failed, send error to console, and terminate               */
    if (rc == SOCKET_ERROR)             /*  Error from socket call           */
      {
        if (sockerrno == EINTR)         /*  Ignore interrupted call          */
            raise_exception (no_activity_event);
        else
        if (sockerrno != EBADF)         /*  Ignore errors on handles         */
          {
            sendfmt (&operq, "ERROR",
                     "smtsock: error on select(): %s", sockmsg ());
            raise_exception (exception_event);
            if (trace_flag)
                sendfmt (&operq, "INFO",
                         "smtsock: error from select() = %d %s",
                          sockerrno, sockmsg ());
          }
      }
    else
    if (rc == 0)
        raise_exception (no_activity_event);

    had_activity = FALSE;
}


/**********************   CHECK FIRST SOCKET ACTIVITY   **********************/

MODULE check_first_socket_activity (THREAD *thread)
{
    request = (SOCKREQ *) requests.next;
    check_next_socket_activity (thread);
}


/***********************   CHECK NEXT SOCKET ACTIVITY   **********************/

MODULE check_next_socket_activity (THREAD *thread)
{
    /*  We want to write any output waiting before handling new input        */
    the_next_event = finished_event;
    while (request != (SOCKREQ *) &requests)
      {
        if (FD_ISSET ((int) request-> output, &write_set))
          {
            had_activity = TRUE;
            the_next_event = (request-> buffer? write_event: output_event);
            if (trace_flag)
                sendfmt (&operq, "INFO",
                         "smtsock: -- output ready on %d", request-> output);
          }
        /*  If any event got set, we can access it as active_request         */
        if (the_next_event != finished_event)
          {
            active_request = request;
            request = request-> next;
            return;
          }
        else
            request = request-> next;
      }
    /*  If finished checking output sockets, check input socket              */
    if (request == (SOCKREQ *) &requests)
        request = (SOCKREQ *) requests.next;
    while (request != (SOCKREQ *) &requests)
      {
        if (FD_ISSET ((int) request-> input,  &read_set))
          {
            had_activity = TRUE;
            the_next_event = (request-> buffer? read_event: input_event);
            if (trace_flag)
                sendfmt (&operq, "INFO",
                         "smtsock: -- input ready on %d", request-> input);
          }
        /*  If any event got set, we can access it as active_request         */
        if (the_next_event != finished_event)
          {
            active_request = request;
            request = request-> next;
            return;
          }
        else
            request = request-> next;
      }
}


/*************************   READ DATA FROM SOCKET   *************************/

MODULE read_data_from_socket (THREAD *thread)
{
    /*  Read as much data as we can from the request's socket, then          */
    /*  update the request appropriately.                                    */
    if (trace_flag)
      {
        sendfmt (&operq, "INFO",
                 "smtsock: reading %d bytes from %ld",
                  active_request-> max_size - active_request-> cur_size,
                  active_request-> input);
      }
    handle_partial_io (
        active_request,
        read_TCP (active_request-> input,
                  active_request-> buffer   + active_request-> cur_size,
        (size_t) (active_request-> max_size - active_request-> cur_size))
    );
}


/*  -------------------------------------------------------------------------
 *  handle_partial_io
 *
 *  Handles the return code from a socket read or write, to update the
 *  request size indicators and set the next event.
 */

static void
handle_partial_io (SOCKREQ *request, int bytes_done)
{
    /*  If we read something, update the request cur_size, and check if      */
    /*  we got everything.  If so, we can signal 'finished'.  Else we loop.  */
    if (bytes_done > 0)
      {
        if (trace_flag)
          {
            byte *ptr = (byte *) request-> buffer + request-> cur_size;
            sendfmt (&operq, "INFO",
                     "smtsock: %02x %02x %02x %02x %02x %02x %02x %02x...",
                      ptr [0], ptr [1], ptr [2], ptr [3],
                      ptr [4], ptr [5], ptr [6], ptr [7]);
          }
        request-> cur_size += bytes_done;
        if (request-> cur_size >= request-> min_size)
            the_next_event = finished_event;
        else
            the_next_event = incomplete_event;
      }

    /*  If the return code was zero, the socket got closed.  Whatever we     */
    /*  got, we'll send back.  Some systems return EPIPE or ECONNRESET.      */
    else
    if (bytes_done == 0 || sockerrno == EPIPE || sockerrno == ECONNRESET)
        the_next_event = closed_event;
    else
    /*  In principle we can't get an EAGAIN, since we waited until the       */
    /*  socket was ready, but you never know.  We'll just try again...       */
    if (sockerrno == EAGAIN || sockerrno == EWOULDBLOCK)
        the_next_event = incomplete_event;

    /*  Anything else, that's an error                                       */
    else
        the_next_event = error_event;
}


/**************************   WRITE DATA TO SOCKET   *************************/

MODULE write_data_to_socket (THREAD *thread)
{
    /*  Write as much data as we can to the request's socket, then           */
    /*  update the request appropriately.                                    */
    if (trace_flag)
        sendfmt (&operq, "INFO",
                 "smtsock: writing %d bytes to %ld",
                  active_request-> max_size - active_request-> cur_size,
                  active_request-> output);

    handle_partial_io (
        active_request,
        write_TCP (active_request-> output,
                   active_request-> buffer   + active_request-> cur_size,
         (size_t) (active_request-> max_size - active_request-> cur_size))
    );
}


/*********************   SIGNAL SOCKET READY FOR INPUT   *********************/

MODULE signal_socket_ready_for_input (THREAD *thread)
{
    reply_normal (active_request, "SOCK_INPUT_OK");
    if (!active_request-> repeat)
        request_destroy (active_request);
}


/*  -------------------------------------------------------------------------
 *  reply_normal
 *
 *  Formats and sends a message containing a socket number only.  Used for
 *  all normal (non-read) replies - after a write or a connect.  Destroys
 *  the specified request.
 */

static void
reply_normal (SOCKREQ *request, char *event_name)
{
    msg_size = exdr_writed (&msg, SMT_SOCK_OK,
                            request_handle (request), request-> tag);
    event_send (
        &request-> reply_to,            /*  Send to specified queue          */
        NULL,                           /*  No queue for reply               */
        event_name,                     /*  Name of event to send            */
        msg_body,                       /*  Event body contents              */
        msg_size,                       /*  Event body size                  */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*********************   SIGNAL SOCKET READY FOR OUTPUT   ********************/

MODULE signal_socket_ready_for_output (THREAD *thread)
{
    reply_normal (active_request, "SOCK_OUTPUT_OK");
    request_destroy (active_request);
}


/**************************   SIGNAL READ COMPLETE   *************************/

MODULE signal_read_complete (THREAD *thread)
{
    if (active_request-> huge_block)
        send_sock_readh_ok (
            &active_request-> reply_to,
            active_request-> timeout,
            request_handle (active_request),
            active_request-> cur_size,
            active_request-> buffer,
            active_request-> tag);
    else
        send_sock_read_ok (
            &active_request-> reply_to,
            active_request-> timeout,
            request_handle (active_request),
            (dbyte) active_request-> cur_size,
            active_request-> buffer,
            active_request-> tag);

    if (active_request-> repeat)
        active_request-> cur_size = 0;
    else
        request_destroy (active_request);
}


/***************************   SIGNAL READ CLOSED   **************************/

MODULE signal_read_closed (THREAD *thread)
{
    /*  We send back a short data block, if any data was read                */
    send_sock_closed (
        &active_request-> reply_to,
        active_request-> timeout,
        request_handle (active_request),
        (dbyte) active_request-> cur_size,
        active_request-> buffer,
        active_request-> tag);

    request_destroy (active_request);
}


/*************************   SIGNAL WRITE COMPLETE   *************************/

MODULE signal_write_complete (THREAD *thread)
{
    if (active_request-> huge_block)
        send_sock_writeh_ok (
            &active_request-> reply_to,
            request_handle (active_request),
            active_request-> tag);
    else
        send_sock_write_ok (
            &active_request-> reply_to,
            request_handle (active_request),
            active_request-> tag);

    request_destroy (active_request);
}


/**************************   SIGNAL WRITE CLOSED   **************************/

MODULE signal_write_closed (THREAD *thread)
{
    reply_normal (active_request, "SOCK_CLOSED");
    request_destroy (active_request);
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    reply_error (&active_request-> reply_to, request_handle (active_request),
                 (char *) sockmsg (), active_request-> tag);
    request_destroy (active_request);
}


/***********************   SEND TIMEOUT EVENT TO SELF   **********************/

MODULE send_timeout_event_to_self (THREAD *thread)
{
    event_send (
        &thread-> queue-> qid,          /*  Send to specified queue          */
        NULL,                           /*  No queue for reply               */
        "_TIMEOUT",                     /*  Name of event to send            */
        NULL, 0,                        /*  No event body                    */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/**************************   DESTROY ALL REQUESTS   *************************/

MODULE destroy_all_requests (THREAD *thread)
{
    while (requests.next != &requests)
        request_destroy (requests.next);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    the_next_event = terminate_event;
}

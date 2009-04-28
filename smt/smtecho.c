/*===========================================================================*
 *                                                                           *
 *  smtecho.c -                                                              *
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
    Synopsis:   Handles the TCP/IP echo protocol on port 7.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   SMT_ECHO           /*  Our public name                  */

typedef struct {                        /*  Thread context block:            */
    event_t thread_type;                /*    Thread type indicator          */
    sock_t  handle;                     /*    Handle for i/o                 */
} TCB;


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    operq,                              /*  Operator console event queue     */
    logq,                               /*  Logging agent event queue        */
    sockq;                              /*  Socket agent event queue         */
static byte
    msg_body [LINE_MAX + 32];           /*  Message sent to socket agent     */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed       */
    msg = {sizeof (msg_body), msg_body};


#include "smtecho.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtecho_init

    Synopsis: Initialises the SMT echo agent.  Returns 0 if initialised
    okay, -1 if there was an error.  The echo agent handles the TCP ECHO
    protocol on port 7.  It logs connections to the file smtecho.log.  It
    sends errors to the SMTOPER agent.  If you set the ip_portbase before
    calling this function, the echo port is shifted by that amount.  A
    typical value for ip_portbase is 5000: the echo agent will then handle
    connections on port 5007.
    ---------------------------------------------------------------------[>]-*/

int
smtecho_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to various threads        */
#   include "smtecho.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event, SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  ok_event,       0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,       0);
    method_declare (agent, "SOCK_READ_OK",   read_ok_event,  0);
    method_declare (agent, "SOCK_WRITE_OK",  write_ok_event, 0);
    method_declare (agent, "SOCK_CLOSED",    closed_event,   0);
    method_declare (agent, "SOCK_ERROR",     error_event,    0);
    method_declare (agent, "SOCK_TIMEOUT",   error_event,    0);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",        master_event,   0);
    method_declare (agent, "_CLIENT",        client_event,   0);

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

    /*  Ensure that logging agent is running, and create new thread          */
    smtlog_init ();
    if ((thread = thread_create (SMT_LOGGING, "")) != NULL)
        logq = thread-> queue-> qid;        /*  Get logging queue id         */
    else
        return (-1);

    /*  Create initial thread to manage master port                          */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
        ((TCB *) thread-> tcb)-> handle      = 0;
      }
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    /*  We don't set the_next_event because we expect an argument event      */
    /*  to supply these.                                                     */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
}


/**************************   OPEN AGENT LOG FILE    *************************/

MODULE open_agent_log_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    sendfmt (&logq, "OPEN", "smtecho.log");
}


/***************************   OPEN MASTER SOCKET   **************************/

MODULE open_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> handle = passive_TCP (SMT_ECHO_PORT, 5);
    if (tcb-> handle == INVALID_SOCKET)
      {
        sendfmt (&operq, "ERROR",
                 "smtecho: could not open ECHO port %d/%s",
                  ip_portbase, SMT_ECHO_PORT);
        sendfmt (&operq, "ERROR",
                 connect_errlist [connect_error ()]);
        raise_exception (fatal_event);
      }
    else
        sendfmt (&logq, "PUT", "I: opened echo port %s", SMT_ECHO_PORT);
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    msg_size = exdr_writed (&msg, SMT_SOCK_INPUT, 0,
                            tcb-> handle, (qbyte) 0);
    event_send (
        &sockq,                         /*  Send to socket agent             */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "INPUT",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/************************   ACCEPT CLIENT CONNECTION   ***********************/

MODULE accept_client_connection (THREAD *thread)
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
            SEND (&child_thread-> queue-> qid, "_CLIENT", "");
            ((TCB *) child_thread-> tcb)-> thread_type = client_event;
            ((TCB *) child_thread-> tcb)-> handle      = slave_socket;
          }
      }
    else
    if (sockerrno != EAGAIN && sockerrno != EWOULDBLOCK)
      {
        sendfmt (&operq, "ERROR",
                 "smtecho: could not accept connection: %s", sockmsg ());
        raise_exception (exception_event);
      }
}


/**********************   READ SOCKET DATA REPEATEDLY   **********************/

MODULE read_socket_data_repeatedly (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  We ask the socket agent to read what it can from the socket, and
     *  to return that to us as a message; from 1 to LINE_MAX bytes.  We
     *  want to work with chunks that will fit into the msg buffer.
     *  Whenever input arrives, we get an event, until the client closes
     *  the socket, there is an error, or we send a FLUSH to smtsock.
     */

    msg_size = exdr_writed (&msg, SMT_SOCK_READ,
        0,                              /*  Timeout for request              */
        tcb-> handle,                   /*  Socket to write to               */
        LINE_MAX,                       /*  Amount of data to read           */
        1,                              /*    but we'll accept 1 byte        */
        (qbyte) 0);                     /*  Request tag                      */

    event_send (
        &sockq,                         /*  Send to socket agent             */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "READR",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/****************************   ECHO SOCKET DATA   ***************************/

MODULE echo_socket_data (THREAD *thread)
{
    /*  As a decent example, we first unpack the message from smtsock,
     *  then reformat it for sending back to the client.  It could be
     *  simpler, since the input and output event bodies are exactly
     *  the same.  But the code is more generally reusable like this.
     */

    word
        timeout,                        /*  Timeout, in seconds, or zero     */
        read_size;                      /*  Amount of data that was read     */
    sock_t
        handle;                         /*  Socket used in read              */
    char
        *read_data = NULL;              /*  Buffer will get read data        */
    qbyte
        tag;                            /*  User-defined request tag         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get arguments from message.  Note that we pass the address of
     *  'read_data', which itself contains a null value. exdr_read() will
     *  allocate a block of memory and set read_data to point to this
     *  block.  We must free the block when we no longer use it, by a
     *  call to mem_free().  We could also use a fixed block, if we're
     *  certain about the max. amount of data coming in.  Then we must
     *  pass the address of a variable _that_points_ to read_data
     *  (not the address of read_data).
     */
    exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
               &timeout, &handle, &read_size, &read_data, &tag);

    msg_size = exdr_writed (&msg, SMT_SOCK_WRITE,
        0,                              /*  Timeout for request              */
        tcb-> handle,                   /*  Socket to write to               */
        read_size,                      /*  Amount of data to write          */
        read_data,                      /*  Address of data block            */
        0);                             /*  Request tag                      */

    event_send (
        &sockq,                         /*  Send to socket agent             */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "WRITE",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    mem_free (read_data);
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    sendfmt (&operq, "ERROR",
             "smtecho: error on socket: %s", thread-> event-> body);
}


/***************************   CHECK SOCKET TYPE   ***************************/

MODULE check_socket_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = tcb-> thread_type;
}


/*************************   CLOSE AGENT LOG FILE    *************************/

MODULE close_agent_log_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    sendfmt (&logq, "CLOSE", "");
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

    the_next_event = terminate_event;
}

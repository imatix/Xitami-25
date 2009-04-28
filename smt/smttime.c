/*===========================================================================*
 *                                                                           *
 *  smttime.c -                                                              *
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
    Synopsis:   Generates one-off or repeated timing events.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME      SMT_TIMER       /*  Our public name                  */
#define SINGLE_THREADED TRUE            /*  Single-threaded agent            */

typedef struct _TIMEREQ {               /*  Request descriptor               */
    struct _TIMEREQ                     /*                                   */
            *next, *prev;               /*    Doubly-linked list             */
    QID     reply_to;                   /*    Who sent the request           */
    qbyte   days;                       /*    Delay in days                  */
    qbyte   csecs;                      /*    Delay in centiseconds          */
    word    cycles;                     /*    How many cycles left           */
    long    exp_date;                   /*    Date and time                  */
    long    exp_time;                   /*      that the request expires     */
    dbyte   body_size;                  /*    Body to return with            */
    byte   *body_data;                  /*      reply event                  */
} TIMEREQ;


/*- Function prototypes -----------------------------------------------------*/

static TIMEREQ *absolute_request_create  (QID *reply_to,
                                          long date, long time,
                                          dbyte body_size, byte *body_data);
static TIMEREQ *relative_request_create  (QID *reply_to,
                                          qbyte days, qbyte csecs, word cycles,
                                          dbyte body_size, byte *body_data);
static void     request_destroy          (TIMEREQ *request);
static void     send_alarm_reply         (TIMEREQ *request);

#if (defined (__WINDOWS__))
VOID CALLBACK handle_timer (HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
#endif

/*- Global variables used in this source file only --------------------------*/

static NODE
    requests;                           /*  Request list header              */


#include "smttime.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/


/*  ---------------------------------------------------------------------[<]-
    Function: smttime_init

    Synopsis: Initialises the SMT timer agent.  Returns 0 if initialised
    okay, -1 if there was an error.  The timer agent provides timing events
    after a certain delay, at a specific time, or at a specific frequency.
    When you initialise the timer agent it creates an unnamed thread
    automatically.  Send events to this thread.  The timer accuracy is
    1/100th of a second, depending on the system capacity and speed.
    Supports these public methods:
    <Table>
    ALARM       Send an alarm after some delay (use SMT_TIME_ALARM).
    WAKEUP      Send an alarm at some time (use SMT_TIME_ALARM).
    CLOCK       Send an alarm at some frequency (use SMT_TIME_CLOCK).
    FLUSH       Cancel all timing events for a client thread.
    </Table>
    Sends errors to the SMTOPER agent; see doc for reply events.
    ---------------------------------------------------------------------[>]-*/

int
smttime_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
#   include "smttime.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event, SMT_PRIORITY_MAX);

    /*  Timer event sent by kernel to the timer agent (this program)         */
    method_declare (agent, "TIMER",          timer_event,    0);

    /*  Private event, used to loop if no system timers are available        */
    method_declare (agent, "_TIMER",         timer_event,    SMT_PRIORITY_LOW);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "ALARM",          alarm_event,    0);
    method_declare (agent, "WAKEUP",         wakeup_event,   0);
    method_declare (agent, "CLOCK",          clock_event,    0);
    method_declare (agent, "FLUSH",          flush_event,    0);

    /*  Create initial, unnamed thread                                       */
    thread_create (AGENT_NAME, "");

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    node_reset (&requests);             /*  Initialise requests list         */
    smt_set_timer (&thread-> queue-> qid);
    the_next_event = ok_event;
}


/**********************   CREATE SINGLE ALARM REQUEST   **********************/

MODULE create_single_alarm_request (THREAD *thread)
{
    qbyte
        days,                           /*  Delay in days                    */
        csecs;                          /*  Delay in centiseconds            */
    dbyte
        body_size;                      /*  Arbitrary body size              */
    byte
        *body_data = NULL;              /*  Arbitrary body contents          */

    exdr_read (thread-> event-> body, SMT_TIME_ALARM,
               &days, &csecs, &body_size, &body_data);
    relative_request_create (&thread-> event-> sender, days, csecs, 1,
                             body_size, body_data);
}


/*  -------------------------------------------------------------------------
 *  relative_request_create
 *
 *  Creates a new request, and initialises it to empty.  If the request
 *  could not be created, sends a TIME_ERROR to the caller, and returns
 *  null.  Otherwise returns the address of the created request.  Sets
 *  the expiry time as specified by the delay.  Attaches the user-defined
 *  body to the request; this is returned with the alarm event.
 */

static TIMEREQ *
relative_request_create (
    QID   *reply_to,                    /*  Who sent this timing request     */
    qbyte  days,                        /*  Days to delay                    */
    qbyte  csecs,                       /*  Csecs to delay                   */
    word   cycles,                      /*  Number of alarm cycles           */
    dbyte  body_size,                   /*  Attachment size                  */
    byte  *body_data)                   /*  Attachment data                  */
{
    TIMEREQ
        *request;                       /*  Request we create                */

    if ((request = absolute_request_create (reply_to, date_now(), time_now(),
                                            body_size, body_data)) != NULL)
      {
        /*  A zero time is treated as the smallest possible unit             */
        if (days == 0 && csecs == 0)
            csecs = 1;

        /*  Fill-in request fields                                           */
        request-> days   = days;
        request-> csecs  = csecs;
        request-> cycles = cycles;

        /*  Set request expiry date and time                                 */
        future_date (&request-> exp_date, &request-> exp_time,
                      request-> days,      request-> csecs);
      }
    return (request);
}


/*  -------------------------------------------------------------------------
 *  absolute_request_create
 *
 *  Creates a new request, and initialises it to empty.  If the request
 *  could not be created, sends a TIME_ERROR to the caller, and returns
 *  null.  Otherwise returns the address of the created request.  Sets
 *  the expiry time as specified by the delay.  Attaches the user-defined
 *  body to the request; this is returned with the alarm event.
 */

static TIMEREQ *
absolute_request_create (QID *reply_to, long date, long time,
                         dbyte body_size, byte *body_data)
{
    TIMEREQ
        *request;                       /*  Request we create                */

    if ((request = node_create (requests.prev, sizeof (TIMEREQ))) == NULL)
        sendfmt (reply_to, "TIME_ERROR", "Out of memory");
    else
      {
        /*  Fill-in request fields                                           */
        request-> reply_to  = *reply_to;
        request-> body_size = body_size;
        request-> body_data = body_data;
        request-> cycles    = 1;
        request-> exp_date  = date;
        request-> exp_time  = time;
      }
    return (request);
}


/**********************   CREATE CYCLED CLOCK REQUEST   **********************/

MODULE create_cycled_clock_request (THREAD *thread)
{
    qbyte
        days,                           /*  Delay in days                    */
        csecs;                          /*  Delay in centiseconds            */
    word
        cycles;                         /*  Number of cycles; 0 = forever    */
    dbyte
        body_size;                      /*  Arbitrary body size              */
    byte
        *body_data = NULL;              /*  Arbitrary body contents          */

    exdr_read (thread-> event-> body, SMT_TIME_CLOCK,
               &days, &csecs, &cycles, &body_size, &body_data);
    relative_request_create (&thread-> event-> sender, days, csecs, cycles,
                             body_size, body_data);
}


/**********************   CREATE SINGLE WAKEUP REQUEST   *********************/

MODULE create_single_wakeup_request (THREAD *thread)
{
    long
        date,
        time;
    dbyte
        body_size;                      /*  Arbitrary body size              */
    byte
        *body_data = NULL;              /*  Arbitrary body contents          */

    exdr_read (thread-> event-> body, SMT_TIME_ALARM,
               &date, &time, &body_size, &body_data);
    absolute_request_create (&thread-> event-> sender, date, time,
                             body_size, body_data);
}


/************************   GENERATE RESPONSE EVENTS   ***********************/

MODULE generate_response_events (THREAD *thread)
{
    static long
        cur_date = 0,                   /*  Check if clock went backwards    */
        cur_time = 0;
    TIMEREQ
        *request;                       /*  Pointer to request in list       */
    long
        sig_date,                       /*  When do we signal                */
        sig_time,                       /*    the next alarm?                */
        delay_days,                     /*  Which is in how many days        */
        delay_csecs;                    /*    and how many centiseconds      */

    /*  Handle a backwards clock adjustment by estimating the difference     */
    /*  and applying this to all time requests.                              */
    smt_set_step ("handle clock adjustment");
    if (date_is_future (cur_date, cur_time))
      {
        date_diff (cur_date,    cur_time,
                   date_now (), time_now (),
                   &delay_days, &delay_csecs);
        for (request  = requests.next;
             request != (TIMEREQ *) &requests;
             request  = request-> next)
          {
            past_date (&request-> exp_date, &request-> exp_time,
                       delay_days, delay_csecs);
          }
      }
    cur_time = time_now ();
    cur_date = date_now ();
    sig_date = 0;                       /*  No alarm requests, yet           */
    sig_time = 0;

    /*  First pass - generate response events and expire old requests        */
    smt_set_step ("expire old requests");
    for (request  = requests.next;
         request != (TIMEREQ *) &requests;
         request  = request-> next)
      {
        if (request-> exp_date  < cur_date
        || (request-> exp_date == cur_date
        &&  request-> exp_time <= cur_time))
          {
            send_alarm_reply (request); /*  Send back an ALARM to caller     */
            if (request-> cycles == 1)  /*  Expire if single-shot            */
              {
                request = request-> prev;
                request_destroy (request-> next);
              }
            /*  Else set next expiry time to closest future point...  under
             *  normal circumstances we add the delay date and time.  If the
             *  delay is very short (too short), or the clock was moved
             *  forwards, this may not be enough.  We then take the current
             *  date and time and add the delay to that.
             */
            else
              {
                future_date (&request-> exp_date, &request-> exp_time,
                              request-> days, request-> csecs);

                if (request-> exp_date <  cur_date
                || (request-> exp_date == cur_date
                &&  request-> exp_time <  cur_time))
                  {
                    request-> exp_date = cur_date;
                    request-> exp_time = cur_time;
                    future_date (&request-> exp_date, &request-> exp_time,
                                  request-> days, request-> csecs);
                  }
                if (request-> cycles > 1)
                    request-> cycles--;
              }
          }
      }
    /*  Second pass - calculate time for next signal                         */
    smt_set_step ("calculate next signal");
    for (request  = requests.next;
         request != (TIMEREQ *) &requests;
         request  = request-> next)
      {
        /*  Keep track of the oldest expiry time, for next timer signal      */
        if (sig_date >  request-> exp_date
        || (sig_date == request-> exp_date
        &&  sig_time >  request-> exp_time)
        ||  sig_date == 0)
          {
            sig_date = request-> exp_date;
            sig_time = request-> exp_time;
          }
      }
    /*  If we had an alarm request, go set it off                            */
    smt_set_step ("set alarm request");
    if (sig_date)
      {
        date_diff (sig_date, sig_time,
                   cur_date, cur_time,
                   &delay_days, &delay_csecs);
        if (delay_days > 24)            /*  24 days are less than 2^31       */
            delay_days = 24;

        /*  Try to set a process alarm (SIGALRM signal) after the desired
         *  delay.  If this fails -- usually because we're on a crippleOS
         *  -- then we substitute a real timer by a slow SMT loop.  This is
         *  okay on crippleOS'es since these usually don't worry too much
         *  if one process hogs the CPU.
         */
        if (!process_alarm (delay_days * 86400000L + delay_csecs * 10))
            SEND (&thread-> queue-> qid, "_TIMER", "");
      }
}

static void
send_alarm_reply (TIMEREQ *request)
{
    byte
        *msg_body;                      /*  Message returned to caller       */
    int
        msg_size;                       /*  Size of formatted msg_body       */

    /*  Calculate size required for message body                             */
    msg_size = exdr_write (NULL, SMT_TIME_REPLY,
                           request-> body_size, request-> body_data);

    /*  Now allocate and format the buffer                                   */
    msg_body = mem_alloc  (msg_size);
    msg_size = exdr_write (msg_body, SMT_TIME_REPLY,
                           request-> body_size, request-> body_data);
    event_send (
        &request-> reply_to,            /*  Send to specified queue          */
        NULL,                           /*  No queue for reply               */
        "TIME_ALARM",                   /*  Name of event to send            */
        msg_body,                       /*  Event body contents              */
        msg_size,                       /*  Event body size                  */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    mem_free (msg_body);                /*  And we can free the buffer       */
}


/*  -------------------------------------------------------------------------
 *  request_destroy
 *
 *  Destroys the specified request.
 */

static void
request_destroy (TIMEREQ *request)
{
    mem_free (request-> body_data);
    node_destroy (request);
}


/***********************   FLUSH REQUESTS FOR CLIENT   ***********************/

MODULE flush_requests_for_client (THREAD *thread)
{
    TIMEREQ
        *request;                       /*  Pointer to request in list       */

    /*  Destroy any requests originally created by the sending thread        */
    for (request  = requests.next;
         request != (TIMEREQ *) &requests;
         request  = request-> next)
      {
        if (memcmp (&request-> reply_to,
                    &thread-> event-> sender, sizeof (QID)) == 0)
          {
            request = request-> prev;
            request_destroy (request-> next);
          }
      }
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

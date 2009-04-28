/*===========================================================================*
 *                                                                           *
 *  smtslot.c -                                                              *
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
    Synopsis:   Simulates a timer wall-switch: manages time slots.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME      SMT_SLOT        /*  Our public name                  */
#define SLOT_TICK       500             /*  Accuracy in centiseconds         */

typedef struct {                        /*  Thread context block:            */
    NODE specs;                         /*    List of slot specifiers        */
    long today;                         /*    'Today' for the time slot      */
    day_range
         range;                         /*    Active minutes in the day      */
    QID  reply_to;                      /*    Thread that sent us last msg   */
} TCB;

typedef struct _SPEC {                  /*  Time slot specification          */
    struct _SPEC                        /*                                   */
         *next, *prev;                  /*    Doubly-linked list             */
    char *times;                        /*    Time specifications            */
} SPEC;



/*- Function prototypes -----------------------------------------------------*/

static void parse_slot_specifier (THREAD *thread, SPEC *spec);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    timeq;                              /*  Timer agent event queue          */

static byte
    msg_body [LINE_MAX];                /*  Message sent to requestors       */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_write        */
    msg = { LINE_MAX, msg_body };


#include "smtslot.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/


/*  ---------------------------------------------------------------------[<]-
    Function: smtslot_init

    Synopsis: Initialises the SMT time slot agent. Returns 0 if initialised
    okay, -1 if there was an error.  The time slot agent manages time slots.
    You create a named thread, then send SPECIFY events to define the various
    time slots for your application.  Then you send an ON or OFF event to
    initialise the timer.  The time slot agent then sends SWITCH_ON and
    SWITCH_OFF events as required.  A slot specification is a string, in the
    format: "name value ...".  The name field is a day name ("mon"-"sun"), a
    date in MD order ("12/31") or a date in YMD order ("95/12/31").  The
    value is a list of times in 24 hour HH:MM[-HH:MM] format ("7:30-12:30
    13:30-17:30 17:35").  A value "off" clears all time slots for that day.
    The time slot accuracy is SLOT_TICK csecs.  Any day that does not have
    specified values is switched 'off'.  Supports these public
    methods:
    <Table>
    SPECIFY     Define a time slot specification.
    RESET       Reset all time slots.
    ON          Initialise timer - application is switched on.
    OFF         Initialise timer - application is switched off.
    FINISH      End time slot thread.
    </Table>
    Sends errors to the SMTOPER agent; see doc for reply events.
    ---------------------------------------------------------------------[>]-*/

int
smtslot_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smtslot.i"                 /*  Include dialog interpreter       */

    /*                      Method name   Event value      Priority          */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",    shutdown_event,  SMT_PRIORITY_MAX);

    /*  Alarm event sent by timer to this agent                              */
    method_declare (agent, "TIME_ALARM",  tick_event,      0);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "SPECIFY",     specify_event,   0);
    method_declare (agent, "RESET",       reset_event,     0);
    method_declare (agent, "ON",          on_event,        0);
    method_declare (agent, "OFF",         off_event,       0);
    method_declare (agent, "FINISH",      finish_event,    0);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    node_reset (&tcb-> specs);          /*  Initialise specs list            */
    tcb-> today = 0;                    /*  No work done for today yet       */

    the_next_event = ok_event;
}


/**************************   RESET ALL TIME SLOTS   *************************/

MODULE reset_all_time_slots (THREAD *thread)
{
    SPEC
        *spec;                          /*  Spec in list                     */

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    while (tcb-> specs.next != &tcb-> specs)
      {
        spec = tcb-> specs.next;
        mem_free (spec-> times);
        node_destroy (spec);
      }
    node_reset (&tcb-> specs);          /*  Initialise specs list            */
}


/*********************   STORE TIME SLOT SPECIFICATION   *********************/

MODULE store_time_slot_specification (THREAD *thread)
{
    char
        *times = NULL;                  /*  Time specification string        */
    SPEC
        *spec;                          /*  Spec we create                   */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get fields from event body; just copy, don't parse them yet          */
    tcb-> reply_to = thread-> event-> sender;
    exdr_read (thread-> event-> body, SMT_SLOT_SPEC, &times);

    if ((spec = node_create (tcb-> specs.prev, sizeof (SPEC))) == NULL)
        sendfmt (&tcb-> reply_to, "SLOT_ERROR", "Out of memory");
    else
        spec-> times = strlwc (times);  /*  Store day and times for slot     */
}


/*********************   REBUILD TIME SLOTS IF NEW DAY   *********************/

MODULE rebuild_time_slots_if_new_day (THREAD *thread)
{
    SPEC
        *spec;                          /*  Spec in list                     */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> today != date_now ())
      {
        tcb-> today = date_now ();
        day_range_empty (tcb-> range);  /*  All slots in day are cleared     */
        for (spec  = tcb-> specs.next;
             spec != (SPEC *) &tcb-> specs;
             spec  = spec-> next)
            parse_slot_specifier (thread, spec);
      }
}


static void
parse_slot_specifier (THREAD *thread, SPEC *spec)
{
    int
        day,                            /*  Specifier is weekday             */
        time_nbr,                       /*  Index into spec_list             */
        time_from,                      /*  Start and end of range           */
        time_to;                        /*    of minutes for specifier       */
    long
        date,                           /*  Converted date value             */
        time;                           /*  Converted time value             */
    Bool
        use_spec;                       /*  Do we want this specifier?       */
    char
        **spec_list,                    /*  Broken-up specifier list         */
        *time_ptr;                      /*  Delimiter in specifier           */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    spec_list = tok_split (spec-> times);
    day = conv_str_day (spec_list [0]);
    if (day != -1)
        use_spec = (day == day_of_week (tcb-> today));
    else
      {
        /*  Try to parse date as YY/MM/DD                                    */
        date = conv_str_date (spec_list [0], 0, DATE_YMD_DELIM, DATE_ORDER_YMD);
        if (date == 0)
          {
            /*  If that fails, try as MM/DD                                  */
            date = conv_str_date
                             (spec_list [0], 0, DATE_MD_DELIM, DATE_ORDER_YMD);
            if (date > 0)               /*  Add in current century/year      */
                date += (tcb-> today % 10000L) * 10000L;
          }
        use_spec = (date == tcb-> today);
      }
    /*  If specification matches today, parse the specifier                  */
    if (use_spec)
      {
        for (time_nbr = 1; spec_list [time_nbr]; time_nbr++)
          {
            /*  We expect either "off" or a time range specification         */
            if (streq (spec_list [time_nbr], "off"))
              {
                day_range_empty (tcb-> range);
                continue;
              }
            /*  Split string at hyphen; if not found, means single minute    */
            time_ptr = strchr (spec_list [time_nbr], '-');
            if (time_ptr)
                *time_ptr++ = '\0';     /*  Split the string into 2 pieces   */
            else                        /*  Or parse the same string twice   */
                time_ptr = spec_list [time_nbr];

            time = conv_str_time (spec_list [time_nbr]);
            if (time <= 0)
                continue;               /*  Invalid or empty time            */
            time_from = time_to_min (time);

            time = conv_str_time (time_ptr);
            if (time <= 0)
                continue;               /*  Invalid or empty time            */
            time_to = time_to_min (time);

            day_slot_set (tcb-> range, time_from, time_to);
          }
      }
    tok_free (spec_list);
}


/**************************   WAIT FOR TIMER TICK   **************************/

MODULE wait_for_timer_tick (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Ask timer to send us an event after 5 seconds                        */
    msg_size = exdr_writed (&msg, SMT_TIME_ALARM, (qbyte) 0,
                           (qbyte) SLOT_TICK, 0, (void *) NULL);
    event_send (
        &timeq,                         /*  Send to timer queue              */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "ALARM",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/***********************   CHECK IF TIME TO SWITCH ON   **********************/

MODULE check_if_time_to_switch_on (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (day_slot_filled (tcb-> range, time_to_min (time_now ())))
        raise_exception (on_event);
}


/**********************   CHECK IF TIME TO SWITCH OFF   **********************/

MODULE check_if_time_to_switch_off (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (!day_slot_filled (tcb-> range, time_to_min (time_now ())))
        raise_exception (off_event);
}


/**************************   SIGNAL SWITCH ON NOW   *************************/

MODULE signal_switch_on_now (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    SEND (&tcb-> reply_to, "SWITCH_ON", "");
}


/*************************   SIGNAL SWITCH OFF NOW   *************************/

MODULE signal_switch_off_now (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    SEND (&tcb-> reply_to, "SWITCH_OFF", "");
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    reset_all_time_slots (thread);
    the_next_event = terminate_event;
}

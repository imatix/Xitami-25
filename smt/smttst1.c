/*===========================================================================*
 *                                                                           *
 *  smttst1.c -                                                              *
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
    Synopsis:   Sets a clock ticking every second.  To see the return
                messages, compile this program with animation.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   "smttst1"          /*  Our public name                  */

typedef struct                          /*  Thread context block:            */
{
    qbyte delay;                        /*    Delay for this thread          */
} TCB;


/*- Function prototypes -----------------------------------------------------*/


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    console,                            /*  Operator console event queue     */
    timer;                              /*  Timer event queue                */

static byte
    msg_body [LINE_MAX];                /*  Message sent to timer agent      */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed       */
    msg = { LINE_MAX, msg_body };


#include "smttst1.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int smttst1_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smttst1.i"                 /*  Include dialog interpreter       */

    /*  Declare all methods here, with corresponding internal events         */
    /*                      Method name  Event value      Priority           */
    method_declare (agent, "SHUTDOWN",   shutdown_event,  SMT_PRIORITY_MAX);
    method_declare (agent, "TIME_ALARM", alarm_event,     0);
    method_declare (agent, "TIME_ERROR", error_event,     0);

    /*  Create initial thread - all threads are unnamed                      */
    thread_create (AGENT_NAME, "");

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        console = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer is running, else start it up                       */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timer = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = ok_event;
}


/***************************   SET CLOCK TICKING   ***************************/

MODULE set_clock_ticking (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Request clock messages with 1 second delay                           */
    tcb-> delay = 100;                  /*  Measured in centiseconds         */
    msg_size = exdr_writed (&msg, SMT_TIME_CLOCK,
                           (qbyte) 0, tcb-> delay, (word) 0, (word) 5, "TOKEN");
    event_send (
        &timer,                         /*  Send to specified queue          */
        &thread-> queue-> qid,          /*  No queue for reply               */
        "CLOCK",                        /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = terminate_event;
}

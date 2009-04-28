/*===========================================================================*
 *                                                                           *
 *  smtlog.c -                                                               *
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
    Synopsis:   Writes data to log files.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME   SMT_LOGGING        /*  Our public name                  */
#define LOG_LINEMAX  4096

typedef struct                          /*  Thread context block:            */
{
    int  handle;                        /*    Handle for i/o                 */
    Bool timestamp;                     /*    By default, we timestamp       */
} TCB;


/*- Function prototypes -----------------------------------------------------*/

static char *logfile_name (THREAD *thread);
static void  open_logfile (THREAD *thread, char mode);
static char *time_str     (void);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    console;                            /*  Operator console event queue     */

#include "smtlog.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT    ********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtlog_init

    Synopsis: Initialises the SMT logging agent.  Returns 0 if initialised
    okay, -1 if there was an error.  The logging agent writes data to log
    files.  Create an unnamed thread for each log file you want to manage,
    then send events to that thread.  Supports these public methods:
    <Table>
    CYCLE       Cycle log file if it already exists.
    OPEN        Start a new logfile as specified by event body.
    APPEND      Append to an existing logfile as specified by event body.
    PUT         Write line to logile, prefixed by date and time.
    PLAIN       Use plain logfile output (no timestamp).
    STAMP       Put timestamp at start of each logged line.
    CLOSE       Close logfile and destroy thread.
    </Table>
    Sends errors to the SMTOPER agent; does not send reply events.
    ---------------------------------------------------------------------[>]-*/

int
smtlog_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smtlog.i"                  /*  Include dialog interpreter       */

    /*                      Method name   Event value     Priority           */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",    shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "CYCLE",       cycle_event,    0);
    method_declare (agent, "OPEN",        open_event,     0);
    method_declare (agent, "APPEND",      append_event,   0);
    method_declare (agent, "PUT",         put_event,      0);
    method_declare (agent, "PLAIN",       plain_event,    0);
    method_declare (agent, "STAMP",       stamp_event,    0);
    method_declare (agent, "CLOSE",       close_event,    0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        console = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> handle    = 0;                /*  File is not open                 */
    tcb-> timestamp = TRUE;             /*  By default, we timestamp         */
    the_next_event = ok_event;
}


/************************   CYCLE LOGFILE IF EXISTS   ************************/

MODULE cycle_logfile_if_exists (THREAD *thread)
{
    char
        *name;

    if ((name = logfile_name (thread)) != NULL)
        file_cycle (name, CYCLE_ALWAYS);
}

static char *
logfile_name (THREAD *thread)
{
    char
        *name;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    /*  Event body or thread name supplies name for the log file             */
    if (thread-> event-> body && strused (thread-> event-> body))
        name = (char *) thread-> event-> body;
    else
        name = thread-> name;

    if (streq (name, "") || streq (name, "NULL"))
        return (NULL);
    else
        return (name);
}


/**************************   OPEN THREAD LOGFILE   **************************/

MODULE open_thread_logfile (THREAD *thread)
{
    open_logfile (thread, 'w');
}

static void
open_logfile (THREAD *thread, char mode)
{
    char
        *name;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if ((name = logfile_name (thread)) == NULL)
        tcb-> handle = 0;
    else
      {
        tcb-> handle = lazy_open_text (name,
                       mode == 'w'? O_WRONLY | O_CREAT | O_TRUNC:
                       mode == 'a'? O_WRONLY | O_CREAT | O_APPEND:
                       /*  else  */ O_WRONLY | O_CREAT);
        if (io_completed)
            if (tcb-> handle < 0)       /*  If the open failed, send error   */
              {                         /*    to console, and terminate      */
                sendfmt (&console, "ERROR", "Could not open %s", name);
                senderr (&console);
                raise_exception (exception_event);
              }
      }
}


/*************************   APPEND THREAD LOGFILE   *************************/

MODULE append_thread_logfile (THREAD *thread)
{
    open_logfile (thread, 'a');
}


/************************   LOG FILE OUTPUT IS PLAIN   ***********************/

MODULE log_file_output_is_plain (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> timestamp = FALSE;            /*  No timestamp in data             */
}


/************************   LOG FILE OUTPUT IS TIMED   ***********************/

MODULE log_file_output_is_timed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> timestamp = TRUE;             /*  Add timestamp to data            */
}


/*************************   WRITE TEXT TO LOGFILE   *************************/

MODULE write_text_to_logfile (THREAD *thread)
{
    static char
        formatted [LOG_LINEMAX + 1];    /*  Formatted string                 */
    word
        size,                           /*  Size of event body               */
        source;                         /*  Copy text from event body        */
    int
        fmtsize;                        /*   into the formatted string       */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> timestamp)
      {                                 /*  Start with date and time         */
        strcpy (formatted, time_str ());
        strcat (formatted, ": ");       /*  Add a colon and a space          */
        fmtsize = strlen (formatted);   /*    and add event body text        */
      }
    else
        fmtsize = 0;                    /*  No date/time stamp               */

    size = thread-> event-> body_size;
    if (thread-> event-> body [size - 1] == '\0')
        size--;

    for (source = 0; source < size; source++)
      {
        formatted [fmtsize++] = thread-> event-> body [source];
        if (fmtsize == LOG_LINEMAX)
            break;
      }
    formatted [fmtsize++] = '\n';       /*  Add a newline                    */

    /*  Write to the log file, but do not try to signal errors - if we       */
    /*  send a message to the console now, we could create an infinite       */
    /*  loop... (the console may send it right back to us, see?)             */

    if (tcb-> handle)
        lazy_write (tcb-> handle, formatted, fmtsize);
}


/*  -------------------------------------------------------------------------
 *  time_str
 *
 *  Returns the current date and time formatted as: "yy/mm/dd hh:mm:ss".
 *  The formatted time is in a static string that each call overwrites.
 */

static char *
time_str (void)
{
    static char
        formatted_time [18];
    time_t
        time_secs;
    struct tm
        *time_struct;

    time_secs   = time (NULL);
    time_struct = safe_localtime (&time_secs);

    sprintf (formatted_time, "%2d/%02d/%02d %2d:%02d:%02d",
                              time_struct-> tm_year % 100,
                              time_struct-> tm_mon + 1,
                              time_struct-> tm_mday,
                              time_struct-> tm_hour,
                              time_struct-> tm_min,
                              time_struct-> tm_sec);
    return (formatted_time);
}


/**************************   CLOSE THREAD LOGFILE   *************************/

MODULE close_thread_logfile (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)                   /*  Close log file, if opened        */
        lazy_close (tcb-> handle);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    the_next_event = terminate_event;
}

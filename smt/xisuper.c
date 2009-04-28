/*===========================================================================*
 *                                                                           *
 *  xisuper.c -                                                              *
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
    Synopsis:   Manages temporary and log files.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMTHTTPL prototypes & globals    */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME       "xisuper"      /*  Our public name                  */
#define SINGLE_THREADED  TRUE           /*  Single-threaded agent            */
#define XISUPER_INTERVAL INTERVAL_HOUR  /*  Activate once per hour           */

local cleanup_directory (char *directory, char *mask, int min_age);


/*- Global variables used in this source file only --------------------------*/

static QID
    operq,                              /*  Operator console event queue     */
    timeq;                              /*  Timer event queue                */

static long
    busy_interval;                      /*  How long have we been waiting?   */
    
#include "xisuper.d"                    /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT    ********************/

/*  ---------------------------------------------------------------------[<]-
    Function: xisuper_init

    Synopsis: Initialises the Xitami supervisor agent.  Returns 0 if
    initialised okay, -1 if there was an error.
    ---------------------------------------------------------------------[>]-*/

int
xisuper_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "xisuper.i"                 /*  Include dialog interpreter       */

    /*                      Method name    Event value    Priority           */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",     shutdown_event, SMT_PRIORITY_MAX);

    /*  Alarm event sent by timer to this agent                              */
    method_declare (agent, "TIME_ALARM",   ok_event,       0);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create single master thread                                          */
    thread_create (AGENT_NAME, "main");

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    busy_interval  = 0;
    the_next_event = ok_event;
}


/************************   SLEEP FOR AN HOUR OR SO   ************************/

MODULE sleep_for_an_hour_or_so (THREAD *thread)
{
    send_alarm (&timeq, 0, XISUPER_INTERVAL, 0, 0);
}


/***********************   CHECK WHETHER XITAMI BUSY   ***********************/

MODULE check_whether_xitami_busy (THREAD *thread)
{
    if (cur_connects > 0)
      {
        the_next_event = busy_event;
        busy_interval += XISUPER_INTERVAL;
      }
    else
      {
        the_next_event = not_busy_event;
        busy_interval = 0;
      }
}


/*************************   CHECK WHETHER OVERDUE   *************************/

MODULE check_whether_overdue (THREAD *thread)
{
    if (busy_interval > INTERVAL_DAY)
      {
        raise_exception (not_busy_event);
        busy_interval = 0;
      }
}


/***************************   CLEAN UP LOG FILES   **************************/

MODULE clean_up_log_files (THREAD *thread)
{
    SYMBOL
        *symbol;
        
    /*  We get the list of log file directories (potentially a different one
     *  for each virtual host) from the http_dirs symbol table.  We delete
     *  log files older than two weeks.
     */
    for (symbol = http_dirs-> symbols; symbol; symbol = symbol-> next)
        cleanup_directory (symbol-> name, "*.log", 14);
}

static void
cleanup_directory (char *directory, char *mask, int min_age)
{
    DIRST
        dir;
    time_t
        cut_off_point;
    char
        *full_name;
    int
        files_deleted = 0;

    /*  Calculate cut-off point in seconds, as a number of days before NOW   */
    cut_off_point = time (NULL) - min_age * 86400L;
    if (open_dir (&dir, directory)) do
      {
        if ((dir.file_attrs & ATTR_HIDDEN) == 0
        &&  (dir.file_attrs & ATTR_SUBDIR) == 0)
          {
            if (file_matches (dir.file_name, mask)
            &&  dir.file_time < cut_off_point)
              {
                full_name = xstrcpy (NULL, directory, "/", dir.file_name, NULL);
                file_delete (full_name);    
                files_deleted++;
                mem_free (full_name);
              }
          }
      }
    while (read_dir (&dir));
    close_dir (&dir);
    if (files_deleted)
        sendfmt (&operq, "INFO", "%d files deleted in directory '%s'",
                                  files_deleted, directory);
}


/************************   CLEAN UP TEMPORARY FILES   ***********************/

MODULE clean_up_temporary_files (THREAD *thread)
{
    SYMBOL
        *symbol;
        
    /*  We get the list of temp file directories (potentially a different one
     *  for each virtual host) from the http_dirs symbol table.  We delete
     *  temporary files older than one day.
     */
    for (symbol = http_dirs-> symbols; symbol; symbol = symbol-> next)
        cleanup_directory (symbol-> name, "pipe*", 1);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    the_next_event = terminate_event;
}


/*===========================================================================*
 *                                                                           *
 *  xixlog.c -                                                               *
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
#include "smtrdnsl.h"                   /*  Reverse-DNS functions            */
#include "xixlog.h"                     /*  Xixlog prototypes & definitions  */


/*  -------------------------------------------------------------------------
    Log file formats are defined as a string:

    CLF        NCSA/httpd common logging format (basic)
    CLFX       NCSA/httpd common logging format (extended)
    MS         Microsoft standard format
    LML        Xitami logging markup language
    XLML       Xitami extended logging markup language
    string     User-defined string, containing any of:
                $(client)   - client address, as translated string
                $(ipcli)    - client address, as dotted number
                $(ipsrv)    - server address, as dotted number
                $(request)  - request line (HTTP only)
                $(url)      - requested resource (HTTP only)
                $(query)    - query string, if any (HTTP only)
                $(method)   - HTTP method or FTP command
                $(status)   - response code, 3 digits
                $(recd)     - request size, in bytes
                $(sent)     - response size, in bytes
                $(time)     - request duration, in msecs
                $(stime)    - request duration, in seconds (n.nnn)
                $(file)     - filename to which request was translated
                $(agent)    - HTTP 'User-Agent' field (browser name)
                $(referer)  - HTTP 'Referer' field
                $(from)     - HTTP 'From' field
                $(user)     - user name, if any, else -
                $(service)  - name of service (HTTP, FTP)
                $(vhost)    - virtual host name, if any, else -
                $(datetime) - date/time in NCSA format
                $(yy)       - year as two digits
                $(year)     - year as four digits
                $(mon)      - month
                $(day)      - day
                $(hh)       - hour, using 24-hour clock
                $(mm)       - minutes
                $(ss)       - seconds
                $(XXX)      - environment variable XXX (uppercase)
                Anything else is output as-is

    Logging formats:
    NCS common logging format, basic:
    client - user [date] "request" status size

    NCS common logging format, extended:
    client - user [date] "request" status size "referer" "user-agent"

    Microsoft standard format:
    client, user, MM/DD/YY, HH:MM:SS, service, "Xitami", server ip,
    time (secs), bytes recd, bytes sent, status, 0, method, filename

    Log file names are generated when created: supplied name is timestamped.
    If file to create already exists, cycles file using specified method, if
    cycle condition is time-based.  If cycle condition is size-based, cycles
    if the file is large enough.

    Cycling conditions:
        MANUAL  - Manually only
        STARTUP - When web server starts
        HOURLY  - Hourly, at x minutes past the hour
        DAILY   - Daily, at hh:mm
        WEEKLY  - Weekly, at day-of-week, hh:mm
        MONTHLY - Monthly, at day-of-month, hh:mm
        SIZE    - When log file exceeds n kbytes
        LINES   - When log file exceeds n lines

    Cycling methods:
        RENAME  - Rename to path/filename where filename is timestamped
                  Any existing file with same name is overwritten
        DELETE  - Delete old file (no copies left)
        MOVE    - Move to path (not timestamped)
        CONCAT  - Concat to path/filename where filename can be timestamped
        PROCESS - Process using timestamped command, %f is log filename

    Timestamping:
        %y        day of year, 001-366
        %yy       year 2 digits, 00-99
        %yyyy     year 4 digits, 0100-9999
        %mm       month, 01-12
        %mmm      month, Jan
        %mmmm     month, January
        %MMM      month, JAN
        %MMMM     month, JANUARY
        %dd       day, 01-31
        %ddd      day of week, Sun
        %dddd     day of week, Sunday
        %DDD      day of week, SUN
        %DDDD     day of week, SUNDAY
        %w        day of week, 1-7 (1=Sunday)
        %ww       week of year, 01-53
        %q        year quarter, 1-4
        %h        hour, 00-23
        %m        minute, 00-59
        %s        second, 00-59
        %c        centisecond, 00-99
        %%        literal character %
    -------------------------------------------------------------------------*/


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME       XIXLOG_AGENT   /*  Our public name                  */
#define XIXLOG_INTERVAL  INTERVAL_MIN   /*  Check log files once per minute  */

#define CYCLE_STARTUP    0              /*  Encoded cycle_when values        */
#define CYCLE_HOURLY     1
#define CYCLE_DAILY      2
#define CYCLE_WEEKLY     3
#define CYCLE_MONTHLY    4
#define CYCLE_MANUAL     5
#define CYCLE_SIZE       6
#define CYCLE_LINES      7

#define CYCLE_RENAME     0              /*  Encoded cycle_how values         */
#define CYCLE_DELETE     1
#define CYCLE_MOVE       2
#define CYCLE_CONCAT     3
#define CYCLE_PROCESS    4

typedef struct                          /*  Thread context block:            */
{
    LOGSTATS stats;                     /*    Log file statistics            */
                                        /*    Must be at start of TCB for    */
                                        /*      xiadmin.c                    */
    struct_xixlog_open                  /*                                   */
           *open;                       /*    Logfile OPEN arguments         */
    struct_xixlog_log                   /*                                   */
           *log;                        /*    Logfile LOG arguments          */
    int     handle;                     /*    Handle for i/o to logfile      */
    char   *filename;                   /*    Full log-file filename         */
    char   *log_format;                 /*    Log format string used         */
    char   *log_header;                 /*    Log file header                */
    char   *client_host;                /*    Translated client hostname     */
    Bool    uses_rdns;                  /*    Do we need rdns lookups?       */
    int     cycle_when;                 /*    Decoded cycle_when             */
    int     cycle_how;                  /*    Decoded cycle_how              */
    long    cycle_date;                 /*    Date and time when log file    */
    long    cycle_time;                 /*      should be cycled again       */
    qbyte   file_limit;                 /*    Max. log file size             */
    PROCESS process_id;                 /*    If we use subprocesses         */
    SYMTAB *symtab;                     /*    Used for symbol substitution   */
    QUEUE  *queue;                      /*    Separate event queue           */
} TCB;


/*- Function prototypes -----------------------------------------------------*/

static void  open_logfile   (THREAD *thread, char mode);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread context block     */
static QID
    operq,                              /*  Operator console event queue     */
    timeq,                              /*  Timer event queue                */
    rdnsq;                              /*  RDNS agent queue                 */
static AGENT
    *this_agent;                        /*  Pointer to this agent            */

#include "xixlog.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT    ********************/

/*  ---------------------------------------------------------------------[<]-
    Function: xixlog_init

    Synopsis: Initialises the Xitami extended logging agent.  Returns 0 if
    initialised okay, -1 if there was an error.  The logging agent writes
    data to log files.  Create an named thread for each log file you want to
    manage, then send events to that thread.  Supports these methods:
    <Table>
    OPEN    Start a new logfile as specified by event body.
    LOG     Write normal log file line
    PUT     Write plain log file line
    CYCLE   Cycle log file if it already exists
    CLEAR   Clear (empty) log file and continue
    CLOSE   Close logfile and prepare for new open event
    </Table>
    Sends errors to the SMTOPER agent; does not send reply events.
    ---------------------------------------------------------------------[>]-*/

int
xixlog_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "xixlog.i"                  /*  Include dialog interpreter       */

    /*                      Method name    Event value    Priority           */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",     shutdown_event, SMT_PRIORITY_MAX);

    /*  Alarm event sent by timer to this agent                              */
    method_declare (agent, "TIME_ALARM",   timer_event,        0);

    /*  Reply events from reverse DNS agent                                  */
    method_declare (agent, "HOST_NAME",    rdns_host_event,    0);
    method_declare (agent, "HOST_IP",      rdns_error_event,   0);
    method_declare (agent, "HOST_ERROR",   rdns_error_event,   0);
    method_declare (agent, "HOST_END",     rdns_end_event,     0);
    method_declare (agent, "HOST_TIMEOUT", rdns_timeout_event, 0);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "SET_RDNS",     set_rdns_event,     0);
    method_declare (agent, "OPEN",         open_event,         0);
    method_declare (agent, "LOG",          log_event,          0);
    method_declare (agent, "PUT",          put_event,          0);
    method_declare (agent, "CYCLE",        cycle_event,        0);
    method_declare (agent, "CLEAR",        clear_event,        0);
    method_declare (agent, "CLOSE",        close_event,        0);

    this_agent = agent;

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

    /*  Ensure that RDNS agent is running, else start it up                  */
    smtrdns_init ();
    if ((thread = thread_lookup (SMT_RDNS, "")) != NULL)
        rdnsq = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> open        = NULL;           /*  No open parameters allocated     */
    tcb-> log         = NULL;           /*  No log parameters allocated      */
    tcb-> client_host = NULL;           /*  No translated client hostname    */
    tcb-> handle      = 0;              /*  File is not open                 */
    tcb-> filename    = NULL;           /*  And no filename is specified     */
    tcb-> log_header  = NULL;           /*  And no log header so far         */
    tcb-> symtab      = env2symb ();    /*  Start with full environment      */

    the_next_event = ok_event;
}


/************************   INITIALISE RDNS LIBRARY   ************************/

MODULE initialise_rdns_library (THREAD *thread)
{
    struct_xixlog_set_rdns
        *set;                           /*  set RDNS message                 */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_xixlog_set_rdns (thread-> event-> body, &set);

    server_list.ns_addr [0].sin_addr.s_addr = inet_addr (set-> primary);
    server_list.ns_addr [0].sin_port = htons (DNS_PORT);
    server_list.recursive_accept [0] = set-> recursive;

    server_list.ns_addr [1].sin_addr.s_addr = inet_addr (set-> secondary);
    server_list.ns_addr [1].sin_port = htons (DNS_PORT);
    server_list.recursive_accept [1] = set-> recursive;
    server_list.ns_count = 2;
    dns_debug_mode = set-> debug;

    free_xixlog_set_rdns (&set);
}


/***************************   CREATE EVENT QUEUE   **************************/

MODULE create_event_queue (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> queue = queue_create (NULL, 100);
}


/***************************   FLUSH EVENT QUEUE   ***************************/

MODULE flush_event_queue (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    queue_flush (tcb-> queue);
}


/**************************   DESTROY EVENT QUEUE   **************************/

MODULE destroy_event_queue (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    queue_destroy (tcb-> queue);
}


/*************************   GET LOGFILE PARAMETERS   ************************/

MODULE get_logfile_parameters (THREAD *thread)
{
    static LOOKUP
        lookup_when [] = {
            { XI_CYCLE_STARTUP, CYCLE_STARTUP },
            { XI_CYCLE_HOURLY,  CYCLE_HOURLY  },
            { XI_CYCLE_DAILY,   CYCLE_DAILY   },
            { XI_CYCLE_WEEKLY,  CYCLE_WEEKLY  },
            { XI_CYCLE_MONTHLY, CYCLE_MONTHLY },
            { XI_CYCLE_MANUAL,  CYCLE_MANUAL  },
            { XI_CYCLE_SIZE,    CYCLE_SIZE    },
            { XI_CYCLE_LINES,   CYCLE_LINES   },
            { "0",              CYCLE_STARTUP },
            { "1",              CYCLE_HOURLY  },
            { "2",              CYCLE_DAILY   },
            { "3",              CYCLE_WEEKLY  },
            { "4",              CYCLE_MONTHLY },
            { "5",              CYCLE_MANUAL  },
            { "6",              CYCLE_SIZE    },
            { "7",              CYCLE_LINES   },
            { NULL,             -1            }
        },
        lookup_how [] = {
            { XI_CYCLE_RENAME,  CYCLE_RENAME  },
            { XI_CYCLE_DELETE,  CYCLE_DELETE  },
            { XI_CYCLE_MOVE,    CYCLE_MOVE    },
            { XI_CYCLE_CONCAT,  CYCLE_CONCAT  },
            { XI_CYCLE_PROCESS, CYCLE_PROCESS },
            { "0",              CYCLE_RENAME  },
            { "1",              CYCLE_DELETE  },
            { "2",              CYCLE_MOVE    },
            { "3",              CYCLE_CONCAT  },
            { "4",              CYCLE_PROCESS },
            { NULL,             -1            }
        };
    char
        *format,                        /*  Refer to fields in open message  */
        *when,
        *how;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  We free the xixlog_open structure only when we're done with it       */
    if (tcb-> open)
        free_xixlog_open (&tcb-> open);

    /*  Load log file parameters into open block                             */
    get_xixlog_open (thread-> event-> body, &tcb-> open);

    /*  Use some short names; we reference these a lot                       */
    format = tcb-> open-> log_format;
    when   = tcb-> open-> cycle_when;
    how    = tcb-> open-> cycle_how;

    /*  Get actual log format to use                                         */
    tcb-> log_format = format;
    if (lexcmp (format, "CLF") == 0)
        tcb-> log_format = LOG_FORMAT_CLF;
    else
    if (lexcmp (format, "CLFX") == 0)
        tcb-> log_format = LOG_FORMAT_CLFX;
    else
    /*  Compatability with 2.4d3 and earlier                                 */
    if (lexcmp (format, "XCLF") == 0)
        tcb-> log_format = LOG_FORMAT_CLFX;
    else
    if (lexcmp (format, "MS") == 0)
        tcb-> log_format = LOG_FORMAT_MS;
    else
    if (lexcmp (format, "LML") == 0)
        tcb-> log_format = LOG_FORMAT_LML;
    else
    if (lexcmp (format, "XLML") == 0)
        tcb-> log_format = LOG_FORMAT_XLML;

    /*  Copy other fields                                                    */
    mem_strfree (&tcb-> log_header);
    tcb-> log_header = mem_strdup (tcb-> open-> log_header);

    /*  Parse cycle_when argument, which maps over the standard options in
     *  Xitami, and which can be numeric as well as a string in up/low case.
     */
    tcb-> cycle_when = strlookup (lookup_when, strlwc (when));
    if (tcb-> cycle_when == -1)
      {
        sendfmt (&operq, "ERROR", "Invalid cycle condition: %s", when);
        raise_exception (exception_event);
      }
    tcb-> cycle_how = strlookup (lookup_how, strlwc (how));
    if (tcb-> cycle_how == -1)
      {
        sendfmt (&operq, "ERROR", "Invalid cycle method: %s", how);
        raise_exception (exception_event);
      }

    /*  Check if thread requires reverse-DNS translation                     */
    if (strstr (tcb-> log_format, "$(client)"))
        tcb-> uses_rdns = tcb-> open-> translate;
    else
        tcb-> uses_rdns = FALSE;
}


/***************************   BUILD LOG FILENAME   **************************/

MODULE build_log_filename (THREAD *thread)
{
    char
        *formatted;                     /*  Formatted file name              */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Build a filename as specified from the path and file pattern         */
    if (strnull (tcb-> open-> log_path)
    || file_is_directory (tcb-> open-> log_path))
      {
        formatted = timestamp_string (NULL, tcb-> open-> log_file);
        mem_strfree (&tcb-> filename);
        tcb-> filename = mem_strdup (
            file_where ('s', tcb-> open-> log_path, formatted, NULL));
        mem_free (formatted);
        ASSERT (tcb-> filename);
      }
    else
      {
        sendfmt (&operq, "ERROR", "Log path '%s' is not accessible",
                                   tcb-> open-> log_path);
        raise_exception (exception_event);
      }
}


/***********************   CHECK IF CYCLE BEFORE OPEN   **********************/

MODULE check_if_cycle_before_open (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  If the log file already exists when we start we cycle it if
     *  cycling is manual, or size-based and the file is too large.
     */
    if (file_exists (tcb-> filename))
      {
        if (tcb-> cycle_when == CYCLE_SIZE)
          {
            if (get_file_size (tcb-> filename) / 1024
            > atol (tcb-> open-> cycle_size))
                raise_exception (cycle_now_event);
          }
        else
        if (tcb-> cycle_when == CYCLE_LINES)
          {
            if (file_lines (tcb-> filename)
            > atol (tcb-> open-> cycle_lines))
                raise_exception (cycle_now_event);
          }
        else
        if (tcb-> cycle_when == CYCLE_STARTUP)
            raise_exception (cycle_now_event);
      }
}


/************************   RECALCULATE CYCLE TIMER   ************************/

MODULE recalculate_cycle_timer (THREAD *thread)
{
    long
        arg_time,                       /*  Log file parameters              */
        arg_day,                        /*    for timing-based cycling       */
        cycle_time,                     /*  Calculated time and date         */
        cycle_date,                     /*    for next cycle operation       */
        cycle_days,                     /*  Julian date for next cycle       */
        cycle_hh,                       /*  Hour for next cycle              */
        cycle_mm,                       /*  Minute for next cycle            */
        cycle_year,                     /*  Year for next cycle              */
        cycle_month,                    /*  Month for next cycle             */
        cycle_day;                      /*  Day for next cycle               */
    Bool
        want_alarm = TRUE;              /*  Do we use timer alarms?          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Calculate the time for the next cycling operation, if cycle_when is
     *  time-based.
     */
    arg_time = conv_str_time (tcb-> open-> cycle_time);
    arg_day  = atol          (tcb-> open-> cycle_date);

    /*  Start with current time as base point                                */
    cycle_date = date_now ();
    cycle_time = time_now ();
    cycle_days = date_to_days (cycle_date);
    cycle_hh   = GET_HOUR     (cycle_time);
    cycle_mm   = GET_MINUTE   (cycle_time);

    switch (tcb-> cycle_when)
      {
        case CYCLE_HOURLY:
            /*  At mm minutes past the hour                                  */
            if (cycle_mm >= GET_MINUTE (arg_time))
                if (++cycle_hh == 24)
                  {
                    cycle_hh = 0;
                    cycle_days++;
                  }
            cycle_mm = GET_MINUTE (arg_time);
            break;

        case CYCLE_DAILY:
            if (cycle_time >= arg_time)
                cycle_days++;
            cycle_hh = GET_HOUR   (arg_time);
            cycle_mm = GET_MINUTE (arg_time);
            break;

        case CYCLE_WEEKLY:
            /*  First calculate cycle day, in same week as today, 0=Sunday   */
            cycle_days = cycle_days - day_of_week (cycle_date) + arg_day;

            /*  If that date has passed, move to next week                   */
            if ((cycle_days <  date_to_days (cycle_date))
            ||  (cycle_days == date_to_days (cycle_date)
            &&   cycle_time >= arg_time))
                cycle_days += 7;
            cycle_hh = GET_HOUR   (arg_time);
            cycle_mm = GET_MINUTE (arg_time);
            break;

        case CYCLE_MONTHLY:
            cycle_year  = GET_CCYEAR (cycle_date);
            cycle_month = GET_MONTH  (cycle_date);
            cycle_day   = GET_DAY    (cycle_date);
            if (arg_day < 1)
                arg_day = 1;
            if (cycle_day >  arg_day
            || (cycle_day == arg_day && cycle_time >= arg_time))
                if (++cycle_month == 13)
                  {
                    cycle_month = 1;
                    cycle_year++;
                  }
            cycle_hh   = GET_HOUR   (arg_time);
            cycle_mm   = GET_MINUTE (arg_time);
            cycle_date = cycle_year * 10000 + cycle_month * 100 + arg_day;
            cycle_days = date_to_days (cycle_date);
            break;

        case CYCLE_STARTUP:
        case CYCLE_MANUAL:
            want_alarm = FALSE;
            break;

        case CYCLE_SIZE:
            tcb-> file_limit = atol (tcb-> open-> cycle_size);
            break;

        case CYCLE_LINES:
            tcb-> file_limit = atol (tcb-> open-> cycle_lines);
            break;

        default:
            sendfmt (&operq, "ERROR", "xixlog: internal error 001");
            raise_exception (exception_event);
      }
    tcb-> cycle_time = MAKE_TIME    (cycle_hh, cycle_mm, 0, 0);
    tcb-> cycle_date = days_to_date (cycle_days);

    /*  Check the log file every XIXLOG_INTERVAL centiseconds                */
    if (want_alarm)
        send_alarm (&timeq, 0, XIXLOG_INTERVAL, 0, 0);
}


/***********************   CHECK IF CYCLE WHILE OPEN   ***********************/

MODULE check_if_cycle_while_open (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    switch (tcb-> cycle_when)
      {
        case CYCLE_HOURLY:
        case CYCLE_DAILY:
        case CYCLE_WEEKLY:
        case CYCLE_MONTHLY:
            if (date_now () >  tcb-> cycle_date
            || (date_now () == tcb-> cycle_date
             && time_now () >= tcb-> cycle_time))
                raise_exception (cycle_now_event);
            break;

        case CYCLE_SIZE:
            if (tcb-> stats.file_size / 1024 > tcb-> file_limit)
                raise_exception (cycle_now_event);
            break;

        case CYCLE_LINES:
            if (tcb-> stats.file_lines > tcb-> file_limit)
                raise_exception (cycle_now_event);
            break;

        default:
            sendfmt (&operq, "ERROR", "xixlog: internal error 002");
            raise_exception (exception_event);
      }
}


/***************************   CHECK CYCLE METHOD   **************************/

MODULE check_cycle_method (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    switch (tcb-> cycle_how)
      {
        case CYCLE_RENAME:
            the_next_event = rename_old_event;
            break;
        case CYCLE_DELETE:
            the_next_event = delete_old_event;
            break;
        case CYCLE_MOVE:
            the_next_event = move_old_event;
            break;
        case CYCLE_CONCAT:
            the_next_event = concat_old_event;
            break;
        case CYCLE_PROCESS:
            the_next_event = process_old_event;
            break;
        default:
            sendfmt (&operq, "ERROR", "xixlog: internal error 003");
            raise_exception (exception_event);
      }
}


/**************************   OPEN LOGFILE APPEND   **************************/

MODULE open_logfile_append (THREAD *thread)
{
    open_logfile (thread, 'a');
}

static void
open_logfile (THREAD *thread, char mode)
{
    int
        open_mode;
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  First get size of file, if necessary                                 */
    if (mode == 'a')
      {
        tcb-> stats.file_size  = get_file_size  (tcb-> filename);
        tcb-> stats.file_lines = get_file_lines (tcb-> filename);
      }
    else
      {
        /*  Zero, since we're going to create an new file                    */
        tcb-> stats.file_size  = 0;
        tcb-> stats.file_lines = 0;
      }
    if (mode == 'w')
        open_mode = O_WRONLY | O_CREAT | O_TRUNC;
    else
        open_mode = O_WRONLY | O_CREAT | O_APPEND;

    /*  Open file as specified                                               */
    tcb-> handle = lazy_open_text (tcb-> filename, open_mode);
                   
    /*  If file is already opened by another application, don't panic        */
    /*  We'll set the last character of the filename to '$' and try again    */
    if (io_completed && tcb-> handle < 0
    &&  errno == EACCES)
      {
        strlast (tcb-> filename) = '$';
        tcb-> handle = lazy_open_text (tcb-> filename, open_mode);
      }
    if (io_completed)
      {
        if (tcb-> handle > 0)
          {
            if strused (tcb-> log_header)
              {
                lazy_write (tcb-> handle, tcb-> log_header, strlen (tcb-> log_header));
                lazy_write (tcb-> handle, "\n", 1);
              }
          }
        else
          {
            /*  If the open failed, send error to console, and terminate     */
            sendfmt (&operq, "ERROR", "Could not open %s", tcb-> filename);
            senderr (&operq);
            raise_exception (exception_event);
          }
      }
}


/**************************   OPEN LOGFILE CREATE   **************************/

MODULE open_logfile_create (THREAD *thread)
{
    open_logfile (thread, 'w');
}


/*****************************   CLOSE LOGFILE   *****************************/

MODULE close_logfile (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)                   /*  Close log file, if opened        */
      {
        lazy_close (tcb-> handle);
        tcb-> handle = 0;
      }
}


/***************************   DELETE OLD LOGFILE   **************************/

MODULE delete_old_logfile (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    file_delete (tcb-> filename);
}


/***************************   RENAME OLD LOGFILE   **************************/

MODULE rename_old_logfile (THREAD *thread)
{
    char
        *formatted,
        *new_name;                      /*  Target file name                 */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Rename log file to new name using supplied path and pattern          */
    formatted = timestamp_string (NULL, tcb-> open-> cycle_argument);
    new_name  = file_where ('s', tcb-> open-> log_path, formatted, NULL);

    if (streq (new_name, tcb-> filename))
        sendfmt (&operq, "ERROR", "Can't rename '%s' to '%s'",
                                   tcb-> filename, new_name);
    else
      {
        if (file_exists (new_name))
          {
            mem_free (formatted);
            formatted = get_new_filename (new_name);
            new_name  = formatted;
          }
        if (file_rename (tcb-> filename, new_name) == 0)
            file_delete (tcb-> filename);
        else
          {
            sendfmt (&operq, "ERROR", "Could not rename '%s' to '%s'",
                                       tcb-> filename, new_name);
            senderr (&operq);
          }
      }
    mem_free (formatted);
}


/****************************   MOVE OLD LOGFILE   ***************************/

MODULE move_old_logfile (THREAD *thread)
{
    char
        *rename_to,                     /*  New location and name for file   */
        *new_filename = NULL;           /*  In case of duplicates            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Move log file to specified directory                                 */
    rename_to = file_where ('s', tcb-> open-> cycle_argument,
                                 tcb-> filename, NULL);
    ASSERT (rename_to);
    if (file_exists (rename_to))
      {
        new_filename = get_new_filename (rename_to);
        rename_to = new_filename;
      }
    if (file_rename (tcb-> filename, rename_to) == 0)
        file_delete (tcb-> filename);
    else
      {
        sendfmt (&operq, "ERROR", "Could not move '%s' to '%s'",
                                   tcb-> filename, rename_to);
        senderr (&operq);
      }
    mem_free (new_filename);            /*  If this was allocated            */
}


/***************************   CONCAT OLD LOGFILE   **************************/

MODULE concat_old_logfile (THREAD *thread)
{
    char
        *target;                        /*  Target file name                 */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Concat log file to specified file                                    */
    target = timestamp_string (NULL, tcb-> open-> cycle_argument);
    if (file_concat (tcb-> filename, target) == 0)
        file_delete (tcb-> filename);
    else
      {
        sendfmt (&operq, "ERROR", "Could not write to '%s'", target);
        senderr (&operq);
      }
    mem_free (target);
}


/**************************   PROCESS OLD LOGFILE   **************************/

MODULE process_old_logfile (THREAD *thread)
{
    char
        *insert_mark,                   /*  Position of %f in command        */
        *command,                       /*  Command to execute               */
        *copy_command;                  /*  With inserted filename           */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Execute command on specified file                                    */
    /*  First look for %f, and replace by filename, if necessary             */
    command = timestamp_string (NULL, tcb-> open-> cycle_argument);
    while ((insert_mark = strstr (command, "%f")) != NULL)
      {
        *insert_mark = '\0';
        copy_command = xstrcpy (NULL, command, tcb-> filename,
                                insert_mark + 2, NULL);
        mem_free (command);
        command = copy_command;
      }
    tcb-> process_id = process_create (
        command, NULL, ".", NULL, NULL, NULL, NULL, FALSE);

    if (tcb-> process_id == NULL_PROCESS)
      {
        sendfmt (&operq, "ERROR", "Can't run '%s'", command);
        senderr (&operq);
      }
    mem_free (command);
}


/***********************   GET LOG REQUEST ARGUMENTS   ***********************/

MODULE get_log_request_arguments (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT (tcb-> log == NULL);
    get_xixlog_log (thread-> event-> body, &tcb-> log);
    tcb-> client_host = NULL;           /*  No translated client hostname    */
}


/***********************   FREE LOG REQUEST ARGUMENTS   **********************/

MODULE free_log_request_arguments (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    free_xixlog_log (&tcb-> log);
    mem_strfree (&tcb-> client_host);
}


/*************************   CHECK IF RDNS REQUIRED   ************************/

MODULE check_if_rdns_required (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> uses_rdns)
        the_next_event = rdns_required_event;
    else
        the_next_event = ok_event;      /*  No translation wanted            */
}


/************************   SEND REQUEST TO RESOLVER   ***********************/

MODULE send_request_to_resolver (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_get_host_name (&rdnsq, 0, tcb-> log-> ip_server, 0);
}


/*************************   USE RESOLVED HOST NAME   ************************/

MODULE use_resolved_host_name (THREAD *thread)
{
    struct_smt_host_name
        *reply;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_smt_host_name (thread-> event-> body, &reply);
    tcb-> client_host = mem_strdup (reply-> host_name);
    free_smt_host_name (&reply);
}


/************************   WRITE REQUEST LOG ENTRY   ************************/

MODULE write_request_log_entry (THREAD *thread)
{
#   define STORE(name,value)  \
        sym_assume_symbol (tcb-> symtab, (name), (value))
#   define STFMT(name,format,value) \
        sprintf (buffer, (format), (value)); \
        sym_assume_symbol (tcb-> symtab, (name), buffer)
#   define NOTNULL(x)  (x) && *(x)? (x): "-"

    time_t
        time_secs;
    struct tm
        *time_struct;
    static char
        buffer [20];                    /*  Formatted values                 */
    char
        *query_string,                  /*  Full query string                */
        *log_line;

    /*  Get current date and time                                            */
    time_secs   = time (NULL);
    time_struct = localtime (&time_secs);

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (strused (tcb-> log-> query))
      {
        xstrcpy_debug ();
        query_string = xstrcpy (NULL, "?", tcb-> log-> query, NULL);
      }
    else
        query_string = NULL;
        
    STORE ("client"  , tcb-> client_host?
                       tcb-> client_host: tcb-> log-> ip_client);
    STORE ("ipcli"   , tcb-> log-> ip_client);
    STORE ("ipsrv"   , tcb-> log-> ip_server);
    STORE ("request" , tcb-> log-> request);
    STORE ("url"     , tcb-> log-> url);
    STORE ("query"   , query_string? query_string: "");
    STORE ("method"  , tcb-> log-> method);
    STORE ("status"  , tcb-> log-> response);
    STFMT ("recd"    , "%ld", tcb-> log-> size_recd);
    STFMT ("sent"    , "%ld", tcb-> log-> size_sent);
    STFMT ("time"    , "%ld", tcb-> log-> time_ms);
    STFMT ("stime"   , "%f", (float) (tcb-> log-> time_ms / 1000));
    STORE ("file"    , tcb-> log-> file_name);
    STORE ("agent"   , tcb-> log-> agent);
    STORE ("referer" , tcb-> log-> referer);
    STORE ("from"    , tcb-> log-> from);
    STORE ("service" , tcb-> log-> service);
    STORE ("user"    , NOTNULL (tcb-> log-> user_name));
    STORE ("vhost"   , NOTNULL (tcb-> log-> vhost_name));
    STORE ("datetime", http_time_str ());
    STFMT ("yy"      , "%02d", time_struct-> tm_year);
    STFMT ("year"    , "%04d", time_struct-> tm_year + 1900);
    STFMT ("mon"     , "%02d", time_struct-> tm_mon + 1);
    STFMT ("day"     , "%02d", time_struct-> tm_mday);
    STFMT ("hh"      , "%02d", time_struct-> tm_hour);
    STFMT ("mm"      , "%02d", time_struct-> tm_min);
    STFMT ("ss"      , "%02d", time_struct-> tm_sec);

    log_line = tok_subst (tcb-> log_format, tcb-> symtab);
    if (tcb-> handle)
      {
        lazy_write (tcb-> handle, log_line, strlen (log_line));
        lazy_write (tcb-> handle, "\n",     1);
      }

    tcb-> stats.file_size  += strlen (log_line) + 1;
    tcb-> stats.file_lines += 1;
    mem_strfree (&query_string);
    mem_strfree (&log_line);
}


/*************************   WRITE PLAIN LOG ENTRY   *************************/

MODULE write_plain_log_entry (THREAD *thread)
{
    char
        *log_line;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    log_line = (char *) thread-> event-> body;
    if (tcb-> handle)
      {
        lazy_write (tcb-> handle, log_line, strlen (log_line));
        lazy_write (tcb-> handle, "\n",     1);
      }
}


/***************************   REQUEUE THE EVENT   ***************************/

MODULE requeue_the_event (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    event_send (&tcb-> queue-> qid,
                &thread-> event-> sender,
                 thread-> event-> name,
                 thread-> event-> body,
                 thread-> event-> body_size,
                 thread-> event-> accept_event,
                 thread-> event-> reject_event,
                 thread-> event-> expire_event,
                 0);
}


/***********************   CHECK QUEUED EVENTS IF ANY   **********************/

MODULE check_queued_events_if_any (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    queue_deliver (tcb-> queue, thread);
}


/***************************   SIGNAL RDNS ERROR   ***************************/

MODULE signal_rdns_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
}


/**************************   SIGNAL RDNS TIMEOUT   **************************/

MODULE signal_rdns_timeout (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> open)
        free_xixlog_open (&tcb-> open);
    sym_delete_table (tcb-> symtab);
    mem_strfree (&tcb-> filename);
    mem_strfree (&tcb-> log_header);

    the_next_event = terminate_event;
}


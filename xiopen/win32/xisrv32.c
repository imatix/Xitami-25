/*===========================================================================*
 *                                                                           *
 *  xisrv32.c - Xitami service for Windows                                   *
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
 *===========================================================================*/

#include <windowsx.h>
#include <direct.h>                     /*  Directory create functions       */
#include "xitami.h"

/*- Instance definitions ----------------------------------------------------*/

#ifdef XITAMI_PRO
#include "xicorpro.d"                   /*  Xitami core definitions          */
#define APPLICATION_NAME  "xiprosrv"    /* Name of the executable            */
#else
#include "xicorstd.d"                   /*  Xitami core definitions          */
#define APPLICATION_NAME  "xisrv32"     /* Name of the executable            */
#endif


/*- Global definitions ------------------------------------------------------*/

#define DEPENDENCIES      ""
#define REGISTRY_XITAMI   "SOFTWARE\\imatix\\xitami"
#define REGISTRY_RUN      "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices"
#define WINDOWS_95        1             /*  Return from get_windows_version  */
#define WINDOWS_NT_4      2
#define WINDOWS_NT_3X     3

#define USAGE                                                                \
    XITAMI_NAME "web server: Windows service model\n"                        \
    "Syntax: " APPLICATION_NAME " [options...]\n"                            \
    "Options:\n"                                                             \
    "  -i               Install Windows service\n"                           \
    "  -u               Uninstall Windows service\n"                         \
    "  -d               Run as DOS console program\n"                        \
    "  -r directory     Root directory for web pages (webpages).\n"          \
    "  -c directory     Directory for CGI programs (cgi-bin).\n"             \
    "  -f directory     Root directory for FTP files (webpages).\n"          \
    "  -b portbase      Shift HTTP port 80 by this value.  E.g. to run\n"    \
    "                   on port 5080, do 'xitami -b 5000'.\n"                \
    "  -l filename      Log file for output (xitami.log).\n"                 \
    "  -a filename      Authorisation file (xitami.aut).\n"                  \
    "  -q               Quite mode: no messages or log.\n"                   \
    "  -t               Trace all socket i/o operations to log file.\n"      \
    "  -v               Show version information.\n"                         \
    "  -h               Show summary of command-line options.\n"             \
    "\nThe order of arguments is not important. Switches and filenames\n" \
    "are case sensitive. See documentation for detailed information."


/*- Global variables --------------------------------------------------------*/

static SERVICE_STATUS
    service_status;                     /* current status of the service     */
static SERVICE_STATUS_HANDLE
    service_status_handle;              /* Service status handle             */
static HANDLE
    server_stop_event = NULL;           /* Handle for server stop event      */
static DWORD
    error_code = 0;                     /*  Last error code                  */
static BOOL
    console_mode = FALSE,               /*  TRUE if console mode             */
    control_break = FALSE;              /*  TRUE if control break            */
static char
    *service_name,                      /*  Service name                     */
    *service_text,                      /*  Service description              */
    *rootdir,                           /*  Default root directory           */
    *cgidir,                            /*  CGI program directory            */
    *ftproot,                           /*  Default FTP root directory       */
    *portbase,                          /*  Value for IP portbase            */
    error_buffer [LINE_MAX + 1];        /*  Buffer for error string          */

/*- Function prototypes -----------------------------------------------------*/

void WINAPI  service_main        (int argc, char **argv);
void         service_start       (int argc, char **argv);
void         service_stop        (void);
void WINAPI  service_control     (DWORD control_code);
void         install_service     (void);
void         remove_service      (void);
void         console_service     (int argc, char **argv);
BOOL WINAPI  control_handler     (DWORD control_type);
static char *get_last_error_text (char *buffer, int size);
static int   get_windows_version (void);
static long  set_win95_service   (BOOL add);
static BOOL  report_status       (DWORD state, DWORD exit_code, DWORD wait_hint);
static void  add_to_message_log  (char *message);
static void  query_statistics    (void);
static int   report_smt_error    (void);
static void  hide_window         (void);


/*  ---------------------------------------------------------------------[<]-
    Function: main

    Synopsis: Main service function
    ---------------------------------------------------------------------[>]-*/

int
main (int argc, char **argv)
{
    static char
        buffer [LINE_MAX];
    int
        argn,                           /*  Argument number                  */
        win_version;
    char
        *p_char;

    SERVICE_TABLE_ENTRY 
        dispatch_table [] = {
        { NULL, (LPSERVICE_MAIN_FUNCTION) service_main },
        { NULL, NULL }
    };

    /*  Change to the correct working directory                              */
    GetModuleFileName (NULL, buffer, LINE_MAX);
    if ((p_char = strrchr (buffer, '\\')) != NULL)
        *p_char = '\0';
    SetCurrentDirectory (buffer);

    /*  Load configuration data, if any, into the config table               */
    config = ini_dyn_load (NULL, "xitami.cfg");
    ini_dyn_load (config, CONFIG ("server:defaults"));
    service_name = strdupl (CONFIG ("win32:service-name"));
    service_text = strdupl (CONFIG ("win32:service-text"));

    dispatch_table [0].lpServiceName = service_name;
    win_version = get_windows_version ();

    printf ("%s\n", PRODUCT);
    puts (QUOTES_TEXT);
    for (argn = 1; argn < argc; argn++)
      {
        if (*argv [argn] == '-')
          {
            switch (argv [argn][1])
              {
                case 'v':
                    printf ("%s\n", PRODUCT);
                    printf ("%s\n", BUILDMODEL);
                    printf ("%s\n", COPYRIGHT);
                    printf ("Built on: %s\n", BUILDDATE);
                    return (0);
                case 'h':
                    puts (USAGE);
                    return (0);
                /*  These switches take a parameter                          */
                case 'i':
                    if (win_version == WINDOWS_95)
                        set_win95_service (TRUE);
                    else
                        install_service ();
                    return (0);
                case 'u':
                    if (win_version == WINDOWS_95)
                        set_win95_service (FALSE);
                    else
                        remove_service ();
                    return (0);
                case 'd':
                    console_mode = TRUE;
                    console_service (argc, argv);
                    return (0);
              }
          }
      }
    if (win_version == WINDOWS_95)
      {
        hide_window ();
        console_mode = TRUE;
        console_service (argc, argv);
      }
    else
    if (win_version == WINDOWS_NT_3X
    ||  win_version == WINDOWS_NT_4)
      {
        printf ("\n%s: initialising service dispatcher...", APPLICATION_NAME);
        if (!StartServiceCtrlDispatcher (dispatch_table))
            add_to_message_log ("StartServiceCtrlDispatcher failed");
      }
	return (0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: service_main

    Synopsis: This routine performs the service initialization and then calls
              the user defined service_start() routine to perform majority
              of the work.
    ---------------------------------------------------------------------[>]-*/

void WINAPI
service_main (int argc, char **argv)
{
    /* Register our service control handler:                                 */
    service_status_handle 
        = RegisterServiceCtrlHandler (service_name, service_control);
    if (!service_status_handle)
        return;

    service_status.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
    service_status.dwServiceSpecificExitCode = 0;

    /* report the status to the service control manager.                     */
    if (report_status (
            SERVICE_START_PENDING,      /*  Service state                    */
            NO_ERROR,                   /*  Exit code                        */
            3000))                      /*  Wait Hint                        */
        service_start (argc, argv);

    /* Try to report the stopped status to the service control manager.      */
    if (service_status_handle)
        report_status (SERVICE_STOPPED, error_code, 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: service_start

    Synopsis: Main routine for xitami web server. The service stops when
    server_stop_event is signaled.
    ---------------------------------------------------------------------[>]-*/

void
service_start (int argc, char **argv)
{
    int
        argn;                           /*  Argument number                  */
    Bool
        args_ok     = TRUE,             /*  Were the arguments okay?         */
        quite_mode  = FALSE,            /*  -q means suppress all output     */
        server_mode = FALSE;            /*  -s means run in background       */
    char
        **argparm;                      /*  Argument parameter to pick-up    */
    DWORD
        wait;
    FILE
        *trace_file;

    /*  Initialise arguments, taking defaults from the config table          */
    rootdir  = strdupl (CONFIG ("server:webpages"));
    cgidir   = strdupl (CONFIG ("server:cgi-bin"));
    portbase = strdupl (CONFIG ("server:portbase"));
    ftproot  = strdupl (CONFIG ("ftp:root"));

    argparm = NULL;
    for (argn = 1; argn < argc; argn++)
      {
        /*  If argparm is set, we have to collect an argument parameter      */
        if (argparm)
          {
            if (*argv [argn] != '-')    /*  Parameter can't start with '-'   */
              {
                free (*argparm);
                *argparm = strdupl (argv [argn]);
                argparm = NULL;
              }
            else
              {
                args_ok = FALSE;
                break;
              }
          }
        else
        if (*argv [argn] == '-')
          {
            switch (argv [argn][1])
              {
                /*  These switches take a parameter                          */
                case 'r':
                    argparm = &rootdir;  break;
                case 'c':
                    argparm = &cgidir;   break;
                case 'f':
                    argparm = &ftproot;  break;
                case 'b':
                    argparm = &portbase; break;

                /*  These switches have an immediate effect                  */
                case 'q':
                    quite_mode = TRUE;
                    break;
                case 's':
                    server_mode = TRUE;
                    break;
                case 't':
                    smtsock_trace (TRUE);
                    break;
                /*  Used only for service                                    */
                case 'i':
                case 'd':
                case 'u':
                case 'v':
                case 'h':
                    break;
                /*  Anything else is an error                                */
                default:
                    args_ok = FALSE;
              }
          }
        else
          {
            args_ok = FALSE;
            break;
          }
      }

    /*  If there was a missing parameter or an argument error, quit          */
    if (argparm)
      {
        add_to_message_log ("Argument missing - type 'xitami -h' for help");
        return;
      }
    else
    if (!args_ok)
      {
        add_to_message_log ("Invalid arguments - type 'xitami -h' for help");
        return;
      }
    ip_portbase = atoi (portbase);

    /* Service initialization                                                */

    /* Report the status to the service control manager.                     */
    if (!report_status (
            SERVICE_START_PENDING,      /* Service state                     */
            NO_ERROR,                   /* Exit code                         */
            3000))                      /* wait hint                         */
        return;

    /* Create the event object. The control handler function signals         */
    /* this event when it receives the "stop" control code.                  */
    server_stop_event = CreateEvent (
                            NULL,       /* no security attributes            */
                            TRUE,       /* manual reset event                */
                            FALSE,      /* not-signalled                     */
                            NULL);      /* no name                           */

    if (server_stop_event == NULL)
        return;

    /* report the status to the service control manager.                     */
    if (!report_status (
            SERVICE_START_PENDING,      /* Service state                     */
            NO_ERROR,                   /* Exit code                         */
            3000))                      /* wait hint                         */
      {
        CloseHandle (server_stop_event);
        return;
      }
    if (quite_mode)
      {
        fclose (stdout);                /*  Kill standard output             */
        fclose (stderr);                /*   and standard error              */
      }
    /*  Report the status to the service control manager.                    */
    if (!report_status (SERVICE_RUNNING, NO_ERROR, 0))                
      {
        CloseHandle (server_stop_event);
        return;
      }

    while (!control_break)
      {
#ifdef XITAMI_PRO
#       include "xicorpro.i"            /*  Xitami core, with SSL            */
#else
#       include "xicorstd.i"            /*  Xitami core, standard            */
#endif
        /*  We do the main smt_exec loop here, so that we can also check
         *  service event messages.
         */
        FOREVER 
          {
            __try 
              {
                if (!smt_exec_step ())  /*  Run just one step                */
                  {
                    control_break = TRUE;
                    break;
                  }
              }
            __except (report_smt_error ()) 
              {
                /*  Fatal error handling                                     */
                http_term ();           /*  Shut-down HTTP server            */
                smt_term  ();           /*  Shut-down SMT kernel             */
                mem_freeall ();         /*  Free ALL allocated memory        */

                config = ini_dyn_load (NULL, "xitami.cfg");
                ini_dyn_load (config, CONFIG ("server:defaults"));
                break;                  /*  We'll recover control            */
              }
            wait = WaitForSingleObject (server_stop_event, 0);
            if (wait != WAIT_TIMEOUT)
                smt_shutdown ();        /*  Shut down the HTTP server        */
          }
        if (control_break)
            break;
      }
    smt_term ();
    CloseHandle (server_stop_event);

    /*  Deallocate configuration symbol table                                */
    sym_delete_table (config);

    /*  Check that all memory was cleanly released                           */
    if (mem_used ())
      {
        add_to_message_log ("Memory leak error, see 'memtrace.lst'");
        trace_file = fopen ("memtrace.lst", "w");
        mem_display (trace_file);
        fclose (trace_file);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: report_smt_error

    Synopsis: Pops-up a window; returns 0 if the user asked to debug the
    error, 1 if the user asked to continue.
    ---------------------------------------------------------------------[>]-*/

static int
report_smt_error (void)
{
    char
        *message;
    FILE
        *crash_log;

    message = xstrcpy (NULL,
        http_time_str (), " ", SERVER_VERS, "\r\n",
        smt_crash_report (), 
        NULL);
    add_to_message_log (message);

    /*  Log error to crash.log file                                          */
    crash_log = fopen ("crash.log", "a");
    if (crash_log)
      {
        fprintf (crash_log, message);
        fclose (crash_log);
      }
    /*  Recover silently if necessary                                        */
    if (*CONFIG ("server:recover") == '1')
        return (EXCEPTION_EXECUTE_HANDLER);
    else
    /*  Else start debugger                                                  */
        return (EXCEPTION_CONTINUE_SEARCH);
}


/*  ---------------------------------------------------------------------[<]-
    Function: service_stop

    Synopsis: Stops the service. If a service_stop procedure is going to
    take longer than 3 seconds to execute, it should spawn a thread to
    execute the stop code, and return.  Otherwise, ServiceControlManager
    will believe that the service has stopped responding.
    ---------------------------------------------------------------------[>]-*/

void
service_stop (void)
{
    if (server_stop_event)
        SetEvent (server_stop_event);
}


/*  ---------------------------------------------------------------------[<]-
    Function: query_statistics

    Synopsis: save statistics and security argument to registry
    ---------------------------------------------------------------------[>]-*/

static void
query_statistics (void)
{
    HKEY
        key;
    DWORD
        disp,
        type = REG_SZ;
    long
        size = LINE_MAX;
    int
        rc;
    char
        *curdir;                        /*  Current working directory        */

    /*  Check if control panel asked us to 'reset' the statistics            */
    rc = RegOpenKeyEx (HKEY_LOCAL_MACHINE, REGISTRY_XITAMI, 0, KEY_READ, &key);
    if (rc == ERROR_SUCCESS)
      {
        rc = RegQueryValueEx (key, (LPSTR) "reset", NULL,
                             (LPDWORD) &type, (LPBYTE) string, (LPDWORD) &size);
        if (rc == ERROR_SUCCESS)
          {
            if (streq (string, "true"))
              {
                connect_count = 0;
                max_connects  = 0;
                transfer_size = 0;
                error_count   = 0;
              }
          }
        RegCloseKey (key);
      }

    /*  Now store statistics                                                 */
    rc = RegCreateKeyEx (HKEY_LOCAL_MACHINE, REGISTRY_XITAMI, 0, REG_NONE,
                        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &disp);
    if (rc == ERROR_SUCCESS)
      {
        sprintf (string, "%ld", connect_count);
        RegSetValueEx (key, "total_connects",
                       0, REG_SZ, string, strlen (string) + 1);

        sprintf (string, "%ld", max_connects);
        RegSetValueEx (key, "max_connects",
                       0, REG_SZ, string, strlen (string) + 1);

        sprintf (string, "%ld", cur_connects);
        RegSetValueEx (key, "cur_connects",
                       0, REG_SZ, string, strlen (string) + 1);

        sprintf (string, "%ld", transfer_size);
        RegSetValueEx (key, "transfer_size",
                       0, REG_SZ, string, strlen (string) + 1);

        sprintf (string, "%ld", error_count);
        RegSetValueEx (key, "error_count",
                       0, REG_SZ, string, strlen (string) + 1);

        sprintf (string, "%ld", mem_used ());
        RegSetValueEx (key, "mem_used",
                       0, REG_SZ, string, strlen (string) + 1);

        sprintf (string, "%ld", ip_portbase);
        RegSetValueEx (key, "ip_portbase",
                       0, REG_SZ, string, strlen (string) + 1);

        /*  'secure' argument is "1" if we're running in secure mode         */
        if (config)
            strcpy (string, http_config (config, "win32:secure"));
        else
            strcpy (string, "0");
        RegSetValueEx (key, "secure",
                       0, REG_SZ, string, strlen (string) + 1);

        RegSetValueEx (key, "reset", 0, REG_SZ, "false", 6);

        /*  'curdir' argument is the current server working directory        */
        curdir = get_curdir ();
        RegSetValueEx (key, "curdir",
                       0, REG_SZ, curdir, strlen (curdir) + 1);
        mem_free (curdir);

        RegCloseKey (key);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: service_control

    Synopsis: This function is called by the service control manager whenever
              ControlService() is called on this service.
    ---------------------------------------------------------------------[>]-*/

void WINAPI
service_control (DWORD control_code)
{
    /* Handle the requested control code.                                    */
    switch (control_code)
      {
        case SERVICE_CONTROL_STOP:      /*  Stop the service                 */
            service_status.dwCurrentState = SERVICE_STOP_PENDING;
            service_stop ();
            break;

        case SERVICE_CONTROL_INTERROGATE:/* Update the service status        */
            query_statistics ();
            break;
        default:                        /*  Invalid control code             */
            break;
      }
    report_status (service_status.dwCurrentState, NO_ERROR, 0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: report_status

    Synopsis: Sets the current status of the service and
              reports it to the Service Control Manager.
    ---------------------------------------------------------------------[>]-*/

static BOOL
report_status (DWORD state, DWORD exit_code, DWORD wait_hint)
{
    static DWORD
        check_point = 1;
    BOOL
       result       = TRUE;

    /*  when debugging we don't report to the SCM                            */
    if (!console_mode)
      {
        if (state == SERVICE_START_PENDING)
            service_status.dwControlsAccepted = 0;
        else
            service_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;

        service_status.dwCurrentState  = state;
        service_status.dwWin32ExitCode = exit_code;
        service_status.dwWaitHint      = wait_hint;

        if (state == SERVICE_RUNNING
        ||  state == SERVICE_STOPPED)
            service_status.dwCheckPoint = 0;
        else
            service_status.dwCheckPoint = check_point++;


        /* Report the status of the service to the service control manager.  */
        result = SetServiceStatus (service_status_handle, &service_status);
        if (!result)
            add_to_message_log ("SetServiceStatus");
      }
    return result;
}


/*  ---------------------------------------------------------------------[<]-
    Function: add_to_message_log

    Synopsis: Allows any thread to log an error message.
    ---------------------------------------------------------------------[>]-*/

static void
add_to_message_log (char *message)
{
    static char
        *strings       [2],
        message_buffer [LINE_MAX + 1];
    HANDLE
        event_source_handle;

    if (!console_mode)
      {
        error_code = GetLastError();

        /* Use event logging to log the error.                               */
        event_source_handle = RegisterEventSource (NULL, service_name);

        sprintf (message_buffer, "%s error: %d", service_name, error_code);
        strings [0] = message_buffer;
        strings [1] = message;

        if (event_source_handle)
          {
            ReportEvent (event_source_handle,/* handle of event source       */
                EVENTLOG_ERROR_TYPE,         /* event type                   */
                0,                           /* event category               */
                0,                           /* event ID                     */
                NULL,                        /* current user's SID           */
                2,                           /* strings in variable strings  */
                0,                           /* no bytes of raw data         */
                strings,                     /* array of error strings       */
                NULL);                       /* no raw data                  */

            DeregisterEventSource (event_source_handle);
        }
    }
}


/*  ---------------------------------------------------------------------[<]-
    Function: install_service

    Synopsis: Installs the service
    ---------------------------------------------------------------------[>]-*/

void
install_service (void)
{
    SC_HANDLE
        service,
        manager;
    static char
        path [512];

    if (GetModuleFileName( NULL, path, 512 ) == 0)
      {
        printf ("%s: cannot install '%s': %s\n",
                 APPLICATION_NAME, service_name, 
                 get_last_error_text (error_buffer, LINE_MAX));
        return;
      }

    manager = OpenSCManager(
                    NULL,                      /* machine  (NULL == local)   */
                    NULL,                      /* database (NULL == default) */
                    SC_MANAGER_ALL_ACCESS      /* access required            */
                );
    if (manager)
      {
        service = CreateService (
                    manager,                   /* SCManager database         */
                    service_name,              /* Short name for service     */
                    service_text,              /* Name to display            */
                    SERVICE_ALL_ACCESS,        /* desired access             */
                    SERVICE_WIN32_OWN_PROCESS, /* service type               */
                    SERVICE_AUTO_START,        /* start type                 */
                    SERVICE_ERROR_NORMAL,      /* error control type         */
                    path,                      /* service's binary           */
                    NULL,                      /* no load ordering group     */
                    NULL,                      /* no tag identifier          */
                    DEPENDENCIES,              /* dependencies               */
                    NULL,                      /* LocalSystem account        */
                    NULL);                     /* no password                */

        if (service)
          {
            printf ("%s: service '%s' installed\n",
                     APPLICATION_NAME, service_name);
            CloseServiceHandle (service);
          }
        else
            printf ("%s: CreateService '%s' failed: %s\n", 
                    APPLICATION_NAME, service_name,
                    get_last_error_text (error_buffer, LINE_MAX));

        CloseServiceHandle (manager);
      }
    else
        printf ("%s: OpenSCManager failed: %s\n",
                APPLICATION_NAME, 
                get_last_error_text (error_buffer, LINE_MAX));
}


/*  ---------------------------------------------------------------------[<]-
    Function: remove_service

    Synopsis: Stops and removes the service
    ---------------------------------------------------------------------[>]-*/

void
remove_service (void)
{
    SC_HANDLE
        service,
        manager;

    manager = OpenSCManager(
                        NULL,                  /* machine (NULL == local)    */
                        NULL,                  /* database (NULL == default) */
                        SC_MANAGER_ALL_ACCESS  /* access required            */
                        );
    if (manager)
      {
        service = OpenService (manager, service_name, SERVICE_ALL_ACCESS);
        if (service)
          {
            /*  Try to stop the service                                      */
            if (ControlService (service, SERVICE_CONTROL_STOP, 
                &service_status))
              {
                printf ("%s: stopping service '%s'...",
                         APPLICATION_NAME, service_name);
                sleep (1);

                while (QueryServiceStatus (service, &service_status))
                    if (service_status.dwCurrentState == SERVICE_STOP_PENDING)
                      {
                        printf (".");
                        sleep  (1);
                      }
                    else
                        break;

                if (service_status.dwCurrentState == SERVICE_STOPPED)
                    printf (" Ok\n");
                else
                    printf (" Failed\n");
              }

            /*  Now remove the service                                       */
            if (DeleteService (service))
                printf ("%s: service '%s' removed\n",
                         APPLICATION_NAME, service_name);
            else
                printf ("%s: DeleteService '%s' failed: %s\n",
                         APPLICATION_NAME, service_name,
                         get_last_error_text (error_buffer, LINE_MAX));

            CloseServiceHandle (service);
          }
        else
            printf ("%s: OpenService '%s' failed: %s\n",
                     APPLICATION_NAME, service_name,
                     get_last_error_text (error_buffer, LINE_MAX));

        CloseServiceHandle (manager);
    }
    else
        printf ("%s: OpenSCManager failed: %s\n",
                 APPLICATION_NAME,
                 get_last_error_text (error_buffer, LINE_MAX));
}


/*  ---------------------------------------------------------------------[<]-
    Function: console_service

    Synopsis: Runs the service as a console application
    ---------------------------------------------------------------------[>]-*/

void
console_service (int argc, char ** argv)
{
    printf ("%s: starting in console mode\n", APPLICATION_NAME);
    SetConsoleCtrlHandler (control_handler, TRUE);
    service_start (argc, argv);
    control_break = FALSE;
}


/*  ---------------------------------------------------------------------[<]-
    Function: control_handler

    Synopsis: Handled console control events
    ---------------------------------------------------------------------[>]-*/

BOOL WINAPI
control_handler (DWORD control_type)
{
    switch (control_type)
      {
        /* Use Ctrl+C or Ctrl+Break to simulate SERVICE_CONTROL_STOP in      */
        /* console mode                                                      */
        case CTRL_BREAK_EVENT:
        case CTRL_C_EVENT:
            printf ("%s: stopping service\n", APPLICATION_NAME);
            control_break = TRUE;
            return (TRUE);

      }
    return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_last_error_text

    Synopsis: copies error message text to string
    ---------------------------------------------------------------------[>]-*/

static char *
get_last_error_text (char *buffer, int size)
{
    DWORD
        return_code;
    char
        *temp = NULL;

    return_code = FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                 FORMAT_MESSAGE_FROM_SYSTEM     |
                                 FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                 NULL,
                                 GetLastError (),
                                 LANG_NEUTRAL,
                                 (LPTSTR) &temp,
                                 0,
                                 NULL );

    /*  Supplied buffer is not long enough                                    */
    if (return_code == 0 || ((long) size < (long) return_code + 14))
        buffer [0] = '\0';
    else
      {
        temp [lstrlen (temp) - 2] = '\0'; /*remove cr and newline character  */
        sprintf (buffer, "%s (0x%x)", temp, GetLastError ());
      }
    if (temp)
        LocalFree ((HLOCAL) temp);

    return (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_windows_version

    Synopsis: Return the windows version
    <TABLE>
    WINDOWS_95       Windows 95 or later
    WINDOWS_NT_3X    Windows NT 3.x
    WINDOWS_NT_4     Windows NT 4.0 or later
    </TABLE>
    ---------------------------------------------------------------------[>]-*/

static int
get_windows_version (void)
{
    static int
        version = 0;
    OSVERSIONINFO
        version_info;

    version_info.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    if (GetVersionEx (&version_info))
      {
        if (version_info.dwMajorVersion < 4)
            version = WINDOWS_NT_3X;
        else
        if (version_info.dwPlatformId == VER_PLATFORM_WIN32_NT)
            version = WINDOWS_NT_4;
        else
            version = WINDOWS_95;
      }
    return (version);
}


/*  ---------------------------------------------------------------------[<]-
    Function: set_win95_service

    Synopsis: Add or remove from the windows registry the value to run
              the web server on startup.
    ---------------------------------------------------------------------[>]-*/

static long
set_win95_service (BOOL add)
{
    HKEY
        key;
    DWORD
        disp;
    long
        feedback;
    static char
        path [LINE_MAX + 1];

    feedback = RegCreateKeyEx (HKEY_LOCAL_MACHINE, REGISTRY_RUN, 
        0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &disp);

    if (feedback == ERROR_SUCCESS)
      {
        if (add)
          {
            GetModuleFileName (NULL, path, LINE_MAX);
            feedback = RegSetValueEx (key, "updater", 0, REG_SZ,
                                     (CONST BYTE *) path, strlen (path) + 1);
            coprintf ("Updater: service '%s' installed", service_name);
          }
        else
          {
            feedback = RegDeleteValue (key, "updater");
            coprintf ("Updater: service '%s' uninstalled", service_name);
          }
        RegCloseKey (key);
      }
    return (feedback);
}

static void
hide_window (void)
{
    char
        title [255];
    HWND
        win;
    GetConsoleTitle (title, 255);
    win = FindWindow( NULL,title);
    if (win)
        SetWindowPos (win, NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);
}

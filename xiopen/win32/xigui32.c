/*===========================================================================*
 *                                                                           *
 *  xigui32.c - Xitami windows front-end                                     *
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
#include "resource.h"                   /*  Program resources                */
#include "xitami.h"

/*- Instance definitions ----------------------------------------------------*/

#ifdef XITAMI_PRO
#   include "xicorpro.d"                /*  Xitami core definitions          */
#   define ABOUT_DIALOG      IDD_ABOUT_PRO
#   define MAIN_DIALOG       IDD_HTTP_PRO
#else
#   include "xicorstd.d"               /*  Xitami core definitions          */
#   define ABOUT_DIALOG      IDD_ABOUT
#   define MAIN_DIALOG       IDD_HTTP
#endif


/*- Global definitions ------------------------------------------------------*/

#define REGISTRY_RUN     "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"
#define REGISTRY_XITAMI  "SOFTWARE\\imatix\\xitami"
#define SC_SETBITMAP     0x8521
#define WINDOWS_95       1
#define WINDOWS_NT_4     2
#define WINDOWS_NT_3X    3
#define REFRESH_TIMER    1
#define REFRESH_DELAY    3000           /*  In milliseconds                  */
#define MYWM_NOTIFYICON  (WM_APP+100)
#define REDIRECT_URL     "redirect.url"

/*- Variables used in this program source -----------------------------------*/

static HMENU
    hMenu;                              /*  Handle to main menu              */
static HANDLE
    instance;
static HWND
    http_window,
    main_window;
static HICON
    hOn,
    hActive,
    hOff;
static Bool
    server_active = FALSE,              /*  Xitami on/off state              */
    terminate_req = FALSE,              /*  Terminate requested              */
    suspend_req = FALSE,                /*  Suspend requested                */
    show_dialog = FALSE,                /*  Displaying control panel?        */
    secure = FALSE;                     /*  Disable stop/start controls      */
static UINT
    timer_id = 0;
static HANDLE
    thread = NULL;                      /*  SMT server thread handle         */
static DWORD
    thread_id;
static int
    windows_version;


/*- Function declarations ---------------------------------------------------*/

static void terminate_the_program     (void);
static int  register_bitmap_control   (HANDLE hInst);
static void unregister_bitmap_control (HANDLE hInst);
static void show_server_state         (HWND hDlg);
static void update_system_bar_icon    (HWND hDlg);
static void refresh_statistics        (HWND hDlg);
static int  get_windows_version       (void);
static void launch_url                (char *url);
static void launch_setup              (void);
static void show_right_button_menu    (HWND hDlg);
static int  report_smt_error          (void);
static BOOL CALLBACK
       about_procedure (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK
       crash_procedure (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


static void 
show_address (char *address)
{
    if (strlen (string) + strlen (address) + 2 < LINE_MAX)
      {
        if (*string)
            strcat (string, ", ");
        strcat (string, address);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: refresh_statistics

    Synopsis: Updates the server statistics display box.
    ---------------------------------------------------------------------[>]-*/

static void
refresh_statistics (HWND hDlg)
{
    qbyte
        *hostaddrs;                     /*  List of host addresses           */
    char
        *hostname;                      /*  Host name                        */
    int
        index;

    strclr (string);
    hostaddrs = get_hostaddrs ();
    if (*CONFIG ("server:ipaddress") == '*')
      {
        if (hostaddrs)
            for (index = 0; hostaddrs [index]; index++)
                show_address (sock_ntoa (hostaddrs [index]));
        show_address ("127.0.0.1");
      }
    else
        show_address (CONFIG ("server:ipaddress"));
    mem_free (hostaddrs);

    SetDlgItemText (hDlg, IDC_IPADDRESS, string);

    /*  Format local hostname                                                */
    sprintf (string, "http://%s", get_hostname ());
    if (ip_portbase != 0)
      {
        hostname = string + strlen (string);
        sprintf (hostname, ":%d", ip_portbase + 80);
      }
    SetDlgItemText (hDlg, IDC_HOSTNAME,  string);
    sprintf (string, "%lu", connect_count);
    SetDlgItemText (hDlg, IDC_TOTAL_CONNECTS, string);
    sprintf (string, "%lu", cur_connects);
    SetDlgItemText (hDlg, IDC_CUR_CONNECTS, string);
    sprintf (string, "%lu", max_connects);
    SetDlgItemText (hDlg, IDC_MAX_CONNECTS, string);
    sprintf (string, "%lu", transfer_size);
    SetDlgItemText (hDlg, IDC_TRANSFERRED, string);
    sprintf (string, "%lu", error_count);
    SetDlgItemText (hDlg, IDC_ERRORS, string);
    sprintf (string, "%lu", mem_used () / 1024);
    SetDlgItemText (hDlg, IDC_MEMORY, string);
}


/*  ---------------------------------------------------------------------[<]-
    Function: SetBitmpapToDevice

    Synopsis: Load bitmap from resource, resize and display on device context.
    ---------------------------------------------------------------------[>]-*/

static void
SetBitmpapToDevice(
    HDC hDc,
    int dest_x,
    int dest_y,
    int dest_dx,
    int dest_dy,
    int bmp_name
)
{
    HBITMAP
        hBmp,
        hBitmapOld,
        hBitmapOld2,
        hBmpTmp;
    HDC
        hDcMemSrc,
        hDcMemDest,
        hDcScreen;
    BITMAP
        Bitmap;
    BOOL
        bRc;

    if (hDc)
      {
        hBmp = LoadBitmap (instance, MAKEINTRESOURCE (bmp_name));
        if (hBmp)
          {
            GetObject (hBmp, sizeof (BITMAP), (LPSTR)&Bitmap);

            if (Bitmap.bmWidth != 0)
                dest_dy = (int)((float)Bitmap.bmHeight *
                          ((float)dest_dx /(float)Bitmap.bmWidth ));
            else
                dest_dy = 0;

            if (dest_dy)
              {
                hBmpTmp = CreateBitmap (dest_dx, dest_dy, Bitmap.bmPlanes,
                                        Bitmap.bmBitsPixel, NULL);
                hDcScreen   = GetDC ((HWND)NULL);
                hDcMemSrc   = CreateCompatibleDC (hDcScreen);
                hDcMemDest  = CreateCompatibleDC (hDcScreen);
                hBitmapOld  = SelectObject (hDcMemSrc, hBmp);
                hBitmapOld2 = SelectObject (hDcMemDest, hBmpTmp);
                bRc = StretchBlt (hDcMemDest, dest_x, dest_y, dest_dx,
                                  dest_dy, hDcMemSrc, 0, 0, Bitmap.bmWidth,
                                  Bitmap.bmHeight, SRCCOPY);
                bRc = BitBlt (hDc, dest_x, dest_y, dest_dx, dest_dy,
                              hDcMemDest, dest_x, dest_y, SRCCOPY);
                SelectObject (hDcMemSrc,  hBitmapOld);
                SelectObject (hDcMemDest, hBitmapOld2);
                bRc = DeleteDC (hDcMemSrc);
                bRc = DeleteDC (hDcMemDest);
                bRc = ReleaseDC ((HWND)NULL, hDcScreen);
                bRc = DeleteObject (hBmp);
                bRc = DeleteObject (hBmpTmp);
              }
          }
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: bitmap_window_proc

    Synopsis: window procedure of bitmap control
    ---------------------------------------------------------------------[>]-*/

static LONG FAR PASCAL
bitmap_window_proc (HWND hWnd, WORD Message, WORD wParam, LONG lParam)
{
    HDC
        hDC;
    PAINTSTRUCT
        ps;                             /* holds PAINT information           */

    switch (Message)
      {
        case WM_COMMAND:
            switch (wParam)
              {
                 case IDCANCEL:
                     SendMessage( hWnd , WM_CLOSE , 0 , 0 );
                     break;
              }
            break;

        case WM_CREATE:
            SetWindowWord( hWnd , 0 , 0);
            break;

        case SC_SETBITMAP :
            {
            int
                bitmap_id;
            bitmap_id  = (int) GetWindowWord( hWnd , 0 );
            if ((int) wParam != bitmap_id)
              {
                SetWindowWord  (hWnd, 0, wParam);
                InvalidateRect (hWnd, NULL, FALSE);
                UpdateWindow   (hWnd);
              }
            }
            break;

        case WM_PAINT:
            {
            RECT
                rect;
            int
                bitmap_id;
            memset (&ps, 0x00, sizeof(PAINTSTRUCT));
            hDC = BeginPaint (hWnd, &ps);
            GetClientRect (hWnd , &rect);
            bitmap_id = (int)GetWindowWord( hWnd , 0 );
            SetBitmpapToDevice (hDC, 0, 0, rect.right - rect.left,
                                rect.bottom - rect.top, bitmap_id);
            EndPaint(hWnd, &ps);
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, Message, wParam, lParam);
      }
    return 0L;
}


static int
register_bitmap_control (HANDLE hInst)
{
    WNDCLASS
        wndclass;                       /* struct to define a window class   */

    memset(&wndclass, 0x00, sizeof(WNDCLASS));

    /* load WNDCLASS with window's characteristics                           */
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC) bitmap_window_proc;

    /* Extra storage for Class and Window objects                            */
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 4;
    wndclass.hInstance     = hInst;
    wndclass.hIcon         = (HICON)NULL;
    wndclass.hCursor       = LoadCursor((HINSTANCE)NULL, IDC_ARROW);

    /* Create brush for erasing background                                   */
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = NULL;       /* Menu Name is App Name             */
    wndclass.lpszClassName = "BMP_CTRL";/* Class Name is App Name            */

    if (!RegisterClass (&wndclass))
        return -1;

    return (0);
}

static void
unregister_bitmap_control (HANDLE hInst)
{
    UnregisterClass ("BMP_CTRL", hInst);
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
    Function: launch_url

    Synopsis: Starts default browser with specified URL as argument.
    Requires Win95 shell.  The URL argument should contain a %s symbol
    if the :xxx port is required.
    ---------------------------------------------------------------------[>]-*/

static void
launch_url (char *url)
{
    FILE
        *shortcut;

    if (ip_portbase == 0)
        strclr (string);
    else
        sprintf (string, ":%d", ip_portbase + 80);

    /*  Create shortcut file                                                 */
    shortcut = fopen (REDIRECT_URL, "wt");
    if (shortcut)
      {
        fprintf (shortcut, "[InternetShortcut]\nURL=");
        fprintf (shortcut, url, string);
        fprintf (shortcut, "\n");
        fclose  (shortcut);
        /*  Start shell command to handle URL                                */
        getcwd (string, LINE_MAX);
        ShellExecute (GetDesktopWindow (), "open", REDIRECT_URL,
                      NULL, string, SW_SHOW);
      }
}


static void
launch_setup (void)
{
    BOOL
        show_setup;
    int
        rc;                             /*  Return code from system call     */

    if (file_exists ("xiadmin.adm"))
        show_setup = TRUE;
    else
      {
        rc = MessageBox (main_window, SETUP_NOTE, "Information",
                         MB_APPLMODAL + MB_ICONEXCLAMATION + MB_OKCANCEL);
        show_setup = (rc != IDCANCEL);
      }
    if (show_setup)
        launch_url ("http://127.0.0.1%s/admin");
}

/*  ---------------------------------------------------------------------[<]-
    Function: SMT_thread

    Synopsis: Main SMT thread procedure
    ---------------------------------------------------------------------[>]-*/

static long
SMT_thread (void)
{
    Bool
        autostart;
    char
        *rootdir,                       /*  Default root directory           */
        *cgidir,                        /*  CGI program directory            */
        *ftproot;                       /*  Default FTP root directory       */

#if defined (XITAMI_PRO)
    server_name   = "Xitami/Pro";       /*  Set smthttp server name          */
#endif
    server_active = TRUE;               /*  Initially, running               */
    suspend_req   = FALSE;              /*  No-one asked for a suspend       */

    /*  The thread loops for ever, until terminate_req is set TRUE.          */
    /*  The main thread halts the server by calling smt_shutdown(), and      */
    /*  restarts it by setting server_active to TRUE.                        */

    FOREVER
      {
        /*  Load configuration data, if any, into the config table           */
        config = ini_dyn_load (NULL, "xitami.cfg");
        ini_dyn_load (config, CONFIG ("server:defaults"));
        secure    = *CONFIG ("win32:secure")     == '1';
        autostart = *CONFIG ("server:autostart") == '1';
        rootdir    = CONFIG ("server:webpages");
        cgidir     = CONFIG ("server:cgi-bin");
        ftproot    = CONFIG ("ftp:root");

        if (*CONFIG ("security:filename")
        && !file_exists (CONFIG ("security:filename")))
          {
            sprintf (string, 
            "Xitami could not find its password file '%s'.\r\n" \
            "you must reinstall Xitami, create this file, or reconfigure\r\n"\
            "Xitami (in defaults.cfg).  Xitami will now halt.", 
            CONFIG ("security:filename"));

            MessageBox (main_window, string, "Missing Password File",
                        MB_APPLMODAL + MB_ICONEXCLAMATION);
            sym_delete_table (config);
            config = NULL;
            break;
          }

        /*  Wait until the main thread asks us to activate the server        */
        /*  If server was explicitly suspended, we ignore autostart flag     */
        until (server_active || terminate_req || (autostart && !suspend_req))
            Sleep (200);                /*  1/5th of a second                */

        suspend_req = FALSE;            /*  No-one asked for a suspend       */
        if (terminate_req)
          {
            sym_delete_table (config);
            config = NULL;
            break;
          }
        SetFocus (http_window);
        show_server_state (http_window);

#if defined (XITAMI_PRO)
#   include "xicorpro.i"                /*  Xitami core, Pro                 */
#else
#   include "xicorstd.i"                /*  Xitami core, standard            */
#endif
        __try 
          {
            smt_exec_full ();           /*  Run until completed              */
          }
        __except (report_smt_error ()) 
          {
            /*  Fatal error handling                                         */
            http_term ();               /*  Shut-down HTTP server            */
            smt_term  ();               /*  Shut-down SMT kernel             */
            mem_freeall ();             /*  Free ALL allocated memory        */
            continue;
          }

        smt_term ();                    /*  Shut-down SMT kernel             */
        server_active = FALSE;          /*  It is no longer running          */
        show_server_state (http_window);

        /*  Deallocate configuration symbol table                            */
        sym_delete_table (config);
        config = NULL;

        /*  If the server was halted by the Admin control panel, then the    */
        /*  server_killed global is TRUE.                                    */
        if (server_killed)
            break;

        if (!suspend_req)
          {
            /*  If we did not ask for the server to halt then there was an   */
            /*  error.  If server:autostart is on, sleep and try again...    */
            /*  Else most probably the requested port is not available       */
            if (autostart)
              {
                sleep (5);
                server_active = TRUE;   /*  It is just almost running        */
                continue;
              }
            MessageBox (main_window, server_message, 
                        "Xitami was suspended",
                        MB_APPLMODAL + MB_ICONEXCLAMATION);
          }
      }
    /*  Tell main window to exit         */
    PostMessage (main_window, WM_QUIT, 0, 0);

    ExitThread (0);
    return (0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: report_smt_error

    Synopsis: Pops-up a window; returns 0 if the user asked to debug the
    error, 1 if the user asked to continue.
    ---------------------------------------------------------------------[>]-*/

static int
report_smt_error (void)
{
    FILE
        *crash_log;
    int
        rc;                             /*  Pop-up return code               */

    /*  Log error to crash.log file                                          */
    crash_log = fopen ("crash.log", "a");
    if (crash_log)
      {
        fprintf (crash_log, "%s %s\n%s\n",
                            http_time_str (), SERVER_VERS,
                            smt_crash_report ());
        fclose (crash_log);
      }
    /*  Recover silently if necessary                                        */
    if (*CONFIG ("server:recover") == '1')
        return (EXCEPTION_EXECUTE_HANDLER);
    else
      {
        rc = DialogBox (instance, MAKEINTRESOURCE (IDD_CRASH),
                        main_window, crash_procedure);

        if (rc == IDC_DEBUG)
            return (EXCEPTION_CONTINUE_SEARCH);
        else
        if (rc == IDC_RESTART)
            return (EXCEPTION_EXECUTE_HANDLER);
        else
        if (rc == IDC_ABORT)
          {
            /*  Tell main window to exit                                     */
            PostMessage (main_window, WM_QUIT, 0, 0);
            ExitThread (0);
          }
      }
    return (EXCEPTION_CONTINUE_SEARCH);
}


/*  ---------------------------------------------------------------------[<]-
    Function: crash_procedure

    Synopsis: Main crash window procedure
    ---------------------------------------------------------------------[>]-*/

static BOOL CALLBACK
crash_procedure (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int
        rc;
    char
        *message;

    switch (uMsg)
      {
        case WM_INITDIALOG:
            message = xstrcpy (NULL,
                http_time_str (), " ", SERVER_VERS, "\r\n",
                smt_crash_report (), 
                NULL);

            SetDlgItemText (hDlg, IDC_MESSAGE, message);
            mem_free (message);
            break;

        case WM_COMMAND:
            rc = GET_WM_COMMAND_ID (wParam, lParam);
            if (rc == IDC_RESTART || rc == IDC_DEBUG || rc == IDC_ABORT)
              {
                EndDialog (hDlg, rc);
                return (TRUE); 
              }
            break;
      }
    return (FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: about_procedure

    Synopsis: Main About window procedure
    ---------------------------------------------------------------------[>]-*/

static BOOL CALLBACK
about_procedure (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Bool
        end_dialog = FALSE;

    switch (uMsg)
      {
        case WM_INITDIALOG:
            SetDlgItemText (hDlg, IDC_VERSION, SERVER_VERS);
            SetDlgItemText (hDlg, IDC_QUOTES,  QUOTES_TEXT);
            break;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID (wParam, lParam))
              {
                case IDC_EMAIL:
                    launch_url ("mailto:register-xitami@imatix.com");
                    break;
                case IDC_IMATIX:
                    launch_url ("http://www.imatix.com/");
                    break;
                case IDC_XITAMI:
                    launch_url ("http://www.xitami.com/");
                    break;
                case IDOK:
                    end_dialog = TRUE;
                    break;
              }
            break;
      }
    if (end_dialog)
        EndDialog (hDlg, TRUE);

    return (end_dialog);
}


/*  ---------------------------------------------------------------------[<]-
    Function: terminate_the_program

    Synopsis: Terminates Xiwin: shuts down SMT, then tells the server
    thread to halt, then tells the main window to exit.
    ---------------------------------------------------------------------[>]-*/

static void
terminate_the_program (void)
{
    terminate_req = TRUE;               /*  Tell server thread to exit       */
    suspend_req   = TRUE;
    smt_shutdown ();                    /*  Shut down the HTTP server        */
}

/*  ---------------------------------------------------------------------[<]-
    Function: tray_message

    Synopsis: Sets the tray message.
    ---------------------------------------------------------------------[>]-*/

static BOOL
tray_message (HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip)
{
    BOOL
        res;
    NOTIFYICONDATA
        tnd;

    tnd.cbSize           = sizeof (NOTIFYICONDATA);
    tnd.hWnd             = hDlg;
    tnd.uID              = uID;
    tnd.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    tnd.uCallbackMessage = MYWM_NOTIFYICON;
    tnd.hIcon            = hIcon;

    if (pszTip)
        lstrcpyn (tnd.szTip, pszTip, sizeof (tnd.szTip));
    else
        tnd.szTip[0] = '\0';

    res = Shell_NotifyIcon (dwMessage, &tnd);

    if (hIcon)
        DestroyIcon (hIcon);

    return (res);
}


/*  ---------------------------------------------------------------------[<]-
    Function: draw_system_bar_icon

    Synopsis: Draw icon on the system bar
    ---------------------------------------------------------------------[>]-*/

static LRESULT
draw_system_bar_icon (LPDRAWITEMSTRUCT lpdi)
{
    HICON
        hIcon;

    hIcon = (HICON) LoadImage (instance, MAKEINTRESOURCE (lpdi-> CtlID),
                               IMAGE_ICON, 16, 16, 0);
    if (!hIcon)
        return(FALSE);


    DrawIconEx (lpdi-> hDC, lpdi-> rcItem.left, lpdi-> rcItem.top, hIcon,
                0, 0,                   /*  Icon size                        */
                0, NULL,
                DI_DEFAULTSIZE + DI_NORMAL);

    return (TRUE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: set_run_registry_key

    Synopsis: Add or remove from the windows registry the value to run
              the web server on startup.
    ---------------------------------------------------------------------[>]-*/

static long
set_run_registry_key (BOOL add)
{
    HKEY
        key;
    long
        feedback;
    static char
        path [LINE_MAX + 1];

    feedback = RegOpenKeyEx (
               HKEY_LOCAL_MACHINE, REGISTRY_RUN, 0, KEY_WRITE, &key);

    if (feedback == ERROR_SUCCESS)
      {
        if (add)
          {
            GetModuleFileName (NULL, path, LINE_MAX);
            feedback = RegSetValueEx (key, "xitami", 0, REG_SZ,
                                     (CONST BYTE *) path, strlen (path) + 1);
          }
        else
            feedback = RegDeleteValue (key, "xitami");
      }
    else
        feedback = RegDeleteValue (key, "xitami");

    RegCloseKey (key);

    return(feedback);
}


/*  ---------------------------------------------------------------------[<]-
    Function: check_if_run_at_startup

    Synopsis: Return TRUE if the web server run on startup
    ---------------------------------------------------------------------[>]-*/

static BOOL
check_if_run_at_startup (void)
{
    HKEY
        key;
    long
        size = LINE_MAX,
        open;
    DWORD
        type;

    open = RegOpenKeyEx (
           HKEY_LOCAL_MACHINE, REGISTRY_RUN, 0, KEY_QUERY_VALUE, &key);

    if (open == ERROR_SUCCESS)
      {
        open = RegQueryValueEx (
               key, "xitami",
               NULL, (LPDWORD) &type, (LPBYTE) string, (LPDWORD) &size);
        RegCloseKey (key);
      }
    return (open == ERROR_SUCCESS);
}


/*  ---------------------------------------------------------------------[<]-
    Function: save_run_registry

    Synopsis:
    ---------------------------------------------------------------------[>]-*/

static void
save_run_registry (HWND hDlg)
{
    int
       check;

    check = (int) SendDlgItemMessage (hDlg, IDC_STARTUP, BM_GETCHECK, 0, 0L);
    set_run_registry_key ((BOOL) check);
}


/*  ---------------------------------------------------------------------[<]-
    Function: show_server_state

    Synopsis: Set value of dialog control in function of server state.
    ---------------------------------------------------------------------[>]-*/

static void
show_server_state (HWND hDlg)
{
    update_system_bar_icon (main_window);
    if (!show_dialog)
        return;

    /*  If we're in secure mode, restrict controls                           */
    EnableWindow (GetDlgItem (hDlg, IDC_START),           !server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_SETUP),            server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_STOP),  !secure && server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_HELPS), !secure && server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_TERMINATE),              !secure);
    EnableWindow (GetDlgItem (hDlg, IDC_STARTUP),                !secure);

    if (server_active)
      {
        ShowWindow (GetDlgItem (hDlg, IDC_STATE_OFF), SW_HIDE);
        if (cur_connects > 0)
          {
            sprintf (string, "%d connection", cur_connects);
            if (cur_connects > 1)
                strcat (string, "s");
            SetDlgItemText (hDlg, IDC_SERVER_STATE, string);
            ShowWindow (GetDlgItem (hDlg, IDC_STATE_ACTIVE), SW_SHOW);
            ShowWindow (GetDlgItem (hDlg, IDC_STATE_ON),     SW_HIDE);
          }
        else
          {
            SetDlgItemText (hDlg, IDC_SERVER_STATE, "Active");
            ShowWindow (GetDlgItem (hDlg, IDC_STATE_ACTIVE), SW_HIDE);
            ShowWindow (GetDlgItem (hDlg, IDC_STATE_ON),     SW_SHOW);
          }
      }
    else
      {
        SetDlgItemText (hDlg, IDC_SERVER_STATE, "Suspended");
        ShowWindow (GetDlgItem (hDlg, IDC_STATE_ON),     SW_HIDE);
        ShowWindow (GetDlgItem (hDlg, IDC_STATE_ACTIVE), SW_HIDE);
        ShowWindow (GetDlgItem (hDlg, IDC_STATE_OFF),    SW_SHOW);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: update_system_bar_icon

    Synopsis: Refreshes the tray icon.
    ---------------------------------------------------------------------[>]-*/

static void
update_system_bar_icon (HWND hDlg)
{
    int
        icon;

    if (!server_active)
        icon = IDI_ICON_OFF;
    else
    if (cur_connects > 0)
        icon = IDI_ICON_ACTIVE;
    else
        icon = IDI_ICON_ON;

    sprintf (string, "%lu hits, %luKb, %lu active",
             connect_count, transfer_size, cur_connects);
    tray_message (
        hDlg,
        NIM_MODIFY,
        IDC_NOTIFY,
        LoadImage (
            instance,
            MAKEINTRESOURCE (icon),
            IMAGE_ICON, 0, 0,
            LR_DEFAULTSIZE), string); 
}


/*  ---------------------------------------------------------------------[<]-
    Function: dialog_procedure

    Synopsis: Main dialog window procedure
    ---------------------------------------------------------------------[>]-*/

static BOOL CALLBACK
http_dialog_procedure (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL
        in_reg;

    switch (uMsg)
      {
        case WM_INITDIALOG:
            /*  Indicate if the server is supposed to run at system startup  */
            in_reg = check_if_run_at_startup ();
            CheckDlgButton (hDlg, IDC_STARTUP, in_reg);

            /*  Initialise server state                                      */
            show_server_state (hDlg);
            break;

        case WM_TIMER:
            if (wParam == REFRESH_TIMER)
              {
                show_server_state (hDlg);
                refresh_statistics (hDlg);
              }
            break;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID (wParam, lParam))
              {
                case IDOK:
                    save_run_registry (hDlg);
                    show_dialog = FALSE;
                    if (windows_version == WINDOWS_NT_3X)
                        ShowWindow (main_window, SW_MINIMIZE);
                    else
                        ShowWindow (main_window, SW_HIDE);
                    break;

                case IDC_COPY:
                    if (OpenClipboard (hDlg))
                      {
                        LPTSTR  lptstrCopy; 
                        HGLOBAL hglbCopy; 

                        EmptyClipboard ();
                        hglbCopy = GlobalAlloc (GMEM_DDESHARE, 1024);
                        if (hglbCopy)
                          {
                            lptstrCopy = GlobalLock (hglbCopy); 
                            /*  Copy first host address                      */
                            GetDlgItemText (hDlg, IDC_IPADDRESS, lptstrCopy, 1024);
                            if (strchr (lptstrCopy, ','))
                               *strchr (lptstrCopy, ',') = '\0';
                            GlobalUnlock(hglbCopy); 
                            SetClipboardData(CF_TEXT, hglbCopy); 
                          }
                        CloseClipboard ();
                      }
                    break;

                case IDC_START:
                    server_active = TRUE;
                    show_server_state  (hDlg);
                    refresh_statistics (hDlg);
                    break;

                case IDC_STOP:
                    suspend_req = TRUE;
                    smt_shutdown ();
                    break;

                case IDC_RESET:
                    connect_count = 0;
                    max_connects  = 0;
                    error_count   = 0;
                    transfer_size = 0;
                    refresh_statistics (hDlg);
                    break;

                case IDC_HELPS:
                    launch_url ("http://127.0.0.1%s/windows.htm");
                    break;

                case IDC_SETUP:
                    launch_setup ();
                    break;

                case IDC_TERMINATE:     /*  End Xiwin                        */
                    KillTimer (hDlg, timer_id);
                    save_run_registry (hDlg);
                    terminate_the_program ();
                    break;

                case IDC_ABOUT:
                    DialogBox (instance, MAKEINTRESOURCE (ABOUT_DIALOG),
                               hDlg, about_procedure);
                    break;
              }
            break;

        default:
            return (FALSE);
      }
    return (TRUE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: main_window_proc

    Synopsis: Main window procedure
    ---------------------------------------------------------------------[>]-*/

static LONG CALLBACK
main_window_proc (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
      {
        case WM_CREATE:
            if (windows_version != WINDOWS_NT_3X)
                tray_message   (hDlg, NIM_ADD, IDC_NOTIFY, NULL, NULL);
            break;

        case WM_SETFOCUS:
            SetFocus (http_window);
            break;

        case WM_PAINT:
         {
           PAINTSTRUCT
               ps;

           if (windows_version == WINDOWS_NT_3X && IsIconic (hDlg))
             {
               BeginPaint(hDlg, (LPPAINTSTRUCT)&ps);
               /* Paint the desktop window background                        */
               DefWindowProc(hDlg, WM_ICONERASEBKGND, (WORD)ps.hdc, 0L);
               /* Draw the icon on top of it                                 */
               DrawIcon(ps.hdc, 0,0, server_active?
                                     cur_connects > 0?
                                     hActive: hOn: hOff);
               EndPaint(hDlg, (LPPAINTSTRUCT)&ps);
             }
           else
               return (DefWindowProc(hDlg, uMsg, wParam, lParam));
         }
           break;

       case WM_ERASEBKGND:
           if (windows_version == WINDOWS_NT_3X && IsIconic(hDlg))
              /* Don't erase the background now, since we will do it
                 at WM_PAINT time when we paint our own icon...              */
               return(TRUE);
           else
               return (DefWindowProc(hDlg, uMsg, wParam, lParam));

        case WM_DRAWITEM:
            if (windows_version != WINDOWS_NT_3X)
                return (draw_system_bar_icon ((LPDRAWITEMSTRUCT) lParam));
            break;

        case WM_CLOSE:
            SendMessage (http_window, WM_COMMAND, IDOK, 0L);
            break;

        case WM_DESTROY:
            if (windows_version != WINDOWS_NT_3X)
                tray_message (hDlg, NIM_DELETE, IDC_NOTIFY, NULL, NULL);
            break;

        case WM_COMMAND:
            switch (GET_WM_COMMAND_ID (wParam, lParam))
              {
                case IDFM_ABOUT:
                    DialogBox (instance, MAKEINTRESOURCE (ABOUT_DIALOG),
                               hDlg, about_procedure);
                    break;

                case IDFM_TERMINATE:    /*  End Xiwin                        */
                    KillTimer (http_window, timer_id);
                    terminate_the_program ();
                    break;

                case IDFM_SETUP:
                    launch_setup ();
                    break;

                case IDFM_PROPERTIES:
                    show_dialog = TRUE;
                    show_server_state   (http_window);
                    refresh_statistics  (http_window);
                    ShowWindow          (hDlg, SW_SHOWNORMAL);
                    SetForegroundWindow (hDlg);
                    break;

                case IDFM_ACTIVE:
                    if (server_active)
                      {
                        suspend_req = TRUE;
                        smt_shutdown ();
                      }
                    else
                      {
                        server_active = TRUE;
                        show_server_state  (http_window);
                        refresh_statistics (http_window);
                      }
              }
            break;

        case MYWM_NOTIFYICON:
            switch (lParam)
              {
                case WM_LBUTTONDBLCLK:
                    show_dialog = TRUE;
                    refresh_statistics  (http_window);
                    show_server_state   (http_window);
                    ShowWindow          (hDlg, SW_SHOWNORMAL);
                    SetForegroundWindow (hDlg);
                    break;
                case WM_RBUTTONDOWN:
                    show_right_button_menu (hDlg);
                    break;
                default:
                    break;
              }
            break;

        default:
            return (DefWindowProc(hDlg, uMsg, wParam, lParam));
      }
    return (0L);
}

static void show_right_button_menu (HWND hDlg)
{
    HMENU
        popup,
        menu;
    APPBARDATA
        pabd;
    POINT
        mouse_pos;

    menu  = LoadMenu (instance, MAKEINTRESOURCE (IDR_POPUP_MENU));
    popup = GetSubMenu (menu, 0);
    pabd.cbSize = sizeof (pabd);
    pabd.hWnd   = hDlg;
    SHAppBarMessage (ABM_GETTASKBARPOS, &pabd);

    CheckMenuItem  (popup, IDFM_ACTIVE,    server_active?
                    MF_CHECKED: MF_UNCHECKED);
    EnableMenuItem (popup, IDFM_SETUP,     server_active?
                    MF_ENABLED: MF_GRAYED);
    EnableMenuItem (popup, IDFM_TERMINATE, secure? MF_GRAYED: MF_ENABLED);
    EnableMenuItem (popup, IDFM_ACTIVE,    secure? MF_GRAYED: MF_ENABLED);

    SetForegroundWindow (hDlg);
    GetCursorPos   (&mouse_pos);
    TrackPopupMenu (popup, TPM_LEFTALIGN | TPM_LEFTBUTTON |
                           TPM_RIGHTBUTTON | TPM_VERTICAL,
                           (int) mouse_pos.x, (int) mouse_pos.y,
                           0, hDlg, NULL);
    DestroyMenu (menu);
}


/*  ---------------------------------------------------------------------[<]-
    Function: register_window

    Synopsis: Register Main window
    ---------------------------------------------------------------------[>]-*/

static int
register_window (HANDLE hInst)
{
    WNDCLASS
        wndclass;                       /* struct to define a window class   */

    memset(&wndclass, 0x00, sizeof(WNDCLASS));

    /* load WNDCLASS with window's characteristics                           */
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)main_window_proc;

    /* Extra storage for Class and Window objects                            */
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 2;
    wndclass.hInstance     = hInst;
    wndclass.hIcon         = (windows_version == WINDOWS_NT_3X)? (HICON)NULL:
                                                                 (HICON)hOn;
    wndclass.hCursor       = LoadCursor((HINSTANCE)NULL, IDC_ARROW);

    /* Create brush for erasing background                                   */
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wndclass.lpszMenuName  = NULL;      /* Menu Name is App Name             */
    wndclass.lpszClassName = "XIWIN";   /* Class Name is App Name            */

    if (!RegisterClass (&wndclass))
        return -1;

    return (0);
}


/*  ---------------------------------------------------------------------[<]-
    Function: unregister_window

    Synopsis: Unregister Main window
    ---------------------------------------------------------------------[>]-*/

static void
unregister_window (HANDLE hInst)
{
    UnregisterClass ("XIWIN", hInst);
}


/*  ---------------------------------------------------------------------[<]-
    Function: WinMain

    Synopsis: Main procedure
    ---------------------------------------------------------------------[>]-*/

int PASCAL
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR command_line,
         int nCmdShow)
{
    MSG
        msg;                            /* MSG structure to store messages   */
    static char
        *p_char,
        buffer [LINE_MAX];
    RECT
        rect;

    instance = hInstance;

    hOn     = LoadIcon (instance, MAKEINTRESOURCE (IDI_ICON_ON));
    hOff    = LoadIcon (instance, MAKEINTRESOURCE (IDI_ICON_OFF));
    hActive = LoadIcon (instance, MAKEINTRESOURCE (IDI_ICON_ACTIVE));

    windows_version = get_windows_version ();

    register_bitmap_control (instance);
    register_window         (instance);

    /*  Change to the correct working directory                              */
    GetModuleFileName (NULL, buffer, LINE_MAX);
    if ((p_char = strrchr (buffer, '\\')) != NULL)
        *p_char = '\0';
    SetCurrentDirectory (buffer);

    main_window = CreateWindow (
                "XIWIN",                /* Window class name                 */
                "Xitami Web Server Properties",
                                        /* Window's title                    */
                WS_CAPTION      |       /* Title and Min/Max                 */
                WS_BORDER       |
                WS_CLIPCHILDREN |       /* don't draw in child windows areas */
                WS_SYSMENU      |
                WS_MINIMIZEBOX  |
                WS_OVERLAPPED,
                200, 100,               /* X, Y                              */
                270, 245,               /* DX, DY                            */
                NULL,                   /* Parent window's handle            */
                NULL,                   /* Default to Class Menu             */
                instance,               /* Instance of window                */
                NULL);                  /* Create struct for WM_CREATE       */

    if (main_window == NULL)
      {
        LoadString (instance, IDS_ERR_CREATE_WINDOW, string, sizeof (string));
        MessageBox (NULL, string, NULL, MB_ICONEXCLAMATION);
        unregister_bitmap_control (instance);
        unregister_window (instance);
        DestroyIcon (hOn);
        DestroyIcon (hOff);
        DestroyIcon (hActive);
        return (IDS_ERR_CREATE_WINDOW);
      }

    /*  Create main control panel window                                     */
    http_window = CreateDialog (
        instance,
        MAKEINTRESOURCE (MAIN_DIALOG),
        main_window,
        http_dialog_procedure);

    if (http_window == NULL)
      {
        LoadString (instance, IDS_ERR_CREATE_WINDOW, string, sizeof (string));
        MessageBox (NULL, string, NULL, MB_ICONEXCLAMATION);
        unregister_bitmap_control (instance);
        unregister_window (instance);
        DestroyIcon  (hOn);
        DestroyIcon  (hOff);
        DestroyIcon (hActive);
        DestroyWindow (main_window);
        return (IDS_ERR_CREATE_WINDOW);
      }
    /*  Create server thread                                                 */
    thread = CreateThread (
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) SMT_thread,
        NULL,                           /*  No argument                      */
        0,                              /*  And run thread at once           */
        (LPDWORD) &thread_id);

    if (thread == NULL)
      {
        MessageBox (NULL, "Could not initialise Xitami web server",
                    NULL, MB_ICONEXCLAMATION);
        return (1);
      }
    else
        SetThreadPriority (thread, THREAD_PRIORITY_NORMAL);

    /*  Adjust main window size  (same as HTTP dialog)                       */
    GetWindowRect (http_window, &rect);
    SetWindowPos  (main_window, HWND_TOP, 0, 0, rect.right - rect.left,
                   rect.bottom - rect.top + 20, SWP_NOMOVE);
    BringWindowToTop (http_window);
    SetFocus (http_window);

    /*  We start by hiding the control panel window                          */
    show_dialog = FALSE;
    timer_id = SetTimer (http_window, REFRESH_TIMER, REFRESH_DELAY, NULL);

    if (windows_version == WINDOWS_NT_3X)
        ShowWindow (main_window, SW_MINIMIZE);
    else
        ShowWindow (main_window, SW_HIDE);

    /*  Now loop until we are finished                                       */
    while (GetMessage (&msg, main_window, 0, 0))
      {
        if (IsDialogMessage (http_window, &msg))
            continue;

        TranslateMessage (&msg);
        DispatchMessage  (&msg);
      }

    DestroyIcon (hOn);
    DestroyIcon (hOff);
    DestroyIcon (hActive);
    unregister_bitmap_control (instance);
    unregister_window         (instance);

    if (main_window)
        DestroyWindow (main_window);
    return (msg.wParam);
}

/*===========================================================================*
 *                                                                           *
 *  xicpl32.c - Xitami control panel for Windows                             *
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

#include "xitami.h"
#include "resource.h"
#include <cpl.h>

/*- Instance definitions ----------------------------------------------------*/

#ifdef XITAMI_PRO
#   define APPLICATION_NAME  "XIPROCPL"
#   define PANEL_NAME        "Xitami/Pro"
#   define MODULE_NAME       "xiprocpl.cpl"
#   define ABOUT_DIALOG      IDD_ABOUT_PRO
#   define MAIN_DIALOG       IDD_PRO_SERVICE
#else
#   define APPLICATION_NAME  "XIWINNTC"
#   define PANEL_NAME        "Xitami"
#   define MODULE_NAME       "xicpl32.cpl"
#   define ABOUT_DIALOG      IDD_ABOUT
#   define MAIN_DIALOG       IDD_MAIN_SERVICE
#endif


/*- Global definitions ------------------------------------------------------*/

#define SERVICE_NAME      "Xitami"      /* Internal name of the service      */
#define DEPENDENCIES      ""
#define REGISTRY_XITAMI   "SOFTWARE\\imatix\\xitami"
#define REG_XITAMI_SERV   "SYSTEM\\CurrentControlSet\\Services\\Xitami"
#define REDIRECT_URL      "redirect.url"
#define SC_SETBITMAP      0x8521
#define WINDOWS_95        1
#define WINDOWS_NT_4      2
#define WINDOWS_NT_3X     3
#define REFRESH_TIMER     1
#define MYWM_NOTIFYICON   (WM_APP+100)
#ifndef GET_WM_COMMAND_ID
#define GET_WM_COMMAND_ID(a,b) a
#endif

/*- Global variables --------------------------------------------------------*/

static HANDLE
    instance = NULL;
static HWND
    main_window;
static Bool
    server_active = FALSE;              /*  Xitami on/off state              */
static UINT
    timer_id = 0;
static HANDLE
    thread = NULL;                      /*  SMT server thread handle         */
static DWORD
    thread_id;
static int
    windows_version;
static long
    nt_connect_count,                   /*  Number of connections            */
    nt_cur_connects,                    /*  Current connections              */
    nt_max_connects,                    /*  Highest connections              */
    nt_transfer_size,                   /*  Number of errors                 */
    nt_error_count,                     /*  Amount of data transfered        */
    nt_mem_used,                        /*  Amount of memory allocated       */
    nt_ip_portbase,                     /*  Current IP port base             */
    nt_secure;                          /*  Run console in secure mode?      */


/*- Exported Functions declaration ------------------------------------------*/

long APIENTRY CPlApplet (HWND hwndCPl, UINT uMsg, LONG lParam1, LONG lParam2);

/*- Internal function declaration -------------------------------------------*/

static int   register_bitmap_control   (HANDLE hInst);
static void  unregister_bitmap_control (HANDLE hInst);
static void  get_server_state          (void);
static void  show_server_state         (HWND hDlg);
static void  set_server_state          (void);
static void  refresh_statistics        (HWND hDlg);
static int   get_windows_version       (void);
static long  on_inquire                (UINT uAppNum, NEWCPLINFO* pInfo);
static void  show_main_dialog          (HWND parent);
static void  query_statistics          (void);
static char *get_reg_value             (HKEY key, char *name);
static void  reset_statistics          (void);
static void  launch_url                (char *url);


/*  ---------------------------------------------------------------------[<]-
    Function: CPlApplet

    Synopsis: Main function of a control panel applet
    ---------------------------------------------------------------------[>]-*/

long APIENTRY
CPlApplet (HWND hwndCPl, UINT uMsg, LONG lParam1, LONG lParam2)
{
    if (instance == NULL)
        instance = GetModuleHandle (MODULE_NAME);

    switch (uMsg)
      {
        case CPL_DBLCLK:
            show_main_dialog (hwndCPl);
            return (0);

        case CPL_EXIT:
            unregister_bitmap_control (instance);
            return (0);

        case CPL_GETCOUNT:
            return (1);

        case CPL_INIT:
            register_bitmap_control (instance);
            windows_version = get_windows_version ();
            return (1);

        case CPL_NEWINQUIRE:
            return (on_inquire (lParam1, (NEWCPLINFO*)lParam2));

        case CPL_INQUIRE:
            return (0);

        case CPL_SELECT:
            return (1);

        case CPL_STOP:
            return (1);

        default:
            break;
      }

    return ((long)1);
}



/*  ---------------------------------------------------------------------[<]-
    Function: on_inquire

    Synopsis: Set info and incon of control panel applet
    ---------------------------------------------------------------------[>]-*/

static long
on_inquire (UINT uAppNum, NEWCPLINFO* pInfo)
{
    /* Fill in the data                                                      */
    pInfo-> dwSize = sizeof (NEWCPLINFO); /* Important                       */
    pInfo-> dwFlags       = 0;
    pInfo-> dwHelpContext = 0;
    pInfo-> lData         = 0;
    pInfo-> hIcon         = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON_ON));
    strcpy (pInfo-> szName, PANEL_NAME);
    strcpy (pInfo-> szInfo, SERVER_NAME);
    strcpy (pInfo-> szHelpFile, "");
    return (0);                         /* OK (don't send CPL_INQUIRE msg)   */
}


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

    query_statistics ();

    /*  Format local hostname                                                */
    sprintf (string, "http://%s", get_hostname ());
    if (nt_ip_portbase != 0)
      {
        hostname = string + strlen (string);
        sprintf (hostname, ":%d", nt_ip_portbase + 80);
      }
    SetDlgItemText (hDlg, IDC_HOSTNAME, string);
    sprintf (string, "%ld", nt_connect_count);
    SetDlgItemText (hDlg, IDC_CONNECTIONS, string);
    sprintf (string, "%lu", nt_cur_connects);
    SetDlgItemText (hDlg, IDC_CUR_CONNECTS, string);
    sprintf (string, "%lu", nt_max_connects);
    SetDlgItemText (hDlg, IDC_MAX_CONNECTS, string);
    sprintf (string, "%ld", nt_transfer_size);
    SetDlgItemText (hDlg, IDC_TRANSFERRED, string);
    sprintf (string, "%ld", nt_error_count);
    SetDlgItemText (hDlg, IDC_ERRORS, string);
    sprintf (string, "%lu", nt_mem_used / 1024);
    SetDlgItemText (hDlg, IDC_MEMORY, string);
}


/*  ---------------------------------------------------------------------[<]-
    Function: query_statistics

    Synopsis: query_statistics from the registry
    ---------------------------------------------------------------------[>]-*/

static void
query_statistics (void)
{
    DWORD
        state = 0xFFFFFFFF,
        error = 0xFFFFFFFF;
    SC_HANDLE
        hSCM,
        hService;
    SERVICE_STATUS
        ss;
    BOOL
        feedback;
    HKEY
        key;

    if (!server_active)
        return;

    /* open the service control manager                                      */
    hSCM = OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);

    ASSERT(hSCM);

    /* open the service                                                      */
    hService = OpenService (hSCM, SERVICE_NAME, SERVICE_ALL_ACCESS);
    if (hService)
      {
        /* Get the current status                                            */
        memset (&ss, 0, sizeof (ss));
        feedback = QueryServiceStatus (hService, &ss);
        if(feedback)
          {
            error = ss.dwWin32ExitCode;
            state = ss.dwCurrentState;
            if (ControlService (hService, SERVICE_CONTROL_INTERROGATE, &ss))
              {
                if (RegOpenKeyEx (HKEY_LOCAL_MACHINE,
                                  REGISTRY_XITAMI, 0, KEY_READ, &key)
                                  == ERROR_SUCCESS)
                  {
                    nt_connect_count = atol (
                        get_reg_value (key, "total_connects"));
                    nt_cur_connects  = atol (
                        get_reg_value (key, "cur_connects"));
                    nt_max_connects  = atol (
                        get_reg_value (key, "max_connects"));
                    nt_transfer_size = atol (
                        get_reg_value (key, "transfer_size"));
                    nt_error_count   = atol (
                        get_reg_value (key, "error_count"));
                    nt_mem_used      = atol (
                        get_reg_value (key, "mem_used"));
                    nt_ip_portbase   = atol (
                        get_reg_value (key, "ip_portbase"));
                    nt_secure        = atol (
                        get_reg_value (key, "secure"));
                    set_curdir (
                        get_reg_value (key, "curdir"));
                    RegCloseKey (key);
                  }
              }
          }
        /* Close the service handle                                          */
        CloseServiceHandle (hService);
      }

    /* Close the service control manager handle                              */
    CloseServiceHandle (hSCM);
}


static char *
get_reg_value (HKEY key, char *name)
{
    long
        size = LINE_MAX;
    DWORD
        type = REG_SZ;

    if (RegQueryValueEx (
            key,
            (LPSTR) name,
            NULL,
            (LPDWORD) &type,
            (LPBYTE) string,
            (LPDWORD) &size
    ) == ERROR_SUCCESS)
        return (string);
    else
        return ("");
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
            bitmap_id  = (int)GetWindowWord( hWnd , 0 );
            if( (int)wParam != bitmap_id )
              {
                SetWindowWord  (hWnd, 0 ,wParam );
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
    wndclass.lpszMenuName  = NULL;      /*  Menu Name is App Name            */
    wndclass.lpszClassName = "BMP_CTRL";/*  Class Name is App Name           */

    if (!RegisterClass (&wndclass))
        return -1;

    return(0);
}

static void
unregister_bitmap_control (HANDLE hInst)
{
    UnregisterClass("BMP_CTRL", hInst);
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
    Function: reset_statistics

    Synopsis: Save request of reset statistics to registry.
    ---------------------------------------------------------------------[>]-*/

static void
reset_statistics (void)
{
    HKEY
        key;
    DWORD
        disp,
        type = REG_SZ;

    if (RegCreateKeyEx (HKEY_LOCAL_MACHINE, REGISTRY_XITAMI, 0, REG_NONE,
                        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &disp)
        == ERROR_SUCCESS)
      {
        RegSetValueEx (key, "reset", 0, REG_SZ, "true", 5);
        RegCloseKey (key);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: show_server_state

    Synopsis: Set value of dialog control in function of server state.
    ---------------------------------------------------------------------[>]-*/

static void
show_server_state (HWND hDlg)
{
    get_server_state ();

    /*  If we're in secure mode, restrict controls                           */
    EnableWindow (GetDlgItem (hDlg, IDC_START),              !server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_SETUP),               server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_STOP),  !nt_secure && server_active);
    EnableWindow (GetDlgItem (hDlg, IDC_HELPS), !nt_secure && server_active);

    /*  Always show Autorun as TRUE; this and Terminate are disabled         */
    CheckDlgButton (hDlg, IDC_STARTUP, TRUE);

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
    Function: get_server_state

    Synopsis: Get the service state.
    ---------------------------------------------------------------------[>]-*/

static void
get_server_state (void)
{
    DWORD
        state = 0xFFFFFFFF,
        error = 0xFFFFFFFF;
    SC_HANDLE
        hSCM,
        hService;
    SERVICE_STATUS
        ss;
    BOOL
        feedback;

    server_active = FALSE;

    /* open the service control manager                                      */
    hSCM = OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);

    ASSERT(hSCM);

    /* open the service                                                      */
    hService = OpenService (hSCM, SERVICE_NAME, SERVICE_ALL_ACCESS);
    if (hService)
      {
        /* Get the current status                                            */
        memset (&ss, 0, sizeof (ss));
        feedback = QueryServiceStatus (hService, &ss);
        if(feedback)
          {
            error = ss.dwWin32ExitCode;
            state = ss.dwCurrentState;

            server_active = (state == SERVICE_RUNNING)? TRUE: FALSE;
          }
        /* Close the service handle                                          */
        CloseServiceHandle (hService);
      }

    /* Close the service control manager handle                              */
    CloseServiceHandle (hSCM);
}


/*  ---------------------------------------------------------------------[<]-
    Function: set_server_state

    Synopsis: set the service state (start or stop).
    ---------------------------------------------------------------------[>]-*/

static void
set_server_state (void)
{
    DWORD
         state = 0xFFFFFFFF,
         error = 0xFFFFFFFF;
    SC_HANDLE
         hSCM,
         hService;
    SERVICE_STATUS
         ss;

    /* open the service control manager                                      */
    hSCM = OpenSCManager (NULL, NULL, SC_MANAGER_ALL_ACCESS);

    ASSERT(hSCM);

    /* open the service                                                      */
    hService = OpenService (hSCM, SERVICE_NAME, SERVICE_ALL_ACCESS);
    if (hService)
      {
        if (server_active)
            ControlService (hService, SERVICE_CONTROL_STOP, &ss);
        else
            StartService   (hService, 0, NULL);
        CloseServiceHandle (hService);
      }

    /* Close the service control manager handle                              */
    CloseServiceHandle (hSCM);

}


/*  ---------------------------------------------------------------------[<]-
    Function: launch_url

    Synopsis: Starts default browser with specified URL as argument.
    Requires Win95 shell.
    ---------------------------------------------------------------------[>]-*/

static void
launch_url (char *url)
{
    FILE
        *shortcut;

    if (nt_ip_portbase == 0)
        strclr (string);
    else
        sprintf (string, ":%d", nt_ip_portbase + 80);

    /*  Create shortcut file                                                 */
    shortcut = fopen (REDIRECT_URL, "wt");
    fprintf (shortcut, "[InternetShortcut]\nURL=");
    fprintf (shortcut, url, string);
    fprintf (shortcut, "\n");
    fclose  (shortcut);

    /*  Start shell command to handle URL                                    */
    getcwd (string, LINE_MAX);
    ShellExecute (GetDesktopWindow (), "open", REDIRECT_URL,
                  NULL, string, SW_SHOW);
}


/*  ---------------------------------------------------------------------[<]-
    Function: dialog_procedure

    Synopsis: Main dialog window procedure
    ---------------------------------------------------------------------[>]-*/

BOOL CALLBACK
dialog_procedure (HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL
        show_setup;
    int
        rc;                             /*  Return code from system call     */

    switch (uMsg)
      {
        case WM_INITDIALOG:
            main_window = hDlg;
            /*  Initialise server state                                      */
            show_server_state (hDlg);
            if (server_active)
                timer_id = SetTimer (hDlg, REFRESH_TIMER, 1000, NULL);
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
                case IDCANCEL:
                    KillTimer (hDlg, timer_id);
                    EndDialog (hDlg, TRUE);
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
                    set_server_state   ();
                    show_server_state  (hDlg);
                    refresh_statistics (hDlg);
                    timer_id = SetTimer (hDlg, REFRESH_TIMER, 1000, NULL);
                    SetFocus (hDlg);
                    break;

                case IDC_STOP:
                    set_server_state   ();
                    show_server_state  (hDlg);
                    KillTimer (hDlg, timer_id);
                    SetFocus  (hDlg);
                    break;

                case IDC_RESET:
                    reset_statistics ();
                    nt_connect_count = 0;
                    nt_max_connects  = 0;
                    nt_error_count   = 0;
                    nt_transfer_size = 0;
                    refresh_statistics (hDlg);
                    SetFocus (hDlg);
                    break;

                case IDC_HELPS:
                    launch_url ("http://127.0.0.1/xitami/");
                    break;

                case IDC_SETUP:
                    if (file_exists (REDIRECT_URL))
                        show_setup = TRUE;
                    else
                      {
                        rc = MessageBox (main_window,
                                         SETUP_NOTE,
                                        "Information",
                                         MB_APPLMODAL + MB_ICONEXCLAMATION +
                                         MB_OKCANCEL);
                        show_setup = (rc != IDCANCEL);
                      }
                    if (show_setup)
                        launch_url ("http://127.0.0.1/admin");
                    break;

                case IDC_ABOUT:
                    DialogBox (instance, MAKEINTRESOURCE (ABOUT_DIALOG),
                               hDlg, about_procedure);
                    SetFocus (hDlg);
                    break;

              }
            break;
        default:
            return (FALSE);
      }

    return (TRUE);
}

void
show_main_dialog (HWND parent)
{
    if (windows_version == WINDOWS_95)
        MessageBox (parent, "Requires Windows NT", "Error",
                            MB_APPLMODAL + MB_ICONEXCLAMATION +
                            MB_OK);
    else
        DialogBox (
            instance,
            MAKEINTRESOURCE (MAIN_DIALOG),
            parent,
            dialog_procedure);
}

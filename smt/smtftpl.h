/*===========================================================================*
 *                                                                           *
 *  smtftpl.h -                                                              *
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

#ifndef _SMTFTPL_INCLUDED              /*  Allow multiple inclusions         */
#define _SMTFTPL_INCLUDED

#define FTP_VERSION \
    "Xitami FTP " XITAMI_VERSION " (c) 1991-2002 iMatix <http://www.imatix.com>"

#define FTP_SOFT_QUOTA  "***  Warning - FTP disk quota exceeded  ***\r\n"
#define FTP_HARD_QUOTA  "***   Uploads are no longer permitted   ***\r\n"

#define FTP_HELP_MESSAGE                                                      \
    "214-The following commands are recognized (* =>'s unimplemented).\r\n"   \
    "    USER    PASV    STOU*   MAIL*   ALLO*   CWD     PWD     XMKD \r\n"   \
    "    PASS    TYPE    SYST    MSND*   REST    CDUP    RMD     XRMD \r\n"   \
    "    ACCT*   STRU    XSYS*   MSOM*   RNFR    XCWD    SITE*   XPWD \r\n"   \
    "    REIN    MODE    PASV    MSAM*   RNTO    LIST    STAT*   XCUP*\r\n"   \
    "    QUIT    RETR    APPE    MRSQ*   ABOR    MKD     HELP    XEXC*\r\n"   \
    "    PORT    STOR    MLFL*   MRCP*   DELE    NLST    NOOP    SIZE \r\n"   \
    "214 " FTP_VERSION "\r\n"

/*- Global variables --------------------------------------------------------*/

extern qbyte
    ftp_connects;                       /*  Cur number of connections        */


/*- FTP responses -----------------------------------------------------------*/

#define FTP_RC_RESTART_MARKER             0
#define FTP_RC_READY_IN_DELAY             1
#define FTP_RC_DATA_OPEN_START            2
#define FTP_RC_FILE_OK                    3
#define FTP_RC_COMMAND_OK                 4
#define FTP_RC_NOT_IMPLEMENTED            5
#define FTP_RC_SYS_STATUS                 6
#define FTP_RC_DIR_STATUS                 7
#define FTP_RC_FILE_STATUS                8
#define FTP_RC_HELP_MESSAGE               9
#define FTP_RC_SYSTEM_NAME                10
#define FTP_RC_SERVICE_READY              11
#define FTP_RC_SERVICE_CLOSING            12
#define FTP_RC_DATA_OPEN_NO_TRANSFER      13
#define FTP_RC_DATA_CLOSE                 14
#define FTP_RC_PASSIVE_MODE               15
#define FTP_RC_USER_LOGGED                16
#define FTP_RC_FILE_ACTION_OK             17
#define FTP_RC_PATHNAME_CREATED           18
#define FTP_RC_USER_NAME_OK               19
#define FTP_RC_NEED_ACCOUNT               20
#define FTP_RC_FILE_ACTION_PENDING        21
#define FTP_RC_SERVICE_NOT_AVAILABLE      22
#define FTP_RC_DATA_OPEN_FAIL             23
#define FTP_RC_CONNECTION_CLOSE           24
#define FTP_RC_FILE_ACTION_NOT_TAKEN      25
#define FTP_RC_ACTION_ABORTED             26
#define FTP_RC_OVER_QUOTA                 27
#define FTP_RC_SYNTAX_ERROR               28
#define FTP_RC_SYNTAX_ERROR_PARAM         29
#define FTP_RC_COMMAND_NOT_IMPLEMENTED    30
#define FTP_RC_BAD_SEQUENCE               31
#define FTP_RC_BAD_PARAMETER              32
#define FTP_RC_LOGIN_FAILED               33
#define FTP_RC_NEED_ACCOUNT_STORE         34
#define FTP_RC_FILE_NOT_FOUND             35
#define FTP_RC_PAGE_TYPE_UKNOW            36
#define FTP_RC_BAD_STORAGE_ALLOC          37
#define FTP_RC_PERMISSION_DENIED          38
#define FTP_RC_MAX                        39

typedef struct {
    char *code;                         /*  Response code, 3 digits          */
    char *name;                         /*  Response text                    */
} FTP_RESPONSE;

#if (defined (DEFINE_FTP_TABLES))
FTP_RESPONSE                            /*  Some strings are in smtftpl.c    */
ftp_response [] = {
    { "110", "" /*  Restart reply       */                                   },
    { "120", "Service ready in %d minutes"                                   },
    { "125", "Data connection already open; transfer starting"               },
    { "150", "" /*  Prepare transfer    */                                   },
    { "200", "Command okay"                                                  },
    { "202", "Command not implemented"                                       },
    { "211", "System status, or system help reply"                           },
    { "212", "Directory status"                                              },
    { "213", "" /*  File status         */                                   },
    { "214", "" /*  Help message        */                                   },
    { "215", "" /*  System type         */                                   },
    { "220", "" /*  Ready for login     */                                   },
    { "221", "" /*  Closing connection  */                                   },
    { "225", "Data connection open; no transfer in progress"                 },
    { "226", "Closing data connection"                                       },
    { "227", "" /*  Passive mode        */                                   },
    { "230", "" /*  User logged-in      */                                   },
    { "250", "Requested file action okay, completed"                         },
    { "257", "" /*  Pathname created    */                                   },
    { "331", "" /*  Password required   */                                   },
    { "332", "Need account for login"                                        },
    { "350", "" /*  Restart okay        */                                   },
    { "421", "Service not available at present"                              },
    { "425", "Can't open data connection"                                    },
    { "426", "Connection closed; transfer aborted"                           },
    { "450", "Requested file action not taken"                               },
    { "451", "Requested action aborted: local error in processing"           },
    { "452", "Command failed - insufficient disk quota"                      },
    { "500", "" /*  Syntax error        */                                   },
    { "501", "Syntax error in parameters or arguments"                       },
    { "502", "" /*  Not implemented     */                                   },
    { "503", "" /*  Bad sequence        */                                   },
    { "504", "Command not implemented for that parameter"                    },
    { "530", "" /*  Login failed    */                                       },
    { "532", "Need account for storing files"                                },
    { "550", "" /*  No such file or directory */                             },
    { "551", "Failed: page type unknown"                                     },
    { "552", "Failed: aborted"                                               },
    { "553", "" /*  Permission denied */                                     },
    };
#else
extern FTP_RESPONSE ftp_response [];
#endif


/*- Permission bits ---------------------------------------------------------*/

#define FTP_AUTH_GET     0x0001
#define FTP_AUTH_PUT     0x0002
#define FTP_AUTH_DELETE  0x0004
#define FTP_AUTH_MKDIR   0x0008
#define FTP_AUTH_RMDIR   0x0010
#define FTP_AUTH_UPLOAD  0x0020
#define FTP_AUTH_ALL     0xFFFF
#define FTP_AUTH_COUNT   6              /*  Number of different types        */


/*- File types --------------------------------------------------------------*/

#define FTP_TYPE_ASCII  0x0001
#define FTP_TYPE_EBCDIC 0x0002
#define FTP_TYPE_IMAGE  0x0004
#define FTP_TYPE_NONPRT 0x0008
#define FTP_TYPE_TELNET 0x0010
#define FTP_TYPE_CAR    0x0020
#define FTP_TYPE_LOCBYT 0x0040


/*- Structure definitions ---------------------------------------------------*/

typedef struct {
    SYMTAB
        *users,                         /*  Users table                      */
        *direct,                        /*  Directory access table           */
        *config;                        /*  Configuration values             */
    char
        *user,                          /*  User name                        */
        *password,                      /*  Required password                */
        *guestname,                     /*  Supplied anonymous password      */
        *user_root,                     /*  User root directory              */
        *real_root,                     /*  As physical file name            */
        *cur_dir,                       /*  Current directory                */
        *last_file,                     /*  Last protected resource          */
        *file_name,                     /*  File name                        */
        *pipe,                          /*  Throttle pipe, if any            */
        *parameters,                    /*  Command parameters               */
         command [5];                   /*  Command (3-4 characters)         */
    sock_t
        socket;                         /*  Socket for FTP connection        */
    Bool
        aliases,                        /*  TRUE if can see root aliases     */
        login,                          /*  TRUE if login                    */
        passive,                        /*  TRUE if passive connection       */
        use_quotas,                     /*  TRUE if quotas apply to user     */
        temp_file;                      /*  Temporary files                  */
    dbyte
        last_permissions,               /*  Last permissions                 */
        file_type,                      /*  File type                        */
        return_code,                    /*  Return message                   */
        port,                           /*  Control port                     */
        data_port;                      /*  Port number of data connection   */
    qbyte
        cur_usage,                      /*  Current amount of disk used      */
        soft_quota,                     /*  User's soft quota, bytes         */
        hard_quota,                     /*  User's hard quota, bytes         */
        file_size,                      /*  File size                        */
        file_offset,                    /*  File offset for restarts         */
        ip_address,                     /*  IP adress of control connection  */
        timeout,                        /*  Wait input timeout               */
        data_host;                      /*  Host address of data connection  */
} FTP_CONTROL_CTX;


/*- Function prototypes -----------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*  Ftp control functions                                                    */

void  ftp_initialise       (void);
void  ftpc_init_connection (FTP_CONTROL_CTX *, sock_t handle);
void  ftpc_free_connection (FTP_CONTROL_CTX *);
void  ftpc_set_type        (FTP_CONTROL_CTX *);
void  ftpc_get_port        (FTP_CONTROL_CTX *);
Bool  ftpc_get_user        (FTP_CONTROL_CTX *);
Bool  ftpc_get_password    (FTP_CONTROL_CTX *);
Bool  ftpc_verify_password (FTP_CONTROL_CTX *);
void  ftpc_get_rootdir     (FTP_CONTROL_CTX *, char *rootdir);
void  ftpc_get_quotas      (FTP_CONTROL_CTX *);
void  ftpc_get_pipe        (FTP_CONTROL_CTX *);
dbyte ftpc_permissions     (FTP_CONTROL_CTX *, char *filename, Bool full);
void  ftpc_mkdir           (FTP_CONTROL_CTX *);
void  ftpc_rmdir           (FTP_CONTROL_CTX *);
void  ftpc_chdir           (FTP_CONTROL_CTX *);
void  ftpc_cdup            (FTP_CONTROL_CTX *);
void  ftpc_return_message  (FTP_CONTROL_CTX *, char *buffer);
void  ftpc_file_name       (FTP_CONTROL_CTX *, char *buffer);
Bool  ftpc_dir_name        (FTP_CONTROL_CTX *, char *buffer);
Bool  ftpc_make_listing    (FTP_CONTROL_CTX *, Bool full);
char *ftpc_map_name        (FTP_CONTROL_CTX *, char *external);
dbyte ftpc_access_bits     (char *access);

#ifdef __cplusplus
}

#endif

#endif

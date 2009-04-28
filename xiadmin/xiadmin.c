/*===========================================================================*
 *                                                                           *
 *  xiadmin.c - Administration Console                                       *
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

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP definitions             */
#include "smtftpl.h"                    /*  SMT FTP definitions              */
#include "formio.h"                     /*  Studio form i/o functions        */
#include "xixlog.h"                     /*  Xitami logging agent             */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME        "xiadmin"     /*  Our public name                  */
#define SINGLE_THREADED   TRUE          /*  Single-threaded agent            */
#define FORM_MAX          16000         /*  Max size of form data            */
#define MESSAGES_MAX      4000          /*  Amount of console data we hold   */
#define MESSAGE_TO_USER   0             /*  Always first field on form       */
#define FILENAME_SIZE     40            /*  Max. filename size (no path)     */
#define USERNAME_SIZE     40            /*  Max. user name size              */
#define WEBMASK_SIZE      80            /*  xxx.xxx.xxx.xxx                  */
#define REALM_SIZE        80            /*  Authentication realm             */
#define CUSTOM_WIDTH      65            /*  Width of custom log format box   */

typedef struct {                        /*  Fields on a particular form      */
    int   number;
    char *name;
    int   label;                        /*  Name of label tag                */
} FIELDREF;


/*- Macros ------------------------------------------------------------------*/

#define CONFVAL(s)        http_config (config_table, (s))
#define DEFTVAL(s)        http_config (defaults, (s))
#define USERVAL(s,d)      ini_dyn_value (passwd_table, user_name, (s), (d))
#define MAPURI(u)         http_map_uri (config_table, \
                          CONFVAL ("server:webpages"), \
                          CONFVAL ("server:cgi-bin"), (u), \
                          CONFVAL ("server:cgi-url"), 0)


/*- Function prototypes -----------------------------------------------------*/

static FORM_ITEM *open_form      (FORM_DEFN *defn);
static void set_form_focus       (FORM_ITEM **form);
static void show_form            (THREAD *thread);
static void close_form           (FORM_ITEM **form);
static Bool livelink_event       (void);
static Bool reserved_config      (char *config_file);
static void show_configs_page    (THREAD *thread);
static void show_resource_page   (THREAD *thread);
static void show_ftp_dir_page    (THREAD *thread);
static void put_values           (const char *prefix, FIELDREF *fields);
static void put_defaults         (const char *prefix, FIELDREF *fields);
static void get_values           (const char *prefix, FIELDREF *fields);
static void update_value         (const char *prefix, const char *name,
                                  const char *value, int field);
static void set_config_key       (const char *prefix, const char *name);
static void set_or_clear_symbol  (SYMTAB *table, char *name, char *prefix,
                                  char *value);
static SYMBOL *find_next_user    (SYMBOL *symbol);
static void update_user_value    (char *key, char *value);
static Bool is_default           (const char *key, const char *value, int type);
static void show_list_page       (THREAD *thread);
static void show_first_next      (int list_max);
static void free_config_table    (void);
static void free_passwd_table    (void);
static void free_direct_table    (void);
static void messages_handler     (const char *message);
static void show_pipes           (SYMTAB *table, char *key, int field, int label);
static void show_ipaddr_list     (SYMTAB *table, char *key, int field, int label);
static void update_ipaddress     (char *key, int field);
static void show_ftp_users_page  (THREAD *thread);
static void show_ftp_user_access (dbyte bits);
static int  show_server_threads  (char *agent_name, char *tag, int line);
static void show_ddns_services   (SYMTAB *table);
static void show_log_cycle       (SYMTAB *table);
static void show_log_format      (SYMTAB *table);
static void show_log_custom      (SYMTAB *table);
static QID *lookup_log_queue     (void);
static void update_log_custom    (void);
static void send_ddns_method     (char *method);
static void send_to_all_logfiles (char *method, char *mesg);
static void show_log_file_stats  (void);


/*- Global variables used in this source file only --------------------------*/

static QID
    operq,                              /*  Operator console event queue     */
    httpq;                              /*  SMTHTTP event queue              */
static struct_smt_wsx_request
    *request = NULL;                    /*  Incoming smt_wsx request         */
static FORM_ITEM
    *cur_form              = NULL,      /*  Current form                     */
    **cur_formp            = NULL,      /*  Address of current form          */
    *main_menu_form        = NULL,      /*  Main menu form                   */
    *config_list_form      = NULL,      /*  List of configuration files      */
    *config_server_form    = NULL,      /*  Server properties                */
    *config_advanced_form  = NULL,      /*  Advanced server properties       */
    *config_aliases_form   = NULL,      /*  Alias definitions                */
    *config_vhosts_form    = NULL,      /*  Virtual hosts                    */
    *config_cgi_form       = NULL,      /*  CGI properties                   */
    *config_security_form  = NULL,      /*  Security options                 */
    *config_logging_form   = NULL,      /*  Logging options                  */
    *config_log_file_form  = NULL,      /*  Log file options                 */
    *config_mimes_form     = NULL,      /*  MIME types                       */
    *config_ddns_form      = NULL,      /*  Dynamic DDNS options             */
    *config_cgi_envir_form = NULL,      /*  CGI environment                  */
    *config_cgi_alias_form = NULL,      /*  CGI aliases                      */
    *config_ssi_form       = NULL,      /*  SSI properties                   */
    *config_errors_form    = NULL,      /*  Custom error messages            */
    *config_wsx_form       = NULL,      /*  WSX plug-ins                     */
    *config_resource_form  = NULL,      /*  List of protected URIs           */
    *config_users_form     = NULL,      /*  Users and passwords for a URI    */
    *config_filter_form    = NULL,      /*  Filter programs                  */
    *config_ftp_form       = NULL,      /*  FTP setup                        */
    *config_ftp_users_form = NULL,      /*  FTP user setup                   */
    *config_ftp_user_form  = NULL,      /*  FTP setup                        */
    *config_ftp_dirs_form  = NULL,      /*  FTP directory accesses           */
    *config_ftp_uri_users_form = NULL,  /*  FTP users for a URI              */
    *config_ftp_alias_form = NULL,      /*  FTP aliases                      */
    *console_panel_form    = NULL,      /*  Control Panel                    */
    *console_messages_form = NULL,      /*  Control Panel messages           */
    *console_config_form   = NULL,      /*  Control Panel configuration      */
    *connection_list_form  = NULL,      /*  Current connections              */
    *vhost_wizard_form     = NULL;      /*  Virtual host wizard              */
static SYMTAB
    *symbols,                           /*  Form symbol table                */
    *config_table,                      /*  Current config symbol table      */
    *passwd_table,                      /*  Current user/password table      */
    *direct_table,                      /*  Current ftp dir table            */
    *list_table;                        /*  Current table for list           */
static LINEBUF
    *messages_buffer;                   /*  Console messages buffer          */
static Bool
    rich_logging,                       /*  Showing rich log file?           */
    messages_invert = FALSE;            /*  Show last data first?            */
static VDESCR
    buffer = { FORM_MAX, 0, NULL };     /*  Form i/o buffer                  */
static int
    session_id,                         /*  Current session id               */
    list_base,                          /*  List form scroll base            */
    list_count,                         /*  List form actual size            */
    list_max,                           /*  List form max size               */
    list_key,                           /*  List form key field              */
    list_name,                          /*  List form name field             */
    list_index,                         /*  List form index field            */
    list_value,                         /*  List form value field            */
    resource_base;                      /*  List base for resource screen    */
static char
    session_key   [12],                 /*  Formatted session key            */
    last_key      [12],                 /*  Key for displayed form           */
    config_key    [LINE_MAX + 1],       /*  Config field access key          */
    config_file   [FILENAME_SIZE + 1],  /*  Current config file name         */
    config_full   [FILENAME_SIZE + 5],  /*  Filename plus extension          */
    passwd_file   [FILENAME_SIZE + 1],  /*  Current open password file       */
    direct_file   [FILENAME_SIZE + 1],  /*  Current open directory list      */
    webmask       [WEBMASK_SIZE + 1],   /*  Current resource web mask        */
    realm         [REALM_SIZE + 1],     /*  Current resource realm name      */
    user_name     [USERNAME_SIZE + 1],  /*  FTP user name                    */
    resource_name [LINE_MAX + 1],       /*  Protected resource name          */
    resource_full [LINE_MAX + 1],       /*  Resource name followed by ':'    */
    *list_prefix,                       /*  Prefix string for current list   */
    *log_prefix;                        /*  Prefix string for log file page  */

#include "xiadmin.d"                    /*  Include dialog data              */
#include "xiadm01.h"                    /*  Admin form definitions           */
#include "xiadm02.h"
#include "xiadm03.h"
#include "xiadm04.h"
#include "xiadm05.h"
#include "xiadm06.h"
#include "xiadm07.h"
#include "xiadm08.h"
#include "xiadm09.h"
#include "xiadm10.h"
#include "xiadm11.h"
#include "xiadm12.h"
#include "xiadm13.h"
#include "xiadm14.h"
#include "xiadm15.h"
#include "xiadm16.h"
#include "xiadm17.h"
#include "xiadm18.h"
#include "xiadm19.h"
#include "xiadm20.h"
#include "xiadm21.h"
#include "xiadm22.h"
#include "xiadm23.h"
#include "xiadm24.h"
#include "xiadm25.h"
#include "xiadm26.h"
#include "xiadm27.h"
#include "xiadm28.h"
#include "xiadm29.h"
#include "xiadm30.h"
#include "xiadm31.h"
#include "xiadmin.h"                    /*  Graphic resources                */


/*- Screen display tables ---------------------------------------------------*/

static FIELDREF
    server_fields [] = {
      { XIADM03_AUTOSTART,      "autostart",       XIADM03_L_AUTOSTART       },
      { XIADM03_BACKGROUND,     "background",      XIADM03_L_BACKGROUND      },
      { XIADM03_CGI_BIN,        "cgi-bin",         XIADM03_L_CGI_BIN         },
      { XIADM03_CGI_URL,        "cgi-url",         XIADM03_L_CGI_URL         },
      { XIADM03_DEBUG,          "debug",           XIADM03_L_DEBUG           },
      { XIADM03_DEFAULT1,       "default1",        XIADM03_L_DEFAULT1        },
      { XIADM03_DEFAULT2,       "default2",        XIADM03_L_DEFAULT2        },
      { XIADM03_DEFAULT3,       "default3",        0                         },
      { XIADM03_DEFAULT4,       "default4",        0                         },
      { XIADM03_DIR_SCRIPT,     "dir-script",      XIADM03_L_DIR_SCRIPT      },
      { XIADM03_DIRSORT,        "dirsort",         XIADM03_L_DIRSORT         },
      { XIADM03_LIMIT,          "limit",           XIADM03_L_LIMIT           },
      { XIADM03_KEEP_ALIVE,     "keep-alive",      XIADM03_L_KEEP_ALIVE      },
      { XIADM03_KEEP_ALIVE_MAX, "keep-alive-max",  XIADM03_L_KEEP_ALIVE_MAX  },
      { XIADM03_RECOVER,        "recover",         XIADM03_L_RECOVER         },
      { XIADM03_REFRESH_RATE,   "refresh",         XIADM03_L_REFRESH_RATE    },
      { XIADM03_TIMEOUT,        "timeout",         XIADM03_L_TIMEOUT         },
      { XIADM03_WEBPAGES,       "webpages",        XIADM03_L_WEBPAGES        },
      { 0, NULL, 0                                                           }
    },
    cgi_fields [] = {
      { XIADM06_DEBUG,          "debug",           XIADM06_L_DEBUG           },
      { XIADM06_DIRLIST,        "dirlist",         XIADM06_L_DIRLIST         },
      { XIADM06_ENABLED,        "enabled",         XIADM06_L_ENABLED         },
      { XIADM06_ENVIRON,        "environment",     XIADM06_L_ENVIRON         },
      { XIADM06_ERRLOG,         "errlog",          XIADM06_L_ERRLOG          },
      { XIADM06_FORM_FIELDS,    "form-fields",     XIADM06_L_FORM_FIELDS     },
      { XIADM06_FORM_PREFIX,    "form-prefix",     XIADM06_L_FORM_PREFIX     },
      { XIADM06_FORM_QUERY,     "form-query",      XIADM06_L_FORM_QUERY      },
      { XIADM06_HTTP_FIELDS,    "http-fields",     XIADM06_L_HTTP_FIELDS     },
      { XIADM06_HTTP_PREFIX,    "http-prefix",     XIADM06_L_HTTP_PREFIX     },
      { XIADM06_MIXED_URL,      "mixed-url",       XIADM06_L_MIXED_URL       },
      { XIADM06_MONITOR,        "monitor",         XIADM06_L_MONITOR         },
      { XIADM06_MSDOS_STYLE,    "msdos-style",     XIADM06_L_MSDOS_STYLE     },
      { XIADM06_STDIO,          "stdio",           XIADM06_L_STDIO           },
      { XIADM06_SUPPORT_16BIT,  "win32:16bit-cgi", XIADM06_L_SUPPORT_16BIT   },
      { XIADM06_TIMEOUT,        "timeout",         XIADM06_L_TIMEOUT         },
      { XIADM06_WILDCARD,       "wildcard",        XIADM06_L_WILDCARD        },
      { XIADM06_WORKDIR,        "workdir",         XIADM06_L_WORKDIR         },
      { 0, NULL, 0                                                           }
    },
    security_fields [] = {
      { XIADM07_ADMIN,          "admin",           XIADM07_L_ADMIN           },
      { XIADM07_DIRLIST,        "dirlist",         XIADM07_L_DIRLIST         },
      { XIADM07_FILENAME,       "filename",        XIADM07_L_FILENAME        },
      { XIADM07_PASSWORD_CASE,  "password-case",   XIADM07_L_PASSWORD_CASE   },
      { XIADM07_SAFEPATHS,      "safepaths",       XIADM07_L_SAFEPATHS       },
      { XIADM07_SECURE,         "win32:secure",    XIADM07_L_SECURE          },
      { XIADM07_SUPERUSER,      "superuser",       XIADM07_L_SUPERUSER       },
      { XIADM07_CGI_USERNAME,   "cgi-username",    XIADM07_L_CGI_USERNAME    },
      { XIADM07_CGI_GROUPNAME,  "cgi-groupname",   XIADM07_L_CGI_GROUPNAME   },
      { XIADM07_CGI_PASSWORD,   "cgi-password",    XIADM07_L_CGI_PASSWORD    },
      { XIADM07_SETUID,         "setuid",          XIADM07_L_SETUID          },
      { XIADM07_SETUID_USER,    "setuid-user",     XIADM07_L_SETUID_USER     },
      { XIADM07_SETUID_GROUP,   "setuid-group",    XIADM07_L_SETUID_GROUP    },
      { XIADM07_WEBMASK,        "webmask",         XIADM07_L_WEBMASK         },
      { 0, NULL, 0                                                           }
    },
    logging_fields [] = {
      { XIADM08_LOG_DIR,     "server:log-dir",        XIADM08_L_LOG_DIR      },
      { XIADM08_SERVER_MSGS, "serverlog:filename",    0,                     },
      { XIADM08_HTTP_ACCESS, "accesslog:filename",    0,                     },
      { XIADM08_HTTP_ERROR,  "errorlog:filename",     0,                     },
      { XIADM08_FTP_ACCESS,  "ftplog:filename",       0,                     },
      { XIADM08_FTP_ERROR,   "ftperrlog:filename",    0,                     },
      { XIADM08_PRIMARY,     "rdns:primary-server",   XIADM08_L_PRIMARY      },
      { XIADM08_SECONDARY,   "rdns:secondary-server", XIADM08_L_SECONDARY    },
      { XIADM08_RECURSE,     "rdns:recurse-lookups",  XIADM08_L_RECURSE      },
      { XIADM08_DEBUG,       "rdns:debug",            XIADM08_L_DEBUG        },
      { 0, NULL, 0                                                           }
    },
    error_fields [] = {
      { XIADM10_ERROR_SCRIPT,   "error-script",      XIADM10_L_ERROR_SCRIPT  },
      { XIADM10_ERROR_HEADER,   "error-header",      XIADM10_L_ERROR_HEADER  },
      { XIADM10_TEXT_400,       "text-400",          XIADM10_L_TEXT_400      },
      { XIADM10_TEXT_401,       "text-401",          XIADM10_L_TEXT_401      },
      { XIADM10_TEXT_402,       "text-402",          XIADM10_L_TEXT_402      },
      { XIADM10_TEXT_403,       "text-403",          XIADM10_L_TEXT_403      },
      { XIADM10_TEXT_404,       "text-404",          XIADM10_L_TEXT_404      },
      { XIADM10_TEXT_412,       "text-412",          XIADM10_L_TEXT_412      },
      { XIADM10_TEXT_413,       "text-413",          XIADM10_L_TEXT_413      },
      { XIADM10_TEXT_500,       "text-500",          XIADM10_L_TEXT_500      },
      { XIADM10_TEXT_501,       "text-501",          XIADM10_L_TEXT_501      },
      { XIADM10_TEXT_502,       "text-502",          XIADM10_L_TEXT_502      },
      { XIADM10_ERROR_FOOTER,   "error-footer",      XIADM10_L_ERROR_FOOTER  },
      { 0, NULL, 0                                                           }
    },
    ftp_fields [] = {
      { XIADM16_DATA_PORT,      "data-port",         XIADM16_L_DATA_PORT     },
      { XIADM16_DIRECTORY_FILE, "directory-file",    XIADM16_L_DIRECTORY_FILE},
      { XIADM16_DIRSORT,        "dirsort",           XIADM16_L_DIRSORT       },
      { XIADM16_EMAIL_CHECK,    "email-check",       XIADM16_L_EMAIL_CHECK   },
      { XIADM16_ENABLED,        "enabled",           XIADM16_L_ENABLED       },
      { XIADM16_HTTP_ALIASES,   "http-aliases",      XIADM16_L_HTTP_ALIASES  },
      { XIADM16_LIMIT,          "limit",             XIADM16_L_LIMIT         },
      { XIADM16_LOGIN,          "login-text",        XIADM16_L_LOGIN         },
      { XIADM16_MESSAGE_SCRIPT, "message-script",    XIADM16_L_MESSAGE_SCRIPT},
      { XIADM16_PASSWORD_CASE,  "password-case",     XIADM16_L_PASSWORD_CASE },
      { XIADM16_PORT,           "port",              XIADM16_L_PORT          },
      { XIADM16_ROOTDIR,        "root",              XIADM16_L_ROOTDIR       },
      { XIADM16_SIGNOFF,        "signoff",           XIADM16_L_SIGNOFF       },
      { XIADM16_TIMEOUT,        "timeout",           XIADM16_L_TIMEOUT       },
      { XIADM16_SOFT_QUOTA,     "soft-quota",        XIADM16_L_SOFT_QUOTA    },
      { XIADM16_HARD_QUOTA,     "hard-quota",        XIADM16_L_HARD_QUOTA    },
      { XIADM16_USER_FILE,      "user-file",         XIADM16_L_USER_FILE     },
      { XIADM16_USER_AT_HOST,   "user-at-host",      XIADM16_L_USER_AT_HOST  },
      { XIADM16_WEBMASK,        "webmask",           XIADM16_L_WEBMASK       },
      { XIADM16_WELCOME,        "welcome",           XIADM16_L_WELCOME       },
      { 0, NULL, 0                                                           }
    },
    console_fields [] = {
      { XIADM23_STARTUP,        "startup",         XIADM23_L_STARTUP         },
      { XIADM23_CAPTURE,        "capture",         XIADM23_L_CAPTURE         },
      { XIADM23_FILENAME,       "filename",        XIADM23_L_FILENAME        },
      { XIADM23_APPEND,         "append",          XIADM23_L_APPEND          },
      { XIADM23_JAVASCRIPT,     "javascript",      XIADM23_L_JAVASCRIPT      },
      { XIADM23_LARGE_ICONS,    "large-icons",     XIADM23_L_LARGE_ICONS     },
      { 0, NULL, 0                                                           }
    },
    ssi_fields [] = {
      { XIADM28_ENABLED,        "enabled",         XIADM28_L_ENABLED         },
      { XIADM28_EXEC,           "exec",            XIADM28_L_EXEC            },
      { XIADM28_TIMEFMT,        "timefmt",         XIADM28_L_TIMEFMT         },
      { XIADM28_SIZEFMT,        "sizefmt",         XIADM28_L_SIZEFMT         },
      { XIADM28_ERRMSG,         "errmsg",          XIADM28_L_ERRMSG          },
      { XIADM28_TIMEOUT,        "timeout",         XIADM28_L_TIMEOUT         },
      { 0, NULL, 0                                                           }
    },
    log_file_fields [] = {
      { XIADM29_ENABLED,        "enabled",         XIADM29_L_ENABLED         },
      { XIADM29_FILENAME,       "filename",        XIADM29_L_FILENAME        },
      { XIADM29_INC_LOCAL,      "local",           XIADM29_L_INC_LOCAL       },
      { XIADM29_HEADER,         "header",          XIADM29_L_HEADER          },
      { XIADM29_CYCLE_TIME,     "cycle-time",      XIADM29_L_CYCLE_TIME      },
      { XIADM29_CYCLE_DAY,      "cycle-day",       XIADM29_L_CYCLE_DAY       },
      { XIADM29_CYCLE_SIZE,     "cycle-size",      XIADM29_L_CYCLE_SIZE      },
      { XIADM29_CYCLE_LINES,    "cycle-lines",     XIADM29_L_CYCLE_LINES     },
      { XIADM29_CYCLE_HOW,      "cycle-how",       XIADM29_L_CYCLE_HOW       },
      { XIADM29_CYCLE_ARG,      "cycle-arg",       XIADM29_L_CYCLE_ARG       },
      { XIADM29_TRANSLATE,      "translate",       XIADM29_L_TRANSLATE       },
      { 0, NULL, 0                                                           }
    },
    ddns_fields [] = {
      { XIADM30_ENABLED,        "enabled",         XIADM30_L_ENABLED         },
      { XIADM30_DOMAIN,         "domain",          XIADM30_L_DOMAIN          },
      { XIADM30_USERNAME,       "username",        XIADM30_L_USERNAME        },
      { XIADM30_PASSWORD,       "password",        XIADM30_L_PASSWORD        },
      { XIADM30_FILENAME,       "filename",        XIADM30_L_FILENAME        },
      { 0, NULL, 0                                                           }
    },
    advanced_fields [] = {
      { XIADM31_BASE_HOST,      "base-host",       XIADM31_L_BASE_HOST       },
      { XIADM31_CACHE_DEFAULTS, "cache-defaults",  XIADM31_L_CACHE_DEFAULTS  },
      { XIADM31_DEBUG_DIR,      "debug-dir",       XIADM31_L_DEBUG_DIR       },
      { XIADM31_HOSTNAME,       "hostname",        XIADM31_L_HOSTNAME        },
      { XIADM31_PORTBASE,       "portbase",        XIADM31_L_PORTBASE        },
      { XIADM31_PRIORITY,       "priority",        XIADM31_L_PRIORITY        },
      { XIADM31_SUPERVISOR,     "supervisor",      XIADM31_L_SUPERVISOR      },
      { XIADM31_TEMP_DIR,       "temp-dir",        XIADM31_L_TEMP_DIR        },
      { XIADM31_LRWP_ENABLED,   "lrwp:enabled",    XIADM31_L_LRWP_ENABLED    },
      { XIADM31_LRWP_PORT,      "lrwp:port",       XIADM31_L_LRWP_PORT       },
      { XIADM31_LRWP_WEBMASK,   "lrwp:webmask",    XIADM31_L_LRWP_WEBMASK    },
      { XIADM31_PIPEDEF,        "pipedef",         XIADM31_L_PIPEDEF         },
      { XIADM31_SSL_ENABLED,  "ssl-http:enabled",     XIADM31_L_SSL_ENABLED  },
      { XIADM31_SSL_FILENAME, "ssl-http:config-file", XIADM31_L_SSL_FILENAME },
      { 0, NULL, 0                                                           }
    };

/*  Extensions on SSI page                                                   */

static int
    ext_field [] = {
        XIADM28_FILEEXT1,
        XIADM28_FILEEXT2,
        XIADM28_FILEEXT3,
        XIADM28_FILEEXT4,
        XIADM28_FILEEXT5,
        XIADM28_FILEEXT6
    };


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int xiadmin_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */
#   include "xiadmin.i"                 /*  Include dialog interpreter       */

    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN", shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "WSX_REQUEST", ok_event, 0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create master thread                                                 */
    thread_create (AGENT_NAME, "main");
    randomize ();                       /*  We use random URL keys           */

    /*  Create messages buffer and redirect console output to our handler    */
    messages_buffer = linebuf_create (MESSAGES_MAX);
    console_send (messages_handler, TRUE);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    symbols     = sym_create_table ();
    buffer.data = mem_alloc (FORM_MAX + 1);
    strclr (session_key);
    strclr (config_file);
    strclr (passwd_file);
    strclr (direct_file);

    httpq = thread_lookup (SMT_HTTP, "main")-> queue-> qid;
    the_next_event = ok_event;
}


/************************   DETERMINE INITIAL SCREEN   ***********************/

MODULE determine_initial_screen (THREAD *thread)
{
    switch (atoi (http_config (config, "console:startup")))
      {
        case 1:  the_next_event = main_event;    break;
        case 2:  the_next_event = config_event;  break;
        case 3:  the_next_event = hosts_event;   break;
        case 4:  the_next_event = console_event; break;
        default: the_next_event = main_event;    break;
      }
}


/**********************   DECODE HTTP INITIAL REQUEST   **********************/

MODULE decode_http_initial_request (THREAD *thread)
{
    if (the_external_event == ok_event)
      {
        /*  Decode WTP request into structure                                */
        if (request)
            free_smt_wsx_request (&request);
        get_smt_wsx_request (thread-> event-> body, &request);
      }
    else                                /*  Something like shutdown_event    */
        raise_exception (the_external_event);
}


/**********************   DECODE HTTP REQUEST REPONSE   **********************/

MODULE decode_http_request_reponse (THREAD *thread)
{
    char
        *slash,                         /*  Second slash in URL              */    
        *url_args,                      /*  If &data supplied in arguments   */
        *post_data = NULL;              /*  Posted data string               */
    DESCR
        *data_descr = NULL;

    if (the_external_event == ok_event)
      {
        /*  Decode WTP request into structure                                */
        if (request)
            free_smt_wsx_request (&request);
        get_smt_wsx_request (thread-> event-> body, &request);

        ASSERT (request-> arguments);
        ASSERT (request-> post_data);

        /*  Look at posted data; if necessary, slurp it from response file   */
        post_data = request-> post_data;
        if (*post_data == '@')
          {
            data_descr = file_slurp (post_data + 1);
            if (data_descr)
                post_data = (char *) data_descr-> data;
          }

        /*  If arguments contain &... data, cut, then append to posted data  */
        slash     = strchr (request-> request_url + 1, '/');
        url_args  = strchr (request-> arguments, '&');
        xstrcpy_debug ();
        post_data = xstrcpy (NULL, post_data, url_args, NULL);

        /*  Maybe we have a request for a resource file                      */
        if (slash && slash [1] != '\0')
            the_next_event = resource_event;
        else
        if (cur_form)
          {
            /*  Clear message to user in all cases                           */
            fxput_text (MESSAGE_TO_USER, "");

            /*  Do we have a normal submit or Enter action?                  */
            if (strused (session_key)
            &&  strprefixed (request-> arguments, session_key))
              {
                /*  Get form - if there are bad dates or numbers, reshow     */
                if (form_get (cur_form, post_data) == -1)
                  {
                    fxput_text (MESSAGE_TO_USER, form_strerror);
                    the_next_event = data_error_event;
                  }
                else
                    the_next_event = cur_form-> event;
              }
            else
            /*  Maybe we have a form Reload action?                          */
            if (strused (last_key)
            &&  strprefixed (request-> arguments, last_key))
              {
                strcpy (session_key, last_key);
                the_next_event = reshow_form_event;
              }
            else
            /*  Anything else is unusable, so start a new session            */
                raise_exception (new_session_event);
          }
        else
            raise_exception (new_session_event);

        mem_free (post_data);
        mem_free (data_descr);
      }
    else                                /*  Something like shutdown_event    */
        raise_exception (the_external_event);
}


/**********************   SEND RESOURCE FILE IF KNOWN   **********************/

MODULE send_resource_file_if_known (THREAD *thread)
{
    DESCR
        symbols;                        /*  Symbol descriptor                */
    SYMTAB
        *symtab;                        /*  Symbol table                     */
    int
        lookup;                         /*  Lookup table index               */
    char
        *filename;                      /*  Resource filename                */
    RESOURCE
        *resource;                      /*  Resource structure               */

    /*  Check for an 'If-Modified' header in the request symbol table        */
    symbols.size = request-> symbols_size;
    symbols.data = request-> symbols_data;
    symtab = descr2symb (&symbols);
    if (sym_lookup_symbol (symtab, "HTTP_IF_MODIFIED_SINCE"))
        send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_NOTMODIFIED);
    else
      {
        /*  Request URL should be in the form /xxxx/filename.ext             */
        filename = strchr (request-> request_url + 1, '/');
        ASSERT (filename);
        filename++;

        /*  Icon filenames starting with '$' can be shown in large or small
         *  forms; for small form we skip the '$', for large forms we replace
         *  it by 'l'.
         */
        if (filename [0] == '$')
          {
            if (*http_config (config, "console:large-icons") == '1')
                filename [0] = 'l';
            else
                filename++;
          }
        /*  Do simple scan; if number of resources hits 50 we should do a
         *  binary chop.  In any case the lookup table is sorted by name in
         *  preparation of this.
         */
        resource = NULL;
        for (lookup = 0; lookup < tblsize (lookup_xiadmin); lookup++)
          {
            if (streq (lookup_xiadmin [lookup].filename, filename))
                resource = lookup_xiadmin [lookup].resource;
          }
        if (resource)
            send_wsx_bin (&thread-> event-> sender,
                          resource-> size, resource-> body);
        else
            send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_NOTFOUND);
      }
    sym_delete_table (symtab);

    /*  Wait for next request                                                */
    if (request)
        free_smt_wsx_request (&request);

    event_wait ();
}


/**************************   OPEN MAIN ADMIN MENU   *************************/

MODULE open_main_admin_menu (THREAD *thread)
{
    FILE
        *log_file;

    main_menu_form = open_form (&form_xiadm01);
    session_id = random (65535L);
    log_file = file_open ("xiadmin.adm", 'w');
    if (log_file)
      {
        file_write (log_file, "Admin screens accessed successfully.");
        file_close (log_file);
      }
}


static FORM_ITEM *
open_form (FORM_DEFN *defn)
{
    cur_form = form_init (defn, TRUE);
    cur_form-> click_event = enter_event;
    cur_form-> date_order  = DATE_ORDER_YMD;
    cur_form-> date_sep    = '-';
    cur_form-> dec_point   = '.';

    form_use (cur_form);
    return (cur_form);
}


/**************************   SHOW MAIN ADMIN MENU   *************************/

MODULE show_main_admin_menu (THREAD *thread)
{
    set_form_focus (&main_menu_form);
    show_form (thread);
}


static void
set_form_focus (FORM_ITEM **form)
{
    cur_form = *form;                   /*  To refer to the 'current' form   */
    cur_formp = form;                   /*  And its specific pointer         */
    form_use (*form);                   /*  Set fxform focus too             */
}


static void
show_form (THREAD *thread)
{
    char
        *request_end;
        
    /*  Request URL should be in the form /xxxx/filename.ext                 */
    request_end = strchr (request-> request_url + 1, '/');
    if (request_end)
        request_end = '\0';

    /*  Format #uri symbol; this lets us establish a on-going session        */
    strcpy (last_key, session_key);     /*  Save key for previous form       */
    sprintf (session_key, "%04X%04X", session_id, random (65535L));
    sprintf ((char *) buffer.data, "%s?%s", request-> request_url, session_key);
    sym_assume_symbol (symbols, "uri", (char *) buffer.data);
    sym_assume_symbol (symbols, "proto", "");
    sym_assume_symbol (symbols, "host",  "");

    /*  Format #date and #time symbols                                       */
    sym_assume_symbol (symbols, "date",
        conv_date_str (date_now (),
                       FLAG_D_CENTURY + FLAG_D_MONTH_ABC,
                       DATE_YMD_COMMA, DATE_ORDER_DMY, ' ', 20));
    sym_assume_symbol (symbols, "time",
        conv_time_str (time_now (), 0, ':', 5));

    /*  Format #config symbol for pages referring to one config file         */
    sym_assume_symbol (symbols, "config", config_file);

    /*  Format #product symbol to reflect actual Xitami product              */
    sym_assume_symbol (symbols, "product", server_name);

    /*  Format the HTML data and send it back to SMTHTTP                     */
    cur_form-> JavaScript
        = *http_config (config, "console:javascript") == '1';

    form_put (cur_form, &buffer, symbols);
    send_wsx_ok (&thread-> event-> sender, (char *) buffer.data);

    /*  Wait for next request                                                */
    if (request)
        free_smt_wsx_request (&request);

    event_wait ();
}


/*************************   CHECK SIMPLE LIVELINK   *************************/

MODULE check_simple_livelink (THREAD *thread)
{
    if (!livelink_event ())
        raise_exception (exception_event);
}


static Bool
livelink_event (void)
{
    if (streq (cur_form-> livelink, "console"))
        raise_exception (console_event);

    return (exception_raised);
}


/****************************   OPEN CONFIG LIST   ***************************/

MODULE open_config_list (THREAD *thread)
{
    config_list_form = open_form (&form_xiadm02);
}


/*************************   SHOW CONFIG LIST FIRST   ************************/

MODULE show_config_list_first (THREAD *thread)
{
    list_base = 0;
    show_configs_page (thread);
}


static void
show_configs_page (THREAD *thread)
{
    DIRST
        dir;                            /*  Directory list                   */
    int
        line_nbr;                       /*  Index into screen table          */

    line_nbr = 0;
    list_count = 0;
    set_form_focus (&config_list_form);

    if (open_dir (&dir, NULL)) do
      {
        if (file_matches (dir.file_name, "*.cfg")
        && !file_matches (dir.file_name, "xitami.cfg"))
          {
            if (list_count >= list_base && line_nbr < CONFIG_LIST_MAX)
              {
                /*  Cut filename at .cfg to hide extension (always .cfg)     */
                /*  We always show filenames in lowercase                    */
                fxputn_date (XIADM02_FILEDATE, line_nbr, timer_to_date (dir.file_time));
                fxputn_time (XIADM02_FILETIME, line_nbr, timer_to_time (dir.file_time));
                fxputn_long (XIADM02_FILESIZE, line_nbr, get_file_lines (dir.file_name));
                dir.file_name [strlen (dir.file_name) - 4] = '\0';
                strlwc (dir.file_name);
                fxputn_text (XIADM02_FILENAME, line_nbr, dir.file_name);
                line_nbr++;
              }
            list_count++;
          }
      }
    while (read_dir (&dir));
    close_dir (&dir);

    show_first_next (CONFIG_LIST_MAX);
    fxput_int (XIADM02_CONFIG_LIST, line_nbr);
    show_form (thread);
}


static void
show_first_next (int list_max)
{
    if (list_count >= list_max && list_base < list_count)
        action_enable (cur_form, next_event);
    else
        action_hide   (cur_form, next_event);

    if (list_base > 0)
        action_enable (cur_form, first_event);
    else
        action_hide   (cur_form, first_event);
}


/*************************   SHOW CONFIG LIST NEXT   *************************/

MODULE show_config_list_next (THREAD *thread)
{
    if (list_base < list_count)
        list_base += CONFIG_LIST_MAX;

    show_configs_page (thread);
}


/***********************   CHECK CONFIG LIST LIVELINK   **********************/

MODULE check_config_list_livelink (THREAD *thread)
{
    if (!livelink_event ())
      {
        if (cur_form-> click_field == XIADM02_FILENAME)
          {
            strcpy (config_file, fxgetn_text (cur_form-> click_field,
                                              cur_form-> click_index));
            raise_exception (select_config_event);
          }
        else
            raise_exception (exception_event);
      }
}


/************************   USE DEFAULTS CONFIG NAME   ***********************/

MODULE use_defaults_config_name (THREAD *thread)
{
    strcpy (config_file, "defaults");
}


/************************   USE BASEHOST CONFIG NAME   ***********************/

MODULE use_basehost_config_name (THREAD *thread)
{
    strcpy (config_file, "basehost");
}


/************************   LOAD CURRENT CONFIG FILE   ***********************/

MODULE load_current_config_file (THREAD *thread)
{
    free_config_table ();
    sprintf (config_full, "%s.cfg", config_file);
    config_table = ini_dyn_load (NULL, config_full);

    /*  Sort table by symbol name                                            */
    sym_sort_table (config_table, NULL);
}


static void
free_config_table (void)
{
    if (config_table)
      {
        sym_delete_table (config_table);
        config_table = NULL;
      }
}


/************************   SAVE CURRENT CONFIG FILE   ***********************/

MODULE save_current_config_file (THREAD *thread)
{
    if (config_table)
      {
        ini_dyn_save (config_table, config_full);
        free_config_table ();
      }
}


/***********************   CANCEL CURRENT CONFIG FILE   **********************/

MODULE cancel_current_config_file (THREAD *thread)
{
    free_config_table ();
}


/***************************   OPEN CONFIG SERVER   **************************/

MODULE open_config_server (THREAD *thread)
{
    config_server_form = open_form (&form_xiadm03);
}


/***************************   SHOW CONFIG SERVER   **************************/

MODULE show_config_server (THREAD *thread)
{
    set_form_focus (&config_server_form);

    /*  Set base config flag if in one of the two base files                 */
    if (reserved_config (config_file))
      {
        fxput_long (XIADM03_MAIN_CONFIG, 1);
        /*  Set ON_UNIX flag if we're running under UNIX                     */
#if (defined (__UNIX__))
        fxput_long (XIADM03_ON_UNIX, 1);
#else
        fxput_long (XIADM03_ON_UNIX, 0);
#endif
#if (defined (WIN32))
        fxput_long (XIADM03_ON_WINDOWS_32, 1);
#else
        fxput_long (XIADM03_ON_WINDOWS_32, 0);
#endif
      }
    else
      {
        fxput_long (XIADM03_MAIN_CONFIG,   0);
        fxput_long (XIADM03_ON_UNIX,       0);
        fxput_long (XIADM03_ON_WINDOWS_32, 0);
      }
    put_values ("server", server_fields);
    show_pipes (config_table, "server:pipe", XIADM03_PIPE, XIADM03_L_PIPE);
    show_form  (thread);
}


static Bool
reserved_config (char *config_file)
{
    return (streq (config_file, "xitami") || streq (config_file, "defaults"));
}


static void
put_values (const char *prefix, FIELDREF *fields)
{
    int
        index,                          /*  Index into field table           */
        field;                          /*  Field number on form             */
    char
        attr,                           /*  Label attribute                  */
        *value;                         /*  Field value on form              */

    for (index = 0; fields [index].number; index++)
      {
        set_config_key (prefix, fields [index].name);
        field = fields [index].number;
        value = CONFVAL (config_key);
        fxput_text (field, value);
        if (fields [index].label)
          {
            if (is_default (config_key, value, form_ftype (cur_form, field)))
                attr = FATTR_LABEL;
            else
                attr = FATTR_TITLE;

            fxattr_put (fields [index].label, 0, attr);
          }
      }
}


static void
set_config_key (const char *prefix, const char *name)
{
    if (strchr (name, ':'))
        strcpy (config_key, name);
    else
        sprintf (config_key, "%s:%s", prefix, name);
}


static Bool
is_default (const char *key, const char *value, int type)
{
    Bool
        same_as_default = TRUE;

    switch (type)
      {
        case BLOCK_NUMERIC:
        case BLOCK_DATE:
        case BLOCK_BOOLEAN:
        case BLOCK_SELECT:
        case BLOCK_RADIO:
            same_as_default = atol (value) == atol (DEFTVAL (key));
            break;
        case BLOCK_TEXTUAL:
        case BLOCK_TEXTBOX:
            same_as_default = streq (value, DEFTVAL (key));
            break;
      }
    return (same_as_default);
}

static void
show_pipes (SYMTAB *table, char *key, int field, int label)
{
    XML_ITEM
        *pipes,                         /*  List of throttle pipes           */
        *pipe,                          /*  XML pipe item                    */
        *instance;                      /*  XML instance item                */
    char
        *name;                          /*  Pipe instance name               */

    pipes = NULL;
    switch (xml_load_file (&pipes, "PATH", "pipedef.xml", FALSE))
      {
        case XML_NOERROR:
            fxlist_reset  (field, 0);
            fxlist_append (field, 0, "", "- no throttle -");
            FORCHILDREN (pipe, xml_first_child (pipes))
              {
                FORCHILDREN (instance, pipe)
                  {
                    name = xml_get_attr (instance, "NAME", NULL);
                    if (!name)
                        continue;           /*  Ignore if no name defined        */
                    fxlist_append (field, 0, name, name);
                  }
              }
            if (key)
                fxlist_set (field, 0, http_config (table, key));

            if (label)    
                if (streq (http_config (table, key), DEFTVAL (key)))
                    fxattr_put (label, 0, FATTR_LABEL);
                else
                    fxattr_put (label, 0, FATTR_TITLE);
    
            xml_free (pipes);
            break;
        case XML_FILEERROR:
            fxput_text (MESSAGE_TO_USER, "'pipedef.xml' is not readable");
            break;
        case XML_LOADERROR:
            fxput_text (MESSAGE_TO_USER, "Syntax error in 'pipedef.xml'");
            break;
      }
}


/**************************   UPDATE CONFIG SERVER   *************************/

MODULE update_config_server (THREAD *thread)
{
    get_values ("server", server_fields);
    update_value ("server", "pipe", fxlist_key (XIADM03_PIPE, 0), 0);
}


static void
get_values (const char *prefix, FIELDREF *fields)
{
    int
        index;

    for (index = 0; fields [index].number; index++)
        if (fxattr_get (fields [index].number, 0) == FATTR_INPUT)
            update_value (prefix,
                          fields [index].name,
                          fxget_text (fields [index].number),
                          fields [index].number);
}


/*  Updates a field in the config_table, or deletes it if default            */

static void
update_value (
    const char *prefix,
    const char *name,
    const char *value,
    int         field)
{
    SYMBOL
        *symbol;
    int
        type;

    /*  Try to get field type from form, if possible                         */
    if (field > 0)
        type = form_ftype (cur_form, field);
    else
        type = BLOCK_TEXTUAL;           /*  Assume text if not specified     */
        
    set_config_key (prefix, name);
    if (is_default (config_key, value, type))
      {
        symbol = sym_lookup_symbol (config_table, config_key);
        if (symbol)
            sym_delete_symbol (config_table, symbol);
      }
    else
      {
        /*  Skip leading zeroes in number                                    */
        if (type  == BLOCK_NUMERIC)
            while (value [0] == '0' && value [1] != '\0')
                value++;
        sym_assume_symbol (config_table, config_key, value);
      }
}


/**********************   SHOW CONFIG SERVER DEFAULTS   **********************/

MODULE show_config_server_defaults (THREAD *thread)
{
    set_form_focus (&config_server_form);
    put_defaults ("server", server_fields);
    show_form (thread);
}


static void
put_defaults (const char *prefix, FIELDREF *fields)
{
    int
        index;

    for (index = 0; fields [index].number; index++)
      {
        set_config_key (prefix, fields [index].name);
        fxput_text (fields [index].number, DEFTVAL (config_key));
        if (fields [index].label)
            fxattr_put (fields [index].label, 0, FATTR_LABEL);
      }
}


/**************************   OPEN CONFIG ADVANCED   *************************/

MODULE open_config_advanced (THREAD *thread)
{
    config_advanced_form = open_form (&form_xiadm31);
}


/**************************   SHOW CONFIG ADVANCED   *************************/

MODULE show_config_advanced (THREAD *thread)
{
    set_form_focus (&config_advanced_form);

    /*  Set base config flag if in one of the two base files                 */
    if (reserved_config (config_file))
        fxput_long (XIADM31_MAIN_CONFIG, 1);
    else
        fxput_long (XIADM31_MAIN_CONFIG, 0);

    put_values ("server", advanced_fields);

    show_ipaddr_list (config_table, "server:ipaddress", 
                      XIADM31_IPADDRESS, XIADM31_L_IPADDRESS);
    show_form (thread);
}

/*  Show ipaddress list and indicate whether we're showing the default       */

static void
show_ipaddr_list (SYMTAB *table, char *key, int field, int label)
{
    qbyte
        *address;                       /*  Address table, ends in zero      */
    int
        index;                          /*  Index into the table             */
    char
        *dotted;                        /*  Address in dotted format         */

    /*  Format list of system IP addresses                                   */
    fxlist_reset  (field, 0);
    fxlist_append (field, 0, "*", "All addresses (recommended)");
    address = get_hostaddrs ();
    if (address)
        for (index = 0; address [index]; index++)
          {
            dotted = sock_ntoa (address [index]);
            fxlist_append (field, 0, dotted, dotted);
          }
    fxlist_append (field, 0, "127.0.0.1", "127.0.0.1");
    if (key)
        fxlist_set (field, 0, http_config (table, key));

    if (label)    
        if (streq (http_config (table, key), DEFTVAL (key)))
            fxattr_put (label, 0, FATTR_LABEL);
        else
            fxattr_put (label, 0, FATTR_TITLE);
    
    mem_free (address);
}



/*************************   UPDATE CONFIG ADVANCED   ************************/

MODULE update_config_advanced (THREAD *thread)
{
    get_values ("server", advanced_fields);
    update_ipaddress ("server:ipaddress", XIADM31_IPADDRESS);
}


static void 
update_ipaddress (char *key, int field)
{
    char
        *ipaddress;
    SYMBOL
        *symbol;

    ipaddress = fxlist_key (field, 0);
    if (strnull (ipaddress))
        ipaddress = "*";                /*  Option zero is 'any address'     */

    if (streq (ipaddress, DEFTVAL (key)))
      {
        symbol = sym_lookup_symbol (config_table, key);
        if (symbol)
            sym_delete_symbol (config_table, symbol);
      }
    else
        sym_assume_symbol (config_table, key, ipaddress);
}


/*********************   SHOW CONFIG ADVANCED DEFAULTS   *********************/

MODULE show_config_advanced_defaults (THREAD *thread)
{
    set_form_focus (&config_advanced_form);
    put_defaults ("server", advanced_fields);
    fxlist_set   (XIADM31_IPADDRESS, 0, DEFTVAL ("server:ipaddress"));
    show_form (thread);
}


/****************************   TEST URL MAPPING   ***************************/

MODULE test_url_mapping (THREAD *thread)
{
    char
        *mapped_uri;

    mapped_uri = MAPURI (fxget_text (XIADM31_TEST_URI));
    fxput_text (XIADM31_MAPPED_URI, mapped_uri);
    mem_strfree (&mapped_uri);
}


/***************************   OPEN CONFIG ERRORS   **************************/

MODULE open_config_errors (THREAD *thread)
{
    config_errors_form = open_form (&form_xiadm10);
}


/***************************   SHOW CONFIG ERRORS   **************************/

MODULE show_config_errors (THREAD *thread)
{
    set_form_focus (&config_errors_form);
    put_values ("server", error_fields);
    show_form (thread);
}
                                              

/**************************   UPDATE CONFIG ERRORS   *************************/

MODULE update_config_errors (THREAD *thread)
{
    get_values ("server", error_fields);
}


/**********************   SHOW CONFIG ERRORS DEFAULTS   **********************/

MODULE show_config_errors_defaults (THREAD *thread)
{
    put_defaults ("server", error_fields);
    show_form (thread);
}


/****************************   OPEN CONFIG DDNS   ***************************/

MODULE open_config_ddns (THREAD *thread)
{
    config_ddns_form = open_form (&form_xiadm30);
}


/****************************   SHOW CONFIG DDNS   ***************************/

MODULE show_config_ddns (THREAD *thread)
{
    set_form_focus (&config_ddns_form);
    put_values ("ddns", ddns_fields);
    show_ddns_services (config_table);
    show_form (thread);
}

static void
show_ddns_services (SYMTAB *table)
{
    XML_ITEM
        *services,                      /*  List of DDNS services            */
        *service;
    char
        *name,                          /*  Server name and title            */
        *title;                         /*    from ddnsdef.xml file          */

    services = NULL;

    switch (xml_load_file (&services, "PATH", "ddnsdef.xml", FALSE))
      {
        case XML_NOERROR:
            fxlist_reset (XIADM30_SERVICE, 0);
            FORCHILDREN (service, xml_first_child (services))
              {
                name  = xml_get_attr (service, "NAME",  NULL);
                title = xml_get_attr (service, "TITLE", NULL);
                if (!name)
                    continue;               /*  Ignore if no name defined        */
                if (!title)
                    title = name;
                fxlist_append (XIADM30_SERVICE, 0, name, title);
              }
            fxlist_set (XIADM30_SERVICE, 0, http_config (table, "ddns:service"));
            xml_free (services);
            break;
        case XML_FILEERROR:
            fxput_text (MESSAGE_TO_USER, "'ddnsdef.xml' is not readable");
            break;
        case XML_LOADERROR:
            fxput_text (MESSAGE_TO_USER, "Syntax error in 'ddnsdef.xml'");
            break;
      }
}


/***************************   UPDATE CONFIG DDNS   **************************/

MODULE update_config_ddns (THREAD *thread)
{
    get_values ("ddns", ddns_fields);
    update_value ("ddns", "service", fxlist_key (XIADM30_SERVICE, 0), 0);
}


/***********************   SEND SIGNON TO DDNS AGENT   ***********************/

MODULE send_signon_to_ddns_agent (THREAD *thread)
{
    send_ddns_method ("SIGNON");
}

static void
send_ddns_method (char *method)
{
    THREAD
        *ddns_thread;
        
    if ((ddns_thread = thread_lookup ("XIDDNS", "main")) != NULL)
      {
        sendfmt (&ddns_thread-> queue-> qid, method, "");
        fxput_text (MESSAGE_TO_USER, "In progress - check console messages");
      }
    else
        fxput_text (MESSAGE_TO_USER,
                    "DDNS agent not running - enable it and restart Xitami");
}


/***********************   SEND SIGNOFF TO DDNS AGENT   **********************/

MODULE send_signoff_to_ddns_agent (THREAD *thread)
{
    send_ddns_method ("SIGNOFF");
}


/***********************   SHOW CONFIG DDNS DEFAULTS   ***********************/

MODULE show_config_ddns_defaults (THREAD *thread)
{
    put_defaults ("ddns", ddns_fields);
    show_ddns_services (config_table);
    show_form (thread);
}


/**************************   OPEN CONFIG ALIASES   **************************/

MODULE open_config_aliases (THREAD *thread)
{
    config_aliases_form = open_form (&form_xiadm04);
    set_form_focus (&config_aliases_form);

    list_prefix = "alias:";
    list_max    = ALIAS_LIST_MAX;
    list_key    = XIADM04_KEY;
    list_name   = XIADM04_ALIAS_NAME;
    list_value  = XIADM04_ALIAS_PATH;
    list_index  = XIADM04_ALIAS_LIST;
    list_table  = config_table;
}


/****************************   OPEN CONFIG SSI   ****************************/

MODULE open_config_ssi (THREAD *thread)
{
    config_ssi_form = open_form (&form_xiadm28);
}


/****************************   SHOW CONFIG SSI   ****************************/

MODULE show_config_ssi (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in config table           */
    int
        ext_nbr = 0;                    /*  Index into screen table          */
    Bool
        in_defaults = TRUE;             /*  Show defaults after main         */
    char
        attr;                           /*  Attribute on screen              */

    set_form_focus (&config_ssi_form);
    put_values ("ssi", ssi_fields);

    /*  Show file extensions used for xixssi WSX agent                       */
    symbol = defaults-> symbols;
    while (symbol)
      {
        if (strprefixed (symbol-> name,  "wsx")
        &&  streq       (symbol-> value, "xixssi")
        &&  ext_nbr < tblsize (ext_field))
          {
            attr = in_defaults? FATTR_LABEL: FATTR_INPUT;
            fxput_text (ext_field [ext_nbr], symbol-> name + 4);
            fxattr_put (ext_field [ext_nbr], 0, attr);
            ext_nbr++;
          }        
        symbol = symbol-> next;
        if (symbol == NULL && in_defaults)
          {
            symbol = config_table-> symbols;
            in_defaults = FALSE;
          }
       }
    show_form (thread);
}


/***************************   UPDATE CONFIG SSI   ***************************/

MODULE update_config_ssi (THREAD *thread)
{
    SYMBOL
        *symbol,                        /*  Symbol in config table           */
        *nextsym;
    int
        ext_nbr;                        /*  Index into screen table          */
    char
        *extension;                     /*  Extension on screen              */

    get_values ("ssi", ssi_fields);

    /*  First delete all xixssi WSX definitions in config                    */
    for (symbol = config_table-> symbols; symbol; symbol = symbol-> next)
      {
        if (strprefixed (symbol-> name,  "wsx")
        &&  streq       (symbol-> value, "xixssi"))
          {
            nextsym = symbol-> next;
            sym_delete_symbol (config_table, symbol);
            symbol = nextsym;
          }
      }
    /*  Save user-defined extensions                                         */
    for (ext_nbr = 0; ext_nbr < tblsize (ext_field); ext_nbr++)
      {
        extension = fxget_text (ext_field [ext_nbr]);
        if (fxattr_get (ext_field [ext_nbr], 0) == FATTR_INPUT
        &&  *extension)
          {
            extension = fxget_text (ext_field [ext_nbr]);
            set_config_key ("wsx", extension);
            sym_assume_symbol (config_table, config_key, "xixssi");
          }
      }
}


/************************   SHOW CONFIG SSI DEFAULTS   ***********************/

MODULE show_config_ssi_defaults (THREAD *thread)
{
    put_defaults ("ssi", ssi_fields);
    show_form (thread);
}


/***************************   OPEN CONFIG MIMES   ***************************/

MODULE open_config_mimes (THREAD *thread)
{
    config_mimes_form = open_form (&form_xiadm09);
    set_form_focus (&config_mimes_form);

    list_prefix = "mime:";
    list_max    = MIME_LIST_MAX;
    list_key    = XIADM09_KEY;
    list_name   = XIADM09_MIME_EXT;
    list_value  = XIADM09_MIME_TYPE;
    list_index  = XIADM09_MIME_LIST;
    list_table  = config_table;
}


/****************************   OPEN CONFIG WSX   ****************************/

MODULE open_config_wsx (THREAD *thread)
{
    config_wsx_form = open_form (&form_xiadm15);
    set_form_focus (&config_wsx_form);

    list_prefix = "wsx:";
    list_max    = WSX_LIST_MAX;
    list_key    = XIADM15_KEY;
    list_name   = XIADM15_WSX_ALIAS;
    list_value  = XIADM15_WSX_AGENT;
    list_index  = XIADM15_WSX_LIST;
    list_table  = config_table;
}


/***************************   OPEN CONFIG FILTER   **************************/

MODULE open_config_filter (THREAD *thread)
{
    config_filter_form = open_form (&form_xiadm20);
    set_form_focus (&config_filter_form);

    list_prefix = "filter:";
    list_max    = FILTER_LIST_MAX;
    list_key    = XIADM20_KEY;
    list_name   = XIADM20_FILTER_ALIAS;
    list_value  = XIADM20_FILTER_AGENT;
    list_index  = XIADM20_FILTER_LIST;
    list_table  = config_table;
}


/***************************   OPEN CONFIG VHOSTS   **************************/

MODULE open_config_vhosts (THREAD *thread)
{
    config_vhosts_form = open_form (&form_xiadm05);
    set_form_focus (&config_vhosts_form);

    list_prefix = "virtual-hosts:";
    list_max    = VHOST_LIST_MAX;
    list_key    = XIADM05_KEY;
    list_name   = XIADM05_VHOST_NAME;
    list_value  = XIADM05_VHOST_FILE;
    list_index  = XIADM05_VHOST_LIST;
    list_table  = config_table;
}


/****************************   OPEN CONFIG CGI   ****************************/

MODULE open_config_cgi (THREAD *thread)
{
    config_cgi_form = open_form (&form_xiadm06);
}


/****************************   SHOW CONFIG CGI   ****************************/

MODULE show_config_cgi (THREAD *thread)
{
    set_form_focus (&config_cgi_form);

    /*  Set Win32 flag if we're running under Windows 32                     */
#if (defined (WIN32))
    fxput_long (XIADM06_ON_WINDOWS_32, 1);
#else
    fxput_long (XIADM06_ON_WINDOWS_32, 0);
#endif

    put_values ("cgi", cgi_fields);
    show_form (thread);
}


/***************************   UPDATE CONFIG CGI   ***************************/

MODULE update_config_cgi (THREAD *thread)
{
    get_values ("cgi", cgi_fields);
}


/************************   SHOW CONFIG CGI DEFAULTS   ***********************/

MODULE show_config_cgi_defaults (THREAD *thread)
{
    put_defaults ("cgi", cgi_fields);
    show_form (thread);
}


/**************************   OPEN CONFIG SECURITY   *************************/

MODULE open_config_security (THREAD *thread)
{
    config_security_form = open_form (&form_xiadm07);
}


/**************************   SHOW CONFIG SECURITY   *************************/

MODULE show_config_security (THREAD *thread)
{
    set_form_focus (&config_security_form);

    /*  Set Win32 flag if we're running under Windows 32                     */
#if (defined (WIN32))
    fxput_long (XIADM07_ON_WINDOWS_32, 1);
#else
    fxput_long (XIADM07_ON_WINDOWS_32, 0);
#endif
    /*  Set ON_UNIX flag if we're running under UNIX                         */
#if (defined (__UNIX__))
    fxput_long (XIADM07_ON_UNIX, 1);
#else
    fxput_long (XIADM07_ON_UNIX, 0);
#endif

    put_values ("security", security_fields);
    show_form (thread);
}


/*************************   UPDATE CONFIG SECURITY   ************************/

MODULE update_config_security (THREAD *thread)
{
    get_values ("security", security_fields);
}


/*********************   SHOW CONFIG SECURITY DEFAULTS   *********************/

MODULE show_config_security_defaults (THREAD *thread)
{
    put_defaults ("security", security_fields);
    show_form (thread);
}


/**************************   OPEN CONFIG LOGGING   **************************/

MODULE open_config_logging (THREAD *thread)
{
    config_logging_form = open_form (&form_xiadm08);
}


/**************************   SHOW CONFIG LOGGING   **************************/

MODULE show_config_logging (THREAD *thread)
{
    set_form_focus (&config_logging_form);
    put_values ("", logging_fields);

    /*  Set base config flag if in one of the two base files                 */
    fxput_bool (XIADM08_MAIN_CONFIG, reserved_config (config_file));

    show_form (thread);
}


/*************************   UPDATE CONFIG LOGGING   *************************/

MODULE update_config_logging (THREAD *thread)
{
    get_values ("", logging_fields);
}


/**********************   SHOW CONFIG LOGGING DEFAULTS   *********************/

MODULE show_config_logging_defaults (THREAD *thread)
{
    put_defaults ("", logging_fields);
    show_form (thread);
}


/**************************   OPEN CONFIG LOG FILE   *************************/

MODULE open_config_log_file (THREAD *thread)
{
    config_log_file_form = open_form (&form_xiadm29);
}


/***************************   CHOOSE SERVER LOG   ***************************/

MODULE choose_server_log (THREAD *thread)
{
    fxput_text (XIADM29_LOG_TYPE, "Server messages");
    rich_logging = FALSE;
    log_prefix = "serverlog";
}


/*************************   CHOOSE HTTP ACCESS LOG   ************************/

MODULE choose_http_access_log (THREAD *thread)
{
    fxput_text (XIADM29_LOG_TYPE, "HTTP accesses");
    rich_logging = TRUE;
    log_prefix = "accesslog";
}


/*************************   CHOOSE HTTP ERROR LOG   *************************/

MODULE choose_http_error_log (THREAD *thread)
{
    fxput_text (XIADM29_LOG_TYPE, "HTTP errors");
    rich_logging = TRUE;
    log_prefix = "errorlog";
}


/*************************   CHOOSE FTP ACCESS LOG   *************************/

MODULE choose_ftp_access_log (THREAD *thread)
{
    fxput_text (XIADM29_LOG_TYPE, "FTP accesses");
    rich_logging = TRUE;
    log_prefix = "ftplog";
}


/**************************   CHOOSE FTP ERROR LOG   *************************/

MODULE choose_ftp_error_log (THREAD *thread)
{
    fxput_text (XIADM29_LOG_TYPE, "FTP errors");
    rich_logging = TRUE;
    log_prefix = "ftperrlog";
}


/*************************   SHOW LOG FILE DETAILS   *************************/

MODULE show_log_file_details (THREAD *thread)
{
    set_form_focus (&config_log_file_form);
    put_values (log_prefix, log_file_fields);
    show_log_cycle (config_table);
    if (rich_logging)
      {
        show_log_format (config_table);
        show_log_custom (config_table);
      }
    fxput_bool (XIADM29_RICH_LOGGING, rich_logging);

    show_form (thread);
}

static void
show_log_cycle (SYMTAB *table)
{
    char
        *cycle;

    fxlist_reset  (XIADM29_CYCLE, 0);
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_STARTUP, "When starting the server");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_HOURLY,  "Every hour at mm minutes");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_DAILY,   "Every day at hh:mm");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_WEEKLY,  "Every week at dd:hh:mm");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_MONTHLY, "Every month at dd:hh:mm");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_SIZE,    "When log file exceeds X Kb");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_LINES,   "When log file exceeds X lines");
    fxlist_append (XIADM29_CYCLE, 0, XI_CYCLE_MANUAL,  "Manual cycling only");

    set_config_key (log_prefix, "cycle");
    cycle = http_config (table, config_key);

    /*  Convert pre-2.5 numeric cycle codes into keywords                    */
    if (streq (cycle, "0"))
        cycle = XI_CYCLE_STARTUP;  
    else
    if (streq (cycle, "1"))
        cycle = XI_CYCLE_HOURLY;   
    else
    if (streq (cycle, "2"))
        cycle = XI_CYCLE_DAILY;    
    else
    if (streq (cycle, "3"))
        cycle = XI_CYCLE_WEEKLY;   
    else
    if (streq (cycle, "4"))
        cycle = XI_CYCLE_MONTHLY;  
    else
    if (streq (cycle, "5"))
        cycle = XI_CYCLE_MANUAL;   
    else
    if (streq (cycle, "6"))
        cycle = XI_CYCLE_SIZE;     
    else
    if (streq (cycle, "7"))
        cycle = XI_CYCLE_LINES;    
        
    fxlist_set (XIADM29_CYCLE, 0,  cycle);
}


static void
show_log_format (SYMTAB *table)
{
    fxlist_reset  (XIADM29_FORMAT, 0);
    fxlist_append (XIADM29_FORMAT, 0, "CLF",    "NCSA common logging format (basic)");
    fxlist_append (XIADM29_FORMAT, 0, "CLFX",   "NCSA common logging format (extended)");
    fxlist_append (XIADM29_FORMAT, 0, "MS",     "Microsoft IIS format");
    fxlist_append (XIADM29_FORMAT, 0, "LML",    "Xitami Logging Markup Language (LML)");
    fxlist_append (XIADM29_FORMAT, 0, "XLML",   "Xitami Extended LML");
    fxlist_append (XIADM29_FORMAT, 0, "custom", "Custom-defined format");

    set_config_key (log_prefix, "format");
    fxlist_set (XIADM29_FORMAT, 0, http_config (table, config_key));
}

static void show_log_custom (SYMTAB *table)
{
    char
        *text_block;
        
    set_config_key (log_prefix, "custom");
    text_block = strreformat (http_config (table, config_key), CUSTOM_WIDTH, "");
    fxput_text (XIADM29_CUSTOM, text_block);
    mem_free (text_block);
}



/**************************   SHOW LOG FILE FORMAT   *************************/

MODULE show_log_file_format (THREAD *thread)
{
    char
        *text_block,
        *format;

    /*  Show details for logging format if not custom format                 */
    format = fxlist_key (XIADM29_FORMAT, 0);
    if (lexcmp (format, "CLF") == 0)
        format = LOG_FORMAT_CLF;
    else
    if (lexcmp (format, "CLFX") == 0)
        format = LOG_FORMAT_CLFX;
    else
    if (lexcmp (format, "MS") == 0)
        format = LOG_FORMAT_MS;
    else
    if (lexcmp (format, "LML") == 0)
        format = LOG_FORMAT_LML;
    else
    if (lexcmp (format, "XLML") == 0)
        format = LOG_FORMAT_XLML;
    else
        format = NULL;

    if (format)
      {
        text_block = strreformat (format, CUSTOM_WIDTH, "");
        fxput_text (XIADM29_CUSTOM, text_block);
        mem_free (text_block);
      }
    show_form (thread);
}


/************************   UPDATE LOG FILE DETAILS   ************************/

MODULE update_log_file_details (THREAD *thread)
{
    get_values (log_prefix, log_file_fields);
    update_value (log_prefix, "cycle", fxlist_key (XIADM29_CYCLE, 0), 0); 
    if (rich_logging)
      {
        update_value (log_prefix, "format", fxlist_key (XIADM29_FORMAT, 0), 0);
        update_log_custom ();
      }
}


static void 
update_log_custom (void)
{
    char
        *custom;
     
    custom = fxget_text (XIADM29_CUSTOM);
    strconvch (custom, '\n', ' ');
    update_value (log_prefix, "custom", custom, 0);
}



/*************************   SHOW LOG FILE DEFAULTS   ************************/

MODULE show_log_file_defaults (THREAD *thread)
{
    put_defaults (log_prefix, log_file_fields);
    show_log_cycle (defaults);
    if (rich_logging)
      {
        show_log_format (defaults);
        show_log_custom (defaults);
      }
    show_form (thread);
}


/***********************   CYCLE LOG FILE IF POSSIBLE   **********************/

MODULE cycle_log_file_if_possible (THREAD *thread)
{
    QID
        *logq;

    logq = lookup_log_queue ();
    if (logq)
      {
        send_cycle (logq);
        fxput_text (MESSAGE_TO_USER, "Active log file has been cycled");
      }
    show_form (thread);
}

static QID *
lookup_log_queue (void)
{
    char
        *filename;
    THREAD
        *log_thread;                    /*  Log thread                       */

    filename = file_where ('s', CONFVAL ("server:log-dir"),
                           fxget_text (XIADM29_FILENAME), NULL);

    log_thread = thread_lookup (XIXLOG_AGENT, filename);
    if (log_thread == NULL)
      {
        fxput_text (MESSAGE_TO_USER, "Log file is not active");
        return (NULL);
      }
    else
        return (&log_thread-> queue-> qid);
}


/***********************   CLEAR LOG FILE IF POSSIBLE   **********************/

MODULE clear_log_file_if_possible (THREAD *thread)
{
    QID
        *logq;

    logq = lookup_log_queue ();
    if (logq)
      {
        send_clear (logq);
        fxput_text (MESSAGE_TO_USER, "Active log file has been emptied");
      }
    show_form (thread);
}


/*************************   OPEN CONFIG CGI ENVIR   *************************/

MODULE open_config_cgi_envir (THREAD *thread)
{
    config_cgi_envir_form = open_form (&form_xiadm11);
    set_form_focus (&config_cgi_envir_form);

    list_prefix = "cgi-environment:";
    list_max    = CGI_ENVIR_LIST_MAX;
    list_key    = XIADM11_KEY;
    list_name   = XIADM11_CGI_ENVIR_NAME;
    list_value  = XIADM11_CGI_ENVIR_VALUE;
    list_index  = XIADM11_CGI_ENVIR_LIST;
    list_table  = config_table;
}


/*************************   OPEN CONFIG CGI ALIAS   *************************/

MODULE open_config_cgi_alias (THREAD *thread)
{
    config_cgi_alias_form = open_form (&form_xiadm14);
    set_form_focus (&config_cgi_alias_form);

    list_prefix = "cgi-alias:";
    list_max    = CGI_ALIAS_LIST_MAX;
    list_key    = XIADM14_KEY;
    list_name   = XIADM14_CGI_ALIAS_NAME;
    list_value  = XIADM14_CGI_ALIAS_PATH;
    list_index  = XIADM14_CGI_ALIAS_LIST;
    list_table  = config_table;
}


/**********************   SHOW CONFIG VALUE LIST FIRST   *********************/

MODULE show_config_value_list_first (THREAD *thread)
{
    list_base = 0;
    show_list_page (thread);
}

static void
show_list_page (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in config table           */
    int
        line_nbr;                       /*  Index into screen table          */
    char
        attr,                           /*  Attribute on screen              */
        *key_value;                     /*  Key for each item on the list    */
    Bool
        in_defaults = TRUE;             /*  Show defaults after main         */
                  
    /*  We always show a full page, possibly with blank entries              */
    fxput_int (list_index, list_max);

    line_nbr   = 0;
    list_count = 0;
    symbol = defaults-> symbols;
    while (symbol)
      {
        if (strprefixed (symbol-> name, list_prefix))
          {
            if (list_count >= list_base && line_nbr < list_max)
              {
                key_value = symbol-> name + strlen (list_prefix);
                fxputn_text (list_key,   line_nbr, key_value);
                fxputn_text (list_name,  line_nbr, key_value);
                fxputn_text (list_value, line_nbr, symbol-> value);

                attr = in_defaults? FATTR_LABEL: FATTR_INPUT;
                fxattr_put (list_name,  line_nbr, attr);
                fxattr_put (list_value, line_nbr, attr);

                line_nbr++;
              }
            list_count++;               /*  Actual number of configs         */
          }
        symbol = symbol-> next;
        if (symbol == NULL && in_defaults)
          {
            symbol = list_table-> symbols;
            in_defaults = FALSE;
          }
       }
    /*  Clear unused lines                                                   */
    for (; line_nbr < list_max; line_nbr++)
      {
        fxputn_text (list_key,   line_nbr, "");
        fxputn_text (list_name,  line_nbr, "");
        fxputn_text (list_value, line_nbr, "");
        fxattr_put  (list_name,  line_nbr, FATTR_INPUT);
        fxattr_put  (list_value, line_nbr, FATTR_INPUT);
      }
    /*  Show/hide function keys as appropriate                               */
    show_first_next (list_max);
    show_form (thread);
}


/**********************   SHOW CONFIG VALUE LIST NEXT   **********************/

MODULE show_config_value_list_next (THREAD *thread)
{
    if (list_base < list_count)
        list_base += list_max;

    show_list_page (thread);
}


/************************   CLEAR CONFIG VALUE LIST   ************************/

MODULE clear_config_value_list (THREAD *thread)
{
    int
        line_nbr;                       /*  Index into screen table          */

    for (line_nbr = 0; line_nbr < list_max; line_nbr++)
      {
        if (fxattr_get (list_name, line_nbr) == FATTR_INPUT)
          {
            fxputn_text (list_name,  line_nbr, "");
            fxputn_text (list_value, line_nbr, "");
          }  
      }
}


/***********************   VALIDATE CONFIG VALUE LIST   **********************/

MODULE validate_config_value_list (THREAD *thread)
{
    int
        line_nbr;                       /*  Index into screen table          */

    /*  Validations:
     *  Value must be filled if name is not empty
     */
    for (line_nbr = 0; line_nbr < list_max; line_nbr++)
      {
        if (*fxgetn_text (list_name, line_nbr)
        && !*fxgetn_text (list_value, line_nbr))
          {
            SET_ERRORN (list_value, line_nbr);
            fxput_text (MESSAGE_TO_USER, "Value must be supplied");
            raise_exception (exception_event);
          }
      }
}


/************************   UPDATE CONFIG VALUE LIST   ***********************/

MODULE update_config_value_list (THREAD *thread)
{
    int
        line_nbr;                       /*  Index into screen table          */
    char
        *old_key,                       /*  Hidden key at display time       */
        *new_key,                       /*  Key now on screen                */
        *value;                         /*  Value on screen                  */
    SYMBOL
        *symbol;                        /*  Symbol in config table           */

    for (line_nbr = 0; line_nbr < list_max; line_nbr++)
      {
        old_key = fxgetn_text (list_key,   line_nbr);
        new_key = fxgetn_text (list_name,  line_nbr);
        value   = fxgetn_text (list_value, line_nbr);

        /*  Update algorithm:
         *  - if line is not open, do nothing
         */
        if (fxattr_get (list_name, line_nbr) != FATTR_INPUT)
            ;
        else
        /*  - update entry if old key = new key and not empty
         */
        if (*new_key && streq (old_key, new_key))
          {
            sprintf (config_key, "%s%s", list_prefix, old_key);
            sym_assume_symbol (list_table, config_key, value);
          }
        else
          {
            /* - insert entry with new key, if new key is not empty          */
            if (strused (new_key))
              {
                sprintf (config_key, "%s%s", list_prefix, new_key);
                if (sym_lookup_symbol (list_table, config_key))
                  {
                    SET_ERRORN (list_name, line_nbr);
                    fxput_text (MESSAGE_TO_USER, "Value already exists");
                    raise_exception (exception_event);
                  }
                else
                    sym_assume_symbol (list_table, config_key, value);
              }
            /* - delete entry with old key, if old key was not empty         */
            if (!exception_raised)
              {
                if (strused (old_key))
                  {
                    sprintf (config_key, "%s%s", list_prefix, old_key);
                    symbol = sym_lookup_symbol (list_table, config_key);
                    ASSERT (symbol);
                    sym_delete_symbol (list_table, symbol);
                  }
                fxputn_text (list_key, line_nbr, new_key);
              }
          }
      }
}


/*************************   OPEN CONFIG RESOURCES   *************************/

MODULE open_config_resources (THREAD *thread)
{
    strcpy (passwd_file, fxget_text (XIADM07_FILENAME));
    if (strnull (passwd_file))
      {
        SET_ERROR (XIADM07_FILENAME);
        fxput_text (MESSAGE_TO_USER, "Supply password file name");
        raise_exception (exception_event);
      }
    else
      {
        free_passwd_table ();
        passwd_table = ini_dyn_load (NULL, passwd_file);
        config_resource_form = open_form (&form_xiadm12);
      }
}


static void
free_passwd_table (void)
{
    if (passwd_table)
      {
        sym_delete_table (passwd_table);
        passwd_table = NULL;
      }
}


/**********************   SHOW CONFIG RESOURCES FIRST   **********************/

MODULE show_config_resources_first (THREAD *thread)
{
    list_base = 0;
    show_resource_page (thread);
}


static void
show_resource_page (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in password table         */
    int
        user_count,                     /*  Number of users for resource     */
        line_nbr;                       /*  Index into screen table          */
    char
        *value,                         /*  Split symbol name:value          */
        *mapped_uri;

    line_nbr   = 0;
    list_count = 0;

    set_form_focus (&config_resource_form);
    sym_sort_table (passwd_table, NULL);
    symbol = passwd_table-> symbols;
    while (symbol)
      {
        /*  Look for start of section: name with no value                    */
        if (symbol-> value && *symbol-> value)
          {
            symbol = symbol-> next;
            continue;
          }
        strcpy  (resource_name, symbol-> name);
        xstrcpy (resource_full, symbol-> name, ":", NULL);
        symbol = symbol-> next;

        /*  Now go through this section                                      */
        user_count = 0;
        strclr (webmask);
        strclr (realm);
        while (symbol && strprefixed (symbol-> name, resource_full))
          {
            value = symbol-> name + strlen (resource_full);
            if (streq (value, "webmask"))
              {
                strncpy (webmask, symbol-> value, WEBMASK_SIZE);
                webmask [WEBMASK_SIZE] = 0;
              }
            else
            if (streq (value, "realm"))
              {
                strncpy (realm, symbol-> value, REALM_SIZE);
                realm [REALM_SIZE] = 0;
              }
            else
                user_count++;

            symbol = symbol-> next;
          }
        /*  Display what we got, if we're within the list                    */
        if (list_count >= list_base && line_nbr < RESOURCE_LIST_MAX)
          {
            mapped_uri = MAPURI (resource_name);
            fxputn_text (XIADM12_URI_NAME,  line_nbr, resource_name);
            fxputn_text (XIADM12_URI_PATH,  line_nbr, mapped_uri);
            fxputn_text (XIADM12_WEBMASK,   line_nbr, webmask);
            fxputn_text (XIADM12_REALM,     line_nbr, realm);
            fxputn_int  (XIADM12_URI_USERS, line_nbr, user_count);
            mem_strfree (&mapped_uri);
            line_nbr++;
          }
        list_count++;
       }
    show_first_next (RESOURCE_LIST_MAX);

    fxput_int (XIADM12_RESOURCE_LIST, line_nbr);
    show_form (thread);
    resource_base = list_base;
}


/***********************   SHOW CONFIG RESOURCES NEXT   **********************/

MODULE show_config_resources_next (THREAD *thread)
{
    if (list_base < list_count)
        list_base += RESOURCE_LIST_MAX;

    show_resource_page (thread);
}


/***********************   SHOW CONFIG RESOURCES SAME   **********************/

MODULE show_config_resources_same (THREAD *thread)
{
    list_base = resource_base;
    show_resource_page (thread);
}


/************************   CHECK RESOURCES LIVELINK   ***********************/

MODULE check_resources_livelink (THREAD *thread)
{
    if (!livelink_event ())
      {
        if (cur_form-> click_field == XIADM12_URI_NAME)
          {
            strcpy (resource_name, fxgetn_text (cur_form-> click_field,
                                                cur_form-> click_index));
            xstrcpy (resource_full, resource_name, ":", NULL);
            raise_exception (select_resource_event);
          }
        else
            raise_exception (exception_event);
      }
}


/************************   CHECK NEW RESOURCE NAME   ************************/

MODULE check_new_resource_name (THREAD *thread)
{
    strcpy (resource_name, fxget_text (XIADM12_NEW_URI));
    if (strnull (resource_name))
      {
        SET_ERROR (XIADM12_NEW_URI);
        fxput_text (MESSAGE_TO_USER, "Please supply name for resource");
        raise_exception (exception_event);
      }
    else
        xstrcpy (resource_full, resource_name, ":", NULL);
}


/************************   UPDATE CONFIG RESOURCES   ************************/

MODULE update_config_resources (THREAD *thread)
{
    int
        line_nbr;                       /*  Index into screen table          */
    char
        *webmask,                       /*  Value on screen                  */
        *realm;                         /*  Value on screen                  */
    SYMBOL
        *symbol;                        /*  Symbol in config table           */

    for (line_nbr = 0; line_nbr < list_max; line_nbr++)
      {
        sprintf (config_key, "%s:webmask",
                  fxgetn_text (XIADM12_URI_NAME, line_nbr));
        webmask = fxgetn_text (XIADM12_WEBMASK, line_nbr);
        if (strnull (webmask))
          {
            symbol = sym_lookup_symbol (passwd_table, config_key);
            if (symbol)
                sym_delete_symbol (passwd_table, symbol);
          }
        else
            sym_assume_symbol (passwd_table, config_key, webmask);

        sprintf (config_key, "%s:realm",
                  fxgetn_text (XIADM12_URI_NAME, line_nbr));
        realm = fxgetn_text (XIADM12_REALM, line_nbr);
        if (strnull (realm))
          {
            symbol = sym_lookup_symbol (passwd_table, config_key);
            if (symbol)
                sym_delete_symbol (passwd_table, symbol);
          }
        else
            sym_assume_symbol (passwd_table, config_key, realm);
      }
}


/***********************   SAVE CONFIG RESOURCE FILE   ***********************/

MODULE save_config_resource_file (THREAD *thread)
{
    if (passwd_table)
      {
        ini_dyn_save (passwd_table, passwd_file);
        free_passwd_table ();
      }
}


/**********************   CANCEL CONFIG RESOURCE FILE   **********************/

MODULE cancel_config_resource_file (THREAD *thread)
{
    free_passwd_table ();
}


/*************************   OPEN CONFIG USER LIST   *************************/

MODULE open_config_user_list (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in config table           */

    config_users_form = open_form (&form_xiadm13);
    set_form_focus (&config_users_form);

    /*  We save, then delete 'webmask' and 'realm' from the user list        */
    sprintf (config_key, "%swebmask", resource_full);
    symbol = sym_lookup_symbol (passwd_table, config_key);
    if (symbol)
      {
        strcpy (webmask, symbol-> value);
        sym_delete_symbol (passwd_table, symbol);
      }
    else
        strclr (webmask);

    sprintf (config_key, "%srealm", resource_full);
    symbol = sym_lookup_symbol (passwd_table, config_key);
    if (symbol)
      {
        strcpy (realm, symbol-> value);
        sym_delete_symbol (passwd_table, symbol);
      }
    else
        strclr (realm);

    list_prefix = resource_full;
    list_max    = USER_LIST_MAX;
    list_key    = XIADM13_KEY;
    list_name   = XIADM13_USER_NAME;
    list_value  = XIADM13_PASSWORD;
    list_index  = XIADM13_USER_LIST;
    list_table  = passwd_table;
}


/************************   UPDATE CONFIG USER LIST   ************************/

MODULE update_config_user_list (THREAD *thread)
{
    /*  Define symbol for resource itself                                    */
    sym_assume_symbol   (passwd_table, resource_name, "");
    set_or_clear_symbol (passwd_table, resource_name, "webmask", webmask);
    set_or_clear_symbol (passwd_table, resource_name, "realm",   realm);
    update_config_value_list (thread);
}

static void
set_or_clear_symbol (SYMTAB *table, char *name, char *prefix, char *value)
{
    SYMBOL
        *symbol;

    set_config_key (prefix, name);
    if (strused (value))
        sym_assume_symbol (table, config_key, value);
    else
      {
        symbol = sym_lookup_symbol (table, config_key);
        if (symbol)
            sym_delete_symbol (table, symbol);
      }
}


/****************************   OPEN CONFIG FTP   ****************************/

MODULE open_config_ftp (THREAD *thread)
{
    config_ftp_form = open_form (&form_xiadm16);
}


/****************************   SHOW CONFIG FTP   ****************************/

MODULE show_config_ftp (THREAD *thread)
{
    set_form_focus (&config_ftp_form);
    put_values ("ftp", ftp_fields);

    if (reserved_config (config_file))
        fxput_long (XIADM16_MAIN_CONFIG, 1);

    show_ipaddr_list (config_table, "ftp:paddress", 
                      XIADM16_IPADDRESS, XIADM16_L_IPADDRESS);
    show_pipes       (config_table, "ftp:pipe", XIADM16_PIPE, XIADM16_L_PIPE);
    show_form (thread);
}


/***************************   UPDATE CONFIG FTP   ***************************/

MODULE update_config_ftp (THREAD *thread)
{
    get_values ("ftp", ftp_fields);
    update_ipaddress ("ftp:ipaddress", XIADM16_IPADDRESS);
    update_value     ("ftp", "pipe", fxlist_key (XIADM16_PIPE, 0), 0);
}


/************************   SHOW CONFIG FTP DEFAULTS   ***********************/

MODULE show_config_ftp_defaults (THREAD *thread)
{
    put_defaults ("ftp", ftp_fields);
    fxlist_set   (XIADM16_IPADDRESS, 0, DEFTVAL ("ftp:ipaddress"));
    show_form (thread);
}


/*************************   OPEN CONFIG FTP USERS   *************************/

MODULE open_config_ftp_users (THREAD *thread)
{
    strcpy (passwd_file, fxget_text (XIADM16_USER_FILE));
    if (strnull (passwd_file))
      {
        SET_ERROR (XIADM16_USER_FILE);
        fxput_text (MESSAGE_TO_USER, "Supply user definition file name");
        raise_exception (exception_event);
      }
    else
      {
        free_passwd_table ();
        passwd_table = ini_dyn_load (NULL, passwd_file);
        config_ftp_users_form = open_form (&form_xiadm17);
      }
}


/**********************   SHOW CONFIG FTP USERS FIRST   **********************/

MODULE show_config_ftp_users_first (THREAD *thread)
{
    list_base = 0;

    show_ftp_users_page (thread);
}

static void
show_ftp_users_page (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in config table           */
    int
        line_nbr;                       /*  Index into screen table          */
    char
        *ftproot,                       /*  FTP root directory               */
        *property,                      /*  Property name                    */
        *password,                      /*  Shown user password              */
        *rootdir,                       /*  Shown user root dir              */
        *access;                        /*  Shown user permissions           */

    line_nbr   = 0;
    list_count = 0;
    set_form_focus (&config_ftp_users_form);
    sym_sort_table (passwd_table, NULL);
    ftproot = CONFVAL ("ftp:root");

    symbol = passwd_table-> symbols;
    while (symbol)
      {
        symbol = find_next_user (symbol);
        if (!symbol)
            break;

        /*  Set default values for all properties                            */
        password = "-";
        rootdir  = locate_path (ftproot, "");
        access   = "";

        /*  Now go through this section (one user profile)                   */
        while (symbol && strprefixed (symbol-> name, resource_full))
          {
            property = symbol-> name + strlen (resource_full);
            if (streq (property, "password"))
                password = symbol-> value;
            else
            if (streq (property, "root"))
              {
                mem_free (rootdir);
                rootdir = locate_path (ftproot, symbol-> value);
              }
            else
            if (streq (property, "access"))
                access = symbol-> value;

            symbol = symbol-> next;
          }

        if (lexcmp (access, "GPUDMR") == 0)
            access = "*";

        /*  Display what we got, if we're within the list                    */
        if (list_count >= list_base && line_nbr < FTP_USER_LIST_MAX)
          {
            /*  Show user name and hidden key                                */
            fxputn_text   (XIADM17_USER_NAME, line_nbr, user_name);
            fxputn_text   (XIADM17_PASSWORD,  line_nbr, password);
            fxputn_text   (XIADM17_ROOTDIR,   line_nbr, rootdir);
            fxputn_text   (XIADM17_ACCESS,    line_nbr, access);
            fxputn_double (XIADM17_CUR_USAGE, line_nbr,
                          (double) (dir_usage (rootdir, TRUE)) / 1048576);
            fxputn_long   (XIADM17_CUR_FILES, line_nbr,
                                    dir_files (rootdir, TRUE));
            line_nbr++;
          }
        list_count++;                   /*  Actual number of entries         */
        mem_free (rootdir);
      }
    show_first_next (FTP_USER_LIST_MAX);

    fxput_int (XIADM17_FTP_USER_LIST, line_nbr);
    show_form (thread);
}


/*  Searches along the symbol chain for a symbol representing a user
 *  name and sets the user_name to this value.  A symbol is considered
 *  to be a user-name if it has an empty value, and does not contain ':'.
 *  Formats the resource_full string and returns a pointer to the next 
 *  symbol.  If no user name was found, sets user_name to empty, and 
 *  returns NULL.
 */

static SYMBOL *
find_next_user (SYMBOL *symbol)
{
    strclr (user_name);
    strclr (resource_full);
    while (symbol)
      {
        /*  Look for start of section: name with no value                    */
        if (strchr (symbol-> name, ':') != NULL
        || (symbol-> value && *symbol-> value))
          {
            symbol = symbol-> next;
            continue;
          }
        strcpy  (user_name,     symbol-> name);
        xstrcpy (resource_full, symbol-> name, ":", NULL);
        symbol = symbol-> next;
        break;
      }
    return (symbol);
}


/***********************   SHOW CONFIG FTP USERS NEXT   **********************/

MODULE show_config_ftp_users_next (THREAD *thread)
{
    if (list_base < list_count)
        list_base += FTP_USER_LIST_MAX;

    show_ftp_users_page (thread);
}


/***********************   SHOW CONFIG FTP USERS SAME   **********************/

MODULE show_config_ftp_users_same (THREAD *thread)
{
    show_ftp_users_page (thread);
}


/************************   CHECK FTP USERS LIVELINK   ***********************/

MODULE check_ftp_users_livelink (THREAD *thread)
{
    if (!livelink_event ())
      {
        if (cur_form-> click_field == XIADM17_USER_NAME)
          {
            strcpy (user_name, fxgetn_text (cur_form-> click_field,
                                            cur_form-> click_index));
            xstrcpy (resource_full, user_name, ":", NULL);
            raise_exception (select_user_event);
          }
        else
            raise_exception (exception_event);
      }
}


/**************************   OPEN CONFIG FTP USER   *************************/

MODULE open_config_ftp_user (THREAD *thread)
{
    config_ftp_user_form = open_form (&form_xiadm27);
}


/************************   SHOW CONFIG FTP USER NEW   ***********************/

MODULE show_config_ftp_user_new (THREAD *thread)
{
    strcpy (user_name, "");
    show_config_ftp_user (thread);
}


/**************************   SHOW CONFIG FTP USER   *************************/

MODULE show_config_ftp_user (THREAD *thread)
{
    fxput_text (XIADM27_USER_NAME,  user_name);
    fxput_text (XIADM27_PASSWORD,   USERVAL ("password",   "-"));
    fxput_text (XIADM27_ROOTDIR,    USERVAL ("root",       "" ));
    fxput_text (XIADM27_ALIASES,    USERVAL ("aliases",    "0"));
    fxput_text (XIADM27_USE_QUOTAS, USERVAL ("use-quotas", "0"));
    fxput_text (XIADM27_SOFT_QUOTA, USERVAL ("soft-quota", "" ));
    fxput_text (XIADM27_HARD_QUOTA, USERVAL ("hard-quota", "" ));
    show_ftp_user_access (ftpc_access_bits (USERVAL ("access", "")));
    set_config_key (user_name, "pipe");
    show_pipes (passwd_table, config_key, XIADM27_PIPE, XIADM27_L_PIPE);

    set_form_focus (&config_ftp_user_form);
    show_form (thread);
}

static void
show_ftp_user_access (dbyte bits)
{
    fxput_text (XIADM27_ACCESS_GET,    bits & FTP_AUTH_GET?    "1": "0");
    fxput_text (XIADM27_ACCESS_PUT,    bits & FTP_AUTH_PUT?    "1": "0");
    fxput_text (XIADM27_ACCESS_DELETE, bits & FTP_AUTH_DELETE? "1": "0");
    fxput_text (XIADM27_ACCESS_MKDIR,  bits & FTP_AUTH_MKDIR?  "1": "0");
    fxput_text (XIADM27_ACCESS_RMDIR,  bits & FTP_AUTH_RMDIR?  "1": "0");
    fxput_text (XIADM27_ACCESS_UPLOAD, bits & FTP_AUTH_UPLOAD? "1": "0");
}


/*************************   UPDATE CONFIG FTP USER   ************************/

MODULE update_config_ftp_user (THREAD *thread)
{
    char
        *shown_user,
        accesses [FTP_AUTH_COUNT + 1],
        *access_ptr;                    /*  Pointer into access array        */

    /*  Our update algorithm is:
     *  - user name is required
     *  - if user name changed, new name may not exist
     *  - delete old user symbols unless empty
     *  - create new user symbols
     */

    shown_user = fxget_text (XIADM27_USER_NAME);
    if (strnull (shown_user))
      {
        SET_ERROR (XIADM27_USER_NAME);
        fxput_text (MESSAGE_TO_USER, "Supply user name");
        raise_exception (exception_event);
      }
    else
    if (strneq (user_name, shown_user)
    &&  ini_dyn_value (passwd_table, shown_user, "", NULL) != NULL)
      {
        SET_ERROR (XIADM27_USER_NAME);
        fxput_text (MESSAGE_TO_USER, "This user already exists");
        raise_exception (exception_event);
      }
    else
      {
        /*  Build access string from screen options                          */
        access_ptr = accesses;
        if (fxget_bool (XIADM27_ACCESS_GET))
            *access_ptr++ = 'G';
        if (fxget_bool (XIADM27_ACCESS_PUT))
            *access_ptr++ = 'P';
        if (fxget_bool (XIADM27_ACCESS_UPLOAD))
            *access_ptr++ = 'U';
        if (fxget_bool (XIADM27_ACCESS_DELETE))
            *access_ptr++ = 'D';
        if (fxget_bool (XIADM27_ACCESS_MKDIR))
            *access_ptr++ = 'M';
        if (fxget_bool (XIADM27_ACCESS_RMDIR))
            *access_ptr++ = 'R';
        *access_ptr = '\0';

        delete_config_ftp_user (thread);

        strcpy (user_name, shown_user);
        sym_assume_symbol (passwd_table, user_name, "");

        update_user_value ("password",   fxget_text (XIADM27_PASSWORD));
        update_user_value ("root",       fxget_text (XIADM27_ROOTDIR));
        update_user_value ("aliases",    fxget_text (XIADM27_ALIASES));
        update_user_value ("access",     accesses);
        update_user_value ("use-quotas", fxget_text (XIADM27_USE_QUOTAS));
        update_user_value ("soft-quota", fxget_text (XIADM27_SOFT_QUOTA));
        update_user_value ("hard-quota", fxget_text (XIADM27_HARD_QUOTA));
        update_user_value ("pipe",       fxlist_key (XIADM27_PIPE, 0));

        sym_sort_table (passwd_table, NULL);
      }
}


/*  Updates the passwd_table as specified, for the current user_name         */

static void
update_user_value (char *key, char *value)
{
    set_config_key    (user_name, key);
    sym_assume_symbol (passwd_table, config_key, value);
}


/*************************   DELETE CONFIG FTP USER   ************************/

MODULE delete_config_ftp_user (THREAD *thread)
{
    SYMBOL
        *symbol,                        /*  Symbol in password table         */
        *nextsym;

    symbol = sym_lookup_symbol (passwd_table, user_name);
    if (symbol)
      {
        nextsym = symbol-> next;
        sym_delete_symbol (passwd_table, symbol);
        symbol = nextsym;

        xstrcpy (resource_full, user_name, ":", NULL);
        while (symbol && strprefixed (symbol-> name, resource_full))
          {
            nextsym = symbol-> next;
            sym_delete_symbol (passwd_table, symbol);
            symbol = nextsym;
          }
        /*  Show next user, or first if we're at the end                     */
        if (find_next_user (symbol) == NULL)
            find_next_user (passwd_table-> symbols);
      }
}


/*********************   SHOW CONFIG FTP USER DEFAULTS   *********************/

MODULE show_config_ftp_user_defaults (THREAD *thread)
{
    fxput_text (XIADM27_PASSWORD,      "-");
    fxput_text (XIADM27_ROOTDIR,       "" );
    fxput_text (XIADM27_ALIASES,       "0");
    fxput_text (XIADM27_USE_QUOTAS,    "0");
    fxput_text (XIADM27_SOFT_QUOTA,    "" );
    fxput_text (XIADM27_HARD_QUOTA,    "" );
    show_ftp_user_access (0);
}


/***********************   SHOW CONFIG FTP USER FIRST   **********************/

MODULE show_config_ftp_user_first (THREAD *thread)
{
    find_next_user (passwd_table-> symbols);
    show_config_ftp_user (thread);
}


/***********************   SHOW CONFIG FTP USER NEXT   ***********************/

MODULE show_config_ftp_user_next (THREAD *thread)
{
    SYMBOL
        *old_symbol,
        *symbol;

    old_symbol = sym_lookup_symbol (passwd_table, user_name);
    if (old_symbol)
      {
        /*  Find next symbol but stay at end of list if already there        */
        symbol = old_symbol-> next;
        if (find_next_user (symbol) == NULL)
            strcpy (user_name, old_symbol-> name);
      }
    show_config_ftp_user (thread);
}


/***********************   SHOW CONFIG FTP USER SAME   ***********************/

MODULE show_config_ftp_user_same (THREAD *thread)
{
    show_config_ftp_user (thread);
}


/***********************   SET PERMISSIONS AS CHOSEN   ***********************/

MODULE set_permissions_as_chosen (THREAD *thread)
{
    switch (fxget_int (XIADM27_CHOOSER))
      {
        case 1:                         /*  Full access                      */
            fxput_text (XIADM27_ALIASES, "1");
            show_ftp_user_access (FTP_AUTH_GET
                                + FTP_AUTH_PUT
                                + FTP_AUTH_DELETE
                                + FTP_AUTH_MKDIR
                                + FTP_AUTH_RMDIR);
            break;
        case 2:                         /*  Restricted access                */
            fxput_text (XIADM27_ALIASES, "0");
            show_ftp_user_access (FTP_AUTH_GET
                                + FTP_AUTH_PUT
                                + FTP_AUTH_DELETE);
            break;
        case 3:                         /*  Full upload                      */
            fxput_text (XIADM27_ALIASES, "0");
            show_ftp_user_access (FTP_AUTH_PUT);
            break;
        case 4:                         /*  Restricted upload                */
            fxput_text (XIADM27_ALIASES, "0");
            show_ftp_user_access (FTP_AUTH_UPLOAD);
            break;
        case 5:                         /*  Download only                    */
            fxput_text (XIADM27_ALIASES, "0");
            show_ftp_user_access (FTP_AUTH_GET);
            break;
      }
}


/**************************   OPEN CONFIG FTP DIRS   *************************/

MODULE open_config_ftp_dirs (THREAD *thread)
{
    strcpy (direct_file, fxget_text (XIADM16_DIRECTORY_FILE));
    if (strnull (direct_file))
      {
        SET_ERROR (XIADM16_DIRECTORY_FILE);
        fxput_text (MESSAGE_TO_USER, "Supply name for directory access file");
        raise_exception (exception_event);
      }
    else
      {
        free_direct_table ();
        direct_table = ini_dyn_load (NULL, direct_file);
        config_ftp_dirs_form = open_form (&form_xiadm18);
      }
}


static void
free_direct_table (void)
{
    if (direct_table)
      {
        sym_delete_table (direct_table);
        direct_table = NULL;
      }
}


/***********************   SHOW CONFIG FTP DIRS FIRST   **********************/

MODULE show_config_ftp_dirs_first (THREAD *thread)
{
    list_base = 0;
    show_ftp_dir_page (thread);
}


static void
show_ftp_dir_page (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Symbol in password table         */
    int
        user_count,                     /*  Number of users for ftp_dir     */
        line_nbr;                       /*  Index into screen table          */
    char
        *value;                         /*  Split symbol name:value          */

    line_nbr   = 0;
    list_count = 0;

    set_form_focus (&config_ftp_dirs_form);
    sym_sort_table (direct_table, NULL);
    symbol = direct_table-> symbols;
    while (symbol)
      {
        /*  Look for start of section: name with no value                    */
        if (symbol-> value && *symbol-> value)
          {
            symbol = symbol-> next;
            continue;
          }
        strcpy  (resource_name, symbol-> name);
        xstrcpy (resource_full, symbol-> name, ":", NULL);
        symbol = symbol-> next;

        /*  Now go through this section                                      */
        user_count = 0;
        while (symbol && strprefixed (symbol-> name, resource_full))
          {
            value = symbol-> name + strlen (resource_full);
            if (*value)
                user_count++;

            symbol = symbol-> next;
          }
        /*  Display what we got, if we're within the list                    */
        if (list_count >= list_base && line_nbr < CONFIG_LIST_MAX)
          {
            fxputn_text (XIADM18_DIR_NAME,  line_nbr, resource_name);
            fxputn_text (XIADM18_DIR_PATH,  line_nbr, resource_name);
            fxputn_int  (XIADM18_DIR_USERS, line_nbr, user_count);
            line_nbr++;
          }
        list_count++;
       }
    show_first_next (FTP_DIR_LIST_MAX);

    fxput_int (XIADM18_FTP_DIR_LIST, line_nbr);
    show_form (thread);
    resource_base = list_base;
}


/***********************   SHOW CONFIG FTP DIRS NEXT   ***********************/

MODULE show_config_ftp_dirs_next (THREAD *thread)
{
    if (list_base < list_count)
        list_base += RESOURCE_LIST_MAX;

    show_ftp_dir_page (thread);
}


/***********************   SHOW CONFIG FTP DIRS SAME   ***********************/

MODULE show_config_ftp_dirs_same (THREAD *thread)
{
    list_base = resource_base;
    show_ftp_dir_page (thread);
}


/*************************   CHECK FTP DIR LIVELINK   ************************/

MODULE check_ftp_dir_livelink (THREAD *thread)
{
    if (!livelink_event ())
      {
        if (cur_form-> click_field == XIADM18_DIR_NAME)
          {
            strcpy (resource_name, fxgetn_text (cur_form-> click_field,
                                                cur_form-> click_index));
            xstrcpy (resource_full, resource_name, ":", NULL);
            raise_exception (select_resource_event);
          }
        else
            raise_exception (exception_event);
      }
}


/*************************   CHECK NEW FTP DIR NAME   ************************/

MODULE check_new_ftp_dir_name (THREAD *thread)
{
    strcpy (resource_name, fxget_text (XIADM18_NEW_DIR));
    if (strnull (resource_name))
      {
        SET_ERROR (XIADM18_NEW_DIR);
        fxput_text (MESSAGE_TO_USER, "Please supply name for directory");
        raise_exception (exception_event);
      }
    else
        xstrcpy (resource_full, resource_name, ":", NULL);
}


/************************   SAVE CONFIG FTP DIR FILE   ***********************/

MODULE save_config_ftp_dir_file (THREAD *thread)
{
    if (direct_table)
      {
        ini_dyn_save (direct_table, direct_file);
        free_direct_table ();
      }
}


/***********************   CANCEL CONFIG FTP DIR FILE   **********************/

MODULE cancel_config_ftp_dir_file (THREAD *thread)
{
    free_direct_table ();
}


/***********************   OPEN CONFIG FTP USER LIST   ***********************/

MODULE open_config_ftp_user_list (THREAD *thread)
{
    config_ftp_uri_users_form = open_form (&form_xiadm19);
    set_form_focus (&config_ftp_uri_users_form);

    list_prefix = resource_full;
    list_max    = FTP_DIR_USER_LIST_MAX;
    list_key    = XIADM19_KEY;
    list_name   = XIADM19_USER_NAME;
    list_value  = XIADM19_ACCESSES;
    list_index  = XIADM19_FTP_DIR_USER_LIST;
    list_table  = direct_table;
}


/**********************   UPDATE CONFIG FTP USER LIST   **********************/

MODULE update_config_ftp_user_list (THREAD *thread)
{
    /*  Define symbol for resource itself                                    */
    sym_assume_symbol (direct_table, resource_name, "");

    update_config_value_list (thread);
}


/*************************   OPEN CONFIG FTP ALIAS   *************************/

MODULE open_config_ftp_alias (THREAD *thread)
{
    config_ftp_alias_form = open_form (&form_xiadm26);
    set_form_focus (&config_ftp_alias_form);

    list_prefix = "ftp-alias:";
    list_max    = FTP_ALIAS_LIST_MAX;
    list_key    = XIADM26_KEY;
    list_name   = XIADM26_FTP_ALIAS_NAME;
    list_value  = XIADM26_FTP_ALIAS_PATH;
    list_index  = XIADM26_FTP_ALIAS_LIST;
    list_table  = config_table;
}


/***************************   OPEN CONSOLE PANEL   **************************/

MODULE open_console_panel (THREAD *thread)
{
    console_panel_form = open_form (&form_xiadm21);
}


/***************************   SHOW CONSOLE PANEL   **************************/

MODULE show_console_panel (THREAD *thread)
{
    long
        shown_size;
    char
        *shown_unit;

    shown_size = transfer_size;
    shown_unit = "Kb";
    if (shown_size > 10000)
      {
        shown_size /= 1024;
        shown_unit = "Mb";
        if (shown_size > 10000)
          {
            shown_size /= 1024;
            shown_unit = "Gb";
          }
      }
    set_form_focus (&console_panel_form);

    fxput_date (XIADM21_DATE_STARTED,   date_started);
    fxput_time (XIADM21_TIME_STARTED,   time_started);
    fxput_text (XIADM21_SERVER_MESSAGE, server_message);
    fxput_long (XIADM21_HTTP_PORT,      ip_portbase + 80);
    fxput_long (XIADM21_FTP_PORT,       ip_portbase
                + atol (http_config (config, "ftp:port")));
    fxput_long (XIADM21_CUR_CONNECTS,   cur_connects);
    fxput_long (XIADM21_MAX_CONNECTS,   max_connects);
    fxput_long (XIADM21_CONNECT_COUNT,  connect_count);
    fxput_long (XIADM21_ERROR_COUNT,    error_count);
    fxput_long (XIADM21_TRANSFER_SIZE,  shown_size);
    fxput_text (XIADM21_TRANSFER_UNIT,  shown_unit);
    show_log_file_stats ();
    console_panel_form-> input_range = range_none;

    show_form (thread);
}


static void
show_log_file_stats (void)
{
    AGENT
        *agent;
    QUEUE
        *queue;
    THREAD
        *thread;
    LOGSTATS
        *stats;
    qbyte
        files  = 0,
        lines  = 0,
        bytes  = 0,
        kbytes = 0;
        
    agent = agent_lookup (XIXLOG_AGENT);
    if (agent)
      {
        FORLIST (queue, agent-> queues)
          {
            /*  Get first (only) thread                                      */
            thread = queue-> threads.next;
            stats  = (LOGSTATS *) thread-> tcb;
    
            lines  += stats-> file_lines;
            bytes  += stats-> file_size;
            kbytes += bytes / 1024;
            bytes   = bytes % 1024;
            files++;
          }
      }
    fxput_long (XIADM21_LOG_FILES,  files);
    fxput_long (XIADM21_LOG_LINES,  lines);
    fxput_long (XIADM21_LOG_KBYTES, kbytes);
}


/*********************   CLEAR CONSOLE PANEL STATISTICS   ********************/

MODULE clear_console_panel_statistics (THREAD *thread)
{
    max_connects  = 0;
    connect_count = 0;
    error_count   = 0;
    transfer_size = 0;
}


/***********************   CYCLE ALL ACTIVE LOGFILES   ***********************/

MODULE cycle_all_active_logfiles (THREAD *thread)
{
    send_to_all_logfiles ("CYCLE", "Cycled all log files");
}


static void
send_to_all_logfiles (char *method, char *message)
{
    AGENT
        *agent;
    QUEUE
        *queue;

    agent = agent_lookup (XIXLOG_AGENT);
    if (agent)                          /*  Do nothing if agent not active   */
      {
        FORLIST (queue, agent-> queues)
            SEND (&queue-> qid, method, "");
        fxput_text (MESSAGE_TO_USER, message);
      }
    else
        fxput_text (MESSAGE_TO_USER, "Logging agent is not running");
}


/***********************   CLEAR ALL ACTIVE LOGFILES   ***********************/

MODULE clear_all_active_logfiles (THREAD *thread)
{
    send_to_all_logfiles ("CLEAR", "Cleared all log files");
}


/***********************   RESTART HTTP SERVER AGENT   ***********************/

MODULE restart_http_server_agent (THREAD *thread)
{
    xstrcpy ((char *) buffer.data, 
             "<HTML><BODY>",
             "<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"5; URL=/admin\">",
             "<H2>Restarting the Web Server...</H2>",
             "<P>The WBA main page should re-appear in a few seconds. ",
             "If it does not, click <A HREF=\"/admin\">here</A>.",
             "If you changed the portbase, enter the new URL by hand.",
             "</BODY></HTML>",
             NULL);
    send_wsx_restart (&thread-> event-> sender, (char *) buffer.data);

    /*  Wait for next request                                                */
    if (request)
        free_smt_wsx_request (&request);

    event_wait ();
}


/***********************   SHUTDOWN HTTP SERVER AGENT   **********************/

MODULE shutdown_http_server_agent (THREAD *thread)
{
    xstrcpy ((char *) buffer.data, 
             "<HTML><BODY>",
             "<H2>Shutting-down the Web Server...</H2>",
             "</BODY></HTML>",
             NULL);
    send_wsx_kill (&thread-> event-> sender, (char *) buffer.data);
}


/*************************   REDIRECT TO HOME PAGE   *************************/

MODULE redirect_to_home_page (THREAD *thread)
{
    send_wsx_redirect (&thread-> event-> sender, "/");
}


/*************************   OPEN CONSOLE MESSAGES   *************************/

MODULE open_console_messages (THREAD *thread)
{
    console_messages_form = open_form (&form_xiadm22);
}


/*  This function receives the messages data and appends it to the messages
 *  line buffer.
 */

static void
messages_handler (const char *message)
{
    linebuf_append (messages_buffer, message);
}


/*************************   SHOW CONSOLE MESSAGES   *************************/

MODULE show_console_messages (THREAD *thread)
{
    char
        *dest,
        *next_line;
    static byte
        line [LINE_MAX + 1];
    DESCR
        descr = { LINE_MAX, line };
    int
        messages_size;

    set_form_focus (&console_messages_form);

    /*  Point to start of messages text box                                  */
    dest = ((XIADM22_DATA *) cur_form-> data)-> messages;
    messages_size = 0;
    if (messages_invert)
      {
        next_line = linebuf_last (messages_buffer, &descr);
        while (next_line)
          {
            strcpy (dest, (char *) line);
            messages_size += strlen (dest) + 1;
            ASSERT (messages_size < 4000);
            dest += strlen (dest);
            *dest++ = '\n';             /*  Lines are separated by newline   */
            next_line = linebuf_prev (messages_buffer, &descr, next_line);
          }
      }
    else
      {
        next_line = linebuf_first (messages_buffer, &descr);
        while (next_line)
          {
            strcpy (dest, (char *) line);
            messages_size += strlen (dest) + 1;
            ASSERT (messages_size < 4000);
            dest += strlen (dest);
            *dest++ = '\n';             /*  Lines are separated by newline   */
            next_line = linebuf_next (messages_buffer, &descr, next_line);
          }
      }
    *dest = '\0';                       /*  End string cleanly               */

    show_form (thread);
}


/*************************   CLEAR CONSOLE MESSAGES   ************************/

MODULE clear_console_messages (THREAD *thread)
{
    linebuf_reset (messages_buffer);
}


/**************************   INVERT CONSOLE DATA   **************************/

MODULE invert_console_data (THREAD *thread)
{
    messages_invert = !messages_invert;
}


/**************************   OPEN CONNECTION LIST   *************************/

MODULE open_connection_list (THREAD *thread)
{
    connection_list_form = open_form (&form_xiadm24);
    connection_list_form-> input_range = range_none;
}


/**************************   SHOW CONNECTION LIST   *************************/

MODULE show_connection_list (THREAD *thread)
{
    int
        line_nbr = 0;

    set_form_focus (&connection_list_form);
    line_nbr = show_server_threads (SMT_HTTP, "Http", line_nbr);
    line_nbr = show_server_threads (SMT_FTPC, "Ftp",  line_nbr);
    fxput_int (XIADM24_CLIENT_LIST, line_nbr);
    connection_list_form-> input_range = range_none;
    show_form (thread);
}


static int
show_server_threads  (char *agent_name, char *tag, int line_nbr)
{
    AGENT
        *agent;
    QUEUE
        *queue;
    THREAD
        *thread;
    HTTP_STAT
        *stats;

    agent = agent_lookup (agent_name);
    if (agent)                          /*  Do nothing if agent not active   */
      {
        FORLIST (queue, agent-> queues)
          {
            if (line_nbr == CLIENT_LIST_MAX)
                break;

            thread = queue-> threads.next;  /* Get first (only) thread       */
            stats = (HTTP_STAT *) thread-> tcb;
            if (stats-> client)
              {
                fxputn_text (XIADM24_TYPE,      line_nbr, tag);
                fxputn_text (XIADM24_IPADDRESS, line_nbr, socket_peeraddr
                                                         (stats-> socket));
                fxputn_text (XIADM24_USERNAME,  line_nbr, stats-> username?
                             stats-> username: "(None)");
                fxputn_text (XIADM24_REQUEST,   line_nbr, stats-> request?
                             stats-> request:  "(None)");
                line_nbr++;
              }
          }
      }
    return (line_nbr);
}


/**************************   OPEN CONSOLE CONFIG   **************************/

MODULE open_console_config (THREAD *thread)
{
    console_config_form = open_form (&form_xiadm23);
}


/**************************   SHOW CONSOLE CONFIG   **************************/

MODULE show_console_config (THREAD *thread)
{
    set_form_focus (&console_config_form);
    put_values ("console", console_fields);
    show_form (thread);
}


/*************************   UPDATE CONSOLE CONFIG   *************************/

MODULE update_console_config (THREAD *thread)
{
    get_values ("console", console_fields);
}


/**********************   SHOW CONSOLE CONFIG DEFAULTS   *********************/

MODULE show_console_config_defaults (THREAD *thread)
{
    put_defaults ("console", console_fields);
    show_form (thread);
}


/***************************   OPEN VHOST WIZARD   ***************************/

MODULE open_vhost_wizard (THREAD *thread)
{
    vhost_wizard_form = open_form (&form_xiadm25);
}


/***************************   SHOW VHOST WIZARD   ***************************/

MODULE show_vhost_wizard (THREAD *thread)
{
    set_form_focus (&vhost_wizard_form);
    show_ipaddr_list (config_table, NULL, XIADM25_HOST_ADDR, 0);
    show_form (thread);
}


/***********************   VALIDATE VHOST DEFINITION   ***********************/

MODULE validate_vhost_definition (THREAD *thread)
{
    XIADM25_DATA
        *data;

    data = (XIADM25_DATA *) cur_form-> data;

    /*  Preparation: remove extension from filename if any                   */
    if (strused (data-> host_file)
    &&  strchr  (data-> host_file, '.'))
        *strchr (data-> host_file, '.') = '\0';
    sprintf (config_full, "%s.cfg", data-> host_file);

    /*  Create virtual-host directories if necessary - ignore errors         */
    if (*data-> makedirs == '1')
      {
        make_dir (data-> webpages);
        make_dir (data-> cgi_bin);
        make_dir (data-> ftproot);
      }        

    /*  Check 1: profile may not be blank                                    */
    if (strnull (data-> host_file))
      {
        SET_ERROR (XIADM25_HOST_FILE);
        fxput_text (MESSAGE_TO_USER, "Enter a name for the profile");
        raise_exception (exception_event);
      }
    else
    /*  Check 2: profile may not exist unless 'Overwrite' was selected       */
    if (file_exists (config_full) && *data-> overwrite == '0')
      {
        SET_ERROR (XIADM25_HOST_FILE);
        fxput_text (MESSAGE_TO_USER, "Profile already exists");
        raise_exception (exception_event);
      }
    else
    /*  Check 3: 'xitami' and 'defaults' are not allowed                     */
    if (reserved_config (data-> host_file))
      {
        SET_ERROR (XIADM25_HOST_FILE);
        fxput_text (MESSAGE_TO_USER, "You cannot use this filename");
        raise_exception (exception_event);
      }
    else
    /*  Check 3: one but not both address & name can be selected             */
    if (atoi (data-> host_addr) == 0 && strnull (data-> host_name))
      {
        SET_ERROR (XIADM25_HOST_ADDR);
        SET_ERROR (XIADM25_HOST_NAME);
        fxput_text (MESSAGE_TO_USER, "Choose an address or supply a name");
        raise_exception (exception_event);
      }
    else
    if (atoi (data-> host_addr) > 1 && strused (data-> host_name))
      {
        SET_ERROR (XIADM25_HOST_ADDR);
        SET_ERROR (XIADM25_HOST_NAME);
        fxput_text (MESSAGE_TO_USER, "Choose just one of these");
        raise_exception (exception_event);
      }
    else
    /*  Check 4: webpages directory must exist, if not blank                 */
    if (strused (data-> webpages) && !file_is_directory (data-> webpages))
      {
        SET_ERROR (XIADM25_WEBPAGES);
        fxput_text (MESSAGE_TO_USER, "Directory does not exist");
        raise_exception (exception_event);
      }
    else
    /*  Check 5: CGI directory must exist, if not blank                      */
    if (strused (data-> cgi_bin) && !file_is_directory (data-> cgi_bin))
      {
        SET_ERROR (XIADM25_CGI_BIN);
        fxput_text (MESSAGE_TO_USER, "Directory does not exist");
        raise_exception (exception_event);
      }
    else
    /*  Check 6: ftproot directory must exist, if not blank                 */
    if (strused (data-> ftproot) && !file_is_directory (data-> ftproot))
      {
        SET_ERROR (XIADM25_FTPROOT);
        fxput_text (MESSAGE_TO_USER, "Directory does not exist");
        raise_exception (exception_event);
      }

    /*  Check 6: WBA user id and password must be filled-in                  */
    if (strnull (data-> admin_user))
        strcpy (data-> admin_user, "admin");
    if (strnull (data-> admin_pass))
        strcpy (data-> admin_pass, "-");
    if (strnull (data-> vhwba_user))
        strcpy (data-> vhwba_user, "admin");
    if (strnull (data-> vhwba_pass))
        strcpy (data-> vhwba_pass, "-");
}


/************************   CREATE VHOST DEFINITION   ************************/

MODULE create_vhost_definition (THREAD *thread)
{
    XIADM25_DATA
        *data;
    SYMTAB
        *table;
    FILE
        *authfile;

    data = (XIADM25_DATA *) cur_form-> data;

    /*  Step 1: install virtual host definition in defaults.cfg              */
    table = ini_dyn_load (NULL, "defaults.cfg");
    sprintf (config_key, "virtual-hosts:%s", *data-> host_name?
             data-> host_name: fxlist_key (XIADM25_HOST_ADDR, 0));
    sym_assume_symbol (table, config_key, config_full);
    ini_dyn_save (table, "defaults.cfg");
    sym_delete_table (table);

    /*  Step 2: create virtual host profile                                  */
    table = sym_create_table ();
    if (strused (data-> webpages))
      {
        sym_assume_symbol (table, "server", "");
        sym_assume_symbol (table, "server:webpages", data-> webpages);
      }
    if (strused (data-> cgi_bin))
      {
        sym_assume_symbol (table, "server", "");
        sym_assume_symbol (table, "server:cgi-bin", data-> cgi_bin);
      }
    if (strused (data-> ftproot))
      {
        sym_assume_symbol (table, "ftp", "");
        sym_assume_symbol (table, "ftp:root", data-> ftproot);
      }
    if (strused (data-> superuser))
        sym_assume_symbol (table, "security:superuser", data-> superuser);

    if (*data-> sharelogs == '0')
      {
        sprintf (config_key, "%s.log", data-> host_file);
        sym_assume_symbol (table, "accesslog", "");
        sym_assume_symbol (table, "accesslog:filename", config_key);
      }
    if (*data-> use_admin == '0')
      {
        sym_assume_symbol (table, "wsx", "");
        sym_assume_symbol (table, "wsx:admin", "");
      }
    if (*data-> use_vhwba == '0')
      {
        sym_assume_symbol (table, "wsx", "");
        sym_assume_symbol (table, "wsx:setup", "");
      }
        
    /*  Create authorisation file                                            */
    sprintf (config_key, "%s.aut", data-> host_file);
    sym_assume_symbol (table, "security", "");
    sym_assume_symbol (table, "security:filename", config_key);
    if (!file_exists (config_key))
      {
        authfile = file_open (config_key, 'w');
        if (authfile)
          {
            fprintf (authfile, "#   Created by Virtual Host wizard\n");
            fprintf (authfile, "[/Admin]\n");
            fprintf (authfile, "    %s=%s\n", data-> admin_user,
                                              data-> admin_pass);
            fprintf (authfile, "[/Setup]\n");
            fprintf (authfile, "    %s=%s\n", data-> vhwba_user,
                                              data-> vhwba_pass);
            file_close (authfile);
          }
      }
    ini_dyn_save (table, config_full);
    sym_delete_table (table);
}


/***********************   RELOAD SERVER BASE CONFIG   ***********************/

MODULE reload_server_base_config (THREAD *thread)
{
    char
        *old_capture,                   /*  Previous console capture flag    */
        *old_filename;

    old_capture  = mem_strdup (http_config (config, "console:capture"));
    old_filename = mem_strdup (http_config (config, "console:filename"));

    sym_delete_table (config);
    config = ini_dyn_load (NULL, "xitami.cfg");
    ini_dyn_load (config, CONFIG ("server:defaults"));

    /*  If console configuration changed, reset capture file and mode        */
    if (strneq (old_capture , http_config (config, "console:capture"))
    ||  strneq (old_filename, http_config (config, "console:filename")))
        http_capture_console ();

    mem_free (old_capture);
    mem_free (old_filename);
}


/**************************   RESHOW CURRENT FORM   **************************/

MODULE reshow_current_form (THREAD *thread)
{
    show_form (thread);
}


/***************************   CLOSE CURRENT FORM   **************************/

MODULE close_current_form (THREAD *thread)
{
    close_form (cur_formp);
}


static void
close_form (FORM_ITEM **form)
{
    if (form)
      {
        form_term (*form);
        *form = NULL;
      }
}


/****************************   CLOSE ALL FORMS   ****************************/

MODULE close_all_forms (THREAD *thread)
{
    close_form (&main_menu_form);
    close_form (&config_list_form);
    close_form (&config_server_form);
    close_form (&config_advanced_form);
    close_form (&config_aliases_form);
    close_form (&config_vhosts_form);
    close_form (&config_cgi_form);
    close_form (&config_security_form);
    close_form (&config_logging_form);
    close_form (&config_log_file_form);
    close_form (&config_mimes_form);
    close_form (&config_ddns_form);
    close_form (&config_cgi_envir_form);
    close_form (&config_cgi_alias_form);
    close_form (&config_ssi_form);
    close_form (&config_errors_form);
    close_form (&config_wsx_form);
    close_form (&config_filter_form);
    close_form (&config_security_form);
    close_form (&config_users_form);
    close_form (&config_ftp_form);
    close_form (&config_ftp_users_form);
    close_form (&config_ftp_user_form);
    close_form (&config_ftp_dirs_form);
    close_form (&config_ftp_uri_users_form);
    close_form (&config_ftp_alias_form);
    close_form (&console_panel_form);
    close_form (&console_messages_form);
    close_form (&console_config_form);
    close_form (&connection_list_form);
    close_form (&vhost_wizard_form);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    if (request)
        free_smt_wsx_request (&request);

    sym_delete_table  (symbols);
    free_config_table ();
    free_passwd_table ();
    free_direct_table ();
    mem_free (buffer.data);

    /*  Stop capturing the console output                                    */
    console_send    (NULL, TRUE);
    linebuf_destroy (messages_buffer);

    the_next_event = terminate_event;
}


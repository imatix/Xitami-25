/*===========================================================================*
 *                                                                           *
 *  smthttpl.h -                                                             *
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

#ifndef _SMTHTTPL_INCLUDED              /*  Allow multiple inclusions        */
#define _SMTHTTPL_INCLUDED


/*- Defaults for configuration options --------------------------------------*/

#define XITAMI_VERSION          "2.5c2"


/*- Global variables --------------------------------------------------------*/

extern char
    *server_name,                       /*  Name for our server program      */
    *server_message;                    /*  HTTP server error message        */
#define SERVER_ADDRS_MAX  128           /*  Max. size of this string         */
extern qbyte
    connect_count,                      /*  Total connections made           */
    cur_connects,                       /*  Cur number of connections        */
    max_connects,                       /*  Max number of connections        */
    error_count,                        /*  Number of errors                 */
    transfer_size;                      /*  Amount of data transfered        */
extern long
    time_started,                       /*  Time that server started         */
    date_started;                       /*  Date that server started         */
extern SYMTAB
    *config,                            /*  Our configuration table          */
    *defaults,                          /*    and defaults table             */
    *wsx_aliases,                       /*  Global WSX alias table           */
    *http_dirs;                         /*  Directories we work in           */
    
extern Bool
    server_killed;                      /*  If ended from control panel      */


/*- Macros ------------------------------------------------------------------*/

#define CONFIG(s)     http_config   (config, (s))
#define DEFAULT(s)    sym_get_value (defaults, (s), "")


/*- Defines -----------------------------------------------------------------*/

/*  Check file type return                                                   */

#define HTTP_FILE_OK            1       /*  File found normally              */
#define HTTP_FILE_DIRECTORY     2       /*  File is a directory              */
#define HTTP_FILE_EXECUTABLE    3
#define HTTP_FILE_NOT_OK        4
#define HTTP_FILE_NOT_FOUND     5

/*  URL Type                                                                 */

#define HTTP_URL_ILLEGAL        0       /*  URL is not supported             */
#define HTTP_URL_HTML           1       /*  URL is a file of some kind       */
#define HTTP_URL_CGI            2       /*  URL is a CGI binary              */
#define HTTP_URL_WSX            3       /*  URL is a WSX plug-in             */
#define HTTP_URL_FILTER         4       /*  URL is a filtered file           */

/*  Transaction types                                                        */

#define TRANSACTION_FILE        0
#define TRANSACTION_CGI         1
#define TRANSACTION_WSX         2
#define TRANSACTION_FILTER      3

/*  CGI process states                                                       */

#define CGI_STATE_RUNNING       0
#define CGI_STATE_END           1
#define CGI_STATE_ERROR         2

/*  Other constants                                                          */

#define HTTP_OUTPUT_TIMEOUT     "60"    /*  Timeout for transmitted data     */
#define HTTP_HEADER_MAX         32000   /*  Max. size of HTTP header         */
#define HTTP_URL_MAX            4096    /*  Max. size of a URL + args        */
#if (HTTP_URL_MAX < LINE_MAX)
#   define HTTP_URL_MAX         LINE_MAX
#endif
#define HTTP_AUTH_MAX           1000    /*  Max. size of basic auth.         */
#define HTTP_LOG_REQ_MAX        1024    /*  Max. size of logged request      */
#define VHOST_ANY               "<any>" /*  Basic non-virtual host           */
#define MULTIPART_DELIM         "XITAMI_DELIVERS"


/*  HTTP methods                                                             */

#define HTTP_METHOD_GET         0
#define HTTP_METHOD_HEAD        1
#define HTTP_METHOD_POST        2
#define HTTP_METHOD_PUT         3
#define HTTP_METHOD_DELETE      4
#define HTTP_METHOD_MOVE        5
#define HTTP_METHOD_COPY        6

#if (defined (DEFINE_HTTP_TABLES))
char
    *http_methods [] = {                /*  Http method syntax in request    */
        "GET",
        "HEAD",
        "POST",
        "PUT",
        "DELETE",
        "MOVE",
        "COPY",
        ""
    };
#else
extern char *http_methods [];
#endif

/*  HTTP response codes                                                      */

#define HTTP_RESPONSE_OK               0
#define HTTP_RESPONSE_CREATED          1
#define HTTP_RESPONSE_ACCEPTED         2
#define HTTP_RESPONSE_NOCONTENT        3
#define HTTP_RESPONSE_PARTIAL          4
#define HTTP_RESPONSE_MOVED            5
#define HTTP_RESPONSE_FOUND            6
#define HTTP_RESPONSE_METHOD           7
#define HTTP_RESPONSE_NOTMODIFIED      8
#define HTTP_RESPONSE_BADREQUEST       9
#define HTTP_RESPONSE_UNAUTHORIZED     10
#define HTTP_RESPONSE_PAYEMENT         11
#define HTTP_RESPONSE_FORBIDDEN        12
#define HTTP_RESPONSE_NOTFOUND         13
#define HTTP_RESPONSE_PRECONDITION     14
#define HTTP_RESPONSE_TOOLARGE         15
#define HTTP_RESPONSE_INTERNALERROR    16
#define HTTP_RESPONSE_NOTIMPLEMENTED   17
#define HTTP_RESPONSE_OVERLOADED       18

typedef struct {
    char *code;                         /*  Response code, 3 digits          */
    char *name;                         /*  Response text                    */
} RESPONSE;

#if (defined (DEFINE_HTTP_TABLES))
RESPONSE
http_response [] = {                    /*  HTTP response code               */
    { "200", "Ok"                              },
    { "201", "Created"                         },
    { "202", "Accepted"                        },
    { "204", "No content"                      },
    { "206", "Partial content"                 },
    { "301", "Moved"                           },
    { "302", "Found"                           },
    { "303", "Method"                          },
    { "304", "Not modified"                    },
    { "400", "Bad request"                     },
    { "401", "Unauthorized"                    },
    { "402", "Payment required"                },
    { "403", "Forbidden"                       },
    { "404", "Not found"                       },
    { "412", "Precondition failed"             },
    { "413", "Request entity too large"        },
    { "500", "Internal error"                  },
    { "501", "Not implemented"                 },
    { "503", "Service temporarily overloaded"  },
    { NULL, NULL },                     /*  End of table                     */
    };
#else
extern RESPONSE http_response [];
#endif

/*  Error types                                                              */

#define ERROR_UNSPECIFIED       0
#define ERROR_CGI_NORESOURCES   1
#define ERROR_CGI_URLTOOLONG    2
#define ERROR_CGI_NOSTDIO       3
#define ERROR_CGI_PROCESSNF     4
#define ERROR_CGI_PROCESSERROR  5
#define ERROR_CGI_INTERRUPTED   6
#define ERROR_CGI_INTERNALERROR 7


/*  Corresponding error messages                                             */

#if (defined (DEFINE_HTTP_TABLES))
static char
    *error_msg [] = {                   /*  Various error messages           */
        "",
        "Insufficient resources to run this CGI program",
        "CGI arguments are too long - request was refused",
        "Cannot create stdin stream for CGI",
        "Cannot create CGI process - program not found",
        "CGI process ended with an error status",
        "CGI process was interrupted before ending",
        "Internal server error while running CGI",
        ""
    };
#endif


/*- Structure definitions ---------------------------------------------------*/

typedef struct {
    dbyte
        response;                       /*  HTTP response code               */
    int
        method,                         /*  HTTP method in request           */
        protocol_major,                 /*  HTTP protocol major revision     */
        protocol_minor,                 /*  HTTP protocol minor revision     */
        keep_alive_max,                 /*  Max keep-alive connections       */
        port,                           /*  HTTP port                        */
        ssl_port,                       /*  HTTPS port, if used              */
        transaction,                    /*  Transaction type: FILE, CGI ...  */
        error_type;                     /*  Cause of last error              */
    sock_t
        socket;                         /*  Socket for HTTP connection       */
    char
        *log_request,                   /*  Original HTTP request for log    */
        *url,                           /*  Uniform Resource Locator (URL)   */
        *url_param,                     /*  Arguments after 'url?'           */
        *url_ext,                       /*  URL extension, if any            */
        *file_name,                     /*  File name for the current URL    */
        *username,                      /*  User from authorization string   */
        *password,                      /*  Password from author. string     */
        *realm,                         /*  Realm for authentication         */
        *vhost,                         /*  Virtual host for request         */
        *script_path,                   /*  Script path                      */
        *script_name,                   /*  Name of script, without path     */
        *path_info,                     /*  CGI path info string             */
        *post_data,                     /*  CGI POST data string             */
        *referrer,                      /*  Original Referer: value          */
        *cgi_stdin,                     /*  File name for CGI stdin          */
        *cgi_status,                    /*  CGI response code, if any        */
        **cgi_environ,                  /*  CGI environment variables        */
        *wsx_agent,                     /*  WSX agent name if used           */
        *rootdir,                       /*  Copy of rootdir location         */
        *cgidir,                        /*  Copy of cgi dir location         */
        *webmask;                       /*  Copy of webmask for vhost        */
    Bool
        send_file,                      /*  Set to TRUE if send file         */
        temp_file,                      /*  TRUE if temporary file           */
        keep_alive,                     /*  Keep alive connection            */
        uses_vhost,                     /*  Based on virtual host            */
        default_page,                   /*  Sending default page             */
        send_range,                     /*  Sending a range                  */
        no_cache,                       /*  For directory lists, etc.        */
        cgi_header,                     /*  If CGI output starts with HTTP/  */
        ssl_connection;                 /*  TRUE for SSL connection          */
    long
        file_size,                      /*  File information                 */
        file_date,                      /*  File local date and              */
        file_time,                      /*    time of modification           */
        file_offset,                    /*  Skip start of CGI response file  */
        timeout_date,                   /*  Expiry date and time for CGI     */
        timeout_time;                   /*    processes                      */
    size_t
        post_size;                      /*  POSTed data size                 */
    SYMTAB
        *config,                        /*  Virtual host configuration       */
        *request_headers,               /*  Header values, input request     */
        *response_headers;              /*  Header values, output response   */
    word
        input_timeout,                  /*  Wait socket input timeout        */
        output_timeout;                 /*  Wait socket output timeout       */
    PROCESS
        cgi_process_id;                 /*  ID for CGI process               */
} HTTP_CONTEXT;


/*  Connection statistics block                                              */

typedef struct {
    Bool
        client;                         /*  Is this a client connection?     */
    sock_t
        socket;                         /*  Socket for connection            */
    char
        *request;                       /*  Current request string           */
    char
        *username;                      /*  Current authorised user          */
} HTTP_STAT;


/*- Function prototypes -----------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

void    http_init                  (void);
void    http_term                  (void);
char   *http_config                (SYMTAB *table, const char *key);
void    http_init_context          (HTTP_CONTEXT *p_http);
void    http_refresh_context       (HTTP_CONTEXT *p_http);
void    http_free_context          (HTTP_CONTEXT *p_http);
void    http_set_priority          (void);
int     http_parse_request         (HTTP_CONTEXT *p_http, char *buffer);
char   *http_parse_header          (HTTP_CONTEXT *p_http, char *header);
int     http_get_url_type          (HTTP_CONTEXT *p_http);
char   *http_match_wsx             (HTTP_CONTEXT *p_http);
DESCR  *http_wsx_symbols           (HTTP_CONTEXT *p_http);
int     http_check_file            (HTTP_CONTEXT *p_http);
char   *http_get_file_name         (HTTP_CONTEXT *p_http);
char   *http_format_header         (HTTP_CONTEXT *p_http, char *buffer);
char   *http_header_value          (HTTP_CONTEXT *p_http, char *field);
Bool    http_get_default_page      (HTTP_CONTEXT *p_http);
void    http_get_authorization     (HTTP_CONTEXT *p_http);
Bool    http_list_directory        (HTTP_CONTEXT *p_http);
int     http_create_cgi_process    (HTTP_CONTEXT *p_http);
int     http_create_filter_process (HTTP_CONTEXT *p_http);
int     http_process_state         (HTTP_CONTEXT *p_http);
void    http_close_process         (HTTP_CONTEXT *p_http);
int     http_reparse_output        (HTTP_CONTEXT *p_http);
int     http_reparse_buffer        (HTTP_CONTEXT *p_http, char *buffer);
char   *http_map_uri               (SYMTAB *config, const char *rootdir,
                                    const char *cgidir, const char *uri,
                                    const char *cgi_url, int transaction);
void    http_capture_console       (void);
char   *http_match_alias           (SYMTAB *config, const char *uri,
                                    const char *type, char **base);
Bool    http_uri_protected         (HTTP_CONTEXT *p_http, SYMTAB *passwd,
                                    char *uri);
char   *http_get_mime_type         (HTTP_CONTEXT *p_http);
Bool    http_password_okay         (char *challenge, char *response);
char   *http_pipe                  (HTTP_CONTEXT *p_http, char *ext);
void    http_message               (const char *format, ...);
char   *http_webmask               (const char *config_value, sock_t handle);
Bool    http_reserved_username     (const char *username);
int     http_update_resource       (HTTP_CONTEXT *p_http);
void    http_count_transfer        (long size);
char   *http_clean_request         (const char *request);
char   *http_clean_hostname        (const char *hostname);
Bool    http_modified_since        (HTTP_CONTEXT *, char *filename, char *header);
Bool    http_unmodified_since      (HTTP_CONTEXT *, char *filename, char *header);

#ifdef __cplusplus
}

#endif

#endif

/*---------------------------------------------------------------------------
 *  xixlogm.h - prototypes for Xixlog messages.
 *
 *  Generated on 2004/07/22, 17:52:21 from xixlogm.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_XIXLOGM
#define INCLUDE_XIXLOGM

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for xixlog - Xitami Extended Logging Agent.
 *---------------------------------------------------------------------------*/

#define XIXLOG_SET_RDNS "ssBB"

typedef struct {
    char *primary;                      /*  Primary DNS server               */
    char *secondary;                    /*  Secondary DNS server             */
    Bool  recursive;                    /*  Do recursive lookups?            */
    Bool  debug;                        /*  Debug DNS queries?               */
} struct_xixlog_set_rdns;


int  get_xixlog_set_rdns     (byte *_buffer, struct_xixlog_set_rdns **params);
void free_xixlog_set_rdns    (struct_xixlog_set_rdns **params);
int  put_xixlog_set_rdns     (byte **_buffer, char *primary, char *secondary, Bool  recursive, Bool  debug);

#define declare_set_rdns(_event, _priority)                                  \
    method_declare (agent, "SET_RDNS", _event, _priority)

/*  Send event - Initialise RDNS interface                                   */

int lsend_set_rdns (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *primary,                  /*  Primary DNS server               */
        char *secondary,                /*  Secondary DNS server             */
        Bool  recursive,                /*  Do recursive lookups?            */
        Bool  debug);                   /*  Debug DNS queries?               */

#define send_set_rdns(_to,                                                   \
                      primary,                                               \
                      secondary,                                             \
                      recursive,                                             \
                      debug)                                                 \
       lsend_set_rdns(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      primary,                                               \
                      secondary,                                             \
                      recursive,                                             \
                      debug)


#define XIXLOG_OPEN "sssssssssssB"

typedef struct {
    char *log_path;                     /*  Path for logfiles, or empty      */
    char *log_file;                     /*  Name of logfile                  */
    char *log_format;                   /*  Desired logging format           */
    char *log_header;                   /*  Log file header                  */
    char *cycle_when;                   /*  When to cycle logfile            */
    char *cycle_how;                    /*  How to cycle logfile             */
    char *cycle_time;                   /*  For time-based cycling           */
    char *cycle_date;                   /*  For date-based cycling           */
    char *cycle_size;                   /*  For size-based cycling           */
    char *cycle_lines;                  /*  For size-based cycling           */
    char *cycle_argument;               /*  For other cycle methods          */
    Bool  translate;                    /*  Do reverse-DNS translation?      */
} struct_xixlog_open;


int  get_xixlog_open         (byte *_buffer, struct_xixlog_open **params);
void free_xixlog_open        (struct_xixlog_open **params);
int  put_xixlog_open         (byte **_buffer, char *log_path, char *log_file, char *log_format, char *log_header, char *cycle_when, char *cycle_how, char *cycle_time, char *cycle_date, char *cycle_size, char *cycle_lines, char *cycle_argument, Bool  translate);

#define declare_open(_event, _priority)                                      \
    method_declare (agent, "OPEN", _event, _priority)

/*  Send event - Open log file                                               */

int lsend_open (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *log_path,                 /*  Path for logfiles, or empty      */
        char *log_file,                 /*  Name of logfile                  */
        char *log_format,               /*  Desired logging format           */
        char *log_header,               /*  Log file header                  */
        char *cycle_when,               /*  When to cycle logfile            */
        char *cycle_how,                /*  How to cycle logfile             */
        char *cycle_time,               /*  For time-based cycling           */
        char *cycle_date,               /*  For date-based cycling           */
        char *cycle_size,               /*  For size-based cycling           */
        char *cycle_lines,              /*  For size-based cycling           */
        char *cycle_argument,           /*  For other cycle methods          */
        Bool  translate);               /*  Do reverse-DNS translation?      */

#define send_open(_to,                                                       \
                  log_path,                                                  \
                  log_file,                                                  \
                  log_format,                                                \
                  log_header,                                                \
                  cycle_when,                                                \
                  cycle_how,                                                 \
                  cycle_time,                                                \
                  cycle_date,                                                \
                  cycle_size,                                                \
                  cycle_lines,                                               \
                  cycle_argument,                                            \
                  translate)                                                 \
       lsend_open(_to,                                                       \
                  &thread-> queue-> qid,                                     \
                  NULL, NULL, NULL, 0,                                       \
                  log_path,                                                  \
                  log_file,                                                  \
                  log_format,                                                \
                  log_header,                                                \
                  cycle_when,                                                \
                  cycle_how,                                                 \
                  cycle_time,                                                \
                  cycle_date,                                                \
                  cycle_size,                                                \
                  cycle_lines,                                               \
                  cycle_argument,                                            \
                  translate)


#define XIXLOG_LOG "sssssssssqqqsssss"

typedef struct {
    char *ip_client;                    /*  IP address of client             */
    char *ip_server;                    /*  IP address of server             */
    char *user_name;                    /*  User name, if known              */
    char *service;                      /*  HTTP or FTP                      */
    char *request;                      /*  Request line (HTTP)              */
    char *url;                          /*  Requested resource               */
    char *query;                        /*  Query string (HTTP)              */
    char *method;                       /*  HTTP method or FTP operation     */
    char *response;                     /*  Response code, 3 digits          */
    qbyte size_recd;                    /*  Request size in bytes            */
    qbyte size_sent;                    /*  Response size in bytes           */
    qbyte time_ms;                      /*  Processing time, in msecs        */
    char *referer;                      /*  HTTP Referer field               */
    char *agent;                        /*  HTTP User-Agent field            */
    char *from;                         /*  HTTP From field                  */
    char *file_name;                    /*  Filename used for request        */
    char *vhost_name;                   /*  Virtual host used for request    */
} struct_xixlog_log;


int  get_xixlog_log          (byte *_buffer, struct_xixlog_log **params);
void free_xixlog_log         (struct_xixlog_log **params);
int  put_xixlog_log          (byte **_buffer, char *ip_client, char *ip_server, char *user_name, char *service, char *request, char *url, char *query, char *method, char *response, qbyte size_recd, qbyte size_sent, qbyte time_ms, char *referer, char *agent, char *from, char *file_name, char *vhost_name);

#define declare_log(_event, _priority)                                       \
    method_declare (agent, "LOG", _event, _priority)

/*  Send event - Log normal request                                          */

int lsend_log (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *ip_client,                /*  IP address of client             */
        char *ip_server,                /*  IP address of server             */
        char *user_name,                /*  User name, if known              */
        char *service,                  /*  HTTP or FTP                      */
        char *request,                  /*  Request line (HTTP)              */
        char *url,                      /*  Requested resource               */
        char *query,                    /*  Query string (HTTP)              */
        char *method,                   /*  HTTP method or FTP operation     */
        char *response,                 /*  Response code, 3 digits          */
        qbyte size_recd,                /*  Request size in bytes            */
        qbyte size_sent,                /*  Response size in bytes           */
        qbyte time_ms,                  /*  Processing time, in msecs        */
        char *referer,                  /*  HTTP Referer field               */
        char *agent,                    /*  HTTP User-Agent field            */
        char *from,                     /*  HTTP From field                  */
        char *file_name,                /*  Filename used for request        */
        char *vhost_name);              /*  Virtual host used for request    */

#define send_log(_to,                                                        \
                 ip_client,                                                  \
                 ip_server,                                                  \
                 user_name,                                                  \
                 service,                                                    \
                 request,                                                    \
                 url,                                                        \
                 query,                                                      \
                 method,                                                     \
                 response,                                                   \
                 size_recd,                                                  \
                 size_sent,                                                  \
                 time_ms,                                                    \
                 referer,                                                    \
                 agent,                                                      \
                 from,                                                       \
                 file_name,                                                  \
                 vhost_name)                                                 \
       lsend_log(_to,                                                        \
                 &thread-> queue-> qid,                                      \
                 NULL, NULL, NULL, 0,                                        \
                 ip_client,                                                  \
                 ip_server,                                                  \
                 user_name,                                                  \
                 service,                                                    \
                 request,                                                    \
                 url,                                                        \
                 query,                                                      \
                 method,                                                     \
                 response,                                                   \
                 size_recd,                                                  \
                 size_sent,                                                  \
                 time_ms,                                                    \
                 referer,                                                    \
                 agent,                                                      \
                 from,                                                       \
                 file_name,                                                  \
                 vhost_name)


#define XIXLOG_PUT "s"

typedef struct {
    char *message;                      /*  Line of text to log              */
} struct_xixlog_put;


int  get_xixlog_put          (byte *_buffer, struct_xixlog_put **params);
void free_xixlog_put         (struct_xixlog_put **params);
int  put_xixlog_put          (byte **_buffer, char *message);

#define declare_put(_event, _priority)                                       \
    method_declare (agent, "PUT", _event, _priority)

/*  Send event - Log plain text request                                      */

int lsend_put (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *message);                 /*  Line of text to log              */

#define send_put(_to,                                                        \
                 message)                                                    \
       lsend_put(_to,                                                        \
                 &thread-> queue-> qid,                                      \
                 NULL, NULL, NULL, 0,                                        \
                 message)


#define XIXLOG_CYCLE ""


#define declare_cycle(_event, _priority)                                     \
    method_declare (agent, "CYCLE", _event, _priority)

/*  Send event - Cycle log file                                              */

int lsend_cycle (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_cycle(_to)                                                      \
       lsend_cycle(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0)


#define XIXLOG_CLEAR ""


#define declare_clear(_event, _priority)                                     \
    method_declare (agent, "CLEAR", _event, _priority)

/*  Send event - Clear log file                                              */

int lsend_clear (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_clear(_to)                                                      \
       lsend_clear(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0)


#define XIXLOG_CLOSE ""


#define declare_close(_event, _priority)                                     \
    method_declare (agent, "CLOSE", _event, _priority)

/*  Send event - Close log file                                              */

int lsend_close (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_close(_to)                                                      \
       lsend_close(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0)



#endif                                  /*  Included                         */

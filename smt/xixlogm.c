/*---------------------------------------------------------------------------
 *  xixlogm.c - functions for Xixlog messages.
 *
 *  Generated on 2004/07/22, 17:52:21 from xixlogm.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "xixlogm.h"                    /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for xixlog - Xitami Extended Logging Agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_xixlog_set_rdns    

    Synopsis: Formats a XIXLOG_SET_RDNS message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_xixlog_set_rdns (
    byte **_buffer,
    char *primary,                      /*  Primary DNS server               */
    char *secondary,                    /*  Secondary DNS server             */
    Bool  recursive,                    /*  Do recursive lookups?            */
    Bool  debug)                        /*  Debug DNS queries?               */
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_SET_RDNS, primary, secondary, recursive, debug);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_SET_RDNS, primary, secondary, recursive, debug);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_xixlog_set_rdns    

    Synopsis: Accepts a buffer containing a XIXLOG_SET_RDNS message,
    and unpacks it into a new structxixlog_set_rdns structure. Free the
    structure using free_xixlog_set_rdns() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_xixlog_set_rdns (
    byte *_buffer,
    struct_xixlog_set_rdns **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_set_rdns));
    if (*params)
      {
        (*params)-> primary = NULL;
        (*params)-> secondary = NULL;
        return (exdr_read (_buffer, XIXLOG_SET_RDNS,
                   &(*params)-> primary,
                   &(*params)-> secondary,
                   &(*params)-> recursive,
                   &(*params)-> debug));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_xixlog_set_rdns    

    Synopsis: frees a structure allocated by get_xixlog_set_rdns().
    ---------------------------------------------------------------------[>]-*/

void
free_xixlog_set_rdns (
    struct_xixlog_set_rdns **params)
{
    mem_free ((*params)-> primary);
    mem_free ((*params)-> secondary);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_set_rdns   

    Synopsis: Sends a SET_RDNS (Initialise RDNS interface event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_set_rdns (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *primary,                      /*  Primary DNS server               */
    char *secondary,                    /*  Secondary DNS server             */
    Bool  recursive,                    /*  Do recursive lookups?            */
    Bool  debug)                        /*  Debug DNS queries?               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_xixlog_set_rdns (&_body, primary, secondary, recursive, debug);
    if (_size)
      {
        _rc = event_send (_to, _from, "SET_RDNS",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_xixlog_open        

    Synopsis: Formats a XIXLOG_OPEN message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_xixlog_open (
    byte **_buffer,
    char *log_path,                     /*  Path for logfiles, or empty      */
    char *log_file,                     /*  Name of logfile                  */
    char *log_format,                   /*  Desired logging format           */
    char *log_header,                   /*  Log file header                  */
    char *cycle_when,                   /*  When to cycle logfile            */
    char *cycle_how,                    /*  How to cycle logfile             */
    char *cycle_time,                   /*  For time-based cycling           */
    char *cycle_date,                   /*  For date-based cycling           */
    char *cycle_size,                   /*  For size-based cycling           */
    char *cycle_lines,                  /*  For size-based cycling           */
    char *cycle_argument,               /*  For other cycle methods          */
    Bool  translate)                    /*  Do reverse-DNS translation?      */
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_OPEN, log_path, log_file, log_format, log_header, cycle_when, cycle_how, cycle_time, cycle_date, cycle_size, cycle_lines, cycle_argument, translate);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_OPEN, log_path, log_file, log_format, log_header, cycle_when, cycle_how, cycle_time, cycle_date, cycle_size, cycle_lines, cycle_argument, translate);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_xixlog_open        

    Synopsis: Accepts a buffer containing a XIXLOG_OPEN message,
    and unpacks it into a new structxixlog_open structure. Free the
    structure using free_xixlog_open() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_xixlog_open (
    byte *_buffer,
    struct_xixlog_open **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_open));
    if (*params)
      {
        (*params)-> log_path = NULL;
        (*params)-> log_file = NULL;
        (*params)-> log_format = NULL;
        (*params)-> log_header = NULL;
        (*params)-> cycle_when = NULL;
        (*params)-> cycle_how = NULL;
        (*params)-> cycle_time = NULL;
        (*params)-> cycle_date = NULL;
        (*params)-> cycle_size = NULL;
        (*params)-> cycle_lines = NULL;
        (*params)-> cycle_argument = NULL;
        return (exdr_read (_buffer, XIXLOG_OPEN,
                   &(*params)-> log_path,
                   &(*params)-> log_file,
                   &(*params)-> log_format,
                   &(*params)-> log_header,
                   &(*params)-> cycle_when,
                   &(*params)-> cycle_how,
                   &(*params)-> cycle_time,
                   &(*params)-> cycle_date,
                   &(*params)-> cycle_size,
                   &(*params)-> cycle_lines,
                   &(*params)-> cycle_argument,
                   &(*params)-> translate));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_xixlog_open        

    Synopsis: frees a structure allocated by get_xixlog_open().
    ---------------------------------------------------------------------[>]-*/

void
free_xixlog_open (
    struct_xixlog_open **params)
{
    mem_free ((*params)-> log_path);
    mem_free ((*params)-> log_file);
    mem_free ((*params)-> log_format);
    mem_free ((*params)-> log_header);
    mem_free ((*params)-> cycle_when);
    mem_free ((*params)-> cycle_how);
    mem_free ((*params)-> cycle_time);
    mem_free ((*params)-> cycle_date);
    mem_free ((*params)-> cycle_size);
    mem_free ((*params)-> cycle_lines);
    mem_free ((*params)-> cycle_argument);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_open       

    Synopsis: Sends a OPEN (Open log file event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_open (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *log_path,                     /*  Path for logfiles, or empty      */
    char *log_file,                     /*  Name of logfile                  */
    char *log_format,                   /*  Desired logging format           */
    char *log_header,                   /*  Log file header                  */
    char *cycle_when,                   /*  When to cycle logfile            */
    char *cycle_how,                    /*  How to cycle logfile             */
    char *cycle_time,                   /*  For time-based cycling           */
    char *cycle_date,                   /*  For date-based cycling           */
    char *cycle_size,                   /*  For size-based cycling           */
    char *cycle_lines,                  /*  For size-based cycling           */
    char *cycle_argument,               /*  For other cycle methods          */
    Bool  translate)                    /*  Do reverse-DNS translation?      */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_xixlog_open (&_body, log_path, log_file, log_format, log_header, cycle_when, cycle_how, cycle_time, cycle_date, cycle_size, cycle_lines, cycle_argument, translate);
    if (_size)
      {
        _rc = event_send (_to, _from, "OPEN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_xixlog_log         

    Synopsis: Formats a XIXLOG_LOG message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_xixlog_log (
    byte **_buffer,
    char *ip_client,                    /*  IP address of client             */
    char *ip_server,                    /*  IP address of server             */
    char *user_name,                    /*  User name, if known              */
    char *service,                      /*  HTTP or FTP                      */
    char *request,                      /*  Request line (HTTP)              */
    char *url,                          /*  Requested resource               */
    char *query,                        /*  Query string (HTTP)              */
    char *method,                       /*  HTTP method or FTP operation     */
    char *response,                     /*  Response code, 3 digits          */
    qbyte size_recd,                    /*  Request size in bytes            */
    qbyte size_sent,                    /*  Response size in bytes           */
    qbyte time_ms,                      /*  Processing time, in msecs        */
    char *referer,                      /*  HTTP Referer field               */
    char *agent,                        /*  HTTP User-Agent field            */
    char *from,                         /*  HTTP From field                  */
    char *file_name,                    /*  Filename used for request        */
    char *vhost_name)                   /*  Virtual host used for request    */
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_LOG, ip_client, ip_server, user_name, service, request, url, query, method, response, size_recd, size_sent, time_ms, referer, agent, from, file_name, vhost_name);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_LOG, ip_client, ip_server, user_name, service, request, url, query, method, response, size_recd, size_sent, time_ms, referer, agent, from, file_name, vhost_name);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_xixlog_log         

    Synopsis: Accepts a buffer containing a XIXLOG_LOG message,
    and unpacks it into a new structxixlog_log structure. Free the
    structure using free_xixlog_log() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_xixlog_log (
    byte *_buffer,
    struct_xixlog_log **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_log));
    if (*params)
      {
        (*params)-> ip_client = NULL;
        (*params)-> ip_server = NULL;
        (*params)-> user_name = NULL;
        (*params)-> service = NULL;
        (*params)-> request = NULL;
        (*params)-> url = NULL;
        (*params)-> query = NULL;
        (*params)-> method = NULL;
        (*params)-> response = NULL;
        (*params)-> referer = NULL;
        (*params)-> agent = NULL;
        (*params)-> from = NULL;
        (*params)-> file_name = NULL;
        (*params)-> vhost_name = NULL;
        return (exdr_read (_buffer, XIXLOG_LOG,
                   &(*params)-> ip_client,
                   &(*params)-> ip_server,
                   &(*params)-> user_name,
                   &(*params)-> service,
                   &(*params)-> request,
                   &(*params)-> url,
                   &(*params)-> query,
                   &(*params)-> method,
                   &(*params)-> response,
                   &(*params)-> size_recd,
                   &(*params)-> size_sent,
                   &(*params)-> time_ms,
                   &(*params)-> referer,
                   &(*params)-> agent,
                   &(*params)-> from,
                   &(*params)-> file_name,
                   &(*params)-> vhost_name));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_xixlog_log         

    Synopsis: frees a structure allocated by get_xixlog_log().
    ---------------------------------------------------------------------[>]-*/

void
free_xixlog_log (
    struct_xixlog_log **params)
{
    mem_free ((*params)-> ip_client);
    mem_free ((*params)-> ip_server);
    mem_free ((*params)-> user_name);
    mem_free ((*params)-> service);
    mem_free ((*params)-> request);
    mem_free ((*params)-> url);
    mem_free ((*params)-> query);
    mem_free ((*params)-> method);
    mem_free ((*params)-> response);
    mem_free ((*params)-> referer);
    mem_free ((*params)-> agent);
    mem_free ((*params)-> from);
    mem_free ((*params)-> file_name);
    mem_free ((*params)-> vhost_name);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_log        

    Synopsis: Sends a LOG (Log normal request event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_log (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *ip_client,                    /*  IP address of client             */
    char *ip_server,                    /*  IP address of server             */
    char *user_name,                    /*  User name, if known              */
    char *service,                      /*  HTTP or FTP                      */
    char *request,                      /*  Request line (HTTP)              */
    char *url,                          /*  Requested resource               */
    char *query,                        /*  Query string (HTTP)              */
    char *method,                       /*  HTTP method or FTP operation     */
    char *response,                     /*  Response code, 3 digits          */
    qbyte size_recd,                    /*  Request size in bytes            */
    qbyte size_sent,                    /*  Response size in bytes           */
    qbyte time_ms,                      /*  Processing time, in msecs        */
    char *referer,                      /*  HTTP Referer field               */
    char *agent,                        /*  HTTP User-Agent field            */
    char *from,                         /*  HTTP From field                  */
    char *file_name,                    /*  Filename used for request        */
    char *vhost_name)                   /*  Virtual host used for request    */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_xixlog_log (&_body, ip_client, ip_server, user_name, service, request, url, query, method, response, size_recd, size_sent, time_ms, referer, agent, from, file_name, vhost_name);
    if (_size)
      {
        _rc = event_send (_to, _from, "LOG",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_xixlog_put         

    Synopsis: Formats a XIXLOG_PUT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_xixlog_put (
    byte **_buffer,
    char *message)                      /*  Line of text to log              */
{
    int _size;

    _size = exdr_write (NULL, XIXLOG_PUT, message);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, XIXLOG_PUT, message);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_xixlog_put         

    Synopsis: Accepts a buffer containing a XIXLOG_PUT message,
    and unpacks it into a new structxixlog_put structure. Free the
    structure using free_xixlog_put() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_xixlog_put (
    byte *_buffer,
    struct_xixlog_put **params)
{
    *params = mem_alloc (sizeof (struct_xixlog_put));
    if (*params)
      {
        (*params)-> message = NULL;
        return (exdr_read (_buffer, XIXLOG_PUT,
                   &(*params)-> message));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_xixlog_put         

    Synopsis: frees a structure allocated by get_xixlog_put().
    ---------------------------------------------------------------------[>]-*/

void
free_xixlog_put (
    struct_xixlog_put **params)
{
    mem_free ((*params)-> message);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_put        

    Synopsis: Sends a PUT (Log plain text request event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_put (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *message)                      /*  Line of text to log              */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_xixlog_put (&_body, message);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_cycle      

    Synopsis: Sends a CYCLE (Cycle log file event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_cycle (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "CYCLE", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_clear      

    Synopsis: Sends a CLEAR (Clear log file event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_clear (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "CLEAR", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_close      

    Synopsis: Sends a CLOSE (Close log file event to
    the xixlog agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_close (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "CLOSE", NULL, 0, _accept,
            _reject, _expire, _timeout));
}



/*---------------------------------------------------------------------------
 *  smtsslm.c - functions for Smtssl messages.
 *
 *  Generated on 2004/07/22, 17:52:21 from smtsslm.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "smtsslm.h"                    /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for smtssl - SMT SSL agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_open           

    Synopsis: Formats a SSL_OPEN message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_open (
    byte **_buffer,
    char *config)                       /*  Configuration file to use        */
{
    int _size;

    _size = exdr_write (NULL, SSL_OPEN, config);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_OPEN, config);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_open           

    Synopsis: Accepts a buffer containing a SSL_OPEN message,
    and unpacks it into a new structssl_open structure. Free the
    structure using free_ssl_open() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_open (
    byte *_buffer,
    struct_ssl_open **params)
{
    *params = mem_alloc (sizeof (struct_ssl_open));
    if (*params)
      {
        (*params)-> config = NULL;
        return (exdr_read (_buffer, SSL_OPEN,
                   &(*params)-> config));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_open           

    Synopsis: frees a structure allocated by get_ssl_open().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_open (
    struct_ssl_open **params)
{
    mem_free ((*params)-> config);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_open   

    Synopsis: Sends a SSL_OPEN (Open SSL port event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_open (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *config)                       /*  Configuration file to use        */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_open (&_body, config);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_OPEN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_open_ok        

    Synopsis: Formats a SSL_OPEN_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_open_ok (
    byte **_buffer,
    dbyte port)                         /*  SSL port opened                  */
{
    int _size;

    _size = exdr_write (NULL, SSL_OPEN_OK, port);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_OPEN_OK, port);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_open_ok        

    Synopsis: Accepts a buffer containing a SSL_OPEN_OK message,
    and unpacks it into a new structssl_open_ok structure. Free the
    structure using free_ssl_open_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_open_ok (
    byte *_buffer,
    struct_ssl_open_ok **params)
{
    *params = mem_alloc (sizeof (struct_ssl_open_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_OPEN_OK,
                   &(*params)-> port));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_open_ok        

    Synopsis: frees a structure allocated by get_ssl_open_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_open_ok (
    struct_ssl_open_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_open_ok  

    Synopsis: Sends a SSL_OPEN_OK (SSL port opened OK event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_open_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte port)                         /*  SSL port opened                  */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_open_ok (&_body, port);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_OPEN_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_close  

    Synopsis: Sends a SSL_CLOSE (Close SSL port event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_close (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "SSL_CLOSE", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_restart  

    Synopsis: Sends a SSL_RESTART (Restart SSL connection event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_restart (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "SSL_RESTART", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_accepted       

    Synopsis: Formats a SSL_ACCEPTED message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_accepted (
    byte **_buffer,
    qbyte socket,                       /*  Socket handle for SSL connection  */
    char *user,                         /*  User name                        */
    char *cipher,                       /*  Cipher used                      */
    dbyte verify)                       /*  Level of user verification       */
{
    int _size;

    _size = exdr_write (NULL, SSL_ACCEPTED, socket, user, cipher, verify);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_ACCEPTED, socket, user, cipher, verify);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_accepted       

    Synopsis: Accepts a buffer containing a SSL_ACCEPTED message,
    and unpacks it into a new structssl_accepted structure. Free the
    structure using free_ssl_accepted() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_accepted (
    byte *_buffer,
    struct_ssl_accepted **params)
{
    *params = mem_alloc (sizeof (struct_ssl_accepted));
    if (*params)
      {
        (*params)-> user = NULL;
        (*params)-> cipher = NULL;
        return (exdr_read (_buffer, SSL_ACCEPTED,
                   &(*params)-> socket,
                   &(*params)-> user,
                   &(*params)-> cipher,
                   &(*params)-> verify));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_accepted       

    Synopsis: frees a structure allocated by get_ssl_accepted().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_accepted (
    struct_ssl_accepted **params)
{
    mem_free ((*params)-> user);
    mem_free ((*params)-> cipher);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_accepted  

    Synopsis: Sends a SSL_ACCEPTED (Accept SSL connection event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_accepted (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket handle for SSL connection  */
    char *user,                         /*  User name                        */
    char *cipher,                       /*  Cipher used                      */
    dbyte verify)                       /*  Level of user verification       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_accepted (&_body, socket, user, cipher, verify);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_ACCEPTED",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_read_request   

    Synopsis: Formats a SSL_READ_REQUEST message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_read_request (
    byte **_buffer,
    qbyte size)                         /*  Maximum size to read             */
{
    int _size;

    _size = exdr_write (NULL, SSL_READ_REQUEST, size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_READ_REQUEST, size);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_read_request   

    Synopsis: Accepts a buffer containing a SSL_READ_REQUEST message,
    and unpacks it into a new structssl_read_request structure. Free the
    structure using free_ssl_read_request() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_read_request (
    byte *_buffer,
    struct_ssl_read_request **params)
{
    *params = mem_alloc (sizeof (struct_ssl_read_request));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_READ_REQUEST,
                   &(*params)-> size));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_read_request   

    Synopsis: frees a structure allocated by get_ssl_read_request().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_read_request (
    struct_ssl_read_request **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_read_request  

    Synopsis: Sends a SSL_READ_REQUEST (Request read event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_read_request (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte size)                         /*  Maximum size to read             */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_read_request (&_body, size);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_READ_REQUEST",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_write_request  

    Synopsis: Formats a SSL_WRITE_REQUEST message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_write_request (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to write to               */
    word  size,                         /*  Amount of data to write          */
    byte *data,                         /*  Block of data to write           */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SSL_WRITE_REQUEST, timeout, socket, size, data, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_WRITE_REQUEST, timeout, socket, size, data, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_write_request  

    Synopsis: Accepts a buffer containing a SSL_WRITE_REQUEST message,
    and unpacks it into a new structssl_write_request structure. Free the
    structure using free_ssl_write_request() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_write_request (
    byte *_buffer,
    struct_ssl_write_request **params)
{
    *params = mem_alloc (sizeof (struct_ssl_write_request));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SSL_WRITE_REQUEST,
                   &(*params)-> timeout,
                   &(*params)-> socket,
                   &(*params)-> size,
                   &(*params)-> data,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_write_request  

    Synopsis: frees a structure allocated by get_ssl_write_request().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_write_request (
    struct_ssl_write_request **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_write_request  

    Synopsis: Sends a SSL_WRITE_REQUEST (Write SSL data event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_write_request (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to write to               */
    word  size,                         /*  Amount of data to write          */
    byte *data,                         /*  Block of data to write           */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_write_request (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_WRITE_REQUEST",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_put_slice      

    Synopsis: Formats a SSL_PUT_SLICE message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_put_slice (
    byte **_buffer,
    qbyte socket,                       /*  Socket for output                */
    char *filename,                     /*  Name of file to send             */
    qbyte start,                        /*  Starting offset; 0 = start       */
    qbyte end)                          /*  Ending offset; 0 = end           */
{
    int _size;

    _size = exdr_write (NULL, SSL_PUT_SLICE, socket, filename, start, end);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_PUT_SLICE, socket, filename, start, end);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_put_slice      

    Synopsis: Accepts a buffer containing a SSL_PUT_SLICE message,
    and unpacks it into a new structssl_put_slice structure. Free the
    structure using free_ssl_put_slice() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_put_slice (
    byte *_buffer,
    struct_ssl_put_slice **params)
{
    *params = mem_alloc (sizeof (struct_ssl_put_slice));
    if (*params)
      {
        (*params)-> filename = NULL;
        return (exdr_read (_buffer, SSL_PUT_SLICE,
                   &(*params)-> socket,
                   &(*params)-> filename,
                   &(*params)-> start,
                   &(*params)-> end));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_put_slice      

    Synopsis: frees a structure allocated by get_ssl_put_slice().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_put_slice (
    struct_ssl_put_slice **params)
{
    mem_free ((*params)-> filename);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_put_slice  

    Synopsis: Sends a SSL_PUT_SLICE (Write file slice to SSL socket event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_put_slice (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for output                */
    char *filename,                     /*  Name of file to send             */
    qbyte start,                        /*  Starting offset; 0 = start       */
    qbyte end)                          /*  Ending offset; 0 = end           */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_put_slice (&_body, socket, filename, start, end);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_PUT_SLICE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_error          

    Synopsis: Formats a SSL_ERROR message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_error (
    byte **_buffer,
    qbyte code)                         /*  Error code                       */
{
    int _size;

    _size = exdr_write (NULL, SSL_ERROR, code);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_ERROR, code);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_error          

    Synopsis: Accepts a buffer containing a SSL_ERROR message,
    and unpacks it into a new structssl_error structure. Free the
    structure using free_ssl_error() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_error (
    byte *_buffer,
    struct_ssl_error **params)
{
    *params = mem_alloc (sizeof (struct_ssl_error));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_ERROR,
                   &(*params)-> code));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_error          

    Synopsis: frees a structure allocated by get_ssl_error().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_error (
    struct_ssl_error **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_error  

    Synopsis: Sends a SSL_ERROR (Signal SSL error event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_error (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte code)                         /*  Error code                       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_error (&_body, code);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_write_ok       

    Synopsis: Formats a SSL_WRITE_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_write_ok (
    byte **_buffer,
    qbyte socket,                       /*  Socket used for i/o, or new socket  */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SSL_WRITE_OK, socket, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_WRITE_OK, socket, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_write_ok       

    Synopsis: Accepts a buffer containing a SSL_WRITE_OK message,
    and unpacks it into a new structssl_write_ok structure. Free the
    structure using free_ssl_write_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_write_ok (
    byte *_buffer,
    struct_ssl_write_ok **params)
{
    *params = mem_alloc (sizeof (struct_ssl_write_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_WRITE_OK,
                   &(*params)-> socket,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_write_ok       

    Synopsis: frees a structure allocated by get_ssl_write_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_write_ok (
    struct_ssl_write_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_write_ok  

    Synopsis: Sends a SSL_WRITE_OK (Write OK reply event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_write_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket used for i/o, or new socket  */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_write_ok (&_body, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_WRITE_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_read_ok        

    Synopsis: Formats a SSL_READ_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_read_ok (
    byte **_buffer,
    word  size,                         /*  Size of result                   */
    byte *data)                         /*  Read data                        */
{
    int _size;

    _size = exdr_write (NULL, SSL_READ_OK, size, data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_READ_OK, size, data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_read_ok        

    Synopsis: Accepts a buffer containing a SSL_READ_OK message,
    and unpacks it into a new structssl_read_ok structure. Free the
    structure using free_ssl_read_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_read_ok (
    byte *_buffer,
    struct_ssl_read_ok **params)
{
    *params = mem_alloc (sizeof (struct_ssl_read_ok));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SSL_READ_OK,
                   &(*params)-> size,
                   &(*params)-> data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_read_ok        

    Synopsis: frees a structure allocated by get_ssl_read_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_read_ok (
    struct_ssl_read_ok **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_read_ok  

    Synopsis: Sends a SSL_READ_OK (Read result data event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_read_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    word  size,                         /*  Size of result                   */
    byte *data)                         /*  Read data                        */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_read_ok (&_body, size, data);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_READ_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_ssl_put_slice_ok   

    Synopsis: Formats a SSL_PUT_SLICE_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_ssl_put_slice_ok (
    byte **_buffer,
    qbyte size)                         /*  Amount of transmitted data       */
{
    int _size;

    _size = exdr_write (NULL, SSL_PUT_SLICE_OK, size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SSL_PUT_SLICE_OK, size);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_ssl_put_slice_ok   

    Synopsis: Accepts a buffer containing a SSL_PUT_SLICE_OK message,
    and unpacks it into a new structssl_put_slice_ok structure. Free the
    structure using free_ssl_put_slice_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_ssl_put_slice_ok (
    byte *_buffer,
    struct_ssl_put_slice_ok **params)
{
    *params = mem_alloc (sizeof (struct_ssl_put_slice_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SSL_PUT_SLICE_OK,
                   &(*params)-> size));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_ssl_put_slice_ok   

    Synopsis: frees a structure allocated by get_ssl_put_slice_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_ssl_put_slice_ok (
    struct_ssl_put_slice_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ssl_put_slice_ok  

    Synopsis: Sends a SSL_PUT_SLICE_OK (File written okay event to
    the smtssl agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ssl_put_slice_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte size)                         /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_ssl_put_slice_ok (&_body, size);
    if (_size)
      {
        _rc = event_send (_to, _from, "SSL_PUT_SLICE_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}



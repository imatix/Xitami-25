/*---------------------------------------------------------------------------
 *  smtmsg.c - functions for SMT standard messages.
 *
 *  Generated on 2004/07/22, 17:52:20 from smtmsg.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "smtmsg.h"                     /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for smtopen - Operator agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_oper_log       

    Synopsis: Formats a SMT_OPER_LOG message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_oper_log (
    byte **_buffer,
    char *agent_name,                   /*  Name of logging agent            */
    char *thread_name)                  /*  Name of logging thread           */
{
    int _size;

    _size = exdr_write (NULL, SMT_OPER_LOG, agent_name, thread_name);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_OPER_LOG, agent_name, thread_name);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_oper_log       

    Synopsis: Accepts a buffer containing a SMT_OPER_LOG message,
    and unpacks it into a new structsmt_oper_log structure. Free the
    structure using free_smt_oper_log() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_oper_log (
    byte *_buffer,
    struct_smt_oper_log **params)
{
    *params = mem_alloc (sizeof (struct_smt_oper_log));
    if (*params)
      {
        (*params)-> agent_name = NULL;
        (*params)-> thread_name = NULL;
        return (exdr_read (_buffer, SMT_OPER_LOG,
                   &(*params)-> agent_name,
                   &(*params)-> thread_name));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_oper_log       

    Synopsis: frees a structure allocated by get_smt_oper_log().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_oper_log (
    struct_smt_oper_log **params)
{
    mem_free ((*params)-> agent_name);
    mem_free ((*params)-> thread_name);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_set_log    

    Synopsis: Sends a SET_LOG (Specify logging agent event to
    the smtopen agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_set_log (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *agent_name,                   /*  Name of logging agent            */
    char *thread_name)                  /*  Name of logging thread           */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_oper_log (&_body, agent_name, thread_name);
    if (_size)
      {
        _rc = event_send (_to, _from, "SET_LOG",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtsock - Socket i/o agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_read      

    Synopsis: Formats a SMT_SOCK_READ message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_read (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to read from              */
    dbyte max_size,                     /*  Size of receiving buffer         */
    dbyte min_size,                     /*  Minimum data to read, zero = all  */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READ, timeout, socket, max_size, min_size, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READ, timeout, socket, max_size, min_size, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_read      

    Synopsis: Accepts a buffer containing a SMT_SOCK_READ message,
    and unpacks it into a new structsmt_sock_read structure. Free the
    structure using free_smt_sock_read() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_read (
    byte *_buffer,
    struct_smt_sock_read **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_read));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_READ,
                   &(*params)-> timeout,
                   &(*params)-> socket,
                   &(*params)-> max_size,
                   &(*params)-> min_size,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_read      

    Synopsis: frees a structure allocated by get_smt_sock_read().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_read (
    struct_smt_sock_read **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_read       

    Synopsis: Sends a READ (Read socket data event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_read (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to read from              */
    dbyte max_size,                     /*  Size of receiving buffer         */
    dbyte min_size,                     /*  Minimum data to read, zero = all  */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_read (&_body, timeout, socket, max_size, min_size, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "READ",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_readr      

    Synopsis: Sends a READR (Read, repeat for ever event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_readr (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to read from              */
    dbyte max_size,                     /*  Size of receiving buffer         */
    dbyte min_size,                     /*  Minimum data to read, zero = all  */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_read (&_body, timeout, socket, max_size, min_size, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "READR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_write     

    Synopsis: Formats a SMT_SOCK_WRITE message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_write (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to write to               */
    word  size,                         /*  Amount of data to write          */
    byte *data,                         /*  Block of data to write           */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_WRITE, timeout, socket, size, data, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_WRITE, timeout, socket, size, data, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_write     

    Synopsis: Accepts a buffer containing a SMT_SOCK_WRITE message,
    and unpacks it into a new structsmt_sock_write structure. Free the
    structure using free_smt_sock_write() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_write (
    byte *_buffer,
    struct_smt_sock_write **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_write));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_WRITE,
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
    Function: free_smt_sock_write     

    Synopsis: frees a structure allocated by get_smt_sock_write().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_write (
    struct_smt_sock_write **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_write      

    Synopsis: Sends a WRITE (Write socket data event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_write (QID *_to, QID *_from,
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

    _size = put_smt_sock_write (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "WRITE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_readh     

    Synopsis: Formats a SMT_SOCK_READH message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_readh (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to read from              */
    qbyte max_size,                     /*  Size of receiving buffer         */
    qbyte min_size,                     /*  Minimum data to read, zero = all  */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READH, timeout, socket, max_size, min_size, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READH, timeout, socket, max_size, min_size, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_readh     

    Synopsis: Accepts a buffer containing a SMT_SOCK_READH message,
    and unpacks it into a new structsmt_sock_readh structure. Free the
    structure using free_smt_sock_readh() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_readh (
    byte *_buffer,
    struct_smt_sock_readh **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_readh));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_READH,
                   &(*params)-> timeout,
                   &(*params)-> socket,
                   &(*params)-> max_size,
                   &(*params)-> min_size,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_readh     

    Synopsis: frees a structure allocated by get_smt_sock_readh().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_readh (
    struct_smt_sock_readh **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_readh      

    Synopsis: Sends a READH (Read huge socket data event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_readh (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to read from              */
    qbyte max_size,                     /*  Size of receiving buffer         */
    qbyte min_size,                     /*  Minimum data to read, zero = all  */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_readh (&_body, timeout, socket, max_size, min_size, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "READH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_readrh     

    Synopsis: Sends a READRH (Read huge, repeat for ever event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_readrh (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to read from              */
    qbyte max_size,                     /*  Size of receiving buffer         */
    qbyte min_size,                     /*  Minimum data to read, zero = all  */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_readh (&_body, timeout, socket, max_size, min_size, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "READRH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_writeh    

    Synopsis: Formats a SMT_SOCK_WRITEH message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_writeh (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to write to               */
    qbyte size,                         /*  Amount of data to write          */
    byte *data,                         /*  Block of data to write           */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_WRITEH, timeout, socket, size, data, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_WRITEH, timeout, socket, size, data, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_writeh    

    Synopsis: Accepts a buffer containing a SMT_SOCK_WRITEH message,
    and unpacks it into a new structsmt_sock_writeh structure. Free the
    structure using free_smt_sock_writeh() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_writeh (
    byte *_buffer,
    struct_smt_sock_writeh **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_writeh));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_WRITEH,
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
    Function: free_smt_sock_writeh    

    Synopsis: frees a structure allocated by get_smt_sock_writeh().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_writeh (
    struct_smt_sock_writeh **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_writeh     

    Synopsis: Sends a WRITEH (Write huge socket data event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_writeh (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to write to               */
    qbyte size,                         /*  Amount of data to write          */
    byte *data,                         /*  Block of data to write           */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_writeh (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "WRITEH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_input     

    Synopsis: Formats a SMT_SOCK_INPUT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_input (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to wait on                */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_INPUT, timeout, socket, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_INPUT, timeout, socket, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_input     

    Synopsis: Accepts a buffer containing a SMT_SOCK_INPUT message,
    and unpacks it into a new structsmt_sock_input structure. Free the
    structure using free_smt_sock_input() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_input (
    byte *_buffer,
    struct_smt_sock_input **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_input));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_INPUT,
                   &(*params)-> timeout,
                   &(*params)-> socket,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_input     

    Synopsis: frees a structure allocated by get_smt_sock_input().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_input (
    struct_smt_sock_input **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_input      

    Synopsis: Sends a INPUT (Wait for input event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_input (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to wait on                */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_input (&_body, timeout, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "INPUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_inputr     

    Synopsis: Sends a INPUTR (Wait input, repeat event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_inputr (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to wait on                */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_input (&_body, timeout, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "INPUTR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_output    

    Synopsis: Formats a SMT_SOCK_OUTPUT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_output (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to wait on                */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_OUTPUT, timeout, socket, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_OUTPUT, timeout, socket, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_output    

    Synopsis: Accepts a buffer containing a SMT_SOCK_OUTPUT message,
    and unpacks it into a new structsmt_sock_output structure. Free the
    structure using free_smt_sock_output() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_output (
    byte *_buffer,
    struct_smt_sock_output **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_output));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_OUTPUT,
                   &(*params)-> timeout,
                   &(*params)-> socket,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_output    

    Synopsis: frees a structure allocated by get_smt_sock_output().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_output (
    struct_smt_sock_output **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_output     

    Synopsis: Sends a OUTPUT (Wait for output event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_output (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    qbyte socket,                       /*  Socket to wait on                */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_output (&_body, timeout, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "OUTPUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_connect   

    Synopsis: Formats a SMT_SOCK_CONNECT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_connect (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    char *type,                         /*  Type, UDP or TCP                 */
    char *host,                         /*  Host, name or dotted address, or NULL  */
    char *service,                      /*  Service, as name or port in ASCII, or NULL  */
    dbyte port,                         /*  16-bit host port, or 0           */
    qbyte address,                      /*  32-bit host address, or 0        */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_CONNECT, timeout, type, host, service, port, address, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_CONNECT, timeout, type, host, service, port, address, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_connect   

    Synopsis: Accepts a buffer containing a SMT_SOCK_CONNECT message,
    and unpacks it into a new structsmt_sock_connect structure. Free the
    structure using free_smt_sock_connect() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_connect (
    byte *_buffer,
    struct_smt_sock_connect **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_connect));
    if (*params)
      {
        (*params)-> type = NULL;
        (*params)-> host = NULL;
        (*params)-> service = NULL;
        return (exdr_read (_buffer, SMT_SOCK_CONNECT,
                   &(*params)-> timeout,
                   &(*params)-> type,
                   &(*params)-> host,
                   &(*params)-> service,
                   &(*params)-> port,
                   &(*params)-> address,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_connect   

    Synopsis: frees a structure allocated by get_smt_sock_connect().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_connect (
    struct_smt_sock_connect **params)
{
    mem_free ((*params)-> type);
    mem_free ((*params)-> host);
    mem_free ((*params)-> service);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_connect    

    Synopsis: Sends a CONNECT (Connect to host event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_connect (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout in seconds, zero = none  */
    char *type,                         /*  Type, UDP or TCP                 */
    char *host,                         /*  Host, name or dotted address, or NULL  */
    char *service,                      /*  Service, as name or port in ASCII, or NULL  */
    dbyte port,                         /*  16-bit host port, or 0           */
    qbyte address,                      /*  32-bit host address, or 0        */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_connect (&_body, timeout, type, host, service, port, address, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "CONNECT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_flush     

    Synopsis: Formats a SMT_SOCK_FLUSH message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_flush (
    byte **_buffer,
    qbyte socket)                       /*  Socket to flush requests for     */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_FLUSH, socket);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_FLUSH, socket);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_flush     

    Synopsis: Accepts a buffer containing a SMT_SOCK_FLUSH message,
    and unpacks it into a new structsmt_sock_flush structure. Free the
    structure using free_smt_sock_flush() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_flush (
    byte *_buffer,
    struct_smt_sock_flush **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_flush));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_FLUSH,
                   &(*params)-> socket));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_flush     

    Synopsis: frees a structure allocated by get_smt_sock_flush().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_flush (
    struct_smt_sock_flush **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_flush      

    Synopsis: Sends a FLUSH (Flush requests event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_flush (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket)                       /*  Socket to flush requests for     */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_flush (&_body, socket);
    if (_size)
      {
        _rc = event_send (_to, _from, "FLUSH",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_read_ok   

    Synopsis: Formats a SMT_SOCK_READ_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_read_ok (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout from read request        */
    qbyte socket,                       /*  Socket used for i/o              */
    word  size,                         /*  Amount of data read              */
    byte *data,                         /*  Block of data read               */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READ_OK, timeout, socket, size, data, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READ_OK, timeout, socket, size, data, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_read_ok   

    Synopsis: Accepts a buffer containing a SMT_SOCK_READ_OK message,
    and unpacks it into a new structsmt_sock_read_ok structure. Free the
    structure using free_smt_sock_read_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_read_ok (
    byte *_buffer,
    struct_smt_sock_read_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_read_ok));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_READ_OK,
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
    Function: free_smt_sock_read_ok   

    Synopsis: frees a structure allocated by get_smt_sock_read_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_read_ok (
    struct_smt_sock_read_ok **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_read_ok  

    Synopsis: Sends a SOCK_READ_OK (Read OK reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_read_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout from read request        */
    qbyte socket,                       /*  Socket used for i/o              */
    word  size,                         /*  Amount of data read              */
    byte *data,                         /*  Block of data read               */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_read_ok (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_READ_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_closed  

    Synopsis: Sends a SOCK_CLOSED (Closed reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_closed (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout from read request        */
    qbyte socket,                       /*  Socket used for i/o              */
    word  size,                         /*  Amount of data read              */
    byte *data,                         /*  Block of data read               */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_read_ok (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_CLOSED",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_timeout  

    Synopsis: Sends a SOCK_TIMEOUT (Timeout reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_timeout (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout from read request        */
    qbyte socket,                       /*  Socket used for i/o              */
    word  size,                         /*  Amount of data read              */
    byte *data,                         /*  Block of data read               */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_read_ok (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_TIMEOUT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_readh_ok  

    Synopsis: Formats a SMT_SOCK_READH_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_readh_ok (
    byte **_buffer,
    dbyte timeout,                      /*  Timeout from read request        */
    qbyte socket,                       /*  Socket used for i/o              */
    qbyte size,                         /*  Amount of data read              */
    byte *data,                         /*  Block of data read               */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_READH_OK, timeout, socket, size, data, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_READH_OK, timeout, socket, size, data, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_readh_ok  

    Synopsis: Accepts a buffer containing a SMT_SOCK_READH_OK message,
    and unpacks it into a new structsmt_sock_readh_ok structure. Free the
    structure using free_smt_sock_readh_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_readh_ok (
    byte *_buffer,
    struct_smt_sock_readh_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_readh_ok));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SMT_SOCK_READH_OK,
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
    Function: free_smt_sock_readh_ok  

    Synopsis: frees a structure allocated by get_smt_sock_readh_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_readh_ok (
    struct_smt_sock_readh_ok **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_readh_ok  

    Synopsis: Sends a SOCK_READH_OK (Read OK reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_readh_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte timeout,                      /*  Timeout from read request        */
    qbyte socket,                       /*  Socket used for i/o              */
    qbyte size,                         /*  Amount of data read              */
    byte *data,                         /*  Block of data read               */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_readh_ok (&_body, timeout, socket, size, data, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_READH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_ok        

    Synopsis: Formats a SMT_SOCK_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_ok (
    byte **_buffer,
    qbyte socket,                       /*  Socket used for i/o, or new socket  */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_OK, socket, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_OK, socket, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_ok        

    Synopsis: Accepts a buffer containing a SMT_SOCK_OK message,
    and unpacks it into a new structsmt_sock_ok structure. Free the
    structure using free_smt_sock_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_ok (
    byte *_buffer,
    struct_smt_sock_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_SOCK_OK,
                   &(*params)-> socket,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_ok        

    Synopsis: frees a structure allocated by get_smt_sock_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_ok (
    struct_smt_sock_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_write_ok  

    Synopsis: Sends a SOCK_WRITE_OK (Write OK reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_write_ok (QID *_to, QID *_from,
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

    _size = put_smt_sock_ok (&_body, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_WRITE_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_writeh_ok  

    Synopsis: Sends a SOCK_WRITEH_OK (Write OK reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_writeh_ok (QID *_to, QID *_from,
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

    _size = put_smt_sock_ok (&_body, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_WRITEH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_input_ok  

    Synopsis: Sends a SOCK_INPUT_OK (Input OK reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_input_ok (QID *_to, QID *_from,
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

    _size = put_smt_sock_ok (&_body, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_INPUT_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_output_ok  

    Synopsis: Sends a SOCK_OUTPUT_OK (Output OK reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_output_ok (QID *_to, QID *_from,
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

    _size = put_smt_sock_ok (&_body, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_OUTPUT_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_sock_error     

    Synopsis: Formats a SMT_SOCK_ERROR message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_sock_error (
    byte **_buffer,
    char *message,                      /*  Error message                    */
    qbyte socket,                       /*  Socket for i/o, or new socket    */
    qbyte tag)                          /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_SOCK_ERROR, message, socket, tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SOCK_ERROR, message, socket, tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_sock_error     

    Synopsis: Accepts a buffer containing a SMT_SOCK_ERROR message,
    and unpacks it into a new structsmt_sock_error structure. Free the
    structure using free_smt_sock_error() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_sock_error (
    byte *_buffer,
    struct_smt_sock_error **params)
{
    *params = mem_alloc (sizeof (struct_smt_sock_error));
    if (*params)
      {
        (*params)-> message = NULL;
        return (exdr_read (_buffer, SMT_SOCK_ERROR,
                   &(*params)-> message,
                   &(*params)-> socket,
                   &(*params)-> tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_sock_error     

    Synopsis: frees a structure allocated by get_smt_sock_error().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_sock_error (
    struct_smt_sock_error **params)
{
    mem_free ((*params)-> message);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_sock_error  

    Synopsis: Sends a SOCK_ERROR (Error reply event to
    the smtsock agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_sock_error (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *message,                      /*  Error message                    */
    qbyte socket,                       /*  Socket for i/o, or new socket    */
    qbyte tag)                          /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_sock_error (&_body, message, socket, tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "SOCK_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smttime - Timer agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_time_alarm     

    Synopsis: Formats a SMT_TIME_ALARM message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_time_alarm (
    byte **_buffer,
    qbyte days,                         /*  Time/delay in days               */
    qbyte csecs,                        /*  Time/delay in 1/100th seconds    */
    word  tag_size,                     /*  User-defined data size           */
    byte *tag_data)                     /*  User-defined data block          */
{
    int _size;

    _size = exdr_write (NULL, SMT_TIME_ALARM, days, csecs, tag_size, tag_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TIME_ALARM, days, csecs, tag_size, tag_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_time_alarm     

    Synopsis: Accepts a buffer containing a SMT_TIME_ALARM message,
    and unpacks it into a new structsmt_time_alarm structure. Free the
    structure using free_smt_time_alarm() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_time_alarm (
    byte *_buffer,
    struct_smt_time_alarm **params)
{
    *params = mem_alloc (sizeof (struct_smt_time_alarm));
    if (*params)
      {
        (*params)-> tag_data = NULL;
        return (exdr_read (_buffer, SMT_TIME_ALARM,
                   &(*params)-> days,
                   &(*params)-> csecs,
                   &(*params)-> tag_size,
                   &(*params)-> tag_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_time_alarm     

    Synopsis: frees a structure allocated by get_smt_time_alarm().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_time_alarm (
    struct_smt_time_alarm **params)
{
    mem_free ((*params)-> tag_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_alarm      

    Synopsis: Sends a ALARM (Ask for single alarm event to
    the smttime agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_alarm (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte days,                         /*  Time/delay in days               */
    qbyte csecs,                        /*  Time/delay in 1/100th seconds    */
    word  tag_size,                     /*  User-defined data size           */
    byte *tag_data)                     /*  User-defined data block          */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_time_alarm (&_body, days, csecs, tag_size, tag_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "ALARM",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_time_clock     

    Synopsis: Formats a SMT_TIME_CLOCK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_time_clock (
    byte **_buffer,
    qbyte days,                         /*  Time/delay in days               */
    qbyte csecs,                        /*  Time/delay in 1/100th seconds    */
    word  cycles,                       /*  Cycle count; zero = forever      */
    word  tag_size,                     /*  User-defined data size           */
    byte *tag_data)                     /*  User-defined data block          */
{
    int _size;

    _size = exdr_write (NULL, SMT_TIME_CLOCK, days, csecs, cycles, tag_size, tag_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TIME_CLOCK, days, csecs, cycles, tag_size, tag_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_time_clock     

    Synopsis: Accepts a buffer containing a SMT_TIME_CLOCK message,
    and unpacks it into a new structsmt_time_clock structure. Free the
    structure using free_smt_time_clock() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_time_clock (
    byte *_buffer,
    struct_smt_time_clock **params)
{
    *params = mem_alloc (sizeof (struct_smt_time_clock));
    if (*params)
      {
        (*params)-> tag_data = NULL;
        return (exdr_read (_buffer, SMT_TIME_CLOCK,
                   &(*params)-> days,
                   &(*params)-> csecs,
                   &(*params)-> cycles,
                   &(*params)-> tag_size,
                   &(*params)-> tag_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_time_clock     

    Synopsis: frees a structure allocated by get_smt_time_clock().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_time_clock (
    struct_smt_time_clock **params)
{
    mem_free ((*params)-> tag_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_clock      

    Synopsis: Sends a CLOCK (Ask for repeated alarm event to
    the smttime agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_clock (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte days,                         /*  Time/delay in days               */
    qbyte csecs,                        /*  Time/delay in 1/100th seconds    */
    word  cycles,                       /*  Cycle count; zero = forever      */
    word  tag_size,                     /*  User-defined data size           */
    byte *tag_data)                     /*  User-defined data block          */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_time_clock (&_body, days, csecs, cycles, tag_size, tag_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "CLOCK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_time_reply     

    Synopsis: Formats a SMT_TIME_REPLY message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_time_reply (
    byte **_buffer,
    word  tag_size,                     /*  User-defined data size           */
    byte *tag_data)                     /*  User-defined data block          */
{
    int _size;

    _size = exdr_write (NULL, SMT_TIME_REPLY, tag_size, tag_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TIME_REPLY, tag_size, tag_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_time_reply     

    Synopsis: Accepts a buffer containing a SMT_TIME_REPLY message,
    and unpacks it into a new structsmt_time_reply structure. Free the
    structure using free_smt_time_reply() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_time_reply (
    byte *_buffer,
    struct_smt_time_reply **params)
{
    *params = mem_alloc (sizeof (struct_smt_time_reply));
    if (*params)
      {
        (*params)-> tag_data = NULL;
        return (exdr_read (_buffer, SMT_TIME_REPLY,
                   &(*params)-> tag_size,
                   &(*params)-> tag_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_time_reply     

    Synopsis: frees a structure allocated by get_smt_time_reply().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_time_reply (
    struct_smt_time_reply **params)
{
    mem_free ((*params)-> tag_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_time_reply  

    Synopsis: Sends a TIME_REPLY (Alarm signal event to
    the smttime agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_time_reply (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    word  tag_size,                     /*  User-defined data size           */
    byte *tag_data)                     /*  User-defined data block          */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_time_reply (&_body, tag_size, tag_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "TIME_REPLY",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtslot - Time slot agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_slot_spec      

    Synopsis: Formats a SMT_SLOT_SPEC message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_slot_spec (
    byte **_buffer,
    char *specification)                /*  Time slot specification          */
{
    int _size;

    _size = exdr_write (NULL, SMT_SLOT_SPEC, specification);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_SLOT_SPEC, specification);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_slot_spec      

    Synopsis: Accepts a buffer containing a SMT_SLOT_SPEC message,
    and unpacks it into a new structsmt_slot_spec structure. Free the
    structure using free_smt_slot_spec() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_slot_spec (
    byte *_buffer,
    struct_smt_slot_spec **params)
{
    *params = mem_alloc (sizeof (struct_smt_slot_spec));
    if (*params)
      {
        (*params)-> specification = NULL;
        return (exdr_read (_buffer, SMT_SLOT_SPEC,
                   &(*params)-> specification));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_slot_spec      

    Synopsis: frees a structure allocated by get_smt_slot_spec().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_slot_spec (
    struct_smt_slot_spec **params)
{
    mem_free ((*params)-> specification);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_specify    

    Synopsis: Sends a SPECIFY (Specify a time slot event to
    the smtslot agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_specify (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *specification)                /*  Time slot specification          */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_slot_spec (&_body, specification);
    if (_size)
      {
        _rc = event_send (_to, _from, "SPECIFY",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smttran - Transfer agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_putb      

    Synopsis: Formats a SMT_TRAN_PUTB message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_putb (
    byte **_buffer,
    qbyte socket,                       /*  Socket for output                */
    word  size,                         /*  Amount of data to send           */
    byte *data,                         /*  Block of data to send            */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTB, socket, size, data, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTB, socket, size, data, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_putb      

    Synopsis: Accepts a buffer containing a SMT_TRAN_PUTB message,
    and unpacks it into a new structsmt_tran_putb structure. Free the
    structure using free_smt_tran_putb() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_putb (
    byte *_buffer,
    struct_smt_tran_putb **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putb));
    if (*params)
      {
        (*params)-> data = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_TRAN_PUTB,
                   &(*params)-> socket,
                   &(*params)-> size,
                   &(*params)-> data,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_putb      

    Synopsis: frees a structure allocated by get_smt_tran_putb().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_putb (
    struct_smt_tran_putb **params)
{
    mem_free ((*params)-> data);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_put_block  

    Synopsis: Sends a PUT_BLOCK (Write block to socket event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_put_block (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for output                */
    word  size,                         /*  Amount of data to send           */
    byte *data,                         /*  Block of data to send            */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_putb (&_body, socket, size, data, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT_BLOCK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_getb      

    Synopsis: Formats a SMT_TRAN_GETB message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_getb (
    byte **_buffer,
    qbyte socket,                       /*  Socket for input                 */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETB, socket, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETB, socket, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_getb      

    Synopsis: Accepts a buffer containing a SMT_TRAN_GETB message,
    and unpacks it into a new structsmt_tran_getb structure. Free the
    structure using free_smt_tran_getb() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_getb (
    byte *_buffer,
    struct_smt_tran_getb **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getb));
    if (*params)
      {
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETB,
                   &(*params)-> socket,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_getb      

    Synopsis: frees a structure allocated by get_smt_tran_getb().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_getb (
    struct_smt_tran_getb **params)
{
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_get_block  

    Synopsis: Sends a GET_BLOCK (Read block from socket event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_get_block (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for input                 */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_getb (&_body, socket, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_BLOCK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_puth      

    Synopsis: Formats a SMT_TRAN_PUTH message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_puth (
    byte **_buffer,
    qbyte socket,                       /*  Socket for output                */
    qbyte size,                         /*  Amount of data to send           */
    byte *data,                         /*  Block of data to send            */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTH, socket, size, data, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTH, socket, size, data, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_puth      

    Synopsis: Accepts a buffer containing a SMT_TRAN_PUTH message,
    and unpacks it into a new structsmt_tran_puth structure. Free the
    structure using free_smt_tran_puth() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_puth (
    byte *_buffer,
    struct_smt_tran_puth **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_puth));
    if (*params)
      {
        (*params)-> data = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_TRAN_PUTH,
                   &(*params)-> socket,
                   &(*params)-> size,
                   &(*params)-> data,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_puth      

    Synopsis: frees a structure allocated by get_smt_tran_puth().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_puth (
    struct_smt_tran_puth **params)
{
    mem_free ((*params)-> data);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_put_huge   

    Synopsis: Sends a PUT_HUGE (Write huge block to socket event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_put_huge (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for output                */
    qbyte size,                         /*  Amount of data to send           */
    byte *data,                         /*  Block of data to send            */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_puth (&_body, socket, size, data, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT_HUGE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_geth      

    Synopsis: Formats a SMT_TRAN_GETH message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_geth (
    byte **_buffer,
    qbyte socket,                       /*  Socket for input                 */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETH, socket, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETH, socket, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_geth      

    Synopsis: Accepts a buffer containing a SMT_TRAN_GETH message,
    and unpacks it into a new structsmt_tran_geth structure. Free the
    structure using free_smt_tran_geth() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_geth (
    byte *_buffer,
    struct_smt_tran_geth **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_geth));
    if (*params)
      {
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETH,
                   &(*params)-> socket,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_geth      

    Synopsis: frees a structure allocated by get_smt_tran_geth().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_geth (
    struct_smt_tran_geth **params)
{
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_get_huge   

    Synopsis: Sends a GET_HUGE (Read huge block from socket event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_get_huge (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for input                 */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_geth (&_body, socket, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_HUGE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_putf      

    Synopsis: Formats a SMT_TRAN_PUTF message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_putf (
    byte **_buffer,
    qbyte socket,                       /*  Socket for output                */
    char *filename,                     /*  Name of file to send             */
    dbyte filetype,                     /*  0=binary, 1=ASCII                */
    qbyte start,                        /*  Starting offset; 0 = start       */
    qbyte end,                          /*  Ending offset; 0 = end           */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTF, socket, filename, filetype, start, end, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTF, socket, filename, filetype, start, end, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_putf      

    Synopsis: Accepts a buffer containing a SMT_TRAN_PUTF message,
    and unpacks it into a new structsmt_tran_putf structure. Free the
    structure using free_smt_tran_putf() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_putf (
    byte *_buffer,
    struct_smt_tran_putf **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putf));
    if (*params)
      {
        (*params)-> filename = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_TRAN_PUTF,
                   &(*params)-> socket,
                   &(*params)-> filename,
                   &(*params)-> filetype,
                   &(*params)-> start,
                   &(*params)-> end,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_putf      

    Synopsis: frees a structure allocated by get_smt_tran_putf().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_putf (
    struct_smt_tran_putf **params)
{
    mem_free ((*params)-> filename);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_put_file   

    Synopsis: Sends a PUT_FILE (Write file to socket event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_put_file (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for output                */
    char *filename,                     /*  Name of file to send             */
    dbyte filetype,                     /*  0=binary, 1=ASCII                */
    qbyte start,                        /*  Starting offset; 0 = start       */
    qbyte end,                          /*  Ending offset; 0 = end           */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_putf (&_body, socket, filename, filetype, start, end, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "PUT_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_getf      

    Synopsis: Formats a SMT_TRAN_GETF message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_getf (
    byte **_buffer,
    qbyte socket,                       /*  Socket for input                 */
    char *filename,                     /*  Name of file to receive          */
    dbyte filetype,                     /*  0=binary, 1=ASCII                */
    qbyte start,                        /*  Starting offset; 0 = start       */
    qbyte end,                          /*  Ending offset; 0 = end           */
    Bool  append,                       /*  1 = append existing              */
    qbyte maxsize,                      /*  Max. size, -1 = no limit         */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETF, socket, filename, filetype, start, end, append, maxsize, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETF, socket, filename, filetype, start, end, append, maxsize, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_getf      

    Synopsis: Accepts a buffer containing a SMT_TRAN_GETF message,
    and unpacks it into a new structsmt_tran_getf structure. Free the
    structure using free_smt_tran_getf() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_getf (
    byte *_buffer,
    struct_smt_tran_getf **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getf));
    if (*params)
      {
        (*params)-> filename = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETF,
                   &(*params)-> socket,
                   &(*params)-> filename,
                   &(*params)-> filetype,
                   &(*params)-> start,
                   &(*params)-> end,
                   &(*params)-> append,
                   &(*params)-> maxsize,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_getf      

    Synopsis: frees a structure allocated by get_smt_tran_getf().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_getf (
    struct_smt_tran_getf **params)
{
    mem_free ((*params)-> filename);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_get_file   

    Synopsis: Sends a GET_FILE (Read file from socket event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_get_file (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte socket,                       /*  Socket for input                 */
    char *filename,                     /*  Name of file to receive          */
    dbyte filetype,                     /*  0=binary, 1=ASCII                */
    qbyte start,                        /*  Starting offset; 0 = start       */
    qbyte end,                          /*  Ending offset; 0 = end           */
    Bool  append,                       /*  1 = append existing              */
    qbyte maxsize,                      /*  Max. size, -1 = no limit         */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_getf (&_body, socket, filename, filetype, start, end, append, maxsize, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_putb_ok   

    Synopsis: Formats a SMT_TRAN_PUTB_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_putb_ok (
    byte **_buffer,
    dbyte size)                         /*  Amount of transmitted data       */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTB_OK, size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTB_OK, size);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_putb_ok   

    Synopsis: Accepts a buffer containing a SMT_TRAN_PUTB_OK message,
    and unpacks it into a new structsmt_tran_putb_ok structure. Free the
    structure using free_smt_tran_putb_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_putb_ok (
    byte *_buffer,
    struct_smt_tran_putb_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putb_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_PUTB_OK,
                   &(*params)-> size));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_putb_ok   

    Synopsis: frees a structure allocated by get_smt_tran_putb_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_putb_ok (
    struct_smt_tran_putb_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_putb_ok  

    Synopsis: Sends a TRAN_PUTB_OK (Block written okay event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_putb_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte size)                         /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_putb_ok (&_body, size);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_PUTB_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_getb_ok   

    Synopsis: Formats a SMT_TRAN_GETB_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_getb_ok (
    byte **_buffer,
    word  size,                         /*  Amount of data received          */
    byte *data)                         /*  Block of data received           */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETB_OK, size, data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETB_OK, size, data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_getb_ok   

    Synopsis: Accepts a buffer containing a SMT_TRAN_GETB_OK message,
    and unpacks it into a new structsmt_tran_getb_ok structure. Free the
    structure using free_smt_tran_getb_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_getb_ok (
    byte *_buffer,
    struct_smt_tran_getb_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getb_ok));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETB_OK,
                   &(*params)-> size,
                   &(*params)-> data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_getb_ok   

    Synopsis: frees a structure allocated by get_smt_tran_getb_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_getb_ok (
    struct_smt_tran_getb_ok **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_getb_ok  

    Synopsis: Sends a TRAN_GETB_OK (Block read okay event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_getb_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    word  size,                         /*  Amount of data received          */
    byte *data)                         /*  Block of data received           */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_getb_ok (&_body, size, data);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_GETB_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_puth_ok   

    Synopsis: Formats a SMT_TRAN_PUTH_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_puth_ok (
    byte **_buffer,
    qbyte size)                         /*  Amount of transmitted data       */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTH_OK, size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTH_OK, size);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_puth_ok   

    Synopsis: Accepts a buffer containing a SMT_TRAN_PUTH_OK message,
    and unpacks it into a new structsmt_tran_puth_ok structure. Free the
    structure using free_smt_tran_puth_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_puth_ok (
    byte *_buffer,
    struct_smt_tran_puth_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_puth_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_PUTH_OK,
                   &(*params)-> size));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_puth_ok   

    Synopsis: frees a structure allocated by get_smt_tran_puth_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_puth_ok (
    struct_smt_tran_puth_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_puth_ok  

    Synopsis: Sends a TRAN_PUTH_OK (Block written okay event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_puth_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte size)                         /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_puth_ok (&_body, size);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_PUTH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_geth_ok   

    Synopsis: Formats a SMT_TRAN_GETH_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_geth_ok (
    byte **_buffer,
    qbyte size,                         /*  Amount of data received          */
    byte *data)                         /*  Block of data received           */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETH_OK, size, data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETH_OK, size, data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_geth_ok   

    Synopsis: Accepts a buffer containing a SMT_TRAN_GETH_OK message,
    and unpacks it into a new structsmt_tran_geth_ok structure. Free the
    structure using free_smt_tran_geth_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_geth_ok (
    byte *_buffer,
    struct_smt_tran_geth_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_geth_ok));
    if (*params)
      {
        (*params)-> data = NULL;
        return (exdr_read (_buffer, SMT_TRAN_GETH_OK,
                   &(*params)-> size,
                   &(*params)-> data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_geth_ok   

    Synopsis: frees a structure allocated by get_smt_tran_geth_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_geth_ok (
    struct_smt_tran_geth_ok **params)
{
    mem_free ((*params)-> data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_geth_ok  

    Synopsis: Sends a TRAN_GETH_OK (Block read okay event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_geth_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte size,                         /*  Amount of data received          */
    byte *data)                         /*  Block of data received           */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_geth_ok (&_body, size, data);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_GETH_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_putf_ok   

    Synopsis: Formats a SMT_TRAN_PUTF_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_putf_ok (
    byte **_buffer,
    qbyte size)                         /*  Amount of transmitted data       */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_PUTF_OK, size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_PUTF_OK, size);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_putf_ok   

    Synopsis: Accepts a buffer containing a SMT_TRAN_PUTF_OK message,
    and unpacks it into a new structsmt_tran_putf_ok structure. Free the
    structure using free_smt_tran_putf_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_putf_ok (
    byte *_buffer,
    struct_smt_tran_putf_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_putf_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_PUTF_OK,
                   &(*params)-> size));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_putf_ok   

    Synopsis: frees a structure allocated by get_smt_tran_putf_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_putf_ok (
    struct_smt_tran_putf_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_putf_ok  

    Synopsis: Sends a TRAN_PUTF_OK (File written okay event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_putf_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte size)                         /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_putf_ok (&_body, size);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_PUTF_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_getf_ok   

    Synopsis: Formats a SMT_TRAN_GETF_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_getf_ok (
    byte **_buffer,
    qbyte size)                         /*  Amount of transmitted data       */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_GETF_OK, size);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_GETF_OK, size);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_getf_ok   

    Synopsis: Accepts a buffer containing a SMT_TRAN_GETF_OK message,
    and unpacks it into a new structsmt_tran_getf_ok structure. Free the
    structure using free_smt_tran_getf_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_getf_ok (
    byte *_buffer,
    struct_smt_tran_getf_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_getf_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_TRAN_GETF_OK,
                   &(*params)-> size));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_getf_ok   

    Synopsis: frees a structure allocated by get_smt_tran_getf_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_getf_ok (
    struct_smt_tran_getf_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_getf_ok  

    Synopsis: Sends a TRAN_GETF_OK (File received okay event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_getf_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte size)                         /*  Amount of transmitted data       */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_getf_ok (&_body, size);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_GETF_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_pipe_create    

    Synopsis: Formats a SMT_PIPE_CREATE message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_pipe_create (
    byte **_buffer,
    char *name,                         /*  Name of pipe                     */
    qbyte input_rate,                   /*  Input rate, bytes/s              */
    qbyte output_rate)                  /*  Output rate, bytes/s             */
{
    int _size;

    _size = exdr_write (NULL, SMT_PIPE_CREATE, name, input_rate, output_rate);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_PIPE_CREATE, name, input_rate, output_rate);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_pipe_create    

    Synopsis: Accepts a buffer containing a SMT_PIPE_CREATE message,
    and unpacks it into a new structsmt_pipe_create structure. Free the
    structure using free_smt_pipe_create() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_pipe_create (
    byte *_buffer,
    struct_smt_pipe_create **params)
{
    *params = mem_alloc (sizeof (struct_smt_pipe_create));
    if (*params)
      {
        (*params)-> name = NULL;
        return (exdr_read (_buffer, SMT_PIPE_CREATE,
                   &(*params)-> name,
                   &(*params)-> input_rate,
                   &(*params)-> output_rate));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_pipe_create    

    Synopsis: frees a structure allocated by get_smt_pipe_create().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_pipe_create (
    struct_smt_pipe_create **params)
{
    mem_free ((*params)-> name);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_pipe_create  

    Synopsis: Sends a PIPE_CREATE (Create or modify pipe event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_pipe_create (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *name,                         /*  Name of pipe                     */
    qbyte input_rate,                   /*  Input rate, bytes/s              */
    qbyte output_rate)                  /*  Output rate, bytes/s             */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_pipe_create (&_body, name, input_rate, output_rate);
    if (_size)
      {
        _rc = event_send (_to, _from, "PIPE_CREATE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_clear_pipes  

    Synopsis: Sends a CLEAR_PIPES (Delete all pipes event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_clear_pipes (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "CLEAR_PIPES", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_commit  

    Synopsis: Sends a TRAN_COMMIT (Commit transfer requests event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_commit (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "TRAN_COMMIT", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_closed  

    Synopsis: Sends a TRAN_CLOSED (Socket closed or commit done event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_closed (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout)
{
    return (event_send (_to, _from, "TRAN_CLOSED", NULL, 0, _accept,
            _reject, _expire, _timeout));
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_tran_error     

    Synopsis: Formats a SMT_TRAN_ERROR message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_tran_error (
    byte **_buffer,
    char *reason)                       /*  Error message                    */
{
    int _size;

    _size = exdr_write (NULL, SMT_TRAN_ERROR, reason);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_TRAN_ERROR, reason);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_tran_error     

    Synopsis: Accepts a buffer containing a SMT_TRAN_ERROR message,
    and unpacks it into a new structsmt_tran_error structure. Free the
    structure using free_smt_tran_error() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_tran_error (
    byte *_buffer,
    struct_smt_tran_error **params)
{
    *params = mem_alloc (sizeof (struct_smt_tran_error));
    if (*params)
      {
        (*params)-> reason = NULL;
        return (exdr_read (_buffer, SMT_TRAN_ERROR,
                   &(*params)-> reason));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_tran_error     

    Synopsis: frees a structure allocated by get_smt_tran_error().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_tran_error (
    struct_smt_tran_error **params)
{
    mem_free ((*params)-> reason);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_tran_error  

    Synopsis: Sends a TRAN_ERROR (Socket error event to
    the smttran agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_tran_error (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *reason)                       /*  Error message                    */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_tran_error (&_body, reason);
    if (_size)
      {
        _rc = event_send (_to, _from, "TRAN_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtftpd - FTP data transfer agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_putf      

    Synopsis: Formats a SMT_FTPD_PUTF message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_putf (
    byte **_buffer,
    qbyte id,                           /*  ID for connection                */
    dbyte passive,                      /*  0/1 = active/passive connection  */
    dbyte filetype,                     /*  Type of file to transfer         */
    char *filename,                     /*  Name of file to transfer         */
    qbyte start_position,               /*  Start offset for file            */
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number,                  /*  Port on remote host              */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_PUTF, id, passive, filetype, filename, start_position, host_address, port_number, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_PUTF, id, passive, filetype, filename, start_position, host_address, port_number, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_putf      

    Synopsis: Accepts a buffer containing a SMT_FTPD_PUTF message,
    and unpacks it into a new structsmt_ftpd_putf structure. Free the
    structure using free_smt_ftpd_putf() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_putf (
    byte *_buffer,
    struct_smt_ftpd_putf **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_putf));
    if (*params)
      {
        (*params)-> filename = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_FTPD_PUTF,
                   &(*params)-> id,
                   &(*params)-> passive,
                   &(*params)-> filetype,
                   &(*params)-> filename,
                   &(*params)-> start_position,
                   &(*params)-> host_address,
                   &(*params)-> port_number,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_putf      

    Synopsis: frees a structure allocated by get_smt_ftpd_putf().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_putf (
    struct_smt_ftpd_putf **params)
{
    mem_free ((*params)-> filename);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_put_file  

    Synopsis: Sends a FTPD_PUT_FILE (Send file to host event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_put_file (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte id,                           /*  ID for connection                */
    dbyte passive,                      /*  0/1 = active/passive connection  */
    dbyte filetype,                     /*  Type of file to transfer         */
    char *filename,                     /*  Name of file to transfer         */
    qbyte start_position,               /*  Start offset for file            */
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number,                  /*  Port on remote host              */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_putf (&_body, id, passive, filetype, filename, start_position, host_address, port_number, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_PUT_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_getf      

    Synopsis: Formats a SMT_FTPD_GETF message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_getf (
    byte **_buffer,
    qbyte id,                           /*  ID for connection                */
    dbyte passive,                      /*  0/1 = passive/active connection  */
    dbyte filetype,                     /*  Type of file to transfer         */
    char *filename,                     /*  Name of file to transfer         */
    qbyte start_position,               /*  Start offset for file            */
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number,                  /*  Port on remote host              */
    qbyte maxsize,                      /*  Max. size, -1 = no limit         */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_GETF, id, passive, filetype, filename, start_position, host_address, port_number, maxsize, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_GETF, id, passive, filetype, filename, start_position, host_address, port_number, maxsize, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_getf      

    Synopsis: Accepts a buffer containing a SMT_FTPD_GETF message,
    and unpacks it into a new structsmt_ftpd_getf structure. Free the
    structure using free_smt_ftpd_getf() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_getf (
    byte *_buffer,
    struct_smt_ftpd_getf **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_getf));
    if (*params)
      {
        (*params)-> filename = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_FTPD_GETF,
                   &(*params)-> id,
                   &(*params)-> passive,
                   &(*params)-> filetype,
                   &(*params)-> filename,
                   &(*params)-> start_position,
                   &(*params)-> host_address,
                   &(*params)-> port_number,
                   &(*params)-> maxsize,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_getf      

    Synopsis: frees a structure allocated by get_smt_ftpd_getf().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_getf (
    struct_smt_ftpd_getf **params)
{
    mem_free ((*params)-> filename);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_get_file  

    Synopsis: Sends a FTPD_GET_FILE (Receive file from host event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_get_file (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte id,                           /*  ID for connection                */
    dbyte passive,                      /*  0/1 = passive/active connection  */
    dbyte filetype,                     /*  Type of file to transfer         */
    char *filename,                     /*  Name of file to transfer         */
    qbyte start_position,               /*  Start offset for file            */
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number,                  /*  Port on remote host              */
    qbyte maxsize,                      /*  Max. size, -1 = no limit         */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_getf (&_body, id, passive, filetype, filename, start_position, host_address, port_number, maxsize, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_GET_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_append    

    Synopsis: Formats a SMT_FTPD_APPEND message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_append (
    byte **_buffer,
    qbyte id,                           /*  ID for connection                */
    dbyte passive,                      /*  0/1 = passive/active connection  */
    dbyte filetype,                     /*  Type of file to transfer         */
    char *filename,                     /*  Name of file to transfer         */
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number,                  /*  Port on remote host              */
    qbyte maxsize,                      /*  Max. size, -1 = no limit         */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_APPEND, id, passive, filetype, filename, host_address, port_number, maxsize, pipe);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_APPEND, id, passive, filetype, filename, host_address, port_number, maxsize, pipe);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_append    

    Synopsis: Accepts a buffer containing a SMT_FTPD_APPEND message,
    and unpacks it into a new structsmt_ftpd_append structure. Free the
    structure using free_smt_ftpd_append() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_append (
    byte *_buffer,
    struct_smt_ftpd_append **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_append));
    if (*params)
      {
        (*params)-> filename = NULL;
        (*params)-> pipe = NULL;
        return (exdr_read (_buffer, SMT_FTPD_APPEND,
                   &(*params)-> id,
                   &(*params)-> passive,
                   &(*params)-> filetype,
                   &(*params)-> filename,
                   &(*params)-> host_address,
                   &(*params)-> port_number,
                   &(*params)-> maxsize,
                   &(*params)-> pipe));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_append    

    Synopsis: frees a structure allocated by get_smt_ftpd_append().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_append (
    struct_smt_ftpd_append **params)
{
    mem_free ((*params)-> filename);
    mem_free ((*params)-> pipe);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_append_file  

    Synopsis: Sends a FTPD_APPEND_FILE (Append file from host event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_append_file (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte id,                           /*  ID for connection                */
    dbyte passive,                      /*  0/1 = passive/active connection  */
    dbyte filetype,                     /*  Type of file to transfer         */
    char *filename,                     /*  Name of file to transfer         */
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number,                  /*  Port on remote host              */
    qbyte maxsize,                      /*  Max. size, -1 = no limit         */
    char *pipe)                         /*  Transfer pipe, if any            */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_append (&_body, id, passive, filetype, filename, host_address, port_number, maxsize, pipe);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_APPEND_FILE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_passive   

    Synopsis: Formats a SMT_FTPD_PASSIVE message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_passive (
    byte **_buffer,
    qbyte id,                           /*  ID for control connection        */
    dbyte first_port,                   /*  First port to listen on          */
    qbyte ip_address)                   /*  IP address to listen on          */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_PASSIVE, id, first_port, ip_address);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_PASSIVE, id, first_port, ip_address);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_passive   

    Synopsis: Accepts a buffer containing a SMT_FTPD_PASSIVE message,
    and unpacks it into a new structsmt_ftpd_passive structure. Free the
    structure using free_smt_ftpd_passive() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_passive (
    byte *_buffer,
    struct_smt_ftpd_passive **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_passive));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_PASSIVE,
                   &(*params)-> id,
                   &(*params)-> first_port,
                   &(*params)-> ip_address));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_passive   

    Synopsis: frees a structure allocated by get_smt_ftpd_passive().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_passive (
    struct_smt_ftpd_passive **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_passive  

    Synopsis: Sends a FTPD_PASSIVE (Request passive connection event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_passive (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte id,                           /*  ID for control connection        */
    dbyte first_port,                   /*  First port to listen on          */
    qbyte ip_address)                   /*  IP address to listen on          */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_passive (&_body, id, first_port, ip_address);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_PASSIVE",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_abort     

    Synopsis: Formats a SMT_FTPD_ABORT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_abort (
    byte **_buffer,
    qbyte id)                           /*  ID for control connection        */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_ABORT, id);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_ABORT, id);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_abort     

    Synopsis: Accepts a buffer containing a SMT_FTPD_ABORT message,
    and unpacks it into a new structsmt_ftpd_abort structure. Free the
    structure using free_smt_ftpd_abort() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_abort (
    byte *_buffer,
    struct_smt_ftpd_abort **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_abort));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_ABORT,
                   &(*params)-> id));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_abort     

    Synopsis: frees a structure allocated by get_smt_ftpd_abort().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_abort (
    struct_smt_ftpd_abort **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_abort  

    Synopsis: Sends a FTPD_ABORT (Abort file transfer event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_abort (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte id)                           /*  ID for control connection        */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_abort (&_body, id);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_ABORT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_closectrl  

    Synopsis: Formats a SMT_FTPD_CLOSECTRL message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_closectrl (
    byte **_buffer,
    qbyte id)                           /*  ID for control connection        */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_CLOSECTRL, id);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_CLOSECTRL, id);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_closectrl  

    Synopsis: Accepts a buffer containing a SMT_FTPD_CLOSECTRL message,
    and unpacks it into a new structsmt_ftpd_closectrl structure. Free the
    structure using free_smt_ftpd_closectrl() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_closectrl (
    byte *_buffer,
    struct_smt_ftpd_closectrl **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_closectrl));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_CLOSECTRL,
                   &(*params)-> id));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_closectrl  

    Synopsis: frees a structure allocated by get_smt_ftpd_closectrl().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_closectrl (
    struct_smt_ftpd_closectrl **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_closectrl  

    Synopsis: Sends a FTPD_CLOSECTRL (Close control connection event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_closectrl (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte id)                           /*  ID for control connection        */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_closectrl (&_body, id);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_CLOSECTRL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_ftpd_pass_ok   

    Synopsis: Formats a SMT_FTPD_PASS_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_ftpd_pass_ok (
    byte **_buffer,
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number)                  /*  Port on remote host              */
{
    int _size;

    _size = exdr_write (NULL, SMT_FTPD_PASS_OK, host_address, port_number);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_FTPD_PASS_OK, host_address, port_number);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_ftpd_pass_ok   

    Synopsis: Accepts a buffer containing a SMT_FTPD_PASS_OK message,
    and unpacks it into a new structsmt_ftpd_pass_ok structure. Free the
    structure using free_smt_ftpd_pass_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_ftpd_pass_ok (
    byte *_buffer,
    struct_smt_ftpd_pass_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_ftpd_pass_ok));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_FTPD_PASS_OK,
                   &(*params)-> host_address,
                   &(*params)-> port_number));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_ftpd_pass_ok   

    Synopsis: frees a structure allocated by get_smt_ftpd_pass_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_ftpd_pass_ok (
    struct_smt_ftpd_pass_ok **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_ftpd_pass_ok  

    Synopsis: Sends a FTPD_PASS_OK (Agent request handled ok event to
    the smtftpd agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_ftpd_pass_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte host_address,                 /*  IP address for host              */
    dbyte port_number)                  /*  Port on remote host              */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_ftpd_pass_ok (&_body, host_address, port_number);
    if (_size)
      {
        _rc = event_send (_to, _from, "FTPD_PASS_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for WSX - WSX agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_install    

    Synopsis: Formats a SMT_WSX_INSTALL message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_install (
    byte **_buffer,
    char *virtual_host,                 /*  Virtual host name                */
    char *path,                         /*  URL pattern to match             */
    char *agent)                        /*  Name of WSX agent                */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_INSTALL, virtual_host, path, agent);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_INSTALL, virtual_host, path, agent);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_install    

    Synopsis: Accepts a buffer containing a SMT_WSX_INSTALL message,
    and unpacks it into a new structsmt_wsx_install structure. Free the
    structure using free_smt_wsx_install() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_install (
    byte *_buffer,
    struct_smt_wsx_install **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_install));
    if (*params)
      {
        (*params)-> virtual_host = NULL;
        (*params)-> path = NULL;
        (*params)-> agent = NULL;
        return (exdr_read (_buffer, SMT_WSX_INSTALL,
                   &(*params)-> virtual_host,
                   &(*params)-> path,
                   &(*params)-> agent));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_install    

    Synopsis: frees a structure allocated by get_smt_wsx_install().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_install (
    struct_smt_wsx_install **params)
{
    mem_free ((*params)-> virtual_host);
    mem_free ((*params)-> path);
    mem_free ((*params)-> agent);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_install  

    Synopsis: Sends a WSX_INSTALL (Install SMT_WSX alias event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_install (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *virtual_host,                 /*  Virtual host name                */
    char *path,                         /*  URL pattern to match             */
    char *agent)                        /*  Name of WSX agent                */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_install (&_body, virtual_host, path, agent);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_INSTALL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_cancel     

    Synopsis: Formats a SMT_WSX_CANCEL message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_cancel (
    byte **_buffer,
    char *virtual_host,                 /*  Virtual host name                */
    char *path)                         /*  URL pattern to match             */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_CANCEL, virtual_host, path);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_CANCEL, virtual_host, path);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_cancel     

    Synopsis: Accepts a buffer containing a SMT_WSX_CANCEL message,
    and unpacks it into a new structsmt_wsx_cancel structure. Free the
    structure using free_smt_wsx_cancel() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_cancel (
    byte *_buffer,
    struct_smt_wsx_cancel **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_cancel));
    if (*params)
      {
        (*params)-> virtual_host = NULL;
        (*params)-> path = NULL;
        return (exdr_read (_buffer, SMT_WSX_CANCEL,
                   &(*params)-> virtual_host,
                   &(*params)-> path));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_cancel     

    Synopsis: frees a structure allocated by get_smt_wsx_cancel().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_cancel (
    struct_smt_wsx_cancel **params)
{
    mem_free ((*params)-> virtual_host);
    mem_free ((*params)-> path);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_cancel  

    Synopsis: Sends a WSX_CANCEL (Cancel SMT_WSX alias event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_cancel (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *virtual_host,                 /*  Virtual host name                */
    char *path)                         /*  URL pattern to match             */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_cancel (&_body, virtual_host, path);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_CANCEL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_request    

    Synopsis: Formats a SMT_WSX_REQUEST message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_request (
    byte **_buffer,
    char *request_url,                  /*  URL for WSX request              */
    char *arguments,                    /*  URL arguments, if any            */
    char *virtual_host,                 /*  Virtual host, if any             */
    char *filename,                     /*  Physical filename for URL        */
    char *post_data,                    /*  POSTed data, if any              */
    word  symbols_size,                 /*  HTTP symbol table size           */
    byte *symbols_data,                 /*  HTTP symbol table data           */
    word  config_size,                  /*  HTTP config table size           */
    byte *config_data)                  /*  HTTP config table data           */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_REQUEST, request_url, arguments, virtual_host, filename, post_data, symbols_size, symbols_data, config_size, config_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_REQUEST, request_url, arguments, virtual_host, filename, post_data, symbols_size, symbols_data, config_size, config_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_request    

    Synopsis: Accepts a buffer containing a SMT_WSX_REQUEST message,
    and unpacks it into a new structsmt_wsx_request structure. Free the
    structure using free_smt_wsx_request() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_request (
    byte *_buffer,
    struct_smt_wsx_request **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_request));
    if (*params)
      {
        (*params)-> request_url = NULL;
        (*params)-> arguments = NULL;
        (*params)-> virtual_host = NULL;
        (*params)-> filename = NULL;
        (*params)-> post_data = NULL;
        (*params)-> symbols_data = NULL;
        (*params)-> config_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_REQUEST,
                   &(*params)-> request_url,
                   &(*params)-> arguments,
                   &(*params)-> virtual_host,
                   &(*params)-> filename,
                   &(*params)-> post_data,
                   &(*params)-> symbols_size,
                   &(*params)-> symbols_data,
                   &(*params)-> config_size,
                   &(*params)-> config_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_request    

    Synopsis: frees a structure allocated by get_smt_wsx_request().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_request (
    struct_smt_wsx_request **params)
{
    mem_free ((*params)-> request_url);
    mem_free ((*params)-> arguments);
    mem_free ((*params)-> virtual_host);
    mem_free ((*params)-> filename);
    mem_free ((*params)-> post_data);
    mem_free ((*params)-> symbols_data);
    mem_free ((*params)-> config_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_request  

    Synopsis: Sends a WSX_REQUEST (SMT_WSX request event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_request (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *request_url,                  /*  URL for WSX request              */
    char *arguments,                    /*  URL arguments, if any            */
    char *virtual_host,                 /*  Virtual host, if any             */
    char *filename,                     /*  Physical filename for URL        */
    char *post_data,                    /*  POSTed data, if any              */
    word  symbols_size,                 /*  HTTP symbol table size           */
    byte *symbols_data,                 /*  HTTP symbol table data           */
    word  config_size,                  /*  HTTP config table size           */
    byte *config_data)                  /*  HTTP config table data           */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_request (&_body, request_url, arguments, virtual_host, filename, post_data, symbols_size, symbols_data, config_size, config_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_REQUEST",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_reqbin     

    Synopsis: Formats a SMT_WSX_REQBIN message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_reqbin (
    byte **_buffer,
    char *request_url,                  /*  URL for WSX request              */
    char *arguments,                    /*  URL arguments, if any            */
    char *virtual_host,                 /*  Virtual host, if any             */
    word  post_size,                    /*  POSTed data size                 */
    char *filename,                     /*  Physical filename for URL        */
    byte *post_data,                    /*  POSTed data                      */
    word  symbols_size,                 /*  HTTP symbol table size           */
    byte *symbols_data,                 /*  HTTP symbol table data           */
    word  config_size,                  /*  HTTP config table size           */
    byte *config_data)                  /*  HTTP config table data           */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_REQBIN, request_url, arguments, virtual_host, post_size, filename, post_data, symbols_size, symbols_data, config_size, config_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_REQBIN, request_url, arguments, virtual_host, post_size, filename, post_data, symbols_size, symbols_data, config_size, config_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_reqbin     

    Synopsis: Accepts a buffer containing a SMT_WSX_REQBIN message,
    and unpacks it into a new structsmt_wsx_reqbin structure. Free the
    structure using free_smt_wsx_reqbin() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_reqbin (
    byte *_buffer,
    struct_smt_wsx_reqbin **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_reqbin));
    if (*params)
      {
        (*params)-> request_url = NULL;
        (*params)-> arguments = NULL;
        (*params)-> virtual_host = NULL;
        (*params)-> filename = NULL;
        (*params)-> post_data = NULL;
        (*params)-> symbols_data = NULL;
        (*params)-> config_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_REQBIN,
                   &(*params)-> request_url,
                   &(*params)-> arguments,
                   &(*params)-> virtual_host,
                   &(*params)-> post_size,
                   &(*params)-> filename,
                   &(*params)-> post_data,
                   &(*params)-> symbols_size,
                   &(*params)-> symbols_data,
                   &(*params)-> config_size,
                   &(*params)-> config_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_reqbin     

    Synopsis: frees a structure allocated by get_smt_wsx_reqbin().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_reqbin (
    struct_smt_wsx_reqbin **params)
{
    mem_free ((*params)-> request_url);
    mem_free ((*params)-> arguments);
    mem_free ((*params)-> virtual_host);
    mem_free ((*params)-> filename);
    mem_free ((*params)-> post_data);
    mem_free ((*params)-> symbols_data);
    mem_free ((*params)-> config_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_reqbin  

    Synopsis: Sends a WSX_REQBIN (SMT_WSX binary request event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_reqbin (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *request_url,                  /*  URL for WSX request              */
    char *arguments,                    /*  URL arguments, if any            */
    char *virtual_host,                 /*  Virtual host, if any             */
    word  post_size,                    /*  POSTed data size                 */
    char *filename,                     /*  Physical filename for URL        */
    byte *post_data,                    /*  POSTed data                      */
    word  symbols_size,                 /*  HTTP symbol table size           */
    byte *symbols_data,                 /*  HTTP symbol table data           */
    word  config_size,                  /*  HTTP config table size           */
    byte *config_data)                  /*  HTTP config table data           */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_reqbin (&_body, request_url, arguments, virtual_host, post_size, filename, post_data, symbols_size, symbols_data, config_size, config_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_REQBIN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_ok         

    Synopsis: Formats a SMT_WSX_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_ok (
    byte **_buffer,
    char *html_data)                    /*  HTML response data               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_OK, html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_OK, html_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_ok         

    Synopsis: Accepts a buffer containing a SMT_WSX_OK message,
    and unpacks it into a new structsmt_wsx_ok structure. Free the
    structure using free_smt_wsx_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_ok (
    byte *_buffer,
    struct_smt_wsx_ok **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_ok));
    if (*params)
      {
        (*params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_OK,
                   &(*params)-> html_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_ok         

    Synopsis: frees a structure allocated by get_smt_wsx_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_ok (
    struct_smt_wsx_ok **params)
{
    mem_free ((*params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_ok     

    Synopsis: Sends a WSX_OK (Agent request handled ok event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_ok (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *html_data)                    /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_ok (&_body, html_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_OK",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_bin        

    Synopsis: Formats a SMT_WSX_BIN message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_bin (
    byte **_buffer,
    qbyte html_size,                    /*  HTML response size               */
    byte *html_data)                    /*  HTML response data               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_BIN, html_size, html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_BIN, html_size, html_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_bin        

    Synopsis: Accepts a buffer containing a SMT_WSX_BIN message,
    and unpacks it into a new structsmt_wsx_bin structure. Free the
    structure using free_smt_wsx_bin() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_bin (
    byte *_buffer,
    struct_smt_wsx_bin **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_bin));
    if (*params)
      {
        (*params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_BIN,
                   &(*params)-> html_size,
                   &(*params)-> html_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_bin        

    Synopsis: frees a structure allocated by get_smt_wsx_bin().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_bin (
    struct_smt_wsx_bin **params)
{
    mem_free ((*params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_bin    

    Synopsis: Sends a WSX_BIN (Agent request handled ok event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_bin (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte html_size,                    /*  HTML response size               */
    byte *html_data)                    /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_bin (&_body, html_size, html_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_BIN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_multipart  

    Synopsis: Formats a SMT_WSX_MULTIPART message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_multipart (
    byte **_buffer,
    char *html_data)                    /*  HTML response data               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_MULTIPART, html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_MULTIPART, html_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_multipart  

    Synopsis: Accepts a buffer containing a SMT_WSX_MULTIPART message,
    and unpacks it into a new structsmt_wsx_multipart structure. Free the
    structure using free_smt_wsx_multipart() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_multipart (
    byte *_buffer,
    struct_smt_wsx_multipart **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_multipart));
    if (*params)
      {
        (*params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_MULTIPART,
                   &(*params)-> html_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_multipart  

    Synopsis: frees a structure allocated by get_smt_wsx_multipart().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_multipart (
    struct_smt_wsx_multipart **params)
{
    mem_free ((*params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_multipart  

    Synopsis: Sends a WSX_MULTIPART (Agent multipart response event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_multipart (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *html_data)                    /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_multipart (&_body, html_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_MULTIPART",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_mbin       

    Synopsis: Formats a SMT_WSX_MBIN message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_mbin (
    byte **_buffer,
    qbyte html_size,                    /*  HTML response size               */
    byte *html_data)                    /*  HTML response data               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_MBIN, html_size, html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_MBIN, html_size, html_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_mbin       

    Synopsis: Accepts a buffer containing a SMT_WSX_MBIN message,
    and unpacks it into a new structsmt_wsx_mbin structure. Free the
    structure using free_smt_wsx_mbin() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_mbin (
    byte *_buffer,
    struct_smt_wsx_mbin **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_mbin));
    if (*params)
      {
        (*params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_MBIN,
                   &(*params)-> html_size,
                   &(*params)-> html_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_mbin       

    Synopsis: frees a structure allocated by get_smt_wsx_mbin().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_mbin (
    struct_smt_wsx_mbin **params)
{
    mem_free ((*params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_mbin   

    Synopsis: Sends a WSX_MBIN (Agent multipart response event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_mbin (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte html_size,                    /*  HTML response size               */
    byte *html_data)                    /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_mbin (&_body, html_size, html_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_MBIN",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_restart    

    Synopsis: Formats a SMT_WSX_RESTART message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_restart (
    byte **_buffer,
    char *html_data)                    /*  HTML response data               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_RESTART, html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_RESTART, html_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_restart    

    Synopsis: Accepts a buffer containing a SMT_WSX_RESTART message,
    and unpacks it into a new structsmt_wsx_restart structure. Free the
    structure using free_smt_wsx_restart() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_restart (
    byte *_buffer,
    struct_smt_wsx_restart **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_restart));
    if (*params)
      {
        (*params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_RESTART,
                   &(*params)-> html_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_restart    

    Synopsis: frees a structure allocated by get_smt_wsx_restart().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_restart (
    struct_smt_wsx_restart **params)
{
    mem_free ((*params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_restart  

    Synopsis: Sends a WSX_RESTART (Agent requested restart event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_restart (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *html_data)                    /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_restart (&_body, html_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_RESTART",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_kill       

    Synopsis: Formats a SMT_WSX_KILL message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_kill (
    byte **_buffer,
    char *html_data)                    /*  HTML response data               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_KILL, html_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_KILL, html_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_kill       

    Synopsis: Accepts a buffer containing a SMT_WSX_KILL message,
    and unpacks it into a new structsmt_wsx_kill structure. Free the
    structure using free_smt_wsx_kill() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_kill (
    byte *_buffer,
    struct_smt_wsx_kill **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_kill));
    if (*params)
      {
        (*params)-> html_data = NULL;
        return (exdr_read (_buffer, SMT_WSX_KILL,
                   &(*params)-> html_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_kill       

    Synopsis: frees a structure allocated by get_smt_wsx_kill().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_kill (
    struct_smt_wsx_kill **params)
{
    mem_free ((*params)-> html_data);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_kill   

    Synopsis: Sends a WSX_KILL (Agent requested shutdown event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_kill (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *html_data)                    /*  HTML response data               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_kill (&_body, html_data);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_KILL",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_error      

    Synopsis: Formats a SMT_WSX_ERROR message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_error (
    byte **_buffer,
    dbyte error_code)                   /*  HTTP response code               */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_ERROR, error_code);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_ERROR, error_code);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_error      

    Synopsis: Accepts a buffer containing a SMT_WSX_ERROR message,
    and unpacks it into a new structsmt_wsx_error structure. Free the
    structure using free_smt_wsx_error() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_error (
    byte *_buffer,
    struct_smt_wsx_error **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_error));
    if (*params)
      {
        return (exdr_read (_buffer, SMT_WSX_ERROR,
                   &(*params)-> error_code));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_error      

    Synopsis: frees a structure allocated by get_smt_wsx_error().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_error (
    struct_smt_wsx_error **params)
{
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_error  

    Synopsis: Sends a WSX_ERROR (Agent request failed event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_error (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    dbyte error_code)                   /*  HTTP response code               */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_error (&_body, error_code);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_ERROR",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_wsx_redirect   

    Synopsis: Formats a SMT_WSX_REDIRECT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_wsx_redirect (
    byte **_buffer,
    char *new_url)                      /*  Redirect location                */
{
    int _size;

    _size = exdr_write (NULL, SMT_WSX_REDIRECT, new_url);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_WSX_REDIRECT, new_url);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_wsx_redirect   

    Synopsis: Accepts a buffer containing a SMT_WSX_REDIRECT message,
    and unpacks it into a new structsmt_wsx_redirect structure. Free the
    structure using free_smt_wsx_redirect() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_wsx_redirect (
    byte *_buffer,
    struct_smt_wsx_redirect **params)
{
    *params = mem_alloc (sizeof (struct_smt_wsx_redirect));
    if (*params)
      {
        (*params)-> new_url = NULL;
        return (exdr_read (_buffer, SMT_WSX_REDIRECT,
                   &(*params)-> new_url));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_wsx_redirect   

    Synopsis: frees a structure allocated by get_smt_wsx_redirect().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_wsx_redirect (
    struct_smt_wsx_redirect **params)
{
    mem_free ((*params)-> new_url);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_wsx_redirect  

    Synopsis: Sends a WSX_REDIRECT (Agent redirected request event to
    the WSX agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_wsx_redirect (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *new_url)                      /*  Redirect location                */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_wsx_redirect (&_body, new_url);
    if (_size)
      {
        _rc = event_send (_to, _from, "WSX_REDIRECT",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}

/*---------------------------------------------------------------------------
 *  Message functions for smtrdns - Reverse DNS agent.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_get_host_name  

    Synopsis: Formats a SMT_GET_HOST_NAME message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_get_host_name (
    byte **_buffer,
    qbyte ip_address,                   /*  IP address in network order      */
    char *ip_string,                    /*  Alternative address in string format  */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_GET_HOST_NAME, ip_address, ip_string, request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_GET_HOST_NAME, ip_address, ip_string, request_tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_get_host_name  

    Synopsis: Accepts a buffer containing a SMT_GET_HOST_NAME message,
    and unpacks it into a new structsmt_get_host_name structure. Free the
    structure using free_smt_get_host_name() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_get_host_name (
    byte *_buffer,
    struct_smt_get_host_name **params)
{
    *params = mem_alloc (sizeof (struct_smt_get_host_name));
    if (*params)
      {
        (*params)-> ip_string = NULL;
        return (exdr_read (_buffer, SMT_GET_HOST_NAME,
                   &(*params)-> ip_address,
                   &(*params)-> ip_string,
                   &(*params)-> request_tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_get_host_name  

    Synopsis: frees a structure allocated by get_smt_get_host_name().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_get_host_name (
    struct_smt_get_host_name **params)
{
    mem_free ((*params)-> ip_string);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_get_host_name  

    Synopsis: Sends a GET_HOST_NAME (Get host name for address event to
    the smtrdns agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_get_host_name (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte ip_address,                   /*  IP address in network order      */
    char *ip_string,                    /*  Alternative address in string format  */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_get_host_name (&_body, ip_address, ip_string, request_tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_HOST_NAME",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_get_host_ip    

    Synopsis: Formats a SMT_GET_HOST_IP message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_get_host_ip (
    byte **_buffer,
    char *host_name,                    /*  Host name to look-up             */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_GET_HOST_IP, host_name, request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_GET_HOST_IP, host_name, request_tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_get_host_ip    

    Synopsis: Accepts a buffer containing a SMT_GET_HOST_IP message,
    and unpacks it into a new structsmt_get_host_ip structure. Free the
    structure using free_smt_get_host_ip() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_get_host_ip (
    byte *_buffer,
    struct_smt_get_host_ip **params)
{
    *params = mem_alloc (sizeof (struct_smt_get_host_ip));
    if (*params)
      {
        (*params)-> host_name = NULL;
        return (exdr_read (_buffer, SMT_GET_HOST_IP,
                   &(*params)-> host_name,
                   &(*params)-> request_tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_get_host_ip    

    Synopsis: frees a structure allocated by get_smt_get_host_ip().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_get_host_ip (
    struct_smt_get_host_ip **params)
{
    mem_free ((*params)-> host_name);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_get_host_ip  

    Synopsis: Sends a GET_HOST_IP (Get host address for name event to
    the smtrdns agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_get_host_ip (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    char *host_name,                    /*  Host name to look-up             */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_get_host_ip (&_body, host_name, request_tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "GET_HOST_IP",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_host_name      

    Synopsis: Formats a SMT_HOST_NAME message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_host_name (
    byte **_buffer,
    qbyte ip_address,                   /*  IP address in network order      */
    char *host_name,                    /*  Host name                        */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_HOST_NAME, ip_address, host_name, request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_HOST_NAME, ip_address, host_name, request_tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_host_name      

    Synopsis: Accepts a buffer containing a SMT_HOST_NAME message,
    and unpacks it into a new structsmt_host_name structure. Free the
    structure using free_smt_host_name() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_host_name (
    byte *_buffer,
    struct_smt_host_name **params)
{
    *params = mem_alloc (sizeof (struct_smt_host_name));
    if (*params)
      {
        (*params)-> host_name = NULL;
        return (exdr_read (_buffer, SMT_HOST_NAME,
                   &(*params)-> ip_address,
                   &(*params)-> host_name,
                   &(*params)-> request_tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_host_name      

    Synopsis: frees a structure allocated by get_smt_host_name().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_host_name (
    struct_smt_host_name **params)
{
    mem_free ((*params)-> host_name);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_host_name  

    Synopsis: Sends a HOST_NAME (Return host name event to
    the smtrdns agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_host_name (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte ip_address,                   /*  IP address in network order      */
    char *host_name,                    /*  Host name                        */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_host_name (&_body, ip_address, host_name, request_tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "HOST_NAME",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_smt_host_ip        

    Synopsis: Formats a SMT_HOST_IP message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_smt_host_ip (
    byte **_buffer,
    qbyte ip_address,                   /*  IP address in network order      */
    char *host_name,                    /*  Host name                        */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    int _size;

    _size = exdr_write (NULL, SMT_HOST_IP, ip_address, host_name, request_tag);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, SMT_HOST_IP, ip_address, host_name, request_tag);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_smt_host_ip        

    Synopsis: Accepts a buffer containing a SMT_HOST_IP message,
    and unpacks it into a new structsmt_host_ip structure. Free the
    structure using free_smt_host_ip() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_smt_host_ip (
    byte *_buffer,
    struct_smt_host_ip **params)
{
    *params = mem_alloc (sizeof (struct_smt_host_ip));
    if (*params)
      {
        (*params)-> host_name = NULL;
        return (exdr_read (_buffer, SMT_HOST_IP,
                   &(*params)-> ip_address,
                   &(*params)-> host_name,
                   &(*params)-> request_tag));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_smt_host_ip        

    Synopsis: frees a structure allocated by get_smt_host_ip().
    ---------------------------------------------------------------------[>]-*/

void
free_smt_host_ip (
    struct_smt_host_ip **params)
{
    mem_free ((*params)-> host_name);
    mem_free (*params);
    *params = NULL;
}

/*  ---------------------------------------------------------------------[<]-
    Function: send_host_ip    

    Synopsis: Sends a HOST_IP (Return host IP address event to
    the smtrdns agent
    ---------------------------------------------------------------------[>]-*/

int
lsend_host_ip (QID *_to, QID *_from,
    char *_accept,
    char *_reject,
    char *_expire,
    word _timeout,
    qbyte ip_address,                   /*  IP address in network order      */
    char *host_name,                    /*  Host name                        */
    qbyte request_tag)                  /*  User-defined request tag         */
{
    byte *_body;
    int   _size,
          _rc;

    _size = put_smt_host_ip (&_body, ip_address, host_name, request_tag);
    if (_size)
      {
        _rc = event_send (_to, _from, "HOST_IP",
                          _body, _size,
                          _accept, _reject, _expire, _timeout);
        mem_free (_body);
        return _rc;
      }
    else
        return -1;
}



/*---------------------------------------------------------------------------
 *  wtpmsg.c - functions for WTP/1.0 standard messages.
 *
 *  Generated on 2004/07/22, 17:52:22 from wtpmsg.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/

#include "sfl.h"                        /*  SFL header file                  */
#include "smtlib.h"                     /*  SMT header file                  */
#include "wtpmsg.h"                     /*  Definitions & prototypes         */

/*---------------------------------------------------------------------------
 *  Message functions for wtpman - WTP/1.0 Standard Messages.
 *---------------------------------------------------------------------------*/

/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg            

    Synopsis: Formats a WTP_MSG message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg (
    byte **_buffer,
    byte  type)                         /*  Message type                     */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG, type);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG, type);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg            

    Synopsis: Accepts a buffer containing a WTP_MSG message,
    and unpacks it into a new structwtp_msg structure. Free the
    structure using free_wtp_msg() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg (
    byte *_buffer,
    struct_wtp_msg **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg));
    if (*params)
      {
        return (exdr_read (_buffer, WTP_MSG,
                   &(*params)-> type));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg            

    Synopsis: frees a structure allocated by get_wtp_msg().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg (
    struct_wtp_msg **params)
{
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_connect    

    Synopsis: Formats a WTP_MSG_CONNECT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_connect (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    char *callback_key,                 /*  Callback key                     */
    qbyte signature)                    /*  ATP signature                    */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_CONNECT, type, callback_key, signature);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_CONNECT, type, callback_key, signature);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_connect    

    Synopsis: Accepts a buffer containing a WTP_MSG_CONNECT message,
    and unpacks it into a new structwtp_msg_connect structure. Free the
    structure using free_wtp_msg_connect() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_connect (
    byte *_buffer,
    struct_wtp_msg_connect **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_connect));
    if (*params)
      {
        (*params)-> callback_key = NULL;
        return (exdr_read (_buffer, WTP_MSG_CONNECT,
                   &(*params)-> type,
                   &(*params)-> callback_key,
                   &(*params)-> signature));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_connect    

    Synopsis: frees a structure allocated by get_wtp_msg_connect().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_connect (
    struct_wtp_msg_connect **params)
{
    mem_free ((*params)-> callback_key);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_register   

    Synopsis: Formats a WTP_MSG_REGISTER message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_register (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    char *program,                      /*  Program to register              */
    byte  is_root)                      /*  Root program?                    */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_REGISTER, type, program, is_root);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_REGISTER, type, program, is_root);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_register   

    Synopsis: Accepts a buffer containing a WTP_MSG_REGISTER message,
    and unpacks it into a new structwtp_msg_register structure. Free the
    structure using free_wtp_msg_register() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_register (
    byte *_buffer,
    struct_wtp_msg_register **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_register));
    if (*params)
      {
        (*params)-> program = NULL;
        return (exdr_read (_buffer, WTP_MSG_REGISTER,
                   &(*params)-> type,
                   &(*params)-> program,
                   &(*params)-> is_root));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_register   

    Synopsis: frees a structure allocated by get_wtp_msg_register().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_register (
    struct_wtp_msg_register **params)
{
    mem_free ((*params)-> program);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_ready      

    Synopsis: Formats a WTP_MSG_READY message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_ready (
    byte **_buffer,
    byte  type)                         /*  Message type                     */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_READY, type);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_READY, type);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_ready      

    Synopsis: Accepts a buffer containing a WTP_MSG_READY message,
    and unpacks it into a new structwtp_msg_ready structure. Free the
    structure using free_wtp_msg_ready() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_ready (
    byte *_buffer,
    struct_wtp_msg_ready **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_ready));
    if (*params)
      {
        return (exdr_read (_buffer, WTP_MSG_READY,
                   &(*params)-> type));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_ready      

    Synopsis: frees a structure allocated by get_wtp_msg_ready().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_ready (
    struct_wtp_msg_ready **params)
{
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_disconnect  

    Synopsis: Formats a WTP_MSG_DISCONNECT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_disconnect (
    byte **_buffer,
    byte  type)                         /*  Message type                     */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DISCONNECT, type);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DISCONNECT, type);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_disconnect  

    Synopsis: Accepts a buffer containing a WTP_MSG_DISCONNECT message,
    and unpacks it into a new structwtp_msg_disconnect structure. Free the
    structure using free_wtp_msg_disconnect() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_disconnect (
    byte *_buffer,
    struct_wtp_msg_disconnect **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_disconnect));
    if (*params)
      {
        return (exdr_read (_buffer, WTP_MSG_DISCONNECT,
                   &(*params)-> type));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_disconnect  

    Synopsis: frees a structure allocated by get_wtp_msg_disconnect().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_disconnect (
    struct_wtp_msg_disconnect **params)
{
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_ok         

    Synopsis: Formats a WTP_MSG_OK message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_ok (
    byte **_buffer,
    byte  type)                         /*  Message type                     */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_OK, type);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_OK, type);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_ok         

    Synopsis: Accepts a buffer containing a WTP_MSG_OK message,
    and unpacks it into a new structwtp_msg_ok structure. Free the
    structure using free_wtp_msg_ok() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_ok (
    byte *_buffer,
    struct_wtp_msg_ok **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_ok));
    if (*params)
      {
        return (exdr_read (_buffer, WTP_MSG_OK,
                   &(*params)-> type));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_ok         

    Synopsis: frees a structure allocated by get_wtp_msg_ok().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_ok (
    struct_wtp_msg_ok **params)
{
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_error      

    Synopsis: Formats a WTP_MSG_ERROR message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_error (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    dbyte error_code,                   /*  Error code                       */
    char *error_text)                   /*  Error message text               */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_ERROR, type, error_code, error_text);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_ERROR, type, error_code, error_text);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_error      

    Synopsis: Accepts a buffer containing a WTP_MSG_ERROR message,
    and unpacks it into a new structwtp_msg_error structure. Free the
    structure using free_wtp_msg_error() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_error (
    byte *_buffer,
    struct_wtp_msg_error **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_error));
    if (*params)
      {
        (*params)-> error_text = NULL;
        return (exdr_read (_buffer, WTP_MSG_ERROR,
                   &(*params)-> type,
                   &(*params)-> error_code,
                   &(*params)-> error_text));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_error      

    Synopsis: frees a structure allocated by get_wtp_msg_error().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_error (
    struct_wtp_msg_error **params)
{
    mem_free ((*params)-> error_text);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_do         

    Synopsis: Formats a WTP_MSG_DO message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_do (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    qbyte signature,                    /*  ATP signature                    */
    char *program,                      /*  Program to execute               */
    byte  entry_code,                   /*  Program entry code               */
    char *http_uri,                     /*  URI for hyperlinks               */
    char *http_data,                    /*  Encoded HTTP data                */
    qbyte args_size,                    /*  Return arguments size            */
    byte *args_data,                    /*  Return arguments data            */
    byte  call_result,                  /*  Result of last call              */
    qbyte env_size,                     /*  Environment size                 */
    byte *env_data,                     /*  Environment block                */
    qbyte global_size,                  /*  Global context size              */
    byte *global_data,                  /*  Global context block             */
    qbyte local_size,                   /*  Local context size               */
    byte *local_data)                   /*  Local context block              */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DO, type, signature, program, entry_code, http_uri, http_data, args_size, args_data, call_result, env_size, env_data, global_size, global_data, local_size, local_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DO, type, signature, program, entry_code, http_uri, http_data, args_size, args_data, call_result, env_size, env_data, global_size, global_data, local_size, local_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_do         

    Synopsis: Accepts a buffer containing a WTP_MSG_DO message,
    and unpacks it into a new structwtp_msg_do structure. Free the
    structure using free_wtp_msg_do() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_do (
    byte *_buffer,
    struct_wtp_msg_do **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_do));
    if (*params)
      {
        (*params)-> program = NULL;
        (*params)-> http_uri = NULL;
        (*params)-> http_data = NULL;
        (*params)-> args_data = NULL;
        (*params)-> env_data = NULL;
        (*params)-> global_data = NULL;
        (*params)-> local_data = NULL;
        return (exdr_read (_buffer, WTP_MSG_DO,
                   &(*params)-> type,
                   &(*params)-> signature,
                   &(*params)-> program,
                   &(*params)-> entry_code,
                   &(*params)-> http_uri,
                   &(*params)-> http_data,
                   &(*params)-> args_size,
                   &(*params)-> args_data,
                   &(*params)-> call_result,
                   &(*params)-> env_size,
                   &(*params)-> env_data,
                   &(*params)-> global_size,
                   &(*params)-> global_data,
                   &(*params)-> local_size,
                   &(*params)-> local_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_do         

    Synopsis: frees a structure allocated by get_wtp_msg_do().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_do (
    struct_wtp_msg_do **params)
{
    mem_free ((*params)-> program);
    mem_free ((*params)-> http_uri);
    mem_free ((*params)-> http_data);
    mem_free ((*params)-> args_data);
    mem_free ((*params)-> env_data);
    mem_free ((*params)-> global_data);
    mem_free ((*params)-> local_data);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_doneshow   

    Synopsis: Formats a WTP_MSG_DONESHOW message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_doneshow (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    char *html_data,                    /*  HTML screen data                 */
    qbyte global_size,                  /*  Global context size              */
    byte *global_data,                  /*  Global context block             */
    qbyte local_size,                   /*  Local context size               */
    byte *local_data)                   /*  Local context block              */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DONESHOW, type, html_data, global_size, global_data, local_size, local_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DONESHOW, type, html_data, global_size, global_data, local_size, local_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_doneshow   

    Synopsis: Accepts a buffer containing a WTP_MSG_DONESHOW message,
    and unpacks it into a new structwtp_msg_doneshow structure. Free the
    structure using free_wtp_msg_doneshow() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_doneshow (
    byte *_buffer,
    struct_wtp_msg_doneshow **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_doneshow));
    if (*params)
      {
        (*params)-> html_data = NULL;
        (*params)-> global_data = NULL;
        (*params)-> local_data = NULL;
        return (exdr_read (_buffer, WTP_MSG_DONESHOW,
                   &(*params)-> type,
                   &(*params)-> html_data,
                   &(*params)-> global_size,
                   &(*params)-> global_data,
                   &(*params)-> local_size,
                   &(*params)-> local_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_doneshow   

    Synopsis: frees a structure allocated by get_wtp_msg_doneshow().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_doneshow (
    struct_wtp_msg_doneshow **params)
{
    mem_free ((*params)-> html_data);
    mem_free ((*params)-> global_data);
    mem_free ((*params)-> local_data);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_donecall   

    Synopsis: Formats a WTP_MSG_DONECALL message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_donecall (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    char *program,                      /*  Program to call                  */
    qbyte args_size,                    /*  Call arguments size              */
    byte *args_data,                    /*  Call arguments data              */
    qbyte global_size,                  /*  Global context size              */
    byte *global_data,                  /*  Global context block             */
    qbyte local_size,                   /*  Local context size               */
    byte *local_data)                   /*  Local context block              */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DONECALL, type, program, args_size, args_data, global_size, global_data, local_size, local_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DONECALL, type, program, args_size, args_data, global_size, global_data, local_size, local_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_donecall   

    Synopsis: Accepts a buffer containing a WTP_MSG_DONECALL message,
    and unpacks it into a new structwtp_msg_donecall structure. Free the
    structure using free_wtp_msg_donecall() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_donecall (
    byte *_buffer,
    struct_wtp_msg_donecall **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_donecall));
    if (*params)
      {
        (*params)-> program = NULL;
        (*params)-> args_data = NULL;
        (*params)-> global_data = NULL;
        (*params)-> local_data = NULL;
        return (exdr_read (_buffer, WTP_MSG_DONECALL,
                   &(*params)-> type,
                   &(*params)-> program,
                   &(*params)-> args_size,
                   &(*params)-> args_data,
                   &(*params)-> global_size,
                   &(*params)-> global_data,
                   &(*params)-> local_size,
                   &(*params)-> local_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_donecall   

    Synopsis: frees a structure allocated by get_wtp_msg_donecall().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_donecall (
    struct_wtp_msg_donecall **params)
{
    mem_free ((*params)-> program);
    mem_free ((*params)-> args_data);
    mem_free ((*params)-> global_data);
    mem_free ((*params)-> local_data);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_donereturn  

    Synopsis: Formats a WTP_MSG_DONERETURN message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_donereturn (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    qbyte args_size,                    /*  Call arguments size              */
    byte *args_data,                    /*  Call arguments data              */
    qbyte global_size,                  /*  Global context size              */
    byte *global_data)                  /*  Global context block             */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DONERETURN, type, args_size, args_data, global_size, global_data);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DONERETURN, type, args_size, args_data, global_size, global_data);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_donereturn  

    Synopsis: Accepts a buffer containing a WTP_MSG_DONERETURN message,
    and unpacks it into a new structwtp_msg_donereturn structure. Free the
    structure using free_wtp_msg_donereturn() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_donereturn (
    byte *_buffer,
    struct_wtp_msg_donereturn **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_donereturn));
    if (*params)
      {
        (*params)-> args_data = NULL;
        (*params)-> global_data = NULL;
        return (exdr_read (_buffer, WTP_MSG_DONERETURN,
                   &(*params)-> type,
                   &(*params)-> args_size,
                   &(*params)-> args_data,
                   &(*params)-> global_size,
                   &(*params)-> global_data));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_donereturn  

    Synopsis: frees a structure allocated by get_wtp_msg_donereturn().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_donereturn (
    struct_wtp_msg_donereturn **params)
{
    mem_free ((*params)-> args_data);
    mem_free ((*params)-> global_data);
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_doneexit   

    Synopsis: Formats a WTP_MSG_DONEEXIT message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_doneexit (
    byte **_buffer,
    byte  type)                         /*  Message type                     */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DONEEXIT, type);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DONEEXIT, type);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_doneexit   

    Synopsis: Accepts a buffer containing a WTP_MSG_DONEEXIT message,
    and unpacks it into a new structwtp_msg_doneexit structure. Free the
    structure using free_wtp_msg_doneexit() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_doneexit (
    byte *_buffer,
    struct_wtp_msg_doneexit **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_doneexit));
    if (*params)
      {
        return (exdr_read (_buffer, WTP_MSG_DONEEXIT,
                   &(*params)-> type));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_doneexit   

    Synopsis: frees a structure allocated by get_wtp_msg_doneexit().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_doneexit (
    struct_wtp_msg_doneexit **params)
{
    mem_free (*params);
    *params = NULL;
}


/*  ---------------------------------------------------------------------[<]-
    Function: put_wtp_msg_doneerror  

    Synopsis: Formats a WTP_MSG_DONEERROR message, allocates a new buffer,
    and returns the formatted message in the buffer.  You should free the
    buffer using mem_free() when finished.  Returns the size of the buffer
    in bytes.
    ---------------------------------------------------------------------[>]-*/

int
put_wtp_msg_doneerror (
    byte **_buffer,
    byte  type,                         /*  Message type                     */
    char *error_text)                   /*  Error message text               */
{
    int _size;

    _size = exdr_write (NULL, WTP_MSG_DONEERROR, type, error_text);
    *_buffer = mem_alloc (_size);
    if (*_buffer)
        exdr_write (*_buffer, WTP_MSG_DONEERROR, type, error_text);
    else
        _size = 0;
    return (_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: get_wtp_msg_doneerror  

    Synopsis: Accepts a buffer containing a WTP_MSG_DONEERROR message,
    and unpacks it into a new structwtp_msg_doneerror structure. Free the
    structure using free_wtp_msg_doneerror() when finished.
    ---------------------------------------------------------------------[>]-*/

int
get_wtp_msg_doneerror (
    byte *_buffer,
    struct_wtp_msg_doneerror **params)
{
    *params = mem_alloc (sizeof (struct_wtp_msg_doneerror));
    if (*params)
      {
        (*params)-> error_text = NULL;
        return (exdr_read (_buffer, WTP_MSG_DONEERROR,
                   &(*params)-> type,
                   &(*params)-> error_text));
      }
    else
        return -1;
}


/*  ---------------------------------------------------------------------[<]-
    Function: free_wtp_msg_doneerror  

    Synopsis: frees a structure allocated by get_wtp_msg_doneerror().
    ---------------------------------------------------------------------[>]-*/

void
free_wtp_msg_doneerror (
    struct_wtp_msg_doneerror **params)
{
    mem_free ((*params)-> error_text);
    mem_free (*params);
    *params = NULL;
}



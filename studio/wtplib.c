/*===========================================================================*
 *                                                                           *
 *  wtplib.c - WTP interface functions                                       *
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
/*
    Synopsis:   Provides a high-level interface to the WTP/1.0 interface for
                broker programs.  This is an alternative to direct access
                using the WTP/1.0 Message Functions and the SFL socket i/o
                interface.

*/
#include "sfl.h"                        /*  Standard function library        */
#include "wtpmsg.h"                     /*  WTP message API                  */
#include "wtplib.h"                     /*  WTP definitions                  */


/*  One broker process uses one single WTP socket; this is it...             */

static sock_t
    wtp_socket = 0;

/*  Local function prototypes                                                */

local read_from_wtp_socket (size_t readsize, byte *buffer);


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_open

    Synopsis: Opens the connection to the WTP manager. This must be the first
    WTP function called in a broker.  This function takes as arguments the
    protocol and port passed to the broker program by the WTP manager. The
    function does not return an error status; if the open fails, it aborts
    after printing an error message to stderr.  A broker should normally do
    this series of function calls: wtp_open(), wtp_connect(), wtp_register(),
    - once per program - and finally wtp_ready().
    ---------------------------------------------------------------------[>]-*/

void
wtp_open (
    const char *version,                /*  WTP version                      */
    const char *protocol,               /*  Protocol from command-line       */
    const char *port)                   /*  Port from command-line           */
{
    ASSERT (streq (version, "WTP/1.0"));
    ASSERT (streq (protocol, "tcp"));

    sock_init ();
    ip_nonblock = FALSE;                /*  Use blocking socket i/o          */

    wtp_socket  = connect_TCP (NULL, port);
    if (wtp_socket == INVALID_SOCKET)
      {
        coprintf ("Cannot connect to port %s: %s (%s)\n",
                   port, connect_errlist [connect_error ()], sockmsg ());
        exit (EXIT_FAILURE);
      }
    socket_nodelay (wtp_socket);        /*  Disable Nagle's Algorithm        */
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_close

    Synopsis: Ends the WTP connection.  You should do this after receiving
    a WTP_DISCONNECT message.  However, it is not mandatory.  After a
    wtp_close(), the broker program should exit.
    ---------------------------------------------------------------------[>]-*/

void
wtp_close (void)
{
    close_socket (wtp_socket);
    wtp_socket = 0;
    sock_term ();
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_connect

    Synopsis: Establishes a logical connection to the WTP manager.  This
    function expects as arguments the WTP callback key and the program
    filename, both supplied as command-line arguments.  The filename is
    used to generate a signature for the broker.  If you supply the wrong
    signature, you cannot connect to the WTP manager, and any further
    messages to the WTP manager are ignored.
    ---------------------------------------------------------------------[>]-*/

void
wtp_connect (
    const char *callback_key,           /*  Callback key from command-line   */
    const char *filename)               /*  Program name from command-line   */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_connect (
        &buffer,
        WTP_CONNECT,                    /*  Message type                     */
        (char *) callback_key,          /*  Callback key from WTP manager    */
        wtp_signature (filename));      /*  ATP signature                    */

    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_register

    Synopsis: Registers one program with the WTP manager.  You should call
    this function exactly once for each program that the broker handles.
    There is no way to 'unregister' a program.  The implementation of this
    function is: send a WTP_REGISTER message, and wait for the reply, which
    should be WTP_OK.  If the reply is not WTP_OK, the function exits the
    current process with an error message.
    ---------------------------------------------------------------------[>]-*/

void
wtp_register (
    const char *program,                /*  Name of program to register      */
    Bool  is_root)                      /*  Is this a root program?          */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_register (
        &buffer,
        WTP_REGISTER,                   /*  Message type                     */
        (char *) program,               /*  Program to register              */
        (byte) is_root);                /*  Root flag, 1 or 0                */

    wtp_write (buffer, size);
    mem_free  (buffer);
    if (!wtp_expect_ok ())
      {
        coprintf ("Registration for program '%s' failed.\n", program);
        exit (EXIT_FAILURE);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_ready

    Synopsis: Tells the WTP manager that the broker is ready to receive
    program requests.  The implementation of this function is: send a
    WTP_READY message, and wait for the reply, which should be WTP_OK. If
    the reply is not WTP_OK, the function exits the current process with
    an error message.
    ---------------------------------------------------------------------[>]-*/

void
wtp_ready (void)
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_ready (
        &buffer,
        WTP_READY);                     /*  Message type                     */

    wtp_write (buffer, size);
    mem_free  (buffer);
    if (!wtp_expect_ok ())
      {
        coprintf ("Did not receive WTP_OK when ready.\n");
        exit (EXIT_FAILURE);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_doneshow

    Synopsis: Returns a WTP_DONESHOW message to the WTP manager.  Does not
    wait for any further incoming messages.
    ---------------------------------------------------------------------[>]-*/

void
wtp_doneshow (
    const char *html_data,              /*  HTML data to show                */
    qbyte       global_size,            /*  Global data size                 */
    const byte *global_data,            /*  Global data contents             */
    qbyte       local_size,             /*  Local data size                  */
    const byte *local_data)             /*  Local data contents              */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_doneshow (
        &buffer,
        WTP_DONESHOW,                   /*  Message type                     */
        (char *) html_data,             /*  HTML screen data                 */
                 global_size,           /*  Size of global context           */
        (byte *) global_data,           /*  Global context block             */
                 local_size,            /*  Size of local context            */
        (byte *) local_data);           /*  Local context block              */

    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_donecall

    Synopsis: Returns a WTP_DONECALL message to the WTP manager.  Does not
    wait for any further incoming messages.
    ---------------------------------------------------------------------[>]-*/

void
wtp_donecall (
    const char *program,                /*  Name of program to call          */
    qbyte       args_size,              /*  Program arguments size           */
    const byte *args_data,              /*  Program arguments contents       */
    qbyte       global_size,            /*  Global data size                 */
    const byte *global_data,            /*  Global data contents             */
    qbyte       local_size,             /*  Local data size                  */
    const byte *local_data)             /*  Local data contents              */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_donecall (
        &buffer,
        WTP_DONECALL,                   /*  Message type                     */
        (char *) program,               /*  Program to call                  */
                 args_size,             /*  Call arguments size              */
        (byte *) args_data,             /*  Call arguments data              */
                 global_size,           /*  Size of global context           */
        (byte *) global_data,           /*  Global context block             */
                 local_size,            /*  Size of local context            */
        (byte *) local_data);           /*  Local context block              */

    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_donereturn

    Synopsis: Returns a WTP_DONERETURN message to the WTP manager.  Does
    not wait for any further incoming messages.
    ---------------------------------------------------------------------[>]-*/

void
wtp_donereturn (
    qbyte       args_size,              /*  Return arguments size            */
    const byte *args_data,              /*  Return arguments contents        */
    qbyte       global_size,            /*  Global data size                 */
    const byte *global_data)            /*  Global data contents             */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_donereturn (
        &buffer,
        WTP_DONERETURN,                 /*  Message type                     */
                 args_size,             /*  Call arguments size              */
        (byte *) args_data,             /*  Call arguments data              */
                 global_size,           /*  Size of global context           */
        (byte *) global_data);          /*  Global context block             */

    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_doneexit

    Synopsis: Returns a WTP_DONEEXIT message to the WTP manager.  Does not
    wait for any further incoming messages.
    ---------------------------------------------------------------------[>]-*/

void
wtp_doneexit (void)
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_doneexit (
        &buffer,
        WTP_DONEEXIT);                  /*  Message type                     */
    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_doneerror

    Synopsis: Returns a WTP_DONEERROR message to the WTP manager.  Does
    not wait for any further incoming messages.
    ---------------------------------------------------------------------[>]-*/

void
wtp_doneerror (
    const char *message)                /*  Error message text               */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_doneerror (
        &buffer,
        WTP_DONEERROR,                  /*  Message type                     */
        (char *) message);              /*  Program return code              */
    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_error

    Synopsis: Sends a WTP_ERROR message to the WTP manage.  Does not wait
    for any further incoming messages.
    ---------------------------------------------------------------------[>]-*/

void
wtp_error (
    dbyte       error_code,             /*  WTP error code                   */
    const char *error_text)             /*  Arbitrary error text             */
{
    byte
        *buffer;
    size_t
        size;

    size = put_wtp_msg_error (
        &buffer, WTP_ERROR,
        error_code,                     /*  Error code                       */
        (char *) error_text);           /*  Error message text               */

    wtp_write (buffer, size);
    mem_free  (buffer);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_write

    Synopsis: This is a low-level function that writes an arbitrary message
    to the WTP manager socket.  Normally you do not need to call this
    function, since each WTP message has an explicit function to format and
    send it.  However, you may want to format the message yourself and send
    it using this function call.
    ---------------------------------------------------------------------[>]-*/

void
wtp_write (
    const byte *buffer,                 /*  Address of data to write         */
    size_t      size)                   /*  Amount of data to write          */
{
    qbyte
        netsize;                        /*  Size in network order, 4 bytes   */

    ASSERT (wtp_socket != 0);

    /*  Write buffer size in hi-lo order                                     */
    netsize = htonl (size);
    if (write_TCP (wtp_socket, &netsize, 4)  == SOCKET_ERROR
    ||  write_TCP (wtp_socket, buffer, size) == SOCKET_ERROR)
      {
        coprintf ("Cannot write to socket: %s\n", sockmsg ());
        exit (EXIT_FAILURE);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_read

    Synopsis: Reads the next incoming message from the WTP manager socket.
    This is the correct manner to read a WTP message.  You must unpack the
    WTP messages yourself using the WTP message-level functions.  If the
    buffer is NULL, allocates a new buffer, which you must free using the
    SFL mem_free() function.
    ---------------------------------------------------------------------[>]-*/

size_t
wtp_read (
    byte **buffer)                      /*  Read into this buffer            */
{
    qbyte
        netsize;                        /*  Size in network order, 4 bytes   */
    size_t
        message_size;

    read_from_wtp_socket (4, (byte *) &netsize);
    message_size = ntohl (netsize);
    if (*buffer == NULL)
        *buffer = mem_alloc (message_size);

    read_from_wtp_socket (message_size, *buffer);
    return (message_size);
}

local
read_from_wtp_socket (size_t readsize, byte *buffer)
{
    size_t
        bytes_read;
    int
        rc;

    ASSERT (wtp_socket != 0);
    bytes_read = 0;

    while (bytes_read < readsize)
      {
        rc = read_TCP (wtp_socket, buffer + bytes_read,
                                 readsize - bytes_read);

        /*  If socket from parent is closed, the application has been
         *  shut-down, so we can stop too.
         */
        if (rc == 0 || sockerrno == EPIPE || sockerrno == ECONNRESET)
          {
            wtp_close ();
            exit (EXIT_SUCCESS);         
          }
        else
        if (rc == SOCKET_ERROR)
          {
            coprintf ("Cannot read from socket: %s\n", sockmsg ());
            exit (EXIT_FAILURE);
          }
        bytes_read += rc;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_expect_ok

    Synopsis: Waits for an incoming message, and checks that it is WTP_OK.
    If so, returns TRUE, else returns FALSE.  Does not keep the message.
    ---------------------------------------------------------------------[>]-*/

Bool
wtp_expect_ok (void)
{
    struct_wtp_msg
        *wtp_msg = NULL;
    byte
        *buffer = NULL;                 /*  Message buffer from wtpman       */
    Bool
        okay;

    if (wtp_read (&buffer) == 0)
        return (FALSE);

    get_wtp_msg (buffer, &wtp_msg);
    okay = (wtp_msg-> type == WTP_OK);
    free_wtp_msg (&wtp_msg);
    mem_free (buffer);
    return (okay);
}


/*  ---------------------------------------------------------------------[<]-
    Function: wtp_signature

    Synopsis: Calculates the executable file signature.  This is used to
    detect when an executable file has changed, since that requires that
    the users of the program(s) involved disconnect and reconnect.  The
    signature is a 32-bit hash based on the file name, size, and time.
    ---------------------------------------------------------------------[>]-*/

qbyte
wtp_signature (
    const char *filename)               /*  Name of executable program       */
{
    static char
        signature [30];

    /*  Signature is XXXXXXXX-XXXXXXXX-XXXXXXXX  (hash-size-time)            */
    /*  then passed through 32-bit CRC calculation.                          */
    sprintf (signature, "%08lX-%08lX-%08lX",
                         strhash (filename),
                         get_file_size (filename),
                         get_file_time (filename));

    return (calculate_crc ((byte *) signature, strlen (signature)));
}

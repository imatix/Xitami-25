/*  ----------------------------------------------------------------<Prolog>-
    Name:       testcgi1.c
    Title:      CGI test program
    Package:    Xitami web server

    Written:    96/10/01  Pieter Hintjens <ph@imatix.com>
    Revised:    97/04/29  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Generates an HTML test page containing the arguments passed
                to the CGI process.

                To build this program you must download the SFL package from
                www.imatix.com.

    Copyright:  Copyright (c) 1997 iMatix
    License:    This is free software; you can redistribute it and/or modify
                it under the terms of the XITAMI License Agreement as provided
                in the file LICENSE.TXT.  This software is distributed in
                the hope that it will be useful, but without any warranty.
 ------------------------------------------------------------------</Prolog>-*/

#include "sfl.h"

int
main (int argc, char *argv [])
{
    /*  Generates full HTTP header
     *
     *  This should be passed through the server transparently
     *  Some servers require that the CGI program be named 'nsp-'.
     *  Xitami detects the HTTP header automatically.
     *  Note that this will not work with the Keep-Alive option enabled,
     *  since the content-length is not specified.
     */
    puts ("HTTP/1.0 200 Ok");
    puts ("Content-Type: text/html");
    puts ("");
    puts ("<HTML>");
    puts ("<BODY>Test program 1</BODY></HTML>");

    return (EXIT_SUCCESS);
}

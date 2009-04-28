/*  ----------------------------------------------------------------<Prolog>-
    Name:       testcgi4.c
    Title:      CGI test program
    Package:    Xitami web server

    Written:    96/10/01  Pieter Hintjens <ph@imatix.com>
    Revised:    97/04/08  Pieter Hintjens <ph@imatix.com>

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
    /*  Generates a local location and arguments, which must be handled      */
    /*  by the server directly.                                              */

    puts ("Location: /cgi-bin/testcgi.exe?args_4");

    return (EXIT_SUCCESS);
}

/*  ----------------------------------------------------------------<Prolog>-
    Name:       testcgi7.c
    Title:      CGI test program
    Package:    Xitami web server

    Written:    97/05/09  Pieter Hintjens <ph@imatix.com>
    Revised:    97/07/30  Pieter Hintjens <ph@imatix.com>

    Synopsis:   Simulates a looping CGI process.  Use it to test the server's
                response to a looping CGI process.  You can end the program
                by creating an empty file called 'break'.

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
    file_delete ("break");
    while (!file_exists ("break"));
    file_delete ("break");

    puts ("Content-Type: text/html");
    puts ("");
    puts ("<HTML><BODY>");
    puts ("Testcgi7 was able to complete normally.");
    puts ("</BODY></HTML>");

    return (EXIT_SUCCESS);
}

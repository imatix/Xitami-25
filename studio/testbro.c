/*===========================================================================*
 *                                                                           *
 *  testbro.c - Broker test program                                          *
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
/*===========================================================================*
 *                                                                           *
 *  testbro.c   Test broker                                                  *
 *                                                                           *
 *  Written:    97/06/11   Pieter Hintjens                                   *
 *  Revised:    97/06/23                                                     *
 *                                                                           *
 *===========================================================================*/

#include "sfl.h"                        /*  Standard function library        */
#include "wtplib.h"                     /*  WTP definitions                  */
#include "wtpmsg.h"                     /*  WTP message API                  */


int main (int argc, char *argv [])
{
    static char
        hello [LINE_MAX];
    char
        *protocol,                      /*  Protocol to use                  */
        *port,                          /*  Port number                      */
        *callback;                      /*  Callback key                     */
    byte
        *message;
    struct_wtp_msg_do
        *msg_do;

    if (argc < 4)
      {
        puts ("Must be run from WTP manager!");
        exit (0);
      }
    else
      {
        protocol = argv [1];
        port     = argv [2];
        callback = argv [3];
      }
    wtp_open     ("WTP/1.0", protocol, port);
    wtp_connect  (callback, argv [0]);
    wtp_register ("CLIMAIN", TRUE);
    wtp_ready    ();
    puts ("Ready");

    FOREVER
      {
        message = NULL;
        wtp_read (&message);

        /*  Get just the message type; leave message in event body           */
        get_wtp_msg_do (message, &msg_do);
        switch (msg_do-> type)
          {
            case WTP_CONTEXT:
                puts ("Have WTP_CONTEXT");
                fflush (stdout);
                break;
            case WTP_DISCONNECT:
                puts ("Have WTP_DISCONNECT");
                fflush (stdout);
                return (EXIT_SUCCESS);
            case WTP_DO:
                puts ("Have WTP_DO");
                fflush (stdout);
                sprintf (hello, "%s%s%s",
                         "<HTML><BODY><H1>Hello World!</H1><P><A HREF=\"",
                         msg_do-> http_uri,
                         "\">Continue</A></HTML></BODY>");
                wtp_doneshow (hello, 0, NULL, 0, NULL);
                break;
            case WTP_ERROR:
                puts ("Have WTP_ERROR");
                fflush (stdout);
                break;
            case WTP_OK:
                puts ("Have WTP_OK");
                fflush (stdout);
                break;
            default:
                puts ("Have WTP_????");
                fflush (stdout);
                break;
          }
        free_wtp_msg_do (&msg_do);
        mem_free (message);
      }
}

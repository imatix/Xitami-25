/*===========================================================================*
 *                                                                           *
 *  xitami.h - Header file for Windows versions                              *
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
 *===========================================================================*/

#ifndef _XITAMI_INCLUDED
#define _XITAMI_INCLUDED

#include "sfl.h"                        /*  SFL library header file          */
#include "smtlib.h"                     /*  SMT kernel functions             */
#include "smtdefn.h"                    /*  SMT agent definitions            */
#include "smthttpl.h"                   /*  SMTHTTP definitions              */
#include "version.h"                    

/*- Global definitions ------------------------------------------------------*/

#ifdef XITAMI_PRO
#   define XITAMI_NAME       "Xitami/Pro"
#   define SERVER_NAME       "Xitami/Pro/" VERSION " " COPYRIGHT
#   undef  QUOTES_TEXT
#   define QUOTES_TEXT                                                         \
    "NOTICE: this program is commercial software and is protected by a "    \
    "copyright.  Installation is permitted on a single server at once. "    \
    "For additional licenses, please contact iMatix.com."            
#else
#   define XITAMI_NAME       "Xitami"
#   define SERVER_NAME       "Xitami/" VERSION " " COPYRIGHT
#   define QUOTES_TEXT                                                         \
    "NOTICE: this program is Open Source Software; please read the file "   \
    "LICENSE.TXT for conditions of use and distribution.  Xitami is "       \
    "provided in the hope that it will be useful, but without warranty, "   \
    "not even the implied warranty of merchantability or fitness for a "    \
    "particular purpose."
#endif

#define SERVER_VERS  "Xitami/" VERSION
#define APPLICATION  "Xitami"
#define SETUP_NOTE   \
    "About to enter the browser-based setup screens...  If this does not "  \
    "work, run your browser and connect to 'http://127.0.0.1/admin'. The "  \
    "setup screens are protected by a password defined in xitami.aut or  "  \
    "defaults.aut.  If Windows says that it cannot find URL.DLL, please  "  \
    "install TCP/IP networking.  Now click Ok!"

/*- Global variables --------------------------------------------------------*/

static char
    string [LINE_MAX + 1];              /*  Variable for resource strings    */


#endif

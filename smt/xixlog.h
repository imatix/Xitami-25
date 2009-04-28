/*===========================================================================*
 *                                                                           *
 *  xixlog.h -                                                               *
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

#ifndef _XIXLOG_INCLUDED                /*  Allow multiple inclusions        */
#define _XIXLOG_INCLUDED

#include "xixlogm.h"                    /*  Xixlog message definitions       */


/*- Constants ---------------------------------------------------------------*/

#define XIXLOG_AGENT     "xixlog"       /*  Xixlog agent name                */

/*  Common log file format (NCSA standard)                                   */
#define LOG_FORMAT_CLF   "$(client) - $(user) [$(datetime)] \"$(request)\" "\
                         "$(status) $(sent)"

/*  Extended common log file format (Apache standard)                        */
#define LOG_FORMAT_CLFX  "$(client) - $(user) [$(datetime)] \"$(request)\" "\
                         "$(status) $(sent) \"$(referer)\" \"$(agent)\""

/*  Microsoft log file format (IIS, PWS format)                              */
#define LOG_FORMAT_MS    "$(client), $(user), $(mon)/$(day)/$(year), " \
                         "$(hh):$(mm):$(ss), $(service), Xitami, $(ipsrv), "\
                         "$(stime), $(recd), $(sent), $(status), 0, " \
                         "$(method), $(file)"

/*  Log file markup language format (specific to Xitami)                     */
#define LOG_FORMAT_LML   "<LOG"                      \
                         " DATE=\"$(datetime)\""     \
                         " CLIENT=\"$(client)\""     \
                         " REQUEST=\"$(request)\""   \
                         " METHOD=\"$(method)\""     \
                         " STATUS=\"$(status)\""     \
                         " SENT=\"$(sent)\""         \
                         " FILENAME=\"$(file)\""     \
                         " USERNAME=\"$(user)\""     \
                         " SERVICE=\"$(service)\""   \
                         "/>"

/*  Extended log file markup language format (specific to Xitami)           */
#define LOG_FORMAT_XLML  "<LOG"                      \
                         " DATE=\"$(datetime)\""     \
                         " CLIENT=\"$(client)\""     \
                         " CLIENTIP=\"$(ipcli)\""    \
                         " SERVERIP=\"$(ipsrv)\""    \
                         " REQUEST=\"$(request)\""   \
                         " METHOD=\"$(method)\""     \
                         " STATUS=\"$(status)\""     \
                         " RECEIVED=\"$(recd)\""     \
                         " SENT=\"$(sent)\""         \
                         " DURATION=\"$(time_ms)\""  \
                         " FILENAME=\"$(file)\""     \
                         " USERAGENT=\"$(agent)\""   \
                         " REFERER=\"$(referer)\""   \
                         " USERNAME=\"$(user)\""     \
                         " SERVICE=\"$(service)\""   \
                         " VHOST=\"$(vhost)\""       \
                         "/>"

/*  When to cycle the log file                                               */

#define XI_CYCLE_STARTUP  "startup"     /*  Cycle when starting the server   */
#define XI_CYCLE_HOURLY   "hourly"      /*  Cycle every hour at X minutes    */
#define XI_CYCLE_DAILY    "daily"       /*  Cycle every day at hh:mm         */
#define XI_CYCLE_WEEKLY   "weekly"      /*  Cycle every week at dd:hh:mm     */
#define XI_CYCLE_MONTHLY  "monthly"     /*  Cycle every month at dd:hh:mm    */
#define XI_CYCLE_SIZE     "size"        /*  Cycle when exceeds X Kb          */
#define XI_CYCLE_LINES    "lines"       /*  Cycle when exceeds X lines       */
#define XI_CYCLE_MANUAL   "manual"      /*  Do not cycle the log file        */

/*  How to cycle the log file                                                */

#define XI_CYCLE_RENAME   "rename"      /*  Rename old file                  */
#define XI_CYCLE_DELETE   "delete"      /*  Delete old file                  */
#define XI_CYCLE_MOVE     "move"        /*  Move old file to another path    */
#define XI_CYCLE_CONCAT   "concat"      /*  Concat old data to file          */
#define XI_CYCLE_PROCESS  "process"     /*  Execute some command on file     */

/*  Log file statistics, updated in each thread's TCB                        */

typedef struct {
    qbyte file_size;                    /*    Log file size, in bytes        */
    qbyte file_lines;                   /*    Log file size, in lines        */
} LOGSTATS;


/*- Function prototypes -----------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int xixlog_init (void);

#ifdef __cplusplus
}

#endif

#endif

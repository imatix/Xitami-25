/*===========================================================================*
 *                                                                           *
 *  smtupm.h -                                                               *
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
    Synopsis:   Defines constants, messages, and prototypes for the UPM
                (unattended process monitor) agents.

*/
#ifndef _SMTUPM_INCLUDED                /*  Allow multiple inclusions        */
#define _SMTUPM_INCLUDED


/*---------------------------------------------------------------------------
 *  Function prototypes
 */

#ifdef __cplusplus
extern "C" {
#endif

int  smtupmc_init (char *args, char *port);
int  smtupmd_init (char *inifile, char *port);

#ifdef __cplusplus
}
#endif


/*---------------------------------------------------------------------------
 *  Constants
 */

#define SMT_UPMD        "smtupmd"       /*  Name of UPM daemon agent         */
#define SMT_UPMC        "smtupmc"       /*  Name of UPM client agent         */
#define SMT_UPM_PORT    "5050"          /*  Port for UPM connection          */

/*  Messages (EXDR formatted events)                                         */

#define SMT_UPM_MESSAGE  "ds"
/*  d=message identifier                                                     */
/*  s=message string                                                         */

#define UPM_LIST         100            /*  List processes                   */
#define UPM_HALT         101            /*  Halt UPM and processes           */
#define UPM_START        102            /*  Start-up a process               */
#define UPM_STOP         103            /*  Shut-down a process              */
#define UPM_STATUS       104            /*  Enquire process status           */
#define UPM_READY        200            /*  Reply ready for command          */
#define UPM_ERROR        201            /*  Reply fatal error                */
#define UPM_HALTING      202            /*  Reply halting UPM                */
#define UPM_TASK_ID      203            /*  Reply task name                  */
#define UPM_TASK_OK      204            /*  Reply task status                */
#define UPM_TASK_NF      205            /*  Reply unknown task               */
#define UPM_TASK_RUNNING 206            /*  Reply task is running            */
#define UPM_TASK_STOPPED 207            /*  Reply task is not running        */
#define UPM_START_OK     208            /*  Reply task started ok            */
#define UPM_START_ERROR  209            /*  Reply task could not be started  */
#define UPM_STOP_OK      210            /*  Reply task stopped ok            */
#define UPM_STOP_ERROR   211            /*  Reply task could not be stopped  */

#endif                                  /*  Include smtlib.h                 */

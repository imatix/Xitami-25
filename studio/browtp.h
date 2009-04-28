/*===========================================================================*
 *                                                                           *
 *  browtp.h - WTP broker functions                                          *
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

#ifndef _BROWTP_INCLUDED                /*  Allow multiple inclusions        */
#define _BROWTP_INCLUDED

#if defined (USE_WTP_BROKER)

/*  --- TRANSACTION MANAGER API -------------------------------------------- */

/*  Prototypes for transaction manager functions                             */

int   wtp_broker       (void);

#define STACK_MAX        16             /*  Max. application call depth      */
#define PRGNAME_MAX      64+1           /*  Max. program name size           */
#define LANG_MAX         15+1           /*  Max. language code size          */
#define ARGS_MAX         1024           /*  Max. parameters length           */

/*  This is the format of the WTP session context block                      */

typedef struct {
/*- Private variables ----------------- */
    VDESCR *buffer_;                    /*  Form input/output buffer         */
/*- Public variables ------------------ */
    FORM_ITEM *form;                    /*  Current form instance            */
    SYMTAB    *symbols;                 /*  Program form symbols             */
    char program_name    [PRGNAME_MAX]; /*  Current program name             */
    char program_to_call [PRGNAME_MAX]; /*  Program that we want to call     */
    int  program_callcode;              /*  Result of call request           */
    byte disable_actions;               /*  Show disabled actions?           */
    char user_language   [LANG_MAX];    /*  User language code               */
    Bool back_used;                     /*  Was browser 'back' used          */
} SESSION;


/*  Broker program feedbacks                                                 */

enum {
    FEEDBACK_SHOW     = 0,              /*  Show the form                    */
    FEEDBACK_CALL     = 1,              /*  Call a new program               */
    FEEDBACK_RETURN   = 2,              /*  Return to parent program         */
    FEEDBACK_ERROR    = 3,              /*  Error - terminate                */
    FEEDBACK_UNKNOWN  = 4               /*  Program unknown in application   */
};

/*  Values for session callcode - map to WTP values                          */

enum {
    CALLCODE_OKAY     = WTP_NOERROR,
    CALLCODE_UNKNOWN  = WTP_ERRORNOTFOUND,
    CALLCODE_ACTIVE   = WTP_ERRORWOULDLOOP,
    CALLCODE_OVERFLOW = WTP_ERROROVERFLOW
};


/*  Prompt modes                                                             */

enum {
    DISABLE_VISIBLE   = 0,              /*  Disable unused prompts           */
    DISABLE_HIDDEN    = 1               /*  Hide unused prompts              */
};


/*  Each logical program is handled by a ATP_FCT function; the broker        */
/*  must define a correspondence table between logical programs and          */
/*  function entry points.                                                   */

typedef int (*ATP_FCT) (SESSION *);

typedef struct {
    char   *name;                       /*  Name of program                  */
    ATP_FCT function;                   /*  And function that provides it    */
} BROKER_MAP;


/*  This global table must be supplied by the broker program as a static     */
/*  table with the program names in alphabetical order, and the final        */
/*  entry a NULL, NULL pair.  Program names must be lowercase.               */

extern BROKER_MAP
    wtp_broker_map [];

#endif
#endif

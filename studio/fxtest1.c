/*===========================================================================*
 *                                                                           *
 *  fxtest1.c - Test program 1                                               *
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

#include "fxtest1.d"                    /*  Include dialog data              */
#include "fxtest1.h"                    /*  Form definition file             */

/*- Function prototypes -----------------------------------------------------*/

static Bool dump_symbol (SYMBOL *symbol, ...);


/*- Global variables used in this source file only --------------------------*/

static struct {
    char mark1;
    char bulk1 [32000];
    char mark2;
    char bulk2 [32000];
    char mark3;
    char bulk3 [32000];
    char mark4;
    char bulk4 [32000];
    char mark5;
} cb;

static FXTEST1_DATA *form_data;         /*  Form data block                  */


/********************************   M A I N   ********************************/

int fxtest1_program (SESSION *p_session)
{
    session = p_session;                /*  Localise session block           */
    /*  - - - - - - - - - - - - - - - - - - Do nothing else here - - - - - - */
#   include "fxtest1.i"                 /*  Include dialog interpreter       */
}


/*************************   INITIALISE THE PROGRAM   ************************/

MODULE initialise_the_program (void)
{
    cb.mark1 = '1';
    cb.mark2 = '2';
    cb.mark3 = '3';
    cb.mark4 = '4';
    cb.mark5 = '5';
    memset (cb.bulk1, 'a', 32000);
    memset (cb.bulk2, 'b', 32000);
    memset (cb.bulk3, 'c', 32000);
    memset (cb.bulk4, 'd', 32000);

    fxlist_reset (FXTEST1_CURRENCY, 0);
    fxlist_reset (FXTEST1_CURRENCY, 1);
    fxlist_reset (FXTEST1_CURRENCY, 2);
    fxlist_reset (FXTEST1_CURRENCY, 3);
    fxlist_reset (FXTEST1_CURRENCY, 4);

    fxlist_append (FXTEST1_CURRENCY, 0, "BEF", "Belgian Franc");
    fxlist_append (FXTEST1_CURRENCY, 0, "USD", "US Dollars");
    fxlist_append (FXTEST1_CURRENCY, 0, "CAD", "Canadian Dollars");

    fxlist_append (FXTEST1_CURRENCY, 1, "YEN", "Japanese Yen");
    fxlist_append (FXTEST1_CURRENCY, 1, "CAD", "Canadian Dollars");

    fxlist_append (FXTEST1_CURRENCY, 2, "ITL", "Italian Lire");
    fxlist_append (FXTEST1_CURRENCY, 2, "TUP", "Turkish Pounds");
    fxlist_append (FXTEST1_CURRENCY, 2, "IRP", "Irish Pounds");
    fxlist_append (FXTEST1_CURRENCY, 2, "UKP", "British Pounds");

    the_next_event = ok_event;
}


/************************   PREPARE FOR OUTPUT ONLY   ************************/

MODULE prepare_for_output_only (void)
{
    session-> form-> input_range = range_none;
}


/***************************   PREPARE FOR INPUT   ***************************/

MODULE prepare_for_input (void)
{
    session-> form-> input_range = range_all;
    strcpy (form_data-> message_to_user, "Enter new record data");
    form_data-> message_to_user_a = FATTR_MESSAGE;
}


/**************************   CALL PROGRAM TEST 2   **************************/

MODULE call_program_test_2 (void)
{
    strcpy ((char *) child_args, form_data-> params);
    request_program_call ("fxtest2");
}


/**************************   AFTER CALLING TEST 2   *************************/

MODULE after_calling_test_2 (void)
{
    strcpy (form_data-> params, (char *) child_args);
}


/**************************   CALL PROGRAM TEST 3   **************************/

MODULE call_program_test_3 (void)
{
    strcpy ((char *) child_args, form_data-> params);
    request_program_call ("fxtest3");
}


/**************************   AFTER CALLING TEST 3   *************************/

MODULE after_calling_test_3 (void)
{
    strcpy (form_data-> params, (char *) child_args);
}


/*************************   SIMULATE PROGRAM LOOP   *************************/

MODULE simulate_program_loop (void)
{
    sleep (4);
}


/**************************   BEFORE SHOWING FORM   **************************/

MODULE before_showing_form (void)
{
    static int
        counter = 0;
        
    form_data-> mark1 [0] = cb.mark1;
    form_data-> mark2 [0] = cb.mark2;
    form_data-> mark3 [0] = cb.mark3;
    form_data-> mark4 [0] = cb.mark4;
    form_data-> mark5 [0] = cb.mark5;

    fxput_int  (FXTEST1_EVENT,       session-> form-> event);
    fxput_int  (FXTEST1_CLICK_FIELD, session-> form-> click_field);
    fxput_int  (FXTEST1_CLICK_INDEX, session-> form-> click_index);
    fxput_int  (FXTEST1_IMAGE_X,     session-> form-> image_x);
    fxput_int  (FXTEST1_IMAGE_Y,     session-> form-> image_y);
    fxput_bool (FXTEST1_SHOW_SSL,    session-> form-> ssl_protocol);
    fxput_bool (FXTEST1_BACK_USED,   session-> back_used);
    
    fxput_int  (FXTEST1_COUNTER, ++counter);
}


/***************************   AFTER SHOWING FORM   **************************/

MODULE after_showing_form (void)
{
    strclr (form_data-> message_to_user);
}


/*************************   TERMINATE THE PROGRAM    ************************/

MODULE terminate_the_program (void)
{
    the_next_event = terminate_event;
}


/****************************   SET SECURE MODE   ****************************/

MODULE set_secure_mode (void)
{
    session-> form-> ssl_protocol = TRUE;
}


/***************************   SET INSECURE MODE   ***************************/

MODULE set_insecure_mode (void)
{
    session-> form-> ssl_protocol = FALSE;
}


/**************************   CALL REQUEST FAILED   **************************/

MODULE call_request_failed (void)
{
}


/***************************   AFTER RETURN CALL   ***************************/

MODULE after_return_call (void)
{
}


/**************************   BEFORE REQUEST CALL   **************************/

MODULE before_request_call (void)
{
}


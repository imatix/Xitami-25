/*===========================================================================*
 *                                                                           *
 *  formio.h - Form i/o prototypes                                           *
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
    Synopsis:   Defines structures and constants for the form interface.
                Include this file after the "sfl.h" file in a program that
                uses the form interface.
*/
#ifndef _FORMIO_INCLUDED                /*  Allow multiple inclusions        */
#define _FORMIO_INCLUDED


/*  This structure defines a field descriptor                                */

typedef struct {
    word  data;                         /*  Offset into form data block      */
    word  block;                        /*  Offset into block list           */
    word  max;                          /*  Max. size of field value         */
} FIELD_DEFN;

/*  This structure defines a static form description                         */

typedef struct {
    byte * blocks;                      /*  List of blocks in form           */
    FIELD_DEFN
         * fields;                      /*  List of fields in form           */
    int    block_count;                 /*  Number of blocks in the form     */
    int    field_count;                 /*  Number of fields in the form     */
    int    action_count;                /*  Number of actions on form        */
    size_t fields_size;                 /*  Size of data part of form        */
    char  *form_name;                   /*  Form name                        */
} FORM_DEFN;

/*  This structure defines a range of fields on the form                     */
/*  If the range is set to -1,0 it means 'no fields'.  If it is set to       */
/*  0,-1 it means 'all fields'.                                              */

typedef struct {
    int first;                          /*  First field on form, from 0      */
    int last;                           /*  Last field on form               */
} RANGE;

/*  This structure defines a dynamic form instance                           */

typedef struct {
    FORM_DEFN *defn;                    /*  Form definition                  */
    int     click_event;                /*  When Enter used as action        */
    size_t  data_size;                  /*  Field data, attr, actions        */
    byte   *data;                       /*  Field attributes & data          */
    Bool    JavaScript;                 /*  Browser can handle JavaScript?   */
    Bool    ssl_protocol;               /*  Use SSL/3 protocol?              */
    int     status;                     /*  Put or Get okay?                 */
    int     event;                      /*  Event from form action, or -1    */
    int     date_order;                 /*  Default date field order         */
    char    date_sep;                   /*  Default date separator char      */
    char    dec_point;                  /*  Decimal point character          */
    int     language;                   /*  Form user language               */
    int     focus_field;                /*  Where to put the cursor          */
    int     focus_index;                /*    if 0, first input field        */
    int     click_field;                /*  When Enter used as action        */
    int     click_index;                /*  Index for Enter/click action     */
    char    livelink [9];               /*  For live-link click fields       */
    int     image_x;                    /*  When clicked on image action     */
    int     image_y;                    /*  When clicked on image action     */
    RANGE   input_range;                /*  Outside range = closed           */
    RANGE   blank_range;                /*  Inside range = hidden            */
    SYMTAB *list_values;                /*  Select list values, if any       */
} FORM_ITEM;


/*  Function called by form_exec(); receives the current form item, a pointer
 *  to the current block size; the current block and field number, and a
 *  variable argument list pointer that can be decoded using va_arg().
 */
typedef Bool (*blockfunc) (FORM_ITEM *form, byte *block, int field, va_list ap);


/*  Form form-level functions                                                */

FORM_ITEM * form_init      (FORM_DEFN *defn, Bool values);
size_t      form_put       (FORM_ITEM *form, VDESCR *buffer, SYMTAB *table);
int         form_get       (FORM_ITEM *form, const char *values);
void        form_use       (FORM_ITEM *form);
void        form_term      (FORM_ITEM *form);
int         form_save      (const char *filename, FORM_ITEM *form);
FORM_ITEM * form_load      (const char *filename, FORM_DEFN *defn);
void        form_dump      (FORM_ITEM *form);
int         form_exec      (FORM_ITEM *form, blockfunc func, ...);
int         form_ftype     (FORM_ITEM *form, int field);

/*  Form field-level functions and macros                                    */
/*  These functions access a field, possibly in a repeating table            */

int         fxputn_text    (int field, int index, const char *new_value);
int         fxputn_char    (int field, int index, char        new_value);
int         fxputn_date    (int field, int index, long        new_value);
int         fxputn_time    (int field, int index, long        new_value);
int         fxputn_int     (int field, int index, int         new_value);
int         fxputn_long    (int field, int index, long        new_value);
int         fxputn_double  (int field, int index, double      new_value);
int         fxputn_bool    (int field, int index, Bool        new_value);
char *      fxgetn_text    (int field, int index);
char        fxgetn_char    (int field, int index);
long        fxgetn_date    (int field, int index);
long        fxgetn_time    (int field, int index);
int         fxgetn_int     (int field, int index);
long        fxgetn_long    (int field, int index);
double      fxgetn_double  (int field, int index);
Bool        fxgetn_bool    (int field, int index);
byte        fxattr_get     (int field, int index);
void        fxattr_put     (int field, int index, byte attr);

/*  Functions for manipulating dynamic select lists                          */

size_t      fxlist_size    (int field, int index);
void        fxlist_reset   (int field, int index);
int         fxlist_append  (int field, int index, char *key, char *value);
char       *fxlist_key     (int field, int index);
char       *fxlist_value   (int field, int index);
void        fxlist_set     (int field, int index, char *key);

/*  These macros access non-repeating fields (index = 0)                     */

#define fxput_text(f,v)    fxputn_text   ((f), 0, (v))
#define fxput_char(f,v)    fxputn_char   ((f), 0, (v))
#define fxput_date(f,v)    fxputn_date   ((f), 0, (long) (v))
#define fxput_time(f,v)    fxputn_time   ((f), 0, (long) (v))
#define fxput_int(f,v)     fxputn_int    ((f), 0, (int)  (v))
#define fxput_long(f,v)    fxputn_long   ((f), 0, (long) (v))
#define fxput_double(f,v)  fxputn_double ((f), 0, (v))
#define fxput_bool(f,v)    fxputn_bool   ((f), 0, (Bool) (v))
#define fxget_text(f)      fxgetn_text   ((f), 0)
#define fxget_char(f)      fxgetn_char   ((f), 0)
#define fxget_date(f)      fxgetn_date   ((f), 0)
#define fxget_time(f)      fxgetn_time   ((f), 0)
#define fxget_int(f)       fxgetn_int    ((f), 0)
#define fxget_long(f)      fxgetn_long   ((f), 0)
#define fxget_double(f)    fxgetn_double ((f), 0)
#define fxget_bool(f)      fxgetn_bool   ((f), 0)

/*  These macros are used to signal error fields                             */

#define SET_ERROR(f)       fxattr_put ((f),  0,  FATTR_ERROR)
#define SET_ERRORN(f,n)    fxattr_put ((f), (n), FATTR_ERROR)


/*  Form action-button functions                                             */

void action_enable         (FORM_ITEM *form, int event);
void action_disable        (FORM_ITEM *form, int event);
void action_hide           (FORM_ITEM *form, int event);

/*  Form User Languages                                                      */

enum {
    FLANG_ENGLISH    = 0,               /*  Default is English               */
    FLANG_FRENCH     = 1,
    FLANG_DUTCH      = 2,
    FLANG_GERMAN     = 3,
    FLANG_ITALIAN    = 4,
    FLANG_SPANISH    = 5,
    FLANG_PORTUGUESE = 6,
    FLANG_SWEDISH    = 7,
    FLANG_DANISH     = 8,
    FLANG_NORWEGIAN  = 9,
    FLANG_FINNISH    = 10
};

/*  Form status codes                                                        */

enum {
    FSTATUS_OK       = 0,               /*  No errors                        */
    FSTATUS_FORM     = 1,               /*  Invalid form definition          */
    FSTATUS_FIELD    = 2                /*  Invalid value for field          */
};

/*  Form block types                                                         */

enum {
    BLOCK_PLAIN      = 0,               /*  Plain HTML                       */
    BLOCK_COMPRESSED = 1,               /*  Compressed HTML                  */
    BLOCK_IF         = 2,               /*  Conditional block                */
    BLOCK_UNLESS     = 3,               /*  Conditional block                */
    BLOCK_REPEAT     = 4,               /*  Repeated block                   */
    BLOCK_TEXTUAL    = 10,              /*  Textual field                    */
    BLOCK_NUMERIC    = 11,              /*  Numeric field                    */
    BLOCK_DATE       = 12,              /*  Date field                       */
    BLOCK_TIME       = 13,              /*  Time field                       */
    BLOCK_TEXTBOX    = 14,              /*  Multiline text field             */
    BLOCK_BOOLEAN    = 15,              /*  Boolean field                    */
    BLOCK_SELECT     = 16,              /*  Selection field                  */
    BLOCK_RADIO      = 17,              /*  Radio-button data field          */
    BLOCK_ACTION     = 20,              /*  Action-button field              */
    BLOCK_FILE       = 21,              /*  File upload field                */
    BLOCK_IMAGE      = 22               /*  Conditional image                */
};

/*  Form field attributes                                                    */

enum {
    FATTR_INPUT      = 0,               /*  Input field                      */
    FATTR_ERROR      = 1,               /*  Input field, highlighted         */
    FATTR_SECURE     = 2,               /*  Input field, invisible           */
    FATTR_PROTECT    = 3,               /*  Input field, disabled            */
    FATTR_HIDDEN     = 4,               /*  Hidden field                     */
    FATTR_BLANK      = 5,               /*  Field shown as spaces            */
    FATTR_LABEL      = 6,               /*  Normal text                      */
    FATTR_TITLE      = 7,               /*  Bold text                        */
    FATTR_HILITE     = 8,               /*  Reversed text                    */
    FATTR_MESSAGE    = 9,               /*  Error message text               */
    FATTR_OPTION     = 10               /*  Option field                     */
};

/*  Form compression techniques                                              */

enum {
    COMPR_WHOLEDICT  = 0,               /*  Matches all of prev block        */
    COMPR_PARTDICT   = 1                /*  Matches part of prev block       */
};

/*  Form numeric field sign formats                                          */

enum {
    FSIGN_NONE       = 0,               /*  Sign is not displayed            */
    FSIGN_POST       = 1,               /*  If negative, follows number      */
    FSIGN_PRE        = 2,               /*  If negative, precedes number     */
    FSIGN_POSTPLUS   = 3,               /*  If non-zero, follows number      */
    FSIGN_PREPLUS    = 4,               /*  If non-zero, precedes number     */
    FSIGN_FINANCIAL  = 5                /*  Financial sign, e.g. (123)       */
};

/*  Form numeric field decimal formats                                       */

enum {
    FDECFMT_NONE     = 0,               /*  Do not show decimals             */
    FDECFMT_ALL      = 1,               /*  Show all decimals                */
    FDECFMT_DROP     = 2                /*  Drop trailing zero decimals      */
};

/*  Form numeric field filler formats                                        */

enum {
    FFILL_NONE       = 0,               /*  Left-justify, remove zeroes      */
    FFILL_SPACE      = 1,               /*  Right-justify, leading spaces    */
    FFILL_ZERO       = 2                /*  Right-justify, leading zeroes    */
};

/*  Form date field display modes                                            */

enum {
    FSHOW_YMD        = 0,               /*  Show year, month, and day        */
    FSHOW_YM         = 1,               /*  Show year and month only         */
    FSHOW_MD         = 2                /*  Show month and day only          */
};

/*  Form date field display formats                                          */

enum {
    FFORMAT_COMPACT  = 0,               /*  yymmdd                           */
    FFORMAT_SLASH    = 1,               /*  yy/mm/dd (default)               */
    FFORMAT_SPACE    = 2,               /*  yy mm dd                         */
    FFORMAT_COMMA    = 3                /*  yy mm, dd                        */
};

/*  Form date field year display options                                     */

enum {
    FYEAR_FULL       = 0,               /*  1984 (default)                   */
    FYEAR_SHORT      = 1                /*  84                               */
};

/*  Form date field month display options                                    */

enum {
    FMONTH_NUMERIC   = 0,               /*  02 (default)                     */
    FMONTH_COUNTER   = 1,               /*  2                                */
    FMONTH_ALPHA     = 2,               /*  Feb                              */
    FMONTH_UPPER     = 3                /*  FEB                              */
};

/*  Form date field day display options                                      */

enum {
    FDAY_NUMERIC     = 0,               /*  02 (default)                     */
    FDAY_COUNTER     = 1                /*  2                                */
};

/*  Form action field types                                                  */

enum {
    FTYPE_BUTTON     = 0,               /*  Button action                    */
    FTYPE_PLAIN      = 1,               /*  Plain text action                */
    FTYPE_IMAGE      = 2                /*  Image action                     */
};

/*  Form field attributes                                                    */

enum {
    FACTION_ENABLED  = 0,               /*  Action is enabled, normal        */
    FACTION_DISABLED = 1,               /*  Action is disabled, visible      */
    FACTION_HIDDEN   = 2                /*  Action is disabled, hidden       */
};

/*  Form constants, available to fxgen processor                             */

enum {
    FORMIO_INDEX_SIZE   = 3,            /*  Size of SELECT/RADIO indices     */
    FORMIO_DATE_SIZE    = 8,            /*  yyyymmdd stored as string        */
    FORMIO_TIME_SIZE    = 8,            /*  hhmmsscc stored as string        */
    FORMIO_DATA_MAX     = 32767,        /*  Max. size of data block          */
    FORMIO_LIVELINK_MAX = 8,            /*  Max. size of livelink name       */
    FORMIO_SYMNAME_MAX  = 32            /*  For form insertion symbols       */
};

/*  Form global variables                                                    */

extern char *form_strerror;             /*  Form conversion error            */
extern RANGE range_all;                 /*  Range constant                   */
extern RANGE range_none;                /*  Range constant                   */

#endif

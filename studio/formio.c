/*===========================================================================*
 *                                                                           *
 *  formio.c - Form i/o functions                                            *
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

#include "sfl.h"                        /*  SFL library prototypes           */
#include "formio.h"                     /*  Form i/o functions & defines     */


/*  Global variables                                                         */

char
    *form_strerror;                     /*  Form conversion error            */
RANGE
    range_all  = { 0, -1 },             /*  Can be used to initialise        */
    range_none = { -1, 0 };             /*    form ranges                    */


/*  Variables that are global to this source file                            */

static FORM_ITEM
    *cur_form;                          /*  Currently-active form            */
static SYMTAB
    *cur_symtab;                        /*    and its symbol table           */
static int
    cur_focus;                          /*  Field on form that has focus     */

enum {                                  /*  Types of input focus             */
    focus_input = 1,                    /*  On normal input field            */
    focus_field = 2,                    /*  On requested focus field         */
    focus_error = 3                     /*  On field with error              */
};

/*  This JavaScript manipulates the status bar so that actions show cleanly  */
#define STATUS_TEXT \
    "onMouseOver=\"window.status='Click';return true;\" " \
    "onMouseOut=\"window.status='';return true;\""
static char
    *status_text = STATUS_TEXT;

/*  Local function prototypes                                                */

static FORM_ITEM *new_form_item (FORM_DEFN *defn);
static char *get_init_value  (byte *block_ptr);
static void  put_block       (VDESCR *stream, byte *block, int field, int idx);
static void  put_mem         (VDESCR *stream, char *source, int size);
static void  put_str         (VDESCR *stream, char *source);
static void  put_fmt         (VDESCR *stream, char *format, ...);
static void  put_plain       (VDESCR *stream, byte *block);
static void  put_compressed  (VDESCR *stream, byte *block);
static void  put_textual     (VDESCR *stream, byte *block, int field, int idx);
static void  put_file        (VDESCR *stream, byte *block, int field, int idx);
static void  put_numeric     (VDESCR *stream, byte *block, int field, int idx);
static void  put_date        (VDESCR *stream, byte *block, int field, int idx);
static void  put_time        (VDESCR *stream, byte *block, int field, int idx);
static void  put_textbox     (VDESCR *stream, byte *block, int field, int idx);
static void  put_boolean     (VDESCR *stream, byte *block, int field, int idx);
static void  put_select      (VDESCR *stream, byte *block, int field, int idx);
static void  put_radio       (VDESCR *stream, byte *block, int field, int idx);
static void  put_action      (VDESCR *stream, byte *block, int index);
static void  put_action_img  (VDESCR *stream, byte *block, int index);
static void  put_image       (VDESCR *stream, byte *block, int field, int idx);
static void  put_option      (VDESCR *stream, char *value, int field, int idx);
static void  set_focus       (byte *block, int field, int index, byte attr);
static Bool  within_blank    (int field);
static Bool  within_input    (int field, int index);
static Bool  within_range    (RANGE *range, int field);
static byte *field_attr      (int field, int index);
static char *field_value     (int field, int index);
static char *field_name      (byte *block, int index);
static void  get_cvnopts     (byte *block, int *flags, int *sign, int *decs,
                              int *width);
static int   update_field    (byte *block, int field, int index, char *value);
static void  reset_attr      (int field, int index);
static int   get_textual     (byte *block, int field, int index, char *value);
static int   get_textbox     (byte *block, int field, int index, char *value);
static int   get_numeric     (byte *block, int field, int index, char *value);
static int   get_date        (byte *block, int field, int index, char *value);
static int   get_time        (byte *block, int field, int index, char *value);
static void  get_action      (SYMTAB *symtab, byte *block);
static Bool  empty_value     (char *value);
static char *list_lookup     (int field, int index, int item, char what);
static char *list_key        (int field, int index, int item, char what);

static Bool  form_init_block (FORM_ITEM *form, byte *block_ptr,
                              int field_nbr, va_list argptr);
static Bool  form_get_block  (FORM_ITEM *form, byte *block_ptr,
                              int field_nbr, va_list argptr);
static Bool  form_dump_block (FORM_ITEM *form, byte *block_ptr,
                              int field_nbr, va_list argptr);
static Bool  form_set_action (FORM_ITEM *form, byte *block_ptr,
                              int field_nbr, va_list argptr);
static Bool  form_get_click  (SYMBOL *symbol, ...);
static void  check_jsaction  (SYMTAB *symtab);


/*  Macros that unpack block attributes                                      */
/*  These all assume that (b) points to the block length field               */

#define BLOCK_size(b)      ((b) [0] << 8) + ((b) [1])
#define BLOCK_type(b)      ((b) [2])    /*  Type byte                        */
#define BLOCK_attr(b)      ((b) [3])    /*  Attribute, for field blocks      */
#define BLOCK_times(b)     ((b) [4])    /*  Occurs, for field blocks         */

#define PLAIN_data(b)      ((char *) ((b) + 3))

#define COMPRESS_how(b)    ((b) [3])
#define COMPRESS_dict(b)   ((b) [4] << 8) + ((b) [5])
#define COMPRESS_size(b)   ((b) [6] << 8) + ((b) [7])

#define IF_field(b)        ((b) [3] << 8) + ((b) [4])
#define IF_scope(b)        ((b) [5] << 8) + ((b) [6])
#define IF_value(b)        ((b) [7] << 8) + ((b) [8])

#define UNLESS_field(b)    ((b) [3] << 8) + ((b) [4])
#define UNLESS_scope(b)    ((b) [5] << 8) + ((b) [6])
#define UNLESS_value(b)    ((b) [7] << 8) + ((b) [8])

#define REPEAT_field(b)    ((b) [3] << 8) + ((b) [4])
#define REPEAT_scope(b)    ((b) [5] << 8) + ((b) [6])
#define REPEAT_occurs(b)   ((b) [7] << 8) + ((b) [8])

#define TEXTUAL_attr(b)    ((b) [3])
#define TEXTUAL_times(b)   ((b) [4])
#define TEXTUAL_flags(b)   ((b) [5])
#define TEXTUAL_size(b)    ((b) [6] << 8) + ((b) [7])
#define TEXTUAL_max(b)     ((b) [8] << 8) + ((b) [9])
#define TEXTUAL_name(b)    ((char *) ((b) + 10))
#define TEXTUAL_value(b)   (TEXTUAL_name  (b) + strlen (TEXTUAL_name  (b)) + 1)
#define TEXTUAL_html(b)    (TEXTUAL_value (b) + strlen (TEXTUAL_value (b)) + 1)

#define FILE_attr(b)       ((b) [3])
#define FILE_times(b)      ((b) [4])
#define FILE_size(b)       ((b) [5] << 8) + ((b) [6])
#define FILE_max(b)        ((b) [7] << 8) + ((b) [8])
#define FILE_name(b)       ((char *) ((b) + 9))
#define FILE_value(b)      (FILE_name  (b) + strlen (FILE_name  (b)) + 1)
#define FILE_html(b)       (FILE_value (b) + strlen (FILE_value (b)) + 1)

#define NUMERIC_attr(b)    ((b) [3])
#define NUMERIC_times(b)   ((b) [4])
#define NUMERIC_size(b)    ((b) [5] << 8) + ((b) [6])
#define NUMERIC_max(b)     ((b) [7] << 8) + ((b) [8])
#define NUMERIC_decs(b)    ((b) [9])
#define NUMERIC_sign(b)    ((b) [10])
#define NUMERIC_decfmt(b)  ((b) [11])
#define NUMERIC_fill(b)    ((b) [12])
#define NUMERIC_blank(b)   ((b) [13])
#define NUMERIC_comma(b)   ((b) [14])
#define NUMERIC_name(b)    ((char *) ((b) + 15))
#define NUMERIC_value(b)   (NUMERIC_name  (b) + strlen (NUMERIC_name  (b)) + 1)
#define NUMERIC_html(b)    (NUMERIC_value (b) + strlen (NUMERIC_value (b)) + 1)

#define DATE_attr(b)       ((b) [3])
#define DATE_times(b)      ((b) [4])
#define DATE_size(b)       ((b) [5] << 8) + ((b) [6])
#define DATE_show(b)       ((b) [7])
#define DATE_format(b)     ((b) [8])
#define DATE_year(b)       ((b) [9])
#define DATE_month(b)      ((b) [10])
#define DATE_day(b)        ((b) [11])
#define DATE_name(b)       (char *) ((b) + 12)
#define DATE_value(b)      (DATE_name    (b) + strlen (DATE_name    (b)) + 1)
#define DATE_picture(b)    (DATE_value   (b) + strlen (DATE_value   (b)) + 1)
#define DATE_html(b)       (DATE_picture (b) + strlen (DATE_picture (b)) + 1)

#define TIME_attr(b)       ((b) [3])
#define TIME_times(b)      ((b) [4])
#define TIME_size(b)       ((b) [5] << 8) + ((b) [6])
#define TIME_name(b)       (char *) ((b) + 7)
#define TIME_value(b)      (TIME_name    (b) + strlen (TIME_name    (b)) + 1)
#define TIME_picture(b)    (TIME_value   (b) + strlen (TIME_value   (b)) + 1)
#define TIME_html(b)       (TIME_picture (b) + strlen (TIME_picture (b)) + 1)

#define TEXTBOX_attr(b)    ((b) [3])
#define TEXTBOX_times(b)   ((b) [4])
#define TEXTBOX_rows(b)    ((b) [5])
#define TEXTBOX_cols(b)    ((b) [6])
#define TEXTBOX_flags(b)   ((b) [7])
#define TEXTBOX_max(b)     ((b) [8] << 8) + ((b) [9])
#define TEXTBOX_name(b)    ((char *) ((b) + 10))
#define TEXTBOX_value(b)   (TEXTBOX_name  (b) + strlen (TEXTBOX_name  (b)) + 1)
#define TEXTBOX_html(b)    (TEXTBOX_value (b) + strlen (TEXTBOX_value (b)) + 1)

#define BOOLEAN_attr(b)    ((b) [3])
#define BOOLEAN_times(b)   ((b) [4])
#define BOOLEAN_name(b)    ((char *) ((b) + 5))
#define BOOLEAN_value(b)   (BOOLEAN_name  (b) + strlen (BOOLEAN_name  (b)) + 1)
#define BOOLEAN_true(b)    (BOOLEAN_value (b) + strlen (BOOLEAN_value (b)) + 1)
#define BOOLEAN_false(b)   (BOOLEAN_true  (b) + strlen (BOOLEAN_true  (b)) + 1)
#define BOOLEAN_html(b)    (BOOLEAN_false (b) + strlen (BOOLEAN_false (b)) + 1)

#define SELECT_attr(b)     ((b) [3])
#define SELECT_times(b)    ((b) [4])
#define SELECT_size(b)     ((b) [5])
#define SELECT_options(b)  ((b) [6])
#define SELECT_onchange(b) ((b) [7])
#define SELECT_name(b)     ((char *) ((b) + 8))
#define SELECT_value(b)    (SELECT_name   (b) + strlen (SELECT_name   (b)) + 1)
#define SELECT_script(b)   (SELECT_value  (b) + strlen (SELECT_value  (b)) + 1)
#define SELECT_html(b)     (SELECT_script (b) + strlen (SELECT_script (b)) + 1)
#define SELECT_nosel(b)    (SELECT_html   (b) + strlen (SELECT_html   (b)) + 1)
#define SELECT_first(b)    (SELECT_nosel  (b) + strlen (SELECT_nosel  (b)) + 1)

#define RADIO_attr(b)      ((b) [3])
#define RADIO_times(b)     ((b) [4])
#define RADIO_column(b)    ((b) [5])
#define RADIO_options(b)   ((b) [6])
#define RADIO_onchange(b)  ((b) [7])
#define RADIO_name(b)      ((char *) ((b) + 8))
#define RADIO_value(b)     (RADIO_name   (b) + strlen (RADIO_name   (b)) + 1)
#define RADIO_script(b)    (RADIO_value  (b) + strlen (RADIO_value  (b)) + 1)
#define RADIO_html(b)      (RADIO_script (b) + strlen (RADIO_script (b)) + 1)
#define RADIO_nosel(b)     (RADIO_html   (b) + strlen (RADIO_html   (b)) + 1)
#define RADIO_first(b)     (RADIO_nosel  (b) + strlen (RADIO_nosel  (b)) + 1)

#define ACTION_type(b)     ((b) [3])
#define ACTION_times(b)    ((b) [4])
#define ACTION_event(b)    ((b) [5] << 8) + ((b) [6])
#define ACTION_index(b)    ((b) [7] << 8) + ((b) [8])
#define ACTION_show(b)     ((b) [9])
#define ACTION_height(b)   ((b) [10] << 8) + ((b) [11])
#define ACTION_width(b)    ((b) [12] << 8) + ((b) [13])
#define ACTION_name(b)     ((char *) ((b) + 14))
#define ACTION_label(b)    (ACTION_name     (b) + strlen (ACTION_name     (b)) + 1)
#define ACTION_rollover(b) (ACTION_label    (b) + strlen (ACTION_label    (b)) + 1)
#define ACTION_confirm(b)  (ACTION_rollover (b) + strlen (ACTION_rollover (b)) + 1)
#define ACTION_alt(b)      (ACTION_confirm  (b) + strlen (ACTION_confirm  (b)) + 1)
#define ACTION_html(b)     (ACTION_alt      (b) + strlen (ACTION_alt      (b)) + 1)

#define IMAGE_attr(b)      ((b) [3])
#define IMAGE_times(b)     ((b) [4])
#define IMAGE_max(b)       ((b) [5])
#define IMAGE_name(b)      ((char *) ((b) + 6))
#define IMAGE_label(b)     (IMAGE_name  (b) + strlen (IMAGE_name  (b)) + 1)
#define IMAGE_value(b)     (IMAGE_label (b) + strlen (IMAGE_label (b)) + 1)

#define BLOCK_IS_FIELD(t)  ((t) == BLOCK_TEXTUAL || \
                            (t) == BLOCK_NUMERIC || \
                            (t) == BLOCK_DATE    || \
                            (t) == BLOCK_TIME    || \
                            (t) == BLOCK_TEXTBOX || \
                            (t) == BLOCK_BOOLEAN || \
                            (t) == BLOCK_SELECT  || \
                            (t) == BLOCK_FILE    || \
                            (t) == BLOCK_RADIO   || \
                            (t) == BLOCK_IMAGE      )

/*  Macros to access field information on the current form                   */

#define FIELD_data(f)  ((char *) cur_form-> data + \
                                 cur_form-> defn-> fields [f].data)
#define FIELD_block(f) (cur_form-> defn-> blocks + \
                        cur_form-> defn-> fields [f].block)
#define FIELD_max(f)   (cur_form-> defn-> fields [f].max)
#define ACTION_attr(b,i) ((char *) cur_form-> data + \
                        cur_form-> defn-> fields_size + ACTION_index (b) + i)


/*  Field flag settings                                                      */

#define FLAG_UPPERCASE      1           /*  Bit zero                         */


/*  Table defines presentation for each attribute                            */

typedef struct {
    char *input;                        /*  Input type; NULL = output        */
    char *output;                       /*  Presentation when output only    */
    int   error;                        /*  1 if field is an error input     */
    int   blank;                        /*  1 if field is blanked-out        */
} ATTR_TAGS;

static ATTR_TAGS attr_tags [] = {
    { "TEXT", "%s",                 0, 0 }, /*  FATTR_INPUT                  */
    { "TEXT", "%s",                 1, 0 }, /*  FATTR_ERROR                  */
    { "PASSWORD", "",               0, 0 }, /*  FATTR_SECURE                 */
    {  NULL, "%s",                  0, 0 }, /*  FATTR_PROTECT                */
    { "HIDDEN", "",                 0, 1 }, /*  FATTR_HIDDEN                 */
    {  NULL,  "",                   0, 1 }, /*  FATTR_BLANK                  */
    {  NULL, "%s",                  0, 0 }, /*  FATTR_LABEL                  */
    {  NULL, "<B>%s</B>",           0, 0 }, /*  FATTR_TITLE                  */
    {  NULL, "<STRONG>%s</STRONG>", 0, 0 }, /*  FATTR_HILITE                 */
    {  NULL, "<BIG>%s</BIG>",       0, 0 }, /*  FATTR_MESSAGE                */
    {  NULL, "%s",                  0, 0 }  /*  FATTR_OPTION                 */
};


/*  ---------------------------------------------------------------------[<]-
    Function: form_init

    Synopsis: Creates a new form instance; allocates a new FORM_ITEM and
    intialises all fields to their default values, if the values argument
    is TRUE.  If it is FALSE, fields will have an undefined value.
    ---------------------------------------------------------------------[>]-*/

FORM_ITEM *
form_init (
    FORM_DEFN *defn,
    Bool values)
{
    FORM_ITEM
        *form;                          /*  Newly-allocated form item        */

    ASSERT (defn);
    if ((form = new_form_item (defn)) == NULL)
        return (NULL);                  /*  Signal not enough memory         */

    if (values)
      {
        /*  Initialise form control properties                               */
        form-> language     = FLANG_ENGLISH;
        form-> date_order   = DATE_ORDER_DMY;
        form-> date_sep     = '/';
        form-> dec_point    = '.';
        form-> input_range  = range_all;
        form-> blank_range  = range_none;
        form-> ssl_protocol = 0;        /*  By default                       */
        form-> focus_field  = 0;
        form-> focus_index  = 0;
        form-> click_field  = 0;
        form-> click_index  = 0;

        /*  Initialise form field attributes and values                      */
        form_use  (form);
        form_exec (form, form_init_block);
      }
    return (form);
}


/*  --------------------------------------------------------------------------
 *  new_form_item -- internal
 *
 *  Allocates a new form item and internal data blocks, and initialises
 *  static fields where possible.  Returns new form item if okay, NULL if
 *  there was insufficient memory.
 */

static FORM_ITEM *
new_form_item (
    FORM_DEFN *defn)
{
    FORM_ITEM
        *form;                          /*  Newly-allocated form item        */
    MEMTRN
        *memtrn;

    ASSERT (defn);

    /*  Allocate structure variable for new form instance                    */
    memtrn = mem_new_trans ();
    if ((form = mem_alloc (sizeof (FORM_ITEM))) == NULL)
        return (NULL);                  /*  Signal not enough memory         */

    /*  Initialise static fields in form instance                            */
    memset (form, 0, sizeof (FORM_ITEM));
    form-> defn      = defn;
    form-> data_size = defn-> fields_size + defn-> action_count;
    form-> data      = mem_alloc (form-> data_size);
    if (form-> data == NULL)            /*  Check we have enough memory      */
      {                                 /*    else cancel and quit           */
        mem_rollback (memtrn);
        return (NULL);                  /*  Signal not enough memory         */
      }
    memset (form-> data, 0, form-> data_size);
    mem_commit (memtrn);
    return (form);
}


/*  --------------------------------------------------------------------------
 *  form_init_block -- internal
 *
 *  Initialises data field attributes and values.  Repeated fields are
 *  all set to the same attribute and value.
 */

static Bool
form_init_block (
    FORM_ITEM *form,
    byte      *block_ptr,
    int        field_nbr,
    va_list    argptr)
{
    byte
        occurs,                         /*  Field occurs, if repeated        */
        init_attr;                      /*  Field initial attribute          */
    char
        *data_ptr,                      /*  Destination in form data         */
        *init_value;                    /*  Field initial value              */
    int
        occurence;                      /*  Field occurs index               */

    /*  Get and store initial field attribute                                */
    if (BLOCK_IS_FIELD (BLOCK_type (block_ptr)))
      {
        occurs     = BLOCK_times    (block_ptr);
        init_attr  = BLOCK_attr     (block_ptr);
        init_value = get_init_value (block_ptr);

        /*  Point to destination data buffer                                 */
        data_ptr = FIELD_data (field_nbr);

        /*  Set initial attribute for field(s)                               */
        for (occurence = 0; occurence < occurs; occurence++)
            *data_ptr++ = init_attr;

        /*  Set initial value for field(s)                                   */
        ASSERT (strlen (init_value) <= FIELD_max (field_nbr));
        for (occurence = 0; occurence < occurs; occurence++)
          {
            strcpy ((char *) data_ptr, init_value);
            data_ptr += FIELD_max (field_nbr) + 1;
          }
      }
    else
    if (BLOCK_type (block_ptr) == BLOCK_ACTION)
      {
        occurs    = ACTION_times (block_ptr);
        init_attr = ACTION_show  (block_ptr);

        /*  Point to destination data buffer                                 */
        data_ptr = ACTION_attr (block_ptr, 0);

        /*  Set initial attribute for action(s)                              */
        for (occurence = 0; occurence < occurs; occurence++)
            *data_ptr++ = init_attr;
      }
    return (TRUE);
}


/*  --------------------------------------------------------------------------
 *  get_init_value -- internal
 *
 *  Returns initial value for a block.  Initial values are always strings;
 *  this function returns a pointer to the initial value from the block
 *  definition.  The block_ptr argument must point to the block length.
 */

static char *
get_init_value (byte *block_ptr)
{
    switch (BLOCK_type (block_ptr))
      {
        case BLOCK_TEXTUAL: return (TEXTUAL_value (block_ptr));
        case BLOCK_FILE:    return (FILE_value    (block_ptr));
        case BLOCK_NUMERIC: return (NUMERIC_value (block_ptr));
        case BLOCK_DATE:    return (DATE_value    (block_ptr));
        case BLOCK_TIME:    return (TIME_value    (block_ptr));
        case BLOCK_TEXTBOX: return (TEXTBOX_value (block_ptr));
        case BLOCK_BOOLEAN: return (BOOLEAN_value (block_ptr));
        case BLOCK_SELECT:  return (SELECT_value  (block_ptr));
        case BLOCK_RADIO:   return (RADIO_value   (block_ptr));
        case BLOCK_IMAGE:   return (IMAGE_value   (block_ptr));
      }
    return (NULL);                      /*  Undefined block                  */
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_term

    Synopsis: Destroys a form instance, returning all allocated memory to
    the heap.  Does nothing if the supplied form handle is null.
    ---------------------------------------------------------------------[>]-*/

void
form_term (
    FORM_ITEM *form)
{
    if (form)
      {
        if (form-> list_values)
            sym_delete_table (form-> list_values);
        mem_free (form-> data);         /*  Free if allocated                */
        mem_free (form);                /*  Free form item structure         */
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_use

    Synopsis: Sets the current form for future fxget_ and fxput_ calls.
    ---------------------------------------------------------------------[>]-*/

void
form_use (
    FORM_ITEM *form)
{
    ASSERT (form);
    cur_form = form;
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_put

    Synopsis: Formats a form output stream into a memory buffer.  Returns
    the amount of data stored in the buffer.  The memory buffer argument is
    a VDESCR descriptor block that specifies the size and address of a block
    to fill.  If the generated form overflows the buffer, it is truncated.
    To use livelinks, you must have set the form symbol table fields 'main'
    and 'session' appropriately.
    ---------------------------------------------------------------------[>]-*/

size_t
form_put (
    FORM_ITEM *form,                    /*  Form to prepare for output       */
    VDESCR    *stream,                  /*  Form output buffer               */
    SYMTAB    *symtab)                  /*  Form symbol table                */
{
    byte
        *block_ptr,                     /*  Form block pointer               */
        block_type,                     /*  Form block type                  */
        *loop_block_ptr;                /*  Block pointer in loops           */
    int
        field_nbr,                      /*  Form field number                */
        block_nbr,                      /*  Form block number                */
        skip_count,                     /*  Skip N blocks forward            */
        loop_count,                     /*  Number of times to repeat        */
        loop_index,                     /*  Form field index in loops        */
        loop_field_nbr,                 /*  Field number in loops            */
        loop_block_nbr;                 /*  Block number in loops            */

    ASSERT (form);
    ASSERT (stream);
    ASSERT (symtab);

    stream-> cur_size = 0;              /*  Set output stream -> empty       */
    stream-> data = stream-> data;

    form-> status = FSTATUS_OK;         /*  No errors                        */

    field_nbr  = -1;                    /*  Bump before we get to field      */
    skip_count = 0;
    block_nbr  = 0;
    block_ptr  = form-> defn-> blocks;
    cur_form   = form;                  /*  Set current form context to      */
    cur_symtab = symtab;                /*    make function calls easier     */
    cur_focus  = 0;                     /*  Focus not on any field           */
    sym_assume_symbol (symtab, "_focus", "jsaction");

    while (block_nbr < form-> defn-> block_count)
      {
        /*  field_nbr has to indicate the current field; the specific case
         *  of radio blocks makes this a little subtle: the radio labels
         *  need to refer to the data field, which is before them in the
         *  block list.  So, we must increment field_nbr before processing
         *  a field, not afterwards (else it is 1 too high for the radio
         *  label blocks).
         */
        block_type = BLOCK_type (block_ptr);
        if (BLOCK_IS_FIELD (block_type))
            field_nbr++;                /*  Bump field_nbr if needed         */

        if (skip_count > 0)             /*  First off, we skip if possible   */
            skip_count--;
        else
        if (block_type == BLOCK_IF) {
            if (IF_value (block_ptr) == 0) {
                if (strnull (field_value (IF_field (block_ptr), 0)))
                   skip_count = IF_scope (block_ptr);
            }
            else
            if (atoi (field_value (IF_field (block_ptr), 0)) != IF_value (block_ptr))
                skip_count = IF_scope (block_ptr);
        }
        else
        if (block_type == BLOCK_UNLESS) {
            if (UNLESS_value (block_ptr) == 0) {
                if (strused (field_value (UNLESS_field (block_ptr), 0)))
                   skip_count = UNLESS_scope (block_ptr);
            }
            else
            if (atoi (field_value (UNLESS_field (block_ptr), 0)) == UNLESS_value (block_ptr))
                skip_count = UNLESS_scope (block_ptr);
        }
        else
        if (block_type == BLOCK_REPEAT)
          {
            loop_count = atoi (field_value (REPEAT_field (block_ptr), 0));
            for (loop_index = 0; loop_index < loop_count; loop_index++)
              {
                /*  Prepare to output each block in the repeat scope         */
                loop_field_nbr = field_nbr;
                loop_block_ptr = block_ptr;
                for (loop_block_nbr = 0;
                     loop_block_nbr < REPEAT_scope (block_ptr);
                     loop_block_nbr++)
                  {
                    loop_block_ptr += BLOCK_size (loop_block_ptr) + 2;
                    if (BLOCK_IS_FIELD (BLOCK_type (loop_block_ptr)))
                        loop_field_nbr++;
                    put_block (stream, loop_block_ptr, loop_field_nbr,
                               loop_index);
                  }
              }
            /*  Once finished, we can skip over the repeat scope             */
            skip_count = REPEAT_scope (block_ptr);
          }
        else                            /*  Finally output normal block      */
        if (!within_blank (field_nbr))
            put_block (stream, block_ptr, field_nbr, 0);

        block_ptr += BLOCK_size (block_ptr) + 2;
        block_nbr++;
      }

    form-> focus_field = 0;             /*  Clear any focus request          */
    form-> focus_index = 0;             /*    automatically                  */

    /*  Stick-in a null byte to turn stream data into a valid C string       */
    if (stream-> cur_size >= stream-> max_size)
        stream-> cur_size = stream-> max_size - 1;
    stream-> data [stream-> cur_size] = '\0';

    return (stream-> cur_size);
}


/*  --------------------------------------------------------------------------
 *  within_blank -- internal
 *
 *  Returns TRUE if the specified field lies within the current form's blank
 *  range.
 */

static Bool
within_blank (int field_nbr)
{
    return (within_range (&cur_form-> blank_range, field_nbr));
}


/*  --------------------------------------------------------------------------
 *  within_range -- internal
 *
 *  Returns TRUE if the specified field lies within the specified range.
 *  Returns FALSE if not.  The range specifies two fields, a first and a
 *  last.  If the first is -1, the range excludes all fields on the form.
 *  If the last is -1 the range includes all fields on the form.
 *  Otherwise the first and last specify the inclusive range limits.
 */

static Bool
within_range (RANGE *range, int field_nbr)
{
    if (range-> first == -1)
        return (FALSE);
    else
    if (range-> last == -1)
        return (TRUE);
    else
        return (range-> first <= field_nbr &&
                                 field_nbr <= range-> last);
}


/*  --------------------------------------------------------------------------
 *  put_block -- internal
 *
 *  Outputs one non-control block.
 */

static void
put_block (
    VDESCR *stream,
    byte   *block_ptr,
    int     field_nbr,
    int     index)
{
    switch (BLOCK_type (block_ptr))
      {
        case BLOCK_PLAIN:
            put_plain (stream, block_ptr);
            break;
        case BLOCK_COMPRESSED:
            put_compressed (stream, block_ptr);
            break;
        case BLOCK_TEXTUAL:
            put_textual (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_FILE:
            put_file (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_NUMERIC:
            put_numeric (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_DATE:
            put_date (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_TIME:
            put_time (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_TEXTBOX:
            put_textbox (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_BOOLEAN:
            put_boolean (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_SELECT:
            put_select (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_RADIO:
            put_radio (stream, block_ptr, field_nbr, index);
            break;
        case BLOCK_ACTION:
            put_action (stream, block_ptr, index);
            break;
        case BLOCK_IMAGE:
            put_image (stream, block_ptr, field_nbr, index);
            break;
      }
}


/*  --------------------------------------------------------------------------
 *  put_plain -- internal
 */

static void
put_plain (VDESCR *stream, byte *block_ptr)
{
    put_mem (stream, PLAIN_data (block_ptr), BLOCK_size (block_ptr) - 1);
}


/*  --------------------------------------------------------------------------
 *  put_mem -- internal
 *
 *  Appends a block of memory to the output stream; if there is not enough
 *  space in the stream, does nothing.  Updates the stream size.
 */

static void
put_mem (VDESCR *stream, char *source, int size)
{
    static char
        symname [FORMIO_SYMNAME_MAX + 1];
    char
        *mark,                          /*  Position of #                    */
        *close,                         /*  Position of )                    */
        *symvalue;                      /*  Translated symbol value          */
    int
        name_size;                      /*  Size of symbol name              */

    /*  Translate any symbols #(xxx) by their value (if any)                 */
    while (size > 0 && (mark = memchr (source, '#', size)) != NULL)
      {
        /*  Copy up-to but not including # character                         */
        if (mark > source)
          {
            put_mem (stream, source, (int) (mark - source));
            size -= (int) (mark - source);
            source = mark;
          }
        /*  Look for following ( and )                                       */
        close = memchr (source, ')', size);
        if (source [1] == '(' && close)
          {
            name_size = (int) (close - source - 2);
            if (name_size <= FORMIO_SYMNAME_MAX)
              {
                memcpy (symname, source + 2, name_size);
                symname [name_size] = '\0';
                symvalue = sym_get_value (cur_symtab, symname, "(?)");
                put_mem (stream, symvalue, strlen (symvalue));
              }
            else    /*  If name is too long, leave untranslated              */
                put_mem (stream, source, (int) (close - source) + 1);

            size -= (int) (close - source) + 1;
            source = close + 1;
          }
        else                            /*  Did not match #(...), so just    */
          {                             /*    copy the single '#' and loop   */
            if ((stream-> cur_size + 1) < stream-> max_size)
              {
                memcpy (stream-> data + stream-> cur_size, source, 1);
                stream-> cur_size += 1;
              }
            size--;
            source++;
          }
      }
    /*  Copy remaining source data                                           */
    if ((stream-> cur_size + size) < stream-> max_size)
      {
        memcpy (stream-> data + stream-> cur_size, source, size);
        stream-> cur_size += size;
      }
}


/*  --------------------------------------------------------------------------
 *  put_str -- internal
 *
 *  Appends a null-terminated string to the output stream; if there is not
 *  enough space in the stream, does nothing.  Updates the stream size.
 */

static void
put_str (VDESCR *stream, char *source)
{
    put_mem (stream, source, strlen (source));
}


/*  --------------------------------------------------------------------------
 *  put_compressed -- internal
 */

static void
put_compressed (VDESCR *stream, byte *block_ptr)
{
    byte
        *cmp_block;                     /*  Compressed block data            */
    word
        block_size;                     /*  Size of current block            */

    cmp_block = COMPRESS_dict (block_ptr) + cur_form-> defn-> blocks;
    if (COMPRESS_how (block_ptr) == COMPR_WHOLEDICT)
        block_size = BLOCK_size (cmp_block) - 1;
    else
    if (COMPRESS_how (block_ptr) == COMPR_PARTDICT)
        block_size = COMPRESS_size (block_ptr);
    else
        abort ();                       /*  Bad compression method           */

    put_mem (stream, PLAIN_data (cmp_block), block_size);
}


/*  --------------------------------------------------------------------------
 *  put_textual -- internal
 */

static void
put_textual (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    char
        *value;
    ATTR_TAGS
        *tags;
    byte
        attr;                           /*  Field attribute                  */

    attr  = *field_attr (field_nbr, index);
    tags  = &attr_tags [attr];
    value = field_value (field_nbr, index);
    if (TEXTUAL_flags (block_ptr) & FLAG_UPPERCASE)
        strupc (value);                 /*  Change directly in the form      */

    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<input class=%s type=%s name=\"%s\" size=%d maxlength=%d %s" \
            " onFocus=\"this.form.%s.select();\" value=\"",
            tags-> error? "error": "input",
            tags-> input,
            field_name   (block_ptr, index),
            TEXTUAL_size (block_ptr),
            TEXTUAL_max  (block_ptr),
            TEXTUAL_html (block_ptr),
            field_name   (block_ptr, index));

        /*  Translate metacharacters                                         */
        if (attr != FATTR_SECURE)
            while (*value)
              {
                if (*value == '<')
                    put_str (stream, "&lt;");
                else
                if (*value == '>')
                    put_str (stream, "&gt;");
                else
                if (*value == '"')
                    put_str (stream, "&quot;");
                else
                if (*value == '&')
                    put_str (stream, "&amp;");
                else
                    put_mem (stream, value, 1);
                value++;
              }
        put_str (stream, "\">\n");
      }
    else
    if (attr == FATTR_OPTION)
        put_option (stream, value, field_nbr, index);
    else
    if (!tags-> blank)
        put_fmt (stream, tags-> output, *value? value: "&nbsp;");
}

static void
set_focus (byte *block, int field, int index, byte attr)
{
    char
        *name;

    if ((name = field_name (block, index)) == NULL)
        return;                         /*  Not a valid field - ignore       */

    if (attr == FATTR_ERROR
    &&  cur_focus < focus_error)
      {
        cur_focus = focus_error;
        sym_assume_symbol (cur_symtab, "_focus", name);
      }
    else
    if (field == cur_form-> focus_field
    &&  index == cur_form-> focus_index
    &&  cur_focus < focus_field)
      {
        cur_focus = focus_field;
        sym_assume_symbol (cur_symtab, "_focus", name);
      }
    else
    if (attr != FATTR_HIDDEN
    &&  cur_focus < focus_input)
      {
        cur_focus = focus_input;
        sym_assume_symbol (cur_symtab, "_focus", name);
      }
}


/*  --------------------------------------------------------------------------
 *  put_file -- internal
 */

static void
put_file (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    char
        *fname,
        *value,
        *tmp_name;
    ATTR_TAGS
        *tags;
    byte
        attr;                           /*  Field attribute                  */

    value = field_value (field_nbr, index);
    attr  = *field_attr (field_nbr, index);
    tags  = &attr_tags [attr];

    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<input class=%s type=file name=\"%s\" size=%d maxlength=%d %s" \
            " onFocus=\"this.form.%s.select();\" value=\"%s\">\n",
            tags-> error? "error": "input",
            field_name (block_ptr, index),
            FILE_size  (block_ptr),
            FILE_max   (block_ptr),
            FILE_html  (block_ptr),
            field_name (block_ptr, index),
            attr == FATTR_SECURE? "": value);
      }
    else
    if (attr == FATTR_OPTION
    ||  attr == FATTR_LABEL
    ||  attr == FATTR_HILITE)
      {
        fname = strrchr (value, '/');
        if (fname == NULL)
            fname = strrchr (value, '\\');
        if (fname == NULL)
            fname = value;
        else
            fname++;
        tmp_name = field_value (field_nbr - 1, index);
        put_fmt (stream,
            "<a href=\"/%s\" %s>%s</a>", tmp_name, status_text, fname);
      }
    else
    if (!tags-> blank)
        put_fmt (stream, tags-> output, *value? value: "&nbsp;");
}


/*  --------------------------------------------------------------------------
 *  within_input -- internal
 *
 *  Returns TRUE if the specified field is within the current form's input
 *  range.  Fields with the attribute FATTR_HIDDEN are always treated as
 *  being within the input range.
 */

static Bool
within_input (int field_nbr, int index)
{
    if (*field_attr (field_nbr, index) == FATTR_HIDDEN
    ||   within_range (&cur_form-> input_range, field_nbr))
        return (TRUE);
    else
        return (FALSE);
}


/*  --------------------------------------------------------------------------
 *  field_name -- internal
 *
 *  Returns a static pointer to the field name for the specified block.  If
 *  the index is > 0, appends the index suffix (_nnn) to the name.  Returns
 *  NULL if the block type is not valid or does not refer to a field.
 */

static char *
field_name (byte *block_ptr, int index)
{
    static
        char formatted_name [LINE_MAX + 8];

    switch (BLOCK_type (block_ptr))
      {
        case BLOCK_TEXTUAL:
            strncpy (formatted_name, TEXTUAL_name (block_ptr), LINE_MAX);
            break;
        case BLOCK_FILE:
            strncpy (formatted_name, FILE_name    (block_ptr), LINE_MAX);
            break;
        case BLOCK_NUMERIC:
            strncpy (formatted_name, NUMERIC_name (block_ptr), LINE_MAX);
            break;
        case BLOCK_DATE:
            strncpy (formatted_name, DATE_name    (block_ptr), LINE_MAX);
            break;
        case BLOCK_TIME:
            strncpy (formatted_name, TIME_name    (block_ptr), LINE_MAX);
            break;
        case BLOCK_TEXTBOX:
            strncpy (formatted_name, TEXTBOX_name (block_ptr), LINE_MAX);
            break;
        case BLOCK_BOOLEAN:
            strncpy (formatted_name, BOOLEAN_name (block_ptr), LINE_MAX);
            break;
        case BLOCK_SELECT:
            strncpy (formatted_name, SELECT_name  (block_ptr), LINE_MAX);
            break;
        case BLOCK_RADIO:
            strncpy (formatted_name, RADIO_name   (block_ptr), LINE_MAX);
            break;
        case BLOCK_IMAGE:
            strncpy (formatted_name, IMAGE_name   (block_ptr), LINE_MAX);
            break;
        default:
            return (NULL);              /*  Undefined block                  */
      }
    if (index)
        sprintf (formatted_name + strlen (formatted_name), "_%d", index);
    return (formatted_name);
}


/*  --------------------------------------------------------------------------
 *  put_option -- internal
 *
 *  Outputs an option field as follows: the field is output as a submit
 *  action, and given an encoded name that indicates the original field and
 *  index: "~Cfield.index".  Eg. field 2, index 3 is encoded as "~C2.3".
 *  The form_get() function searches for such fields in the returned
 *  form data and if found, sets the form event to the form click event,
 *  and click_field and click_index appropriately.
 */

static void
put_option (VDESCR *stream, char *value, int field_nbr, int index)
{
    if (strnull (value))
        value = "&lt;Empty&gt;";

    /*  JavaScript action is 'C%d'                                       */
    put_fmt (stream,
             "<A HREF=\"javascript:subform('~C%d.%d')\" %s>%s</A>\n",
             field_nbr, index, status_text, value);
}


/*  --------------------------------------------------------------------------
 *  field_attr -- internal
 *
 *  Returns pointer to attribute for specified field in form. The field
 *  index is used to access a single (index=0) or repeated (index=0..n-1)
 *  field.
 */

static byte *
field_attr (int field_nbr, int index)
{
    ASSERT (field_nbr < cur_form-> defn-> field_count);
    return (cur_form-> data +
            cur_form-> defn-> fields [field_nbr].data + index);
}


/*  --------------------------------------------------------------------------
 *  field_value -- internal
 *
 *  Returns pointer to value for specified field in form.  The field
 *  index is used to access a single (index=0) or repeated (index=0..n-1)
 *  field.
 */

static char *
field_value (int field_nbr, int index)
{
    ASSERT (field_nbr < cur_form-> defn-> field_count);
    ASSERT (index < BLOCK_times (FIELD_block (field_nbr)));

    return (FIELD_data (field_nbr)
            /*  Count attribute bytes                                        */
            + BLOCK_times (FIELD_block (field_nbr))
            /*  Count field values before specified one                      */
            + (FIELD_max (field_nbr) + 1) * index);
}


/*  --------------------------------------------------------------------------
 *  empty_value -- internal
 *
 *  Returns TRUE if value is considered 'empty', i.e. is "" or all '0'.
 */

static Bool
empty_value (char *value)
{
    while (*value == '0')
        value++;
    return (*value == '\0');            /*  Empty if we now have a null      */
}


/*  --------------------------------------------------------------------------
 *  put_fmt -- internal
 *
 *  Appends a printf format to the output stream; if there is not enough
 *  space in the stream, does nothing.  Updates the stream size.
 */

static void
put_fmt (VDESCR *stream, char *format, ...)
{
    static char
        formatted [LINE_MAX];           /*  Formatted string                 */
    va_list
        argptr;                         /*  Argument list pointer            */

    va_start (argptr, format);          /*  Start variable args processing   */
#if (defined (DOES_SNPRINTF))
    vsnprintf (formatted, LINE_MAX, format, argptr);
#else
    vsprintf  (formatted, format, argptr);
#endif
    va_end (argptr);                    /*  End variable args processing     */

    put_mem (stream, formatted, strlen (formatted));
}


/*  --------------------------------------------------------------------------
 *  put_numeric -- internal
 */

static void
put_numeric (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    ATTR_TAGS
        *tags;
    char
        *value;                         /*  Output of conversion             */
    byte
        attr;                           /*  Field attribute                  */
    int
        format_flags,                   /*  conv_number_string() flags       */
        sign_format,                    /*  How is sign shown?               */
        decs_format,                    /*  How are decimals shown?          */
        output_width;                   /*  Output width for formatting      */

    /*  Get conv_number_string() arguments from block information            */
    get_cvnopts (
        block_ptr,
        &format_flags,
        &sign_format,
        &decs_format,
        &output_width);

    value = conv_number_str (
        field_value (field_nbr, index),
        format_flags,
        cur_form-> dec_point,
        NUMERIC_decs (block_ptr),
        decs_format,
        output_width,
        sign_format);

    /*  If there was an error, we'll show the error message itself           */
    if (value == NULL)
        value = conv_reason_text [conv_reason];

    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<input class=%s type=%s name=\"%s\" size=%d maxlength=%d %s "\
            " onFocus=\"this.form.%s.select();\" value=\"%s\">\n",
            tags-> error? "error": "input",
            tags-> input,
            field_name   (block_ptr, index),
            NUMERIC_size (block_ptr),
            NUMERIC_max  (block_ptr),
            NUMERIC_html (block_ptr),
            field_name   (block_ptr, index),
            attr == FATTR_SECURE? "": value);
      }
    else
    if (attr == FATTR_OPTION)
        put_option (stream, value, field_nbr, index);
    else
    if (!tags-> blank)
        put_fmt (stream, tags-> output, *value? value: "&nbsp;");
}


/*  --------------------------------------------------------------------------
 *  get_cvnopts -- internal
 *
 *  From the definition of a numeric field block, prepares the necessary
 *  arguments for a call to the SFL functions conv_number_str() and
 *  conv_str_number().
 */

static void
get_cvnopts (byte *block_ptr, int *flags, int *sign, int *decs, int *width)
{
    *flags = 0;

    /*  Convert number sign option to convert_number_string() options        */
    switch (NUMERIC_sign (block_ptr))
      {
        case FSIGN_NONE:
            *sign = 0;
            break;
        case FSIGN_POST:
            *flags += FLAG_N_SIGNED;
            *sign   = SIGN_NEG_TRAIL;
            break;
        case FSIGN_PRE:
            *flags += FLAG_N_SIGNED;
            *sign   = SIGN_NEG_LEAD;
            break;
        case FSIGN_POSTPLUS:
            *flags += FLAG_N_SIGNED;
            *sign   = SIGN_ALL_TRAIL;
            break;
        case FSIGN_PREPLUS:
            *flags += FLAG_N_SIGNED;
            *sign   = SIGN_ALL_LEAD;
            break;
        case FSIGN_FINANCIAL:
            *flags += FLAG_N_SIGNED;
            *sign   = SIGN_FINANCIAL;
            break;
      }
    /*  Convert number decs option to convert_number_string() options        */
    switch (NUMERIC_decfmt (block_ptr))
      {
        case FDECFMT_NONE:
            *decs = 0;
            break;
        case FDECFMT_ALL:
            *flags += FLAG_N_DECIMALS;
            *decs   = DECS_SHOW_ALL;
            break;
        case FDECFMT_DROP:
            *flags += FLAG_N_DECIMALS;
            *decs   = DECS_DROP_ZEROS;
            break;
      }
    /*  Convert number fill option to convert_number_string() options        */
    switch (NUMERIC_fill (block_ptr))
      {
        case FFILL_NONE:                /*  Left-justify                     */
            *width = 0;
            break;
        case FFILL_SPACE:               /*  Right-justify                    */
            *width = NUMERIC_size (block_ptr);
            break;
        case FFILL_ZERO:
            *width = NUMERIC_size (block_ptr);
            *flags += FLAG_N_ZERO_FILL;
            break;
      }
    if (NUMERIC_blank (block_ptr))
        *flags += FLAG_N_ZERO_BLANK;
    if (NUMERIC_comma (block_ptr))
        *flags += FLAG_N_THOUSANDS;
}


/*  --------------------------------------------------------------------------
 *  put_date -- internal
 */

static void
put_date (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    char
        *picture;                       /*  Date field picture string        */
    int
        flags,                          /*  conv_date_str() flags            */
        format;                         /*  conv_date_str() format           */
    long
        date_value;                     /*  Date as number YYYYMMDD          */
    char
        *value;                         /*  Formatted date value             */
    ATTR_TAGS
        *tags;
    byte
        attr;                           /*  Field attribute                  */

    /*  Format date as string, using picture or formatting options           */
    date_value = atol (field_value (field_nbr, index));
    picture    = DATE_picture (block_ptr);
    if (strused (picture))
        value = conv_date_pict (date_value, picture);
    else
      {
        /*  Analyse show and format options                                  */
        if (DATE_show (block_ptr) == FSHOW_YMD)
            if (DATE_format (block_ptr) == FFORMAT_COMPACT)
                format = DATE_YMD_COMPACT;
            else
            if (DATE_format (block_ptr) == FFORMAT_SLASH)
                format = DATE_YMD_DELIM;
            else
            if (DATE_format (block_ptr) == FFORMAT_SPACE)
                format = DATE_YMD_SPACE;
            else
            if (DATE_format (block_ptr) == FFORMAT_COMMA)
                format = DATE_YMD_COMMA;
            else
                format = DATE_YMD_COMPACT;
        else
        if (DATE_show (block_ptr) == FSHOW_YM)
            if (DATE_format (block_ptr) == FFORMAT_COMPACT)
                format = DATE_YM_COMPACT;
            else
            if (DATE_format (block_ptr) == FFORMAT_SLASH)
                format = DATE_YM_DELIM;
            else
            if (DATE_format (block_ptr) == FFORMAT_SPACE)
                format = DATE_YM_SPACE;
            else
                format = DATE_YM_COMPACT;
        else
        if (DATE_show (block_ptr) == FSHOW_MD)
            if (DATE_format (block_ptr) == FFORMAT_COMPACT)
                format = DATE_MD_COMPACT;
            else
            if (DATE_format (block_ptr) == FFORMAT_SLASH)
                format = DATE_MD_DELIM;
            else
            if (DATE_format (block_ptr) == FFORMAT_SPACE)
                format = DATE_MD_SPACE;
            else
                format = DATE_MD_COMPACT;
        else
            format = DATE_YMD_COMPACT;

        /*  Analyse year/month/day display options                           */
        flags = 0;
        if (DATE_year(block_ptr) == FYEAR_FULL)
            flags += FLAG_D_CENTURY;

        if (DATE_month (block_ptr) == FMONTH_COUNTER)
            flags += FLAG_D_MM_AS_M;
        else
        if (DATE_month (block_ptr) == FMONTH_ALPHA)
            flags += FLAG_D_MONTH_ABC;
        else
        if (DATE_month (block_ptr) == FMONTH_UPPER)
            flags += FLAG_D_UPPER;

        if (DATE_day (block_ptr) == FDAY_COUNTER)
            flags += FLAG_D_DD_AS_D;

        /*  Now convert the date                                             */
        value = conv_date_str (date_value, flags, format,
                               cur_form-> date_order,
                               cur_form-> date_sep,
                               DATE_size (block_ptr));
      }
    /*  If there was an error, we'll show the error message itself           */
    if (value == NULL)
        value = conv_reason_text [conv_reason];

    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<input class=%s type=%s name=\"%s\" size=%d maxlength=%d %s "\
            " onFocus=\"this.form.%s.select();\" value=\"%s\">\n",
            tags-> error? "error": "input",
            tags-> input,
            field_name (block_ptr, index),
            DATE_size  (block_ptr),
            DATE_size  (block_ptr),
            DATE_html  (block_ptr),
            field_name (block_ptr, index),
            attr == FATTR_SECURE? "": value);
      }
    else
    if (attr == FATTR_OPTION)
        put_option (stream, value, field_nbr, index);
    else
    if (!tags-> blank)
        put_fmt (stream, tags-> output, *value? value: "&nbsp;");
}


/*  --------------------------------------------------------------------------
 *  put_time -- internal
 */

static void
put_time (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    long
        time_value;                     /*  Time as number HHMMSSCC          */
    char
        *value;                         /*  Formatted time value             */
    ATTR_TAGS
        *tags;
    byte
        attr;                           /*  Field attribute                  */

    /*  Format time as string, using picture or formatting options           */
    time_value = atol (field_value (field_nbr, index));
    value      = conv_time_pict (time_value, TIME_picture (block_ptr));
    /*  If there was an error, we'll show the error message itself           */
    if (value == NULL)
        value = conv_reason_text [conv_reason];

    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<input class=%s type=%s name=\"%s\" size=%d maxlength=%d %s " \
            " onFocus=\"this.form.%s.select();\" value=\"%s\">\n",
            tags-> error? "error": "input",
            tags-> input,
            field_name (block_ptr, index),
            TIME_size  (block_ptr),
            TIME_size  (block_ptr),
            TIME_html  (block_ptr),
            field_name (block_ptr, index),
            attr == FATTR_SECURE? "": value);
      }
    else
    if (attr == FATTR_OPTION)
        put_option (stream, value, field_nbr, index);
    else
    if (!tags-> blank)
        put_fmt (stream, tags-> output, *value? value: "&nbsp;");
}


/*  --------------------------------------------------------------------------
 *  put_textbox -- internal
 */

static void
put_textbox (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    ATTR_TAGS
        *tags;
    char
        *attrs,                         /*  Attribute for output             */
        *value;                         /*  Textbox field value              */
    byte
        attr;                           /*  Field attribute                  */

    attr  = *field_attr (field_nbr, index);
    tags  = &attr_tags [attr];
    value = (attr == FATTR_SECURE? "": field_value (field_nbr, index));
    if (TEXTBOX_flags (block_ptr) & FLAG_UPPERCASE)
        strupc (value);                 /*  Change directly in the form      */

    if (tags-> blank)
        ;                               /*  Don't show if hidden or blank    */
    else
    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<TEXTAREA CLASS=%s NAME=\"%s\" ROWS=%d COLS=%d MAXLENGTH=%d %s WRAP=\"%s\">",
            tags-> error? "error": "input",
            field_name (block_ptr, index),
            TEXTBOX_rows (block_ptr),
            TEXTBOX_cols (block_ptr),
            TEXTBOX_max  (block_ptr),
            TEXTBOX_html (block_ptr),
            "VIRTUAL");

        /*  Translate metacharacters                                         */
        while (*value)
          {
            if (*value == '<')
                put_str (stream, "&lt;");
            else
            if (*value == '>')
                put_str (stream, "&gt;");
            else
            if (*value == '"')
                put_str (stream, "&quot;");
            else
            if (*value == '&')
                put_str (stream, "&amp;");
            else
                put_mem (stream, value, 1);
            value++;
          }
        put_str (stream, "</TEXTAREA>\n");
      }
    else
    if (attr == FATTR_OPTION)
        put_option (stream, value, field_nbr, index);
    else
      {
        /*  We output the output tag up to %s, then the value, and then the
         *  remainder of the output tag.  Any newlines in the value are
         *  translated into <BR> tags.
         */
        attrs = tags-> output;
        while (*attrs)
          {
            if (*attrs == '%')
              {
                attrs += 2;             /*  Assume we just hit '%s'          */
                break;
              }
            put_mem (stream, attrs, 1);
            attrs++;
          }
        /*  Output value, translating \n to <BR>                             */
        if (*value)
            while (*value)
              {
                if (*value == '\n')
                    put_str (stream, "<BR>");
                else
                    put_mem (stream, value, 1);
                value++;
              }
        else                            /*  Empty value - output hard space  */
            put_str (stream, "&nbsp;");

        /*  Output remainder of tag, if any                                  */
        while (*attrs)
            put_mem (stream, attrs++, 1);
      }
}


/*  --------------------------------------------------------------------------
 *  put_boolean -- internal
 */

static void
put_boolean (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    ATTR_TAGS
        *tags;
    char
        *value;
    byte
        attr;                           /*  Field attribute                  */

    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> blank)
        ;                               /*  Don't show if hidden or blank    */
    else
    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream,
            "<input class=%s type=checkbox %s %sname=\"%s\">\n",
            tags-> error? "error": "checkbox",
            BOOLEAN_html (block_ptr),
            *field_value (field_nbr, index) == '1'? "checked ": "",
            field_name   (block_ptr, index));
      }
    else
      {
        value = *field_value (field_nbr, index) == '1'?
                BOOLEAN_true (block_ptr): BOOLEAN_false (block_ptr);
        if (attr == FATTR_OPTION)
            put_option (stream, value, field_nbr, index);
        else
            put_fmt (stream, tags-> output, *value? value: "&nbsp;");
      }
}


/*  --------------------------------------------------------------------------
 *  put_select -- internal
 */

static void
put_select (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    ATTR_TAGS
        *tags;
    int
        option,                         /*  SELECT option number             */
        options,                        /*  Number of select options         */
        select_value;                   /*  Select field value               */
    char
        *value,                         /*  Select value string              */
        *option_value,                  /*  Formatted option value           */
        *option_text;                   /*  SELECT option text               */
    byte
        attr;                           /*  Field attribute                  */

    select_value = atoi (field_value (field_nbr, index));
    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> blank)
        ;                               /*  Don't show if hidden or blank    */
    else
    if (tags-> input && within_input (field_nbr, index))
      {
        set_focus (block_ptr, field_nbr, index, attr);
        put_fmt (stream, "<SELECT CLASS=%s NAME=\"%s\" %s SIZE=%d",
                 tags-> error? "error": "input",
                 field_name (block_ptr, index),
                 SELECT_html (block_ptr),
                 SELECT_size (block_ptr));

        /*  Check if onchange needed for this select field */
        if (SELECT_onchange (block_ptr) == 1)
            put_fmt (stream, " ONCHANGE=\"%s\">\n", SELECT_script (block_ptr));
        else
            put_fmt (stream, ">\n");

        /*  Dynamic select lists get their data from the list_values table   */
        if (SELECT_options (block_ptr) == 0)
          {
            options = fxlist_size (field_nbr, index);
            for (option = 1; option <= options; option++) {
                option_value = strconvchs (list_lookup (field_nbr, index, option, 'v'),
                                           ' ', "&nbsp;");
                put_fmt (stream, "<OPTION VALUE=\"%d\"%s>%s\n",
                                 option,
                                 option == select_value? " SELECTED": "",
                                 option_value);
                mem_strfree (&option_value);
            }
        }
        else    /*  Fixed select lists get their data from the form defn     */
          {
            /*  Output no-selection text as first option                     */
            put_fmt (stream, "<OPTION VALUE=\"0\" %s>%s\n",
                              select_value == 0? "SELECTED": "",
                              SELECT_nosel (block_ptr));

            option_text = SELECT_first (block_ptr);
            for (option = 1; option <= SELECT_options (block_ptr); option++)
              {
                put_fmt (stream, "<OPTION VALUE=\"%d\"%s>%s\n", option,
                                 option == select_value? " SELECTED": "",
                                 option_text);
                option_text += strlen (option_text) + 1;
              }
          }
        put_str (stream, "</SELECT>\n");
      }
    else
    if (select_value == 0)
        put_fmt (stream, tags-> output, SELECT_nosel (block_ptr));
    else
      {
        /*  Output currently-selected option                                 */
        if (SELECT_options (block_ptr) == 0)
            value = list_lookup (field_nbr, index, select_value, 'v');
        else
          {
            option_text = SELECT_nosel (block_ptr);
            for (option = 0; option < select_value; option++)
                option_text += strlen (option_text) + 1;
            value = option_text;
          }
        if (attr == FATTR_OPTION)
            put_option (stream, value, field_nbr, index);
        else
            put_fmt (stream, tags-> output, *value? value: "&nbsp;");
      }
}


/*  --------------------------------------------------------------------------
 *  put_radio -- internal
 */

static void
put_radio (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    ATTR_TAGS
        *tags;
    int
        option,                         /*  RADIO option number              */
        options,                        /*  Number of radio options          */
        radio_value;                    /*  Radio field value                */
    char
        *value,                         /*  Radio value string               */
        *option_text;                   /*  RADIO option text                */
    byte
        attr;                           /*  Field attribute                  */

    radio_value = atoi (field_value (field_nbr, index));
    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> blank)
        ;                               /*  Don't show if hidden or blank    */
    else
    if (tags-> input && within_input (field_nbr, index)) {
        if (RADIO_options (block_ptr) > 0) {
            /*  Static radio options                                         */
            option_text = RADIO_first (block_ptr);
            options = RADIO_options (block_ptr);
        }
        else
            /*  Dynamic radio options                                        */
            options = fxlist_size (field_nbr, index);

        for (option = 1; option <= options; option++) {
            if (RADIO_column (block_ptr) && option > 1)
                put_str (stream, "<br>");
            
            put_fmt (stream, "<input class=%s type=radio value=\"%d\" %s name=\"%s\"%s",
                tags-> error? "error": "radio",
                option,
                RADIO_html (block_ptr),
                field_name (block_ptr, index),
                option == radio_value? " checked": "");

            if (RADIO_onchange (block_ptr) == 1)
                put_fmt (stream, " onchange=\"%s\"", RADIO_script (block_ptr));

            if (RADIO_options (block_ptr) > 0) {
                put_fmt (stream, ">&nbsp;%s&nbsp;\n", option_text);
                option_text += strlen (option_text) + 1;
            }
            else
                put_fmt (stream, ">&nbsp;%s&nbsp;\n", list_lookup (field_nbr, index, option, 'v'));
        }
    }
    /*  Show radio field as output                                           */
    else 
    if (radio_value == 0)
        put_fmt (stream, tags-> output, RADIO_nosel (block_ptr));
    else {
        /*  Output currently-selected option                                 */
        if (RADIO_options (block_ptr) == 0)
            value = list_lookup (field_nbr, index, radio_value, 'v');
        else {
            option_text = RADIO_nosel (block_ptr);
            for (option = 0; option < radio_value; option++)
                option_text += strlen (option_text) + 1;
            value = option_text;
        }
        if (attr == FATTR_OPTION)
            put_option (stream, value, field_nbr, index);
        else
            put_fmt (stream, tags-> output, *value? value: "&nbsp;");
    }
}


/*  --------------------------------------------------------------------------
 *  put_action -- internal
 */

static void
put_action (VDESCR *stream, byte *block_ptr, int index)
{
    int
        event;
    char
        *name,
        *label,
        *rollover,
        *confirm,
        *alt_text;

    /*  Actions are either enabled, disabled, or hidden                      */
    event    = ACTION_event    (block_ptr);
    name     = ACTION_name     (block_ptr);
    label    = ACTION_label    (block_ptr);
    rollover = ACTION_rollover (block_ptr);
    confirm  = ACTION_confirm  (block_ptr);

    if (*ACTION_attr (block_ptr, index) == FACTION_ENABLED)
      {
        if (ACTION_type (block_ptr) == FTYPE_BUTTON)
            put_fmt (stream, "<input class=button type=submit %s value=\"%s\" name=\"%s\">\n",
                     ACTION_html (block_ptr),
                     label, name);
        else
        if (ACTION_type (block_ptr) == FTYPE_PLAIN)
          {
            /*  JavaScript action is 'Annn.yyy'                          */
            put_fmt (stream,
                     "<a href=\"javascript:subconf('~A%d.%d','%s')\" %s>%s</a>\n",
                     event, index, confirm, status_text, label);
          }
        else
        if (ACTION_type (block_ptr) == FTYPE_IMAGE)
          {
            if (strlen (ACTION_alt (block_ptr)) == 0)
                 alt_text = mem_strdup (ACTION_name (block_ptr));
            else
                 alt_text = mem_strdup (ACTION_alt (block_ptr));

            /*  Make sure 'Alt' text starts with a capital letter        */
            *alt_text = toupper (*alt_text);

            /*  JavaScript action is 'Annn.yyy'                          */
            put_fmt (stream, "<a href=\"javascript:subconf('~A%d.%d','%s')\"",
                               event, index, confirm);
            put_fmt (stream, " TITLE=\"%s\"", alt_text);

            /*  Generate image rollover if required                      */
            if (*rollover)
              {                     /*  We call images ixxxxx            */
                if (index)
                  {
                    put_fmt (stream, " onMouseOver=\"show('i%s%d','%s');window.status='Click';return true;\"",
                             name, index, rollover) ;
                    put_fmt (stream, " onMouseOut=\"show('i%s%d','%s');window.status='';return true;\"",
                             name, index, label) ;
                  }
                else
                  {
                    put_fmt (stream, " onMouseOver=\"show('i%s','%s');window.status='Click';return true;\"",
                             name, rollover);
                    put_fmt (stream, " onMouseOut=\"show('i%s','%s');window.status='';return true;\"",
                             name, label);
                  }
              }
            put_fmt        (stream, ">");
            put_action_img (stream, block_ptr, index);
            put_fmt        (stream, "</a>");
            mem_free       (alt_text);
          }
      }
    else
    if (*ACTION_attr (block_ptr, index) == FACTION_DISABLED)
      {
        if (ACTION_type (block_ptr) == FTYPE_BUTTON)
            put_fmt (stream, "&nbsp;[ %s ]&nbsp;\n", label);
        else
        if (ACTION_type (block_ptr) == FTYPE_PLAIN)
            put_fmt (stream, "%s\n", label);
        else
        if (ACTION_type (block_ptr) == FTYPE_IMAGE)
            put_action_img (stream, block_ptr, index);
      }
}


/*  --------------------------------------------------------------------------
 *  put_image -- internal
 */

static void
put_image (VDESCR *stream, byte *block_ptr, int field_nbr, int index)
{
    ATTR_TAGS
        *tags;
    byte
        attr;                           /*  Field attribute                  */

    attr = *field_attr (field_nbr, index);
    tags = &attr_tags [attr];

    if (tags-> blank)
        ;
    else
    if (tags-> input && within_input (field_nbr, index))
      {
        put_fmt (stream, "<img border=0 src=\"%s\" align=left", IMAGE_label (block_ptr));
        if (index)
            put_fmt (stream, " name=\"%s%d\">", IMAGE_name (block_ptr), index) ;
        else
            put_fmt (stream, " name=\"%s\">", IMAGE_name (block_ptr));
      }
    else
        if (attr == FATTR_OPTION)
          {
            /*  JavaScript action is 'C%d'                                       */
            put_fmt (stream, "<a href=\"javascript:subform('~C%d.%d')\" %s>",
                     field_nbr, index, status_text);
            put_fmt (stream, "<img border=0 src=\"%s\" align=left", IMAGE_label (block_ptr));
            if (index)
                put_fmt (stream, " name=\"%s%d\">", IMAGE_name (block_ptr), index);
            else
                put_fmt (stream, " name=\"%s\">", IMAGE_name (block_ptr));
            put_fmt (stream, "</A>\n");
          }
}


/*  --------------------------------------------------------------------------
 *  put_action_img -- internal
 *
 *  Generates a full <IMG ...> tag
 */

static void
put_action_img (VDESCR *stream, byte *block_ptr, int index)
{
    char
        *alt_text;

    if (strlen(ACTION_alt (block_ptr)) == 0)
         alt_text = mem_strdup (ACTION_name (block_ptr));
    else
         alt_text = mem_strdup (ACTION_alt (block_ptr));

    /*  Make sure 'Alt' text starts with a capital letter                    */
    *alt_text = toupper (*alt_text);

    put_fmt (stream, "<IMG BORDER=0 SRC=\"%s\" ALT=\"%s\" ALIGN=MIDDLE",
             ACTION_label (block_ptr), alt_text);
    if (ACTION_height (block_ptr))
        put_fmt (stream, " HEIGHT=%d WIDTH=%d",
             ACTION_height (block_ptr), ACTION_width (block_ptr));

    if (index)
        put_fmt (stream, " NAME=\"i%s%d\">", ACTION_name (block_ptr), index) ;
    else
        put_fmt (stream, " NAME=\"i%s\">", ACTION_name (block_ptr));

    mem_free (alt_text);
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_get

    Synopsis: Accepts an HTTP query string in escaped format and uses it to
    update the form field values.  Returns the number of fields updated -
    if a field has not changed, it is not updated.  The update algorithm
    depends on the field type:
    <TABLE>
    Textual     If field in query, use new value, else leave unchanged.
    Numeric     Must be valid number, then process as for textual field.
    Multiline   Process as for textual field.
    Date        Must be valid date, then process as for textual field.
    Time        Must be valid time, then process as for textual field.
    Boolean     If field in query, set to "1", else to "0".
    Select      If field in query, use new value, else default value.
    Radio       If field in query, use new value, else default value.
    </TABLE>
    Returns -1 if there was an invalid numeric, date, or time field on the
    form, and sets form_strerror to the error message.
    ---------------------------------------------------------------------[>]-*/

int
form_get (
    FORM_ITEM *form,
    const char *query)
{
    SYMTAB
        *symtab;                        /*  Parsed query variables           */
    int
        nbr_changes = 0;                /*  How many changed fields?         */

    ASSERT (form);
    ASSERT (query);
    if ((symtab = http_query2symb (query)) == NULL)
        return 0;                       /*  Insufficient memory to work      */

    form-> status      = FSTATUS_OK;    /*  No errors                        */
    form-> image_x     = 0;             /*  No image clicked                 */
    form-> image_y     = 0;             /*  No image clicked                 */
    form-> click_field = 0;             /*  No option field clicked          */
    form-> click_index = 0;             /*  No option field clicked          */
    strclr (form-> livelink);           /*  No plain-text field clicked      */

    /*  When the Enter button is pressed on a form, we generate a click
     *  event with a click_field and click_index of 0.  The browser does
     *  not return an action value, so we set this event by default.
     */
    form-> event = form-> click_event;

    /*  Load data from HTTP query into form structures                       */
    mem_check (form-> data);
    form_use  (form);

    /*  Form data can come in various ways: normally we expect a number of
     *  posted fields in the query symbol table.  For clicks on links that
     *  do not post data, we only have the URL argument (&~field=value).
     *  We get the click action in the field called jsaction.
     */
    /*  If data starts with '&' or '~', it's only a click field              */
    if (*query == '&' || *query == '~')
        sym_exec_all (symtab, form_get_click);
    else
      {
        form_exec (form, form_get_block, symtab, &nbr_changes);
        check_jsaction (symtab);
      }
    /*  Clean-up                                                             */
    sym_delete_table (symtab);
    return (form-> status == FSTATUS_OK? nbr_changes: -1);
}


/*  --------------------------------------------------------------------------
 *  form_get_block -- internal
 *
 *  Gets input data from HTML form.  Called indirectly through form_exec().
 */

static Bool
form_get_block (
    FORM_ITEM *form,
    byte      *block_ptr,
    int        field_nbr,
    va_list    argptr)
{
    static int
        skip_count = 0,                 /*  Skip N blocks forward            */
        within_repeat,                  /*  If > 0, in repeated block        */
        repeat_size = 0;                /*  Max. index in repeated block     */
    SYMTAB
        *symtab;                        /*  Parsed query variables           */
    SYMBOL
        *symbol;                        /*  Pointer to field value           */
    byte
        block_type;                     /*  Type of current block            */
    int
        feedback,                       /*  Return from update_field()       */
        *changes,                       /*  Number of changed fields         */
        max_index,                      /*  For repeated fields              */
        index;                          /*  For repeated fields              */

    /*  Get variable arguments off argument list                             */
    symtab  = va_arg (argptr, SYMTAB *);
    changes = va_arg (argptr, int *);
    if (field_nbr == -1)                /*  Initialise static variables      */
        within_repeat = 0;              /*    first time through             */

    /*  Process the block                                                    */
    mem_check (form-> data);            /*  Nothing corrupted?               */
    block_type = BLOCK_type (block_ptr);

    if (skip_count > 0)                 /*  First off, we skip if possible   */
        skip_count--;
    else
    if (block_type == BLOCK_IF) {
        if (IF_value (block_ptr) == 0) {
            if (strnull (field_value (IF_field (block_ptr), 0)))
               skip_count = IF_scope (block_ptr);
        }
        else
        if (atoi (field_value (IF_field (block_ptr), 0)) != IF_value (block_ptr))
            skip_count = IF_scope (block_ptr);
    }
    else
    if (block_type == BLOCK_UNLESS) {
        if (UNLESS_value (block_ptr) == 0) {
            if (strused (field_value (UNLESS_field (block_ptr), 0)))
               skip_count = UNLESS_scope (block_ptr);
        }
        else
        if (atoi (field_value (UNLESS_field (block_ptr), 0)) == UNLESS_value (block_ptr))
            skip_count = UNLESS_scope (block_ptr);
    }
    else
    if (BLOCK_IS_FIELD (block_type))
      {
        /*  Find and update field(s) if present in symbol table              */
        max_index = within_repeat? repeat_size: 1;
        for (index = 0; index < max_index; index++)
          {
            /*  The browser will return the Boolean field if checked, and
             *  will not return it if unchecked. So, we clear the field now:
             *  if it is/was checked, it will be accepted on input.
             */
            if (block_type == BLOCK_BOOLEAN)
                strcpy (field_value (field_nbr, index), "0");

            reset_attr (field_nbr, index);
            symbol = sym_lookup_symbol (symtab, field_name (block_ptr, index));
            if (symbol)
              {
                feedback = update_field (block_ptr, field_nbr, index,
                                         symbol-> value);
                if (feedback == -1)
                    form-> status = FSTATUS_FIELD;
                else
                    *changes += feedback;
              }
          }
      }
    else
    if (block_type == BLOCK_ACTION)
        get_action (symtab, block_ptr);
    else
    if (block_type == BLOCK_REPEAT)
      {
        within_repeat = REPEAT_scope (block_ptr) + 1;
        repeat_size   = atoi (field_value (REPEAT_field (block_ptr), 0));
      }

    /*  Count-down this indicator; when zero we are no longer in a repeat    */
    if (within_repeat)
        within_repeat--;

    return (TRUE);
}


/*  --------------------------------------------------------------------------
 *  update_field -- internal
 *
 *  Updates the field as specified.  The specific validation and update
 *  depends on the block type.  Returns 1 if the field value was changed,
 *  0 if not, -1 if there was a field error.
 */

static int
update_field (byte *block_ptr, int field_nbr, int index, char *value)
{
    switch (BLOCK_type (block_ptr))
      {
        case BLOCK_TEXTUAL:
            return (get_textual (block_ptr, field_nbr, index, value));
        case BLOCK_TEXTBOX:
            return (get_textbox (block_ptr, field_nbr, index, value));
        case BLOCK_SELECT:
        case BLOCK_RADIO:
        case BLOCK_IMAGE:
        case BLOCK_FILE:
            return (fxputn_text (field_nbr, index, value));
        case BLOCK_NUMERIC:
            return (get_numeric (block_ptr, field_nbr, index, value));
        case BLOCK_DATE:
            return (get_date    (block_ptr, field_nbr, index, value));
        case BLOCK_TIME:
            return (get_time    (block_ptr, field_nbr, index, value));
        case BLOCK_BOOLEAN:
            return (fxputn_text (field_nbr, index, "1"));
      }
    return (0);
}


/*  --------------------------------------------------------------------------
 *  get_textual -- internal
 *
 *  Updates the textual field as specified in the returned form data.
 *  Returns 1 if the field was changed, 0 if the field remained the same.
 */

static int
get_textual (byte *block_ptr, int field_nbr, int index, char *value)
{
    if (TEXTUAL_flags (block_ptr) & FLAG_UPPERCASE)
        strupc (value);
    return (fxputn_text (field_nbr, index, value));
}


/*  --------------------------------------------------------------------------
 *  get_textbox -- internal
 *
 *  Updates the textbox field as specified in the returned form data.
 *  Returns 1 if the field was changed, 0 if the field remained the same.
 */

static int
get_textbox (byte *block_ptr, int field_nbr, int index, char *value)
{
    if (TEXTBOX_flags (block_ptr) & FLAG_UPPERCASE)
        strupc (value);
    return (fxputn_text (field_nbr, index, value));
}


/*  --------------------------------------------------------------------------
 *  get_numeric -- internal
 *
 *  Updates the numeric field as specified in the returned form data.
 *  Returns 1 if the field was changed, 0 if the field remained the same,
 *  and -1 if there was an error (invalid number).
 */

static int
get_numeric (byte *block_ptr, int field_nbr, int index, char *value)
{
    static char
        numeric_error [LINE_MAX];       /*  Formatting error message         */
    int
        format_flags,                   /*  conv_number_string() flags       */
        sign_format,                    /*  How is sign shown?               */
        decs_format,                    /*  How are decimals shown?          */
        input_width;                    /*  Output width for formatting      */
    char
        *numeric_value;                 /*  Formatted number                 */
    byte
        *attr;                          /*  Pointer to field attribute       */

    /*  Get conv_number_string() arguments from block information            */
    get_cvnopts (
        block_ptr,
        &format_flags,
        &sign_format,
        &decs_format,
        &input_width);

    input_width = NUMERIC_size (block_ptr);
    numeric_value = conv_str_number (
        value,
        format_flags,
        cur_form-> dec_point,
        NUMERIC_decs (block_ptr),
        decs_format,
        input_width
      );
    if (numeric_value == NULL)
      {
        xstrcpy (numeric_error, "Invalid number (", value, "): ",
                 conv_reason_text [conv_reason], NULL);
        form_strerror = numeric_error;
        attr = field_attr (field_nbr, index);
        if (*attr == FATTR_INPUT)
            *attr  = FATTR_ERROR;
        return (-1);
      }
    else
        return (fxputn_text (field_nbr, index, numeric_value));
}


/*  --------------------------------------------------------------------------
 *  get_date -- internal
 *
 *  Updates the date field as specified in the returned form data.
 *  Returns 1 if the field was changed, 0 if the field remained the same,
 *  and -1 if there was an error (invalid date).
 */

static int
get_date (byte *block_ptr, int field_nbr, int index, char *value)
{
    static char
        date_error [LINE_MAX];          /*  Formatting error message         */
    int
        format;                         /*  conv_str_date() format           */
    long
        date_value = -1;                /*  Internal date value              */
    byte
        *attr;                          /*  Pointer to field attribute       */

    if (DATE_show (block_ptr) == FSHOW_YMD)
        format = DATE_YMD_DELIM;
    else
    if (DATE_show (block_ptr) == FSHOW_YM)
        format = DATE_YM_DELIM;
    else
        format = DATE_MD_DELIM;

    date_value = conv_str_date (value, 0, format, cur_form-> date_order);
    if (date_value == -1)
      {
        xstrcpy (date_error, "Invalid date (", value, "): ",
                 conv_reason_text [conv_reason], NULL);
        form_strerror = date_error;
        attr = field_attr (field_nbr, index);
        if (*attr == FATTR_INPUT)
            *attr  = FATTR_ERROR;
        return (-1);
      }
    else
        return (fxputn_date (field_nbr, index, date_value));
}


/*  --------------------------------------------------------------------------
 *  get_time -- internal
 *
 *  Updates the time field as specified in the returned form data.
 *  Returns 1 if the field was changed, 0 if the field remained the same,
 *  and -1 if there was an error (invalid time).
 */

static int
get_time (byte *block_ptr, int field_nbr, int index, char *value)
{
    static char
        time_error [LINE_MAX];          /*  Formatting error message         */
    long
        time_value = -1;                /*  Internal time value              */
    byte
        *attr;                          /*  Pointer to field attribute       */

    time_value = conv_str_time (value);
    if (time_value == -1)
      {
        xstrcpy (time_error, "Invalid time (", value, "): ",
                 conv_reason_text [conv_reason], NULL);
        form_strerror = time_error;
        attr = field_attr (field_nbr, index);
        if (*attr == FATTR_INPUT)
            *attr  = FATTR_ERROR;
        return (-1);
      }
    else
        return (fxputn_time (field_nbr, index, time_value));
}


/*  --------------------------------------------------------------------------
 *  reset_attr -- internal
 *
 *  Resets field transient attributes:
 *      FATTR_ERROR  -> FATTR_INPUT
 */

static void
reset_attr (int field_nbr, int index)
{
    byte
        *attr;                          /*  Field attribute                  */

    /*  Reset transient field attributes                                     */
    attr = field_attr (field_nbr, index);
    if (*attr == FATTR_ERROR)
        *attr = FATTR_INPUT;
}


/*  --------------------------------------------------------------------------
 *  get_action -- internal
 *
 *  Sets current form event to action event, if that action was selected.
 *  If the action was an image, also sets the form image_x and image_y
 *  fields.
 */

static void
get_action (SYMTAB *symtab, byte *block_ptr)
{
    SYMBOL
        *symbol;                        /*  Pointer to field value           */
    char
        *image_x_name;

    if (ACTION_type (block_ptr) == FTYPE_IMAGE)
      {
        image_x_name = xstrcpy (NULL, ACTION_name (block_ptr), ".x", NULL);
        symbol = sym_lookup_symbol (symtab, image_x_name);
        if (symbol)
          {
            cur_form-> event = ACTION_event (block_ptr);
            cur_form-> image_x = atoi (symbol-> value);
            strlast (image_x_name) = 'y';
            symbol = sym_lookup_symbol (symtab, image_x_name);
            if (symbol)
                cur_form-> image_y = atoi (symbol-> value);
          }
        mem_free (image_x_name);
      }
    else
      {
        symbol = sym_lookup_symbol (symtab, ACTION_name (block_ptr));
        if (symbol)
            cur_form-> event = ACTION_event (block_ptr);
      }
}


/*  --------------------------------------------------------------------------
 *  form_get_click -- internal
 *
 *  Look for a click field; supports these types of click fields:
 *
 *      ~Cxxx.y - option field number xxx, index y
 *      ~Annn.y - action resulting in event number nnn, index y
 *      ~Lxxx   - live link called xxx
 */

static Bool
form_get_click (SYMBOL *symbol, ...)
{
    char
        *index_value;                   /*  Numeric value of index           */

    if (*symbol-> name == '~')          /*  Click fields start with ~        */
      {
        /*  General handling for an index specifier, which is optional       */
        index_value = strchr (symbol-> name + 2, '.');
        if (index_value)
            cur_form-> click_index = atoi (index_value + 1);

        /*  ~Cxxx.yyy is an option field generated by formio.c               */
        if (symbol-> name [1] == 'C')
          {
            cur_form-> click_field = atoi (symbol-> name + 2);
            cur_form-> event       = cur_form-> click_event;
            return (FALSE);             /*  Finished working                 */
          }
        else
        /*  ~Annn.yyy is a textual action field generated by formio.c        */
        if (symbol-> name [1] == 'A')
          {
            cur_form-> event = atoi (symbol-> name + 2);
            return (FALSE);             /*  Finished working                 */
          }
        else
        /*  ~Lxxx is a live link field generated by fdlgen                   */
        if (symbol-> name [1] == 'L')
          {
            strncpy (cur_form-> livelink, symbol-> name + 2,
                     FORMIO_LIVELINK_MAX);
            cur_form-> livelink [FORMIO_LIVELINK_MAX] = '\0';
            cur_form-> event = cur_form-> click_event;
            return (FALSE);             /*  Finished working                 */
          }
      }
    return (TRUE);
}


/*  --------------------------------------------------------------------------
 *  check_jsaction -- internal
 *
 *  Look for a field called jsaction; value may be one of:
 *
 *      ~Cxxx.y - option field number xxx, index y
 *      ~Annn.y - action resulting in event number nnn, index y
 *      ~Lxxx   - live link called xxx
 */

static void
check_jsaction (SYMTAB *symtab)
{
    SYMBOL
        *symbol;                        /*  Pointer to field value           */
    char
        *index_value;                   /*  Numeric value of index           */

    symbol = sym_lookup_symbol (symtab, "jsaction");
    if (symbol && *symbol-> value == '~')
      {
        /*  General handling for an index specifier, which is optional       */
        index_value = strchr (symbol-> value + 2, '.');
        if (index_value)
            cur_form-> click_index = atoi (index_value + 1);

        /*  ~Cxxx.yyy is an option field generated by formio.c               */
        if (symbol-> value [1] == 'C')
          {
            cur_form-> click_field = atoi (symbol-> value + 2);
            cur_form-> event       = cur_form-> click_event;
          }
        else
        /*  ~Annn.yyy is a textual action field generated by formio.c        */
        if (symbol-> value [1] == 'A')
            cur_form-> event = atoi (symbol-> value + 2);
        else
        /*  ~Lxxx is a live link field generated by fdlgen                   */
        if (symbol-> value [1] == 'L')
          {
            strncpy (cur_form-> livelink, symbol-> value + 2,
                     FORMIO_LIVELINK_MAX);
            cur_form-> livelink [FORMIO_LIVELINK_MAX] = '\0';
            cur_form-> event = cur_form-> click_event;
          }
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_text

    Synopsis: Updates a form field with the specified string value.  Returns
    1 if the field changed, 0 if the field had the same value.  Crops any
    trailing spaces in the string.  Assumes that cur_form has been set.
    Does nothing if the field number is out of range.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_text (int field, int index, const char *new_value)
{
    char
        *value;                         /*  Where old value is sitting       */

    ASSERT (new_value);
    ASSERT (index < BLOCK_times (FIELD_block (field)));

    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);

    /*  If old and new value are the same, just return 0                     */
    value = field_value (field, index);
    if (streq (value, new_value))
        return (0);
    else
      {
        strncpy (value, new_value, FIELD_max (field));
        value [FIELD_max (field)] = '\0';
        strcrop (value);
        return (1);
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_char

    Synopsis: Updates a form field with the specified character value.
    Returns 1 if the field changed, 0 if the field had the same value.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_char (int field, int index, char new_value)
{
    char
        new_text [2] = {0, 0};

    ASSERT (index < BLOCK_times (FIELD_block (field)));
    *new_text = new_value;
    return (fxputn_text (field, index, new_text));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_date

    Synopsis: Updates a form field with the specified date value.  Returns
    1 if the field changed, 0 if the field had the same value, -1 if the
    value was not a valid date.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_date (int field, int index, long new_value)
{
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (fxputn_long (field, index, new_value));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_time

    Synopsis: Updates a form field with the specified time value.  Returns
    1 if the field changed, 0 if the field had the same value, -1 if the
    value was not a valid time.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_time (int field, int index, long new_value)
{
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (fxputn_long (field, index, new_value));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_int

    Synopsis: Updates a form field with a specified integer value.
    Returns 1 if the field changed, 0 if the field had the same value.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_int (int field, int index, int new_value)
{
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (fxputn_long (field, index, (long) new_value));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_long

    Synopsis: Updates a form field with a specified long value.  Returns
    1 if the field changed, 0 if the field had the same value.  Does nothing
    if the field number is out of range.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_long (int field, int index, long new_value)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (fxputn_text (field, index, strprintf ("%0ld", new_value)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_double

    Synopsis: Updates a form field with a specified double value.  Returns
    1 if the field changed, 0 if the field had the same value.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_double (int field, int index, double new_value)
{
    static char
        format [10];

    ASSERT (index < BLOCK_times (FIELD_block (field)));
    sprintf (format, "%%.%df", NUMERIC_decs (FIELD_block (field)));
    return (fxputn_text (field, index, strprintf (format, new_value)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxputn_bool

    Synopsis: Updates a form field with the specified Boolean value.
    Returns 1 if the field changed, 0 if the field had the same value.
    ---------------------------------------------------------------------[>]-*/

int
fxputn_bool (int field, int index, Bool new_value)
{
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (fxputn_text (field, index, new_value? "1": "0"));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_text

    Synopsis: Return the current value of a textual field, or NULL if the
    field number is out of range.
    ---------------------------------------------------------------------[>]-*/

char *
fxgetn_text (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (NULL);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (field_value (field, index));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_char

    Synopsis: Return the current value of a character field.
    ---------------------------------------------------------------------[>]-*/

char
fxgetn_char (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (*field_value (field, index));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_date

    Synopsis: Return the current value of a date field as a long.
    ---------------------------------------------------------------------[>]-*/

long
fxgetn_date (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    ASSERT (BLOCK_type (FIELD_block (field)) == BLOCK_DATE);
    return (atol (field_value (field, index)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_time

    Synopsis: Return the current value of a time field as a long.
    ---------------------------------------------------------------------[>]-*/

long
fxgetn_time (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    ASSERT (BLOCK_type (FIELD_block (field)) == BLOCK_TIME);
    return (atol (field_value (field, index)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_int

    Synopsis: Return the current int value of a numeric field.
    ---------------------------------------------------------------------[>]-*/

int
fxgetn_int (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (atoi (field_value (field, index)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_long

    Synopsis: Return the current value of a field. Returns 0 if empty.
    ---------------------------------------------------------------------[>]-*/

long
fxgetn_long (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (atol (field_value (field, index)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_double

    Synopsis: Return the current value of a field. Returns 0 if empty.
    ---------------------------------------------------------------------[>]-*/

double
fxgetn_double (int field, int index)
{
    if (field < 0 || field >= cur_form-> defn-> field_count)
        return (0);
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (atof (field_value (field, index)));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxgetn_bool

    Synopsis: Return the current value of field TRUE or FALSE.
    ---------------------------------------------------------------------[>]-*/

Bool
fxgetn_bool (int field, int index)
{
    ASSERT (index < BLOCK_times (FIELD_block (field)));
    return (fxgetn_long (field, index)? TRUE: FALSE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxattr_get

    Synopsis: Returns the attribute of the specified field on the current
    form.
    ---------------------------------------------------------------------[>]-*/

byte
fxattr_get (
    int field_nbr,
    int index)
{
    FORM_DEFN
        *defn;

    defn = cur_form-> defn;
    ASSERT (field_nbr >= 0 && field_nbr < defn-> field_count);
    return (*field_attr (field_nbr, index));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxattr_put

    Synopsis: Sets the attribute for the specified field on the current form.
    ---------------------------------------------------------------------[>]-*/

void
fxattr_put (
    int  field_nbr,
    int  index,
    byte attr)
{
    FORM_DEFN
        *defn;

    defn = cur_form-> defn;
    ASSERT (field_nbr >= 0 && field_nbr < defn-> field_count);
    *field_attr (field_nbr, index) = attr;
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxlist_size

    Synopsis: Returns size of specified dynamic select list field on the
    current form.  If the field has not been initialised using fxlist_reset,
    returns 0.
    ---------------------------------------------------------------------[>]-*/

size_t
fxlist_size (int field, int index)
{
    return (atoi (list_lookup (field, index, 0, 'h')));
}


/*  --------------------------------------------------------------------------
 *  list_key -- internal
 *
 *  Returns static string holding lookup index for specified list item.
 *  The 'what' argument can be one of:
 *      'h'     Header of list
 *      'k'     Item key
 *      'v'     Item value
 */

static char *
list_key (int field, int index, int item, char what)
{
    static char
        key [12];

    sprintf (key, "%02x.%02x.%03i.%c",
                  (byte) field, (byte) index, item, what);
    return (key);
}


/*  --------------------------------------------------------------------------
 *  list_lookup -- internal
 *
 *  Returns pointer to specified list item value, or "" if none such is
 *  defined.
 */

static char *
list_lookup (int field, int index, int item, char what)
{
    SYMBOL
        *symbol;

    if (cur_form-> list_values)
      {
        symbol = sym_lookup_symbol (cur_form-> list_values,
                                    list_key (field, index, item, what));
        if (symbol)
            return (symbol-> value);
      }
    return ("");
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxlist_reset

    Synopsis: Initialises specified dynamic list field.  You must call this
    function before you can append values to the list.
    ---------------------------------------------------------------------[>]-*/

void
fxlist_reset (int field, int index)
{
    SYMBOL
        *symbol;
    int
        item;

    if (cur_form-> list_values == NULL)
        cur_form-> list_values = sym_create_table ();

    item = fxlist_size (field, index);
    while (item > 0)
      {
        /*  Delete entry key symbol                                          */
        symbol = sym_lookup_symbol (cur_form-> list_values,
                                    list_key (field, index, item, 'k'));
        if (symbol)
            sym_delete_symbol (cur_form-> list_values, symbol);

        /*  Delete entry value symbol                                        */
        symbol = sym_lookup_symbol (cur_form-> list_values,
                                    list_key (field, index, item, 'v'));
        if (symbol)
            sym_delete_symbol (cur_form-> list_values, symbol);
        item--;
      }
    /*  Create header symbol for item 0, allowing a 3-digit value            */
    sym_create_symbol (cur_form-> list_values,
                       list_key (field, index, 0, 'h'), "000");
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxlist_append

    Synopsis: Appends values to the specified list.  Values are shown in the
    order that they are appended, and the select field itself carries the
    value of the selected item, 1 to n.  Returns the number of items on the
    list after appending, 1 or more.  The maximum size for a list is 999
    items.  Returns 0 if the list was not correctly reset.
    ---------------------------------------------------------------------[>]-*/

int
fxlist_append (int field, int index, char *key, char *value)
{
    SYMBOL
        *symbol;
    int
        list_size;

    ASSERT (cur_form-> list_values);
    symbol = sym_lookup_symbol (cur_form-> list_values,
                                list_key (field, index, 0, 'h'));
    if (symbol == NULL)
        return (0);                     /*  List has not been reset          */

    list_size = fxlist_size (field, index);
    if (list_size == 999)
        return (list_size);             /*  Sorry, we're full                */

    list_size++;                        /*  We're adding an item             */
    sym_assume_symbol (cur_form-> list_values,
                       list_key (field, index, list_size, 'k'), key);
    sym_assume_symbol (cur_form-> list_values,
                       list_key (field, index, list_size, 'v'), value);
    sprintf (symbol-> value, "%d", list_size);

    return (list_size);
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxlist_key

    Synopsis: Returns the key value for the select list.  If the field has
    a value zero (no selection), returns the empty string "".
    ---------------------------------------------------------------------[>]-*/

char *
fxlist_key (int field, int index)
{
    return (list_lookup (field, index, fxgetn_int (field, index), 'k'));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxlist_value

    Synopsis: Returns the value for the select list.  If the field has
    a value zero (no selection), returns the empty string "".
    ---------------------------------------------------------------------[>]-*/

char *
fxlist_value (int field, int index)
{
    return (list_lookup (field, index, fxgetn_int (field, index), 'v'));
}


/*  ---------------------------------------------------------------------[<]-
    Function: fxlist_set

    Synopsis: Sets the list variable to a number 1..n depending on the key
    specified.  If the specified key does not match any of the list keys,
    list variable is set to zero.
    ---------------------------------------------------------------------[>]-*/

void
fxlist_set (int field, int index, char *key)
{
    int
        item;

    ASSERT (cur_form-> list_values);
    item = fxlist_size (field, index);
    while (item > 0)
      {
        if (streq (list_lookup (field, index, item, 'k'), key))
            break;
        item--;
      }
    fxputn_int (field, index, item);
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_exec

    Synopsis: Executes a user-defined function for each block in the form.
    ---------------------------------------------------------------------[>]-*/

int
form_exec (
    FORM_ITEM *form,                    /*  Form instance to execute         */
    blockfunc  the_function,            /*  Function called for each block   */
    ...)                                /*  Optional argument list           */
{
    va_list
        argptr;                         /*  Argument list pointer            */
    byte
        *block_ptr;                     /*  Form block pointer               */
    word
        block_size;                     /*  Size of current block            */
    int
        field_nbr,                      /*  Form field number                */
        block_nbr,                      /*  Form block number                */
        count = 0;                      /*  Number of symbols processed ok   */

    ASSERT (form);
    va_start (argptr, the_function);    /*  Start variable args processing   */

    field_nbr = -1;                     /*  Field number 0..n-1              */
    block_ptr = form-> defn-> blocks;
    for (block_nbr = 0; block_nbr < form-> defn-> block_count; block_nbr++)
      {
        /*  Get block size, in high-low order                                */
        block_size = BLOCK_size (block_ptr);
        ASSERT (block_size > 0);
        if (BLOCK_IS_FIELD (BLOCK_type (block_ptr)))
            field_nbr++;
        if ((*the_function) (form, block_ptr, field_nbr, argptr))
            count++;
        else
            break;
        block_ptr += block_size + 2;    /*  Move to next block               */
      }
    va_end (argptr);                    /*  End variable args processing     */
    return (count);
}


/*  ---------------------------------------------------------------------[<]-
    Function: action_enable

    Synopsis: Enables one or all action buttons on the form.  If the event
    argument is -1, enables all form action buttons.  If the event argument
    is >= 0, enables the action button(s) that generate that event value.
    Note that you can also enable/disable action buttons individually by
    manipulating the button attribute data field.
    ---------------------------------------------------------------------[>]-*/

void
action_enable (FORM_ITEM *form, int event)
{
    form_exec (form, form_set_action, event, FACTION_ENABLED);
}


/*  --------------------------------------------------------------------------
 *  form_set_action -- internal
 *
 *  Sets a form action button as specified.  Called indirectly through
 *  form_exec().
 */

static Bool
form_set_action (
    FORM_ITEM *form,
    byte      *block_ptr,
    int        field_nbr,
    va_list    argptr)
{
    byte
        occurs;                         /*  Action occurs, if repeated       */
    int
        event,                          /*  Event specifier                  */
        attr,                           /*  New attribute for action         */
        occurence;                      /*  Occurs index                     */
    char
        *data_ptr;                      /*  Destination in form data         */

    /*  Get variable arguments off argument list                             */
    event = va_arg (argptr, int);
    attr  = va_arg (argptr, int);

    cur_form = form;
    if (BLOCK_type (block_ptr) == BLOCK_ACTION)
        if (event == -1
        ||  event == ACTION_event (block_ptr))
          {
            occurs = ACTION_times (block_ptr);

            /*  Point to destination data buffer                             */
            data_ptr = ACTION_attr (block_ptr, 0);

            /*  Set attribute for action(s)                                  */
            for (occurence = 0; occurence < occurs; occurence++)
                *data_ptr++ = attr;
          }
    return (TRUE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: action_disable

    Synopsis: Disables one or all action buttons on the form. If the event
    argument is -1, disables all form action buttons. If the event argument
    is >= 0, disables the action button(s) that generate that event value.
    Note that you can also enable/disable action buttons individually by
    manipulating the button attribute data field.
    ---------------------------------------------------------------------[>]-*/

void
action_disable (FORM_ITEM *form, int event)
{
    form_exec (form, form_set_action, event, FACTION_DISABLED);
}


/*  ---------------------------------------------------------------------[<]-
    Function: action_hide

    Synopsis: Hides one or all action buttons on the form.  If the event
    argument is -1, hides all form action buttons.  If the event argument
    is >= 0, hides the action button(s) that generate that event value.
    Note that you can also show or hide action buttons individually by
    manipulating the button attribute data field.
    ---------------------------------------------------------------------[>]-*/

void
action_hide (FORM_ITEM *form, int event)
{
    form_exec (form, form_set_action, event, FACTION_HIDDEN);
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_save

    Synopsis: Serialises a form as a binary data file.  Use this function to
    capture forms, or save a form for context management.  You can use the
    form_load() function to restore a saved form.  Returns 0 if okay, -1 if
    there was an error writing the file.  The saved data is fully portable
    and can be reloaded on any platform.
    ---------------------------------------------------------------------[>]-*/

int
form_save (
    const char *filename,
    FORM_ITEM  *form)
{
    FILE
        *stream;                        /*  Output file stream               */

    stream = fopen (filename, FOPEN_WRITE_BINARY);
    if (stream)
      {
        /*  Save form header fields                                          */
        fwrite (form, sizeof (FORM_ITEM), 1, stream);
        /*  Save form fields data and attributes                             */
        fwrite (form-> data, form-> data_size, 1, stream);
        fclose (stream);
        return (0);
      }
    else
        return (-1);
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_load

    Synopsis: Reloads a form item from the specified file stream.  This can
    be used to restore a transaction's form context.  You must pass the form
    definition as an argument.  Returns a newly-allocated form item if okay,
    or NULL if there was an error such as insufficient memory.
    ---------------------------------------------------------------------[>]-*/

FORM_ITEM *
form_load (
    const char *filename,
    FORM_DEFN  *defn)
{
    FILE
        *stream;                        /*  Input file stream                */
    FORM_ITEM
        *form;                          /*  Newly-allocated form item        */
    byte
        *data;                          /*  Allocated form data              */

    stream = fopen (filename, FOPEN_READ_BINARY);
    if (!stream)
        return (NULL);                  /*  File not found                   */

    if ((form = new_form_item (defn)) == NULL)
        return (NULL);                  /*  Signal not enough memory         */

    /*  Load form header fields                                              */
    data = form-> data;
    fread (form, sizeof (FORM_ITEM), 1, stream);
    form-> data = data;                 /*  We destroy these fields when we  */
    form-> defn = defn;                 /*    reload the form item           */

    /*  Load form fields data and attributes                                 */
    fread (form-> data, form-> data_size, 1, stream);
    mem_check (form-> data);            /*  Assert memory block is okay      */

    fclose (stream);
    return (form);
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_dump

    Synopsis: Checks and dumps a form instance.  Use to check that the
    generated form data structures are correctly generated.
    ---------------------------------------------------------------------[>]-*/

void
form_dump (FORM_ITEM *form)
{
    int
        block_nbr = 0;

    ASSERT (form);
    printf ("Dumping contents of form %s\n", form-> defn-> form_name);
    printf ("Block: Size:  Type:      Details:\n");

    form_exec (form, form_dump_block, &block_nbr);
}


/*  --------------------------------------------------------------------------
 *  form_dump_block -- internal
 *
 *  Dumps the definition of a block.  Called indirectly by the form_exec()
 *  function.
 */

static Bool
form_dump_block (
    FORM_ITEM *form,
    byte      *block_ptr,
    int        field_nbr,
    va_list    argptr)
{
    byte
        *cmp_block;                     /*  Compressed master block          */
    word
        block_size;                     /*  Size of current block            */
    int
        *block_nbr;                     /*  Block number                     */

    block_nbr  = va_arg (argptr, int *);
    block_size = BLOCK_size (block_ptr);
    printf ("%p %-6d %-6d ", block_ptr, *block_nbr, block_size);
    (*block_nbr)++;

    switch (BLOCK_type (block_ptr))     /*  Now handle the block             */
      {
        case BLOCK_PLAIN:
            printf ("plain      ");

            block_ptr += 2;             /*  Point to block type byte         */
            block_size--;               /*  Get actual size of HTML text     */
            if (block_size > 50)
                block_size = 50;        /*  Cut to fit on screen             */
            while (block_size-- > 0)
                printf ("%c", *++block_ptr);
            printf ("\n");
            break;

        case BLOCK_COMPRESSED:
            printf ("compressed ");
            cmp_block = COMPRESS_dict (block_ptr) + form-> defn-> blocks;
            if (COMPRESS_how (block_ptr) == COMPR_WHOLEDICT)
                block_size = BLOCK_size (cmp_block) - 1;
            else
            if (COMPRESS_how (block_ptr) == COMPR_PARTDICT)
                block_size = COMPRESS_size (block_ptr);
            else
                abort ();

            /*  Display compressed text                                  */
            cmp_block += 2;         /*  Point to block type byte         */
            if (block_size > 50)
                block_size = 50;
            while (block_size-- > 0)
                printf ("%c", *++cmp_block);
            printf ("\n");
            break;

        case BLOCK_IF:
            printf ("if         ");
            printf ("field=%d scope=%d value=%d\n",
                     IF_field       (block_ptr),
                     IF_scope       (block_ptr),
                     IF_value       (block_ptr));
            break;

        case BLOCK_UNLESS:
            printf ("unless     ");
            printf ("field=%d scope=%d value=%d\n",
                     UNLESS_field   (block_ptr),
                     UNLESS_scope   (block_ptr),
                     UNLESS_value   (block_ptr));
            break;

        case BLOCK_REPEAT:
            printf ("repeat     ");
            printf ("field=%d scope=%d occurs=%d\n",
                     REPEAT_field   (block_ptr),
                     REPEAT_scope   (block_ptr),
                     REPEAT_occurs  (block_ptr));
            break;

        case BLOCK_TEXTUAL:
            printf ("textual    ");
            printf ("x%d attr=%d size=%d max=%d name=%s value=%s\n",
                     TEXTUAL_times  (block_ptr),
                     TEXTUAL_attr   (block_ptr),
                     TEXTUAL_size   (block_ptr),
                     TEXTUAL_max    (block_ptr),
                     TEXTUAL_name   (block_ptr),
                     TEXTUAL_value  (block_ptr));
            break;

        case BLOCK_FILE:
            printf ("file       ");
            printf ("x%d attr=%d size=%d max=%d name=%s value=%s\n",
                     FILE_times  (block_ptr),
                     FILE_attr   (block_ptr),
                     FILE_size   (block_ptr),
                     FILE_max    (block_ptr),
                     FILE_name   (block_ptr),
                     FILE_value  (block_ptr));
            break;

        case BLOCK_NUMERIC:
            printf ("numeric    ");
            printf ("x%d attr=%d size=%d max=%d sign=%d decs=%d ",
                     NUMERIC_times  (block_ptr),
                     NUMERIC_attr   (block_ptr),
                     NUMERIC_size   (block_ptr),
                     NUMERIC_max    (block_ptr),
                     NUMERIC_sign   (block_ptr),
                     NUMERIC_decs   (block_ptr));
            printf ("fill=%d blank=%d comma=%d name=%s value=%s\n",
                     NUMERIC_fill   (block_ptr),
                     NUMERIC_blank  (block_ptr),
                     NUMERIC_comma  (block_ptr),
                     NUMERIC_name   (block_ptr),
                     NUMERIC_value  (block_ptr));
            break;

        case BLOCK_DATE:
            printf ("date       ");
            printf ("x%d attr=%d size=%d show=%d format=%d year=%d ",
                     DATE_times     (block_ptr),
                     DATE_attr      (block_ptr),
                     DATE_size      (block_ptr),
                     DATE_show      (block_ptr),
                     DATE_format    (block_ptr),
                     DATE_year      (block_ptr));
            printf ("month=%d day=%d name=%s value=%s picture=%s\n",
                     DATE_month     (block_ptr),
                     DATE_day       (block_ptr),
                     DATE_name      (block_ptr),
                     DATE_value     (block_ptr),
                     DATE_picture   (block_ptr));
            break;

        case BLOCK_TIME:
            printf ("time       ");
            printf ("x%d attr=%d size=%d name=%s value=%s picture=%s\n",
                     TIME_times     (block_ptr),
                     TIME_attr      (block_ptr),
                     TIME_size      (block_ptr),
                     TIME_name      (block_ptr),
                     TIME_value     (block_ptr),
                     TIME_picture   (block_ptr));
            break;

        case BLOCK_TEXTBOX:
            printf ("textbox    ");
            printf ("x%d attr=%d rows=%d cols=%d max=%d name=%s value=%s\n",
                     TEXTBOX_times  (block_ptr),
                     TEXTBOX_attr   (block_ptr),
                     TEXTBOX_rows   (block_ptr),
                     TEXTBOX_cols   (block_ptr),
                     TEXTBOX_max    (block_ptr),
                     TEXTBOX_name   (block_ptr),
                     TEXTBOX_value  (block_ptr));
            break;

        case BLOCK_BOOLEAN:
            printf ("boolean    ");
            printf ("x%d attr=%d name=%s value=%s\n",
                     BOOLEAN_times  (block_ptr),
                     BOOLEAN_attr   (block_ptr),
                     BOOLEAN_name   (block_ptr),
                     BOOLEAN_value  (block_ptr));
            break;

        case BLOCK_SELECT:
            printf ("select     ");
            printf ("x%d attr=%d size=%d opts=%d name=%s value=%s first=%s onchange=%d-%s\n",
                     SELECT_times    (block_ptr),
                     SELECT_attr     (block_ptr),
                     SELECT_size     (block_ptr),
                     SELECT_options  (block_ptr),
                     SELECT_name     (block_ptr),
                     SELECT_value    (block_ptr),
                     SELECT_first    (block_ptr),
                     SELECT_onchange (block_ptr),
                     SELECT_script   (block_ptr));
            break;

        case BLOCK_RADIO:
            printf ("radio      ");
            printf ("x%d attr=%d column=%d name=%s value=%s\n",
                     RADIO_times    (block_ptr),
                     RADIO_attr     (block_ptr),
                     RADIO_column   (block_ptr),
                     RADIO_name     (block_ptr),
                     RADIO_value    (block_ptr));
            break;

        case BLOCK_ACTION:
            printf ("action     ");
            printf ("x%d type=%d event=%d show=%d height=%d width=%d label=%s alt=%s\n",
                     ACTION_times   (block_ptr),
                     ACTION_type    (block_ptr),
                     ACTION_event   (block_ptr),
                     ACTION_show    (block_ptr),
                     ACTION_height  (block_ptr),
                     ACTION_width   (block_ptr),
                     ACTION_label   (block_ptr),
                     ACTION_alt     (block_ptr));
            break;

        case BLOCK_IMAGE:
            printf ("image      ");
            printf ("x%d attr=%d name=%s label=%s\n",
                     IMAGE_times    (block_ptr),
                     IMAGE_attr     (block_ptr),
                     IMAGE_name     (block_ptr),
                     IMAGE_label    (block_ptr));
            break;

        default:
            printf ("ERROR!\n");
            abort ();
      }
    return (TRUE);
}


/*  ---------------------------------------------------------------------[<]-
    Function: form_ftype

    Synopsis: Returns the type of the specified form field; returns one of
    these values:
    <TABLE>
    BLOCK_TEXTUAL       Textual field
    BLOCK_FILE          File field
    BLOCK_NUMERIC       Numeric field
    BLOCK_DATE          Date field
    BLOCK_TIME          Time field
    BLOCK_TEXTBOX       Multiline text field
    BLOCK_BOOLEAN       Boolean field
    BLOCK_SELECT        Selection field
    BLOCK_RADIO         Radio-button data field
    BLOCK_ACTION        Action-button field
    BLOCK_IMAGE         Image field
    0                   Invalid field number
    </TABLE>
    ---------------------------------------------------------------------[>]-*/

int
form_ftype (
    FORM_ITEM *form,
    int        field_nbr)
{
    FORM_DEFN
        *defn;

    ASSERT (form);

    defn = form-> defn;
    if (field_nbr < 0 || field_nbr >= defn-> field_count)
        return (0);
    else
        return (BLOCK_type (defn-> blocks + defn-> fields [field_nbr].block));
}

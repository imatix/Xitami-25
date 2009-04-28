/*===========================================================================*
 *                                                                           *
 *  wtplib.h - WTP interface functions                                       *
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

#ifndef _WTPLIB_INCLUDED		/*  Allow multiple inclusions	     */
#define _WTPLIB_INCLUDED


/*  Prototypes								     */

#ifdef __cplusplus
extern "C" {
#endif

void   wtp_open       (const char *version, const char *protocol,
		       const char *port);
void   wtp_close      (void);
void   wtp_connect    (const char *callback, const char *filename);
void   wtp_register   (const char *program, Bool is_root);
void   wtp_ready      (void);
void   wtp_doneshow   (const char *html_data,
		       qbyte global_size, const byte *global_data,
		       qbyte local_size, const byte *local_data);
void   wtp_donecall   (const char *program,
		       qbyte args_size,  const byte *args_data,
		       qbyte global_size, const byte *global_data,
		       qbyte local_size, const byte *local_data);
void   wtp_donereturn (qbyte args_size,  const byte *args_data,
		       qbyte global_size, const byte *global_data);
void   wtp_doneexit   (void);
void   wtp_doneerror  (const char *message);
void   wtp_error      (dbyte error_code, const char *error_text);
void   wtp_write      (const byte *buffer, size_t size);
size_t wtp_read       (byte **buffer);
Bool   wtp_expect_ok  (void);
qbyte  wtp_signature  (const char *filename);

#ifdef __cplusplus
}
#endif


/*  Messages								     */

#define WTP_OK		       1	/*  Request suceeded		     */
#define WTP_ERROR	       2	/*  Request failed		     */
#define WTP_CONNECT	       3	/*  Connects to the WTP manager      */
#define WTP_DISCONNECT	       4	/*  Disconnect from the WTP manager  */
#define WTP_REGISTER	       5	/*  Registers a program 	     */
#define WTP_READY	       6	/*  Signal ready for work	     */
#define WTP_DO		       7	/*  Execute some program	     */
#define WTP_DELETE	       8	/*  Get context block		     */
#define WTP_GET 	       9	/*  Get context block		     */
#define WTP_CONTEXT	       10	/*  Supply context block	     */
#define WTP_PUT 	       11	/*  Put context block		     */
#define WTP_DONESHOW	       12	/*  End program, show HTML form      */
#define WTP_DONECALL	       13	/*  End program, call new program    */
#define WTP_DONERETURN	       14	/*  End program, return to caller    */
#define WTP_DONEEXIT	       15	/*  End program, exit application    */
#define WTP_DONEERROR	       16	/*  End program, fatal error	     */


/*  Error codes 							     */

#define WTP_NOERROR	       0	/*  No error			     */
#define WTP_ERRORDUPLICATE     1	/*  Context block already exists     */
#define WTP_ERRORFATAL	       2	/*  WTP manager could not continue   */
#define WTP_ERRORINVALID       3	/*  Invalid message type	     */
#define WTP_ERRORNOTFOUND      4	/*  Program is not known	     */
#define WTP_ERROROVERFLOW      5	/*  Too many active programs	     */
#define WTP_ERRORSIGNATURE     6	/*  ATP signature has changed	     */
#define WTP_ERRORUNAUTHORISED  7	/*  An invalid callback key supplied */
#define WTP_ERRORUNAVAILABLE   8	/*  Program is no longer available   */
#define WTP_ERRORUNCONNECTED   9	/*  WTP_CONNECT not sent, or failed  */
#define WTP_ERRORUNEXPECTED   10	/*  Not valid at this point	     */
#define WTP_ERRORWOULDLOOP    11	/*  Program is already active parent */

/*  Entry codes 							     */

#define WTP_DOINIT	       1	/*  Initialise the program	     */
#define WTP_DOGET	       2	/*  Process HTML form data	     */
#define WTP_DOCONTINUE	       3	/*  Continue from called program     */


#endif					/*  Include wtpdefn.h		     */
/*---------------------------------------------------------------------------
 *  wtpmsg.h - prototypes for WTP/1.0 standard messages.
 *
 *  Generated on 2004/07/22, 17:52:22 from wtpmsg.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_WTPMSG
#define INCLUDE_WTPMSG

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for wtpman - WTP/1.0 Standard Messages.
 *---------------------------------------------------------------------------*/

#define WTP_MSG "b"

typedef struct {
    byte  type;                         /*  Message type                     */
} struct_wtp_msg;


int  get_wtp_msg             (byte *_buffer, struct_wtp_msg **params);
void free_wtp_msg            (struct_wtp_msg **params);
int  put_wtp_msg             (byte **_buffer, byte  type);


#define WTP_MSG_CONNECT "bsq"

typedef struct {
    byte  type;                         /*  Message type                     */
    char *callback_key;                 /*  Callback key                     */
    qbyte signature;                    /*  ATP signature                    */
} struct_wtp_msg_connect;


int  get_wtp_msg_connect     (byte *_buffer, struct_wtp_msg_connect **params);
void free_wtp_msg_connect    (struct_wtp_msg_connect **params);
int  put_wtp_msg_connect     (byte **_buffer, byte  type, char *callback_key, qbyte signature);


#define WTP_MSG_REGISTER "bsb"

typedef struct {
    byte  type;                         /*  Message type                     */
    char *program;                      /*  Program to register              */
    byte  is_root;                      /*  Root program?                    */
} struct_wtp_msg_register;


int  get_wtp_msg_register    (byte *_buffer, struct_wtp_msg_register **params);
void free_wtp_msg_register   (struct_wtp_msg_register **params);
int  put_wtp_msg_register    (byte **_buffer, byte  type, char *program, byte  is_root);


#define WTP_MSG_READY "b"

typedef struct {
    byte  type;                         /*  Message type                     */
} struct_wtp_msg_ready;


int  get_wtp_msg_ready       (byte *_buffer, struct_wtp_msg_ready **params);
void free_wtp_msg_ready      (struct_wtp_msg_ready **params);
int  put_wtp_msg_ready       (byte **_buffer, byte  type);


#define WTP_MSG_DISCONNECT "b"

typedef struct {
    byte  type;                         /*  Message type                     */
} struct_wtp_msg_disconnect;


int  get_wtp_msg_disconnect  (byte *_buffer, struct_wtp_msg_disconnect **params);
void free_wtp_msg_disconnect  (struct_wtp_msg_disconnect **params);
int  put_wtp_msg_disconnect  (byte **_buffer, byte  type);


#define WTP_MSG_OK "b"

typedef struct {
    byte  type;                         /*  Message type                     */
} struct_wtp_msg_ok;


int  get_wtp_msg_ok          (byte *_buffer, struct_wtp_msg_ok **params);
void free_wtp_msg_ok         (struct_wtp_msg_ok **params);
int  put_wtp_msg_ok          (byte **_buffer, byte  type);


#define WTP_MSG_ERROR "bds"

typedef struct {
    byte  type;                         /*  Message type                     */
    dbyte error_code;                   /*  Error code                       */
    char *error_text;                   /*  Error message text               */
} struct_wtp_msg_error;


int  get_wtp_msg_error       (byte *_buffer, struct_wtp_msg_error **params);
void free_wtp_msg_error      (struct_wtp_msg_error **params);
int  put_wtp_msg_error       (byte **_buffer, byte  type, dbyte error_code, char *error_text);


#define WTP_MSG_DO "bqsbsshHbhHhHhH"

typedef struct {
    byte  type;                         /*  Message type                     */
    qbyte signature;                    /*  ATP signature                    */
    char *program;                      /*  Program to execute               */
    byte  entry_code;                   /*  Program entry code               */
    char *http_uri;                     /*  URI for hyperlinks               */
    char *http_data;                    /*  Encoded HTTP data                */
    qbyte args_size;                    /*  Return arguments size            */
    byte *args_data;                    /*  Return arguments data            */
    byte  call_result;                  /*  Result of last call              */
    qbyte env_size;                     /*  Environment size                 */
    byte *env_data;                     /*  Environment block                */
    qbyte global_size;                  /*  Global context size              */
    byte *global_data;                  /*  Global context block             */
    qbyte local_size;                   /*  Local context size               */
    byte *local_data;                   /*  Local context block              */
} struct_wtp_msg_do;


int  get_wtp_msg_do          (byte *_buffer, struct_wtp_msg_do **params);
void free_wtp_msg_do         (struct_wtp_msg_do **params);
int  put_wtp_msg_do          (byte **_buffer, byte  type, qbyte signature, char *program, byte  entry_code, char *http_uri, char *http_data, qbyte args_size, byte *args_data, byte  call_result, qbyte env_size, byte *env_data, qbyte global_size, byte *global_data, qbyte local_size, byte *local_data);


#define WTP_MSG_DONESHOW "bshHhH"

typedef struct {
    byte  type;                         /*  Message type                     */
    char *html_data;                    /*  HTML screen data                 */
    qbyte global_size;                  /*  Global context size              */
    byte *global_data;                  /*  Global context block             */
    qbyte local_size;                   /*  Local context size               */
    byte *local_data;                   /*  Local context block              */
} struct_wtp_msg_doneshow;


int  get_wtp_msg_doneshow    (byte *_buffer, struct_wtp_msg_doneshow **params);
void free_wtp_msg_doneshow   (struct_wtp_msg_doneshow **params);
int  put_wtp_msg_doneshow    (byte **_buffer, byte  type, char *html_data, qbyte global_size, byte *global_data, qbyte local_size, byte *local_data);


#define WTP_MSG_DONECALL "bshHhHhH"

typedef struct {
    byte  type;                         /*  Message type                     */
    char *program;                      /*  Program to call                  */
    qbyte args_size;                    /*  Call arguments size              */
    byte *args_data;                    /*  Call arguments data              */
    qbyte global_size;                  /*  Global context size              */
    byte *global_data;                  /*  Global context block             */
    qbyte local_size;                   /*  Local context size               */
    byte *local_data;                   /*  Local context block              */
} struct_wtp_msg_donecall;


int  get_wtp_msg_donecall    (byte *_buffer, struct_wtp_msg_donecall **params);
void free_wtp_msg_donecall   (struct_wtp_msg_donecall **params);
int  put_wtp_msg_donecall    (byte **_buffer, byte  type, char *program, qbyte args_size, byte *args_data, qbyte global_size, byte *global_data, qbyte local_size, byte *local_data);


#define WTP_MSG_DONERETURN "bhHhH"

typedef struct {
    byte  type;                         /*  Message type                     */
    qbyte args_size;                    /*  Call arguments size              */
    byte *args_data;                    /*  Call arguments data              */
    qbyte global_size;                  /*  Global context size              */
    byte *global_data;                  /*  Global context block             */
} struct_wtp_msg_donereturn;


int  get_wtp_msg_donereturn  (byte *_buffer, struct_wtp_msg_donereturn **params);
void free_wtp_msg_donereturn  (struct_wtp_msg_donereturn **params);
int  put_wtp_msg_donereturn  (byte **_buffer, byte  type, qbyte args_size, byte *args_data, qbyte global_size, byte *global_data);


#define WTP_MSG_DONEEXIT "b"

typedef struct {
    byte  type;                         /*  Message type                     */
} struct_wtp_msg_doneexit;


int  get_wtp_msg_doneexit    (byte *_buffer, struct_wtp_msg_doneexit **params);
void free_wtp_msg_doneexit   (struct_wtp_msg_doneexit **params);
int  put_wtp_msg_doneexit    (byte **_buffer, byte  type);


#define WTP_MSG_DONEERROR "bs"

typedef struct {
    byte  type;                         /*  Message type                     */
    char *error_text;                   /*  Error message text               */
} struct_wtp_msg_doneerror;


int  get_wtp_msg_doneerror   (byte *_buffer, struct_wtp_msg_doneerror **params);
void free_wtp_msg_doneerror  (struct_wtp_msg_doneerror **params);
int  put_wtp_msg_doneerror   (byte **_buffer, byte  type, char *error_text);



#endif                                  /*  Included                         */
/*===========================================================================*
 *                                                                           *
 *  ctxman.h - Context management functions                                  *
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

#ifndef _CTXMAN_INCLUDED                /*  Allow multiple inclusions        */
#define _CTXMAN_INCLUDED


SYMTAB *context_init    (int scope);
void    context_term    (int scope);
SYMTAB *context_addr    (int scope);
char   *context_key     (const char *format, ...);
Bool    context_put     (int scope, const char *key,
                         const void *source, size_t length);
Bool    context_get     (int scope, const char *key,
                         void *dest, size_t length);
Bool    context_putsym  (int scope, const char *key, const SYMTAB *symtab);
Bool    context_getsym  (int scope, const char *key, SYMTAB **symtab);


/*  These macros provide external names for these functions                  */

#define CONTEXT_PUTL(k,s,l)  context_put (SCOPE_LOCAL,  (k), (s), (l))
#define CONTEXT_PUTG(k,s,l)  context_put (SCOPE_GLOBAL, (k), (s), (l))
#define CONTEXT_GETL(k,s,l)  context_get (SCOPE_LOCAL,  (k), (s), (l))
#define CONTEXT_GETG(k,s,l)  context_get (SCOPE_GLOBAL, (k), (s), (l))


/*  Context scopes                                                           */

enum {
    SCOPE_GLOBAL = 1,                   /*  Global context block             */
    SCOPE_LOCAL  = 2                    /*  Program-local context block      */
};


#endif
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
/*===========================================================================*
 *                                                                           *
 *  brocgi.h - CGI broker functions                                          *
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

#ifndef _BROCGI_INCLUDED                /*  Allow multiple inclusions        */
#define _BROCGI_INCLUDED

#if defined (USE_CGI_BROKER)

/*  --- TRANSACTION MANAGER API -------------------------------------------- */

/*  Prototypes for transaction manager functions                             */

int   cgi_broker       (char *uri_data, char *form_data, char *main_url);
char *cgi_root         (void);


#define STACK_MAX        16             /*  Max. application call depth      */
#define PRGNAME_MAX      9              /*  Max. program name size           */
#define ARGS_MAX         1024           /*  Max. parameters length           */

/*  This is the format of the FX/CGI session context block                   */

typedef struct {
/*- Private variables ----------------- */
    long    session_id_;                /*  Session identifier               */
    long    session_step_;              /*  Session step number (1..n)       */
    char    stack_ [STACK_MAX][PRGNAME_MAX];
    int     stack_ptr_;                 /*  Number of stacked programs       */
    VDESCR *buffer_;                    /*  Form input/output buffer         */
    Bool    debug_mode_;                /*  Assist program debug output      */

/*- Public variables ------------------ */
    FORM_ITEM *form;                    /*  Current form instance            */
    SYMTAB    *symbols;                 /*  Program form symbols             */
    char program_name    [PRGNAME_MAX]; /*  Current program name             */
    char program_to_call [PRGNAME_MAX]; /*  Program that we want to call     */
    int  program_callcode;              /*  Result of call request           */
    byte disable_actions;               /*  Show disabled actions            */
} SESSION;


/*  Broker program feedbacks                                                 */

enum {
    FEEDBACK_SHOW    = 0,               /*  Show the form                    */
    FEEDBACK_CALL    = 1,               /*  Call a new program               */
    FEEDBACK_RETURN  = 2,               /*  Return to parent program         */
    FEEDBACK_ERROR   = 3,               /*  Error - terminate                */
    FEEDBACK_UNKNOWN = 4                /*  Program unknown in application   */
};

/*  Values for session callcode                                              */

enum {
    CALLCODE_OKAY     = 0,              /*  Program call succeeded           */
    CALLCODE_UNKNOWN  = 1,              /*  Program unknown in application   */
    CALLCODE_ACTIVE   = 2,              /*  Program is already active        */
    CALLCODE_OVERFLOW = 3               /*  Max. active programs reached     */
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
    char    *name;                      /*  Name of program                  */
    ATP_FCT function;                   /*  And function that provides it    */
} BROKER_MAP;


/*  This global table must be supplied by the broker program as a static     */
/*  table with the program names in alphabetical order, and the final        */
/*  entry a NULL, NULL pair.  Program names must be lowercase.               */

extern BROKER_MAP
    cgi_broker_map [];

#endif
#endif

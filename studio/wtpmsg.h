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

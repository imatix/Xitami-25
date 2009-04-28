/*---------------------------------------------------------------------------
 *  smtsslm.h - prototypes for Smtssl messages.
 *
 *  Generated on 2004/07/22, 17:52:21 from smtsslm.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_SMTSSLM
#define INCLUDE_SMTSSLM

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtssl - SMT SSL agent.
 *---------------------------------------------------------------------------*/

#define SSL_OPEN "s"

typedef struct {
    char *config;                       /*  Configuration file to use        */
} struct_ssl_open;


int  get_ssl_open            (byte *_buffer, struct_ssl_open **params);
void free_ssl_open           (struct_ssl_open **params);
int  put_ssl_open            (byte **_buffer, char *config);

#define declare_ssl_open(_event, _priority)                                  \
    method_declare (agent, "SSL_OPEN", _event, _priority)

/*  Send event - Open SSL port                                               */

int lsend_ssl_open (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *config);                  /*  Configuration file to use        */

#define send_ssl_open(_to,                                                   \
                      config)                                                \
       lsend_ssl_open(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      config)


#define SSL_OPEN_OK "d"

typedef struct {
    dbyte port;                         /*  SSL port opened                  */
} struct_ssl_open_ok;


int  get_ssl_open_ok         (byte *_buffer, struct_ssl_open_ok **params);
void free_ssl_open_ok        (struct_ssl_open_ok **params);
int  put_ssl_open_ok         (byte **_buffer, dbyte port);

#define declare_ssl_open_ok(_event, _priority)                               \
    method_declare (agent, "SSL_OPEN_OK", _event, _priority)

/*  Send event - SSL port opened OK                                          */

int lsend_ssl_open_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte port);                    /*  SSL port opened                  */

#define send_ssl_open_ok(_to,                                                \
                         port)                                               \
       lsend_ssl_open_ok(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         port)


#define SSL_CLOSE ""


#define declare_ssl_close(_event, _priority)                                 \
    method_declare (agent, "SSL_CLOSE", _event, _priority)

/*  Send event - Close SSL port                                              */

int lsend_ssl_close (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_ssl_close(_to)                                                  \
       lsend_ssl_close(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0)


#define SSL_RESTART ""


#define declare_ssl_restart(_event, _priority)                               \
    method_declare (agent, "SSL_RESTART", _event, _priority)

/*  Send event - Restart SSL connection                                      */

int lsend_ssl_restart (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_ssl_restart(_to)                                                \
       lsend_ssl_restart(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0)


#define SSL_ACCEPTED "qssd"

typedef struct {
    qbyte socket;                       /*  Socket handle for SSL connection  */
    char *user;                         /*  User name                        */
    char *cipher;                       /*  Cipher used                      */
    dbyte verify;                       /*  Level of user verification       */
} struct_ssl_accepted;


int  get_ssl_accepted        (byte *_buffer, struct_ssl_accepted **params);
void free_ssl_accepted       (struct_ssl_accepted **params);
int  put_ssl_accepted        (byte **_buffer, qbyte socket, char *user, char *cipher, dbyte verify);

#define declare_ssl_accepted(_event, _priority)                              \
    method_declare (agent, "SSL_ACCEPTED", _event, _priority)

/*  Send event - Accept SSL connection                                       */

int lsend_ssl_accepted (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket handle for SSL connection  */
        char *user,                     /*  User name                        */
        char *cipher,                   /*  Cipher used                      */
        dbyte verify);                  /*  Level of user verification       */

#define send_ssl_accepted(_to,                                               \
                          socket,                                            \
                          user,                                              \
                          cipher,                                            \
                          verify)                                            \
       lsend_ssl_accepted(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          socket,                                            \
                          user,                                              \
                          cipher,                                            \
                          verify)


#define SSL_READ_REQUEST "q"

typedef struct {
    qbyte size;                         /*  Maximum size to read             */
} struct_ssl_read_request;


int  get_ssl_read_request    (byte *_buffer, struct_ssl_read_request **params);
void free_ssl_read_request   (struct_ssl_read_request **params);
int  put_ssl_read_request    (byte **_buffer, qbyte size);

#define declare_ssl_read_request(_event, _priority)                          \
    method_declare (agent, "SSL_READ_REQUEST", _event, _priority)

/*  Send event - Request read                                                */

int lsend_ssl_read_request (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Maximum size to read             */

#define send_ssl_read_request(_to,                                           \
                              size)                                          \
       lsend_ssl_read_request(_to,                                           \
                              &thread-> queue-> qid,                         \
                              NULL, NULL, NULL, 0,                           \
                              size)


#define SSL_WRITE_REQUEST "dqmMq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to write to               */
    word  size;                         /*  Amount of data to write          */
    byte *data;                         /*  Block of data to write           */
    qbyte tag;                          /*  User-defined request tag         */
} struct_ssl_write_request;


int  get_ssl_write_request   (byte *_buffer, struct_ssl_write_request **params);
void free_ssl_write_request  (struct_ssl_write_request **params);
int  put_ssl_write_request   (byte **_buffer, dbyte timeout, qbyte socket, word  size, byte *data, qbyte tag);

#define declare_ssl_write_request(_event, _priority)                         \
    method_declare (agent, "SSL_WRITE_REQUEST", _event, _priority)

/*  Send event - Write SSL data                                              */

int lsend_ssl_write_request (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to write to               */
        word  size,                     /*  Amount of data to write          */
        byte *data,                     /*  Block of data to write           */
        qbyte tag);                     /*  User-defined request tag         */

#define send_ssl_write_request(_to,                                          \
                               timeout,                                      \
                               socket,                                       \
                               size,                                         \
                               data,                                         \
                               tag)                                          \
       lsend_ssl_write_request(_to,                                          \
                               &thread-> queue-> qid,                        \
                               NULL, NULL, NULL, 0,                          \
                               timeout,                                      \
                               socket,                                       \
                               size,                                         \
                               data,                                         \
                               tag)


#define SSL_PUT_SLICE "qsqq"

typedef struct {
    qbyte socket;                       /*  Socket for output                */
    char *filename;                     /*  Name of file to send             */
    qbyte start;                        /*  Starting offset; 0 = start       */
    qbyte end;                          /*  Ending offset; 0 = end           */
} struct_ssl_put_slice;


int  get_ssl_put_slice       (byte *_buffer, struct_ssl_put_slice **params);
void free_ssl_put_slice      (struct_ssl_put_slice **params);
int  put_ssl_put_slice       (byte **_buffer, qbyte socket, char *filename, qbyte start, qbyte end);

#define declare_ssl_put_slice(_event, _priority)                             \
    method_declare (agent, "SSL_PUT_SLICE", _event, _priority)

/*  Send event - Write file slice to SSL socket                              */

int lsend_ssl_put_slice (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        char *filename,                 /*  Name of file to send             */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end);                     /*  Ending offset; 0 = end           */

#define send_ssl_put_slice(_to,                                              \
                           socket,                                           \
                           filename,                                         \
                           start,                                            \
                           end)                                              \
       lsend_ssl_put_slice(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           socket,                                           \
                           filename,                                         \
                           start,                                            \
                           end)


#define SSL_ERROR "q"

typedef struct {
    qbyte code;                         /*  Error code                       */
} struct_ssl_error;


int  get_ssl_error           (byte *_buffer, struct_ssl_error **params);
void free_ssl_error          (struct_ssl_error **params);
int  put_ssl_error           (byte **_buffer, qbyte code);

#define declare_ssl_error(_event, _priority)                                 \
    method_declare (agent, "SSL_ERROR", _event, _priority)

/*  Send event - Signal SSL error                                            */

int lsend_ssl_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte code);                    /*  Error code                       */

#define send_ssl_error(_to,                                                  \
                       code)                                                 \
       lsend_ssl_error(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0,                                  \
                       code)


#define SSL_WRITE_OK "qq"

typedef struct {
    qbyte socket;                       /*  Socket used for i/o, or new socket  */
    qbyte tag;                          /*  User-defined request tag         */
} struct_ssl_write_ok;


int  get_ssl_write_ok        (byte *_buffer, struct_ssl_write_ok **params);
void free_ssl_write_ok       (struct_ssl_write_ok **params);
int  put_ssl_write_ok        (byte **_buffer, qbyte socket, qbyte tag);

#define declare_ssl_write_ok(_event, _priority)                              \
    method_declare (agent, "SSL_WRITE_OK", _event, _priority)

/*  Send event - Write OK reply                                              */

int lsend_ssl_write_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_ssl_write_ok(_to,                                               \
                          socket,                                            \
                          tag)                                               \
       lsend_ssl_write_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          socket,                                            \
                          tag)


#define SSL_READ_OK "mM"

typedef struct {
    word  size;                         /*  Size of result                   */
    byte *data;                         /*  Read data                        */
} struct_ssl_read_ok;


int  get_ssl_read_ok         (byte *_buffer, struct_ssl_read_ok **params);
void free_ssl_read_ok        (struct_ssl_read_ok **params);
int  put_ssl_read_ok         (byte **_buffer, word  size, byte *data);

#define declare_ssl_read_ok(_event, _priority)                               \
    method_declare (agent, "SSL_READ_OK", _event, _priority)

/*  Send event - Read result data                                            */

int lsend_ssl_read_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  size,                     /*  Size of result                   */
        byte *data);                    /*  Read data                        */

#define send_ssl_read_ok(_to,                                                \
                         size,                                               \
                         data)                                               \
       lsend_ssl_read_ok(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         size,                                               \
                         data)


#define SSL_PUT_SLICE_OK "q"

typedef struct {
    qbyte size;                         /*  Amount of transmitted data       */
} struct_ssl_put_slice_ok;


int  get_ssl_put_slice_ok    (byte *_buffer, struct_ssl_put_slice_ok **params);
void free_ssl_put_slice_ok   (struct_ssl_put_slice_ok **params);
int  put_ssl_put_slice_ok    (byte **_buffer, qbyte size);

#define declare_ssl_put_slice_ok(_event, _priority)                          \
    method_declare (agent, "SSL_PUT_SLICE_OK", _event, _priority)

/*  Send event - File written okay                                           */

int lsend_ssl_put_slice_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Amount of transmitted data       */

#define send_ssl_put_slice_ok(_to,                                           \
                              size)                                          \
       lsend_ssl_put_slice_ok(_to,                                           \
                              &thread-> queue-> qid,                         \
                              NULL, NULL, NULL, 0,                           \
                              size)



#endif                                  /*  Included                         */

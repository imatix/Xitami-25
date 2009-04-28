/*---------------------------------------------------------------------------
 *  smtmsg.h - prototypes for SMT standard messages.
 *
 *  Generated on 2004/07/22, 17:52:20 from smtmsg.xml
 *  by smtexdr.gsl using GSLgen.
 *  DO NOT MODIFY THIS FILE.
 *
 *  For documentation and updates see http://www.imatix.com.
 *---------------------------------------------------------------------------*/
#ifndef INCLUDE_SMTMSG
#define INCLUDE_SMTMSG

/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtopen - Operator agent.
 *---------------------------------------------------------------------------*/

#define SMT_OPER_LOG "ss"

typedef struct {
    char *agent_name;                   /*  Name of logging agent            */
    char *thread_name;                  /*  Name of logging thread           */
} struct_smt_oper_log;


int  get_smt_oper_log        (byte *_buffer, struct_smt_oper_log **params);
void free_smt_oper_log       (struct_smt_oper_log **params);
int  put_smt_oper_log        (byte **_buffer, char *agent_name, char *thread_name);

#define declare_set_log(_event, _priority)                                   \
    method_declare (agent, "SET_LOG", _event, _priority)

/*  Send event - Specify logging agent                                       */

int lsend_set_log (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *agent_name,               /*  Name of logging agent            */
        char *thread_name);             /*  Name of logging thread           */

#define send_set_log(_to,                                                    \
                     agent_name,                                             \
                     thread_name)                                            \
       lsend_set_log(_to,                                                    \
                     &thread-> queue-> qid,                                  \
                     NULL, NULL, NULL, 0,                                    \
                     agent_name,                                             \
                     thread_name)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtsock - Socket i/o agent.
 *---------------------------------------------------------------------------*/

#define SMT_SOCK_READ "dqddq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to read from              */
    dbyte max_size;                     /*  Size of receiving buffer         */
    dbyte min_size;                     /*  Minimum data to read, zero = all  */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_read;


int  get_smt_sock_read       (byte *_buffer, struct_smt_sock_read **params);
void free_smt_sock_read      (struct_smt_sock_read **params);
int  put_smt_sock_read       (byte **_buffer, dbyte timeout, qbyte socket, dbyte max_size, dbyte min_size, qbyte tag);

#define declare_read(_event, _priority)                                      \
    method_declare (agent, "READ", _event, _priority)

/*  Send event - Read socket data                                            */

int lsend_read (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        dbyte max_size,                 /*  Size of receiving buffer         */
        dbyte min_size,                 /*  Minimum data to read, zero = all  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_read(_to,                                                       \
                  timeout,                                                   \
                  socket,                                                    \
                  max_size,                                                  \
                  min_size,                                                  \
                  tag)                                                       \
       lsend_read(_to,                                                       \
                  &thread-> queue-> qid,                                     \
                  NULL, NULL, NULL, 0,                                       \
                  timeout,                                                   \
                  socket,                                                    \
                  max_size,                                                  \
                  min_size,                                                  \
                  tag)

#define declare_readr(_event, _priority)                                     \
    method_declare (agent, "READR", _event, _priority)

/*  Send event - Read, repeat for ever                                       */

int lsend_readr (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        dbyte max_size,                 /*  Size of receiving buffer         */
        dbyte min_size,                 /*  Minimum data to read, zero = all  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_readr(_to,                                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   max_size,                                                 \
                   min_size,                                                 \
                   tag)                                                      \
       lsend_readr(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   max_size,                                                 \
                   min_size,                                                 \
                   tag)


#define SMT_SOCK_WRITE "dqmMq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to write to               */
    word  size;                         /*  Amount of data to write          */
    byte *data;                         /*  Block of data to write           */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_write;


int  get_smt_sock_write      (byte *_buffer, struct_smt_sock_write **params);
void free_smt_sock_write     (struct_smt_sock_write **params);
int  put_smt_sock_write      (byte **_buffer, dbyte timeout, qbyte socket, word  size, byte *data, qbyte tag);

#define declare_write(_event, _priority)                                     \
    method_declare (agent, "WRITE", _event, _priority)

/*  Send event - Write socket data                                           */

int lsend_write (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to write to               */
        word  size,                     /*  Amount of data to write          */
        byte *data,                     /*  Block of data to write           */
        qbyte tag);                     /*  User-defined request tag         */

#define send_write(_to,                                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   size,                                                     \
                   data,                                                     \
                   tag)                                                      \
       lsend_write(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   size,                                                     \
                   data,                                                     \
                   tag)


#define SMT_SOCK_READH "dqqqq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to read from              */
    qbyte max_size;                     /*  Size of receiving buffer         */
    qbyte min_size;                     /*  Minimum data to read, zero = all  */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_readh;


int  get_smt_sock_readh      (byte *_buffer, struct_smt_sock_readh **params);
void free_smt_sock_readh     (struct_smt_sock_readh **params);
int  put_smt_sock_readh      (byte **_buffer, dbyte timeout, qbyte socket, qbyte max_size, qbyte min_size, qbyte tag);

#define declare_readh(_event, _priority)                                     \
    method_declare (agent, "READH", _event, _priority)

/*  Send event - Read huge socket data                                       */

int lsend_readh (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        qbyte max_size,                 /*  Size of receiving buffer         */
        qbyte min_size,                 /*  Minimum data to read, zero = all  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_readh(_to,                                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   max_size,                                                 \
                   min_size,                                                 \
                   tag)                                                      \
       lsend_readh(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   max_size,                                                 \
                   min_size,                                                 \
                   tag)

#define declare_readrh(_event, _priority)                                    \
    method_declare (agent, "READRH", _event, _priority)

/*  Send event - Read huge, repeat for ever                                  */

int lsend_readrh (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to read from              */
        qbyte max_size,                 /*  Size of receiving buffer         */
        qbyte min_size,                 /*  Minimum data to read, zero = all  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_readrh(_to,                                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    max_size,                                                \
                    min_size,                                                \
                    tag)                                                     \
       lsend_readrh(_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    NULL, NULL, NULL, 0,                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    max_size,                                                \
                    min_size,                                                \
                    tag)


#define SMT_SOCK_WRITEH "dqhHq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to write to               */
    qbyte size;                         /*  Amount of data to write          */
    byte *data;                         /*  Block of data to write           */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_writeh;


int  get_smt_sock_writeh     (byte *_buffer, struct_smt_sock_writeh **params);
void free_smt_sock_writeh    (struct_smt_sock_writeh **params);
int  put_smt_sock_writeh     (byte **_buffer, dbyte timeout, qbyte socket, qbyte size, byte *data, qbyte tag);

#define declare_writeh(_event, _priority)                                    \
    method_declare (agent, "WRITEH", _event, _priority)

/*  Send event - Write huge socket data                                      */

int lsend_writeh (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to write to               */
        qbyte size,                     /*  Amount of data to write          */
        byte *data,                     /*  Block of data to write           */
        qbyte tag);                     /*  User-defined request tag         */

#define send_writeh(_to,                                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    size,                                                    \
                    data,                                                    \
                    tag)                                                     \
       lsend_writeh(_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    NULL, NULL, NULL, 0,                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    size,                                                    \
                    data,                                                    \
                    tag)


#define SMT_SOCK_INPUT "dqq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to wait on                */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_input;


int  get_smt_sock_input      (byte *_buffer, struct_smt_sock_input **params);
void free_smt_sock_input     (struct_smt_sock_input **params);
int  put_smt_sock_input      (byte **_buffer, dbyte timeout, qbyte socket, qbyte tag);

#define declare_input(_event, _priority)                                     \
    method_declare (agent, "INPUT", _event, _priority)

/*  Send event - Wait for input                                              */

int lsend_input (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to wait on                */
        qbyte tag);                     /*  User-defined request tag         */

#define send_input(_to,                                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   tag)                                                      \
       lsend_input(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   timeout,                                                  \
                   socket,                                                   \
                   tag)

#define declare_inputr(_event, _priority)                                    \
    method_declare (agent, "INPUTR", _event, _priority)

/*  Send event - Wait input, repeat                                          */

int lsend_inputr (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to wait on                */
        qbyte tag);                     /*  User-defined request tag         */

#define send_inputr(_to,                                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    tag)                                                     \
       lsend_inputr(_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    NULL, NULL, NULL, 0,                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    tag)


#define SMT_SOCK_OUTPUT "dqq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    qbyte socket;                       /*  Socket to wait on                */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_output;


int  get_smt_sock_output     (byte *_buffer, struct_smt_sock_output **params);
void free_smt_sock_output    (struct_smt_sock_output **params);
int  put_smt_sock_output     (byte **_buffer, dbyte timeout, qbyte socket, qbyte tag);

#define declare_output(_event, _priority)                                    \
    method_declare (agent, "OUTPUT", _event, _priority)

/*  Send event - Wait for output                                             */

int lsend_output (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        qbyte socket,                   /*  Socket to wait on                */
        qbyte tag);                     /*  User-defined request tag         */

#define send_output(_to,                                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    tag)                                                     \
       lsend_output(_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    NULL, NULL, NULL, 0,                                     \
                    timeout,                                                 \
                    socket,                                                  \
                    tag)


#define SMT_SOCK_CONNECT "dsssdqq"

typedef struct {
    dbyte timeout;                      /*  Timeout in seconds, zero = none  */
    char *type;                         /*  Type, UDP or TCP                 */
    char *host;                         /*  Host, name or dotted address, or NULL  */
    char *service;                      /*  Service, as name or port in ASCII, or NULL  */
    dbyte port;                         /*  16-bit host port, or 0           */
    qbyte address;                      /*  32-bit host address, or 0        */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_connect;


int  get_smt_sock_connect    (byte *_buffer, struct_smt_sock_connect **params);
void free_smt_sock_connect   (struct_smt_sock_connect **params);
int  put_smt_sock_connect    (byte **_buffer, dbyte timeout, char *type, char *host, char *service, dbyte port, qbyte address, qbyte tag);

#define declare_connect(_event, _priority)                                   \
    method_declare (agent, "CONNECT", _event, _priority)

/*  Send event - Connect to host                                             */

int lsend_connect (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout in seconds, zero = none  */
        char *type,                     /*  Type, UDP or TCP                 */
        char *host,                     /*  Host, name or dotted address, or NULL  */
        char *service,                  /*  Service, as name or port in ASCII, or NULL  */
        dbyte port,                     /*  16-bit host port, or 0           */
        qbyte address,                  /*  32-bit host address, or 0        */
        qbyte tag);                     /*  User-defined request tag         */

#define send_connect(_to,                                                    \
                     timeout,                                                \
                     type,                                                   \
                     host,                                                   \
                     service,                                                \
                     port,                                                   \
                     address,                                                \
                     tag)                                                    \
       lsend_connect(_to,                                                    \
                     &thread-> queue-> qid,                                  \
                     NULL, NULL, NULL, 0,                                    \
                     timeout,                                                \
                     type,                                                   \
                     host,                                                   \
                     service,                                                \
                     port,                                                   \
                     address,                                                \
                     tag)


#define SMT_SOCK_FLUSH "q"

typedef struct {
    qbyte socket;                       /*  Socket to flush requests for     */
} struct_smt_sock_flush;


int  get_smt_sock_flush      (byte *_buffer, struct_smt_sock_flush **params);
void free_smt_sock_flush     (struct_smt_sock_flush **params);
int  put_smt_sock_flush      (byte **_buffer, qbyte socket);

#define declare_flush(_event, _priority)                                     \
    method_declare (agent, "FLUSH", _event, _priority)

/*  Send event - Flush requests                                              */

int lsend_flush (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket);                  /*  Socket to flush requests for     */

#define send_flush(_to,                                                      \
                   socket)                                                   \
       lsend_flush(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   socket)


#define SMT_SOCK_READ_OK "dqmMq"

typedef struct {
    dbyte timeout;                      /*  Timeout from read request        */
    qbyte socket;                       /*  Socket used for i/o              */
    word  size;                         /*  Amount of data read              */
    byte *data;                         /*  Block of data read               */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_read_ok;


int  get_smt_sock_read_ok    (byte *_buffer, struct_smt_sock_read_ok **params);
void free_smt_sock_read_ok   (struct_smt_sock_read_ok **params);
int  put_smt_sock_read_ok    (byte **_buffer, dbyte timeout, qbyte socket, word  size, byte *data, qbyte tag);

#define declare_sock_read_ok(_event, _priority)                              \
    method_declare (agent, "SOCK_READ_OK", _event, _priority)

/*  Send event - Read OK reply                                               */

int lsend_sock_read_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        word  size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_read_ok(_to,                                               \
                          timeout,                                           \
                          socket,                                            \
                          size,                                              \
                          data,                                              \
                          tag)                                               \
       lsend_sock_read_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          timeout,                                           \
                          socket,                                            \
                          size,                                              \
                          data,                                              \
                          tag)

#define declare_sock_closed(_event, _priority)                               \
    method_declare (agent, "SOCK_CLOSED", _event, _priority)

/*  Send event - Closed reply                                                */

int lsend_sock_closed (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        word  size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_closed(_to,                                                \
                         timeout,                                            \
                         socket,                                             \
                         size,                                               \
                         data,                                               \
                         tag)                                                \
       lsend_sock_closed(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         timeout,                                            \
                         socket,                                             \
                         size,                                               \
                         data,                                               \
                         tag)

#define declare_sock_timeout(_event, _priority)                              \
    method_declare (agent, "SOCK_TIMEOUT", _event, _priority)

/*  Send event - Timeout reply                                               */

int lsend_sock_timeout (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        word  size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_timeout(_to,                                               \
                          timeout,                                           \
                          socket,                                            \
                          size,                                              \
                          data,                                              \
                          tag)                                               \
       lsend_sock_timeout(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          timeout,                                           \
                          socket,                                            \
                          size,                                              \
                          data,                                              \
                          tag)


#define SMT_SOCK_READH_OK "dqhHq"

typedef struct {
    dbyte timeout;                      /*  Timeout from read request        */
    qbyte socket;                       /*  Socket used for i/o              */
    qbyte size;                         /*  Amount of data read              */
    byte *data;                         /*  Block of data read               */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_readh_ok;


int  get_smt_sock_readh_ok   (byte *_buffer, struct_smt_sock_readh_ok **params);
void free_smt_sock_readh_ok  (struct_smt_sock_readh_ok **params);
int  put_smt_sock_readh_ok   (byte **_buffer, dbyte timeout, qbyte socket, qbyte size, byte *data, qbyte tag);

#define declare_sock_readh_ok(_event, _priority)                             \
    method_declare (agent, "SOCK_READH_OK", _event, _priority)

/*  Send event - Read OK reply                                               */

int lsend_sock_readh_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte timeout,                  /*  Timeout from read request        */
        qbyte socket,                   /*  Socket used for i/o              */
        qbyte size,                     /*  Amount of data read              */
        byte *data,                     /*  Block of data read               */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_readh_ok(_to,                                              \
                           timeout,                                          \
                           socket,                                           \
                           size,                                             \
                           data,                                             \
                           tag)                                              \
       lsend_sock_readh_ok(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           timeout,                                          \
                           socket,                                           \
                           size,                                             \
                           data,                                             \
                           tag)


#define SMT_SOCK_OK "qq"

typedef struct {
    qbyte socket;                       /*  Socket used for i/o, or new socket  */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_ok;


int  get_smt_sock_ok         (byte *_buffer, struct_smt_sock_ok **params);
void free_smt_sock_ok        (struct_smt_sock_ok **params);
int  put_smt_sock_ok         (byte **_buffer, qbyte socket, qbyte tag);

#define declare_sock_write_ok(_event, _priority)                             \
    method_declare (agent, "SOCK_WRITE_OK", _event, _priority)

/*  Send event - Write OK reply                                              */

int lsend_sock_write_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_write_ok(_to,                                              \
                           socket,                                           \
                           tag)                                              \
       lsend_sock_write_ok(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           socket,                                           \
                           tag)

#define declare_sock_writeh_ok(_event, _priority)                            \
    method_declare (agent, "SOCK_WRITEH_OK", _event, _priority)

/*  Send event - Write OK reply                                              */

int lsend_sock_writeh_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_writeh_ok(_to,                                             \
                            socket,                                          \
                            tag)                                             \
       lsend_sock_writeh_ok(_to,                                             \
                            &thread-> queue-> qid,                           \
                            NULL, NULL, NULL, 0,                             \
                            socket,                                          \
                            tag)

#define declare_sock_input_ok(_event, _priority)                             \
    method_declare (agent, "SOCK_INPUT_OK", _event, _priority)

/*  Send event - Input OK reply                                              */

int lsend_sock_input_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_input_ok(_to,                                              \
                           socket,                                           \
                           tag)                                              \
       lsend_sock_input_ok(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           socket,                                           \
                           tag)

#define declare_sock_output_ok(_event, _priority)                            \
    method_declare (agent, "SOCK_OUTPUT_OK", _event, _priority)

/*  Send event - Output OK reply                                             */

int lsend_sock_output_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket used for i/o, or new socket  */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_output_ok(_to,                                             \
                            socket,                                          \
                            tag)                                             \
       lsend_sock_output_ok(_to,                                             \
                            &thread-> queue-> qid,                           \
                            NULL, NULL, NULL, 0,                             \
                            socket,                                          \
                            tag)


#define SMT_SOCK_ERROR "sqq"

typedef struct {
    char *message;                      /*  Error message                    */
    qbyte socket;                       /*  Socket for i/o, or new socket    */
    qbyte tag;                          /*  User-defined request tag         */
} struct_smt_sock_error;


int  get_smt_sock_error      (byte *_buffer, struct_smt_sock_error **params);
void free_smt_sock_error     (struct_smt_sock_error **params);
int  put_smt_sock_error      (byte **_buffer, char *message, qbyte socket, qbyte tag);

#define declare_sock_error(_event, _priority)                                \
    method_declare (agent, "SOCK_ERROR", _event, _priority)

/*  Send event - Error reply                                                 */

int lsend_sock_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *message,                  /*  Error message                    */
        qbyte socket,                   /*  Socket for i/o, or new socket    */
        qbyte tag);                     /*  User-defined request tag         */

#define send_sock_error(_to,                                                 \
                        message,                                             \
                        socket,                                              \
                        tag)                                                 \
       lsend_sock_error(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        message,                                             \
                        socket,                                              \
                        tag)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smttime - Timer agent.
 *---------------------------------------------------------------------------*/

#define SMT_TIME_ALARM "qqmM"

typedef struct {
    qbyte days;                         /*  Time/delay in days               */
    qbyte csecs;                        /*  Time/delay in 1/100th seconds    */
    word  tag_size;                     /*  User-defined data size           */
    byte *tag_data;                     /*  User-defined data block          */
} struct_smt_time_alarm;


int  get_smt_time_alarm      (byte *_buffer, struct_smt_time_alarm **params);
void free_smt_time_alarm     (struct_smt_time_alarm **params);
int  put_smt_time_alarm      (byte **_buffer, qbyte days, qbyte csecs, word  tag_size, byte *tag_data);

#define declare_alarm(_event, _priority)                                     \
    method_declare (agent, "ALARM", _event, _priority)

/*  Send event - Ask for single alarm                                        */

int lsend_alarm (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte days,                     /*  Time/delay in days               */
        qbyte csecs,                    /*  Time/delay in 1/100th seconds    */
        word  tag_size,                 /*  User-defined data size           */
        byte *tag_data);                /*  User-defined data block          */

#define send_alarm(_to,                                                      \
                   days,                                                     \
                   csecs,                                                    \
                   tag_size,                                                 \
                   tag_data)                                                 \
       lsend_alarm(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   days,                                                     \
                   csecs,                                                    \
                   tag_size,                                                 \
                   tag_data)


#define SMT_TIME_CLOCK "qqwmM"

typedef struct {
    qbyte days;                         /*  Time/delay in days               */
    qbyte csecs;                        /*  Time/delay in 1/100th seconds    */
    word  cycles;                       /*  Cycle count; zero = forever      */
    word  tag_size;                     /*  User-defined data size           */
    byte *tag_data;                     /*  User-defined data block          */
} struct_smt_time_clock;


int  get_smt_time_clock      (byte *_buffer, struct_smt_time_clock **params);
void free_smt_time_clock     (struct_smt_time_clock **params);
int  put_smt_time_clock      (byte **_buffer, qbyte days, qbyte csecs, word  cycles, word  tag_size, byte *tag_data);

#define declare_clock(_event, _priority)                                     \
    method_declare (agent, "CLOCK", _event, _priority)

/*  Send event - Ask for repeated alarm                                      */

int lsend_clock (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte days,                     /*  Time/delay in days               */
        qbyte csecs,                    /*  Time/delay in 1/100th seconds    */
        word  cycles,                   /*  Cycle count; zero = forever      */
        word  tag_size,                 /*  User-defined data size           */
        byte *tag_data);                /*  User-defined data block          */

#define send_clock(_to,                                                      \
                   days,                                                     \
                   csecs,                                                    \
                   cycles,                                                   \
                   tag_size,                                                 \
                   tag_data)                                                 \
       lsend_clock(_to,                                                      \
                   &thread-> queue-> qid,                                    \
                   NULL, NULL, NULL, 0,                                      \
                   days,                                                     \
                   csecs,                                                    \
                   cycles,                                                   \
                   tag_size,                                                 \
                   tag_data)


#define SMT_TIME_REPLY "mM"

typedef struct {
    word  tag_size;                     /*  User-defined data size           */
    byte *tag_data;                     /*  User-defined data block          */
} struct_smt_time_reply;


int  get_smt_time_reply      (byte *_buffer, struct_smt_time_reply **params);
void free_smt_time_reply     (struct_smt_time_reply **params);
int  put_smt_time_reply      (byte **_buffer, word  tag_size, byte *tag_data);

#define declare_time_reply(_event, _priority)                                \
    method_declare (agent, "TIME_REPLY", _event, _priority)

/*  Send event - Alarm signal                                                */

int lsend_time_reply (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  tag_size,                 /*  User-defined data size           */
        byte *tag_data);                /*  User-defined data block          */

#define send_time_reply(_to,                                                 \
                        tag_size,                                            \
                        tag_data)                                            \
       lsend_time_reply(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        tag_size,                                            \
                        tag_data)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtslot - Time slot agent.
 *---------------------------------------------------------------------------*/

#define SMT_SLOT_SPEC "s"

typedef struct {
    char *specification;                /*  Time slot specification          */
} struct_smt_slot_spec;


int  get_smt_slot_spec       (byte *_buffer, struct_smt_slot_spec **params);
void free_smt_slot_spec      (struct_smt_slot_spec **params);
int  put_smt_slot_spec       (byte **_buffer, char *specification);

#define declare_specify(_event, _priority)                                   \
    method_declare (agent, "SPECIFY", _event, _priority)

/*  Send event - Specify a time slot                                         */

int lsend_specify (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *specification);           /*  Time slot specification          */

#define send_specify(_to,                                                    \
                     specification)                                          \
       lsend_specify(_to,                                                    \
                     &thread-> queue-> qid,                                  \
                     NULL, NULL, NULL, 0,                                    \
                     specification)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smttran - Transfer agent.
 *---------------------------------------------------------------------------*/

#define SMT_TRAN_PUTB "qmMs"

typedef struct {
    qbyte socket;                       /*  Socket for output                */
    word  size;                         /*  Amount of data to send           */
    byte *data;                         /*  Block of data to send            */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_tran_putb;


int  get_smt_tran_putb       (byte *_buffer, struct_smt_tran_putb **params);
void free_smt_tran_putb      (struct_smt_tran_putb **params);
int  put_smt_tran_putb       (byte **_buffer, qbyte socket, word  size, byte *data, char *pipe);

#define declare_put_block(_event, _priority)                                 \
    method_declare (agent, "PUT_BLOCK", _event, _priority)

/*  Send event - Write block to socket                                       */

int lsend_put_block (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        word  size,                     /*  Amount of data to send           */
        byte *data,                     /*  Block of data to send            */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_put_block(_to,                                                  \
                       socket,                                               \
                       size,                                                 \
                       data,                                                 \
                       pipe)                                                 \
       lsend_put_block(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0,                                  \
                       socket,                                               \
                       size,                                                 \
                       data,                                                 \
                       pipe)


#define SMT_TRAN_GETB "qs"

typedef struct {
    qbyte socket;                       /*  Socket for input                 */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_tran_getb;


int  get_smt_tran_getb       (byte *_buffer, struct_smt_tran_getb **params);
void free_smt_tran_getb      (struct_smt_tran_getb **params);
int  put_smt_tran_getb       (byte **_buffer, qbyte socket, char *pipe);

#define declare_get_block(_event, _priority)                                 \
    method_declare (agent, "GET_BLOCK", _event, _priority)

/*  Send event - Read block from socket                                      */

int lsend_get_block (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for input                 */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_get_block(_to,                                                  \
                       socket,                                               \
                       pipe)                                                 \
       lsend_get_block(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0,                                  \
                       socket,                                               \
                       pipe)


#define SMT_TRAN_PUTH "qhHs"

typedef struct {
    qbyte socket;                       /*  Socket for output                */
    qbyte size;                         /*  Amount of data to send           */
    byte *data;                         /*  Block of data to send            */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_tran_puth;


int  get_smt_tran_puth       (byte *_buffer, struct_smt_tran_puth **params);
void free_smt_tran_puth      (struct_smt_tran_puth **params);
int  put_smt_tran_puth       (byte **_buffer, qbyte socket, qbyte size, byte *data, char *pipe);

#define declare_put_huge(_event, _priority)                                  \
    method_declare (agent, "PUT_HUGE", _event, _priority)

/*  Send event - Write huge block to socket                                  */

int lsend_put_huge (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        qbyte size,                     /*  Amount of data to send           */
        byte *data,                     /*  Block of data to send            */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_put_huge(_to,                                                   \
                      socket,                                                \
                      size,                                                  \
                      data,                                                  \
                      pipe)                                                  \
       lsend_put_huge(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      socket,                                                \
                      size,                                                  \
                      data,                                                  \
                      pipe)


#define SMT_TRAN_GETH "qs"

typedef struct {
    qbyte socket;                       /*  Socket for input                 */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_tran_geth;


int  get_smt_tran_geth       (byte *_buffer, struct_smt_tran_geth **params);
void free_smt_tran_geth      (struct_smt_tran_geth **params);
int  put_smt_tran_geth       (byte **_buffer, qbyte socket, char *pipe);

#define declare_get_huge(_event, _priority)                                  \
    method_declare (agent, "GET_HUGE", _event, _priority)

/*  Send event - Read huge block from socket                                 */

int lsend_get_huge (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for input                 */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_get_huge(_to,                                                   \
                      socket,                                                \
                      pipe)                                                  \
       lsend_get_huge(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      socket,                                                \
                      pipe)


#define SMT_TRAN_PUTF "qsdqqs"

typedef struct {
    qbyte socket;                       /*  Socket for output                */
    char *filename;                     /*  Name of file to send             */
    dbyte filetype;                     /*  0=binary, 1=ASCII                */
    qbyte start;                        /*  Starting offset; 0 = start       */
    qbyte end;                          /*  Ending offset; 0 = end           */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_tran_putf;


int  get_smt_tran_putf       (byte *_buffer, struct_smt_tran_putf **params);
void free_smt_tran_putf      (struct_smt_tran_putf **params);
int  put_smt_tran_putf       (byte **_buffer, qbyte socket, char *filename, dbyte filetype, qbyte start, qbyte end, char *pipe);

#define declare_put_file(_event, _priority)                                  \
    method_declare (agent, "PUT_FILE", _event, _priority)

/*  Send event - Write file to socket                                        */

int lsend_put_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for output                */
        char *filename,                 /*  Name of file to send             */
        dbyte filetype,                 /*  0=binary, 1=ASCII                */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end,                      /*  Ending offset; 0 = end           */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_put_file(_to,                                                   \
                      socket,                                                \
                      filename,                                              \
                      filetype,                                              \
                      start,                                                 \
                      end,                                                   \
                      pipe)                                                  \
       lsend_put_file(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      socket,                                                \
                      filename,                                              \
                      filetype,                                              \
                      start,                                                 \
                      end,                                                   \
                      pipe)


#define SMT_TRAN_GETF "qsdqqBqs"

typedef struct {
    qbyte socket;                       /*  Socket for input                 */
    char *filename;                     /*  Name of file to receive          */
    dbyte filetype;                     /*  0=binary, 1=ASCII                */
    qbyte start;                        /*  Starting offset; 0 = start       */
    qbyte end;                          /*  Ending offset; 0 = end           */
    Bool  append;                       /*  1 = append existing              */
    qbyte maxsize;                      /*  Max. size, -1 = no limit         */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_tran_getf;


int  get_smt_tran_getf       (byte *_buffer, struct_smt_tran_getf **params);
void free_smt_tran_getf      (struct_smt_tran_getf **params);
int  put_smt_tran_getf       (byte **_buffer, qbyte socket, char *filename, dbyte filetype, qbyte start, qbyte end, Bool  append, qbyte maxsize, char *pipe);

#define declare_get_file(_event, _priority)                                  \
    method_declare (agent, "GET_FILE", _event, _priority)

/*  Send event - Read file from socket                                       */

int lsend_get_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte socket,                   /*  Socket for input                 */
        char *filename,                 /*  Name of file to receive          */
        dbyte filetype,                 /*  0=binary, 1=ASCII                */
        qbyte start,                    /*  Starting offset; 0 = start       */
        qbyte end,                      /*  Ending offset; 0 = end           */
        Bool  append,                   /*  1 = append existing              */
        qbyte maxsize,                  /*  Max. size, -1 = no limit         */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_get_file(_to,                                                   \
                      socket,                                                \
                      filename,                                              \
                      filetype,                                              \
                      start,                                                 \
                      end,                                                   \
                      append,                                                \
                      maxsize,                                               \
                      pipe)                                                  \
       lsend_get_file(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      socket,                                                \
                      filename,                                              \
                      filetype,                                              \
                      start,                                                 \
                      end,                                                   \
                      append,                                                \
                      maxsize,                                               \
                      pipe)


#define SMT_TRAN_PUTB_OK "d"

typedef struct {
    dbyte size;                         /*  Amount of transmitted data       */
} struct_smt_tran_putb_ok;


int  get_smt_tran_putb_ok    (byte *_buffer, struct_smt_tran_putb_ok **params);
void free_smt_tran_putb_ok   (struct_smt_tran_putb_ok **params);
int  put_smt_tran_putb_ok    (byte **_buffer, dbyte size);

#define declare_tran_putb_ok(_event, _priority)                              \
    method_declare (agent, "TRAN_PUTB_OK", _event, _priority)

/*  Send event - Block written okay                                          */

int lsend_tran_putb_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte size);                    /*  Amount of transmitted data       */

#define send_tran_putb_ok(_to,                                               \
                          size)                                              \
       lsend_tran_putb_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          size)


#define SMT_TRAN_GETB_OK "mM"

typedef struct {
    word  size;                         /*  Amount of data received          */
    byte *data;                         /*  Block of data received           */
} struct_smt_tran_getb_ok;


int  get_smt_tran_getb_ok    (byte *_buffer, struct_smt_tran_getb_ok **params);
void free_smt_tran_getb_ok   (struct_smt_tran_getb_ok **params);
int  put_smt_tran_getb_ok    (byte **_buffer, word  size, byte *data);

#define declare_tran_getb_ok(_event, _priority)                              \
    method_declare (agent, "TRAN_GETB_OK", _event, _priority)

/*  Send event - Block read okay                                             */

int lsend_tran_getb_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        word  size,                     /*  Amount of data received          */
        byte *data);                    /*  Block of data received           */

#define send_tran_getb_ok(_to,                                               \
                          size,                                              \
                          data)                                              \
       lsend_tran_getb_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          size,                                              \
                          data)


#define SMT_TRAN_PUTH_OK "q"

typedef struct {
    qbyte size;                         /*  Amount of transmitted data       */
} struct_smt_tran_puth_ok;


int  get_smt_tran_puth_ok    (byte *_buffer, struct_smt_tran_puth_ok **params);
void free_smt_tran_puth_ok   (struct_smt_tran_puth_ok **params);
int  put_smt_tran_puth_ok    (byte **_buffer, qbyte size);

#define declare_tran_puth_ok(_event, _priority)                              \
    method_declare (agent, "TRAN_PUTH_OK", _event, _priority)

/*  Send event - Block written okay                                          */

int lsend_tran_puth_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Amount of transmitted data       */

#define send_tran_puth_ok(_to,                                               \
                          size)                                              \
       lsend_tran_puth_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          size)


#define SMT_TRAN_GETH_OK "hH"

typedef struct {
    qbyte size;                         /*  Amount of data received          */
    byte *data;                         /*  Block of data received           */
} struct_smt_tran_geth_ok;


int  get_smt_tran_geth_ok    (byte *_buffer, struct_smt_tran_geth_ok **params);
void free_smt_tran_geth_ok   (struct_smt_tran_geth_ok **params);
int  put_smt_tran_geth_ok    (byte **_buffer, qbyte size, byte *data);

#define declare_tran_geth_ok(_event, _priority)                              \
    method_declare (agent, "TRAN_GETH_OK", _event, _priority)

/*  Send event - Block read okay                                             */

int lsend_tran_geth_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size,                     /*  Amount of data received          */
        byte *data);                    /*  Block of data received           */

#define send_tran_geth_ok(_to,                                               \
                          size,                                              \
                          data)                                              \
       lsend_tran_geth_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          size,                                              \
                          data)


#define SMT_TRAN_PUTF_OK "q"

typedef struct {
    qbyte size;                         /*  Amount of transmitted data       */
} struct_smt_tran_putf_ok;


int  get_smt_tran_putf_ok    (byte *_buffer, struct_smt_tran_putf_ok **params);
void free_smt_tran_putf_ok   (struct_smt_tran_putf_ok **params);
int  put_smt_tran_putf_ok    (byte **_buffer, qbyte size);

#define declare_tran_putf_ok(_event, _priority)                              \
    method_declare (agent, "TRAN_PUTF_OK", _event, _priority)

/*  Send event - File written okay                                           */

int lsend_tran_putf_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Amount of transmitted data       */

#define send_tran_putf_ok(_to,                                               \
                          size)                                              \
       lsend_tran_putf_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          size)


#define SMT_TRAN_GETF_OK "q"

typedef struct {
    qbyte size;                         /*  Amount of transmitted data       */
} struct_smt_tran_getf_ok;


int  get_smt_tran_getf_ok    (byte *_buffer, struct_smt_tran_getf_ok **params);
void free_smt_tran_getf_ok   (struct_smt_tran_getf_ok **params);
int  put_smt_tran_getf_ok    (byte **_buffer, qbyte size);

#define declare_tran_getf_ok(_event, _priority)                              \
    method_declare (agent, "TRAN_GETF_OK", _event, _priority)

/*  Send event - File received okay                                          */

int lsend_tran_getf_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte size);                    /*  Amount of transmitted data       */

#define send_tran_getf_ok(_to,                                               \
                          size)                                              \
       lsend_tran_getf_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          size)


#define SMT_PIPE_CREATE "sqq"

typedef struct {
    char *name;                         /*  Name of pipe                     */
    qbyte input_rate;                   /*  Input rate, bytes/s              */
    qbyte output_rate;                  /*  Output rate, bytes/s             */
} struct_smt_pipe_create;


int  get_smt_pipe_create     (byte *_buffer, struct_smt_pipe_create **params);
void free_smt_pipe_create    (struct_smt_pipe_create **params);
int  put_smt_pipe_create     (byte **_buffer, char *name, qbyte input_rate, qbyte output_rate);

#define declare_pipe_create(_event, _priority)                               \
    method_declare (agent, "PIPE_CREATE", _event, _priority)

/*  Send event - Create or modify pipe                                       */

int lsend_pipe_create (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *name,                     /*  Name of pipe                     */
        qbyte input_rate,               /*  Input rate, bytes/s              */
        qbyte output_rate);             /*  Output rate, bytes/s             */

#define send_pipe_create(_to,                                                \
                         name,                                               \
                         input_rate,                                         \
                         output_rate)                                        \
       lsend_pipe_create(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         name,                                               \
                         input_rate,                                         \
                         output_rate)


#define SMT_CLEAR_PIPES ""


#define declare_clear_pipes(_event, _priority)                               \
    method_declare (agent, "CLEAR_PIPES", _event, _priority)

/*  Send event - Delete all pipes                                            */

int lsend_clear_pipes (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_clear_pipes(_to)                                                \
       lsend_clear_pipes(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0)


#define SMT_TRAN_COMMIT ""


#define declare_tran_commit(_event, _priority)                               \
    method_declare (agent, "TRAN_COMMIT", _event, _priority)

/*  Send event - Commit transfer requests                                    */

int lsend_tran_commit (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_tran_commit(_to)                                                \
       lsend_tran_commit(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0)


#define SMT_TRAN_CLOSED ""


#define declare_tran_closed(_event, _priority)                               \
    method_declare (agent, "TRAN_CLOSED", _event, _priority)

/*  Send event - Socket closed or commit done                                */

int lsend_tran_closed (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout);

#define send_tran_closed(_to)                                                \
       lsend_tran_closed(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0)


#define SMT_TRAN_ERROR "s"

typedef struct {
    char *reason;                       /*  Error message                    */
} struct_smt_tran_error;


int  get_smt_tran_error      (byte *_buffer, struct_smt_tran_error **params);
void free_smt_tran_error     (struct_smt_tran_error **params);
int  put_smt_tran_error      (byte **_buffer, char *reason);

#define declare_tran_error(_event, _priority)                                \
    method_declare (agent, "TRAN_ERROR", _event, _priority)

/*  Send event - Socket error                                                */

int lsend_tran_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *reason);                  /*  Error message                    */

#define send_tran_error(_to,                                                 \
                        reason)                                              \
       lsend_tran_error(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        reason)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtftpd - FTP data transfer agent.
 *---------------------------------------------------------------------------*/

#define SMT_FTPD_PUTF "qddsqqds"

typedef struct {
    qbyte id;                           /*  ID for connection                */
    dbyte passive;                      /*  0/1 = active/passive connection  */
    dbyte filetype;                     /*  Type of file to transfer         */
    char *filename;                     /*  Name of file to transfer         */
    qbyte start_position;               /*  Start offset for file            */
    qbyte host_address;                 /*  IP address for host              */
    dbyte port_number;                  /*  Port on remote host              */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_ftpd_putf;


int  get_smt_ftpd_putf       (byte *_buffer, struct_smt_ftpd_putf **params);
void free_smt_ftpd_putf      (struct_smt_ftpd_putf **params);
int  put_smt_ftpd_putf       (byte **_buffer, qbyte id, dbyte passive, dbyte filetype, char *filename, qbyte start_position, qbyte host_address, dbyte port_number, char *pipe);

#define declare_ftpd_put_file(_event, _priority)                             \
    method_declare (agent, "FTPD_PUT_FILE", _event, _priority)

/*  Send event - Send file to host                                           */

int lsend_ftpd_put_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for connection                */
        dbyte passive,                  /*  0/1 = active/passive connection  */
        dbyte filetype,                 /*  Type of file to transfer         */
        char *filename,                 /*  Name of file to transfer         */
        qbyte start_position,           /*  Start offset for file            */
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number,              /*  Port on remote host              */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_ftpd_put_file(_to,                                              \
                           id,                                               \
                           passive,                                          \
                           filetype,                                         \
                           filename,                                         \
                           start_position,                                   \
                           host_address,                                     \
                           port_number,                                      \
                           pipe)                                             \
       lsend_ftpd_put_file(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           id,                                               \
                           passive,                                          \
                           filetype,                                         \
                           filename,                                         \
                           start_position,                                   \
                           host_address,                                     \
                           port_number,                                      \
                           pipe)


#define SMT_FTPD_GETF "qddsqqdqs"

typedef struct {
    qbyte id;                           /*  ID for connection                */
    dbyte passive;                      /*  0/1 = passive/active connection  */
    dbyte filetype;                     /*  Type of file to transfer         */
    char *filename;                     /*  Name of file to transfer         */
    qbyte start_position;               /*  Start offset for file            */
    qbyte host_address;                 /*  IP address for host              */
    dbyte port_number;                  /*  Port on remote host              */
    qbyte maxsize;                      /*  Max. size, -1 = no limit         */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_ftpd_getf;


int  get_smt_ftpd_getf       (byte *_buffer, struct_smt_ftpd_getf **params);
void free_smt_ftpd_getf      (struct_smt_ftpd_getf **params);
int  put_smt_ftpd_getf       (byte **_buffer, qbyte id, dbyte passive, dbyte filetype, char *filename, qbyte start_position, qbyte host_address, dbyte port_number, qbyte maxsize, char *pipe);

#define declare_ftpd_get_file(_event, _priority)                             \
    method_declare (agent, "FTPD_GET_FILE", _event, _priority)

/*  Send event - Receive file from host                                      */

int lsend_ftpd_get_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for connection                */
        dbyte passive,                  /*  0/1 = passive/active connection  */
        dbyte filetype,                 /*  Type of file to transfer         */
        char *filename,                 /*  Name of file to transfer         */
        qbyte start_position,           /*  Start offset for file            */
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number,              /*  Port on remote host              */
        qbyte maxsize,                  /*  Max. size, -1 = no limit         */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_ftpd_get_file(_to,                                              \
                           id,                                               \
                           passive,                                          \
                           filetype,                                         \
                           filename,                                         \
                           start_position,                                   \
                           host_address,                                     \
                           port_number,                                      \
                           maxsize,                                          \
                           pipe)                                             \
       lsend_ftpd_get_file(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           id,                                               \
                           passive,                                          \
                           filetype,                                         \
                           filename,                                         \
                           start_position,                                   \
                           host_address,                                     \
                           port_number,                                      \
                           maxsize,                                          \
                           pipe)


#define SMT_FTPD_APPEND "qddsqdqs"

typedef struct {
    qbyte id;                           /*  ID for connection                */
    dbyte passive;                      /*  0/1 = passive/active connection  */
    dbyte filetype;                     /*  Type of file to transfer         */
    char *filename;                     /*  Name of file to transfer         */
    qbyte host_address;                 /*  IP address for host              */
    dbyte port_number;                  /*  Port on remote host              */
    qbyte maxsize;                      /*  Max. size, -1 = no limit         */
    char *pipe;                         /*  Transfer pipe, if any            */
} struct_smt_ftpd_append;


int  get_smt_ftpd_append     (byte *_buffer, struct_smt_ftpd_append **params);
void free_smt_ftpd_append    (struct_smt_ftpd_append **params);
int  put_smt_ftpd_append     (byte **_buffer, qbyte id, dbyte passive, dbyte filetype, char *filename, qbyte host_address, dbyte port_number, qbyte maxsize, char *pipe);

#define declare_ftpd_append_file(_event, _priority)                          \
    method_declare (agent, "FTPD_APPEND_FILE", _event, _priority)

/*  Send event - Append file from host                                       */

int lsend_ftpd_append_file (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for connection                */
        dbyte passive,                  /*  0/1 = passive/active connection  */
        dbyte filetype,                 /*  Type of file to transfer         */
        char *filename,                 /*  Name of file to transfer         */
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number,              /*  Port on remote host              */
        qbyte maxsize,                  /*  Max. size, -1 = no limit         */
        char *pipe);                    /*  Transfer pipe, if any            */

#define send_ftpd_append_file(_to,                                           \
                              id,                                            \
                              passive,                                       \
                              filetype,                                      \
                              filename,                                      \
                              host_address,                                  \
                              port_number,                                   \
                              maxsize,                                       \
                              pipe)                                          \
       lsend_ftpd_append_file(_to,                                           \
                              &thread-> queue-> qid,                         \
                              NULL, NULL, NULL, 0,                           \
                              id,                                            \
                              passive,                                       \
                              filetype,                                      \
                              filename,                                      \
                              host_address,                                  \
                              port_number,                                   \
                              maxsize,                                       \
                              pipe)


#define SMT_FTPD_PASSIVE "qdq"

typedef struct {
    qbyte id;                           /*  ID for control connection        */
    dbyte first_port;                   /*  First port to listen on          */
    qbyte ip_address;                   /*  IP address to listen on          */
} struct_smt_ftpd_passive;


int  get_smt_ftpd_passive    (byte *_buffer, struct_smt_ftpd_passive **params);
void free_smt_ftpd_passive   (struct_smt_ftpd_passive **params);
int  put_smt_ftpd_passive    (byte **_buffer, qbyte id, dbyte first_port, qbyte ip_address);

#define declare_ftpd_passive(_event, _priority)                              \
    method_declare (agent, "FTPD_PASSIVE", _event, _priority)

/*  Send event - Request passive connection                                  */

int lsend_ftpd_passive (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id,                       /*  ID for control connection        */
        dbyte first_port,               /*  First port to listen on          */
        qbyte ip_address);              /*  IP address to listen on          */

#define send_ftpd_passive(_to,                                               \
                          id,                                                \
                          first_port,                                        \
                          ip_address)                                        \
       lsend_ftpd_passive(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          id,                                                \
                          first_port,                                        \
                          ip_address)


#define SMT_FTPD_ABORT "q"

typedef struct {
    qbyte id;                           /*  ID for control connection        */
} struct_smt_ftpd_abort;


int  get_smt_ftpd_abort      (byte *_buffer, struct_smt_ftpd_abort **params);
void free_smt_ftpd_abort     (struct_smt_ftpd_abort **params);
int  put_smt_ftpd_abort      (byte **_buffer, qbyte id);

#define declare_ftpd_abort(_event, _priority)                                \
    method_declare (agent, "FTPD_ABORT", _event, _priority)

/*  Send event - Abort file transfer                                         */

int lsend_ftpd_abort (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id);                      /*  ID for control connection        */

#define send_ftpd_abort(_to,                                                 \
                        id)                                                  \
       lsend_ftpd_abort(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        id)


#define SMT_FTPD_CLOSECTRL "q"

typedef struct {
    qbyte id;                           /*  ID for control connection        */
} struct_smt_ftpd_closectrl;


int  get_smt_ftpd_closectrl  (byte *_buffer, struct_smt_ftpd_closectrl **params);
void free_smt_ftpd_closectrl  (struct_smt_ftpd_closectrl **params);
int  put_smt_ftpd_closectrl  (byte **_buffer, qbyte id);

#define declare_ftpd_closectrl(_event, _priority)                            \
    method_declare (agent, "FTPD_CLOSECTRL", _event, _priority)

/*  Send event - Close control connection                                    */

int lsend_ftpd_closectrl (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte id);                      /*  ID for control connection        */

#define send_ftpd_closectrl(_to,                                             \
                            id)                                              \
       lsend_ftpd_closectrl(_to,                                             \
                            &thread-> queue-> qid,                           \
                            NULL, NULL, NULL, 0,                             \
                            id)


#define SMT_FTPD_PASS_OK "qd"

typedef struct {
    qbyte host_address;                 /*  IP address for host              */
    dbyte port_number;                  /*  Port on remote host              */
} struct_smt_ftpd_pass_ok;


int  get_smt_ftpd_pass_ok    (byte *_buffer, struct_smt_ftpd_pass_ok **params);
void free_smt_ftpd_pass_ok   (struct_smt_ftpd_pass_ok **params);
int  put_smt_ftpd_pass_ok    (byte **_buffer, qbyte host_address, dbyte port_number);

#define declare_ftpd_pass_ok(_event, _priority)                              \
    method_declare (agent, "FTPD_PASS_OK", _event, _priority)

/*  Send event - Agent request handled ok                                    */

int lsend_ftpd_pass_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte host_address,             /*  IP address for host              */
        dbyte port_number);             /*  Port on remote host              */

#define send_ftpd_pass_ok(_to,                                               \
                          host_address,                                      \
                          port_number)                                       \
       lsend_ftpd_pass_ok(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          host_address,                                      \
                          port_number)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for WSX - WSX agent.
 *---------------------------------------------------------------------------*/

#define SMT_WSX_INSTALL "sss"

typedef struct {
    char *virtual_host;                 /*  Virtual host name                */
    char *path;                         /*  URL pattern to match             */
    char *agent;                        /*  Name of WSX agent                */
} struct_smt_wsx_install;


int  get_smt_wsx_install     (byte *_buffer, struct_smt_wsx_install **params);
void free_smt_wsx_install    (struct_smt_wsx_install **params);
int  put_smt_wsx_install     (byte **_buffer, char *virtual_host, char *path, char *agent);

#define declare_wsx_install(_event, _priority)                               \
    method_declare (agent, "WSX_INSTALL", _event, _priority)

/*  Send event - Install SMT_WSX alias                                       */

int lsend_wsx_install (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *virtual_host,             /*  Virtual host name                */
        char *path,                     /*  URL pattern to match             */
        char *agent);                   /*  Name of WSX agent                */

#define send_wsx_install(_to,                                                \
                         virtual_host,                                       \
                         path,                                               \
                         agent)                                              \
       lsend_wsx_install(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         virtual_host,                                       \
                         path,                                               \
                         agent)


#define SMT_WSX_CANCEL "ss"

typedef struct {
    char *virtual_host;                 /*  Virtual host name                */
    char *path;                         /*  URL pattern to match             */
} struct_smt_wsx_cancel;


int  get_smt_wsx_cancel      (byte *_buffer, struct_smt_wsx_cancel **params);
void free_smt_wsx_cancel     (struct_smt_wsx_cancel **params);
int  put_smt_wsx_cancel      (byte **_buffer, char *virtual_host, char *path);

#define declare_wsx_cancel(_event, _priority)                                \
    method_declare (agent, "WSX_CANCEL", _event, _priority)

/*  Send event - Cancel SMT_WSX alias                                        */

int lsend_wsx_cancel (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *virtual_host,             /*  Virtual host name                */
        char *path);                    /*  URL pattern to match             */

#define send_wsx_cancel(_to,                                                 \
                        virtual_host,                                        \
                        path)                                                \
       lsend_wsx_cancel(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        virtual_host,                                        \
                        path)


#define SMT_WSX_REQUEST "sssssmMmM"

typedef struct {
    char *request_url;                  /*  URL for WSX request              */
    char *arguments;                    /*  URL arguments, if any            */
    char *virtual_host;                 /*  Virtual host, if any             */
    char *filename;                     /*  Physical filename for URL        */
    char *post_data;                    /*  POSTed data, if any              */
    word  symbols_size;                 /*  HTTP symbol table size           */
    byte *symbols_data;                 /*  HTTP symbol table data           */
    word  config_size;                  /*  HTTP config table size           */
    byte *config_data;                  /*  HTTP config table data           */
} struct_smt_wsx_request;

typedef struct_smt_wsx_request WSXREQ;

int  get_smt_wsx_request     (byte *_buffer, struct_smt_wsx_request **params);
void free_smt_wsx_request    (struct_smt_wsx_request **params);
int  put_smt_wsx_request     (byte **_buffer, char *request_url, char *arguments, char *virtual_host, char *filename, char *post_data, word  symbols_size, byte *symbols_data, word  config_size, byte *config_data);

#define declare_wsx_request(_event, _priority)                               \
    method_declare (agent, "WSX_REQUEST", _event, _priority)

/*  Send event - SMT_WSX request                                             */

int lsend_wsx_request (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *request_url,              /*  URL for WSX request              */
        char *arguments,                /*  URL arguments, if any            */
        char *virtual_host,             /*  Virtual host, if any             */
        char *filename,                 /*  Physical filename for URL        */
        char *post_data,                /*  POSTed data, if any              */
        word  symbols_size,             /*  HTTP symbol table size           */
        byte *symbols_data,             /*  HTTP symbol table data           */
        word  config_size,              /*  HTTP config table size           */
        byte *config_data);             /*  HTTP config table data           */

#define send_wsx_request(_to,                                                \
                         request_url,                                        \
                         arguments,                                          \
                         virtual_host,                                       \
                         filename,                                           \
                         post_data,                                          \
                         symbols_size,                                       \
                         symbols_data,                                       \
                         config_size,                                        \
                         config_data)                                        \
       lsend_wsx_request(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         request_url,                                        \
                         arguments,                                          \
                         virtual_host,                                       \
                         filename,                                           \
                         post_data,                                          \
                         symbols_size,                                       \
                         symbols_data,                                       \
                         config_size,                                        \
                         config_data)


#define SMT_WSX_REQBIN "sssmsMmMmM"

typedef struct {
    char *request_url;                  /*  URL for WSX request              */
    char *arguments;                    /*  URL arguments, if any            */
    char *virtual_host;                 /*  Virtual host, if any             */
    word  post_size;                    /*  POSTed data size                 */
    char *filename;                     /*  Physical filename for URL        */
    byte *post_data;                    /*  POSTed data                      */
    word  symbols_size;                 /*  HTTP symbol table size           */
    byte *symbols_data;                 /*  HTTP symbol table data           */
    word  config_size;                  /*  HTTP config table size           */
    byte *config_data;                  /*  HTTP config table data           */
} struct_smt_wsx_reqbin;


int  get_smt_wsx_reqbin      (byte *_buffer, struct_smt_wsx_reqbin **params);
void free_smt_wsx_reqbin     (struct_smt_wsx_reqbin **params);
int  put_smt_wsx_reqbin      (byte **_buffer, char *request_url, char *arguments, char *virtual_host, word  post_size, char *filename, byte *post_data, word  symbols_size, byte *symbols_data, word  config_size, byte *config_data);

#define declare_wsx_reqbin(_event, _priority)                                \
    method_declare (agent, "WSX_REQBIN", _event, _priority)

/*  Send event - SMT_WSX binary request                                      */

int lsend_wsx_reqbin (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *request_url,              /*  URL for WSX request              */
        char *arguments,                /*  URL arguments, if any            */
        char *virtual_host,             /*  Virtual host, if any             */
        word  post_size,                /*  POSTed data size                 */
        char *filename,                 /*  Physical filename for URL        */
        byte *post_data,                /*  POSTed data                      */
        word  symbols_size,             /*  HTTP symbol table size           */
        byte *symbols_data,             /*  HTTP symbol table data           */
        word  config_size,              /*  HTTP config table size           */
        byte *config_data);             /*  HTTP config table data           */

#define send_wsx_reqbin(_to,                                                 \
                        request_url,                                         \
                        arguments,                                           \
                        virtual_host,                                        \
                        post_size,                                           \
                        filename,                                            \
                        post_data,                                           \
                        symbols_size,                                        \
                        symbols_data,                                        \
                        config_size,                                         \
                        config_data)                                         \
       lsend_wsx_reqbin(_to,                                                 \
                        &thread-> queue-> qid,                               \
                        NULL, NULL, NULL, 0,                                 \
                        request_url,                                         \
                        arguments,                                           \
                        virtual_host,                                        \
                        post_size,                                           \
                        filename,                                            \
                        post_data,                                           \
                        symbols_size,                                        \
                        symbols_data,                                        \
                        config_size,                                         \
                        config_data)


#define SMT_WSX_OK "s"

typedef struct {
    char *html_data;                    /*  HTML response data               */
} struct_smt_wsx_ok;


int  get_smt_wsx_ok          (byte *_buffer, struct_smt_wsx_ok **params);
void free_smt_wsx_ok         (struct_smt_wsx_ok **params);
int  put_smt_wsx_ok          (byte **_buffer, char *html_data);

#define declare_wsx_ok(_event, _priority)                                    \
    method_declare (agent, "WSX_OK", _event, _priority)

/*  Send event - Agent request handled ok                                    */

int lsend_wsx_ok (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data);               /*  HTML response data               */

#define send_wsx_ok(_to,                                                     \
                    html_data)                                               \
       lsend_wsx_ok(_to,                                                     \
                    &thread-> queue-> qid,                                   \
                    NULL, NULL, NULL, 0,                                     \
                    html_data)


#define SMT_WSX_BIN "hM"

typedef struct {
    qbyte html_size;                    /*  HTML response size               */
    byte *html_data;                    /*  HTML response data               */
} struct_smt_wsx_bin;


int  get_smt_wsx_bin         (byte *_buffer, struct_smt_wsx_bin **params);
void free_smt_wsx_bin        (struct_smt_wsx_bin **params);
int  put_smt_wsx_bin         (byte **_buffer, qbyte html_size, byte *html_data);

#define declare_wsx_bin(_event, _priority)                                   \
    method_declare (agent, "WSX_BIN", _event, _priority)

/*  Send event - Agent request handled ok                                    */

int lsend_wsx_bin (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte html_size,                /*  HTML response size               */
        byte *html_data);               /*  HTML response data               */

#define send_wsx_bin(_to,                                                    \
                     html_size,                                              \
                     html_data)                                              \
       lsend_wsx_bin(_to,                                                    \
                     &thread-> queue-> qid,                                  \
                     NULL, NULL, NULL, 0,                                    \
                     html_size,                                              \
                     html_data)


#define SMT_WSX_MULTIPART "s"

typedef struct {
    char *html_data;                    /*  HTML response data               */
} struct_smt_wsx_multipart;


int  get_smt_wsx_multipart   (byte *_buffer, struct_smt_wsx_multipart **params);
void free_smt_wsx_multipart  (struct_smt_wsx_multipart **params);
int  put_smt_wsx_multipart   (byte **_buffer, char *html_data);

#define declare_wsx_multipart(_event, _priority)                             \
    method_declare (agent, "WSX_MULTIPART", _event, _priority)

/*  Send event - Agent multipart response                                    */

int lsend_wsx_multipart (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data);               /*  HTML response data               */

#define send_wsx_multipart(_to,                                              \
                           html_data)                                        \
       lsend_wsx_multipart(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           html_data)


#define SMT_WSX_MBIN "hM"

typedef struct {
    qbyte html_size;                    /*  HTML response size               */
    byte *html_data;                    /*  HTML response data               */
} struct_smt_wsx_mbin;


int  get_smt_wsx_mbin        (byte *_buffer, struct_smt_wsx_mbin **params);
void free_smt_wsx_mbin       (struct_smt_wsx_mbin **params);
int  put_smt_wsx_mbin        (byte **_buffer, qbyte html_size, byte *html_data);

#define declare_wsx_mbin(_event, _priority)                                  \
    method_declare (agent, "WSX_MBIN", _event, _priority)

/*  Send event - Agent multipart response                                    */

int lsend_wsx_mbin (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte html_size,                /*  HTML response size               */
        byte *html_data);               /*  HTML response data               */

#define send_wsx_mbin(_to,                                                   \
                      html_size,                                             \
                      html_data)                                             \
       lsend_wsx_mbin(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      html_size,                                             \
                      html_data)


#define SMT_WSX_RESTART "s"

typedef struct {
    char *html_data;                    /*  HTML response data               */
} struct_smt_wsx_restart;


int  get_smt_wsx_restart     (byte *_buffer, struct_smt_wsx_restart **params);
void free_smt_wsx_restart    (struct_smt_wsx_restart **params);
int  put_smt_wsx_restart     (byte **_buffer, char *html_data);

#define declare_wsx_restart(_event, _priority)                               \
    method_declare (agent, "WSX_RESTART", _event, _priority)

/*  Send event - Agent requested restart                                     */

int lsend_wsx_restart (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data);               /*  HTML response data               */

#define send_wsx_restart(_to,                                                \
                         html_data)                                          \
       lsend_wsx_restart(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         html_data)


#define SMT_WSX_KILL "s"

typedef struct {
    char *html_data;                    /*  HTML response data               */
} struct_smt_wsx_kill;


int  get_smt_wsx_kill        (byte *_buffer, struct_smt_wsx_kill **params);
void free_smt_wsx_kill       (struct_smt_wsx_kill **params);
int  put_smt_wsx_kill        (byte **_buffer, char *html_data);

#define declare_wsx_kill(_event, _priority)                                  \
    method_declare (agent, "WSX_KILL", _event, _priority)

/*  Send event - Agent requested shutdown                                    */

int lsend_wsx_kill (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *html_data);               /*  HTML response data               */

#define send_wsx_kill(_to,                                                   \
                      html_data)                                             \
       lsend_wsx_kill(_to,                                                   \
                      &thread-> queue-> qid,                                 \
                      NULL, NULL, NULL, 0,                                   \
                      html_data)


#define SMT_WSX_ERROR "d"

typedef struct {
    dbyte error_code;                   /*  HTTP response code               */
} struct_smt_wsx_error;


int  get_smt_wsx_error       (byte *_buffer, struct_smt_wsx_error **params);
void free_smt_wsx_error      (struct_smt_wsx_error **params);
int  put_smt_wsx_error       (byte **_buffer, dbyte error_code);

#define declare_wsx_error(_event, _priority)                                 \
    method_declare (agent, "WSX_ERROR", _event, _priority)

/*  Send event - Agent request failed                                        */

int lsend_wsx_error (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        dbyte error_code);              /*  HTTP response code               */

#define send_wsx_error(_to,                                                  \
                       error_code)                                           \
       lsend_wsx_error(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0,                                  \
                       error_code)


#define SMT_WSX_REDIRECT "s"

typedef struct {
    char *new_url;                      /*  Redirect location                */
} struct_smt_wsx_redirect;


int  get_smt_wsx_redirect    (byte *_buffer, struct_smt_wsx_redirect **params);
void free_smt_wsx_redirect   (struct_smt_wsx_redirect **params);
int  put_smt_wsx_redirect    (byte **_buffer, char *new_url);

#define declare_wsx_redirect(_event, _priority)                              \
    method_declare (agent, "WSX_REDIRECT", _event, _priority)

/*  Send event - Agent redirected request                                    */

int lsend_wsx_redirect (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *new_url);                 /*  Redirect location                */

#define send_wsx_redirect(_to,                                               \
                          new_url)                                           \
       lsend_wsx_redirect(_to,                                               \
                          &thread-> queue-> qid,                             \
                          NULL, NULL, NULL, 0,                               \
                          new_url)


/*---------------------------------------------------------------------------
 *  Definitions and prototypes for smtrdns - Reverse DNS agent.
 *---------------------------------------------------------------------------*/

#define SMT_GET_HOST_NAME "qsq"

typedef struct {
    qbyte ip_address;                   /*  IP address in network order      */
    char *ip_string;                    /*  Alternative address in string format  */
    qbyte request_tag;                  /*  User-defined request tag         */
} struct_smt_get_host_name;


int  get_smt_get_host_name   (byte *_buffer, struct_smt_get_host_name **params);
void free_smt_get_host_name  (struct_smt_get_host_name **params);
int  put_smt_get_host_name   (byte **_buffer, qbyte ip_address, char *ip_string, qbyte request_tag);

#define declare_get_host_name(_event, _priority)                             \
    method_declare (agent, "GET_HOST_NAME", _event, _priority)

/*  Send event - Get host name for address                                   */

int lsend_get_host_name (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte ip_address,               /*  IP address in network order      */
        char *ip_string,                /*  Alternative address in string format  */
        qbyte request_tag);             /*  User-defined request tag         */

#define send_get_host_name(_to,                                              \
                           ip_address,                                       \
                           ip_string,                                        \
                           request_tag)                                      \
       lsend_get_host_name(_to,                                              \
                           &thread-> queue-> qid,                            \
                           NULL, NULL, NULL, 0,                              \
                           ip_address,                                       \
                           ip_string,                                        \
                           request_tag)


#define SMT_GET_HOST_IP "sq"

typedef struct {
    char *host_name;                    /*  Host name to look-up             */
    qbyte request_tag;                  /*  User-defined request tag         */
} struct_smt_get_host_ip;


int  get_smt_get_host_ip     (byte *_buffer, struct_smt_get_host_ip **params);
void free_smt_get_host_ip    (struct_smt_get_host_ip **params);
int  put_smt_get_host_ip     (byte **_buffer, char *host_name, qbyte request_tag);

#define declare_get_host_ip(_event, _priority)                               \
    method_declare (agent, "GET_HOST_IP", _event, _priority)

/*  Send event - Get host address for name                                   */

int lsend_get_host_ip (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        char *host_name,                /*  Host name to look-up             */
        qbyte request_tag);             /*  User-defined request tag         */

#define send_get_host_ip(_to,                                                \
                         host_name,                                          \
                         request_tag)                                        \
       lsend_get_host_ip(_to,                                                \
                         &thread-> queue-> qid,                              \
                         NULL, NULL, NULL, 0,                                \
                         host_name,                                          \
                         request_tag)


#define SMT_HOST_NAME "qsq"

typedef struct {
    qbyte ip_address;                   /*  IP address in network order      */
    char *host_name;                    /*  Host name                        */
    qbyte request_tag;                  /*  User-defined request tag         */
} struct_smt_host_name;


int  get_smt_host_name       (byte *_buffer, struct_smt_host_name **params);
void free_smt_host_name      (struct_smt_host_name **params);
int  put_smt_host_name       (byte **_buffer, qbyte ip_address, char *host_name, qbyte request_tag);

#define declare_host_name(_event, _priority)                                 \
    method_declare (agent, "HOST_NAME", _event, _priority)

/*  Send event - Return host name                                            */

int lsend_host_name (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte ip_address,               /*  IP address in network order      */
        char *host_name,                /*  Host name                        */
        qbyte request_tag);             /*  User-defined request tag         */

#define send_host_name(_to,                                                  \
                       ip_address,                                           \
                       host_name,                                            \
                       request_tag)                                          \
       lsend_host_name(_to,                                                  \
                       &thread-> queue-> qid,                                \
                       NULL, NULL, NULL, 0,                                  \
                       ip_address,                                           \
                       host_name,                                            \
                       request_tag)


#define SMT_HOST_IP "qsq"

typedef struct {
    qbyte ip_address;                   /*  IP address in network order      */
    char *host_name;                    /*  Host name                        */
    qbyte request_tag;                  /*  User-defined request tag         */
} struct_smt_host_ip;


int  get_smt_host_ip         (byte *_buffer, struct_smt_host_ip **params);
void free_smt_host_ip        (struct_smt_host_ip **params);
int  put_smt_host_ip         (byte **_buffer, qbyte ip_address, char *host_name, qbyte request_tag);

#define declare_host_ip(_event, _priority)                                   \
    method_declare (agent, "HOST_IP", _event, _priority)

/*  Send event - Return host IP address                                      */

int lsend_host_ip (QID *_to, QID *_from,
        char *_accept,
        char *_reject,
        char *_expire,
        word _timeout,
        qbyte ip_address,               /*  IP address in network order      */
        char *host_name,                /*  Host name                        */
        qbyte request_tag);             /*  User-defined request tag         */

#define send_host_ip(_to,                                                    \
                     ip_address,                                             \
                     host_name,                                              \
                     request_tag)                                            \
       lsend_host_ip(_to,                                                    \
                     &thread-> queue-> qid,                                  \
                     NULL, NULL, NULL, 0,                                    \
                     ip_address,                                             \
                     host_name,                                              \
                     request_tag)



#endif                                  /*  Included                         */

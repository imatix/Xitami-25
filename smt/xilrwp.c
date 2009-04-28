/*===========================================================================*
 *                                                                           *
 *  xilrwp.c -                                                               *
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

#include "smtdefn.h"                    /*  SMT Agent Definitions            */
#include "smthttpl.h"                   /*  SMT HTTP library                 */

#include "xilrwp.h"                     /* LWRP definitions, etc.            */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME          LRWP_NAME

#define LRWP_REQUEST        "LRWP_REQUEST"
#define LRWP_PEERCLOSED     "LRWP_PEERCLOSED"
#define LRWP_JOBCOMP        "LRWP_JOBCOMP"

#define WSX_REQUEST         "WSX_REQUEST"


#define _MASTER             "_MASTER"
#define _PEER               "_PEER"
#define _ROUTER             "_ROUTER"

#define CHALLENGE_LENGTH    32          /* LRWP 2.0 auth challenge           */
#define LRWP_STRING_DELIM      "\xFF"   /* Delimiter as string; to send      */
#define LRWP_STRING_DELIM_CHAR '\xFF'   /* Delimiter as char; to search for  */

#define MAX_APPNAME_LEN     200         /* XXX: Arbitrary values--rationalise*/
#define MAX_VHOST_LEN       200
#define BIG_RESPONSE_LEN    16384       /* Below this, keep in memory        */
#define SEND_BUF_LEN        8192        /* Peer send buffer size             */

#define LENGTH_LEN          9           /* Digits in length val to/from peer */
#define LENGTH_FORMAT       "%09d"      /* sprintf() arg to build length     */
#define LENGTH_FORMAT_LONG  "%09ld"     /* above for int; this for long      */

#define TEMP_FILE_UMASK     0600        /* Access permissions (for open())   */
/*---------------------------------------------------------------------------*/

typedef struct {
    char*   name;
    char*   vhost;
    NODE    peerList;                   /* A list of PTCB's                  */
    NODE    waitingRequests;            /* A list of REQ's                   */
} RTRData;


typedef struct {                        /* Peer Thread control block         */
    void    *next, *prev;
    THREAD* thread;
    int     busy;
} PTCB;

typedef struct {                        /* Waiting requests                  */
    void    *next, *prev;
    WSXREQ* wsxreq;
    QID     replyQ;
} REQ;

typedef struct {                        /*  Thread context block:            */
    /* all types use this */
    int         thread_type;

    /* master and peers */
    sock_t      handle;

    /* peers only */
    int         proto_major;            /*  LRWP Protocol 1.0, 2.0, etc      */
    int         proto_minor;
    char*       appName;                /*  LRWP connection details          */
    char*       vhost;
    char*       filterExt;
    byte        challenge[CHALLENGE_LENGTH];  /*  LRWP 2.0 auth challenge    */
    const char* startupError;           /*  Pointer to startup error (if any)*/
    char*       sockError;              /*  Copy of socket error msg         */

    PTCB*       ptcb;
    RTRData*    rtr;
    QID         replyQ;
    char        sizebuff[LENGTH_LEN + 1];
    size_t      numtoread;
    size_t      numread;
    char*       buffer;
    int         filehandle;

    /* router only */
    Bool        termWhenEmpty;
} LRWP_TCB;


/*- Function prototypes -----------------------------------------------------*/

static char* makeTableKey         (char* name, char* vhost);
static void  sendPeerErrorMessage (int handle, const char *errorMessage, 
                                   int lrwpVer);
static char* makeLRWPAppKey       (char* appName);
static char* maketempname         ();
static int   write_TCP_or_error   (int handle, char *buffer, int buflen);
static Bool is_valid_number       (const char *numstr);


/*- Global variables used in this source file only --------------------------*/

static LRWP_TCB  *tcb;                   /*  Address thread context block    */
#define TCB     LRWP_TCB

static QID  operq,                       /*  Operator console event queue    */
            /*logq, */                   /*  Logging agent event queue       */
            sockq,                       /*  Socket agent event queue        */
            tranq;                       /*  Transfer Agent                  */

static SYMTAB*  peerTable = NULL;
static THREAD*  rtrThread;
static THREAD*  http_thread;

static Bool     round_robin;             /*  If true, peers used in round    */
                                         /*  robin fashion; otherwise favour */
                                         /*  first peer (better locality)    */
                                         /*  Set from [LRWP] round-robin     */

static char     databuf[SEND_BUF_LEN];   /*  Buffer for assembling data to   */
                                         /*  send to peer; used only within  */
                                         /*  functions -- not required       */
                                         /*  between functions.              */

#include "xilrwp.d"                      /*  Include dialog data             */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int xilrwp_init (void)
{
    THREAD  *thread;
    AGENT   *agent;                     /*  Handle for our agent             */
    char    *config_round_robin;
#   include "xilrwp.i"                  /*  Include dialog interpreter       */

    /*  Change any of the agent properties that you need to                  */
    agent->router      = FALSE;         /*  FALSE = default                  */
    agent->max_threads = 0;             /*  0 = default                      */

    /*                      Method name     Event value      Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare(agent, "SHUTDOWN",       shutdown_event,  SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare(agent, "SOCK_INPUT_OK",  sock_input_ok_event,       0);
    method_declare(agent, "SOCK_CLOSED",    sock_closed_event,         0);
    method_declare(agent, "SOCK_ERROR",     sock_error_event,          0);
    method_declare(agent, "SOCK_TIMEOUT",   sock_error_event,          0);
    method_declare(agent, "SOCK_WRITE_OK",  sock_write_ok_event,       0);
    method_declare(agent, "TRAN_PUTF_OK",   sock_write_ok_event,       0);
    method_declare(agent, "TRAN_CLOSED",    sock_closed_event,         0);
    method_declare(agent, "TRAN_ERROR",     sock_error_event,          0);

    /*  Private methods used to pump the initial thread events               */
    method_declare(agent, _MASTER,          master_event,   0);
    method_declare(agent, _PEER,            peer_event,     0);
    method_declare(agent, _ROUTER,          router_event,   0);

    /* other methods this agent supports                                     */
    method_declare(agent, WSX_REQUEST,      wsx_request_event,          0);
    method_declare(agent, LRWP_REQUEST,     lrwp_request_event,         0);
    method_declare(agent, LRWP_PEERCLOSED,  peer_closed_event,          0);
    method_declare(agent, LRWP_JOBCOMP,     peer_job_completed_event,   0);


    /*  Ensure that operator console is running, else start it up            */
    smtoper_init();
    if ((thread = thread_lookup(SMT_OPERATOR, "")) != NULL)
        operq = thread->queue->qid;
    else
        return(-1);

    /*  Ensure that socket agent is running, else start it up                */
    smtsock_init();
    if ((thread = thread_lookup(SMT_SOCKET, "")) != NULL)
        sockq = thread->queue->qid;
    else
        return(-1);

    /*  Ensure that transfer agent is running, else start it up              */
    smttran_init();
    if ((thread = thread_lookup(SMT_TRANSFER, "")) != NULL)
        tranq = thread->queue->qid;
    else
        return(-1);

    /*  Create initial thread to manage listening socket port                */
    if ((thread = thread_create(AGENT_NAME, "")) != NULL) {
        SEND(&thread->queue->qid, _MASTER, "");  /* pump the first event     */
        ((TCB *)thread->tcb)->thread_type = master_event;
        ((TCB *)thread->tcb)->handle      = 0;
      }
    else
        return (-1);

    /*  Create thread to act as the request router, and to respond to the WSX
        messages */
    if ((rtrThread = thread_create(AGENT_NAME, "main")) != NULL) {
        SEND(&rtrThread->queue->qid, _ROUTER, "");  /* pump the first event   */
        ((TCB *)rtrThread->tcb)->thread_type = router_event;
        ((TCB *)rtrThread->tcb)->handle      = 0;
      }
    else
        return (-1);

    config_round_robin = http_config(config, "lrwp:round-robin");
    if (config_round_robin != NULL && *config_round_robin == '1') 
        round_robin = TRUE;
    else
        round_robin = FALSE;

    /*  Signal to caller that we initialised okay */
    return(0);
}

/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    /* Default initialise TCB structure: but first event pumped in           */
    tcb = thread->tcb;                 /*  Point to thread's context         */

    /* For peer threads                                                      */
    tcb->proto_major  = tcb->proto_minor = 0;
    tcb->appName      = tcb->vhost       = tcb->filterExt = NULL;
    tcb->numtoread    = tcb->numread     = 0;
    tcb->sockError    = NULL;
    tcb->startupError = NULL;
    tcb->buffer       = NULL;
    tcb->filehandle   = NULL_HANDLE;
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */
    switch (tcb->thread_type) {
        case master_event:
            if (tcb->handle)
                close_socket(tcb->handle);
            break;

        case peer_event:
            if (tcb->handle != INVALID_SOCKET)
                close_socket(tcb->handle);

            if (tcb->filehandle >= 0)
                close(tcb->filehandle);

            if (tcb->ptcb)
                node_destroy(tcb->ptcb);
            if (tcb->rtr)
                SEND(&rtrThread->queue->qid, LRWP_PEERCLOSED,
                        makeTableKey(tcb->rtr->name, tcb->rtr->vhost));
            if (tcb->appName)
                mem_free(tcb->appName);
            if (tcb->vhost)
                mem_free(tcb->vhost);
            if (tcb->filterExt)
                mem_free(tcb->filterExt);

            ASSERT(! tcb->buffer);
            if (tcb->buffer)
                mem_free(tcb->buffer);

            break;

        case router_event:
            if (peerTable) {
                tcb->termWhenEmpty = TRUE;
                return;       /* bail out here so thread won't terminate yet */
            }
            break;
    }

    the_next_event = terminate_event;
}



/***************************   OPEN MASTER SOCKET   **************************/

MODULE open_master_socket (THREAD *thread)
{
    int     port;
    char*   cPort;

    tcb = thread->tcb;                 /*  Point to thread's context         */

    cPort = http_config(config, "lrwp:port");
    if (!cPort || !*cPort)             /*  Use default port if not set       */
        cPort = LRWP_PORT;
    port = atoi(cPort) + ip_portbase;
    tcb->handle = passive_TCP(cPort, 5);
    if (tcb->handle == INVALID_SOCKET) {
        sendfmt(&operq, "ERROR",
                LRWP_NAME ": Could not open LRWP port %d", port);
        sendfmt(&operq, "ERROR", connect_errlist[connect_error()]);
        raise_exception(fatal_event);
    }
    else {
        sendfmt(&operq, "INFO",
                 LRWP_NAME ": ready for LRWP connections on port %d", port);
    }

    /* We'll need the main thread in HTTP agent later... */
    http_thread = thread_lookup (SMT_HTTP, "main");
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */

    if (the_next_event != sock_closed_event)
        send_input(&sockq, 0, tcb->handle, 0);
}

/******************************   SETUP ROUTER   *****************************/

MODULE setup_router (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */
    tcb->termWhenEmpty = FALSE;
}

/************************   ACCEPT PEER CONNECTION   ***********************/

MODULE accept_peer_connection (THREAD *thread)
{
    sock_t  slave_socket;              /*  Connected socket                  */
    THREAD  *peer_thread;              /*  Handle to child threads           */

    tcb = thread->tcb;                 /*  Point to thread's context         */

    slave_socket = accept_socket(tcb->handle);
    if (slave_socket != INVALID_SOCKET) {
        peer_thread = thread_create(AGENT_NAME, "");
        if (peer_thread) {
            SEND(&peer_thread->queue->qid, _PEER, "");
            ((TCB *)peer_thread->tcb)->thread_type = peer_event;
            ((TCB *)peer_thread->tcb)->handle      = slave_socket;
            ((TCB *)peer_thread->tcb)->ptcb        = NULL;
            ((TCB *)peer_thread->tcb)->rtr         = NULL;

            socket_nodelay(slave_socket);  /* Disable Nagle's algorithm      */
        }
        else {
            sendfmt(&operq, "ERROR",
                     LRWP_NAME ": could not create new thread");
            raise_exception(exception_event);
        }
    }
    else if (sockerrno != EAGAIN && sockerrno != EWOULDBLOCK) {
        sendfmt(&operq, "ERROR",
                 LRWP_NAME ": could not accept connection: %s", sockmsg());
        raise_exception(exception_event);
    }
    else {
        sendfmt(&operq, "ERROR",
                 LRWP_NAME ": got EAGAIN accepting new connection: %s", 
                 sockmsg());
        raise_exception(exception_event);
    }
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */

    if (tcb->sockError) {
        sendfmt(&operq, "ERROR",
                LRWP_NAME ": error on socket: %s", tcb->sockError);

        mem_strfree(&tcb->sockError);
    }
    else {
        /* NOTE: may be a race here between whatever causes the error,
         * and actually retreiving it to print out.  Where possible
         * should save error into tcb->sockError.
         */
        sendfmt(&operq, "ERROR",
                LRWP_NAME ": error on socket: %s", sockmsg());
    }
}


/************************   SHUTDOWN THE APPLICATION   ***********************/

MODULE shutdown_the_application (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */
    smt_shutdown();                    /*  Halt the application              */
}


/*********************   READ APP CONNECTION REQUEST     *********************/

/*  Build string "name:vhost" for indexing LRWP peer tables                  */
/*  If strings will not fit, returns NULL (caller should check this first)   */
static char* makeTableKey(char* name, char* vhost)
{
#define MAX_TABLEKEY_LEN  (MAX_APPNAME_LEN + MAX_VHOST_LEN + 2)

    static char tablekey[MAX_TABLEKEY_LEN];

    vhost = ((vhost && *vhost) ? vhost : VHOST_ANY);

    ASSERT(name  && strlen(name) <= MAX_APPNAME_LEN);
    ASSERT(vhost && strlen(vhost) <= MAX_VHOST_LEN);

    if ((strlen(name) + strlen(vhost) + 2) > MAX_TABLEKEY_LEN)
        return NULL;                             /*  Won't fit!              */

    sprintf(tablekey, "%s:%s", vhost, name);
    return tablekey;
}

/*  Build string "lrwp-application:name" for readind configuration           */
/*  If strings will not fit, returns NULL (caller should check this first)   */
static char* makeLRWPAppKey(char* appName)
{
#define LRWP_APP_PREFIX       "lrwp-application"
#define LRWP_APP_PREFIX_LEN   16
#define MAX_APPKEY_LEN        (MAX_APPNAME_LEN + LRWP_APP_PREFIX_LEN + 2)

    static char appkey[MAX_APPKEY_LEN];
    char *ptr;

    ASSERT(strlen(LRWP_APP_PREFIX) == LRWP_APP_PREFIX_LEN);
    ASSERT(appName && strlen(appName) <= MAX_APPNAME_LEN);

    if ((LRWP_APP_PREFIX_LEN + 2 + strlen(appName)) > MAX_APPKEY_LEN)
        return NULL;                             /*  Won't fit!              */

    sprintf(appkey, LRWP_APP_PREFIX ":%s", appName);

    /* Force it all into lower case, to match lower case in config tables */
    for (ptr = appkey; *ptr; ++ptr) {
        if (isupper(*ptr))
            *ptr = tolower(*ptr);
    }

    return appkey;
}

MODULE read_app_connection_request (THREAD *thread)
{
    int         num;
    char        buff[LRWP_MAXSTARTUP];
    char*       webmask;
    char*       access;
    char*       appName     = NULL;
    char*       vhost       = NULL;
    char*       filterExt   = NULL;
    int         proto_major = 0;
    int         proto_minor = 0;

    /* Error messages that may be used with LRWP1 should be prefixed
     * with ERROR: for backwards compatibility.  LRWP2 messages can
     * simply state the text of the message.
     */
    const char* errUnrecognisedVersion = "ERROR: Unknown LRWP version";
    const char* errLRWP1Malformed      = "ERROR: Malformed startup string";
    const char* errLRWP2Malformed      = "Malformed LRWP2 connection string";
    const char* errUnauthorised        = "ERROR: Unauthorized access";
    const char* errNeedAuth            = 
                "ERROR: Connection requires LRWP2 authentication";
    const char* errExcluded            = "ERROR: Application not permitted";
    const char* errComponentTooLong    = 
                "ERROR: Registration component too long";
    const char* errResourcesExhausted  = "ERROR: Out of resources";

    tcb = thread->tcb;                 /*  Point to thread's context         */

    /* Read in peer connection string */
    /* NOTE: We assume that this arrives in a single packet, which may
     * be a somewhat dangerous assumption given its length, but effectively
     * required by LRWP1 protocol.
     */
    
    /* LRWP connection request contains:
     *   LRWP 1.0: applicationname 0xFF virtualhostname 0xFF filterext [0xFF]
     *   LRWP 2.0: 0xFF proto_major "." proto_minor 0xFF applicationname
     *             0xFF virtualhostname 0xFF
     *
     * We detect the protocol version by the initial 0xFF character (2.0 or
     * higher).
     */
    num = read_TCP(tcb->handle, buff, LRWP_MAXSTARTUP);

    if (num == SOCKET_ERROR) {
        if (sockerrno == EPIPE || sockerrno == ECONNRESET) {
            the_next_event = sock_closed_event;
            return;
        }
        else {
            ASSERT(sockerrno != EAGAIN && sockerrno != EWOULDBLOCK);

            tcb->sockError = mem_strdup(sockmsg());
            raise_exception(sock_error_event);
            return;
        }
    }

    if (num < LRWP_MAXSTARTUP)             /* make sure it is NUL terminated */
        *(buff+num) = '\0';         
    else
        *(buff+LRWP_MAXSTARTUP-1) = '\0';

    /* Determine version of peer LRWP protocol */
    if (*buff == LRWP_STRING_DELIM_CHAR) {
        /* LRWP 2.0 or higher: parse version number: x.y
         * NOTE: assumes numbers are sequential in character set, which
         * is safe for all character sets I'm currently aware of (EDM)
         */
        if (isdigit(buff[1]) && buff[2] == '.' && isdigit(buff[3]) &&
            buff[4] == LRWP_STRING_DELIM_CHAR) {
            proto_major = (buff[1] - '0');
            proto_minor = (buff[3] - '0');
        }
        else {
            tcb->startupError = errLRWP1Malformed;
            the_next_event = startup_error_event;
            return;
        }
    }
    else {
        /* LRWP 1.0, by default */
        proto_major = 1; 
        proto_minor = 0;
    }

    /* parse out the components of the startup string, depending on version  */

    /* NOTE: If start up string changes, major version of protocol should  
     * change; so we assume that we can parse if major version matches.
     */
    if (proto_major == 2) {
        /* parse: 0xFF proto_major "." proto_minor 0xFF applicationname
         *        0xFF virtualhostname 0xFF
         */
        char *lastdelim = NULL;        /*  Position of last deliminter       */

        ASSERT (vhost == NULL && filterExt == NULL);

        appName = buff + 5;            /*  Assumes 0xFF x "." y 0xFF         */

        vhost = strchr(appName, LRWP_STRING_DELIM_CHAR);
        if (vhost != NULL) {
            *(vhost++) = '\0';

            /* Eliminate the last delimiter, if present                      */
            lastdelim = strchr(vhost, LRWP_STRING_DELIM_CHAR);
            if (lastdelim != NULL)
                *lastdelim = '\0';
        }

        /*  Reject malformed connection strings.  All deliminators
         *  should be present and accounted for.
         */
        if (appName == NULL || strlen(appName) <= 0 ||
            vhost   == NULL || lastdelim       == NULL) {

            tcb-> startupError = errLRWP2Malformed;
            the_next_event = startup_error_event;
            return;
        }
    }
    else if (proto_major == 1) {
        /* parse: applicationname 0xFF virtualhostname 0xFF filterext [0xFF] */
        appName = buff;
        ASSERT (vhost == NULL && filterExt == NULL);

        vhost = strchr(appName, LRWP_STRING_DELIM_CHAR);
        if (vhost != NULL) {
            *(vhost++) = '\0';

            filterExt = strchr(vhost, LRWP_STRING_DELIM_CHAR);
            if (filterExt != NULL) {
                char *lastdelim;

                *(filterExt++) = '\0';

                /* Eliminate the last delimiter, if present                  */
                lastdelim = strchr(filterExt, LRWP_STRING_DELIM_CHAR);
                if (lastdelim != NULL)
                    lastdelim = '\0';
            } 
        }

        if (appName == NULL || vhost == NULL || filterExt == NULL) {
                /* If parsing failed, send back an error message */
                tcb-> startupError   = errLRWP1Malformed;
                the_next_event = startup_error_event;
                return;
        }
    }
    else {
        /* Unrecognised version number -- send rejection message             */
        tcb-> startupError   = errUnrecognisedVersion;
        the_next_event = startup_error_event;
        return;
    }

    /* Tidy up registration information                                      */
    if (*appName == '/')
        appName++;

    /* Validate length of components (required to avoid overflows later)     */
    if ((appName && strlen(appName) > MAX_APPNAME_LEN)
    ||  (vhost   && strlen(vhost)   > MAX_VHOST_LEN)) {
        tcb-> startupError = errComponentTooLong;
        the_next_event = startup_error_event;
        return;
    }

    /* If we reach here, we have a properly formed LRWP connection
     * request from a LRWP peer that suits the proto_major protocol.
     */

    /* Copy registration information into LRWP TCB for future reference      */
    /* NOTE: Application name can either be a path, in which case it is
     * matched as a prefix; or it can be a ".ext" in which case it is
     * matched as an extension suffix.
     */
    tcb->appName     = mem_strdup(appName);
    tcb->vhost       = mem_strdup(*vhost ? vhost : VHOST_ANY);
    tcb->filterExt   = mem_strdup(filterExt);
    tcb->proto_major = proto_major;
    tcb->proto_minor = proto_minor;
    tcb->filehandle  = NULL_HANDLE;

    if (tcb->appName == NULL || tcb->vhost == NULL) {
        tcb-> startupError = errResourcesExhausted;
        the_next_event = startup_error_event;
        return;
    }

    /* make sure connection is allowed: check both webmask, and per
     * application authentication.
     */
    webmask = http_webmask (http_config (config, "lrwp:webmask"), tcb-> handle);
    if (!socket_is_permitted(socket_peeraddr(tcb->handle), webmask)) {
        mem_free(webmask);
        tcb-> startupError = errUnauthorised;
        the_next_event = startup_error_event;
        return;
    }
    else
        mem_free(webmask);

    access = http_config(config, "lrwp:allow-all");
    if (access != NULL && *access == '1') {
        the_next_event = peer_accepted_event;
        return;
    }
    else {
        /*  Not all LRWP connections are allowed; need specific permission   */
        /*  Which means a LRWP-Application: entry for the application name.
         *  If the value is "*" then the application is allowed without
         *  any further authentication.  Otherwise it is used as the
         *  basis of a challenge to the application (LRWP 2.0 or higher).  
         *  LRWP 1.0 connections can handle only the "*" form; if we
         *  don't find a "*" then we reject the application in LRWP 1.0.
         */
        access = http_config(config, makeLRWPAppKey(appName));

        if (access != NULL && *access != '\0') {
            if (streq(access, "*")) {
                the_next_event = peer_accepted_event;
                return;
            }
            else if (proto_major >= 2) {
                the_next_event = challenge_peer_event;
                return;
            }
            else {
                tcb-> startupError = errNeedAuth;
                the_next_event = startup_error_event;
                return;
            }
        }
        else {
            tcb-> startupError = errExcluded;
            the_next_event = startup_error_event;
            return;
        }
    }

    /* Unreachable */
    ASSERT (FALSE);
}

/*****************************   REGISTER PEER   *****************************/

MODULE register_peer (THREAD *thread)
{
    char*       key;
    PTCB*       ptcb;
    RTRData*    rtr;
    SYMBOL*     rtrSym;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /* create the table if this is the first peer. */
    if (!peerTable)
        peerTable = sym_create_table();

    ASSERT(peerTable);

    /* find or create the router symbol in the peer symbol table*/
    /* XXX: We need to handle resource exhaustion at this point somehow.  */
    key = makeTableKey(tcb->appName, tcb->vhost);
    rtrSym = sym_lookup_symbol(peerTable, key);
    if (! rtrSym) {
        rtrSym = sym_create_symbol(peerTable, key, NULL);
        rtrSym->data = mem_alloc(sizeof(RTRData));
        rtr = rtrSym->data;
        rtr->name  = mem_strdup(tcb->appName);
        rtr->vhost = mem_strdup(tcb->vhost);
        node_reset(&rtr->peerList);
        node_reset(&rtr->waitingRequests);

        send_wsx_install(&http_thread->queue->qid,
                        tcb->vhost,
                        tcb->appName,
                        LRWP_NAME);
    }
    rtr = rtrSym->data;

    /* tell the router about this thread (at end, to keep even distribution) */
    ptcb = node_create(rtr->peerList.prev, sizeof(PTCB)); 
    ptcb->thread = thread;
    ptcb->busy = 0;

    /* give this thread a pointer to the peer thread control block */
    tcb->ptcb = ptcb;
    tcb->rtr = rtr;

    /* Log peer connection */
    sendfmt(&operq, "INFO",
            LRWP_NAME ": Peer %s connected for %s host",
                tcb->rtr->name, tcb->rtr->vhost);
}

/***********************   SEND PEER ACKNOWLEDGEMENT   ***********************/

/* Write out string to handle; set the_next_event if the socket closes,
 * or raise event if some other socket error occurs.  Will return 
 * value returned by write_TCP: number of bytes written, or SOCKET_ERROR.
 */
static int write_TCP_or_error(int handle, char *buffer, int buflen)
{
    int num;

    ASSERT(buffer);
    num = write_TCP(handle, buffer, buflen);

    if (num == SOCKET_ERROR) {
        if (sockerrno == EPIPE || sockerrno == ECONNRESET) {
            the_next_event = sock_closed_event;
        }
        else {
            ASSERT(sockerrno != EAGAIN && sockerrno != EWOULDBLOCK);

            tcb->sockError = mem_strdup(sockmsg());
            raise_exception(sock_error_event);
        }
    }

    return num;
}

MODULE send_peer_acknowledgement (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb->proto_major == 1) 
        write_TCP_or_error(tcb->handle, "OK", 2);                /* LRWP 1.0 */
    else 
        write_TCP_or_error(tcb->handle,"OK" LRWP_STRING_DELIM,3);/* LRWP>=2.0*/
}


/********************   SEND PEER NEGOTIATION CHALLENGE   ********************/

MODULE send_peer_negotiation_challenge (THREAD *thread)
{
    int  i;
    char *ptr = databuf;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT(CHALLENGE_LENGTH + LENGTH_LEN + 11 <= sizeof(databuf));

    memcpy(ptr, "CHALLENGE" LRWP_STRING_DELIM, 10);
    ptr += 10;
    sprintf(ptr, LENGTH_FORMAT, CHALLENGE_LENGTH);
    ptr += LENGTH_LEN;

    /* Generate challenge string, using high order bits of rand() value
     * which are generally "more random" (see Linux rand() man page, and
     * its sources "Numerical References in C" and Knuth TAOCP vol 2).
     */
    for (i = 0; i < CHALLENGE_LENGTH; i++)
         tcb->challenge[i] = (byte)((256.0 * rand())/(RAND_MAX*1.0));

    memcpy(ptr, tcb->challenge, CHALLENGE_LENGTH);
    ptr += CHALLENGE_LENGTH;

    write_TCP_or_error(tcb->handle, databuf, (ptr-databuf));

    /* Prepare to receive response to challenge                              */
    if (tcb->buffer)
        mem_free(tcb->buffer);
    tcb->numtoread   = 0;
    tcb->numread     = 0;
    *(tcb->sizebuff) = '\0';
}


/*********************   CHECK PEER NEGOTATION RESPONSE   ********************/

/* Check challenge response from peer (stored in tcb buffers)                */
MODULE check_peer_negotiation_response (THREAD *thread)
{
    char *accessKey;
    byte *challengeResponse;
    int  i, accessKeyLen;

    const char *errWrongResponse = "Incorrect LRWP challenge response";

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT(tcb->buffer);

    if (tcb->numtoread != CHALLENGE_LENGTH) {
        tcb->startupError = errWrongResponse;
        the_next_event = startup_error_event;
    }
    else {
        accessKey = http_config(config, makeLRWPAppKey(tcb->appName));
        ASSERT (accessKey);
        accessKeyLen = strlen(accessKey);

        /* Validate challenge response */
        the_next_event = peer_accepted_event;

        for (i = 0, challengeResponse = (byte *)tcb->buffer;
             i < CHALLENGE_LENGTH; 
             i++, challengeResponse++) 

             if (*challengeResponse !=
                     (((tcb->challenge)[i]) ^ (accessKey[i % accessKeyLen]))) 
                 the_next_event = startup_error_event;

        if (the_next_event == startup_error_event) 
                 tcb-> startupError = errWrongResponse;
    }

    mem_free(tcb->buffer);
    tcb->buffer      = NULL;
    tcb->numtoread   = 0;
    tcb->numread     = 0;
    *(tcb->sizebuff) = '\0';
}


/***********************   SEND REQUEST DATA TO PEER   ***********************/

MODULE send_request_data_to_peer (THREAD *thread)
{
    REQ     req;
    long    size;
    long    tosend = 0;

    tcb = thread->tcb;

    /*  We copy the thread body to a REQ structure to avoid alignment errors
     *  which can arise on some systems if we try to use the thread body as
     *  a REQ structure directly (it is byte aligned)
     */
    memcpy (&req, thread-> event-> body, sizeof (REQ));
    tcb-> replyQ = req.replyQ;

    /* For efficiency (since we've turned off Nagle's algorithm on the
     * connection to the peer), we manually buffer the output being sent
     * to the peer to attempt to get it sent in as few packets as
     * possible.  We buffer the data in databuf until we have to send
     * it, but ensure we clear that buffer before the function finishes.
     * We rely on send_write() to copy the data in the buffer (which it
     * does) to ensure the buffer is not required after we exit.
     * (Thanks to Bruce Dodson <bruce_dodson@bigfoot.com> for this
     * suggestion.)
     */

    /*  send the size as a zero-filled field, followed by the env data */
    sprintf(databuf, LENGTH_FORMAT, req.wsxreq->symbols_size);
    tosend = LENGTH_LEN;
 
    /*  If the environment data will fit, copy it into the buffer,
     *  otherwise send in two chunks.
     */
    if (req.wsxreq->symbols_size + LENGTH_LEN <= sizeof(databuf)) {
        memcpy((databuf + tosend), req.wsxreq->symbols_data,
                                   req.wsxreq->symbols_size);
        tosend += req.wsxreq->symbols_size;
    } else {
        /* Only part of the data to send will fit, fit as much as
         * possible, and send that, then buffer/send the rest.
         */
        long firstlen  = sizeof(databuf) - tosend;
        long secondlen = req.wsxreq->symbols_size - firstlen;

        memcpy((databuf + tosend), req.wsxreq->symbols_data, firstlen);
        send_write(&sockq, 0, tcb->handle, (word)(sizeof(databuf)), 
                   (byte *)databuf, 0);

        /* If there's room to buffer the rest of the environment, and at
         * least the header of the post data, buffer it, otherwise send now
         */
        if (secondlen + LENGTH_LEN <= sizeof(databuf)) {
            memcpy(databuf, (req.wsxreq->symbols_data + firstlen), secondlen);
            tosend = secondlen;
        } else {
            send_write(&sockq, 0, tcb->handle, (word)secondlen, 
                       (req.wsxreq->symbols_data + firstlen), 0);
            tosend = 0;
        }
    }

    /* At this point there's guarenteed to be room for the post data header */
    ASSERT(tosend + LENGTH_LEN <= sizeof(databuf));

    /* The post data goes the same way; may either be in a file or in 
     * a buffer.  Depends largely on size of incoming data.  In file if
     * buffer contains @filename, and the filename exists.  Otherwise
     * the data just happens to start with a "@".  (There's still a 
     * slight possibility that someone could send data that happens 
     * to consist of "@name" where name happened to be a filename, but
     * this is considered sufficiently remote to be ignored for now.)
     *
     * The file is considered to exist if get_file_size() returns a
     * file size.
     */
    if (req.wsxreq->post_data[0] == '@' &&
        (size = get_file_size(req.wsxreq->post_data+1)) >= 0) {
        /* File exists, send the file... */

        sprintf((databuf + tosend), LENGTH_FORMAT_LONG, size);
        tosend += LENGTH_LEN;

        send_write(&sockq, 0, tcb->handle, (word)tosend, (byte *)databuf, 0);

        if (size)
            send_put_file (&tranq, tcb-> handle, req.wsxreq-> post_data + 1,
                           0, 0, 0, NULL);
    }
    else {
        /* Send the buffer */
        size = strlen(req.wsxreq->post_data);
        sprintf((databuf + tosend), LENGTH_FORMAT_LONG, size);
        tosend += LENGTH_LEN;

        if (tosend + size <= sizeof(databuf)) {
            /* It'll fit in the same buffer, buffer and send together */
            if (size)
                memcpy((databuf + tosend), req.wsxreq->post_data, size);

            tosend += size;
            send_write(&sockq, 0, tcb->handle, (word)tosend, (byte *)databuf,0);
        } else {
            /* Won't fit; send the data to date, and then then post data */
            ASSERT(size > 0);

            send_write(&sockq, 0, tcb->handle, (word)tosend, (byte *)databuf,0);
            send_write(&sockq, 0, tcb->handle, (word)size,
                       (byte*)req.wsxreq->post_data, 0);
        }
    }

    /* free the request data */
    free_smt_wsx_request (&req.wsxreq);

    /* clear incoming length string ready for the return data */
    tcb-> sizebuff[0] = '\0';
}



/***************************   READ PEER DATA SIZE  **************************/

/* Build a temporary path name for the data output file, and prefix it
 * with a "@".  The returned memory should be freed with mem_free when
 * no longer required.
 */
static char *maketempname()
{
    static unsigned short   count = 0;
    char filename[16];

    if (count > 9999) 
        count = 0;
    sprintf(filename, "lrwp%04d", ++count);

    return xstrcpy (NULL, "@", 
                    file_where ('s', http_config(config, "server:temp-dir"),
                                filename, "lwo"), 
                    NULL);
}

/* Validate that a given string contains only numeric characters, to
 * form a positive integer.
 */
static Bool is_valid_number(const char *numstr)
{
  if (! numstr)
      return FALSE;

  while (*numstr) {
    if (! isdigit(*numstr))
       return FALSE;

    ++numstr;
  }

  return TRUE;
}

/* Log an protocol error message.  Assumes tcb global set appropriately.
 */
static void signal_protocol_error(const char *message)
{
    if (tcb->rtr) {
        sendfmt(&operq, "INFO",
                LRWP_NAME ": App %s on %s: Protocol error: %s",
                tcb->rtr->name, tcb->rtr->vhost, message);
    }
    else {
        sendfmt(&operq, "INFO", 
                LRWP_NAME ": App %s on %s: Protocol error: %s",
                (tcb->appName ? tcb->appName : ""), 
                (tcb->vhost   ? tcb->vhost   : ""),
                message);
    }
}

MODULE read_peer_data_size (THREAD *thread)
{
    int len;

    tcb = thread->tcb;

    /* XXX: Assumes length will arrive in one packet, should usually be true */
    len = read_TCP(tcb->handle, tcb->sizebuff, LENGTH_LEN);
    if (len != LENGTH_LEN) {
        trace(LRWP_NAME ": read_peer_data **** did not read full size!");
        tcb->sockError = mem_strdup(sockmsg());
        raise_exception(sock_error_event);
        return;
    }
    tcb->sizebuff[len] = '\0';          /* NUL terminate string */

    if (is_valid_number(tcb->sizebuff)) {
        tcb->numtoread = atoi(tcb->sizebuff);
        tcb->numread = 0;

        if (tcb->numtoread > BIG_RESPONSE_LEN) {
            /* Large file to read in, buffer to disk immediately */
            tcb->buffer = maketempname();

            tcb->filehandle = open(((tcb->buffer)+1), 
                                   O_CREAT| O_BINARY| O_WRONLY, 
                                   TEMP_FILE_UMASK);

            if (tcb->filehandle < 0)
                tcb->filehandle = NULL_HANDLE;

        } else {
            /* Small enough to buffer in memory */
            tcb->buffer = mem_alloc(tcb->numtoread+1);
            *(tcb->buffer) = '\0';          /* Ensure won't start with "@" */
        }
    }
    else {
        /* Did not receive length number when we expected it. */
        trace(LRWP_NAME ": Unexpectedly received non-numeric data "
                        "while expecting length from peer");
        signal_protocol_error("Received non-numeric data size value");
        raise_exception(protocol_error_event);
    }
}

/*****************************   READ PEER DATA   ****************************/

MODULE read_peer_data (THREAD *thread)
{
    int len;
    tcb = thread->tcb;

    if (tcb->filehandle < 0 && *(tcb->buffer) != '@') {
        /* Buffering in memory, read directly into buffer */
        len = read_TCP(tcb->handle, tcb->buffer+tcb->numread,
                                    tcb->numtoread-tcb->numread);

        /* On first read, check that the buffer read won't cause confusion 
         * later; if it will, then we force it to go out to disk instead.
         */
        if (tcb->numread == 0 && len > 0 && *(tcb->buffer) == '@') {
            char *pathname = maketempname();

            tcb->filehandle = open((pathname+1), O_CREAT| O_BINARY| O_WRONLY, 
                                   TEMP_FILE_UMASK);

            if (tcb->filehandle < 0)
                tcb->filehandle = NULL_HANDLE;
            else {
                if ((int)write(tcb->filehandle, tcb->buffer, tcb->numread) != 
                                                        (int)tcb->numread) {
                    /* Problem saving to file: we have to keep reading
                     * the data from the peer in order to stay in sync, 
                     * but we can't save it, and will send an error back
                     * to the client instead.  Unfortunately this means
                     * the peer and the client have different views of
                     * whether the transaction happened, but there's no
                     * easy solution.
                     */
                    close(tcb->filehandle);
                    tcb->filehandle = NULL_HANDLE;
                }
            }

            mem_free(tcb->buffer);
            tcb->buffer = pathname;
        }
    } else {
        /* Buffering to disk, read into buffer and write to disk */
        int maxread = tcb->numtoread-tcb->numread;
        if (maxread > sizeof(databuf))
            maxread = sizeof(databuf);

        len = read_TCP(tcb->handle, databuf, maxread);

        if (len != SOCKET_ERROR && tcb->filehandle != NULL_HANDLE) {
            if (write(tcb->filehandle, databuf, len) != len) {
                /* Error saving incoming data; have to stop saving it. */
                close(tcb->filehandle);
                tcb->filehandle = NULL_HANDLE;
            }
        }
    }

    if (len == SOCKET_ERROR) {
        if (sockerrno == EAGAIN || sockerrno == EWOULDBLOCK)
            return;
        else
        if (sockerrno == EPIPE || sockerrno == ECONNRESET) {
            the_next_event = sock_closed_event;
            return;
        }
        else {
            tcb->sockError = mem_strdup(sockmsg());
            raise_exception(sock_error_event);
            return;
        }
    }

    tcb->numread += len;
    if (tcb->numread == tcb->numtoread) {
        the_next_event = finished_event;

        if (*(tcb->buffer) != '@') {
            tcb->buffer[tcb->numread] = '\0';
        }
    }
}

/************************   SEND PEER DATA TO XITAMI   ***********************/

MODULE send_peer_data_to_xitami (THREAD *thread)
{
    tcb = thread->tcb;

    /* Return data sent by peer to Xitami.  If the data is large, or 
     * happens to begin with "@", then the buffer will contain "@filename",
     * and the data will be in the file.  Otherwise the data is held in
     * memory.  In either case, the WSX will handle the data.
     */
    if (tcb->filehandle >= 0) {
        close(tcb->filehandle);
        tcb->filehandle = NULL_HANDLE;
        send_wsx_ok(&tcb->replyQ, (byte *)tcb->buffer);
    }
    else if (*(tcb->buffer) == '@') {
        /* Hmm, we should be writing to a file, but something obviously
         * went wrong, so we're not.  Send back an error.  We've had to 
         * wait until this point to figure it out in order to stay in
         * sync with the peer.
         *
         * While it may seem we should send an overloaded error,
         * actually internal error is best because it hints to the
         * client maybe the request succeeded and they just didn't get a
         * response.
         */
        send_wsx_error(&tcb->replyQ, HTTP_RESPONSE_INTERNALERROR);
    }
    else {
        send_wsx_bin(&tcb->replyQ, tcb->numread, (byte *)tcb->buffer);
    }
}


/***********************   CLEANUP AND INFORM ROUTER   ***********************/

MODULE cleanup_and_inform_router (THREAD *thread)
{
    tcb = thread-> tcb;
    tcb->ptcb->busy = FALSE;
    *tcb->sizebuff = '\0';
    tcb->numtoread = 0;
    tcb->numread = 0;
    mem_free(tcb->buffer);
    tcb->buffer = NULL;

    ASSERT(tcb->filehandle == NULL_HANDLE);
    if (tcb->filehandle != NULL_HANDLE)
        close(tcb->filehandle);

    SEND(&rtrThread->queue->qid, LRWP_JOBCOMP,
            makeTableKey(tcb->rtr->name, tcb->rtr->vhost));
}


/***************************   SIGNAL PEER CLOSED   **************************/

MODULE signal_peer_closed (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */

    if (tcb->rtr) {
        sendfmt(&operq, "INFO",
                LRWP_NAME ": App %s on %s terminating",
                tcb->rtr->name, tcb->rtr->vhost);
    }
    else {
        sendfmt(&operq, "INFO", 
                LRWP_NAME ": App %s on %s failed to connect",
                (tcb->appName ? tcb->appName : ""), 
                (tcb->vhost   ? tcb->vhost   : ""));
    }
}

/***************************   SIGNAL STARTUP ERROR   *************************/

MODULE signal_startup_error (THREAD *thread)
{
    tcb = thread->tcb;                 /*  Point to thread's context         */

    /*  Log error message */
    sendfmt(&operq, "INFO",
            LRWP_NAME ": Peer %s failed to connect (%s)", 
            (tcb->appName ? tcb->appName : ""), tcb->startupError);

    /*  And send it out to the peer */
    sendPeerErrorMessage(tcb->handle, tcb->startupError, tcb->proto_major);
}

static void  sendPeerErrorMessage(int handle, const char *errorMessage, 
                                  int lrwpVer)
{
    char *ptr = databuf;
    int  msglen = strlen(errorMessage);

    ASSERT(msglen + 11 < sizeof(databuf));

    if (lrwpVer > 1) {
        memcpy(ptr, "REJECTED" LRWP_STRING_DELIM, 9);
        ptr += 9;
    }

    strcpy(ptr, errorMessage);
    ptr += msglen;

    if (lrwpVer > 1) 
        *(ptr++) = LRWP_STRING_DELIM_CHAR;

    (void)write_TCP(handle, databuf, (ptr-databuf));
}

/****************************   SEND ERROR REPLY   ***************************/

MODULE send_error_reply (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    send_wsx_error(&tcb->replyQ, HTTP_RESPONSE_INTERNALERROR);
}


/**************************   FIND AVAILABLE PEER   **************************/

static Bool send_to_unbusy_peer(THREAD* thread, RTRData* rtr, REQ* req)
{
    PTCB*    ptcb;

    for (ptcb=rtr->peerList.next;
        (NODE*)ptcb != &rtr->peerList;
        ptcb=ptcb->next) {

        if (! ptcb->busy) {
            event_send(&ptcb->thread->queue->qid,   /* To                    */
                &thread->queue->qid,                /* From                  */
                LRWP_REQUEST,                       /* Event name            */
                (byte*)req, sizeof(REQ),            /* The message           */
                NULL, NULL, NULL, 0);

                /* free the req, but not its contents. */
            node_destroy(req);
            ptcb->busy = TRUE;

            /*  If we are doing round robin access to peers, then
             *  rearrange the peers so someone else gets next request.
             */
            if (round_robin &&
                (NODE*)ptcb->next != &rtr->peerList) {
                node_unlink(ptcb);
                node_relink_before(ptcb, &rtr->peerList);
            }

            return TRUE;
        }
    }
    return FALSE;
}

/* Determine which (if any) of the peers matches the URI we are given        */
/* This handles prefix matches and extension matches.                        */
static RTRData* lrwp_match_peer(char* uri, char* vhost)
{
    SYMBOL*     symbol;
    RTRData*    rtr;
    int         urilen, namelen;

    ASSERT(uri);
    ASSERT(vhost);

    if (*uri == '/')
        uri++;

    urilen = strlen(uri);                     /* XXX: Allow for ?... bits?   */

    symbol = peerTable->symbols;
    for (symbol = peerTable->symbols; symbol != NULL; symbol = symbol->next) {
        rtr = symbol->data;
        if (streq(vhost, rtr->vhost) || streq(VHOST_ANY, rtr->vhost)) {

            if (*rtr->name == '.') {                   /*  Match extension   */
                namelen = strlen(rtr->name);

                if (urilen > namelen &&
                    streq((uri+(urilen-namelen)), rtr->name))
                    return rtr;
            }
            else if (strprefixed(uri, rtr->name))     /*  Match prefix       */
                return rtr;
        }
    }
    return NULL;
}


MODULE find_available_peer (THREAD *thread)
{
    REQ*        req;
    WSXREQ*     wsxreq;
    RTRData*    rtr;


    tcb = thread->tcb;                 /*  Point to thread's context         */

    /*  Decode the WSX request          */
    get_smt_wsx_request(thread->event->body, &wsxreq);
    if (!wsxreq) {
        /*  The request can only be null if there is no memory left          */
        send_wsx_error(&thread->event->sender, HTTP_RESPONSE_OVERLOADED);
        the_next_event = exception_event;
        return;
    }

    req = node_create(NULL, sizeof(REQ));
    req->replyQ = thread->event->sender;
    req->wsxreq = wsxreq;

        /*
         * find peerData that matches the vhost and the leading portion of the
         * wsxreq->request_url
         */
    rtr = lrwp_match_peer(wsxreq->request_url, wsxreq->virtual_host);
    if (!rtr) {
        send_wsx_error(&req->replyQ, HTTP_RESPONSE_NOTFOUND);
        mem_free(req);
        free_smt_wsx_request (&wsxreq);
        return;
    }


        /* send request to available peer */
    if (! send_to_unbusy_peer(thread, rtr, req)) {
            /* if none available, save the request for later */
        node_relink_before(req, &rtr->waitingRequests);
    }
}

/************************   CHECK FOR SAVED REQUESTS   ***********************/

MODULE check_for_saved_requests (THREAD *thread)
{
    REQ*        req;
    char*       key;
    SYMBOL*     rtrSym;
    RTRData*    rtr;

    tcb = thread->tcb;
    key = (char*)thread->event->body;
    rtrSym = sym_lookup_symbol(peerTable, key);
    if (rtrSym) {
        rtr = rtrSym->data;
        if (rtr->waitingRequests.next
        && (rtr->waitingRequests.next != (void*)&rtr->waitingRequests)) {
            req = rtr->waitingRequests.next;
            node_unlink(req);
                /* send request to available peer */
            if (! send_to_unbusy_peer(thread, rtr, req)) {
                /* if none available, put the request back at the
                   head of the list */
                node_relink_after(req, &rtr->waitingRequests);
            }
        }
    }
}


/***************************   CHECK IF ALL GONE   ***************************/

MODULE check_if_all_gone (THREAD *thread)
{
    REQ*        req;
    char*       key;
    SYMBOL*     rtrSym;
    RTRData*    rtr;

    tcb = thread->tcb;                 /*  Point to thread's context         */

    /* if the peer list is empty, cleanup. */
    key = (char*)thread->event->body;

    /* Lookup the main webserver thread again.  We may already have this
     * value, but during shutdown the thread may be gone, in which case
     * we don't want to try to send it messages.
     */
    http_thread = thread_lookup (SMT_HTTP, "main");

    /*  PH 98/07/14: peerTable could be NULL at this point                   */
    rtrSym = peerTable? sym_lookup_symbol(peerTable, key): NULL;
    if (rtrSym) {
        rtr = rtrSym->data;
        if (rtr->peerList.next == (void*)&rtr->peerList) {
            /* first clean up the waitingRequests list. */
            while (rtr->waitingRequests.next != (void*)&rtr->waitingRequests) {
                req = rtr->waitingRequests.next;
                node_unlink(req);
                send_wsx_error(&req->replyQ, HTTP_RESPONSE_NOTIMPLEMENTED);
                free_smt_wsx_request (&req->wsxreq);
                mem_free(req);
            }

            /* Remove this alias from Xitami, if HTTP thread still around    */
            if (http_thread)
                send_wsx_cancel(&http_thread->queue->qid,
                                (streq(rtr->vhost, VHOST_ANY) 
                                       ? NULL : rtr->vhost),
                                rtr->name);

            /* Then remove this thing from the peerTable */
            mem_free(rtr->name);
            mem_free(rtr->vhost);
            mem_free(rtrSym->data);
            sym_delete_symbol(peerTable, rtrSym);

            /* if the table is empty, get rid of it. */
            if (peerTable->size == 0) {
                sym_delete_table(peerTable);
                peerTable = NULL;
                if (tcb->termWhenEmpty)
                    the_next_event = terminate_event;
            }
        }
    }
}


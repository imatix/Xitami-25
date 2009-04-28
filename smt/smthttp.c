/*===========================================================================*
 *                                                                           *
 *  smthttp.c -                                                              *
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

#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  HTTP library functions           */
#include "smtmsg.h"                     /*  SMT message functions            */
#include "smtsslm.h"                    /*  SMT SSL message functions        */
#include "xixlog.h"                     /*  Xitami logging interface         */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME     SMT_HTTP         /*  Our public name                  */
#define BUFFER_SIZE    HTTP_HEADER_MAX  /*  Max. incoming HTTP header        */
#define TCONFIG(s)     http_config (tcb-> config, (s))
#define VCONFIG(s)     http_config (vhost-> config, (s))

typedef struct {                        /*  Logging control block            */
    QID
        queue;                          /*    Log queue                      */
    char
        *filename;                      /*    Log filename                   */
    Bool
        owner;                          /*    This thread created log?       */
} LOGCTL;

typedef struct {                        /*  Thread context block:            */
    HTTP_STAT                           /*    Statistics structure           */
        stats;                          /*      this must come first         */
    event_t
        thread_type;                    /*    Thread type indicator          */
    HTTP_CONTEXT
        http;                           /*    HTTP context                   */
    sock_t
        handle;                         /*    Handle for i/o                 */
    int
        read_size;                      /*    Size of input message so far   */
    size_t
        post_size,                      /*    Size of POSTed data, if any    */
        post_read;                      /*    Amount of POSTed data read     */
    long
        request_time,                   /*    Time that request started      */
        range_from,                     /*    Range starting point           */
        range_to;                       /*    Range ending point             */
    Bool
        cgi_request,                    /*    Request for a CGI resource     */
        update_allowed;                 /*    HTTP update methods allowed    */
    char
        *buffer,                        /*    Buffer for i/o                 */
        *http_body,                     /*    HTTP body, if any              */
        *range;                         /*    Current range string           */
    word
        input_timeout,                  /*    Timeout for input and output   */
        output_timeout;                 /*      waits on socket              */
    SYMTAB
        *config,                        /*    Configuration for host         */
        *passwd;                        /*    User authentication data       */
    FILE
        *post_file;                     /*    File captures POSTed data      */
    LOGCTL
        *acclog,                        /*    Access log                     */
        *errlog;                        /*      and error log for thread     */
    QID
        sslq;                           /*    SSL queue                      */
    Bool
        ssl_connection;                 /*    TRUE for SSL connection        */
    char
        *ssl_username;                  /*    SSL user id                    */
} TCB;

typedef struct {                        /*  Virtual host resources           */
    SYMTAB                              /*                                   */
        *config,                        /*    Configuration for host         */
        *passwd;                        /*    User authentication data       */
    char
        *name,                          /*    Virtual host name              */
        *file,                          /*    Config file name               */
        *rootdir,                       /*    Web pages root directory       */
        *cgidir,                        /*    CGI root directory             */
        *webmask;                       /*    Security webmask               */
    LOGCTL
        acclog,                         /*    Access log control block       */
        errlog;                         /*    Error log control block        */
} VHOST;


/*- Function prototypes -----------------------------------------------------*/

static void    set_timer_refresh   (THREAD *thread);
static void    load_config_file    (SYMTAB *table, char *filename);
static SYMTAB *load_password_file  (const char *filename);
static VHOST  *vhost_new           (THREAD *thread, char *name, char *file);
static SYMBOL *vhost_free          (SYMBOL *vhsym);
static void    set_vhost_name      (SYMTAB *table, char *name);
static void    create_log_thread   (THREAD *thread, VHOST *vhost,
                                    char *prefix, LOGCTL *logctl);
static void    inherit_resources   (THREAD *thread, VHOST *vhost);
static char   *find_http_header    (char *data, char *field);
static void    close_post_file     (void);
static int     read_http_next      (THREAD *thread);
static void    log_http_access     (THREAD *thread);
static void    log_access          (THREAD *thread, QID *queue);
static void    set_cgi_timeout     (THREAD *thread);
static char   *make_wsx_path       (char *virtual_host, char *path);
static void    show_addresses      (void);
static void    show_address        (char *address);


/*- Global variables used in this source file only --------------------------*/

static char
    *eoln = "\r\n";                     /*  Standard end-of-line             */
static AGENT
    *this_agent;                        /*  Handle to ourselves              */
static TCB
    *tcb;                               /*  Address thread contect block     */
static QID
    operq,                              /*  Operator console event queue     */
    clogq,                              /*  Server log queue                 */
    sockq,                              /*  Socket agent event queue         */
    timeq,                              /*  Timer agent event queue          */
    tranq,                              /*  Transfer agent event queue       */
    sslq,                               /*  Main SSL event queue             */
    mainq;                              /*  Master thread queue              */
static char
    *rootdir,                           /*  Root directory for documents     */
    *cgidir,                            /*  Directory for CGI programs       */
    *request_log,                       /*  Debug request log file           */
    *header_log,                        /*  Debug header log file            */
    *master_port;                       /*  Port for http service            */
static qbyte
    *hostaddrs;                         /*  List of host addresses           */
static int
    ssl_port = 0;                       /*  SSL port used                    */

static Bool
    server_secure,                      /*  True if SSL agent is present     */
    server_logging;                     /*  True if server logging enabled   */
static SYMTAB
    *vhosts;                            /*  Virtual hosts table              */

#include "smthttp.d"                    /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   ********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smthttp_init

    Synopsis: Initialises the HTTP agent.  Returns 0 if initialised okay,
    -1 if there was an error.  The HTTP agent manages a HTTP service on
    port 80 (+ ip_portbase).  Sends errors and information messages to the
    SMTOPER agent.
    ---------------------------------------------------------------------[>]-*/

int smthttp_init (char *p_rootdir,      /*  Document root directory          */
                  char *p_cgidir)       /*  CGI binary directory             */
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */
#   include "smthttp.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event, SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  ok_event,            0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,            0);
    method_declare (agent, "SOCK_READ_OK",   ok_event,            0);
    method_declare (agent, "SOCK_WRITE_OK",  ok_event,            0);
    method_declare (agent, "SOCK_CLOSED",    sock_closed_event,   0);
    method_declare (agent, "SOCK_ERROR",     sock_error_event,    0);
    method_declare (agent, "SOCK_TIMEOUT",   sock_timeout_event,  0);

    /*  Reply events from transfer agent                                     */
    method_declare (agent, "TRAN_PUTF_OK",   finished_event,      0);
    method_declare (agent, "TRAN_CLOSED",    sock_closed_event,   0);
    method_declare (agent, "TRAN_ERROR",     sock_error_event,    0);

    /*  Registration events from WSX agents                                  */
    method_declare (agent, "WSX_INSTALL",    wsx_install_event,   0);
    method_declare (agent, "WSX_CANCEL",     wsx_cancel_event,    0);

    /*  Reply events from WSX agents                                         */
    method_declare (agent, "WSX_OK",         wsx_ok_event,        0);
    method_declare (agent, "WSX_MULTIPART",  wsx_multi_event,     0);
    method_declare (agent, "WSX_BIN",        wsx_binary_event,    0);
    method_declare (agent, "WSX_MBIN",       wsx_multibin_event,  0);
    method_declare (agent, "WSX_ERROR",      wsx_error_event,     0);
    method_declare (agent, "WSX_REDIRECT",   wsx_redirect_event,  0);
    method_declare (agent, "WSX_RESTART",    wsx_restart_event,   0);
    method_declare (agent, "WSX_KILL",       wsx_kill_event,      0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",     timer_event, SMT_PRIORITY_LOW);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",        master_event,        0);
    method_declare (agent, "_CLIENT",        client_event,        0);

    /*  Private methods used between threads                                 */
    method_declare (agent, "_CANCEL",        cancel_event,        0);
    method_declare (agent, "_RESTART",       restart_event,       0);

    /*  Reply events from SSL agents                                         */
    declare_ssl_accepted     (new_ssl_client_event, 0);
    declare_ssl_read_ok      (ok_event,             0);
    declare_ssl_open_ok      (ssl_open_event,       0);
    declare_ssl_error        (ssl_error_event,      0);
    declare_ssl_write_ok     (ok_event,             0);
    declare_ssl_put_slice_ok (finished_event,       0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket i/o agent is running, else start it up            */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Check whether SSL agent is running                                   */
    if ((thread = thread_lookup ("SMTSSL", "main")) != NULL)
      {
        sslq = thread-> queue-> qid;
        server_secure = TRUE;
      }
    else
        server_secure = FALSE;

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that transfer agent is running, else start it up              */
    smttran_init ();
    if ((thread = thread_lookup (SMT_TRANSFER, "")) != NULL)
        tranq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create initial thread to manage master port                          */
    if ((thread = thread_create (AGENT_NAME, "main")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
        ((TCB *) thread-> tcb)-> handle      = 0;
      }
    else
        return (-1);

    this_agent = agent;                 /*  Handle to ourselves              */

    /*  Use standard port number.  Caller can set ip_portbase if wanted      */
    /*  to place the port into a specific area.                              */
    master_port = SMT_HTTP_PORT;

    http_init ();                       /*  Initialise HTTP library          */

    /*  Get root and cgi directories passed to smthttp.c                     */
    rootdir = p_rootdir;
    cgidir  = p_cgidir;

    /*  Get local host addresses table, which may be NULL                    */
    hostaddrs = get_hostaddrs ();

    /*  These strings are allocated if not null - initialise now             */
    request_log = NULL;
    header_log  = NULL;

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    long
        max_threads;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> buffer    = NULL;
    tcb-> http_body = NULL;             /*  No HTTP body                     */
    tcb-> config    = config;           /*  Start with global config file    */
    tcb-> post_file = NULL;             /*  No POST file capture open        */
    tcb-> acclog    = NULL;
    tcb-> errlog    = NULL;
    tcb-> http.config = tcb-> config;

    http_init_context (&tcb-> http);

    /*  Take timeouts from HTTP context definition if child thread           */
    if (tcb-> thread_type == client_event)
      {
        tcb-> input_timeout  = tcb-> http.input_timeout;
        tcb-> output_timeout = tcb-> http.output_timeout;
        tcb-> http.port      = atoi (master_port) + ip_portbase;
        tcb-> http.socket    = tcb-> handle;
        tcb-> http.ssl_connection = tcb-> ssl_connection;
        tcb-> http.ssl_port  = ssl_port;
        tcb-> stats.client   = TRUE;
        tcb-> stats.socket   = tcb-> handle;
        tcb-> stats.username = NULL;
        tcb-> stats.request  = NULL;
        tcb-> update_allowed = FALSE;
        tcb-> request_time   = time_now ();
      }
    else
      {
        tcb-> input_timeout  = 0;
        tcb-> output_timeout = 0;
        tcb-> http.port      = 0;       /*  Not serving any port             */
        tcb-> stats.client   = FALSE;
        tcb-> ssl_username   = NULL;
        mainq = thread-> queue-> qid;

        /*  Get maximum connections                                          */
        max_threads = atoi (CONFIG ("server:limit"));
        if (max_threads > 0)
            this_agent-> max_threads = max_threads + 1;
      }
}


/**************************   OPEN SERVER LOG FILE   *************************/

MODULE open_server_log_file (THREAD *thread)
{
    char
        *log_filename;
    THREAD
        *log_thread;                    /*  Log thread                       */
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Open console log file: if none, tell console to be quiet also        */
    log_filename   =  CONFIG ("serverlog:filename");
    server_logging = *CONFIG ("serverlog:enabled") == '1';
    if (server_logging && strused (log_filename))
      {
        log_thread = thread_lookup (XIXLOG_AGENT, log_filename);
        if (log_thread == NULL)
            log_thread = thread_create (XIXLOG_AGENT, log_filename);

        ASSERT (log_thread);
        clogq = log_thread-> queue-> qid;

        send_open (&clogq,
                   CONFIG ("server:log-dir"),
                   CONFIG ("serverlog:filename"),
                   NULL,
                   CONFIG ("serverlog:header"),
                   CONFIG ("serverlog:cycle"),
                   CONFIG ("serverlog:cycle-how"),
                   CONFIG ("serverlog:cycle-time"),
                   CONFIG ("serverlog:cycle-date"),
                   CONFIG ("serverlog:cycle-size"),
                   CONFIG ("serverlog:cycle-lines"),
                   CONFIG ("serverlog:cycle-arg"),
                   FALSE);

        send_set_log (&operq, XIXLOG_AGENT, log_filename);
        sendfmt (&operq, "ENABLE", "");
      }
    else
        sendfmt (&operq, "DISABLE", "");

    /*  Set rate at which the timer agent sends us alarm events              */
    set_timer_refresh (thread);

    /*  Open debug log files                                                 */
    mem_strfree (&request_log);
    request_log = mem_strdup (file_where ('s', CONFIG ("server:debug-dir"),
                                          "request.log", NULL));
    mem_strfree (&header_log);
    header_log = mem_strdup (file_where ('s', CONFIG ("server:debug-dir"),
                                          "header.log", NULL));
}


/*  -------------------------------------------------------------------------
 *  set_timer_refresh
 *
 *  Tell timer to send us an alarm every so often, so we can check for
 *  modified configuration files.  Config refresh rate is in seconds; we need
 *  centiseconds.
 */

static void
set_timer_refresh (THREAD *thread)
{
    qbyte
        refresh;                        /*  Server refresh rate              */

    refresh = atol (CONFIG ("server:refresh")) * 100;
    if (refresh == 0)
        return;                         /*  Then do nothing                  */

    if (refresh < 1000)
        refresh = 1000;                 /*  10 seconds minimum rate          */

    event_send (
        &timeq,                         /*  Send to specified queue          */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "FLUSH",                        /*  Name of event to send            */
        NULL, 0,                        /*  No event body                    */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    send_clock (&timeq, 0, refresh, 0, 0, NULL);
}


/***************************   LOAD VIRTUAL HOSTS   **************************/

MODULE load_virtual_hosts (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Virtual host name in config      */
    char
        *vhost_name,                    /*  Virtual host name, if any        */
        *vhost_file;                    /*  Virtual host config file         */
    VHOST
        *vhost;                         /*  Virtual host resource block      */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Find and process all virtual host definitions.  For each virtual
     *  host, we create an entry in the vhosts table, and create the various
     *  resources that a virtual host needs (config table, logger, etc.)
     */
    vhosts = sym_create_table ();
    for (symbol = config-> symbols; symbol; symbol = symbol-> next)
      {
        if (strprefixed (symbol-> name, "virtual-hosts:"))
          {
            /*  Get virtual host name, and required config file              */
            vhost_name = symbol-> name + strlen ("virtual-hosts:");
            vhost_file = symbol-> value;
            trace ("Loading HTTP VH %s from %s", vhost_name, vhost_file);

            /*  Host may not be defined more than once                       */
            if (sym_lookup_symbol (vhosts, vhost_name))
              {
                http_message ("Duplicate host '%s'", vhost_name);
                sendfmt (&operq, "ERROR", server_message);
              }
            else
            if (file_is_readable (vhost_file))
                vhost = vhost_new (thread, vhost_name, vhost_file);
            else
              {
                http_message ("Config file '%s' not found - %s",
                                vhost_file, strerror (errno));
                sendfmt (&operq, "ERROR", server_message);
              }
          }
      }
    trace ("Loading VH data for base host");
    vhost = vhost_new (thread, VHOST_ANY, CONFIG ("server:base-host"));
    if (vhost)
        inherit_resources (thread, vhost);
    else
        /*  Could not create default VH -> fatal error                       */
        raise_exception (fatal_event);      
}


/*  -------------------------------------------------------------------------
 *  load_config_file
 *
 *  Loads the default configuration into the specified table.
 */

static void
load_config_file (SYMTAB *table, char *filename)
{
    ini_dyn_load (table, "xitami.cfg");
    ini_dyn_load (table, CONFIG ("server:defaults"));
    ini_dyn_load (table, filename);
}


/*  -------------------------------------------------------------------------
 *  vhost_new
 *
 *  Creates virtual host in vhosts table.  If there was an error creating
 *  the virtual host, returns NULL.  Else returns a freshly allocated VHOST
 *  block initialised with useful stuff.
 */
 
static VHOST *
vhost_new (THREAD *thread, char *vhost_name, char *vhost_file)
{
    VHOST
        *vhost;
    SYMBOL
        *vhsym;                         /*  Virtual host entry in table      */
    char
        *v_rootdir,
        *v_cgidir;                      /*  Virtual host's root/cgidir       */
            
    trace ("- loading config data from %s", vhost_file);

    /*  Create new symbol for virtual host                                   */
    vhsym = sym_create_symbol (vhosts, vhost_name, NULL);
    vhost = mem_alloc (sizeof (VHOST));
    vhsym-> data = vhost;
    vhost-> name = mem_strdup (vhost_name);
    vhost-> file = mem_strdup (vhost_file);
    vhost-> acclog.filename = NULL;
    vhost-> errlog.filename = NULL;
    vhost-> webmask = NULL;

    /*  Load config file, inheriting xitami.cfg and defaults.cfg             */
    vhost-> config = sym_create_table ();
    load_config_file (vhost-> config, vhost_file);
    set_vhost_name   (vhost-> config, vhost_name);

    /*  Determine rootdir and cgidir for virtual host                        */
    /*  If command-line option is not the default, it takes precedence       */
    /*  NOTE: The default checked comes from xitami.cfg/compiled in values,  */
    /*  not from the defaults.cfg file.                                      */
    if (streq (rootdir, CONFIG ("server:webpages")))
        v_rootdir = VCONFIG ("server:webpages");
    else
        v_rootdir = rootdir;

    if (streq (cgidir, CONFIG ("server:cgi-bin")))
        v_cgidir = VCONFIG ("server:cgi-bin");
    else
        v_cgidir = cgidir;

    vhost-> rootdir = resolve_path (v_rootdir);
    vhost-> cgidir  = resolve_path (v_cgidir);
    trace (" - rootdir=%s, cgi-bin=%s", vhost-> rootdir, vhost-> cgidir);

    /*  Load password data for this virtual host                             */
    vhost-> passwd = load_password_file (VCONFIG ("security:filename"));
    if (vhost-> passwd == NULL)
      {
        trace ("- vhost '%s' password file not present", vhost_name);
        sendfmt (&operq, "INFO",
            "For security reasons, you must define a password file");
        sendfmt (&operq, "INFO",
            "Create a password file, or set 'security:filename=\"\"'");
        vhost_free (vhsym);
        return (NULL);
      }
    /*  Set webmask for virtual host                                         */
    vhost-> webmask = http_webmask (VCONFIG ("security:webmask"), 0);

    /*  Create logging threads as required                                   */
    create_log_thread (thread, vhost, "accesslog", &vhost-> acclog);
    create_log_thread (thread, vhost, "errorlog",  &vhost-> errlog);

    /*  We keep track of log and temp directories used by all VHs            */
    sym_assume_symbol (http_dirs, VCONFIG ("server:log-dir"),   vhost_name);
    sym_assume_symbol (http_dirs, VCONFIG ("server:temp-dir"),  vhost_name);
    sym_assume_symbol (http_dirs, VCONFIG ("server:debug-dir"), vhost_name);

    return (vhost);
}


/*  Free memory used by the virtual host and delete its entry in the
 *  vhosts symbol table.  Returns pointer to next vhost in table.
 */
static SYMBOL *
vhost_free (SYMBOL *vhsym)
{
    VHOST 
        *vhost;
    SYMBOL
        *next_vhsym;

    vhost = vhsym-> data;
    if (vhost-> config)
        sym_delete_table (vhost-> config);
    if (vhost-> passwd)
        sym_delete_table (vhost-> passwd);

    mem_strfree (&vhost-> acclog.filename);
    mem_strfree (&vhost-> errlog.filename);
    mem_strfree (&vhost-> rootdir);
    mem_strfree (&vhost-> cgidir);
    mem_strfree (&vhost-> name);
    mem_strfree (&vhost-> file);
    mem_strfree (&vhost-> webmask);
    mem_free    (vhost);                /*  Free symbol VHOSTS data          */

    next_vhsym = vhsym-> next;
    sym_delete_symbol (vhosts, vhsym);
    return (next_vhsym);
}


/*  If the configuration does not define a server:hostname, and the
 *  vhost name is textual, insert the specified hostname symbol.  
 */
static void
set_vhost_name (SYMTAB *table, char *name)
{
    if (isalpha (*name)
    &&  sym_lookup_symbol (table, "server:hostname") == NULL)
        sym_assume_symbol (table, "server:hostname", name);
}


/*  -------------------------------------------------------------------------
 *  load_password_file
 *
 *  Loads the specified file into a symbol table; returns the symbol table.
 *  If the file could not be read, sends an error message to the console
 *  and returns NULL.  The filename may be empty, in which case an empty
 *  table is loaded.
 */

static SYMTAB *
load_password_file (const char *filename)
{
    SYMTAB
        *table = NULL;

    if (strnull (filename))
      {
        trace ("- no password data");
        table = sym_create_table ();
      }  
    else
    if (file_is_readable (filename))
      {
        trace ("- loading password data from: %s", filename);
        table = ini_dyn_load (NULL, filename);
      }
    else
      {
        http_message ("'%s' not found - %s", filename, strerror (errno));
        sendfmt (&operq, "ERROR", server_message);        
      }
    return (table);
}


static void
create_log_thread (THREAD *thread, VHOST *vhost, char *prefix, LOGCTL *logctl)
{
    static QID
        null_qid = { 0, 0 };
    THREAD
        *log_thread;                    /*  Log thread                       */
    char
        *format;                        /*  Log format                       */

    /*  This macro accesses the virtual host's config table logging section,
     *  using the current prefix.
     */
#   define VCONFIGP(key)  \
        ini_dyn_value (vhost-> config, prefix, (key), \
        ini_dyn_value (defaults, prefix, (key), ""))

    logctl-> owner    = FALSE;
    logctl-> filename = mem_strdup (
             file_where ('s', VCONFIG ("server:log-dir"),
                              VCONFIGP ("filename"), NULL));

    if (*VCONFIGP ("enabled") == '1')
      {
        /*  Create logging thread, if it does not already exist              */
        log_thread = thread_lookup (XIXLOG_AGENT, logctl-> filename);
        if (log_thread == NULL)
          {
            log_thread = thread_create (XIXLOG_AGENT, logctl-> filename);
            logctl-> owner = TRUE;
          }
        logctl-> queue = log_thread-> queue-> qid;
        format = VCONFIGP ("format");
        if (streq (format, "custom"))
            format = VCONFIGP ("custom");
            
        send_set_rdns (&logctl-> queue,
                        CONFIG ("rdns:primary-server"),
                        CONFIG ("rdns:secondary-server"),
                        (Bool) (*CONFIG ("rdns:recurse-lookups") == '1'),
                        (Bool) (*CONFIG ("rdns:debug") == '1'));
        send_open (&logctl-> queue,
                   VCONFIG  ("server:log-dir"),
                   VCONFIGP ("filename"),
                   format,
                   VCONFIGP ("header"),
                   VCONFIGP ("cycle"),
                   VCONFIGP ("cycle-how"),
                   VCONFIGP ("cycle-time"),
                   VCONFIGP ("cycle-date"),
                   VCONFIGP ("cycle-size"),
                   VCONFIGP ("cycle-lines"),
                   VCONFIGP ("cycle-arg"),
                   (Bool) (*VCONFIGP ("translate") == '1'));
      }
    else
        logctl-> queue = null_qid;
}


/*  -------------------------------------------------------------------------
 *  inherit_resources
 *
 *  Inherits configuration and logging data from the virtual host.
 */

static void
inherit_resources (THREAD *thread, VHOST *vhost)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Set TCB for master thread to use default resources                   */
    tcb-> config = vhost-> config;
    tcb-> passwd = vhost-> passwd;
    tcb-> acclog = &vhost-> acclog;
    tcb-> errlog = &vhost-> errlog;
}


/**************************   CHECK ROOTDIR EXISTS   *************************/

MODULE check_rootdir_exists (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Initialise the root directory for document and cgi files             */
    if (!file_is_directory (rootdir))
      {
        http_message ("webpages directory '%s' not found - %s",
                       rootdir, strerror (errno));
        sendfmt (&operq, "ERROR", server_message);
        raise_exception (fatal_event);
      }
}


/***********************   RESTART FTP SERVER IF REQD   **********************/

MODULE restart_ftp_server_if_reqd (THREAD *thread)
{
    THREAD
        *ftp_thread;                    /*  Handle to FTP agent thread       */

    /*  Look for FTP agent                                                   */
    if ((ftp_thread = thread_lookup ("smtftpc", "main")) != NULL)
        SEND (&ftp_thread-> queue-> qid, "RESTART", "");
}


/***************************   OPEN MASTER SOCKET   **************************/

MODULE open_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  If the server:ipaddress is '*' we accept all addresses, otherwise    */
    /*  we limit the connections to the specified address.                   */
    show_addresses ();
    if (*CONFIG ("server:ipaddress") == '*')
        ip_passive = INADDR_ANY;
    else
        ip_passive = inet_addr (CONFIG ("server:ipaddress"));

    if (ip_portbase == 0)
        ip_portbase = atoi (CONFIG ("server:portbase"));

    /*  We try the ip_portbase                                               */
    tcb-> http.port = atoi (master_port) + ip_portbase;
    tcb-> handle    = passive_TCP (master_port, 5);

    sendfmt (&operq, "INFO",
                     "smthttp: opening HTTP service on port %d...",
                      tcb-> http.port);

    if (tcb-> handle != INVALID_SOCKET)
      {
        http_message ("HTTP service started at %s", http_time_str ());
        sendfmt (&operq, "INFO", "smthttp: HTTP service is now running");
      }
    else
      {
        http_message ("Could not open port %d - %s (%s)",
                       tcb-> http.port, connect_errlist [connect_error ()],
                       sockmsg ());        
        sendfmt (&operq, "ERROR", "smthttp: could not open port %d", tcb-> http.port);
        sendfmt (&operq, "ERROR", "smthttp: %s", connect_errlist [connect_error ()]);
        sendfmt (&operq, "ERROR", "smthttp: %s", sockmsg ());
        raise_exception (fatal_event);
      }
}


static void
show_addresses (void)
{
    int
        index;                          /*  Index into hostaddrs table       */

    if (*CONFIG ("server:ipaddress") == '*')
      {
        if (hostaddrs)
            for (index = 0; hostaddrs [index]; index++)
                show_address (sock_ntoa (hostaddrs [index]));
        show_address ("127.0.0.1");
      }
    else
        show_address (CONFIG ("server:ipaddress"));
}


static void show_address (char *address)
{
    sendfmt (&operq, "INFO",
                     "smthttp: web server binding to address %s", address);
}


/***********************   WAIT FOR PROCESS TO SETTLE   **********************/

MODULE wait_for_process_to_settle (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Wait for two seconds to allow all agents to open their sockets       */
    send_alarm (&timeq, 0, 200, 0, NULL);
}


/**************************   CLOSE MASTER SOCKET   **************************/

MODULE close_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> handle)
      {
        close_socket (tcb-> handle);
        tcb-> handle = 0;
      }
}


/************************   SET SERVER PROCESS STATE   ***********************/

MODULE set_server_process_state (THREAD *thread)
{
    char
        *uid, *gid;                     /*  User/group for setuid            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    http_set_priority ();
    if (*CONFIG ("security:setuid") == '1')
      {
        uid = CONFIG ("security:setuid-user");
        gid = CONFIG ("security:setuid-group");

        set_uid_root ();                /*  Switch to root first             */
        switch (set_uid_gid (uid, gid))
          {
            case 0:
                sendfmt (&operq, "INFO",
                         "smthttp: user/group set to %s/%s", uid, gid);
                break;
            case -1:
                sendfmt (&operq, "ERROR",
                         "smthttp: no such user/group: %s/%s", uid, gid);
                set_uid_user ();
                break;
            case -2:
                sendfmt (&operq, "ERROR",
                         "smthttp: unable to setuid to %s/%s", uid, gid);
                set_uid_user ();
                break;
          }
      }
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_input (&sockq, tcb-> input_timeout, tcb-> handle, 0);
}



/************************   RELOAD CONFIG IF CHANGED   ***********************/

MODULE reload_config_if_changed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Reload main config files if changed, during server restart           */
    if (ini_dyn_changed (config))
      {
        sym_empty_table (config);
        ini_dyn_load (config, "xitami.cfg");
        ini_dyn_load (config, CONFIG ("server:defaults"));
        ini_dyn_load (config, CONFIG ("server:base-host"));
      }
}


/************************   RELOAD CONFIG IF NEEDED   ************************/

MODULE reload_config_if_needed (THREAD *thread)
{
    THREAD
        *ftp_thread;                    /*  FTP agent thread, if any         */
    SYMBOL
        *symbol;                        /*  Pointer to symbol                */
    VHOST
        *vhost;
    char
        *vhost_file,                    /*  VH config file and name          */
        *vhost_name;                    /*    loaned from VH config          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Reload virtual host and main config files if changed, during
     *  normal server running.
     */
    for (symbol = vhosts-> symbols; symbol; )
      {
        vhost = symbol-> data;
        if (ini_dyn_changed (vhost-> config))
          {
            vhost_file = mem_strdup (vhost-> file);
            vhost_name = mem_strdup (vhost-> name);
            symbol = vhost_free (symbol);
            vhost_new (thread, vhost_name, vhost_file);
            mem_free (vhost_file);
            mem_free (vhost_name);
          }
        else
            symbol = symbol-> next;
      }
    /*  Also reload main config file                                         */
    if (ini_dyn_changed (config))
      {
        sym_empty_table (config);
        ini_dyn_load (config, "xitami.cfg");
        ini_dyn_load (config, CONFIG ("server:defaults"));
        ini_dyn_load (config, CONFIG ("server:base-host"));
        set_timer_refresh (thread);     /*  Refresh the refresh              */
      }

    /*  Look for FTP agent and refresh that too if possible                  */
    if ((ftp_thread = thread_lookup ("smtftpc", "main")) != NULL)
        SEND (&ftp_thread-> queue-> qid, "RELOAD", "");

    http_set_priority ();
}


/************************   ACCEPT CLIENT CONNECTION   ***********************/

MODULE accept_client_connection (THREAD *thread)
{
    sock_t
        slave_socket;                   /*  Connected socket                 */
    THREAD
        *child_thread;                  /*  Handle to child threads          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    slave_socket = accept_socket (tcb-> handle);
    if (slave_socket != INVALID_SOCKET)
      {
        child_thread = thread_create (AGENT_NAME, "");
        if (child_thread)
          {
            SEND (&child_thread-> queue-> qid, "_CLIENT", "");
            ((TCB *) child_thread-> tcb)-> thread_type    = client_event;
            ((TCB *) child_thread-> tcb)-> handle         = slave_socket;
            ((TCB *) child_thread-> tcb)-> ssl_connection = FALSE;
            ((TCB *) child_thread-> tcb)-> ssl_username   = NULL;
            connect_count++;            /*  Maintain statistics              */
            cur_connects++;             /*  One more active connection       */
            if (max_connects < cur_connects)
                max_connects = cur_connects;
          }
        else
            close_socket (slave_socket);
      }
    else
    if (sockerrno != EAGAIN && sockerrno != EWOULDBLOCK)
      {
        http_message ("Network problem: %s", sockmsg ());
        sendfmt (&operq, "ERROR", "smthttp: could not accept connection: %s", sockmsg ());
        raise_exception (exception_event);
      }
}


/************************   REJECT CLIENT CONNECTION   ***********************/

MODULE reject_client_connection (THREAD *thread)
{
    sock_t
        handle;                         /*  Connected socket                 */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    handle = accept_socket (tcb-> handle);
    close_socket (handle);
}


/*************************   PREPARE CLIENT THREAD   *************************/

MODULE prepare_client_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> buffer = mem_alloc (BUFFER_SIZE + 1);
    if (tcb-> buffer == NULL)
      {
        sendfmt (&operq, "ERROR", "smthttp: out of memory");
        raise_exception (exception_event);
      }
    else
        memset (tcb-> buffer, 0, BUFFER_SIZE + 1);
}


/************************   PREPARE TO READ REQUEST   ************************/

MODULE prepare_to_read_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> read_size = 0;                /*  No data read yet                 */
}


/*************************   READ INPUT FROM SOCKET   ************************/

MODULE read_input_from_socket (THREAD *thread)
{
    qbyte
        bytes_wanted;                   /*  Number of bytes to read          */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> post_file)
      {
        bytes_wanted = tcb-> post_read - tcb-> post_size;
        if (bytes_wanted > BUFFER_SIZE)
            bytes_wanted = BUFFER_SIZE;
      }
    else
        bytes_wanted = BUFFER_SIZE - tcb-> read_size;

    if (tcb-> ssl_connection)
        send_ssl_read_request (&tcb-> sslq, (word) bytes_wanted);
    else
        send_read (&sockq, tcb-> input_timeout, tcb-> handle,
                  (word) bytes_wanted, 1, 0);
}


/*************************   READ HTTP REQUEST NEXT   ************************/

MODULE read_http_request_next (THREAD *thread)
{
    read_http_next (thread);
}


static int
read_http_next (THREAD *thread)
{
    word
        read_size;                      /*  Amount of data read from socket  */
    byte
        *read_data = NULL;              /*  Data read from socket            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ssl_connection)
        exdr_read (thread-> event-> body, SSL_READ_OK,
                   &read_size, &read_data);
    else
        exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
                   NULL, NULL, &read_size, &read_data, NULL);

    /*  tcb-> read_size is amount of data we've read so far.  If we already
     *  read a full buffer, then the buffer is too small.  We reply with a
     *  code 413 (request too large), which is really HTTP/1.1 but okay.
     *  We parse the request, so that whatever header fields we got can
     *  be stuck into the request symbol table (to log the request).
     */
    if (tcb-> read_size + read_size >= BUFFER_SIZE)
      {
        http_parse_request (&tcb-> http, tcb-> buffer);
        read_size = 0;
        raise_exception (too_large_event);
      }
    else
      {
        /*  Move the data into the thread's buffer, offset tcb-> read_size   */
        memcpy (&tcb-> buffer [tcb-> read_size], read_data, read_size);
        tcb-> read_size += read_size;
      }
    mem_free (read_data);
    return (read_size);
}


/***********************   CHECK IF REQUEST COMPLETE   ***********************/

MODULE check_if_request_complete (THREAD *thread)
{
    char
        *eoln,                          /*  End-of-line marker               */
        *blank_line,                    /*  End of request header            */
        *length_ptr,                    /*  Content-Length: field            */
        *type_ptr,                      /*  Content-Type: field              */
        *post_data;                     /*  Start of body content            */
    int
        header_size,                    /*  Size of request header           */
        skip_spaces;                    /*  Whitespace at start of request   */
    Bool
        have_header;                    /*  Did we read the whole header?    */
    FILE
        *log;                           /*  Debugging log file               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  We examine the data we've read so far, to figure-out whether it looks
     *  complete or not.  Since the connection remains open in order for the
     *  server to reply, we can't use the end-of-connection as the end-of-data
     *  indicator.  A normal HTTP header ends in a blank line (CRLFCRLF or
     *  LFLF) followed by the body text.  We also accept a one-line header
     *  that ends in a newline (LF) with no body text.  If the header also
     *  has a 'Content-Length:' field, we expect a body of that size.  The
     *  body is stored in a temporary file that is later passed to the CGI
     *  program (generally posted data is handled by a CGI program).
     */

    /*  Some browsers throw in a CRLF after posting data; on a keep-alive
     *  connection this has the pleasant side-effect of sticking a blank
     *  line at the start of the next request.  We flush any such junk, by
     *  skipping any white space at the start of the request.
     */
    skip_spaces = 0;
    while (skip_spaces < tcb-> read_size
    && isspace (tcb-> buffer [skip_spaces]))
        skip_spaces++;

    if (skip_spaces)
      {
        tcb-> read_size -= skip_spaces;
        memmove (tcb-> buffer, tcb-> buffer + skip_spaces, tcb-> read_size);
      }

    /*  Look for CRLFCRLF, which indicates that the header is complete       */
    tcb-> buffer [tcb-> read_size] = 0;

    eoln = "\r\n\r\n";
    blank_line = txtfind (tcb-> buffer, eoln);
    if (!blank_line)
      {
        eoln = "\n\n";
        blank_line = txtfind (tcb-> buffer, eoln);
      }

    if (blank_line)                     /*  Header is complete               */
      {
        /*  If server:debug is set, log the incoming request                 */
        if (*CONFIG ("server:debug") == '1')
          {
            log = file_open (request_log, 'a');
            if (log)
              {
                *blank_line = '\0';
                fprintf (log, "%s\n\n", tcb-> buffer);
                fclose (log);
                memcpy (blank_line, eoln, 2);
              }
          }
        /*  Look for Content-Length: header field in request header.
         *  If we find it, then we're reading POSTed data.  If the amount
         *  of data is large, we create a temporary file, and save any
         *  posted data already read into that file.  If the data will fit
         *  into the buffer, we carry on reading.
         *  If there's no Content-Length: field, the request is complete.
         */
        the_next_event = finished_event;
        have_header = TRUE;
        length_ptr = find_http_header (tcb-> buffer, "Content-Length:");
        type_ptr   = find_http_header (tcb-> buffer, "Content-Type:");

        if (length_ptr)
          {
            post_data   = blank_line + strlen (eoln);
            header_size = post_data - tcb-> buffer;

            tcb-> post_size = (size_t) (atol (length_ptr));
            tcb-> post_read = tcb-> read_size - header_size;
            tcb-> http.post_size = tcb-> post_size;

            /*  If the POSTed data is large or an uploaded file, we will
             *  shunt it into a temporary file called 'postnnnn.cgi'.
             */
            if ((header_size + tcb-> post_size) > BUFFER_SIZE
            ||  (type_ptr && strprefixed (type_ptr, "multipart")))
              {
                tcb-> http.cgi_stdin = http_pipe (&tcb-> http, "cgi");
                tcb-> post_file = fopen (tcb-> http.cgi_stdin,
                                         FOPEN_WRITE_BINARY);
                if (tcb-> post_file)
                    fwrite (post_data, (size_t) tcb-> post_read, 1,
                            tcb-> post_file);

                the_next_event = post_event;
              }
            else
            if (tcb-> post_size > 0)
              {
                /*  Header + POSTed data will fit into the tcb-> buffer      */
                if (tcb-> post_read < tcb-> post_size)
                    the_next_event = post_event;
              }
          }
      }
    else
        the_next_event = more_event;
}


/*  Looks for a specified header field in the HTTP data block, and returns
 *  either the address of the header value, or NULL.
 */
static char *
find_http_header (char *data, char *field)
{
    char
        *header;

    header = txtfind (data, field);
    if (header)
      {
        header += strlen (field);
        while (*header == ' ')
            header++;
      }
    return (header);
}


/*************************   READ HTTP POSTED DATA   *************************/

MODULE read_http_posted_data (THREAD *thread)
{
    word
        read_size;                      /*  Amount of data read from socket  */
    byte
        *read_data = NULL;              /*  Data read from socket            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> post_file)
      {
        /*  Get chunk of data read by socket agent and write it to the POST
         *  capture file.
         */
        if (tcb-> ssl_connection)
            exdr_read (thread-> event-> body, SSL_READ_OK,
                       &read_size, &read_data);
        else
            exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
                       NULL, NULL, &read_size, &read_data, NULL);

        tcb-> post_read += read_size;   /*  We read something                */
        tcb-> read_size += read_size;
        fwrite (read_data, read_size, 1, tcb-> post_file);
        mem_free (read_data);
      }
    else
        tcb-> post_read += read_http_next (thread);
}


/**********************   CHECK IF POST DATA COMPLETE   **********************/

MODULE check_if_post_data_complete (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> post_read < tcb-> post_size)
        the_next_event = more_event;
    else
      {
        the_next_event = finished_event;
        close_post_file ();
      }
}


static void
close_post_file ()
{
    if (tcb-> post_file)
      {
        fprintf (tcb-> post_file, "\n");
        fclose  (tcb-> post_file);
      }
    tcb-> post_file = NULL;
}


/***************************   PARSE HTTP REQUEST   **************************/

MODULE parse_http_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_parse_request (&tcb-> http, tcb-> buffer))
      {
        /*  Use SSL username from certificate if necessary                   */
        if (tcb-> http.username == NULL
        &&  tcb-> ssl_username && *tcb-> ssl_username)
            tcb-> http.username = mem_strdup (tcb-> ssl_username);

        switch (tcb-> http.method)
          {
            case HTTP_METHOD_GET:
            case HTTP_METHOD_HEAD:
                the_next_event = get_request_event;
                break;
            case HTTP_METHOD_POST:
                the_next_event = post_request_event;
                break;
            case HTTP_METHOD_PUT:
            case HTTP_METHOD_DELETE:
            case HTTP_METHOD_MOVE:
            case HTTP_METHOD_COPY:
                the_next_event = update_request_event;
                break;
            default:
                raise_exception (error_event);
                break;
          }
      }
    else
        raise_exception (error_event);

    tcb-> stats.username = tcb-> http.username;
    tcb-> stats.request  = tcb-> http.log_request;
}


/************************   RESOLVE VIRTUAL HOSTNAME   ***********************/

MODULE resolve_virtual_hostname (THREAD *thread)
{
    char
        *vhost_name;                    /*  Name of virtual host             */
    SYMBOL
        *vhost_sym = NULL;              /*  Virtual host entry in table      */
    VHOST
        *vhost;                         /*  Virtual host resource block      */
    Bool
        uses_vhost = TRUE;              /*  Did we use a virtual host?       */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Resolve virtual host name or multihoming, and prepare thread to use
     *  the required host resources.
     *  First, try Host: header from HTTP request
     */
    vhost_name = http_header_value (&tcb-> http, "Host");
    if (*vhost_name)                    /*  If "", no such header field      */
      {
        vhost_name = http_clean_hostname (vhost_name);
        vhost_sym  = sym_lookup_symbol   (vhosts, vhost_name);
        trace ("Looking for VH using Host value: %s", vhost_name);
        mem_free (vhost_name);
      }
     /*  If that fails, take local socket IP address and try that...         */
    if (!vhost_sym)
      {
        vhost_name = socket_localaddr  (tcb-> handle);
        vhost_sym  = sym_lookup_symbol (vhosts, vhost_name);
        trace (" - looking for VH using IP address: %s", vhost_name);
      }
    /*  If that failed, use VHOST_ANY host name                              */
    if (!vhost_sym)
      {
        vhost_sym = sym_lookup_symbol (vhosts, VHOST_ANY);
        trace ("- using default virtual host values");
        uses_vhost = FALSE;
      }
    ASSERT (vhost_sym);
    vhost = vhost_sym-> data;

    /*  Use virtual host resources                                           */
    inherit_resources (thread, vhost);

    mem_strfree (&tcb-> http.vhost);
    mem_strfree (&tcb-> http.rootdir);
    mem_strfree (&tcb-> http.cgidir);
    mem_strfree (&tcb-> http.webmask);
    tcb-> http.uses_vhost = uses_vhost;
    tcb-> http.vhost      = mem_strdup (vhost_sym-> name);
    tcb-> http.rootdir    = mem_strdup (vhost-> rootdir);
    tcb-> http.cgidir     = mem_strdup (vhost-> cgidir);
    tcb-> http.webmask    = mem_strdup (vhost-> webmask);
    tcb-> http.config     = vhost-> config;
    http_refresh_context (&tcb-> http);
}


/************************   CHECK CLIENT IP ALLOWED   ************************/

MODULE check_client_ip_allowed (THREAD *thread)
{
    char
        *webmask;                       /*  Permitted mask for connection    */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    webmask = tcb-> http.webmask;
    if (streq (webmask, "local"))
        webmask = socket_localaddr (tcb-> handle);

    if (!socket_is_permitted (socket_peeraddr (tcb-> handle), webmask))
        raise_exception (forbidden_event);
}


/******************************   GET URL TYPE   *****************************/

MODULE get_url_type (THREAD *thread)
{
    int
       file_type;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    file_type = http_get_url_type (&tcb-> http);
    switch (file_type)
      {
        case HTTP_URL_HTML:    the_next_event = html_event;       break;
        case HTTP_URL_WSX:     the_next_event = wsx_event;        break;
        case HTTP_URL_CGI:     the_next_event = cgi_event;        break;
        case HTTP_URL_FILTER:  the_next_event = filter_event;     break;
        case HTTP_URL_ILLEGAL: the_next_event = not_found_event;  break;
        default:               the_next_event = error_event;
      }
    tcb-> cgi_request = (file_type == HTTP_URL_CGI);
}


/************************   CHECK FILE OR DIRECTORY   ************************/

MODULE check_file_or_directory (THREAD *thread)
{
    int
        file_status;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    file_status = http_check_file (&tcb-> http);
    switch (file_status)
      {
        case HTTP_FILE_OK:
            the_next_event = file_event;
            break;
        case HTTP_FILE_DIRECTORY:
            the_next_event = directory_event;
            break;
        case HTTP_FILE_EXECUTABLE:
            the_next_event = executable_event;
            break;
        case HTTP_FILE_NOT_FOUND:
            the_next_event = not_found_event;
            break;
        default:
            the_next_event = error_event;
            break;
      }
}


/***************************   CHECK IF PROTECTED   **************************/

MODULE check_if_protected (THREAD *thread)
{
    char
        *url,                           /*  Protected URL value              */
        *url_password,                  /*  Required password for URL        */
        *url_webmask;                   /*  Permitted mask for URL           */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    url = mem_strdup (tcb-> http.url);
    if (http_uri_protected (&tcb-> http, tcb-> passwd, url))
      {
        /*  The Realm is an arbitrary name that the administrator can use to
         *  group resources.  If this is defined in the password file for a
         *  resource, using realm=, we use the realm.  Otherwise we use the
         *  protected resource name.
         */
        the_next_event = unauthorized_event;
        mem_strfree (&tcb-> http.realm);
        tcb-> http.realm = mem_strdup (ini_dyn_value (tcb-> passwd,
                                                      url, "realm", url));
        /*  Get and check webmask for URL                                    */
        url_webmask = http_webmask (
                      ini_dyn_value (tcb-> passwd, url, "webmask", "*"),
                      tcb-> handle);

        /*  Check other permissions for this URL while we're at it           */
        tcb-> update_allowed =
            *ini_dyn_value (tcb-> passwd, url, "http-update", "0") == '1';

        if (socket_is_permitted (socket_peeraddr (tcb-> handle), url_webmask))
          {
            /*  SSL certificates can be used for protected resources
             *  by specifying the password as '*SSL'.
             */
            if (tcb-> ssl_connection
            &&  tcb-> ssl_username && *tcb-> ssl_username
            &&  !http_reserved_username (tcb-> ssl_username))
              {
                url_password = ini_dyn_value (tcb-> passwd,
                                              url, tcb-> ssl_username, "-");
                if (streq (url_password, "*SSL"))
                    the_next_event = ok_event;
              }
            if (the_next_event == unauthorized_event)
              {
                /*  Allow any user if all=* is defined                       */
                if (streq (ini_dyn_value (tcb-> passwd, url, "all", "-"), "*"))
                    the_next_event = ok_event;
                else
                if (tcb-> http.username && *tcb-> http.username
                &&  tcb-> http.password
                &&  !http_reserved_username (tcb-> http.username))
                  {
                    /*  If browser sent authorization information, check it  */
                    url_password = ini_dyn_value (
                            tcb-> passwd, url, tcb-> http.username, "-");
                    if (http_password_okay (url_password, tcb-> http.password))
                        the_next_event = ok_event;
                  }
              }
          }
        else
            /*  Webmask not allowed -> signal 403 error                      */
            raise_exception (forbidden_event);

        mem_free (url_webmask);
      }
    else
        the_next_event = ok_event;      /*  URL is unprotected - no check    */

    mem_free (url);
}


/**************************   GET DEFAULT WEB PAGE   *************************/

MODULE get_default_web_page (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_get_default_page (&tcb-> http))
        the_next_event = file_event;
    else
        the_next_event = not_found_event;
}


/*************************   MAKE DIRECTORY LISTING   ************************/

MODULE make_directory_listing (THREAD *thread)
{
    char
        *dirlist_key;                   /*  Key to use to check dirlists     */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  cgi/security:dirlist must be 1 to enable directory listings          */
    /*  Any system-level protection error is considered as a hard error      */
    if (tcb-> cgi_request)
        dirlist_key = "cgi:dirlist";
    else
        dirlist_key = "security:dirlist";

    if (strneq (TCONFIG (dirlist_key), "1")
    || !http_list_directory (&tcb-> http))
        raise_exception (forbidden_event);
}


/***********************   CHECK FOR CONDITIONAL GET   ***********************/

MODULE check_for_conditional_get (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  In some configurations, defaults page caching is a real pain -
     *  so we allow the user to disable this.
     */
    if (tcb-> http.default_page
    && *TCONFIG ("server:cache-defaults") == '0')
        ;   /*  Do nothing                                                   */
    else
    if (!http_modified_since (&tcb-> http, tcb-> http.file_name,
          "If-Modified-Since"))
        raise_exception (not_modified_event);
    else
    if (!http_unmodified_since (&tcb-> http, tcb-> http.file_name,
          "If-Unmodified-Since"))
        raise_exception (precondition_event);
}


/***************************   WRITE HTTP HEADER   ***************************/

MODULE write_http_header (THREAD *thread)
{
    FILE
        *log;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    http_format_header (&tcb-> http, tcb-> buffer);
    if (tcb-> acclog)                   /*  Log access if possible           */
        log_http_access (thread);
    if (strnull (tcb-> buffer))
        return;                         /*  Empty header - don't send it     */

    /*  If server:debug is set, log the transmitted header                   */
    if (*CONFIG ("server:debug") == '1')
      {
        log = file_open (header_log, 'a');
        if (log)
          {
            fprintf (log, "%s", tcb-> buffer);
            if (*tcb-> buffer && strlast (tcb-> buffer) != '\n')
                fprintf (log, "\n\n");
            fclose (log);
          }
      }
    if (tcb-> ssl_connection)
        send_ssl_write_request (
            &tcb-> sslq, 0,
            tcb-> handle,
            (word) strlen (tcb-> buffer), (byte *) tcb-> buffer, 0);
    else
        send_write (
            &sockq, 0,
            tcb-> handle,
            (word) strlen (tcb-> buffer), (byte *) tcb-> buffer, 0);

    event_wait ();                      /*  Wait for socket agent reply      */
}


/*  Create entry in log file                                                 */

local
log_http_access (THREAD *thread)
{
    char
        *client_ip,
        *username;
    int
        index;                          /*  Index into hostaddrs table       */
    Bool
        is_local;

    tcb = thread-> tcb;

    /*  Get client IP address as a string and see if it's 'local'            */
    client_ip = socket_peeraddr (tcb-> handle);
    if (strprefixed (client_ip, "127"))
        is_local = TRUE;
    else
      {
        is_local = FALSE;
        if (hostaddrs)
            for (index = 0; hostaddrs [index]; index++)
                if (streq (client_ip, sock_ntoa (hostaddrs [index])))
                    is_local = TRUE;
      }
    /*  Use "-" for user name if it's empty                                  */
    username = tcb-> http.username;
    if (username == NULL || *username == '\0')
        username = "-";

    if (!is_local || *TCONFIG ("accesslog:local") == '1')
        log_access (thread, &tcb-> acclog-> queue);

    /*  400 or 402 and higher is an error...                                 */
    if ((tcb-> http.response == HTTP_RESPONSE_BADREQUEST
    ||   tcb-> http.response >  HTTP_RESPONSE_UNAUTHORIZED)
    && (!is_local || *TCONFIG ("errorlog:local") == '1'))
        log_access (thread, &tcb-> errlog-> queue);
}

static void
log_access (THREAD *thread, QID *queue)
{
    tcb = thread-> tcb;
    send_log (
        queue,
        socket_peeraddr  (tcb-> handle),
        socket_localaddr (tcb-> handle),
        tcb-> http.username,
        "HTTP",
        tcb-> http.log_request,
        tcb-> http.url,
        tcb-> http.url_param,
        http_methods  [tcb-> http.method],
        http_response [tcb-> http.response].code,
        tcb-> read_size,
        tcb-> http.file_size,
        (time_now () - tcb-> request_time) * 10,
        tcb-> http.referrer,
        http_header_value (&tcb-> http, "User-Agent"),
        http_header_value (&tcb-> http, "From"),
        tcb-> http.file_name,
        tcb-> http.vhost);
}


/**************************   SEND FILE TO BROWSER   *************************/

MODULE send_file_to_browser (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
     
    if (tcb-> http.method == HTTP_METHOD_HEAD)
        the_next_event = finished_event;
    else
      {
        /*  If server:debug is set, log the transmission data                */
        ASSERT (tcb-> http.file_name);
        trace ("Transfer file=%s size=%ld from=%ld",
                tcb-> http.file_name, tcb-> http.file_size, tcb-> http.file_offset);

        if (tcb-> ssl_connection)
            send_ssl_put_slice (&tcb-> sslq,
                                 tcb-> handle,
                                 tcb-> http.file_name,
                                 tcb-> http.file_offset, 0);
        else
            send_put_file      (&tranq, 
                                 tcb-> handle,
                                 tcb-> http.file_name, 0,
                                 tcb-> http.file_offset, 0,
                                 CONFIG ("server:pipe"));

        http_count_transfer (tcb-> http.file_size);
     }
}


/*************************   LOOK FOR RANGE HEADER   *************************/

MODULE look_for_range_header (THREAD *thread)
{
    char
        *header_value;
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Look for a header 'Range:'.  It must start with 'bytes='             */
    header_value = http_header_value (&tcb-> http, "Range");
    tcb-> range = strdefix (header_value, "bytes=");
    if (tcb-> range)
        the_next_event = ok_event;
    else
        the_next_event = not_found_event;
}


/************************   LOOK FOR RANGE IF HEADER   ***********************/

MODULE look_for_range_if_header (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_unmodified_since (&tcb-> http, tcb-> http.file_name, "If-Range"))
        the_next_event = ok_event;
    else
        the_next_event = modified_event;
}


/************************   GET NEXT RANGE SPECIFIER   ***********************/

MODULE get_next_range_specifier (THREAD *thread)
{
    char
        *range_from,
        *range_to;
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Point to start and end of range                                      */
    range_from = tcb-> range;
    range_to   = tcb-> range;
    while (isdigit (*range_to))
        range_to++;
    if (*range_to == '-')
        range_to++;

    if (isdigit (*range_from))         /*  Have from-[to] byte range        */
      {
        tcb-> range_from = atol (range_from);
        if (isdigit (*range_to))
            tcb-> range_to = atol (range_to);
        else
            tcb-> range_to = tcb-> http.file_size - 1;
            
        the_next_event = more_event;
      }
    else                      
    if (*range_from == '-')             /*  Have -suffix byte range          */
      {
        tcb-> range_from = tcb-> http.file_size - atol (range_to);
        tcb-> range_to   = tcb-> http.file_size - 1;
        if (tcb-> range_from < 0)
            tcb-> range_from = 0;
        the_next_event = more_event;
      }
    else
        the_next_event = finished_event;
        
    /*  Find start of next range specifier, if any                           */
    while (isdigit (*range_to) || *range_to == ',')
        range_to++;
    tcb-> range = range_to;
}


/************************   WRITE HTTP RANGE HEADER   ************************/

MODULE write_http_range_header (THREAD *thread)
{
    char
        range_string [40];
        
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sprintf (range_string, "bytes %ld-%ld/%ld",
             tcb-> range_from, tcb-> range_to, tcb-> http.file_size);
    xstrcat (tcb-> buffer,
        "--", MULTIPART_DELIM, eoln,
        "Content-type: ", http_get_mime_type (&tcb-> http), eoln,
        "Content-range: ", range_string, eoln,
        eoln, NULL);
                    
    if (tcb-> ssl_connection)
        send_ssl_write_request (
            &tcb-> sslq, 0,
            tcb-> handle,
            (word) strlen (tcb-> buffer), (byte *) tcb-> buffer, 0);
    else
        send_write (
            &sockq, 0,
            tcb-> handle,
            (word) strlen (tcb-> buffer), (byte *) tcb-> buffer, 0);

    event_wait ();                      /*  Wait for socket agent reply      */
}


/*************************   WRITE HTTP RANGE BODY   *************************/

MODULE write_http_range_body (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
      
    /*  If server:debug is set, log the transmission data                    */
    trace ("Transfer range=%s from=%ld to=%ld",
            tcb-> http.file_name, tcb-> range_from, tcb-> range_to);

    if (tcb-> ssl_connection)
        send_ssl_put_slice (&tcb-> sslq,
                             tcb-> handle,
                             tcb-> http.file_name,
                             tcb-> range_from, tcb-> range_to);
    else
        send_put_file      (&tranq, 
                             tcb-> handle,
                             tcb-> http.file_name, 0,
                             tcb-> range_from, tcb-> range_to,
                             CONFIG ("server:pipe"));

    http_count_transfer (tcb-> range_to - tcb-> range_from);
}


/************************   WRITE HTTP RANGE FOOTER   ************************/

MODULE write_http_range_footer (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    xstrcpy (tcb-> buffer, eoln, "--", MULTIPART_DELIM, "--", eoln, NULL);
    if (tcb-> ssl_connection)
        send_ssl_write_request (
            &tcb-> sslq, 0,
            tcb-> handle,
            (word) strlen (tcb-> buffer), (byte *) tcb-> buffer, 0);
    else
        send_write (
            &sockq, 0,
            tcb-> handle,
            (word) strlen (tcb-> buffer), (byte *) tcb-> buffer, 0);

    event_wait ();                      /*  Wait for socket agent reply      */
}


/**************************   CHECK IF KEEP ALIVE   **************************/

MODULE check_if_keep_alive (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> http.keep_alive
    &&  socket_is_alive (tcb-> handle))
        the_next_event = ok_event;
    else
        the_next_event = close_event;
}


/***********************   PARTIAL CLEAR HTTP CONTEXT   **********************/

MODULE partial_clear_http_context (THREAD *thread)
{
    int
        max;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    max = tcb-> http.keep_alive_max - 1;
    memset (tcb-> buffer, 0, BUFFER_SIZE);
    tcb-> read_size = 0;

    http_free_context (&tcb-> http);
    http_init_context (&tcb-> http);
    tcb-> http.port   = atoi (master_port) + ip_portbase;
    tcb-> http.socket = tcb-> handle;
    tcb-> http.keep_alive_max = max;
    tcb-> stats.username = NULL;
    tcb-> stats.request  = NULL;

    if (tcb-> post_file)
        close_post_file ();
}


/***************************   CREATE CGI PROCESS   **************************/

MODULE create_cgi_process (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_create_cgi_process (&tcb-> http) == 0)
        set_cgi_timeout (thread);
    else
        raise_exception (internal_error_event);
}


static void
set_cgi_timeout (THREAD *thread)
{
    long
        timeout;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> http.timeout_date = date_now ();
    tcb-> http.timeout_time = time_now ();
    timeout = atol (TCONFIG ("cgi:timeout"));
    if (timeout == 0)
        timeout = 3600;                 /*  Default is 1 hour                */
    timeout *= 100;                     /*  Get value in centiseconds        */

    future_date (&tcb-> http.timeout_date, &tcb-> http.timeout_time,
                 0, timeout);
}


/*************************   CREATE FILTER PROCESS   *************************/

MODULE create_filter_process (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_create_filter_process (&tcb-> http) == 0)
        set_cgi_timeout (thread);
    else
        raise_exception (internal_error_event);
}


/****************************   WAIT PROCESS END   ***************************/

MODULE wait_process_end (THREAD *thread)
{
    int
       state;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    state = http_process_state (&tcb-> http);
    if (state == CGI_STATE_END)         /*  CGI finished okay                */
        the_next_event = finished_event;
    else
    if (state == CGI_STATE_ERROR)       /*  CGI aborted                      */
        raise_exception (internal_error_event);
    else                                /*  CGI ran out of time              */
    if (date_is_past (tcb-> http.timeout_date, tcb-> http.timeout_time))
        raise_exception (overloaded_event);
    else                                /*  CGI is still running             */
        /*  Ask timer to send us an event after the monitor timeout          */
        send_alarm (&timeq, 0, atol (TCONFIG ("cgi:monitor")) / 10, 0, NULL);
}


/**************************   CLOSE CHILD PROCESS   **************************/

MODULE close_child_process (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    http_close_process (&tcb-> http);
}


/*************************   REPARSE PROCESS OUTPUT   ************************/

MODULE reparse_process_output (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_reparse_output (&tcb-> http))
        raise_exception (redirect_event);
}


/***************************   REPARSE HTTP BODY   ***************************/

MODULE reparse_http_body (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (http_reparse_buffer (&tcb-> http, tcb-> http_body))
        raise_exception (redirect_event);
}


/**********************   UPDATE RESOURCE FROM REQUEST   *********************/

MODULE update_resource_from_request (THREAD *thread)
{
    tcb = thread-> tcb;

    /*  Resource must have been cleared by authorisation system              */
    if (tcb-> update_allowed)
      {
        if (http_update_resource (&tcb-> http))
            raise_exception (error_event);
      }
    else
        raise_exception (forbidden_event);
}


/***************************   INSTALL WSX ALIAS   ***************************/

MODULE install_wsx_alias (THREAD *thread)
{
    /*  The wsx_symbol table holds dynamic WSX aliases.  Each symbol is
     *  stored in the form "vhost:alias=agent" as specified by the
     *  WSX_INSTALL message.  When no virtual host is specified, the
     *  symbol is stored with the VHOST_ANY virtual host name.
     *
     *  This table is always kept sorted.  Alias names are normalised to
     *  lowercase with hyphens replaced by underlines, to allow consistent
     *  lookups and comparisons.
     *
     *  For ease of searching, the symbol table is held in the same format
     *  as loaded ini files.  That is, for each different virtual host, a
     *  symbol is defined with the name "vhost" and no value.
     */

    struct_smt_wsx_install
        *request;
    char
        *virtual_host,
        *alias_path;                    /*  vhost:path                       */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_smt_wsx_install (thread-> event-> body, &request);

    alias_path   = make_wsx_path (request-> virtual_host, request-> path);
    virtual_host = *request-> virtual_host? request-> virtual_host: VHOST_ANY;

    sym_assume_symbol (wsx_aliases, alias_path, request-> agent);
    sym_assume_symbol (wsx_aliases, virtual_host, "");
    sym_sort_table    (wsx_aliases, NULL);

    mem_free (alias_path);
    free_smt_wsx_install (&request);
}

static char *
make_wsx_path (char *virtual_host, char *path)
{
    if (virtual_host == NULL || strnull (virtual_host))
        virtual_host = VHOST_ANY;
    if (path [0] == '/' && path [1])
        path++;                         /*  Skip '/' at start of path        */

    xstrcpy_debug ();
    path = xstrcpy (NULL, virtual_host, ":", path, NULL);
    strlwc (path);
    return (path);
}


/****************************   CANCEL WSX ALIAS   ***************************/

MODULE cancel_wsx_alias (THREAD *thread)
{
    struct_smt_wsx_cancel
        *request;
    char
        *alias_path;                    /*  vhost:path                       */
    SYMBOL
        *symbol;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_smt_wsx_cancel (thread-> event-> body, &request);
    alias_path = make_wsx_path (request-> virtual_host, request-> path);
    symbol = sym_lookup_symbol (wsx_aliases, alias_path);
    if (symbol)
        sym_delete_symbol (wsx_aliases, symbol);
    mem_free (alias_path);
    free_smt_wsx_cancel (&request);
}


/***********************   PASS REQUEST TO WSX AGENT   ***********************/

MODULE pass_request_to_wsx_agent (THREAD *thread)
{
    char
        *redirect,                      /*  Redirection filename             */
        *form_data,                     /*  Data to send to agent            */
        *virtual_host;                  /*  Name of virtual host, if any     */
    THREAD
        *wsx_thread;                    /*  Handle to WSX agent thread       */
    DESCR
        *request_symbols,               /*  HTTP header symbol table         */
        *config_symbols;                /*  HTTP config symbol table         */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Look for WSX agent thread                                            */
    if ((wsx_thread = thread_lookup (tcb-> http.wsx_agent, "main")) == NULL)
        raise_exception (not_implemented_event);
    else
      {
        /*  POSTed data may be in a temporary file, or in the http block     */
        if (tcb-> http.cgi_stdin)
          {
            xstrcpy_debug ();
            redirect = xstrcpy (NULL, "@", tcb-> http.cgi_stdin, NULL);
            form_data = redirect;
          }
        else
          {
            redirect = NULL;
            form_data = tcb-> http.post_data;
          }
        if (streq (tcb-> http.vhost, VHOST_ANY))
            virtual_host = NULL;
        else
            virtual_host = tcb-> http.vhost;

        request_symbols = http_wsx_symbols (&tcb-> http);
        config_symbols  = symb2descr (tcb-> http.config);
        if (request_symbols && config_symbols)
            /*  Pass URL, url-param, and symbol table to WSX agent           */
            send_wsx_request (
                &wsx_thread-> queue-> qid,
                tcb-> http.url,         /*  Requested URL                    */
                tcb-> http.url_param,   /*  Arguments following URL          */
                virtual_host,           /*  Virtual host name, if any        */
                tcb-> http.file_name,   /*  Request filename                 */
                form_data,              /*  POSTed data, if any              */
                (word) request_symbols-> size,
                request_symbols-> data,
                (word) config_symbols-> size,
                config_symbols-> data);
        else
            raise_exception (error_event);

        mem_free (request_symbols);
        mem_free (config_symbols);
        mem_strfree (&redirect);
      }
}


/*************************   GET WSX RETURN FIELDS   *************************/

MODULE get_wsx_return_fields (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up WSX reply body from event body, encoded as SMT_WSX_OK.  If
     *  the first character of the reply is '@', it refers to a temporary
     *  file containing the HTTP data.  Otherwise the event body is sent
     *  as-is.
     */
    exdr_read (thread-> event-> body, SMT_WSX_OK, &tcb-> http_body);
    if (tcb-> http_body [0] == '@')     /*  HTTP data is in a file           */
      {
        mem_strfree (&tcb-> http.file_name);
        tcb-> http.file_name = mem_strdup (tcb-> http_body + 1);
        mem_strfree (&tcb-> http_body);
        tcb-> http.temp_file = TRUE;
        the_next_event = wsx_redirect_event;
      }
    else
      {
        tcb-> http.file_size = strlen (tcb-> http_body);
        the_next_event = wsx_ok_event;
      }
}


/***********************   GET WSX BIN RETURN FIELDS   ***********************/

MODULE get_wsx_bin_return_fields (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up WSX reply body from event body, encoded as SMT_WSX_BIN.
     */
    exdr_read (thread-> event-> body, SMT_WSX_BIN,
               &tcb-> http.file_size, &tcb-> http_body);
    the_next_event = wsx_ok_event;
}


/**************************   GET WSX ERROR FIELDS   *************************/

MODULE get_wsx_error_fields (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up HTTP error code from event body, encoded as SMT_WSX_ERROR    */
    exdr_read (thread-> event-> body, SMT_WSX_ERROR, &tcb-> http.response);
}


/************************   GET WSX REDIRECT FIELDS   ************************/

MODULE get_wsx_redirect_fields (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up redirected URL event body, encoded as SMT_WSX_REDIRECT       */
    mem_strfree (&tcb-> http.url);
    exdr_read (thread-> event-> body, SMT_WSX_REDIRECT, &tcb-> http.url);
    tcb-> http.response = HTTP_RESPONSE_FOUND;
}


/****************************   WRITE HTTP BODY   ****************************/

MODULE write_http_body (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> http_body
    &&  tcb-> http.method != HTTP_METHOD_HEAD)
      {
        if (tcb-> ssl_connection)
            send_ssl_write_request (
                &tcb-> sslq, tcb-> output_timeout,
                tcb-> handle,
                (word) tcb-> http.file_size,
                (byte *) (tcb-> http_body + tcb-> http.file_offset), 0);
        else
            send_write (
                &sockq, tcb-> output_timeout,
                tcb-> handle,
                (word) tcb-> http.file_size,
                (byte *) (tcb-> http_body + tcb-> http.file_offset), 0);

        http_count_transfer (tcb-> http.file_size);
        mem_strfree (&tcb-> http_body);
        event_wait ();                  /*  Wait for socket agent reply      */
      }
}


/***********************   SEND MASTER THREAD RESTART   **********************/

MODULE send_master_thread_restart (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    SEND (&mainq, "_RESTART", "");
}


/**********************   SEND MASTER THREAD SHUTDOWN   **********************/

MODULE send_master_thread_shutdown (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    server_killed = TRUE;
    SEND (&mainq, "SHUTDOWN", "");
}


/***********************   OPEN SSL SOCKET IF NEEDED   ***********************/

MODULE open_ssl_socket_if_needed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (server_secure)
        send_ssl_open (&sslq, CONFIG ("ssl-http:config-file"));
}


/**************************   GET SSL MASTER PORT   **************************/

MODULE get_ssl_master_port (THREAD *thread)
{
    struct_ssl_open_ok
        *open_ok_msg;                   /*  OPEN_OK message                  */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    get_ssl_open_ok (thread-> event-> body, &open_ok_msg);
    ssl_port = open_ok_msg-> port;
    free_ssl_open_ok (&open_ok_msg);
}


/************************   CREATE SSL CHILD THREAD   ************************/

MODULE create_ssl_child_thread (THREAD *thread)
{
    THREAD
        *child_thread;                  /*  Handle to child threads          */
    TCB
        *child_tcb;                     /*  TCB of child thread              */
    struct_ssl_accepted
        *accept_msg;                    /*  ACCEPT message parameters        */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    child_thread = thread_create (AGENT_NAME, "");
    if (child_thread)
      {
        SEND (&child_thread-> queue-> qid, "_CLIENT", "");
        get_ssl_accepted (thread-> event-> body, &accept_msg);
        child_tcb = (TCB *) child_thread-> tcb;
        child_tcb-> thread_type    = client_event;
        child_tcb-> handle         = 0;
        child_tcb-> sslq           = thread-> event-> sender;
        child_tcb-> ssl_connection = TRUE;
        child_tcb-> ssl_username   = mem_strdup (accept_msg-> user);
        child_tcb-> handle         = accept_msg-> socket;
        free_ssl_accepted (&accept_msg);

        connect_count++;                /*  Maintain statistics              */
        cur_connects++;                 /*  One more active connection       */
        if (max_connects < cur_connects)
            max_connects = cur_connects;
      }
}


/***********************   RESTART SSL AGENT IF REQD   ***********************/

MODULE restart_ssl_agent_if_reqd (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (server_secure)
        send_ssl_restart (&sslq);
}


/**********************   KILL ALL ACTIVE CONNECTIONS   **********************/

MODULE kill_all_active_connections (THREAD *thread)
{
    QUEUE
        *queue;                         /*  Task control block               */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  We send a CANCEL event to all threads; the master thread ignores it  */
    for (queue = this_agent-> queues.next;
        (void *) queue != &(this_agent-> queues.next);
         queue = queue-> next)
        SEND (&queue-> qid, "_CANCEL", "");
}


/*********************   WAIT FOR CONNECTIONS TO CLOSE   *********************/

MODULE wait_for_connections_to_close (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Wait for one second                                                  */
    send_alarm (&timeq, 0, 100, 0, NULL);
}


/*************************   SIGNAL PARTIAL CONTENT   ************************/

MODULE signal_partial_content (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_PARTIAL;
    write_http_header (thread);
}


/************************   SIGNAL URL UNAUTHORIZED   ************************/

MODULE signal_url_unauthorized (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_UNAUTHORIZED;
    write_http_header (thread);
}


/**************************   SIGNAL URL FORBIDDEN   *************************/

MODULE signal_url_forbidden (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_FORBIDDEN;
    write_http_header (thread);
}


/*************************   SIGNAL NOT IMPLEMENTED   ************************/

MODULE signal_not_implemented (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_NOTIMPLEMENTED;
    write_http_header (thread);
}


/**************************   SIGNAL NOT MODIFIED   **************************/

MODULE signal_not_modified (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_NOTMODIFIED;
    write_http_header (thread);
}


/**************************   SIGNAL PRECONDITION   **************************/

MODULE signal_precondition (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_PRECONDITION;
    write_http_header (thread);
}


/***************************   SIGNAL BAD REQUEST   **************************/

MODULE signal_bad_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_BADREQUEST;
    write_http_header (thread);
}


/**************************   SIGNAL URL NOT FOUND   *************************/

MODULE signal_url_not_found (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_NOTFOUND;
    write_http_header (thread);
}


/****************************   SIGNAL TOO LARGE   ***************************/

MODULE signal_too_large (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_TOOLARGE;
    write_http_header (thread);
}


/*************************   SIGNAL INTERNAL ERROR   *************************/

MODULE signal_internal_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_INTERNALERROR;
    write_http_header (thread);
}


/***************************   SIGNAL OVERLOADED   ***************************/

MODULE signal_overloaded (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> http.response = HTTP_RESPONSE_OVERLOADED;
    write_http_header (thread);
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    sendfmt (&operq, "ERROR", "smthttp: socket %d aborted, closed", (int) tcb-> handle);
}


/**************************   SIGNAL SOCKET CLOSED   *************************/

MODULE signal_socket_closed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    http_message ("HTTP socket was closed: %s", sockmsg ());
    sendfmt (&operq, "ERROR", server_message);
}


/***************************   CHECK SOCKET TYPE   ***************************/

MODULE check_socket_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = tcb-> thread_type;
}


/*********************   PREPARE TO CLOSE MASTER SOCKET   ********************/

MODULE prepare_to_close_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> http.port)
      {
        sendfmt (&operq, "INFO",
            "smthttp: closing HTTP service on port %d", tcb-> http.port);
        send_flush (&sockq, tcb-> handle);
      }
}


/***********************   FREE ALL SERVER RESOURCES   ***********************/

MODULE free_all_server_resources (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Pointer to symbol                */
    VHOST
        *vhost;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Free main resources used by the web server                           */
    if (vhosts)
      {
        for (symbol = vhosts-> symbols; symbol; )
          {
            vhost = symbol-> data;
            if (vhost-> acclog.owner)
                SEND (&vhost-> acclog.queue, "CLOSE", "");
            if (vhost-> errlog.owner)
                SEND (&vhost-> errlog.queue, "CLOSE", "");
            symbol = vhost_free (symbol);
          }
        sym_delete_table (vhosts);      /*    and finally, entire table      */
      }
    if (server_logging)
        sendfmt (&clogq, "CLOSE", "");
}


/************************   SHUTDOWN THE APPLICATION   ***********************/

MODULE shutdown_the_application (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Free all resources used by the web server                            */
    mem_strfree (&request_log);         /*  Debug log file - requests        */
    mem_strfree (&header_log);          /*  Debug log file - replies         */
    mem_free (hostaddrs);
    http_term ();                       /*  Terminate HTTP library           */
    smt_shutdown ();                    /*  Halt the application             */
}


/*************************   FLUSH SOCKET REQUESTS   *************************/

MODULE flush_socket_requests (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_flush (&sockq, tcb-> handle);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    mem_strfree (&tcb-> buffer);
    mem_strfree (&tcb-> ssl_username);
    if (tcb-> handle)
      {
        close_socket (tcb-> handle);
        tcb-> handle = 0;
      }
    if (tcb-> post_file)
        close_post_file ();

    if (tcb-> thread_type == client_event)
        cur_connects--;                 /*  One less active connection       */

    if (tcb-> ssl_connection)
        send_ssl_close (&tcb-> sslq);

    http_free_context (&tcb-> http); 
    the_next_event = terminate_event;
}


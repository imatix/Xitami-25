/*===========================================================================*
 *                                                                           *
 *  smtftpc.c -                                                              *
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
#include "smthttpl.h"                   /*  SMT HTTP definitions             */
#include "smtftpl.h"                    /*  SMT FTP declarations             */
#include "smtmsg.h"                     /*  SMT message functions            */
#include "xixlog.h"                     /*  Xitami logging interface         */


/*- Definitions -------------------------------------------------------------*/

#ifdef AGENT_NAME
#undef AGENT_NAME
#endif

#define AGENT_NAME   SMT_FTPC           /*  Our public name                  */
#define BUFFER_SIZE  4096

/*  TCONFIG gets configuration for user before virtual host is known         */
#define TCONFIG(s)      http_config (tcb-> config, (s))
/*  VCONFIG gets configuration for user in current virtual host              */
#define VCONFIG(s)      http_config (vhost-> config, (s))

/*  Macros to access permission bits for current ftp.file_name               */
#define ALLOW_ACCESS(a) ((ftpc_permissions (&tcb-> ftp, \
                          tcb-> ftp.file_name, TRUE) \
                          & (a)) != 0)
#define ALLOW_GET       ALLOW_ACCESS(FTP_AUTH_GET)
#define ALLOW_PUT       ALLOW_ACCESS(FTP_AUTH_PUT)
#define ALLOW_UPLOAD    ALLOW_ACCESS(FTP_AUTH_UPLOAD)
#define ALLOW_DELETE    ALLOW_ACCESS(FTP_AUTH_DELETE)


typedef struct {                        /*  Logging control block            */
    QID
        queue;                          /*    Log queue                      */
    char
        *filename;                      /*    Log filename                   */
    Bool
        owner;                          /*    This thread created log?       */
} LOGCTL;

typedef struct                          /*  Thread context block:            */
{
    HTTP_STAT
        stats;                          /*    Statistics structure           */
    sock_t
        handle;                         /*    Handle for i/o                 */
    int
        read_size,                      /*    Size of input message          */
        portbase;                       /*    Index for portbase attempts    */
    SYMTAB                              /*                                   */
        *config,                        /*    Configuration for host         */
        *users,                         /*    Users file                     */
        *direct;                        /*    Directory access file          */
    LOGCTL
        *acclog,                        /*    Access log                     */
        *errlog;                        /*      and error log for thread     */
    word
        input_timeout;                  /*    Timeout for input and output   */
    long
        request_time;                   /*    Time that request started      */
    char
        *rootdir,                       /*    FTP rootdir for session        */
        *webmask,                       /*    Security webmask               */
        *vhost,                         /*    Name of virtual host           */
        *buffer,                        /*    Buffer for i/o                 */
        *request;                       /*    FTP command for logging        */
    event_t
        thread_type;                    /*    Thread type indicator          */
    FTP_CONTROL_CTX
        ftp;                            /*    FTP control context            */
    dbyte
        data_port;                      /*    Default data port              */
} TCB;

typedef struct {                        /*  Virtual host resources           */
    SYMTAB                              /*                                   */
        *config,                        /*    Configuration for host         */
        *users,                         /*    Users file                     */
        *direct;                        /*    Directory access file          */
    char
        *name,                          /*    Virtual host name              */
        *rootdir,                       /*    Web pages root directory       */
        *webmask;                       /*    Security webmask               */
    LOGCTL
        acclog,                         /*    Access log control block       */
        errlog;                         /*    Error log control block        */
} VHOST;


/*- Function prototypes -----------------------------------------------------*/

static void   load_config_file     (SYMTAB *table, char *filename);
static VHOST *create_vhost         (THREAD *thread, char *name, char *file);
static void   set_vhost_name       (SYMTAB *table, char *name);
static void   create_log_thread    (THREAD *thread, VHOST *vhost,
                                    char *prefix, LOGCTL *logctl);
static void   inherit_config       (THREAD *thread, VHOST *vhost);
static void   inherit_vhost        (THREAD *thread, SYMBOL *vhost_sym);
static void   log_ftp_access       (THREAD *thread);
static void   log_access           (THREAD *thread, QID *queue);


/*- Global variables used in this source file only --------------------------*/

static TCB
    *tcb;                               /*  Address thread contect block     */
static QID
    operq,                              /*  Operator console event queue     */
    sockq,                              /*  Socket agent event queue         */
    dataq,                              /*  FTP data agent queue             */
    timeq;                              /*  Timer agent event queue          */
static AGENT
    *this_agent;                        /*  Handle to ourselves              */
static char
    *rootdir;                           /*  Root directory for FTP users     */
static qbyte
    *hostaddrs;                         /*  List of host addresses           */

static char
    buffer [BUFFER_SIZE];               /*  General-use string buffer        */
extern SYMTAB
    *config;                            /*  Global config file               */
static SYMTAB
    *vhosts;                            /*  Virtual hosts table              */


#include "smtftpc.d"                    /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtftpc_init

    Synopsis: Initialises the FTP control agent.  Returns 0 if initialised
    okay, -1 if there was an error.
    ---------------------------------------------------------------------[>]-*/

int
smtftpc_init (char *p_rootdir)          /*  Server root directory            */
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */

#   include "smtftpc.i"                 /*  Include dialog interpreter       */

    /*                      Method name      Event value     Priority        */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",       shutdown_event,
                                             SMT_PRIORITY_MAX);

    /*  Restart can come from control panel and HTTP agent                   */
    method_declare (agent, "RESTART",        restart_event,   0);
    method_declare (agent, "RELOAD",         reload_event,    0);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  input_ok_event,     0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,           0);
    method_declare (agent, "SOCK_READ_OK",   ok_event,           0);
    method_declare (agent, "SOCK_WRITE_OK",  ok_event,           0);
    method_declare (agent, "SOCK_CLOSED",    sock_closed_event,  0);
    method_declare (agent, "SOCK_ERROR",     sock_error_event,   0);
    method_declare (agent, "SOCK_TIMEOUT",   sock_timeout_event, 0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",     timeout_event,
                                             SMT_PRIORITY_LOW);
    /*  Reply events from FTP data agent                                     */
    method_declare (agent, "FTPD_CONNECTED", connected_event,
                                             SMT_PRIORITY_LOW);
    method_declare (agent, "FTPD_ERROR",     error_event,
                                             SMT_PRIORITY_LOW);
    method_declare (agent, "FTPD_END",       end_event,
                                             SMT_PRIORITY_HIGH);
    method_declare (agent, "FTPD_PASS_OK",   ok_event,
                                             SMT_PRIORITY_LOW);
    method_declare (agent, "FTPD_ABORTED",   aborted_event,
                                             SMT_PRIORITY_HIGH);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",        master_event,    0);
    method_declare (agent, "_CLIENT",        client_event,    0);

    /*  Private methods used between threads                                 */
    method_declare (agent, "_CANCEL",        cancel_event,    0);

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

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that FTP data agent is running, else start it up              */
    smtftpd_init ();
    if ((thread = thread_lookup (SMT_FTPD, "")) != NULL)
        dataq = thread-> queue-> qid;
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

    ftp_initialise ();

    /*  Get root directory                                                   */
    rootdir = mem_strdup (p_rootdir);

    /*  Get local host addresses table, which may be NULL                    */
    hostaddrs = get_hostaddrs ();

    /*  Signal to caller that we initialised okay                            */
    return (0);
}


/***********************   CHECK THAT HTTP IS ACTIVE   ***********************/

MODULE check_that_http_is_active (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (thread_lookup ("smthttp", "main") == NULL)
        raise_exception (shutdown_event);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> buffer   = NULL;
    tcb-> portbase = 0;                 /*  Not serving any port             */
    tcb-> config   = config;
    tcb-> acclog   = NULL;
    tcb-> errlog   = NULL;
    tcb-> rootdir  = NULL;
    tcb-> webmask  = NULL;
    tcb-> vhost    = NULL;
    tcb-> users    = NULL;
    tcb-> direct   = NULL;
    tcb-> request  = NULL;
    
    ftpc_init_connection (&tcb-> ftp, tcb-> handle);
}


/************************   INITIALISE MASTER THREAD   ***********************/

MODULE initialise_master_thread (THREAD *thread)
{
    long
        max_threads;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    tcb-> stats.client  = FALSE;
    tcb-> input_timeout = 0;

    /*  Get maximum connections                                              */
    max_threads = atoi (CONFIG ("ftp:limit"));
    if (max_threads > 0)
        this_agent-> max_threads = max_threads + 1;
}


/**************************   CHECK IF FTP ENABLED   *************************/

MODULE check_if_ftp_enabled (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (*CONFIG ("ftp:enabled") == '1')
        the_next_event = ok_event;
    else
        the_next_event = disabled_event;
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

            /*  Host may not be defined more than once                       */
            if (sym_lookup_symbol (vhosts, vhost_name))
              {
                http_message ("Duplicate host '%s'", vhost_name);
                sendfmt (&operq, "ERROR", server_message);
              }
            else
            if (file_is_readable (vhost_file))
              {
                vhost = create_vhost (thread, vhost_name, vhost_file);
                vhost-> rootdir = mem_strdup (
                   sym_get_value (vhost-> config, "ftp:root", rootdir));
              }
            else
              {
                http_message ("Config file '%s' not found - %s",
                               vhost_file, strerror (errno));
                sendfmt (&operq, "ERROR", server_message);
              }
          }
      }
    vhost = create_vhost (thread, VHOST_ANY, CONFIG ("server:base-host"));

    /*  Resolve options that can come both from command-line & config file:
     *  If these were specified on the command-line or control panel AND
     *  were not the same as the default values, we look in the config
     *  file.  If both the command-line and config file specify non-default
     *  values, the command-line wins.
     */
    if (streq (rootdir, DEFAULT ("ftp:root")))
      {
        mem_strfree (&rootdir);
        rootdir = resolve_path (VCONFIG ("ftp:root"));
      }
    /*  Set rootdir for default host                                         */
    vhost-> rootdir = mem_strdup (rootdir);
    inherit_config (thread, vhost);
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


static VHOST *
create_vhost (THREAD *thread, char *vhost_name, char *vhost_file)
{
    VHOST
        *vhost;
    SYMBOL
        *vhsym;                         /*  Virtual host entry in table      */
        
    /*  Create new symbol for virtual host                                   */
    vhsym = sym_create_symbol (vhosts, vhost_name, NULL);
    vhost = mem_alloc (sizeof (VHOST));
    vhsym-> data = vhost;
    vhost-> name = mem_strdup (vhost_name);

    /*  Load config file, inheriting xitami.cfg and defaults.cfg             */
    vhost-> config = sym_create_table ();
    load_config_file (vhost-> config, vhost_file);
    set_vhost_name   (vhost-> config, vhost_name);

    /*  Get list of users and directory access permissions                   */
    vhost-> users  = ini_dyn_load (NULL, VCONFIG ("ftp:user-file"));
    vhost-> direct = ini_dyn_load (NULL, VCONFIG ("ftp:directory-file"));

    /*  Set webmask for virtual host                                         */
    vhost-> webmask = http_webmask (VCONFIG ("ftp:webmask"), 0);

    /*  Create logging threads as required                                   */
    create_log_thread (thread, vhost, "ftplog",    &vhost-> acclog);
    create_log_thread (thread, vhost, "ftperrlog", &vhost-> errlog);

    return (vhost);
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
 *  inherit_config
 *
 *  Inherits configuration and logging data from the virtual host.
 */

static void
inherit_config (THREAD *thread, VHOST *vhost)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Set TCB for master thread to use default resources                   */
    tcb-> config = vhost-> config;
    tcb-> users  = vhost-> users;
    tcb-> direct = vhost-> direct;
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
        http_message ("FTP root '%s' not found - %s", rootdir, strerror (errno));
        sendfmt (&operq, "ERROR", server_message);
        raise_exception (no_rootdir_event);
      }
}


/***************************   OPEN MASTER SOCKET   **************************/

MODULE open_master_socket (THREAD *thread)
{
    char
        *master_port;                   /*  Port for http service            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  If the server:ipaddress is '*' we accept all addresses, otherwise    */
    /*  we limit the connections to the specified address.                   */
    if (*CONFIG ("server:ipaddress") == '*')
        ip_passive = INADDR_ANY;
    else
        ip_passive = inet_addr (CONFIG ("server:ipaddress"));

    if (ip_portbase == 0)
        ip_portbase = atoi (CONFIG ("server:portbase"));

    /*  We try the main ip_portbase only                                     */
    master_port = CONFIG ("ftp:port");
    tcb-> ftp.port = atoi (master_port) + ip_portbase;
    tcb-> handle   = passive_TCP (master_port, 5);
    sendfmt (&operq, "INFO",
                     "smtftpc: opening FTP service on port %d...",
                      tcb-> ftp.port);

    if (tcb-> handle != INVALID_SOCKET)
        sendfmt (&operq, "INFO", "smtftpc: FTP service is now running");
    else
      {
        sendfmt (&operq, "ERROR", "smtftpc: could not open port %d",
                 tcb-> ftp.port);
        sendfmt (&operq, "ERROR", "smtftpc: %s",
                 connect_errlist [connect_error ()]);
        sendfmt (&operq, "ERROR", "smtftpc: %s", sockmsg ());
        raise_exception (exception_event);
        http_message ("Could not open port %d - %s (%s)",
                      tcb-> ftp.port,
                      connect_errlist [connect_error ()],
                      sockmsg ());
      }
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
            ((TCB *) child_thread-> tcb)-> thread_type = client_event;
            ((TCB *) child_thread-> tcb)-> handle      = slave_socket;
            connect_count++;            /*  Maintain statistics              */
            cur_connects++;             /*  One more active connection       */
            ftp_connects++;
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
        sendfmt (&operq, "ERROR",
                 "smtftpc: could not accept connection: %s", sockmsg ());
        raise_exception (exception_event);
      }
}


/************************   RESOLVE IP VIRTUAL HOST   ************************/

MODULE resolve_ip_virtual_host (THREAD *thread)
{
    char
        *vhost_name;                    /*  Name of virtual host             */
    SYMBOL
        *vhost_sym = NULL;              /*  Virtual host entry in table      */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    vhost_name = socket_localaddr  (tcb-> handle);
    vhost_sym  = sym_lookup_symbol (vhosts, vhost_name);

    /*  If that failed, use VHOST_ANY host name                              */
    if (!vhost_sym)
        vhost_sym = sym_lookup_symbol (vhosts, VHOST_ANY);

    /*  Use virtual host resources                                           */
    inherit_vhost (thread, vhost_sym);
}


/*  -------------------------------------------------------------------------
 *  inherit_vhost
 *
 *  Inherits configuration, logging, and other virtual host properties.
 */

static void
inherit_vhost (THREAD *thread, SYMBOL *vhost_sym)
{
    VHOST
        *vhost;                         /*  Virtual host resource block      */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ASSERT (vhost_sym);

    vhost = vhost_sym-> data;
    inherit_config (thread, vhost);

    mem_strfree (&tcb-> webmask);
    mem_strfree (&tcb-> rootdir);
    mem_strfree (&tcb-> vhost);
    tcb-> rootdir = mem_strdup (vhost-> rootdir);
    tcb-> webmask = mem_strdup (vhost-> webmask);
    tcb-> vhost   = mem_strdup (vhost_sym-> name);
    
    tcb-> ftp.config = vhost-> config;
    tcb-> ftp.users  = vhost-> users;
    tcb-> ftp.direct = vhost-> direct;
}


/************************   CHECK CLIENT IP ALLOWED   ************************/

MODULE check_client_ip_allowed (THREAD *thread)
{
    char
        *webmask;                       /*  Permitted mask for connection    */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    webmask = tcb-> webmask;
    if (streq (webmask, "local"))
        webmask = socket_localaddr (tcb-> handle);

    if (!socket_is_permitted (socket_peeraddr (tcb-> handle), webmask))
        raise_exception (unauthorised_event);
}


/************************   INITIALISE CLIENT THREAD   ***********************/

MODULE initialise_client_thread (THREAD *thread)
{
    char
        *config_ip;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  If timeout is zero, it's infinite; anything else must be >= 10s      */
    tcb-> ftp.timeout = atol (TCONFIG ("ftp:timeout")) * 100;
    if (tcb-> ftp.timeout > 0
    &&  tcb-> ftp.timeout < 1000)
        tcb-> ftp.timeout = 1000;

    /*  Set IP address of control thread                                     */
    if (*TCONFIG ("ftp:force-ip") == '1')
        config_ip = sym_get_value (tcb-> config, "ftp:passiveip", TCONFIG ("ftp:ipaddress"));
    else
        config_ip = socket_localaddr (tcb-> handle);

    tcb-> ftp.ip_address = ntohl (inet_addr (config_ip));

    /*  Get default data port in passive connection mode                     */
    tcb-> data_port = (dbyte) atoi (TCONFIG ("ftp:data-port"));
    tcb-> input_timeout  = 0;
    tcb-> request_time   = time_now ();

    tcb-> stats.client   = TRUE;
    tcb-> stats.socket   = tcb-> handle;
    tcb-> stats.username = "";
    tcb-> stats.request  = "(Logging in)";

    tcb-> buffer = mem_alloc (BUFFER_SIZE + 1);
    if (tcb-> buffer == NULL)
      {
        sendfmt (&operq, "ERROR", "smtftpc: out of memory");
        raise_exception (exception_event);
      }
    else
        memset (tcb-> buffer, 0, BUFFER_SIZE + 1);
}


/*************************   WAIT FOR SOCKET INPUT   *************************/

MODULE wait_for_socket_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_input (&sockq, 0, tcb-> handle, 0);
}


/************************   RELOAD CONFIG IF NEEDED   ************************/

MODULE reload_config_if_needed (THREAD *thread)
{
    SYMBOL
        *symbol;                        /*  Pointer to symbol                */
    VHOST
        *vhost;
    char
        *vhost_file;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    for (symbol = vhosts-> symbols; symbol; symbol = symbol-> next)
      {
        vhost = symbol-> data;
        if (ini_dyn_changed (vhost-> config))
          {
            vhost_file = mem_strdup (sym_get_value
                             (vhost-> config, "filename", NULL));
            sym_empty_table  (vhost-> config);
            load_config_file (vhost-> config, vhost_file);
            set_vhost_name   (vhost-> config, vhost-> name);
            mem_free (vhost_file);

            /*  Set rootdir for this virtual host                            */
            mem_free (vhost-> rootdir);
            vhost-> rootdir = mem_strdup (
                sym_get_value (vhost-> config, "ftp:root", rootdir));

            mem_free (vhost-> webmask);
            vhost-> webmask = http_webmask (VCONFIG ("ftp:webmask"), 0);
          }
        ini_dyn_refresh (vhost-> users);
        ini_dyn_refresh (vhost-> direct);
      }
    /*  Also reload main config file                                         */
    if (ini_dyn_changed (config))
      {
        sym_empty_table  (config);
        load_config_file (config, CONFIG ("server:base-host"));
      }
}


/**************************   PREPARE TO GET INPUT   *************************/

MODULE prepare_to_get_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> read_size = 0;
}


/**************************   CHECK IF MORE INPUT   **************************/

MODULE check_if_more_input (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Want CRLF or LF in buffer                                            */
    if (strchr (tcb-> buffer, '\n') == NULL)
        raise_exception (sock_retry_event);
}


/****************************   READ FTP REQUEST   ***************************/

MODULE read_ftp_request (THREAD *thread)
{
    int
        rc;                             /*  Return code from read            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    rc = read_TCP (tcb-> handle, tcb-> buffer + tcb-> read_size,
                                 BUFFER_SIZE - tcb-> read_size);
    if (rc > 0)                     /*  We read something                    */
      {
        tcb-> read_size += rc;
        tcb-> buffer [tcb-> read_size] = '\0';
      }
    else
    if (rc == 0 || sockerrno == EPIPE || sockerrno == ECONNRESET)
        raise_exception (sock_closed_event);
    else
    if (sockerrno == EAGAIN || sockerrno == EWOULDBLOCK)
        raise_exception (sock_retry_event);
    else
        raise_exception (sock_error_event);
}


/****************************   GET FTP COMMAND   ****************************/

MODULE get_ftp_command (THREAD *thread)
{
    static struct {
        char    *name;
        event_t  event;
    } command [] = {
      { "ABOR", abort_event        },   /*  Abort                            */
      { "ACCT", unsupported_event  },   /*                                   */
      { "ALLO", unsupported_event  },   /*                                   */
      { "APPE", append_event       },   /*  Store file, with append          */
      { "CDUP", cdup_event         },   /*  Change to parent directory       */
      { "CWD",  cwd_event          },   /*  Change working directory         */
      { "DELE", delete_event       },   /*  Delete a file                    */
      { "HELP", help_event         },   /*  Display server help              */
      { "LIST", list_event         },   /*  Return directory listing         */
      { "MAIL", unsupported_event  },   /*                                   */
      { "MKD",  mkdir_event        },   /*  Make directory                   */
      { "MLFL", unsupported_event  },   /*                                   */
      { "MODE", mode_event         },   /*  Stream mode                      */
      { "MRCP", unsupported_event  },   /*                                   */
      { "MRSQ", unsupported_event  },   /*                                   */
      { "MSAM", unsupported_event  },   /*                                   */
      { "MSND", unsupported_event  },   /*                                   */
      { "MSOM", unsupported_event  },   /*                                   */
      { "NLST", names_event        },   /*  Name list                        */
      { "NOOP", noop_event         },   /*  Null operation                   */
      { "PASS", password_event     },   /*  User password                    */
      { "PASV", passive_event      },   /*  Request passive data connection  */
      { "PORT", port_event         },   /*  Data port                        */
      { "PWD",  pwd_event          },   /*  Print current directory          */
      { "QUIT", quit_event         },   /*  Logout                           */
      { "REIN", reinit_event       },   /*  Reinitialise connection          */
      { "REST", restart_event      },   /*  Set file restart position        */
      { "RETR", retrieve_event     },   /*  Retrieve file                    */
      { "RMD",  rmdir_event        },   /*  Remove directory                 */
      { "RNFR", rename_from_event  },   /*  Rename, source filename          */
      { "RNTO", rename_to_event    },   /*  Rename, destination filename     */
      { "SITE", unsupported_event  },   /*                                   */
      { "SIZE", size_event         },   /*  Get size of file                 */
      { "STAT", unsupported_event  },   /*                                   */
      { "STOR", store_event        },   /*  Store a file                     */
      { "STOU", unsupported_event  },   /*                                   */
      { "STRU", structure_event    },   /*  Set structure                    */
      { "SYST", system_event       },   /*  Return the OS type               */
      { "TYPE", type_event         },   /*  Representation type              */
      { "USER", user_event         },   /*  User name login                  */
      { "XCUP", unsupported_event  },   /*                                   */
      { "XCWD", cwd_event          },   /*  X change working directory       */
      { "XEXC", unsupported_event  },   /*                                   */
      { "XMKD", mkdir_event        },   /*  X Make directory                 */
      { "XPWD", pwd_event          },   /*  X print current directory        */
      { "XRMD", rmdir_event        },   /*  X Remove directory               */
      { "XSYS", unsupported_event  }    /*                                   */
     };
    char
        *cur_command,
        *line_ptr;
    int
        lower_limit,
        upper_limit,
        index;

    tcb = thread-> tcb;                 /*  Point to thread's context        */
    /*  Remove CR/LF at end of buffer                                        */
    line_ptr = tcb-> buffer + tcb-> read_size - 1;
    if (*line_ptr == '\n')
        *line_ptr-- = '\0';
    if (*line_ptr == '\r')
        *line_ptr-- = '\0';

    /*  If debug mode, trace the start of whatever was in the buffer         */
    strncpy (buffer, tcb-> buffer, 80);
    buffer [80] = '\0';
    trace ("FTP input: %s", buffer);

    mem_strfree (&tcb-> request);
    tcb-> request       = mem_strdup (tcb-> buffer);
    tcb-> stats.request = tcb-> request;

    /*  Get 4-char command from buffer                                       */
    cur_command = tcb-> ftp.command;
    memcpy (cur_command, tcb-> buffer, 4);
    if (tcb-> buffer [3] == ' ')
        cur_command [3] = '\0';
    else
        cur_command [4] = '\0';

    /*  Do binary search through the table                                   */
    lower_limit  = 0;
    upper_limit  = tblsize (command) - 1;
    index = (lower_limit + upper_limit) / 2;

    strupc (cur_command);               /*  Compare in uppercase             */
    until (streq (command [index].name, cur_command)
    ||     lower_limit > upper_limit)
      {
        index = (lower_limit + upper_limit) / 2;
        if (strcmp (command [index].name, cur_command) > 0)
            upper_limit = index - 1;
        else
        if (strcmp (command [index].name, cur_command) < 0)
            lower_limit = index + 1;
      }
    if (lower_limit <= upper_limit)     /*  Found?                           */
      {
        /*  Get parameters off original command, if they're present          */
        strcrop (tcb-> buffer);         /*  Remove trailing spaces if any    */
        line_ptr = strchr (tcb-> buffer, ' ');
        if (line_ptr)
          {
            *line_ptr++ = '\0';
            strconvch (line_ptr, '\\', '/');
            strunique (line_ptr, '/');
          }
        tcb-> ftp.parameters  = line_ptr;
        tcb-> ftp.return_code = FTP_RC_COMMAND_OK;
        the_next_event = command [index].event;
      }
    else
      {
        /*  Point parameters field to original command, for error message    */
        tcb-> ftp.parameters = tcb-> buffer;
        the_next_event = invalid_event;
      }
}


/**************************   WRITE RETURN MESSAGE   *************************/

MODULE write_return_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_return_message (&tcb-> ftp, buffer);
    send_write (&sockq, 0, tcb-> handle,
               (word) strlen (buffer), (byte *) buffer, 0);
}


/***********************   RESOLVE USER VIRTUAL HOST   ***********************/

MODULE resolve_user_virtual_host (THREAD *thread)
{
    char
        *vhost_name;                    /*  Name of virtual host             */
    SYMBOL
        *vhost_sym = NULL;              /*  Virtual host entry in table      */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Check if user name was specified as user@hostname                    */
    if (*TCONFIG ("ftp:user-at-host") == '1'
    &&  tcb-> ftp.parameters)
      {
        strlwc (tcb-> ftp.parameters);
        vhost_name = strchr (tcb-> ftp.parameters, '@');
        if (vhost_name)
          {
            *vhost_name = '\0';         /*  Truncate at '@' character        */
            vhost_name++;               /*    and bump up to vhost name      */
            vhost_sym = sym_lookup_symbol (vhosts, vhost_name);
            if (vhost_sym)
                inherit_vhost (thread, vhost_sym);
            else
                /*  Host not known -> user rejected                          */
                raise_exception (invalid_vhost_event);
          }
      }
}


/***************************   CHECK USER PROFILE   **************************/

MODULE check_user_profile (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (ftpc_get_user     (&tcb-> ftp)
    &&  ftpc_get_password (&tcb-> ftp))
      {
        /*  Empty password means we can consider the user logged-in          */
        if (strnull (tcb-> ftp.password))
            the_next_event = not_protected_event;
        else
            the_next_event = ok_event;
      }
    else
        the_next_event = error_event;   /*  Fatal error, e.g. in user file   */
}


/**************************   CHECK USER PASSWORD   **************************/

MODULE check_user_password (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (ftpc_verify_password (&tcb-> ftp))
        the_next_event = ok_event;
    else
        the_next_event = invalid_event;
}


/************************   INITIALISE USER SESSION   ************************/

MODULE initialise_user_session (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> stats.username = tcb-> ftp.user;
    tcb-> ftp.login = TRUE;
    ftpc_get_rootdir (&tcb-> ftp, tcb-> rootdir);
    ftpc_get_quotas  (&tcb-> ftp);
    ftpc_get_pipe    (&tcb-> ftp);
}


/***************************   CHECK USER QUOTAS   ***************************/

MODULE check_user_quotas (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.use_quotas)
      {
        if (tcb-> ftp.cur_usage > tcb-> ftp.hard_quota)
            sendfmt (&operq, "ERROR",
                     "smtftpc: user '%s' exceeded hard quota, %ld/%ld",
                                       tcb-> ftp.user,
                                       tcb-> ftp.cur_usage,
                                       tcb-> ftp.hard_quota);
        else
        if (tcb-> ftp.cur_usage > tcb-> ftp.soft_quota)
            sendfmt (&operq, "ERROR",
                     "smtftpc: user '%s' exceeded soft quota, %ld/%ld",
                                       tcb-> ftp.user,
                                       tcb-> ftp.cur_usage,
                                       tcb-> ftp.soft_quota);
      }
}


/************************   SET REPRESENTATION TYPE   ************************/

MODULE set_representation_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_set_type (&tcb-> ftp);
}


/***************************   SET STRUCTURE TYPE   **************************/

MODULE set_structure_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.parameters == NULL
    ||  tolower (*tcb-> ftp.parameters) != 'f')
        tcb-> ftp.return_code = FTP_RC_BAD_PARAMETER;
}


/*****************************   GET DATA PORT   *****************************/

MODULE get_data_port (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_get_port (&tcb-> ftp);
}


/**********************   MAKE FULL DIRECTORY LISTING   **********************/

MODULE make_full_directory_listing (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (!ftpc_make_listing (&tcb-> ftp, TRUE))
        raise_exception (error_event);
}


/**********************   MAKE BRIEF DIRECTORY LISTING   *********************/

MODULE make_brief_directory_listing (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (!ftpc_make_listing (&tcb-> ftp, FALSE))
        raise_exception (error_event);
}


/************************   CHECK IF TEMPORARY FILE   ************************/

MODULE check_if_temporary_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.temp_file)
      {
        if (tcb-> ftp.file_name)
            file_delete (tcb-> ftp.file_name);
        tcb-> ftp.temp_file = FALSE;
      }
}


/*****************************   MAKE FILE NAME   ****************************/

MODULE make_file_name (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_file_name (&tcb-> ftp, buffer);
    mem_strfree    (&tcb-> ftp.file_name);
    tcb-> ftp.file_name = ftpc_map_name (&tcb-> ftp, buffer);
}


/**************************   CHECK IF FILE EXISTS   *************************/

MODULE check_if_file_exists (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (file_exists       (tcb-> ftp.file_name)
    && !file_is_directory (tcb-> ftp.file_name))
      {
        the_next_event = ok_event;
        tcb-> ftp.file_size =
            get_file_size (tcb-> ftp.file_name);
      }
    else
        the_next_event = not_found_event;
}


/****************************   DELETE THE FILE   ****************************/

MODULE delete_the_file (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.file_name == NULL)
        tcb-> ftp.return_code = FTP_RC_SYNTAX_ERROR_PARAM;
    else
    if (ALLOW_DELETE)
      {
        if (file_delete (tcb-> ftp.file_name) == 0)
          {
            tcb-> ftp.return_code = FTP_RC_FILE_ACTION_OK;
            tcb-> ftp.cur_usage  -= tcb-> ftp.file_size;
          }
        else
            tcb-> ftp.return_code = FTP_RC_FILE_ACTION_NOT_TAKEN;
      }
    else
        raise_exception (unauthorised_event);
}


/****************************   RENAME THE FILE   ****************************/

MODULE rename_the_file (THREAD *thread)
{
    char
        *destname = NULL;               /*  Destination file name            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Get destination file name into buffer                                */
    ftpc_file_name (&tcb-> ftp, buffer);
    destname = ftpc_map_name (&tcb-> ftp, buffer);

    if (tcb-> ftp.file_name == NULL)
        tcb-> ftp.return_code = FTP_RC_SYNTAX_ERROR_PARAM;
    else
    if ((ftpc_permissions (&tcb-> ftp, destname, TRUE)
    &    FTP_AUTH_DELETE) == 0
    ||  (ftpc_permissions (&tcb-> ftp, buffer, FALSE)
    &    FTP_AUTH_PUT) == 0)
        raise_exception (unauthorised_event);
    else
    if (ALLOW_GET)                      /*  Read access is mandatory         */
      {
        if (file_rename (tcb-> ftp.file_name, destname) == 0)
            tcb-> ftp.return_code = FTP_RC_FILE_ACTION_OK;
        else
            tcb-> ftp.return_code = FTP_RC_FILE_ACTION_NOT_TAKEN;
      }
    else
        raise_exception (unauthorised_event);

    mem_strfree (&destname);
}


/****************************   SET STREAM MODE   ****************************/

MODULE set_stream_mode (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.parameters == NULL
    ||  tolower (*tcb-> ftp.parameters) != 's')
        tcb-> ftp.return_code = FTP_RC_BAD_PARAMETER;
}


/**************************   SET RESTART POSITION   *************************/

MODULE set_restart_position (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Parameter is bad unless it is (a) specified, and (b) a positive      */
    /*  number (0 or higher)                                                 */
    if (tcb-> ftp.parameters
    &&  isdigit (*(tcb-> ftp.parameters)))
      {
        tcb-> ftp.file_offset = atol (tcb-> ftp.parameters);
        tcb-> ftp.return_code = FTP_RC_FILE_ACTION_PENDING;
      }
    else
        tcb-> ftp.return_code = FTP_RC_BAD_PARAMETER;
}


/*********************   CHECK READY FOR FILE TRANSFER   *********************/

MODULE check_ready_for_file_transfer (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.passive   == FALSE
    &&  tcb-> ftp.data_host == 0
    &&  tcb-> ftp.data_port == 0)
        raise_exception (unexpected_event);
}


/***********************   SEND PUT DATA FILE REQUEST   **********************/

MODULE send_put_data_file_request (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (ALLOW_GET
    ||  tcb-> ftp.temp_file)
        send_ftpd_put_file (
            &dataq,                     
            thread-> thread_id,         
            tcb-> ftp.passive,  
            tcb-> ftp.file_type,
            tcb-> ftp.file_name,
            tcb-> ftp.file_offset,
            tcb-> ftp.data_host,  
            tcb-> ftp.data_port,
            tcb-> ftp.pipe); 
    else
      {
        raise_exception (unauthorised_event);
        return;
      }
}


/***********************   SEND GET DATA FILE REQUEST   **********************/

MODULE send_get_data_file_request (THREAD *thread)
{
    qbyte
        old_usage,                      /*  Disk usage prior to command      */
        maxsize = 0xFFFFFFFFUL;         /*  Max. permitted upload            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (ALLOW_PUT
    || (ALLOW_UPLOAD && !file_exists (tcb-> ftp.file_name)))
      {
        old_usage = tcb-> ftp.cur_usage;
        if (file_exists (tcb-> ftp.file_name))
            tcb-> ftp.cur_usage 
                -= get_file_size (tcb-> ftp.file_name);

        if (tcb-> ftp.use_quotas)
          {
            if (tcb-> ftp.cur_usage > tcb-> ftp.hard_quota)
              {
                raise_exception (over_quota_event);
                tcb-> ftp.cur_usage = old_usage;
              }
            else        
                maxsize = tcb-> ftp.hard_quota - tcb-> ftp.cur_usage;
          }
        if (!exception_raised)
            send_ftpd_get_file (
                &dataq,                         
                thread-> thread_id,             
                tcb-> ftp.passive,      
                tcb-> ftp.file_type,    
                tcb-> ftp.file_name,    
                tcb-> ftp.file_offset,  
                tcb-> ftp.data_host,    
                tcb-> ftp.data_port,
                maxsize,
                tcb-> ftp.pipe);
      }
    else
      {
        raise_exception (unauthorised_event);
        return;
      }
}


/*********************   SEND APPEND DATA FILE REQUEST   *********************/

MODULE send_append_data_file_request (THREAD *thread)
{
    qbyte
        maxsize = 0xFFFFFFFFUL;         /*  Max. permitted upload            */

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (ALLOW_PUT)
      {
        if (tcb-> ftp.use_quotas)
          {
            if (tcb-> ftp.cur_usage > tcb-> ftp.hard_quota)
                raise_exception (over_quota_event);
            else        
                maxsize = tcb-> ftp.hard_quota - tcb-> ftp.cur_usage;
          }
        if (!exception_raised)
            send_ftpd_append_file (
                &dataq,                       
                thread-> thread_id,           
                tcb-> ftp.passive,    
                tcb-> ftp.file_type,  
                tcb-> ftp.file_name,  
                tcb-> ftp.data_host,  
                tcb-> ftp.data_port,
                maxsize,
                tcb-> ftp.pipe);
      }
    else
      {
        raise_exception (unauthorised_event);
        return;
      }
}


/***************************   SET TRANSFER ENDED   **************************/

MODULE set_transfer_ended (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_DATA_CLOSE;
    tcb-> ftp.passive     = FALSE;
    tcb-> ftp.data_host   = 0;
    tcb-> ftp.data_port   = 0;
    tcb-> ftp.file_offset = 0;
}


/*************************   GET UPLOADED FILE SIZE   ************************/

MODULE get_uploaded_file_size (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */
    
    tcb-> ftp.file_size = get_file_size (tcb-> ftp.file_name);
    tcb-> ftp.cur_usage += tcb-> ftp.file_size;
}


/************************   CHANGE CURRENT DIRECTORY   ***********************/

MODULE change_current_directory (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_chdir (&tcb-> ftp);
}


/***************************   DIRECTORY MOVE UP   ***************************/

MODULE directory_move_up (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_cdup (&tcb-> ftp);
}


/***********************   MAKE OPEN PASSIVE MESSAGE   ***********************/

MODULE make_open_passive_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.passive = TRUE;
    exdr_read (thread-> event-> body, SMT_FTPD_PASS_OK,
                &tcb-> ftp.data_host,
                &tcb-> ftp.data_port);
}


/**********************   OPEN PASSIVE DATA CONNECTION   *********************/

MODULE open_passive_data_connection (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_ftpd_passive (&dataq,
                       thread-> thread_id,
                       tcb-> data_port,
                       tcb-> ftp.ip_address);
}


/*********************   SEND ABORT TO DATA CONNECTION   *********************/

MODULE send_abort_to_data_connection (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    send_ftpd_abort (&dataq, thread-> thread_id);
}


/***************************   CANCEL DATA THREAD   **************************/

MODULE cancel_data_thread (THREAD *thread)
{
    THREAD
        *data_thread;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /* check if a ftp data thread is active for this connection thread
     * if TRUE, send close control message to this thread
     */
    sprintf (buffer, "%ld", thread-> thread_id);
    if ((data_thread = thread_lookup (SMT_FTPD, buffer)) != NULL)
        SEND (&data_thread-> queue-> qid, "FTPD_CLOSECTRL", "");
}


/***************************   MAKE NEW DIRECTORY   **************************/

MODULE make_new_directory (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_mkdir (&tcb-> ftp);
}


/****************************   REMOVE DIRECTORY   ***************************/

MODULE remove_directory (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_rmdir (&tcb-> ftp);
}


/*****************************   FLUSH TIME OUT   ****************************/

MODULE flush_time_out (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.timeout > 0)
        sendfmt (&timeq, "FLUSH", "");
}


/******************************   SET TIME OUT   *****************************/

MODULE set_time_out (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  NOTE: timeout value in ftp.timeout is already in centi-seconds       */
    if (tcb-> ftp.timeout > 0)
        send_alarm (&timeq, 0, tcb-> ftp.timeout, 0, NULL);
}


/**********************   SLEEP AFTER FAILED PASSWORD   **********************/

MODULE sleep_after_failed_password (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Sleep for 2 seconds to frustrate dictionary hacks                    */
    send_alarm (&timeq, 0, 200, 0, NULL);
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    char
        *message = NULL;

    tcb = thread-> tcb;                 /*  Point to thread's context        */

    /*  Pick up message from event body, encoded as SMT_SOCK_ERROR           */
    exdr_read (thread-> event-> body, SMT_SOCK_ERROR, &message, NULL, NULL);

    sendfmt (&operq, "ERROR",
             "smtftpc: error on socket %d: %s", (int) tcb-> handle, message);
    mem_free (message);
}


/**************************   WRITE SERVICE READY   **************************/

MODULE write_service_ready (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_SERVICE_READY;
    write_return_message (thread);
}


/**************************   WRITE USER LOGGED IN   *************************/

MODULE write_user_logged_in (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_USER_LOGGED;
    write_return_message (thread);
}


/*************************   WRITE INVALID PASSWORD   ************************/

MODULE write_invalid_password (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_LOGIN_FAILED;
    write_return_message (thread);
}


/************************   WRITE OPEN PASSIVE OKAY   ************************/

MODULE write_open_passive_okay (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_PASSIVE_MODE;
    write_return_message (thread);
}


/************************   WRITE CLOSING CONNECTION   ***********************/

MODULE write_closing_connection (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_SERVICE_CLOSING;
    write_return_message (thread);
    event_wait ();                      /*  Before closing socket            */
}


/***********************   WRITE USER NOT AUTHORISED   ***********************/

MODULE write_user_not_authorised (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_PERMISSION_DENIED;
    write_return_message (thread);
}


/*************************   WRITE USER OVER QUOTA   *************************/

MODULE write_user_over_quota (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_OVER_QUOTA;
    write_return_message (thread);
}


/**************************   WRITE FILE NOT FOUND   *************************/

MODULE write_file_not_found (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_FILE_NOT_FOUND;
    write_return_message (thread);
}


/*************************   WRITE TIME OUT MESSAGE   ************************/

MODULE write_time_out_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_SERVICE_NOT_AVAILABLE;
    write_return_message (thread);
    event_wait ();                      /*  Before closing socket            */
}


/*************************   WRITE INVALID COMMAND   *************************/

MODULE write_invalid_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_SYNTAX_ERROR;
    write_return_message (thread);
}


/***********************   WRITE UNSUPPORTED COMMAND   ***********************/

MODULE write_unsupported_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_COMMAND_NOT_IMPLEMENTED;
    write_return_message (thread);
}


/************************   WRITE UNEXPECTED COMMAND   ***********************/

MODULE write_unexpected_command (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_BAD_SEQUENCE;
    write_return_message (thread);
}


/**************************   WRITE PENDING ACTION   *************************/

MODULE write_pending_action (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_FILE_ACTION_PENDING;
    write_return_message (thread);
}


/****************************   WRITE FILE SIZE   ****************************/

MODULE write_file_size (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_FILE_STATUS;
    write_return_message (thread);
}


/**************************   WRITE NAME OF SYSTEM   *************************/

MODULE write_name_of_system (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_SYSTEM_NAME;
    write_return_message (thread);
}


/************************   WRITE WORKING DIRECTORY   ************************/

MODULE write_working_directory (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_PATHNAME_CREATED;
    write_return_message (thread);
}


/***************************   WRITE HELP MESSAGE   **************************/

MODULE write_help_message (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_HELP_MESSAGE;
    write_return_message (thread);
}


/*************************   WRITE TRANSFER ABORTED   ************************/

MODULE write_transfer_aborted (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_ACTION_ABORTED;
    write_return_message (thread);
}


/**************************   WRITE DATA CONNECTED   *************************/

MODULE write_data_connected (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_FILE_OK;
    write_return_message (thread);
}


/***********************   WRITE OPEN PASSIVE FAILED   ***********************/

MODULE write_open_passive_failed (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_DATA_OPEN_FAIL;
    write_return_message (thread);
}


/***********************   WRITE SERVICE UNAVAILABLE   ***********************/

MODULE write_service_unavailable (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    tcb-> ftp.return_code = FTP_RC_SERVICE_NOT_AVAILABLE;
    write_return_message (thread);
    event_wait ();                      /*  Before closing socket            */
}


/*************************   WRITE ENTRY TO LOGFILE   ************************/

MODULE write_entry_to_logfile (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    http_count_transfer (tcb-> ftp.file_size);
    if (tcb-> acclog)                   /*  Log access if possible           */
        log_ftp_access (thread);
}


/*  Create entry in log file                                                 */

local
log_ftp_access (THREAD *thread)
{
    char
        *client_ip;
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
    if (!is_local || *TCONFIG ("ftplog:local") == '1')
        log_access (thread, &tcb-> acclog-> queue);

    /*  Anything >= FTP_RC_SERVICE_NOT_AVAILABLE is an error...              */
    if (tcb-> ftp.return_code >= FTP_RC_SERVICE_NOT_AVAILABLE
    && (!is_local || *TCONFIG ("ftperrlog:local") == '1'))
        log_access (thread, &tcb-> errlog-> queue);
}

static void
log_access (THREAD *thread, QID *queue)
{
    char
        *request;
        
    tcb = thread-> tcb;

    /*  Format request as ftp:// URL                                         */
    request = xstrcpy (NULL, "ftp://", socket_peeraddr (tcb-> handle),
                             "/", tcb-> ftp.file_name, NULL);
    send_log (
        queue,
        socket_peeraddr  (tcb-> handle),
        socket_localaddr (tcb-> handle),
        tcb-> ftp.user,
        "FTP",
        request,
        "", "",
        tcb-> request,
        ftp_response [tcb-> ftp.return_code].code,
        tcb-> read_size,
        tcb-> ftp.file_size,
        (time_now () - tcb-> request_time) * 10,
        "-",
        tcb-> ftp.guestname,
        "",
        tcb-> ftp.file_name,
        tcb-> vhost);

    mem_strfree (&request);
}


/***************************   CHECK SOCKET TYPE   ***************************/

MODULE check_socket_type (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    the_next_event = tcb-> thread_type;
}


/**************************   CLOSE MASTER SOCKET   **************************/

MODULE close_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    close_socket (tcb-> handle);
    tcb-> handle = 0;
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
        for (symbol = vhosts-> symbols; symbol; symbol = symbol-> next)
          {
            vhost = symbol-> data;

            /*  Close any log files that we own                              */
            if (vhost-> acclog.owner)
                SEND (&vhost-> acclog.queue, "CLOSE", "");
            if (vhost-> errlog.owner)
                SEND (&vhost-> errlog.queue, "CLOSE", "");

            sym_delete_table (vhost-> config);
            sym_delete_table (vhost-> users);
            sym_delete_table (vhost-> direct);
            mem_free (vhost-> acclog.filename);
            mem_free (vhost-> errlog.filename);
            mem_free (vhost-> rootdir);
            mem_free (vhost-> name);
            mem_free (vhost-> webmask);
            mem_free (vhost);           /*  Free symbol VHOSTS data          */
          }
        sym_delete_table (vhosts);      /*    and finally, entire table      */
      }
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


/*********************   PREPARE TO CLOSE MASTER SOCKET   ********************/

MODULE prepare_to_close_master_socket (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    if (tcb-> ftp.port)
      {
        sendfmt (&operq, "INFO",
            "smtftpc: closing FTP service on port %d", tcb-> ftp.port);
        send_flush (&sockq, tcb-> handle);
      }
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    tcb = thread-> tcb;                 /*  Point to thread's context        */

    ftpc_free_connection (&tcb-> ftp);
    mem_strfree (&tcb-> buffer);
    mem_strfree (&tcb-> rootdir);
    mem_strfree (&tcb-> webmask);
    mem_strfree (&tcb-> vhost);
    mem_strfree (&tcb-> request);

    if (tcb-> handle)
      {
        close_socket (tcb-> handle);
        tcb-> handle = 0;
      }
    if (tcb-> thread_type == client_event)
      {
        cur_connects--;                 /*  One less active connection       */
        ftp_connects--;
      }
    else
    if (tcb-> thread_type == master_event)
      {
        mem_strfree (&rootdir);         /*  For server thread                */
        mem_free (hostaddrs);
      }
    the_next_event = terminate_event;
}


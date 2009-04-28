/*===========================================================================*
 *                                                                           *
 *  xiddns.c -                                                               *
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
    Synopsis:   Handles connection/disconnection to DDNS server

*/
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMTHTTPL prototypes & globals    */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME       "XIDDNS"       /*  Our public name                  */
#define SINGLE_THREADED  TRUE           /*  Single-threaded agent            */
#define DDNS_TIMEOUT     120            /*  DDNS connect timeout, seconds    */
#define BUFFER_MAX       512            /*  For working buffer               */
#define AUTHEN_MAX       100            /*  Size of username + password      */


/*- Function prototypes -----------------------------------------------------*/

static void send_ddns_request     (THREAD *thread, Bool signon);


/*- Global variables used in this source file only --------------------------*/

static QID
    sockq,                              /*  Socket agent event queue         */
    timeq,                              /*  Timer agent event queue          */
    operq;                              /*  Operator console event queue     */
static XML_ITEM
    *services,                          /*  List of DDNS services            */
    *service_item;                      /*  Service item in XML tree         */
static char
    *ddns_service,                      /*  Server name                      */
    *ddns_username,                     /*  User name or e-mail address      */
    *ddns_password,                     /*  Password or key                  */
    *ddns_domain,                       /*  Requested domain name            */
    *ddns_host,                         /*  DDNS host to contact             */
    *ddns_port,                         /*  Port to connect to               */
    *ddns_req,                          /*  Request string to server         */
    *ddns_ack;                          /*  Acknowledgment string            */
static Bool
    ddns_verbose = FALSE,               /*  Show conversation?               */
    ddns_trace = FALSE;                 /*  Trace conversation?              */
    
static struct_smt_sock_ok
    *connection;                        /*  Connection data                  */
static int
    ddns_index;                         /*  "ddns..." index number           */
static char
    buffer [BUFFER_MAX + 1];            /*  For queries and responses        */

    
#include "xiddns.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT    ********************/

/*  ---------------------------------------------------------------------[<]-
    Function: xiddns_init

    Synopsis: Initialises the Xitami DDNS agent.  Returns 0 if initialised
    okay, -1 if there was an error.  Supports these public methods:
    <Table>
    SIGNON      Sign-on to all DDNS hosts (done when agent starts-up)
    SIGNOFF     Sign-off from all DDNS hosts
    </Table>
    Does not send reply events.
    ---------------------------------------------------------------------[>]-*/

int
xiddns_init (void)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "xiddns.i"                  /*  Include dialog interpreter       */

    /*                      Method name    Event value    Priority           */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",     shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "SIGNON",           signon_event,       0);
    method_declare (agent, "SIGNOFF",          signoff_event,      0);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",    ok_event,           0);
    method_declare (agent, "SOCK_OUTPUT_OK",   ok_event,           0);
    method_declare (agent, "SOCK_READ_OK",     ok_event,           0);
    method_declare (agent, "SOCK_WRITE_OK",    ok_event,           0);
    method_declare (agent, "SOCK_CLOSED",      ok_event,           0);
    method_declare (agent, "SOCK_ERROR",       sock_error_event,   0);
    method_declare (agent, "SOCK_TIMEOUT",     sock_timeout_event, 0);

    /*  Reply events from timer agent                                        */
    method_declare (agent, "TIME_ALARM",       signon_event,       0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer agent is running, else start it up                 */
    smttime_init ();
    if ((thread = thread_lookup (SMT_TIMER, "")) != NULL)
        timeq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket i/o agent is running, else start it up            */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Create single master thread                                          */
    thread_create (AGENT_NAME, "main");

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    the_next_event = ok_event;
}



/************************   INITIALISE SIGNON TIMER   ************************/

MODULE initialise_signon_timer (THREAD *thread)
{
    qbyte
        refresh;                        /*  Server refresh rate              */

    refresh = atol (CONFIG ("ddns:refresh")) * 100;
    if (refresh == 0)
        return;                         /*  Then do nothing                  */

    if (refresh < 6000)
        refresh = 6000;                 /*  1 minute minimum rate            */

    send_clock (&timeq, 0, refresh, 0, 0, NULL);
}


/***********************   CHECK IF AUTOMATIC SIGNON   ***********************/

MODULE check_if_automatic_signon (THREAD *thread)
{
    if (*CONFIG ("ddns:enabled") == '1')
        the_next_event = ok_event;
    else
        the_next_event = ignore_event;
}


/************************   LOAD DDNS SERVICES LIST   ************************/

MODULE load_ddns_services_list (THREAD *thread)
{
    char
        *filename;

    filename = CONFIG ("ddns:filename");
    services = NULL;

    switch (xml_load_file (&services, "PATH", filename, FALSE))
      {
        case XML_FILEERROR:
            sendfmt (&operq, "ERROR",
                "xiddns: cannot read '%s': %s", filename, xml_error ());
            raise_exception (exception_event);
            break;
        case XML_LOADERROR:
            sendfmt (&operq, "ERROR",
                "xiddns: error in '%s': %s", filename, xml_error ());
            raise_exception (exception_event);
            break;
      }
}


/************************   DROP DDNS SERVICES LIST   ************************/

MODULE drop_ddns_services_list (THREAD *thread)
{
    xml_free (services);
}


/*************************   GET FIRST DDNS PROFILE   ************************/

MODULE get_first_ddns_profile (THREAD *thread)
{
    ddns_index = 0;
    get_next_ddns_profile (thread);
}


/*************************   GET NEXT DDNS PROFILE   *************************/

MODULE get_next_ddns_profile (THREAD *thread)
{
    char
        ddns_prefix [10];               /*  "ddns.." config table prefix     */
    XML_ATTR
        *attr;                          /*  XML attribute                    */

    /*  If we have a symbol with the name ddns... then we can assume that
     *  this is the start of a DDNS entry.
     */
    sprintf (ddns_prefix, "ddns%.0d", ddns_index++);
    ddns_service = ini_dyn_value (config, ddns_prefix, "service", NULL);

    if (ddns_service)
      {
        the_next_event = ok_event;
        ddns_username = ini_dyn_value (config, ddns_prefix, "username", "");
        ddns_password = ini_dyn_value (config, ddns_prefix, "password", "");
        ddns_domain   = ini_dyn_value (config, ddns_prefix, "domain",   "");

        /*  Now find service properties                                      */
        FORCHILDREN (service_item, xml_first_child (services))
          {
            attr = xml_attr (service_item, "NAME");
            if (attr == NULL)
                sendfmt (&operq, "ERROR",
                         "xiddns: syntax error in definition file - no NAME");
            else
            if (streq (ddns_service, xml_attr_value (attr)))
                break;
           }
        if (service_item == NULL)
          {
            sendfmt (&operq, "ERROR",
                     "xiddns: service '%s' not defined", ddns_service);
            the_next_event = error_event;
          }
      }
    else
        the_next_event = no_more_event;
}


/*************************   CONNECT TO DDNS SERVER   ************************/

MODULE connect_to_ddns_server (THREAD *thread)
{
    ddns_host    =  xml_get_attr (service_item, "HOST",    "localhost");
    ddns_port    =  xml_get_attr (service_item, "PORT",    "80");
    ddns_verbose = *xml_get_attr (service_item, "VERBOSE", "1") == '1';
    ddns_trace   = *xml_get_attr (service_item, "TRACE",   "0") == '1';

    if (ddns_verbose)
        sendfmt (&operq, "INFO", 
                 "xiddns: connecting to %s...", ddns_host);

    send_connect (&sockq, 0, "TCP", ddns_host, ddns_port, 0, 0, 0);
}


/**************************   GET CONNECTED SOCKET   *************************/

MODULE get_connected_socket (THREAD *thread)
{
    get_smt_sock_ok (thread-> event-> body, &connection);
    if (ddns_trace)
        coprintf ("xiddns: connected on socket %d", connection-> socket);
}


/************************   SEND DDNS SIGNON REQUEST   ***********************/

MODULE send_ddns_signon_request (THREAD *thread)
{
    if (ddns_verbose && !ddns_trace)
        sendfmt (&operq, "INFO", "xiddns: sending DDNS sign-on");
        
    send_ddns_request (thread, TRUE);
}

static void
send_ddns_request (THREAD *thread, Bool signon)
{
    SYMTAB
        *symtab;                        /*  Token insertion table            */
    XML_ITEM
        *xml_item;                      /*  SIGNON or SIGNOFF item           */
    XML_ATTR
        *xml_attr;                      /*  Attributes for item              */
    int
        auth_length;                    /*  Length of authorisation string   */
    char
        authorisation [AUTHEN_MAX * 2], /*  HTTP authorisation, base 64      */
        *attr_name,                     /*  XML attribute name               */
        *attr_value,                    /*  XML attribute value              */
        *expanded;                      /*  String after token expansion     */

    /*  Create symbol table for insertion symbols                            */
    symtab = sym_create_table ();
    
    /*  Set insertion symbols                                                */
    sym_assume_symbol (symtab, "username", ddns_username);
    sym_assume_symbol (symtab, "password", ddns_password);
    sym_assume_symbol (symtab, "domain",   ddns_domain);
    sym_assume_symbol (symtab, "ipaddr",   socket_localaddr (connection-> socket));

    /*  Format HTTP authentication string                                    */
    sprintf (buffer, "%s:%s", ddns_username, ddns_password);
    buffer [AUTHEN_MAX] = '\0';     /*  Truncate brutally                    */
    auth_length = encode_base64 ((byte *) buffer, (byte *) authorisation,
                                  strlen (buffer));
    authorisation [auth_length] = '\0';
    sprintf (buffer, "Authorization: Basic %s\r\n", authorisation);
    sym_assume_symbol (symtab, "httpauth", buffer);

    /*  Format other HTTP headers                                            */
    sprintf (buffer, "User-Agent: Xitami DDNS Agent\r\nHost: %s\r\n\r\n",
                      ddns_host);
    sym_assume_symbol (symtab, "httpheaders", buffer);

    /*  Get signon / signoff item as required                                */
    FORCHILDREN (xml_item, service_item)
      {
        if (lexcmp (xml_item_name (xml_item), signon? "SIGNON": "SIGNOFF") == 0)
            break;
      }
    /*  If none is defined, we ignore this service                           */
    if (xml_item == NULL)
      {
        raise_exception (ignore_event);
        return;
      }

    /*  Format symbols from attributes in signon item                        */
    ddns_req = NULL;                    /*  Required attribute               */
    ddns_ack = "HTTP/1.? 200*";         /*  Optional attribute               */
    FORATTRIBUTES (xml_attr, xml_item)
      {
        attr_name  = xml_attr_name  (xml_attr);
        attr_value = xml_attr_value (xml_attr);
        if (lexcmp (attr_name, "SEND") == 0)
            ddns_req = attr_value;
        else
        if (lexcmp (attr_name, "EXPECT") == 0)
            ddns_ack = attr_value;
        else
          {
            expanded = tok_subst (attr_value, symtab);
            sym_assume_symbol (symtab, attr_name, expanded);
            mem_free (expanded);
          }
      }
    /*  The SEND attribute is required                                       */
    if (ddns_req == NULL)
      {
        sendfmt (&operq, "ERROR", "xiddns: SEND missing for '%s'", ddns_host);
        raise_exception (ignore_event);
        return;
      }

    /*  Now format request string and send it off                            */
    expanded = tok_subst (ddns_req, symtab);
    searchreplace (expanded, "\\r", "\r");
    searchreplace (expanded, "\\n", "\n");
    if (ddns_trace)
      {
        coprintf ("xiddns: sending sign-%s request", signon? "on": "off");
        coprintf (expanded);
      }
    send_write (&sockq, 0, connection-> socket,
                (word) strlen (expanded), (byte *) expanded, 0);
    mem_free (expanded);
    sym_delete_table (symtab);
}


/***********************   SEND DDNS SIGNOFF REQUEST   ***********************/

MODULE send_ddns_signoff_request (THREAD *thread)
{
    if (ddns_verbose && !ddns_trace)
        sendfmt (&operq, "INFO", "xiddns: sending DDNS sign-off");

    send_ddns_request (thread, FALSE);
}


/************************   GET DDNS SERVER RESPONSE   ***********************/

MODULE get_ddns_server_response (THREAD *thread)
{
    if (ddns_trace)
        coprintf ("xiddns: waiting for response from %s...", ddns_host);

    send_read (&sockq, 0, connection-> socket, BUFFER_MAX, 0, 0);
}


/************************   CHECK DDNS CONFIRMATION   ************************/

MODULE check_ddns_confirmation (THREAD *thread)
{
    word
        read_size;                      /*  Amount of data read from socket  */
    char
        *read_data = buffer;            /*  Data read from socket            */

    /*  Get reply from server into buffer                                    */
    exdr_read (thread-> event-> body, SMT_SOCK_READ_OK,
               NULL, NULL, &read_size, &read_data, NULL);
    ASSERT (read_size <= BUFFER_MAX);
    buffer [read_size] = '\0';
    if (ddns_trace)
      {
        coprintf ("xiddns: have response from DDNS server");
        coprintf (buffer);
      }

    /*  Check return code                                                    */
    searchreplace (ddns_ack, "\\r", "\r");
    searchreplace (ddns_ack, "\\n", "\n");
    if (lexwcmp (buffer, ddns_ack) == 0)
      {
        if (ddns_verbose)
            sendfmt (&operq, "INFO",
                     "xiddns: domain '%s' registered", ddns_domain);
      }
    else        
      {
        /*  Error - show first line of response                              */
        strconvch (buffer, '\r', '\0');
        strconvch (buffer, '\n', '\0');
        sendfmt (&operq, "Error", "xiddns: '%s': %s", ddns_host, buffer);
      }
}


/***************************   CLOSE DDNS SOCKET   ***************************/

MODULE close_ddns_socket (THREAD *thread)
{
    close_socket (connection-> socket);
    send_flush   (&sockq, connection-> socket);
    free_smt_sock_ok (&connection);
}


/************************   SIGNAL CONNECTION FAILED   ***********************/

MODULE signal_connection_failed (THREAD *thread)
{
    sendfmt (&operq, "ERROR", "xiddns: connection to %s failed", ddns_host);
}


/************************   SIGNAL DDNS SOCK TIMEOUT   ***********************/

MODULE signal_ddns_sock_timeout (THREAD *thread)
{
    sendfmt (&operq, "ERROR", "xiddns: no response from %s", ddns_host);
}


/*************************   SIGNAL DDNS SOCK ERROR   ************************/

MODULE signal_ddns_sock_error (THREAD *thread)
{
    char
        *message = NULL;

    /*  Pick up message from event body, encoded as SMT_SOCK_ERROR           */
    exdr_read (thread-> event-> body, SMT_SOCK_ERROR, &message, NULL, NULL);
    sendfmt (&operq, "ERROR", "xiddns: TCP/IP error: %s", message);

    mem_free (message);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    the_next_event = terminate_event;
}


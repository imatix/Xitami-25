/*===========================================================================*
 *                                                                           *
 *  smtupmc.c -                                                              *
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
    Synopsis:   Connects to the UPM daemon and lets you issue UPM commands.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smtupm.h"                     /*  SMT UPM definitions              */


/*- Definitions -------------------------------------------------------------*/

#define AGENT_NAME       "smtupmc"      /*  Name of our agent                */
#define SINGLE_THREADED  TRUE
#define UPMC_VERSION     "1.0"


/*- Function prototypes -----------------------------------------------------*/

static void   put_upm_message  (THREAD *thread, dbyte ident, char *body);
static dbyte  get_upm_message  (THREAD *thread, char *body);


/*- Global variables used in this source file only --------------------------*/

static char
    *portname,                          /*  Connection port                  */
    *args;                              /*  Command-line arguments           */

static sock_t
    upm_socket = 0;                     /*  Socket to UPM daemon             */
static QID
    sockq,                              /*  Socket agent event queue         */
    tranq;                              /*  Transfer agent event queue       */
static char
    **token_list = NULL,                /*  Parsed command line              */
    upm_body [LINE_MAX];                /*  Message from UPM daemon          */

static dbyte
    upm_id;                             /*  UPM message id                   */
static byte
    msg_body [LINE_MAX];                /*  Message sent to socket agent     */
static int
    msg_size;                           /*  Size of formatted msg_body       */
static DESCR                            /*  Descriptor for exdr_writed       */
    msg = { LINE_MAX, msg_body };


#include "smtupmc.d"                    /*  Include dialog data              */

/********************   INITIALISE AGENT - ENTRY POINT   *********************/

/*  ---------------------------------------------------------------------[<]-
    Function: smtupmc_init

    Synopsis: Initialises the SMT UPM client agent.  Returns 0 if okay,
    -1 if there was an error.  The UPM client agent allows you to pass
    commands to the UPM daemon.  See the SMT documentation for details.
    ---------------------------------------------------------------------[>]-*/

int
smtupmc_init (char *p_args, char *p_portname)
{
    AGENT   *agent;                     /*  Handle for our agent             */
    THREAD  *thread;                    /*  Handle to console thread         */
#   include "smtupmc.i"                 /*  Include dialog interpreter       */

    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN", shutdown_event, SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    method_declare (agent, "SOCK_INPUT_OK",  ok_event,          0);
    method_declare (agent, "SOCK_OUTPUT_OK", ok_event,          0);
    method_declare (agent, "SOCK_READ_OK",   ok_event,          0);
    method_declare (agent, "SOCK_WRITE_OK",  ok_event,          0);
    method_declare (agent, "SOCK_CLOSED",    sock_closed_event, 0);
    method_declare (agent, "SOCK_ERROR",     sock_error_event,  0);
    method_declare (agent, "SOCK_TIMEOUT",   sock_error_event,  0);

    /*  Reply events from transfer agent                                     */
    method_declare (agent, "TRAN_GETF_OK",   ok_event,          0);
    method_declare (agent, "TRAN_PUTF_OK",   SMT_NULL_EVENT,    0);
    method_declare (agent, "TRAN_CLOSED",    sock_closed_event, 0);
    method_declare (agent, "TRAN_ERROR",     sock_error_event,  0);

    /*  Create initial, unnamed thread                                       */
    thread_create (AGENT_NAME, "");

    /*  Ensure that socket agent is running, else start it up                */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that transfer agent is running, else start it up              */
    smttran_init ();
    if ((thread = thread_lookup (SMT_TRANSFER, "")) != NULL)
        tranq = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    args     = p_args;                  /*  Get command-line arguments       */
    portname = p_portname;
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    the_next_event = ok_event;
}


/*************************   CONNECT TO UPM DAEMON   *************************/

MODULE connect_to_upm_daemon (THREAD *thread)
{
    printf ("upmc> 100- Connecting to UPM daemon...\n");
    msg_size = exdr_writed (&msg, SMT_SOCK_CONNECT, 0,
                            "TCP", "", portname, 0, (qbyte) 0, (qbyte) 0);
    event_send (
        &sockq,                         /*  Send to socket agent             */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "CONNECT",                      /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/*************************   STORE CONNECTION DATA   *************************/

MODULE store_connection_data (THREAD *thread)
{
    /*  Reply message contains connected socket number plus tag (unused)     */
    exdr_read (thread-> event-> body, SMT_SOCK_OK, &upm_socket, NULL);
}


/***************************   GET DAEMON MESSAGE   **************************/

MODULE get_daemon_message (THREAD *thread)
{
    /*  Ask the transfer agent to read a block from the socket               */
    msg_size = exdr_writed (&msg, SMT_TRAN_GETB, upm_socket, NULL);
    event_send (
        &tranq,                         /*  Send to transfer agent           */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "GET_BLOCK",                    /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */

    event_wait ();                      /*  Wait for reply event             */
}


/**************************   CHECK DAEMON MESSAGE   *************************/

MODULE check_daemon_message (THREAD *thread)
{
    /*  This table converts a UPM message id into an event for the dialog    */
    static struct {
        dbyte   id;
        event_t event;
    } idents [] = {
        { UPM_READY,        upm_ready_event         },
        { UPM_ERROR,        upm_error_event         },
        { UPM_HALTING,      upm_halting_event       },
        { UPM_TASK_ID,      upm_task_id_event       },
        { UPM_TASK_OK,      upm_task_ok_event       },
        { UPM_TASK_NF,      upm_task_nf_event       },
        { UPM_TASK_RUNNING, upm_task_running_event  },
        { UPM_TASK_STOPPED, upm_task_stopped_event  },
        { UPM_START_OK,     upm_start_ok_event      },
        { UPM_START_ERROR,  upm_start_error_event   },
        { UPM_STOP_OK,      upm_stop_ok_event       },
        { UPM_STOP_ERROR,   upm_stop_error_event    },
        { 0,                0                       }
    };
    int
        ident_nbr;

    if (the_external_event == ok_event)
      {
        /*  Get arguments from message                                       */
        upm_id = get_upm_message (thread, upm_body);
        for (ident_nbr = 0; idents [ident_nbr].id; ident_nbr++)
            if (idents [ident_nbr].id == upm_id)
              {
                the_next_event = idents [ident_nbr].event;
                break;
              }
        if (idents [ident_nbr].id == 0)
          {
            signal_unexpected_message (thread);
            raise_exception (exception_event);
          }
      }
    else
        raise_exception (the_external_event);
}


/*  -------------------------------------------------------------------------
 *  get_upm_message -- local
 *
 *  Decodes the thread body to give a message id and a message body.  Puts
 *  the message body in the specified string and returns the message id.
 */

static dbyte
get_upm_message (THREAD *thread, char *body)
{
    byte
       *msg_body_addr = msg_body;
    dbyte
        upm_ident;

    /*  Get buffer from transfer agent                                       */
    exdr_read (thread-> event-> body, SMT_TRAN_GETB_OK,
               NULL, &msg_body_addr);

    /*  Decode UPM message                                                   */
    exdr_read (msg_body, SMT_UPM_MESSAGE, &upm_ident, &body);
    return (upm_ident);
}


/*************************   GET USER COMMAND INPUT   ************************/

MODULE get_user_command_input (THREAD *thread)
{
    static char
        input_line [LINE_MAX + 1];
    static struct {
        char   *name;
        event_t event;
    } keywords [] = {
        { "LIST",    list_event     },
        { "START",   start_event    },
        { "STOP",    stop_event     },
        { "STATUS",  status_event   },
        { "HALT",    halt_event     },
        { "EXIT",    exit_event     },
        { "QUIT",    exit_event     },
        { "HELP",    help_event     },
        { "VERSION", version_event  },
        {  NULL,     0              }
    };
    int
        keyword_nbr;

    /*  If we got function arguments, use those, else prompt the user        */
    if (args && strused (args))
      {
        strncpy (input_line, args, LINE_MAX);
        input_line [LINE_MAX] = '\0';   /*  Ensure delimited, if looong      */
        args = "exit";                  /*  Next time treat as Exit          */
      }
    else
      {
        /*  Show upmc prompt and wait for user command                       */
        printf ("upmc> ");
        fflush (stdout);
        if (fgets (input_line, LINE_MAX, stdin) == NULL)
            strclr (input_line);        /*  Treat EOF as empty               */
      }
    if (token_list)
        tok_free (token_list);
    token_list = tok_split (input_line);

    /*  Get event corresponding to user command                              */
    if (token_list [0] && *token_list [0])
      {
        the_next_event = error_event;
        strupc (token_list [0]);
        for (keyword_nbr = 0; keywords [keyword_nbr].name; keyword_nbr++)
            if (streq (token_list [0], keywords [keyword_nbr].name))
              {
                the_next_event = keywords [keyword_nbr].event;
                break;
              }
      }
    else
        the_next_event = empty_event;
}


/************************   SEND DAEMON LIST COMMAND   ***********************/

MODULE send_daemon_list_command (THREAD *thread)
{
    put_upm_message (thread, UPM_LIST, "");
}


static void
put_upm_message (THREAD *thread, dbyte ident, char *body)
{
    static byte
        upm_body [LINE_MAX];            /*  Message to UPM client agent      */
    static DESCR                        /*  Descriptor for exdr_writed       */
        upm = { LINE_MAX, upm_body };
    int
        upm_size;                       /*  Size of formatted upm_body       */

    upm_size = exdr_writed (&upm, SMT_UPM_MESSAGE, ident, body);
    msg_size = exdr_writed (&msg, SMT_TRAN_PUTB,
                            upm_socket, upm_size, upm_body, NULL);
    event_send (
        &tranq,                         /*  Send to transfer agent           */
        &thread-> queue-> qid,          /*  Queue for reply                  */
        "PUT_BLOCK",                    /*  Name of event to send            */
        msg_body, msg_size,             /*  Event body and size              */
        NULL, NULL, NULL,               /*  No response events               */
        0);                             /*  No timeout                       */
}


/***********************   SEND DAEMON START COMMAND   ***********************/

MODULE send_daemon_start_command (THREAD *thread)
{
    put_upm_message (thread, UPM_START, token_list [1]);
}


/************************   SEND DAEMON STOP COMMAND   ***********************/

MODULE send_daemon_stop_command (THREAD *thread)
{
    put_upm_message (thread, UPM_STOP, token_list [1]);
}


/***********************   SEND DAEMON STATUS COMMAND   **********************/

MODULE send_daemon_status_command (THREAD *thread)
{
    put_upm_message (thread, UPM_STATUS, token_list [1]);
}


/************************   SEND DAEMON HALT COMMAND   ***********************/

MODULE send_daemon_halt_command (THREAD *thread)
{
    put_upm_message (thread, UPM_HALT, "");
}


/************************   SHOW VERSION INFORMATION   ***********************/

MODULE show_version_information (THREAD *thread)
{
    printf ("upmc> 101- UPM client version %s\n", UPMC_VERSION);
}


/*************************   SHOW HELP INFORMATION   *************************/

MODULE show_help_information (THREAD *thread)
{
#   define HELP_TEXT                                                         \
    "Commands and arguments can be in any case.  Commands are:\n"            \
    "LIST                 - list all known tasks\n"                          \
    "START [task | ALL]   - start specified task (default all)\n"            \
    "STOP [task | ALL]    - stop specified task (default all)\n"             \
    "STATUS [task | ALL]  - show status for specified task (default all)\n"  \
    "HALT                 - halt UPM daemon\n"                               \
    "EXIT                 - end this UPM client session\n"                   \
    "QUIT                 - end this UPM client session\n"                   \
    "HELP                 - show this information\n"                         \
    "VERSION              - show UPM client version\n"

    puts (HELP_TEXT);
}


/*************************   SIGNAL CONNECTED OKAY   *************************/

MODULE signal_connected_okay (THREAD *thread)
{
    printf ("upmc> 102- Connected to UPM daemon version %s\n", upm_body);
}


/*****************************   SHOW TASK NAME   ****************************/

MODULE show_task_name (THREAD *thread)
{
    printf ("upmc> 200- %s\n", upm_body);
}


/*************************   SIGNAL TASK STARTED OK   ************************/

MODULE signal_task_started_ok (THREAD *thread)
{
    printf ("upmc> 201- task started successfully: %s\n", upm_body);
}


/************************   SIGNAL TASK NOT STARTED   ************************/

MODULE signal_task_not_started (THREAD *thread)
{
    printf ("upmc> 202- task not started: %s\n", upm_body);
}


/*************************   SIGNAL TASK STOPPED OK   ************************/

MODULE signal_task_stopped_ok (THREAD *thread)
{
    printf ("upmc> 203- task stopped successfully: %s\n", upm_body);
}


/************************   SIGNAL TASK NOT STOPPED   ************************/

MODULE signal_task_not_stopped (THREAD *thread)
{
    printf ("upmc> 204- task not stopped: %s\n", upm_body);
}


/*************************   SIGNAL TASK NOT KNOWN   *************************/

MODULE signal_task_not_known (THREAD *thread)
{
    printf ("upmc> 205- task not defined: %s\n", upm_body);
}


/**************************   SIGNAL TASK RUNNING   **************************/

MODULE signal_task_running (THREAD *thread)
{
    printf ("upmc> 206- %s running\n", upm_body);
}


/**************************   SIGNAL TASK STOPPED   **************************/

MODULE signal_task_stopped (THREAD *thread)
{
    printf ("upmc> 207- %s stopped\n", upm_body);
}


/**************************   SIGNAL SOCKET CLOSED   *************************/

MODULE signal_socket_closed (THREAD *thread)
{
    printf ("upmc> 300- UPM daemon closed connection\n");
}


/**************************   SIGNAL SOCKET ERROR   **************************/

MODULE signal_socket_error (THREAD *thread)
{
    printf ("upmc> 301- UPD daemon connection failed: %s\n",
             thread-> event-> body);
}


/*************************   SIGNAL INVALID COMMAND   ************************/

MODULE signal_invalid_command (THREAD *thread)
{
    printf ("upmc> 302- Invalid command - 'help' shows possible commands\n");
}


/***********************   SIGNAL UNEXPECTED MESSAGE   ***********************/

MODULE signal_unexpected_message (THREAD *thread)
{
    printf ("upmc> 303- Unexpected message from UPM daemon: %d\n", upm_id);
}


/*************************   SIGNAL UPM FATAL ERROR   ************************/

MODULE signal_upm_fatal_error (THREAD *thread)
{
    printf ("upmc> 304- Fatal error from UPM daemon: %s\n", upm_body);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    if (upm_socket)
        close_socket (upm_socket);
    if (token_list)
        tok_free (token_list);          /*  Free-up allocated memory         */

    smt_shutdown ();                    /*  End the entire application       */
    the_next_event = terminate_event;
}

/*===========================================================================*
 *                                                                           *
 *  xixxml.c -                                                               *
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
    Synopsis:   Installs itself as a WSX agent to handle all files with the
                extension 'xml' and 'gsl'.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP definitions             */
#include "ggcode.h"                     /*  GSLgen functions                 */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME        "xixxml"      /*  Our public name                  */
#define SINGLE_THREADED   TRUE          /*  Single-threaded agent            */
#define BUFFER_MAX        64000         /*  Output buffer size               */

static void  gslgen_stdout  (const char *line);

/*- Global variables used in this source file only --------------------------*/

static QID
    operq;                              /*  Operator console event queue     */

static XML_ITEM
    *xml_root,                          /*  XML root item                    */
    *xml_main,                          /*  XML error item                   */
    *xml_switches;

static char
    *buffer = NULL;
static Bool
    resolve_script;                     /*  Do we need to resolve script?    */
    
static struct_smt_wsx_request
    *request = NULL;                    /*  Incoming smt_wsx request         */

#include "xixxml.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int xixxml_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread; 
#   include "xixxml.i"                  /*  Include dialog interpreter       */

    /*                      Method name   Event value     Priority           */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",    shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "WSX_REQUEST", request_event,  0);

    /*  Create master thread to manage WSX requests                          */
    thread_create (AGENT_NAME, "main");

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    buffer = mem_alloc (BUFFER_MAX + 1);
    the_next_event = ok_event;
}


/***************************   DECODE WSX REQUEST   **************************/

MODULE decode_wsx_request (THREAD *thread)
{
    FILE
        *resource;
    char
        *extension;
        
    /*  Decode the WSX request using this standard function call             */
    if (request)
        free_smt_wsx_request (&request);

    get_smt_wsx_request (thread-> event-> body, &request);

    if (request)
      {
        the_next_event = other_event;
        extension = strrchr (request-> filename, '.');
        if (extension)
          {
            if (streq (extension, ".gsl"))
              {
                if (file_exists (request-> filename))
                    the_next_event = gsl_file_event;
                else
                    the_next_event = not_found_event;
              }
            else
              {
                /*  Check whether the requested file looks like a valid
                 *  XML file, starting with '<'
                 */
                resource = file_open (request-> filename, 'r');
                if (resource == NULL)
                    the_next_event = not_found_event;
                else
                  {
                    if (fgetc (resource) == '<')
                        the_next_event = xml_file_event;
                    file_close (resource);
                  }
              }
          }
      }
    else
      {
        /*  The request can only be null if there is no memory left          */
        send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_OVERLOADED);
        the_next_event = exception_event;
      }
}


/*****************************   LOAD XML FILE   *****************************/

MODULE load_xml_file (THREAD *thread)
{
    xml_root = NULL;
    switch (xml_load_file (&xml_root, NULL, request-> filename, FALSE))
      {
        case XML_NOERROR:
            xml_main = xml_first_child (xml_root);
            resolve_script = TRUE;
            break;
        case XML_FILEERROR:
            sendfmt (&operq, "ERROR",
                "xixxml: cannot read '%s': %s", request-> filename, xml_error ());
            raise_exception (not_found_event);
            break;
        case XML_LOADERROR:
            sendfmt (&operq, "ERROR",
                "xixxml: error in '%s': %s", request-> filename, xml_error ());
            raise_exception (not_found_event);
            break;
      }
}


/*************************   CREATE EMPTY XML FILE   *************************/

MODULE create_empty_xml_file (THREAD *thread)
{
    xml_main = xml_root = xml_new (NULL, "root", "");
    xml_put_attr (xml_main, "script", request-> filename);
    resolve_script = FALSE;
}


/************************   SET STANDARD ATTRIBUTES   ************************/

MODULE set_standard_attributes (THREAD *thread)
{
    DESCR
        symbols;                        /*  Symbol descriptor                */
    SYMTAB
        *envtab,                        /*  Environment symbols              */
        *config;                        /*  Configuration symbols            */
    SYMBOL
        *symbol;                        /*  Entry in symbol table            */
    XML_ITEM
        *env_item;                      /*  Environment item in XML tree     */
    XML_ATTR
        *script;                        /*  script attribute in XML file     */
    static char
        script_name [FILE_NAME_MAX];    /*  Actual script filename           */
    char
        *query_string,                  /*  Query string, if any             */
        *full_name,                     /*  Full script filename             */
        *cgi_url,                       /*  CGI url                          */ 
        *cgi_root,                      /*  CGI root directory               */
        *webpages;                      /*  Webpages directory               */

    xml_switches = xml_new (NULL, "switches", NULL);

    symbols.size = request-> symbols_size;
    symbols.data = request-> symbols_data;
    envtab = descr2symb (&symbols);

    symbols.size = request-> config_size;
    symbols.data = request-> config_data;
    config = descr2symb (&symbols);

    /*  Store query string if specified                                      */
    query_string = sym_get_value (envtab, "QUERY_STRING", "");
    cgi_parse_query_vars (envtab, query_string, "");

    /*  Add all environment symbols usually passed to CGI programs           */
    for (symbol = envtab-> symbols; symbol; symbol = symbol-> next)
      {
        xml_put_attr (xml_main, symbol-> name, symbol-> value);
        env_item = xml_new (xml_main, "argument", "");
        xml_put_attr (env_item, "name",  symbol-> name);
        xml_put_attr (env_item, "value", symbol-> value);
      }

    /*  Get and prepare full filename for script to use                      */
    if (resolve_script)
      {
        script = xml_attr (xml_main, "script");
        if (!script)
            script = xml_attr (xml_main, "script");

        if (script)
          {
            strcpy (script_name, xml_attr_value (script));
            xml_free_attr (script);
            webpages  = sym_get_value (envtab, "DOCUMENT_ROOT", "./");
            cgi_root  = sym_get_value (envtab, "CGI_ROOT",       NULL);
            cgi_url   = sym_get_value (config, "server:cgi-url", NULL);
            full_name = http_map_uri  (config, webpages, cgi_root, 
                                               script_name, cgi_url, 0);
          }
        else                            /*  Default is filename + .gsl       */
          {
            fixed_extension (script_name, request-> filename, "gsl");
            full_name = mem_strdup (script_name);
          }
        if (file_exists (full_name))
            xml_put_attr (xml_main, "script", full_name);
        else
          {
            sendfmt (&operq, "ERROR",
                "xixxml: script '%s' not found for '%s'", 
                full_name, request-> filename);
            raise_exception (not_found_event);
          }
        mem_free (full_name);
      }

    /*  These attributes are defined last and cannot be overwritten          */
    xml_put_attr (xml_switches, "shuffle",    "1");
    xml_put_attr (xml_switches, "ignorecase", "1");
    xml_put_attr (xml_switches, "template",   "1");
    xml_put_attr (xml_switches, "me",         "xixxml");
    xml_put_attr (xml_switches, "date", conv_date_pict (date_now (), "yyyy/mm/dd"));
    xml_put_attr (xml_switches, "time", conv_time_pict (time_now (), "hh:mm:ss"));
    xml_put_attr (xml_switches, "filename", request-> filename);
    
    sym_delete_table (envtab);
    sym_delete_table (config);
}


/****************************   PROCESS XML FILE   ***************************/

MODULE process_xml_file (THREAD *thread)
{
    /*  Send gslgen output to our own handler                                */
    gg_send_stdout (gslgen_stdout, FALSE);
    gslgen_stdout (NULL);               /*  Initialise output buffer         */
    
    /*  Now generate code                                                    */
    gg_code (xml_main, xml_switches);

    /*  And stop capturing output                                            */
    gg_send_stdout (NULL, FALSE);
}


/*  Append GSLgen output to our buffer                                       */

static void
gslgen_stdout (const char *line)
{
    static int
        buffer_size;                    /*  Total size of message text       */

    if (line)
      {
        if (buffer_size + strlen (line) < BUFFER_MAX)
          {
            strcat (buffer, line);
            buffer_size += strlen (line);
          }
      }
    else
      {
        strclr (buffer);
        buffer_size = 0;
      }
}


/*****************************   FREE XML FILE   *****************************/

MODULE free_xml_file (THREAD *thread)
{
    xml_free (xml_switches);
    xml_free (xml_root);
}


/*************************   REPLY WSX WITH OUTPUT   *************************/

MODULE reply_wsx_with_output (THREAD *thread)
{
    send_wsx_ok (&thread-> event-> sender, buffer);
}


/**************************   REPLY ILLEGAL ACCESS   *************************/

MODULE reply_illegal_access (THREAD *thread)
{
    send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_FORBIDDEN);
}


/****************************   REPLY NOT FOUND   ****************************/

MODULE reply_not_found (THREAD *thread)
{
    send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_NOTFOUND);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    if (request)
        free_smt_wsx_request (&request);

    mem_free (buffer);
    the_next_event = terminate_event;
}


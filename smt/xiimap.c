/*===========================================================================*
 *                                                                           *
 *  xiimap.c -                                                               *
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
    Synopsis:   Installs itself as a WSX filter agent on *.map, and handles
                server-side image maps.

*/
#include "smtdefn.h"                    /*  SMT definitions                  */
#include "smthttpl.h"                   /*  SMT HTTP definitions             */


/*- Definitions -------------------------------------------------------------*/

#undef  AGENT_NAME
#define AGENT_NAME        "xiimap"      /*  Our public name                  */
#define SINGLE_THREADED   TRUE          /*  Single-threaded agent            */
#define MAP_MAX_POINTS    100           /*  Max. points in one map line      */

static char *get_map_value        (char *map_file, char *request_point);
static void  point_in_map_element (char *buffer, char *rc_url, int x, int y,
                                   char *url_def);


/*- Global variables used in this source file only --------------------------*/

static struct_smt_wsx_request
    *request = NULL;                    /*  Incoming smt_wsx request         */

#include "xiimap.d"                     /*  Include dialog data              */


/********************   INITIALISE AGENT - ENTRY POINT   *********************/

int xiimap_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
#   include "xiimap.i"                  /*  Include dialog interpreter       */

    /*                      Method name   Event value     Priority          */
    /*  Shutdown event comes from Kernel                                     */
    method_declare (agent, "SHUTDOWN",    shutdown_event, SMT_PRIORITY_MAX);

    /*  Public methods supported by this agent                               */
    method_declare (agent, "WSX_REQUEST", request_event,  0);

    /*  Create master thread to manage WSX requests                          */
    thread_create (AGENT_NAME, "main");

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}


/*************************   INITIALISE THE THREAD   *************************/

MODULE initialise_the_thread (THREAD *thread)
{
    /*  This agent is installed by the config file, which lets us enable/
     *  disable it per virtual host.
     */
    the_next_event = ok_event;
}


/***************************   DECODE WSX REQUEST   **************************/

MODULE decode_wsx_request (THREAD *thread)
{
    ASSERT (request == NULL);

    get_smt_wsx_request (thread-> event-> body, &request);
    if (request)
        the_next_event = ok_event;
    else
      {
        /*  The request can only be null if there is no memory left          */
        send_wsx_error (&thread-> event-> sender, HTTP_RESPONSE_OVERLOADED);
        the_next_event = exception_event;
      }
}



/***********************   RETURN URL FROM IMAGE MAP   ***********************/

MODULE return_url_from_image_map (THREAD *thread)
{
    char
        *url_map;                       /*  URL for image map                */

    url_map = get_map_value (request-> filename, request-> arguments);
    if (url_map)
        send_wsx_redirect (&thread-> event-> sender, url_map);
    else
        send_wsx_error    (&thread-> event-> sender, HTTP_RESPONSE_NOTFOUND);
}


/*  -------------------------------------------------------------------------
    Function: get_map_value - Internal

    Synopsis: Returns a URL in function of a point in the map.  Uses a map
    file in NCSA format.  Returns a static pointer to an URL name if one
    was found, else returns NULL.  The point is supplied as a string
    formatted like this: "X,Y" - e.g. "120,12".  The map file must be fully
    specified.
    -------------------------------------------------------------------------*/

static char *
get_map_value (
    char *map_file,                     /*  Name of map file                 */
    char *request_point                 /*  Point coordinates                */
)
{
    static char
        buffer      [LINE_MAX],         /*  Buffer for map file line         */
        url         [LINE_MAX],         /*  Buffer to store URL              */
        default_url [LINE_MAX];         /*  Default URL value for the map    */
    char
        *full_uri;                      /*  Full URI                         */
    FILE
        *file;
    int
        point_x = 0,                    /*  Used only for sscanf             */
        point_y = 0;

    ASSERT (map_file);

    strclr (url);
    strclr (default_url);
    file = file_open (map_file, 'r');
    if (file)
      {
        /*  Get the coodinates of point                                      */
        if (request_point)
            sscanf (request_point, "%d,%d", &point_x, &point_y);

        /*  Note: The first line of map sets the value url_def               */
        while (file_readn (file, buffer, LINE_MAX))
          {
            /*  Ignore comments and blank lines                              */
            if ((buffer [0] == '#') || strnull (buffer))
                continue;
            point_in_map_element (buffer, url, point_x, point_y, default_url);
            if (strused (url))
                break;
           }
        /*  If not found a URL, set the return with the default value        */
        if (strnull (url))
            strcpy (url, default_url);

        file_close (file);
      }

    /*  Return final URL string, or NULL if we did not find anything         */
    if (strused (url))
      {
        full_uri = build_full_url (url, map_file);
        strcpy (url, full_uri);
        mem_free (full_uri);
        return (url);
      }
    else
        return (NULL);
}


/*  -------------------------------------------------------------------------
    Function: point_in_map_element - Internal

    Synopsis: Check if the requested point is in the element.
              The syntax of each map line is:
                  <Type of element> <URL> <x,y>...
              Each item must be separated by 1 or more spaces.
              Element is point, rectangle, circle, polygon, or default.
              Example:
              poly /test.htm 49,6 93,16 88,50
    -------------------------------------------------------------------------*/

static void
point_in_map_element (char *line, char *return_url, int point_x, int point_y,
                      char *default_url)
{
    char
        **tokens,                       /*  Line split into tokens           */
        *map_type,                      /*  Element type name                */
        *map_url,                       /*  Element URL value                */
        *comma;                         /*  Split x,y at comma               */
    FPOINT
        click_point,                    /*  Request point                    */
        shape_points [MAP_MAX_POINTS];  /*  Array of element point           */
    int
        token_nbr,                      /*  Index into token array           */
        nbr_points;                     /*  Number of points in element      */

    /*  Store selected point in image                                        */
    click_point.x = (double) point_x;
    click_point.y = (double) point_y;

    /*  Now parse the map file line into space-delimited tokens              */
    tokens = tok_split (line);

    /*  Ignore anything which is unparsable                                  */
    if (tokens [0] == NULL || tokens [1] == NULL)
      {
        tok_free (tokens);              /*  Release memory                   */
        return;
      }

    /*  First token is image element type; second is the URL                 */
    map_type = strlwc (tokens [0]);
    map_url  = tokens [1];

    /*  Third to n tokens are x,y pairs...                                   */
    token_nbr = 2;
    for (nbr_points = 0; nbr_points < MAP_MAX_POINTS; nbr_points++)
      {
        if (!tokens [token_nbr])
            break;                      /*  Null token => finished           */
        comma = strchr (tokens [token_nbr], ',');
        if (!comma)
            break;                      /*  Syntax error in line => quit     */
        *comma = '\0';                  /*  Else break into separate x & y   */
        shape_points [nbr_points].x = atof (tokens [token_nbr]);
        shape_points [nbr_points].y = atof (comma + 1);
        token_nbr++;                    /*  Bump to next token               */
      }

    /*  Check element type and test the request point                      */
    if (streq (map_type, "poly"))
      {
        if (point_in_poly (&click_point, shape_points, nbr_points))
            strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "circle"))
      {
        if (point_in_circle (&click_point, shape_points))
            strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "rect"))
      {
        if (point_in_rect (&click_point, shape_points))
            strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "point"))
      {
        double dist;
        dist = ((click_point.x - shape_points [0].x)
             *  (click_point.x - shape_points [0].x))
             + ((click_point.y - shape_points [0].y)
             *  (click_point.y - shape_points [0].y));
       if (dist < 10)
          strcpy (return_url, map_url);
      }
    else
    if (streq (map_type, "default"))
        strcpy (default_url, map_url);

    tok_free (tokens);                  /*  Release memory                   */
}


/****************************   FREE WSX REQUEST   ***************************/

MODULE free_wsx_request (THREAD *thread)
{
    /*  We're finished with the request structure - deallocate it            */
    free_smt_wsx_request (&request);
}


/*************************   TERMINATE THE THREAD   **************************/

MODULE terminate_the_thread (THREAD *thread)
{
    /*  If we were interrupted during processing the request, free it.
     *  This avoids potential memory leaks.
     */
    if (request)
        free_smt_wsx_request (&request);

    the_next_event = terminate_event;
}

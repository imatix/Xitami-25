/*---------------------------------------------------------------------------
 *  xiadm12.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM12__
#define __FORM_XIADM12__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define RESOURCE_LIST_MAX                   15
#define XIADM12_L_URI_NAME                  0
#define XIADM12_L_URI_PATH                  1
#define XIADM12_L_WEBMASK                   2
#define XIADM12_L_REALM                     3
#define XIADM12_L_URI_USERS                 4
#define XIADM12_URI_NAME                    5
#define XIADM12_URI_PATH                    6
#define XIADM12_WEBMASK                     7
#define XIADM12_REALM                       8
#define XIADM12_URI_USERS                   9
#define XIADM12_L_NEW_URI                   10
#define XIADM12_NEW_URI                     11
#define XIADM12_RESOURCE_LIST               12
#define XIADM12_MESSAGE_TO_USER             13

/*  This table contains each block in the form                               */

static byte xiadm12_blocks [] = {
    /*  Cache-control: no-cache                                              */
    0, 25, 0, 'C', 'a', 'c', 'h', 'e', 45, 'c', 'o', 'n', 't', 'r', 'o',
    'l', ':', 32, 'n', 'o', 45, 'c', 'a', 'c', 'h', 'e', 10,
    /*  Expires: 0                                                           */
    0, 12, 0, 'E', 'x', 'p', 'i', 'r', 'e', 's', ':', 32, '0', 10,
    /*                                                                       */
    0, 2, 0, 10,
    /*  <HTML>                                                               */
    0, 8, 0, '<', 'H', 'T', 'M', 'L', '>', 10,
    /*  <HEAD><TITLE>Xitami Administration</TITLE>                           */
    0, 44, 0, '<', 'H', 'E', 'A', 'D', '>', '<', 'T', 'I', 'T', 'L',
    'E', '>', 'X', 'i', 't', 'a', 'm', 'i', 32, 'A', 'd', 'm', 'i', 'n',
    'i', 's', 't', 'r', 'a', 't', 'i', 'o', 'n', '<', '/', 'T', 'I',
    'T', 'L', 'E', '>', 10,
    /*  <script type="text/javascript">                                      */
    0, 33, 0, '<', 's', 'c', 'r', 'i', 'p', 't', 32, 't', 'y', 'p', 'e',
    '=', '"', 't', 'e', 'x', 't', '/', 'j', 'a', 'v', 'a', 's', 'c',
    'r', 'i', 'p', 't', '"', '>', 10,
    /*  function show(img,show) {    ... forms[0].#(_focus).focus();}        */
    1, 228, 0, 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', 32, 's', 'h',
    'o', 'w', '(', 'i', 'm', 'g', ',', 's', 'h', 'o', 'w', ')', 32, '{',
    10, 32, 32, 32, 32, 'i', 'f', 32, '(', 'd', 'o', 'c', 'u', 'm', 'e',
    'n', 't', '.', 'i', 'm', 'a', 'g', 'e', 's', ')', 10, 32, 32, 32,
    32, 32, 32, 32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '[',
    'i', 'm', 'g', ']', '.', 's', 'r', 'c', 32, '=', 32, 's', 'h', 'o',
    'w', ';', 10, '}', 10, 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', 32,
    's', 'u', 'b', 'm', 'i', 't', '(', 'a', 'r', 'g', 'u', 'm', 'e',
    'n', 't', 's', ')', 32, '{', 10, 32, 32, 32, 32, 'd', 'o', 'c', 'u',
    'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm', 's', '[', '0', ']',
    '.', 'j', 's', 'a', 'c', 't', 'i', 'o', 'n', '.', 'v', 'a', 'l',
    'u', 'e', 32, '=', 32, 'a', 'r', 'g', 'u', 'm', 'e', 'n', 't', 's',
    ';', 10, 32, 32, 32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't',
    '.', 'f', 'o', 'r', 'm', 's', '[', '0', ']', '.', 's', 'u', 'b',
    'm', 'i', 't', '(', ')', ';', 10, '}', 10, 'f', 'u', 'n', 'c', 't',
    'i', 'o', 'n', 32, 's', 'u', 'b', 'c', 'o', 'n', 'f', '(', 'a', 'r',
    'g', 'u', 'm', 'e', 'n', 't', 's', ',', 'm', 'e', 's', 's', 'a',
    'g', 'e', ')', 32, '{', 10, 32, 32, 32, 32, 'i', 'f', 32, '(', 'm',
    'e', 's', 's', 'a', 'g', 'e', 32, '=', '=', 32, 39, 39, 32, '|',
    '|', 32, 'c', 'o', 'n', 'f', 'i', 'r', 'm', 32, '(', 'm', 'e', 's',
    's', 'a', 'g', 'e', ')', ')', 32, '{', 10, 32, 32, 32, 32, 32, 32,
    32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r',
    'm', 's', '[', '0', ']', '.', 'j', 's', 'a', 'c', 't', 'i', 'o',
    'n', '.', 'v', 'a', 'l', 'u', 'e', 32, '=', 32, 'a', 'r', 'g', 'u',
    'm', 'e', 'n', 't', 's', ';', 10, 32, 32, 32, 32, 32, 32, 32, 32,
    'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm',
    's', '[', '0', ']', '.', 's', 'u', 'b', 'm', 'i', 't', '(', ')',
    ';', 10, 32, 32, 32, 32, '}', 10, '}', 10, 'f', 'u', 'n', 'c', 't',
    'i', 'o', 'n', 32, 'f', 'o', 'c', 'u', 's', '(', ')', 32, '{', 10,
    32, 32, 32, 32, 'i', 'f', 32, '(', '"', '#', '(', '_', 'f', 'o',
    'c', 'u', 's', ')', '"', 32, '!', '=', 32, '"', 'j', 's', 'a', 'c',
    't', 'i', 'o', 'n', '"', ')', 10, 32, 32, 32, 32, 32, 32, 32, 32,
    'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm',
    's', '[', '0', ']', '.', '#', '(', '_', 'f', 'o', 'c', 'u', 's',
    ')', '.', 'f', 'o', 'c', 'u', 's', '(', ')', ';', 10, '}', 10,
    /*  </script>                                                            */
    0, 11, 0, '<', '/', 's', 'c', 'r', 'i', 'p', 't', '>', 10,
    /*  </HEAD>                                                              */
    0, 9, 0, '<', '/', 'H', 'E', 'A', 'D', '>', 10,
    /*  <BODY onLoad="focus()" style ... ns-serif" BGCOLOR="#87CEFA">        */
    0, 75, 0, '<', 'B', 'O', 'D', 'Y', 32, 'o', 'n', 'L', 'o', 'a', 'd',
    '=', '"', 'f', 'o', 'c', 'u', 's', '(', ')', '"', 32, 's', 't', 'y',
    'l', 'e', '=', '"', 'f', 'o', 'n', 't', 45, 'f', 'a', 'm', 'i', 'l',
    'y', ':', 32, 's', 'a', 'n', 's', 45, 's', 'e', 'r', 'i', 'f', '"',
    32, 'B', 'G', 'C', 'O', 'L', 'O', 'R', '=', '"', '#', '8', '7', 'C',
    'E', 'F', 'A', '"', '>', 10,
    /*  <SCRIPT LANGUAGE="JavaScript">                                       */
    0, 32, 0, '<', 'S', 'C', 'R', 'I', 'P', 'T', 32, 'L', 'A', 'N', 'G',
    'U', 'A', 'G', 'E', '=', '"', 'J', 'a', 'v', 'a', 'S', 'c', 'r',
    'i', 'p', 't', '"', '>', 10,
    /*  function show(img,show) {    ... ent.forms[0].submit();    }}        */
    1, 128, 0, 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', 32, 's', 'h',
    'o', 'w', '(', 'i', 'm', 'g', ',', 's', 'h', 'o', 'w', ')', 32, '{',
    10, 32, 32, 32, 32, 'i', 'f', 32, '(', 'd', 'o', 'c', 'u', 'm', 'e',
    'n', 't', '.', 'i', 'm', 'a', 'g', 'e', 's', ')', 10, 32, 32, 32,
    32, 32, 32, 32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '[',
    'i', 'm', 'g', ']', '.', 's', 'r', 'c', 32, '=', 32, 's', 'h', 'o',
    'w', ';', 10, '}', 10, 'f', 'u', 'n', 'c', 't', 'i', 'o', 'n', 32,
    's', 'u', 'b', 'f', 'o', 'r', 'm', '(', 'a', 'r', 'g', 'u', 'm',
    'e', 'n', 't', 's', ')', 32, '{', 10, 32, 32, 32, 32, 'd', 'o', 'c',
    'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm', 's', '[', '0',
    ']', '.', 'j', 's', 'a', 'c', 't', 'i', 'o', 'n', '.', 'v', 'a',
    'l', 'u', 'e', 32, '=', 32, 'a', 'r', 'g', 'u', 'm', 'e', 'n', 't',
    's', ';', 10, 32, 32, 32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n',
    't', '.', 'f', 'o', 'r', 'm', 's', '[', '0', ']', '.', 's', 'u',
    'b', 'm', 'i', 't', '(', ')', ';', 10, '}', 10, 'f', 'u', 'n', 'c',
    't', 'i', 'o', 'n', 32, 's', 'u', 'b', 'c', 'o', 'n', 'f', '(', 'a',
    'r', 'g', 'u', 'm', 'e', 'n', 't', 's', ',', 'm', 'e', 's', 's',
    'a', 'g', 'e', ')', 32, '{', 10, 32, 32, 32, 32, 'i', 'f', 32, '(',
    'm', 'e', 's', 's', 'a', 'g', 'e', 32, '=', '=', 32, 39, 39, 32,
    '|', '|', 32, 'c', 'o', 'n', 'f', 'i', 'r', 'm', 32, '(', 'm', 'e',
    's', 's', 'a', 'g', 'e', ')', ')', 32, '{', 10, 32, 32, 32, 32, 32,
    32, 32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o',
    'r', 'm', 's', '[', '0', ']', '.', 'j', 's', 'a', 'c', 't', 'i',
    'o', 'n', '.', 'v', 'a', 'l', 'u', 'e', 32, '=', 32, 'a', 'r', 'g',
    'u', 'm', 'e', 'n', 't', 's', ';', 10, 32, 32, 32, 32, 32, 32, 32,
    32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm',
    's', '[', '0', ']', '.', 's', 'u', 'b', 'm', 'i', 't', '(', ')',
    ';', 10, 32, 32, 32, 32, '}', 10, '}', 10,
    /*  </SCRIPT>                                                            */
    0, 11, 0, '<', '/', 'S', 'C', 'R', 'I', 'P', 'T', '>', 10,
    /*  <TABLE CELLSPACING=0 CELLPADDING=0 WIDTH=100%>                       */
    0, 48, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'C', 'E', 'L', 'L', 'S',
    'P', 'A', 'C', 'I', 'N', 'G', '=', '0', 32, 'C', 'E', 'L', 'L', 'P',
    'A', 'D', 'D', 'I', 'N', 'G', '=', '0', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', 10,
    /*  <FORM METHOD=POST ACTION="#(proto)#(host)#(uri)">                    */
    0, 51, 0, '<', 'F', 'O', 'R', 'M', 32, 'M', 'E', 'T', 'H', 'O', 'D',
    '=', 'P', 'O', 'S', 'T', 32, 'A', 'C', 'T', 'I', 'O', 'N', '=', '"',
    '#', '(', 'p', 'r', 'o', 't', 'o', ')', '#', '(', 'h', 'o', 's',
    't', ')', '#', '(', 'u', 'r', 'i', ')', '"', '>', 10,
    /*  <INPUT TYPE=HIDDEN NAME=jsaction VALUE="">                           */
    0, 44, 0, '<', 'I', 'N', 'P', 'U', 'T', 32, 'T', 'Y', 'P', 'E', '=',
    'H', 'I', 'D', 'D', 'E', 'N', 32, 'N', 'A', 'M', 'E', '=', 'j', 's',
    'a', 'c', 't', 'i', 'o', 'n', 32, 'V', 'A', 'L', 'U', 'E', '=', '"',
    '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT>                                                  */
    0, 21, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 51, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'l', 'e', 'f', 't', '.', 'g', 'i',
    'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A', 'L',
    'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>',
    /*  !--ACTION back81  LABEL="/ad ...  ROLLOVER="/admin/backa.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '8',
    '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c', 'k',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b', 'a',
    'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save82  LABEL="/ad ...  ROLLOVER="/admin/savea.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '8',
    '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v', 'e',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's', 'a',
    'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo83  LABEL="/ad ...  ROLLOVER="/admin/undoa.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 2, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '8',
    '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd', 'o',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u', 'n',
    'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION first84  LABEL="/a ... ROLLOVER="/admin/firsta.gif"        */
    0, 59, 20, 2, 1, (byte) ((word) first_event / 256), (byte) ((word)
    first_event & 255), 0, 3, 0, 0, 39, 0, '(', 'f', 'i', 'r', 's', 't',
    '8', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'f', 'i', 'r',
    's', 't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    'f', 'i', 'r', 's', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION next85  LABEL="/ad ...  ROLLOVER="/admin/nexta.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) next_event / 256), (byte) ((word)
    next_event & 255), 0, 4, 0, 0, 39, 0, '(', 'n', 'e', 'x', 't', '8',
    '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'x', 't',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'n', 'e',
    'x', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 80, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'c', 'g', 'i',
    '_', 'e', 'n', 'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', '"', 32,
    'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H', 'e', 'l', 'p', '"', 32,
    'T', 'I', 'T', 'L', 'E', '=', '"', 'H', 'e', 'l', 'p', '"', 10,
    /*  onMouseOver="show('Help','/a ... .gif" BORDER=0 ALIGN=MIDDLE>        */
    0, 236, 0, 'o', 'n', 'M', 'o', 'u', 's', 'e', 'O', 'v', 'e', 'r',
    '=', '"', 's', 'h', 'o', 'w', '(', 39, 'H', 'e', 'l', 'p', 39, ',',
    39, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h', 'e', 'l', 'p', 'a', '.',
    'g', 'i', 'f', 39, ')', '"', 10, 'o', 'n', 'M', 'o', 'u', 's', 'e',
    'O', 'u', 't', '=', '"', 's', 'h', 'o', 'w', '(', 39, 'H', 'e', 'l',
    'p', 39, ',', 39, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'e',
    'l', 'p', '.', 'g', 'i', 'f', 39, ')', '"', '>', '<', 'I', 'M', 'G',
    32, 'S', 'R', 'C', '=', '"', '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'h', 'e', 'l', 'p', '.', 'g', 'i', 'f', '"', 32, 'A', 'L', 'T', '=',
    '"', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A', 'L',
    'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', 32, 'N', 'A', 'M',
    'E', '=', '"', 'H', 'e', 'l', 'p', '"', 10, 'W', 'I', 'D', 'T', 'H',
    '=', '4', '0', 32, 'H', 'E', 'I', 'G', 'H', 'T', '=', '3', '9', '>',
    '<', '/', 'A', '>', '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"',
    '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'i', 'g', 'h', 't',
    '.', 'g', 'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0',
    32, 'A', 'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>',
    10,
    /*  <TD ALIGN=CENTER><FONT SIZE= ... ig) - Protected URIs </FONT>        */
    0, 67, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'P', 'r', 'o', 't', 'e', 'c', 't', 'e', 'd', 32,
    'U', 'R', 'I', 's', 32, '<', '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console86  LABEL=" ... LLOVER="/admin/consolea.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 5, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '8', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt87  LABEL="/ad ...  ROLLOVER="/admin/halta.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 6, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '8',
    '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h', 'a',
    'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart88  LABEL=" ... LLOVER="/admin/restarta.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 7, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '8', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit89  LABEL="/ad ...  ROLLOVER="/admin/exita.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 8, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '8',
    '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i', 't',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'e', 'x',
    'i', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <IMG SRC="/admin/$right.gif" BORDER=0 ALIGN=MIDDLE>                  */
    0, 53, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'r', 'i', 'g', 'h', 't', '.', 'g',
    'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A',
    'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', 10,
    /*  </TABLE><p>                                                          */
    0, 13, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', '<', 'p', '>', 10,
    /*  <FONT SIZE=-1>                                                       */
    0, 16, 0, '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E', '=', 45,
    '1', '>', 10,
    /*  !--ACTION ok  LABEL="Ok" EVE ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 22, 20, 1, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 9, 0, 0, 0, 0, 0, 'o', 'k', 0, 'O', 'k', 0, 0,
    0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 10, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0, 0, 0, 0, 0,
    /*  </FONT><HR>                                                          */
    0, 13, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH="90%"  CELLPADDING=0 CELLSPACING=0>                     */
    0, 50, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '9', '0', '%', '"', 32, 32, 'C', 'E', 'L', 'L', 'P', 'A',
    'D', 'D', 'I', 'N', 'G', '=', '0', 32, 'C', 'E', 'L', 'L', 'S', 'P',
    'A', 'C', 'I', 'N', 'G', '=', '0', '>', 10,
    /*  <TR>                                                                 */
    0, 6, 0, '<', 'T', 'R', '>', 10,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 30, 0, '<', 'T', 'H', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O',
    'P', '>', 10,
    /*  !--FIELD TEXTUAL f181 NAME=L ... VALUE="URI or partial URI:"         */
    0, 34, 10, 6, 1, 0, 0, 19, 0, 19, 'f', '1', '8', '1', 0, 'U', 'R',
    'I', 32, 'o', 'r', 32, 'p', 'a', 'r', 't', 'i', 'a', 'l', 32, 'U',
    'R', 'I', ':', 0, 0,
    /*  </TH>                                                                */
    0, 7, 0, '<', '/', 'T', 'H', '>', 10,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 9, 254,
    /*  !--FIELD TEXTUAL f182 NAME=L ... th VALUE="Translated path:"         */
    0, 31, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '1', '8', '2', 0, 'T', 'r',
    'a', 'n', 's', 'l', 'a', 't', 'e', 'd', 32, 'p', 'a', 't', 'h', ':',
    0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 'B',
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 9, 254,
    /*  !--FIELD TEXTUAL f183 NAME=L_webmask VALUE="IP address mask:"        */
    0, 31, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '1', '8', '3', 0, 'I', 'P',
    32, 'a', 'd', 'd', 'r', 'e', 's', 's', 32, 'm', 'a', 's', 'k', ':',
    0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 'B',
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 9, 254,
    /*  !--FIELD TEXTUAL f184 NAME=L ... LUE="Authentication realm:"         */
    0, 36, 10, 6, 1, 0, 0, 21, 0, 21, 'f', '1', '8', '4', 0, 'A', 'u',
    't', 'h', 'e', 'n', 't', 'i', 'c', 'a', 't', 'i', 'o', 'n', 32, 'r',
    'e', 'a', 'l', 'm', ':', 0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 'B',
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 9, 254,
    /*  !--FIELD TEXTUAL f185 NAME=L_uri-users VALUE="Users:"                */
    0, 21, 10, 6, 1, 0, 0, 6, 0, 6, 'f', '1', '8', '5', 0, 'U', 's',
    'e', 'r', 's', ':', 0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 'B',
    /*  !--REPEAT resource_list  ROWS=15                                     */
    0, 7, 4, 0, 12, 0, 18, 0, 15,
    /*  </TR>                                                                */
    0, 7, 0, '<', '/', 'T', 'R', '>', 10,
    /*  <TR>                                                                 */
    0, 4, 1, 0, 9, 246,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 42, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E',
    'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P', 32,
    'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'f', 'i', 'e', 'l', 'd',
    '>', 10,
    /*  !--FIELD TEXTUAL f186 NAME=u ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 10, 15, 0, 0, 'P', 0, 'P', 'f', '1', '8', '6', 0, 0, 0,
    /*  </TD>                                                                */
    0, 7, 0, '<', '/', 'T', 'D', '>', 10,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 18,
    /*  !--FIELD TEXTUAL f187 NAME=u ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 6, 15, 0, 0, '<', 0, '<', 'f', '1', '8', '7', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 'O',
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 18,
    /*  !--FIELD TEXTUAL f188 NAME=w ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 15, 0, 0, 15, 0, 'P', 'f', '1', '8', '8', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 'O',
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 18,
    /*  !--FIELD TEXTUAL f189 NAME=r ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 15, 0, 0, 15, 0, 'P', 'f', '1', '8', '9', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 'O',
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 18,
    /*  !--FIELD NUMERIC f190 NAME=u ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 6, 15, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '1', '9', '0',
    0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 'O',
    /*  </TR>                                                                */
    0, 4, 1, 0, 11, 3,
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f191 NAME=L ... protected URI:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '1', '9', '1', 0, 'A', 'd',
    'd', 32, 'n', 'e', 'w', 32, 'p', 'r', 'o', 't', 'e', 'c', 't', 'e',
    'd', 32, 'U', 'R', 'I', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f192 NAME=n ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '1', '9', '2', 0, 0, 0,
    /*  !--ACTION define90  LABEL="D ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 35, 20, 0, 1, (byte) ((word) define_event / 256), (byte) ((word)
    define_event & 255), 0, 11, 0, 0, 0, 0, 0, 'd', 'e', 'f', 'i', 'n',
    'e', '9', '0', 0, 'D', 'e', 'f', 'i', 'n', 'e', '.', '.', '.', 0, 0,
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 11, 215,
    /*  !--FIELD NUMERIC resource_list SIZE=4 VALUE=15                       */
    0, 31, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'r', 'e', 's', 'o',
    'u', 'r', 'c', 'e', '_', 'l', 'i', 's', 't', 0, '1', '5', 0, 0,
    /*  !--FIELD TEXTUAL message_to_user SIZE=120                            */
    0, 26, 10, 4, 1, 0, 0, 'x', 0, 'x', 'm', 'e', 's', 's', 'a', 'g',
    'e', '_', 't', 'o', '_', 'u', 's', 'e', 'r', 0, 0, 0,
    /*  </FORM>                                                              */
    0, 9, 0, '<', '/', 'F', 'O', 'R', 'M', '>', 10,
    /*  <SCRIPT LANGUAGE="JavaScript">                                       */
    0, 4, 1, 0, 2, 211,
    /*      if ("#(_focus)" != "jsac ... .forms[0].#(_focus).focus();        */
    0, 112, 0, 32, 32, 32, 32, 'i', 'f', 32, '(', '"', '#', '(', '_',
    'f', 'o', 'c', 'u', 's', ')', '"', 32, '!', '=', 32, '"', 'j', 's',
    'a', 'c', 't', 'i', 'o', 'n', '"', 32, '&', '&', 32, 'd', 'o', 'c',
    'u', 'm', 'e', 'n', 't', '.', 'f', 'o', 'r', 'm', 's', '[', '0',
    ']', '.', '#', '(', '_', 'f', 'o', 'c', 'u', 's', ')', ')', 10, 32,
    32, 32, 32, 32, 32, 32, 32, 'd', 'o', 'c', 'u', 'm', 'e', 'n', 't',
    '.', 'f', 'o', 'r', 'm', 's', '[', '0', ']', '.', '#', '(', '_',
    'f', 'o', 'c', 'u', 's', ')', '.', 'f', 'o', 'c', 'u', 's', '(',
    ')', ';', 10,
    /*  </SCRIPT>                                                            */
    0, 4, 1, 0, 4, 'w',
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH=100%><TR>                                               */
    0, 24, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', '<', 'T', 'R', '>', 10,
    /*  <TD><IMG SRC="/admin/imatix.gif"                                     */
    0, 34, 0, '<', 'T', 'D', '>', '<', 'I', 'M', 'G', 32, 'S', 'R', 'C',
    '=', '"', '/', 'a', 'd', 'm', 'i', 'n', '/', 'i', 'm', 'a', 't',
    'i', 'x', '.', 'g', 'i', 'f', '"', 10,
    /*  WIDTH=96 HEIGHT=41>                                                  */
    0, 21, 0, 'W', 'I', 'D', 'T', 'H', '=', '9', '6', 32, 'H', 'E', 'I',
    'G', 'H', 'T', '=', '4', '1', '>', 10,
    /*  <TD ALIGN=CENTER><FONT SIZE= ... 1996-2002 iMatix Corporation        */
    0, 77, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', 45, '1', '>', 'C', 'o', 'p', 'y', 'r', 'i', 'g', 'h', 't',
    32, '&', '#', '1', '6', '9', 32, '1', '9', '9', '6', 45, '2', '0',
    '0', '2', 32, 'i', 'M', 'a', 't', 'i', 'x', 32, 'C', 'o', 'r', 'p',
    'o', 'r', 'a', 't', 'i', 'o', 'n', 10,
    /*  <BR>Powered by iMatix Studio 2.5                                     */
    0, 34, 0, '<', 'B', 'R', '>', 'P', 'o', 'w', 'e', 'r', 'e', 'd', 32,
    'b', 'y', 32, 'i', 'M', 'a', 't', 'i', 'x', 32, 'S', 't', 'u', 'd',
    'i', 'o', 32, '2', '.', '5', 10,
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>#(date) #(time)                        */
    0, 47, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', '#', '(', 'd', 'a', 't', 'e', ')', 32, '#', '(',
    't', 'i', 'm', 'e', ')', 10,
    /*  <BR>#(product) v2.5c2                                                */
    0, 23, 0, '<', 'B', 'R', '>', '#', '(', 'p', 'r', 'o', 'd', 'u',
    'c', 't', ')', 32, 'v', '2', '.', '5', 'c', '2', 10,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 11, 215,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm12_fields [] = {
    { 0, 2590, 19 },                    /*  l_uri_name                      */
    { 21, 2641, 16 },                   /*  l_uri_path                      */
    { 39, 2686, 16 },                   /*  l_webmask                       */
    { 57, 2731, 21 },                   /*  l_realm                         */
    { 80, 2781, 6 },                    /*  l_uri_users                     */
    { 88, 2878, 80 },                   /*  uri_name                        */
    { 1318, 2910, 60 },                 /*  uri_path                        */
    { 2248, 2939, 80 },                 /*  webmask                         */
    { 3478, 2968, 80 },                 /*  realm                           */
    { 4708, 2997, 5 },                  /*  uri_users                       */
    { 4813, 3129, 34 },                 /*  l_new_uri                       */
    { 4849, 3243, 80 },                 /*  new_uri                         */
    { 4931, 3317, 4 },                  /*  resource_list                   */
    { 4937, 3350, 120 },                /*  message_to_user                 */
    { 5059, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_uri_name_a         ;
    char   l_uri_name           [19 + 1];
    byte   l_uri_path_a         ;
    char   l_uri_path           [16 + 1];
    byte   l_webmask_a          ;
    char   l_webmask            [16 + 1];
    byte   l_realm_a            ;
    char   l_realm              [21 + 1];
    byte   l_uri_users_a        ;
    char   l_uri_users          [6 + 1];
    byte   uri_name_a           [15] ;
    char   uri_name             [15] [80 + 1];
    byte   uri_path_a           [15] ;
    char   uri_path             [15] [60 + 1];
    byte   webmask_a            [15] ;
    char   webmask              [15] [80 + 1];
    byte   realm_a              [15] ;
    char   realm                [15] [80 + 1];
    byte   uri_users_a          [15] ;
    char   uri_users            [15] [5 + 1];
    byte   l_new_uri_a          ;
    char   l_new_uri            [34 + 1];
    byte   new_uri_a            ;
    char   new_uri              [80 + 1];
    byte   resource_list_a      ;
    char   resource_list        [4 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back81_a;
    byte   save82_a;
    byte   undo83_a;
    byte   first84_a;
    byte   next85_a;
    byte   console86_a;
    byte   halt87_a;
    byte   restart88_a;
    byte   exit89_a;
    byte   ok_a;
    byte   cancel_a;
    byte   define90_a;
    } XIADM12_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm12 = {
    xiadm12_blocks,
    xiadm12_fields,
    100,                                /*  Number of blocks in form        */
    14,                                 /*  Number of fields in form        */
    12,                                 /*  Number of actions in form       */
    5059,                               /*  Size of fields                  */
    "xiadm12",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

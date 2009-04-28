/*---------------------------------------------------------------------------
 *  xiadm30.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM30__
#define __FORM_XIADM30__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM30_L_ENABLED                   0
#define XIADM30_ENABLED                     1
#define XIADM30_L_FILENAME                  2
#define XIADM30_FILENAME                    3
#define XIADM30_L_SERVICE                   4
#define XIADM30_SERVICE                     5
#define XIADM30_L_DOMAIN                    6
#define XIADM30_DOMAIN                      7
#define XIADM30_L_USERNAME                  8
#define XIADM30_USERNAME                    9
#define XIADM30_L_PASSWORD                  10
#define XIADM30_PASSWORD                    11
#define XIADM30_MESSAGE_TO_USER             12

/*  This table contains each block in the form                               */

static byte xiadm30_blocks [] = {
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
    /*  !--ACTION back241  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '2',
    '4', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save242  LABEL="/a ...  ROLLOVER="/admin/savea.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '2',
    '4', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v',
    'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's',
    'a', 'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default243  LABEL= ... LLOVER="/admin/defaulta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '2', '4', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo244  LABEL="/a ...  ROLLOVER="/admin/undoa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '2',
    '4', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd',
    'o', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u',
    'n', 'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 69, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'd', 'd', 'n',
    's', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H', 'e', 'l',
    'p', '"', 32, 'T', 'I', 'T', 'L', 'E', '=', '"', 'H', 'e', 'l', 'p',
    '"', 10,
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ... mic DNS Registration </FONT>        */
    0, 77, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'D', 'y', 'n', 'a', 'm', 'i', 'c', 32, 'D', 'N',
    'S', 32, 'R', 'e', 'g', 'i', 's', 't', 'r', 'a', 't', 'i', 'o', 'n',
    32, '<', '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console245  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '2', '4', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt246  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '2',
    '4', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart247  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '2', '4', '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit248  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '2',
    '4', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'e',
    'x', 'i', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
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
    save_event & 255), 0, 8, 0, 0, 0, 0, 0, 'o', 'k', 0, 'O', 'k', 0, 0,
    0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 9, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0, 0, 0, 0, 0,
    /*  </FONT><HR>                                                          */
    0, 13, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'H', 'R', '>', 10,
    /*  <P>Xitami will automatically ... most popular DDNS providers.        */
    0, 73, 0, '<', 'P', '>', 'X', 'i', 't', 'a', 'm', 'i', 32, 'w', 'i',
    'l', 'l', 32, 'a', 'u', 't', 'o', 'm', 'a', 't', 'i', 'c', 'a', 'l',
    'l', 'y', 32, 'r', 'e', 'g', 'i', 's', 't', 'e', 'r', 32, 'w', 'i',
    't', 'h', 32, 'm', 'o', 's', 't', 32, 'p', 'o', 'p', 'u', 'l', 'a',
    'r', 32, 'D', 'D', 'N', 'S', 32, 'p', 'r', 'o', 'v', 'i', 'd', 'e',
    'r', 's', '.', 10,
    /*  When you enter your password ...  type it exactlyas provided.        */
    0, 86, 0, 'W', 'h', 'e', 'n', 32, 'y', 'o', 'u', 32, 'e', 'n', 't',
    'e', 'r', 32, 'y', 'o', 'u', 'r', 32, 'p', 'a', 's', 's', 'w', 'o',
    'r', 'd', 32, 'o', 'r', 32, 'D', 'D', 'N', 'S', 32, 'k', 'e', 'y',
    ',', 32, 'm', 'a', 'k', 'e', 32, 's', 'u', 'r', 'e', 32, 'y', 'o',
    'u', 32, 't', 'y', 'p', 'e', 32, 'i', 't', 32, 'e', 'x', 'a', 'c',
    't', 'l', 'y', 10, 'a', 's', 32, 'p', 'r', 'o', 'v', 'i', 'd', 'e',
    'd', '.', 10,
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
    /*  !--FIELD TEXTUAL f451 NAME=L ... c DNS sign-on?&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, 39, 0, 39, 'f', '4', '5', '1', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'd', 'y', 'n', 'a', 'm', 'i', 'c', 32, 'D',
    'N', 'S', 32, 's', 'i', 'g', 'n', 45, 'o', 'n', '?', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD BOOLEAN f452 NAME=e ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '5', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 'W',
    /*  !--FIELD TEXTUAL f453 NAME=L ... efinition file&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '4', '5', '3', 0, 'D', 'D',
    'N', 'S', 32, 's', 'e', 'r', 'v', 'i', 'c', 'e', 32, 'd', 'e', 'f',
    'i', 'n', 'i', 't', 'i', 'o', 'n', 32, 'f', 'i', 'l', 'e', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 198,
    /*  !--FIELD TEXTUAL f454 NAME=f ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '4', '5', '4', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 'W',
    /*  !--FIELD TEXTUAL f455 NAME=L ... c DNS service:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '4', '5', '5', 0, 'D', 'y',
    'n', 'a', 'm', 'i', 'c', 32, 'D', 'N', 'S', 32, 's', 'e', 'r', 'v',
    'i', 'c', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 198,
    /*  !--FIELD SELECT f456 NAME=se ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '4', '5', '6', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 'W',
    /*  !--FIELD TEXTUAL f457 NAME=L ... r domain name:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '4', '5', '7', 0, 'Y', 'o',
    'u', 'r', 32, 's', 'e', 'r', 'v', 'e', 'r', 32, 'd', 'o', 'm', 'a',
    'i', 'n', 32, 'n', 'a', 'm', 'e', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 198,
    /*  !--FIELD TEXTUAL f458 NAME=d ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '4', '5', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 'W',
    /*  !--FIELD TEXTUAL f459 NAME=L ... mail adddress:&nbsp;&nbsp;"         */
    0, 60, 10, 6, 1, 0, 0, 45, 0, 45, 'f', '4', '5', '9', 0, 'Y', 'o',
    'u', 'r', 32, 'u', 's', 'e', 'r', 'n', 'a', 'm', 'e', 32, 'o', 'r',
    32, 'e', 45, 'm', 'a', 'i', 'l', 32, 'a', 'd', 'd', 'd', 'r', 'e',
    's', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 198,
    /*  !--FIELD TEXTUAL f460 NAME=u ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '4', '6', '0', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 'W',
    /*  !--FIELD TEXTUAL f461 NAME=L ... d or DDNS key:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '4', '6', '1', 0, 'Y', 'o',
    'u', 'r', 32, 'p', 'a', 's', 's', 'w', 'o', 'r', 'd', 32, 'o', 'r',
    32, 'D', 'D', 'N', 'S', 32, 'k', 'e', 'y', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 198,
    /*  !--FIELD TEXTUAL f462 NAME=p ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '<', 0, '<', 'f', '4', '6', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 56, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '9', '9', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L',
    'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P',
    32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'b', 'o', 'd', 'y', '>',
    10,
    /*  <P>                                                                  */
    0, 4, 1, 0, 10, '8',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  <TR><TD></TD><TD VALIGN=TOP  ... WIDTH=""80%"" CLASS=tdvalue>        */
    0, 69, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T',
    'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E', 'F', 'T', 32,
    'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8', '0', '%', '"', '"', 32,
    'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v', 'a', 'l', 'u', 'e',
    '>', 10,
    /*  !--ACTION sign_on  LABEL="Si ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 32, 20, 0, 1, (byte) ((word) signon_event / 256), (byte) ((word)
    signon_event & 255), 0, 10, 0, 0, 0, 0, 0, 's', 'i', 'g', 'n', '_',
    'o', 'n', 0, 'S', 'i', 'g', 'n', 45, 'o', 'n', 0, 0, 0, 0, 0,
    /*  !--ACTION sign_off  LABEL="S ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 34, 20, 0, 1, (byte) ((word) signoff_event / 256), (byte) ((word)
    signoff_event & 255), 0, 11, 0, 0, 0, 0, 0, 's', 'i', 'g', 'n', '_',
    'o', 'f', 'f', 0, 'S', 'i', 'g', 'n', 45, 'o', 'f', 'f', 0, 0, 0, 0,
    0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 25,
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
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
    0, 4, 1, 0, 13, 210,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm30_fields [] = {
    { 0, 2702, 39 },                    /*  l_enabled                       */
    { 41, 2821, 1 },                    /*  enabled                         */
    { 44, 2861, 40 },                   /*  l_filename                      */
    { 86, 2924, 80 },                   /*  filename                        */
    { 168, 2953, 32 },                  /*  l_service                       */
    { 202, 3008, 3 },                   /*  service                         */
    { 207, 3052, 36 },                  /*  l_domain                        */
    { 245, 3111, 60 },                  /*  domain                          */
    { 307, 3140, 45 },                  /*  l_username                      */
    { 354, 3208, 60 },                  /*  username                        */
    { 416, 3237, 38 },                  /*  l_password                      */
    { 456, 3298, 60 },                  /*  password                        */
    { 518, 3550, 120 },                 /*  message_to_user                 */
    { 640, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_enabled_a          ;
    char   l_enabled            [39 + 1];
    byte   enabled_a            ;
    char   enabled              [1 + 1];
    byte   l_filename_a         ;
    char   l_filename           [40 + 1];
    byte   filename_a           ;
    char   filename             [80 + 1];
    byte   l_service_a          ;
    char   l_service            [32 + 1];
    byte   service_a            ;
    char   service              [3 + 1];
    byte   l_domain_a           ;
    char   l_domain             [36 + 1];
    byte   domain_a             ;
    char   domain               [60 + 1];
    byte   l_username_a         ;
    char   l_username           [45 + 1];
    byte   username_a           ;
    char   username             [60 + 1];
    byte   l_password_a         ;
    char   l_password           [38 + 1];
    byte   password_a           ;
    char   password             [60 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back241_a;
    byte   save242_a;
    byte   default243_a;
    byte   undo244_a;
    byte   console245_a;
    byte   halt246_a;
    byte   restart247_a;
    byte   exit248_a;
    byte   ok_a;
    byte   cancel_a;
    byte   sign_on_a;
    byte   sign_off_a;
    } XIADM30_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm30 = {
    xiadm30_blocks,
    xiadm30_fields,
    94,                                 /*  Number of blocks in form        */
    13,                                 /*  Number of fields in form        */
    12,                                 /*  Number of actions in form       */
    640,                                /*  Size of fields                  */
    "xiadm30",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

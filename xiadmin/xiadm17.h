/*---------------------------------------------------------------------------
 *  xiadm17.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM17__
#define __FORM_XIADM17__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define FTP_USER_LIST_MAX                   15
#define XIADM17_L_USER_NAME                 0
#define XIADM17_L_PASSWORD                  1
#define XIADM17_L_ROOTDIR                   2
#define XIADM17_L_ACCESS                    3
#define XIADM17_L_CUR_USAGE                 4
#define XIADM17_L_CUR_FILES                 5
#define XIADM17_USER_NAME                   6
#define XIADM17_PASSWORD                    7
#define XIADM17_ROOTDIR                     8
#define XIADM17_ACCESS                      9
#define XIADM17_CUR_USAGE                   10
#define XIADM17_CUR_FILES                   11
#define XIADM17_FTP_USER_LIST               12
#define XIADM17_MESSAGE_TO_USER             13

/*  This table contains each block in the form                               */

static byte xiadm17_blocks [] = {
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
    /*  !--ACTION back129  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '1',
    '2', '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION new130  LABEL="/ad ... " ROLLOVER="/admin/newa.gif"        */
    0, 54, 20, 2, 1, (byte) ((word) new_event / 256), (byte) ((word)
    new_event & 255), 0, 1, 0, 0, 39, 0, '(', 'n', 'e', 'w', '1', '3',
    '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'w', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'n', 'e', 'w',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save131  LABEL="/a ...  ROLLOVER="/admin/savea.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 2, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '1',
    '3', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v',
    'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's',
    'a', 'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo132  LABEL="/a ...  ROLLOVER="/admin/undoa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '1',
    '3', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd',
    'o', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u',
    'n', 'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION first133  LABEL="/ ... ROLLOVER="/admin/firsta.gif"        */
    0, 60, 20, 2, 1, (byte) ((word) first_event / 256), (byte) ((word)
    first_event & 255), 0, 4, 0, 0, 39, 0, '(', 'f', 'i', 'r', 's', 't',
    '1', '3', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'f', 'i',
    'r', 's', 't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n',
    '/', 'f', 'i', 'r', 's', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION next134  LABEL="/a ...  ROLLOVER="/admin/nexta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) next_event / 256), (byte) ((word)
    next_event & 255), 0, 5, 0, 0, 39, 0, '(', 'n', 'e', 'x', 't', '1',
    '3', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'x',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'n',
    'e', 'x', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION refresh  LABEL="/a ... LLOVER="/admin/refresha.gif"        */
    0, 63, 20, 2, 1, (byte) ((word) refresh_event / 256), (byte) ((word)
    refresh_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 'f', 'r',
    'e', 's', 'h', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r', 'e',
    'f', 'r', 'e', 's', 'h', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm',
    'i', 'n', '/', 'r', 'e', 'f', 'r', 'e', 's', 'h', 'a', '.', 'g',
    'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 68, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'f', 't', 'p',
    '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H', 'e', 'l', 'p',
    '"', 32, 'T', 'I', 'T', 'L', 'E', '=', '"', 'H', 'e', 'l', 'p', '"',
    10,
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  - FTP User Profiles </FONT>        */
    0, 70, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'F', 'T', 'P', 32, 'U', 's', 'e', 'r', 32, 'P',
    'r', 'o', 'f', 'i', 'l', 'e', 's', 32, '<', '/', 'F', 'O', 'N', 'T',
    '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console135  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 7, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '1', '3', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt136  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 8, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '1',
    '3', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart137  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 9, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '1', '3', '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit138  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 10, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '1',
    '3', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
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
    save_event & 255), 0, 11, 0, 0, 0, 0, 0, 'o', 'k', 0, 'O', 'k', 0,
    0, 0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 12, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
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
    /*  !--FIELD TEXTUAL f253 NAME=L_user-name VALUE="User name:"            */
    0, 25, 10, 6, 1, 0, 0, 10, 0, 10, 'f', '2', '5', '3', 0, 'U', 's',
    'e', 'r', 32, 'n', 'a', 'm', 'e', ':', 0, 0,
    /*  </TH>                                                                */
    0, 7, 0, '<', '/', 'T', 'H', '>', 10,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 10, 'w',
    /*  !--FIELD TEXTUAL f254 NAME=L_password VALUE="Password:"              */
    0, 24, 10, 6, 1, 0, 0, 9, 0, 9, 'f', '2', '5', '4', 0, 'P', 'a',
    's', 's', 'w', 'o', 'r', 'd', ':', 0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 178,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 10, 'w',
    /*  !--FIELD TEXTUAL f255 NAME=L_rootdir VALUE="Login directory:"        */
    0, 31, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '2', '5', '5', 0, 'L', 'o',
    'g', 'i', 'n', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', ':',
    0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 178,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 10, 'w',
    /*  !--FIELD TEXTUAL f256 NAME=L_access VALUE="Permissions:"             */
    0, 27, 10, 6, 1, 0, 0, 12, 0, 12, 'f', '2', '5', '6', 0, 'P', 'e',
    'r', 'm', 'i', 's', 's', 'i', 'o', 'n', 's', ':', 0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 178,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 10, 'w',
    /*  !--FIELD TEXTUAL f257 NAME=L ... ge VALUE="Space used (Mb):"         */
    0, 31, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '2', '5', '7', 0, 'S', 'p',
    'a', 'c', 'e', 32, 'u', 's', 'e', 'd', 32, '(', 'M', 'b', ')', ':',
    0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 178,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 4, 1, 0, 10, 'w',
    /*  !--FIELD TEXTUAL f258 NAME=L ... es VALUE="Number of files:"         */
    0, 31, 10, 6, 1, 0, 0, 16, 0, 16, 'f', '2', '5', '8', 0, 'N', 'u',
    'm', 'b', 'e', 'r', 32, 'o', 'f', 32, 'f', 'i', 'l', 'e', 's', ':',
    0, 0,
    /*  </TH>                                                                */
    0, 4, 1, 0, 10, 178,
    /*  !--REPEAT ftp_user_list  ROWS=15                                     */
    0, 7, 4, 0, 12, 0, 21, 0, 15,
    /*  </TR>                                                                */
    0, 7, 0, '<', '/', 'T', 'R', '>', 10,
    /*  <TR>                                                                 */
    0, 4, 1, 0, 10, 'o',
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 42, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E',
    'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P', 32,
    'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'f', 'i', 'e', 'l', 'd',
    '>', 10,
    /*  !--FIELD TEXTUAL f259 NAME=u ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 10, 15, 0, 0, '(', 0, '(', 'f', '2', '5', '9', 0, 0, 0,
    /*  </TD>                                                                */
    0, 7, 0, '<', '/', 'T', 'D', '>', 10,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 169,
    /*  !--FIELD TEXTUAL f260 NAME=p ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 6, 15, 0, 0, '(', 0, '(', 'f', '2', '6', '0', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 230,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 169,
    /*  !--FIELD TEXTUAL f261 NAME=r ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 6, 15, 0, 0, '2', 0, '2', 'f', '2', '6', '1', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 230,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 169,
    /*  !--FIELD TEXTUAL f262 NAME=a ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 6, 15, 0, 0, 6, 0, 6, 'f', '2', '6', '2', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 230,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 169,
    /*  !--FIELD NUMERIC f263 NAME=c ... E=15 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 6, 15, 0, 15, 0, 15, 3, 0, 2, 0, 0, 0, 'f', '2', '6',
    '3', 0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 230,
    /*  <TD ALIGN=LEFT VALIGN=TOP CLASS=tdfield>                             */
    0, 4, 1, 0, 11, 169,
    /*  !--FIELD NUMERIC f264 NAME=c ... ZE=7 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 6, 15, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 'f', '2', '6', '4',
    0, 0, 0,
    /*  </TD>                                                                */
    0, 4, 1, 0, 11, 230,
    /*  </TR>                                                                */
    0, 4, 1, 0, 11, 154,
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
    /*  !--FIELD NUMERIC ftp_user_list SIZE=4 VALUE=15                       */
    0, 31, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'f', 't', 'p', '_',
    'u', 's', 'e', 'r', '_', 'l', 'i', 's', 't', 0, '1', '5', 0, 0,
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
    0, 4, 1, 0, 12, 144,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm17_fields [] = {
    { 0, 2711, 10 },                    /*  l_user_name                     */
    { 12, 2753, 9 },                    /*  l_password                      */
    { 23, 2791, 16 },                   /*  l_rootdir                       */
    { 41, 2836, 12 },                   /*  l_access                        */
    { 55, 2877, 16 },                   /*  l_cur_usage                     */
    { 73, 2922, 16 },                   /*  l_cur_files                     */
    { 91, 3029, 40 },                   /*  user_name                       */
    { 721, 3061, 40 },                  /*  password                        */
    { 1351, 3090, 50 },                 /*  rootdir                         */
    { 2131, 3119, 6 },                  /*  access                          */
    { 2251, 3148, 15 },                 /*  cur_usage                       */
    { 2506, 3182, 7 },                  /*  cur_files                       */
    { 2641, 3228, 4 },                  /*  ftp_user_list                   */
    { 2647, 3261, 120 },                /*  message_to_user                 */
    { 2769, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_user_name_a        ;
    char   l_user_name          [10 + 1];
    byte   l_password_a         ;
    char   l_password           [9 + 1];
    byte   l_rootdir_a          ;
    char   l_rootdir            [16 + 1];
    byte   l_access_a           ;
    char   l_access             [12 + 1];
    byte   l_cur_usage_a        ;
    char   l_cur_usage          [16 + 1];
    byte   l_cur_files_a        ;
    char   l_cur_files          [16 + 1];
    byte   user_name_a          [15] ;
    char   user_name            [15] [40 + 1];
    byte   password_a           [15] ;
    char   password             [15] [40 + 1];
    byte   rootdir_a            [15] ;
    char   rootdir              [15] [50 + 1];
    byte   access_a             [15] ;
    char   access               [15] [6 + 1];
    byte   cur_usage_a          [15] ;
    char   cur_usage            [15] [15 + 1];
    byte   cur_files_a          [15] ;
    char   cur_files            [15] [7 + 1];
    byte   ftp_user_list_a      ;
    char   ftp_user_list        [4 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back129_a;
    byte   new130_a;
    byte   save131_a;
    byte   undo132_a;
    byte   first133_a;
    byte   next134_a;
    byte   refresh_a;
    byte   console135_a;
    byte   halt136_a;
    byte   restart137_a;
    byte   exit138_a;
    byte   ok_a;
    byte   cancel_a;
    } XIADM17_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm17 = {
    xiadm17_blocks,
    xiadm17_fields,
    99,                                 /*  Number of blocks in form        */
    14,                                 /*  Number of fields in form        */
    13,                                 /*  Number of actions in form       */
    2769,                               /*  Size of fields                  */
    "xiadm17",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

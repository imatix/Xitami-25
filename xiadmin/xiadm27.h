/*---------------------------------------------------------------------------
 *  xiadm27.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM27__
#define __FORM_XIADM27__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM27_L_USER_NAME                 0
#define XIADM27_USER_NAME                   1
#define XIADM27_L_PASSWORD                  2
#define XIADM27_PASSWORD                    3
#define XIADM27_L_ROOTDIR                   4
#define XIADM27_ROOTDIR                     5
#define XIADM27_L_ALIASES                   6
#define XIADM27_ALIASES                     7
#define XIADM27_L_NONAME5                   8
#define XIADM27_L_ACCESS_GET                9
#define XIADM27_ACCESS_GET                  10
#define XIADM27_L_ACCESS_PUT                11
#define XIADM27_ACCESS_PUT                  12
#define XIADM27_L_ACCESS_UPLOAD             13
#define XIADM27_ACCESS_UPLOAD               14
#define XIADM27_L_ACCESS_DELETE             15
#define XIADM27_ACCESS_DELETE               16
#define XIADM27_L_ACCESS_MKDIR              17
#define XIADM27_ACCESS_MKDIR                18
#define XIADM27_L_ACCESS_RMDIR              19
#define XIADM27_ACCESS_RMDIR                20
#define XIADM27_L_CHOOSER                   21
#define XIADM27_CHOOSER                     22
#define XIADM27_L_USE_QUOTAS                23
#define XIADM27_USE_QUOTAS                  24
#define XIADM27_L_SOFT_QUOTA                25
#define XIADM27_SOFT_QUOTA                  26
#define XIADM27_L_HARD_QUOTA                27
#define XIADM27_HARD_QUOTA                  28
#define XIADM27_L_PIPE                      29
#define XIADM27_PIPE                        30
#define XIADM27_MESSAGE_TO_USER             31

/*  This table contains each block in the form                               */

static byte xiadm27_blocks [] = {
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
    /*  !--ACTION back212  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '2',
    '1', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION new213  LABEL="/ad ... " ROLLOVER="/admin/newa.gif"        */
    0, 54, 20, 2, 1, (byte) ((word) new_event / 256), (byte) ((word)
    new_event & 255), 0, 1, 0, 0, 39, 0, '(', 'n', 'e', 'w', '2', '1',
    '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'w', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'n', 'e', 'w',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save214  LABEL="/a ...  ROLLOVER="/admin/savea.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 2, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '2',
    '1', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v',
    'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's',
    'a', 'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION delete  LABEL="/ad ... OLLOVER="/admin/deletea.gif"        */
    0, 60, 20, 2, 1, (byte) ((word) delete_event / 256), (byte) ((word)
    delete_event & 255), 0, 3, 0, 0, 39, 0, '(', 'd', 'e', 'l', 'e',
    't', 'e', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'd', 'e', 'l',
    'e', 't', 'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n',
    '/', 'd', 'e', 'l', 'e', 't', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0,
    0,
    /*  !--ACTION default215  LABEL= ... LLOVER="/admin/defaulta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 4, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '2', '1', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo216  LABEL="/a ...  ROLLOVER="/admin/undoa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 5, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '2',
    '1', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd',
    'o', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u',
    'n', 'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION first217  LABEL="/ ... ROLLOVER="/admin/firsta.gif"        */
    0, 60, 20, 2, 1, (byte) ((word) first_event / 256), (byte) ((word)
    first_event & 255), 0, 6, 0, 0, 39, 0, '(', 'f', 'i', 'r', 's', 't',
    '2', '1', '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'f', 'i',
    'r', 's', 't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n',
    '/', 'f', 'i', 'r', 's', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION next218  LABEL="/a ...  ROLLOVER="/admin/nexta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) next_event / 256), (byte) ((word)
    next_event & 255), 0, 7, 0, 0, 39, 0, '(', 'n', 'e', 'x', 't', '2',
    '1', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'n', 'e', 'x',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'n',
    'e', 'x', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 74, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'f', 't', 'p',
    '_', 'u', 's', 'e', 'r', 's', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T',
    '=', '"', 'H', 'e', 'l', 'p', '"', 32, 'T', 'I', 'T', 'L', 'E', '=',
    '"', 'H', 'e', 'l', 'p', '"', 10,
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  FTP User Properties </FONT>        */
    0, 72, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'F', 'T', 'P', 32, 'U', 's', 'e', 'r', 32, 'P',
    'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's', 32, '<', '/', 'F', 'O',
    'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console219  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 8, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '2', '1', '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt220  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 9, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '2',
    '2', '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart221  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 10, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '2', '2', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit222  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 11, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '2',
    '2', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
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
    save_event & 255), 0, 12, 0, 0, 0, 0, 0, 'o', 'k', 0, 'O', 'k', 0,
    0, 0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 13, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0, 0, 0, 0, 0,
    /*  </FONT><HR>                                                          */
    0, 13, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'H', 'R', '>', 10,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f365 NAME=L ... UE="User name:&nbsp;&nbsp;"         */
    0, 37, 10, 6, 1, 0, 0, 22, 0, 22, 'f', '3', '6', '5', 0, 'U', 's',
    'e', 'r', 32, 'n', 'a', 'm', 'e', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f366 NAME=u ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '3', '6', '6', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f367 NAME=L ... LUE="Password:&nbsp;&nbsp;"         */
    0, 36, 10, 6, 1, 0, 0, 21, 0, 21, 'f', '3', '6', '7', 0, 'P', 'a',
    's', 's', 'w', 'o', 'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD TEXTUAL f368 NAME=p ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '3', '6', '8', 0, 0, 0,
    /*  Blank=none; -=disabled; *=anonymous                                  */
    0, 37, 0, 'B', 'l', 'a', 'n', 'k', '=', 'n', 'o', 'n', 'e', ';', 32,
    45, '=', 'd', 'i', 's', 'a', 'b', 'l', 'e', 'd', ';', 32, '*', '=',
    'a', 'n', 'o', 'n', 'y', 'm', 'o', 'u', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f369 NAME=L ... gin directory:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '3', '6', '9', 0, 'L', 'o',
    'g', 'i', 'n', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD TEXTUAL f370 NAME=r ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '3', '7', '0', 0, 0, 0,
    /*  below ftproot, or absolute                                           */
    0, 28, 0, 'b', 'e', 'l', 'o', 'w', 32, 'f', 't', 'p', 'r', 'o', 'o',
    't', ',', 32, 'o', 'r', 32, 'a', 'b', 's', 'o', 'l', 'u', 't', 'e',
    10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f371 NAME=L ...  sees aliases?&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '7', '1', 0, 'U', 's',
    'e', 'r', 32, 's', 'e', 'e', 's', 32, 'a', 'l', 'i', 'a', 's', 'e',
    's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD BOOLEAN f372 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '7', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f373 NAME=L ... r permissions:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '7', '3', 0, 'U', 's',
    'e', 'r', 32, 'p', 'e', 'r', 'm', 'i', 's', 's', 'i', 'o', 'n', 's',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD TEXTUAL f374 NAME=L ... bsp;&nbsp;Get:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '3', '7', '4', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'G', 'e', 't',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  !--FIELD BOOLEAN f375 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '7', '5', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  !--FIELD TEXTUAL f376 NAME=L ... bsp;&nbsp;Put:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '3', '7', '6', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'P', 'u', 't',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  !--FIELD BOOLEAN f377 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '7', '7', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  !--FIELD TEXTUAL f378 NAME=L ... ;&nbsp;Upload:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '7', '8', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'U', 'p', 'l',
    'o', 'a', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  !--FIELD BOOLEAN f379 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '7', '9', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  !--FIELD TEXTUAL f380 NAME=L ... ;&nbsp;Delete:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '8', '0', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'D', 'e', 'l',
    'e', 't', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  !--FIELD BOOLEAN f381 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '8', '1', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  !--FIELD TEXTUAL f382 NAME=L ... p;&nbsp;Mkdir:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '8', '2', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'M', 'k', 'd',
    'i', 'r', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  !--FIELD BOOLEAN f383 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '8', '3', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  !--FIELD TEXTUAL f384 NAME=L ... p;&nbsp;Rmdir:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '8', '4', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'R', 'm', 'd',
    'i', 'r', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  !--FIELD BOOLEAN f385 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '8', '5', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f386 NAME=L ... sions chooser:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '3', '8', '6', 0, 'P', 'e',
    'r', 'm', 'i', 's', 's', 'i', 'o', 'n', 's', 32, 'c', 'h', 'o', 'o',
    's', 'e', 'r', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD SELECT f387 NAME=ch ... d upload" 5="Download only"         */
    0, 107, 16, 0, 1, 0, 5, 0, 'f', '3', '8', '7', 0, '0', 0, 'n', 'o',
    0, 0, 'L', 'e', 'a', 'v', 'e', 32, 'u', 'n', 'c', 'h', 'a', 'n',
    'g', 'e', 'd', 0, 'F', 'u', 'l', 'l', 32, 'a', 'c', 'c', 'e', 's',
    's', 0, 'R', 'e', 's', 't', 'r', 'i', 'c', 't', 'e', 'd', 32, 'a',
    'c', 'c', 'e', 's', 's', 0, 'F', 'u', 'l', 'l', 32, 'u', 'p', 'l',
    'o', 'a', 'd', 0, 'R', 'e', 's', 't', 'r', 'i', 'c', 't', 'e', 'd',
    32, 'u', 'p', 'l', 'o', 'a', 'd', 0, 'D', 'o', 'w', 'n', 'l', 'o',
    'a', 'd', 32, 'o', 'n', 'l', 'y', 0,
    /*  !--ACTION define  LABEL="Def ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) define_event / 256), (byte) ((word)
    define_event & 255), 0, 14, 0, 0, 0, 0, 0, 'd', 'e', 'f', 'i', 'n',
    'e', 0, 'D', 'e', 'f', 'i', 'n', 'e', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f388 NAME=L ... it disk usage?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '8', '8', 0, 'L', 'i',
    'm', 'i', 't', 32, 'd', 'i', 's', 'k', 32, 'u', 's', 'a', 'g', 'e',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD BOOLEAN f389 NAME=u ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '8', '9', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f390 NAME=L ... ft quota (Mb):&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '9', '0', 0, 32, 45, 32,
    's', 'o', 'f', 't', 32, 'q', 'u', 'o', 't', 'a', 32, '(', 'M', 'b',
    ')', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD TEXTUAL f391 NAME=s ... 10 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 8, 0, 10, 'f', '3', '9', '1', 0, 0, 0,
    /*  !--FIELD TEXTUAL f392 NAME=L ... rd quota (Mb):&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '3', '9', '2', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'h', 'a', 'r',
    'd', 32, 'q', 'u', 'o', 't', 'a', 32, '(', 'M', 'b', ')', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f393 NAME=h ... 10 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 8, 0, 10, 'f', '3', '9', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 156,
    /*  !--FIELD TEXTUAL f394 NAME=L ... Throttle pipe:&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '3', '9', '4', 0, 'T', 'h',
    'r', 'o', 't', 't', 'l', 'e', 32, 'p', 'i', 'p', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, 250,
    /*  !--FIELD SELECT f395 NAME=pi ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '3', '9', '5', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'J',
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
    0, 4, 1, 0, 16, 'y',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm27_fields [] = {
    { 0, 2771, 22 },                    /*  l_user_name                     */
    { 24, 2873, 40 },                   /*  user_name                       */
    { 66, 2910, 21 },                   /*  l_password                      */
    { 89, 2954, 40 },                   /*  password                        */
    { 131, 3022, 28 },                  /*  l_rootdir                       */
    { 161, 3073, 100 },                 /*  rootdir                         */
    { 263, 3132, 30 },                  /*  l_aliases                       */
    { 295, 3185, 1 },                   /*  aliases                         */
    { 298, 3217, 29 },                  /*  l_noname5                       */
    { 329, 3269, 28 },                  /*  l_access_get                    */
    { 359, 3314, 1 },                   /*  access_get                      */
    { 362, 3334, 28 },                  /*  l_access_put                    */
    { 392, 3379, 1 },                   /*  access_put                      */
    { 395, 3399, 31 },                  /*  l_access_upload                 */
    { 428, 3447, 1 },                   /*  access_upload                   */
    { 431, 3467, 31 },                  /*  l_access_delete                 */
    { 464, 3515, 1 },                   /*  access_delete                   */
    { 467, 3535, 30 },                  /*  l_access_mkdir                  */
    { 499, 3582, 1 },                   /*  access_mkdir                    */
    { 502, 3602, 30 },                  /*  l_access_rmdir                  */
    { 534, 3649, 1 },                   /*  access_rmdir                    */
    { 537, 3681, 32 },                  /*  l_chooser                       */
    { 571, 3736, 3 },                   /*  chooser                         */
    { 576, 3889, 29 },                  /*  l_use_quotas                    */
    { 607, 3941, 1 },                   /*  use_quotas                      */
    { 610, 3973, 31 },                  /*  l_soft_quota                    */
    { 643, 4027, 10 },                  /*  soft_quota                      */
    { 655, 4044, 40 },                  /*  l_hard_quota                    */
    { 697, 4101, 10 },                  /*  hard_quota                      */
    { 709, 4130, 26 },                  /*  l_pipe                          */
    { 737, 4179, 3 },                   /*  pipe                            */
    { 742, 4229, 120 },                 /*  message_to_user                 */
    { 864, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_user_name_a        ;
    char   l_user_name          [22 + 1];
    byte   user_name_a          ;
    char   user_name            [40 + 1];
    byte   l_password_a         ;
    char   l_password           [21 + 1];
    byte   password_a           ;
    char   password             [40 + 1];
    byte   l_rootdir_a          ;
    char   l_rootdir            [28 + 1];
    byte   rootdir_a            ;
    char   rootdir              [100 + 1];
    byte   l_aliases_a          ;
    char   l_aliases            [30 + 1];
    byte   aliases_a            ;
    char   aliases              [1 + 1];
    byte   l_noname5_a          ;
    char   l_noname5            [29 + 1];
    byte   l_access_get_a       ;
    char   l_access_get         [28 + 1];
    byte   access_get_a         ;
    char   access_get           [1 + 1];
    byte   l_access_put_a       ;
    char   l_access_put         [28 + 1];
    byte   access_put_a         ;
    char   access_put           [1 + 1];
    byte   l_access_upload_a    ;
    char   l_access_upload      [31 + 1];
    byte   access_upload_a      ;
    char   access_upload        [1 + 1];
    byte   l_access_delete_a    ;
    char   l_access_delete      [31 + 1];
    byte   access_delete_a      ;
    char   access_delete        [1 + 1];
    byte   l_access_mkdir_a     ;
    char   l_access_mkdir       [30 + 1];
    byte   access_mkdir_a       ;
    char   access_mkdir         [1 + 1];
    byte   l_access_rmdir_a     ;
    char   l_access_rmdir       [30 + 1];
    byte   access_rmdir_a       ;
    char   access_rmdir         [1 + 1];
    byte   l_chooser_a          ;
    char   l_chooser            [32 + 1];
    byte   chooser_a            ;
    char   chooser              [3 + 1];
    byte   l_use_quotas_a       ;
    char   l_use_quotas         [29 + 1];
    byte   use_quotas_a         ;
    char   use_quotas           [1 + 1];
    byte   l_soft_quota_a       ;
    char   l_soft_quota         [31 + 1];
    byte   soft_quota_a         ;
    char   soft_quota           [10 + 1];
    byte   l_hard_quota_a       ;
    char   l_hard_quota         [40 + 1];
    byte   hard_quota_a         ;
    char   hard_quota           [10 + 1];
    byte   l_pipe_a             ;
    char   l_pipe               [26 + 1];
    byte   pipe_a               ;
    char   pipe                 [3 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back212_a;
    byte   new213_a;
    byte   save214_a;
    byte   delete_a;
    byte   default215_a;
    byte   undo216_a;
    byte   first217_a;
    byte   next218_a;
    byte   console219_a;
    byte   halt220_a;
    byte   restart221_a;
    byte   exit222_a;
    byte   ok_a;
    byte   cancel_a;
    byte   define_a;
    } XIADM27_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm27 = {
    xiadm27_blocks,
    xiadm27_fields,
    119,                                /*  Number of blocks in form        */
    32,                                 /*  Number of fields in form        */
    15,                                 /*  Number of actions in form       */
    864,                                /*  Size of fields                  */
    "xiadm27",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

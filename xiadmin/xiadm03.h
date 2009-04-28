/*---------------------------------------------------------------------------
 *  xiadm03.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM03__
#define __FORM_XIADM03__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM03_MAIN_CONFIG                 0
#define XIADM03_ON_UNIX                     1
#define XIADM03_ON_WINDOWS_32               2
#define XIADM03_L_WEBPAGES                  3
#define XIADM03_WEBPAGES                    4
#define XIADM03_L_CGI_BIN                   5
#define XIADM03_CGI_BIN                     6
#define XIADM03_L_CGI_URL                   7
#define XIADM03_CGI_URL                     8
#define XIADM03_L_DEBUG                     9
#define XIADM03_DEBUG                       10
#define XIADM03_L_REFRESH_RATE              11
#define XIADM03_REFRESH_RATE                12
#define XIADM03_L_LIMIT                     13
#define XIADM03_LIMIT                       14
#define XIADM03_L_PIPE                      15
#define XIADM03_PIPE                        16
#define XIADM03_L_BACKGROUND                17
#define XIADM03_BACKGROUND                  18
#define XIADM03_L_AUTOSTART                 19
#define XIADM03_AUTOSTART                   20
#define XIADM03_L_RECOVER                   21
#define XIADM03_RECOVER                     22
#define XIADM03_L_DEFAULT1                  23
#define XIADM03_DEFAULT1                    24
#define XIADM03_L_DEFAULT2                  25
#define XIADM03_DEFAULT2                    26
#define XIADM03_DEFAULT3                    27
#define XIADM03_DEFAULT4                    28
#define XIADM03_L_KEEP_ALIVE                29
#define XIADM03_KEEP_ALIVE                  30
#define XIADM03_L_KEEP_ALIVE_MAX            31
#define XIADM03_KEEP_ALIVE_MAX              32
#define XIADM03_L_TIMEOUT                   33
#define XIADM03_TIMEOUT                     34
#define XIADM03_L_DIRSORT                   35
#define XIADM03_DIRSORT                     36
#define XIADM03_L_DIR_SCRIPT                37
#define XIADM03_DIR_SCRIPT                  38
#define XIADM03_MESSAGE_TO_USER             39

/*  This table contains each block in the form                               */

static byte xiadm03_blocks [] = {
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
    /*  !--ACTION back5  LABEL="/adm ...  ROLLOVER="/admin/backa.gif"        */
    0, 55, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '5',
    0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c', 'k', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b', 'a', 'c',
    'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save  LABEL="/admi ...  ROLLOVER="/admin/savea.gif"        */
    0, 54, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', 0,
    '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v', 'e', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's', 'a', 'v',
    'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default  LABEL="/a ... LLOVER="/admin/defaulta.gif"        */
    0, 63, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'd', 'e',
    'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm',
    'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't', 'a', '.', 'g',
    'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo  LABEL="/admi ...  ROLLOVER="/admin/undoa.gif"        */
    0, 54, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', 0,
    '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd', 'o', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u', 'n', 'd',
    'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 71, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 's', 'e', 'r',
    'v', 'e', 'r', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H',
    'e', 'l', 'p', '"', 32, 'T', 'I', 'T', 'L', 'E', '=', '"', 'H', 'e',
    'l', 'p', '"', 10,
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  - Server Properties </FONT>        */
    0, 70, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'S', 'e', 'r', 'v', 'e', 'r', 32, 'P', 'r', 'o',
    'p', 'e', 'r', 't', 'i', 'e', 's', 32, '<', '/', 'F', 'O', 'N', 'T',
    '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console6  LABEL="/ ... LLOVER="/admin/consolea.gif"        */
    0, 64, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c',
    'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd',
    'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e', 'a', '.',
    'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt7  LABEL="/adm ...  ROLLOVER="/admin/halta.gif"        */
    0, 55, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '7',
    0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h', 'a', 'l',
    't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart8  LABEL="/ ... LLOVER="/admin/restarta.gif"        */
    0, 64, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'r',
    'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd',
    'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't', 'a', '.',
    'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit9  LABEL="/adm ...  ROLLOVER="/admin/exita.gif"        */
    0, 55, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '9',
    0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i', 't', '.',
    'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'e', 'x', 'i',
    't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <IMG SRC="/admin/$right.gif" BORDER=0 ALIGN=MIDDLE>                  */
    0, 53, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'r', 'i', 'g', 'h', 't', '.', 'g',
    'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A',
    'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', 10,
    /*  </TABLE><p>                                                          */
    0, 13, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', '<', 'p', '>', 10,
    /*  <TABLE CELLSPACING=0 CELLPADDING=0 WIDTH=100%><TR>                   */
    0, 52, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'C', 'E', 'L', 'L', 'S',
    'P', 'A', 'C', 'I', 'N', 'G', '=', '0', 32, 'C', 'E', 'L', 'L', 'P',
    'A', 'D', 'D', 'I', 'N', 'G', '=', '0', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '1', '0', '0', '%', '>', '<', 'T', 'R', '>', 10,
    /*  <TD ALIGN=LEFT><FONT SIZE=-1>                                        */
    0, 31, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E',
    'F', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E', '=',
    45, '1', '>', 10,
    /*  !--ACTION aliases  LABEL="Al ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) aliases_event / 256), (byte) ((word)
    aliases_event & 255), 0, 8, 0, 0, 0, 0, 0, 'a', 'l', 'i', 'a', 's',
    'e', 's', 0, 'A', 'l', 'i', 'a', 's', 'e', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION errors  LABEL="Err ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) errors_event / 256), (byte) ((word)
    errors_event & 255), 0, 9, 0, 0, 0, 0, 0, 'e', 'r', 'r', 'o', 'r',
    's', 0, 'E', 'r', 'r', 'o', 'r', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION ssi  LABEL="SSI" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) ssi_event / 256), (byte) ((word)
    ssi_event & 255), 0, 10, 0, 0, 0, 0, 0, 's', 's', 'i', 0, 'S', 'S',
    'I', 0, 0, 0, 0, 0,
    /*  !--ACTION mimes  LABEL="MIME ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 28, 20, 1, 1, (byte) ((word) mimes_event / 256), (byte) ((word)
    mimes_event & 255), 0, 11, 0, 0, 0, 0, 0, 'm', 'i', 'm', 'e', 's',
    0, 'M', 'I', 'M', 'E', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION wsx  LABEL="WSX" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) wsx_event / 256), (byte) ((word)
    wsx_event & 255), 0, 12, 0, 0, 0, 0, 0, 'w', 's', 'x', 0, 'W', 'S',
    'X', 0, 0, 0, 0, 0,
    /*  !--ACTION filters  LABEL="Fi ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) filters_event / 256), (byte) ((word)
    filters_event & 255), 0, 13, 0, 0, 0, 0, 0, 'f', 'i', 'l', 't', 'e',
    'r', 's', 0, 'F', 'i', 'l', 't', 'e', 'r', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION ddns  LABEL="DDNS" ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 26, 20, 1, 1, (byte) ((word) ddns_event / 256), (byte) ((word)
    ddns_event & 255), 0, 14, 0, 0, 0, 0, 0, 'd', 'd', 'n', 's', 0, 'D',
    'D', 'N', 'S', 0, 0, 0, 0, 0,
    /*  !--ACTION advanced  LABEL="A ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 34, 20, 1, 1, (byte) ((word) advanced_event / 256), (byte)
    ((word) advanced_event & 255), 0, 15, 0, 0, 0, 0, 0, 'a', 'd', 'v',
    'a', 'n', 'c', 'e', 'd', 0, 'A', 'd', 'v', 'a', 'n', 'c', 'e', 'd',
    0, 0, 0, 0, 0,
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>                                       */
    0, 32, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', 10,
    /*  <EM>Server</EM>                                                      */
    0, 17, 0, '<', 'E', 'M', '>', 'S', 'e', 'r', 'v', 'e', 'r', '<',
    '/', 'E', 'M', '>', 10,
    /*  !--ACTION vhosts  LABEL="Vho ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) vhosts_event / 256), (byte) ((word)
    vhosts_event & 255), 0, 16, 0, 0, 0, 0, 0, 'v', 'h', 'o', 's', 't',
    's', 0, 'V', 'h', 'o', 's', 't', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION cgi  LABEL="CGI" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) cgi_event / 256), (byte) ((word)
    cgi_event & 255), 0, 17, 0, 0, 0, 0, 0, 'c', 'g', 'i', 0, 'C', 'G',
    'I', 0, 0, 0, 0, 0,
    /*  !--ACTION security  LABEL="S ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 34, 20, 1, 1, (byte) ((word) security_event / 256), (byte)
    ((word) security_event & 255), 0, 18, 0, 0, 0, 0, 0, 's', 'e', 'c',
    'u', 'r', 'i', 't', 'y', 0, 'S', 'e', 'c', 'u', 'r', 'i', 't', 'y',
    0, 0, 0, 0, 0,
    /*  !--ACTION logging  LABEL="Lo ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) logging_event / 256), (byte) ((word)
    logging_event & 255), 0, 19, 0, 0, 0, 0, 0, 'l', 'o', 'g', 'g', 'i',
    'n', 'g', 0, 'L', 'o', 'g', 'g', 'i', 'n', 'g', 0, 0, 0, 0, 0,
    /*  !--ACTION ftp  LABEL="FTP" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) ftp_event / 256), (byte) ((word)
    ftp_event & 255), 0, 20, 0, 0, 0, 0, 0, 'f', 't', 'p', 0, 'F', 'T',
    'P', 0, 0, 0, 0, 0,
    /*  </FONT></TABLE><HR>                                                  */
    0, 21, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', '/', 'T', 'A',
    'B', 'L', 'E', '>', '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC main_config SIZE=4 VALUE=1                          */
    0, 28, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'm', 'a', 'i', 'n',
    '_', 'c', 'o', 'n', 'f', 'i', 'g', 0, '1', 0, 0,
    /*  !--FIELD NUMERIC on_unix SIZE=4 VALUE=1                              */
    0, 24, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'o', 'n', '_', 'u',
    'n', 'i', 'x', 0, '1', 0, 0,
    /*  !--FIELD NUMERIC on_windows_32 SIZE=4 VALUE=1                        */
    0, 30, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'o', 'n', '_', 'w',
    'i', 'n', 'd', 'o', 'w', 's', '_', '3', '2', 0, '1', 0, 0,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f8 NAME=L_w ... TML directory:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '8', 0, 'M', 'a', 'i', 'n',
    32, 'H', 'T', 'M', 'L', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
    'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f9 NAME=web ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '9', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f10 NAME=L_ ... CGI directory:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '1', '0', 0, 'M', 'a', 'i',
    'n', 32, 'C', 'G', 'I', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
    'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD TEXTUAL f11 NAME=cg ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '1', '1', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f12 NAME=L_ ... Ls start with:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '1', '2', 0, 'C', 'G', 'I',
    32, 'U', 'R', 'L', 's', 32, 's', 't', 'a', 'r', 't', 32, 'w', 'i',
    't', 'h', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD TEXTUAL f13 NAME=cg ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '1', '3', 0, 0, 0,
    /*  !--IF main_config  VALUE=1                                           */
    0, 7, 2, 0, 0, 0, 23, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f14 NAME=L_ ... in debug mode?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '1', '4', 0, 'R', 'u', 'n',
    32, 'i', 'n', 32, 'd', 'e', 'b', 'u', 'g', 32, 'm', 'o', 'd', 'e',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD BOOLEAN f15 NAME=de ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '1', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  - creates additional log files                                       */
    0, 32, 0, 45, 32, 'c', 'r', 'e', 'a', 't', 'e', 's', 32, 'a', 'd',
    'd', 'i', 't', 'i', 'o', 'n', 'a', 'l', 32, 'l', 'o', 'g', 32, 'f',
    'i', 'l', 'e', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f16 NAME=L_ ...  config every:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '1', '6', 0, 'R', 'e', 'f',
    'r', 'e', 's', 'h', 32, 'c', 'o', 'n', 'f', 'i', 'g', 32, 'e', 'v',
    'e', 'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD NUMERIC f17 NAME=re ... ZE=8 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 0, 1, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 'f', '1', '7', 0, 0,
    0,
    /*  seconds                                                              */
    0, 9, 0, 's', 'e', 'c', 'o', 'n', 'd', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f18 NAME=L_ ... P connections:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '1', '8', 0, 'M', 'a', 'x',
    32, 'H', 'T', 'T', 'P', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i',
    'o', 'n', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD NUMERIC f19 NAME=li ... ZE=4 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 0, 1, 0, 4, 0, 4, 0, 0, 0, 0, 1, 0, 'f', '1', '9', 0, 0,
    0,
    /*  if any                                                               */
    0, 8, 0, 'i', 'f', 32, 'a', 'n', 'y', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f20 NAME=L_ ... throttle pipe:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '0', 0, 'H', 'T', 'T',
    'P', 32, 't', 'h', 'r', 'o', 't', 't', 'l', 'e', 32, 'p', 'i', 'p',
    'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD SELECT f21 NAME=pip ... PE=dynamic 0="No selection"         */
    0, 29, 16, 0, 1, 0, 0, 0, 'f', '2', '1', 0, '0', 0, 'n', 'o', 0, 0,
    'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  !--IF on_unix  VALUE=1                                               */
    0, 7, 2, 0, 1, 0, 5, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f22 NAME=L_ ... in background?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '2', 0, 'R', 'u', 'n',
    32, 'i', 'n', 32, 'b', 'a', 'c', 'k', 'g', 'r', 'o', 'u', 'n', 'd',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD BOOLEAN f23 NAME=ba ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '3', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  !--IF on_windows_32  VALUE=1                                         */
    0, 7, 2, 0, 2, 0, 10, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f24 NAME=L_ ... P/IP is ready?&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, 39, 0, 39, 'f', '2', '4', 0, 'S', 't', 'a',
    'r', 't', 32, 'w', 'h', 'e', 'n', 32, 'T', 'C', 'P', '/', 'I', 'P',
    32, 'i', 's', 32, 'r', 'e', 'a', 'd', 'y', '?', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD BOOLEAN f25 NAME=au ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f26 NAME=L_ ...  from crashes?&nbsp;&nbsp;"         */
    0, 56, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '2', '6', 0, 'R', 'e', 'c',
    'o', 'v', 'e', 'r', 32, 's', 'i', 'l', 'e', 'n', 't', 'l', 'y', 32,
    'f', 'r', 'o', 'm', 32, 'c', 'r', 'a', 's', 'h', 'e', 's', '?', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD BOOLEAN f27 NAME=re ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '2', '7', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f28 NAME=L_ ... ult HTML page:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '8', 0, 'D', 'e', 'f',
    'a', 'u', 'l', 't', 32, 'H', 'T', 'M', 'L', 32, 'p', 'a', 'g', 'e',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD TEXTUAL f29 NAME=de ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '2', '9', 0, 0, 0,
    /*  !--FIELD TEXTUAL f30 NAME=L_ ... sp;&nbsp;Then:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '0', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'T', 'h', 'e', 'n',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  !--FIELD TEXTUAL f31 NAME=de ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '3', '1', 0, 0, 0,
    /*  !--FIELD TEXTUAL f32 NAME=de ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '3', '2', 0, 0, 0,
    /*  !--FIELD TEXTUAL f33 NAME=de ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 12, 0, 'P', 'f', '3', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f34 NAME=L_ ... e connections?&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, ')', 0, ')', 'f', '3', '4', 0, 'A', 'l', 'l',
    'o', 'w', 32, 'K', 'e', 'e', 'p', 45, 'A', 'l', 'i', 'v', 'e', 32,
    'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 's', '?', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD BOOLEAN f35 NAME=ke ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '3', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  !--FIELD TEXTUAL f36 NAME=L_ ... p;Allow up to:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '6', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'A', 'l', 'l', 'o',
    'w', 32, 'u', 'p', 32, 't', 'o', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f37 NAME=ke ... ZE=4 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 0, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'f', '3', '7', 0, 0,
    0,
    /*  requests                                                             */
    0, 10, 0, 'r', 'e', 'q', 'u', 'e', 's', 't', 's', 10,
    /*  !--FIELD TEXTUAL f38 NAME=L_ ... p;Close after:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '8', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'C', 'l', 'o', 's',
    'e', 32, 'a', 'f', 't', 'e', 'r', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f39 NAME=ti ... ZE=4 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 0, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'f', '3', '9', 0, 0,
    0,
    /*  seconds                                                              */
    0, 4, 1, 0, 13, 252,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f40 NAME=L_ ... ist sort order&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '4', '0', 0, 'D', 'i', 'r',
    'e', 'c', 't', 'o', 'r', 'y', 32, 'l', 'i', 's', 't', 32, 's', 'o',
    'r', 't', 32, 'o', 'r', 'd', 'e', 'r', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD TEXTUAL f41 NAME=di ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '4', '1', 0, 0, 0,
    /*  n=name x=ext t=time s=size N,X,T,S=inverted                          */
    0, 45, 0, 'n', '=', 'n', 'a', 'm', 'e', 32, 'x', '=', 'e', 'x', 't',
    32, 't', '=', 't', 'i', 'm', 'e', 32, 's', '=', 's', 'i', 'z', 'e',
    32, 'N', ',', 'X', ',', 'T', ',', 'S', '=', 'i', 'n', 'v', 'e', 'r',
    't', 'e', 'd', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 11, 199,
    /*  !--FIELD TEXTUAL f42 NAME=L_ ... mplate script:&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '+', 0, '+', 'f', '4', '2', 0, 'D', 'i', 'r',
    'e', 'c', 't', 'o', 'r', 'y', 32, 'l', 'i', 's', 't', 32, 't', 'e',
    'm', 'p', 'l', 'a', 't', 'e', 32, 's', 'c', 'r', 'i', 'p', 't', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 12, 45,
    /*  !--FIELD TEXTUAL f43 NAME=di ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '4', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 12, '{',
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
    0, 4, 1, 0, 18, 129,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm03_fields [] = {
    { 0, 2903, 4 },                     /*  main_config                     */
    { 6, 2933, 4 },                     /*  on_unix                         */
    { 12, 2959, 4 },                    /*  on_windows_32                   */
    { 18, 3070, 32 },                   /*  l_webpages                      */
    { 52, 3180, 100 },                  /*  webpages                        */
    { 154, 3215, 31 },                  /*  l_cgi_bin                       */
    { 187, 3268, 100 },                 /*  cgi_bin                         */
    { 289, 3296, 32 },                  /*  l_cgi_url                       */
    { 323, 3350, 40 },                  /*  cgi_url                         */
    { 365, 3387, 30 },                  /*  l_debug                         */
    { 397, 3439, 1 },                   /*  debug                           */
    { 400, 3504, 33 },                  /*  l_refresh_rate                  */
    { 435, 3559, 8 },                   /*  refresh_rate                    */
    { 445, 3603, 33 },                  /*  l_limit                         */
    { 480, 3658, 4 },                   /*  limit                           */
    { 486, 3701, 31 },                  /*  l_pipe                          */
    { 519, 3754, 3 },                   /*  pipe                            */
    { 524, 3806, 30 },                  /*  l_background                    */
    { 556, 3858, 1 },                   /*  background                      */
    { 559, 3898, 39 },                  /*  l_autostart                     */
    { 600, 3959, 1 },                   /*  autostart                       */
    { 603, 3990, 42 },                  /*  l_recover                       */
    { 647, 4054, 1 },                   /*  recover                         */
    { 650, 4085, 30 },                  /*  l_default1                      */
    { 682, 4137, 80 },                  /*  default1                        */
    { 764, 4153, 29 },                  /*  l_default2                      */
    { 795, 4198, 80 },                  /*  default2                        */
    { 877, 4214, 80 },                  /*  default3                        */
    { 959, 4230, 80 },                  /*  default4                        */
    { 1041, 4258, 41 },                 /*  l_keep_alive                    */
    { 1084, 4321, 1 },                  /*  keep_alive                      */
    { 1087, 4340, 36 },                 /*  l_keep_alive_max                */
    { 1125, 4392, 4 },                  /*  keep_alive_max                  */
    { 1131, 4425, 36 },                 /*  l_timeout                       */
    { 1169, 4477, 4 },                  /*  timeout                         */
    { 1175, 4516, 37 },                 /*  l_dirsort                       */
    { 1214, 4575, 5 },                  /*  dirsort                         */
    { 1221, 4650, 43 },                 /*  l_dir_script                    */
    { 1266, 4715, 80 },                 /*  dir_script                      */
    { 1348, 4749, 120 },                /*  message_to_user                 */
    { 1470, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   main_config_a        ;
    char   main_config          [4 + 1];
    byte   on_unix_a            ;
    char   on_unix              [4 + 1];
    byte   on_windows_32_a      ;
    char   on_windows_32        [4 + 1];
    byte   l_webpages_a         ;
    char   l_webpages           [32 + 1];
    byte   webpages_a           ;
    char   webpages             [100 + 1];
    byte   l_cgi_bin_a          ;
    char   l_cgi_bin            [31 + 1];
    byte   cgi_bin_a            ;
    char   cgi_bin              [100 + 1];
    byte   l_cgi_url_a          ;
    char   l_cgi_url            [32 + 1];
    byte   cgi_url_a            ;
    char   cgi_url              [40 + 1];
    byte   l_debug_a            ;
    char   l_debug              [30 + 1];
    byte   debug_a              ;
    char   debug                [1 + 1];
    byte   l_refresh_rate_a     ;
    char   l_refresh_rate       [33 + 1];
    byte   refresh_rate_a       ;
    char   refresh_rate         [8 + 1];
    byte   l_limit_a            ;
    char   l_limit              [33 + 1];
    byte   limit_a              ;
    char   limit                [4 + 1];
    byte   l_pipe_a             ;
    char   l_pipe               [31 + 1];
    byte   pipe_a               ;
    char   pipe                 [3 + 1];
    byte   l_background_a       ;
    char   l_background         [30 + 1];
    byte   background_a         ;
    char   background           [1 + 1];
    byte   l_autostart_a        ;
    char   l_autostart          [39 + 1];
    byte   autostart_a          ;
    char   autostart            [1 + 1];
    byte   l_recover_a          ;
    char   l_recover            [42 + 1];
    byte   recover_a            ;
    char   recover              [1 + 1];
    byte   l_default1_a         ;
    char   l_default1           [30 + 1];
    byte   default1_a           ;
    char   default1             [80 + 1];
    byte   l_default2_a         ;
    char   l_default2           [29 + 1];
    byte   default2_a           ;
    char   default2             [80 + 1];
    byte   default3_a           ;
    char   default3             [80 + 1];
    byte   default4_a           ;
    char   default4             [80 + 1];
    byte   l_keep_alive_a       ;
    char   l_keep_alive         [41 + 1];
    byte   keep_alive_a         ;
    char   keep_alive           [1 + 1];
    byte   l_keep_alive_max_a   ;
    char   l_keep_alive_max     [36 + 1];
    byte   keep_alive_max_a     ;
    char   keep_alive_max       [4 + 1];
    byte   l_timeout_a          ;
    char   l_timeout            [36 + 1];
    byte   timeout_a            ;
    char   timeout              [4 + 1];
    byte   l_dirsort_a          ;
    char   l_dirsort            [37 + 1];
    byte   dirsort_a            ;
    char   dirsort              [5 + 1];
    byte   l_dir_script_a       ;
    char   l_dir_script         [43 + 1];
    byte   dir_script_a         ;
    char   dir_script           [80 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back5_a;
    byte   save_a;
    byte   default_a;
    byte   undo_a;
    byte   console6_a;
    byte   halt7_a;
    byte   restart8_a;
    byte   exit9_a;
    byte   aliases_a;
    byte   errors_a;
    byte   ssi_a;
    byte   mimes_a;
    byte   wsx_a;
    byte   filters_a;
    byte   ddns_a;
    byte   advanced_a;
    byte   vhosts_a;
    byte   cgi_a;
    byte   security_a;
    byte   logging_a;
    byte   ftp_a;
    } XIADM03_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm03 = {
    xiadm03_blocks,
    xiadm03_fields,
    158,                                /*  Number of blocks in form        */
    40,                                 /*  Number of fields in form        */
    21,                                 /*  Number of actions in form       */
    1470,                               /*  Size of fields                  */
    "xiadm03",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

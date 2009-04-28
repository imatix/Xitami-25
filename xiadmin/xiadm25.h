/*---------------------------------------------------------------------------
 *  xiadm25.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM25__
#define __FORM_XIADM25__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM25_L_HOST_FILE                 0
#define XIADM25_HOST_FILE                   1
#define XIADM25_L_OVERWRITE                 2
#define XIADM25_OVERWRITE                   3
#define XIADM25_L_HOST_ADDR                 4
#define XIADM25_HOST_ADDR                   5
#define XIADM25_L_HOST_NAME                 6
#define XIADM25_HOST_NAME                   7
#define XIADM25_L_WEBPAGES                  8
#define XIADM25_WEBPAGES                    9
#define XIADM25_L_CGI_BIN                   10
#define XIADM25_CGI_BIN                     11
#define XIADM25_L_FTPROOT                   12
#define XIADM25_FTPROOT                     13
#define XIADM25_L_MAKEDIRS                  14
#define XIADM25_MAKEDIRS                    15
#define XIADM25_L_SUPERUSER                 16
#define XIADM25_SUPERUSER                   17
#define XIADM25_L_SHARELOGS                 18
#define XIADM25_SHARELOGS                   19
#define XIADM25_L_USE_ADMIN                 20
#define XIADM25_USE_ADMIN                   21
#define XIADM25_L_ADMIN_USER                22
#define XIADM25_ADMIN_USER                  23
#define XIADM25_L_ADMIN_PASS                24
#define XIADM25_ADMIN_PASS                  25
#define XIADM25_L_USE_VHWBA                 26
#define XIADM25_USE_VHWBA                   27
#define XIADM25_L_VHWBA_USER                28
#define XIADM25_VHWBA_USER                  29
#define XIADM25_L_VHWBA_PASS                30
#define XIADM25_VHWBA_PASS                  31
#define XIADM25_MESSAGE_TO_USER             32

/*  This table contains each block in the form                               */

static byte xiadm25_blocks [] = {
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
    /*  !--ACTION back197  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '1',
    '9', '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 72, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'c', 'o', 'n',
    's', 'o', 'l', 'e', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=', '"',
    'H', 'e', 'l', 'p', '"', 32, 'T', 'I', 'T', 'L', 'E', '=', '"', 'H',
    'e', 'l', 'p', '"', 10,
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
    /*  <TD ALIGN=CENTER><FONT SIZE=+1>Virtual Host Wizard </FONT>           */
    0, 60, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', 'V', 'i', 'r', 't', 'u', 'a', 'l', 32, 'H',
    'o', 's', 't', 32, 'W', 'i', 'z', 'a', 'r', 'd', 32, '<', '/', 'F',
    'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console198  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 1, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '1', '9', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt199  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 2, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '1',
    '9', '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart200  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 3, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '2', '0', '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit201  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 4, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '2',
    '0', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'e',
    'x', 'i', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <IMG SRC="/admin/$right.gif" BORDER=0 ALIGN=MIDDLE>                  */
    0, 53, 0, '<', 'I', 'M', 'G', 32, 'S', 'R', 'C', '=', '"', '/', 'a',
    'd', 'm', 'i', 'n', '/', '$', 'r', 'i', 'g', 'h', 't', '.', 'g',
    'i', 'f', '"', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '0', 32, 'A',
    'L', 'I', 'G', 'N', '=', 'M', 'I', 'D', 'D', 'L', 'E', '>', 10,
    /*  </TABLE><p>                                                          */
    0, 13, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', '<', 'p', '>', 10,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  <H2><A NAME="TOC2">Virtual Host Wizard</A></H2>                      */
    0, 49, 0, '<', 'H', '2', '>', '<', 'A', 32, 'N', 'A', 'M', 'E', '=',
    '"', 'T', 'O', 'C', '2', '"', '>', 'V', 'i', 'r', 't', 'u', 'a',
    'l', 32, 'H', 'o', 's', 't', 32, 'W', 'i', 'z', 'a', 'r', 'd', '<',
    '/', 'A', '>', '<', '/', 'H', '2', '>', 10,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f328 NAME=L ...  host profile:&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '3', '2', '8', 0, 'C', 'r',
    'e', 'a', 't', 'e', 32, 'v', 'i', 'r', 't', 'u', 'a', 'l', 32, 'h',
    'o', 's', 't', 32, 'p', 'r', 'o', 'f', 'i', 'l', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f329 NAME=h ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '3', '2', '9', 0, 0, 0,
    /*  .cfg extension is assumed                                            */
    0, 27, 0, '.', 'c', 'f', 'g', 32, 'e', 'x', 't', 'e', 'n', 's', 'i',
    'o', 'n', 32, 'i', 's', 32, 'a', 's', 's', 'u', 'm', 'e', 'd', 10,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f330 NAME=L ... rite existing?&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '3', '0', 0, 'O', 'v',
    'e', 'r', 'w', 'r', 'i', 't', 'e', 32, 'e', 'x', 'i', 's', 't', 'i',
    'n', 'g', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD BOOLEAN f331 NAME=o ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '3', '3', '1', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 56, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '9', '9', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L',
    'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P',
    32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'b', 'o', 'd', 'y', '>',
    10,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 8, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f332 NAME=L ... ct IP address:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '3', '2', 0, 'S', 'e',
    'l', 'e', 'c', 't', 32, 'I', 'P', 32, 'a', 'd', 'd', 'r', 'e', 's',
    's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD SELECT f333 NAME=ho ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '3', '3', '3', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f334 NAME=L ... DNS host name:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '3', '4', 0, 'O', 'r',
    ',', 32, 'e', 'n', 't', 'e', 'r', 32, 'D', 'N', 'S', 32, 'h', 'o',
    's', 't', 32, 'n', 'a', 'm', 'e', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f335 NAME=h ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '3', '3', '5', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 4, 1, 0, 10, 8,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 8, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f336 NAME=L ... oot directory:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '3', '3', '6', 0, 'W', 'e',
    'b', 32, 'p', 'a', 'g', 'e', 32, 'r', 'o', 'o', 't', 32, 'd', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f337 NAME=w ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '3', '3', '7', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f338 NAME=L ... bin directory:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '3', '3', '8', 0, 'C', 'G',
    'I', 45, 'b', 'i', 'n', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r',
    'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f339 NAME=c ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '3', '3', '9', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f340 NAME=L ... oot directory:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '4', '0', 0, 'F', 'T',
    'P', 32, 'r', 'o', 'o', 't', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o',
    'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f341 NAME=f ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '3', '4', '1', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f342 NAME=L ...  if necessary?&nbsp;&nbsp;"         */
    0, 59, 10, 6, 1, 0, 0, ',', 0, ',', 'f', '3', '4', '2', 0, 'C', 'r',
    'e', 'a', 't', 'e', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'i',
    'e', 's', 32, 'i', 'f', 32, 'n', 'e', 'c', 'e', 's', 's', 'a', 'r',
    'y', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD BOOLEAN f343 NAME=m ...  FALSE=no ATTR="" VALUE=yes         */
    0, 18, 15, 0, 1, 'f', '3', '4', '3', 0, '1', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f344 NAME=L ... user password:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '3', '4', '4', 0, 'S', 'u',
    'p', 'e', 'r', 'u', 's', 'e', 'r', 32, 'p', 'a', 's', 's', 'w', 'o',
    'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f345 NAME=s ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '3', '4', '5', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f346 NAME=L ... ared logfiles?&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '3', '4', '6', 0, 'U', 's',
    'e', 's', 32, 's', 'h', 'a', 'r', 'e', 'd', 32, 'l', 'o', 'g', 'f',
    'i', 'l', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD BOOLEAN f347 NAME=s ... s FALSE=no ATTR="" VALUE=no         */
    0, 18, 15, 0, 1, 'f', '3', '4', '7', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f348 NAME=L ...  use full WBA?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '4', '8', 0, 'C', 'a',
    'n', 32, 'u', 's', 'e', 32, 'f', 'u', 'l', 'l', 32, 'W', 'B', 'A',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD BOOLEAN f349 NAME=u ... s FALSE=no ATTR="" VALUE=no         */
    0, 18, 15, 0, 1, 'f', '3', '4', '9', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f350 NAME=L ... f so, user id:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', '5', '0', 0, 'I', 'f',
    32, 's', 'o', ',', 32, 'u', 's', 'e', 'r', 32, 'i', 'd', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f351 NAME=a ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '3', '5', '1', 0, 0, 0,
    /*  !--FIELD TEXTUAL f352 NAME=L ... nbsp;password:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '3', '5', '2', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'p', 'a', 's',
    's', 'w', 'o', 'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f353 NAME=a ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '3', '5', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f354 NAME=L ... WBA (limited)?&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '3', '5', '4', 0, 'C', 'a',
    'n', 32, 'u', 's', 'e', 32, 'V', 'H', 32, 'W', 'B', 'A', 32, '(',
    'l', 'i', 'm', 'i', 't', 'e', 'd', ')', '?', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD BOOLEAN f355 NAME=u ...  FALSE=no ATTR="" VALUE=yes         */
    0, 18, 15, 0, 1, 'f', '3', '5', '5', 0, '1', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 8, 199,
    /*  !--FIELD TEXTUAL f356 NAME=L ... f so, user id:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', '5', '6', 0, 'I', 'f',
    32, 's', 'o', ',', 32, 'u', 's', 'e', 'r', 32, 'i', 'd', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, '7',
    /*  !--FIELD TEXTUAL f357 NAME=v ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '3', '5', '7', 0, 0, 0,
    /*  !--FIELD TEXTUAL f358 NAME=L ... nbsp;password:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '3', '5', '8', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'p', 'a', 's',
    's', 'w', 'o', 'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f359 NAME=v ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '3', '5', '9', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 4, 1, 0, 10, 8,
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
    /*  <TR><TD></TD><TD VALIGN=TOP  ... WIDTH=""80%"" CLASS=tdvalue>        */
    0, 69, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T',
    'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E', 'F', 'T', 32,
    'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8', '0', '%', '"', '"', 32,
    'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v', 'a', 'l', 'u', 'e',
    '>', 10,
    /*  !--ACTION create  LABEL="Cre ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) define_event / 256), (byte) ((word)
    define_event & 255), 0, 5, 0, 0, 0, 0, 0, 'c', 'r', 'e', 'a', 't',
    'e', 0, 'C', 'r', 'e', 'a', 't', 'e', 0, 0, 0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 6, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 9, 164,
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
    0, 4, 1, 0, 8, 't',
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
    0, 4, 1, 0, 15, 152,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm25_fields [] = {
    { 0, 2302, 40 },                    /*  l_host_file                     */
    { 42, 2422, 80 },                   /*  host_file                       */
    { 124, 2488, 31 },                  /*  l_overwrite                     */
    { 157, 2542, 1 },                   /*  overwrite                       */
    { 160, 2644, 30 },                  /*  l_host_addr                     */
    { 192, 2697, 3 },                   /*  host_addr                       */
    { 197, 2741, 36 },                  /*  l_host_name                     */
    { 235, 2800, 50 },                  /*  host_name                       */
    { 287, 2847, 36 },                  /*  l_webpages                      */
    { 325, 2906, 50 },                  /*  webpages                        */
    { 377, 2935, 30 },                  /*  l_cgi_bin                       */
    { 409, 2988, 50 },                  /*  cgi_bin                         */
    { 461, 3017, 31 },                  /*  l_ftproot                       */
    { 494, 3071, 50 },                  /*  ftproot                         */
    { 546, 3100, 44 },                  /*  l_makedirs                      */
    { 592, 3167, 1 },                   /*  makedirs                        */
    { 595, 3199, 31 },                  /*  l_superuser                     */
    { 628, 3253, 20 },                  /*  superuser                       */
    { 650, 3282, 33 },                  /*  l_sharelogs                     */
    { 685, 3338, 1 },                   /*  sharelogs                       */
    { 688, 3370, 29 },                  /*  l_use_admin                     */
    { 719, 3422, 1 },                   /*  use_admin                       */
    { 722, 3454, 27 },                  /*  l_admin_user                    */
    { 751, 3504, 20 },                  /*  admin_user                      */
    { 773, 3521, 33 },                  /*  l_admin_pass                    */
    { 808, 3571, 20 },                  /*  admin_pass                      */
    { 830, 3600, 37 },                  /*  l_use_vhwba                     */
    { 869, 3660, 1 },                   /*  use_vhwba                       */
    { 872, 3692, 27 },                  /*  l_vhwba_user                    */
    { 901, 3742, 20 },                  /*  vhwba_user                      */
    { 923, 3759, 33 },                  /*  l_vhwba_pass                    */
    { 958, 3809, 20 },                  /*  vhwba_pass                      */
    { 980, 4004, 120 },                 /*  message_to_user                 */
    { 1102, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_host_file_a        ;
    char   l_host_file          [40 + 1];
    byte   host_file_a          ;
    char   host_file            [80 + 1];
    byte   l_overwrite_a        ;
    char   l_overwrite          [31 + 1];
    byte   overwrite_a          ;
    char   overwrite            [1 + 1];
    byte   l_host_addr_a        ;
    char   l_host_addr          [30 + 1];
    byte   host_addr_a          ;
    char   host_addr            [3 + 1];
    byte   l_host_name_a        ;
    char   l_host_name          [36 + 1];
    byte   host_name_a          ;
    char   host_name            [50 + 1];
    byte   l_webpages_a         ;
    char   l_webpages           [36 + 1];
    byte   webpages_a           ;
    char   webpages             [50 + 1];
    byte   l_cgi_bin_a          ;
    char   l_cgi_bin            [30 + 1];
    byte   cgi_bin_a            ;
    char   cgi_bin              [50 + 1];
    byte   l_ftproot_a          ;
    char   l_ftproot            [31 + 1];
    byte   ftproot_a            ;
    char   ftproot              [50 + 1];
    byte   l_makedirs_a         ;
    char   l_makedirs           [44 + 1];
    byte   makedirs_a           ;
    char   makedirs             [1 + 1];
    byte   l_superuser_a        ;
    char   l_superuser          [31 + 1];
    byte   superuser_a          ;
    char   superuser            [20 + 1];
    byte   l_sharelogs_a        ;
    char   l_sharelogs          [33 + 1];
    byte   sharelogs_a          ;
    char   sharelogs            [1 + 1];
    byte   l_use_admin_a        ;
    char   l_use_admin          [29 + 1];
    byte   use_admin_a          ;
    char   use_admin            [1 + 1];
    byte   l_admin_user_a       ;
    char   l_admin_user         [27 + 1];
    byte   admin_user_a         ;
    char   admin_user           [20 + 1];
    byte   l_admin_pass_a       ;
    char   l_admin_pass         [33 + 1];
    byte   admin_pass_a         ;
    char   admin_pass           [20 + 1];
    byte   l_use_vhwba_a        ;
    char   l_use_vhwba          [37 + 1];
    byte   use_vhwba_a          ;
    char   use_vhwba            [1 + 1];
    byte   l_vhwba_user_a       ;
    char   l_vhwba_user         [27 + 1];
    byte   vhwba_user_a         ;
    char   vhwba_user           [20 + 1];
    byte   l_vhwba_pass_a       ;
    char   l_vhwba_pass         [33 + 1];
    byte   vhwba_pass_a         ;
    char   vhwba_pass           [20 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back197_a;
    byte   console198_a;
    byte   halt199_a;
    byte   restart200_a;
    byte   exit201_a;
    byte   create_a;
    byte   cancel_a;
    } XIADM25_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm25 = {
    xiadm25_blocks,
    xiadm25_fields,
    137,                                /*  Number of blocks in form        */
    33,                                 /*  Number of fields in form        */
    7,                                  /*  Number of actions in form       */
    1102,                               /*  Size of fields                  */
    "xiadm25",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

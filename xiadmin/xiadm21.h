/*---------------------------------------------------------------------------
 *  xiadm21.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM21__
#define __FORM_XIADM21__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM21_LOCKED                      0
#define XIADM21_L_DATE_STARTED              1
#define XIADM21_DATE_STARTED                2
#define XIADM21_L_TIME_STARTED              3
#define XIADM21_TIME_STARTED                4
#define XIADM21_L_SERVER_MESSAGE            5
#define XIADM21_SERVER_MESSAGE              6
#define XIADM21_L_HTTP_PORT                 7
#define XIADM21_HTTP_PORT                   8
#define XIADM21_L_FTP_PORT                  9
#define XIADM21_FTP_PORT                    10
#define XIADM21_L_CUR_CONNECTS              11
#define XIADM21_CUR_CONNECTS                12
#define XIADM21_L_MAX_CONNECTS              13
#define XIADM21_MAX_CONNECTS                14
#define XIADM21_L_CONNECT_COUNT             15
#define XIADM21_CONNECT_COUNT               16
#define XIADM21_L_ERROR_COUNT               17
#define XIADM21_ERROR_COUNT                 18
#define XIADM21_L_TRANSFER_SIZE             19
#define XIADM21_TRANSFER_SIZE               20
#define XIADM21_TRANSFER_UNIT               21
#define XIADM21_L_LOG_FILES                 22
#define XIADM21_LOG_FILES                   23
#define XIADM21_LOG_LINES                   24
#define XIADM21_LOG_KBYTES                  25
#define XIADM21_MESSAGE_TO_USER             26

/*  This table contains each block in the form                               */

static byte xiadm21_blocks [] = {
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
    /*  !--ACTION back168  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '1',
    '6', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION clear169  LABEL="/ ... ROLLOVER="/admin/cleara.gif"        */
    0, 60, 20, 2, 1, (byte) ((word) clear_event / 256), (byte) ((word)
    clear_event & 255), 0, 1, 0, 0, 39, 0, '(', 'c', 'l', 'e', 'a', 'r',
    '1', '6', '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'c', 'l',
    'e', 'a', 'r', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n',
    '/', 'c', 'l', 'e', 'a', 'r', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION refresh170  LABEL= ... LLOVER="/admin/refresha.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) refresh_event / 256), (byte) ((word)
    refresh_event & 255), 0, 2, 0, 0, 39, 0, '(', 'r', 'e', 'f', 'r',
    'e', 's', 'h', '1', '7', '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 'f', 'r', 'e', 's', 'h', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 'f', 'r', 'e', 's', 'h',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 71, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'f', 'i', 'l',
    't', 'e', 'r', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=', '"', 'H',
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
    /*  <TD ALIGN=CENTER><FONT SIZE=+1>Server Console Panel </FONT>          */
    0, 61, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', 'S', 'e', 'r', 'v', 'e', 'r', 32, 'C', 'o',
    'n', 's', 'o', 'l', 'e', 32, 'P', 'a', 'n', 'e', 'l', 32, '<', '/',
    'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console171  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 3, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '1', '7', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt172  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 4, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '1',
    '7', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart173  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 5, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '1', '7', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit174  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 6, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '1',
    '7', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
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
    /*  !--ACTION close  LABEL="Clos ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 28, 20, 1, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 7, 0, 0, 0, 0, 0, 'c', 'l', 'o', 's', 'e', 0,
    'C', 'l', 'o', 's', 'e', 0, 0, 0, 0, 0,
    /*  </FONT><HR>                                                          */
    0, 13, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC locked SIZE=4 VALUE=1                               */
    0, 23, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'l', 'o', 'c', 'k',
    'e', 'd', 0, '1', 0, 0,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f283 NAME=L ... er started at:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '8', '3', 0, 'S', 'e',
    'r', 'v', 'e', 'r', 32, 's', 't', 'a', 'r', 't', 'e', 'd', 32, 'a',
    't', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD DATE f284 NAME=date ... TH=? DAY=? ATTR="" VALUE=""         */
    0, 18, 12, 0, 1, 0, 15, 0, 1, 0, 0, 0, 'f', '2', '8', '4', 0, 0, 0,
    0,
    /*  !--FIELD TEXTUAL f285 NAME=L_time-started VALUE=":"                  */
    0, 16, 10, 6, 1, 0, 0, 1, 0, 1, 'f', '2', '8', '5', 0, ':', 0, 0,
    /*  !--FIELD TIME f286 NAME=time ... E=8 MAX=20 ATTR="" VALUE=""         */
    0, 21, 13, 0, 1, 0, 8, 'f', '2', '8', '6', 0, 0, 'h', 'h', ':', 'm',
    'm', ':', 's', 's', 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f287 NAME=L ... error message:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '2', '8', '7', 0, 'L', 'a',
    's', 't', 32, 's', 'e', 'r', 'v', 'e', 'r', 32, 'e', 'r', 'r', 'o',
    'r', 32, 'm', 'e', 's', 's', 'a', 'g', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f288 NAME=s ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 'P', 0, 'P', 'f', '2', '8', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f289 NAME=L ... ce is on port:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '8', '9', 0, 'H', 'T',
    'T', 'P', 32, 's', 'e', 'r', 'v', 'i', 'c', 'e', 32, 'i', 's', 32,
    'o', 'n', 32, 'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f290 NAME=h ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '2', '9', '0',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f291 NAME=L ... ce is on port:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '2', '9', '1', 0, 'F', 'T',
    'P', 32, 's', 'e', 'r', 'v', 'i', 'c', 'e', 32, 'i', 's', 32, 'o',
    'n', 32, 'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f292 NAME=f ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '2', '9', '2',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f293 NAME=L ... n connections:&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, 39, 0, 39, 'f', '2', '9', '3', 0, 'N', 'u',
    'm', 'b', 'e', 'r', 32, 'o', 'f', 32, 'o', 'p', 'e', 'n', 32, 'c',
    'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f294 NAME=c ... ZE=6 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '2', '9', '4',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f295 NAME=L ... n connections:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '2', '9', '5', 0, 'H', 'i',
    'g', 'h', 'e', 's', 't', 32, 'o', 'p', 'e', 'n', 32, 'c', 'o', 'n',
    'n', 'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f296 NAME=m ... ZE=6 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '2', '9', '6',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f297 NAME=L ... umber of hits:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '2', '9', '7', 0, 'T', 'o',
    't', 'a', 'l', 32, 'n', 'u', 'm', 'b', 'e', 'r', 32, 'o', 'f', 32,
    'h', 'i', 't', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f298 NAME=c ... E=10 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 'f', '2', '9', '8',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f299 NAME=L ... ber of errors:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '2', '9', '9', 0, 'T', 'o',
    't', 'a', 'l', 32, 'n', 'u', 'm', 'b', 'e', 'r', 32, 'o', 'f', 32,
    'e', 'r', 'r', 'o', 'r', 's', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f300 NAME=e ... E=10 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 'f', '3', '0', '0',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f301 NAME=L ... ta transferred&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '3', '0', '1', 0, 'T', 'o',
    't', 'a', 'l', 32, 'd', 'a', 't', 'a', 32, 't', 'r', 'a', 'n', 's',
    'f', 'e', 'r', 'r', 'e', 'd', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f302 NAME=t ... E=10 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 10, 0, 10, 0, 0, 0, 0, 0, 0, 'f', '3', '0', '2',
    0, 0, 0,
    /*  !--FIELD TEXTUAL f303 NAME=t ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '3', '0', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 'f',
    /*  !--FIELD TEXTUAL f304 NAME=L ... ive log files:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '3', '0', '4', 0, 'A', 'c',
    't', 'i', 'v', 'e', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', 's',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD NUMERIC f305 NAME=l ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '3', '0', '5',
    0, 0, 0,
    /*  files                                                                */
    0, 7, 0, 'f', 'i', 'l', 'e', 's', 10,
    /*  !--FIELD NUMERIC f306 NAME=l ... ZE=8 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 'f', '3', '0', '6',
    0, 0, 0,
    /*  lines                                                                */
    0, 7, 0, 'l', 'i', 'n', 'e', 's', 10,
    /*  !--FIELD NUMERIC f307 NAME=l ... ZE=8 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 'f', '3', '0', '7',
    0, 0, 0,
    /*  Kb                                                                   */
    0, 4, 0, 'K', 'b', 10,
    /*  !--ACTION cycle_data  LABEL= ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 33, 20, 1, 1, (byte) ((word) cycle_logs_event / 256), (byte)
    ((word) cycle_logs_event & 255), 0, 8, 0, 0, 0, 0, 0, 'c', 'y', 'c',
    'l', 'e', '_', 'd', 'a', 't', 'a', 0, 'C', 'y', 'c', 'l', 'e', 0, 0,
    0, 0, 0,
    /*  !--ACTION clear_data  LABEL= ...  files?" ATTR="" TYPE=PLAIN         */
    0, 56, 20, 1, 1, (byte) ((word) clear_logs_event / 256), (byte)
    ((word) clear_logs_event & 255), 0, 9, 0, 0, 0, 0, 0, 'c', 'l', 'e',
    'a', 'r', '_', 'd', 'a', 't', 'a', 0, 'E', 'm', 'p', 't', 'y', 0, 0,
    'R', 'e', 'a', 'l', 'l', 'y', 32, 'c', 'l', 'e', 'a', 'r', 32, 'l',
    'o', 'g', 32, 'f', 'i', 'l', 'e', 's', '?', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 'H',
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  !--ACTION messages  LABEL="M ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 37, 20, 0, 1, (byte) ((word) messages_event / 256), (byte)
    ((word) messages_event & 255), 0, 10, 0, 0, 0, 0, 0, 'm', 'e', 's',
    's', 'a', 'g', 'e', 's', 0, 'M', 'e', 's', 's', 'a', 'g', 'e', 's',
    '.', '.', '.', 0, 0, 0, 0, 0,
    /*  !--ACTION details  LABEL="De ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 35, 20, 0, 1, (byte) ((word) details_event / 256), (byte) ((word)
    details_event & 255), 0, 11, 0, 0, 0, 0, 0, 'd', 'e', 't', 'a', 'i',
    'l', 's', 0, 'D', 'e', 't', 'a', 'i', 'l', 's', '.', '.', '.', 0, 0,
    0, 0, 0,
    /*  !--ACTION preferences  LABEL ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 43, 20, 0, 1, (byte) ((word) define_event / 256), (byte) ((word)
    define_event & 255), 0, 12, 0, 0, 0, 0, 0, 'p', 'r', 'e', 'f', 'e',
    'r', 'e', 'n', 'c', 'e', 's', 0, 'P', 'r', 'e', 'f', 'e', 'r', 'e',
    'n', 'c', 'e', 's', '.', '.', '.', 0, 0, 0, 0, 0,
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
    0, 4, 1, 0, 14, '@',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm21_fields [] = {
    { 0, 2357, 4 },                     /*  locked                          */
    { 6, 2461, 30 },                    /*  l_date_started                  */
    { 38, 2571, 8 },                    /*  date_started                    */
    { 48, 2591, 1 },                    /*  l_time_started                  */
    { 51, 2609, 8 },                    /*  time_started                    */
    { 61, 2652, 38 },                   /*  l_server_message                */
    { 101, 2713, 80 },                  /*  server_message                  */
    { 183, 2742, 36 },                  /*  l_http_port                     */
    { 221, 2801, 5 },                   /*  http_port                       */
    { 228, 2835, 35 },                  /*  l_ftp_port                      */
    { 265, 2893, 5 },                   /*  ftp_port                        */
    { 272, 2927, 39 },                  /*  l_cur_connects                  */
    { 313, 2989, 6 },                   /*  cur_connects                    */
    { 321, 3023, 37 },                  /*  l_max_connects                  */
    { 360, 3083, 6 },                   /*  max_connects                    */
    { 368, 3117, 33 },                  /*  l_connect_count                 */
    { 403, 3173, 10 },                  /*  connect_count                   */
    { 415, 3207, 35 },                  /*  l_error_count                   */
    { 452, 3265, 10 },                  /*  error_count                     */
    { 464, 3299, 34 },                  /*  l_transfer_size                 */
    { 500, 3356, 10 },                  /*  transfer_size                   */
    { 512, 3378, 5 },                   /*  transfer_unit                   */
    { 519, 3407, 29 },                  /*  l_log_files                     */
    { 550, 3459, 5 },                   /*  log_files                       */
    { 557, 3490, 8 },                   /*  log_lines                       */
    { 567, 3521, 8 },                   /*  log_kbytes                      */
    { 577, 3788, 120 },                 /*  message_to_user                 */
    { 699, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   locked_a             ;
    char   locked               [4 + 1];
    byte   l_date_started_a     ;
    char   l_date_started       [30 + 1];
    byte   date_started_a       ;
    char   date_started         [8 + 1];
    byte   l_time_started_a     ;
    char   l_time_started       [1 + 1];
    byte   time_started_a       ;
    char   time_started         [8 + 1];
    byte   l_server_message_a   ;
    char   l_server_message     [38 + 1];
    byte   server_message_a     ;
    char   server_message       [80 + 1];
    byte   l_http_port_a        ;
    char   l_http_port          [36 + 1];
    byte   http_port_a          ;
    char   http_port            [5 + 1];
    byte   l_ftp_port_a         ;
    char   l_ftp_port           [35 + 1];
    byte   ftp_port_a           ;
    char   ftp_port             [5 + 1];
    byte   l_cur_connects_a     ;
    char   l_cur_connects       [39 + 1];
    byte   cur_connects_a       ;
    char   cur_connects         [6 + 1];
    byte   l_max_connects_a     ;
    char   l_max_connects       [37 + 1];
    byte   max_connects_a       ;
    char   max_connects         [6 + 1];
    byte   l_connect_count_a    ;
    char   l_connect_count      [33 + 1];
    byte   connect_count_a      ;
    char   connect_count        [10 + 1];
    byte   l_error_count_a      ;
    char   l_error_count        [35 + 1];
    byte   error_count_a        ;
    char   error_count          [10 + 1];
    byte   l_transfer_size_a    ;
    char   l_transfer_size      [34 + 1];
    byte   transfer_size_a      ;
    char   transfer_size        [10 + 1];
    byte   transfer_unit_a      ;
    char   transfer_unit        [5 + 1];
    byte   l_log_files_a        ;
    char   l_log_files          [29 + 1];
    byte   log_files_a          ;
    char   log_files            [5 + 1];
    byte   log_lines_a          ;
    char   log_lines            [8 + 1];
    byte   log_kbytes_a         ;
    char   log_kbytes           [8 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back168_a;
    byte   clear169_a;
    byte   refresh170_a;
    byte   console171_a;
    byte   halt172_a;
    byte   restart173_a;
    byte   exit174_a;
    byte   close_a;
    byte   cycle_data_a;
    byte   clear_data_a;
    byte   messages_a;
    byte   details_a;
    byte   preferences_a;
    } XIADM21_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm21 = {
    xiadm21_blocks,
    xiadm21_fields,
    117,                                /*  Number of blocks in form        */
    27,                                 /*  Number of fields in form        */
    13,                                 /*  Number of actions in form       */
    699,                                /*  Size of fields                  */
    "xiadm21",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

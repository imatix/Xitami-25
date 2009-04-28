/*---------------------------------------------------------------------------
 *  xiadm16.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM16__
#define __FORM_XIADM16__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM16_MAIN_CONFIG                 0
#define XIADM16_L_ENABLED                   1
#define XIADM16_ENABLED                     2
#define XIADM16_L_ROOTDIR                   3
#define XIADM16_ROOTDIR                     4
#define XIADM16_L_TIMEOUT                   5
#define XIADM16_TIMEOUT                     6
#define XIADM16_L_USER_FILE                 7
#define XIADM16_USER_FILE                   8
#define XIADM16_L_DIRECTORY_FILE            9
#define XIADM16_DIRECTORY_FILE              10
#define XIADM16_L_DIRSORT                   11
#define XIADM16_DIRSORT                     12
#define XIADM16_L_EMAIL_CHECK               13
#define XIADM16_EMAIL_CHECK                 14
#define XIADM16_L_HTTP_ALIASES              15
#define XIADM16_HTTP_ALIASES                16
#define XIADM16_L_USER_AT_HOST              17
#define XIADM16_USER_AT_HOST                18
#define XIADM16_L_PASSWORD_CASE             19
#define XIADM16_PASSWORD_CASE               20
#define XIADM16_L_SOFT_QUOTA                21
#define XIADM16_SOFT_QUOTA                  22
#define XIADM16_L_HARD_QUOTA                23
#define XIADM16_HARD_QUOTA                  24
#define XIADM16_L_MESSAGE_SCRIPT            25
#define XIADM16_MESSAGE_SCRIPT              26
#define XIADM16_L_NONAME3                   27
#define XIADM16_L_WELCOME                   28
#define XIADM16_WELCOME                     29
#define XIADM16_L_LOGIN                     30
#define XIADM16_LOGIN                       31
#define XIADM16_L_SIGNOFF                   32
#define XIADM16_SIGNOFF                     33
#define XIADM16_L_PORT                      34
#define XIADM16_PORT                        35
#define XIADM16_L_LIMIT                     36
#define XIADM16_LIMIT                       37
#define XIADM16_L_PIPE                      38
#define XIADM16_PIPE                        39
#define XIADM16_L_WEBMASK                   40
#define XIADM16_WEBMASK                     41
#define XIADM16_L_DATA_PORT                 42
#define XIADM16_DATA_PORT                   43
#define XIADM16_L_IPADDRESS                 44
#define XIADM16_IPADDRESS                   45
#define XIADM16_MESSAGE_TO_USER             46

/*  This table contains each block in the form                               */

static byte xiadm16_blocks [] = {
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
    /*  !--ACTION back121  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '1',
    '2', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save122  LABEL="/a ...  ROLLOVER="/admin/savea.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '1',
    '2', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v',
    'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's',
    'a', 'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default123  LABEL= ... LLOVER="/admin/defaulta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '1', '2', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo124  LABEL="/a ...  ROLLOVER="/admin/undoa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '1',
    '2', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd',
    'o', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u',
    'n', 'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  - FTP Configuration </FONT>        */
    0, 70, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'F', 'T', 'P', 32, 'C', 'o', 'n', 'f', 'i', 'g',
    'u', 'r', 'a', 't', 'i', 'o', 'n', 32, '<', '/', 'F', 'O', 'N', 'T',
    '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console125  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '1', '2', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt126  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '1',
    '2', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart127  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '1', '2', '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit128  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '1',
    '2', '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'e',
    'x', 'i', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
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
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>                                       */
    0, 32, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', 10,
    /*  !--ACTION server  LABEL="Ser ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) server_event / 256), (byte) ((word)
    server_event & 255), 0, 8, 0, 0, 0, 0, 0, 's', 'e', 'r', 'v', 'e',
    'r', 0, 'S', 'e', 'r', 'v', 'e', 'r', 0, 0, 0, 0, 0,
    /*  !--ACTION vhosts  LABEL="Vho ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) vhosts_event / 256), (byte) ((word)
    vhosts_event & 255), 0, 9, 0, 0, 0, 0, 0, 'v', 'h', 'o', 's', 't',
    's', 0, 'V', 'h', 'o', 's', 't', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION cgi  LABEL="CGI" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) cgi_event / 256), (byte) ((word)
    cgi_event & 255), 0, 10, 0, 0, 0, 0, 0, 'c', 'g', 'i', 0, 'C', 'G',
    'I', 0, 0, 0, 0, 0,
    /*  !--ACTION security  LABEL="S ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 34, 20, 1, 1, (byte) ((word) security_event / 256), (byte)
    ((word) security_event & 255), 0, 11, 0, 0, 0, 0, 0, 's', 'e', 'c',
    'u', 'r', 'i', 't', 'y', 0, 'S', 'e', 'c', 'u', 'r', 'i', 't', 'y',
    0, 0, 0, 0, 0,
    /*  !--ACTION logging  LABEL="Lo ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) logging_event / 256), (byte) ((word)
    logging_event & 255), 0, 12, 0, 0, 0, 0, 0, 'l', 'o', 'g', 'g', 'i',
    'n', 'g', 0, 'L', 'o', 'g', 'g', 'i', 'n', 'g', 0, 0, 0, 0, 0,
    /*  <EM>FTP</EM>                                                         */
    0, 14, 0, '<', 'E', 'M', '>', 'F', 'T', 'P', '<', '/', 'E', 'M',
    '>', 10,
    /*  </FONT></TABLE><HR>                                                  */
    0, 21, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', '/', 'T', 'A',
    'B', 'L', 'E', '>', '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC main_config SIZE=4 VALUE=1                          */
    0, 28, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'm', 'a', 'i', 'n',
    '_', 'c', 'o', 'n', 'f', 'i', 'g', 0, '1', 0, 0,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  !--IF main_config  VALUE=1                                           */
    0, 7, 2, 0, 0, 0, 4, 0, 1,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f208 NAME=L ... le FTP server?&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '2', '0', '8', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'F', 'T', 'P', 32, 's', 'e', 'r', 'v', 'e',
    'r', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD BOOLEAN f209 NAME=e ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '2', '0', '9', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f210 NAME=L ... oot directory:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '1', '0', 0, 'F', 'T',
    'P', 32, 'r', 'o', 'o', 't', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o',
    'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f211 NAME=r ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '2', '1', '1', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f212 NAME=L ... r connections:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '1', '2', 0, 'T', 'i',
    'm', 'e', 'o', 'u', 't', 32, 'f', 'o', 'r', 32, 'c', 'o', 'n', 'n',
    'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD NUMERIC f213 NAME=t ... ZE=6 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '2', '1', '3',
    0, 0, 0,
    /*  seconds                                                              */
    0, 9, 0, 's', 'e', 'c', 'o', 'n', 'd', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f214 NAME=L ... guration file:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '1', '4', 0, 'U', 's',
    'e', 'r', 32, 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i',
    'o', 'n', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f215 NAME=u ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '2', '1', '5', 0, 0, 0,
    /*  !--ACTION define_users  LABE ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 39, 20, 0, 1, (byte) ((word) define_users_event / 256), (byte)
    ((word) define_users_event & 255), 0, 13, 0, 0, 0, 0, 0, 'd', 'e',
    'f', 'i', 'n', 'e', '_', 'u', 's', 'e', 'r', 's', 0, 'D', 'e', 'f',
    'i', 'n', 'e', '.', '.', '.', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f216 NAME=L ... y access file:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '2', '1', '6', 0, 'D', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'a', 'c', 'c', 'e', 's', 's',
    32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f217 NAME=d ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '2', '1', '7', 0, 0, 0,
    /*  !--ACTION define_dirs  LABEL ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 38, 20, 0, 1, (byte) ((word) define_dirs_event / 256), (byte)
    ((word) define_dirs_event & 255), 0, 14, 0, 0, 0, 0, 0, 'd', 'e',
    'f', 'i', 'n', 'e', '_', 'd', 'i', 'r', 's', 0, 'D', 'e', 'f', 'i',
    'n', 'e', '.', '.', '.', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f218 NAME=L ... ist sort order&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '2', '1', '8', 0, 'D', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'l', 'i', 's', 't', 32, 's',
    'o', 'r', 't', 32, 'o', 'r', 'd', 'e', 'r', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f219 NAME=d ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '2', '1', '9', 0, 0, 0,
    /*  n=name x=ext t=time s=size NXTS=invert                               */
    0, 40, 0, 'n', '=', 'n', 'a', 'm', 'e', 32, 'x', '=', 'e', 'x', 't',
    32, 't', '=', 't', 'i', 'm', 'e', 32, 's', '=', 's', 'i', 'z', 'e',
    32, 'N', 'X', 'T', 'S', '=', 'i', 'n', 'v', 'e', 'r', 't', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f220 NAME=L ... ous passwords?&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '2', '2', '0', 0, 'C', 'h',
    'e', 'c', 'k', 32, 'a', 'n', 'o', 'n', 'y', 'm', 'o', 'u', 's', 32,
    'p', 'a', 's', 's', 'w', 'o', 'r', 'd', 's', '?', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD BOOLEAN f221 NAME=e ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '2', '2', '1', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f222 NAME=L ...  HTTP aliases?&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '2', '2', 0, 'S', 'h',
    'a', 'r', 'e', 32, 'H', 'T', 'T', 'P', 32, 'a', 'l', 'i', 'a', 's',
    'e', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD BOOLEAN f223 NAME=h ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '2', '2', '3', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  !--ACTION ftp_aliases  LABEL ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 50, 20, 0, 1, (byte) ((word) aliases_event / 256), (byte) ((word)
    aliases_event & 255), 0, 15, 0, 0, 0, 0, 0, 'f', 't', 'p', '_', 'a',
    'l', 'i', 'a', 's', 'e', 's', 0, 'D', 'e', 'f', 'i', 'n', 'e', 32,
    'F', 'T', 'P', 32, 'a', 'l', 'i', 'a', 's', 'e', 's', '.', '.', '.',
    0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f224 NAME=L ... user@hostname?&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '2', '2', '4', 0, 'A', 'l',
    'l', 'o', 'w', 32, 'u', 's', 'e', 'r', '@', 'h', 'o', 's', 't', 'n',
    'a', 'm', 'e', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD BOOLEAN f225 NAME=u ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '2', '2', '5', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f226 NAME=L ... ive passwords?&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '2', '2', '6', 0, 'C', 'a',
    's', 'e', 45, 's', 'e', 'n', 's', 'i', 't', 'i', 'v', 'e', 32, 'p',
    'a', 's', 's', 'w', 'o', 'r', 'd', 's', '?', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD BOOLEAN f227 NAME=p ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '2', '2', '7', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f228 NAME=L ... ft quota (Mb):&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '2', '8', 0, 'D', 'e',
    'f', 'a', 'u', 'l', 't', 32, 's', 'o', 'f', 't', 32, 'q', 'u', 'o',
    't', 'a', 32, '(', 'M', 'b', ')', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f229 NAME=s ... 10 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 8, 0, 10, 'f', '2', '2', '9', 0, 0, 0,
    /*  !--FIELD TEXTUAL f230 NAME=L ... rd quota (Mb):&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '2', '3', '0', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'h', 'a', 'r',
    'd', 32, 'q', 'u', 'o', 't', 'a', 32, '(', 'M', 'b', ')', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f231 NAME=h ... 10 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 8, 0, 10, 'f', '2', '3', '1', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 56, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '9', '9', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L',
    'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P',
    32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'b', 'o', 'd', 'y', '>',
    10,
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f232 NAME=L ... mplate script:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '2', '3', '2', 0, 'M', 'e',
    's', 's', 'a', 'g', 'e', 32, 't', 'e', 'm', 'p', 'l', 'a', 't', 'e',
    32, 's', 'c', 'r', 'i', 'p', 't', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f233 NAME=m ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '2', '3', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f234 NAME=L ... e these texts:&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '2', '3', '4', 0, 'I', 'f',
    32, 'n', 'o', 32, 's', 'c', 'r', 'i', 'p', 't', ',', 32, 'u', 's',
    'e', 32, 't', 'h', 'e', 's', 'e', 32, 't', 'e', 'x', 't', 's', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f235 NAME=L ... lcome message:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '2', '3', '5', 0, 'W', 'e',
    'l', 'c', 'o', 'm', 'e', 32, 'm', 'e', 's', 's', 'a', 'g', 'e', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTBOX f236 NAME=w ... 40 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 14, 0, 1, 1, '(', 0, 0, 240, 'f', '2', '3', '6', 0, 0, 0,
    /*  text or @filename                                                    */
    0, 19, 0, 't', 'e', 'x', 't', 32, 'o', 'r', 32, '@', 'f', 'i', 'l',
    'e', 'n', 'a', 'm', 'e', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f237 NAME=L ... Login message:&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '2', '3', '7', 0, 'L', 'o',
    'g', 'i', 'n', 32, 'm', 'e', 's', 's', 'a', 'g', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTBOX f238 NAME=l ... 40 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 14, 0, 1, 1, '(', 0, 0, 240, 'f', '2', '3', '8', 0, 0, 0,
    /*  text or @filename                                                    */
    0, 4, 1, 0, 17, ')',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f239 NAME=L ... n-off message:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '2', '3', '9', 0, 'S', 'i',
    'g', 'n', 45, 'o', 'f', 'f', 32, 'm', 'e', 's', 's', 'a', 'g', 'e',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTBOX f240 NAME=s ... 40 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 14, 0, 1, 1, '(', 0, 0, 240, 'f', '2', '4', '0', 0, 0, 0,
    /*  text or @filename                                                    */
    0, 4, 1, 0, 17, ')',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 4, 1, 0, 15, 243,
    /*  <B>Advanced options</B>                                              */
    0, 25, 0, '<', 'B', '>', 'A', 'd', 'v', 'a', 'n', 'c', 'e', 'd', 32,
    'o', 'p', 't', 'i', 'o', 'n', 's', '<', '/', 'B', '>', 10,
    /*  !--IF main_config  VALUE=1                                           */
    0, 7, 2, 0, 0, 0, 11, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f241 NAME=L ... P connections:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '2', '4', '1', 0, 'P', 'o',
    'r', 't', 32, 'f', 'o', 'r', 32, 'F', 'T', 'P', 32, 'c', 'o', 'n',
    'n', 'e', 'c', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD NUMERIC f242 NAME=p ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '2', '4', '2',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f243 NAME=L ... P connections:&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '2', '4', '3', 0, 'M', 'a',
    'x', 32, 'F', 'T', 'P', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i',
    'o', 'n', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD NUMERIC f244 NAME=l ... ZE=6 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 1, 0, 'f', '2', '4', '4',
    0, 0, 0,
    /*  if any                                                               */
    0, 8, 0, 'i', 'f', 32, 'a', 'n', 'y', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f245 NAME=L ... throttle pipe:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '2', '4', '5', 0, 'D', 'e',
    'f', 'a', 'u', 'l', 't', 32, 't', 'h', 'r', 'o', 't', 't', 'l', 'e',
    32, 'p', 'i', 'p', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD SELECT f246 NAME=pi ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '2', '4', '6', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f247 NAME=L ...  address mask:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '2', '4', '7', 0, 'I', 'P',
    32, 'a', 'd', 'd', 'r', 'e', 's', 's', 32, 'm', 'a', 's', 'k', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD TEXTUAL f248 NAME=w ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '2', '4', '8', 0, 0, 0,
    /*  - eg. 111.222.333.*                                                  */
    0, 21, 0, 45, 32, 'e', 'g', '.', 32, '1', '1', '1', '.', '2', '2',
    '2', '.', '3', '3', '3', '.', '*', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f249 NAME=L ... nnection port:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '2', '4', '9', 0, 'D', 'a',
    't', 'a', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 32,
    'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD NUMERIC f250 NAME=d ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '2', '5', '0',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 179,
    /*  !--FIELD TEXTUAL f251 NAME=L ... ve IP address:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '2', '5', '1', 0, 'P', 'a',
    's', 's', 'i', 'v', 'e', 32, 'I', 'P', 32, 'a', 'd', 'd', 'r', 'e',
    's', 's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 25,
    /*  !--FIELD SELECT f252 NAME=ip ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '2', '5', '2', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 'l',
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
    0, 4, 1, 0, 20, 'h',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm16_fields [] = {
    { 0, 2676, 4 },                     /*  main_config                     */
    { 6, 2794, 30 },                    /*  l_enabled                       */
    { 38, 2904, 1 },                    /*  enabled                         */
    { 41, 2944, 31 },                   /*  l_rootdir                       */
    { 74, 2998, 100 },                  /*  rootdir                         */
    { 176, 3027, 36 },                  /*  l_timeout                       */
    { 214, 3086, 6 },                   /*  timeout                         */
    { 222, 3131, 36 },                  /*  l_user_file                     */
    { 260, 3190, 80 },                  /*  user_file                       */
    { 342, 3260, 34 },                  /*  l_directory_file                */
    { 378, 3317, 80 },                  /*  directory_file                  */
    { 460, 3386, 37 },                  /*  l_dirsort                       */
    { 499, 3446, 5 },                   /*  dirsort                         */
    { 506, 3517, 38 },                  /*  l_email_check                   */
    { 546, 3578, 1 },                   /*  email_check                     */
    { 549, 3610, 31 },                  /*  l_http_aliases                  */
    { 582, 3664, 1 },                   /*  http_aliases                    */
    { 585, 3748, 32 },                  /*  l_user_at_host                  */
    { 619, 3803, 1 },                   /*  user_at_host                    */
    { 622, 3835, 37 },                  /*  l_password_case                 */
    { 661, 3895, 1 },                   /*  password_case                   */
    { 664, 3927, 36 },                  /*  l_soft_quota                    */
    { 702, 3986, 10 },                  /*  soft_quota                      */
    { 714, 4003, 40 },                  /*  l_hard_quota                    */
    { 756, 4060, 10 },                  /*  hard_quota                      */
    { 768, 4160, 36 },                  /*  l_message_script                */
    { 806, 4219, 80 },                  /*  message_script                  */
    { 888, 4248, 42 },                  /*  l_noname3                       */
    { 932, 4325, 28 },                  /*  l_welcome                       */
    { 962, 4376, 240 },                 /*  welcome                         */
    { 1204, 4426, 26 },                 /*  l_login                         */
    { 1232, 4475, 240 },                /*  login                           */
    { 1474, 4510, 29 },                 /*  l_signoff                       */
    { 1505, 4562, 240 },                /*  signoff                         */
    { 1747, 4645, 37 },                 /*  l_port                          */
    { 1786, 4705, 5 },                  /*  port                            */
    { 1793, 4739, 32 },                 /*  l_limit                         */
    { 1827, 4794, 6 },                  /*  limit                           */
    { 1835, 4838, 34 },                 /*  l_pipe                          */
    { 1871, 4895, 3 },                  /*  pipe                            */
    { 1876, 4939, 28 },                 /*  l_webmask                       */
    { 1906, 4990, 80 },                 /*  webmask                         */
    { 1988, 5042, 33 },                 /*  l_data_port                     */
    { 2023, 5098, 5 },                  /*  data_port                       */
    { 2030, 5132, 31 },                 /*  l_ipaddress                     */
    { 2063, 5186, 3 },                  /*  ipaddress                       */
    { 2068, 5236, 120 },                /*  message_to_user                 */
    { 2190, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   main_config_a        ;
    char   main_config          [4 + 1];
    byte   l_enabled_a          ;
    char   l_enabled            [30 + 1];
    byte   enabled_a            ;
    char   enabled              [1 + 1];
    byte   l_rootdir_a          ;
    char   l_rootdir            [31 + 1];
    byte   rootdir_a            ;
    char   rootdir              [100 + 1];
    byte   l_timeout_a          ;
    char   l_timeout            [36 + 1];
    byte   timeout_a            ;
    char   timeout              [6 + 1];
    byte   l_user_file_a        ;
    char   l_user_file          [36 + 1];
    byte   user_file_a          ;
    char   user_file            [80 + 1];
    byte   l_directory_file_a   ;
    char   l_directory_file     [34 + 1];
    byte   directory_file_a     ;
    char   directory_file       [80 + 1];
    byte   l_dirsort_a          ;
    char   l_dirsort            [37 + 1];
    byte   dirsort_a            ;
    char   dirsort              [5 + 1];
    byte   l_email_check_a      ;
    char   l_email_check        [38 + 1];
    byte   email_check_a        ;
    char   email_check          [1 + 1];
    byte   l_http_aliases_a     ;
    char   l_http_aliases       [31 + 1];
    byte   http_aliases_a       ;
    char   http_aliases         [1 + 1];
    byte   l_user_at_host_a     ;
    char   l_user_at_host       [32 + 1];
    byte   user_at_host_a       ;
    char   user_at_host         [1 + 1];
    byte   l_password_case_a    ;
    char   l_password_case      [37 + 1];
    byte   password_case_a      ;
    char   password_case        [1 + 1];
    byte   l_soft_quota_a       ;
    char   l_soft_quota         [36 + 1];
    byte   soft_quota_a         ;
    char   soft_quota           [10 + 1];
    byte   l_hard_quota_a       ;
    char   l_hard_quota         [40 + 1];
    byte   hard_quota_a         ;
    char   hard_quota           [10 + 1];
    byte   l_message_script_a   ;
    char   l_message_script     [36 + 1];
    byte   message_script_a     ;
    char   message_script       [80 + 1];
    byte   l_noname3_a          ;
    char   l_noname3            [42 + 1];
    byte   l_welcome_a          ;
    char   l_welcome            [28 + 1];
    byte   welcome_a            ;
    char   welcome              [240 + 1];
    byte   l_login_a            ;
    char   l_login              [26 + 1];
    byte   login_a              ;
    char   login                [240 + 1];
    byte   l_signoff_a          ;
    char   l_signoff            [29 + 1];
    byte   signoff_a            ;
    char   signoff              [240 + 1];
    byte   l_port_a             ;
    char   l_port               [37 + 1];
    byte   port_a               ;
    char   port                 [5 + 1];
    byte   l_limit_a            ;
    char   l_limit              [32 + 1];
    byte   limit_a              ;
    char   limit                [6 + 1];
    byte   l_pipe_a             ;
    char   l_pipe               [34 + 1];
    byte   pipe_a               ;
    char   pipe                 [3 + 1];
    byte   l_webmask_a          ;
    char   l_webmask            [28 + 1];
    byte   webmask_a            ;
    char   webmask              [80 + 1];
    byte   l_data_port_a        ;
    char   l_data_port          [33 + 1];
    byte   data_port_a          ;
    char   data_port            [5 + 1];
    byte   l_ipaddress_a        ;
    char   l_ipaddress          [31 + 1];
    byte   ipaddress_a          ;
    char   ipaddress            [3 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back121_a;
    byte   save122_a;
    byte   default123_a;
    byte   undo124_a;
    byte   console125_a;
    byte   halt126_a;
    byte   restart127_a;
    byte   exit128_a;
    byte   server_a;
    byte   vhosts_a;
    byte   cgi_a;
    byte   security_a;
    byte   logging_a;
    byte   define_users_a;
    byte   define_dirs_a;
    byte   ftp_aliases_a;
    } XIADM16_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm16 = {
    xiadm16_blocks,
    xiadm16_fields,
    190,                                /*  Number of blocks in form        */
    47,                                 /*  Number of fields in form        */
    16,                                 /*  Number of actions in form       */
    2190,                               /*  Size of fields                  */
    "xiadm16",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

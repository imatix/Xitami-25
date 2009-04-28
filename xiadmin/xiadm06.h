/*---------------------------------------------------------------------------
 *  xiadm06.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM06__
#define __FORM_XIADM06__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM06_ON_WINDOWS_32               0
#define XIADM06_L_ENABLED                   1
#define XIADM06_ENABLED                     2
#define XIADM06_L_WORKDIR                   3
#define XIADM06_WORKDIR                     4
#define XIADM06_L_WILDCARD                  5
#define XIADM06_WILDCARD                    6
#define XIADM06_L_TIMEOUT                   7
#define XIADM06_TIMEOUT                     8
#define XIADM06_L_MONITOR                   9
#define XIADM06_MONITOR                     10
#define XIADM06_L_DIRLIST                   11
#define XIADM06_DIRLIST                     12
#define XIADM06_L_SUPPORT_16BIT             13
#define XIADM06_SUPPORT_16BIT               14
#define XIADM06_L_MSDOS_STYLE               15
#define XIADM06_MSDOS_STYLE                 16
#define XIADM06_L_DEBUG                     17
#define XIADM06_DEBUG                       18
#define XIADM06_L_STDIO                     19
#define XIADM06_STDIO                       20
#define XIADM06_L_MIXED_URL                 21
#define XIADM06_MIXED_URL                   22
#define XIADM06_L_ERRLOG                    23
#define XIADM06_ERRLOG                      24
#define XIADM06_L_NONAME1                   25
#define XIADM06_L_ENVIRON                   26
#define XIADM06_ENVIRON                     27
#define XIADM06_L_HTTP_FIELDS               28
#define XIADM06_HTTP_FIELDS                 29
#define XIADM06_L_HTTP_PREFIX               30
#define XIADM06_HTTP_PREFIX                 31
#define XIADM06_L_FORM_FIELDS               32
#define XIADM06_FORM_FIELDS                 33
#define XIADM06_L_FORM_PREFIX               34
#define XIADM06_FORM_PREFIX                 35
#define XIADM06_L_FORM_QUERY                36
#define XIADM06_FORM_QUERY                  37
#define XIADM06_L_CGI_ENVIR                 38
#define XIADM06_L_CGI_ALIAS                 39
#define XIADM06_MESSAGE_TO_USER             40

/*  This table contains each block in the form                               */

static byte xiadm06_blocks [] = {
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
    /*  !--ACTION back29  LABEL="/ad ...  ROLLOVER="/admin/backa.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '2',
    '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c', 'k',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b', 'a',
    'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save30  LABEL="/ad ...  ROLLOVER="/admin/savea.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '3',
    '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v', 'e',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's', 'a',
    'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default31  LABEL=" ... LLOVER="/admin/defaulta.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '3', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo32  LABEL="/ad ...  ROLLOVER="/admin/undoa.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '3',
    '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd', 'o',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u', 'n',
    'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 68, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'c', 'g', 'i',
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ... ig) - CGI Properties </FONT>        */
    0, 67, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'C', 'G', 'I', 32, 'P', 'r', 'o', 'p', 'e', 'r',
    't', 'i', 'e', 's', 32, '<', '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console33  LABEL=" ... LLOVER="/admin/consolea.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '3', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt34  LABEL="/ad ...  ROLLOVER="/admin/halta.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '3',
    '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h', 'a',
    'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart35  LABEL=" ... LLOVER="/admin/restarta.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '3', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit36  LABEL="/ad ...  ROLLOVER="/admin/exita.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '3',
    '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i', 't',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'e', 'x',
    'i', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
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
    /*  !--ACTION environment  LABEL ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 40, 20, 1, 1, (byte) ((word) environment_event / 256), (byte)
    ((word) environment_event & 255), 0, 9, 0, 0, 0, 0, 0, 'e', 'n',
    'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', 0, 'E', 'n', 'v', 'i',
    'r', 'o', 'n', 'm', 'e', 'n', 't', 0, 0, 0, 0, 0,
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>                                       */
    0, 32, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', 10,
    /*  !--ACTION server  LABEL="Ser ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) server_event / 256), (byte) ((word)
    server_event & 255), 0, 10, 0, 0, 0, 0, 0, 's', 'e', 'r', 'v', 'e',
    'r', 0, 'S', 'e', 'r', 'v', 'e', 'r', 0, 0, 0, 0, 0,
    /*  !--ACTION vhosts  LABEL="Vho ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) vhosts_event / 256), (byte) ((word)
    vhosts_event & 255), 0, 11, 0, 0, 0, 0, 0, 'v', 'h', 'o', 's', 't',
    's', 0, 'V', 'h', 'o', 's', 't', 's', 0, 0, 0, 0, 0,
    /*  <EM>CGI</EM>                                                         */
    0, 14, 0, '<', 'E', 'M', '>', 'C', 'G', 'I', '<', '/', 'E', 'M',
    '>', 10,
    /*  !--ACTION security  LABEL="S ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 34, 20, 1, 1, (byte) ((word) security_event / 256), (byte)
    ((word) security_event & 255), 0, 12, 0, 0, 0, 0, 0, 's', 'e', 'c',
    'u', 'r', 'i', 't', 'y', 0, 'S', 'e', 'c', 'u', 'r', 'i', 't', 'y',
    0, 0, 0, 0, 0,
    /*  !--ACTION logging  LABEL="Lo ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) logging_event / 256), (byte) ((word)
    logging_event & 255), 0, 13, 0, 0, 0, 0, 0, 'l', 'o', 'g', 'g', 'i',
    'n', 'g', 0, 'L', 'o', 'g', 'g', 'i', 'n', 'g', 0, 0, 0, 0, 0,
    /*  !--ACTION ftp  LABEL="FTP" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) ftp_event / 256), (byte) ((word)
    ftp_event & 255), 0, 14, 0, 0, 0, 0, 0, 'f', 't', 'p', 0, 'F', 'T',
    'P', 0, 0, 0, 0, 0,
    /*  </FONT></TABLE><HR>                                                  */
    0, 21, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', '/', 'T', 'A',
    'B', 'L', 'E', '>', '<', 'H', 'R', '>', 10,
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
    /*  !--FIELD TEXTUAL f54 NAME=L_ ... ="CGI enabled?&nbsp;&nbsp;"         */
    0, 38, 10, 6, 1, 0, 0, 24, 0, 24, 'f', '5', '4', 0, 'C', 'G', 'I',
    32, 'e', 'n', 'a', 'b', 'l', 'e', 'd', '?', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD BOOLEAN f55 NAME=en ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '5', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f56 NAME=L_ ... ing directory:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '5', '6', 0, 'W', 'o', 'r',
    'k', 'i', 'n', 'g', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD TEXTUAL f57 NAME=wo ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'd', 'f', '5', '7', 0, 0, 0,
    /*  '-' means use program directory                                      */
    0, 33, 0, 39, 45, 39, 32, 'm', 'e', 'a', 'n', 's', 32, 'u', 's',
    'e', 32, 'p', 'r', 'o', 'g', 'r', 'a', 'm', 32, 'd', 'i', 'r', 'e',
    'c', 't', 'o', 'r', 'y', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f58 NAME=L_ ... ywhere in URL?&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '+', 0, '+', 'f', '5', '8', 0, 'M', 'a', 't',
    'c', 'h', 32, '/', 'c', 'g', 'i', 45, 'b', 'i', 'n', 32, 'a', 'n',
    'y', 'w', 'h', 'e', 'r', 'e', 32, 'i', 'n', 32, 'U', 'R', 'L', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f59 NAME=wi ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '5', '9', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  If not, /cgi-bin must come at the start                              */
    0, 41, 0, 'I', 'f', 32, 'n', 'o', 't', ',', 32, '/', 'c', 'g', 'i',
    45, 'b', 'i', 'n', 32, 'm', 'u', 's', 't', 32, 'c', 'o', 'm', 'e',
    32, 'a', 't', 32, 't', 'h', 'e', 32, 's', 't', 'a', 'r', 't', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f60 NAME=L_ ...  CGI programs:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '6', '0', 0, 'T', 'i', 'm',
    'e', 'o', 'u', 't', 32, 'f', 'o', 'r', 32, 'C', 'G', 'I', 32, 'p',
    'r', 'o', 'g', 'r', 'a', 'm', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD NUMERIC f61 NAME=ti ... ZE=8 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 0, 1, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 'f', '6', '1', 0, 0,
    0,
    /*  seconds                                                              */
    0, 9, 0, 's', 'e', 'c', 'o', 'n', 'd', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f62 NAME=L_ ... rogress every:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '6', '2', 0, 'C', 'h', 'e',
    'c', 'k', 32, 'C', 'G', 'I', 32, 'p', 'r', 'o', 'g', 'r', 'e', 's',
    's', 32, 'e', 'v', 'e', 'r', 'y', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD NUMERIC f63 NAME=mo ... ZE=8 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 0, 1, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 'f', '6', '3', 0, 0,
    0,
    /*  msecs                                                                */
    0, 7, 0, 'm', 's', 'e', 'c', 's', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f64 NAME=L_ ... rectory lists?&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '6', '4', 0, 'A', 'l', 'l',
    'o', 'w', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'l',
    'i', 's', 't', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f65 NAME=di ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '6', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  !--IF on_windows_32  VALUE=1                                         */
    0, 7, 2, 0, 0, 0, 5, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f66 NAME=L_ ...  CGI programs?&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '6', '6', 0, 'S', 'u', 'p',
    'p', 'o', 'r', 't', 32, '1', '6', 45, 'b', 'i', 't', 32, 'C', 'G',
    'I', 32, 'p', 'r', 'o', 'g', 'r', 'a', 'm', 's', '?', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f67 NAME=su ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '6', '7', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f68 NAME=L_ ... yle filenames?&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, 39, 0, 39, 'f', '6', '8', 0, 'U', 's', 'e',
    32, 'M', 'S', 45, 'D', 'O', 'S', 45, 's', 't', 'y', 'l', 'e', 32,
    'f', 'i', 'l', 'e', 'n', 'a', 'm', 'e', 's', '?', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f69 NAME=ms ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '6', '9', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f70 NAME=L_ ... ug CGI in/out?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '7', '0', 0, 'D', 'e', 'b',
    'u', 'g', 32, 'C', 'G', 'I', 32, 'i', 'n', '/', 'o', 'u', 't', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f71 NAME=de ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '7', '1', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f72 NAME=L_ ...  standard I/O?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '7', '2', 0, 'U', 's', 'e',
    32, 's', 't', 'a', 'n', 'd', 'a', 'r', 'd', 32, 'I', '/', 'O', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f73 NAME=st ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '7', '3', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  - switch off if you use CGI_STDOUT, e.g. for Basic                   */
    0, 52, 0, 45, 32, 's', 'w', 'i', 't', 'c', 'h', 32, 'o', 'f', 'f',
    32, 'i', 'f', 32, 'y', 'o', 'u', 32, 'u', 's', 'e', 32, 'C', 'G',
    'I', '_', 'S', 'T', 'D', 'O', 'U', 'T', ',', 32, 'e', '.', 'g', '.',
    32, 'f', 'o', 'r', 32, 'B', 'a', 's', 'i', 'c', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f74 NAME=L_ ... w file mixing?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '7', '4', 0, 'A', 'l', 'l',
    'o', 'w', 32, 'f', 'i', 'l', 'e', 32, 'm', 'i', 'x', 'i', 'n', 'g',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f75 NAME=mi ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '7', '5', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  - e.g. images in CGI bin directory                                   */
    0, 36, 0, 45, 32, 'e', '.', 'g', '.', 32, 'i', 'm', 'a', 'g', 'e',
    's', 32, 'i', 'n', 32, 'C', 'G', 'I', 32, 'b', 'i', 'n', 32, 'd',
    'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f76 NAME=L_ ... file (stderr):&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '7', '6', 0, 'E', 'r', 'r',
    'o', 'r', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', 32, '(', 's',
    't', 'd', 'e', 'r', 'r', ')', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD TEXTUAL f77 NAME=er ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '7', '7', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 56, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '9', '9', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L',
    'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P',
    32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'b', 'o', 'd', 'y', '>',
    10,
    /*  <P>                                                                  */
    0, 5, 0, '<', 'P', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f78 NAME=L_ ... GI environment&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '7', '8', 0, 'C', 'G', 'I',
    32, 'e', 'n', 'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f79 NAME=L_ ... l environment?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '7', '9', 0, 'F', 'u', 'l',
    'l', 32, 'e', 'n', 'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f80 NAME=en ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '8', '0', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f81 NAME=L_ ... s HTTP fields?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '8', '1', 0, 'P', 'a', 's',
    's', 32, 'H', 'T', 'T', 'P', 32, 'f', 'i', 'e', 'l', 'd', 's', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f82 NAME=ht ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '8', '2', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  !--FIELD TEXTUAL f83 NAME=L_ ... ;Using prefix:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '8', '3', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'U', 's', 'i', 'n',
    'g', 32, 'p', 'r', 'e', 'f', 'i', 'x', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f84 NAME=ht ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '8', '4', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f85 NAME=L_ ... s form fields?&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '8', '5', 0, 'P', 'a', 's',
    's', 32, 'f', 'o', 'r', 'm', 32, 'f', 'i', 'e', 'l', 'd', 's', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f86 NAME=fo ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '8', '6', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  !--FIELD TEXTUAL f87 NAME=L_ ... ;Using prefix:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '8', '7', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'U', 's', 'i', 'n',
    'g', 32, 'p', 'r', 'e', 'f', 'i', 'x', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f88 NAME=fo ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '8', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f89 NAME=L_ ...  QUERY_STRING?&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '8', '9', 0, 'P', 'a', 's',
    's', 32, 'Q', 'U', 'E', 'R', 'Y', '_', 'S', 'T', 'R', 'I', 'N', 'G',
    '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--FIELD BOOLEAN f90 NAME=fo ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '9', '0', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f91 NAME=L_ ... I environment:&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '9', '1', 0, 'S', 'p', 'e',
    'c', 'i', 'f', 'i', 'c', 32, 'C', 'G', 'I', 32, 'e', 'n', 'v', 'i',
    'r', 'o', 'n', 'm', 'e', 'n', 't', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--ACTION cgi_envir  LABEL=" ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 36, 20, 0, 1, (byte) ((word) environment_event / 256), (byte)
    ((word) environment_event & 255), 0, 15, 0, 0, 0, 0, 0, 'c', 'g',
    'i', '_', 'e', 'n', 'v', 'i', 'r', 0, 'D', 'e', 'f', 'i', 'n', 'e',
    '.', '.', '.', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 237,
    /*  !--FIELD TEXTUAL f92 NAME=L_ ... I directories:&nbsp;&nbsp;"         */
    0, 54, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '9', '2', 0, 'A', 'l', 'i',
    'a', 's', 'e', 's', 32, 'f', 'o', 'r', 32, 'C', 'G', 'I', 32, 'd',
    'i', 'r', 'e', 'c', 't', 'o', 'r', 'i', 'e', 's', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'L',
    /*  !--ACTION cgi_alias  LABEL=" ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 36, 20, 0, 1, (byte) ((word) aliases_event / 256), (byte) ((word)
    aliases_event & 255), 0, 16, 0, 0, 0, 0, 0, 'c', 'g', 'i', '_', 'a',
    'l', 'i', 'a', 's', 0, 'D', 'e', 'f', 'i', 'n', 'e', '.', '.', '.',
    0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 158,
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
    0, 4, 1, 0, 19, 'l',
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm06_fields [] = {
    { 0, 2741, 4 },                     /*  on_windows_32                   */
    { 6, 2852, 24 },                    /*  l_enabled                       */
    { 32, 2955, 1 },                    /*  enabled                         */
    { 35, 2994, 30 },                   /*  l_workdir                       */
    { 67, 3046, 100 },                  /*  workdir                         */
    { 169, 3109, 43 },                  /*  l_wildcard                      */
    { 214, 3174, 1 },                   /*  wildcard                        */
    { 217, 3248, 37 },                  /*  l_timeout                       */
    { 256, 3307, 8 },                   /*  timeout                         */
    { 266, 3351, 37 },                  /*  l_monitor                       */
    { 305, 3410, 8 },                   /*  monitor                         */
    { 315, 3452, 34 },                  /*  l_dirlist                       */
    { 351, 3508, 1 },                   /*  dirlist                         */
    { 354, 3548, 40 },                  /*  l_support_16bit                 */
    { 396, 3610, 1 },                   /*  support_16bit                   */
    { 399, 3641, 39 },                  /*  l_msdos_style                   */
    { 440, 3702, 1 },                   /*  msdos_style                     */
    { 443, 3733, 29 },                  /*  l_debug                         */
    { 474, 3784, 1 },                   /*  debug                           */
    { 477, 3815, 29 },                  /*  l_stdio                         */
    { 508, 3866, 1 },                   /*  stdio                           */
    { 511, 3951, 30 },                  /*  l_mixed_url                     */
    { 543, 4003, 1 },                   /*  mixed_url                       */
    { 546, 4072, 36 },                  /*  l_errlog                        */
    { 584, 4130, 80 },                  /*  errlog                          */
    { 666, 4229, 27 },                  /*  l_noname1                       */
    { 695, 4290, 29 },                  /*  l_environ                       */
    { 726, 4341, 1 },                   /*  environ                         */
    { 729, 4372, 29 },                  /*  l_http_fields                   */
    { 760, 4423, 1 },                   /*  http_fields                     */
    { 763, 4442, 37 },                  /*  l_http_prefix                   */
    { 802, 4495, 20 },                  /*  http_prefix                     */
    { 824, 4523, 29 },                  /*  l_form_fields                   */
    { 855, 4574, 1 },                   /*  form_fields                     */
    { 858, 4593, 37 },                  /*  l_form_prefix                   */
    { 897, 4646, 20 },                  /*  form_prefix                     */
    { 919, 4674, 30 },                  /*  l_form_query                    */
    { 951, 4726, 1 },                   /*  form_query                      */
    { 954, 4757, 37 },                  /*  l_cgi_envir                     */
    { 993, 4866, 40 },                  /*  l_cgi_alias                     */
    { 1035, 4984, 120 },                /*  message_to_user                 */
    { 1157, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   on_windows_32_a      ;
    char   on_windows_32        [4 + 1];
    byte   l_enabled_a          ;
    char   l_enabled            [24 + 1];
    byte   enabled_a            ;
    char   enabled              [1 + 1];
    byte   l_workdir_a          ;
    char   l_workdir            [30 + 1];
    byte   workdir_a            ;
    char   workdir              [100 + 1];
    byte   l_wildcard_a         ;
    char   l_wildcard           [43 + 1];
    byte   wildcard_a           ;
    char   wildcard             [1 + 1];
    byte   l_timeout_a          ;
    char   l_timeout            [37 + 1];
    byte   timeout_a            ;
    char   timeout              [8 + 1];
    byte   l_monitor_a          ;
    char   l_monitor            [37 + 1];
    byte   monitor_a            ;
    char   monitor              [8 + 1];
    byte   l_dirlist_a          ;
    char   l_dirlist            [34 + 1];
    byte   dirlist_a            ;
    char   dirlist              [1 + 1];
    byte   l_support_16bit_a    ;
    char   l_support_16bit      [40 + 1];
    byte   support_16bit_a      ;
    char   support_16bit        [1 + 1];
    byte   l_msdos_style_a      ;
    char   l_msdos_style        [39 + 1];
    byte   msdos_style_a        ;
    char   msdos_style          [1 + 1];
    byte   l_debug_a            ;
    char   l_debug              [29 + 1];
    byte   debug_a              ;
    char   debug                [1 + 1];
    byte   l_stdio_a            ;
    char   l_stdio              [29 + 1];
    byte   stdio_a              ;
    char   stdio                [1 + 1];
    byte   l_mixed_url_a        ;
    char   l_mixed_url          [30 + 1];
    byte   mixed_url_a          ;
    char   mixed_url            [1 + 1];
    byte   l_errlog_a           ;
    char   l_errlog             [36 + 1];
    byte   errlog_a             ;
    char   errlog               [80 + 1];
    byte   l_noname1_a          ;
    char   l_noname1            [27 + 1];
    byte   l_environ_a          ;
    char   l_environ            [29 + 1];
    byte   environ_a            ;
    char   environ              [1 + 1];
    byte   l_http_fields_a      ;
    char   l_http_fields        [29 + 1];
    byte   http_fields_a        ;
    char   http_fields          [1 + 1];
    byte   l_http_prefix_a      ;
    char   l_http_prefix        [37 + 1];
    byte   http_prefix_a        ;
    char   http_prefix          [20 + 1];
    byte   l_form_fields_a      ;
    char   l_form_fields        [29 + 1];
    byte   form_fields_a        ;
    char   form_fields          [1 + 1];
    byte   l_form_prefix_a      ;
    char   l_form_prefix        [37 + 1];
    byte   form_prefix_a        ;
    char   form_prefix          [20 + 1];
    byte   l_form_query_a       ;
    char   l_form_query         [30 + 1];
    byte   form_query_a         ;
    char   form_query           [1 + 1];
    byte   l_cgi_envir_a        ;
    char   l_cgi_envir          [37 + 1];
    byte   l_cgi_alias_a        ;
    char   l_cgi_alias          [40 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back29_a;
    byte   save30_a;
    byte   default31_a;
    byte   undo32_a;
    byte   console33_a;
    byte   halt34_a;
    byte   restart35_a;
    byte   exit36_a;
    byte   aliases_a;
    byte   environment_a;
    byte   server_a;
    byte   vhosts_a;
    byte   security_a;
    byte   logging_a;
    byte   ftp_a;
    byte   cgi_envir_a;
    byte   cgi_alias_a;
    } XIADM06_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm06 = {
    xiadm06_blocks,
    xiadm06_fields,
    171,                                /*  Number of blocks in form        */
    41,                                 /*  Number of fields in form        */
    17,                                 /*  Number of actions in form       */
    1157,                               /*  Size of fields                  */
    "xiadm06",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

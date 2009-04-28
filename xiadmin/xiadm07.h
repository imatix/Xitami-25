/*---------------------------------------------------------------------------
 *  xiadm07.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM07__
#define __FORM_XIADM07__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM07_ON_WINDOWS_32               0
#define XIADM07_ON_UNIX                     1
#define XIADM07_L_FILENAME                  2
#define XIADM07_FILENAME                    3
#define XIADM07_L_PASSWORD_CASE             4
#define XIADM07_PASSWORD_CASE               5
#define XIADM07_L_DIRLIST                   6
#define XIADM07_DIRLIST                     7
#define XIADM07_L_ADMIN                     8
#define XIADM07_ADMIN                       9
#define XIADM07_L_WEBMASK                   10
#define XIADM07_WEBMASK                     11
#define XIADM07_L_SUPERUSER                 12
#define XIADM07_SUPERUSER                   13
#define XIADM07_L_SAFEPATHS                 14
#define XIADM07_SAFEPATHS                   15
#define XIADM07_L_SECURE                    16
#define XIADM07_SECURE                      17
#define XIADM07_L_CGI_USERNAME              18
#define XIADM07_CGI_USERNAME                19
#define XIADM07_L_CGI_GROUPNAME             20
#define XIADM07_CGI_GROUPNAME               21
#define XIADM07_L_CGI_PASSWORD              22
#define XIADM07_CGI_PASSWORD                23
#define XIADM07_L_SETUID                    24
#define XIADM07_SETUID                      25
#define XIADM07_L_SETUID_USER               26
#define XIADM07_SETUID_USER                 27
#define XIADM07_L_SETUID_GROUP              28
#define XIADM07_SETUID_GROUP                29
#define XIADM07_MESSAGE_TO_USER             30

/*  This table contains each block in the form                               */

static byte xiadm07_blocks [] = {
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
    /*  !--ACTION back37  LABEL="/ad ...  ROLLOVER="/admin/backa.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '3',
    '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c', 'k',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b', 'a',
    'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save38  LABEL="/ad ...  ROLLOVER="/admin/savea.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '3',
    '8', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v', 'e',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's', 'a',
    'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default39  LABEL=" ... LLOVER="/admin/defaulta.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '3', '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo40  LABEL="/ad ...  ROLLOVER="/admin/undoa.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '4',
    '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd', 'o',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u', 'n',
    'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 73, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 's', 'e', 'c',
    'u', 'r', 'i', 't', 'y', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=',
    '"', 'H', 'e', 'l', 'p', '"', 32, 'T', 'I', 'T', 'L', 'E', '=', '"',
    'H', 'e', 'l', 'p', '"', 10,
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ... fig) - HTTP Security </FONT>        */
    0, 66, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'H', 'T', 'T', 'P', 32, 'S', 'e', 'c', 'u', 'r',
    'i', 't', 'y', 32, '<', '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console41  LABEL=" ... LLOVER="/admin/consolea.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '4', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt42  LABEL="/ad ...  ROLLOVER="/admin/halta.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '4',
    '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l', 't',
    '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h', 'a',
    'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart43  LABEL=" ... LLOVER="/admin/restarta.gif"        */
    0, 65, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '4', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$',
    'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/', 'a',
    'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't', 'a',
    '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit44  LABEL="/ad ...  ROLLOVER="/admin/exita.gif"        */
    0, 56, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '4',
    '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i', 't',
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
    /*  !--ACTION passwords  LABEL=" ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 36, 20, 1, 1, (byte) ((word) passwords_event / 256), (byte)
    ((word) passwords_event & 255), 0, 8, 0, 0, 0, 0, 0, 'p', 'a', 's',
    's', 'w', 'o', 'r', 'd', 's', 0, 'P', 'a', 's', 's', 'w', 'o', 'r',
    'd', 's', 0, 0, 0, 0, 0,
    /*  <TD ALIGN=RIGHT><FONT SIZE=-1>                                       */
    0, 32, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z', 'E',
    '=', 45, '1', '>', 10,
    /*  !--ACTION server  LABEL="Ser ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) server_event / 256), (byte) ((word)
    server_event & 255), 0, 9, 0, 0, 0, 0, 0, 's', 'e', 'r', 'v', 'e',
    'r', 0, 'S', 'e', 'r', 'v', 'e', 'r', 0, 0, 0, 0, 0,
    /*  !--ACTION vhosts  LABEL="Vho ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) vhosts_event / 256), (byte) ((word)
    vhosts_event & 255), 0, 10, 0, 0, 0, 0, 0, 'v', 'h', 'o', 's', 't',
    's', 0, 'V', 'h', 'o', 's', 't', 's', 0, 0, 0, 0, 0,
    /*  !--ACTION cgi  LABEL="CGI" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) cgi_event / 256), (byte) ((word)
    cgi_event & 255), 0, 11, 0, 0, 0, 0, 0, 'c', 'g', 'i', 0, 'C', 'G',
    'I', 0, 0, 0, 0, 0,
    /*  <EM>Security</EM>                                                    */
    0, 19, 0, '<', 'E', 'M', '>', 'S', 'e', 'c', 'u', 'r', 'i', 't',
    'y', '<', '/', 'E', 'M', '>', 10,
    /*  !--ACTION logging  LABEL="Lo ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) logging_event / 256), (byte) ((word)
    logging_event & 255), 0, 12, 0, 0, 0, 0, 0, 'l', 'o', 'g', 'g', 'i',
    'n', 'g', 0, 'L', 'o', 'g', 'g', 'i', 'n', 'g', 0, 0, 0, 0, 0,
    /*  !--ACTION ftp  LABEL="FTP" E ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 24, 20, 1, 1, (byte) ((word) ftp_event / 256), (byte) ((word)
    ftp_event & 255), 0, 13, 0, 0, 0, 0, 0, 'f', 't', 'p', 0, 'F', 'T',
    'P', 0, 0, 0, 0, 0,
    /*  </FONT></TABLE><HR>                                                  */
    0, 21, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', '/', 'T', 'A',
    'B', 'L', 'E', '>', '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC on_windows_32 SIZE=4 VALUE=1                        */
    0, 30, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'o', 'n', '_', 'w',
    'i', 'n', 'd', 'o', 'w', 's', '_', '3', '2', 0, '1', 0, 0,
    /*  !--FIELD NUMERIC on_unix SIZE=4 VALUE=1                              */
    0, 24, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'o', 'n', '_', 'u',
    'n', 'i', 'x', 0, '1', 0, 0,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f93 NAME=L_ ... Password file:&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '9', '3', 0, 'P', 'a', 's',
    's', 'w', 'o', 'r', 'd', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f94 NAME=fi ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 20, 0, 'P', 'f', '9', '4', 0, 0, 0,
    /*  - blank to disable password protection                               */
    0, 40, 0, 45, 32, 'b', 'l', 'a', 'n', 'k', 32, 't', 'o', 32, 'd',
    'i', 's', 'a', 'b', 'l', 'e', 32, 'p', 'a', 's', 's', 'w', 'o', 'r',
    'd', 32, 'p', 'r', 'o', 't', 'e', 'c', 't', 'i', 'o', 'n', 10,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD></TD><TD VALIGN=TOP  ... WIDTH=""80%"" CLASS=tdvalue>        */
    0, 69, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T',
    'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E', 'F', 'T', 32,
    'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8', '0', '%', '"', '"', 32,
    'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v', 'a', 'l', 'u', 'e',
    '>', 10,
    /*  !--ACTION define  LABEL="Def ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 33, 20, 0, 1, (byte) ((word) passwords_event / 256), (byte)
    ((word) passwords_event & 255), 0, 14, 0, 0, 0, 0, 0, 'd', 'e', 'f',
    'i', 'n', 'e', 0, 'D', 'e', 'f', 'i', 'n', 'e', '.', '.', '.', 0, 0,
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f95 NAME=L_ ... ive passwords?&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '9', '5', 0, 'C', 'a', 's',
    'e', 45, 's', 'e', 'n', 's', 'i', 't', 'i', 'v', 'e', 32, 'p', 'a',
    's', 's', 'w', 'o', 'r', 'd', 's', '?', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD BOOLEAN f96 NAME=pa ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '9', '6', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f97 NAME=L_ ... rectory lists?&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '9', '7', 0, 'A', 'l', 'l',
    'o', 'w', 32, 'd', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'l',
    'i', 's', 't', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD BOOLEAN f98 NAME=di ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 0, 1, 'f', '9', '8', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f99 NAME=L_ ... b-based admin?&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '9', '9', 0, 'A', 'l', 'l',
    'o', 'w', 32, 'w', 'e', 'b', 45, 'b', 'a', 's', 'e', 'd', 32, 'a',
    'd', 'm', 'i', 'n', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD BOOLEAN f100 NAME=a ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '1', '0', '0', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f101 NAME=L ...  address mask:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', '0', '1', 0, 'I', 'P',
    32, 'a', 'd', 'd', 'r', 'e', 's', 's', 32, 'm', 'a', 's', 'k', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD TEXTUAL f102 NAME=w ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 'P', 'f', '1', '0', '2', 0, 0, 0,
    /*  - eg. 111.222.333.*                                                  */
    0, 21, 0, 45, 32, 'e', 'g', '.', 32, '1', '1', '1', '.', '2', '2',
    '2', '.', '3', '3', '3', '.', '*', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f103 NAME=L ... user password:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '1', '0', '3', 0, 'S', 'u',
    'p', 'e', 'r', 'u', 's', 'e', 'r', 32, 'p', 'a', 's', 's', 'w', 'o',
    'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD TEXTUAL f104 NAME=s ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 20, 'f', '1', '0', '4', 0, 0, 0,
    /*  - gives FULL ACCESS to ALL RESOURCES                                 */
    0, 38, 0, 45, 32, 'g', 'i', 'v', 'e', 's', 32, 'F', 'U', 'L', 'L',
    32, 'A', 'C', 'C', 'E', 'S', 'S', 32, 't', 'o', 32, 'A', 'L', 'L',
    32, 'R', 'E', 'S', 'O', 'U', 'R', 'C', 'E', 'S', 10,
    /*  !--IF on_windows_32  VALUE=1                                         */
    0, 7, 2, 0, 0, 0, 10, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f105 NAME=L ... ort filenames?&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '1', '0', '5', 0, 'R', 'e',
    'j', 'e', 'c', 't', 32, 'u', 'n', 's', 'a', 'f', 'e', 32, 's', 'h',
    'o', 'r', 't', 32, 'f', 'i', 'l', 'e', 'n', 'a', 'm', 'e', 's', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD BOOLEAN f106 NAME=s ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '1', '0', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f107 NAME=L ... control panel?&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '1', '0', '7', 0, 'D', 'i',
    's', 'a', 'b', 'l', 'e', 32, 'W', 'i', 'n', 'd', 'o', 'w', 's', 32,
    'c', 'o', 'n', 't', 'r', 'o', 'l', 32, 'p', 'a', 'n', 'e', 'l', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD BOOLEAN f108 NAME=s ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '1', '0', '8', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f109 NAME=L ... der user name:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '1', '0', '9', 0, 'R', 'u',
    'n', 32, 'C', 'G', 'I', 's', 32, 'u', 'n', 'd', 'e', 'r', 32, 'u',
    's', 'e', 'r', 32, 'n', 'a', 'm', 'e', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD TEXTUAL f110 NAME=c ... 30 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 10, 0, 30, 'f', '1', '1', '0', 0, 0, 0,
    /*  !--FIELD TEXTUAL f111 NAME=L ... p;&nbsp;group:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '1', '1', '1', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'g', 'r', 'o',
    'u', 'p', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f112 NAME=c ... 30 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 10, 0, 30, 'f', '1', '1', '2', 0, 0, 0,
    /*  !--FIELD TEXTUAL f113 NAME=L ... nbsp;password:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '1', '1', '3', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'p', 'a', 's',
    's', 'w', 'o', 'r', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f114 NAME=c ... 30 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 2, 1, 0, 0, 10, 0, 30, 'f', '1', '1', '4', 0, 0, 0,
    /*  !--IF on_unix  VALUE=1                                               */
    0, 7, 2, 0, 1, 0, 12, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f115 NAME=L ...  safe user id?&nbsp;&nbsp;"         */
    0, 57, 10, 6, 1, 0, 0, '*', 0, '*', 'f', '1', '1', '5', 0, 'R', 'u',
    'n', 32, 'X', 'i', 't', 'a', 'm', 'i', 32, 'u', 'n', 'd', 'e', 'r',
    32, 's', 'a', 'f', 'e', 32, 'u', 's', 'e', 'r', 32, 'i', 'd', '?',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD BOOLEAN f116 NAME=s ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '1', '1', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 10, 224,
    /*  !--FIELD TEXTUAL f117 NAME=L ... mless user id:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '1', '1', '7', 0, 32, 32,
    'U', 's', 'i', 'n', 'g', 32, 'h', 'a', 'r', 'm', 'l', 'e', 's', 's',
    32, 'u', 's', 'e', 'r', 32, 'i', 'd', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 11, 'A',
    /*  !--FIELD TEXTUAL f118 NAME=s ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 30, 'f', '1', '1', '8', 0, 0, 0,
    /*  !--FIELD TEXTUAL f119 NAME=L ... bsp;and group:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '1', '1', '9', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'a', 'n', 'd', 32,
    'g', 'r', 'o', 'u', 'p', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD TEXTUAL f120 NAME=s ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 30, 'f', '1', '2', '0', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 11, 186,
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
    0, 4, 1, 0, 16, 209,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm07_fields [] = {
    { 0, 2702, 4 },                     /*  on_windows_32                   */
    { 6, 2734, 4 },                     /*  on_unix                         */
    { 12, 2839, 26 },                   /*  l_filename                      */
    { 40, 2944, 80 },                   /*  filename                        */
    { 122, 3134, 37 },                  /*  l_password_case                 */
    { 161, 3193, 1 },                   /*  password_case                   */
    { 164, 3224, 34 },                  /*  l_dirlist                       */
    { 200, 3280, 1 },                   /*  dirlist                         */
    { 203, 3311, 34 },                  /*  l_admin                         */
    { 239, 3367, 1 },                   /*  admin                           */
    { 242, 3399, 28 },                  /*  l_webmask                       */
    { 272, 3450, 80 },                  /*  webmask                         */
    { 354, 3502, 31 },                  /*  l_superuser                     */
    { 387, 3556, 20 },                  /*  superuser                       */
    { 409, 3634, 42 },                  /*  l_safepaths                     */
    { 453, 3699, 1 },                   /*  safepaths                       */
    { 456, 3731, 42 },                  /*  l_secure                        */
    { 500, 3796, 1 },                   /*  secure                          */
    { 503, 3828, 37 },                  /*  l_cgi_username                  */
    { 542, 3888, 30 },                  /*  cgi_username                    */
    { 574, 3905, 30 },                  /*  l_cgi_groupname                 */
    { 606, 3952, 30 },                  /*  cgi_groupname                   */
    { 638, 3969, 33 },                  /*  l_cgi_password                  */
    { 673, 4019, 30 },                  /*  cgi_password                    */
    { 705, 4057, 42 },                  /*  l_setuid                        */
    { 749, 4122, 1 },                   /*  setuid                          */
    { 752, 4154, 37 },                  /*  l_setuid_user                   */
    { 791, 4214, 30 },                  /*  setuid_user                     */
    { 823, 4231, 34 },                  /*  l_setuid_group                  */
    { 859, 4282, 30 },                  /*  setuid_group                    */
    { 891, 4317, 120 },                 /*  message_to_user                 */
    { 1013, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   on_windows_32_a      ;
    char   on_windows_32        [4 + 1];
    byte   on_unix_a            ;
    char   on_unix              [4 + 1];
    byte   l_filename_a         ;
    char   l_filename           [26 + 1];
    byte   filename_a           ;
    char   filename             [80 + 1];
    byte   l_password_case_a    ;
    char   l_password_case      [37 + 1];
    byte   password_case_a      ;
    char   password_case        [1 + 1];
    byte   l_dirlist_a          ;
    char   l_dirlist            [34 + 1];
    byte   dirlist_a            ;
    char   dirlist              [1 + 1];
    byte   l_admin_a            ;
    char   l_admin              [34 + 1];
    byte   admin_a              ;
    char   admin                [1 + 1];
    byte   l_webmask_a          ;
    char   l_webmask            [28 + 1];
    byte   webmask_a            ;
    char   webmask              [80 + 1];
    byte   l_superuser_a        ;
    char   l_superuser          [31 + 1];
    byte   superuser_a          ;
    char   superuser            [20 + 1];
    byte   l_safepaths_a        ;
    char   l_safepaths          [42 + 1];
    byte   safepaths_a          ;
    char   safepaths            [1 + 1];
    byte   l_secure_a           ;
    char   l_secure             [42 + 1];
    byte   secure_a             ;
    char   secure               [1 + 1];
    byte   l_cgi_username_a     ;
    char   l_cgi_username       [37 + 1];
    byte   cgi_username_a       ;
    char   cgi_username         [30 + 1];
    byte   l_cgi_groupname_a    ;
    char   l_cgi_groupname      [30 + 1];
    byte   cgi_groupname_a      ;
    char   cgi_groupname        [30 + 1];
    byte   l_cgi_password_a     ;
    char   l_cgi_password       [33 + 1];
    byte   cgi_password_a       ;
    char   cgi_password         [30 + 1];
    byte   l_setuid_a           ;
    char   l_setuid             [42 + 1];
    byte   setuid_a             ;
    char   setuid               [1 + 1];
    byte   l_setuid_user_a      ;
    char   l_setuid_user        [37 + 1];
    byte   setuid_user_a        ;
    char   setuid_user          [30 + 1];
    byte   l_setuid_group_a     ;
    char   l_setuid_group       [34 + 1];
    byte   setuid_group_a       ;
    char   setuid_group         [30 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back37_a;
    byte   save38_a;
    byte   default39_a;
    byte   undo40_a;
    byte   console41_a;
    byte   halt42_a;
    byte   restart43_a;
    byte   exit44_a;
    byte   passwords_a;
    byte   server_a;
    byte   vhosts_a;
    byte   cgi_a;
    byte   logging_a;
    byte   ftp_a;
    byte   define_a;
    } XIADM07_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm07 = {
    xiadm07_blocks,
    xiadm07_fields,
    132,                                /*  Number of blocks in form        */
    31,                                 /*  Number of fields in form        */
    15,                                 /*  Number of actions in form       */
    1013,                               /*  Size of fields                  */
    "xiadm07",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

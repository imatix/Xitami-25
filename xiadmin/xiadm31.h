/*---------------------------------------------------------------------------
 *  xiadm31.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM31__
#define __FORM_XIADM31__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM31_MAIN_CONFIG                 0
#define XIADM31_L_SUPERVISOR                1
#define XIADM31_SUPERVISOR                  2
#define XIADM31_L_CACHE_DEFAULTS            3
#define XIADM31_CACHE_DEFAULTS              4
#define XIADM31_L_HOSTNAME                  5
#define XIADM31_HOSTNAME                    6
#define XIADM31_L_PRIORITY                  7
#define XIADM31_PRIORITY                    8
#define XIADM31_L_PORTBASE                  9
#define XIADM31_PORTBASE                    10
#define XIADM31_L_BASE_HOST                 11
#define XIADM31_BASE_HOST                   12
#define XIADM31_L_IPADDRESS                 13
#define XIADM31_IPADDRESS                   14
#define XIADM31_L_TEMP_DIR                  15
#define XIADM31_TEMP_DIR                    16
#define XIADM31_L_DEBUG_DIR                 17
#define XIADM31_DEBUG_DIR                   18
#define XIADM31_L_LRWP_ENABLED              19
#define XIADM31_LRWP_ENABLED                20
#define XIADM31_L_LRWP_PORT                 21
#define XIADM31_LRWP_PORT                   22
#define XIADM31_L_LRWP_WEBMASK              23
#define XIADM31_LRWP_WEBMASK                24
#define XIADM31_L_PIPEDEF                   25
#define XIADM31_PIPEDEF                     26
#define XIADM31_L_SSL_ENABLED               27
#define XIADM31_SSL_ENABLED                 28
#define XIADM31_L_SSL_FILENAME              29
#define XIADM31_SSL_FILENAME                30
#define XIADM31_L_TEST_URI                  31
#define XIADM31_TEST_URI                    32
#define XIADM31_L_MAPPED_URI                33
#define XIADM31_MAPPED_URI                  34
#define XIADM31_MESSAGE_TO_USER             35

/*  This table contains each block in the form                               */

static byte xiadm31_blocks [] = {
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
    /*  !--ACTION back249  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '2',
    '4', '9', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save250  LABEL="/a ...  ROLLOVER="/admin/savea.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '2',
    '5', '0', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v',
    'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's',
    'a', 'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default251  LABEL= ... LLOVER="/admin/defaulta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '2', '5', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo252  LABEL="/a ...  ROLLOVER="/admin/undoa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '2',
    '5', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd',
    'o', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u',
    'n', 'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 73, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 'a', 'd', 'v',
    'a', 'n', 'c', 'e', 'd', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T', '=',
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ... ed Server Properties </FONT>        */
    0, 79, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'A', 'd', 'v', 'a', 'n', 'c', 'e', 'd', 32, 'S',
    'e', 'r', 'v', 'e', 'r', 32, 'P', 'r', 'o', 'p', 'e', 'r', 't', 'i',
    'e', 's', 32, '<', '/', 'F', 'O', 'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console253  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '2', '5', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt254  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '2',
    '5', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart255  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '2', '5', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit256  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '2',
    '5', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'e', 'x', 'i',
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
    /*  !--FIELD NUMERIC main_config SIZE=4 VALUE=1                          */
    0, 28, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'm', 'a', 'i', 'n',
    '_', 'c', 'o', 'n', 'f', 'i', 'g', 0, '1', 0, 0,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f463 NAME=L ... ervisor agent?&nbsp;&nbsp;"         */
    0, 51, 10, 6, 1, 0, 0, '$', 0, '$', 'f', '4', '6', '3', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 's', 'u', 'p', 'e', 'r', 'v', 'i', 's', 'o',
    'r', 32, 'a', 'g', 'e', 'n', 't', '?', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD BOOLEAN f464 NAME=s ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '6', '4', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f465 NAME=L ... default pages?&nbsp;&nbsp;"         */
    0, 47, 10, 6, 1, 0, 0, 32, 0, 32, 'f', '4', '6', '5', 0, 'C', 'a',
    'c', 'h', 'e', 32, 'd', 'e', 'f', 'a', 'u', 'l', 't', 32, 'p', 'a',
    'g', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD BOOLEAN f466 NAME=c ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '6', '6', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f467 NAME=L ... rect hostname:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '4', '6', '7', 0, 'D', 'e',
    'f', 'a', 'u', 'l', 't', 32, 'r', 'e', 'd', 'i', 'r', 'e', 'c', 't',
    32, 'h', 'o', 's', 't', 'n', 'a', 'm', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f468 NAME=h ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '4', '6', '8', 0, 0, 0,
    /*  !--IF main_config  VALUE=1                                           */
    0, 7, 2, 0, 0, 0, '?', 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f469 NAME=L ... r performance:&nbsp;&nbsp;"         */
    0, 46, 10, 6, 1, 0, 0, 31, 0, 31, 'f', '4', '6', '9', 0, 'S', 'e',
    'r', 'v', 'e', 'r', 32, 'p', 'e', 'r', 'f', 'o', 'r', 'm', 'a', 'n',
    'c', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's',
    'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD RADIO f470 NAME=pri ... " 2="Background" 3="Turbo!"         */
    0, 55, 17, 0, 1, 0, 3, 0, 'f', '4', '7', '0', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    'N', 'o', 'r', 'm', 'a', 'l', 0, 'B', 'a', 'c', 'k', 'g', 'r', 'o',
    'u', 'n', 'd', 0, 'T', 'u', 'r', 'b', 'o', '!', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f471 NAME=L ... "IP port base:&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 25, 0, 25, 'f', '4', '7', '1', 0, 'I', 'P',
    32, 'p', 'o', 'r', 't', 32, 'b', 'a', 's', 'e', ':', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD NUMERIC f472 NAME=p ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '4', '7', '2',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f473 NAME=L ... t config file:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '4', '7', '3', 0, 'B', 'a',
    's', 'e', 32, 'h', 'o', 's', 't', 32, 'c', 'o', 'n', 'f', 'i', 'g',
    32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f474 NAME=b ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '4', '7', '4', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f475 NAME=L ... er IP address:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '4', '7', '5', 0, 'S', 'e',
    'r', 'v', 'e', 'r', 32, 'I', 'P', 32, 'a', 'd', 'd', 'r', 'e', 's',
    's', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD SELECT f476 NAME=ip ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '4', '7', '6', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f477 NAME=L ... or temp files:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '4', '7', '7', 0, 'D', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'f', 'o', 'r', 32, 't', 'e',
    'm', 'p', 32, 'f', 'i', 'l', 'e', 's', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f478 NAME=t ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'd', 'f', '4', '7', '8', 0, 0, 0,
    /*  Can be an environment variable                                       */
    0, 32, 0, 'C', 'a', 'n', 32, 'b', 'e', 32, 'a', 'n', 32, 'e', 'n',
    'v', 'i', 'r', 'o', 'n', 'm', 'e', 'n', 't', 32, 'v', 'a', 'r', 'i',
    'a', 'b', 'l', 'e', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f479 NAME=L ... r debug files:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '4', '7', '9', 0, 'D', 'i',
    'r', 'e', 'c', 't', 'o', 'r', 'y', 32, 'f', 'o', 'r', 32, 'd', 'e',
    'b', 'u', 'g', 32, 'f', 'i', 'l', 'e', 's', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f480 NAME=d ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'd', 'f', '4', '8', '0', 0, 0, 0,
    /*  Can be an environment variable                                       */
    0, 4, 1, 0, 13, '/',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f481 NAME=L ... LRWP protocol?&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '4', '8', '1', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'L', 'R', 'W', 'P', 32, 'p', 'r', 'o', 't',
    'o', 'c', 'o', 'l', '?', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD BOOLEAN f482 NAME=l ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '8', '2', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f483 NAME=L ... nnection port:&nbsp;&nbsp;"         */
    0, 48, 10, 6, 1, 0, 0, '!', 0, '!', 'f', '4', '8', '3', 0, 'L', 'R',
    'W', 'P', 32, 'c', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', 32,
    'p', 'o', 'r', 't', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD NUMERIC f484 NAME=l ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '4', '8', '4',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f485 NAME=L ... "LRWP webmask:&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 25, 0, 25, 'f', '4', '8', '5', 0, 'L', 'R',
    'W', 'P', 32, 'w', 'e', 'b', 'm', 'a', 's', 'k', ':', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f486 NAME=l ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 20, 0, 'P', 'f', '4', '8', '6', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f487 NAME=L ... e definitions:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '4', '8', '7', 0, 'T', 'h',
    'r', 'o', 't', 't', 'l', 'e', 32, 'p', 'i', 'p', 'e', 32, 'd', 'e',
    'f', 'i', 'n', 'i', 't', 'i', 'o', 'n', 's', ':', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f488 NAME=p ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '4', '8', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f489 NAME=L ... SL interface?:&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '4', '8', '9', 0, 'E', 'n',
    'a', 'b', 'l', 'e', 32, 'S', 'S', 'L', 32, 'i', 'n', 't', 'e', 'r',
    'f', 'a', 'c', 'e', '?', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD BOOLEAN f490 NAME=s ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '9', '0', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  Xitami/Pro only                                                      */
    0, 17, 0, 'X', 'i', 't', 'a', 'm', 'i', '/', 'P', 'r', 'o', 32, 'o',
    'n', 'l', 'y', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f491 NAME=L ... L config file:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '4', '9', '1', 0, 'S', 'S',
    'L', 32, 'c', 'o', 'n', 'f', 'i', 'g', 32, 'f', 'i', 'l', 'e', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f492 NAME=s ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 30, 0, 'P', 'f', '4', '9', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 56, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '9', '9', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L',
    'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P',
    32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'b', 'o', 'd', 'y', '>',
    10,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f493 NAME=L ... t URI mapping:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '4', '9', '3', 0, 'T', 'e',
    's', 't', 32, 'U', 'R', 'I', 32, 'm', 'a', 'p', 'p', 'i', 'n', 'g',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f494 NAME=t ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '2', 0, '2', 'f', '4', '9', '4', 0, 0, 0,
    /*  !--ACTION test  LABEL="Test" ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 26, 20, 0, 1, (byte) ((word) test_event / 256), (byte) ((word)
    test_event & 255), 0, 10, 0, 0, 0, 0, 0, 't', 'e', 's', 't', 0, 'T',
    'e', 's', 't', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 209,
    /*  !--FIELD TEXTUAL f495 NAME=L ... lt of mapping:&nbsp;&nbsp;"         */
    0, 45, 10, 6, 1, 0, 0, 30, 0, 30, 'f', '4', '9', '5', 0, 'R', 'e',
    's', 'u', 'l', 't', 32, 'o', 'f', 32, 'm', 'a', 'p', 'p', 'i', 'n',
    'g', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '=',
    /*  !--FIELD TEXTUAL f496 NAME=m ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 6, 1, 0, 0, '2', 0, '2', 'f', '4', '9', '6', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 144,
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
    0, 4, 1, 0, 16, 6,
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
    0, 4, 1, 0, 16, 211,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm31_fields [] = {
    { 0, 2459, 4 },                     /*  main_config                     */
    { 6, 2568, 36 },                    /*  l_supervisor                    */
    { 44, 2684, 1 },                    /*  supervisor                      */
    { 47, 2724, 32 },                   /*  l_cache_defaults                */
    { 81, 2779, 1 },                    /*  cache_defaults                  */
    { 84, 2811, 38 },                   /*  l_hostname                      */
    { 124, 2872, 80 },                  /*  hostname                        */
    { 206, 2910, 31 },                  /*  l_priority                      */
    { 239, 2964, 3 },                   /*  priority                        */
    { 244, 3033, 25 },                  /*  l_portbase                      */
    { 271, 3081, 5 },                   /*  portbase                        */
    { 278, 3115, 34 },                  /*  l_base_host                     */
    { 314, 3172, 80 },                  /*  base_host                       */
    { 396, 3201, 30 },                  /*  l_ipaddress                     */
    { 428, 3254, 3 },                   /*  ipaddress                       */
    { 433, 3298, 37 },                  /*  l_temp_dir                      */
    { 472, 3358, 100 },                 /*  temp_dir                        */
    { 574, 3421, 38 },                  /*  l_debug_dir                     */
    { 614, 3482, 100 },                 /*  debug_dir                       */
    { 716, 3517, 33 },                  /*  l_lrwp_enabled                  */
    { 751, 3573, 1 },                   /*  lrwp_enabled                    */
    { 754, 3605, 33 },                  /*  l_lrwp_port                     */
    { 789, 3661, 5 },                   /*  lrwp_port                       */
    { 796, 3695, 25 },                  /*  l_lrwp_webmask                  */
    { 823, 3743, 80 },                  /*  lrwp_webmask                    */
    { 905, 3772, 38 },                  /*  l_pipedef                       */
    { 945, 3833, 80 },                  /*  pipedef                         */
    { 1027, 3862, 34 },                 /*  l_ssl_enabled                   */
    { 1063, 3919, 1 },                  /*  ssl_enabled                     */
    { 1066, 3970, 28 },                 /*  l_ssl_filename                  */
    { 1096, 4021, 80 },                 /*  ssl_filename                    */
    { 1178, 4122, 29 },                 /*  l_test_uri                      */
    { 1209, 4174, 50 },                 /*  test_uri                        */
    { 1261, 4231, 30 },                 /*  l_mapped_uri                    */
    { 1293, 4284, 50 },                 /*  mapped_uri                      */
    { 1345, 4319, 120 },                /*  message_to_user                 */
    { 1467, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   main_config_a        ;
    char   main_config          [4 + 1];
    byte   l_supervisor_a       ;
    char   l_supervisor         [36 + 1];
    byte   supervisor_a         ;
    char   supervisor           [1 + 1];
    byte   l_cache_defaults_a   ;
    char   l_cache_defaults     [32 + 1];
    byte   cache_defaults_a     ;
    char   cache_defaults       [1 + 1];
    byte   l_hostname_a         ;
    char   l_hostname           [38 + 1];
    byte   hostname_a           ;
    char   hostname             [80 + 1];
    byte   l_priority_a         ;
    char   l_priority           [31 + 1];
    byte   priority_a           ;
    char   priority             [3 + 1];
    byte   l_portbase_a         ;
    char   l_portbase           [25 + 1];
    byte   portbase_a           ;
    char   portbase             [5 + 1];
    byte   l_base_host_a        ;
    char   l_base_host          [34 + 1];
    byte   base_host_a          ;
    char   base_host            [80 + 1];
    byte   l_ipaddress_a        ;
    char   l_ipaddress          [30 + 1];
    byte   ipaddress_a          ;
    char   ipaddress            [3 + 1];
    byte   l_temp_dir_a         ;
    char   l_temp_dir           [37 + 1];
    byte   temp_dir_a           ;
    char   temp_dir             [100 + 1];
    byte   l_debug_dir_a        ;
    char   l_debug_dir          [38 + 1];
    byte   debug_dir_a          ;
    char   debug_dir            [100 + 1];
    byte   l_lrwp_enabled_a     ;
    char   l_lrwp_enabled       [33 + 1];
    byte   lrwp_enabled_a       ;
    char   lrwp_enabled         [1 + 1];
    byte   l_lrwp_port_a        ;
    char   l_lrwp_port          [33 + 1];
    byte   lrwp_port_a          ;
    char   lrwp_port            [5 + 1];
    byte   l_lrwp_webmask_a     ;
    char   l_lrwp_webmask       [25 + 1];
    byte   lrwp_webmask_a       ;
    char   lrwp_webmask         [80 + 1];
    byte   l_pipedef_a          ;
    char   l_pipedef            [38 + 1];
    byte   pipedef_a            ;
    char   pipedef              [80 + 1];
    byte   l_ssl_enabled_a      ;
    char   l_ssl_enabled        [34 + 1];
    byte   ssl_enabled_a        ;
    char   ssl_enabled          [1 + 1];
    byte   l_ssl_filename_a     ;
    char   l_ssl_filename       [28 + 1];
    byte   ssl_filename_a       ;
    char   ssl_filename         [80 + 1];
    byte   l_test_uri_a         ;
    char   l_test_uri           [29 + 1];
    byte   test_uri_a           ;
    char   test_uri             [50 + 1];
    byte   l_mapped_uri_a       ;
    char   l_mapped_uri         [30 + 1];
    byte   mapped_uri_a         ;
    char   mapped_uri           [50 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back249_a;
    byte   save250_a;
    byte   default251_a;
    byte   undo252_a;
    byte   console253_a;
    byte   halt254_a;
    byte   restart255_a;
    byte   exit256_a;
    byte   ok_a;
    byte   cancel_a;
    byte   test_a;
    } XIADM31_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm31 = {
    xiadm31_blocks,
    xiadm31_fields,
    148,                                /*  Number of blocks in form        */
    36,                                 /*  Number of fields in form        */
    11,                                 /*  Number of actions in form       */
    1467,                               /*  Size of fields                  */
    "xiadm31",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

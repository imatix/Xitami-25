/*---------------------------------------------------------------------------
 *  xiadm29.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:24 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_XIADM29__
#define __FORM_XIADM29__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define XIADM29_RICH_LOGGING                0
#define XIADM29_L_LOG_TYPE                  1
#define XIADM29_LOG_TYPE                    2
#define XIADM29_L_ENABLED                   3
#define XIADM29_ENABLED                     4
#define XIADM29_L_FILENAME                  5
#define XIADM29_FILENAME                    6
#define XIADM29_L_INC_LOCAL                 7
#define XIADM29_INC_LOCAL                   8
#define XIADM29_L_TRANSLATE                 9
#define XIADM29_TRANSLATE                   10
#define XIADM29_L_FORMAT                    11
#define XIADM29_FORMAT                      12
#define XIADM29_L_CUSTOM                    13
#define XIADM29_CUSTOM                      14
#define XIADM29_L_HEADER                    15
#define XIADM29_HEADER                      16
#define XIADM29_L_CYCLE                     17
#define XIADM29_CYCLE                       18
#define XIADM29_L_CYCLE_TIME                19
#define XIADM29_CYCLE_TIME                  20
#define XIADM29_L_CYCLE_DAY                 21
#define XIADM29_CYCLE_DAY                   22
#define XIADM29_L_CYCLE_SIZE                23
#define XIADM29_CYCLE_SIZE                  24
#define XIADM29_L_CYCLE_LINES               25
#define XIADM29_CYCLE_LINES                 26
#define XIADM29_L_CYCLE_HOW                 27
#define XIADM29_CYCLE_HOW                   28
#define XIADM29_L_CYCLE_ARG                 29
#define XIADM29_CYCLE_ARG                   30
#define XIADM29_L_CYCLE_DATA                31
#define XIADM29_MESSAGE_TO_USER             32

/*  This table contains each block in the form                               */

static byte xiadm29_blocks [] = {
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
    /*  !--ACTION back231  LABEL="/a ...  ROLLOVER="/admin/backa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 0, 0, 0, 39, 0, '(', 'b', 'a', 'c', 'k', '2',
    '3', '1', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'b', 'a', 'c',
    'k', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'b',
    'a', 'c', 'k', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION save232  LABEL="/a ...  ROLLOVER="/admin/savea.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) save_event / 256), (byte) ((word)
    save_event & 255), 0, 1, 0, 0, 39, 0, '(', 's', 'a', 'v', 'e', '2',
    '3', '2', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 's', 'a', 'v',
    'e', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 's',
    'a', 'v', 'e', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION default233  LABEL= ... LLOVER="/admin/defaulta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) default_event / 256), (byte) ((word)
    default_event & 255), 0, 2, 0, 0, 39, 0, '(', 'd', 'e', 'f', 'a',
    'u', 'l', 't', '2', '3', '3', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'd', 'e', 'f', 'a', 'u', 'l', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'd', 'e', 'f', 'a', 'u', 'l', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION undo234  LABEL="/a ...  ROLLOVER="/admin/undoa.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) undo_event / 256), (byte) ((word)
    undo_event & 255), 0, 3, 0, 0, 39, 0, '(', 'u', 'n', 'd', 'o', '2',
    '3', '4', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'u', 'n', 'd',
    'o', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'u',
    'n', 'd', 'o', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  <A HREF="/xitami/index4.htm# ... " TARGET="Help" TITLE="Help"        */
    0, 74, 0, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"', '/', 'x', 'i',
    't', 'a', 'm', 'i', '/', 'i', 'n', 'd', 'e', 'x', '4', '.', 'h',
    't', 'm', '#', 'c', 'o', 'n', 'f', 'i', 'g', '_', 's', 'e', 'r',
    'v', 'e', 'r', 'l', 'o', 'g', '"', 32, 'T', 'A', 'R', 'G', 'E', 'T',
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
    /*  <TD ALIGN=CENTER><FONT SIZE= ...  Log File Properties </FONT>        */
    0, 72, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', '>', '<', 'F', 'O', 'N', 'T', 32, 'S', 'I', 'Z',
    'E', '=', '+', '1', '>', '#', '(', 'c', 'o', 'n', 'f', 'i', 'g',
    ')', 32, 45, 32, 'L', 'o', 'g', 32, 'F', 'i', 'l', 'e', 32, 'P',
    'r', 'o', 'p', 'e', 'r', 't', 'i', 'e', 's', 32, '<', '/', 'F', 'O',
    'N', 'T', '>', 10,
    /*  <TD ALIGN=RIGHT>                                                     */
    0, 18, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'R', 'I',
    'G', 'H', 'T', '>', 10,
    /*  <IMG SRC="/admin/$left.gif" BORDER=0 ALIGN=MIDDLE>                   */
    0, 4, 1, 0, 5, '0',
    /*  !--ACTION console235  LABEL= ... LLOVER="/admin/consolea.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) console_event / 256), (byte) ((word)
    console_event & 255), 0, 4, 0, 0, 39, 0, '(', 'c', 'o', 'n', 's',
    'o', 'l', 'e', '2', '3', '5', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'c', 'o', 'n', 's', 'o', 'l', 'e', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'c', 'o', 'n', 's', 'o', 'l', 'e',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION halt236  LABEL="/a ...  ROLLOVER="/admin/halta.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) halt_event / 256), (byte) ((word)
    halt_event & 255), 0, 5, 0, 0, 39, 0, '(', 'h', 'a', 'l', 't', '2',
    '3', '6', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', '$', 'h', 'a', 'l',
    't', '.', 'g', 'i', 'f', 0, '/', 'a', 'd', 'm', 'i', 'n', '/', 'h',
    'a', 'l', 't', 'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION restart237  LABEL= ... LLOVER="/admin/restarta.gif"        */
    0, 66, 20, 2, 1, (byte) ((word) restart_event / 256), (byte) ((word)
    restart_event & 255), 0, 6, 0, 0, 39, 0, '(', 'r', 'e', 's', 't',
    'a', 'r', 't', '2', '3', '7', 0, '/', 'a', 'd', 'm', 'i', 'n', '/',
    '$', 'r', 'e', 's', 't', 'a', 'r', 't', '.', 'g', 'i', 'f', 0, '/',
    'a', 'd', 'm', 'i', 'n', '/', 'r', 'e', 's', 't', 'a', 'r', 't',
    'a', '.', 'g', 'i', 'f', 0, 0, 0, 0,
    /*  !--ACTION exit238  LABEL="/a ...  ROLLOVER="/admin/exita.gif"        */
    0, 57, 20, 2, 1, (byte) ((word) exit_event / 256), (byte) ((word)
    exit_event & 255), 0, 7, 0, 0, 39, 0, '(', 'e', 'x', 'i', 't', '2',
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
    save_event & 255), 0, 8, 0, 0, 0, 0, 0, 'o', 'k', 0, 'O', 'k', 0, 0,
    0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) back_event / 256), (byte) ((word)
    back_event & 255), 0, 9, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0, 0, 0, 0, 0,
    /*  </FONT><HR>                                                          */
    0, 13, 0, '<', '/', 'F', 'O', 'N', 'T', '>', '<', 'H', 'R', '>', 10,
    /*  !--FIELD NUMERIC rich_logging SIZE=4 VALUE=1                         */
    0, 29, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'r', 'i', 'c', 'h',
    '_', 'l', 'o', 'g', 'g', 'i', 'n', 'g', 0, '1', 0, 0,
    /*  <TABLE WIDTH="100%">                                                 */
    0, 22, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f420 NAME=L ... e of log file:&nbsp;&nbsp;"         */
    0, 44, 10, 6, 1, 0, 0, 29, 0, 29, 'f', '4', '2', '0', 0, 'T', 'y',
    'p', 'e', 32, 'o', 'f', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e',
    ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 61, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '"', '8',
    '0', '%', '"', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v',
    'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f421 NAME=l ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 7, 1, 0, 0, '(', 0, '(', 'f', '4', '2', '1', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f422 NAME=L ... gging enabled:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '4', '2', '2', 0, 'L', 'o',
    'g', 'g', 'i', 'n', 'g', 32, 'e', 'n', 'a', 'b', 'l', 'e', 'd', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD BOOLEAN f423 NAME=e ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '2', '3', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f424 NAME=L ... Log file name:&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '4', '2', '4', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'n', 'a', 'm', 'e', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD TEXTUAL f425 NAME=f ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '4', '2', '5', 0, 0, 0,
    /*  !--IF rich_logging  VALUE=1                                          */
    0, 7, 2, 0, 0, 0, 21, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f426 NAME=L ... ocal requests?&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '4', '2', '6', 0, 'I', 'n',
    'c', 'l', 'u', 'd', 'e', 32, 'l', 'o', 'c', 'a', 'l', 32, 'r', 'e',
    'q', 'u', 'e', 's', 't', 's', '?', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD BOOLEAN f427 NAME=i ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '2', '7', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f428 NAME=L ...  IP addresses?&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '4', '2', '8', 0, 'T', 'r',
    'a', 'n', 's', 'l', 'a', 't', 'e', 32, 'I', 'P', 32, 'a', 'd', 'd',
    'r', 'e', 's', 's', 'e', 's', '?', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD BOOLEAN f429 NAME=t ... es FALSE=no ATTR="" VALUE=0         */
    0, 18, 15, 0, 1, 'f', '4', '2', '9', 0, '0', 0, 'y', 'e', 's', 0,
    'n', 'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f430 NAME=L ... g file format:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '4', '3', '0', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'f', 'o', 'r', 'm', 'a', 't', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD SELECT f431 NAME=fo ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '4', '3', '1', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  !--ACTION show  LABEL="Show" ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 26, 20, 0, 1, (byte) ((word) show_event / 256), (byte) ((word)
    show_event & 255), 0, 10, 0, 0, 0, 0, 0, 's', 'h', 'o', 'w', 0, 'S',
    'h', 'o', 'w', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f432 NAME=L ... format string:&nbsp;&nbsp;"         */
    0, 50, 10, 6, 1, 0, 0, '#', 0, '#', 'f', '4', '3', '2', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'f', 'o', 'r', 'm', 'a', 't', 32,
    's', 't', 'r', 'i', 'n', 'g', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD TEXTBOX f433 NAME=c ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 14, 0, 1, 7, 'F', 0, 3, 232, 'f', '4', '3', '3', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f434 NAME=L ... g file header:&nbsp;&nbsp;"         */
    0, 43, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '4', '3', '4', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'h', 'e', 'a', 'd', 'e', 'r', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD TEXTBOX f435 NAME=h ... 00 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 14, 0, 1, 4, 'F', 0, 1, 244, 'f', '4', '3', '5', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f436 NAME=L ... ycle log file:&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '4', '3', '6', 0, 'C', 'y',
    'c', 'l', 'e', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD SELECT f437 NAME=cy ... PE=dynamic 0="No selection"         */
    0, 30, 16, 0, 1, 0, 0, 0, 'f', '4', '3', '7', 0, '0', 0, 'n', 'o',
    0, 0, 'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f438 NAME=L ...  time (HH:MM):&nbsp;&nbsp;"         */
    0, 49, 10, 6, 1, 0, 0, '"', 0, '"', 'f', '4', '3', '8', 0, 'C', 'y',
    'c', 'l', 'e', 32, 'a', 't', 32, 't', 'i', 'm', 'e', 32, '(', 'H',
    'H', ':', 'M', 'M', ')', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD TEXTUAL f439 NAME=c ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '4', '3', '9', 0, 0, 0,
    /*  !--FIELD TEXTUAL f440 NAME=L ... week or month:&nbsp;&nbsp;"         */
    0, 63, 10, 6, 1, 0, 0, '0', 0, '0', 'f', '4', '4', '0', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'o', 'n', 32, 'd',
    'a', 'y', 32, 'o', 'f', 32, 'w', 'e', 'e', 'k', 32, 'o', 'r', 32,
    'm', 'o', 'n', 't', 'h', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f441 NAME=c ... ZE=3 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '4', '4', '1',
    0, 0, 0,
    /*  0=Sunday, 1=Monday... or 0-31                                        */
    0, 31, 0, '0', '=', 'S', 'u', 'n', 'd', 'a', 'y', ',', 32, '1', '=',
    'M', 'o', 'n', 'd', 'a', 'y', '.', '.', '.', 32, 'o', 'r', 32, '0',
    45, '3', '1', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f442 NAME=L ...  for log file:&nbsp;&nbsp;"         */
    0, 52, 10, 6, 1, 0, 0, '%', 0, '%', 'f', '4', '4', '2', 0, 'M', 'a',
    'x', '.', 32, 'k', 'b', 'y', 't', 'e', 's', 32, 'f', 'o', 'r', 32,
    'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD NUMERIC f443 NAME=c ... ZE=6 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 6, 0, 6, 0, 0, 0, 0, 0, 0, 'f', '4', '4', '3',
    0, 0, 0,
    /*  !--FIELD TEXTUAL f444 NAME=L ...  for log file:&nbsp;&nbsp;"         */
    0, 63, 10, 6, 1, 0, 0, '0', 0, '0', 'f', '4', '4', '4', 0, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'm', 'a', 'x',
    '.', 32, 'l', 'i', 'n', 'e', 's', 32, 'f', 'o', 'r', 32, 'l', 'o',
    'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f445 NAME=c ... ZE=9 MAX=? ATTR="" VALUE=""         */
    0, 20, 11, 0, 1, 0, 9, 0, 9, 0, 0, 0, 0, 0, 0, 'f', '4', '4', '5',
    0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f446 NAME=L ...  old log file:&nbsp;&nbsp;"         */
    0, 53, 10, 6, 1, 0, 0, '&', 0, '&', 'f', '4', '4', '6', 0, 'H', 'o',
    'w', 32, 't', 'o', 32, 'c', 'y', 'c', 'l', 'e', 32, 'o', 'l', 'd',
    32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD SELECT f447 NAME=cy ... ng command specified below"         */
    0, 214, 16, 0, 1, 0, 4, 0, 'f', '4', '4', '7', 0, '0', 0, 'n', 'o',
    0, 0, 'R', 'e', 'n', 'a', 'm', 'e', 32, 't', 'o', 32, 'p', 'a', 't',
    'h', '/', 'f', 'i', 'l', 'e', 'n', 'a', 'm', 'e', 32, 'a', 's', 32,
    's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o',
    'w', 0, 'D', 'e', 'l', 'e', 't', 'e', 32, 'o', 'l', 'd', 32, 'l',
    'o', 'g', 32, 'f', 'i', 'l', 'e', 0, 'M', 'o', 'v', 'e', 32, 'l',
    'o', 'g', 32, 'f', 'i', 'l', 'e', 32, 't', 'o', 32, 'p', 'a', 't',
    'h', 32, 's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e',
    'l', 'o', 'w', 0, 'A', 'p', 'p', 'e', 'n', 'd', 32, 'l', 'o', 'g',
    32, 'f', 'i', 'l', 'e', 32, 't', 'o', 32, 'p', 'a', 't', 'h', '/',
    'f', 'i', 'l', 'e', 'n', 'a', 'm', 'e', 32, 's', 'p', 'e', 'c', 'i',
    'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o', 'w', 0, 'P', 'r', 'o',
    'c', 'e', 's', 's', 32, 'l', 'o', 'g', 32, 'f', 'i', 'l', 'e', 32,
    'u', 's', 'i', 'n', 'g', 32, 'c', 'o', 'm', 'm', 'a', 'n', 'd', 32,
    's', 'p', 'e', 'c', 'i', 'f', 'i', 'e', 'd', 32, 'b', 'e', 'l', 'o',
    'w', 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f448 NAME=L ... ycle operation&nbsp;&nbsp;"         */
    0, 55, 10, 6, 1, 0, 0, '(', 0, '(', 'f', '4', '4', '8', 0, 'A', 'r',
    'g', 'u', 'm', 'e', 'n', 't', 32, 'f', 'o', 'r', 32, 'c', 'y', 'c',
    'l', 'e', 32, 'o', 'p', 'e', 'r', 'a', 't', 'i', 'o', 'n', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--FIELD TEXTUAL f449 NAME=c ... 80 UPPER=0 ATTR="" VALUE=""         */
    0, 15, 10, 0, 1, 0, 0, '(', 0, 'P', 'f', '4', '4', '9', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 9, 204,
    /*  !--FIELD TEXTUAL f450 NAME=L ... Log file data:&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '4', '5', '0', 0, 'L', 'o',
    'g', 32, 'f', 'i', 'l', 'e', 32, 'd', 'a', 't', 'a', ':', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH=""80%"" CLASS=tdvalue>          */
    0, 4, 1, 0, 10, '1',
    /*  !--ACTION cycle_data239  LAB ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 40, 20, 0, 1, (byte) ((word) cycle_event / 256), (byte) ((word)
    cycle_event & 255), 0, 11, 0, 0, 0, 0, 0, 'c', 'y', 'c', 'l', 'e',
    '_', 'd', 'a', 't', 'a', '2', '3', '9', 0, 'C', 'y', 'c', 'l', 'e',
    32, 'n', 'o', 'w', 0, 0, 0, 0, 0,
    /*  !--ACTION clear_data240  LAB ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 43, 20, 0, 1, (byte) ((word) clear_event / 256), (byte) ((word)
    clear_event & 255), 0, 12, 0, 0, 0, 0, 0, 'c', 'l', 'e', 'a', 'r',
    '_', 'd', 'a', 't', 'a', '2', '4', '0', 0, 'W', 'i', 'p', 'e', 32,
    'l', 'o', 'g', 'f', 'i', 'l', 'e', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 10, 129,
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
    0, 4, 1, 0, 17, 1,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN xiadm29_fields [] = {
    { 0, 2453, 4 },                     /*  rich_logging                    */
    { 6, 2563, 29 },                    /*  l_log_type                      */
    { 37, 2672, 40 },                   /*  log_type                        */
    { 79, 2709, 28 },                   /*  l_enabled                       */
    { 109, 2760, 1 },                   /*  enabled                         */
    { 112, 2792, 26 },                  /*  l_filename                      */
    { 140, 2841, 80 },                  /*  filename                        */
    { 222, 2879, 35 },                  /*  l_inc_local                     */
    { 259, 2937, 1 },                   /*  inc_local                       */
    { 262, 2969, 35 },                  /*  l_translate                     */
    { 299, 3027, 1 },                   /*  translate                       */
    { 302, 3059, 28 },                  /*  l_format                        */
    { 332, 3110, 3 },                   /*  format                          */
    { 337, 3182, 35 },                  /*  l_custom                        */
    { 374, 3240, 1000 },                /*  custom                          */
    { 1376, 3269, 28 },                 /*  l_header                        */
    { 1406, 3320, 500 },                /*  header                          */
    { 1908, 3349, 27 },                 /*  l_cycle                         */
    { 1937, 3399, 3 },                  /*  cycle                           */
    { 1942, 3443, 34 },                 /*  l_cycle_time                    */
    { 1978, 3500, 5 },                  /*  cycle_time                      */
    { 1985, 3517, 48 },                 /*  l_cycle_day                     */
    { 2035, 3582, 3 },                  /*  cycle_day                       */
    { 2040, 3649, 37 },                 /*  l_cycle_size                    */
    { 2079, 3709, 6 },                  /*  cycle_size                      */
    { 2087, 3731, 48 },                 /*  l_cycle_lines                   */
    { 2137, 3796, 9 },                  /*  cycle_lines                     */
    { 2148, 3830, 38 },                 /*  l_cycle_how                     */
    { 2188, 3891, 3 },                  /*  cycle_how                       */
    { 2193, 4119, 40 },                 /*  l_cycle_arg                     */
    { 2235, 4182, 80 },                 /*  cycle_arg                       */
    { 2317, 4211, 26 },                 /*  l_cycle_data                    */
    { 2345, 4365, 120 },                /*  message_to_user                 */
    { 2467, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   rich_logging_a       ;
    char   rich_logging         [4 + 1];
    byte   l_log_type_a         ;
    char   l_log_type           [29 + 1];
    byte   log_type_a           ;
    char   log_type             [40 + 1];
    byte   l_enabled_a          ;
    char   l_enabled            [28 + 1];
    byte   enabled_a            ;
    char   enabled              [1 + 1];
    byte   l_filename_a         ;
    char   l_filename           [26 + 1];
    byte   filename_a           ;
    char   filename             [80 + 1];
    byte   l_inc_local_a        ;
    char   l_inc_local          [35 + 1];
    byte   inc_local_a          ;
    char   inc_local            [1 + 1];
    byte   l_translate_a        ;
    char   l_translate          [35 + 1];
    byte   translate_a          ;
    char   translate            [1 + 1];
    byte   l_format_a           ;
    char   l_format             [28 + 1];
    byte   format_a             ;
    char   format               [3 + 1];
    byte   l_custom_a           ;
    char   l_custom             [35 + 1];
    byte   custom_a             ;
    char   custom               [1000 + 1];
    byte   l_header_a           ;
    char   l_header             [28 + 1];
    byte   header_a             ;
    char   header               [500 + 1];
    byte   l_cycle_a            ;
    char   l_cycle              [27 + 1];
    byte   cycle_a              ;
    char   cycle                [3 + 1];
    byte   l_cycle_time_a       ;
    char   l_cycle_time         [34 + 1];
    byte   cycle_time_a         ;
    char   cycle_time           [5 + 1];
    byte   l_cycle_day_a        ;
    char   l_cycle_day          [48 + 1];
    byte   cycle_day_a          ;
    char   cycle_day            [3 + 1];
    byte   l_cycle_size_a       ;
    char   l_cycle_size         [37 + 1];
    byte   cycle_size_a         ;
    char   cycle_size           [6 + 1];
    byte   l_cycle_lines_a      ;
    char   l_cycle_lines        [48 + 1];
    byte   cycle_lines_a        ;
    char   cycle_lines          [9 + 1];
    byte   l_cycle_how_a        ;
    char   l_cycle_how          [38 + 1];
    byte   cycle_how_a          ;
    char   cycle_how            [3 + 1];
    byte   l_cycle_arg_a        ;
    char   l_cycle_arg          [40 + 1];
    byte   cycle_arg_a          ;
    char   cycle_arg            [80 + 1];
    byte   l_cycle_data_a       ;
    char   l_cycle_data         [26 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   back231_a;
    byte   save232_a;
    byte   default233_a;
    byte   undo234_a;
    byte   console235_a;
    byte   halt236_a;
    byte   restart237_a;
    byte   exit238_a;
    byte   ok_a;
    byte   cancel_a;
    byte   show_a;
    byte   cycle_data239_a;
    byte   clear_data240_a;
    } XIADM29_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_xiadm29 = {
    xiadm29_blocks,
    xiadm29_fields,
    133,                                /*  Number of blocks in form        */
    33,                                 /*  Number of fields in form        */
    13,                                 /*  Number of actions in form       */
    2467,                               /*  Size of fields                  */
    "xiadm29",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

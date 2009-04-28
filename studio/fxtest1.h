/*---------------------------------------------------------------------------
 *  fxtest1.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:22 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_FXTEST1__
#define __FORM_FXTEST1__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define HOTELS_MAX                          5
#define FXTEST1_L_COUNTER                   0
#define FXTEST1_COUNTER                     1
#define FXTEST1_L_BACK_USED                 2
#define FXTEST1_BACK_USED                   3
#define FXTEST1_L_MONEY                     4
#define FXTEST1_MONEY                       5
#define FXTEST1_L_EVENT                     6
#define FXTEST1_EVENT                       7
#define FXTEST1_L_CLICK_FIELD               8
#define FXTEST1_CLICK_FIELD                 9
#define FXTEST1_L_CLICK_INDEX               10
#define FXTEST1_CLICK_INDEX                 11
#define FXTEST1_L_IMAGE_X                   12
#define FXTEST1_IMAGE_X                     13
#define FXTEST1_L_IMAGE_Y                   14
#define FXTEST1_IMAGE_Y                     15
#define FXTEST1_L_SHOW_SSL                  16
#define FXTEST1_SHOW_SSL                    17
#define FXTEST1_L_NONAME1                   18
#define FXTEST1_L_NONAME2                   19
#define FXTEST1_L_PARAMS                    20
#define FXTEST1_PARAMS                      21
#define FXTEST1_L_NONAME3                   22
#define FXTEST1_L_NONAME4                   23
#define FXTEST1_L_NONAME5                   24
#define FXTEST1_L_NONAME6                   25
#define FXTEST1_L_PARAMS1                   26
#define FXTEST1_PARAMS1                     27
#define FXTEST1_L_NONAME7                   28
#define FXTEST1_L_NONAME8                   29
#define FXTEST1_CLICK1                      30
#define FXTEST1_CLICK2                      31
#define FXTEST1_L_MARK1                     32
#define FXTEST1_MARK1                       33
#define FXTEST1_L_MARK2                     34
#define FXTEST1_MARK2                       35
#define FXTEST1_L_MARK3                     36
#define FXTEST1_MARK3                       37
#define FXTEST1_L_MARK4                     38
#define FXTEST1_MARK4                       39
#define FXTEST1_L_MARK5                     40
#define FXTEST1_MARK5                       41
#define FXTEST1_L_CURRENCY                  42
#define FXTEST1_CURRENCY                    43
#define FXTEST1_L_QUIT                      44
#define FXTEST1_ADDRESS                     45
#define FXTEST1_HOTELS                      46
#define FXTEST1_MESSAGE_TO_USER             47
#define maxsize                             255

/*  This table contains each block in the form                               */

static byte fxtest1_blocks [] = {
    /*  Cache-control: no-cache                                              */
    0, 25, 0, 'C', 'a', 'c', 'h', 'e', 45, 'c', 'o', 'n', 't', 'r', 'o',
    'l', ':', 32, 'n', 'o', 45, 'c', 'a', 'c', 'h', 'e', 10,
    /*  Expires: 0                                                           */
    0, 12, 0, 'E', 'x', 'p', 'i', 'r', 'e', 's', ':', 32, '0', 10,
    /*                                                                       */
    0, 2, 0, 10,
    /*  <HTML>                                                               */
    0, 8, 0, '<', 'H', 'T', 'M', 'L', '>', 10,
    /*  <HEAD>                                                               */
    0, 8, 0, '<', 'H', 'E', 'A', 'D', '>', 10,
    /*  <TITLE>Formatix Test Form 1</TITLE>                                  */
    0, 37, 0, '<', 'T', 'I', 'T', 'L', 'E', '>', 'F', 'o', 'r', 'm',
    'a', 't', 'i', 'x', 32, 'T', 'e', 's', 't', 32, 'F', 'o', 'r', 'm',
    32, '1', '<', '/', 'T', 'I', 'T', 'L', 'E', '>', 10,
    /*  <META http-equiv=Content-Language content=en>                        */
    0, 47, 0, '<', 'M', 'E', 'T', 'A', 32, 'h', 't', 't', 'p', 45, 'e',
    'q', 'u', 'i', 'v', '=', 'C', 'o', 'n', 't', 'e', 'n', 't', 45, 'L',
    'a', 'n', 'g', 'u', 'a', 'g', 'e', 32, 'c', 'o', 'n', 't', 'e', 'n',
    't', '=', 'e', 'n', '>', 10,
    /*  <META http-equiv=Content-Type content="text/html">                   */
    0, 52, 0, '<', 'M', 'E', 'T', 'A', 32, 'h', 't', 't', 'p', 45, 'e',
    'q', 'u', 'i', 'v', '=', 'C', 'o', 'n', 't', 'e', 'n', 't', 45, 'T',
    'y', 'p', 'e', 32, 'c', 'o', 'n', 't', 'e', 'n', 't', '=', '"', 't',
    'e', 'x', 't', '/', 'h', 't', 'm', 'l', '"', '>', 10,
    /*  </HEAD>                                                              */
    0, 9, 0, '<', '/', 'H', 'E', 'A', 'D', '>', 10,
    /*  <BODY onLoad="focus()">                                              */
    0, 25, 0, '<', 'B', 'O', 'D', 'Y', 32, 'o', 'n', 'L', 'o', 'a', 'd',
    '=', '"', 'f', 'o', 'c', 'u', 's', '(', ')', '"', '>', 10,
    /*  <H1>Formatix Test Form 1</H1>                                        */
    0, 31, 0, '<', 'H', '1', '>', 'F', 'o', 'r', 'm', 'a', 't', 'i',
    'x', 32, 'T', 'e', 's', 't', 32, 'F', 'o', 'r', 'm', 32, '1', '<',
    '/', 'H', '1', '>', 10,
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
    /*  <P>This is the first of several test forms.  Please fill in          */
    0, 61, 0, '<', 'P', '>', 'T', 'h', 'i', 's', 32, 'i', 's', 32, 't',
    'h', 'e', 32, 'f', 'i', 'r', 's', 't', 32, 'o', 'f', 32, 's', 'e',
    'v', 'e', 'r', 'a', 'l', 32, 't', 'e', 's', 't', 32, 'f', 'o', 'r',
    'm', 's', '.', 32, 32, 'P', 'l', 'e', 'a', 's', 'e', 32, 'f', 'i',
    'l', 'l', 32, 'i', 'n', 10,
    /*  some fields and use the acti ... &~Llink1=1">application</A>.        */
    0, 118, 0, 's', 'o', 'm', 'e', 32, 'f', 'i', 'e', 'l', 'd', 's', 32,
    'a', 'n', 'd', 32, 'u', 's', 'e', 32, 't', 'h', 'e', 32, 'a', 'c',
    't', 'i', 'o', 'n', 32, 'b', 'u', 't', 't', 'o', 'n', 's', 32, 't',
    'o', 32, 'c', 'a', 'l', 'l', 32, 'f', 'u', 'r', 't', 'h', 'e', 'r',
    32, 'f', 'o', 'r', 'm', 's', 10, 'o', 'r', 32, 'q', 'u', 'i', 't',
    32, 't', 'h', 'e', 32, '<', 'A', 32, 'H', 'R', 'E', 'F', '=', '"',
    '#', '(', 'u', 'r', 'i', ')', '&', '~', 'L', 'l', 'i', 'n', 'k',
    '1', '=', '1', '"', '>', 'a', 'p', 'p', 'l', 'i', 'c', 'a', 't',
    'i', 'o', 'n', '<', '/', 'A', '>', '.', 10,
    /*  !--ACTION test_2x  LABEL="Te ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 32, 20, 1, 1, (byte) ((word) test_2_event / 256), (byte) ((word)
    test_2_event & 255), 0, 0, 0, 0, 0, 0, 0, 't', 'e', 's', 't', '_',
    '2', 'x', 0, 'T', 'e', 's', 't', 45, '2', 'x', 0, 0, 0, 0, 0,
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
    /*  <TABLE WIDTH="750">                                                  */
    0, 21, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '7', '5', '0', '"', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 53, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'A', 'L', 'I', 'G',
    'N', '=', 'L', 'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=',
    'T', 'O', 'P', 32, 'N', 'O', 'W', 'R', 'A', 'P', 32, 'C', 'L', 'A',
    'S', 'S', '=', 't', 'd', 'l', 'a', 'b', 'e', 'l', '>', 10,
    /*  !--FIELD TEXTUAL f1 NAME=L_c ... ALUE="Counter:&nbsp;&nbsp;"         */
    0, 33, 10, 7, 1, 0, 0, 20, 0, 20, 'f', '1', 0, 'C', 'o', 'u', 'n',
    't', 'e', 'r', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 59, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '8', '0',
    '%', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v', 'a', 'l',
    'u', 'e', '>', 10,
    /*  !--FIELD NUMERIC f2 NAME=cou ... ZE=5 MAX=? ATTR="" VALUE=""         */
    0, 18, 11, 0, 1, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0, 'f', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f3 NAME=L_b ... orm back used?&nbsp;&nbsp;"         */
    0, 40, 10, 7, 1, 0, 0, 27, 0, 27, 'f', '3', 0, 'F', 'o', 'r', 'm',
    32, 'b', 'a', 'c', 'k', 32, 'u', 's', 'e', 'd', '?', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--FIELD BOOLEAN f4 NAME=bac ... ALSE=no ATTR="" VALUE=false         */
    0, 16, 15, 0, 1, 'f', '4', 0, '0', 0, 'y', 'e', 's', 0, 'n', 'o', 0,
    0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f5 NAME=L_m ... Decimal field:&nbsp;&nbsp;"         */
    0, 39, 10, 7, 1, 0, 0, 26, 0, 26, 'f', '5', 0, 'D', 'e', 'c', 'i',
    'm', 'a', 'l', 32, 'f', 'i', 'e', 'l', 'd', ':', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--FIELD NUMERIC f6 NAME=mon ... AX=? ATTR="" VALUE="123.45"         */
    0, 24, 11, 0, 1, 0, 12, 0, 12, 2, 0, 1, 0, 0, 1, 'f', '6', 0, '1',
    '2', '3', '.', '4', '5', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f7 NAME=L_e ... E="Form event:&nbsp;&nbsp;"         */
    0, 36, 10, 7, 1, 0, 0, 23, 0, 23, 'f', '7', 0, 'F', 'o', 'r', 'm',
    32, 'e', 'v', 'e', 'n', 't', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--FIELD NUMERIC f8 NAME=eve ... ZE=3 MAX=? ATTR="" VALUE=""         */
    0, 18, 11, 3, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '8', 0, 0, 0,
    /*  !--FIELD TEXTUAL f9 NAME=L_c ... p;click field:&nbsp;&nbsp;"         */
    0, 49, 10, 7, 1, 0, 0, '$', 0, '$', 'f', '9', 0, '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 'c', 'l', 'i', 'c', 'k', 32,
    'f', 'i', 'e', 'l', 'd', ':', '&', 'n', 'b', 's', 'p', ';', '&',
    'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f10 NAME=cl ... ZE=3 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 3, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '1', '0', 0, 0,
    0,
    /*  !--FIELD TEXTUAL f11 NAME=L_ ... p;click index:&nbsp;&nbsp;"         */
    0, 50, 10, 7, 1, 0, 0, '$', 0, '$', 'f', '1', '1', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'c', 'l', 'i', 'c',
    'k', 32, 'i', 'n', 'd', 'e', 'x', ':', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f12 NAME=cl ... ZE=3 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 3, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '1', '2', 0, 0,
    0,
    /*  !--FIELD TEXTUAL f13 NAME=L_ ... &nbsp;image_x:&nbsp;&nbsp;"         */
    0, 46, 10, 7, 1, 0, 0, 32, 0, 32, 'f', '1', '3', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'i', 'm', 'a', 'g',
    'e', '_', 'x', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f14 NAME=im ... ZE=3 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 3, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '1', '4', 0, 0,
    0,
    /*  !--FIELD TEXTUAL f15 NAME=L_ ... &nbsp;image_y:&nbsp;&nbsp;"         */
    0, 46, 10, 7, 1, 0, 0, 32, 0, 32, 'f', '1', '5', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 'i', 'm', 'a', 'g',
    'e', '_', 'y', ':', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  !--FIELD NUMERIC f16 NAME=im ... ZE=3 MAX=? ATTR="" VALUE=""         */
    0, 19, 11, 3, 1, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 'f', '1', '6', 0, 0,
    0,
    /*  !--FIELD TEXTUAL f17 NAME=L_ ... bsp;&nbsp;ssl:&nbsp;&nbsp;"         */
    0, 42, 10, 7, 1, 0, 0, 28, 0, 28, 'f', '1', '7', 0, '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 's', 's', 'l', ':',
    '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  !--FIELD BOOLEAN f18 NAME=sh ... es FALSE=no ATTR="" VALUE=0         */
    0, 17, 15, 3, 1, 'f', '1', '8', 0, '0', 0, 'y', 'e', 's', 0, 'n',
    'o', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 56, 0, '<', 'T', 'R', '>', '<', 'T', 'D', 32, 'C', 'O', 'L', 'S',
    'P', 'A', 'N', '=', '9', '9', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L',
    'E', 'F', 'T', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O', 'P',
    32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'b', 'o', 'd', 'y', '>',
    10,
    /*  <HR>                                                                 */
    0, 6, 0, '<', 'H', 'R', '>', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f19 NAME=L_ ... EFORE IF EVENT&nbsp;&nbsp;"         */
    0, 41, 10, 7, 1, 0, 0, 27, 0, 27, 'f', '1', '9', 0, 'B', 'E', 'F',
    'O', 'R', 'E', 32, 'I', 'F', 32, 'E', 'V', 'E', 'N', 'T', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--IF event  VALUE=1                                                 */
    0, 7, 2, 0, 7, 0, 13, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f20 NAME=L_ ... BEGIN IF EVENT&nbsp;&nbsp;"         */
    0, 40, 10, 7, 1, 0, 0, 26, 0, 26, 'f', '2', '0', 0, 'B', 'E', 'G',
    'I', 'N', 32, 'I', 'F', 32, 'E', 'V', 'E', 'N', 'T', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f21 NAME=L_ ... UE="Parameters&nbsp;&nbsp;"         */
    0, 36, 10, 7, 1, 0, 0, 22, 0, 22, 'f', '2', '1', 0, 'P', 'a', 'r',
    'a', 'm', 'e', 't', 'e', 'r', 's', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--FIELD TEXTUAL f22 NAME=pa ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '2', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f23 NAME=L_ ... ="END IF EVENT&nbsp;&nbsp;"         */
    0, 38, 10, 7, 1, 0, 0, 24, 0, 24, 'f', '2', '3', 0, 'E', 'N', 'D',
    32, 'I', 'F', 32, 'E', 'V', 'E', 'N', 'T', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f24 NAME=L_ ... AFTER IF EVENT&nbsp;&nbsp;"         */
    0, 40, 10, 7, 1, 0, 0, 26, 0, 26, 'f', '2', '4', 0, 'A', 'F', 'T',
    'E', 'R', 32, 'I', 'F', 32, 'E', 'V', 'E', 'N', 'T', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 4, 1, 0, 7, 28,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 7, 'V',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f25 NAME=L_ ... E UNLESS EVENT&nbsp;&nbsp;"         */
    0, 45, 10, 7, 1, 0, 0, 31, 0, 31, 'f', '2', '5', 0, 'B', 'E', 'F',
    'O', 'R', 'E', 32, 'U', 'N', 'L', 'E', 'S', 'S', 32, 'E', 'V', 'E',
    'N', 'T', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p',
    ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--UNLESS event  VALUE=1                                             */
    0, 7, 3, 0, 7, 0, 13, 0, 1,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f26 NAME=L_ ... N UNLESS EVENT&nbsp;&nbsp;"         */
    0, 44, 10, 7, 1, 0, 0, 30, 0, 30, 'f', '2', '6', 0, 'B', 'E', 'G',
    'I', 'N', 32, 'U', 'N', 'L', 'E', 'S', 'S', 32, 'E', 'V', 'E', 'N',
    'T', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f27 NAME=L_ ... UE="Parameters&nbsp;&nbsp;"         */
    0, 36, 10, 7, 1, 0, 0, 22, 0, 22, 'f', '2', '7', 0, 'P', 'a', 'r',
    'a', 'm', 'e', 't', 'e', 'r', 's', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--FIELD TEXTUAL f28 NAME=pa ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '2', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f29 NAME=L_ ... D UNLESS EVENT&nbsp;&nbsp;"         */
    0, 42, 10, 7, 1, 0, 0, 28, 0, 28, 'f', '2', '9', 0, 'E', 'N', 'D',
    32, 'U', 'N', 'L', 'E', 'S', 'S', 32, 'E', 'V', 'E', 'N', 'T', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f30 NAME=L_ ... R UNLESS EVENT&nbsp;&nbsp;"         */
    0, 44, 10, 7, 1, 0, 0, 30, 0, 30, 'f', '3', '0', 0, 'A', 'F', 'T',
    'E', 'R', 32, 'U', 'N', 'L', 'E', 'S', 'S', 32, 'E', 'V', 'E', 'N',
    'T', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0,
    0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD COLSPAN=99 ALIGN=LEFT VALIGN=TOP CLASS=tdbody>               */
    0, 4, 1, 0, 7, 28,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 7, 'V',
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD></TD><TD VALIGN=TOP  ... T WIDTH="80%" CLASS=tdvalue>        */
    0, 67, 0, '<', 'T', 'R', '>', '<', 'T', 'D', '>', '<', '/', 'T',
    'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T',
    'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=', 'L', 'E', 'F', 'T', 32,
    'W', 'I', 'D', 'T', 'H', '=', '"', '8', '0', '%', '"', 32, 'C', 'L',
    'A', 'S', 'S', '=', 't', 'd', 'v', 'a', 'l', 'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f31 NAME=cl ... ATTR="" VALUE="Click Here!"         */
    0, 25, 10, 10, 1, 0, 0, 11, 0, 11, 'f', '3', '1', 0, 'C', 'l', 'i',
    'c', 'k', 32, 'H', 'e', 'r', 'e', '!', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD></TD><TD VALIGN=TOP  ... T WIDTH="80%" CLASS=tdvalue>        */
    0, 4, 1, 0, 10, 24,
    /*  !--FIELD TEXTUAL f32 NAME=cl ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 10, 1, 0, 0, 'P', 0, 'P', 'f', '3', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f33 NAME=L_ ... ontext check: &nbsp;&nbsp;"         */
    0, 41, 10, 7, 1, 0, 0, 27, 0, 27, 'f', '3', '3', 0, 'C', 'o', 'n',
    't', 'e', 'x', 't', 32, 'c', 'h', 'e', 'c', 'k', ':', 32, '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--FIELD TEXTUAL f34 NAME=ma ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 1, 0, 1, 'f', '3', '4', 0, 0, 0,
    /*  !--FIELD TEXTUAL f35 NAME=L_mark2 VALUE=":"                          */
    0, 15, 10, 7, 1, 0, 0, 1, 0, 1, 'f', '3', '5', 0, ':', 0, 0,
    /*  !--FIELD TEXTUAL f36 NAME=ma ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 1, 0, 1, 'f', '3', '6', 0, 0, 0,
    /*  !--FIELD TEXTUAL f37 NAME=L_mark3 VALUE=":"                          */
    0, 15, 10, 7, 1, 0, 0, 1, 0, 1, 'f', '3', '7', 0, ':', 0, 0,
    /*  !--FIELD TEXTUAL f38 NAME=ma ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 1, 0, 1, 'f', '3', '8', 0, 0, 0,
    /*  !--FIELD TEXTUAL f39 NAME=L_mark4 VALUE=":"                          */
    0, 15, 10, 7, 1, 0, 0, 1, 0, 1, 'f', '3', '9', 0, ':', 0, 0,
    /*  !--FIELD TEXTUAL f40 NAME=ma ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 1, 0, 1, 'f', '4', '0', 0, 0, 0,
    /*  !--FIELD TEXTUAL f41 NAME=L_mark5 VALUE=":"                          */
    0, 15, 10, 7, 1, 0, 0, 1, 0, 1, 'f', '4', '1', 0, ':', 0, 0,
    /*  !--FIELD TEXTUAL f42 NAME=ma ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, 1, 0, 1, 'f', '4', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 7, 'V',
    /*  <TABLE WIDTH=60% BORDER=1>                                           */
    0, 28, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '6', '0', '%', 32, 'B', 'O', 'R', 'D', 'E', 'R', '=', '1', '>',
    10,
    /*  <TR>                                                                 */
    0, 6, 0, '<', 'T', 'R', '>', 10,
    /*  <TD>The following Hotels wer ... you selected. Price is based        */
    0, 80, 0, '<', 'T', 'D', '>', 'T', 'h', 'e', 32, 'f', 'o', 'l', 'l',
    'o', 'w', 'i', 'n', 'g', 32, 'H', 'o', 't', 'e', 'l', 's', 32, 'w',
    'e', 'r', 'e', 32, 'f', 'o', 'u', 'n', 'd', 32, 'f', 'o', 'r', 32,
    't', 'h', 'e', 32, 'd', 'a', 't', 'e', 's', 32, 'y', 'o', 'u', 32,
    's', 'e', 'l', 'e', 'c', 't', 'e', 'd', '.', 32, 'P', 'r', 'i', 'c',
    'e', 32, 'i', 's', 32, 'b', 'a', 's', 'e', 'd', 10,
    /*  on 2 people sharing a standa ... Select a hotel to view.</TD>        */
    0, 137, 0, 'o', 'n', 32, '2', 32, 'p', 'e', 'o', 'p', 'l', 'e', 32,
    's', 'h', 'a', 'r', 'i', 'n', 'g', 32, 'a', 32, 's', 't', 'a', 'n',
    'd', 'a', 'r', 'd', 32, 'r', 'o', 'o', 'm', '.', 32, 'A', 'n', 'y',
    32, 's', 'u', 'p', 'l', 'e', 'm', 'e', 'n', 't', 's', 32, 'w', 'h',
    'i', 'c', 'h', 32, 'm', 'a', 'y', 32, 'a', 'p', 'p', 'l', 'y', 32,
    'w', 'i', 'l', 'l', 32, 'b', 'e', 10, 'i', 'n', 'd', 'i', 'c', 'a',
    't', 'e', 'd', 32, 'b', 'e', 'f', 'o', 'r', 'e', 32, 'c', 'o', 'n',
    'f', 'i', 'r', 'm', 'a', 't', 'i', 'o', 'n', '.', 32, 'S', 'e', 'l',
    'e', 'c', 't', 32, 'a', 32, 'h', 'o', 't', 'e', 'l', 32, 't', 'o',
    32, 'v', 'i', 'e', 'w', '.', '<', '/', 'T', 'D', '>', 10,
    /*  </TR><TR><TD>                                                        */
    0, 15, 0, '<', '/', 'T', 'R', '>', '<', 'T', 'R', '>', '<', 'T',
    'D', '>', 10,
    /*  <TABLE WIDTH="100%" >                                                */
    0, 23, 0, '<', 'T', 'A', 'B', 'L', 'E', 32, 'W', 'I', 'D', 'T', 'H',
    '=', '"', '1', '0', '0', '%', '"', 32, '>', 10,
    /*  <TR>                                                                 */
    0, 4, 1, 0, 11, 155,
    /*  <TH ALIGN=CENTER VALIGN=TOP>                                         */
    0, 30, 0, '<', 'T', 'H', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O',
    'P', '>', 10,
    /*  !--FIELD TEXTUAL f43 NAME=L_currency VALUE="Selection"               */
    0, 23, 10, 6, 1, 0, 0, 9, 0, 9, 'f', '4', '3', 0, 'S', 'e', 'l',
    'e', 'c', 't', 'i', 'o', 'n', 0, 0,
    /*  </TH>                                                                */
    0, 7, 0, '<', '/', 'T', 'H', '>', 10,
    /*  !--REPEAT hotels  ROWS=5                                             */
    0, 7, 4, 0, '.', 0, 6, 0, 5,
    /*  </TR>                                                                */
    0, 7, 0, '<', '/', 'T', 'R', '>', 10,
    /*  <TR>                                                                 */
    0, 4, 1, 0, 11, 155,
    /*  <TD ALIGN=CENTER VALIGN=TOP CLASS=tdfield>                           */
    0, 44, 0, '<', 'T', 'D', 32, 'A', 'L', 'I', 'G', 'N', '=', 'C', 'E',
    'N', 'T', 'E', 'R', 32, 'V', 'A', 'L', 'I', 'G', 'N', '=', 'T', 'O',
    'P', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'f', 'i', 'e', 'l',
    'd', '>', 10,
    /*  !--FIELD SELECT f44 NAME=cur ... PE=dynamic 0="No selection"         */
    0, 29, 16, 0, 5, 0, 0, 0, 'f', '4', '4', 0, '0', 0, 'n', 'o', 0, 0,
    'N', 'o', 32, 's', 'e', 'l', 'e', 'c', 't', 'i', 'o', 'n', 0,
    /*  </TD>                                                                */
    0, 7, 0, '<', '/', 'T', 'D', '>', 10,
    /*  </TR>                                                                */
    0, 4, 1, 0, 12, 251,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 11, 'k',
    /*  </TD></TR><TR><TD>                                                   */
    0, 20, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', '<',
    'T', 'R', '>', '<', 'T', 'D', '>', 10,
    /*  RQ indicates we will need to ... dit card details to do this.        */
    0, 120, 0, 'R', 'Q', 32, 'i', 'n', 'd', 'i', 'c', 'a', 't', 'e',
    's', 32, 'w', 'e', 32, 'w', 'i', 'l', 'l', 32, 'n', 'e', 'e', 'd',
    32, 't', 'o', 32, 'c', 'o', 'n', 't', 'a', 'c', 't', 32, 't', 'h',
    'e', 32, 'h', 'o', 't', 'e', 'l', 32, 't', 'o', 32, 'r', 'e', 'q',
    'u', 'e', 's', 't', 32, 't', 'h', 'e', 32, 'r', 'o', 'o', 'm', '.',
    32, 32, 'W', 'e', 10, 'w', 'i', 'l', 'l', 32, 'n', 'e', 'e', 'd',
    32, 'y', 'o', 'u', 'r', 32, 'c', 'r', 'e', 'd', 'i', 't', 32, 'c',
    'a', 'r', 'd', 32, 'd', 'e', 't', 'a', 'i', 'l', 's', 32, 't', 'o',
    32, 'd', 'o', 32, 't', 'h', 'i', 's', '.', 10,
    /*  !--ACTION why_ccard  EVENT=t ... UE="Click here to see why?"         */
    0, 37, 20, 1, 1, (byte) ((word) test_2_event / 256), (byte) ((word)
    test_2_event & 255), 0, 1, 0, 0, 0, 0, 0, 'w', 'h', 'y', '_', 'c',
    'c', 'a', 'r', 'd', 0, '<', 'N', 'o', 32, 'l', 'a', 'b', 'e', 'l',
    '>', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 11, 'k',
    /*  <H1><A NAME="TOC1">Form Symbols</A></H1>                             */
    0, 42, 0, '<', 'H', '1', '>', '<', 'A', 32, 'N', 'A', 'M', 'E', '=',
    '"', 'T', 'O', 'C', '1', '"', '>', 'F', 'o', 'r', 'm', 32, 'S', 'y',
    'm', 'b', 'o', 'l', 's', '<', '/', 'A', '>', '<', '/', 'H', '1',
    '>', 10,
    /*  <P>Server software: #(SERVER_SOFTWARE) #(SERVER_VERSION)             */
    0, 58, 0, '<', 'P', '>', 'S', 'e', 'r', 'v', 'e', 'r', 32, 's', 'o',
    'f', 't', 'w', 'a', 'r', 'e', ':', 32, '#', '(', 'S', 'E', 'R', 'V',
    'E', 'R', '_', 'S', 'O', 'F', 'T', 'W', 'A', 'R', 'E', ')', 32, '#',
    '(', 'S', 'E', 'R', 'V', 'E', 'R', '_', 'V', 'E', 'R', 'S', 'I',
    'O', 'N', ')', 10,
    /*  <BR>Server URL:     #(SERVER_URL)                                    */
    0, 35, 0, '<', 'B', 'R', '>', 'S', 'e', 'r', 'v', 'e', 'r', 32, 'U',
    'R', 'L', ':', 32, 32, 32, 32, 32, '#', '(', 'S', 'E', 'R', 'V',
    'E', 'R', '_', 'U', 'R', 'L', ')', 10,
    /*  <BR>Server Name:    #(SERVER_NAME)                                   */
    0, 36, 0, '<', 'B', 'R', '>', 'S', 'e', 'r', 'v', 'e', 'r', 32, 'N',
    'a', 'm', 'e', ':', 32, 32, 32, 32, '#', '(', 'S', 'E', 'R', 'V',
    'E', 'R', '_', 'N', 'A', 'M', 'E', ')', 10,
    /*  <HR>                                                                 */
    0, 4, 1, 0, 7, 'V',
    /*  <TABLE WIDTH="750">                                                  */
    0, 4, 1, 0, 4, 3,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 26,
    /*  !--FIELD TEXTUAL f45 NAME=L_ ... oose an action&nbsp;&nbsp;"         */
    0, 42, 10, 7, 1, 0, 0, 28, 0, 28, 'f', '4', '5', 0, 'C', 'h', 'o',
    'o', 's', 'e', 32, 'a', 'n', 32, 'a', 'c', 't', 'i', 'o', 'n', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 't',
    /*  !--ACTION quit  LABEL="Quit" ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 26, 20, 0, 1, (byte) ((word) return_event / 256), (byte) ((word)
    return_event & 255), 0, 2, 0, 0, 0, 0, 0, 'q', 'u', 'i', 't', 0,
    'Q', 'u', 'i', 't', 0, 0, 0, 0, 0,
    /*  !--ACTION test_2  LABEL="Tes ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) test_2_event / 256), (byte) ((word)
    test_2_event & 255), 0, 3, 0, 0, 0, 0, 0, 't', 'e', 's', 't', '_',
    '2', 0, 'T', 'e', 's', 't', 45, '2', 0, 0, 0, 0, 0,
    /*  !--ACTION test_3  LABEL="Tes ... NFIRM="" ATTR="" TYPE=PLAIN         */
    0, 30, 20, 1, 1, (byte) ((word) test_3_event / 256), (byte) ((word)
    test_3_event & 255), 0, 4, 0, 0, 0, 0, 0, 't', 'e', 's', 't', '_',
    '3', 0, 'T', 'e', 's', 't', 45, '3', 0, 0, 0, 0, 0,
    /*  !--ACTION create  LABEL="Cre ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) create_event / 256), (byte) ((word)
    create_event & 255), 0, 5, 0, 0, 0, 0, 0, 'c', 'r', 'e', 'a', 't',
    'e', 0, 'C', 'r', 'e', 'a', 't', 'e', 0, 0, 0, 0, 0,
    /*  !--ACTION secure  LABEL="Sec ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) secure_event / 256), (byte) ((word)
    secure_event & 255), 0, 6, 0, 0, 0, 0, 0, 's', 'e', 'c', 'u', 'r',
    'e', 0, 'S', 'e', 'c', 'u', 'r', 'e', 0, 0, 0, 0, 0,
    /*  !--ACTION insecure  LABEL="I ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 34, 20, 0, 1, (byte) ((word) insecure_event / 256), (byte)
    ((word) insecure_event & 255), 0, 7, 0, 0, 0, 0, 0, 'i', 'n', 's',
    'e', 'c', 'u', 'r', 'e', 0, 'I', 'n', 's', 'e', 'c', 'u', 'r', 'e',
    0, 0, 0, 0, 0,
    /*  !--ACTION cancel  LABEL="Can ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) cancel_event / 256), (byte) ((word)
    cancel_event & 255), 0, 8, 0, 0, 0, 0, 0, 'c', 'a', 'n', 'c', 'e',
    'l', 0, 'C', 'a', 'n', 'c', 'e', 'l', 0, 0, 0, 0, 0,
    /*  !--ACTION loop  LABEL="Loop" ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 26, 20, 0, 1, (byte) ((word) loop_event / 256), (byte) ((word)
    loop_event & 255), 0, 9, 0, 0, 0, 0, 0, 'l', 'o', 'o', 'p', 0, 'L',
    'o', 'o', 'p', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 197,
    /*  </TABLE>                                                             */
    0, 4, 1, 0, 11, 'k',
    /*  !--FIELD NUMERIC address SIZE=4 VALUE=1                              */
    0, 24, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'a', 'd', 'd', 'r',
    'e', 's', 's', 0, '1', 0, 0,
    /*  !--FIELD NUMERIC hotels SIZE=4 VALUE=5                               */
    0, 23, 11, 5, 1, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 'h', 'o', 't', 'e',
    'l', 's', 0, '5', 0, 0,
    /*  !--FIELD TEXTUAL message_to_user SIZE=120                            */
    0, 26, 10, 4, 1, 0, 0, 'x', 0, 'x', 'm', 'e', 's', 's', 'a', 'g',
    'e', '_', 't', 'o', '_', 'u', 's', 'e', 'r', 0, 0, 0,
    /*  </FORM>                                                              */
    0, 9, 0, '<', '/', 'F', 'O', 'R', 'M', '>', 10,
    /*  <SCRIPT LANGUAGE="JavaScript">                                       */
    0, 4, 1, 0, 1, 22,
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
    0, 4, 1, 0, 2, 186,
    /*  </BODY></HTML>                                                       */
    0, 16, 0, '<', '/', 'B', 'O', 'D', 'Y', '>', '<', '/', 'H', 'T',
    'M', 'L', '>', 10,
    0, 0, 0
    };

static FIELD_DEFN fxtest1_fields [] = {
    { 0, 1105, 20 },                    /*  l_counter                       */
    { 22, 1201, 5 },                    /*  counter                         */
    { 29, 1241, 27 },                   /*  l_back_used                     */
    { 58, 1289, 1 },                    /*  back_used                       */
    { 61, 1319, 26 },                   /*  l_money                         */
    { 89, 1366, 12 },                   /*  money                           */
    { 103, 1404, 23 },                  /*  l_event                         */
    { 128, 1448, 3 },                   /*  event                           */
    { 133, 1468, 36 },                  /*  l_click_field                   */
    { 171, 1519, 3 },                   /*  click_field                     */
    { 176, 1540, 36 },                  /*  l_click_index                   */
    { 214, 1592, 3 },                   /*  click_index                     */
    { 219, 1613, 32 },                  /*  l_image_x                       */
    { 253, 1661, 3 },                   /*  image_x                         */
    { 258, 1682, 32 },                  /*  l_image_y                       */
    { 292, 1730, 3 },                   /*  image_y                         */
    { 297, 1751, 28 },                  /*  l_show_ssl                      */
    { 327, 1795, 1 },                   /*  show_ssl                        */
    { 330, 1898, 27 },                  /*  l_noname1                       */
    { 359, 1968, 26 },                  /*  l_noname2                       */
    { 387, 2028, 22 },                  /*  l_params                        */
    { 411, 2072, 40 },                  /*  params                          */
    { 453, 2100, 24 },                  /*  l_noname3                       */
    { 479, 2158, 26 },                  /*  l_noname4                       */
    { 507, 2236, 31 },                  /*  l_noname5                       */
    { 540, 2310, 30 },                  /*  l_noname6                       */
    { 572, 2374, 22 },                  /*  l_params1                       */
    { 596, 2418, 40 },                  /*  params1                         */
    { 638, 2446, 28 },                  /*  l_noname7                       */
    { 668, 2508, 30 },                  /*  l_noname8                       */
    { 700, 2653, 11 },                  /*  click1                          */
    { 713, 2692, 80 },                  /*  click2                          */
    { 795, 2720, 27 },                  /*  l_mark1                         */
    { 824, 2769, 1 },                   /*  mark1                           */
    { 827, 2785, 1 },                   /*  l_mark2                         */
    { 830, 2802, 1 },                   /*  mark2                           */
    { 833, 2818, 1 },                   /*  l_mark3                         */
    { 836, 2835, 1 },                   /*  mark3                           */
    { 839, 2851, 1 },                   /*  l_mark4                         */
    { 842, 2868, 1 },                   /*  mark4                           */
    { 845, 2884, 1 },                   /*  l_mark5                         */
    { 848, 2901, 1 },                   /*  mark5                           */
    { 851, 3280, 9 },                   /*  l_currency                      */
    { 862, 3384, 3 },                   /*  currency                        */
    { 887, 3828, 28 },                  /*  l_quit                          */
    { 917, 4142, 4 },                   /*  address                         */
    { 923, 4168, 4 },                   /*  hotels                          */
    { 929, 4193, 120 },                 /*  message_to_user                 */
    { 1051, 0, 0 },                     /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_counter_a          ;
    char   l_counter            [20 + 1];
    byte   counter_a            ;
    char   counter              [5 + 1];
    byte   l_back_used_a        ;
    char   l_back_used          [27 + 1];
    byte   back_used_a          ;
    char   back_used            [1 + 1];
    byte   l_money_a            ;
    char   l_money              [26 + 1];
    byte   money_a              ;
    char   money                [12 + 1];
    byte   l_event_a            ;
    char   l_event              [23 + 1];
    byte   event_a              ;
    char   event                [3 + 1];
    byte   l_click_field_a      ;
    char   l_click_field        [36 + 1];
    byte   click_field_a        ;
    char   click_field          [3 + 1];
    byte   l_click_index_a      ;
    char   l_click_index        [36 + 1];
    byte   click_index_a        ;
    char   click_index          [3 + 1];
    byte   l_image_x_a          ;
    char   l_image_x            [32 + 1];
    byte   image_x_a            ;
    char   image_x              [3 + 1];
    byte   l_image_y_a          ;
    char   l_image_y            [32 + 1];
    byte   image_y_a            ;
    char   image_y              [3 + 1];
    byte   l_show_ssl_a         ;
    char   l_show_ssl           [28 + 1];
    byte   show_ssl_a           ;
    char   show_ssl             [1 + 1];
    byte   l_noname1_a          ;
    char   l_noname1            [27 + 1];
    byte   l_noname2_a          ;
    char   l_noname2            [26 + 1];
    byte   l_params_a           ;
    char   l_params             [22 + 1];
    byte   params_a             ;
    char   params               [40 + 1];
    byte   l_noname3_a          ;
    char   l_noname3            [24 + 1];
    byte   l_noname4_a          ;
    char   l_noname4            [26 + 1];
    byte   l_noname5_a          ;
    char   l_noname5            [31 + 1];
    byte   l_noname6_a          ;
    char   l_noname6            [30 + 1];
    byte   l_params1_a          ;
    char   l_params1            [22 + 1];
    byte   params1_a            ;
    char   params1              [40 + 1];
    byte   l_noname7_a          ;
    char   l_noname7            [28 + 1];
    byte   l_noname8_a          ;
    char   l_noname8            [30 + 1];
    byte   click1_a             ;
    char   click1               [11 + 1];
    byte   click2_a             ;
    char   click2               [80 + 1];
    byte   l_mark1_a            ;
    char   l_mark1              [27 + 1];
    byte   mark1_a              ;
    char   mark1                [1 + 1];
    byte   l_mark2_a            ;
    char   l_mark2              [1 + 1];
    byte   mark2_a              ;
    char   mark2                [1 + 1];
    byte   l_mark3_a            ;
    char   l_mark3              [1 + 1];
    byte   mark3_a              ;
    char   mark3                [1 + 1];
    byte   l_mark4_a            ;
    char   l_mark4              [1 + 1];
    byte   mark4_a              ;
    char   mark4                [1 + 1];
    byte   l_mark5_a            ;
    char   l_mark5              [1 + 1];
    byte   mark5_a              ;
    char   mark5                [1 + 1];
    byte   l_currency_a         ;
    char   l_currency           [9 + 1];
    byte   currency_a           [5] ;
    char   currency             [5] [3 + 1];
    byte   l_quit_a             ;
    char   l_quit               [28 + 1];
    byte   address_a            ;
    char   address              [4 + 1];
    byte   hotels_a             ;
    char   hotels               [4 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   test_2x_a;
    byte   why_ccard_a;
    byte   quit_a;
    byte   test_2_a;
    byte   test_3_a;
    byte   create_a;
    byte   secure_a;
    byte   insecure_a;
    byte   cancel_a;
    byte   loop_a;
    } FXTEST1_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_fxtest1 = {
    fxtest1_blocks,
    fxtest1_fields,
    174,                                /*  Number of blocks in form        */
    48,                                 /*  Number of fields in form        */
    10,                                 /*  Number of actions in form       */
    1051,                               /*  Size of fields                  */
    "fxtest1",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

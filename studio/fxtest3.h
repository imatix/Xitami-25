/*---------------------------------------------------------------------------
 *  fxtest3.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:22 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_FXTEST3__
#define __FORM_FXTEST3__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define FXTEST3_L_FIELD_1                   0
#define FXTEST3_FIELD_1                     1
#define FXTEST3_L_FIELD_2                   2
#define FXTEST3_FIELD_2                     3
#define FXTEST3_L_FIELD_9                   4
#define FXTEST3_FIELD_9_TMP                 5
#define FXTEST3_FIELD_9                     6
#define FXTEST3_L_FIELD_3                   7
#define FXTEST3_FIELD_3                     8
#define FXTEST3_L_FIELD_4                   9
#define FXTEST3_FIELD_4                     10
#define FXTEST3_L_PARAMS                    11
#define FXTEST3_PARAMS                      12
#define FXTEST3_L_COMMENTS                  13
#define FXTEST3_COMMENTS                    14
#define FXTEST3_L_RETURN                    15
#define FXTEST3_MESSAGE_TO_USER             16

/*  This table contains each block in the form                               */

static byte fxtest3_blocks [] = {
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
    /*  <TITLE>Formatix Test Form 3</TITLE>                                  */
    0, 37, 0, '<', 'T', 'I', 'T', 'L', 'E', '>', 'F', 'o', 'r', 'm',
    'a', 't', 'i', 'x', 32, 'T', 'e', 's', 't', 32, 'F', 'o', 'r', 'm',
    32, '3', '<', '/', 'T', 'I', 'T', 'L', 'E', '>', 10,
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
    /*  <H1>Formatix Test Form 3</H1>                                        */
    0, 31, 0, '<', 'H', '1', '>', 'F', 'o', 'r', 'm', 'a', 't', 'i',
    'x', 32, 'T', 'e', 's', 't', 32, 'F', 'o', 'r', 'm', 32, '3', '<',
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
    /*  <P>This is the third of several test forms.                          */
    0, 45, 0, '<', 'P', '>', 'T', 'h', 'i', 's', 32, 'i', 's', 32, 't',
    'h', 'e', 32, 't', 'h', 'i', 'r', 'd', 32, 'o', 'f', 32, 's', 'e',
    'v', 'e', 'r', 'a', 'l', 32, 't', 'e', 's', 't', 32, 'f', 'o', 'r',
    'm', 's', '.', 10,
    /*  <FORM METHOD=POST ACTION="#( ... CTYPE="multipart/form-data">        */
    0, 81, 0, '<', 'F', 'O', 'R', 'M', 32, 'M', 'E', 'T', 'H', 'O', 'D',
    '=', 'P', 'O', 'S', 'T', 32, 'A', 'C', 'T', 'I', 'O', 'N', '=', '"',
    '#', '(', 'p', 'r', 'o', 't', 'o', ')', '#', '(', 'h', 'o', 's',
    't', ')', '#', '(', 'u', 'r', 'i', ')', '"', 32, 'E', 'N', 'C', 'T',
    'Y', 'P', 'E', '=', '"', 'm', 'u', 'l', 't', 'i', 'p', 'a', 'r',
    't', '/', 'f', 'o', 'r', 'm', 45, 'd', 'a', 't', 'a', '"', '>', 10,
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
    /*  !--FIELD TEXTUAL f1 NAME=L_f ... ort text field&nbsp;&nbsp;"         */
    0, 41, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', 0, 'S', 'h', 'o', 'r',
    't', 32, 't', 'e', 'x', 't', 32, 'f', 'i', 'e', 'l', 'd', '&', 'n',
    'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 59, 0, '<', '/', 'T', 'D', '>', '<', 'T', 'D', 32, 'V', 'A', 'L',
    'I', 'G', 'N', '=', 'T', 'O', 'P', 32, 'A', 'L', 'I', 'G', 'N', '=',
    'L', 'E', 'F', 'T', 32, 'W', 'I', 'D', 'T', 'H', '=', '"', '8', '0',
    '%', '"', 32, 'C', 'L', 'A', 'S', 'S', '=', 't', 'd', 'v', 'a', 'l',
    'u', 'e', '>', 10,
    /*  !--FIELD TEXTUAL f2 NAME=fie ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 5, 0, 5, 'f', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 12, 0, '<', '/', 'T', 'D', '>', '<', '/', 'T', 'R', '>', 10,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f3 NAME=L_f ... ong text field&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', 0, 'L', 'o', 'n', 'g',
    32, 't', 'e', 'x', 't', 32, 'f', 'i', 'e', 'l', 'd', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--FIELD TEXTUAL f4 NAME=fie ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 'P', 0, 'P', 'f', '4', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f5 NAME=L_f ... LUE="File name&nbsp;&nbsp;"         */
    0, 34, 10, 6, 1, 0, 0, 21, 0, 21, 'f', '5', 0, 'F', 'i', 'l', 'e',
    32, 'n', 'a', 'm', 'e', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--FIELD TEXTUAL f6_tmp NAME ... ALUE="/upload/00000001.tmp"         */
    0, 37, 10, 4, 1, 0, 0, 'P', 0, 'P', 'f', '6', '_', 't', 'm', 'p', 0,
    '/', 'u', 'p', 'l', 'o', 'a', 'd', '/', '0', '0', '0', '0', '0',
    '0', '0', '1', '.', 't', 'm', 'p', 0, 0,
    /*  !--FIELD FILE f6 NAME=field- ... ALUE="/upload/00000001.tmp"         */
    0, 32, 21, 6, 1, 0, 'P', 0, 'P', 'f', '6', 0, '/', 'u', 'p', 'l',
    'o', 'a', 'd', '/', '0', '0', '0', '0', '0', '0', '0', '1', '.',
    't', 'm', 'p', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f7 NAME=L_f ... "Numeric field&nbsp;&nbsp;"         */
    0, 38, 10, 6, 1, 0, 0, 25, 0, 25, 'f', '7', 0, 'N', 'u', 'm', 'e',
    'r', 'i', 'c', 32, 'f', 'i', 'e', 'l', 'd', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--FIELD NUMERIC f8 NAME=fie ... E=12 MAX=? ATTR="" VALUE=""         */
    0, 18, 11, 0, 1, 0, 12, 0, 12, 0, 0, 0, 0, 0, 0, 'f', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f9 NAME=L_f ... Field number 3&nbsp;&nbsp;"         */
    0, 39, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '9', 0, 'F', 'i', 'e', 'l',
    'd', 32, 'n', 'u', 'm', 'b', 'e', 'r', 32, '3', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--FIELD DATE f10 NAME=field ... TH=? DAY=? ATTR="" VALUE=""         */
    0, 28, 12, 0, 1, 0, 15, 0, 1, 0, 0, 0, 'f', '1', '0', 0, 0, 'y',
    'y', 'y', 'y', 45, 'M', 'M', 'M', 45, 'd', 'd', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f11 NAME=L_ ... UE="Parameters&nbsp;&nbsp;"         */
    0, 36, 10, 6, 1, 0, 0, 22, 0, 22, 'f', '1', '1', 0, 'P', 'a', 'r',
    'a', 'm', 'e', 't', 'e', 'r', 's', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--FIELD TEXTUAL f12 NAME=pa ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '1', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f13 NAME=L_ ... ALUE="Comments&nbsp;&nbsp;"         */
    0, 34, 10, 6, 1, 0, 0, 20, 0, 20, 'f', '1', '3', 0, 'C', 'o', 'm',
    'm', 'e', 'n', 't', 's', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--FIELD TEXTBOX f14 NAME=co ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 14, 0, 1, 4, '(', 0, 0, 160, 'f', '1', '4', 0, 0, 0,
    /*  Free text                                                            */
    0, 11, 0, 'F', 'r', 'e', 'e', 32, 't', 'e', 'x', 't', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 3, 142,
    /*  !--FIELD TEXTUAL f15 NAME=L_ ... oose an action&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', '5', 0, 'C', 'h', 'o',
    'o', 's', 'e', 32, 'a', 'n', 32, 'a', 'c', 't', 'i', 'o', 'n', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 3, 240,
    /*  !--ACTION return  LABEL="Ret ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) return_event / 256), (byte) ((word)
    return_event & 255), 0, 0, 0, 0, 0, 0, 0, 'r', 'e', 't', 'u', 'r',
    'n', 0, 'R', 'e', 't', 'u', 'r', 'n', 0, 0, 0, 0, 0,
    /*  !--ACTION process  LABEL="Pr ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 32, 20, 0, 1, (byte) ((word) process_event / 256), (byte) ((word)
    process_event & 255), 0, 1, 0, 0, 0, 0, 0, 'p', 'r', 'o', 'c', 'e',
    's', 's', 0, 'P', 'r', 'o', 'c', 'e', 's', 's', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, '<',
    /*  </TABLE>                                                             */
    0, 10, 0, '<', '/', 'T', 'A', 'B', 'L', 'E', '>', 10,
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

static FIELD_DEFN fxtest3_fields [] = {
    { 0, 965, 28 },                     /*  l_field_1                       */
    { 30, 1069, 5 },                    /*  field_1                         */
    { 37, 1104, 27 },                   /*  l_field_2                       */
    { 66, 1152, 80 },                   /*  field_2                         */
    { 148, 1179, 21 },                  /*  l_field_9                       */
    { 171, 1221, 80 },                  /*  field_9_tmp                     */
    { 253, 1260, 80 },                  /*  field_9                         */
    { 335, 1306, 25 },                  /*  l_field_3                       */
    { 362, 1352, 12 },                  /*  field_3                         */
    { 376, 1384, 26 },                  /*  l_field_4                       */
    { 404, 1431, 8 },                   /*  field_4                         */
    { 414, 1473, 22 },                  /*  l_params                        */
    { 438, 1517, 40 },                  /*  params                          */
    { 480, 1545, 20 },                  /*  l_comments                      */
    { 502, 1587, 160 },                 /*  comments                        */
    { 664, 1628, 28 },                  /*  l_return                        */
    { 694, 1762, 120 },                 /*  message_to_user                 */
    { 816, 0, 0 },                      /*  -- sentinel --                  */
    };

/*  The data of a form is a list of attributes and fields                    */

typedef struct {
    byte   l_field_1_a          ;
    char   l_field_1            [28 + 1];
    byte   field_1_a            ;
    char   field_1              [5 + 1];
    byte   l_field_2_a          ;
    char   l_field_2            [27 + 1];
    byte   field_2_a            ;
    char   field_2              [80 + 1];
    byte   l_field_9_a          ;
    char   l_field_9            [21 + 1];
    byte   field_9_tmp_a        ;
    char   field_9_tmp          [80 + 1];
    byte   field_9_a            ;
    char   field_9              [80 + 1];
    byte   l_field_3_a          ;
    char   l_field_3            [25 + 1];
    byte   field_3_a            ;
    char   field_3              [12 + 1];
    byte   l_field_4_a          ;
    char   l_field_4            [26 + 1];
    byte   field_4_a            ;
    char   field_4              [8 + 1];
    byte   l_params_a           ;
    char   l_params             [22 + 1];
    byte   params_a             ;
    char   params               [40 + 1];
    byte   l_comments_a         ;
    char   l_comments           [20 + 1];
    byte   comments_a           ;
    char   comments             [160 + 1];
    byte   l_return_a           ;
    char   l_return             [28 + 1];
    byte   message_to_user_a    ;
    char   message_to_user      [120 + 1];
    byte   return_a;
    byte   process_a;
    } FXTEST3_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_fxtest3 = {
    fxtest3_blocks,
    fxtest3_fields,
    68,                                 /*  Number of blocks in form        */
    17,                                 /*  Number of fields in form        */
    2,                                  /*  Number of actions in form       */
    816,                                /*  Size of fields                  */
    "fxtest3",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

/*---------------------------------------------------------------------------
 *  fxtest2.h - HTML form definition
 *
 *  Generated 2004/07/22, 16:52:22 by fxgen 3.1
 *  See Studio on-line help pages at <http://www.imatix.com>.
 *---------------------------------------------------------------------------*/

#ifndef __FORM_FXTEST2__
#define __FORM_FXTEST2__

#include "sfl.h"
#include "formio.h"


/*  Constants defining size of tables, etc.                                  */

#define FXTEST2_L_FIELD_1                   0
#define FXTEST2_FIELD_1                     1
#define FXTEST2_L_FIELD_2                   2
#define FXTEST2_FIELD_2                     3
#define FXTEST2_L_FIELD_3                   4
#define FXTEST2_FIELD_3_TMP                 5
#define FXTEST2_FIELD_3                     6
#define FXTEST2_L_FIELD_4                   7
#define FXTEST2_FIELD_4                     8
#define FXTEST2_L_FIELD_5                   9
#define FXTEST2_FIELD_5                     10
#define FXTEST2_L_PARAMS                    11
#define FXTEST2_PARAMS                      12
#define FXTEST2_L_COMMENTS                  13
#define FXTEST2_COMMENTS                    14
#define FXTEST2_L_RETURN                    15
#define FXTEST2_MESSAGE_TO_USER             16

/*  This table contains each block in the form                               */

static byte fxtest2_blocks [] = {
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
    /*  <TITLE>Formatix Test Form 2</TITLE>                                  */
    0, 37, 0, '<', 'T', 'I', 'T', 'L', 'E', '>', 'F', 'o', 'r', 'm',
    'a', 't', 'i', 'x', 32, 'T', 'e', 's', 't', 32, 'F', 'o', 'r', 'm',
    32, '2', '<', '/', 'T', 'I', 'T', 'L', 'E', '>', 10,
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
    /*  <H1>Formatix Test Form 2</H1>                                        */
    0, 31, 0, '<', 'H', '1', '>', 'F', 'o', 'r', 'm', 'a', 't', 'i',
    'x', 32, 'T', 'e', 's', 't', 32, 'F', 'o', 'r', 'm', 32, '2', '<',
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
    /*  <P>This is the second of several test forms.                         */
    0, 46, 0, '<', 'P', '>', 'T', 'h', 'i', 's', 32, 'i', 's', 32, 't',
    'h', 'e', 32, 's', 'e', 'c', 'o', 'n', 'd', 32, 'o', 'f', 32, 's',
    'e', 'v', 'e', 'r', 'a', 'l', 32, 't', 'e', 's', 't', 32, 'f', 'o',
    'r', 'm', 's', '.', 10,
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
    0, 6, 0, '<', 'H', 'R', '>', 10,
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
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f3 NAME=L_f ... ong text field&nbsp;&nbsp;"         */
    0, 40, 10, 6, 1, 0, 0, 27, 0, 27, 'f', '3', 0, 'L', 'o', 'n', 'g',
    32, 't', 'e', 'x', 't', 32, 'f', 'i', 'e', 'l', 'd', '&', 'n', 'b',
    's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--FIELD TEXTUAL f4 NAME=fie ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 13, 10, 0, 1, 0, 0, 'P', 0, 'P', 'f', '4', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f5 NAME=L_f ... LUE="File name&nbsp;&nbsp;"         */
    0, 34, 10, 6, 1, 0, 0, 21, 0, 21, 'f', '5', 0, 'F', 'i', 'l', 'e',
    32, 'n', 'a', 'm', 'e', '&', 'n', 'b', 's', 'p', ';', '&', 'n', 'b',
    's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--FIELD TEXTUAL f6_tmp NAME ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 17, 10, 4, 1, 0, 0, 'P', 0, 'P', 'f', '6', '_', 't', 'm', 'p', 0,
    0, 0,
    /*  !--FIELD FILE f6 NAME=field-3 SIZE=80 MAX=? ATTR="" VALUE=""         */
    0, 12, 21, 0, 1, 0, 'P', 0, 'P', 'f', '6', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f7 NAME=L_f ... "Numeric field&nbsp;&nbsp;"         */
    0, 38, 10, 6, 1, 0, 0, 25, 0, 25, 'f', '7', 0, 'N', 'u', 'm', 'e',
    'r', 'i', 'c', 32, 'f', 'i', 'e', 'l', 'd', '&', 'n', 'b', 's', 'p',
    ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--FIELD NUMERIC f8 NAME=fie ... E=12 MAX=? ATTR="" VALUE=""         */
    0, 18, 11, 0, 1, 0, 12, 0, 12, 0, 0, 0, 0, 0, 0, 'f', '8', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f9 NAME=L_f ... Field number 3&nbsp;&nbsp;"         */
    0, 39, 10, 6, 1, 0, 0, 26, 0, 26, 'f', '9', 0, 'F', 'i', 'e', 'l',
    'd', 32, 'n', 'u', 'm', 'b', 'e', 'r', 32, '3', '&', 'n', 'b', 's',
    'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--FIELD DATE f10 NAME=field ... TH=? DAY=? ATTR="" VALUE=""         */
    0, 28, 12, 0, 1, 0, 15, 0, 1, 0, 0, 0, 'f', '1', '0', 0, 0, 'y',
    'y', 'y', 'y', 45, 'M', 'M', 'M', 45, 'd', 'd', 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f11 NAME=L_ ... UE="Parameters&nbsp;&nbsp;"         */
    0, 36, 10, 6, 1, 0, 0, 22, 0, 22, 'f', '1', '1', 0, 'P', 'a', 'r',
    'a', 'm', 'e', 't', 'e', 'r', 's', '&', 'n', 'b', 's', 'p', ';',
    '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--FIELD TEXTUAL f12 NAME=pa ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 10, 0, 1, 0, 0, '(', 0, '(', 'f', '1', '2', 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f13 NAME=L_ ... ALUE="Comments&nbsp;&nbsp;"         */
    0, 34, 10, 6, 1, 0, 0, 20, 0, 20, 'f', '1', '3', 0, 'C', 'o', 'm',
    'm', 'e', 'n', 't', 's', '&', 'n', 'b', 's', 'p', ';', '&', 'n',
    'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--FIELD TEXTBOX f14 NAME=co ... =? UPPER=0 ATTR="" VALUE=""         */
    0, 14, 14, 0, 1, 4, '(', 0, 0, 160, 'f', '1', '4', 0, 0, 0,
    /*  Free text                                                            */
    0, 11, 0, 'F', 'r', 'e', 'e', 32, 't', 'e', 'x', 't', 10,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
    /*  <TR><TD ALIGN=LEFT VALIGN=TOP NOWRAP CLASS=tdlabel>                  */
    0, 4, 1, 0, 4, 'J',
    /*  !--FIELD TEXTUAL f15 NAME=L_ ... oose an action&nbsp;&nbsp;"         */
    0, 42, 10, 6, 1, 0, 0, 28, 0, 28, 'f', '1', '5', 0, 'C', 'h', 'o',
    'o', 's', 'e', 32, 'a', 'n', 32, 'a', 'c', 't', 'i', 'o', 'n', '&',
    'n', 'b', 's', 'p', ';', '&', 'n', 'b', 's', 'p', ';', 0, 0,
    /*  </TD><TD VALIGN=TOP ALIGN=LEFT WIDTH="80%" CLASS=tdvalue>            */
    0, 4, 1, 0, 4, 172,
    /*  !--ACTION return  LABEL="Ret ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) return_event / 256), (byte) ((word)
    return_event & 255), 0, 0, 0, 0, 0, 0, 0, 'r', 'e', 't', 'u', 'r',
    'n', 0, 'R', 'e', 't', 'u', 'r', 'n', 0, 0, 0, 0, 0,
    /*  !--ACTION test_3  LABEL="Tes ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 30, 20, 0, 1, (byte) ((word) test_3_event / 256), (byte) ((word)
    test_3_event & 255), 0, 1, 0, 0, 0, 0, 0, 't', 'e', 's', 't', '_',
    '3', 0, 'T', 'e', 's', 't', 45, '3', 0, 0, 0, 0, 0,
    /*  !--ACTION process  LABEL="Pr ... FIRM="" ATTR="" TYPE=BUTTON         */
    0, 32, 20, 0, 1, (byte) ((word) process_event / 256), (byte) ((word)
    process_event & 255), 0, 2, 0, 0, 0, 0, 0, 'p', 'r', 'o', 'c', 'e',
    's', 's', 0, 'P', 'r', 'o', 'c', 'e', 's', 's', 0, 0, 0, 0, 0,
    /*  </TD></TR>                                                           */
    0, 4, 1, 0, 4, 248,
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

static FIELD_DEFN fxtest2_fields [] = {
    { 0, 1153, 28 },                    /*  l_field_1                       */
    { 30, 1257, 5 },                    /*  field_1                         */
    { 37, 1292, 27 },                   /*  l_field_2                       */
    { 66, 1340, 80 },                   /*  field_2                         */
    { 148, 1367, 21 },                  /*  l_field_3                       */
    { 171, 1409, 80 },                  /*  field_3_tmp                     */
    { 253, 1428, 80 },                  /*  field_3                         */
    { 335, 1454, 25 },                  /*  l_field_4                       */
    { 362, 1500, 12 },                  /*  field_4                         */
    { 376, 1532, 26 },                  /*  l_field_5                       */
    { 404, 1579, 8 },                   /*  field_5                         */
    { 414, 1621, 22 },                  /*  l_params                        */
    { 438, 1665, 40 },                  /*  params                          */
    { 480, 1693, 20 },                  /*  l_comments                      */
    { 502, 1735, 160 },                 /*  comments                        */
    { 664, 1776, 28 },                  /*  l_return                        */
    { 694, 1942, 120 },                 /*  message_to_user                 */
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
    byte   l_field_3_a          ;
    char   l_field_3            [21 + 1];
    byte   field_3_tmp_a        ;
    char   field_3_tmp          [80 + 1];
    byte   field_3_a            ;
    char   field_3              [80 + 1];
    byte   l_field_4_a          ;
    char   l_field_4            [25 + 1];
    byte   field_4_a            ;
    char   field_4              [12 + 1];
    byte   l_field_5_a          ;
    char   l_field_5            [26 + 1];
    byte   field_5_a            ;
    char   field_5              [8 + 1];
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
    byte   test_3_a;
    byte   process_a;
    } FXTEST2_DATA;

/*  The form definition collects these tables into a header                  */

static FORM_DEFN form_fxtest2 = {
    fxtest2_blocks,
    fxtest2_fields,
    74,                                 /*  Number of blocks in form        */
    17,                                 /*  Number of fields in form        */
    3,                                  /*  Number of actions in form       */
    816,                                /*  Size of fields                  */
    "fxtest2",                          /*  Name of form                    */
    };

#endif                                  /*  End included file               */

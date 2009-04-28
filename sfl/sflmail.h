/*===========================================================================*
 *                                                                           *
 *  sflmail.h - Generated file - do not modify                               *
 *                                                                           *
 *  Copyright (c) 1991-2003 iMatix Corporation                               *
 *                                                                           *
 *  ------------------ GPL Licensed Source Code ------------------           *
 *  iMatix makes this software available under the GNU General               *
 *  Public License (GPL) license for open source projects.  For              *
 *  details of the GPL license please see www.gnu.org or read the            *
 *  file license.gpl provided in this package.                               *
 *                                                                           *
 *  This program is free software; you can redistribute it and/or            *
 *  modify it under the terms of the GNU General Public License as           *
 *  published by the Free Software Foundation; either version 2 of           *
 *  the License, or (at your option) any later version.                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public                *
 *  License along with this program in the file 'license.gpl'; if            *
 *  not, write to the Free Software Foundation, Inc., 59 Temple              *
 *  Place - Suite 330, Boston, MA 02111-1307, USA.                           *
 *                                                                           *
 *  You can also license this software under iMatix's General Terms          *
 *  of Business (GTB) for commercial projects.  If you have not              *
 *  explicitly licensed this software under the iMatix GTB you may           *
 *  only use it under the terms of the GNU General Public License.           *
 *                                                                           *
 *  For more information, send an email to info@imatix.com.                  *
 *  --------------------------------------------------------------           *
 *===========================================================================*/
/*
    Synopsis:   Functions to format and send SMTP messages.  Messages
                can contain attachments, and be sent with "cc"'s "bcc"'s as
                well as the normal "to" receivers.
            
*/
#ifndef _sflmail_included               /*  allow multiple inclusions        */
#define _sflmail_included

typedef struct SMTP {
   char *strSmtpServer;
   char *strMessageBody;
   char *strHtmlMessageBody;
   char *strSubject;
   char *strSenderUserId;
   char *strFullSenderUserId;          /* to be filled with: "realname" <e-mail> */
   char *strDestUserIds;
   char *strFullDestUserIds;           /* to be filled with: "realname" <e-mail> */   
   char *strCcUserIds;
   char *strFullCcUserIds;             /* to be filled with: "realname" <e-mail> */
   char *strBccUserIds;
   char *strFullBccUserIds;
   char *strRetPathUserId;
   char *strRrcpUserId;
   char *strMsgComment;
   char *strMailerName;
   char *strBinFiles;
   char *strTxtFiles;
   char strlast_smtp_message[513];
   int  debug;
   char *strDebugFile;
   int  mime;
   int  encode_type;
   int  connect_retry_cnt;
   int  retry_wait_time;
} SMTP;

/* SMTP Error value                                                          */

#define SMTP_NO_ERROR                       0
#define SMTP_ERROR_CONNECT                  1
#define SMTP_ERROR_INIT                     2
#define SMTP_ERROR_INVALID_SENDER           3
#define SMTP_ERROR_INVALID_RECEIPT_USER     4
#define SMTP_ERROR_INVALID_DATA             5
#define SMTP_ERROR_MISSING_ATTACH_FILE      6
#define SMTP_ERROR_ON_CLOSE                 7
#define SMTP_ERROR_ON_QUIT                  8
#define SMTP_ERROR_MISSING_DESTINATION      9
#define SMTP_ERROR_MISSING_SUBJECT          10
#define SMTP_ERROR_MISSING_SERVER_NAME      11
#define SMTP_ERROR_MEMORY                   12

#define MAX_SMTP_ERROR                      13


#define ENCODE_BASE64                       0
#define ENCODE_UUENCODE                     1

/*  Function prototypes                                                      */

#ifdef __cplusplus
extern "C" {
#endif
int   smtp_send_mail_ex      (SMTP *smtp);
int   smtp_send_mail         (char *strSmtpServer,       char *strMessageBody,
                              char *strSubject,          char *strSenderUserId,
                              char *strFullSenderUserId, char *strDestUserIds,
                              char *strFullDestUserIds,  char *strCcUserIds,
                              char *strFullCcUserIds,    char *strBccUserIds,
                              char *strFullBccUserIds,   char *strRetPathUserId,
                              char *strRrcpUserId,       char *strMsgComment,
                              char *strMailerName,       char *strBinFiles,
                              char *strTxtFiles,         char *strDebugFile );
char *smtp_error_description (int error_value);

#ifdef __cplusplus
}
#endif

#endif


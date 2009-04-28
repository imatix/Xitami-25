/*===========================================================================*
 *                                                                           *
 *  sflmail.c -                                                              *
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
#include "prelude.h"                    /*  Universal header file            */
#include "sflstr.h"
#include "sflsock.h"
#include "sfldate.h"
#include "sflmem.h"
#include "sflmime.h"
#include "sflmail.h"

Bool sock_error_flag,
    sock_read_flag,
    sock_write_flag;

/*- Macros & defines --------------------------------------------------------*/

/*  Macro to encoding a char and make it printable.                          */
#define ENC(c) ((c) ? ((c) & 077) + ' ': '`')
/* Macro to write too the smtp port.                                         */
#define smtp_send_data(sock,strout)                                          \
      write_TCP((sock),(strout),strlen((strout)))


#define SMTP_SERVER_ERROR    400
#define BUFFER_SIZE          512        /* Maximum size of a line            */
#define LINE_SIZE            77

#define MESSAGE_BOUNDARY "----=_NextPart_000_0144_01BF935D.6B92FD20"

#define CLEAN_SEND_MAIL                                                         \
   close_socket (socket_handle);        /* Close the port up.                */ \
   ip_nonblock = iOld_ip_nonblock;                                              \
   sock_term ()

#define SEND_BODY                                                               \
       /* Escape dot in begin of message line                                */ \
       if (*smtp-> strMessageBody == '.'                                        \
       ||  (data = strstr (smtp-> strMessageBody, "\r\n.")) != NULL)            \
         {                                                                      \
           p_buffer = smtp-> strMessageBody;                                    \
           while (data)                                                         \
             {                                                                  \
               data += 2;                                                       \
               *data++ = '\0';                                                  \
               smtp_send_data (socket_handle, p_buffer);                        \
               smtp_send_data (socket_handle, "..");                            \
               p_buffer = data;                                                 \
               data = strstr (p_buffer, "\r\n.");                               \
             }                                                                  \
           if (strlen (p_buffer))                                               \
               smtp_send_data (socket_handle, p_buffer);                        \
         }                                                                      \
       else                                                                     \
           smtp_send_data (socket_handle, smtp-> strMessageBody);

/* Stactic function prototypes                                               */
static int   uuencode    (char *strin, char *strout, char *last_smtp_message);
static void  putgroup    (register char *strgroup, register FILE *fp);
static int   getreply    (sock_t socket_handle, SMTP *smtp);
static char *getfilename (char *strfullpath);

/*  ---------------------------------------------------------------------[<]-
    Function: smtp_send_mail_ex

    Synopsis: Format and send a SMTP message.  This function gives you the
    options of sneding to multi receivers, CC's, Bcc's and also send
    UUencoded attachments. Receivers and files are ";" or "," terminated.
    NOTE: The sock_init function should be called before use of this
    function.
    ---------------------------------------------------------------------[>]-*/

int smtp_send_mail_ex (
   SMTP *smtp)
{
   FILE
      *fpin;
   int
       iCnt;
   sock_t
       socket_handle;
   char
       strOut     [514],
       strFile    [256],
       strUUEFile [256],
       buffer     [BUFFER_SIZE + 1],
      *data,
      *p_buffer,
      *strRcptUserIds;
   int
       iOld_ip_nonblock = ip_nonblock,
       rcptUserIdsLen;
  long
      out_size,
      in_size;
  char
     *in_buf,
     *out_buf;

   /* Check required parameters                                              */
   if (smtp == NULL)
       return (SMTP_ERROR_CONNECT);
   if (smtp->strDestUserIds == NULL)
       return (SMTP_ERROR_MISSING_DESTINATION);
   if (smtp->strSubject == NULL)
       return (SMTP_ERROR_MISSING_SUBJECT);
   if (smtp->strSmtpServer == NULL)
       return (SMTP_ERROR_MISSING_SERVER_NAME);

   /*  Make sure we block on socket accesses                                 */
   ip_nonblock = FALSE;
   sock_init ();

   /* Open up the SMTP port (25 most of the time). */
   socket_handle = connect_socket (smtp-> strSmtpServer,
                                   "smtp", "tcp", NULL,
                                   smtp-> connect_retry_cnt,
                                   smtp-> retry_wait_time);

   if (socket_handle == INVALID_SOCKET 
   ||  getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
     {
       sock_term ();
       return (SMTP_ERROR_CONNECT);
     }
   /* Format a SMTP meassage header.                                         */
   /* Just say hello to the mail server.                                     */
   xstrcpy (strOut, "HELO ", get_hostname (), "\n", NULL);
   smtp_send_data (socket_handle, strOut);
   if (getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
       return (SMTP_ERROR_INIT);

   /* Tell the mail server who the message is from. */
   xstrcpy (strOut, "MAIL FROM:<", smtp-> strSenderUserId, ">\n", NULL);
   smtp_send_data (socket_handle, strOut);
   if (getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
     {
       CLEAN_SEND_MAIL;
       return (SMTP_ERROR_INVALID_SENDER);
     }
   rcptUserIdsLen = 0;
   if (smtp-> strDestUserIds)
       rcptUserIdsLen += strlen (smtp->strDestUserIds) + 1;
   if (smtp-> strCcUserIds)
       rcptUserIdsLen += strlen (smtp->strCcUserIds)   + 1;
   if (smtp-> strBccUserIds)
       rcptUserIdsLen += strlen (smtp->strBccUserIds)  + 1;

   strRcptUserIds = (char *) mem_alloc (rcptUserIdsLen);
   p_buffer = strRcptUserIds;
   data = smtp-> strDestUserIds;
   while (*data)
       *p_buffer++ = *data++;
   if (smtp-> strCcUserIds)
     {
       *p_buffer++ = ';';
       data = smtp-> strCcUserIds;
       while (*data)
           *p_buffer++ = *data++;
     }   
   if (smtp-> strBccUserIds)
     {
       *p_buffer++ = ';';
       data = smtp-> strBccUserIds;
       while (*data)
           *p_buffer++ = *data++;
     }   
   *p_buffer = '\0';

   /* The following tells the mail server who to send it to.                 */
   iCnt = 0;
   FOREVER
     {
       getstrfld (strRcptUserIds, iCnt++, 0, ",;", buffer);

       if (*buffer)
         {
           xstrcpy (strOut, "RCPT TO:<", buffer, ">\r\n", NULL);
           smtp_send_data (socket_handle, strOut);
           if (getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
             {
               CLEAN_SEND_MAIL;
               return (SMTP_ERROR_INVALID_RECEIPT_USER);
             }
         }

       else
           break;
     }

   mem_free (strRcptUserIds);

   /* Now give it the Subject and the message to send.                       */
   smtp_send_data (socket_handle, "DATA\r\n");
   if (getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
     {
       CLEAN_SEND_MAIL;
       return (SMTP_ERROR_INVALID_DATA);
     }

   /* Set the date and time of the message.                                  */
   xstrcpy ( strOut, "Date: ", encode_mime_time (date_now (), time_now ()),
             " \r\n", NULL );

   /* The following shows all who it was sent to. */
   if ( smtp-> strFullDestUserIds && *smtp-> strFullDestUserIds )
    {
       replacechrswith (smtp-> strFullDestUserIds, ";", ',');
       xstrcpy (strOut, "To: ", smtp-> strFullDestUserIds, "\r\n", NULL);
     }
   else
    {
       replacechrswith (smtp-> strDestUserIds, ";", ',');
       xstrcpy (strOut, "To: ", smtp-> strDestUserIds, "\r\n", NULL);
    }

   /* Set up the Reply-To path. */
   if (!smtp-> strRetPathUserId || !*smtp-> strRetPathUserId)
       smtp-> strRetPathUserId = smtp-> strSenderUserId;

   if ( strstr( smtp-> strRetPathUserId, "<" ) != NULL &&
        strstr( smtp-> strRetPathUserId, ">" ) != NULL )
       xstrcat (strOut, "Reply-To:",  smtp-> strRetPathUserId, "\r\n", NULL);
   else
       xstrcat (strOut, "Reply-To:<", smtp-> strRetPathUserId, ">\r\n", NULL);

   if ( smtp-> strFullSenderUserId && *smtp-> strFullSenderUserId )
     {
       xstrcat (strOut, "Sender:", smtp-> strFullSenderUserId, "\r\n", NULL);
       xstrcat (strOut, "From:",   smtp-> strFullSenderUserId, "\r\n", NULL);
     }
   else
     {
       xstrcat (strOut, "Sender:", smtp-> strSenderUserId, "\r\n", NULL);
       xstrcat (strOut, "From:",   smtp-> strSenderUserId, "\r\n", NULL);
     }
   smtp_send_data (socket_handle, strOut);

   *strOut = '\0';

   /* Post any CC's. */
   if (smtp->strFullCcUserIds && *smtp->strFullCcUserIds)
     {
       replacechrswith (smtp->strFullCcUserIds, ";", ',');
       xstrcat (strOut, "Cc:", smtp->strFullCcUserIds, "\r\n", NULL );
     }
   else
   if (smtp->strCcUserIds && *smtp->strCcUserIds)
     {
       replacechrswith (smtp->strCcUserIds, ";", ',');
       xstrcat (strOut, "Cc:", smtp->strCcUserIds, "\r\n", NULL );
     }

   /* Post any BCC's. */
   if (smtp->strFullBccUserIds && *smtp->strFullBccUserIds)
     {
       replacechrswith (smtp->strFullBccUserIds, ";", ',');
       xstrcat (strOut, "Bcc:", smtp->strFullBccUserIds, "\r\n", NULL);
     }
   else
   if (smtp->strBccUserIds && *smtp->strBccUserIds)
     {
       replacechrswith (smtp->strBccUserIds, ";", ',');
       xstrcat (strOut, "Bcc:", smtp->strBccUserIds, "\r\n", NULL);
     }
   /* Post any Return-Receipt-To. */
   if (smtp->strRrcpUserId && *smtp->strRrcpUserId)
       xstrcat (strOut, "Return-Receipt-To:", smtp->strRrcpUserId, ">\r\n",
                NULL);

   if (smtp->strMailerName && *smtp->strMailerName)
       xstrcat (strOut, "X-Mailer: ", smtp->strMailerName, "\r\n", NULL);
   else
       strcat  (strOut, "X-Mailer: sflmail function\r\n");

   /* Set the mime version. */
   xstrcat (strOut, "MIME-Version: 1.0\r\n",
           "Content-Type: Multipart/Mixed; boundary=\"", MESSAGE_BOUNDARY,"\"\r\n",
            NULL);

   smtp_send_data (socket_handle, strOut);

   *strOut = '\0';
   /* Write out any message comment included. */
   if (smtp->strMsgComment && *smtp->strMsgComment)
       xstrcpy (strOut, "Comments: ", smtp->strMsgComment, "\r\n", NULL);

   /* Send the subject and message body. */
   xstrcat (strOut, "Subject:", smtp->strSubject, "\r\n\r\n", NULL);
   smtp_send_data (socket_handle, strOut);

   /* Keep rfc822 in mind with all the sections.                             */
   if (smtp->strMessageBody && *smtp->strMessageBody)
     {
	   /* check if we got html/alternate files                               */
	   if ( smtp->strHtmlMessageBody && *smtp->strHtmlMessageBody )
         {
           xstrcpy (strOut,
                    "\r\n--", MESSAGE_BOUNDARY, "\r\n",
		            "Content-Type: multipart/alternative; \r\n",
		            "        boundary=\"", MESSAGE_BOUNDARY, "\"\r\n",
                    "\r\n--", MESSAGE_BOUNDARY, "\r\n", NULL);
           smtp_send_data (socket_handle, strOut);
           xstrcpy (strOut,
                    "Content-Type: text/plain; charset=US-ASCII\r\n",
                    "Content-Transfer-Encoding: 7BIT\r\n",
                    "Content-description: Body of message\r\n\r\n", NULL);
           smtp_send_data (socket_handle, strOut);
           SEND_BODY;
           xstrcpy (strOut,
                    "\r\n\r\n--", MESSAGE_BOUNDARY, "\r\n",
                    "Content-Type: text/html; charset=US-ASCII\r\n",
                    "Content-Transfer-Encoding: 7BIT\r\n",
                    "Content-description: Body of message\r\n\r\n", NULL);
		   smtp_send_data (socket_handle, strOut);
		   smtp_send_data (socket_handle, smtp->strHtmlMessageBody);
           xstrcpy (strOut, "\r\n--", MESSAGE_BOUNDARY, "--\r\n", NULL);
		   smtp_send_data (socket_handle, strOut);
         }
       else
         {
           xstrcpy (strOut,
                    "\r\n--", MESSAGE_BOUNDARY, "\r\n",
                    "Content-Type: text/plain; charset=US-ASCII\r\n",
                    "Content-Transfer-Encoding: 7BIT\r\n",
                    "Content-description: Body of message\r\n\r\n", NULL);
           smtp_send_data (socket_handle, strOut);
           SEND_BODY;
           smtp_send_data (socket_handle, "\r\n\r\n");
         }
     }
   /* Include any Text type files and Attach them to the message. */
   if (smtp->strTxtFiles && *smtp->strTxtFiles)
     {
       iCnt = 0;
       FOREVER
         {
           getstrfld (smtp->strTxtFiles, iCnt++, 0, ",;", strFile);
           trim (strFile);
           if (*strFile)
             {
               fpin = fopen (strFile, "rb");
               if (!fpin)
                 {
                   strcpy (smtp->strlast_smtp_message, strFile);
                     {
                       CLEAN_SEND_MAIL;
                       return (SMTP_ERROR_MISSING_ATTACH_FILE);
                     }
                 }

               xstrcpy (strOut, "\r\n--", MESSAGE_BOUNDARY, "\r\n",
                       "Content-Type: text/plain; charset=US-ASCII\r\n",
                       "Content-Transfer-Encoding: 7BIT\r\n",
                       "Content-Disposition: attachment; filename=",
                        getfilename (strFile), "\r\n\r\n", NULL);
               smtp_send_data (socket_handle, strOut);
               while (fgets (buffer, BUFFER_SIZE, fpin))
                 {
                   if (*buffer == '.')
                       write_TCP (socket_handle, ".", 1);
                   smtp_send_data (socket_handle, buffer);
                 }
               fclose (fpin);
             }
           else
               break;
         }
     }

   /* Attach any bin files to the message. */
   if (smtp->strBinFiles && *smtp->strBinFiles)
     {
       iCnt = 0;
       FOREVER
         {
           getstrfld (smtp->strBinFiles, iCnt++, 0, ",;", strFile);
           trim (strFile);
           if (*strFile)
             {
               if (smtp-> encode_type == ENCODE_BASE64)
                 {
                   fpin = fopen (strFile, "rb");
                   if (fpin)
                     {
                       /* Get file size                                      */
                       fseek (fpin, 0, SEEK_END);
                       in_size = ftell (fpin);
                       fseek (fpin, 0, SEEK_SET);
                       /* Alloc conversion buffer                            */
                       in_buf  = mem_alloc (in_size + 1);
                       out_buf = mem_alloc ((int)(in_size * 1.4));
                       if (in_buf && out_buf)
                         {
                           xstrcpy (strOut, "\r\n--", MESSAGE_BOUNDARY, "\r\n",
                                    "Content-Type: application/octet-stream; name=",
                                     getfilename (strFile), "\r\n", 
                                     "Content-Transfer-Encoding: base64\r\n",
                                     "Content-Disposition: attachment; filename=",
                                     getfilename (strFile), "\r\n\r\n", NULL);
                           smtp_send_data (socket_handle, strOut);
                           in_size = fread (in_buf, 1, in_size, fpin);
                           out_size = encode_base64 (in_buf, out_buf, in_size);
    
                           /* Format Encoded buffer into line                   */
                           p_buffer = out_buf;
                           while (out_size > 0)
                             {
                               if (out_size > LINE_SIZE)
                                 {
                                   write_TCP (socket_handle, p_buffer, LINE_SIZE);
                                   write_TCP (socket_handle, "\r\n",  2);
                                   out_size -= LINE_SIZE;
                                   p_buffer += LINE_SIZE;
                                 }
                               else
                                 {
                                   write_TCP (socket_handle, p_buffer, out_size);
                                   write_TCP (socket_handle, "\r\n",  2);
                                   out_size = 0;
                                 }
                             }
                         }
                       else
                         {
                           if (in_buf)  mem_free (in_buf);
                           if (out_buf) mem_free (out_buf);
                           CLEAN_SEND_MAIL;
                           return (SMTP_ERROR_MEMORY);
                         }
                       if (in_buf)  mem_free (in_buf);
                       if (out_buf) mem_free (out_buf);
                       fclose (fpin);
                     }
                   else
                     {
                       CLEAN_SEND_MAIL;
                       return (SMTP_ERROR_MISSING_ATTACH_FILE);
                     }
                 }
               else
                 {
                   strcpy (strUUEFile, strFile);
                   if (strchr (strUUEFile, '.'))
                       *((strchr (strUUEFile, '.')))= (char)NULL;
                   strcat (strUUEFile, ".uue");
                   uuencode (strFile, strUUEFile, smtp->strlast_smtp_message);
                   fpin = fopen (strUUEFile, "rb");
                   if (!fpin)
                     {
                       CLEAN_SEND_MAIL;
                       return (SMTP_ERROR_MISSING_ATTACH_FILE);
                     }
                   xstrcpy (strOut, "\r\n--", MESSAGE_BOUNDARY, "\r\n",
                            "Content-Type: application/octet-stream; name=",
                             getfilename (strFile), "\r\n", 
                            "Content-Transfer-Encoding: x-uuencode\r\n",
                            "Content-Disposition: attachment; filename=",
                            getfilename (strFile), "\r\n\r\n", NULL);
                   smtp_send_data (socket_handle, strOut);
                   while (fgets (buffer, BUFFER_SIZE, fpin))
                     {
                       if (*buffer == '.')
                           write_TCP (socket_handle, ".", 1);
                       smtp_send_data (socket_handle, buffer);
                     }
                   fclose (fpin);
    
                   if ( !smtp->debug )
                      unlink (strUUEFile);
                 }
             }
           else
               break;
         }
     }

   /* This ends the message. */
   xstrcpy (strOut, "\r\n--", MESSAGE_BOUNDARY, "--\r\n\r\n.\r\n", NULL);
   smtp_send_data (socket_handle, strOut);
   if (getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
     {
        CLEAN_SEND_MAIL;
        return (SMTP_ERROR_ON_CLOSE);
     }

   /* Now log off the SMTP port. */
   smtp_send_data (socket_handle, "QUIT\r\n");
   if (getreply (socket_handle, smtp) > SMTP_SERVER_ERROR)
     {
        CLEAN_SEND_MAIL;
        return (SMTP_ERROR_ON_QUIT);
     }

   CLEAN_SEND_MAIL;
   return 0;
}

/*  ---------------------------------------------------------------------[<]-
    Function: smtp_send_mail

    Synopsis: Format and send a SMTP message, by calling the
    smtp_send_mail_ex function.  This function is kept to be compatable
    with previous versions of smtp_send_mail, smtp_send_mail_ex should
    now be used, this will be deleted soon.
    ---------------------------------------------------------------------[>]-*/

int smtp_send_mail (
   char *strSmtpServer,
   char *strMessageBody,
   char *strSubject,
   char *strSenderUserId,
   char *strFullSenderUserId,
   char *strDestUserIds,
   char *strFullDestUserIds,
   char *strCcUserIds,
   char *strFullCcUserIds,
   char *strBccUserIds,
   char *strFullBccUserIds,
   char *strRetPathUserId,
   char *strRrcpUserId,
   char *strMsgComment,
   char *strMailerName,
   char *strBinFiles,
   char *strTxtFiles,
   char *strDebugFile )
{
   SMTP smtp;

   memset (&smtp, 0, sizeof (SMTP));

   smtp.strSmtpServer       = strSmtpServer;
   smtp.strMessageBody      = strMessageBody;
   smtp.strSubject          = strSubject;
   smtp.strSenderUserId     = strSenderUserId;
   smtp.strFullSenderUserId = strFullSenderUserId;
   smtp.strDestUserIds      = strDestUserIds;
   smtp.strFullDestUserIds  = strFullDestUserIds;
   smtp.strCcUserIds        = strCcUserIds;
   smtp.strFullCcUserIds    = strFullCcUserIds;
   smtp.strBccUserIds       = strBccUserIds;
   smtp.strFullBccUserIds   = strFullBccUserIds;
   smtp.strRetPathUserId    = strRetPathUserId;
   smtp.strRrcpUserId       = strRrcpUserId;
   smtp.strMsgComment       = strMsgComment;
   smtp.strMailerName       = strMailerName;
   smtp.strBinFiles         = strBinFiles;
   smtp.strTxtFiles         = strTxtFiles;
   smtp.connect_retry_cnt   = 3;
   smtp.retry_wait_time     = 0;
   smtp.debug               = 0;
   smtp.strDebugFile        = strDebugFile;
   smtp.encode_type         = ENCODE_BASE64;

   return smtp_send_mail_ex (&smtp);
}

/*
 *  uuencode -- internal
 *
 *  Synopsis: Uuencode a file, with the output going to a new file. This
 *  function is used by smtp_send_mail.
 * -------------------------------------------------------------------------*/

static int uuencode (
   char *strIn,
   char *strOut,
   char *strlast_smtp_message)
{
   char strLine[46];
   int iCnt, iLineLen;
   FILE *fpin, *fpout;

   if (!(fpin = fopen (strIn, "rb")))
     {
       strcpy (strlast_smtp_message, strIn);
       return 1;
     }

   if (!(fpout = fopen (strOut, "wb")))
     {
       fclose (fpin);
       strcpy (strlast_smtp_message, "Could not create temp file for write.");
       return 1;
     }

   fprintf (fpout, "begin 666 %s\n", getfilename (strIn));

   while (1)
     {
       iLineLen = fread (strLine, sizeof (char), 45, fpin);
       if (iLineLen <= 0)
           break;

       fputc (ENC (iLineLen), fpout);

       for (iCnt = 0; iCnt < iLineLen; iCnt += 3)
         {
           putgroup (&strLine[iCnt], fpout);
         }

       fputc ('\n', fpout);
     }

   fprintf (fpout, "end\n");

   fclose (fpin);
   fclose (fpout);
   return 0;
}

/*
 *  putgroup -- internal
 *
 *  Synopsis: Write out 3 char group to uuendcoded file making it
 *  printable  This function is used by uuencode.
 * -------------------------------------------------------------------------*/

static void putgroup (
   char *strgroup,
   FILE *fp)
{
    register byte ichr1, ichr2, ichr3, ichr4;

    ichr1 =   strgroup [0] >> 2;
    ichr2 = ((strgroup [0] << 4) & 0x30) | ((strgroup [1] >> 4) & 0x0f);
    ichr3 = ((strgroup [1] << 2) & 0x3c) | ((strgroup [2] >> 6) & 0x03);
    ichr4 =   strgroup [2] & 0x3f;

    fputc (ENC (ichr1), fp);
    fputc (ENC (ichr2), fp);
    fputc (ENC (ichr3), fp);
    fputc (ENC (ichr4), fp);
}

/*
 *  getreply -- internal
 *
 *  Synopsis: Get a reply from the SMTP server and see thats it's not
 *  an error. This function is used by smtp_send_mail.
 * -------------------------------------------------------------------------*/

static int 
getreply (sock_t socket_handle, SMTP *smtp)
{
    int
       read_size;
    FILE
      *fpout;
    char
       buffer [512 + 1];

    read_size = read_TCP (socket_handle, buffer, 512);
    /* See if we have not gotten a responce back from the mail server. */
    if (read_size == 0)
        return 777;
    else
        buffer [read_size] = '\0';

    /* Save off server reply. */
    strcpy (smtp-> strlast_smtp_message, buffer);
    trim (buffer);
    buffer [3] = '\0';

    if (smtp->debug && smtp->strDebugFile && *smtp->strDebugFile)
      {
        if ((fpout = fopen (smtp->strDebugFile, "a")))
          {
            fputs (smtp->strlast_smtp_message, fpout );
            fclose (fpout);
          }
      }
   return atoi (buffer);
}

/*
 *  getfilename -- internal
 *
 *  Synopsis: Get's the name from the full path of a file. This function
 *  is used by smtp_send_mail.
 * -------------------------------------------------------------------------*/

static char *getfilename (
   char *strFullPath)
{
   int iLen;
   char *strTmp;

   iLen = strlen (strFullPath);
   strTmp = (strFullPath + iLen);
   while (1)
     {
       if (*strTmp == PATHEND || !iLen)
           break;
       strTmp--;
       iLen--;
     }

   if (*strTmp == PATHEND)
       strTmp++;

   return strTmp;
}


/*  ---------------------------------------------------------------------[<]-
    Function: smtp_error_description

    Synopsis: Get error description
    ---------------------------------------------------------------------[>]-*/

char *
smtp_error_description (int error_value)
{
    static char * smtp_error [] = {
        "No Error",
        "Error on connect, verify smtp server name",
        "Error on init, smtp server refuse you post",
        "Invalid sender value",
        "Invalid receipt user",
        "Invalid data value", 
        "Error in name of attach file(s), i can't open",
        "Error on close transaction",
        "Error on Quit transaction",
        "Missing Destination value",
        "Missing Subject",
        "Missing Server name",
        "Error in memory allocation, Free some resource and try again"
    };

    if (error_value >= 0
    &&  error_value <  MAX_SMTP_ERROR)
        return (smtp_error [error_value]);
    else
        return ("");
}


/*===========================================================================*
 *                                                                           *
 *  wtplib.h - WTP interface functions                                       *
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

#ifndef _WTPLIB_INCLUDED		/*  Allow multiple inclusions	     */
#define _WTPLIB_INCLUDED


/*  Prototypes								     */

#ifdef __cplusplus
extern "C" {
#endif

void   wtp_open       (const char *version, const char *protocol,
		       const char *port);
void   wtp_close      (void);
void   wtp_connect    (const char *callback, const char *filename);
void   wtp_register   (const char *program, Bool is_root);
void   wtp_ready      (void);
void   wtp_doneshow   (const char *html_data,
		       qbyte global_size, const byte *global_data,
		       qbyte local_size, const byte *local_data);
void   wtp_donecall   (const char *program,
		       qbyte args_size,  const byte *args_data,
		       qbyte global_size, const byte *global_data,
		       qbyte local_size, const byte *local_data);
void   wtp_donereturn (qbyte args_size,  const byte *args_data,
		       qbyte global_size, const byte *global_data);
void   wtp_doneexit   (void);
void   wtp_doneerror  (const char *message);
void   wtp_error      (dbyte error_code, const char *error_text);
void   wtp_write      (const byte *buffer, size_t size);
size_t wtp_read       (byte **buffer);
Bool   wtp_expect_ok  (void);
qbyte  wtp_signature  (const char *filename);

#ifdef __cplusplus
}
#endif


/*  Messages								     */

#define WTP_OK		       1	/*  Request suceeded		     */
#define WTP_ERROR	       2	/*  Request failed		     */
#define WTP_CONNECT	       3	/*  Connects to the WTP manager      */
#define WTP_DISCONNECT	       4	/*  Disconnect from the WTP manager  */
#define WTP_REGISTER	       5	/*  Registers a program 	     */
#define WTP_READY	       6	/*  Signal ready for work	     */
#define WTP_DO		       7	/*  Execute some program	     */
#define WTP_DELETE	       8	/*  Get context block		     */
#define WTP_GET 	       9	/*  Get context block		     */
#define WTP_CONTEXT	       10	/*  Supply context block	     */
#define WTP_PUT 	       11	/*  Put context block		     */
#define WTP_DONESHOW	       12	/*  End program, show HTML form      */
#define WTP_DONECALL	       13	/*  End program, call new program    */
#define WTP_DONERETURN	       14	/*  End program, return to caller    */
#define WTP_DONEEXIT	       15	/*  End program, exit application    */
#define WTP_DONEERROR	       16	/*  End program, fatal error	     */


/*  Error codes 							     */

#define WTP_NOERROR	       0	/*  No error			     */
#define WTP_ERRORDUPLICATE     1	/*  Context block already exists     */
#define WTP_ERRORFATAL	       2	/*  WTP manager could not continue   */
#define WTP_ERRORINVALID       3	/*  Invalid message type	     */
#define WTP_ERRORNOTFOUND      4	/*  Program is not known	     */
#define WTP_ERROROVERFLOW      5	/*  Too many active programs	     */
#define WTP_ERRORSIGNATURE     6	/*  ATP signature has changed	     */
#define WTP_ERRORUNAUTHORISED  7	/*  An invalid callback key supplied */
#define WTP_ERRORUNAVAILABLE   8	/*  Program is no longer available   */
#define WTP_ERRORUNCONNECTED   9	/*  WTP_CONNECT not sent, or failed  */
#define WTP_ERRORUNEXPECTED   10	/*  Not valid at this point	     */
#define WTP_ERRORWOULDLOOP    11	/*  Program is already active parent */

/*  Entry codes 							     */

#define WTP_DOINIT	       1	/*  Initialise the program	     */
#define WTP_DOGET	       2	/*  Process HTML form data	     */
#define WTP_DOCONTINUE	       3	/*  Continue from called program     */


#endif					/*  Include wtpdefn.h		     */

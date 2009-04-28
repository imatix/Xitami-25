/*===========================================================================*
 *                                                                           *
 *  ctxman.h - Context management functions                                  *
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

#ifndef _CTXMAN_INCLUDED                /*  Allow multiple inclusions        */
#define _CTXMAN_INCLUDED


SYMTAB *context_init    (int scope);
void    context_term    (int scope);
SYMTAB *context_addr    (int scope);
char   *context_key     (const char *format, ...);
Bool    context_put     (int scope, const char *key,
                         const void *source, size_t length);
Bool    context_get     (int scope, const char *key,
                         void *dest, size_t length);
Bool    context_putsym  (int scope, const char *key, const SYMTAB *symtab);
Bool    context_getsym  (int scope, const char *key, SYMTAB **symtab);


/*  These macros provide external names for these functions                  */

#define CONTEXT_PUTL(k,s,l)  context_put (SCOPE_LOCAL,  (k), (s), (l))
#define CONTEXT_PUTG(k,s,l)  context_put (SCOPE_GLOBAL, (k), (s), (l))
#define CONTEXT_GETL(k,s,l)  context_get (SCOPE_LOCAL,  (k), (s), (l))
#define CONTEXT_GETG(k,s,l)  context_get (SCOPE_GLOBAL, (k), (s), (l))


/*  Context scopes                                                           */

enum {
    SCOPE_GLOBAL = 1,                   /*  Global context block             */
    SCOPE_LOCAL  = 2                    /*  Program-local context block      */
};


#endif

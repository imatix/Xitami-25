/*===========================================================================*
 *                                                                           *
 *  ctxman.c - Context management functions                                  *
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

#include "sfl.h"                        /*  SFL prototypes & definitions     */
#include "ctxman.h"                     /*  Function prototypes              */


/*- Local function prototypes -----------------------------------------------*/

static SYMBOL *context_lookup   (int scope, const char *key);

static char
    cur_key [LINE_MAX + 2] = "";        /*  Formatted by cgictx_key()        */
static SYMTAB
    *global_context = NULL,             /*  Global context table             */
    *local_context  = NULL;             /*  Local context table              */


/*  ---------------------------------------------------------------------[<]-
    Function: context_init

    Synopsis: Initialises the specified context table.  Normally not used
    in user programs.  Returns allocated symbol table.
    ---------------------------------------------------------------------[>]-*/

SYMTAB *
context_init (int scope)
{
    SYMTAB
        **table;                        /*  Context symbol table             */

    table = scope == SCOPE_GLOBAL? &global_context: &local_context;
    context_term (scope);
    *table = sym_create_table ();
    return (*table);
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_term

    Synopsis: Terminates the specified context table, releasing all memory
    back to the heap.  Normally not used in user programs.
    ---------------------------------------------------------------------[>]-*/

void
context_term (scope)
{
    SYMTAB
        **table;                        /*  Context symbol table             */
    SYMBOL
        *symbol;                        /*  Symbol in table                  */

    table = scope == SCOPE_GLOBAL? &global_context: &local_context;
    if (*table)
      {
        symbol = (*table)-> symbols;
        while (symbol)
          {
            mem_free (symbol-> data);
            symbol = symbol-> next;
          }
        sym_delete_table (*table);
        *table = NULL;
      }
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_addr

    Synopsis: Returns the address of the specified context table.  Normally
    not used in user programs.
    ---------------------------------------------------------------------[>]-*/

SYMTAB *
context_addr (int scope)
{
    return (scope == SCOPE_GLOBAL? global_context: local_context);
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_key

    Synopsis: Formats a key for the following context operation.  The key is
    held in a static area that remains valid until the next context_key()
    call.  The arguments to context_key() are as for printf().  If the
    formatted key is too long (> LINE_MAX characters) the program aborts
    with an assertion failure.  Returns the formatted key.
    ---------------------------------------------------------------------[>]-*/

char *
context_key (
    const char *format,
    ...)
{
    va_list
        argptr;                         /*  Argument list pointer            */

    cur_key [LINE_MAX + 1] = (char) 0xFA;

    va_start (argptr, format);          /*  Start variable arguments list    */
    vsprintf (cur_key, format, argptr);
    va_end   (argptr);                  /*  End variable arguments list      */

    ASSERT (cur_key [LINE_MAX + 1] == (char) 0xFA);
    return (cur_key);
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_put

    Synopsis: Writes a block of context.  If the scope is SCOPE_LOCAL,
    the block is local to the currently-active program.  If the scope is
    SCOPE_GLOBAL, the block is global to all programs.  The key is an
    arbitrary non-NULL case-sensitive string.  Overwrites any previous
    context block with the same key.  The length may be zero or greater;
    if zero, the context is not stored, and any previous context block
    with the same name is deleted.  Returns TRUE if there was no error; if
    there was a problem (e.g. insufficient memory), returns FALSE.  This
    may be interpreted as a fatal error. If the key argument is NULL, uses
    the last context_key() result.
    ---------------------------------------------------------------------[>]-*/

Bool
context_put (
    int scope,
    const char *key,
    const void *source,
    size_t length)
{
    SYMTAB
        *table;
    SYMBOL
        *symbol;

    /*  Look in appropriate symbol table                                     */
    table  = scope == SCOPE_GLOBAL? global_context: local_context;
    symbol = sym_assume_symbol (table, key? key: cur_key, NULL);
    if (symbol-> data)
        mem_free (symbol-> data);
    symbol-> data = (void *) mem_descr ((byte *) source, length);
    return (symbol-> data != NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_get

    Synopsis: Reads a block of context.  If the scope is SCOPE_LOCAL,
    the block is local to the currently-active program.  If the scope is
    SCOPE_GLOBAL, the block is global to all programs.  The key is an
    arbitrary non-NULL case-sensitive string.  The read block is stored
    at the specified address, up to the specified length.  If the read
    block is shorter than the length, the extra bytes are filled with
    binary zeroes.
    Returns 1 if the block was found, 0 if the block was not found (in
    which case the destination memory is not changed).  If the key
    argument is NULL, uses the last context_key() result.
    ---------------------------------------------------------------------[>]-*/

Bool
context_get (
    int scope,
    const char *key,
    void *dest,
    size_t length)
{
    SYMBOL
        *symbol;
    DESCR
        *descr;

    symbol = context_lookup (scope, key);
    if (symbol)
      {
        /*  If receiving block is too large, pad with binary zeroes          */
        descr = (DESCR *) symbol-> data;
        if (descr-> size < length)
          {
            memcpy (dest, descr-> data, descr-> size);
            memset ((byte *) dest + descr-> size, 0, length - descr-> size);
          }
        else
            /*  Else copy as much as we can                                  */
            memcpy (dest, descr-> data, length);
      }
    return (symbol != NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_putsym

    Synopsis: As context_put(), but operates on an entire symbol table; the
    symbol table is stored entirely in the context, under the specified key.
    If the symbol table argument is NULL, does nothing.
    ---------------------------------------------------------------------[>]-*/

Bool
context_putsym (
    int scope,
    const char *key,
    const SYMTAB *symtab)
{
    SYMTAB
        *table;
    SYMBOL
        *symbol;
    DESCR
        *descr = NULL;

    if (symtab)
      {
        /*  Look in appropriate symbol table                                 */
        table  = scope == SCOPE_GLOBAL? global_context: local_context;
        descr  = symb2descr (symtab);
        symbol = sym_assume_symbol (table, key? key: cur_key, NULL);
        if (symbol-> data)
            mem_free (symbol-> data);
        symbol-> data = descr;
      }
    return (descr != NULL);
}


/*  ---------------------------------------------------------------------[<]-
    Function: context_getsym

    Synopsis: As context_get(), but operates on an entire symbol table.
    If the specified table is found, sets the symtab argument to a newly
    created symbol table containing the specified data.  If the specified
    table is not found, sets the symtab argument to NULL.  Returns TRUE if
    the table was found, else FALSE.
    ---------------------------------------------------------------------[>]-*/

Bool
context_getsym (
    int scope,
    const char *key,
    SYMTAB **symtab)
{
    SYMBOL
        *symbol;

    symbol = context_lookup (scope, key);
    if (symbol)
        *symtab = descr2symb ((DESCR *) symbol-> data);
    else
        *symtab = NULL;

    return (symbol != NULL);
}



/*  --------------------------------------------------------------------------
 *  context_lookup -- internal
 *
 *  Searches for a context block as specified; if found, returns a pointer
 *  to the context symbol block.  If not found, returns NULL.
 */

static SYMBOL *
context_lookup (
    int scope,
    const char *key)
{
    SYMTAB
        *table;
    SYMBOL
        *symbol;

    /*  Look in appropriate symbol table                                     */
    table  = scope == SCOPE_GLOBAL? global_context: local_context;
    symbol = sym_lookup_symbol (table, key? key: cur_key);

    /*  If symbol found, check it has a valid context block                  */
    if (symbol)
      {
        ASSERT (symbol-> data);
      }
    return (symbol);
}

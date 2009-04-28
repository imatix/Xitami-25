/*===========================================================================*
 *                                                                           *
 *  sflxml.h - Generated file - do not modify                                *
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
    Synopsis:   Provides functions to read and write XML files, and manipulate
                XML data in memory as list structures.  XML is the Extensible
                Markup Language.  Accepts this XML syntax:
                <item [attr=["]value["]]...>value [child]</item>

*/
#ifndef SLFXML_INCLUDED                /*  Allow multiple inclusions        */
#define SLFXML_INCLUDED

/* -------------------------------------------------------------------------
    An XML tree is built as the following recursive structure:

                   .---------.    .----------.
                 .-:  Attr   :<-->:   0..n   :  Attributes are not sorted.
    .----------. : :  Head   :    :   attrs  :
    :   Item   :-' `---------'    `----------'
    :   node   :-. .---------.    .----------.
    `----------' : :  Child/ :<-->:   0..n   :  Each child node is the root
                 `-:  Value  :    : children :  of its own tree of nodes.
                   `---------'    `----------'
   ------------------------------------------------------------------------- */


/*- Structure definitions -------------------------------------------------- */

typedef struct _XML_ITEM XML_ITEM;
typedef struct _XML_ATTR XML_ATTR;


/*- Function prototypes ---------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/*  XML item functions */
XML_ITEM *xml_new          (XML_ITEM *parent,
                            const char *name,
                            const char *value);

XML_ITEM *xml_create       (const char *name,
                            const char *value);
void      xml_modify_value (XML_ITEM *item,
                            const char *value);
void      xml_rename       (XML_ITEM *item,
                            const char *name);
char     *xml_item_name    (XML_ITEM *item);
char     *xml_item_value   (XML_ITEM *item);
char     *xml_item_child_value (XML_ITEM *item);
void      xml_free         (XML_ITEM *item);

/*  XML tree manipulation  */
void      xml_attach_child   (XML_ITEM *parent,  XML_ITEM *item);
void      xml_attach_sibling (XML_ITEM *sibling, XML_ITEM *item);
void      xml_detach         (XML_ITEM *item);

/*  XML family navigation  */
XML_ITEM *xml_first_child  (XML_ITEM *item);
XML_ITEM *xml_last_child   (XML_ITEM *item);
XML_ITEM *xml_next_sibling (XML_ITEM *item);
XML_ITEM *xml_prev_sibling (XML_ITEM *item);
XML_ITEM *xml_parent       (XML_ITEM *item);

/*  XML attribute functions  */
int       xml_put_attr_ic  (XML_ITEM   *item,
                            const char *name,
                            const char *value,
                            Bool        ignore_case);
XML_ATTR *xml_attr_ic      (XML_ITEM   *item, 
                            const char *name,
                            Bool        ignore_case);
char     *xml_attr_name    (XML_ATTR   *item);
char     *xml_attr_value   (XML_ATTR   *item);
char     *xml_get_attr_ic  (XML_ITEM   *item,
                            const char *name,
                            const char *deflt,
                            Bool        ignore_case);
void      xml_free_attr    (XML_ATTR   *attr);

#define  xml_put_attr(item, name, value)                                      \
         xml_put_attr_ic (item, name, value, FALSE)
#define  xml_attr(item, name)                                                 \
         xml_attr_ic (item, name, FALSE)
#define  xml_get_attr(item, name, dflt)                                       \
         xml_get_attr_ic (item, name, dflt, FALSE)

/*  XML attribute navigation  */
XML_ATTR *xml_first_attr   (XML_ITEM *item);
XML_ATTR *xml_last_attr    (XML_ITEM *item);
XML_ATTR *xml_next_attr    (XML_ATTR *attr);
XML_ATTR *xml_prev_attr    (XML_ATTR *attr);

/*  XML housekeeping functions  */
Bool     xml_changed       (XML_ITEM *item);
Bool     xml_refresh       (XML_ITEM **item);


/*  Macros to treat all children and all attributes                          */

#define FORCHILDREN(child,item)    for (child  = xml_first_child (item);      \
                                        child != NULL;                        \
                                        child  = xml_next_sibling (child))    \
                                       if (xml_item_name (child))

#define FORVALUES(child,item)      for (child  = xml_first_child (item);      \
                                        child != NULL;                        \
                                        child  = xml_next_sibling (child))    \
                                       if (!xml_item_name (child))

#define FORATTRIBUTES(attr,item)   for (attr  = xml_first_attr (item);        \
                                        attr != NULL;                         \
                                        attr  = xml_next_attr (attr))


#ifdef __cplusplus
}
#endif


#endif

!-----------------------------------------------------------------------------
!                                                                            !
!   fdlgen.l - Form Definition Language generator                            !
!                                                                            !
!   Copyright (c) 1991-2003 iMatix Corporation                               !
!                                                                            !
!   ------------------ GPL Licensed Source Code ------------------           !
!   iMatix makes this software available under the GNU General               !
!   Public License (GPL) license for open source projects.  For              !
!   details of the GPL license please see www.gnu.org or read the            !
!   file license.gpl provided in this package.                               !
!                                                                            !
!   This program is free software; you can redistribute it and/or            !
!   modify it under the terms of the GNU General Public License as           !
!   published by the Free Software Foundation; either version 2 of           !
!   the License, or (at your option) any later version.                      !
!                                                                            !
!   This program is distributed in the hope that it will be useful,          !
!   but WITHOUT ANY WARRANTY; without even the implied warranty of           !
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            !
!   GNU General Public License for more details.                             !
!                                                                            !
!   You should have received a copy of the GNU General Public                !
!   License along with this program in the file 'license.gpl'; if            !
!   not, write to the Free Software Foundation, Inc., 59 Temple              !
!   Place - Suite 330, Boston, MA 02111-1307, USA.                           !
!                                                                            !
!   You can also license this software under iMatix's General Terms          !
!   of Business (GTB) for commercial projects.  If you have not              !
!   explicitly licensed this software under the iMatix GTB you may           !
!   only use it under the terms of the GNU General Public License.           !
!                                                                            !
!   For more information, send an email to info@imatix.com.                  !
!   --------------------------------------------------------------           !
!-----------------------------------------------------------------------------
-schema=lrschema.pl

After-Init:
    (--) Ok                                 -> Have-Argument
          + Initialise-Program-Data
          + Parse-Formio-Header-File
          + Load-Anchor-Definitions
          + Get-Next-Argument-Value
    (--) Error                              ->
          + Terminate-The-Program

Have-Argument:
    (--) Ok                                 -> First-Pass
          + Start-First-Pass
          + Open-Main-Document
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Switch                             -> Have-Argument
          + Process-The-Switch
          + Get-Next-Argument-Value
    (--) Finished                           ->
          + Save-Anchor-Definitions
          + Terminate-The-Program

!--------------------------    FIRST PASS   --------------------------------

First-Pass:
    (--) Body-Text                          -> First-Pass
          + Expand-Symbols-In-Line
          + Collect-Title-If-Present
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Macro-Text                         -> First-Pass
          + Expand-Symbols-In-Macro
          + Collect-Title-If-Present
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Blank-Line                         -> First-Pass
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Comment                            -> First-Pass
          + Get-Next-Document-Line
    (--) Define                             -> First-Pass
          + Store-Symbol-Definition
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Const                              -> First-Pass
          + Store-Constant-Definition
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Macro                              -> First-Pass
          + Store-Macro-Definition
          + Get-Next-Document-Line
    (--) Include                            -> First-Pass
          + Expand-Symbols-In-Line
          + Take-Include-File-Name
          + Open-The-Document
          + Get-Next-Document-Line
    (--) Ignore                             -> First-Pass
          + Expand-Symbols-In-Line
          + Handle-Ignore-Command
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Page                               -> First-Pass
          + Expand-Symbols-In-Line
          + Check-If-Ignore-Pages
          + Parse-Page-Title-For-Toc
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Ignore-Pages                       -> First-Pass
          + Parse-Page-Title-Only
          + Get-Next-Document-Line
    (--) Block                              -> First-Pass-Block
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) End-Block                          -> First-Pass
          + Signal-Unexpected-End-Block
          + Get-Next-Document-Line
    (--) If                                 -> First-Pass
          + Expand-Symbols-In-Line
          + Skip-If-Block-If-False
          + Get-Next-Document-Line
    (--) Else                               -> First-Pass
          + Skip-Else-Block-Always
          + Get-Next-Document-Line
    (--) End-If                             -> First-Pass
          + Close-If-Block-If-Open
          + Get-Next-Document-Line
    (--) For                                -> First-Pass
          + Expand-Symbols-In-Line
          + Repeat-For-Loop-Contents
          + Get-Next-Document-Line
    (--) End-For                            -> First-Pass
          + Signal-Unexpected-End-For
          + Get-Next-Document-Line
    (--) Build                              -> First-Pass
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Echo                               -> First-Pass
          + Expand-Symbols-In-Line
          + Echo-Text-To-Console
          + Get-Next-Document-Line
    (--) Finished                           -> Main-Pass
          + Close-The-Document
          + Start-Main-Pass
          + Reuse-Work-File-As-Input
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Finished-Include                   -> First-Pass
          + Get-Next-Document-Line
    (--) Error                              -> First-Pass
          + Get-Next-Document-Line
    (--) $other                             -> First-Pass
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Livelink                           -> First-Pass
          + Store-Livelink-Definition
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line

First-Pass-Block:
    (--) Body-Text                          -> First-Pass-Block
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Macro-Text                         -> First-Pass-Block
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Blank-Line                         -> First-Pass-Block
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) $other                             -> First-Pass-Block
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Block                              -> First-Pass-Block
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) End-Block                          -> First-Pass
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Finished                           -> Main-Pass
          + Close-The-Document
          + Start-Main-Pass
          + Reuse-Work-File-As-Input
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Finished-Include                   -> First-Pass
          + Get-Next-Document-Line
    (--) Error                              -> First-Pass
          + Get-Next-Document-Line

!--------------------------    MAIN PASS   ---------------------------------

Main-Pass:
    (--) Body-Text                          -> Main-Pass
          + Expand-Symbols-In-Line
          + Anchor-Title-If-Present
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Main-Pass
          + Expand-Symbols-In-Macro
          + Anchor-Title-If-Present
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Blank-Line                         -> Main-Pass
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Comment                            -> Main-Pass
          + Get-Next-Document-Line
    (--) Define                             -> Main-Pass
          + Store-Symbol-Definition
          + Get-Next-Document-Line
    (--) Const                              -> Main-Pass
          + Store-Constant-Definition
          + Get-Next-Document-Line
    (--) Livelink                           -> Main-Pass
          + Store-Livelink-Definition
          + Get-Next-Document-Line
    (--) Include                            -> Main-Pass
          + Expand-Symbols-In-Line
          + Take-Include-File-Name
          + Open-The-Document
          + Get-Next-Document-Line
    (--) Ignore                             -> Main-Pass
          + Expand-Symbols-In-Line
          + Handle-Ignore-Command
          + Get-Next-Document-Line
    (--) Page                               -> Main-Pass
          + Check-If-Ignore-Pages
          + Output-Footer-For-Page
          + Expand-Symbols-In-Line
          + Parse-Page-Title-And-Name
          + Copy-Action-Line-To-Output
          + Output-Header-For-Page
          + Get-Next-Document-Line
    (--) Ignore-Pages                       -> Main-Pass
          + Parse-Page-Title-Only
          + Get-Next-Document-Line
    (--) Block                              -> Main-Pass-Block
          + Clear-Specified-Block
          + Get-Next-Document-Line
    (--) End-Block                          -> Main-Pass
          + Signal-Unexpected-End-Block
          + Get-Next-Document-Line
    (--) If                                 -> Main-Pass
          + Expand-Symbols-In-Line
          + Skip-If-Block-If-False
          + Get-Next-Document-Line
    (--) Else                               -> Main-Pass
          + Skip-Else-Block-Always
          + Get-Next-Document-Line
    (--) End-If                             -> Main-Pass
          + Close-If-Block-If-Open
          + Get-Next-Document-Line
    (--) For                                -> Main-Pass
          + Expand-Symbols-In-Line
          + Repeat-For-Loop-Contents
          + Get-Next-Document-Line
    (--) End-For                            -> Main-Pass
          + Signal-Unexpected-End-For
          + Get-Next-Document-Line
    (--) Build                              -> Main-Pass
          + Expand-Symbols-In-Line
          + Build-Specified-Table
          + Get-Next-Document-Line
    (--) Echo                               -> Main-Pass
          + Expand-Symbols-In-Line
          + Echo-Text-To-Console
          + Get-Next-Document-Line
    (--) Finished                           -> Final-Pass
          + Close-The-Document
          + Output-Footer-For-Page
          + Check-If-Inter-Pass-Needed
          + Start-Final-Pass
          + Reuse-Work-File-As-Input
          + Get-Next-Document-Line
    (--) Finished-Include                   -> Main-Pass
          + Get-Next-Document-Line
    (--) Need-Inter-Pass                    -> Inter-Pass
          + Start-Inter-Pass
          + Reuse-Work-File-As-Input
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Error                              -> Main-Pass
          + Get-Next-Document-Line
    (--) Fields                             -> Main-Pass
          + Start-Form-If-Needed
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Table                              -> Main-Pass
          + Start-Form-If-Needed
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Action                             -> Main-Pass
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) $other                             -> Main-Pass
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line

Main-Pass-Block:
    (--) Body-Text                          -> Main-Pass-Block
          + Add-Line-To-Block
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Main-Pass-Block
          + Add-Line-To-Block
          + Get-Next-Document-Line
    (--) Blank-Line                         -> Main-Pass-Block
          + Add-Line-To-Block
          + Get-Next-Document-Line
    (--) $other                             -> Main-Pass-Block
          + Add-Action-Line-To-Block
          + Get-Next-Document-Line
    (--) Block                              -> Main-Pass-Block
          + Clear-Specified-Block
          + Get-Next-Document-Line
    (--) End-Block                          -> Main-Pass
          + Get-Next-Document-Line
    (--) Finished                           -> Final-Pass
          + Close-The-Document
          + Output-Footer-For-Page
          + Check-If-Inter-Pass-Needed
          + Start-Final-Pass
          + Reuse-Work-File-As-Input
          + Get-Next-Document-Line
    (--) Finished-Include                   -> Main-Pass
          + Get-Next-Document-Line
    (--) Need-Inter-Pass                    -> Inter-Pass
          + Start-Main-Pass
          + Reuse-Work-File-As-Input
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Error                              -> Main-Pass
          + Get-Next-Document-Line

!--------------------------    INTER PASS   --------------------------------

Inter-Pass:
    (--) Body-Text                          -> Inter-Pass
          + Expand-Symbols-In-Line
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Inter-Pass
          + Expand-Symbols-In-Macro
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Blank-Line                         -> Inter-Pass
          + Copy-Line-To-Output
          + Get-Next-Document-Line
    (--) Comment                            -> Inter-Pass
          + Get-Next-Document-Line
    (--) Define                             -> Inter-Pass
          + Store-Symbol-Definition
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Const                              -> Inter-Pass
          + Store-Constant-Definition
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Macro                              -> Inter-Pass
          + Store-Macro-Definition
          + Get-Next-Document-Line
    (--) Include                            -> Inter-Pass
          + Expand-Symbols-In-Line
          + Take-Include-File-Name
          + Open-The-Document
          + Get-Next-Document-Line
    (--) Ignore                             -> Inter-Pass
          + Expand-Symbols-In-Line
          + Handle-Ignore-Command
          + Get-Next-Document-Line
    (--) Page                               -> Inter-Pass
          + Check-If-Ignore-Pages
          + Parse-Page-Title-And-Name
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line
    (--) Ignore-Pages                       -> Inter-Pass
          + Parse-Page-Title-Only
          + Get-Next-Document-Line
    (--) Block                              -> Inter-Pass-Block
          + Clear-Specified-Block
          + Get-Next-Document-Line
    (--) End-Block                          -> Inter-Pass
          + Signal-Unexpected-End-Block
          + Get-Next-Document-Line
    (--) If                                 -> Inter-Pass
          + Expand-Symbols-In-Line
          + Skip-If-Block-If-False
          + Get-Next-Document-Line
    (--) Else                               -> Inter-Pass
          + Skip-Else-Block-Always
          + Get-Next-Document-Line
    (--) End-If                             -> Inter-Pass
          + Close-If-Block-If-Open
          + Get-Next-Document-Line
    (--) For                                -> Inter-Pass
          + Expand-Symbols-In-Line
          + Repeat-For-Loop-Contents
          + Get-Next-Document-Line
    (--) End-For                            -> Inter-Pass
          + Signal-Unexpected-End-For
          + Get-Next-Document-Line
    (--) Build                              -> Inter-Pass
          + Expand-Symbols-In-Line
          + Build-Specified-Table
          + Get-Next-Document-Line
    (--) Echo                               -> Inter-Pass
          + Expand-Symbols-In-Line
          + Echo-Text-To-Console
          + Get-Next-Document-Line
    (--) Finished                           -> Final-Pass
          + Close-The-Document
          + Check-If-Inter-Pass-Needed
          + Start-Final-Pass
          + Reuse-Work-File-As-Input
          + Get-Next-Document-Line
    (--) Finished-Include                   -> Inter-Pass
          + Get-Next-Document-Line
    (--) Need-Inter-Pass                    -> Inter-Pass
          + Start-Inter-Pass
          + Reuse-Work-File-As-Input
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Error                              -> Inter-Pass
          + Get-Next-Document-Line
    (--) Livelink                           -> Inter-Pass
          + Store-Livelink-Definition
          + Get-Next-Document-Line
    (--) $other                             -> Inter-Pass
          + Expand-Symbols-In-Line
          + Copy-Action-Line-To-Output
          + Get-Next-Document-Line

Inter-Pass-Block:
    (--) Body-Text                          -> Inter-Pass-Block
          + Add-Line-To-Block
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Inter-Pass-Block
          + Add-Line-To-Block
          + Get-Next-Document-Line
    (--) Blank-Line                         -> Inter-Pass-Block
          + Add-Line-To-Block
          + Get-Next-Document-Line
    (--) $other                             -> Inter-Pass-Block
          + Add-Action-Line-To-Block
          + Get-Next-Document-Line
    (--) Block                              -> Inter-Pass-Block
          + Clear-Specified-Block
          + Get-Next-Document-Line
    (--) End-Block                          -> Inter-Pass
          + Get-Next-Document-Line
    (--) Finished                           -> Final-Pass
          + Close-The-Document
          + Check-If-Inter-Pass-Needed
          + Start-Final-Pass
          + Reuse-Work-File-As-Input
          + Get-Next-Document-Line
    (--) Finished-Include                   -> Inter-Pass
          + Get-Next-Document-Line
    (--) Need-Inter-Pass                    -> Inter-Pass
          + Start-Inter-Pass
          + Reuse-Work-File-As-Input
          + Open-Output-Work-File
          + Get-Next-Document-Line
    (--) Error                              -> Inter-Pass
          + Get-Next-Document-Line

!--------------------------    FINAL PASS   --------------------------------

Final-Pass:
    (--) Body-Text                          -> Final-Pass
          + Expand-Symbols-In-Line
          + Copy-Line-To-Final-Output
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Final-Pass
          + Expand-Symbols-In-Line
          + Copy-Line-To-Final-Output
          + Get-Next-Document-Line
    (--) Blank-Line                         -> Final-Pass
          + Copy-Line-To-Final-Output
          + Get-Next-Document-Line
    (--) Page                               -> Final-Pass
          + Expand-Symbols-In-Line
          + Parse-Page-Title-And-Name
          + Build-Table-Index-Fields
          + Open-New-Output-Page
          + Get-Next-Document-Line
    (--) Finished                           -> Have-Argument
          + Generate-Constants
          + Close-The-Document
          + Clean-Up-Work-Files
          + Signal-Document-Processed
          + Save-Document-Page-List
          + Get-Next-Argument-Value
    (--) Form-End                           -> Final-Pass
          + Build-Table-Index-Fields
          + Get-Next-Document-Line
    (--) Fields                             -> Within-Fields
          + Expand-Symbols-In-Line
          + Start-Fields-Definition
          + Get-Next-Document-Line
    (--) Table                              -> Within-Table
          + Expand-Symbols-In-Line
          + Start-Table-Definition
          + Get-Next-Document-Line
    (--) Do                                 -> Final-Pass
          + Expand-Symbols-In-Line
          + Start-Do-Definition
          + Get-Next-Document-Line
    (--) End-Do                             -> Final-Pass
          + End-Do-Definition
          + Get-Next-Document-Line
    (--) Textual                            -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) File                               -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Textbox                            -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Numeric                            -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Date                               -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Time                               -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Boolean                            -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Select                             -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Radio                              -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Action                             -> Final-Pass
          + Expand-Symbols-In-Line
          + Build-Action-Button-Field
          + Get-Next-Document-Line
    (--) Label                              -> Final-Pass
          + Signal-Outside-Field
          + Get-Next-Document-Line
    (--) Index                              -> Final-Pass
          + Expand-Symbols-In-Line
          + Build-Simple-Index-Field
          + Get-Next-Document-Line
    (--) Error                              -> Final-Pass
          + Get-Next-Document-Line
    (--) $other                             ->
          + Signal-Internal-Failure
          + Terminate-The-Program
    (--) Exception                          ->
          + Terminate-The-Program

Within-Fields:
    (--) Blank-Line                         -> Within-Fields
          + Store-Body-Text-Field
          + Get-Next-Document-Line
    (--) Body-Text                          -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Body-Text-Field
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Within-Fields
          + Expand-Symbols-In-Macro
          + Store-Body-Text-Field
          + Get-Next-Document-Line
    (--) Fields                             -> Within-Fields
          + End-Fields-Definition
          + Expand-Symbols-In-Line
          + Start-Fields-Definition
          + Get-Next-Document-Line
    (--) Table                              -> Within-Table
          + End-Fields-Definition
          + Expand-Symbols-In-Line
          + Start-Table-Definition
          + Get-Next-Document-Line
    (--) Do                                 -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Do-Definition
          + Get-Next-Document-Line
    (--) End-Do                             -> Within-Fields
          + Store-End-Do-Definition
          + Get-Next-Document-Line
    (--) Textual                            -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Textual-Field
          + Get-Next-Document-Line
    (--) File                               -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-File-Field
          + Get-Next-Document-Line
    (--) Textbox                            -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Textbox-Field
          + Get-Next-Document-Line
    (--) Numeric                            -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Numeric-Field
          + Get-Next-Document-Line
    (--) Date                               -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Date-Field
          + Get-Next-Document-Line
    (--) Time                               -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Time-Field
          + Get-Next-Document-Line
    (--) Boolean                            -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Boolean-Field
          + Get-Next-Document-Line
    (--) Select                             -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Select-Field
          + Get-Next-Document-Line
    (--) Radio                              -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Radio-Field
          + Get-Next-Document-Line
    (--) Action                             -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Action-Button-Field
          + Get-Next-Document-Line
    (--) Label                              -> Within-Fields
          + Expand-Symbols-In-Line
          + Store-Simple-Label-Field
          + Get-Next-Document-Line
    (--) Index                              -> Within-Fields
          + Signal-Invalid-Inside-Fields
          + Get-Next-Document-Line
    (--) End-Fields                         -> Final-Pass
          + Expand-Symbols-In-Line
          + End-Fields-Definition
          + Get-Next-Document-Line
    (--) Finished                           -> Have-Argument
          + Generate-Constants
          + Close-The-Document
          + Signal-End-Not-Expected
          + Signal-Document-Processed
          + Save-Document-Page-List
          + Get-Next-Argument-Value

Within-Table:
    (--) Blank-Line                         -> Within-Table
          + Get-Next-Document-Line
    (--) Body-Text                          -> Within-Table
          + Reject-Text-Inside-Table
          + Get-Next-Document-Line
    (--) Macro-Text                         -> Within-Table
          + Reject-Text-Inside-Table
          + Get-Next-Document-Line
    (--) Fields                             -> Within-Fields
          + End-Table-Definition
          + Expand-Symbols-In-Line
          + Start-Fields-Definition
          + Get-Next-Document-Line
    (--) Table                              -> Within-Table
          + End-Table-Definition
          + Expand-Symbols-In-Line
          + Start-Table-Definition
          + Get-Next-Document-Line
    (--) Do                                 -> Within-Table
          + Signal-Invalid-Within-Table
          + Get-Next-Document-Line
    (--) End-Do                             -> Within-Table
          + Signal-Invalid-Within-Table
          + Get-Next-Document-Line
    (--) Textual                            -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Textual-Field
          + Get-Next-Document-Line
    (--) File                               -> Within-Table
          + Expand-Symbols-In-Line
          + Store-File-Field
          + Get-Next-Document-Line
    (--) Textbox                            -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Textbox-Field
          + Get-Next-Document-Line
    (--) Numeric                            -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Numeric-Field
          + Get-Next-Document-Line
    (--) Date                               -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Date-Field
          + Get-Next-Document-Line
    (--) Time                               -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Time-Field
          + Get-Next-Document-Line
    (--) Boolean                            -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Boolean-Field
          + Get-Next-Document-Line
    (--) Select                             -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Select-Field
          + Get-Next-Document-Line
    (--) Radio                              -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Radio-Field
          + Get-Next-Document-Line
    (--) Action                             -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Action-Button-Field
          + Get-Next-Document-Line
    (--) Label                              -> Within-Table
          + Expand-Symbols-In-Line
          + Store-Simple-Label-Field
          + Get-Next-Document-Line
    (--) Index                              -> Within-Table
          + Signal-Invalid-Inside-Table
          + Get-Next-Document-Line
    (--) End-Table                          -> Final-Pass
          + Expand-Symbols-In-Line
          + End-Table-Definition
          + Get-Next-Document-Line
    (--) Finished                           -> Have-Argument
          + Generate-Constants
          + Close-The-Document
          + Signal-End-Not-Expected
          + Signal-Document-Processed
          + Save-Document-Page-List
          + Get-Next-Argument-Value

Defaults:
    (--) $other                             ->
          + Signal-Internal-Failure
          + Terminate-The-Program
    (--) Exception                          ->
          + Terminate-The-Program

!-----------------------------------------------------------------------------
!                                                                            !
!   fmlgen.l - Form Markup Language generator                                !
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
    (--) Ok                                 -> Have-Filename
          + Parse-Formio-Header-File
          + Initialise-Program-Data
          + Build-List-Of-Html-Files
          + Get-Next-File-To-Process
    (--) Error                              ->
          + Terminate-The-Program

Have-Filename:
    (--) Ok                                 -> Have-Segment
          + Open-Html-Page-File
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) No-More-Files                      ->
          + Terminate-The-Program
    (--) End-Of-File                        -> Have-Filename
          + Generate-Output-File
          + Close-Html-Page-File
          + Get-Next-File-To-Process

Have-Segment:
    (--) Html-Text                          -> After-Html-Text
          + Store-Html-Text-Segment
          + Get-Next-Line-Segment
    (--) Blank-Line                         -> Have-Segment
          + Store-Html-Text-Segment
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) If                                 -> Have-Segment
          + Open-If-Block
          + Get-Next-Line-Segment
    (--) End-If                             -> Have-Segment
          + Close-If-Block
          + Get-Next-Line-Segment
    (--) Unless                             -> Have-Segment
          + Open-Unless-Block
          + Get-Next-Line-Segment
    (--) End-Unless                         -> Have-Segment
          + Close-Unless-Block
          + Get-Next-Line-Segment
    (--) Repeat                             -> Within-Repeat
          + Open-Repeat-Block
          + Get-Next-Line-Segment
    (--) End-Repeat                         ->
          + Signal-No-Repeat-Open
          + Terminate-The-Program
    (--) Const                              -> Have-Segment
          + Store-Constant-Definition
          + Get-Next-Line-Segment
    (--) End-Const                          -> Have-Segment
          + Get-Next-Line-Segment
    (--) Field                              -> Within-Field
          + Open-Field-Block
          + Get-Next-Line-Segment
          + Dialog-Call
    (--) Action                             -> Within-Action
          + Open-Action-Block
          + Get-Next-Line-Segment
          + Dialog-Call
    (--) Return                             -> Have-Segment
          + Get-Next-Line-Segment
    (--) End-Field                          ->
          + Signal-No-Field-Open
          + Terminate-The-Program
    (--) End-Action                         ->
          + Signal-No-Action-Open
          + Terminate-The-Program
    (--) No-More-Segments                   -> Have-Segment
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) End-Of-File                        -> Have-Filename
          + Generate-Output-File
          + Close-Html-Page-File
          + Get-Next-File-To-Process

After-Html-Text: <Have-Segment>
    (--) Html-Text                          -> After-Html-Text
          + Concat-Html-Text-Segment
          + Get-Next-Line-Segment
    (--) Blank-Line                         -> Have-Segment
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) If                                 -> Have-Segment
          + Open-If-Block
          + Get-Next-Line-Segment
    (--) End-If                             -> Have-Segment
          + Close-If-Block
          + Get-Next-Line-Segment
    (--) Unless                             -> Have-Segment
          + Open-Unless-Block
          + Get-Next-Line-Segment
    (--) End-Unless                         -> Have-Segment
          + Close-Unless-Block
          + Get-Next-Line-Segment
    (--) Action                             -> Within-Action
          + Open-Action-Block
          + Get-Next-Line-Segment
          + Dialog-Call
    (--) Return                             -> Have-Segment
          + Get-Next-Line-Segment

Within-Repeat:
    (--) Html-Text                          -> Within-Repeat
          + Store-Html-Text-Segment
          + Get-Next-Line-Segment
    (--) Blank-Line                         -> Within-Repeat
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) Field                              -> Within-Field
          + Open-Field-Block
          + Get-Next-Line-Segment
          + Dialog-Call
    (--) Action                             -> Within-Action
          + Open-Action-Block
          + Get-Next-Line-Segment
          + Dialog-Call
    (--) Return                             -> Within-Repeat
          + Get-Next-Line-Segment
    (--) End-Repeat                         -> Have-Segment
          + Close-Repeat-Block
          + Get-Next-Line-Segment
    (--) No-More-Segments                   -> Within-Repeat
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) End-Of-File                        ->
          + Signal-Unfinished-Repeat
          + Terminate-The-Program
    (--) Exception                          ->
          + Terminate-The-Program
    (--) $other                             ->
          + Signal-Not-Valid-In-Repeat
          + Terminate-The-Program

Within-Field:
    (--) Html-Text                          -> Within-Field
!    Html within a field block is ignored
          + Get-Next-Line-Segment
    (--) Blank-Line                         -> Within-Field
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) End-Field                          ->
          + Dialog-Return
    (--) No-More-Segments                   -> Within-Field
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) End-Of-File                        ->
          + Signal-Unfinished-Field
          + Terminate-The-Program
    (--) Exception                          ->
          + Terminate-The-Program
    (--) $other                             ->
          + Signal-Not-Valid-In-Field
          + Terminate-The-Program

Within-Action:
    (--) Html-Text                          -> Within-Action
!    Html within an action block is ignored
          + Get-Next-Line-Segment
    (--) Blank-Line                         -> 
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) End-Action                         ->
          + Dialog-Return
    (--) No-More-Segments                   -> Within-Action
          + Get-Next-Html-Line
          + Get-Next-Line-Segment
    (--) End-Of-File                        ->
          + Signal-Unfinished-Action
          + Terminate-The-Program
    (--) Exception                          ->
          + Terminate-The-Program
    (--) $other                             ->
          + Signal-Not-Valid-In-Action
          + Terminate-The-Program

Defaults:
    (--) Exception                          ->
          + Terminate-The-Program

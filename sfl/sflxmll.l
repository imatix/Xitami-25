!----------------------------------------------------------------------------
!                                                                            *
!   sflxmll.l -                                                              *
!                                                                            *
!   Copyright (c) 1991-2003 iMatix Corporation                               *
!                                                                            *
!   ------------------ GPL Licensed Source Code ------------------           *
!   iMatix makes this software available under the GNU General               *
!   Public License (GPL) license for open source projects.  For              *
!   details of the GPL license please see www.gnu.org or read the            *
!   file license.gpl provided in this package.                               *
!                                                                            *
!   This program is free software; you can redistribute it and/or            *
!   modify it under the terms of the GNU General Public License as           *
!   published by the Free Software Foundation; either version 2 of           *
!   the License, or (at your option) any later version.                      *
!                                                                            *
!   This program is distributed in the hope that it will be useful,          *
!   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
!   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
!   GNU General Public License for more details.                             *
!                                                                            *
!   You should have received a copy of the GNU General Public                *
!   License along with this program in the file 'license.gpl'; if            *
!   not, write to the Free Software Foundation, Inc., 59 Temple              *
!   Place - Suite 330, Boston, MA 02111-1307, USA.                           *
!                                                                            *
!   You can also license this software under iMatix's General Terms          *
!   of Business (GTB) for commercial projects.  If you have not              *
!   explicitly licensed this software under the iMatix GTB you may           *
!   only use it under the terms of the GNU General Public License.           *
!                                                                            *
!   For more information, send an email to info@imatix.com.                  *
!   --------------------------------------------------------------           *
!----------------------------------------------------------------------------*/

-source=sflxmll

After-Init:
    (--) File                               -> Getting-First-Item
          + Open-XML-File
          + Initialise-XML-Tree
          + Get-Content-Token
    (--) String                             -> Getting-First-Item
          + Initialise-XML-Tree
          + Get-Content-Token
    (--) Looks-Like-XML                     -> Examine-First-Item
          + Open-XML-File
          + Get-Content-Token
    (--) Error                              ->
          + Close-XML-File
          + Free-Partial-XML-Tree
          + Terminate-The-Program

Getting-First-Item:
    (--) Open                               -> Getting-Start-Tag
          + Expect-Name
          + Attach-New-Item
          + Note-Top-Level-Item
          + Get-Tag-Token
    (--) Processing                         ->
          + Skip-Rest-Of-Processing
          + Get-Content-Token
    (--) Comment                            ->
          + Skip-Rest-Of-Comment
          + Get-Content-Token
    (--) Ignore                             ->
          + Skip-Rest-Of-Section
          + Get-Content-Token
    (--) Space                              ->
          + Skip-Spaces    
          + Get-Content-Token
    (--) End-Of-File                        ->
          + Report-No-XML
          + Close-XML-File
          + Return-Error-Feedback
          + Terminate-The-Program

Getting-Start-Tag:
    (--) Name                               -> Getting-Start-Tag
          + Expect-Equals-Token
          + Expect-Literal
          + Attach-New-Attribute
          + Get-Tag-Token
    (--) Close                              -> Getting-Content
          + Get-Content-Token
    (--) Slash                              -> After-Closing-Item
          + Expect-Close
          + Close-The-Item
          + Check-For-Open-Item
    (--) Comment                            ->
          + Skip-Rest-Of-Comment
          + Get-Tag-Token

Getting-Content:
    (--) Open                               -> Getting-Start-Tag
          + Expect-Name
          + Attach-New-Item
          + Get-Tag-Token
    (--) Processing                         ->
          + Skip-Rest-Of-Processing
          + Get-Content-Token
    (--) Comment                            ->
          + Skip-Rest-Of-Comment
          + Get-Content-Token
    (--) Ignore                             ->
          + Skip-Rest-Of-Section
          + Get-Content-Token
    (--) Char                               ->
          + Collect-Item-Value
          + Get-Content-Token
    (--) Space                              ->
          + Collect-Item-Value
          + Get-Content-Token
    (--) Close                              -> After-Closing-Item
          + Expect-Name
          + Confirm-Item-Name
          + Remove-Values-If-All-White-Space
          + Close-The-Item
          + Expect-Close
          + Check-For-Open-Item

After-Closing-Item:
    (--) Ok                                 -> Getting-Content
          + Get-Content-Token
    (--) Optional-Items                     -> Getting-Optional-Tag
          + Get-Content-Token
    (--) No-More-Items
          + Expect-End-Of-File
          + Close-XML-File
          + Terminate-The-Program

Getting-Optional-Tag:
    (--) Open                               -> Getting-Start-Tag
          + Expect-Name
          + Attach-New-Item
          + Note-Top-Level-Item
          + Get-Tag-Token
    (--) Processing                         ->
          + Skip-Rest-Of-Processing
          + Get-Content-Token
    (--) Comment                            ->
          + Skip-Rest-Of-Comment
          + Get-Content-Token
    (--) Ignore                             ->
          + Skip-Rest-Of-Section
          + Get-Content-Token
    (--) Space                              ->
          + Skip-Spaces    
          + Get-Content-Token
    (--) End-Of-File                        ->
          + Close-XML-File
          + Terminate-The-Program

Examine-First-Item:
    (--) Processing                         ->
          + Close-XML-File
          + Terminate-The-Program
    (--) $other                             ->
          + Close-XML-File
          + Return-Error-Feedback
          + Terminate-The-Program

Defaults:
    (--) Error                              ->
          + Close-XML-File
          + Free-Partial-XML-Tree
          + Return-Error-Feedback
          + Terminate-The-Program
    (--) End-Of-File                        ->
          + Unexpected-Token-Error
    (--) $other                             ->
          + Unexpected-Token-Error

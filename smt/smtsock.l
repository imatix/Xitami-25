!----------------------------------------------------------------------------
!                                                                            *
!   smtsock.l - Generated file - do not modify                               *
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
-schema=smtschm.c

After-Init:
    (--) Ok                                 -> Getting-Event
          +
    (--) Error                              ->
          + Terminate-The-Thread

Getting-Event:
    (--) Read                               -> Getting-Event
          + Create-Read-Request
          + Get-Next-Event-From-Queue
    (--) Readh                              -> Getting-Event
          + Create-Huge-Read-Request
          + Get-Next-Event-From-Queue
    (--) Readr                              -> Getting-Event
          + Create-Read-Repeat-Request
          + Get-Next-Event-From-Queue
    (--) Readrh                             -> Getting-Event
          + Create-Huge-Read-Repeat-Request
          + Get-Next-Event-From-Queue
    (--) Write                              -> Getting-Event
          + Create-Write-Request
          + Get-Next-Event-From-Queue
    (--) Writeh                             -> Getting-Event
          + Create-Huge-Write-Request
          + Get-Next-Event-From-Queue
    (--) Input                              -> Getting-Event
          + Create-Input-Request
          + Get-Next-Event-From-Queue
    (--) Inputr                             -> Getting-Event
          + Create-Input-Repeat-Request
          + Get-Next-Event-From-Queue
    (--) Output                             -> Getting-Event
          + Create-Output-Request
          + Get-Next-Event-From-Queue
    (--) Connect                            -> Getting-Event
          + Create-Connect-Request
          + Get-Next-Event-From-Queue
    (--) Flush                              -> Getting-Event
          + Flush-Socket-Requests
          + Get-Next-Event-From-Queue
    (--) Timeout                            -> Getting-Event
          + Get-Next-Event-From-Queue
    (--) Invalid                            -> Getting-Event
          + Get-Next-Event-From-Queue
    (--) Empty                              -> Socket-Activity
          + Check-For-Expired-Requests
          + Wait-For-Socket-Activity
          + Check-First-Socket-Activity
    (--) No-Requests                        -> Getting-Event
          + Send-Timeout-Event-To-Self
    (--) No-Activity                        -> Getting-Event
          + Send-Timeout-Event-To-Self

Socket-Activity:
    (--) Read                               -> After-Reading
          + Read-Data-From-Socket
    (--) Write                              -> After-Writing
          + Write-Data-To-Socket
    (--) Input                              -> Socket-Activity
          + Signal-Socket-Ready-For-Input
          + Check-Next-Socket-Activity
    (--) Output                             -> Socket-Activity
          + Signal-Socket-Ready-For-Output
          + Check-Next-Socket-Activity
    (--) Error                              -> Socket-Activity
          + Signal-Socket-Error
          + Check-Next-Socket-Activity
    (--) Finished                           -> Getting-Event
          + Send-Timeout-Event-To-Self

After-Reading:
    (--) Incomplete                         -> Socket-Activity
          + Check-Next-Socket-Activity
    (--) Finished                           -> Socket-Activity
          + Signal-Read-Complete
          + Check-Next-Socket-Activity
    (--) Closed                             -> Socket-Activity
          + Signal-Read-Closed
          + Check-Next-Socket-Activity
    (--) Error                              -> Socket-Activity
          + Signal-Socket-Error
          + Check-Next-Socket-Activity

After-Writing:
    (--) Incomplete                         -> Socket-Activity
          + Check-Next-Socket-Activity
    (--) Finished                           -> Socket-Activity
          + Signal-Write-Complete
          + Check-Next-Socket-Activity
    (--) Closed                             -> Socket-Activity
          + Signal-Write-Closed
          + Check-Next-Socket-Activity
    (--) Error                              -> Socket-Activity
          + Signal-Socket-Error
          + Check-Next-Socket-Activity

Defaults:
    (--) Exception                          ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Destroy-All-Requests
          + Terminate-The-Thread
    (--) $other                             ->
          +

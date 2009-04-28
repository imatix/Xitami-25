!----------------------------------------------------------------------------
!                                                                            *
!   smtftpd.l - Generated file - do not modify                               *
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
    (--) Master                             -> Getting-Event
          +
    (--) Put-File                           -> Before-Put
          + Connect-To-Client
    (--) Get-File                           -> Before-Get
          + Connect-To-Client
    (--) Append-File                        -> Before-Append
          + Connect-To-Client
    (--) Passive                            -> After-Open-Passive
          + Open-Listen-Socket
    (--) Error                              ->
          + Terminate-The-Thread

Getting-Event:
    (--) Put-File                           -> Connection-Type
          + Get-Message-Put-File
          + Check-Connection-Type
    (--) Get-File                           -> Connection-Type
          + Get-Message-Get-File
          + Check-Connection-Type
    (--) Append-File                        -> Connection-Type
          + Get-Message-Append-File
          + Check-Connection-Type
    (--) Passive                            -> Getting-Event
          + Get-Message-Passive
          + Create-Child-Thread
    (--) Abort                              -> Getting-Event
          + Get-Message-Abort
          + Send-Event-To-Child-Thread

After-Open-Passive:
    (--) Ok                                 -> Getting-Passive-Event
          + Signal-Passive-Open
          + Wait-For-Socket-Input
    (--) Error                              ->
          + Signal-Error
          + Terminate-The-Thread

Getting-Passive-Event:
    (--) Ok                                 -> After-Passive-Connect
          + Accept-Client-Connection
          + Set-Transfer-Mode
    (--) Put-File                           -> Getting-Passive-Event
          + Get-Message-Put-File
    (--) Get-File                           -> Getting-Passive-Event
          + Get-Message-Get-File
    (--) Append-File                        -> Getting-Passive-Event
          + Get-Message-Append-File

After-Passive-Connect:
    (--) Put-File-Mode                      -> End-Transfer
          + Signal-Connection-To-Control
          + Put-File
    (--) Get-File-Mode                      -> End-Transfer
          + Signal-Connection-To-Control
          + Get-File
    (--) Append-File-Mode                   -> End-Transfer
          + Signal-Connection-To-Control
          + Append-File
    (--) Put-File                           -> End-Transfer
          + Get-Message-Put-File
          + Signal-Connection-To-Control
          + Put-File
    (--) Get-File                           -> End-Transfer
          + Get-Message-Get-File
          + Signal-Connection-To-Control
          + Get-File
    (--) Append-File                        -> End-Transfer
          + Get-Message-Append-File
          + Signal-Connection-To-Control
          + Append-File

Connection-Type:
    (--) Active                             -> Getting-Event
          + Create-Child-Thread
    (--) Passive                            -> Getting-Event
          + Send-Event-To-Child-Thread

Before-Put:
    (--) Ok                                 -> End-Transfer
          + Get-Connection-Handle
          + Signal-Connection-To-Control
          + Put-File
    (--) Sock-Error                         ->
          + Signal-Connection-Failed
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Terminate-The-Thread
    (--) Sock-Timeout                       ->
          + Terminate-The-Thread
    (--) Sock-Retry                         ->
          + Terminate-The-Thread

Before-Get:
    (--) Ok                                 -> End-Transfer
          + Get-Connection-Handle
          + Signal-Connection-To-Control
          + Get-File
    (--) Sock-Error                         ->
          + Signal-Connection-Failed
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Terminate-The-Thread
    (--) Sock-Timeout                       ->
          + Terminate-The-Thread
    (--) Sock-Retry                         ->
          + Terminate-The-Thread

Before-Append:
    (--) Ok                                 -> End-Transfer
          + Get-Connection-Handle
          + Signal-Connection-To-Control
          + Append-File
    (--) Sock-Error                         ->
          + Signal-Connection-Failed
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Terminate-The-Thread
    (--) Sock-Timeout                       ->
          + Terminate-The-Thread
    (--) Sock-Retry                         ->
          + Terminate-The-Thread

End-Transfer:
    (--) Finished                           ->
          + Signal-End-Of-Transfer
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Error-In-Transfer
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Signal-Error-In-Transfer
          + Terminate-The-Thread
    (--) Abort                              ->
          + Abort-File-Transfer
          + Terminate-The-Thread

Defaults:
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) Close-Control                      ->
          + Terminate-The-Thread
    (--) Abort                              ->
          + Close-Data-Connection
          + Signal-Abort-To-Control
          + Terminate-The-Thread
    (--) $other                             ->
          +

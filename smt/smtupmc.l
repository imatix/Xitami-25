!----------------------------------------------------------------------------
!                                                                            *
!   smtupmc.l - Generated file - do not modify                               *
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
    (--) Ok                                 -> Have-Connection
          + Connect-To-Upm-Daemon
    (--) Error                              ->
          + Terminate-The-Thread

Have-Connection:
    (--) Ok                                 -> Making-Connection
          + Store-Connection-Data
          + Get-Daemon-Message
          + Check-Daemon-Message

Making-Connection:
    (--) Upm-Ready                          -> User-Command
          + Signal-Connected-Okay
          + Get-User-Command-Input

Daemon-Message:
    (--) Upm-Ready                          -> User-Command
          + Get-User-Command-Input
    (--) Upm-Task-Id                        -> Daemon-Message
          + Show-Task-Name
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Start-Ok                       -> Daemon-Message
          + Signal-Task-Started-Ok
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Start-Error                    -> Daemon-Message
          + Signal-Task-Not-Started
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Stop-Ok                        -> Daemon-Message
          + Signal-Task-Stopped-Ok
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Stop-Error                     -> Daemon-Message
          + Signal-Task-Not-Stopped
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Task-Nf                        -> Daemon-Message
          + Signal-Task-Not-Known
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Task-Running                   -> Daemon-Message
          + Signal-Task-Running
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Upm-Task-Stopped                   -> Daemon-Message
          + Signal-Task-Stopped
          + Get-Daemon-Message
          + Check-Daemon-Message

User-Command:
    (--) List                               -> Daemon-Message
          + Send-Daemon-List-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Stop                               -> Daemon-Message
          + Send-Daemon-Stop-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Start                              -> Daemon-Message
          + Send-Daemon-Start-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Status                             -> Daemon-Message
          + Send-Daemon-Status-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Halt                               -> Daemon-Halting
          + Send-Daemon-Halt-Command
          + Get-Daemon-Message
          + Check-Daemon-Message
    (--) Version                            -> User-Command
          + Show-Version-Information
          + Get-User-Command-Input
    (--) Help                               -> User-Command
          + Show-Help-Information
          + Get-User-Command-Input
    (--) Exit                               ->
          + Terminate-The-Thread
    (--) Empty                              -> User-Command
          + Get-User-Command-Input
    (--) Error                              -> User-Command
          + Signal-Invalid-Command
          + Get-User-Command-Input

Daemon-Halting:
    (--) Upm-Halting                        ->
          + Terminate-The-Thread

Defaults:
    (--) Sock-Closed                        ->
          + Signal-Socket-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Upm-Ready                          ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Error                          ->
          + Signal-Upm-Fatal-Error
          + Terminate-The-Thread
    (--) Upm-Halting                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Id                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Ok                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Nf                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Running                   ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Task-Stopped                   ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Start-Ok                       ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Start-Error                    ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Stop-Ok                        ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Upm-Stop-Error                     ->
          + Signal-Unexpected-Message
          + Terminate-The-Thread
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread

!----------------------------------------------------------------------------
!                                                                            *
!   smthlog.l - Generated file - do not modify                               *
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
    (--) Master                             -> Process-Argument
          + Initialise-Dns-Library
          + Get-Next-Argument
    (--) Error                              -> End-Thread
          + Check-Thread-Type
    (--) Request                            -> Resolver-Feedback
          + Send-Request-To-Resolver

Process-Argument:
    (--) Server-Ip                          -> Process-Argument
          + Set-Server-Ip-Value
          + Get-Next-Argument
    (--) Debug-Mode                         -> Process-Argument
          + Set-Debug-Mode
          + Get-Next-Argument
    (--) Verbose-Mode                       -> Process-Argument
          + Set-Verbose-Mode
          + Get-Next-Argument
    (--) Recursive-Mode                     -> Process-Argument
          + Set-Recursive-Mode
          + Get-Next-Argument
    (--) Log-File                           -> After-Open-File
          + Check-Dns-Config
          + Open-Log-File
    (--) End                                -> End-Thread
          + Check-Thread-Type
    (--) Help                               -> End-Thread
          + Show-Help
          + Check-Thread-Type

After-Open-File:
    (--) Ok                                 -> After-Request-Creation
          + Read-Next-Line
          + Create-Request
    (--) Error                              -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

After-Request-Creation:
    (--) Ok                                 -> Stack-Level
          + Create-Request-Thread
          + Check-Stack-Level
    (--) Error                              -> After-Request-Creation
          + Write-Current-Line-To-Output
          + Read-Next-Line
          + Create-Request
    (--) End-Of-File                        -> Master-Input
          + Show-Processing-Statistics
          + Set-End-File-Flag

Stack-Level:
    (--) Full                               -> Master-Input
          +
    (--) Not-Full                           -> After-Request-Creation
          + Read-Next-Line
          + Create-Request
    (--) Empty                              -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

Master-Input:
    (--) Request-Complete                   -> After-Request-Complete
          + Check-If-First-Request-Complete
    (--) End-Of-File                        -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

After-Request-Complete:
    (--) First-Request                      -> After-Request-Complete
          + Store-Line-To-Output
          + Remove-Request-Form-Stack
          + Check-If-First-Request-Complete
    (--) Not-First                          -> Stack-Level
          + Check-Stack-Level
    (--) Empty-Stack                        -> After-Request-Creation
          + Read-Next-Line
          + Create-Request
    (--) End-Of-File                        -> Process-Argument
          + Partial-Initialisation
          + Get-Next-Argument

Resolver-Feedback:
    (--) Host                               -> End-Thread
          + Store-Host-Name
          + Check-Thread-Type
    (--) Ip                                 -> End-Thread
          + Set-Feedback-To-Error
          + Check-Thread-Type
    (--) Error                              -> End-Thread
          + Set-Feedback-To-Error
          + Check-Thread-Type
    (--) End                                -> End-Thread
          + Set-Feedback-To-Not-Found
          + Check-Thread-Type
    (--) Timeout                            -> End-Thread
          + Set-Feedback-To-Timeout
          + Check-Thread-Type

Defaults:
    (--) Exception                          -> End-Thread
          + Check-Thread-Type
    (--) Shutdown                           -> End-Thread
          + Check-Thread-Type
    (--) Fatal                              -> End-Thread
          + Check-Thread-Type

End-Thread:
    (--) Master                             ->
          + Terminate-The-Thread
          + Shutdown-Application
    (--) Request                            ->
          + Display-Result-To-Console
          + Send-Request-Complete
          + Terminate-The-Thread

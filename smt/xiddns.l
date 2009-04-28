!----------------------------------------------------------------------------
!                                                                            *
!   xiddns.l - Generated file - do not modify                                *
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
    (--) Ok                                 -> After-Startup
          + Check-If-Automatic-Signon
    (--) Error                              ->
          + Terminate-The-Thread

After-Startup:
    (--) Ok                                 -> Before-Signon
          + Initialise-Signon-Timer
          + Load-Ddns-Services-List
          + Get-First-Ddns-Profile
    (--) Ignore                             -> Server-Running
          +
          
Server-Running:
    (--) Signon                             -> Before-Signon
          + Load-Ddns-Services-List
          + Get-First-Ddns-Profile
    (--) Signoff                            -> Before-Signoff
          + Load-Ddns-Services-List
          + Get-First-Ddns-Profile
      
Before-Signon:
    (--) Ok                                 -> Signon-Connect
          + Connect-To-Ddns-Server
    (--) No-More                            -> Server-Running
          + Drop-Ddns-Services-List
    (--) Error                              -> 
          + Get-Next-Ddns-Profile

Signon-Connect:
    (--) Ok                                 -> Signon-Sent
          + Get-Connected-Socket
          + Send-Ddns-Signon-Request
    (--) Ignore                             -> Before-Signon
          + Close-Ddns-Socket
          + Get-Next-Ddns-Profile
    (--) Sock-Error                         -> Before-Signon
          + Signal-Connection-Failed
          + Get-Next-Ddns-Profile

Signon-Sent:
    (--) Ok                                 -> Signon-Answer
          + Get-Ddns-Server-Response

Signon-Answer:
    (--) Ok                                 -> Before-Signon
          + Check-Ddns-Confirmation
          + Close-Ddns-Socket
          + Get-Next-Ddns-Profile

Before-Signoff:
    (--) Ok                                 -> Signoff-Connect
          + Connect-To-Ddns-Server
    (--) No-More                            -> Server-Running
          + Drop-Ddns-Services-List
    (--) Error                              -> 
          + Get-Next-Ddns-Profile

Signoff-Connect:
    (--) Ok                                 -> Signoff-Sent
          + Get-Connected-Socket
          + Send-Ddns-Signoff-Request
    (--) Ignore                             -> Before-Signoff
          + Close-Ddns-Socket
          + Get-Next-Ddns-Profile
    (--) Sock-Error                         -> Before-Signoff
          + Signal-Connection-Failed
          + Get-Next-Ddns-Profile

Signoff-Sent:
    (--) Ok                                 -> Signoff-Answer
          + Get-Ddns-Server-Response

Signoff-Answer:
    (--) Ok                                 -> Before-Signoff
          + Check-Ddns-Confirmation
          + Close-Ddns-Socket
          + Get-Next-Ddns-Profile

Defaults:
    (--) Sock-Timeout                       -> 
          + Signal-Ddns-Sock-Timeout
          + Terminate-The-Thread
    (--) Sock-Error                         -> 
          + Signal-Ddns-Sock-Error
          + Terminate-The-Thread
    (--) Exception                          -> 
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) Signon                             -> 
          + 
    (--) Signoff                            -> 
          + 


!----------------------------------------------------------------------------
!                                                                            *
!   xilrwp.l - Generated file - do not modify                                *
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

!
!------------------------------------------------------------------------
! default state

After-Init:
    (--) Master                             -> Master-Input
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Peer                               -> Peer-Startup
          + Wait-For-Socket-Input
    (--) Router                             -> Wait-For-Router-Request
          + Setup-Router
!
!------------------------------------------------------------------------
! The listening socket

Master-Input:
    (--) Sock-Input-Ok                      -> Master-Input
          + Accept-Peer-Connection
          + Wait-For-Socket-Input
!
!------------------------------------------------------------------------
! Handles communications with the peer application

Peer-Startup:
    (--) Sock-Input-Ok                      -> Peer-Negotiation
          + Read-App-Connection-Request
    (--) Sock-Closed                        ->
          + Terminate-The-Thread

Peer-Negotiation:
    ! For LRWP 1.0 only Peer-Accepted is used (immediately).
    ! For LRWP 2.0 if challenges are turned off, then Peer-Accepted is
    !     used immediately.  Otherwise Challenge-Peer is used to send
    !     out a challenge, and wait for the response.  The response is
    !     received and checked, and if valid Peer-Accepted is used.
    !
    ! Startup-Error is used for errors at any stage in start up negotation
    !
    (--) Peer-Accepted                      -> Waiting-For-Request
          + Register-Peer
          + Send-Peer-Acknowledgement
          + Wait-For-Socket-Input
    (--) Challenge-Peer                     -> Receive-Negotiation-Response-Size
          + Send-Peer-Negotiation-Challenge
          + Wait-For-Socket-Input
    (--) Startup-Error                      ->
          + Signal-startup-error
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Signal-Peer-Closed
          + Terminate-The-Thread

Receive-Negotiation-Response-Size:
    ! Auxilliary peer negotation state -- receives size of challenge response
    (--) Sock-Input-Ok                      -> Receive-Negotiation-Response
          + Read-Peer-Data-Size
          + Wait-For-Socket-Input
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread

Receive-Negotiation-Response:
    ! Auxilliary peer negotation state -- receives challenge response
    ! and validates response (returning to peer-negotation when done)
    (--) Sock-Input-Ok                      -> Receive-Negotiation-Response
          + Read-Peer-Data
          + Wait-For-Socket-Input
    (--) Finished                           -> Peer-Negotiation
          + Check-Peer-Negotiation-Response
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread

Waiting-For-Request:
    (--) LRWP-Request                       -> Waiting-For-Peer-Response
          + Send-Request-Data-To-Peer
          + Wait-For-Socket-Input
    (--) Sock-Closed                        ->
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Input-Ok                      ->
    ! While waiting on an INPUT and the peer closes the socket, we
    ! get a Sock-Input-Ok event instead of a Sock-Closed event...
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Startup-Error                      ->
          + Signal-startup-error
          + Terminate-The-Thread


Waiting-For-Peer-Response:
    (--) Sock-Input-Ok                      -> Wait-For-Peer-Data-Block
          + Read-Peer-Data-Size
          + Wait-For-Socket-Input
    (--) Sock-Write-Ok                      ->
          +
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread

Wait-For-Peer-Data-Block:
    (--) Sock-Input-Ok                      -> Wait-For-Peer-Data-Block
          + Read-Peer-Data
          + Wait-For-Socket-Input
    (--) Finished                           -> Waiting-For-Request
          + Send-Peer-Data-To-Xitami
          + Cleanup-And-Inform-Router
          + Wait-For-Socket-Input
    (--) Sock-Closed                        ->
          + Send-Error-Reply
          + Signal-Peer-Closed
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Send-Error-Reply
          + Signal-Socket-Error
          + Signal-Peer-Closed
          + Terminate-The-Thread
!
!------------------------------------------------------------------------
! The router thread

Wait-For-Router-Request:
    (--) WSX-Request                        -> Wait-For-Router-Request
          + Find-Available-Peer
    (--) Peer-Job-Completed                 -> Wait-For-Router-Request
          + Check-For-Saved-Requests
    (--) Peer-Closed                        -> Wait-For-Router-Request
          + Check-if-all-gone
!
!------------------------------------------------------------------------
! shared events

Defaults:
    (--) Exception                          ->
          + Terminate-The-Thread
    (--) Shutdown                           ->
          + Terminate-The-Thread
    (--) Fatal                              ->
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Sock-Error                         ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Signal-Socket-Error
          + Terminate-The-Thread
    (--) Protocol-Error                     ->
          + Terminate-The-Thread


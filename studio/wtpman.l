!-----------------------------------------------------------------------------
!                                                                            !
!   wtpman.l - WTP manager WSX agent                                         !
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
-schema=smtschm.c

After-Init:
    (--) Master                             -> Master-Thread
          + Load-Master-Config-File
          + Open-Master-Log-File
          + Create-Applic-Threads
    (--) Applic                             -> Applic-Intialise
          + Initialise-Application-Thread
          + Check-Application-Autorun
    (--) Session                            -> Session-Busy
          + Initialise-Session-Data
          + Session-Use-Initial-Program
          + Route-Wtp-Request-To-Server
    (--) Server                             -> Server-Initialise
          + Read-Server-Message
          + Decode-Server-Message

!  ----------------------------------------------------------------------
!   Master thread handles WTP requests from the browser, and passes these
!   to the appropriate application thread.

Master-Thread:
    (--) Request                            -> Master-Thread
          + Partial-Decode-Wtp-Request
          + Route-Wtp-Request-To-Applic
          + Free-Wtp-Request
    (--) Not-Found                          -> Master-Thread
          + Http-Reply-Not-Found
          + Free-Wtp-Request

!  ----------------------------------------------------------------------
!   Each applic thread manages a single WTP application

Applic-Intialise:
    (--) Ok                                 -> Applic-Running
          + Open-Application-Socket
          + Start-Application-Servers
          + Wait-For-Socket-Input
    (--) Error                              -> Applic-Stopped
          +
    (--) Suspended                          -> Applic-Stopped
          +

Applic-Running:
    (--) Ok                                 -> Applic-Running
          + Accept-Server-Connection
          + Wait-For-Socket-Input
    (--) Request                            -> Applic-Running
          + Decode-Wtp-Request
          + Route-Wtp-Request-To-Session
          + Free-Wtp-Request
    (--) Control                            -> Applic-Running-Control
          + Decode-Wtp-Request
          + Check-Applic-Control-Command
          + Free-Wtp-Request
    (--) Refresh                            -> Applic-Running
          + Check-Application-Servers

Applic-Running-Control:
    (--) Control-Start                      -> Applic-Running
          + Http-Reply-Applic-Running
    (--) Control-Stop                       -> Applic-Stopped
          + Close-Application-Socket
          + Stop-Application-Servers
          + Http-Reply-Stopping-Applic
    (--) Control-Report                     -> Applic-Running
          + Http-Reply-Applic-Report
    (--) Control-Lock                       -> Applic-Running
          + Lock-Application-Sessions
          + Http-Reply-Applic-Locked
    (--) Control-Unlock                     -> Applic-Running
          + Unlock-Application-Sessions
          + Http-Reply-Applic-Unlocked
    (--) Error                              -> Applic-Running
          + Http-Reply-Invalid-Control

Applic-Stopped:
    (--) Request                            -> Applic-Stopped
          + Decode-Wtp-Request
          + Http-Reply-Applic-Unavailable
          + Free-Wtp-Request
    (--) Control                            -> Applic-Stopped-Control
          + Decode-Wtp-Request
          + Check-Applic-Control-Command
          + Free-Wtp-Request
    (--) Sock-Closed                        -> Applic-Stopped
          +
    (--) Refresh                            -> Applic-Stopped
          +

Applic-Stopped-Control:
    (--) Control-Start                      -> Applic-Running
          + Http-Reply-Starting-Applic
          + Open-Application-Socket
          + Start-Application-Servers
          + Wait-For-Socket-Input
    (--) Exception                          -> Applic-Stopped
          +
    (--) Control-Stop                       -> Applic-Stopped
          + Http-Reply-Applic-Not-Running
    (--) Control-Report                     -> Applic-Stopped
          + Http-Reply-Applic-Report
    (--) Control-Lock                       -> Applic-Stopped
          + Http-Reply-Applic-Not-Running
    (--) Control-Unlock                     -> Applic-Stopped
          + Http-Reply-Applic-Not-Running
    (--) Sock-Closed                        -> Applic-Stopped
          +
    (--) Error                              -> Applic-Stopped
          + Http-Reply-Invalid-Control

Session-Waiting:
    (--) Continue                           -> Session-Busy
          + Clear-Alarms-For-Thread
          + Session-Use-Current-Program
          + Route-Wtp-Request-To-Server
    (--) Refresh                            -> Session-Busy
          + Clear-Alarms-For-Thread
          + Session-Use-Current-Program
          + Route-Wtp-Request-To-Server
    (--) Timeout                            ->
          + Session-End-Processing
          + Terminate-The-Thread

Session-Busy:
    (--) Refresh                            -> Session-Busy
          + Session-Resynchronize
    (--) Session-Call                       -> Session-Busy
          + Session-Use-Called-Program
          + Route-Wtp-Request-To-Server
    (--) Session-Return                     -> Session-Busy
          + Session-Use-Parent-Program
          + Route-Wtp-Request-To-Server
    (--) Session-Show                       -> Session-Waiting
          + Session-Show-Html-Data
          + Session-Set-Timeout
    (--) Session-Exit                       ->
          + Session-Show-Application-Ended
          + Session-End-Processing
          + Terminate-The-Thread
    (--) Session-Error                      ->
          + Session-Show-Application-Error
          + Session-End-Processing
          + Terminate-The-Thread
    (--) Server-Timeout                     ->
          + Http-Reply-Server-Timed-Out
          + Session-End-Processing
          + Terminate-The-Thread
    (--) Server-Abort                       ->
          + Http-Reply-Server-Aborted
          + Session-End-Processing
          + Terminate-The-Thread

!  ----------------------------------------------------------------------
!   Each server thread each handles communications with one ATP
!   This superstate defines default handling for each message

Server-Message:
    (--) Wtp-Connect                        -> Server-Message
          + Wtp-Send-Not-Expected
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Register                       -> Server-Message
          + Wtp-Send-Not-Expected
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Ready                          -> Server-Message
          + Wtp-Send-Not-Expected
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Disconnect                     ->
          + Server-End-Processing
          + Terminate-The-Thread
    (--) Wtp-Ok                             -> Server-Message
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Error                          -> Server-Message
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Do                             -> Server-Message
          + Wtp-Send-Not-Expected
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Done                           -> Server-Message
          + Wtp-Send-Not-Expected
          + Read-Server-Message
          + Decode-Server-Message
    (--) Error                              -> Server-Message
          + Wtp-Send-Invalid
          + Read-Server-Message
          + Decode-Server-Message
    (--) Sock-Closed                        ->
          + Signal-Server-Aborted
          + Server-End-Processing
          + Terminate-The-Thread

Server-Initialise: <Server-Message>
    (--) Wtp-Connect                        -> Server-Connected
          + Handle-Server-Connection
          + Read-Server-Message
          + Decode-Server-Message
    (--) Error                              ->
          + Wtp-Send-Not-Authorised
          + Server-End-Processing
          + Terminate-The-Thread
    (--) Wtp-Register                       ->
          + Wtp-Send-Not-Connected
          + Server-End-Processing
          + Terminate-The-Thread

Server-Connected: <Server-Message>
    (--) Wtp-Register                       -> Server-Connected
          + Handle-Server-Registration
          + Read-Server-Message
          + Decode-Server-Message
    (--) Wtp-Ready                          -> Server-Have-Request
          + Handle-Server-Ready
          + Take-Do-Request-If-Any

Server-Have-Request: <Server-Message>
    (--) Ok                                 -> Server-Expect-Done
          + Wtp-Send-Do-Program
          + Server-Set-Timeout
          + Read-Server-Message
          + Clear-Alarms-For-Thread
          + Decode-Server-Message
    (--) Not-Found                          -> Server-Ready
          + Clear-Alarms-For-Thread
          + Server-Process-Is-Ready
    (--) Timeout                            ->
          + Signal-Server-Timed-Out
          + Server-End-Processing
          + Terminate-The-Thread

Server-Expect-Done: <Server-Message>
    (--) Wtp-Done                           -> Server-Have-Request
          + Handle-Server-Done
          + Take-Do-Request-If-Any

Server-Ready: <Server-Message>
    (--) Request                            -> Server-Expect-Done
          + Wtp-Send-Do-Program
          + Server-Set-Timeout
          + Read-Server-Message
          + Clear-Alarms-For-Thread
          + Decode-Server-Message
    (--) Timeout                            ->
          + Signal-Server-Timed-Out
          + Server-End-Processing
          + Terminate-The-Thread

Defaults:
    (--) Sock-Error                         -> End-Thread-Normal
          + Signal-Socket-Error
          + Check-Thread-Type
    (--) Sock-Closed                        -> End-Thread-Normal
          + Check-Thread-Type
    (--) Exception                          -> End-Thread-Normal
          + Check-Thread-Type
    (--) Shutdown                           -> End-Thread-Normal
          + Check-Thread-Type
    (--) Fatal-Error                        -> End-Thread-Normal
          + Shutdown-The-Application
          + Check-Thread-Type
    (--) Out-Of-Memory                      -> End-Thread-No-Memory
          + Signal-Out-Of-Memory
          + Check-Thread-Type
    (--) $other                             ->
          + Signal-Invalid-Event

End-Thread-Normal:
    (--) Master                             ->
          + Close-Manager-Log-File
          + Terminate-The-Thread
    (--) Applic                             ->
          + Close-Application-Socket
          + Stop-Application-Servers
          + Terminate-The-Thread
    (--) Session                            ->
          + Session-End-Processing
          + Terminate-The-Thread
    (--) Server                             ->
          + Server-End-Processing
          + Terminate-The-Thread

End-Thread-No-Memory: <End-Thread-Normal>
    (--) Session                            ->
          + Http-Reply-Insufficient-Resources
          + Terminate-The-Thread

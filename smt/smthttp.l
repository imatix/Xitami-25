!----------------------------------------------------------------------------
!                                                                            *
!   smthttp.l - Generated file - do not modify                               *
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
    (--) Master                             -> Master-Settle
          + Open-Server-Log-File
          + Load-Virtual-Hosts
          + Check-Rootdir-Exists
          + Open-Ssl-Socket-If-Needed
          + Open-Master-Socket
          + Wait-For-Socket-Input
          + Wait-For-Process-To-Settle
    (--) Sock-Retry                         -> Master-Input
          + Open-Master-Socket
          + Set-Server-Process-State
          + Wait-For-Socket-Input
    (--) Client                             -> Client-Input
          + Prepare-Client-Thread
          + Prepare-To-Read-Request
          + Read-Input-From-Socket

!   In the settle state we act normally except that we will switch
!   to non-root operations after the first timer event.
!
Master-Settle: <Master-Input>
    (--) Timer                              -> Master-Input
          + Set-Server-Process-State

Master-Input:
    (--) Ok                                 ->
          + Accept-Client-Connection
          + Wait-For-Socket-Input
    (--) New-Ssl-Client                     ->
          + Create-Ssl-Child-Thread
    (--) Exception                          ->
          + Wait-For-Socket-Input
    (--) Timer                              ->
          + Reload-Config-If-Needed
    (--) Restart                            -> Master-Restart
          + Free-All-Server-Resources
          + Kill-All-Active-Connections
          + Prepare-To-Close-Master-Socket
          + Wait-For-Connections-To-Close
    (--) Sock-Retry                         ->
          + Open-Master-Socket
          + Wait-For-Socket-Input
    (--) Sock-Closed                        -> End-Thread
          + Signal-Socket-Closed
          + Check-Socket-Type
    (--) Cancel                             ->
          +
    (--) Ssl-Open                           ->
          + Get-Ssl-Master-Port
    (--) Wsx-Install                        ->
          + Install-Wsx-Alias
    (--) Wsx-Cancel                         ->
          + Cancel-Wsx-Alias

Master-Restart: <Master-Input>
    (--) Timer                              -> Master-Input
          + Close-Master-Socket
          + Reload-Config-If-Changed
          + Open-Server-Log-File
          + Load-Virtual-Hosts
          + Check-Rootdir-Exists
          + Restart-Ftp-Server-If-Reqd
          + Restart-Ssl-Agent-If-Reqd
          + Open-Ssl-Socket-If-Needed
          + Open-Master-Socket
          + Wait-For-Socket-Input
!   We reject any connection requests that come in now
    (--) Ok                                 ->
          + Reject-Client-Connection
          + Wait-For-Socket-Input

!   Superstate defines error-handling for client threads.
!   This makes error handling a little faster in all child
!   threads; in any case the Defaults handling is secure too.

Client:
    (--) Sock-Error                         ->
          + Flush-Socket-Requests
          + Terminate-The-Thread
    (--) Sock-Closed                        ->
          + Terminate-The-Thread
    (--) Sock-Timeout                       ->
          + Terminate-The-Thread
    (--) Sock-Retry                         ->
          + Terminate-The-Thread
    (--) Error                              ->
          + Write-Http-Header
          + Terminate-The-Thread
    (--) Ssl-Error                          ->
          + Terminate-The-Thread
    (--) Bad-Request                        ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Unauthorized                       ->
          + Signal-Url-Unauthorized
          + Terminate-The-Thread
    (--) Forbidden                          ->
          + Signal-Url-Forbidden
          + Terminate-The-Thread
    (--) Not-Found                          ->
          + Signal-Url-Not-Found
          + Terminate-The-Thread
    (--) Too-Large                          ->
          + Signal-Too-Large
          + Terminate-The-Thread
    (--) Internal-Error                     ->
          + Signal-Internal-Error
          + Terminate-The-Thread
    (--) Not-Implemented                    ->
          + Signal-Not-Implemented
          + Terminate-The-Thread
    (--) Overloaded                         ->
          + Signal-Overloaded
          + Terminate-The-Thread

Client-Input: <Client>
    (--) Ok                                 -> Have-Client-Request
          + Read-Http-Request-Next
          + Check-If-Request-Complete
    (--) Sock-Retry                         -> Client-Input
          + Read-Input-From-Socket

Have-Client-Request: <Client>
    (--) More                               -> Client-Input
          + Read-Input-From-Socket
    (--) Post                               -> Have-Client-Post
          + Check-If-Post-Data-Complete
    (--) Finished                           -> Execute-Http-Request
          + Parse-Http-Request
          + Resolve-Virtual-Hostname
          + Check-Client-Ip-Allowed

Client-Input-Post: <Client>
    (--) Ok                                 -> Have-Client-Post
          + Read-Http-Posted-Data
          + Check-If-Post-Data-Complete
    (--) Sock-Retry                         -> Client-Input-Post
          + Read-Input-From-Socket

Have-Client-Post: <Client>
    (--) More                               -> Client-Input-Post
          + Read-Input-From-Socket
    (--) Finished                           -> Execute-Http-Request
          + Parse-Http-Request
          + Resolve-Virtual-Hostname
          + Check-Client-Ip-Allowed

Execute-Http-Request: <Client>
    (--) Get-Request                        -> Process-Http-Get
          + Get-Url-Type
    (--) Post-Request                       -> Process-Http-Post
          + Get-Url-Type
    (--) Update-Request                     -> Process-Http-Update
          + Get-Url-Type

Process-Http-Get: <Client>
    (--) Html                               -> Have-Type-Of-Get
          + Check-File-Or-Directory
    (--) Cgi                                -> Have-Type-Of-Cgi
          + Check-File-Or-Directory
    (--) Filter                             -> Have-Type-Of-Filter
          + Check-File-Or-Directory
    (--) Wsx                                -> Trying-To-Get-Wsx
          + Check-If-Protected

Have-Type-Of-Get: <Client>
    (--) File                               -> Trying-To-Get-File
          + Check-If-Protected
    (--) Executable                         -> Trying-To-Get-File
          + Check-If-Protected
    (--) Directory                          -> Trying-To-Get-Dir
          + Check-If-Protected

Trying-To-Get-File: <Client>
    (--) Ok                                 -> Get-Range-Header
          + Check-For-Conditional-Get
          + Look-For-Range-Header
!   Exceptions produced by If-Modified and If-Not-Modified headers
    (--) Not-Modified                       -> Request-Finished
          + Signal-Not-Modified
          + Check-If-Keep-Alive
    (--) Precondition                       -> Request-Finished
          + Signal-Precondition
          + Check-If-Keep-Alive

Get-Range-Header:
    (--) Ok                                 -> Get-Range-If-Header
          + Look-For-Range-If-Header
    (--) Not-Found                          -> After-Sending-File
          + Write-Http-Header
          + Send-File-To-Browser

Get-Range-If-Header:
    (--) Ok                                 -> Have-Range-To-Send
          + Signal-Partial-Content
          + Get-Next-Range-Specifier
    (--) Modified                           -> After-Sending-File
          + Write-Http-Header
          + Send-File-To-Browser

Have-Range-To-Send:
    (--) More                               -> After-Sending-Range
          + Write-Http-Range-Header
          + Write-Http-Range-Body
    (--) Finished                           -> Request-Finished
          + Check-If-Keep-Alive
          
After-Sending-Range:
    (--) Finished                           -> Have-Range-To-Send
          + Write-Http-Range-Footer
          + Get-Next-Range-Specifier
          
Process-Http-Post: <Client>
    (--) Html                               ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Cgi                                -> Have-Type-Of-Cgi
          + Check-File-Or-Directory
    (--) Filter                             -> Have-Type-Of-Filter
          + Check-File-Or-Directory
    (--) Wsx                                -> Trying-To-Get-Wsx
          + Check-If-Protected

Process-Http-Update: <Client>
    (--) Html                               -> Have-Type-Of-Update
          + Check-File-Or-Directory
    (--) Cgi                                ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Wsx                                ->
          + Signal-Bad-Request
          + Terminate-The-Thread
    (--) Filter                             ->
          + Signal-Bad-Request
          + Terminate-The-Thread

Have-Type-Of-Update: <Client>
    (--) File                               -> Trying-To-Update
          + Check-If-Protected
    (--) Not-Found                          -> Trying-To-Update
          + Check-If-Protected
    (--) Executable                         ->
          + Signal-Url-Forbidden
          + Terminate-The-Thread
    (--) Directory                          ->
          + Signal-Url-Forbidden
          + Terminate-The-Thread

Trying-To-Update: <Client>
    (--) Ok                                 -> Request-Finished
          + Update-Resource-From-Request
          + Write-Http-Header
          + Check-If-Keep-Alive

After-Sending-File: <Client>
    (--) Finished                           -> Request-Finished
          + Check-If-Keep-Alive

Trying-To-Get-Dir: <Client>
    (--) Ok                                 -> Have-Default
          + Get-Default-Web-Page

Have-Default: <Client>
    (--) File                               -> Process-Http-Get
          + Get-Url-Type
    (--) Not-Found                          -> After-Sending-File
          + Make-Directory-Listing
          + Write-Http-Header
          + Send-File-To-Browser

Have-Type-Of-Cgi: <Client>
!   If /cgi-bin contains non-executable file (e.g. image) we just send it
    (--) File                               -> Trying-To-Get-File
          + Check-If-Protected
    (--) Executable                         -> Before-Running-Cgi
          + Check-If-Protected
    (--) Directory                          -> Trying-To-Get-Dir
          + Check-If-Protected

Before-Running-Cgi: <Client>
    (--) Ok                                 -> Wait-For-Cgi
          + Create-Cgi-Process
          + Wait-Process-End

Wait-For-Cgi: <Client>
    (--) Timer                              -> Wait-For-Cgi
          + Wait-Process-End
    (--) Finished                           -> After-Sending-File
          + Close-Child-Process
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
    (--) Redirect                           -> Process-Http-Get
          + Get-Url-Type
    (--) Error                              ->
          + Close-Child-Process
          + Write-Http-Header
          + Terminate-The-Thread

Have-Type-Of-Filter: <Client>
    (--) File                               -> Trying-To-Get-Filter
          + Check-If-Protected
    (--) Executable                         -> Trying-To-Get-Filter
          + Check-If-Protected
    (--) Directory                          -> Trying-To-Get-Dir
          + Check-If-Protected

Trying-To-Get-Filter: <Client>
    (--) Ok                                 -> Wait-For-Filter
          + Create-Filter-Process
          + Wait-Process-End

Wait-For-Filter: <Client>
    (--) Timer                              -> Wait-For-Filter
          + Wait-Process-End
    (--) Finished                           -> After-Sending-File
          + Close-Child-Process
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
    (--) Redirect                           -> Process-Http-Get
          + Get-Url-Type
    (--) Error                              ->
          + Close-Child-Process
          + Write-Http-Header
          + Terminate-The-Thread

Trying-To-Get-Wsx: <Client>
    (--) Ok                                 -> Wait-For-Wsx
          + Pass-Request-To-Wsx-Agent

Wait-For-Wsx: <Client>
    (--) Wsx-Ok                             -> Process-Wsx-Done
          + Get-Wsx-Return-Fields
    (--) Wsx-Multi                          -> Process-Wsx-Multipart
          + Get-Wsx-Return-Fields
    (--) Wsx-Binary                         -> Process-Wsx-Done
          + Get-Wsx-Bin-Return-Fields
    (--) Wsx-Multibin                       -> Process-Wsx-Multipart
          + Get-Wsx-Bin-Return-Fields
    (--) Wsx-Error                          ->
          + Get-Wsx-Error-Fields
          + Write-Http-Header
          + Terminate-The-Thread
    (--) Wsx-Redirect                       ->
          + Get-Wsx-Redirect-Fields
          + Write-Http-Header
          + Terminate-The-Thread
    (--) Wsx-Restart                        -> Process-Wsx-Restart
          + Get-Wsx-Return-Fields
    (--) Wsx-Kill                           -> Process-Wsx-Kill
          + Get-Wsx-Return-Fields

Process-Wsx-Done:
!   Normally the WSX response data is in the event body
    (--) Wsx-Ok                             -> Request-Finished
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
          + Check-If-Keep-Alive
!   But it might be redirected to a file
    (--) Wsx-Redirect                       -> After-Sending-File
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser

Process-Wsx-Multipart:
    (--) Wsx-Ok                             -> Wait-For-Wsx
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
    (--) Wsx-Redirect                       -> Wait-For-Wsx
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser

Process-Wsx-Restart:
    (--) Wsx-Ok                             ->
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
          + Send-Master-Thread-Restart
          + Terminate-The-Thread
    (--) Wsx-Redirect                       ->
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
          + Send-Master-Thread-Restart
          + Terminate-The-Thread

Process-Wsx-Kill:
    (--) Wsx-Ok                             ->
          + Reparse-Http-Body
          + Write-Http-Header
          + Write-Http-Body
          + Send-Master-Thread-Shutdown
          + Terminate-The-Thread
    (--) Wsx-Redirect                       ->
          + Reparse-Process-Output
          + Write-Http-Header
          + Send-File-To-Browser
          + Send-Master-Thread-Shutdown
          + Terminate-The-Thread

Request-Finished: <Client>
    (--) Ok                                 -> Client-Input
          + Partial-Clear-Http-Context
          + Read-Input-From-Socket
    (--) Close                              ->
          + Terminate-The-Thread

Defaults:
    (--) Exception                          -> End-Thread
          + Check-Socket-Type
    (--) Shutdown                           -> End-Thread
          + Check-Socket-Type
    (--) Cancel                             -> End-Thread
          + Check-Socket-Type
    (--) Fatal                              ->
          + Free-All-Server-Resources
          + Shutdown-The-Application
          + Terminate-The-Thread
    (--) Sock-Error                         -> End-Thread
          + Check-Socket-Type
    (--) Sock-Closed                        -> End-Thread
          + Check-Socket-Type
    (--) Sock-Timeout                       -> End-Thread
          + Check-Socket-Type
    (--) Sock-Retry                         -> End-Thread
          + Check-Socket-Type
    (--) $other                             ->
          +

End-Thread:
    (--) Master                             ->
          + Free-All-Server-Resources
          + Shutdown-The-Application
          + Prepare-To-Close-Master-Socket
          + Close-Master-Socket
          + Terminate-The-Thread
    (--) Client                             ->
          + Flush-Socket-Requests
          + Terminate-The-Thread

!----------------------------------------------------------------------------
!                                                                            *
!   xiadmin.l - Administration Console                                       *
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
    (--) Ok                                 -> Start-Session
          +

Start-Session:
    (--) Ok                                 -> Select-Initial
          + Decode-Http-Initial-Request
          + Determine-Initial-Screen

Select-Initial:
    (--) Main                               -> Main-Menu
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse
    (--) Config                             -> Config-Server
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Hosts                              -> Config-List
          + Open-Config-List
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             -> Main-Menu
          + Close-All-Forms
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse

Main-Menu:
    (--) Config                             -> Config-Server
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Hosts                              -> Config-List
          + Open-Config-List
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Wizard                             -> Vhost-Wizard
          + Open-Vhost-Wizard
          + Show-Vhost-Wizard
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             -> Main-Menu
          + Close-All-Forms
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse

Config-List:
    (--) Enter                              ->
          + Check-Config-List-Livelink
    (--) Back                               ->
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Close-Current-Form
          + Dialog-Return
    (--) New                                -> Vhost-Wizard
          + Open-Vhost-Wizard
          + Show-Vhost-Wizard
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) First                              ->
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Show-Config-List-Next
          + Decode-Http-Request-Reponse
    (--) Default                            -> Config-Server
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Basehost                           -> Config-Server
          + Use-Basehost-Config-Name
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
!   Exceptions generated in this state
    (--) Select-Config                      -> Config-Server
          + Load-Current-Config-File
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Reshow-Form                        ->
          + Show-Config-List-First
          + Decode-Http-Request-Reponse
    (--) Return                             ->
          + Show-Config-List-First
          + Decode-Http-Request-Reponse

Config-Server:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Server
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Server-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Server-List
          + Update-Config-Server
          + Open-Config-Aliases
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Mimes                              -> Config-Server-List
          + Update-Config-Server
          + Open-Config-Mimes
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Errors                             -> Config-Errors
          + Update-Config-Server
          + Open-Config-Errors
          + Show-Config-Errors
          + Decode-Http-Request-Reponse
    (--) Wsx                                -> Config-Server-List
          + Update-Config-Server
          + Open-Config-Wsx
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Filters                            -> Config-Server-List
          + Update-Config-Server
          + Open-Config-Filter
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Ssi                                -> Config-Ssi
          + Update-Config-Server
          + Open-Config-Ssi
          + Show-Config-Ssi
          + Decode-Http-Request-Reponse
    (--) Ddns                               -> Config-Ddns
          + Update-Config-Server
          + Open-Config-Ddns
          + Show-Config-Ddns
          + Decode-Http-Request-Reponse
    (--) Advanced                           -> Config-Advanced
          + Update-Config-Server
          + Open-Config-Advanced
          + Show-Config-Advanced
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Server
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse

Config-Value-List:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Clear                              ->
          + Clear-Config-Value-List
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Show-Config-Value-List-Next
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse

Config-Server-List:  <Config-Value-List>
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse

Config-Errors:
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Update-Config-Errors
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Errors-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Errors
          + Decode-Http-Request-Reponse

Config-Ssi:
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Update-Config-Ssi
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Ssi-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Ssi
          + Decode-Http-Request-Reponse

Config-Ddns:
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Update-Config-Ddns
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Ddns-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Ddns
          + Decode-Http-Request-Reponse
    (--) Signon                             -> 
          + Send-Signon-To-Ddns-Agent
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Signoff                            -> 
          + Send-Signoff-To-Ddns-Agent
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse

Config-Advanced:
    (--) Back                               -> Config-Server
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Server
          + Update-Config-Advanced
          + Close-Current-Form
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Advanced-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Advanced
          + Decode-Http-Request-Reponse
    (--) Test                               ->
          + Update-Config-Advanced
          + Test-Url-Mapping
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse

Config-Cgi:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Cgi
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Cgi-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Cgi
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Environment                        -> Config-Cgi-Sub-List
          + Update-Config-Cgi
          + Open-Config-Cgi-Envir
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Cgi-Sub-List
          + Update-Config-Cgi
          + Open-Config-Cgi-Alias
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Cgi-Sub-List:  <Config-Value-List>
    (--) Back                               -> Config-Cgi
          + Close-Current-Form
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Cgi
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse

Config-Ftp:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Ftp
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Ftp-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Ftp
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Define-Users                       -> Config-Ftp-Users
          + Update-Config-Ftp
          + Open-Config-Ftp-Users
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) Define-Dirs                        -> Config-Ftp-Dirs
          + Update-Config-Ftp
          + Open-Config-Ftp-Dirs
          + Show-Config-Ftp-Dirs-First
          + Decode-Http-Request-Reponse
    (--) Aliases                            -> Config-Ftp-Sub-List
          + Update-Config-Ftp
          + Open-Config-Ftp-Alias
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Ftp-Users:  <Config-Value-List>
    (--) Enter                              ->
          + Check-Ftp-Users-Livelink
    (--) New                                -> Config-Ftp-User
          + Open-Config-Ftp-User
          + Show-Config-Ftp-User-New
          + Decode-Http-Request-Reponse
    (--) Back                               -> Config-Ftp
          + Cancel-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp
          + Save-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Show-Config-Ftp-Users-Next
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Config-Ftp-Users-Same
          + Decode-Http-Request-Reponse
!   Exceptions generated in this state
    (--) Select-User                        -> Config-Ftp-User
          + Open-Config-Ftp-User
          + Show-Config-Ftp-User
          + Decode-Http-Request-Reponse

Config-Ftp-User:
    (--) Back                               -> Config-Ftp-Users
          + Close-Current-Form
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) New                                ->
          + Show-Config-Ftp-User-New
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp-Users
          + Update-Config-Ftp-User
          + Close-Current-Form
          + Show-Config-Ftp-Users-First
          + Decode-Http-Request-Reponse
    (--) Delete                             ->
          + Delete-Config-Ftp-User
          + Show-Config-Ftp-User-Same
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Config-Ftp-User-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Ftp-User
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Update-Config-Ftp-User
          + Show-Config-Ftp-User-First
          + Decode-Http-Request-Reponse
    (--) Define                             ->
          + Set-Permissions-As-Chosen
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Update-Config-Ftp-User
          + Show-Config-Ftp-User-Next
          + Decode-Http-Request-Reponse

Config-Ftp-Dirs:
    (--) Enter                              ->
          + Check-Ftp-Dir-Livelink
    (--) Back                               -> Config-Ftp
          + Cancel-Config-Ftp-Dir-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp
          + Save-Config-Ftp-Dir-File
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Show-Config-Ftp-Dirs-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Show-Config-Ftp-Dirs-Next
          + Decode-Http-Request-Reponse
    (--) Define                             -> Config-Ftp-User-List
          + Check-New-Ftp-Dir-Name
          + Open-Config-Ftp-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
!   Exceptions generated in this state
    (--) Select-Resource                    -> Config-Ftp-User-List
          + Open-Config-Ftp-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-Ftp-User-List:  <Config-Value-List>
    (--) Back                               -> Config-Ftp-Dirs
          + Close-Current-Form
          + Show-Config-Ftp-Dirs-Same
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp-Dirs
          + Validate-Config-Value-List
          + Update-Config-Ftp-User-List
          + Close-Current-Form
          + Show-Config-Ftp-Dirs-Same
          + Decode-Http-Request-Reponse

Config-Ftp-Sub-List:  <Config-Value-List>
    (--) Back                               -> Config-Ftp
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Ftp
          + Validate-Config-Value-List
          + Update-Config-Value-List
          + Close-Current-Form
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse

Config-Security:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Security
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Security-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Logging                            -> Config-Logging
          + Update-Config-Security
          + Close-Current-Form
          + Open-Config-Logging
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Passwords                          -> Config-Resources
          + Update-Config-Security
          + Open-Config-Resources
          + Show-Config-Resources-First
          + Decode-Http-Request-Reponse

Config-Resources:
    (--) Enter                              ->
          + Check-Resources-Livelink
    (--) Back                               -> Config-Security
          + Cancel-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Security
          + Update-Config-Resources
          + Save-Config-Resource-File
          + Close-Current-Form
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Resources-First
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Update-Config-Resources
          + Show-Config-Resources-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Update-Config-Resources
          + Show-Config-Resources-Next
          + Decode-Http-Request-Reponse
    (--) Define                             -> Config-User-List
          + Update-Config-Resources
          + Check-New-Resource-Name
          + Open-Config-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
!   Exceptions generated in this state
    (--) Select-Resource                    -> Config-User-List
          + Open-Config-User-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse

Config-User-List: <Config-Value-List>
    (--) Back                               -> Config-Resources
          + Close-Current-Form
          + Show-Config-Resources-Same
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Resources
          + Update-Config-User-List
          + Close-Current-Form
          + Show-Config-Resources-Same
          + Decode-Http-Request-Reponse
    (--) First                              ->
          + Update-Config-Value-List
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Next                               ->
          + Update-Config-Value-List
          + Show-Config-Value-List-Next
          + Decode-Http-Request-Reponse

Config-Logging:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Config-Logging
          + Save-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Config-Logging-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Server                             -> Config-Server
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Server
          + Show-Config-Server
          + Decode-Http-Request-Reponse
    (--) Vhosts                             -> Config-Value-List
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Vhosts
          + Show-Config-Value-List-First
          + Decode-Http-Request-Reponse
    (--) Cgi                                -> Config-Cgi
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Cgi
          + Show-Config-Cgi
          + Decode-Http-Request-Reponse
    (--) Ftp                                -> Config-Ftp
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Ftp
          + Show-Config-Ftp
          + Decode-Http-Request-Reponse
    (--) Security                           -> Config-Security
          + Update-Config-Logging
          + Close-Current-Form
          + Open-Config-Security
          + Show-Config-Security
          + Decode-Http-Request-Reponse
    (--) ServerLog                         -> Config-Log-File
          + Update-Config-Logging
          + Open-Config-Log-File
          + Choose-Server-Log
          + Show-Log-File-Details
          + Decode-Http-Request-Reponse
    (--) AccessLog                          -> Config-Log-File
          + Update-Config-Logging
          + Open-Config-Log-File
          + Choose-Http-Access-Log
          + Show-Log-File-Details
          + Decode-Http-Request-Reponse
    (--) ErrorLog                           -> Config-Log-File
          + Update-Config-Logging
          + Open-Config-Log-File
          + Choose-Http-Error-Log
          + Show-Log-File-Details
          + Decode-Http-Request-Reponse
    (--) FtpLog                             -> Config-Log-File
          + Update-Config-Logging
          + Open-Config-Log-File
          + Choose-Ftp-Access-Log
          + Show-Log-File-Details
          + Decode-Http-Request-Reponse
    (--) FtpErrors                          -> Config-Log-File
          + Update-Config-Logging
          + Open-Config-Log-File
          + Choose-Ftp-Error-Log
          + Show-Log-File-Details
          + Decode-Http-Request-Reponse
    
Config-Log-File:
    (--) Back                               -> Config-Logging
          + Close-Current-Form
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Save                               -> Config-Logging
          + Update-Log-File-Details
          + Close-Current-Form
          + Show-Config-Logging
          + Decode-Http-Request-Reponse
    (--) Show                               ->
          + Show-Log-File-Format  
          + Decode-Http-Request-Reponse
    (--) Default                            ->
          + Show-Log-File-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Log-File-Details
          + Decode-Http-Request-Reponse
    (--) Cycle                              -> 
          + Cycle-Log-File-If-Possible
          + Decode-Http-Request-Reponse
    (--) Clear                              -> 
          + Clear-Log-File-If-Possible
          + Decode-Http-Request-Reponse
    
Console-Panel:
    (--) Back                               -> Main-Menu
          + Close-All-Forms
          + Open-Main-Admin-Menu
          + Show-Main-Admin-Menu
          + Decode-Http-Request-Reponse
    (--) Clear                              ->
          + Clear-Console-Panel-Statistics
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Define                             -> Console-Config
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Console-Config
          + Show-Console-Config
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Clear-Logs                         ->
          + Clear-All-Active-Logfiles
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Cycle-Logs                         ->
          + Cycle-All-Active-Logfiles
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Return                             ->
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Messages                           -> Console-Messages
          + Open-Console-Messages
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Details                            -> Connection-List
          + Open-Connection-List
          + Show-Connection-List
          + Decode-Http-Request-Reponse
    (--) Reshow-Form                        ->
          + Show-Console-Panel
          + Decode-Http-Request-Reponse

Console-Messages:
    (--) Back                               -> Console-Panel
          + Close-Current-Form
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Clear                              ->
          + Clear-Console-Messages
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Define                             -> Console-Config
          + Use-Defaults-Config-Name
          + Load-Current-Config-File
          + Open-Console-Config
          + Show-Console-Config
          + Decode-Http-Request-Reponse
          + Dialog-Call
    (--) Return                             ->
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Invert                             ->
          + Invert-Console-Data
          + Show-Console-Messages
          + Decode-Http-Request-Reponse
    (--) Reshow-Form                        ->
          + Show-Console-Messages
          + Decode-Http-Request-Reponse

Console-Config:
    (--) Back                               ->
          + Cancel-Current-Config-File
          + Close-Current-Form
          + Dialog-Return
    (--) Save                               ->
          + Update-Console-Config
          + Save-Current-Config-File
          + Reload-Server-Base-Config
          + Close-Current-Form
          + Dialog-Return
    (--) Default                            ->
          + Show-Console-Config-Defaults
          + Decode-Http-Request-Reponse
    (--) Undo                               ->
          + Show-Console-Config
          + Decode-Http-Request-Reponse

Connection-List:
    (--) Back                               -> Console-Panel
          + Close-Current-Form
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Refresh                            ->
          + Show-Connection-List
          + Decode-Http-Request-Reponse
    (--) Reshow-Form                        ->
          + Show-Connection-List
          + Decode-Http-Request-Reponse

Vhost-Wizard:
    (--) Back                               ->
          + Close-Current-Form
          + Dialog-Return
    (--) Define                             ->
          + Validate-Vhost-Definition
          + Create-Vhost-Definition
          + Close-Current-Form
          + Dialog-Return

Defaults:
    (--) Resource                           ->
          + Send-Resource-File-If-Known
          + Decode-Http-Request-Reponse
    (--) New-Session                        -> Select-Initial
          + Close-All-Forms
          + Determine-Initial-Screen
    (--) Reshow-Form                        ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Exception                          ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Data-Error                         ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse
    (--) Shutdown                           ->
          + Close-All-Forms
          + Terminate-The-Thread
    (--) Timeout                            ->
          +
!   Generally the same
    (--) Enter                              ->
          + Check-Simple-Livelink
    (--) Exit                               -> Start-Session
          + Close-All-Forms
          + Redirect-To-Home-Page
    (--) Console                            -> Console-Panel
          + Close-All-Forms
          + Open-Console-Panel
          + Show-Console-Panel
          + Decode-Http-Request-Reponse
    (--) Restart                            -> Select-Initial
          + Close-All-Forms
          + Restart-Http-Server-Agent
          + Decode-Http-Initial-Request
          + Determine-Initial-Screen
    (--) Halt                               ->
          + Close-All-Forms
          + Shutdown-Http-Server-Agent
          + Terminate-The-Thread
    (--) Help                               ->
          + Reshow-Current-Form
          + Decode-Http-Request-Reponse


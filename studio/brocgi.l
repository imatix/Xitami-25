!-----------------------------------------------------------------------------
!                                                                            !
!   brocgi.l - CGI broker functions                                          !
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
-schema=lrschema.c

After-Init:
    (--) Ok                                 -> Have-Session
          + Cleanup-Old-Sessions
          + Initialise-Session-Data
          + Parse-Arguments-If-Any
          + Check-If-New-Session
    (--) Error                              ->
          + Terminate-The-Program

Have-Session:
    (--) New-Session                        -> After-Program
          + Prepare-New-Session
          + Set-Initial-Program
          + Init-Program-Context
          + Start-The-Transaction
          + Invoke-Active-Program
    (--) In-Progress                        -> After-Program
          + Try-To-Restore-Context
          + Load-Program-Context
          + Start-The-Transaction
          + Invoke-Active-Program
    (--) Timed-Out                          ->
          + Signal-Session-Timed-Out
          + Terminate-The-Program
    (--) Out-Of-Step                        ->
          + Signal-Invalid-Session
          + Terminate-The-Program

After-Program:
    (--) Show                               ->
          + Send-Html-Form-To-Client
          + Save-Program-Context
          + Save-Session-Context
          + End-The-Transaction
          + Terminate-The-Program
    (--) Call                               -> After-Program
          + Save-Program-Context
          + Push-New-Active-Program
          + Init-Program-Context
          + Check-Program-Not-Active
          + Invoke-Active-Program
    (--) Call-Failed                        -> After-Program
          + Close-Program-Context
          + Pop-Old-Active-Program
          + Load-Program-Context
          + Invoke-Active-Program
    (--) Return                             -> After-Program
          + Close-Program-Context
          + Pop-Old-Active-Program
          + Load-Program-Context
          + Invoke-Active-Program
    !   Pop-Old signals 'Finished' if the stack is was empty
    (--) Finished                           -> After-Program
          + Set-Initial-Program
          + Init-Program-Context
          + Invoke-Active-Program

Defaults:
    (--) Exception                          ->
          + Delete-Session-Context
          + Terminate-The-Program
    (--) File-Io-Error
          + Signal-File-Io-Error
          + Terminate-The-Program

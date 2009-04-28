!-----------------------------------------------------------------------------
!                                                                            !
!   browtp.l - WTP broker functions                                          !
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
    (--) Ok                                 -> Have-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context
    (--) Error                              ->
          + Terminate-The-Program

Have-Request:
    (--) Ok                                 -> After-Program
          + Invoke-Active-Program
    (--) Error                              -> Have-Request
          + Wtp-Free-Do-Request
          + Wtp-Error-Invalid
          + Wtp-Get-Do-Request

After-Program:
    (--) Show                               -> Have-Request
          + Save-Session-Context
          + Wtp-Reply-Done-Show
          + Wtp-Free-Do-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context
    (--) Call                               -> Have-Request
          + Save-Session-Context
          + Wtp-Reply-Done-Call
          + Wtp-Free-Do-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context
    (--) Return                             -> Have-Request
          + Save-Session-Context
          + Wtp-Reply-Done-Return
          + Wtp-Free-Do-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context
    (--) Exit                               -> Have-Request
          + Wtp-Reply-Done-Exit
          + Wtp-Free-Do-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context
    (--) Error                              -> Have-Request
          + Wtp-Reply-Done-Error
          + Wtp-Free-Do-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context
    (--) Not-Found                          -> Have-Request
          + Wtp-Error-Not-Found
          + Wtp-Free-Do-Request
          + Wtp-Get-Do-Request
          + Load-Session-Context

Defaults:
    (--) Exception                          ->
          + Wtp-Free-Do-Request
          + Terminate-The-Program

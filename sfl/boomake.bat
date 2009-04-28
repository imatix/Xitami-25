@echo off
:-
:-  Boom builder for SFL 2.50
:-  Generated from standard.pwl on 2004/07/22
:-  See www.imatix.com for more information.
:-  Copyright (c) 1991-2003 iMatix Corporation
:-
if "%1"=="-goto" goto %2
if not "%OS%"=="Windows_NT" goto err_bad_os
:-
:-  Set environment variables to point to install location
:-  Start by using final IBASE, then handle local -install path
set self=%0
set OLDPATH=%PATH%
set OLDPERLLIB=%PERLLIB%
set _IBASE=%IBASE%
if "%_IBASE%"=="" set _IBASE=c:\imatix
set INCDIR=%_IBASE%\xitami-25\include
set LIBDIR=%_IBASE%\xitami-25\lib
set PATH=.;%_IBASE%\xitami-25\bin;%PATH%
set PERLLIB=.;%_IBASE%\xitami-25\bin;%PERLLIB%
set _LOCAL=0
if .%1==.-install (
    set _IBASE=%2
    set _LOCAL=1
    set PERLLIB=%2\xitami-25\bin;%PERLLIB%
    set PATH=%2\xitami-25\bin;%PATH%
    set INCDIR_ALT=%2\xitami-25\include
    set LIBDIR_ALT=%2\xitami-25\lib
    shift
    shift
)
goto process

:batch
    shift

:process
    set state=initial
    set event=ok
    set debug=0
    goto s_%state%

:---------------------------   BUILD BINARY FILES   ---------------------------

:a_build_binary_files
    if "%MSVCDir%"=="" set MSVCDir=C:\Program Files\Microsoft Visual Studio\VC98
    if not exist "%MSVCDir%\bin" (
        echo Cannot find MSVC compiler in %MSVCdir%.
        echo Please set MSVCDir environment variable to VC98 directory.
        goto err_exception
    )
    echo Building application...
    set COPTS=-g
    if %_LOCAL%==1 set COPTS=%COPTS% -li %INCDIR_ALT% -ll %LIBDIR_ALT%
    dir>nul
    call c -q %COPTS% sflbits
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflbits" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcomp
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcomp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcons
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcons" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflconv
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflconv" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcryp
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcryp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvbs
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvbs" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvdp
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvdp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvds
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvds" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvns
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvns" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvsb
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvsb" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvsd
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvsd" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvsn
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvsn" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvst
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvst" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvtp
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvtp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflcvts
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflcvts" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfldate
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfldate" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfldbio
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfldbio" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfldir
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfldir" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflenv
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflenv" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflexdr
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflexdr" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflfile
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflfile" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflfind
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflfind" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflfort
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflfort" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflhttp
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflhttp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflini
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflini" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfllang
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfllang" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfllbuf
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfllbuf" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfllist
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfllist" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflmail
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflmail" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflmath
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflmath" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflmem
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflmem" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflmesg
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflmesg" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflmime
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflmime" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflmysql
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflmysql" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflnode
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflnode" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflprint
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflprint" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflproc
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflproc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflslot
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflslot" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflsock
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflsock" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflstr
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflstr" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflsymb
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflsymb" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflsyst
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflsyst" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfltok
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfltok" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfltree
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfltree" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfltron
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfltron" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sfluid
    if errorlevel 1 echo boomake: "call c -q %COPTS% sfluid" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflxml
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflxml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% sflxmll
    if errorlevel 1 echo boomake: "call c -q %COPTS% sflxmll" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflbits
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflbits" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcomp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcomp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcons
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcons" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflconv
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflconv" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcryp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcryp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvbs
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvbs" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvdp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvdp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvds
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvds" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvns
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvns" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvsb
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvsb" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvsd
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvsd" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvsn
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvsn" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvst
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvst" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvtp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvtp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflcvts
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflcvts" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfldate
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfldate" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfldbio
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfldbio" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfldir
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfldir" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflenv
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflenv" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflexdr
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflexdr" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflfile
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflfile" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflfind
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflfind" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflfort
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflfort" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflhttp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflhttp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflini
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflini" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfllang
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfllang" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfllbuf
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfllbuf" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfllist
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfllist" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflmail
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflmail" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflmath
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflmath" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflmem
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflmem" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflmesg
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflmesg" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflmime
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflmime" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflmysql
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflmysql" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflnode
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflnode" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflprint
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflprint" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflproc
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflproc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflslot
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflslot" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflsock
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflsock" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflstr
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflstr" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflsymb
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflsymb" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflsyst
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflsyst" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfltok
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfltok" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfltree
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfltree" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfltron
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfltron" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sfluid
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sfluid" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflxml
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflxml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsfl.lib sflxmll
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsfl.lib sflxmll" failed
    if errorlevel 1 goto err_exception
    goto exit

:--------------------------   BUILD SOURCE PACKAGES   -------------------------

:a_build_source_packages
    if exist _package.lst del _package.lst
    if exist sfl\version.h echo sfl\version.h>>_package.lst
    if exist sfl\prelude.h echo sfl\prelude.h>>_package.lst
    if exist sfl\sflhead.h echo sfl\sflhead.h>>_package.lst
    if exist sfl\sflbits.c echo sfl\sflbits.c>>_package.lst
    if exist sfl\sflcomp.c echo sfl\sflcomp.c>>_package.lst
    if exist sfl\sflcons.c echo sfl\sflcons.c>>_package.lst
    if exist sfl\sflconv.c echo sfl\sflconv.c>>_package.lst
    if exist sfl\sflcryp.c echo sfl\sflcryp.c>>_package.lst
    if exist sfl\sflcvbs.c echo sfl\sflcvbs.c>>_package.lst
    if exist sfl\sflcvdp.c echo sfl\sflcvdp.c>>_package.lst
    if exist sfl\sflcvds.c echo sfl\sflcvds.c>>_package.lst
    if exist sfl\sflcvns.c echo sfl\sflcvns.c>>_package.lst
    if exist sfl\sflcvsb.c echo sfl\sflcvsb.c>>_package.lst
    if exist sfl\sflcvsd.c echo sfl\sflcvsd.c>>_package.lst
    if exist sfl\sflcvsn.c echo sfl\sflcvsn.c>>_package.lst
    if exist sfl\sflcvst.c echo sfl\sflcvst.c>>_package.lst
    if exist sfl\sflcvtp.c echo sfl\sflcvtp.c>>_package.lst
    if exist sfl\sflcvts.c echo sfl\sflcvts.c>>_package.lst
    if exist sfl\sfldate.c echo sfl\sfldate.c>>_package.lst
    if exist sfl\sfldbio.c echo sfl\sfldbio.c>>_package.lst
    if exist sfl\sfldir.c echo sfl\sfldir.c>>_package.lst
    if exist sfl\sflenv.c echo sfl\sflenv.c>>_package.lst
    if exist sfl\sflexdr.c echo sfl\sflexdr.c>>_package.lst
    if exist sfl\sflfile.c echo sfl\sflfile.c>>_package.lst
    if exist sfl\sflfind.c echo sfl\sflfind.c>>_package.lst
    if exist sfl\sflfort.c echo sfl\sflfort.c>>_package.lst
    if exist sfl\sflhttp.c echo sfl\sflhttp.c>>_package.lst
    if exist sfl\sflini.c echo sfl\sflini.c>>_package.lst
    if exist sfl\sfllang.c echo sfl\sfllang.c>>_package.lst
    if exist sfl\sfllbuf.c echo sfl\sfllbuf.c>>_package.lst
    if exist sfl\sfllist.c echo sfl\sfllist.c>>_package.lst
    if exist sfl\sflmail.c echo sfl\sflmail.c>>_package.lst
    if exist sfl\sflmath.c echo sfl\sflmath.c>>_package.lst
    if exist sfl\sflmem.c echo sfl\sflmem.c>>_package.lst
    if exist sfl\sflmesg.c echo sfl\sflmesg.c>>_package.lst
    if exist sfl\sflmime.c echo sfl\sflmime.c>>_package.lst
    if exist sfl\sflmysql.c echo sfl\sflmysql.c>>_package.lst
    if exist sfl\sflmysql.h echo sfl\sflmysql.h>>_package.lst
    if exist sfl\sflnode.c echo sfl\sflnode.c>>_package.lst
    if exist sfl\sflprint.c echo sfl\sflprint.c>>_package.lst
    if exist sfl\sflproc.c echo sfl\sflproc.c>>_package.lst
    if exist sfl\sflprocx.h echo sfl\sflprocx.h>>_package.lst
    if exist sfl\sflproco.imp echo sfl\sflproco.imp>>_package.lst
    if exist sfl\sflprocu.imp echo sfl\sflprocu.imp>>_package.lst
    if exist sfl\sflprocv.imp echo sfl\sflprocv.imp>>_package.lst
    if exist sfl\sflprocw.imp echo sfl\sflprocw.imp>>_package.lst
    if exist sfl\sflprocx.imp echo sfl\sflprocx.imp>>_package.lst
    if exist sfl\sflslot.c echo sfl\sflslot.c>>_package.lst
    if exist sfl\sflsock.c echo sfl\sflsock.c>>_package.lst
    if exist sfl\sflstr.c echo sfl\sflstr.c>>_package.lst
    if exist sfl\sflsymb.c echo sfl\sflsymb.c>>_package.lst
    if exist sfl\sflsyst.c echo sfl\sflsyst.c>>_package.lst
    if exist sfl\sfltok.c echo sfl\sfltok.c>>_package.lst
    if exist sfl\sfltree.c echo sfl\sfltree.c>>_package.lst
    if exist sfl\sfltron.c echo sfl\sfltron.c>>_package.lst
    if exist sfl\sfluid.c echo sfl\sfluid.c>>_package.lst
    if exist sfl\sflxml.c echo sfl\sflxml.c>>_package.lst
    if exist sfl\sflxmll.c echo sfl\sflxmll.c>>_package.lst
    if exist sfl\sflxmll.l echo sfl\sflxmll.l>>_package.lst
    if exist sfl\prelude.pdl echo sfl\prelude.pdl>>_package.lst
    if exist sfl\license.gpl echo sfl\license.gpl>>_package.lst
    if exist sfl\project.pdl echo sfl\project.pdl>>_package.lst
    if exist sfl\readme.txt echo sfl\readme.txt>>_package.lst
    if exist sfl\sflbits.h echo sfl\sflbits.h>>_package.lst
    if exist sfl\sflcomp.h echo sfl\sflcomp.h>>_package.lst
    if exist sfl\sflcons.h echo sfl\sflcons.h>>_package.lst
    if exist sfl\sflconv.h echo sfl\sflconv.h>>_package.lst
    if exist sfl\sflcryp.h echo sfl\sflcryp.h>>_package.lst
    if exist sfl\sflcvst.l echo sfl\sflcvst.l>>_package.lst
    if exist sfl\sflcvst.i echo sfl\sflcvst.i>>_package.lst
    if exist sfl\sflcvst.d echo sfl\sflcvst.d>>_package.lst
    if exist sfl\sfldate.h echo sfl\sfldate.h>>_package.lst
    if exist sfl\sfldbio.h echo sfl\sfldbio.h>>_package.lst
    if exist sfl\sfldir.h echo sfl\sfldir.h>>_package.lst
    if exist sfl\sflenv.h echo sfl\sflenv.h>>_package.lst
    if exist sfl\sflexdr.h echo sfl\sflexdr.h>>_package.lst
    if exist sfl\sflfile.h echo sfl\sflfile.h>>_package.lst
    if exist sfl\sflfind.h echo sfl\sflfind.h>>_package.lst
    if exist sfl\sflfort.h echo sfl\sflfort.h>>_package.lst
    if exist sfl\sflhttp.h echo sfl\sflhttp.h>>_package.lst
    if exist sfl\sflini.h echo sfl\sflini.h>>_package.lst
    if exist sfl\sfllang.h echo sfl\sfllang.h>>_package.lst
    if exist sfl\sfllbuf.h echo sfl\sfllbuf.h>>_package.lst
    if exist sfl\sfllist.h echo sfl\sfllist.h>>_package.lst
    if exist sfl\sflmail.h echo sfl\sflmail.h>>_package.lst
    if exist sfl\sflmath.h echo sfl\sflmath.h>>_package.lst
    if exist sfl\sflmem.h echo sfl\sflmem.h>>_package.lst
    if exist sfl\sflmesg.h echo sfl\sflmesg.h>>_package.lst
    if exist sfl\sflmime.h echo sfl\sflmime.h>>_package.lst
    if exist sfl\sflnode.h echo sfl\sflnode.h>>_package.lst
    if exist sfl\sflprint.h echo sfl\sflprint.h>>_package.lst
    if exist sfl\sflproc.h echo sfl\sflproc.h>>_package.lst
    if exist sfl\sflslot.h echo sfl\sflslot.h>>_package.lst
    if exist sfl\sflsock.h echo sfl\sflsock.h>>_package.lst
    if exist sfl\sflstr.h echo sfl\sflstr.h>>_package.lst
    if exist sfl\sflsymb.h echo sfl\sflsymb.h>>_package.lst
    if exist sfl\sflsyst.h echo sfl\sflsyst.h>>_package.lst
    if exist sfl\sfltok.h echo sfl\sfltok.h>>_package.lst
    if exist sfl\sfltree.h echo sfl\sfltree.h>>_package.lst
    if exist sfl\sfltron.h echo sfl\sfltron.h>>_package.lst
    if exist sfl\sfluid.h echo sfl\sfluid.h>>_package.lst
    if exist sfl\sflxml.h echo sfl\sflxml.h>>_package.lst
    if exist sfl\sflxmll.h echo sfl\sflxmll.h>>_package.lst
    if exist sfl\sflxmll.i echo sfl\sflxmll.i>>_package.lst
    if exist sfl\sflxmll.d echo sfl\sflxmll.d>>_package.lst
    if exist sfl\sfl.h echo sfl\sfl.h>>_package.lst
    if exist sfl\boomake echo sfl\boomake>>_package.lst
    if exist sfl\boomake.bat echo sfl\boomake.bat>>_package.lst
    if exist sfl\makefile echo sfl\makefile>>_package.lst
    if exist sfl\msmake echo sfl\msmake>>_package.lst
    echo Building sfl_2_50_src.zip...
    dir>nul
    zip -q sfl_2_50_src -@<_package.lst
    if errorlevel 1 echo boomake: "zip -q sfl_2_50_src -@<_package.lst" failed
    if errorlevel 1 goto err_exception
    del _package.lst
    goto exit

:------------------------   CHECK BINARY FILES EXIST   ------------------------

:a_check_binary_files_exist
    if not exist sflmysql.h (
        echo sflmysql.h is missing, cannot continue
        goto err_exception
    )
    if not exist libsfl.lib (
        echo libsfl.lib is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist sfl.h (
        echo sfl.h is missing, cannot continue
        goto err_exception
    )
    if not exist boomake (
        echo boomake is missing, cannot continue
        goto err_exception
    )
    if not exist boomake.bat (
        echo boomake.bat is missing, cannot continue
        goto err_exception
    )
    goto exit

:-------------------------   CHECK OPERATING CONTEXT   ------------------------

:a_check_operating_context
    set event=source
    if exist CVS\nul set event=rawcvs
    goto exit

:------------------------   CHECK PROJECT FILES EXIST   -----------------------

:a_check_project_files_exist
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.h (
        echo prelude.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflhead.h (
        echo sflhead.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflbits.c (
        echo sflbits.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcomp.c (
        echo sflcomp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcons.c (
        echo sflcons.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflconv.c (
        echo sflconv.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcryp.c (
        echo sflcryp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvbs.c (
        echo sflcvbs.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvdp.c (
        echo sflcvdp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvds.c (
        echo sflcvds.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvns.c (
        echo sflcvns.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvsb.c (
        echo sflcvsb.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvsd.c (
        echo sflcvsd.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvsn.c (
        echo sflcvsn.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvst.c (
        echo sflcvst.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvtp.c (
        echo sflcvtp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvts.c (
        echo sflcvts.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.c (
        echo sfldate.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfldbio.c (
        echo sfldbio.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfldir.c (
        echo sfldir.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflenv.c (
        echo sflenv.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflexdr.c (
        echo sflexdr.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflfile.c (
        echo sflfile.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflfind.c (
        echo sflfind.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflfort.c (
        echo sflfort.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflhttp.c (
        echo sflhttp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflini.c (
        echo sflini.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfllang.c (
        echo sfllang.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfllbuf.c (
        echo sfllbuf.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfllist.c (
        echo sfllist.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmail.c (
        echo sflmail.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmath.c (
        echo sflmath.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmem.c (
        echo sflmem.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmesg.c (
        echo sflmesg.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmime.c (
        echo sflmime.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmysql.c (
        echo sflmysql.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmysql.h (
        echo sflmysql.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflnode.c (
        echo sflnode.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflprint.c (
        echo sflprint.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflproc.c (
        echo sflproc.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocx.h (
        echo sflprocx.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflproco.imp (
        echo sflproco.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocu.imp (
        echo sflprocu.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocv.imp (
        echo sflprocv.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocw.imp (
        echo sflprocw.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocx.imp (
        echo sflprocx.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflslot.c (
        echo sflslot.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflsock.c (
        echo sflsock.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflstr.c (
        echo sflstr.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflsymb.c (
        echo sflsymb.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflsyst.c (
        echo sflsyst.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfltok.c (
        echo sfltok.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfltree.c (
        echo sfltree.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfltron.c (
        echo sfltron.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfluid.c (
        echo sfluid.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflxml.c (
        echo sflxml.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.c (
        echo sflxmll.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.l (
        echo sflxmll.l is missing, cannot continue
        goto err_exception
    )
    if not exist project.pdl (
        echo project.pdl is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist sflbits.h (
        echo sflbits.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcomp.h (
        echo sflcomp.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcons.h (
        echo sflcons.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflconv.h (
        echo sflconv.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcryp.h (
        echo sflcryp.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvst.l (
        echo sflcvst.l is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.h (
        echo sfldate.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfldbio.h (
        echo sfldbio.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfldir.h (
        echo sfldir.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflenv.h (
        echo sflenv.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflexdr.h (
        echo sflexdr.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflfile.h (
        echo sflfile.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflfind.h (
        echo sflfind.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflfort.h (
        echo sflfort.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflhttp.h (
        echo sflhttp.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflini.h (
        echo sflini.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfllang.h (
        echo sfllang.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfllbuf.h (
        echo sfllbuf.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfllist.h (
        echo sfllist.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmail.h (
        echo sflmail.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmath.h (
        echo sflmath.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmem.h (
        echo sflmem.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmesg.h (
        echo sflmesg.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmime.h (
        echo sflmime.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflnode.h (
        echo sflnode.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflprint.h (
        echo sflprint.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflproc.h (
        echo sflproc.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflslot.h (
        echo sflslot.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflsock.h (
        echo sflsock.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflstr.h (
        echo sflstr.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflsymb.h (
        echo sflsymb.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflsyst.h (
        echo sflsyst.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfltok.h (
        echo sfltok.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfltree.h (
        echo sfltree.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfltron.h (
        echo sfltron.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfluid.h (
        echo sfluid.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflxml.h (
        echo sflxml.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.h (
        echo sflxmll.h is missing, cannot continue
        goto err_exception
    )
    if not exist boomake (
        echo boomake is missing, cannot continue
        goto err_exception
    )
    if not exist boomake.bat (
        echo boomake.bat is missing, cannot continue
        goto err_exception
    )
    if not exist makefile (
        echo makefile is missing, cannot continue
        goto err_exception
    )
    if not exist msmake (
        echo msmake is missing, cannot continue
        goto err_exception
    )
    goto exit

:------------------------   CHECK SOURCE FILES EXIST   ------------------------

:a_check_source_files_exist
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.h (
        echo prelude.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflhead.h (
        echo sflhead.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflbits.c (
        echo sflbits.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcomp.c (
        echo sflcomp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcons.c (
        echo sflcons.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflconv.c (
        echo sflconv.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcryp.c (
        echo sflcryp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvbs.c (
        echo sflcvbs.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvdp.c (
        echo sflcvdp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvds.c (
        echo sflcvds.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvns.c (
        echo sflcvns.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvsb.c (
        echo sflcvsb.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvsd.c (
        echo sflcvsd.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvsn.c (
        echo sflcvsn.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvst.c (
        echo sflcvst.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvtp.c (
        echo sflcvtp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvts.c (
        echo sflcvts.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.c (
        echo sfldate.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfldbio.c (
        echo sfldbio.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfldir.c (
        echo sfldir.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflenv.c (
        echo sflenv.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflexdr.c (
        echo sflexdr.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflfile.c (
        echo sflfile.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflfind.c (
        echo sflfind.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflfort.c (
        echo sflfort.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflhttp.c (
        echo sflhttp.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflini.c (
        echo sflini.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfllang.c (
        echo sfllang.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfllbuf.c (
        echo sfllbuf.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfllist.c (
        echo sfllist.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmail.c (
        echo sflmail.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmath.c (
        echo sflmath.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmem.c (
        echo sflmem.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmesg.c (
        echo sflmesg.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmime.c (
        echo sflmime.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmysql.c (
        echo sflmysql.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflmysql.h (
        echo sflmysql.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflnode.c (
        echo sflnode.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflprint.c (
        echo sflprint.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflproc.c (
        echo sflproc.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocx.h (
        echo sflprocx.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflproco.imp (
        echo sflproco.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocu.imp (
        echo sflprocu.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocv.imp (
        echo sflprocv.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocw.imp (
        echo sflprocw.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflprocx.imp (
        echo sflprocx.imp is missing, cannot continue
        goto err_exception
    )
    if not exist sflslot.c (
        echo sflslot.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflsock.c (
        echo sflsock.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflstr.c (
        echo sflstr.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflsymb.c (
        echo sflsymb.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflsyst.c (
        echo sflsyst.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfltok.c (
        echo sfltok.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfltree.c (
        echo sfltree.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfltron.c (
        echo sfltron.c is missing, cannot continue
        goto err_exception
    )
    if not exist sfluid.c (
        echo sfluid.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflxml.c (
        echo sflxml.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.c (
        echo sflxmll.c is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.l (
        echo sflxmll.l is missing, cannot continue
        goto err_exception
    )
    if not exist project.pdl (
        echo project.pdl is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist sflbits.h (
        echo sflbits.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcomp.h (
        echo sflcomp.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcons.h (
        echo sflcons.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflconv.h (
        echo sflconv.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcryp.h (
        echo sflcryp.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvst.l (
        echo sflcvst.l is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvst.i (
        echo sflcvst.i is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvst.d (
        echo sflcvst.d is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.h (
        echo sfldate.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfldbio.h (
        echo sfldbio.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfldir.h (
        echo sfldir.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflenv.h (
        echo sflenv.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflexdr.h (
        echo sflexdr.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflfile.h (
        echo sflfile.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflfind.h (
        echo sflfind.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflfort.h (
        echo sflfort.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflhttp.h (
        echo sflhttp.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflini.h (
        echo sflini.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfllang.h (
        echo sfllang.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfllbuf.h (
        echo sfllbuf.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfllist.h (
        echo sfllist.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmail.h (
        echo sflmail.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmath.h (
        echo sflmath.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmem.h (
        echo sflmem.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmesg.h (
        echo sflmesg.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflmime.h (
        echo sflmime.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflnode.h (
        echo sflnode.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflprint.h (
        echo sflprint.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflproc.h (
        echo sflproc.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflslot.h (
        echo sflslot.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflsock.h (
        echo sflsock.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflstr.h (
        echo sflstr.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflsymb.h (
        echo sflsymb.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflsyst.h (
        echo sflsyst.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfltok.h (
        echo sfltok.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfltree.h (
        echo sfltree.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfltron.h (
        echo sfltron.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfluid.h (
        echo sfluid.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflxml.h (
        echo sflxml.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.h (
        echo sflxmll.h is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.i (
        echo sflxmll.i is missing, cannot continue
        goto err_exception
    )
    if not exist sflxmll.d (
        echo sflxmll.d is missing, cannot continue
        goto err_exception
    )
    if not exist sfl.h (
        echo sfl.h is missing, cannot continue
        goto err_exception
    )
    if not exist boomake (
        echo boomake is missing, cannot continue
        goto err_exception
    )
    if not exist boomake.bat (
        echo boomake.bat is missing, cannot continue
        goto err_exception
    )
    if not exist makefile (
        echo makefile is missing, cannot continue
        goto err_exception
    )
    if not exist msmake (
        echo msmake is missing, cannot continue
        goto err_exception
    )
    goto exit

:--------------------------   INSTALL DELIVERABLES   --------------------------

:a_install_deliverables
    set TARGET=%_IBASE%\xitami-25
    echo Installing SFL into %TARGET%...
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y sflmysql.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y sflmysql.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\lib\nul mkdir %TARGET%\lib\
    dir>nul
    copy/y libsfl.lib %TARGET%\lib\>nul
    if errorlevel 1 echo boomake: "copy/y libsfl.lib %TARGET%\lib\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    if not exist %TARGET%\doc\SFL\nul mkdir %TARGET%\doc\SFL\
    dir>nul
    copy/y readme.txt %TARGET%\doc\SFL\>nul
    if errorlevel 1 echo boomake: "copy/y readme.txt %TARGET%\doc\SFL\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y sfl.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y sfl.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception

    if exist %TARGET%\bin\setvars.bat goto have_setvars
    echo Creating %TARGET%\bin\setvars.bat...
    echo @echo off                                 >%TARGET%\bin\setvars.bat
    echo if "%%INCDIR%%"=="" (                    >>%TARGET%\bin\setvars.bat
    echo     set INCDIR=%TARGET%\include          >>%TARGET%\bin\setvars.bat
    echo     set LIBDIR=%TARGET%\lib              >>%TARGET%\bin\setvars.bat
    echo     set PATH=%TARGET%\bin;%%PATH%%       >>%TARGET%\bin\setvars.bat
    echo     set PERLLIB=%TARGET%\bin;%%PERLLIB%%>>%TARGET%\bin\setvars.bat
    echo )                                        >>%TARGET%\bin\setvars.bat
:have_setvars
    goto exit

:-------------------------   PRODUCE GENERATED FILES   ------------------------

:a_produce_generated_files
    if exist sfl.h del sfl.h
    type sflhead.h>>sfl.h
    type prelude.h>>sfl.h
    type sflbits.h>>sfl.h
    type sflcomp.h>>sfl.h
    type sflcons.h>>sfl.h
    type sflconv.h>>sfl.h
    type sflcryp.h>>sfl.h
    type sfldate.h>>sfl.h
    type sfldbio.h>>sfl.h
    type sflexdr.h>>sfl.h
    type sflfind.h>>sfl.h
    type sflfile.h>>sfl.h
    type sfllang.h>>sfl.h
    type sfllbuf.h>>sfl.h
    type sfllist.h>>sfl.h
    type sflmath.h>>sfl.h
    type sflmesg.h>>sfl.h
    type sflmem.h>>sfl.h
    type sflmime.h>>sfl.h
    type sflmysql.h>>sfl.h
    type sflnode.h>>sfl.h
    type sfldir.h>>sfl.h
    type sflslot.h>>sfl.h
    type sflstr.h>>sfl.h
    type sflsock.h>>sfl.h
    type sflsymb.h>>sfl.h
    type sflproc.h>>sfl.h
    type sflprint.h>>sfl.h
    type sflsyst.h>>sfl.h
    type sflhttp.h>>sfl.h
    type sflini.h>>sfl.h
    type sflenv.h>>sfl.h
    type sfltok.h>>sfl.h
    type sfltree.h>>sfl.h
    type sfltron.h>>sfl.h
    type sfluid.h>>sfl.h
    type sflxml.h>>sfl.h
    type sflxmll.h>>sfl.h
    dir>nul
    call lr sflxmll.l
    if errorlevel 1 echo boomake: "call lr sflxmll.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr sflcvst.l
    if errorlevel 1 echo boomake: "call lr sflcvst.l" failed
    if errorlevel 1 goto err_exception
    goto exit

:------------------------   REMOVE GENERATED BINARIES   -----------------------

:a_remove_generated_binaries
    if exist libsfl.lib del libsfl.lib
    if exist sflbits.obj del sflbits.obj
    if exist sflcomp.obj del sflcomp.obj
    if exist sflcons.obj del sflcons.obj
    if exist sflconv.obj del sflconv.obj
    if exist sflcryp.obj del sflcryp.obj
    if exist sflcvbs.obj del sflcvbs.obj
    if exist sflcvdp.obj del sflcvdp.obj
    if exist sflcvds.obj del sflcvds.obj
    if exist sflcvns.obj del sflcvns.obj
    if exist sflcvsb.obj del sflcvsb.obj
    if exist sflcvsd.obj del sflcvsd.obj
    if exist sflcvsn.obj del sflcvsn.obj
    if exist sflcvst.obj del sflcvst.obj
    if exist sflcvtp.obj del sflcvtp.obj
    if exist sflcvts.obj del sflcvts.obj
    if exist sfldate.obj del sfldate.obj
    if exist sfldbio.obj del sfldbio.obj
    if exist sfldir.obj del sfldir.obj
    if exist sflenv.obj del sflenv.obj
    if exist sflexdr.obj del sflexdr.obj
    if exist sflfile.obj del sflfile.obj
    if exist sflfind.obj del sflfind.obj
    if exist sflfort.obj del sflfort.obj
    if exist sflhttp.obj del sflhttp.obj
    if exist sflini.obj del sflini.obj
    if exist sfllang.obj del sfllang.obj
    if exist sfllbuf.obj del sfllbuf.obj
    if exist sfllist.obj del sfllist.obj
    if exist sflmail.obj del sflmail.obj
    if exist sflmath.obj del sflmath.obj
    if exist sflmem.obj del sflmem.obj
    if exist sflmesg.obj del sflmesg.obj
    if exist sflmime.obj del sflmime.obj
    if exist sflmysql.obj del sflmysql.obj
    if exist sflnode.obj del sflnode.obj
    if exist sflprint.obj del sflprint.obj
    if exist sflproc.obj del sflproc.obj
    if exist sflslot.obj del sflslot.obj
    if exist sflsock.obj del sflsock.obj
    if exist sflstr.obj del sflstr.obj
    if exist sflsymb.obj del sflsymb.obj
    if exist sflsyst.obj del sflsyst.obj
    if exist sfltok.obj del sfltok.obj
    if exist sfltree.obj del sfltree.obj
    if exist sfltron.obj del sfltron.obj
    if exist sfluid.obj del sfluid.obj
    if exist sflxml.obj del sflxml.obj
    if exist sflxmll.obj del sflxmll.obj
    if exist vc60.pdb del vc60.pdb
    goto exit

:------------------------   REMOVE GENERATED SOURCES   ------------------------

:a_remove_generated_sources
    if exist sflcvst.i del sflcvst.i
    if exist sflcvst.d del sflcvst.d
    if exist sflxmll.i del sflxmll.i
    if exist sflxmll.d del sflxmll.d
    if exist sfl.h del sfl.h
    goto exit

:-------------------------   REPORT HELP INFORMATION   ------------------------

:a_report_help_information
    echo boomake - Boom! builder for SFL 2.50
    echo Copyright (c) 1991-2003 iMatix Corporation
    echo.
    echo This script acts as a project 'make' tool.  Boom! uses an XML-based
    echo project description and generates various make tools (including this
    echo one) from it.  To find out more about Boom!, visit www.imatix.com.
    echo.
    goto r_%state%
    goto exit

:--------------------------   RUN REGRESSION TESTS   --------------------------

:a_run_regression_tests
    goto exit

:s_initial
    if "%debug%"=="1" echo State: initial
    if "%event%"=="" goto s_1_empty
    if "%event%"=="ok" goto s_1_1
    goto err_event
:s_1_1
    if "%debug%"=="1" echo Event: ok
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check operating context
    call %self% -goto a_check_operating_context
    if "%exception%"=="1" goto exit_clean
    set state=initial_check
    goto s_%state%
:s_1_empty
    if "%debug%"=="1" echo Get event from user
    set event=%1
    shift
    if "%event%"=="" set event=empty
    goto s_initial
:r_initial
    echo The actions you can use in this state are:
    goto exit

:s_initial_check
    if "%debug%"=="1" echo State: initial check
    if "%event%"=="" goto s_2_empty
    if "%event%"=="rawcvs" goto s_2_1
    if "%event%"=="source" goto s_2_2
    goto err_event
:s_2_1
    if "%debug%"=="1" echo Event: rawcvs
    set event=
    set exception=
    set state=rawcvs
    goto s_%state%
:s_2_2
    if "%debug%"=="1" echo Event: source
    set event=
    set exception=
    set state=source
    goto s_%state%
:s_2_empty
    if "%debug%"=="1" echo Get event from user
    set event=%1
    shift
    if "%event%"=="" set event=empty
    goto s_initial_check
:r_initial_check
    echo The actions you can use in this state are:
    goto exit

:s_rawcvs
    if "%debug%"=="1" echo State: rawcvs
    if "%event%"=="" goto s_3_empty
    if "%event%"=="build" goto s_3_1
    if "%event%"=="regen" goto s_3_2
    if "%event%"=="install" goto s_3_3
    if "%event%"=="distrib" goto s_3_4
    if "%event%"=="clean" goto s_3_5
    goto s_default
:s_3_1
    if "%debug%"=="1" echo Event: build
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check project files exist
    call %self% -goto a_check_project_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: produce generated files
    call %self% -goto a_produce_generated_files
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: check source files exist
    call %self% -goto a_check_source_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: build binary files
    call %self% -goto a_build_binary_files
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_3_2
    if "%debug%"=="1" echo Event: regen
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check project files exist
    call %self% -goto a_check_project_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: produce generated files
    call %self% -goto a_produce_generated_files
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_3_3
    if "%debug%"=="1" echo Event: install
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check binary files exist
    call %self% -goto a_check_binary_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: install deliverables
    call %self% -goto a_install_deliverables
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_3_4
    if "%debug%"=="1" echo Event: distrib
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check source files exist
    call %self% -goto a_check_source_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: build source packages
    call %self% -goto a_build_source_packages
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_3_5
    if "%debug%"=="1" echo Event: clean
    set event=
    set exception=
    if "%debug%"=="1" echo Action: remove generated sources
    call %self% -goto a_remove_generated_sources
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: remove generated binaries
    call %self% -goto a_remove_generated_binaries
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_3_empty
    if "%debug%"=="1" echo Get event from user
    set event=%1
    shift
    if "%event%"=="" set event=empty
    goto s_rawcvs
:r_rawcvs
    echo The actions you can use in this state are:
echo build:
    echo   
    echo     From the raw project sources, produces all generated files, and
    echo     compiles all source files.
echo regen:
    echo   
    echo     Produces all generated files.
echo install:
    echo   
    echo     Installs deliverables into the final or temporary install tree.
    echo     This action is only valid after a successful build.
echo distrib:
    echo   
    echo     Creates a source distribution for the project.  Note that binary
    echo     distributions can only be created at the product level.
echo clean:
    echo   
    echo     When working with the raw project sources, removes all generated
    echo     source and binary files from the project directory.
    goto exit

:s_source
    if "%debug%"=="1" echo State: source
    if "%event%"=="" goto s_4_empty
    if "%event%"=="build" goto s_4_1
    if "%event%"=="regen" goto s_4_2
    if "%event%"=="install" goto s_4_3
    if "%event%"=="distrib" goto s_4_4
    if "%event%"=="clean" goto s_4_5
    goto s_default
:s_4_1
    if "%debug%"=="1" echo Event: build
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check source files exist
    call %self% -goto a_check_source_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: build binary files
    call %self% -goto a_build_binary_files
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_4_2
    if "%debug%"=="1" echo Event: regen
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check project files exist
    call %self% -goto a_check_project_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: produce generated files
    call %self% -goto a_produce_generated_files
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_4_3
    if "%debug%"=="1" echo Event: install
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check binary files exist
    call %self% -goto a_check_binary_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: install deliverables
    call %self% -goto a_install_deliverables
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_4_4
    if "%debug%"=="1" echo Event: distrib
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check source files exist
    call %self% -goto a_check_source_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: build source packages
    call %self% -goto a_build_source_packages
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_4_5
    if "%debug%"=="1" echo Event: clean
    set event=
    set exception=
    if "%debug%"=="1" echo Action: remove generated binaries
    call %self% -goto a_remove_generated_binaries
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_4_empty
    if "%debug%"=="1" echo Get event from user
    set event=%1
    shift
    if "%event%"=="" set event=empty
    goto s_source
:r_source
    echo The actions you can use in this state are:
echo build:
    echo   
    echo     From the packaged sources, compiles all source files without any
    echo     code generation.
echo regen:
    echo   
    echo     Produces all generated files.
echo install:
    echo   
    echo     Installs deliverables into the final or temporary install tree.
    echo     This action is only valid after a successful build.
echo distrib:
    echo   
    echo     Creates a source distribution for the project.  Note that binary
    echo     distributions can only be created at the product level.
echo clean:
    echo   
    echo     When working with the packaged sources, removes all generated
    echo     source files from the project directory.
    goto exit

:s_default
    if "%debug%"=="1" echo State: default
    if "%event%"=="" goto s_5_empty
    if "%event%"=="test" goto s_5_1
    if "%event%"=="help" goto s_5_2
    if "%event%"=="empty" goto s_5_3
    goto err_event
:s_5_1
    if "%debug%"=="1" echo Event: test
    set event=
    set exception=
    if "%debug%"=="1" echo Action: check binary files exist
    call %self% -goto a_check_binary_files_exist
    if "%exception%"=="1" goto exit_clean
    if "%debug%"=="1" echo Action: run regression tests
    call %self% -goto a_run_regression_tests
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_5_2
    if "%debug%"=="1" echo Event: help
    set event=
    set exception=
    if "%debug%"=="1" echo Action: report help information
    call %self% -goto a_report_help_information
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_5_3
    if "%debug%"=="1" echo Event: empty
    set event=
    set exception=
    if "%debug%"=="1" echo Action: report help information
    call %self% -goto a_report_help_information
    if "%exception%"=="1" goto exit_clean
    if not "%1"=="" goto process
    goto exit_clean
:s_5_empty
    if "%debug%"=="1" echo Get event from user
    set event=%1
    shift
    if "%event%"=="" set event=empty
    goto s_default
:r_default
    echo The actions you can use in this state are:
echo test:
    echo   
    echo     Runs regression tests for the project.
echo help:
    echo   
    echo     Shows a list of the available builder commands.
    goto exit

:err_event
    echo '%event%' is not allowed here (state=%state%)
    goto exit_clean

:err_exception
    set exception=1
    goto exit

:err_badd_os
    echo This script requires Windows NT/2000
    goto exit

:exit_clean
    set self=
    set debug=
    set state=
    set event=
    set exception=
    set TARGET=
    set PATH=%OLDPATH%
    set PERLLIB=%OLDPERLLIB%
    set OLDPATH=
    set OLDPERLLIB=
    set INCDIR_ALT=
    set LIBDIR_ALT=
    set COPTS=
    set _LOCAL=
    set _IBASE=
    dir>nul
:exit

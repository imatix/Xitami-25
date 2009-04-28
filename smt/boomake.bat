@echo off
:-
:-  Boom builder for SMT 2.80
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
    call c -q %COPTS% smtecho
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtecho" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtftpc
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtftpc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtftpd
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtftpd" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtftpl
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtftpl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smthlog
    if errorlevel 1 echo boomake: "call c -q %COPTS% smthlog" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smthttp
    if errorlevel 1 echo boomake: "call c -q %COPTS% smthttp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smthttpl
    if errorlevel 1 echo boomake: "call c -q %COPTS% smthttpl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtlib
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtlib" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtlog
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtlog" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtoper
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtoper" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtpipe
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtpipe" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtrdns
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtrdns" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtrdnsl
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtrdnsl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtsimu
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtsimu" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtslot
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtslot" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtsock
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtsock" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smttime
    if errorlevel 1 echo boomake: "call c -q %COPTS% smttime" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smttran
    if errorlevel 1 echo boomake: "call c -q %COPTS% smttran" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smttst1
    if errorlevel 1 echo boomake: "call c -q %COPTS% smttst1" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smttst2
    if errorlevel 1 echo boomake: "call c -q %COPTS% smttst2" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smttst3
    if errorlevel 1 echo boomake: "call c -q %COPTS% smttst3" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtupmc
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtupmc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtupmd
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtupmd" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xiddns
    if errorlevel 1 echo boomake: "call c -q %COPTS% xiddns" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xierror
    if errorlevel 1 echo boomake: "call c -q %COPTS% xierror" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xiredir
    if errorlevel 1 echo boomake: "call c -q %COPTS% xiredir" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xiimap
    if errorlevel 1 echo boomake: "call c -q %COPTS% xiimap" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xilrwp
    if errorlevel 1 echo boomake: "call c -q %COPTS% xilrwp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xisuper
    if errorlevel 1 echo boomake: "call c -q %COPTS% xisuper" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xixlog
    if errorlevel 1 echo boomake: "call c -q %COPTS% xixlog" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xixssi
    if errorlevel 1 echo boomake: "call c -q %COPTS% xixssi" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xixxml
    if errorlevel 1 echo boomake: "call c -q %COPTS% xixxml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtmsg
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtmsg" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% smtsslm
    if errorlevel 1 echo boomake: "call c -q %COPTS% smtsslm" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xixlogm
    if errorlevel 1 echo boomake: "call c -q %COPTS% xixlogm" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtecho
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtecho" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtftpc
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtftpc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtftpd
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtftpd" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtftpl
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtftpl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smthlog
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smthlog" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smthttp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smthttp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smthttpl
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smthttpl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtlib
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtlib" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtlog
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtlog" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtoper
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtoper" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtpipe
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtpipe" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtrdns
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtrdns" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtrdnsl
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtrdnsl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtsimu
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtsimu" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtslot
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtslot" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtsock
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtsock" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smttime
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smttime" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smttran
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smttran" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smttst1
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smttst1" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smttst2
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smttst2" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smttst3
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smttst3" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtupmc
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtupmc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtupmd
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtupmd" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xiddns
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xiddns" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xierror
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xierror" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xiredir
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xiredir" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xiimap
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xiimap" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xilrwp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xilrwp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xisuper
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xisuper" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xixlog
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xixlog" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xixssi
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xixssi" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xixxml
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xixxml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtmsg
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtmsg" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib smtsslm
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib smtsslm" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libsmt.lib xixlogm
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libsmt.lib xixlogm" failed
    if errorlevel 1 goto err_exception
    goto exit

:--------------------------   BUILD SOURCE PACKAGES   -------------------------

:a_build_source_packages
    if exist _package.lst del _package.lst
    if exist smt\version.h echo smt\version.h>>_package.lst
    if exist smt\smtdefn.h echo smt\smtdefn.h>>_package.lst
    if exist smt\smtlib.h echo smt\smtlib.h>>_package.lst
    if exist smt\smtmsg.h echo smt\smtmsg.h>>_package.lst
    if exist smt\smtsslm.h echo smt\smtsslm.h>>_package.lst
    if exist smt\smthttpl.h echo smt\smthttpl.h>>_package.lst
    if exist smt\smtftpl.h echo smt\smtftpl.h>>_package.lst
    if exist smt\xixlogm.h echo smt\xixlogm.h>>_package.lst
    if exist smt\xixlog.h echo smt\xixlog.h>>_package.lst
    if exist smt\smtupm.h echo smt\smtupm.h>>_package.lst
    if exist smt\smtsimu.h echo smt\smtsimu.h>>_package.lst
    if exist smt\xilrwp.h echo smt\xilrwp.h>>_package.lst
    if exist smt\smtschm.c echo smt\smtschm.c>>_package.lst
    if exist smt\smtecho.c echo smt\smtecho.c>>_package.lst
    if exist smt\smtftpc.c echo smt\smtftpc.c>>_package.lst
    if exist smt\smtftpd.c echo smt\smtftpd.c>>_package.lst
    if exist smt\smtftpl.c echo smt\smtftpl.c>>_package.lst
    if exist smt\smthlog.c echo smt\smthlog.c>>_package.lst
    if exist smt\smthttp.c echo smt\smthttp.c>>_package.lst
    if exist smt\smthttpl.c echo smt\smthttpl.c>>_package.lst
    if exist smt\smtlib.c echo smt\smtlib.c>>_package.lst
    if exist smt\smtlog.c echo smt\smtlog.c>>_package.lst
    if exist smt\smtoper.c echo smt\smtoper.c>>_package.lst
    if exist smt\smtpipe.c echo smt\smtpipe.c>>_package.lst
    if exist smt\smtrdns.c echo smt\smtrdns.c>>_package.lst
    if exist smt\smtrdnsl.c echo smt\smtrdnsl.c>>_package.lst
    if exist smt\smtsimu.c echo smt\smtsimu.c>>_package.lst
    if exist smt\smtslot.c echo smt\smtslot.c>>_package.lst
    if exist smt\smtsock.c echo smt\smtsock.c>>_package.lst
    if exist smt\smttime.c echo smt\smttime.c>>_package.lst
    if exist smt\smttran.c echo smt\smttran.c>>_package.lst
    if exist smt\smttst1.c echo smt\smttst1.c>>_package.lst
    if exist smt\smttst2.c echo smt\smttst2.c>>_package.lst
    if exist smt\smttst3.c echo smt\smttst3.c>>_package.lst
    if exist smt\smtupmc.c echo smt\smtupmc.c>>_package.lst
    if exist smt\smtupmd.c echo smt\smtupmd.c>>_package.lst
    if exist smt\xiddns.c echo smt\xiddns.c>>_package.lst
    if exist smt\xierror.c echo smt\xierror.c>>_package.lst
    if exist smt\xiredir.c echo smt\xiredir.c>>_package.lst
    if exist smt\xiimap.c echo smt\xiimap.c>>_package.lst
    if exist smt\xilrwp.c echo smt\xilrwp.c>>_package.lst
    if exist smt\xisuper.c echo smt\xisuper.c>>_package.lst
    if exist smt\xixlog.c echo smt\xixlog.c>>_package.lst
    if exist smt\xixssi.c echo smt\xixssi.c>>_package.lst
    if exist smt\xixxml.c echo smt\xixxml.c>>_package.lst
    if exist smt\wsxrc echo smt\wsxrc>>_package.lst
    if exist smt\smtexdr.gsl echo smt\smtexdr.gsl>>_package.lst
    if exist smt\smtmsg.xml echo smt\smtmsg.xml>>_package.lst
    if exist smt\smtsslm.xml echo smt\smtsslm.xml>>_package.lst
    if exist smt\xixlogm.xml echo smt\xixlogm.xml>>_package.lst
    if exist smt\xiconfig.gsl echo smt\xiconfig.gsl>>_package.lst
    if exist smt\xiconfig.xml echo smt\xiconfig.xml>>_package.lst
    if exist smt\xiconfig.h echo smt\xiconfig.h>>_package.lst
    if exist smt\ximodel.gsl echo smt\ximodel.gsl>>_package.lst
    if exist smt\ximodel.xml echo smt\ximodel.xml>>_package.lst
    if exist smt\xicore.xml echo smt\xicore.xml>>_package.lst
    if exist smt\prelude.pdl echo smt\prelude.pdl>>_package.lst
    if exist smt\license.gpl echo smt\license.gpl>>_package.lst
    if exist smt\project.pdl echo smt\project.pdl>>_package.lst
    if exist smt\readme.txt echo smt\readme.txt>>_package.lst
    if exist smt\smtecho.l echo smt\smtecho.l>>_package.lst
    if exist smt\smtecho.i echo smt\smtecho.i>>_package.lst
    if exist smt\smtecho.d echo smt\smtecho.d>>_package.lst
    if exist smt\smtftpc.l echo smt\smtftpc.l>>_package.lst
    if exist smt\smtftpc.i echo smt\smtftpc.i>>_package.lst
    if exist smt\smtftpc.d echo smt\smtftpc.d>>_package.lst
    if exist smt\smtftpd.l echo smt\smtftpd.l>>_package.lst
    if exist smt\smtftpd.i echo smt\smtftpd.i>>_package.lst
    if exist smt\smtftpd.d echo smt\smtftpd.d>>_package.lst
    if exist smt\smthlog.l echo smt\smthlog.l>>_package.lst
    if exist smt\smthlog.i echo smt\smthlog.i>>_package.lst
    if exist smt\smthlog.d echo smt\smthlog.d>>_package.lst
    if exist smt\smthttp.l echo smt\smthttp.l>>_package.lst
    if exist smt\smthttp.i echo smt\smthttp.i>>_package.lst
    if exist smt\smthttp.d echo smt\smthttp.d>>_package.lst
    if exist smt\smtlog.l echo smt\smtlog.l>>_package.lst
    if exist smt\smtlog.i echo smt\smtlog.i>>_package.lst
    if exist smt\smtlog.d echo smt\smtlog.d>>_package.lst
    if exist smt\smtoper.l echo smt\smtoper.l>>_package.lst
    if exist smt\smtoper.i echo smt\smtoper.i>>_package.lst
    if exist smt\smtoper.d echo smt\smtoper.d>>_package.lst
    if exist smt\smtpipe.l echo smt\smtpipe.l>>_package.lst
    if exist smt\smtpipe.i echo smt\smtpipe.i>>_package.lst
    if exist smt\smtpipe.d echo smt\smtpipe.d>>_package.lst
    if exist smt\smtrdns.l echo smt\smtrdns.l>>_package.lst
    if exist smt\smtrdns.i echo smt\smtrdns.i>>_package.lst
    if exist smt\smtrdns.d echo smt\smtrdns.d>>_package.lst
    if exist smt\smtrdnsl.h echo smt\smtrdnsl.h>>_package.lst
    if exist smt\smtsimu.l echo smt\smtsimu.l>>_package.lst
    if exist smt\smtsimu.i echo smt\smtsimu.i>>_package.lst
    if exist smt\smtsimu.d echo smt\smtsimu.d>>_package.lst
    if exist smt\smtslot.l echo smt\smtslot.l>>_package.lst
    if exist smt\smtslot.i echo smt\smtslot.i>>_package.lst
    if exist smt\smtslot.d echo smt\smtslot.d>>_package.lst
    if exist smt\smtsock.l echo smt\smtsock.l>>_package.lst
    if exist smt\smtsock.i echo smt\smtsock.i>>_package.lst
    if exist smt\smtsock.d echo smt\smtsock.d>>_package.lst
    if exist smt\smttime.l echo smt\smttime.l>>_package.lst
    if exist smt\smttime.i echo smt\smttime.i>>_package.lst
    if exist smt\smttime.d echo smt\smttime.d>>_package.lst
    if exist smt\smttran.l echo smt\smttran.l>>_package.lst
    if exist smt\smttran.i echo smt\smttran.i>>_package.lst
    if exist smt\smttran.d echo smt\smttran.d>>_package.lst
    if exist smt\smttst1.l echo smt\smttst1.l>>_package.lst
    if exist smt\smttst1.i echo smt\smttst1.i>>_package.lst
    if exist smt\smttst1.d echo smt\smttst1.d>>_package.lst
    if exist smt\smttst2.l echo smt\smttst2.l>>_package.lst
    if exist smt\smttst2.i echo smt\smttst2.i>>_package.lst
    if exist smt\smttst2.d echo smt\smttst2.d>>_package.lst
    if exist smt\smttst3.l echo smt\smttst3.l>>_package.lst
    if exist smt\smttst3.i echo smt\smttst3.i>>_package.lst
    if exist smt\smttst3.d echo smt\smttst3.d>>_package.lst
    if exist smt\smtupmc.l echo smt\smtupmc.l>>_package.lst
    if exist smt\smtupmc.i echo smt\smtupmc.i>>_package.lst
    if exist smt\smtupmc.d echo smt\smtupmc.d>>_package.lst
    if exist smt\smtupmd.l echo smt\smtupmd.l>>_package.lst
    if exist smt\smtupmd.i echo smt\smtupmd.i>>_package.lst
    if exist smt\smtupmd.d echo smt\smtupmd.d>>_package.lst
    if exist smt\xiddns.l echo smt\xiddns.l>>_package.lst
    if exist smt\xiddns.i echo smt\xiddns.i>>_package.lst
    if exist smt\xiddns.d echo smt\xiddns.d>>_package.lst
    if exist smt\xierror.l echo smt\xierror.l>>_package.lst
    if exist smt\xierror.i echo smt\xierror.i>>_package.lst
    if exist smt\xierror.d echo smt\xierror.d>>_package.lst
    if exist smt\xiredir.l echo smt\xiredir.l>>_package.lst
    if exist smt\xiredir.i echo smt\xiredir.i>>_package.lst
    if exist smt\xiredir.d echo smt\xiredir.d>>_package.lst
    if exist smt\xiimap.l echo smt\xiimap.l>>_package.lst
    if exist smt\xiimap.i echo smt\xiimap.i>>_package.lst
    if exist smt\xiimap.d echo smt\xiimap.d>>_package.lst
    if exist smt\xilrwp.l echo smt\xilrwp.l>>_package.lst
    if exist smt\xilrwp.i echo smt\xilrwp.i>>_package.lst
    if exist smt\xilrwp.d echo smt\xilrwp.d>>_package.lst
    if exist smt\xisuper.l echo smt\xisuper.l>>_package.lst
    if exist smt\xisuper.i echo smt\xisuper.i>>_package.lst
    if exist smt\xisuper.d echo smt\xisuper.d>>_package.lst
    if exist smt\xixlog.l echo smt\xixlog.l>>_package.lst
    if exist smt\xixlog.i echo smt\xixlog.i>>_package.lst
    if exist smt\xixlog.d echo smt\xixlog.d>>_package.lst
    if exist smt\xixssi.l echo smt\xixssi.l>>_package.lst
    if exist smt\xixssi.i echo smt\xixssi.i>>_package.lst
    if exist smt\xixssi.d echo smt\xixssi.d>>_package.lst
    if exist smt\xixxml.l echo smt\xixxml.l>>_package.lst
    if exist smt\xixxml.i echo smt\xixxml.i>>_package.lst
    if exist smt\xixxml.d echo smt\xixxml.d>>_package.lst
    if exist smt\wsxrc.l echo smt\wsxrc.l>>_package.lst
    if exist smt\wsxrc.d echo smt\wsxrc.d>>_package.lst
    if exist smt\wsxrc.bat echo smt\wsxrc.bat>>_package.lst
    if exist smt\smtmsg.c echo smt\smtmsg.c>>_package.lst
    if exist smt\smtsslm.c echo smt\smtsslm.c>>_package.lst
    if exist smt\xixlogm.c echo smt\xixlogm.c>>_package.lst
    if exist smt\xicorpro.d echo smt\xicorpro.d>>_package.lst
    if exist smt\xicorpro.i echo smt\xicorpro.i>>_package.lst
    if exist smt\xicorstd.d echo smt\xicorstd.d>>_package.lst
    if exist smt\xicorstd.i echo smt\xicorstd.i>>_package.lst
    if exist smt\boomake echo smt\boomake>>_package.lst
    if exist smt\boomake.bat echo smt\boomake.bat>>_package.lst
    if exist smt\makefile echo smt\makefile>>_package.lst
    if exist smt\msmake echo smt\msmake>>_package.lst
    echo Building smt_2_80_src.zip...
    dir>nul
    zip -q smt_2_80_src -@<_package.lst
    if errorlevel 1 echo boomake: "zip -q smt_2_80_src -@<_package.lst" failed
    if errorlevel 1 goto err_exception
    del _package.lst
    goto exit

:------------------------   CHECK BINARY FILES EXIST   ------------------------

:a_check_binary_files_exist
    if not exist smtdefn.h (
        echo smtdefn.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtlib.h (
        echo smtlib.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtmsg.h (
        echo smtmsg.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtsslm.h (
        echo smtsslm.h is missing, cannot continue
        goto err_exception
    )
    if not exist smthttpl.h (
        echo smthttpl.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpl.h (
        echo smtftpl.h is missing, cannot continue
        goto err_exception
    )
    if not exist xixlogm.h (
        echo xixlogm.h is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.h (
        echo xixlog.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtschm.c (
        echo smtschm.c is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc (
        echo wsxrc is missing, cannot continue
        goto err_exception
    )
    if not exist smtexdr.gsl (
        echo smtexdr.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.gsl (
        echo xiconfig.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.xml (
        echo xiconfig.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ximodel.gsl (
        echo ximodel.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist ximodel.xml (
        echo ximodel.xml is missing, cannot continue
        goto err_exception
    )
    if not exist libsmt.lib (
        echo libsmt.lib is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.d (
        echo wsxrc.d is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.bat (
        echo wsxrc.bat is missing, cannot continue
        goto err_exception
    )
    if not exist xicorpro.d (
        echo xicorpro.d is missing, cannot continue
        goto err_exception
    )
    if not exist xicorpro.i (
        echo xicorpro.i is missing, cannot continue
        goto err_exception
    )
    if not exist xicorstd.d (
        echo xicorstd.d is missing, cannot continue
        goto err_exception
    )
    if not exist xicorstd.i (
        echo xicorstd.i is missing, cannot continue
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
    if not exist smtdefn.h (
        echo smtdefn.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtlib.h (
        echo smtlib.h is missing, cannot continue
        goto err_exception
    )
    if not exist smthttpl.h (
        echo smthttpl.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpl.h (
        echo smtftpl.h is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.h (
        echo xixlog.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtupm.h (
        echo smtupm.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.h (
        echo smtsimu.h is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.h (
        echo xilrwp.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtschm.c (
        echo smtschm.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtecho.c (
        echo smtecho.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpc.c (
        echo smtftpc.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpd.c (
        echo smtftpd.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpl.c (
        echo smtftpl.c is missing, cannot continue
        goto err_exception
    )
    if not exist smthlog.c (
        echo smthlog.c is missing, cannot continue
        goto err_exception
    )
    if not exist smthttp.c (
        echo smthttp.c is missing, cannot continue
        goto err_exception
    )
    if not exist smthttpl.c (
        echo smthttpl.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtlib.c (
        echo smtlib.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtlog.c (
        echo smtlog.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtoper.c (
        echo smtoper.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtpipe.c (
        echo smtpipe.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdns.c (
        echo smtrdns.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdnsl.c (
        echo smtrdnsl.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.c (
        echo smtsimu.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtslot.c (
        echo smtslot.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtsock.c (
        echo smtsock.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttime.c (
        echo smttime.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttran.c (
        echo smttran.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttst1.c (
        echo smttst1.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttst2.c (
        echo smttst2.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttst3.c (
        echo smttst3.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmc.c (
        echo smtupmc.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmd.c (
        echo smtupmd.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiddns.c (
        echo xiddns.c is missing, cannot continue
        goto err_exception
    )
    if not exist xierror.c (
        echo xierror.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiredir.c (
        echo xiredir.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiimap.c (
        echo xiimap.c is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.c (
        echo xilrwp.c is missing, cannot continue
        goto err_exception
    )
    if not exist xisuper.c (
        echo xisuper.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.c (
        echo xixlog.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixssi.c (
        echo xixssi.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixxml.c (
        echo xixxml.c is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc (
        echo wsxrc is missing, cannot continue
        goto err_exception
    )
    if not exist smtexdr.gsl (
        echo smtexdr.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist smtmsg.xml (
        echo smtmsg.xml is missing, cannot continue
        goto err_exception
    )
    if not exist smtsslm.xml (
        echo smtsslm.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xixlogm.xml (
        echo xixlogm.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.gsl (
        echo xiconfig.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.xml (
        echo xiconfig.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ximodel.gsl (
        echo ximodel.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist ximodel.xml (
        echo ximodel.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xicore.xml (
        echo xicore.xml is missing, cannot continue
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
    if not exist smtecho.l (
        echo smtecho.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpc.l (
        echo smtftpc.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpd.l (
        echo smtftpd.l is missing, cannot continue
        goto err_exception
    )
    if not exist smthlog.l (
        echo smthlog.l is missing, cannot continue
        goto err_exception
    )
    if not exist smthttp.l (
        echo smthttp.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtlog.l (
        echo smtlog.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtoper.l (
        echo smtoper.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtpipe.l (
        echo smtpipe.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdns.l (
        echo smtrdns.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdnsl.h (
        echo smtrdnsl.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.l (
        echo smtsimu.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtslot.l (
        echo smtslot.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtsock.l (
        echo smtsock.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttime.l (
        echo smttime.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttran.l (
        echo smttran.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttst1.l (
        echo smttst1.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttst2.l (
        echo smttst2.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttst3.l (
        echo smttst3.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmc.l (
        echo smtupmc.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmd.l (
        echo smtupmd.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiddns.l (
        echo xiddns.l is missing, cannot continue
        goto err_exception
    )
    if not exist xierror.l (
        echo xierror.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiredir.l (
        echo xiredir.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiimap.l (
        echo xiimap.l is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.l (
        echo xilrwp.l is missing, cannot continue
        goto err_exception
    )
    if not exist xisuper.l (
        echo xisuper.l is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.l (
        echo xixlog.l is missing, cannot continue
        goto err_exception
    )
    if not exist xixssi.l (
        echo xixssi.l is missing, cannot continue
        goto err_exception
    )
    if not exist xixxml.l (
        echo xixxml.l is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.l (
        echo wsxrc.l is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.bat (
        echo wsxrc.bat is missing, cannot continue
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
    if not exist smtdefn.h (
        echo smtdefn.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtlib.h (
        echo smtlib.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtmsg.h (
        echo smtmsg.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtsslm.h (
        echo smtsslm.h is missing, cannot continue
        goto err_exception
    )
    if not exist smthttpl.h (
        echo smthttpl.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpl.h (
        echo smtftpl.h is missing, cannot continue
        goto err_exception
    )
    if not exist xixlogm.h (
        echo xixlogm.h is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.h (
        echo xixlog.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtupm.h (
        echo smtupm.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.h (
        echo smtsimu.h is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.h (
        echo xilrwp.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtschm.c (
        echo smtschm.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtecho.c (
        echo smtecho.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpc.c (
        echo smtftpc.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpd.c (
        echo smtftpd.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpl.c (
        echo smtftpl.c is missing, cannot continue
        goto err_exception
    )
    if not exist smthlog.c (
        echo smthlog.c is missing, cannot continue
        goto err_exception
    )
    if not exist smthttp.c (
        echo smthttp.c is missing, cannot continue
        goto err_exception
    )
    if not exist smthttpl.c (
        echo smthttpl.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtlib.c (
        echo smtlib.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtlog.c (
        echo smtlog.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtoper.c (
        echo smtoper.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtpipe.c (
        echo smtpipe.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdns.c (
        echo smtrdns.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdnsl.c (
        echo smtrdnsl.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.c (
        echo smtsimu.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtslot.c (
        echo smtslot.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtsock.c (
        echo smtsock.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttime.c (
        echo smttime.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttran.c (
        echo smttran.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttst1.c (
        echo smttst1.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttst2.c (
        echo smttst2.c is missing, cannot continue
        goto err_exception
    )
    if not exist smttst3.c (
        echo smttst3.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmc.c (
        echo smtupmc.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmd.c (
        echo smtupmd.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiddns.c (
        echo xiddns.c is missing, cannot continue
        goto err_exception
    )
    if not exist xierror.c (
        echo xierror.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiredir.c (
        echo xiredir.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiimap.c (
        echo xiimap.c is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.c (
        echo xilrwp.c is missing, cannot continue
        goto err_exception
    )
    if not exist xisuper.c (
        echo xisuper.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.c (
        echo xixlog.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixssi.c (
        echo xixssi.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixxml.c (
        echo xixxml.c is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc (
        echo wsxrc is missing, cannot continue
        goto err_exception
    )
    if not exist smtexdr.gsl (
        echo smtexdr.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist smtmsg.xml (
        echo smtmsg.xml is missing, cannot continue
        goto err_exception
    )
    if not exist smtsslm.xml (
        echo smtsslm.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xixlogm.xml (
        echo xixlogm.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.gsl (
        echo xiconfig.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.xml (
        echo xiconfig.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.h (
        echo xiconfig.h is missing, cannot continue
        goto err_exception
    )
    if not exist ximodel.gsl (
        echo ximodel.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist ximodel.xml (
        echo ximodel.xml is missing, cannot continue
        goto err_exception
    )
    if not exist xicore.xml (
        echo xicore.xml is missing, cannot continue
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
    if not exist smtecho.l (
        echo smtecho.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtecho.i (
        echo smtecho.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtecho.d (
        echo smtecho.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpc.l (
        echo smtftpc.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpc.i (
        echo smtftpc.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpc.d (
        echo smtftpc.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpd.l (
        echo smtftpd.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpd.i (
        echo smtftpd.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtftpd.d (
        echo smtftpd.d is missing, cannot continue
        goto err_exception
    )
    if not exist smthlog.l (
        echo smthlog.l is missing, cannot continue
        goto err_exception
    )
    if not exist smthlog.i (
        echo smthlog.i is missing, cannot continue
        goto err_exception
    )
    if not exist smthlog.d (
        echo smthlog.d is missing, cannot continue
        goto err_exception
    )
    if not exist smthttp.l (
        echo smthttp.l is missing, cannot continue
        goto err_exception
    )
    if not exist smthttp.i (
        echo smthttp.i is missing, cannot continue
        goto err_exception
    )
    if not exist smthttp.d (
        echo smthttp.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtlog.l (
        echo smtlog.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtlog.i (
        echo smtlog.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtlog.d (
        echo smtlog.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtoper.l (
        echo smtoper.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtoper.i (
        echo smtoper.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtoper.d (
        echo smtoper.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtpipe.l (
        echo smtpipe.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtpipe.i (
        echo smtpipe.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtpipe.d (
        echo smtpipe.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdns.l (
        echo smtrdns.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdns.i (
        echo smtrdns.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdns.d (
        echo smtrdns.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtrdnsl.h (
        echo smtrdnsl.h is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.l (
        echo smtsimu.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.i (
        echo smtsimu.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtsimu.d (
        echo smtsimu.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtslot.l (
        echo smtslot.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtslot.i (
        echo smtslot.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtslot.d (
        echo smtslot.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtsock.l (
        echo smtsock.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtsock.i (
        echo smtsock.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtsock.d (
        echo smtsock.d is missing, cannot continue
        goto err_exception
    )
    if not exist smttime.l (
        echo smttime.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttime.i (
        echo smttime.i is missing, cannot continue
        goto err_exception
    )
    if not exist smttime.d (
        echo smttime.d is missing, cannot continue
        goto err_exception
    )
    if not exist smttran.l (
        echo smttran.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttran.i (
        echo smttran.i is missing, cannot continue
        goto err_exception
    )
    if not exist smttran.d (
        echo smttran.d is missing, cannot continue
        goto err_exception
    )
    if not exist smttst1.l (
        echo smttst1.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttst1.i (
        echo smttst1.i is missing, cannot continue
        goto err_exception
    )
    if not exist smttst1.d (
        echo smttst1.d is missing, cannot continue
        goto err_exception
    )
    if not exist smttst2.l (
        echo smttst2.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttst2.i (
        echo smttst2.i is missing, cannot continue
        goto err_exception
    )
    if not exist smttst2.d (
        echo smttst2.d is missing, cannot continue
        goto err_exception
    )
    if not exist smttst3.l (
        echo smttst3.l is missing, cannot continue
        goto err_exception
    )
    if not exist smttst3.i (
        echo smttst3.i is missing, cannot continue
        goto err_exception
    )
    if not exist smttst3.d (
        echo smttst3.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmc.l (
        echo smtupmc.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmc.i (
        echo smtupmc.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmc.d (
        echo smtupmc.d is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmd.l (
        echo smtupmd.l is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmd.i (
        echo smtupmd.i is missing, cannot continue
        goto err_exception
    )
    if not exist smtupmd.d (
        echo smtupmd.d is missing, cannot continue
        goto err_exception
    )
    if not exist xiddns.l (
        echo xiddns.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiddns.i (
        echo xiddns.i is missing, cannot continue
        goto err_exception
    )
    if not exist xiddns.d (
        echo xiddns.d is missing, cannot continue
        goto err_exception
    )
    if not exist xierror.l (
        echo xierror.l is missing, cannot continue
        goto err_exception
    )
    if not exist xierror.i (
        echo xierror.i is missing, cannot continue
        goto err_exception
    )
    if not exist xierror.d (
        echo xierror.d is missing, cannot continue
        goto err_exception
    )
    if not exist xiredir.l (
        echo xiredir.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiredir.i (
        echo xiredir.i is missing, cannot continue
        goto err_exception
    )
    if not exist xiredir.d (
        echo xiredir.d is missing, cannot continue
        goto err_exception
    )
    if not exist xiimap.l (
        echo xiimap.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiimap.i (
        echo xiimap.i is missing, cannot continue
        goto err_exception
    )
    if not exist xiimap.d (
        echo xiimap.d is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.l (
        echo xilrwp.l is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.i (
        echo xilrwp.i is missing, cannot continue
        goto err_exception
    )
    if not exist xilrwp.d (
        echo xilrwp.d is missing, cannot continue
        goto err_exception
    )
    if not exist xisuper.l (
        echo xisuper.l is missing, cannot continue
        goto err_exception
    )
    if not exist xisuper.i (
        echo xisuper.i is missing, cannot continue
        goto err_exception
    )
    if not exist xisuper.d (
        echo xisuper.d is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.l (
        echo xixlog.l is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.i (
        echo xixlog.i is missing, cannot continue
        goto err_exception
    )
    if not exist xixlog.d (
        echo xixlog.d is missing, cannot continue
        goto err_exception
    )
    if not exist xixssi.l (
        echo xixssi.l is missing, cannot continue
        goto err_exception
    )
    if not exist xixssi.i (
        echo xixssi.i is missing, cannot continue
        goto err_exception
    )
    if not exist xixssi.d (
        echo xixssi.d is missing, cannot continue
        goto err_exception
    )
    if not exist xixxml.l (
        echo xixxml.l is missing, cannot continue
        goto err_exception
    )
    if not exist xixxml.i (
        echo xixxml.i is missing, cannot continue
        goto err_exception
    )
    if not exist xixxml.d (
        echo xixxml.d is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.l (
        echo wsxrc.l is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.d (
        echo wsxrc.d is missing, cannot continue
        goto err_exception
    )
    if not exist wsxrc.bat (
        echo wsxrc.bat is missing, cannot continue
        goto err_exception
    )
    if not exist smtmsg.c (
        echo smtmsg.c is missing, cannot continue
        goto err_exception
    )
    if not exist smtsslm.c (
        echo smtsslm.c is missing, cannot continue
        goto err_exception
    )
    if not exist xixlogm.c (
        echo xixlogm.c is missing, cannot continue
        goto err_exception
    )
    if not exist xicorpro.d (
        echo xicorpro.d is missing, cannot continue
        goto err_exception
    )
    if not exist xicorpro.i (
        echo xicorpro.i is missing, cannot continue
        goto err_exception
    )
    if not exist xicorstd.d (
        echo xicorstd.d is missing, cannot continue
        goto err_exception
    )
    if not exist xicorstd.i (
        echo xicorstd.i is missing, cannot continue
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
    echo Installing SMT into %TARGET%...
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y smtdefn.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y smtdefn.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y smtlib.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y smtlib.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y smtmsg.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y smtmsg.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y smtsslm.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y smtsslm.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y smthttpl.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y smthttpl.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y smtftpl.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y smtftpl.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xixlogm.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y xixlogm.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xixlog.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y xixlog.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    dir>nul
    copy/y smtschm.c %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y smtschm.c %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y wsxrc %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y wsxrc %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y smtexdr.gsl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y smtexdr.gsl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xiconfig.gsl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y xiconfig.gsl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xiconfig.xml %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y xiconfig.xml %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ximodel.gsl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y ximodel.gsl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ximodel.xml %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y ximodel.xml %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\lib\nul mkdir %TARGET%\lib\
    dir>nul
    copy/y libsmt.lib %TARGET%\lib\>nul
    if errorlevel 1 echo boomake: "copy/y libsmt.lib %TARGET%\lib\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    if not exist %TARGET%\doc\SMT\nul mkdir %TARGET%\doc\SMT\
    dir>nul
    copy/y readme.txt %TARGET%\doc\SMT\>nul
    if errorlevel 1 echo boomake: "copy/y readme.txt %TARGET%\doc\SMT\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    dir>nul
    copy/y wsxrc.d %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y wsxrc.d %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y wsxrc.bat %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y wsxrc.bat %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y xicorpro.d %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y xicorpro.d %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xicorpro.i %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y xicorpro.i %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xicorstd.d %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y xicorstd.d %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xicorstd.i %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y xicorstd.i %TARGET%\include\>nul" failed
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
    dir>nul
    call gsl -q -build_header:1 xiconfig
    if errorlevel 1 echo boomake: "call gsl -q -build_header:1 xiconfig" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call gsl -q smtmsg.xml
    if errorlevel 1 echo boomake: "call gsl -q smtmsg.xml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call gsl -q smtsslm.xml
    if errorlevel 1 echo boomake: "call gsl -q smtsslm.xml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call gsl -q xixlogm.xml
    if errorlevel 1 echo boomake: "call gsl -q xixlogm.xml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call gsl -q xicore.xml
    if errorlevel 1 echo boomake: "call gsl -q xicore.xml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtecho.l
    if errorlevel 1 echo boomake: "call lr smtecho.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtftpc.l
    if errorlevel 1 echo boomake: "call lr smtftpc.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtftpd.l
    if errorlevel 1 echo boomake: "call lr smtftpd.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smthlog.l
    if errorlevel 1 echo boomake: "call lr smthlog.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smthttp.l
    if errorlevel 1 echo boomake: "call lr smthttp.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtlog.l
    if errorlevel 1 echo boomake: "call lr smtlog.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtoper.l
    if errorlevel 1 echo boomake: "call lr smtoper.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtpipe.l
    if errorlevel 1 echo boomake: "call lr smtpipe.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtrdns.l
    if errorlevel 1 echo boomake: "call lr smtrdns.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtsimu.l
    if errorlevel 1 echo boomake: "call lr smtsimu.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtslot.l
    if errorlevel 1 echo boomake: "call lr smtslot.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtsock.l
    if errorlevel 1 echo boomake: "call lr smtsock.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smttime.l
    if errorlevel 1 echo boomake: "call lr smttime.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smttran.l
    if errorlevel 1 echo boomake: "call lr smttran.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smttst1.l
    if errorlevel 1 echo boomake: "call lr smttst1.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smttst2.l
    if errorlevel 1 echo boomake: "call lr smttst2.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smttst3.l
    if errorlevel 1 echo boomake: "call lr smttst3.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtupmc.l
    if errorlevel 1 echo boomake: "call lr smtupmc.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr smtupmd.l
    if errorlevel 1 echo boomake: "call lr smtupmd.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xiddns.l
    if errorlevel 1 echo boomake: "call lr xiddns.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xierror.l
    if errorlevel 1 echo boomake: "call lr xierror.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xiredir.l
    if errorlevel 1 echo boomake: "call lr xiredir.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xiimap.l
    if errorlevel 1 echo boomake: "call lr xiimap.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xilrwp.l
    if errorlevel 1 echo boomake: "call lr xilrwp.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xisuper.l
    if errorlevel 1 echo boomake: "call lr xisuper.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xixlog.l
    if errorlevel 1 echo boomake: "call lr xixlog.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xixssi.l
    if errorlevel 1 echo boomake: "call lr xixssi.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xixxml.l
    if errorlevel 1 echo boomake: "call lr xixxml.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr wsxrc.l
    if errorlevel 1 echo boomake: "call lr wsxrc.l" failed
    if errorlevel 1 goto err_exception
    goto exit

:------------------------   REMOVE GENERATED BINARIES   -----------------------

:a_remove_generated_binaries
    if exist libsmt.lib del libsmt.lib
    if exist smtecho.obj del smtecho.obj
    if exist smtftpc.obj del smtftpc.obj
    if exist smtftpd.obj del smtftpd.obj
    if exist smtftpl.obj del smtftpl.obj
    if exist smthlog.obj del smthlog.obj
    if exist smthttp.obj del smthttp.obj
    if exist smthttpl.obj del smthttpl.obj
    if exist smtlib.obj del smtlib.obj
    if exist smtlog.obj del smtlog.obj
    if exist smtoper.obj del smtoper.obj
    if exist smtpipe.obj del smtpipe.obj
    if exist smtrdns.obj del smtrdns.obj
    if exist smtrdnsl.obj del smtrdnsl.obj
    if exist smtsimu.obj del smtsimu.obj
    if exist smtslot.obj del smtslot.obj
    if exist smtsock.obj del smtsock.obj
    if exist smttime.obj del smttime.obj
    if exist smttran.obj del smttran.obj
    if exist smttst1.obj del smttst1.obj
    if exist smttst2.obj del smttst2.obj
    if exist smttst3.obj del smttst3.obj
    if exist smtupmc.obj del smtupmc.obj
    if exist smtupmd.obj del smtupmd.obj
    if exist xiddns.obj del xiddns.obj
    if exist xierror.obj del xierror.obj
    if exist xiredir.obj del xiredir.obj
    if exist xiimap.obj del xiimap.obj
    if exist xilrwp.obj del xilrwp.obj
    if exist xisuper.obj del xisuper.obj
    if exist xixlog.obj del xixlog.obj
    if exist xixssi.obj del xixssi.obj
    if exist xixxml.obj del xixxml.obj
    if exist smtmsg.c.obj del smtmsg.c.obj
    if exist smtsslm.c.obj del smtsslm.c.obj
    if exist xixlogm.c.obj del xixlogm.c.obj
    if exist smtmsg.obj del smtmsg.obj
    if exist smtsslm.obj del smtsslm.obj
    if exist xixlogm.obj del xixlogm.obj
    if exist vc60.pdb del vc60.pdb
    goto exit

:------------------------   REMOVE GENERATED SOURCES   ------------------------

:a_remove_generated_sources
    if exist smtmsg.h del smtmsg.h
    if exist smtsslm.h del smtsslm.h
    if exist xixlogm.h del xixlogm.h
    if exist xiconfig.h del xiconfig.h
    if exist smtecho.i del smtecho.i
    if exist smtecho.d del smtecho.d
    if exist smtftpc.i del smtftpc.i
    if exist smtftpc.d del smtftpc.d
    if exist smtftpd.i del smtftpd.i
    if exist smtftpd.d del smtftpd.d
    if exist smthlog.i del smthlog.i
    if exist smthlog.d del smthlog.d
    if exist smthttp.i del smthttp.i
    if exist smthttp.d del smthttp.d
    if exist smtlog.i del smtlog.i
    if exist smtlog.d del smtlog.d
    if exist smtoper.i del smtoper.i
    if exist smtoper.d del smtoper.d
    if exist smtpipe.i del smtpipe.i
    if exist smtpipe.d del smtpipe.d
    if exist smtrdns.i del smtrdns.i
    if exist smtrdns.d del smtrdns.d
    if exist smtsimu.i del smtsimu.i
    if exist smtsimu.d del smtsimu.d
    if exist smtslot.i del smtslot.i
    if exist smtslot.d del smtslot.d
    if exist smtsock.i del smtsock.i
    if exist smtsock.d del smtsock.d
    if exist smttime.i del smttime.i
    if exist smttime.d del smttime.d
    if exist smttran.i del smttran.i
    if exist smttran.d del smttran.d
    if exist smttst1.i del smttst1.i
    if exist smttst1.d del smttst1.d
    if exist smttst2.i del smttst2.i
    if exist smttst2.d del smttst2.d
    if exist smttst3.i del smttst3.i
    if exist smttst3.d del smttst3.d
    if exist smtupmc.i del smtupmc.i
    if exist smtupmc.d del smtupmc.d
    if exist smtupmd.i del smtupmd.i
    if exist smtupmd.d del smtupmd.d
    if exist xiddns.i del xiddns.i
    if exist xiddns.d del xiddns.d
    if exist xierror.i del xierror.i
    if exist xierror.d del xierror.d
    if exist xiredir.i del xiredir.i
    if exist xiredir.d del xiredir.d
    if exist xiimap.i del xiimap.i
    if exist xiimap.d del xiimap.d
    if exist xilrwp.i del xilrwp.i
    if exist xilrwp.d del xilrwp.d
    if exist xisuper.i del xisuper.i
    if exist xisuper.d del xisuper.d
    if exist xixlog.i del xixlog.i
    if exist xixlog.d del xixlog.d
    if exist xixssi.i del xixssi.i
    if exist xixssi.d del xixssi.d
    if exist xixxml.i del xixxml.i
    if exist xixxml.d del xixxml.d
    if exist wsxrc.d del wsxrc.d
    if exist smtmsg.c del smtmsg.c
    if exist smtsslm.c del smtsslm.c
    if exist xixlogm.c del xixlogm.c
    if exist xicorpro.d del xicorpro.d
    if exist xicorpro.i del xicorpro.i
    if exist xicorstd.d del xicorstd.d
    if exist xicorstd.i del xicorstd.i
    goto exit

:-------------------------   REPORT HELP INFORMATION   ------------------------

:a_report_help_information
    echo boomake - Boom! builder for SMT 2.80
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

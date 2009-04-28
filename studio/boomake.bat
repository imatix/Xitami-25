@echo off
:-
:-  Boom builder for Studio 2.2
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
    pushd doc\
    popd
    dir>nul
    call c -q %COPTS% ctxman
    if errorlevel 1 echo boomake: "call c -q %COPTS% ctxman" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% wtplib
    if errorlevel 1 echo boomake: "call c -q %COPTS% wtplib" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% formio
    if errorlevel 1 echo boomake: "call c -q %COPTS% formio" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% wtpman
    if errorlevel 1 echo boomake: "call c -q %COPTS% wtpman" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% browtp
    if errorlevel 1 echo boomake: "call c -q %COPTS% browtp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% brocgi
    if errorlevel 1 echo boomake: "call c -q %COPTS% brocgi" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% testbro
    if errorlevel 1 echo boomake: "call c -q %COPTS% testbro" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% fxtest1
    if errorlevel 1 echo boomake: "call c -q %COPTS% fxtest1" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% fxtest2
    if errorlevel 1 echo boomake: "call c -q %COPTS% fxtest2" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% fxtest3
    if errorlevel 1 echo boomake: "call c -q %COPTS% fxtest3" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% fxdemo
    if errorlevel 1 echo boomake: "call c -q %COPTS% fxdemo" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% fxdemo2
    if errorlevel 1 echo boomake: "call c -q %COPTS% fxdemo2" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% fxdemo3
    if errorlevel 1 echo boomake: "call c -q %COPTS% fxdemo3" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% wtpmsg
    if errorlevel 1 echo boomake: "call c -q %COPTS% wtpmsg" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib ctxman
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib ctxman" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib wtplib
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib wtplib" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib formio
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib formio" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib wtpman
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib wtpman" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib browtp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib browtp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib brocgi
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib brocgi" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib fxtest1
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib fxtest1" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib fxtest2
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib fxtest2" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib fxtest3
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib fxtest3" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libstu.lib wtpmsg
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libstu.lib wtpmsg" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L testbro
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L testbro" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L fxdemo
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L fxdemo" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L fxdemo2
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L fxdemo2" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L fxdemo3
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L fxdemo3" failed
    if errorlevel 1 goto err_exception
    goto exit

:--------------------------   BUILD SOURCE PACKAGES   -------------------------

:a_build_source_packages
    if exist _package.lst del _package.lst
    if exist studio\doc\fdldoc.txt echo studio\doc\fdldoc.txt>>_package.lst
    if exist studio\doc\fmldoc.txt echo studio\doc\fmldoc.txt>>_package.lst
    if exist studio\doc\rfc001.txt echo studio\doc\rfc001.txt>>_package.lst
    if exist studio\doc\rfc002.txt echo studio\doc\rfc002.txt>>_package.lst
    if exist studio\version.h echo studio\version.h>>_package.lst
    if exist studio\ctxman.c echo studio\ctxman.c>>_package.lst
    if exist studio\ctxman.h echo studio\ctxman.h>>_package.lst
    if exist studio\wtplib.c echo studio\wtplib.c>>_package.lst
    if exist studio\wtplib.h echo studio\wtplib.h>>_package.lst
    if exist studio\formio.c echo studio\formio.c>>_package.lst
    if exist studio\formio.h echo studio\formio.h>>_package.lst
    if exist studio\wtpman.c echo studio\wtpman.c>>_package.lst
    if exist studio\browtp.c echo studio\browtp.c>>_package.lst
    if exist studio\browtp.h echo studio\browtp.h>>_package.lst
    if exist studio\brocgi.c echo studio\brocgi.c>>_package.lst
    if exist studio\wtpmsg.xml echo studio\wtpmsg.xml>>_package.lst
    if exist studio\wtpmsg.h echo studio\wtpmsg.h>>_package.lst
    if exist studio\stupriv.h echo studio\stupriv.h>>_package.lst
    if exist studio\defaults.cfg echo studio\defaults.cfg>>_package.lst
    if exist studio\fdlgen echo studio\fdlgen>>_package.lst
    if exist studio\fdlgen.fmt echo studio\fdlgen.fmt>>_package.lst
    if exist studio\fmlgen echo studio\fmlgen>>_package.lst
    if exist studio\fmlgen.fmt echo studio\fmlgen.fmt>>_package.lst
    if exist studio\findfile.pl echo studio\findfile.pl>>_package.lst
    if exist studio\shellwd.pl echo studio\shellwd.pl>>_package.lst
    if exist studio\sflcvdp.pl echo studio\sflcvdp.pl>>_package.lst
    if exist studio\sfldate.pl echo studio\sfldate.pl>>_package.lst
    if exist studio\testbro.c echo studio\testbro.c>>_package.lst
    if exist studio\fxdemo.adf echo studio\fxdemo.adf>>_package.lst
    if exist studio\fxdemo.ini echo studio\fxdemo.ini>>_package.lst
    if exist studio\fxtest1.c echo studio\fxtest1.c>>_package.lst
    if exist studio\fxtest2.c echo studio\fxtest2.c>>_package.lst
    if exist studio\fxtest3.c echo studio\fxtest3.c>>_package.lst
    if exist studio\fxdemo.c echo studio\fxdemo.c>>_package.lst
    if exist studio\fxdemo2.c echo studio\fxdemo2.c>>_package.lst
    if exist studio\fxdemo3.c echo studio\fxdemo3.c>>_package.lst
    if exist studio\index.htm echo studio\index.htm>>_package.lst
    if exist studio\wtpcfg.ini echo studio\wtpcfg.ini>>_package.lst
    if exist studio\adfgen.gsl echo studio\adfgen.gsl>>_package.lst
    if exist studio\lrstudio.c echo studio\lrstudio.c>>_package.lst
    if exist studio\anchor.def echo studio\anchor.def>>_package.lst
    if exist studio\prelude.def echo studio\prelude.def>>_package.lst
    if exist studio\prelude.pdl echo studio\prelude.pdl>>_package.lst
    if exist studio\license.gpl echo studio\license.gpl>>_package.lst
    if exist studio\project.pdl echo studio\project.pdl>>_package.lst
    if exist studio\readme.txt echo studio\readme.txt>>_package.lst
    if exist studio\wtpman.l echo studio\wtpman.l>>_package.lst
    if exist studio\wtpman.i echo studio\wtpman.i>>_package.lst
    if exist studio\wtpman.d echo studio\wtpman.d>>_package.lst
    if exist studio\browtp.l echo studio\browtp.l>>_package.lst
    if exist studio\browtp.i echo studio\browtp.i>>_package.lst
    if exist studio\browtp.d echo studio\browtp.d>>_package.lst
    if exist studio\brocgi.l echo studio\brocgi.l>>_package.lst
    if exist studio\brocgi.i echo studio\brocgi.i>>_package.lst
    if exist studio\brocgi.d echo studio\brocgi.d>>_package.lst
    if exist studio\brocgi.h echo studio\brocgi.h>>_package.lst
    if exist studio\wtpmsg.c echo studio\wtpmsg.c>>_package.lst
    if exist studio\fdlgen.l echo studio\fdlgen.l>>_package.lst
    if exist studio\fdlgen.d echo studio\fdlgen.d>>_package.lst
    if exist studio\fdlgen.bat echo studio\fdlgen.bat>>_package.lst
    if exist studio\fmlgen.l echo studio\fmlgen.l>>_package.lst
    if exist studio\fmlgen.d echo studio\fmlgen.d>>_package.lst
    if exist studio\fmlgen.bat echo studio\fmlgen.bat>>_package.lst
    if exist studio\fxtest1.fdl echo studio\fxtest1.fdl>>_package.lst
    if exist studio\fxtest1.htm echo studio\fxtest1.htm>>_package.lst
    if exist studio\fxtest1.log echo studio\fxtest1.log>>_package.lst
    if exist studio\fxtest1.h echo studio\fxtest1.h>>_package.lst
    if exist studio\fxtest1.l echo studio\fxtest1.l>>_package.lst
    if exist studio\fxtest1.i echo studio\fxtest1.i>>_package.lst
    if exist studio\fxtest1.d echo studio\fxtest1.d>>_package.lst
    if exist studio\fxtest2.fdl echo studio\fxtest2.fdl>>_package.lst
    if exist studio\fxtest2.htm echo studio\fxtest2.htm>>_package.lst
    if exist studio\fxtest2.log echo studio\fxtest2.log>>_package.lst
    if exist studio\fxtest2.h echo studio\fxtest2.h>>_package.lst
    if exist studio\fxtest2.l echo studio\fxtest2.l>>_package.lst
    if exist studio\fxtest2.i echo studio\fxtest2.i>>_package.lst
    if exist studio\fxtest2.d echo studio\fxtest2.d>>_package.lst
    if exist studio\fxtest3.fdl echo studio\fxtest3.fdl>>_package.lst
    if exist studio\fxtest3.htm echo studio\fxtest3.htm>>_package.lst
    if exist studio\fxtest3.log echo studio\fxtest3.log>>_package.lst
    if exist studio\fxtest3.h echo studio\fxtest3.h>>_package.lst
    if exist studio\fxtest3.l echo studio\fxtest3.l>>_package.lst
    if exist studio\fxtest3.i echo studio\fxtest3.i>>_package.lst
    if exist studio\fxtest3.d echo studio\fxtest3.d>>_package.lst
    if exist studio\studio.h echo studio\studio.h>>_package.lst
    if exist studio\boomake echo studio\boomake>>_package.lst
    if exist studio\boomake.bat echo studio\boomake.bat>>_package.lst
    if exist studio\makefile echo studio\makefile>>_package.lst
    if exist studio\msmake echo studio\msmake>>_package.lst
    echo Building stu_2_2_src.zip...
    dir>nul
    zip -q stu_2_2_src -@<_package.lst
    if errorlevel 1 echo boomake: "zip -q stu_2_2_src -@<_package.lst" failed
    if errorlevel 1 goto err_exception
    del _package.lst
    goto exit

:------------------------   CHECK BINARY FILES EXIST   ------------------------

:a_check_binary_files_exist
    if exist doc\nul cd doc
    if exist ..\doc\nul cd ..
    if not exist ctxman.h (
        echo ctxman.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtplib.h (
        echo wtplib.h is missing, cannot continue
        goto err_exception
    )
    if not exist formio.h (
        echo formio.h is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.h (
        echo browtp.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtpmsg.h (
        echo wtpmsg.h is missing, cannot continue
        goto err_exception
    )
    if not exist defaults.cfg (
        echo defaults.cfg is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen (
        echo fdlgen is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.fmt (
        echo fdlgen.fmt is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen (
        echo fmlgen is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.fmt (
        echo fmlgen.fmt is missing, cannot continue
        goto err_exception
    )
    if not exist findfile.pl (
        echo findfile.pl is missing, cannot continue
        goto err_exception
    )
    if not exist shellwd.pl (
        echo shellwd.pl is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvdp.pl (
        echo sflcvdp.pl is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.pl (
        echo sfldate.pl is missing, cannot continue
        goto err_exception
    )
    if not exist adfgen.gsl (
        echo adfgen.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist lrstudio.c (
        echo lrstudio.c is missing, cannot continue
        goto err_exception
    )
    if not exist libstu.lib (
        echo libstu.lib is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.d (
        echo fdlgen.d is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.bat (
        echo fdlgen.bat is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.d (
        echo fmlgen.d is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.bat (
        echo fmlgen.bat is missing, cannot continue
        goto err_exception
    )
    if not exist studio.h (
        echo studio.h is missing, cannot continue
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
    if not exist doc\nul (
        echo directory doc is missing, cannot continue
        goto err_exception
    )
    if exist doc\nul cd doc
    if not exist fdldoc.txt (
        echo fdldoc.txt is missing, cannot continue
        goto err_exception
    )
    if not exist fmldoc.txt (
        echo fmldoc.txt is missing, cannot continue
        goto err_exception
    )
    if not exist rfc001.txt (
        echo rfc001.txt is missing, cannot continue
        goto err_exception
    )
    if not exist rfc002.txt (
        echo rfc002.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\doc\nul cd ..
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist ctxman.c (
        echo ctxman.c is missing, cannot continue
        goto err_exception
    )
    if not exist ctxman.h (
        echo ctxman.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtplib.c (
        echo wtplib.c is missing, cannot continue
        goto err_exception
    )
    if not exist wtplib.h (
        echo wtplib.h is missing, cannot continue
        goto err_exception
    )
    if not exist formio.c (
        echo formio.c is missing, cannot continue
        goto err_exception
    )
    if not exist formio.h (
        echo formio.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtpman.c (
        echo wtpman.c is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.c (
        echo browtp.c is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.h (
        echo browtp.h is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.c (
        echo brocgi.c is missing, cannot continue
        goto err_exception
    )
    if not exist wtpmsg.xml (
        echo wtpmsg.xml is missing, cannot continue
        goto err_exception
    )
    if not exist stupriv.h (
        echo stupriv.h is missing, cannot continue
        goto err_exception
    )
    if not exist defaults.cfg (
        echo defaults.cfg is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen (
        echo fdlgen is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.fmt (
        echo fdlgen.fmt is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen (
        echo fmlgen is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.fmt (
        echo fmlgen.fmt is missing, cannot continue
        goto err_exception
    )
    if not exist findfile.pl (
        echo findfile.pl is missing, cannot continue
        goto err_exception
    )
    if not exist shellwd.pl (
        echo shellwd.pl is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvdp.pl (
        echo sflcvdp.pl is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.pl (
        echo sfldate.pl is missing, cannot continue
        goto err_exception
    )
    if not exist testbro.c (
        echo testbro.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo.adf (
        echo fxdemo.adf is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo.ini (
        echo fxdemo.ini is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.c (
        echo fxtest1.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.c (
        echo fxtest2.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.c (
        echo fxtest3.c is missing, cannot continue
        goto err_exception
    )
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist wtpcfg.ini (
        echo wtpcfg.ini is missing, cannot continue
        goto err_exception
    )
    if not exist adfgen.gsl (
        echo adfgen.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist lrstudio.c (
        echo lrstudio.c is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.def (
        echo prelude.def is missing, cannot continue
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
    if not exist wtpman.l (
        echo wtpman.l is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.l (
        echo browtp.l is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.l (
        echo brocgi.l is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.h (
        echo brocgi.h is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.l (
        echo fdlgen.l is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.bat (
        echo fdlgen.bat is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.l (
        echo fmlgen.l is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.bat (
        echo fmlgen.bat is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.fdl (
        echo fxtest1.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.l (
        echo fxtest1.l is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.fdl (
        echo fxtest2.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.l (
        echo fxtest2.l is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.fdl (
        echo fxtest3.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.l (
        echo fxtest3.l is missing, cannot continue
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
    if exist doc\nul cd doc
    if not exist fdldoc.txt (
        echo fdldoc.txt is missing, cannot continue
        goto err_exception
    )
    if not exist fmldoc.txt (
        echo fmldoc.txt is missing, cannot continue
        goto err_exception
    )
    if not exist rfc001.txt (
        echo rfc001.txt is missing, cannot continue
        goto err_exception
    )
    if not exist rfc002.txt (
        echo rfc002.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\doc\nul cd ..
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist ctxman.c (
        echo ctxman.c is missing, cannot continue
        goto err_exception
    )
    if not exist ctxman.h (
        echo ctxman.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtplib.c (
        echo wtplib.c is missing, cannot continue
        goto err_exception
    )
    if not exist wtplib.h (
        echo wtplib.h is missing, cannot continue
        goto err_exception
    )
    if not exist formio.c (
        echo formio.c is missing, cannot continue
        goto err_exception
    )
    if not exist formio.h (
        echo formio.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtpman.c (
        echo wtpman.c is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.c (
        echo browtp.c is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.h (
        echo browtp.h is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.c (
        echo brocgi.c is missing, cannot continue
        goto err_exception
    )
    if not exist wtpmsg.xml (
        echo wtpmsg.xml is missing, cannot continue
        goto err_exception
    )
    if not exist wtpmsg.h (
        echo wtpmsg.h is missing, cannot continue
        goto err_exception
    )
    if not exist stupriv.h (
        echo stupriv.h is missing, cannot continue
        goto err_exception
    )
    if not exist defaults.cfg (
        echo defaults.cfg is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen (
        echo fdlgen is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.fmt (
        echo fdlgen.fmt is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen (
        echo fmlgen is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.fmt (
        echo fmlgen.fmt is missing, cannot continue
        goto err_exception
    )
    if not exist findfile.pl (
        echo findfile.pl is missing, cannot continue
        goto err_exception
    )
    if not exist shellwd.pl (
        echo shellwd.pl is missing, cannot continue
        goto err_exception
    )
    if not exist sflcvdp.pl (
        echo sflcvdp.pl is missing, cannot continue
        goto err_exception
    )
    if not exist sfldate.pl (
        echo sfldate.pl is missing, cannot continue
        goto err_exception
    )
    if not exist testbro.c (
        echo testbro.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo.adf (
        echo fxdemo.adf is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo.ini (
        echo fxdemo.ini is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.c (
        echo fxtest1.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.c (
        echo fxtest2.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.c (
        echo fxtest3.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo.c (
        echo fxdemo.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo2.c (
        echo fxdemo2.c is missing, cannot continue
        goto err_exception
    )
    if not exist fxdemo3.c (
        echo fxdemo3.c is missing, cannot continue
        goto err_exception
    )
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist wtpcfg.ini (
        echo wtpcfg.ini is missing, cannot continue
        goto err_exception
    )
    if not exist adfgen.gsl (
        echo adfgen.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist lrstudio.c (
        echo lrstudio.c is missing, cannot continue
        goto err_exception
    )
    if not exist anchor.def (
        echo anchor.def is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.def (
        echo prelude.def is missing, cannot continue
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
    if not exist wtpman.l (
        echo wtpman.l is missing, cannot continue
        goto err_exception
    )
    if not exist wtpman.i (
        echo wtpman.i is missing, cannot continue
        goto err_exception
    )
    if not exist wtpman.d (
        echo wtpman.d is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.l (
        echo browtp.l is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.i (
        echo browtp.i is missing, cannot continue
        goto err_exception
    )
    if not exist browtp.d (
        echo browtp.d is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.l (
        echo brocgi.l is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.i (
        echo brocgi.i is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.d (
        echo brocgi.d is missing, cannot continue
        goto err_exception
    )
    if not exist brocgi.h (
        echo brocgi.h is missing, cannot continue
        goto err_exception
    )
    if not exist wtpmsg.c (
        echo wtpmsg.c is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.l (
        echo fdlgen.l is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.d (
        echo fdlgen.d is missing, cannot continue
        goto err_exception
    )
    if not exist fdlgen.bat (
        echo fdlgen.bat is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.l (
        echo fmlgen.l is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.d (
        echo fmlgen.d is missing, cannot continue
        goto err_exception
    )
    if not exist fmlgen.bat (
        echo fmlgen.bat is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.fdl (
        echo fxtest1.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.htm (
        echo fxtest1.htm is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.log (
        echo fxtest1.log is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.h (
        echo fxtest1.h is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.l (
        echo fxtest1.l is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.i (
        echo fxtest1.i is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest1.d (
        echo fxtest1.d is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.fdl (
        echo fxtest2.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.htm (
        echo fxtest2.htm is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.log (
        echo fxtest2.log is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.h (
        echo fxtest2.h is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.l (
        echo fxtest2.l is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.i (
        echo fxtest2.i is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest2.d (
        echo fxtest2.d is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.fdl (
        echo fxtest3.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.htm (
        echo fxtest3.htm is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.log (
        echo fxtest3.log is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.h (
        echo fxtest3.h is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.l (
        echo fxtest3.l is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.i (
        echo fxtest3.i is missing, cannot continue
        goto err_exception
    )
    if not exist fxtest3.d (
        echo fxtest3.d is missing, cannot continue
        goto err_exception
    )
    if not exist studio.h (
        echo studio.h is missing, cannot continue
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
    echo Installing Studio into %TARGET%...
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y ctxman.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y ctxman.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y wtplib.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y wtplib.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y formio.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y formio.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y browtp.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y browtp.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y wtpmsg.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y wtpmsg.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    dir>nul
    copy/y defaults.cfg %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y defaults.cfg %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fdlgen %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fdlgen %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fdlgen.fmt %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fdlgen.fmt %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fmlgen %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fmlgen %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fmlgen.fmt %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fmlgen.fmt %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y findfile.pl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y findfile.pl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y shellwd.pl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y shellwd.pl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y sflcvdp.pl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y sflcvdp.pl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y sfldate.pl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y sfldate.pl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y adfgen.gsl %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y adfgen.gsl %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y lrstudio.c %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y lrstudio.c %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\lib\nul mkdir %TARGET%\lib\
    dir>nul
    copy/y libstu.lib %TARGET%\lib\>nul
    if errorlevel 1 echo boomake: "copy/y libstu.lib %TARGET%\lib\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    if not exist %TARGET%\doc\Studio\nul mkdir %TARGET%\doc\Studio\
    dir>nul
    copy/y readme.txt %TARGET%\doc\Studio\>nul
    if errorlevel 1 echo boomake: "copy/y readme.txt %TARGET%\doc\Studio\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    dir>nul
    copy/y fdlgen.d %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fdlgen.d %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fdlgen.bat %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fdlgen.bat %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fmlgen.d %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fmlgen.d %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y fmlgen.bat %TARGET%\bin\>nul
    if errorlevel 1 echo boomake: "copy/y fmlgen.bat %TARGET%\bin\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y studio.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y studio.h %TARGET%\include\>nul" failed
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
    call gsl -q fxdemo.adf
    if errorlevel 1 echo boomake: "call gsl -q fxdemo.adf" failed
    if errorlevel 1 goto err_exception
    if exist doc\nul cd doc
    if exist ..\doc\nul cd ..
    dir>nul
    call gsl -q wtpmsg.xml
    if errorlevel 1 echo boomake: "call gsl -q wtpmsg.xml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr wtpman.l
    if errorlevel 1 echo boomake: "call lr wtpman.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr browtp.l
    if errorlevel 1 echo boomake: "call lr browtp.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr brocgi.l
    if errorlevel 1 echo boomake: "call lr brocgi.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr fdlgen.l
    if errorlevel 1 echo boomake: "call lr fdlgen.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr fmlgen.l
    if errorlevel 1 echo boomake: "call lr fmlgen.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call perl fdlgen fxtest1.fdl
    if errorlevel 1 echo boomake: "call perl fdlgen fxtest1.fdl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call perl fmlgen fxtest1.fdl
    if errorlevel 1 echo boomake: "call perl fmlgen fxtest1.fdl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr fxtest1.l
    if errorlevel 1 echo boomake: "call lr fxtest1.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call perl fdlgen fxtest2.fdl
    if errorlevel 1 echo boomake: "call perl fdlgen fxtest2.fdl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call perl fmlgen fxtest2.fdl
    if errorlevel 1 echo boomake: "call perl fmlgen fxtest2.fdl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr fxtest2.l
    if errorlevel 1 echo boomake: "call lr fxtest2.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call perl fdlgen fxtest3.fdl
    if errorlevel 1 echo boomake: "call perl fdlgen fxtest3.fdl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call perl fmlgen fxtest3.fdl
    if errorlevel 1 echo boomake: "call perl fmlgen fxtest3.fdl" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr fxtest3.l
    if errorlevel 1 echo boomake: "call lr fxtest3.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call gsl -q fxdemo.adf
    if errorlevel 1 echo boomake: "call gsl -q fxdemo.adf" failed
    if errorlevel 1 goto err_exception
    if exist studio.h del studio.h
    type wtplib.h>>studio.h
    type wtpmsg.h>>studio.h
    type ctxman.h>>studio.h
    type formio.h>>studio.h
    type browtp.h>>studio.h
    type brocgi.h>>studio.h
    goto exit

:------------------------   REMOVE GENERATED BINARIES   -----------------------

:a_remove_generated_binaries
    if exist doc\libstu.lib del doc\libstu.lib
    if exist libstu.lib del libstu.lib
    if exist ctxman.obj del ctxman.obj
    if exist wtplib.obj del wtplib.obj
    if exist formio.obj del formio.obj
    if exist wtpman.obj del wtpman.obj
    if exist browtp.obj del browtp.obj
    if exist brocgi.obj del brocgi.obj
    if exist wtpmsg.c.obj del wtpmsg.c.obj
    if exist testbro.obj del testbro.obj
    if exist testbro.exe del testbro.exe
    if exist fxtest1.obj del fxtest1.obj
    if exist fxtest2.obj del fxtest2.obj
    if exist fxtest3.obj del fxtest3.obj
    if exist fxdemo.obj del fxdemo.obj
    if exist fxdemo.exe del fxdemo.exe
    if exist fxdemo2.obj del fxdemo2.obj
    if exist fxdemo2.exe del fxdemo2.exe
    if exist fxdemo3.obj del fxdemo3.obj
    if exist fxdemo3.exe del fxdemo3.exe
    if exist wtpmsg.obj del wtpmsg.obj
    if exist doc\nul cd doc
    if exist ..\doc\nul cd ..
    if exist vc60.pdb del vc60.pdb
    goto exit

:------------------------   REMOVE GENERATED SOURCES   ------------------------

:a_remove_generated_sources
    if exist wtpmsg.h del wtpmsg.h
    if exist fxdemo.c del fxdemo.c
    if exist fxdemo2.c del fxdemo2.c
    if exist fxdemo3.c del fxdemo3.c
    if exist anchor.def del anchor.def
    if exist wtpman.i del wtpman.i
    if exist wtpman.d del wtpman.d
    if exist browtp.i del browtp.i
    if exist browtp.d del browtp.d
    if exist brocgi.i del brocgi.i
    if exist brocgi.d del brocgi.d
    if exist wtpmsg.c del wtpmsg.c
    if exist fdlgen.d del fdlgen.d
    if exist fmlgen.d del fmlgen.d
    if exist fxtest1.htm del fxtest1.htm
    if exist fxtest1.log del fxtest1.log
    if exist fxtest1.h del fxtest1.h
    if exist fxtest1.i del fxtest1.i
    if exist fxtest1.d del fxtest1.d
    if exist fxtest2.htm del fxtest2.htm
    if exist fxtest2.log del fxtest2.log
    if exist fxtest2.h del fxtest2.h
    if exist fxtest2.i del fxtest2.i
    if exist fxtest2.d del fxtest2.d
    if exist fxtest3.htm del fxtest3.htm
    if exist fxtest3.log del fxtest3.log
    if exist fxtest3.h del fxtest3.h
    if exist fxtest3.i del fxtest3.i
    if exist fxtest3.d del fxtest3.d
    if exist studio.h del studio.h
    goto exit

:-------------------------   REPORT HELP INFORMATION   ------------------------

:a_report_help_information
    echo boomake - Boom! builder for Studio 2.2
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

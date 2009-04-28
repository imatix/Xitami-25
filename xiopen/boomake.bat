@echo off
:-
:-  Boom builder for Xitami/Open 2.5c2
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
    pushd cgi-bin\
    popd
    pushd cgi-src\
    popd
    pushd debug\
    popd
    pushd errors\
    popd
    pushd ftproot\guest\
    popd
    pushd ftproot\pub\
    popd
    pushd ftproot\upload\
    popd
    pushd ftproot\
    popd
    pushd headers\
    popd
    pushd logs\
    popd
    pushd temp\
    popd
    pushd templates\
    popd
    pushd html\
    popd
    pushd win32\
    dir>nul
    call msdev xitami.dsw /make "all - release"
    if errorlevel 1 echo boomake: "call msdev xitami.dsw /make "all - release"" failed
    if errorlevel 1 goto err_exception
    popd
    pushd webpages\xitami\
    popd
    pushd webpages\images\
    popd
    pushd webpages\private\
    popd
    pushd webpages\
    popd
    dir>nul
    call c -q %COPTS% xixlat
    if errorlevel 1 echo boomake: "call c -q %COPTS% xixlat" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xitami
    if errorlevel 1 echo boomake: "call c -q %COPTS% xitami" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xilite
    if errorlevel 1 echo boomake: "call c -q %COPTS% xilite" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% xiwtp
    if errorlevel 1 echo boomake: "call c -q %COPTS% xiwtp" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L xixlat
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L xixlat" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L xitami
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L xitami" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L xilite
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L xilite" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L xiwtp
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L xiwtp" failed
    if errorlevel 1 goto err_exception
    goto exit

:--------------------------   BUILD SOURCE PACKAGES   -------------------------

:a_build_source_packages
    if exist _package.lst del _package.lst
    if exist xiopen\cgi-bin\readme.txt echo xiopen\cgi-bin\readme.txt>>_package.lst
    if exist xiopen\cgi-src\testcgi.c echo xiopen\cgi-src\testcgi.c>>_package.lst
    if exist xiopen\cgi-src\testcgi1.c echo xiopen\cgi-src\testcgi1.c>>_package.lst
    if exist xiopen\cgi-src\testcgi2.c echo xiopen\cgi-src\testcgi2.c>>_package.lst
    if exist xiopen\cgi-src\testcgi3.c echo xiopen\cgi-src\testcgi3.c>>_package.lst
    if exist xiopen\cgi-src\testcgi4.c echo xiopen\cgi-src\testcgi4.c>>_package.lst
    if exist xiopen\cgi-src\testcgi5.c echo xiopen\cgi-src\testcgi5.c>>_package.lst
    if exist xiopen\cgi-src\testcgi6.c echo xiopen\cgi-src\testcgi6.c>>_package.lst
    if exist xiopen\cgi-src\testcgi7.c echo xiopen\cgi-src\testcgi7.c>>_package.lst
    if exist xiopen\cgi-src\testperl.pl echo xiopen\cgi-src\testperl.pl>>_package.lst
    if exist xiopen\debug\readme.txt echo xiopen\debug\readme.txt>>_package.lst
    if exist xiopen\errors\footer.htm echo xiopen\errors\footer.htm>>_package.lst
    if exist xiopen\errors\header.htm echo xiopen\errors\header.htm>>_package.lst
    if exist xiopen\errors\text-400.htm echo xiopen\errors\text-400.htm>>_package.lst
    if exist xiopen\errors\text-401.htm echo xiopen\errors\text-401.htm>>_package.lst
    if exist xiopen\errors\text-402.htm echo xiopen\errors\text-402.htm>>_package.lst
    if exist xiopen\errors\text-403.htm echo xiopen\errors\text-403.htm>>_package.lst
    if exist xiopen\errors\text-404.htm echo xiopen\errors\text-404.htm>>_package.lst
    if exist xiopen\errors\text-412.htm echo xiopen\errors\text-412.htm>>_package.lst
    if exist xiopen\errors\text-413.htm echo xiopen\errors\text-413.htm>>_package.lst
    if exist xiopen\errors\text-500.htm echo xiopen\errors\text-500.htm>>_package.lst
    if exist xiopen\errors\text-501.htm echo xiopen\errors\text-501.htm>>_package.lst
    if exist xiopen\errors\text-502.htm echo xiopen\errors\text-502.htm>>_package.lst
    if exist xiopen\ftproot\guest\index.htm echo xiopen\ftproot\guest\index.htm>>_package.lst
    if exist xiopen\ftproot\guest\index.txt echo xiopen\ftproot\guest\index.txt>>_package.lst
    if exist xiopen\ftproot\pub\index.htm echo xiopen\ftproot\pub\index.htm>>_package.lst
    if exist xiopen\ftproot\pub\index.txt echo xiopen\ftproot\pub\index.txt>>_package.lst
    if exist xiopen\ftproot\upload\index.htm echo xiopen\ftproot\upload\index.htm>>_package.lst
    if exist xiopen\ftproot\upload\index.txt echo xiopen\ftproot\upload\index.txt>>_package.lst
    if exist xiopen\ftproot\readme.txt echo xiopen\ftproot\readme.txt>>_package.lst
    if exist xiopen\headers\readme.txt echo xiopen\headers\readme.txt>>_package.lst
    if exist xiopen\logs\readme.txt echo xiopen\logs\readme.txt>>_package.lst
    if exist xiopen\temp\readme.txt echo xiopen\temp\readme.txt>>_package.lst
    if exist xiopen\templates\errors.gsl echo xiopen\templates\errors.gsl>>_package.lst
    if exist xiopen\templates\ftpmesg.gsl echo xiopen\templates\ftpmesg.gsl>>_package.lst
    if exist xiopen\templates\httpdir.gsl echo xiopen\templates\httpdir.gsl>>_package.lst
    if exist xiopen\html\anchor.def echo xiopen\html\anchor.def>>_package.lst
    if exist xiopen\html\macros.def echo xiopen\html\macros.def>>_package.lst
    if exist xiopen\html\prelude.def echo xiopen\html\prelude.def>>_package.lst
    if exist xiopen\html\xitami1.txt echo xiopen\html\xitami1.txt>>_package.lst
    if exist xiopen\html\xitami2.txt echo xiopen\html\xitami2.txt>>_package.lst
    if exist xiopen\html\testssi.ssi echo xiopen\html\testssi.ssi>>_package.lst
    if exist xiopen\html\private.htm echo xiopen\html\private.htm>>_package.lst
    if exist xiopen\html\default.htm echo xiopen\html\default.htm>>_package.lst
    if exist xiopen\html\index*.htm echo xiopen\html\index*.htm>>_package.lst
    if exist xiopen\html\license.htm echo xiopen\html\license.htm>>_package.lst
    if exist xiopen\html\belgium.htm echo xiopen\html\belgium.htm>>_package.lst
    if exist xiopen\html\mapfail.htm echo xiopen\html\mapfail.htm>>_package.lst
    if exist xiopen\html\os2-readme.htm echo xiopen\html\os2-readme.htm>>_package.lst
    if exist xiopen\html\unix-readme.htm echo xiopen\html\unix-readme.htm>>_package.lst
    if exist xiopen\html\windows.htm echo xiopen\html\windows.htm>>_package.lst
    if exist xiopen\win32\about.ico echo xiopen\win32\about.ico>>_package.lst
    if exist xiopen\win32\active.bmp echo xiopen\win32\active.bmp>>_package.lst
    if exist xiopen\win32\bitmap4.bmp echo xiopen\win32\bitmap4.bmp>>_package.lst
    if exist xiopen\win32\bitmap5.bmp echo xiopen\win32\bitmap5.bmp>>_package.lst
    if exist xiopen\win32\bug100.bmp echo xiopen\win32\bug100.bmp>>_package.lst
    if exist xiopen\win32\gsl.dsp echo xiopen\win32\gsl.dsp>>_package.lst
    if exist xiopen\win32\imatix1.bmp echo xiopen\win32\imatix1.bmp>>_package.lst
    if exist xiopen\win32\off.bmp echo xiopen\win32\off.bmp>>_package.lst
    if exist xiopen\win32\off.ico echo xiopen\win32\off.ico>>_package.lst
    if exist xiopen\win32\on.bmp echo xiopen\win32\on.bmp>>_package.lst
    if exist xiopen\win32\on.ico echo xiopen\win32\on.ico>>_package.lst
    if exist xiopen\win32\resource.h echo xiopen\win32\resource.h>>_package.lst
    if exist xiopen\win32\sfl.dsp echo xiopen\win32\sfl.dsp>>_package.lst
    if exist xiopen\win32\smt.dsp echo xiopen\win32\smt.dsp>>_package.lst
    if exist xiopen\win32\studio.dsp echo xiopen\win32\studio.dsp>>_package.lst
    if exist xiopen\win32\xiadmin.dsp echo xiopen\win32\xiadmin.dsp>>_package.lst
    if exist xiopen\win32\xicpl32.c echo xiopen\win32\xicpl32.c>>_package.lst
    if exist xiopen\win32\xicpl32.def echo xiopen\win32\xicpl32.def>>_package.lst
    if exist xiopen\win32\xigui32.c echo xiopen\win32\xigui32.c>>_package.lst
    if exist xiopen\win32\xiprocpl.def echo xiopen\win32\xiprocpl.def>>_package.lst
    if exist xiopen\win32\xisrv32.c echo xiopen\win32\xisrv32.c>>_package.lst
    if exist xiopen\win32\Xitami_Console.dsp echo xiopen\win32\Xitami_Console.dsp>>_package.lst
    if exist xiopen\win32\Xitami_Control_Panel.dsp echo xiopen\win32\Xitami_Control_Panel.dsp>>_package.lst
    if exist xiopen\win32\Xitami_Service.dsp echo xiopen\win32\Xitami_Service.dsp>>_package.lst
    if exist xiopen\win32\Xitami_Win32.dsp echo xiopen\win32\Xitami_Win32.dsp>>_package.lst
    if exist xiopen\win32\xitami.dsw echo xiopen\win32\xitami.dsw>>_package.lst
    if exist xiopen\win32\xitami.h echo xiopen\win32\xitami.h>>_package.lst
    if exist xiopen\win32\xitami1.bmp echo xiopen\win32\xitami1.bmp>>_package.lst
    if exist xiopen\win32\xiwin.rc echo xiopen\win32\xiwin.rc>>_package.lst
    if exist xiopen\webpages\xitami\index*.htm echo xiopen\webpages\xitami\index*.htm>>_package.lst
    if exist xiopen\webpages\xitami\license.htm echo xiopen\webpages\xitami\license.htm>>_package.lst
    if exist xiopen\webpages\images\buttons.gif echo xiopen\webpages\images\buttons.gif>>_package.lst
    if exist xiopen\webpages\images\imatix.gif echo xiopen\webpages\images\imatix.gif>>_package.lst
    if exist xiopen\webpages\images\xitami1.gif echo xiopen\webpages\images\xitami1.gif>>_package.lst
    if exist xiopen\webpages\images\powered*.gif echo xiopen\webpages\images\powered*.gif>>_package.lst
    if exist xiopen\webpages\private\private.htm echo xiopen\webpages\private\private.htm>>_package.lst
    if exist xiopen\webpages\buttons.map echo xiopen\webpages\buttons.map>>_package.lst
    if exist xiopen\webpages\testssi.inc echo xiopen\webpages\testssi.inc>>_package.lst
    if exist xiopen\webpages\testssi.ssi echo xiopen\webpages\testssi.ssi>>_package.lst
    if exist xiopen\webpages\default.htm echo xiopen\webpages\default.htm>>_package.lst
    if exist xiopen\webpages\mapfail.htm echo xiopen\webpages\mapfail.htm>>_package.lst
    if exist xiopen\webpages\windows.htm echo xiopen\webpages\windows.htm>>_package.lst
    if exist xiopen\version.h echo xiopen\version.h>>_package.lst
    if exist xiopen\xiopen.xml echo xiopen\xiopen.xml>>_package.lst
    if exist xiopen\ddnsdef.xml echo xiopen\ddnsdef.xml>>_package.lst
    if exist xiopen\pipedef.xml echo xiopen\pipedef.xml>>_package.lst
    if exist xiopen\ftpadios.txt echo xiopen\ftpadios.txt>>_package.lst
    if exist xiopen\ftphello.txt echo xiopen\ftphello.txt>>_package.lst
    if exist xiopen\ftplogin.txt echo xiopen\ftplogin.txt>>_package.lst
    if exist xiopen\ftpdirs.aut echo xiopen\ftpdirs.aut>>_package.lst
    if exist xiopen\ftpusers.aut echo xiopen\ftpusers.aut>>_package.lst
    if exist xiopen\xitami.aut echo xiopen\xitami.aut>>_package.lst
    if exist xiopen\xitami.cfg echo xiopen\xitami.cfg>>_package.lst
    if exist xiopen\xixlat.c echo xiopen\xixlat.c>>_package.lst
    if exist xiopen\xiconfig.htp echo xiopen\xiconfig.htp>>_package.lst
    if exist xiopen\perlssi echo xiopen\perlssi>>_package.lst
    if exist xiopen\prelude.pdl echo xiopen\prelude.pdl>>_package.lst
    if exist xiopen\license.gpl echo xiopen\license.gpl>>_package.lst
    if exist xiopen\project.pdl echo xiopen\project.pdl>>_package.lst
    if exist xiopen\readme.txt echo xiopen\readme.txt>>_package.lst
    if exist xiopen\xitami.c echo xiopen\xitami.c>>_package.lst
    if exist xiopen\xilite.c echo xiopen\xilite.c>>_package.lst
    if exist xiopen\xiwtp.c echo xiopen\xiwtp.c>>_package.lst
    if exist xiopen\boomake echo xiopen\boomake>>_package.lst
    if exist xiopen\boomake.bat echo xiopen\boomake.bat>>_package.lst
    echo Building xit_2_5c2_src.zip...
    dir>nul
    zip -q xit_2_5c2_src -@<_package.lst
    if errorlevel 1 echo boomake: "zip -q xit_2_5c2_src -@<_package.lst" failed
    if errorlevel 1 goto err_exception
    del _package.lst
    goto exit

:------------------------   CHECK BINARY FILES EXIST   ------------------------

:a_check_binary_files_exist
    if exist cgi-bin\nul cd cgi-bin
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\cgi-bin\nul cd ..
    if exist cgi-src\nul cd cgi-src
    if not exist testcgi.c (
        echo testcgi.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi1.c (
        echo testcgi1.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi2.c (
        echo testcgi2.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi3.c (
        echo testcgi3.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi4.c (
        echo testcgi4.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi5.c (
        echo testcgi5.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi6.c (
        echo testcgi6.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi7.c (
        echo testcgi7.c is missing, cannot continue
        goto err_exception
    )
    if not exist testperl.pl (
        echo testperl.pl is missing, cannot continue
        goto err_exception
    )
    if exist ..\cgi-src\nul cd ..
    if exist debug\nul cd debug
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\debug\nul cd ..
    if exist errors\nul cd errors
    if not exist footer.htm (
        echo footer.htm is missing, cannot continue
        goto err_exception
    )
    if not exist header.htm (
        echo header.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-400.htm (
        echo text-400.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-401.htm (
        echo text-401.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-402.htm (
        echo text-402.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-403.htm (
        echo text-403.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-404.htm (
        echo text-404.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-412.htm (
        echo text-412.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-413.htm (
        echo text-413.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-500.htm (
        echo text-500.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-501.htm (
        echo text-501.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-502.htm (
        echo text-502.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\errors\nul cd ..
    if exist ftproot\nul cd ftproot
    if exist guest\nul cd guest
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\guest\nul cd ..
    if exist pub\nul cd pub
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\pub\nul cd ..
    if exist upload\nul cd upload
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\upload\nul cd ..
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\ftproot\nul cd ..
    if exist headers\nul cd headers
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\headers\nul cd ..
    if exist logs\nul cd logs
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\logs\nul cd ..
    if exist temp\nul cd temp
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\temp\nul cd ..
    if exist templates\nul cd templates
    if not exist errors.gsl (
        echo errors.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist ftpmesg.gsl (
        echo ftpmesg.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist httpdir.gsl (
        echo httpdir.gsl is missing, cannot continue
        goto err_exception
    )
    if exist ..\templates\nul cd ..
    if exist html\nul cd html
    if not exist macros.def (
        echo macros.def is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.def (
        echo prelude.def is missing, cannot continue
        goto err_exception
    )
    if exist ..\html\nul cd ..
    if exist win32\nul cd win32
    if not exist xidos32.exe (
        echo xidos32.exe is missing, cannot continue
        goto err_exception
    )
    if not exist xigui32.exe (
        echo xigui32.exe is missing, cannot continue
        goto err_exception
    )
    if not exist xisrv32.exe (
        echo xisrv32.exe is missing, cannot continue
        goto err_exception
    )
    if not exist xicpl32.cpl (
        echo xicpl32.cpl is missing, cannot continue
        goto err_exception
    )
    if exist ..\win32\nul cd ..
    if exist webpages\nul cd webpages
    if exist xitami\nul cd xitami
    if not exist index*.htm (
        echo index*.htm is missing, cannot continue
        goto err_exception
    )
    if not exist license.htm (
        echo license.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\xitami\nul cd ..
    if exist images\nul cd images
    if not exist buttons.gif (
        echo buttons.gif is missing, cannot continue
        goto err_exception
    )
    if not exist imatix.gif (
        echo imatix.gif is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.gif (
        echo xitami1.gif is missing, cannot continue
        goto err_exception
    )
    if not exist powered*.gif (
        echo powered*.gif is missing, cannot continue
        goto err_exception
    )
    if exist ..\images\nul cd ..
    if exist private\nul cd private
    if not exist private.htm (
        echo private.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\private\nul cd ..
    if not exist buttons.map (
        echo buttons.map is missing, cannot continue
        goto err_exception
    )
    if not exist testssi.inc (
        echo testssi.inc is missing, cannot continue
        goto err_exception
    )
    if not exist testssi.ssi (
        echo testssi.ssi is missing, cannot continue
        goto err_exception
    )
    if not exist default.htm (
        echo default.htm is missing, cannot continue
        goto err_exception
    )
    if not exist mapfail.htm (
        echo mapfail.htm is missing, cannot continue
        goto err_exception
    )
    if not exist windows.htm (
        echo windows.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\webpages\nul cd ..
    if not exist xitami.exe (
        echo xitami.exe is missing, cannot continue
        goto err_exception
    )
    if not exist xilite.exe (
        echo xilite.exe is missing, cannot continue
        goto err_exception
    )
    if not exist xiwtp.exe (
        echo xiwtp.exe is missing, cannot continue
        goto err_exception
    )
    if not exist ddnsdef.xml (
        echo ddnsdef.xml is missing, cannot continue
        goto err_exception
    )
    if not exist pipedef.xml (
        echo pipedef.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ftpadios.txt (
        echo ftpadios.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftphello.txt (
        echo ftphello.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftplogin.txt (
        echo ftplogin.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftpdirs.aut (
        echo ftpdirs.aut is missing, cannot continue
        goto err_exception
    )
    if not exist ftpusers.aut (
        echo ftpusers.aut is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.aut (
        echo xitami.aut is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.cfg (
        echo xitami.cfg is missing, cannot continue
        goto err_exception
    )
    if not exist perlssi (
        echo perlssi is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
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
    if not exist cgi-bin\nul (
        echo directory cgi-bin is missing, cannot continue
        goto err_exception
    )
    if exist cgi-bin\nul cd cgi-bin
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\cgi-bin\nul cd ..
    if not exist cgi-src\nul (
        echo directory cgi-src is missing, cannot continue
        goto err_exception
    )
    if exist cgi-src\nul cd cgi-src
    if not exist testcgi.c (
        echo testcgi.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi1.c (
        echo testcgi1.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi2.c (
        echo testcgi2.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi3.c (
        echo testcgi3.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi4.c (
        echo testcgi4.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi5.c (
        echo testcgi5.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi6.c (
        echo testcgi6.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi7.c (
        echo testcgi7.c is missing, cannot continue
        goto err_exception
    )
    if not exist testperl.pl (
        echo testperl.pl is missing, cannot continue
        goto err_exception
    )
    if exist ..\cgi-src\nul cd ..
    if not exist debug\nul (
        echo directory debug is missing, cannot continue
        goto err_exception
    )
    if exist debug\nul cd debug
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\debug\nul cd ..
    if not exist errors\nul (
        echo directory errors is missing, cannot continue
        goto err_exception
    )
    if exist errors\nul cd errors
    if not exist footer.htm (
        echo footer.htm is missing, cannot continue
        goto err_exception
    )
    if not exist header.htm (
        echo header.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-400.htm (
        echo text-400.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-401.htm (
        echo text-401.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-402.htm (
        echo text-402.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-403.htm (
        echo text-403.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-404.htm (
        echo text-404.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-412.htm (
        echo text-412.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-413.htm (
        echo text-413.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-500.htm (
        echo text-500.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-501.htm (
        echo text-501.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-502.htm (
        echo text-502.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\errors\nul cd ..
    if not exist ftproot\nul (
        echo directory ftproot is missing, cannot continue
        goto err_exception
    )
    if exist ftproot\nul cd ftproot
    if not exist guest\nul (
        echo directory guest is missing, cannot continue
        goto err_exception
    )
    if exist guest\nul cd guest
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\guest\nul cd ..
    if not exist pub\nul (
        echo directory pub is missing, cannot continue
        goto err_exception
    )
    if exist pub\nul cd pub
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\pub\nul cd ..
    if not exist upload\nul (
        echo directory upload is missing, cannot continue
        goto err_exception
    )
    if exist upload\nul cd upload
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\upload\nul cd ..
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\ftproot\nul cd ..
    if not exist headers\nul (
        echo directory headers is missing, cannot continue
        goto err_exception
    )
    if exist headers\nul cd headers
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\headers\nul cd ..
    if not exist logs\nul (
        echo directory logs is missing, cannot continue
        goto err_exception
    )
    if exist logs\nul cd logs
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\logs\nul cd ..
    if not exist temp\nul (
        echo directory temp is missing, cannot continue
        goto err_exception
    )
    if exist temp\nul cd temp
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\temp\nul cd ..
    if not exist templates\nul (
        echo directory templates is missing, cannot continue
        goto err_exception
    )
    if exist templates\nul cd templates
    if not exist errors.gsl (
        echo errors.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist ftpmesg.gsl (
        echo ftpmesg.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist httpdir.gsl (
        echo httpdir.gsl is missing, cannot continue
        goto err_exception
    )
    if exist ..\templates\nul cd ..
    if not exist html\nul (
        echo directory html is missing, cannot continue
        goto err_exception
    )
    if exist html\nul cd html
    if not exist macros.def (
        echo macros.def is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.def (
        echo prelude.def is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.txt (
        echo xitami1.txt is missing, cannot continue
        goto err_exception
    )
    if not exist xitami2.txt (
        echo xitami2.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\html\nul cd ..
    if not exist win32\nul (
        echo directory win32 is missing, cannot continue
        goto err_exception
    )
    if exist win32\nul cd win32
    if not exist about.ico (
        echo about.ico is missing, cannot continue
        goto err_exception
    )
    if not exist active.bmp (
        echo active.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist bitmap4.bmp (
        echo bitmap4.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist bitmap5.bmp (
        echo bitmap5.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist bug100.bmp (
        echo bug100.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist gsl.dsp (
        echo gsl.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist imatix1.bmp (
        echo imatix1.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist off.bmp (
        echo off.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist off.ico (
        echo off.ico is missing, cannot continue
        goto err_exception
    )
    if not exist on.bmp (
        echo on.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist on.ico (
        echo on.ico is missing, cannot continue
        goto err_exception
    )
    if not exist resource.h (
        echo resource.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfl.dsp (
        echo sfl.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist smt.dsp (
        echo smt.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist studio.dsp (
        echo studio.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.dsp (
        echo xiadmin.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist xicpl32.c (
        echo xicpl32.c is missing, cannot continue
        goto err_exception
    )
    if not exist xicpl32.def (
        echo xicpl32.def is missing, cannot continue
        goto err_exception
    )
    if not exist xigui32.c (
        echo xigui32.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiprocpl.def (
        echo xiprocpl.def is missing, cannot continue
        goto err_exception
    )
    if not exist xisrv32.c (
        echo xisrv32.c is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Console.dsp (
        echo Xitami_Console.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Control_Panel.dsp (
        echo Xitami_Control_Panel.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Service.dsp (
        echo Xitami_Service.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Win32.dsp (
        echo Xitami_Win32.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.dsw (
        echo xitami.dsw is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.h (
        echo xitami.h is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.bmp (
        echo xitami1.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist xiwin.rc (
        echo xiwin.rc is missing, cannot continue
        goto err_exception
    )
    if exist ..\win32\nul cd ..
    if not exist webpages\nul (
        echo directory webpages is missing, cannot continue
        goto err_exception
    )
    if exist webpages\nul cd webpages
    if not exist xitami\nul (
        echo directory xitami is missing, cannot continue
        goto err_exception
    )
    if exist xitami\nul cd xitami
    if exist ..\xitami\nul cd ..
    if not exist images\nul (
        echo directory images is missing, cannot continue
        goto err_exception
    )
    if exist images\nul cd images
    if not exist buttons.gif (
        echo buttons.gif is missing, cannot continue
        goto err_exception
    )
    if not exist imatix.gif (
        echo imatix.gif is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.gif (
        echo xitami1.gif is missing, cannot continue
        goto err_exception
    )
    if not exist powered*.gif (
        echo powered*.gif is missing, cannot continue
        goto err_exception
    )
    if exist ..\images\nul cd ..
    if not exist private\nul (
        echo directory private is missing, cannot continue
        goto err_exception
    )
    if exist private\nul cd private
    if exist ..\private\nul cd ..
    if not exist buttons.map (
        echo buttons.map is missing, cannot continue
        goto err_exception
    )
    if not exist testssi.inc (
        echo testssi.inc is missing, cannot continue
        goto err_exception
    )
    if exist ..\webpages\nul cd ..
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist xiopen.xml (
        echo xiopen.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ddnsdef.xml (
        echo ddnsdef.xml is missing, cannot continue
        goto err_exception
    )
    if not exist pipedef.xml (
        echo pipedef.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ftpadios.txt (
        echo ftpadios.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftphello.txt (
        echo ftphello.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftplogin.txt (
        echo ftplogin.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftpdirs.aut (
        echo ftpdirs.aut is missing, cannot continue
        goto err_exception
    )
    if not exist ftpusers.aut (
        echo ftpusers.aut is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.aut (
        echo xitami.aut is missing, cannot continue
        goto err_exception
    )
    if not exist xixlat.c (
        echo xixlat.c is missing, cannot continue
        goto err_exception
    )
    if not exist perlssi (
        echo perlssi is missing, cannot continue
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
    if not exist boomake (
        echo boomake is missing, cannot continue
        goto err_exception
    )
    if not exist boomake.bat (
        echo boomake.bat is missing, cannot continue
        goto err_exception
    )
    goto exit

:------------------------   CHECK SOURCE FILES EXIST   ------------------------

:a_check_source_files_exist
    if exist cgi-bin\nul cd cgi-bin
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\cgi-bin\nul cd ..
    if exist cgi-src\nul cd cgi-src
    if not exist testcgi.c (
        echo testcgi.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi1.c (
        echo testcgi1.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi2.c (
        echo testcgi2.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi3.c (
        echo testcgi3.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi4.c (
        echo testcgi4.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi5.c (
        echo testcgi5.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi6.c (
        echo testcgi6.c is missing, cannot continue
        goto err_exception
    )
    if not exist testcgi7.c (
        echo testcgi7.c is missing, cannot continue
        goto err_exception
    )
    if not exist testperl.pl (
        echo testperl.pl is missing, cannot continue
        goto err_exception
    )
    if exist ..\cgi-src\nul cd ..
    if exist debug\nul cd debug
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\debug\nul cd ..
    if exist errors\nul cd errors
    if not exist footer.htm (
        echo footer.htm is missing, cannot continue
        goto err_exception
    )
    if not exist header.htm (
        echo header.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-400.htm (
        echo text-400.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-401.htm (
        echo text-401.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-402.htm (
        echo text-402.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-403.htm (
        echo text-403.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-404.htm (
        echo text-404.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-412.htm (
        echo text-412.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-413.htm (
        echo text-413.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-500.htm (
        echo text-500.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-501.htm (
        echo text-501.htm is missing, cannot continue
        goto err_exception
    )
    if not exist text-502.htm (
        echo text-502.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\errors\nul cd ..
    if exist ftproot\nul cd ftproot
    if exist guest\nul cd guest
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\guest\nul cd ..
    if exist pub\nul cd pub
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\pub\nul cd ..
    if exist upload\nul cd upload
    if not exist index.htm (
        echo index.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index.txt (
        echo index.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\upload\nul cd ..
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\ftproot\nul cd ..
    if exist headers\nul cd headers
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\headers\nul cd ..
    if exist logs\nul cd logs
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\logs\nul cd ..
    if exist temp\nul cd temp
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if exist ..\temp\nul cd ..
    if exist templates\nul cd templates
    if not exist errors.gsl (
        echo errors.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist ftpmesg.gsl (
        echo ftpmesg.gsl is missing, cannot continue
        goto err_exception
    )
    if not exist httpdir.gsl (
        echo httpdir.gsl is missing, cannot continue
        goto err_exception
    )
    if exist ..\templates\nul cd ..
    if exist html\nul cd html
    if not exist anchor.def (
        echo anchor.def is missing, cannot continue
        goto err_exception
    )
    if not exist macros.def (
        echo macros.def is missing, cannot continue
        goto err_exception
    )
    if not exist prelude.def (
        echo prelude.def is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.txt (
        echo xitami1.txt is missing, cannot continue
        goto err_exception
    )
    if not exist xitami2.txt (
        echo xitami2.txt is missing, cannot continue
        goto err_exception
    )
    if not exist testssi.ssi (
        echo testssi.ssi is missing, cannot continue
        goto err_exception
    )
    if not exist private.htm (
        echo private.htm is missing, cannot continue
        goto err_exception
    )
    if not exist default.htm (
        echo default.htm is missing, cannot continue
        goto err_exception
    )
    if not exist index*.htm (
        echo index*.htm is missing, cannot continue
        goto err_exception
    )
    if not exist license.htm (
        echo license.htm is missing, cannot continue
        goto err_exception
    )
    if not exist belgium.htm (
        echo belgium.htm is missing, cannot continue
        goto err_exception
    )
    if not exist mapfail.htm (
        echo mapfail.htm is missing, cannot continue
        goto err_exception
    )
    if not exist os2-readme.htm (
        echo os2-readme.htm is missing, cannot continue
        goto err_exception
    )
    if not exist unix-readme.htm (
        echo unix-readme.htm is missing, cannot continue
        goto err_exception
    )
    if not exist windows.htm (
        echo windows.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\html\nul cd ..
    if exist win32\nul cd win32
    if not exist about.ico (
        echo about.ico is missing, cannot continue
        goto err_exception
    )
    if not exist active.bmp (
        echo active.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist bitmap4.bmp (
        echo bitmap4.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist bitmap5.bmp (
        echo bitmap5.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist bug100.bmp (
        echo bug100.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist gsl.dsp (
        echo gsl.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist imatix1.bmp (
        echo imatix1.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist off.bmp (
        echo off.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist off.ico (
        echo off.ico is missing, cannot continue
        goto err_exception
    )
    if not exist on.bmp (
        echo on.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist on.ico (
        echo on.ico is missing, cannot continue
        goto err_exception
    )
    if not exist resource.h (
        echo resource.h is missing, cannot continue
        goto err_exception
    )
    if not exist sfl.dsp (
        echo sfl.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist smt.dsp (
        echo smt.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist studio.dsp (
        echo studio.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.dsp (
        echo xiadmin.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist xicpl32.c (
        echo xicpl32.c is missing, cannot continue
        goto err_exception
    )
    if not exist xicpl32.def (
        echo xicpl32.def is missing, cannot continue
        goto err_exception
    )
    if not exist xigui32.c (
        echo xigui32.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiprocpl.def (
        echo xiprocpl.def is missing, cannot continue
        goto err_exception
    )
    if not exist xisrv32.c (
        echo xisrv32.c is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Console.dsp (
        echo Xitami_Console.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Control_Panel.dsp (
        echo Xitami_Control_Panel.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Service.dsp (
        echo Xitami_Service.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist Xitami_Win32.dsp (
        echo Xitami_Win32.dsp is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.dsw (
        echo xitami.dsw is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.h (
        echo xitami.h is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.bmp (
        echo xitami1.bmp is missing, cannot continue
        goto err_exception
    )
    if not exist xiwin.rc (
        echo xiwin.rc is missing, cannot continue
        goto err_exception
    )
    if exist ..\win32\nul cd ..
    if exist webpages\nul cd webpages
    if exist xitami\nul cd xitami
    if not exist index*.htm (
        echo index*.htm is missing, cannot continue
        goto err_exception
    )
    if not exist license.htm (
        echo license.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\xitami\nul cd ..
    if exist images\nul cd images
    if not exist buttons.gif (
        echo buttons.gif is missing, cannot continue
        goto err_exception
    )
    if not exist imatix.gif (
        echo imatix.gif is missing, cannot continue
        goto err_exception
    )
    if not exist xitami1.gif (
        echo xitami1.gif is missing, cannot continue
        goto err_exception
    )
    if not exist powered*.gif (
        echo powered*.gif is missing, cannot continue
        goto err_exception
    )
    if exist ..\images\nul cd ..
    if exist private\nul cd private
    if not exist private.htm (
        echo private.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\private\nul cd ..
    if not exist buttons.map (
        echo buttons.map is missing, cannot continue
        goto err_exception
    )
    if not exist testssi.inc (
        echo testssi.inc is missing, cannot continue
        goto err_exception
    )
    if not exist testssi.ssi (
        echo testssi.ssi is missing, cannot continue
        goto err_exception
    )
    if not exist default.htm (
        echo default.htm is missing, cannot continue
        goto err_exception
    )
    if not exist mapfail.htm (
        echo mapfail.htm is missing, cannot continue
        goto err_exception
    )
    if not exist windows.htm (
        echo windows.htm is missing, cannot continue
        goto err_exception
    )
    if exist ..\webpages\nul cd ..
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist xiopen.xml (
        echo xiopen.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ddnsdef.xml (
        echo ddnsdef.xml is missing, cannot continue
        goto err_exception
    )
    if not exist pipedef.xml (
        echo pipedef.xml is missing, cannot continue
        goto err_exception
    )
    if not exist ftpadios.txt (
        echo ftpadios.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftphello.txt (
        echo ftphello.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftplogin.txt (
        echo ftplogin.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ftpdirs.aut (
        echo ftpdirs.aut is missing, cannot continue
        goto err_exception
    )
    if not exist ftpusers.aut (
        echo ftpusers.aut is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.aut (
        echo xitami.aut is missing, cannot continue
        goto err_exception
    )
    if not exist xitami.cfg (
        echo xitami.cfg is missing, cannot continue
        goto err_exception
    )
    if not exist xixlat.c (
        echo xixlat.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiconfig.htp (
        echo xiconfig.htp is missing, cannot continue
        goto err_exception
    )
    if not exist perlssi (
        echo perlssi is missing, cannot continue
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
    if not exist xitami.c (
        echo xitami.c is missing, cannot continue
        goto err_exception
    )
    if not exist xilite.c (
        echo xilite.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiwtp.c (
        echo xiwtp.c is missing, cannot continue
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

:--------------------------   INSTALL DELIVERABLES   --------------------------

:a_install_deliverables
    set TARGET=%_IBASE%\xitami-25\app
    echo Installing Xitami/Open into %TARGET%...
    if not exist %TARGET%\cgi-bin\nul mkdir %TARGET%\cgi-bin\
    dir>nul
    copy/y cgi-bin\readme.txt %TARGET%\cgi-bin\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-bin\readme.txt %TARGET%\cgi-bin\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\cgi-src\nul mkdir %TARGET%\cgi-src\
    dir>nul
    copy/y cgi-src\testcgi.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi1.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi1.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi2.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi2.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi3.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi3.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi4.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi4.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi5.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi5.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi6.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi6.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testcgi7.c %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testcgi7.c %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y cgi-src\testperl.pl %TARGET%\cgi-src\>nul
    if errorlevel 1 echo boomake: "copy/y cgi-src\testperl.pl %TARGET%\cgi-src\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\debug\nul mkdir %TARGET%\debug\
    dir>nul
    copy/y debug\readme.txt %TARGET%\debug\>nul
    if errorlevel 1 echo boomake: "copy/y debug\readme.txt %TARGET%\debug\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\errors\nul mkdir %TARGET%\errors\
    dir>nul
    copy/y errors\footer.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\footer.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\header.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\header.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-400.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-400.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-401.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-401.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-402.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-402.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-403.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-403.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-404.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-404.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-412.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-412.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-413.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-413.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-500.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-500.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-501.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-501.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y errors\text-502.htm %TARGET%\errors\>nul
    if errorlevel 1 echo boomake: "copy/y errors\text-502.htm %TARGET%\errors\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\ftproot\guest\nul mkdir %TARGET%\ftproot\guest\
    dir>nul
    copy/y ftproot\guest\index.htm %TARGET%\ftproot\guest\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\guest\index.htm %TARGET%\ftproot\guest\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftproot\guest\index.txt %TARGET%\ftproot\guest\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\guest\index.txt %TARGET%\ftproot\guest\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\ftproot\pub\nul mkdir %TARGET%\ftproot\pub\
    dir>nul
    copy/y ftproot\pub\index.htm %TARGET%\ftproot\pub\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\pub\index.htm %TARGET%\ftproot\pub\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftproot\pub\index.txt %TARGET%\ftproot\pub\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\pub\index.txt %TARGET%\ftproot\pub\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\ftproot\upload\nul mkdir %TARGET%\ftproot\upload\
    dir>nul
    copy/y ftproot\upload\index.htm %TARGET%\ftproot\upload\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\upload\index.htm %TARGET%\ftproot\upload\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftproot\upload\index.txt %TARGET%\ftproot\upload\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\upload\index.txt %TARGET%\ftproot\upload\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\ftproot\nul mkdir %TARGET%\ftproot\
    dir>nul
    copy/y ftproot\readme.txt %TARGET%\ftproot\>nul
    if errorlevel 1 echo boomake: "copy/y ftproot\readme.txt %TARGET%\ftproot\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\headers\nul mkdir %TARGET%\headers\
    dir>nul
    copy/y headers\readme.txt %TARGET%\headers\>nul
    if errorlevel 1 echo boomake: "copy/y headers\readme.txt %TARGET%\headers\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\logs\nul mkdir %TARGET%\logs\
    dir>nul
    copy/y logs\readme.txt %TARGET%\logs\>nul
    if errorlevel 1 echo boomake: "copy/y logs\readme.txt %TARGET%\logs\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\temp\nul mkdir %TARGET%\temp\
    dir>nul
    copy/y temp\readme.txt %TARGET%\temp\>nul
    if errorlevel 1 echo boomake: "copy/y temp\readme.txt %TARGET%\temp\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\templates\nul mkdir %TARGET%\templates\
    dir>nul
    copy/y templates\errors.gsl %TARGET%\templates\>nul
    if errorlevel 1 echo boomake: "copy/y templates\errors.gsl %TARGET%\templates\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y templates\ftpmesg.gsl %TARGET%\templates\>nul
    if errorlevel 1 echo boomake: "copy/y templates\ftpmesg.gsl %TARGET%\templates\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y templates\httpdir.gsl %TARGET%\templates\>nul
    if errorlevel 1 echo boomake: "copy/y templates\httpdir.gsl %TARGET%\templates\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\html\nul mkdir %TARGET%\html\
    dir>nul
    copy/y html\macros.def %TARGET%\html\>nul
    if errorlevel 1 echo boomake: "copy/y html\macros.def %TARGET%\html\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\prelude.def %TARGET%\html\>nul
    if errorlevel 1 echo boomake: "copy/y html\prelude.def %TARGET%\html\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\nul mkdir %TARGET%\
    dir>nul
    copy/y win32\xidos32.exe %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y win32\xidos32.exe %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y win32\xigui32.exe %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y win32\xigui32.exe %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y win32\xisrv32.exe %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y win32\xisrv32.exe %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y win32\xicpl32.cpl %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y win32\xicpl32.cpl %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\webpages\xitami\nul mkdir %TARGET%\webpages\xitami\
    dir>nul
    copy/y webpages\xitami\index*.htm %TARGET%\webpages\xitami\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\xitami\index*.htm %TARGET%\webpages\xitami\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\xitami\license.htm %TARGET%\webpages\xitami\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\xitami\license.htm %TARGET%\webpages\xitami\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\webpages\images\nul mkdir %TARGET%\webpages\images\
    dir>nul
    copy/y webpages\images\buttons.gif %TARGET%\webpages\images\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\images\buttons.gif %TARGET%\webpages\images\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\images\imatix.gif %TARGET%\webpages\images\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\images\imatix.gif %TARGET%\webpages\images\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\images\xitami1.gif %TARGET%\webpages\images\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\images\xitami1.gif %TARGET%\webpages\images\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\images\powered*.gif %TARGET%\webpages\images\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\images\powered*.gif %TARGET%\webpages\images\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\webpages\private\nul mkdir %TARGET%\webpages\private\
    dir>nul
    copy/y webpages\private\private.htm %TARGET%\webpages\private\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\private\private.htm %TARGET%\webpages\private\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\webpages\nul mkdir %TARGET%\webpages\
    dir>nul
    copy/y webpages\buttons.map %TARGET%\webpages\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\buttons.map %TARGET%\webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\testssi.inc %TARGET%\webpages\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\testssi.inc %TARGET%\webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\testssi.ssi %TARGET%\webpages\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\testssi.ssi %TARGET%\webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\default.htm %TARGET%\webpages\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\default.htm %TARGET%\webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\mapfail.htm %TARGET%\webpages\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\mapfail.htm %TARGET%\webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y webpages\windows.htm %TARGET%\webpages\>nul
    if errorlevel 1 echo boomake: "copy/y webpages\windows.htm %TARGET%\webpages\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\nul mkdir %TARGET%\
    dir>nul
    copy/y xitami.exe %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y xitami.exe %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xilite.exe %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y xilite.exe %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xiwtp.exe %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y xiwtp.exe %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ddnsdef.xml %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y ddnsdef.xml %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y pipedef.xml %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y pipedef.xml %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftpadios.txt %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y ftpadios.txt %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftphello.txt %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y ftphello.txt %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftplogin.txt %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y ftplogin.txt %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftpdirs.aut %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y ftpdirs.aut %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y ftpusers.aut %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y ftpusers.aut %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xitami.aut %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y xitami.aut %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y xitami.cfg %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y xitami.cfg %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y perlssi %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y perlssi %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y readme.txt %TARGET%\>nul
    if errorlevel 1 echo boomake: "copy/y readme.txt %TARGET%\>nul" failed
    if errorlevel 1 goto err_exception
    goto exit

:-------------------------   PRODUCE GENERATED FILES   ------------------------

:a_produce_generated_files
    dir>nul
    call gsl -q -build_doc:1 -build_config:1 xiconfig
    if errorlevel 1 echo boomake: "call gsl -q -build_doc:1 -build_config:1 xiconfig" failed
    if errorlevel 1 goto err_exception
    if exist cgi-bin\nul cd cgi-bin
    if exist ..\cgi-bin\nul cd ..
    if exist cgi-src\nul cd cgi-src
    if exist ..\cgi-src\nul cd ..
    if exist debug\nul cd debug
    if exist ..\debug\nul cd ..
    if exist errors\nul cd errors
    if exist ..\errors\nul cd ..
    if exist ftproot\nul cd ftproot
    if exist guest\nul cd guest
    if exist ..\guest\nul cd ..
    if exist pub\nul cd pub
    if exist ..\pub\nul cd ..
    if exist upload\nul cd upload
    if exist ..\upload\nul cd ..
    if exist ..\ftproot\nul cd ..
    if exist headers\nul cd headers
    if exist ..\headers\nul cd ..
    if exist logs\nul cd logs
    if exist ..\logs\nul cd ..
    if exist temp\nul cd temp
    if exist ..\temp\nul cd ..
    if exist templates\nul cd templates
    if exist ..\templates\nul cd ..
    if exist html\nul cd html
    dir>nul
    call htmlpp xitami1.txt
    if errorlevel 1 echo boomake: "call htmlpp xitami1.txt" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call htmlpp xitami2.txt
    if errorlevel 1 echo boomake: "call htmlpp xitami2.txt" failed
    if errorlevel 1 goto err_exception
    if exist ..\html\nul cd ..
    if exist win32\nul cd win32
    if exist ..\win32\nul cd ..
    if exist webpages\nul cd webpages
    if exist xitami\nul cd xitami
    if exist ..\xitami\nul cd ..
    if exist images\nul cd images
    if exist ..\images\nul cd ..
    if exist private\nul cd private
    if exist ..\private\nul cd ..
    if exist ..\webpages\nul cd ..
    dir>nul
    call gsl -q xiopen.xml
    if errorlevel 1 echo boomake: "call gsl -q xiopen.xml" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\index*.htm webpages\xitami\>nul
    if errorlevel 1 echo boomake: "copy/y html\index*.htm webpages\xitami\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\license.htm webpages\xitami\>nul
    if errorlevel 1 echo boomake: "copy/y html\license.htm webpages\xitami\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\private.htm webpages\private\>nul
    if errorlevel 1 echo boomake: "copy/y html\private.htm webpages\private\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\testssi.ssi webpages\>nul
    if errorlevel 1 echo boomake: "copy/y html\testssi.ssi webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\default.htm webpages\>nul
    if errorlevel 1 echo boomake: "copy/y html\default.htm webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\mapfail.htm webpages\>nul
    if errorlevel 1 echo boomake: "copy/y html\mapfail.htm webpages\>nul" failed
    if errorlevel 1 goto err_exception
    dir>nul
    copy/y html\windows.htm webpages\>nul
    if errorlevel 1 echo boomake: "copy/y html\windows.htm webpages\>nul" failed
    if errorlevel 1 goto err_exception
    goto exit

:------------------------   REMOVE GENERATED BINARIES   -----------------------

:a_remove_generated_binaries
    if exist xitami.exe del xitami.exe
    if exist xilite.exe del xilite.exe
    if exist xiwtp.exe del xiwtp.exe
    if exist xitami.obj del xitami.obj
    if exist xitami.exe del xitami.exe
    if exist xilite.obj del xilite.obj
    if exist xilite.exe del xilite.exe
    if exist xiwtp.obj del xiwtp.obj
    if exist xiwtp.exe del xiwtp.exe
    if exist xixlat.obj del xixlat.obj
    if exist xixlat.exe del xixlat.exe
    if exist cgi-bin\nul cd cgi-bin
    if exist ..\cgi-bin\nul cd ..
    if exist cgi-src\nul cd cgi-src
    if exist ..\cgi-src\nul cd ..
    if exist debug\nul cd debug
    if exist ..\debug\nul cd ..
    if exist errors\nul cd errors
    if exist ..\errors\nul cd ..
    if exist ftproot\nul cd ftproot
    if exist guest\nul cd guest
    if exist ..\guest\nul cd ..
    if exist pub\nul cd pub
    if exist ..\pub\nul cd ..
    if exist upload\nul cd upload
    if exist ..\upload\nul cd ..
    if exist ..\ftproot\nul cd ..
    if exist headers\nul cd headers
    if exist ..\headers\nul cd ..
    if exist logs\nul cd logs
    if exist ..\logs\nul cd ..
    if exist temp\nul cd temp
    if exist ..\temp\nul cd ..
    if exist templates\nul cd templates
    if exist ..\templates\nul cd ..
    if exist html\nul cd html
    if exist ..\html\nul cd ..
    if exist win32\nul cd win32
    dir>nul
    call msdev xitami.dsw /make "all - release" /clean
    if errorlevel 1 echo boomake: "call msdev xitami.dsw /make "all - release" /clean" failed
    if errorlevel 1 goto err_exception
    if exist ..\win32\nul cd ..
    if exist webpages\nul cd webpages
    if exist xitami\nul cd xitami
    if exist ..\xitami\nul cd ..
    if exist images\nul cd images
    if exist ..\images\nul cd ..
    if exist private\nul cd private
    if exist ..\private\nul cd ..
    if exist ..\webpages\nul cd ..
    if exist vc60.pdb del vc60.pdb
    goto exit

:------------------------   REMOVE GENERATED SOURCES   ------------------------

:a_remove_generated_sources
    if exist html\anchor.def del html\anchor.def
    if exist html\testssi.ssi del html\testssi.ssi
    if exist html\private.htm del html\private.htm
    if exist html\default.htm del html\default.htm
    if exist html\index*.htm del html\index*.htm
    if exist html\license.htm del html\license.htm
    if exist html\belgium.htm del html\belgium.htm
    if exist html\mapfail.htm del html\mapfail.htm
    if exist html\os2-readme.htm del html\os2-readme.htm
    if exist html\unix-readme.htm del html\unix-readme.htm
    if exist html\windows.htm del html\windows.htm
    if exist win32\xidos32.exe del win32\xidos32.exe
    if exist win32\xigui32.exe del win32\xigui32.exe
    if exist win32\xisrv32.exe del win32\xisrv32.exe
    if exist win32\xicpl32.cpl del win32\xicpl32.cpl
    if exist webpages\xitami\index*.htm del webpages\xitami\index*.htm
    if exist webpages\xitami\license.htm del webpages\xitami\license.htm
    if exist webpages\private\private.htm del webpages\private\private.htm
    if exist webpages\testssi.ssi del webpages\testssi.ssi
    if exist webpages\default.htm del webpages\default.htm
    if exist webpages\mapfail.htm del webpages\mapfail.htm
    if exist webpages\windows.htm del webpages\windows.htm
    if exist xitami.cfg del xitami.cfg
    if exist xiconfig.htp del xiconfig.htp
    if exist xitami.c del xitami.c
    if exist xilite.c del xilite.c
    if exist xiwtp.c del xiwtp.c
    goto exit

:-------------------------   REPORT HELP INFORMATION   ------------------------

:a_report_help_information
    echo boomake - Boom! builder for Xitami/Open 2.5c2
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

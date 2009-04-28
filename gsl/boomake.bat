@echo off
:-
:-  Boom builder for GSL 2.01
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
    call c -q %COPTS% gslgen
    if errorlevel 1 echo boomake: "call c -q %COPTS% gslgen" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggcode
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggcode" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggcomm
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggcomm" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggeval
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggeval" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggfile
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggfile" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggfunc
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggfunc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggobjt
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggobjt" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggstrn
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggstrn" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% ggpars
    if errorlevel 1 echo boomake: "call c -q %COPTS% ggpars" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggcode
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggcode" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggcomm
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggcomm" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggeval
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggeval" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggfile
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggfile" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggfunc
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggfunc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggobjt
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggobjt" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggstrn
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggstrn" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libgsl.lib ggpars
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libgsl.lib ggpars" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -L gslgen
    if errorlevel 1 echo boomake: "call c -q %COPTS% -L gslgen" failed
    if errorlevel 1 goto err_exception
    goto exit

:--------------------------   BUILD SOURCE PACKAGES   -------------------------

:a_build_source_packages
    if exist _package.lst del _package.lst
    if exist gsl\version.h echo gsl\version.h>>_package.lst
    if exist gsl\gslgen.c echo gsl\gslgen.c>>_package.lst
    if exist gsl\gslgen.l echo gsl\gslgen.l>>_package.lst
    if exist gsl\ggcode.c echo gsl\ggcode.c>>_package.lst
    if exist gsl\ggcode.h echo gsl\ggcode.h>>_package.lst
    if exist gsl\ggcomm.c echo gsl\ggcomm.c>>_package.lst
    if exist gsl\ggeval.c echo gsl\ggeval.c>>_package.lst
    if exist gsl\ggfile.c echo gsl\ggfile.c>>_package.lst
    if exist gsl\ggfunc.c echo gsl\ggfunc.c>>_package.lst
    if exist gsl\ggjs.h echo gsl\ggjs.h>>_package.lst
    if exist gsl\ggobjt.c echo gsl\ggobjt.c>>_package.lst
    if exist gsl\ggstrn.c echo gsl\ggstrn.c>>_package.lst
    if exist gsl\ggpars.c echo gsl\ggpars.c>>_package.lst
    if exist gsl\gsldoc.txt echo gsl\gsldoc.txt>>_package.lst
    if exist gsl\guru.def echo gsl\guru.def>>_package.lst
    if exist gsl\macros.def echo gsl\macros.def>>_package.lst
    if exist gsl\prelude.def echo gsl\prelude.def>>_package.lst
    if exist gsl\prelude.pdl echo gsl\prelude.pdl>>_package.lst
    if exist gsl\license.gpl echo gsl\license.gpl>>_package.lst
    if exist gsl\project.pdl echo gsl\project.pdl>>_package.lst
    if exist gsl\readme.txt echo gsl\readme.txt>>_package.lst
    if exist gsl\gslgen.i echo gsl\gslgen.i>>_package.lst
    if exist gsl\gslgen.d echo gsl\gslgen.d>>_package.lst
    if exist gsl\ggcode.l echo gsl\ggcode.l>>_package.lst
    if exist gsl\ggcode.i echo gsl\ggcode.i>>_package.lst
    if exist gsl\ggcode.d echo gsl\ggcode.d>>_package.lst
    if exist gsl\ggcomm.h echo gsl\ggcomm.h>>_package.lst
    if exist gsl\ggeval.h echo gsl\ggeval.h>>_package.lst
    if exist gsl\ggfile.h echo gsl\ggfile.h>>_package.lst
    if exist gsl\ggfunc.h echo gsl\ggfunc.h>>_package.lst
    if exist gsl\ggobjt.h echo gsl\ggobjt.h>>_package.lst
    if exist gsl\ggstrn.h echo gsl\ggstrn.h>>_package.lst
    if exist gsl\ggpars.l echo gsl\ggpars.l>>_package.lst
    if exist gsl\ggpars.i echo gsl\ggpars.i>>_package.lst
    if exist gsl\ggpars.d echo gsl\ggpars.d>>_package.lst
    if exist gsl\ggpars.h echo gsl\ggpars.h>>_package.lst
    if exist gsl\boomake echo gsl\boomake>>_package.lst
    if exist gsl\boomake.bat echo gsl\boomake.bat>>_package.lst
    if exist gsl\makefile echo gsl\makefile>>_package.lst
    if exist gsl\msmake echo gsl\msmake>>_package.lst
    echo Building gsl_2_01_src.zip...
    dir>nul
    zip -q gsl_2_01_src -@<_package.lst
    if errorlevel 1 echo boomake: "zip -q gsl_2_01_src -@<_package.lst" failed
    if errorlevel 1 goto err_exception
    del _package.lst
    goto exit

:------------------------   CHECK BINARY FILES EXIST   ------------------------

:a_check_binary_files_exist
    if not exist ggcode.h (
        echo ggcode.h is missing, cannot continue
        goto err_exception
    )
    if not exist libgsl.lib (
        echo libgsl.lib is missing, cannot continue
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
    if not exist version.h (
        echo version.h is missing, cannot continue
        goto err_exception
    )
    if not exist gslgen.c (
        echo gslgen.c is missing, cannot continue
        goto err_exception
    )
    if not exist gslgen.l (
        echo gslgen.l is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.c (
        echo ggcode.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.h (
        echo ggcode.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggcomm.c (
        echo ggcomm.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggeval.c (
        echo ggeval.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggfile.c (
        echo ggfile.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggfunc.c (
        echo ggfunc.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggjs.h (
        echo ggjs.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggobjt.c (
        echo ggobjt.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggstrn.c (
        echo ggstrn.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.c (
        echo ggpars.c is missing, cannot continue
        goto err_exception
    )
    if not exist gsldoc.txt (
        echo gsldoc.txt is missing, cannot continue
        goto err_exception
    )
    if not exist guru.def (
        echo guru.def is missing, cannot continue
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
    if not exist project.pdl (
        echo project.pdl is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.l (
        echo ggcode.l is missing, cannot continue
        goto err_exception
    )
    if not exist ggcomm.h (
        echo ggcomm.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggeval.h (
        echo ggeval.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggfile.h (
        echo ggfile.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggfunc.h (
        echo ggfunc.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggobjt.h (
        echo ggobjt.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggstrn.h (
        echo ggstrn.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.l (
        echo ggpars.l is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.h (
        echo ggpars.h is missing, cannot continue
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
    if not exist gslgen.c (
        echo gslgen.c is missing, cannot continue
        goto err_exception
    )
    if not exist gslgen.l (
        echo gslgen.l is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.c (
        echo ggcode.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.h (
        echo ggcode.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggcomm.c (
        echo ggcomm.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggeval.c (
        echo ggeval.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggfile.c (
        echo ggfile.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggfunc.c (
        echo ggfunc.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggjs.h (
        echo ggjs.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggobjt.c (
        echo ggobjt.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggstrn.c (
        echo ggstrn.c is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.c (
        echo ggpars.c is missing, cannot continue
        goto err_exception
    )
    if not exist gsldoc.txt (
        echo gsldoc.txt is missing, cannot continue
        goto err_exception
    )
    if not exist guru.def (
        echo guru.def is missing, cannot continue
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
    if not exist project.pdl (
        echo project.pdl is missing, cannot continue
        goto err_exception
    )
    if not exist readme.txt (
        echo readme.txt is missing, cannot continue
        goto err_exception
    )
    if not exist gslgen.i (
        echo gslgen.i is missing, cannot continue
        goto err_exception
    )
    if not exist gslgen.d (
        echo gslgen.d is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.l (
        echo ggcode.l is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.i (
        echo ggcode.i is missing, cannot continue
        goto err_exception
    )
    if not exist ggcode.d (
        echo ggcode.d is missing, cannot continue
        goto err_exception
    )
    if not exist ggcomm.h (
        echo ggcomm.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggeval.h (
        echo ggeval.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggfile.h (
        echo ggfile.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggfunc.h (
        echo ggfunc.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggobjt.h (
        echo ggobjt.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggstrn.h (
        echo ggstrn.h is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.l (
        echo ggpars.l is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.i (
        echo ggpars.i is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.d (
        echo ggpars.d is missing, cannot continue
        goto err_exception
    )
    if not exist ggpars.h (
        echo ggpars.h is missing, cannot continue
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
    echo Installing GSL into %TARGET%...
    if not exist %TARGET%\include\nul mkdir %TARGET%\include\
    dir>nul
    copy/y ggcode.h %TARGET%\include\>nul
    if errorlevel 1 echo boomake: "copy/y ggcode.h %TARGET%\include\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\lib\nul mkdir %TARGET%\lib\
    dir>nul
    copy/y libgsl.lib %TARGET%\lib\>nul
    if errorlevel 1 echo boomake: "copy/y libgsl.lib %TARGET%\lib\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    if not exist %TARGET%\doc\GSL\nul mkdir %TARGET%\doc\GSL\
    dir>nul
    copy/y readme.txt %TARGET%\doc\GSL\>nul
    if errorlevel 1 echo boomake: "copy/y readme.txt %TARGET%\doc\GSL\>nul" failed
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
    call lr gslgen.l
    if errorlevel 1 echo boomake: "call lr gslgen.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr ggcode.l
    if errorlevel 1 echo boomake: "call lr ggcode.l" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr ggpars.l
    if errorlevel 1 echo boomake: "call lr ggpars.l" failed
    if errorlevel 1 goto err_exception
    goto exit

:------------------------   REMOVE GENERATED BINARIES   -----------------------

:a_remove_generated_binaries
    if exist libgsl.lib del libgsl.lib
    if exist gslgen.obj del gslgen.obj
    if exist gslgen.exe del gslgen.exe
    if exist ggcode.obj del ggcode.obj
    if exist ggcomm.obj del ggcomm.obj
    if exist ggeval.obj del ggeval.obj
    if exist ggfile.obj del ggfile.obj
    if exist ggfunc.obj del ggfunc.obj
    if exist ggobjt.obj del ggobjt.obj
    if exist ggstrn.obj del ggstrn.obj
    if exist ggpars.obj del ggpars.obj
    if exist vc60.pdb del vc60.pdb
    goto exit

:------------------------   REMOVE GENERATED SOURCES   ------------------------

:a_remove_generated_sources
    if exist gslgen.i del gslgen.i
    if exist gslgen.d del gslgen.d
    if exist ggcode.i del ggcode.i
    if exist ggcode.d del ggcode.d
    if exist ggpars.i del ggpars.i
    if exist ggpars.d del ggpars.d
    goto exit

:-------------------------   REPORT HELP INFORMATION   ------------------------

:a_report_help_information
    echo boomake - Boom! builder for GSL 2.01
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

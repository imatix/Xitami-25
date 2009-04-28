@echo off
:-
:-  Boom builder for Xitami Administration Console 2.5
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
    call c -q %COPTS% xiadmin
    if errorlevel 1 echo boomake: "call c -q %COPTS% xiadmin" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call c -q %COPTS% -r libxac.lib xiadmin
    if errorlevel 1 echo boomake: "call c -q %COPTS% -r libxac.lib xiadmin" failed
    if errorlevel 1 goto err_exception
    goto exit

:--------------------------   BUILD SOURCE PACKAGES   -------------------------

:a_build_source_packages
    if exist _package.lst del _package.lst
    if exist xiadmin\version.h echo xiadmin\version.h>>_package.lst
    if exist xiadmin\xiadmin.c echo xiadmin\xiadmin.c>>_package.lst
    if exist xiadmin\xiadmin.fdl echo xiadmin\xiadmin.fdl>>_package.lst
    if exist xiadmin\xiadmin.rc echo xiadmin\xiadmin.rc>>_package.lst
    if exist xiadmin\*.gif echo xiadmin\*.gif>>_package.lst
    if exist xiadmin\xiadm??.htm echo xiadmin\xiadm??.htm>>_package.lst
    if exist xiadmin\xiadm??.h echo xiadmin\xiadm??.h>>_package.lst
    if exist xiadmin\xiadmin.log echo xiadmin\xiadmin.log>>_package.lst
    if exist xiadmin\prelude.pdl echo xiadmin\prelude.pdl>>_package.lst
    if exist xiadmin\license.gpl echo xiadmin\license.gpl>>_package.lst
    if exist xiadmin\project.pdl echo xiadmin\project.pdl>>_package.lst
    if exist xiadmin\readme.txt echo xiadmin\readme.txt>>_package.lst
    if exist xiadmin\xiadmin.l echo xiadmin\xiadmin.l>>_package.lst
    if exist xiadmin\xiadmin.i echo xiadmin\xiadmin.i>>_package.lst
    if exist xiadmin\xiadmin.d echo xiadmin\xiadmin.d>>_package.lst
    if exist xiadmin\boomake echo xiadmin\boomake>>_package.lst
    if exist xiadmin\boomake.bat echo xiadmin\boomake.bat>>_package.lst
    if exist xiadmin\makefile echo xiadmin\makefile>>_package.lst
    if exist xiadmin\msmake echo xiadmin\msmake>>_package.lst
    echo Building xac_2_5_src.zip...
    dir>nul
    zip -q xac_2_5_src -@<_package.lst
    if errorlevel 1 echo boomake: "zip -q xac_2_5_src -@<_package.lst" failed
    if errorlevel 1 goto err_exception
    del _package.lst
    goto exit

:------------------------   CHECK BINARY FILES EXIST   ------------------------

:a_check_binary_files_exist
    if not exist libxac.lib (
        echo libxac.lib is missing, cannot continue
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
    if not exist xiadmin.c (
        echo xiadmin.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.fdl (
        echo xiadmin.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.rc (
        echo xiadmin.rc is missing, cannot continue
        goto err_exception
    )
    if not exist *.gif (
        echo *.gif is missing, cannot continue
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
    if not exist xiadmin.l (
        echo xiadmin.l is missing, cannot continue
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
    if not exist xiadmin.c (
        echo xiadmin.c is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.fdl (
        echo xiadmin.fdl is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.rc (
        echo xiadmin.rc is missing, cannot continue
        goto err_exception
    )
    if not exist *.gif (
        echo *.gif is missing, cannot continue
        goto err_exception
    )
    if not exist xiadm??.htm (
        echo xiadm??.htm is missing, cannot continue
        goto err_exception
    )
    if not exist xiadm??.h (
        echo xiadm??.h is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.log (
        echo xiadmin.log is missing, cannot continue
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
    if not exist xiadmin.l (
        echo xiadmin.l is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.i (
        echo xiadmin.i is missing, cannot continue
        goto err_exception
    )
    if not exist xiadmin.d (
        echo xiadmin.d is missing, cannot continue
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
    echo Installing Xitami Administration Console into %TARGET%...
    if not exist %TARGET%\lib\nul mkdir %TARGET%\lib\
    dir>nul
    copy/y libxac.lib %TARGET%\lib\>nul
    if errorlevel 1 echo boomake: "copy/y libxac.lib %TARGET%\lib\>nul" failed
    if errorlevel 1 goto err_exception
    if not exist %TARGET%\bin\nul mkdir %TARGET%\bin\
    if not exist %TARGET%\doc\Xitami_Administration_Console\nul mkdir %TARGET%\doc\Xitami_Administration_Console\
    dir>nul
    copy/y readme.txt %TARGET%\doc\Xitami_Administration_Console\>nul
    if errorlevel 1 echo boomake: "copy/y readme.txt %TARGET%\doc\Xitami_Administration_Console\>nul" failed
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
    call wsxrc @xiadmin.rc
    if errorlevel 1 echo boomake: "call wsxrc @xiadmin.rc" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call fdlgen xiadmin
    if errorlevel 1 echo boomake: "call fdlgen xiadmin" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call fmlgen xiadmin
    if errorlevel 1 echo boomake: "call fmlgen xiadmin" failed
    if errorlevel 1 goto err_exception
    dir>nul
    call lr xiadmin.l
    if errorlevel 1 echo boomake: "call lr xiadmin.l" failed
    if errorlevel 1 goto err_exception
    goto exit

:------------------------   REMOVE GENERATED BINARIES   -----------------------

:a_remove_generated_binaries
    if exist libxac.lib del libxac.lib
    if exist xiadmin.obj del xiadmin.obj
    if exist vc60.pdb del vc60.pdb
    goto exit

:------------------------   REMOVE GENERATED SOURCES   ------------------------

:a_remove_generated_sources
    if exist xiadm??.htm del xiadm??.htm
    if exist xiadm??.h del xiadm??.h
    if exist xiadmin.log del xiadmin.log
    if exist xiadmin.i del xiadmin.i
    if exist xiadmin.d del xiadmin.d
    goto exit

:-------------------------   REPORT HELP INFORMATION   ------------------------

:a_report_help_information
    echo boomake - Boom! builder for Xitami Administration Console 2.5
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

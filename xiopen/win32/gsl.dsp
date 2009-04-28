# Microsoft Developer Studio Project File - Name="gsl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=gsl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gsl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gsl.mak" CFG="gsl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gsl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gsl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gsl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\sfl" /I "..\..\smt" /I "..\..\gsl" /I "..\..\studio" /I "..\..\xiadmin" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "DEBUG" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"libgsl.lib"

!ELSEIF  "$(CFG)" == "gsl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gsl___Win32_Debug"
# PROP BASE Intermediate_Dir "gsl___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\sfl" /I "..\..\smt" /I "..\..\gsl" /I "..\..\studio" /I "..\..\xiadmin" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "DEBUG" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"libgsl.lib"

!ENDIF 

# Begin Target

# Name "gsl - Win32 Release"
# Name "gsl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\gsl\ggcode.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggcomm.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggeval.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggfile.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggfunc.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggobjt.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggpars.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\ggstrn.c
# End Source File
# Begin Source File

SOURCE=..\..\gsl\gslgen.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project

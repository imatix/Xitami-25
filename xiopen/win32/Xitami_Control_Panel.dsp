# Microsoft Developer Studio Project File - Name="Xitami Control Panel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Xitami Control Panel - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Xitami_Control_Panel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Xitami_Control_Panel.mak" CFG="Xitami Control Panel - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Xitami Control Panel - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Xitami Control Panel - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Xitami Control Panel - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Xitami Control Panel\Release"
# PROP BASE Intermediate_Dir ".\Xitami Control Panel\Release"
# PROP BASE Target_Dir ".\Xitami Control Panel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ".\Xitami Control Panel"
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /I "..\..\sfl" /I "..\..\smt" /I "..\..\gsl" /I "..\..\studio" /I "..\..\xiadmin" /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mpr.lib /nologo /subsystem:windows /dll /map /machine:I386 /out:"xicpl32.cpl"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "Xitami Control Panel - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Xitami Control Panel\Debug"
# PROP BASE Intermediate_Dir ".\Xitami Control Panel\Debug"
# PROP BASE Target_Dir ".\Xitami Control Panel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ".\Xitami Control Panel"
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "..\..\sfl" /I "..\..\smt" /I "..\..\gsl" /I "..\..\studio" /I "..\..\xiadmin" /D "_WINDOWS" /D "WIN32" /D "_DEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib mpr.lib /nologo /subsystem:windows /dll /machine:I386 /out:"xicpl32.cpl"
# SUBTRACT LINK32 /debug /nodefaultlib

!ENDIF 

# Begin Target

# Name "Xitami Control Panel - Win32 Release"
# Name "Xitami Control Panel - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\xiopen\win32\xicpl32.c
# End Source File
# Begin Source File

SOURCE=..\..\xiopen\win32\xicpl32.def
# End Source File
# Begin Source File

SOURCE=..\..\xiopen\win32\xiwin.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\about.ico
# End Source File
# Begin Source File

SOURCE=.\active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\bug100.bmp
# End Source File
# Begin Source File

SOURCE=.\imatix1.bmp
# End Source File
# Begin Source File

SOURCE=.\off.bmp
# End Source File
# Begin Source File

SOURCE=.\off.ico
# End Source File
# Begin Source File

SOURCE=.\on.bmp
# End Source File
# Begin Source File

SOURCE=.\on.ico
# End Source File
# Begin Source File

SOURCE=.\xitami1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\libsfl.lib
# End Source File
# Begin Source File

SOURCE=.\libstu.lib
# End Source File
# Begin Source File

SOURCE=.\libgsl.lib
# End Source File
# Begin Source File

SOURCE=.\libsmt.lib
# End Source File
# Begin Source File

SOURCE=.\libxac.lib
# End Source File
# End Target
# End Project

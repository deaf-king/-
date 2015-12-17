# Microsoft Developer Studio Project File - Name="Attendance" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Attendance - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Attendance.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Attendance.mak" CFG="Attendance - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Attendance - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Attendance - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Attendance - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Attendance - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Attendance - Win32 Release"
# Name "Attendance - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AttDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Attendance.cpp
# End Source File
# Begin Source File

SOURCE=.\Attendance.rc
# End Source File
# Begin Source File

SOURCE=.\AttendanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AttendanceRS.cpp
# End Source File
# Begin Source File

SOURCE=.\CounterRS.cpp
# End Source File
# Begin Source File

SOURCE=.\Crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\DepartRS.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrandRS.cpp
# End Source File
# Begin Source File

SOURCE=.\LeaveRS.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OvertimeRS.cpp
# End Source File
# Begin Source File

SOURCE=.\Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Page4.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonRS.cpp
# End Source File
# Begin Source File

SOURCE=.\StatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatRS.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Test.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkplanDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AttDlg.h
# End Source File
# Begin Source File

SOURCE=.\Attendance.h
# End Source File
# Begin Source File

SOURCE=.\AttendanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\AttendanceRS.h
# End Source File
# Begin Source File

SOURCE=.\CounterRS.h
# End Source File
# Begin Source File

SOURCE=.\Crypt.h
# End Source File
# Begin Source File

SOURCE=.\DepartRS.h
# End Source File
# Begin Source File

SOURCE=.\ErrandRS.h
# End Source File
# Begin Source File

SOURCE=.\LeaveRS.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\OvertimeRS.h
# End Source File
# Begin Source File

SOURCE=.\Page1.h
# End Source File
# Begin Source File

SOURCE=.\Page2.h
# End Source File
# Begin Source File

SOURCE=.\Page3.h
# End Source File
# Begin Source File

SOURCE=.\Page4.h
# End Source File
# Begin Source File

SOURCE=.\PersonRS.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StatDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatRS.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Test.h
# End Source File
# Begin Source File

SOURCE=.\WorkplanDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\attendance.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Attendance.ico
# End Source File
# Begin Source File

SOURCE=.\res\Attendance.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="PhotoThing" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PhotoThing - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PhotoThing.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PhotoThing.mak" CFG="PhotoThing - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PhotoThing - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PhotoThing - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PhotoThing - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "C:\Temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PhotoThing - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "C:\Temp"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "STRICT" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PhotoThing - Win32 Release"
# Name "PhotoThing - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\PhotoThing.cpp
# End Source File
# Begin Source File

SOURCE=.\PhotoThing.rc
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Collect.h
# End Source File
# Begin Source File

SOURCE=.\DarkCommandBar.h
# End Source File
# Begin Source File

SOURCE=.\FadeStateButton.h
# End Source File
# Begin Source File

SOURCE=.\ImageHelpers.h
# End Source File
# Begin Source File

SOURCE=.\ImageListView.h
# End Source File
# Begin Source File

SOURCE=.\InfoView.h
# End Source File
# Begin Source File

SOURCE=.\ListPanelView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MiscControls.h
# End Source File
# Begin Source File

SOURCE=.\NavPanelView.h
# End Source File
# Begin Source File

SOURCE=.\PhotoBrowserView.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchView.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TableOfContentsView.h
# End Source File
# Begin Source File

SOURCE=.\TreeView.h
# End Source File
# Begin Source File

SOURCE=.\VistaLayer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\addkeyword.png
# End Source File
# Begin Source File

SOURCE=.\res\bar_chevron.png
# End Source File
# Begin Source File

SOURCE=.\res\bar_help.png
# End Source File
# Begin Source File

SOURCE=.\res\bar_navleft.png
# End Source File
# Begin Source File

SOURCE=.\res\bar_navright.png
# End Source File
# Begin Source File

SOURCE=.\res\barbutton_left.png
# End Source File
# Begin Source File

SOURCE=.\res\barbutton_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\barbutton_right.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_burn.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_edit.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_email.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_file.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_info.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_movie.png
# End Source File
# Begin Source File

SOURCE=.\res\baritem_print.png
# End Source File
# Begin Source File

SOURCE=.\res\empty1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\infoshadow.png
# End Source File
# Begin Source File

SOURCE=.\res\keywords.bmp
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_back.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_delete.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_forward.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_options.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_reset.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_rotleft.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_rotright.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_run.png
# End Source File
# Begin Source File

SOURCE=.\res\navbuttons_zoom.png
# End Source File
# Begin Source File

SOURCE=.\res\navpanel_left.png
# End Source File
# Begin Source File

SOURCE=.\res\navpanel_middle.png
# End Source File
# Begin Source File

SOURCE=.\res\navpanel_right.png
# End Source File
# Begin Source File

SOURCE=.\res\navpanel_side.bmp
# End Source File
# Begin Source File

SOURCE=.\res\navpanel_side.png
# End Source File
# Begin Source File

SOURCE=.\res\nosel.png
# End Source File
# Begin Source File

SOURCE=.\res\options.png
# End Source File
# Begin Source File

SOURCE=.\res\PhotoThing.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\res\PhotoThing.ico
# End Source File
# Begin Source File

SOURCE=.\res\search.bmp
# End Source File
# Begin Source File

SOURCE=.\res\searchbutton.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeimages.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeimages_mask.bmp
# End Source File
# End Group
# End Target
# End Project


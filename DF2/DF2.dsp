# Microsoft Developer Studio Project File - Name="DF2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DF2 - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "DF2.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "DF2.mak" CFG="DF2 - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "DF2 - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "DF2 - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DF2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DF2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DF2 - Win32 Release"
# Name "DF2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Java3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Java3DModel.cpp
# End Source File
# Begin Source File

SOURCE=.\Java3DModelGround.cpp
# End Source File
# Begin Source File

SOURCE=.\Java3DModelSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\Java3DWorld.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaApplet.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaDF2.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaDF2Fractal.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaDF2Models.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaDF2Panel.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaRender.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaRenderAbstract.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaRenderBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaRenderGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaRenderMemory.cpp

!IF  "$(CFG)" == "DF2 - Win32 Release"

# ADD CPP /GB /FAcs

!ELSEIF  "$(CFG)" == "DF2 - Win32 Debug"

# ADD CPP /FAcs

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\JavaRenderMemorySSE2.cpp
# End Source File
# Begin Source File

SOURCE=.\JavaRenderMemorySSE2asm.asm

!IF  "$(CFG)" == "DF2 - Win32 Release"

# Begin Custom Build
InputDir=.
TargetDir=.\Release
InputPath=.\JavaRenderMemorySSE2asm.asm
InputName=JavaRenderMemorySSE2asm

"$(TargetDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	@rem $(InputDir)\..\masm\ml /c /Fo$(TargetDir)\$(InputName).obj /Fl$(TargetDir)\$(InputName).lst $(InputPath) 
	\BIN\DEV\masm7\ml /c /Fo$(TargetDir)\$(InputName).obj /Fl$(TargetDir)\$(InputName).lst $(InputPath) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DF2 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\JavaRenderTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\Log.cpp
# End Source File
# Begin Source File

SOURCE=.\Perf.cpp
# End Source File
# Begin Source File

SOURCE=.\winmain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Source File

SOURCE=.\bench.txt
# End Source File
# End Target
# End Project

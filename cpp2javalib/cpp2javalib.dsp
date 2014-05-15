# Microsoft Developer Studio Project File - Name="cpp2javalib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cpp2javalib - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "cpp2javalib.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "cpp2javalib.mak" CFG="cpp2javalib - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "cpp2javalib - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "cpp2javalib - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cpp2javalib - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "cpp2javalib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "cpp2javalib - Win32 Release"
# Name "cpp2javalib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cpp2java.AppletViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\LIBDEBUG.C
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cpp2java.AppletViewer.h
# End Source File
# Begin Source File

SOURCE=.\cpp2javalib.h
# End Source File
# Begin Source File

SOURCE=.\cpp2javalibdef.h
# End Source File
# Begin Source File

SOURCE=.\cpp2javalibimp.h
# End Source File
# Begin Source File

SOURCE=.\java.applet.h
# End Source File
# Begin Source File

SOURCE=.\java.awt.event.h
# End Source File
# Begin Source File

SOURCE=.\java.awt.h
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.h
# End Source File
# Begin Source File

SOURCE=.\java.io.h
# End Source File
# Begin Source File

SOURCE=.\java.lang.h
# End Source File
# Begin Source File

SOURCE=.\java.net.h
# End Source File
# Begin Source File

SOURCE=.\java.util.h
# End Source File
# Begin Source File

SOURCE=.\LIBDEBUG.H
# End Source File
# End Group
# Begin Group "applet"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\applet\Applet.cpp
# End Source File
# Begin Source File

SOURCE=.\java.applet.Applet
# End Source File
# End Group
# Begin Group "awt"

# PROP Default_Filter "cpp;h"
# Begin Group "event"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\java.awt.event.KeyEvent
# End Source File
# Begin Source File

SOURCE=.\java.awt.event.KeyListener
# End Source File
# Begin Source File

SOURCE=.\java.awt.event.MouseEvent
# End Source File
# Begin Source File

SOURCE=.\java.awt.event.MouseListener
# End Source File
# Begin Source File

SOURCE=.\java.awt.event.MouseMotionListener
# End Source File
# Begin Source File

SOURCE=.\awt\event\KeyEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\event\MouseEvent.cpp
# End Source File
# End Group
# Begin Group "image"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\awt\image\ColorModel.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\image\DirectColorModel.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\image\IndexColorModel.cpp
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.ColorModel
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.DirectColorModel
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.ImageConsumer
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.ImageObserver
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.ImageProducer
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.IndexColorModel
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.MemoryImageSource
# End Source File
# Begin Source File

SOURCE=.\java.awt.image.PixelGrabber
# End Source File
# Begin Source File

SOURCE=.\awt\image\MemoryImageSource.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\image\PixelGrabber.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\awt\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\Component.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\Font.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\FontMetrics.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\Graphics.cpp
# End Source File
# Begin Source File

SOURCE=.\awt\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\java.awt.Color
# End Source File
# Begin Source File

SOURCE=.\java.awt.Component
# End Source File
# Begin Source File

SOURCE=.\java.awt.Font
# End Source File
# Begin Source File

SOURCE=.\java.awt.FontMetrics
# End Source File
# Begin Source File

SOURCE=.\java.awt.Graphics
# End Source File
# Begin Source File

SOURCE=.\java.awt.Image
# End Source File
# Begin Source File

SOURCE=.\java.awt.Rectangle
# End Source File
# Begin Source File

SOURCE=.\awt\Rectangle.cpp
# End Source File
# End Group
# Begin Group "io"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\java.io.PrintStream
# End Source File
# Begin Source File

SOURCE=.\io\PrintStream.cpp
# End Source File
# End Group
# Begin Group "lang"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\lang\Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\Integer.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\InterruptedException.cpp
# End Source File
# Begin Source File

SOURCE=.\java.lang.Exception
# End Source File
# Begin Source File

SOURCE=.\java.lang.Integer
# End Source File
# Begin Source File

SOURCE=.\java.lang.InterruptedException
# End Source File
# Begin Source File

SOURCE=.\java.lang.Math
# End Source File
# Begin Source File

SOURCE=.\java.lang.Object
# End Source File
# Begin Source File

SOURCE=.\java.lang.Runnable
# End Source File
# Begin Source File

SOURCE=.\java.lang.Runtime
# End Source File
# Begin Source File

SOURCE=.\java.lang.String
# End Source File
# Begin Source File

SOURCE=.\java.lang.System
# End Source File
# Begin Source File

SOURCE=.\java.lang.Thread
# End Source File
# Begin Source File

SOURCE=.\java.lang.Throwable
# End Source File
# Begin Source File

SOURCE=.\lang\Math.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\Runtime.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\String.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\System.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\lang\Throwable.cpp
# End Source File
# End Group
# Begin Group "util"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\java.util.Random
# End Source File
# Begin Source File

SOURCE=.\util\Random.cpp
# End Source File
# End Group
# Begin Group "net"

# PROP Default_Filter "cpp;h"
# Begin Source File

SOURCE=.\java.net.URL
# End Source File
# Begin Source File

SOURCE=.\net\URL.cpp
# End Source File
# End Group
# End Target
# End Project

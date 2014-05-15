/**
 * winmain.cpp : Win32 Template
 * Copyright (C) 1996- T.Matsushima All rights reserved.
 *
 * @since   1.0 1996/08/20 matsushima Prototype
 * @author  1.0 2006/01/24 matsushima DF2
 * @version $Id: winmain.cpp,v 1.8 2008/03/06 16:42:46 matsushima Exp $
 * 
 * $Log: winmain.cpp,v $
 * Revision 1.8  2008/03/06 16:42:46  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.7  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.6  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.5  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.4  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */

#define _IS_H_
#include "JavaDF2.cpp"
#include "../cpp2javalib/AppletViewer.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    AppletViewer a(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &JavaDF2(), 640, 480);
/*    JavaDF2* applet = new JavaDF2();
    AppletViewer a(hInstance, hPrevInstance, lpCmdLine, nCmdShow, applet, 640, 480);
    delete applet;
*/    return 0;
}

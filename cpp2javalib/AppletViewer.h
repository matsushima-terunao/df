/**
 * @file
 *
 * $Id: cpp2java.AppletViewer.h,v 1.1.1.1 2006/08/17 20:26:00 matsushima Exp $
 *
 * cpp2java.AppletViewer.h : 
 *
 * @author  0.0 2005/03/24 matsushima h2java
 * @author  0.1 2006/07/19 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/24 matsushima h2java
 *
 * $Log: cpp2java.AppletViewer.h,v $
 * Revision 1.1.1.1  2006/08/17 20:26:00  matsushima
 * new
 *
 */

#ifndef _CPP2JAVA_APPLETVIEWER_H_
#define _CPP2JAVA_APPLETVIEWER_H_

#include "cpp2javalib.h"
#include "java/applet/all"
#include <windows.h>

/*------------------------------------------------------------*/

class AppletViewer
{
public:
    Applet* applet;
public:
    AppletViewer(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow,
        Applet* applet,
        int width,
        int height);
};

/*------------------------------------------------------------*/

#endif /* #ifndef _CPP2JAVA_APPLETVIEWER_H_ */

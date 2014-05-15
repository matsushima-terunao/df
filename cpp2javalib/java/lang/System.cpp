/**
 * @file
 *
 * $Id: System.cpp,v 1.6 2007/11/30 22:42:27 matsushima Exp $
 *
 * System.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima
 * @author  0.1 2006/07/13 matsushima cpp2javalib
 * @version $Revision: 1.6 $
 * @since   0.0 2005/03/19 matsushima
 *
 * $Log: System.cpp,v $
 * Revision 1.6  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.5  2007/05/14 18:47:46  matsushima
 * no message
 *
 * Revision 1.4  2007/05/10 22:29:47  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.3  2007/05/09 12:45:23  matsushima
 * no message
 *
 * Revision 1.2  2007/05/08 15:24:46  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include <windows.h>

//#define QPC

#ifdef QPC
static __int64 freq;
#endif

PrintStream System::out;

System::System()
{
#ifdef QPC
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
#endif
}

void System::runFinalization()
{
}

void System::gc()
{
}

long System::currentTimeMillis()
{
#ifdef QPC
    __int64 count;
    QueryPerformanceCounter((LARGE_INTEGER*)&count);
    return (long)(1000 * count / freq);
#else
    return GetTickCount();
#endif
}

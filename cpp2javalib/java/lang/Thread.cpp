/**
 * @file
 *
 * $Id: Thread.cpp,v 1.6 2008/03/11 16:57:48 matsushima Exp $
 *
 * Thread.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.6 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Thread.cpp,v $
 * Revision 1.6  2008/03/11 16:57:48  matsushima
 * スレッド同期 Object.wait(), notify()
 *
 * Revision 1.5  2007/11/30 22:42:27  matsushima
 * 再登録
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
#include <process.h>
#include <windows.h>

int thread_cnt = 0;

/*------------------------------------------------------------*/

Thread::Thread(Runnable* target)
{
    this->target = target;
}

static void start_func(void* param)
{
    ++ thread_cnt;
    Runnable* target = (Runnable*)param;
    target->run();
    -- thread_cnt;
#ifdef _DEBUG
    OutputDebugString("--thread\n");
#endif
}

void Thread::start()
{
    _beginthread(start_func, 0, target);
}

void Thread::run()
{
}

void Thread::sleep(long millis)
{
    //throw InterruptedException(C2J_THROWMSG("java.lang.Thread.sleep"));
    Sleep(millis);
}

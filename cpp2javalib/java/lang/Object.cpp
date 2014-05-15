/**
 * @file
 *
 * $Id: Object.cpp,v 1.4 2008/03/11 16:57:48 matsushima Exp $
 *
 * Object.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.4 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Object.cpp,v $
 * Revision 1.4  2008/03/11 16:57:48  matsushima
 * ÉXÉåÉbÉhìØä˙ Object.wait(), notify()
 *
 * Revision 1.3  2007/11/30 22:42:27  matsushima
 * çƒìoò^
 *
 * Revision 1.2  2007/05/14 13:38:09  matsushima
 * Java/C++ ã§í âª
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include <windows.h>

/*------------------------------------------------------------*/

OBJSTACK Object::objstack;

Object::Object()
{
    event = null;
    refcnt = 0;
}

Object::~Object()
{
    term_event();
}

String Object::toString()
{
    return String("Object");
}

void Object::init_event(boolean initial)
{
    event = (void*)CreateEvent(NULL, FALSE, initial ? TRUE : FALSE, NULL);
    objstack.stack.push_back(this);
}

void Object::term_event()
{
    if (NULL != event)
    {
        HANDLE e = (HANDLE)event;
        event = NULL;
SetEvent(e);
        CloseHandle(e);
        objstack.stack.remove(this);
    }
}

void Object::term_events()
{
    OBJSTACK::STACK::iterator it;
    for (it = objstack.stack.begin(); it != objstack.stack.end(); )
    {
        Object* o = (Object*)*it;
        ++ it;
        o->term_event();
    }
}

void Object::wait()
{
    DWORD result = WaitForSingleObject((HANDLE)event, INFINITE);
    if (null == event)
    {
        throw InterruptedException("wait()");
    }
    else
    if ((WAIT_OBJECT_0 != result) && (WAIT_TIMEOUT != result))
    {
        throw InterruptedException("wait()");
    }
}

void Object::notify()
{
    SetEvent((HANDLE)event);
}

Object::operator const char*()
{
	return toString();
}

String Object::operator+(const char* value)
{
    String s = *this;
    s += value;
    return s;
}

String Object::operator+(int value)
{
    char buf[32];
    sprintf(buf, "%ld", value);
    return *this + buf;
}

String Object::operator+(long value)
{
    char buf[32];
    sprintf(buf, "%ld", value);
    return *this + buf;
}

String Object::operator+(unsigned short value)
{
	char buf[3] = "  ";
	buf[0] = value & 0xff;
	buf[1] = value >> 8;
	return *this + buf;
}

String Object::operator+(double value)
{
    char buf[32];
    sprintf(buf, "%lf", value);
    return *this + buf;
}

String Object::operator+(bool value)
{
	return operator+(value ? "true" : "false");
}

// "abc" + s
String operator+(const char* str, Object& value)
{
	return String(str) + value.toString();
}

bool Object::refer()
{
    ++ refcnt;
    return true;
}

bool Object::release()
{
    -- refcnt;
    if (0 == refcnt)
    {
        return true;
    }
    return false;
}

void Object::outref(const char* m)
{
///System::out.print(m);
///System::out.print(":");
///System::out.println(refcnt);
}

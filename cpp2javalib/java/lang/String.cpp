/**
 * @file
 *
 * $Id: String.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * String.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: String.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"

/*------------------------------------------------------------*/

String::String()
{
}

String::String(const char* original)
{
    value = original;
}

String String::toString()
{
	return *this;
}

int String::length()
{
    return value.length();
}

unsigned short String::charAt(int index)
{
    return value[index];
}

String String::substring(int beginIndex)
{
    return String(value.substr(beginIndex, value.npos).c_str());
}

String String::substring(int beginIndex, int endIndex)
{
    return String(value.substr(beginIndex, endIndex - beginIndex).c_str());
}

String::String(long value)
{
    char buf[32];
    sprintf(buf, "%ld", value);
    this->value = buf;
}

String& String::operator+=(const char* value)
{
    this->value += value;
    return *this;
}

String::operator const char*()
{
    return value.c_str();
}

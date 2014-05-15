/**
 * @file
 *
 * $Id: Throwable.cpp,v 1.2 2008/03/11 16:57:48 matsushima Exp $
 *
 * Throwable.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/27 matsushima cpp2javalib
 * @version $Revision: 1.2 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Throwable.cpp,v $
 * Revision 1.2  2008/03/11 16:57:48  matsushima
 * ƒXƒŒƒbƒh“¯Šú Object.wait(), notify()
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"

/*------------------------------------------------------------*/

Throwable::Throwable()
{
}

Throwable::Throwable(const char* message)
{
    this->message = message;
}

String& Throwable::getMessage()
{
    return message;
}

void Throwable::printStackTrace()
{
    System::out.println(message);
}

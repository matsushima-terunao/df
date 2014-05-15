/**
 * @file
 *
 * $Id: URL.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * URL : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/26 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: URL.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "URL"

/*------------------------------------------------------------*/

URL::URL()
{
}

URL::URL(const char* spec)
{
    url = spec;
}

URL::~URL()
{
}

String URL::toString()
{
    return url;
}

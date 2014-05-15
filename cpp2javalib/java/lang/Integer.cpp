/**
 * @file
 *
 * $Id: Integer.cpp,v 1.5 2007/11/30 22:42:27 matsushima Exp $
 *
 * Integer.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.5 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Integer.cpp,v $
 * Revision 1.5  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.4  2007/05/11 14:37:31  matsushima
 * no message
 *
 * Revision 1.3  2007/05/08 15:24:46  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.2  2006/08/18 11:39:56  matsushima
 * no message
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"

/*------------------------------------------------------------*/

Integer::Integer(int value)
{
    this->value = value;
}

String Integer::toString()
{
	char buf[32];
	sprintf(buf, "%d", value);
    return buf;
}

String Integer::toHexString(int i)
{
    char buf[32];
    sprintf(buf, "%x", i);
    return String(buf);
}

Integer::operator const int()
{
    return value;
}

/**
 * @file
 *
 * $Id: Math.cpp,v 1.5 2007/11/30 22:42:27 matsushima Exp $
 *
 * Math.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/21 matsushima cpp2javalib
 * @version $Revision: 1.5 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Math.cpp,v $
 * Revision 1.5  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.4  2007/05/10 22:29:47  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.3  2007/05/09 12:45:23  matsushima
 * no message
 *
 * Revision 1.2  2007/05/07 21:39:52  matsushima
 * staticメンバアクセス :: -> .
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include <math.h>

/*------------------------------------------------------------*/

const double Math::PI = 3.141592653589793;

double Math::sin(double a)
{
    return ::sin(a);
}

double Math::cos(double a)
{
    return ::cos(a);
}

double Math::tan(double a)
{
    return ::tan(a);
}

double Math::sqrt(double a)
{
    return ::sqrt(a);
}

double Math::pow(double a, double b)
{
    return ::pow(a, b);
}

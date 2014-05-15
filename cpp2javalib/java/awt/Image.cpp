/**
 * @file
 *
 * $Id: Image.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * Image.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Image.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Image_"
#include <windows.h>

/*------------------------------------------------------------*/

Image::Image()
{
    _hdc = NULL;
    graphics = NULL;
}

Image::~Image()
{
}

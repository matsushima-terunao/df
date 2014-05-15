/**
 * @file
 *
 * $Id: DirectColorModel.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * DirectColorModel.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/25 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: DirectColorModel.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "DirectColorModel"

/*------------------------------------------------------------*/

DirectColorModel::DirectColorModel(int bits, int rmask, int gmask, int bmask)
    : ColorModel(bits)
{
    this->rmask = rmask;
    this->gmask = gmask;
    this->bmask = bmask;
}

DirectColorModel::~DirectColorModel()
{
}

/**
 * @file
 *
 * $Id: ColorModel.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * ColorModel.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/25 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: ColorModel.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "ColorModel"

/*------------------------------------------------------------*/

ColorModel::ColorModel(int bits)
{
    this->bits = bits;
}

ColorModel::~ColorModel()
{
}

int ColorModel::getPixelSize()
{
    return bits;
}

int ColorModel::getRGB(int pixel)
{
    return pixel;
}

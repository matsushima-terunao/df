/**
 * @file
 *
 * $Id: IndexColorModel.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * IndexColorModel.cpp : 
 *
 * @author  0.0 2006/07/26 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2006/07/26 matsushima cpp2javalib
 *
 * $Log: IndexColorModel.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "IndexColorModel"

/*------------------------------------------------------------*/

IndexColorModel::IndexColorModel(int bits, int size, int* r, int* g, int* b)
    : ColorModel(bits)
{
    _ASSERTE(this->size = size);
    _ASSERTE(this->r = new int[size]);
    _ASSERTE(this->g = new int[size]);
    _ASSERTE(this->b = new int[size]);
    memcpy(this->r, r, size * sizeof(int));
    memcpy(this->g, g, size * sizeof(int));
    memcpy(this->b, b, size * sizeof(int));
}

IndexColorModel::~IndexColorModel()
{
    delete[] r;
    delete[] g;
    delete[] b;
}

int IndexColorModel::getRGB(int pixel)
{
    _ASSERTE((pixel < size));
    return (r[pixel] << 16) | (g[pixel] << 8) | b[pixel];
}

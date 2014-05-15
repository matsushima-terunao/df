/**
 * @file
 *
 * $Id: Rectangle.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * Rectangle.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/23 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Rectangle.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Rectangle"

typedef class Rectangle _Rectangle; // WINGDIAPI BOOL WINAPI Rectangle(HDC, int, int, int, int); ‚Æd‚È‚é‚½‚ß

/*------------------------------------------------------------*/

Rectangle::Rectangle()
{
    this->x = this->y = this->width = this->height = 0;
}

Rectangle::Rectangle(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Rectangle::~Rectangle()
{
}

double Rectangle::getWidth()
{
    return width;
}

double Rectangle::getHeight()
{
    return height;
}

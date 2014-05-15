/**
 * @file
 *
 * $Id: MemoryImageSource.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * MemoryImageSource.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/25 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: MemoryImageSource.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "MemoryImageSource"
#include "ColorModel"
#include "ImageConsumer"

/*------------------------------------------------------------*/

MemoryImageSource::MemoryImageSource(int w, int h, ColorModel* cm, int* pix, int off, int scan)
{
    this->width = w;
    this->height = h;
    this->pix = pix;
    this->animated = false;
    this->consumer = NULL;
}

void MemoryImageSource::setAnimated(bool animated)
{
    this->animated = animated;
}

void MemoryImageSource::setFullBufferUpdates(bool fullbuffers)
{
}

void MemoryImageSource::newPixels()
{
    if (false != animated)
    {
        if (NULL != consumer)
        {
            // java.awt.Component.ProducedImage.setPixels()
            // java.awt.Component.repaint()
            // java.awt.Component.update()
            // java.awt.Component.paint()
            // java.awt.Component.ComponentGraphics.drawImage(java.awt.Component.ProducedImage)
            // java.awt.Component.ProducedImage.startProduction(java.awt.Component.ComponentGraphics)
            // java.awt.Component.ComponentGraphics.setPixels()
            // -> draw
            consumer->setPixels(0, 0, width, height, NULL, pix, 0, width);
        }
    }
}

void MemoryImageSource::addConsumer(ImageConsumer* ic)
{
    this->consumer = ic;
}

void MemoryImageSource::startProduction(ImageConsumer* ic)
{
    //addConsumer(ic);
    ic->setPixels(0, 0, width, height, NULL, pix, 0, width);
}

/**
 * @file
 *
 * $Id: PixelGrabber.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * PixelGrabber : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/26 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: PixelGrabber.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "PixelGrabber"
#include "../Image_"
#include "ColorModel"
#include "ImageObserver"
#include "ImageProducer"
#include <windows.h>

/*------------------------------------------------------------*/

PixelGrabber::PixelGrabber(Image* img, int x, int y, int w, int h, int* pix, int off, int scansize)
{
    this->img = img;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->pix = pix;
    this->off = off;
    this->scansize = scansize;
}

PixelGrabber::~PixelGrabber()
{
}

bool PixelGrabber::grabPixels()
{
    _ASSERTE(img->getSource());
    img->getSource()->startProduction(this);
    return true;
}

int PixelGrabber::getStatus()
{
    return ImageObserver::ALLBITS;
}

void PixelGrabber::setPixels(int x, int y, int w, int h, ColorModel* model, unsigned char* pixels, int off, int scansize)
{
    _ASSERTE((0 == x) && (0 == y));
    int dir = 1;
    if (h < 0)
    {
        h = -h;
        off = scansize * (h - 1) - off;
        dir = -1;
    }
    int bits = model->getPixelSize();
    int bytes = (bits + 7) / 8;
    int j, i, k, d, s;
    for (j = y; j < y + h; ++ j)
    {
        d = this->off + j * this->scansize;
        s = off + j * scansize * dir;
        for (i = x; i < x + w; ++ i, ++ d)
        {
            int pixel = 0;
            for (k = 0; k < bytes; ++ k, ++ s)
            {
                pixel = (pixel << 8) | pixels[s];
            }
            this->pix[d] = model->getRGB(pixel);
        }
    }
}

void PixelGrabber::setPixels(int x, int y, int w, int h, ColorModel* model, int* pixels, int off, int scansize)
{
    setPixels(x, y, w, h, model, (unsigned char*)pixels, off * sizeof(int), scansize * sizeof(int));
}

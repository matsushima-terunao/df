/*
 * $Id: JavaRenderTexture.cpp,v 1.16 2008/03/12 16:30:47 matsushima Exp $
 */

/*J*
package javarender;

import java.awt.Component;
import java.awt.Image;
import java.awt.image.ImageObserver;
import java.awt.image.PixelGrabber;

import commons.JavaObject;
import commons.Log;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/awt/Component"
#include "../cpp2javalib/java/awt/Image"
#include "../cpp2javalib/java/awt/image/ImageObserver"
#include "../cpp2javalib/java/awt/image/PixelGrabber"

#else

#define _IS_H_ // cpp
#include "JavaRenderTexture.cpp"
#include "Log.cpp"
#undef _IS_H_

#endif
/**/

/**
 * ポリゴン塗りつぶし用テクスチャ、文字列描画用フォント。
 * 
 * @since   1.0 2005/03/27 matsushima
 * @author  1.0 2005/03/27 matsushima
 * @version $Id: JavaRenderTexture.cpp,v 1.16 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: JavaRenderTexture.cpp,v $
 * Revision 1.16  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.15  2008/03/06 16:42:46  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.14  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.13  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.12  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.11  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.10  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.9  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.8  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.7  2007/05/14 13:38:21  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.5  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*
public class JavaRenderTexture extends JavaObject
{
/*C*/
#ifdef _IS_H_
class JavaRenderTexture
{
/**/
/*J*
    // Text texture
    public int pix[];               // image bitmap
    public int width, height;     // image width
    public int ptx[], pty[];         // vertices
    public int font_w, font_h;    // char width in image
    public int font_ws[], font_hs[]; // each char width
    public int font_w_max;        // maximum char width
/*C*/
    // Text texture
public:
    int *pix;               // image bitmap
    int  width, height;     // image width
    int *ptx, *pty;         // vertices
    int  font_w, font_h;    // char width in image
    int *font_ws, *font_hs; // each char width
    int  font_w_max;        // maximum char width
#endif
/**/

/*J*
    public JavaRenderTexture(int[] pix, int width, int height, int[] ptx, int[] pty) {
/*C*/
#ifdef _IS_H_
public:
    JavaRenderTexture(int* pix, int width, int height, int* ptx, int* pty);
#else
    JavaRenderTexture::JavaRenderTexture(int* pix, int width, int height, int* ptx, int* pty) {
/**/
        this->pix = pix;
        this->width = width;
        this->height = height;
        this->ptx = ptx;
        this->pty = pty;
        this->font_ws = null;
        this->font_hs = null;
    }
/*C*/
#endif
/**/

/*J*
    public JavaRenderTexture(int width, int height, int[] ptx, int[] pty) {
/*C*/
#ifdef _IS_H_
public:
    JavaRenderTexture(int width, int height, int* ptx, int* pty);
#else
    JavaRenderTexture::JavaRenderTexture(int width, int height, int* ptx, int* pty) {
/**/
        this->pix = new int[width * height];
        this->width = width;
        this->height = height;
        this->ptx = ptx;
        this->pty = pty;
        this->font_ws = null;
        this->font_hs = null;
    }
/*C*/
#endif
/**/

/*J*
    public JavaRenderTexture(Component component, int font_w, int font_h, Image font_image) {
/*C*/
#ifdef _IS_H_
public:
    JavaRenderTexture(Component* component, int font_w, int font_h, Image* font_image);
#else
    JavaRenderTexture::JavaRenderTexture(Component* component, int font_w, int font_h, Image* font_image) {
/**/
        this->ptx = null;
        this->pty = null;
        this->font_w = font_w;
        this->font_h = font_h;
        try
        {
            while (false == _R(component).prepareImage(font_image, component))
            {
                Thread::sleep(100);
            }
            width = font_image->getWidth(component);
            height = font_image->getHeight(component);
            pix = new int[width * height];
            PixelGrabber pg/*J* = new PixelGrabber/**/(
                font_image, 0, 0, width, height,
                pix, 0, width);
            pg.grabPixels();
            if (0 != (pg.getStatus() & ImageObserver::ABORT))
            {
            }
            font_image->flush();
            font_ws = new int[16 * 6];
            font_hs = new int[16 * 6];
            font_w_max = 0;
            int c;
            for (c = 0; c < 16 * 6; ++ c)
            {
                int w = 0, h = 0;
                int px0 = (c % 16) * font_w;
                int py0 = (c / 16) * font_h;
                int p = px0 + py0 * width;
                int px, py;
                for (py = 0; py < font_h - 0; ++ py, p += width - (font_w - 1))
                {
                for (px = 0; px < font_w - 1; ++ px, ++ p)
                    {
                        pix[p] = ((-1 == pix[p]) || (0x00ffffff == pix[p]))
                            ? 0 : 256 - (pix[p] & 0xff);
                        if (0 != pix[p])
                        {
                            if (w < px)
                            {
                                w = px;
                            }
                            if (h < py)
                            {
                                h = py;
                            }
                        }
                    }
                }
                if (0 == w)
                {
                    w = font_w / 2;
                }
                font_ws[c] = w;
                font_hs[c] = h;
                if (font_w_max < font_ws[c])
                {
                    font_w_max = font_ws[c];
                }
            }
        }
        catch (InterruptedException e)
        {
Log::out("JavaRenderTexture.JavaRenderTexture() : > InterruptedException");
Log::out(e.getMessage());
        }
    }
/*C*/
#endif
/**/

/*C*/
#ifdef _IS_H_
public:
    virtual ~JavaRenderTexture();
#else
    JavaRenderTexture::~JavaRenderTexture() {
        if (null != pix)
        {
            delete[] pix;
        }
        if (null != ptx)
        {
            delete[] ptx;
            delete[] pty;
        }
        if (null != font_ws)
        {
            delete[] font_ws;
            delete[] font_hs;
        }
    }
#endif
/**/
/*J*
}
/*C*/
#ifdef _IS_H_
};
#endif
/**/

/*
 * $Id: JavaRenderAbstract.cpp,v 1.7 2008/03/12 16:30:47 matsushima Exp $
 */

/*J*
package javarender;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.image.ImageObserver;

import commons.JavaObject;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/awt/Graphics"
#include "../cpp2javalib/java/awt/Rectangle"
#include "../cpp2javalib/java/awt/image/ImageObserver"
#include "JavaRenderTexture.cpp"
#include "JavaRender.cpp"

#else // cpp

#define _IS_H_
#include "JavaRenderAbstract.cpp"
#undef _IS_H_

#endif
/**/

/**
 * レンダの基本クラス。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: JavaRenderAbstract.cpp,v 1.7 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: JavaRenderAbstract.cpp,v $
 * Revision 1.7  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.6  2008/03/06 16:42:45  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.5  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.4  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.3  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.2  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.1  2007/05/23 18:30:22  matsushima
 * JavaRender カプセル化
 *
 * Revision 1.7  2007/05/14 13:38:20  matsushima
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
public abstract class JavaRenderAbstract extends JavaObject implements JavaRender
{
/*C*/
#ifdef _IS_H_
class JavaRenderAbstract : public JavaRender
{
/**/
/*J*
    protected int width, height;
/*C*/
protected:
    int width, height;
#endif
/**/
/*J*
    public JavaRenderAbstract(int width, int height) {
/*C*/
#ifdef _IS_H_
public:
    JavaRenderAbstract(int width, int height);
#else
    JavaRenderAbstract::JavaRenderAbstract(int width, int height) {
#define this (*this)
/**/
        this.width = width;
        this.height = height;
    }
/*C*/
#endif
/**/

/*C*/
#ifdef _IS_H_
public:
    virtual ~JavaRenderAbstract();
#else
    JavaRenderAbstract::~JavaRenderAbstract() {
    }
#endif
/**/

/*J*
    public abstract void clear();
/*C*/
#ifdef _IS_H_
public:
    virtual void clear() = 0;
/**/
/*J*
    public abstract void repaint();
/*C*/
public:
    virtual void repaint() = 0;
/**/
/*J*
    public abstract void paint(Graphics graphics, ImageObserver observer);
/*C*/
public:
    virtual void paint(Graphics* graphics, ImageObserver* observer) = 0;
/**/
/*J*
    public abstract int getPixel(int x, int y);
/*C*/
public:
    virtual int getPixel(int x, int y) = 0;
/**/
/*J*
    public abstract void setPixel(int color, int x, int y);
/*C*/
public:
    virtual void setPixel(int color, int x, int y) = 0;
/**/
/*J*
    public abstract void drawLine(int color, int x1, int y1, int x2, int y2);
/*C*/
public:
    virtual void drawLine(int color, int x1, int y1, int x2, int y2) = 0;
/**/
/*J*
    public abstract void drawPolygon(int[] px, int[] py, int[] pc, int cnt);
/*C*/
public:
    virtual void drawPolygon(int* px, int* py, int* pc, int cnt) = 0;
/**/
/*J*
    public abstract void drawPolyline(int[] px, int[] py, int[] pc, int cnt);
/*C*/
public:
    virtual void drawPolyline(int* px, int* py, int* pc, int cnt) = 0;
/**/
/*J*
    public abstract void fillPolygon(int[] px, int[] py, int[] pc, JavaRenderTexture render, int[] ptx, int[] pty, int cnt);
/*C*/
public:
    virtual void fillPolygon(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) = 0;
/**/
/*J*
    public abstract void fillPolygonAlpha(int[] px, int[] py, int[] pc, JavaRenderTexture render, int[] ptx, int[] pty, int cnt);
/*C*/
public:
    virtual void fillPolygonAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) = 0;
/**/
/*J*
    public abstract void fillPolygonGouraud(int[] px, int[] py, int[] pc, JavaRenderTexture render, int[] ptx, int[] pty, int cnt);
/*C*/
public:
    virtual void fillPolygonGouraud(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) = 0;
/**/
/*J*
    public abstract void fillPolygonGouraudAlpha(int[] px, int[] py, int[] pc, JavaRenderTexture render, int[] ptx, int[] pty, int cnt);
/*C*/
public:
    virtual void fillPolygonGouraudAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) = 0;
/**/
/*J*
    public abstract void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture font);
/*C*/
public:
    virtual void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture* font) = 0;
/**/
/*J*
    public abstract void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture font);
/*C*/
public:
    virtual void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* font) = 0;
/**/
/*J*
    public abstract Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture render_font);
/*C*/
public:
    virtual Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font) = 0;
/**/
/*J*
    public abstract void render(int render_mode, int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, String string, int cnt);
/*C*/
public:
    virtual void render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt) = 0;
/**/
/*J*
    public abstract void render(Polygon poly, Vertex[] vert);
/*C*/
public:
    virtual void render(Polygon* _poly, Vertex** vert) = 0;
#endif
/**/

/*J*
    public static int get_brightness_color(int color, int brightness) {
/*C*/
#ifdef _IS_H_
public:
    static int get_brightness_color(int color, int brightness);
#else
    int JavaRenderAbstract::get_brightness_color(int color, int brightness) {
/**/
        if (brightness <= 0)
        {
            return color & 0xff000000;
        }
        else
        if (brightness >= BRIGHTNESS_MAX - 1)
        {
//*testcolor*/return 0xff000000;
            return (color & 0xff000000) | 0x00fffffe;
        }
        int r = (color >> 16) & 0xff;
        int g = (color >>  8) & 0xff;
        int b = (color      ) & 0xff;
        if (brightness <= BRIGHTNESS_BORDER2)
        {
            r = r * brightness / BRIGHTNESS_BORDER2;
            g = g * brightness / BRIGHTNESS_BORDER2;
            b = b * brightness / BRIGHTNESS_BORDER2;
//*testcolor*/return 0xff0000ff;
        }
        else if (brightness <= BRIGHTNESS_BORDER1)
        {
//*testcolor*/return 0xff00ff00;
            return color;
        }
        else
        {
//*testcolor*/return 0xffff0000;
            int mul = brightness - BRIGHTNESS_BORDER1;
            int div = BRIGHTNESS_MAX - BRIGHTNESS_BORDER1;
            // 非線形
/*
            r += (256 - r) * mul * mul / div / div;
            g += (256 - g) * mul * mul / div / div;
            b += (256 - b) * mul * mul / div / div;
*/
            r += (256 - r) * mul / div;
            g += (256 - g) * mul / div;
            b += (256 - b) * mul / div;
        }
        return (color & 0xff000000) | (r << 16) | (g << 8) | b;
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/

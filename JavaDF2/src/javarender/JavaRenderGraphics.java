/*
 * $id$
 */

/*J*/
package javarender;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.image.ImageObserver;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java.awt.Color"
#include "../cpp2javalib/java.awt.Component"
#include "../cpp2javalib/java.awt.Graphics"
#include "../cpp2javalib/java.awt.Image"
#include "../cpp2javalib/java.awt.Rectangle"
#include "../cpp2javalib/java.awt.image.ImageObserver"
#include "JavaRenderAbstract.cpp"

#else // cpp

#define _IS_H_
#include "JavaRenderGraphics.cpp"
#undef _IS_H_

#endif
/**/

/**
 * JavaRenderGraphics
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: JavaRenderGraphics.java,v 1.12 2008/03/06 16:44:00 matsushima Exp $
 * 
 * $Log: JavaRenderGraphics.java,v $
 * Revision 1.12  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.17  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.16  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.15  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.14  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.13  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.12  2007/05/23 18:30:22  matsushima
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
/*J*/
public class JavaRenderGraphics extends JavaRenderAbstract
{
/*C*
#ifdef _IS_H_
class JavaRenderGraphics : public JBase<JavaRenderGraphics>, public JavaRenderAbstract
{
/**/
/*J*/
    private Component component;
    private Image imageOff;
    public Graphics graphOff;
    private int[] px = new int[1024], py = new int[1024], pc = new int[1024], ptx = new int[1024], pty = new int[1024];
/*C*
private:
    Component* component;
    Image* imageOff;
public:
    Graphics* graphOff;
/**/

/*J*/
    public JavaRenderGraphics(int width, int height, Component component) {
        super(width, height);
/*C*
#endif
#ifdef _IS_H_
public:
    JavaRenderGraphics(int width, int height, Component* component);
#else
    JavaRenderGraphics::JavaRenderGraphics(int width, int height, Component* component)
        : JavaRenderAbstract(width, height) {
#define this (*this)
/**/
        this.component = component;
        imageOff = _R(component).createImage(width, height);
        graphOff = _R(imageOff).getGraphics();
    }

/*C*
#endif
#ifdef _IS_H_
public:
    virtual ~JavaRenderGraphics();
#else
    JavaRenderGraphics::~JavaRenderGraphics() {
        delete imageOff;
    }
/**/

/*J*/
    public void clear() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void clear();
#else
    void JavaRenderGraphics::clear() {
        JMEMBER(Graphics, graphOff);
/**/
        graphOff.setColor(Color.blue);
        graphOff.fillRect(0, 0, width, height);
    }

/*J*/
    public void repaint() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void repaint();
#else
    void JavaRenderGraphics::repaint() {
/**/
        _R(component).repaint();
    }

/*J*/
    public void paint(Graphics graphics, ImageObserver observer) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void paint(Graphics* graphics, ImageObserver* observer);
#else
    void JavaRenderGraphics::paint(Graphics* graphics, ImageObserver* observer) {
/**/
        _R(graphics).drawImage(imageOff, 0, 0, observer);
    }

/*J*/
    public int getPixel(int x, int y) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int getPixel(int x, int y);
#else
    int JavaRenderGraphics::getPixel(int x, int y) {
/**/
        return 0;
    }

/*J*/
    public void setPixel(int color, int x, int y) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void setPixel(int color, int x, int y);
#else
    void JavaRenderGraphics::setPixel(int color, int x, int y) {
/**/
    }

/*J*/
    public void drawLine(int color, int x1, int y1, int x2, int y2) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void drawLine(int color, int x1, int y1, int x2, int y2);
#else
    void JavaRenderGraphics::drawLine(int color, int x1, int y1, int x2, int y2) {
        JMEMBER(Graphics, graphOff);
/**/
        graphOff.setColor(/*J*/new /**/Color(color));
        graphOff.drawLine(x1, y1, x2, y2);
    }

/*J*/
    public void drawPolygon(int[] px, int[] py, int[] pc, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void drawPolygon(int* px, int* py, int* pc, int cnt);
#else
    void JavaRenderGraphics::drawPolygon(int* px, int* py, int* pc, int cnt) {
/**/
        if (cnt <= 1)
        {
            return;
        }
        drawPolyline(px, py, pc, cnt);
        if (cnt >= 3)
        {
            drawLine(pc[cnt - 1], px[cnt - 1], py[cnt - 1], px[0], py[0]);
        }
    }

/*J*/
    public void drawPolyline(int[] px, int[] py, int[] pc, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void drawPolyline(int* px, int* py, int* pc, int cnt);
#else
    void JavaRenderGraphics::drawPolyline(int* px, int* py, int* pc, int cnt) {
/**/
        if (cnt <= 1)
        {
            return;
        }
        for (int i = 0; i < cnt - 1; ++ i)
        {
            drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
        }
    }

/*J*/
    public void fillPolygon(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void fillPolygon(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderGraphics::fillPolygon(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
        JMEMBER(Graphics, graphOff);
/**/
        int c0 = (pc[0] >> 1) & 0x007f7f7f;
        int c1 = (pc[1] >> 2) & 0x003f3f3f;
        int c2 = (pc[2] >> 2) & 0x003f3f3f;
        int color = c0 + c1 + c2;
        graphOff.setColor(/*J*/new /**/Color(color));
        graphOff.fillPolygon(px, py, cnt);
    }

/*J*/
    public void fillPolygonAlpha(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void fillPolygonAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderGraphics::fillPolygonAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
        JMEMBER(Graphics, graphOff);
/**/
        int c0 = (pc[0] >> 1) & 0x007f7f7f;
        int c1 = (pc[1] >> 2) & 0x003f3f3f;
        int c2 = (pc[2] >> 2) & 0x003f3f3f;
        int color = c0 + c1 + c2;
        graphOff.setColor(/*J*/new /**/Color(color));
        graphOff.fillPolygon(px, py, cnt);
    }

/*J*/
    public void fillPolygonGouraud(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void fillPolygonGouraud(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderGraphics::fillPolygonGouraud(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
/**/
        fillPolygon(px, py, pc, texture, ptx, pty, cnt);
    }

/*J*/
    public void fillPolygonGouraudAlpha(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void fillPolygonGouraudAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderGraphics::fillPolygonGouraudAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
/**/
        fillPolygon(px, py, pc, texture, ptx, pty, cnt);
    }

/*J*/
    public void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture render_font) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture* render_font);
#else
    void JavaRenderGraphics::drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture* render_font) {
/**/
        drawString(color, x, y, 65536 / 4, string, proportional, render_font);
    }

/*J*/
    public void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture render_font) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font);
#else
    void JavaRenderGraphics::drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font) {
        JMEMBER(Graphics, graphOff);
/**/
        graphOff.setColor(/*J*/new /**/Color(color));
        graphOff.drawString(string, x, y);
    }

/*J*/
    public Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture render_font) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font);
#else
    Rectangle JavaRenderGraphics::calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font) {
/**/
        return /*J*/null/*C*Rectangle()/**/;
    }

/*J*/
    public void render(int render_mode, int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, String string, int cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt);
#else
    void JavaRenderGraphics::render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt) {
/**/
        int idx = 0;
        int i = idx;
        if (2 == cnt)
        {
            drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
        }
        else
        {
            switch (render_mode & RENDER_MASK)
            {
            case RENDER_POLYLINE:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
                    }
                    break;
                }
            case RENDER_POLYFRAME:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
                    }
                    drawLine(pc[i], px[i], py[i], px[idx], py[idx]);
                    break;
                }
            case RENDER_POLYGON:
                {
                    fillPolygon(px, py, pc, texture, ptx, pty, cnt);
                    break;
                }
            case RENDER_STRING:
                {
                    drawString(pc[i], px[i], py[i], string, true, texture);
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }

/*J*/
    public void render(Polygon poly, Vertex[] vert) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void render(Polygon* _poly, Vertex** vert);
#else
    void JavaRenderGraphics::render(Polygon* _poly, Vertex** vert) {
        Polygon& poly = *_poly;
/**/
        int idx = poly.vert_idx;
        int cnt = poly.vert_cnt;
        if (2 == cnt)
        {
            drawLine(
                _R(vert[idx]).color,
                _R(vert[idx    ]).x2, _R(vert[idx    ]).y2,
                _R(vert[idx + 1]).x2, _R(vert[idx + 1]).y2);
        }
        else
        {
            int i;
            switch (poly.render_mode & RENDER_MASK)
            {
            case RENDER_POLYLINE:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
                    }
                    break;
                }
            case RENDER_POLYFRAME:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
                    }
                    drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[idx]).x2, _R(vert[idx]).y2);
                    break;
                }
            case RENDER_POLYGON:
                {
/*C*
                    int px[1024], py[1024], pc[1024], ptx[1024], pty[1024];
/**/
                    for (i = 0; i < cnt; ++ i)
                    {
                        px[i] = _R(vert[idx + i]).x2;
                        py[i] = _R(vert[idx + i]).y2;
                        pc[i] = _R(vert[idx + i]).color;
                        ptx[i] = _R(vert[idx + i]).tx;
                        pty[i] = _R(vert[idx + i]).ty;
                    }
                    fillPolygon(px, py, pc, poly.texture, ptx, pty, cnt);
                    break;
                }
            case RENDER_STRING:
                {
                    drawString(
                        _R(vert[idx]).color, _R(vert[idx]).x2, _R(vert[idx]).y2, poly.string, true, poly.texture);
                    poly.string = "";
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
};
#endif
/**/

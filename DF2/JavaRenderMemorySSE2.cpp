/*
 * $Id: JavaRenderMemorySSE2.cpp,v 1.17 2008/03/12 16:30:47 matsushima Exp $
 */

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "JavaRenderMemory.cpp"

#else // cpp

#define _IS_H_
#include "JavaRenderMemorySSE2.cpp"
#include "Log.cpp"
#include "../cpp2javalib/java/lang/Integer"
#undef _IS_H_

#ifdef _DEBUG
    static int width, height, width_4, height_width, *pixOff, *pixOffBottom, (*b_tbl)[256];
    static JavaRenderMemory::VERT* verts;
    static int JavaRenderMemory_clear() { return 0; }
    static int JavaRenderMemory_drawLine(int color, int x1, int y1, int x2, int y2) { return 0; }
    static int JavaRenderMemorySSE2_render(int render_mode, int* texture, int tw, int th, int cnt) { return 0; }
    static int mmx_bench() { return 0; }
#else
extern "C" {
    extern int width, height, width_4, height_width, *pixOff, *pixOffBottom, (*b_tbl)[256];
    extern JavaRenderMemory::VERT* verts;
    extern int JavaRenderMemory_clear();
    extern int JavaRenderMemory_drawLine(int color, int x1, int y1, int x2, int y2);
    extern int JavaRenderMemorySSE2_render(int render_mode, int* texture, int tw, int th, int cnt);
    extern int mmx_bench();
    extern int ttt1, ttt2, ttt3, ttt4, ttt5, ttt6, ttt7, ttt8;
    void logout(int i)
    {
        Log::out(String("") + i);
    }
}
#endif
void __test();

#endif
/**/

/**
 * 配列を使用したレンダ(SSE2 + MMX 使用)。
 * 
 * @since   1.0 2007/05/08 matsushima
 * @author  1.0 2007/05/08 matsushima
 * @version $Id: JavaRenderMemorySSE2.cpp,v 1.17 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: JavaRenderMemorySSE2.cpp,v $
 * Revision 1.17  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.16  2008/03/06 16:42:46  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.15  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.14  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.13  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.12  2008/02/24 19:06:02  matsushima
 * 高速化
 *
 * Revision 1.11  2007/05/24 18:42:03  matsushima
 * no message
 *
 * Revision 1.10  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.9  2007/05/22 01:34:45  matsushima
 * no message
 *
 * Revision 1.8  2007/05/21 15:32:02  matsushima
 * no message
 *
 * Revision 1.7  2007/05/18 16:35:27  matsushima
 * no message
 *
 * Revision 1.6  2007/05/18 06:01:16  matsushima
 * no message
 *
 * Revision 1.5  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.3  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.1  2007/05/09 04:18:38  matsushima
 * JavaRenderMemory から SSE2 を分離
 *
 */
/*C*/
#ifdef _IS_H_
class JavaRenderMemorySSE2 : public JavaRenderMemory
{
public:
    JavaRenderMemorySSE2(int width, int height, Component* component);
#else
    JavaRenderMemorySSE2::JavaRenderMemorySSE2(int width, int height, Component* component)
        : JavaRenderMemory(width, height, component, false) {
//__test();
        ::width = width;
        ::height = height;
        ::width_4 = width * 4;
        ::height_width = height * width;
        ::pixOff = pixOff;
        ::pixOffBottom = pixOff + width * (height - 1);
        ::b_tbl = b_tbl;
        ::verts = verts;
        create_polygon_class();
    }
#endif

#ifdef _IS_H_
public:
    virtual ~JavaRenderMemorySSE2();
#else
    JavaRenderMemorySSE2::~JavaRenderMemorySSE2() {
    }
#endif

#ifdef _IS_H_
public:
    void clear();
#else
    void JavaRenderMemorySSE2::clear() {
        if (0 == JavaRenderMemory_clear())
        {
            JavaRenderMemory::clear();
        }
    }
#endif

#ifdef _IS_H_
public:
    //void repaint();

public:
    //void paint(Graphics* graphics, ImageObserver* observer);

private:
    //int _y(int y);

public:
    //int getPixel(int x, int y);

public:
    //void setPixel(int color, int x, int y);

public:
    void drawLine(int color, int x1, int y1, int x2, int y2);
#else
    void JavaRenderMemorySSE2::drawLine(int color, int x1, int y1, int x2, int y2) {
        if (0 == JavaRenderMemory_drawLine(color, x1, y1, x2, y2))
        {
            JavaRenderMemory::drawLine(color, x1, y1, x2, y2);
        }
    }
#endif

#ifdef _IS_H_
public:
    //void drawPolygon(int* px, int* py, int* pc, int cnt);

public:
    //void drawPolyline(int* px, int* py, int* pc, int cnt);

public:
    //void fillPolygon(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);

public:
    //void fillPolygonAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);

public:
    //void fillPolygonGouraud(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);

public:
    //void fillPolygonGouraudAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);

public:
    //void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture* render_font);

public:
    //void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font);

public:
    //Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font);

public:
    virtual void render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt);
#else
    void JavaRenderMemorySSE2::render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt) {
#ifdef _DEBUG
        JavaRenderMemory::render(render_mode, px, py, pc, texture, ptx, pty, string, cnt);
#else
        int idx = 0;
        if (null == texture)
        {
            for (int i = 0; i < cnt; ++ i)
            {
                verts[i].x = px[i];
                verts[i].y = py[i];
                verts[i].c = pc[i];               // solid:   |  a|  r|  g|  b|
            }
            JavaRenderMemorySSE2_render(render_mode, null, 0, 0, cnt);
        }
        else
        {
            for (int i = 0; i < cnt; ++ i)
            {
                verts[i].x = px[i];
                verts[i].y = py[i];
                verts[i].c = pc[i];               // texture: |  a| brightness|
                verts[i].tx = ptx[i];
                verts[i].ty = pty[i];
            }
            JavaRenderMemorySSE2_render(render_mode, texture->pix, texture->width, texture->height, cnt);
        }
#endif
    }
#endif

#ifdef _IS_H_
public:
    virtual void render(JavaRender::Polygon* _poly, JavaRender::Vertex** vert);
#else
    void JavaRenderMemorySSE2::render(JavaRender::Polygon* _poly, JavaRender::Vertex** vert) {
#ifdef _DEBUG
        JavaRenderMemory::render(_poly, vert);
#else
        JavaRender::Polygon& poly = *_poly;
        int render_mode = poly.render_mode;
        JavaRenderTexture* texture = poly.texture;
        int idx = poly.vert_idx;
        int cnt = poly.vert_cnt;
        if (null == texture)
        {
            for (int i = 0; i < cnt; ++ i)
            {
                verts[i].x = _R(vert[idx + i]).x2;
                verts[i].y = _R(vert[idx + i]).y2;
                verts[i].c = _R(vert[idx + i]).color;               // solid:   |  a|  r|  g|  b|
            }
            JavaRenderMemorySSE2_render(render_mode, null, 0, 0, cnt);
        }
        else
        {
            for (int i = 0; i < cnt; ++ i)
            {
                verts[i].x = _R(vert[idx + i]).x2;
                verts[i].y = _R(vert[idx + i]).y2;
                verts[i].c
                    = (_R(vert[idx + i]).color & 0xff000000)
                    | (_R(vert[idx + i]).brightness & 0x00ffffff);  // texture: |  a| brightness|
                verts[i].tx = _R(vert[idx + i]).tx;
                verts[i].ty = _R(vert[idx + i]).ty;
            }
            JavaRenderMemorySSE2_render(render_mode, texture->pix, texture->width, texture->height, cnt);
        }
#endif
    }

    //1361460
    // /1000000/1000000000*1600000000
    // *0.0000016
    #include <windows.h>
    void __test()
    {
    static __int64 freq, pc2, pc;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&pc2);
    int r=mmx_bench();
    QueryPerformanceCounter((LARGE_INTEGER*)&pc);
    pc -= pc2;
    pc = pc * 1000000;
    pc /= freq;
    double res = (double)pc;
    res *= 0.0000016;
    res-=0.1;
    Log::out(String("mmx_bench() : r = ") + r + ", res = " + res);
}
#endif
#ifdef _IS_H_
};
#endif
/**/

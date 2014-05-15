/*
 * $Id: JavaRenderBuffer.cpp,v 1.8 2008/03/30 16:25:48 matsushima Exp $
 */

/*J*
package javarender;

import java.applet.Applet;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.ImageObserver;

import commons.JavaObject;
import commons.Log;
import commons.Perf;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/applet/Applet"
#include "../cpp2javalib/java/awt/Component"
#include "JavaRender.cpp"
#include "JavaRenderAbstract.cpp"
#include "JavaRenderTexture.cpp"
#include "Perf.cpp"

#else // cpp

#define _IS_H_
#include "JavaRenderBuffer.cpp"
#include "JavaRenderMemory.cpp"
#include "JavaRenderMemorySSE2.cpp"
#include "../cpp2javalib/java/awt/Image"
#include "../cpp2javalib/java/net/URL"
#include "Log.cpp"
#include <windows.h>
#undef _IS_H_

#endif
/**/

/**
 * レンダのバッファ。
 * 
 * @since   1.0 2007/05/23 matsushima
 * @author  1.0 2007/05/23 matsushima
 * @version $Id: JavaRenderBuffer.cpp,v 1.8 2008/03/30 16:25:48 matsushima Exp $
 * 
 * $Log: JavaRenderBuffer.cpp,v $
 * Revision 1.8  2008/03/30 16:25:48  matsushima
 * マルチスレッド切り替え
 *
 * Revision 1.7  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.6  2008/03/11 16:21:00  matsushima
 * RenderBuffer マルチスレッド化
 *
 * Revision 1.3  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.4  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.3  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.2  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.1  2008/02/24 05:52:06  matsushima
 * JavaRenderInterface -> JavaRender
 * JavaRender -> JavaRenderBuffer
 *
 * Revision 1.14  2008/02/23 23:45:19  matsushima
 * 高速化
 *
 * Revision 1.13  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.12  2007/05/28 00:43:05  matsushima
 * no message
 *
 * Revision 1.11  2007/05/24 18:42:03  matsushima
 * no message
 *
 * Revision 1.10  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.9  2007/05/23 18:30:22  matsushima
 * JavaRenderBuffer カプセル化
 *
 * Revision 1.1  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRender を Java3D から分離
 *
 */
/*J*
public class JavaRenderBuffer extends JavaObject implements JavaRender, Runnable
{
/*C*/
#ifdef _IS_H_
class JavaRenderBuffer : public JavaRender, public Runnable
{
/**/
    // スレッドを使用するか
/*J*
    public static final int
/*C*/
    enum {
/**/
        USER_THREAD = 0//1
/*J*
    ;
/*C*/
/**/
    };
/*J*
    // render フォント
    public JavaRenderTexture render_font;
    public JavaRenderTexture render_fontp;
    // render (ダブルバッファリング)
    public JavaRenderAbstract render1;
    public JavaRenderAbstract render2;
    public JavaRenderAbstract render_draw;
    public JavaRenderAbstract render_paint;
    // render スレッド
    private Thread thread;
    volatile private boolean is_notify_this;
    volatile private boolean is_notify_thread;

    public static final int
        TRVERT_CNT      = 102400/2*2,
        TRPOLY_CNT      = 102400/4*4,
        TRPOLYVERT_CNT  = 102400/2*2
    ;
    public int         trvert_cnt_max;
    public int         trpoly_cnt_max;
    public int         trpolyvert_cnt_max;
    public Vertex[]    trverts;
    public int         trvert_cnt;
    public Polygon[]   trpolys;
    public int         trpoly_cnt;
    public Vertex[]    trpolyverts;
    public int         trpolyvert_cnt;
    public Polygon    trpoly_top;
    public Polygon    trpoly_end;
    public Polygon    trpoly_sort_top;
    public Polygon    trpoly_sort_end;
    public int buffer_cnt;
    public int append_cnt, sort_cnt;

    public Perf render_time;
    public Perf clear_time;
    public Perf repaint_time;
    public Perf paint_time;
/*C*/
public:
    // render フォント
    JavaRenderTexture* render_font;
    JavaRenderTexture* render_fontp;
    // render (ダブルバッファリング)
    JavaRenderAbstract* render1;
    JavaRenderAbstract* render2;
    JavaRenderAbstract* render_draw;
    JavaRenderAbstract* render_paint;
    // render スレッド
private:
    Thread* thread;
    volatile boolean is_notify_this;
    volatile boolean is_notify_thread;
    void* event_this;
    void* event_thread;

public:
    enum {
        TRVERT_CNT      = 102400/2*2 *2,
        TRPOLY_CNT      = 102400/4*4 *2,
        TRPOLYVERT_CNT  = 102400/2*2 *2
    };
    int         trvert_cnt_max;
    int         trpoly_cnt_max;
    int         trpolyvert_cnt_max;
    Vertex*    trverts;
    int         trvert_cnt;
    Polygon*   trpolys;
    int         trpoly_cnt;
    Vertex**    trpolyverts;
    int         trpolyvert_cnt;
    Polygon*    trpoly_top;
    Polygon*    trpoly_end;
    Polygon*    trpoly_sort_top;
    Polygon*    trpoly_sort_end;
    int buffer_cnt;
    int append_cnt, sort_cnt;

    Perf* render_time;
    Perf* clear_time;
    Perf* repaint_time;
    Perf* paint_time;
#endif
/**/

/*J*
    public JavaRenderBuffer(Applet applet, Component component, int width, int height) {
/*C*/
#ifdef _IS_H_
public:
    JavaRenderBuffer(Applet* _applet, Component* component, int width, int height);
#else
    JavaRenderBuffer::JavaRenderBuffer(Applet* _applet, Component* component, int width, int height) {
        JTYPEDEF_P(Image);
        JPARAM(Applet, applet);
/**/
        // render フォント
        String path = /*J*"./"/*C*/"../DF2/"/**/;
        Image i1 = applet.getImage(&applet.getCodeBase(), path + "font.png");
        render_font = new JavaRenderTexture(component, 55, 50, i1);
        jdelete(i1);
        Image i2 = applet.getImage(&applet.getCodeBase(), path + "fontp.png");
        render_fontp = new JavaRenderTexture(component, 45, 50, i2);
        jdelete(i2);
        // render (ダブルバッファリング)
        //render1 = new JavaRenderBufferGraphics(viewport_width, viewport_height, component);
        //render2 = new JavaRenderBufferGraphics(viewport_width, viewport_height, component);
/*J*
        render1 = new JavaRenderMemory(width, height, component);
        render2 = new JavaRenderMemory(width, height, component);
/*C*/
        /**/
        render1 = new JavaRenderMemory(width, height, component);
        render2 = new JavaRenderMemory(width, height, component);
        /**
        render1 = new JavaRenderMemorySSE2(width, height, component);
        render2 = new JavaRenderMemorySSE2(width, height, component);
/**/
        // render スレッド
        is_notify_this = true;
        is_notify_thread = false;
        thread = null;
        if (0 != USER_THREAD) // スレッドを使用するか
        {
            thread = new Thread(this);
/*C*/
            init_event(true);
            thread->init_event(false);
/**/
            _R(thread).start();
        }

        render_time       = new Perf();
        clear_time        = new Perf();
        repaint_time      = new Perf();
        paint_time        = new Perf();

        // 変換後バッファを作成する
        init_buffer();
    }
/*C*/
#endif
/**/

/*C*/
#ifdef _IS_H_
public:
    virtual ~JavaRenderBuffer();
#else
    JavaRenderBuffer::~JavaRenderBuffer() {
        delete thread;
        delete render1;
        delete render2;
        delete render_font;
        delete render_fontp;

        int i;
        for (i = 0; i < TRVERT_CNT; ++ i)
        {
            //delete trverts[i];
        }
        delete[] trverts;
        for (i = 0; i < TRPOLY_CNT; ++ i)
        {
            //delete trpolys[i];
        }
        delete[] trpolys;
        delete[] trpolyverts;

        delete render_time;
        delete clear_time;
        delete repaint_time;
        delete paint_time;
    }
#endif
/**/

    /**
     * 変換後バッファを作成する。
     */
/*J*
    public void init_buffer() {
/*C*/
#ifdef _IS_H_
public:
    virtual void init_buffer();
#else
    void JavaRenderBuffer::init_buffer() {
/**/
        int i;
        trverts = new Vertex[TRVERT_CNT];
        for (i = 0; i < TRVERT_CNT; ++ i)
        {
            /*J*trverts[i] = new Vertex();/**/
        }
        trpolys = new Polygon[TRPOLY_CNT];
        for (i = 0; i < TRPOLY_CNT; ++ i)
        {
            /*J*trpolys[i] = new Polygon();/**/
            trpolys[i].next = null;
            trpolys[i].prev = null;
            trpolys[i].render_mode = 0;
            trpolys[i].vert_idx = 0;
            trpolys[i].vert_cnt = 0;
            trpolys[i].z_order = 0;
        }
        trpolyverts = new Vertex/*C*/* /**/[TRPOLYVERT_CNT];
        for (i = 0; i < TRPOLYVERT_CNT; ++ i)
        {
            trpolyverts[i] = null;
        }
        trvert_cnt_max = 0;
        trpoly_cnt_max = 0;
        trpolyvert_cnt_max = 0;
        buffer_cnt = 0;
        append_cnt = sort_cnt = 0;
        clear_buffer();
    }
/*C*/
#endif
/**/

    /**
     * 変換後バッファをクリアする。
     */
/*J*
    public void clear_buffer() {
/*C*/
#ifdef _IS_H_
public:
    virtual void clear_buffer();
#else
    void JavaRenderBuffer::clear_buffer() {
/**/
//Log.logout(String(trvert_cnt) + "," + trpoly_cnt + "," + trpolyvert_cnt);
        int cnt_v = TRVERT_CNT / 2 * (buffer_cnt % 2);
        int cnt_p = TRPOLY_CNT / 2 * (buffer_cnt % 2);
        int cnt_pv = TRPOLYVERT_CNT / 2 * (buffer_cnt % 2);
        if (trvert_cnt_max < trvert_cnt - cnt_v)
        {
            trvert_cnt_max = trvert_cnt - cnt_v;
        }
        if (trpoly_cnt_max < trpoly_cnt - cnt_p)
        {
            trpoly_cnt_max = trpoly_cnt - cnt_p;
        }
        if (trpolyvert_cnt_max < trpolyvert_cnt - cnt_pv)
        {
            trpolyvert_cnt_max = trpolyvert_cnt - cnt_pv;
        }
        ++ buffer_cnt;
        cnt_v = TRVERT_CNT / 2 * (buffer_cnt % 2);
        cnt_p = TRPOLY_CNT / 2 * (buffer_cnt % 2);
        cnt_pv = TRPOLYVERT_CNT / 2 * (buffer_cnt % 2);
        render_draw = (0 == cnt_p) ? render1 : render2;
        render_paint = (0 == cnt_p) ? render2 : render1;
        trpoly_top      = &trpolys[cnt_p];
        trpoly_end      = &trpolys[cnt_p];
        trpoly_sort_top = &trpolys[cnt_p];
        trpoly_sort_end = null;
        trpolys[cnt_p].next = null;
        trpoly_cnt      = cnt_p + 1;
        trpolyvert_cnt  = cnt_pv;
        trvert_cnt      = cnt_v;
    }
/*C*/
#endif
/**/

    /**
     * 変換後バッファを破棄する。
     */
/*J*
    public void free_buffer() {
/*C*/
#ifdef _IS_H_
public:
    virtual void free_buffer();
#else
    void JavaRenderBuffer::free_buffer() {
/**/
Log::out(String("trvert_cnt_max/TRVERT_CNT = ") + trvert_cnt_max + "/" + TRVERT_CNT);
Log::out(String("trpoly_cnt_max/TRPOLY_CNT = ") + trpoly_cnt_max + "/" + TRPOLY_CNT);
Log::out(String("trpolyvert_cnt_max/TRPOLYVERT_CNT = ") + trpolyvert_cnt_max + "/" + TRPOLYVERT_CNT);
    }
/*C*/
#endif
/**/

    /**
     * 変換後ポリゴンバッファにポリゴンを追加する。
     * 
     * @param trpoly
     * @param z_order
     * @param vert_cnt
     * @param mode
     */
/*J*
    public void append_buffer(Polygon trpoly, int z_order, int vert_cnt, int mode) {
/*C*/
#ifdef _IS_H_
public:
    virtual void append_buffer(Polygon* trpoly, int z_order, int vert_cnt, int mode);
#else
    void JavaRenderBuffer::append_buffer(Polygon* trpoly, int z_order, int vert_cnt, int mode) {
/**/
++ append_cnt;
        trpoly->vert_idx = trpolyvert_cnt;
        switch (mode & APPEND_MASK)
        {
        case APPEND_FRONT:
            trpoly->next = trpoly_top->next;
            trpoly_top->next = trpoly;
            if (trpoly_sort_top == trpoly_top)
            {
                trpoly_sort_top = trpoly;
            }
            break;
        case APPEND_BACK:
            trpoly->next = trpoly_end->next;
            trpoly_end->next = trpoly;
            if (trpoly_sort_end == null)
            {
                trpoly_sort_end = trpoly;
            }
            break;
        case APPEND_SORT:
            Polygon* i;
            for (i = trpoly_sort_top; trpoly_sort_end != i->next; i = i->next)
            {
++ sort_cnt;
                if (z_order >= i->next->z_order)
                {
                    break;
                }
            }
            trpoly->next = i->next;
            i->next = trpoly;
            break;
        }
        if (null == trpoly->next)
        {
            this->trpoly_end = trpoly;
        }
        ++ trpoly_cnt;
        trpolyvert_cnt += vert_cnt;
    }
/*C*/
#endif
/**/

    /**
     * ポリゴンバッファに追加されたモデルを描画する。
     * render スレッドに追加。
     */
/*J*
    public void render() {
/*C*/
#ifdef _IS_H_
public:
    virtual void render();
#else
    void JavaRenderBuffer::render() {
        JMEMBER(Perf, render_time);
        JMEMBER(JavaRenderAbstract, render_draw);
        JMEMBER(Thread, thread);
/**/
        if (0 != USER_THREAD) // スレッドを使用するか
        {
            try
            {
                /*J*synchronized (this)/**/
                {
                    /*J*if (! is_notify_this)/**/
                    {
                        wait();
                    }
                    is_notify_this = false;
                }
                clear_buffer();
                /*J*synchronized (thread)/**/
                {
                    is_notify_thread = true;
                    thread.notify();
                }
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        }
        else
        {
            clear_buffer();
            run_render();
        }
    }
/*C*/
#endif
/**/

    /**
     * render スレッド。
     */
/*J*
    public void run() {
/*C*/
#ifdef _IS_H_
public:
    virtual void run();
#else
    void JavaRenderBuffer::run() {
        JMEMBER(Thread, thread);
/**/
        try
        {
            while (true)
            {
                /*J*synchronized (thread)/**/
                {
                    /*J*if (! is_notify_thread)/**/
                    {
                        thread.wait();
                    }
                    is_notify_thread = false;
                }
                run_render();
                /*J*synchronized (this)/**/
                {
                    is_notify_this = true;
                    notify();
                }
            }
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }
/*C*/
#endif
/**/

    /**
     * ポリゴンバッファに追加されたモデルを描画する。
     */
/*J*
    public void run_render() {
/*C*/
#ifdef _IS_H_
public:
    virtual void run_render();
#else
    void JavaRenderBuffer::run_render() {
        JMEMBER(Perf, render_time);
        JMEMBER(JavaRenderAbstract, render_draw);
/**/
        clear();        
render_time.start();
        int cnt_p = TRPOLY_CNT / 2 * (1 - buffer_cnt % 2);
        Polygon/*C*/* /**/ poly;
        for (poly = trpolys[cnt_p].next; null != poly; poly = _R(poly).next)
        {
            render_draw.render(poly, trpolyverts);
render_time.count();
        }
        /*C*/_asm emms/**/
render_time.end();
    }
/*C*/
#endif
/**/

    /**
     * 画面を消去する。
     */
/*J*
    public void clear() {
/*C*/
#ifdef _IS_H_
public:
    virtual void clear();
#else
    void JavaRenderBuffer::clear() {
        JMEMBER(Perf, clear_time);
        JMEMBER(JavaRenderAbstract, render_draw);
/**/
clear_time.start();
        render_draw.clear();
clear_time.end();
    }
/*C*/
#endif
/**/

    /**
     * 画面を再描画する。
     */
/*J*
    public void repaint() {
/*C*/
#ifdef _IS_H_
public:
    virtual void repaint();
#else
    void JavaRenderBuffer::repaint() {
        JMEMBER(Perf, repaint_time);
        JMEMBER(JavaRenderAbstract, render_paint);
/**/
repaint_time.start();
        render_paint.repaint();
repaint_time.end();
    }
/*C*/
#endif
/**/

    /**
     * 画面を描画する。
     * 
     * @param graphics
     * @param observer
     */
/*J*
    public void paint(Graphics graphics, ImageObserver observer) {
/*C*/
#ifdef _IS_H_
public:
    virtual void paint(Graphics* graphics, ImageObserver* observer);
#else
    void JavaRenderBuffer::paint(Graphics* graphics, ImageObserver* observer) {
        JMEMBER(Perf, paint_time);
        JMEMBER(JavaRenderAbstract, render_paint);
/**/
paint_time.start();
        render_paint.paint(graphics, observer);
paint_time.end();
    }
/*C*/
#endif
/**/

/*J*
    public Vertex get_trvert(int index) {
/*C*/
#ifdef _IS_H_
public:
    virtual Vertex& get_trvert(int index);
#else
    JavaRenderBuffer::Vertex& JavaRenderBuffer::get_trvert(int index) {
/**/
        return trverts[trvert_cnt + index];
    }
/*C*/
#endif
/**/

/*J*
    public Vertex get_trpolyvert(int index) {
/*C*/
#ifdef _IS_H_
public:
    virtual Vertex& get_trpolyvert(int index);
#else
    JavaRenderBuffer::Vertex& JavaRenderBuffer::get_trpolyvert(int index) {
/**/
        return /*C*/* /**/trpolyverts[trpolyvert_cnt + index];
    }
/*C*/
#endif
/**/

/*J*
    public void set_trpolyvert(int index, Vertex trvert) {
/*C*/
#ifdef _IS_H_
public:
    virtual void set_trpolyvert(int index, Vertex* trvert);
#else
    void JavaRenderBuffer::set_trpolyvert(int index, Vertex* trvert) {
/**/
        trpolyverts[trpolyvert_cnt + index] = trvert;
    }
/*C*/
#endif
/**/

/*J*
    public Polygon get_trpoly(int index) {
/*C*/
#ifdef _IS_H_
public:
    virtual Polygon& get_trpoly(int index);
#else
    JavaRenderBuffer::Polygon& JavaRenderBuffer::get_trpoly(int index) {
/**/
        return trpolys[trpoly_cnt + index];
    }
/*C*/
#endif
/**/

/*J*
    public void advance_trvert(int trcount) {
/*C*/
#ifdef _IS_H_
public:
    virtual void advance_trvert(int trcount);
#else
    void JavaRenderBuffer::advance_trvert(int trcount) {
/**/
        trvert_cnt += trcount;
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/

/*
 * $Id: JavaPanel.java,v 1.13 2008/03/06 16:44:00 matsushima Exp $
 */

/*J*/
package commons;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java.awt.Color"
#include "../cpp2javalib/java.awt.Component"
#include "../cpp2javalib/java.awt.Font"
#include "../cpp2javalib/java.awt.FontMetrics"
#include "../cpp2javalib/java.awt.Graphics"
#include "../cpp2javalib/java.awt.Image"
#include "../cpp2javalib/java.awt.Rectangle"
#include "../cpp2javalib/java.awt.event.KeyEvent"

#else // cpp

#define _IS_H_
#include "JavaPanel.cpp"
#undef _IS_H_

#endif
/**/

/**
 * パネルの基本クラス。
 * 
 * @since   1.0 2000 matsushima
 * @author  1.0 2000 matsushima
 * @version $Id: JavaPanel.java,v 1.13 2008/03/06 16:44:00 matsushima Exp $
 * 
 * $Log: JavaPanel.java,v $
 * Revision 1.13  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.12  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.11  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.10  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.12  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.11  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.10  2007/05/14 13:38:20  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.7  2007/05/10 22:29:39  matsushima
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
public class JavaPanel extends JavaObject
{
/*C*
#ifdef _IS_H_
class JavaPanel : public JBase<JavaPanel>
{
/**/
/*J*/
    protected int left, top, width, height;
    protected Component component;
    protected Graphics graphics;
    protected Image imageOff;
    protected Graphics graphOff;
    protected Font font;

    public Item[] items;
    public int item_cnt, item_cur;
    public long time_start, time_span_begin;
    public long time_open, time_span_open;
    public long time_close, time_span_close;
/*C*
public:
    class Item;

protected:
    int left, top, width, height;
    Component* component;
    Graphics* graphics;
    Image* imageOff;
    Graphics* graphOff;
    Font* font;

public:
    Item** items;
    int item_cnt, item_cur;
    long time_start, time_span_begin;
    long time_open, time_span_open;
    long time_close, time_span_close;
/**/

/*J*/
    public static final int
/*C*
public:
    enum {
/**/
        TIME_SPAN_CURSOR        = 2000,
        WIDTH_CURSOR            = 5,
        TIME_SPAN_ARROW         = 500,
        WIDTH_ARROW             = 12,
        COLOR_BACKGROUND        = 0xff000000,
        COLOR_TITLE             = 0xff00ff00,
        COLOR_ITEM_TITLE        = 0xff00ffff,
        COLOR_ITEM              = 0xff0000ff,
        COLOR_CURSOR            = 0xffff0000,
        COLOR_ARROW             = 0xff00ff00,
        COLOR_ARROW_DISABLED    = 0xffff0000
/*J*/
    ;
/*C*
    };
/**/

    /**
     * パネルを構築する。
     * 
     * @param   left        パネルの左上側の x 座標。
     * @param   top         パネルの左上側の y 座標。
     * @param   width       パネルの幅。
     * @param   height      パネルの高さ。
     * @param   component
     * @param   graphics
     */
/*J*/
    public JavaPanel(int left, int top, int width, int height, Component component, Graphics graphics) {
/*C*
#endif
#ifdef _IS_H_
public:
    JavaPanel(int left, int top, int width, int height, Component* component, Graphics* graphics);
#else
    JavaPanel::JavaPanel(int left, int top, int width, int height, Component* component, Graphics* graphics) {
#define this (*this)
/**/
        this.left   = left;
        this.top    = top;
        this.width  = width;
        this.height = height;
        this.component = component;
        this.graphics = graphics;
        this.imageOff = null;
        this.graphOff = graphics;
        if ((null == graphics) && (null != component))
        {
            imageOff = _R(component).createImage(width, height);
            graphOff = _R(imageOff).getGraphics();
        }
        this.font = new Font("Dialog", Font.BOLD, 16);
        this.items = null;
        this.item_cnt = this.item_cur = 0;
        this.time_start = this.time_span_begin = -1;
        this.time_open = this.time_span_open = -1;
        this.time_close = this.time_span_close = -1;
    }

    /**
     * パネルを破棄する。
     */
/*C*
#endif
#ifdef _IS_H_
public:
    virtual ~JavaPanel();
#else
    JavaPanel::~JavaPanel() {
        if (null != imageOff)
        {
            delete imageOff;
            if (null != graphOff)
            {
                delete graphOff;
            }
        }
        delete font;
        int i;
        for (i = 0; i < item_cnt; ++ i)
        {
            delete items[i];
        }
        delete[] items;
    }
/**/

    /**
     * 項目を設定する。
     * 
     * @param   items       項目の配列。
     * @param   item_cnt    items の数。
     */
/*J*/
    public void setItems(Item[] items, int item_cnt) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void setItems(Item** items, int item_cnt);
#else
    void JavaPanel::setItems(Item** items, int item_cnt) {
/**/
        this.items = items;
        this.item_cnt = item_cnt;
        this.item_cur = 0;
        move_y(0);
    }

    /**
     * パネルを開く。
     */
/*J*/
    public void open() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void open();
#else
    void JavaPanel::open() {
        JSTATIC(System);
/**/
        time_start = time_open = System.currentTimeMillis();
        time_span_open = height / 2;
        time_close = time_span_close = -1;
    }

    /**
     * パネルが開かれているかを返す。
     * 
     * @return  パネルが開かれているとき true。
     */
/*J*/
    public boolean opened() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual boolean opened();
#else
    boolean JavaPanel::opened() {
/**/
        return ((-1 != time_open) && (-1 == time_close)) ? true : false;
    }

    /**
     * パネルを閉じる。
     */
/*J*/
    public void close() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void close();
#else
    void JavaPanel::close() {
        JSTATIC(System);
/**/
        time_close = System.currentTimeMillis();
        time_span_close = height / 2;
    }

    /**
     * パネル上のキーイベントを処理する。
     * 
     * @param   e   キーイベント。
     */
/*J*/
    public void processKeyEvent(KeyEvent e) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void processKeyEvent(KeyEvent* _e);
#else
    void JavaPanel::processKeyEvent(KeyEvent* _e) {
        JPARAM(KeyEvent, e);
        JSTATIC(KeyEvent);
/**/
        if (false == opened())
        {
            return;
        }
        if (KeyEvent.KEY_PRESSED == e.getID())
        {
            switch (e.getKeyCode())
            {
            case KeyEvent.VK_DOWN:
            case KeyEvent.VK_NUMPAD2:
                move_y(+1);
                break;
            case KeyEvent.VK_UP:
            case KeyEvent.VK_NUMPAD8:
                move_y(-1);
                break;
            case KeyEvent.VK_RIGHT:
            case KeyEvent.VK_NUMPAD6:
                _R(items[item_cur]).move_x(+1);
                break;
            case KeyEvent.VK_LEFT:
            case KeyEvent.VK_NUMPAD4:
                _R(items[item_cur]).move_x(-1);
                break;
            }
        }
    }

    /**
     * 項目のカーソルを y 方向に移動する。
     * 
     * @param   d   移動量。
     */
/*J*/
    protected void move_y(int d) {
/*C*
#endif
#ifdef _IS_H_
protected:
    virtual void move_y(int d);
#else
    void JavaPanel::move_y(int d) {
        JSTATIC(System);
/**/
        _R(items[item_cur]).move_y(false);
        int i, dir = (0 == d) ? 1 : d;
        for (i = 0; i < item_cnt; ++ i)
        {
            item_cur += dir;
            if (false != _R(items[(item_cur + item_cnt) % item_cnt]).move_y(true))
            {
                break; // 行項目が列項目を持っているので止まる
            }
        }
        if ((item_cur >= item_cnt) || (item_cur < 0))
        {
            d = - d; // wrap row: swing reverse
            item_cur = (item_cur + item_cnt) % item_cnt; // wrap row
        }
        long span = -d * TIME_SPAN_CURSOR / 4; // +1:-PI/2, -1:+PI/2
        time_start = System.currentTimeMillis() + span;
        time_span_begin = (0 == d) ? 0 : (TIME_SPAN_CURSOR / 4) - span;
    }

    /**
     * パネルを再描画する。
     * 
     * @param   g   描画に使用するグラフィックコンテキスト。
     */
/*J*/
    public void update(Graphics g) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void update(Graphics* g);
#else
    void JavaPanel::update(Graphics* g) {
        JSTATIC(System);
/**/
        if (false == opened())
        {
            if ((-1 == time_close)
            || (System.currentTimeMillis() - time_close >= time_span_close))
            {
                return;
            }
            else
            {
                // close() が呼び出されてから time_span_close の間は閉じるアクション中
            }
        }
        if (null != graphOff)
        {
            g = graphOff; // オフスクリーンバッファに描画
        }
        long span_open = System.currentTimeMillis() - time_open;
        long span_close = System.currentTimeMillis() - time_close;
        if (span_close < time_span_close)
        {
            // close() が呼び出されてから time_span_close の間は閉じるアクション中
            int h = (int)(height - height * span_close / time_span_close);
            drawBackground(g, COLOR_BACKGROUND, left, top + (height - h) / 2, width, h, false);
        }
        else
        if (span_open < time_span_open)
        {
            // open() が呼び出されてから time_span_open の間は開くアクション中
            int h = (int)(height * span_open / time_span_open);
            drawBackground(g, COLOR_BACKGROUND, left, top + (height - h) / 2, width, h, false);
        }
        else
        {
            drawBackground(g, COLOR_BACKGROUND, left, top, width, height, false);
        }
        // 項目を描画
        Rectangle r/*J*/ = new Rectangle/**/(left + 20, top + 20, 0, 0);
        int i;
        for (i = 0; i < item_cnt; ++ i)
        {
            if (i == item_cur)
            {
                draw_cursor(g, COLOR_CURSOR, left + 10, r.y + r.height, false);
            }
            r = _R(items[i]).update(g, left + 20, r.y + r.height);
        }
    }

    /**
     * カーソルを描画する。
     * 
     * @param   g       描画に使用するグラフィックコンテキスト。
     * @param   color   色。
     * @param   x       x 座標。
     * @param   y       y 座標。
     * @param   calc    描画せずに領域の計算のみ行う場合 true。
     * @return  描画領域。
     */
/*J*/
    protected Rectangle draw_cursor(Graphics g, int color, int x, int y, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
protected:
    virtual Rectangle draw_cursor(Graphics* g, int color, int x, int y, boolean calc);
#else
    Rectangle JavaPanel::draw_cursor(Graphics* g, int color, int x, int y, boolean calc) {
        JSTATIC(System);
        JSTATIC(Math);
/**/
        long span = System.currentTimeMillis() - time_start;
        int w = (span < time_span_begin) ? WIDTH_CURSOR * 2 : WIDTH_CURSOR;
        int dy = (int)(w * Math.sin(2 * Math.PI * span / TIME_SPAN_CURSOR));
        return drawCursor(g, color, x, y + dy, calc);
    }

    /**
     * 背景を描画する。
     * 
     * @param   g       描画に使用するグラフィックコンテキスト。
     * @param   color   色。
     * @param   x       x 座標。
     * @param   y       y 座標。
     * @param   width   幅。
     * @param   height  高さ。
     * @param   calc    描画せずに領域の計算のみ行う場合 true。
     * @return  描画領域。
     */
/*J*/
    public Rectangle drawBackground(Graphics g, int color, int x, int y, int width, int height, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawBackground(Graphics* _g, int color, int x, int y, int width, int height, boolean calc);
#else
    Rectangle JavaPanel::drawBackground(Graphics* _g, int color, int x, int y, int width, int height, boolean calc) {
        JPARAM(Graphics, g);
/**/
        if (false == calc)
        {
            g.setColor(/*J*/new /*C*&/**/Color(color));
            g.fillRect(x, y, width, height);
        }
        return /*J*/new /**/Rectangle(x, y, width, height);
    }

    /**
     * 文字列を描画する。
     * 
     * @param   g       描画に使用するグラフィックコンテキスト。
     * @param   color   色。
     * @param   str     文字列。
     * @param   x       x 座標。
     * @param   y       y 座標。
     * @param   calc    描画せずに領域の計算のみ行う場合 true。
     * @return  描画領域。
     */
/*J*/
    public Rectangle drawString(Graphics g, int color, String str, int x, int y, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawString(Graphics* _g, int color, _String str, int x, int y, boolean calc);
#else
    Rectangle JavaPanel::drawString(Graphics* _g, int color, _String str, int x, int y, boolean calc) {
        JPARAM(Graphics, g);
        JTYPEDEF_R(FontMetrics);
/**/
        g.setFont(font);
        FontMetrics metrics = _R(g.getFontMetrics());
        int w = metrics.stringWidth(str);
        int h = metrics.getAscent() + metrics.getDescent();
        jdelete(metrics);
        if (false == calc)
        {
            g.setColor(/*J*/new /**/Color(color));
            g.drawString(str, x, y - h / 2);
        }
        return /*J*/new /**/Rectangle(x, y, w, h);
    }

    /**
     * カーソルを描画する。
     * 
     * @param   g       描画に使用するグラフィックコンテキスト。
     * @param   color   色。
     * @param   x       x 座標。
     * @param   y       y 座標。
     * @param   calc    描画せずに領域の計算のみ行う場合 true。
     * @return  描画領域。
     */
/*J*/
    public Rectangle drawCursor(Graphics g, int color, int x, int y, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawCursor(Graphics* _g, int color, int x, int y, boolean calc);
#else
    Rectangle JavaPanel::drawCursor(Graphics* _g, int color, int x, int y, boolean calc) {
        JPARAM(Graphics, g);
        JSTATIC(Color);
/**/
        if (false == calc)
        {
            /*J*/float[] hsb = new float[3];/*C*float hsb[3];/**/
            Color.RGBtoHSB((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, hsb);
            int i;
            for (i = 0; i <= 8; ++ i)
            {
                float c = i / 8.0f;
                g.setColor(Color.getHSBColor(hsb[0], (2.0f - c) / 2.0f * hsb[1], (1.0f + c) / 2.0f * hsb[2]));
                g.fillArc(x - i / 5, y - i / 5, 9 - i, 9 - i, 0, 360);
            }
        }
        return /*J*/new /**/Rectangle(x, y, 15, 15);
    }

    /**
     * 矢印を描画する。
     * 
     * @param   g       描画に使用するグラフィックコンテキスト。
     * @param   color   色。
     * @param   x       x 座標。
     * @param   y       y 座標。
     * @param   d       矢印の向き。
     * @param   calc    描画せずに領域の計算のみ行う場合 true。
     * @return  描画領域。
     */
/*J*/
    public Rectangle drawArrow(Graphics g, int color, int x, int y, int d, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawArrow(Graphics* _g, int color, int x, int y, int d, boolean calc);
#else
    Rectangle JavaPanel::drawArrow(Graphics* _g, int color, int x, int y, int d, boolean calc) {
        JPARAM(Graphics, g);
        JSTATIC(Color);
/**/
        if (false == calc)
        {
            /*J*/float[] hsb = new float[3];/*C*float hsb[3];/**/
            Color.RGBtoHSB((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, hsb);
            int i;
            for (i = 0; i <= 1; ++ i)
            {
                float c = i;
                g.setColor(Color.getHSBColor(hsb[0], (2.0f + c) / 3.0f * hsb[1], (2.0f - c) / 2.0f * hsb[2]));
                g.drawLine(x, y + (- 1 - i), x + 5 * d, y + (- 1 - i));
            }
            for (i = 0; i <= 3; ++ i)
            {
                float c = i / 3.0f;
                g.setColor(Color.getHSBColor(hsb[0], (2.0f + c) / 3.0f * hsb[1], (2.0f - c) / 2.0f * hsb[2]));
                g.drawLine(x, y + (- 1 + i), x + 4 * d, y + (- 1 + i));
            }
            for (i = 0; i <= 2; ++ i)
            {
                float c = i / 2.0f;
                g.setColor(Color.getHSBColor(hsb[0], (2.0f + c) / 3.0f * hsb[1], (2.0f - c) / 2.0f * hsb[2]));
                g.drawLine(x + 4 * d, y + (- 3 - i), x + (9 + i / 2) * d, y + 1);
            }
            for (i = 0; i <= 8; ++ i)
            {
                float c = i / 8.0f;
                g.setColor(Color.getHSBColor(hsb[0], (2.0f + c) / 3.0f * hsb[1], (2.0f - c) / 2.0f * hsb[2]));
                g.drawLine(x + 4 * d, y + (- 3 + i), x + (6 + i / 2) * d, y - 1);
            }
        }
        return /*J*/new /**/Rectangle(x, y, 9 + WIDTH_ARROW, 15);
    }

    /**
     * パネルの項目の抽象クラス。
     */
/*J*/
    public static abstract class Item
    {
/*C*
#endif
#ifdef _IS_H_
public:
    class Item : public JBase<Item>
    {
/**/
        /**
         * この項目が存在するパネル。
         */
/*J*/
        protected JavaPanel panel;

        public int item_cur;
/*C*
    protected:
        JavaPanel* panel;

    public:
        int item_cur;
/**/

        /**
         * 項目を構築する。
         * 
         * @param   panel   この項目が存在するパネル。
         */
/*J*/
        protected Item(JavaPanel panel) {
/*C*
#endif
#ifdef _IS_H_
    protected:
        Item(JavaPanel* panel);
#else
        JavaPanel::Item::Item(JavaPanel* panel) {
/**/
            this.panel = panel;
        }

        /**
         * 項目を破棄する。
         */
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual ~Item();
#else
        JavaPanel::Item::~Item() {
        }
/**/

        /**
         * カーソルを移動する。
         * 
         * @param   cur
         * @return  処理したとき true。
         */
/*J*/
        public boolean move_y(boolean cur) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual boolean move_y(boolean cur);
#else
        boolean JavaPanel::Item::move_y(boolean cur) {
/**/
            return false;
        }

        /**
         * カーソルを移動する。
         * 
         * @param dir
         */
/*J*/
        public void move_x(int dir) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual void move_x(int dir);
#else
        void JavaPanel::Item::move_x(int dir) {
/**/
        }

        /**
         * 項目を描画する。
         * 
         * @param   g       描画に使用するグラフィックコンテキスト。
         * @param   x       x 座標。
         * @param   y       y 座標。
         * @return  項目の座標。
         */
/*J*/
        public Rectangle update(Graphics g, int x, int y) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual Rectangle update(Graphics* g, int x, int y);
#else
        Rectangle JavaPanel::Item::update(Graphics* g, int x, int y) {
/**/
            return /*J*/null/*C*Rectangle()/**/;
        }

        /**
         * カーソルを描画する。
         * 
         * @param g
         * @param color
         * @param x
         * @param y
         * @param d
         * @param calc
         * @param time_start
         * @param time_span_begin
         * @param time_span_end
         * @return  項目の座標。
         */
/*J*/
        protected Rectangle draw_arrow(Graphics g, int color, int x, int y, int d, boolean calc,
            long time_start, long time_span_begin, long time_span_end) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual Rectangle draw_arrow(Graphics* g, int color, int x, int y, int d, boolean calc,
            long time_start, long time_span_begin, long time_span_end);
#else
        Rectangle JavaPanel::Item::draw_arrow(Graphics* g, int color, int x, int y, int d, boolean calc,
            long time_start, long time_span_begin, long time_span_end) {
            JSTATIC(System);
            JMEMBER(JavaPanel, panel);
/**/
            long t = System.currentTimeMillis() - time_start;
            int dx = 0, dy = d * 2, a;
            if (0 == d)
            {
                d = 1;
                a = WIDTH_ARROW;
            }
            else
            {
                a = WIDTH_ARROW / 2;
                dx = (int)(a * (1 - d + 0.5));
            }
            int w = (t < time_span_begin) ? 2 : 1;
            w = ((-1 != time_span_end) && (t >= time_span_end)) ? 0 : w;
            dx += (a - a * (t % TIME_SPAN_ARROW) / TIME_SPAN_ARROW) * d * w;
            Rectangle r = panel.drawArrow(g, color, x + dx, y + dy, d, calc);
            return /*J*/new /**/Rectangle(x, y, r.width, r.height);
        }
/*J*/
    }
/*C*
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * タイトル項目。
     */
/*J*/
    public static class ItemTitle extends Item
    {
/*C*
public:
    class ItemTitle : public JBase<ItemTitle>, public Item
    {
/**/
        /**
         * タイトル文字列。
         */
/*J*/
        protected String title;
/*C*
    protected:
        String title;
/**/

        /**
         * タイトル項目を構築する。
         * 
         * @param   panel   この項目が存在するパネル。
         * @param   title   タイトル文字列。
         */
/*J*/
        public ItemTitle(JavaPanel panel, String title) {
            super(panel);
/*C*
#endif
#ifdef _IS_H_
    public:
        ItemTitle(JavaPanel* panel, String title);
#else
        JavaPanel::ItemTitle::ItemTitle(JavaPanel* panel, String title)
            : Item(panel) {
/**/
            this.title = title;
        }

        /**
         * 項目を描画する。
         * 
         * @param   g       描画に使用するグラフィックコンテキスト。
         * @param   x       x 座標。
         * @param   y       y 座標。
         * @return  項目の座標。
         */
/*J*/
        public Rectangle update(Graphics g, int x, int y) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual Rectangle update(Graphics* g, int x, int y);
#else
        Rectangle JavaPanel::ItemTitle::update(Graphics* g, int x, int y) {
            JMEMBER(JavaPanel, panel);
/**/
            return panel.drawString(g, COLOR_TITLE, title, x, y, false);
        }
/*J*/
    }
/*C*
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * 選択項目。
     */
/*J*/
    public static class ItemSelect extends Item
    {
/*C*
public:
    class ItemSelect : public JBase<ItemSelect>, public Item
    {
/**/
        /** タイトル文字列。 */
/*J*/
        protected String title;
/*C*
    protected:
        String title;
/**/
        /** 列項目。 */
/*J*/
        protected String[] items;
/*C*
    protected:
        String* items;
/**/
        /** 列項目の数。 */
/*J*/
        protected int item_cnt;
/*C*
    protected:
        int item_cnt;
/**/
        /** 時間。 */
/*J*/
        protected long time, time_span_begin, time_span_end;
/*C*
    protected:
        long time, time_span_begin, time_span_end;
/**/

        /**
         * 選択項目を構築する。
         * 
         * @param   panel       この項目が存在するパネル。
         * @param   title       タイトル文字列。
         * @param   items       列項目の配列。
         * @param   item_cnt    列項目の数。
         * @param   item_cur    現在選択されている列項目のインデックス。
         */
/*J*/
        public ItemSelect(JavaPanel panel, String title, String[] items, int item_cnt, int item_cur) {
            super(panel);
/*C*
#endif
#ifdef _IS_H_
    public:
        ItemSelect(JavaPanel* panel, String title, String* items, int item_cnt, int item_cur);
#else
        JavaPanel::ItemSelect::ItemSelect(JavaPanel* panel, String title, String* items, int item_cnt, int item_cur)
            : Item(panel) {
/**/
            this.title = title;
            this.items = items;
            this.item_cnt = item_cnt;
            this.item_cur = item_cur;
            this.time = this.time_span_begin = this.time_span_end = 0;
        }

        /**
         * 項目を破棄する。
         */
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual ~ItemSelect();
#else
        JavaPanel::ItemSelect::~ItemSelect() {
        }
/**/

        /**
         * カーソルを移動する。
         * 
         * @param   cur
         */
/*J*/
        public boolean move_y(boolean cur) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual boolean move_y(boolean cur);
#else
        boolean JavaPanel::ItemSelect::move_y(boolean cur) {
            JSTATIC(System);
/**/
            if (false != cur)
            {
                // start
                time = System.currentTimeMillis();
                time_span_begin = time_span_end = -1;
            }
            else
            {
                // stop
                long span = System.currentTimeMillis() - time;
                time_span_end = span - span % TIME_SPAN_ARROW + TIME_SPAN_ARROW;
            }
            return true;
        }

        /**
         * カーソルを移動する。
         * 
         * @param dir
         */
/*J*/
        public void move_x(int dir) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual void move_x(int dir);
#else
        void JavaPanel::ItemSelect::move_x(int dir) {
            JSTATIC(System);
/**/
            item_cur = (item_cur + dir + item_cnt) % item_cnt;
            // restart
            time = System.currentTimeMillis();
            time_span_begin = TIME_SPAN_ARROW;
        }

        /**
         * 項目を描画する。
         * 
         * @param   g       描画に使用するグラフィックコンテキスト。
         * @param   x       x 座標。
         * @param   y       y 座標。
         * @return  項目の座標。
         */
/*J*/
        public Rectangle update(Graphics g, int x, int y) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual Rectangle update(Graphics* g, int x, int y);
#else
        Rectangle JavaPanel::ItemSelect::update(Graphics* g, int x, int y) {
            JMEMBER(JavaPanel, panel);
/**/
            Rectangle r;
            r = panel.drawString(g, COLOR_ITEM_TITLE, title, x, y, false);
            int i;
            for (i = 0; i < item_cnt; ++ i)
            {
                r = draw_arrow(g, COLOR_ARROW, r.x + r.width, y, 0, (i == item_cur) ? false : true,
                    time, time_span_begin, time_span_end);
                r = panel.drawString(g, COLOR_ITEM, items[i], r.x + r.width, y, false);
            }
            return r;
        }
/*J*/
    }
/*C*
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * 値範囲項目。
     */
/*J*/
    public static class ItemValue extends Item
    {
/*C*
public:
    class ItemValue : public JBase<ItemValue>, public Item
    {
/**/
        /** タイトル文字列。 */
/*J*/
        protected String title;
/*C*
    protected:
        String title;
/**/
        /** 値範囲。 */
/*J*/
        protected int min, max;
/*C*
    protected:
        int min, max;
/**/
        /** 時間。 */
/*J*/
        protected long time_start1, time_span_begin1, time_span_end1;
/*C*
    protected:
        long time_start1, time_span_begin1, time_span_end1;
/**/
        /** 時間。 */
/*J*/
        protected long time_start2, time_span_begin2, time_span_end2;
/*C*
    protected:
        long time_start2, time_span_begin2, time_span_end2;
/**/

        /**
         * 値範囲項目を構築する。
         * 
         * @param   panel   この項目が存在するパネル。
         * @param   title   タイトル文字列。
         * @param   min     最小値。
         * @param   max     最大値。
         * @param   item_cur    現在選択されている列項目のインデックス。
         */
/*J*/
        public ItemValue(JavaPanel panel, String title, int min, int max, int item_cur) {
            super(panel);
/*C*
#endif
#ifdef _IS_H_
    public:
        ItemValue(JavaPanel* panel, String title, int min, int max, int item_cur);
#else
        JavaPanel::ItemValue::ItemValue(JavaPanel* panel, String title, int min, int max, int item_cur)
            : Item(panel) {
/**/
            this.title = title;
            this.min = min;
            this.max = max;
            this.item_cur = item_cur;
            this.time_start1 = this.time_span_begin1 = this.time_span_end1 = 0;
            this.time_start2 = this.time_span_begin2 = this.time_span_end2 = 0;
        }

        /**
         * カーソルを移動する。
         * 
         * @param   cur
         */
/*J*/
        public boolean move_y(boolean cur) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual boolean move_y(boolean cur);
#else
        boolean JavaPanel::ItemValue::move_y(boolean cur) {
            JSTATIC(System);
/**/
            if (false != cur)
            {
                // start
                time_start1 = time_start2 = System.currentTimeMillis();
                time_span_begin1 = time_span_begin2 = -1;
                time_span_end1 = (item_cur == max) ? 0 : -1;
                time_span_end2 = (item_cur == min) ? 0 : -1;
            }
            else
            {
                // stop
                if (item_cur != max)
                {
                    long span1 = System.currentTimeMillis() - time_start1;
                    time_span_end1 = span1 - span1 % TIME_SPAN_ARROW + TIME_SPAN_ARROW;
                }
                if (item_cur != min)
                {
                    long span2 = System.currentTimeMillis() - time_start2;
                    time_span_end2 = span2 - span2 % TIME_SPAN_ARROW + TIME_SPAN_ARROW;
                }
            }
            return true;
        }

        /**
         * カーソルを移動する。
         * 
         * @param dir
         */
/*J*/
        public void move_x(int dir) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual void move_x(int dir);
#else
        void JavaPanel::ItemValue::move_x(int dir) {
            JSTATIC(System);
/**/
            if (dir > 0)
            {
                if (item_cur + dir <= max)
                {
                    item_cur += dir;
                    // restart
                    time_start1 = System.currentTimeMillis();
                    time_span_begin1 = TIME_SPAN_ARROW;
                    if (item_cur == max)
                    {
                        // stop
                        time_span_end1 = TIME_SPAN_ARROW;
                    }
                }
                if (-1 != time_span_end2)
                {
                    // start
                    time_start2 = System.currentTimeMillis();
                    time_span_begin2 = time_span_end2 = -1;
                }
            }
            else
            if (dir < 0)
            {
                if (item_cur + dir >= min)
                {
                    item_cur += dir;
                    // restart
                    time_start2 = System.currentTimeMillis();
                    time_span_begin2 = TIME_SPAN_ARROW;
                    if (item_cur == min)
                    {
                        // stop
                        time_span_end2 = TIME_SPAN_ARROW;
                    }
                }
                if (-1 != time_span_end1)
                {
                    // start
                    time_start1 = System.currentTimeMillis();
                    time_span_begin1 = time_span_end1 = -1;
                }
            }
        }

        /**
         * 項目を描画する。
         * 
         * @param   g       描画に使用するグラフィックコンテキスト。
         * @param   x       x 座標。
         * @param   y       y 座標。
         * @return  項目の座標。
         */
/*J*/
        public Rectangle update(Graphics g, int x, int y) {
/*C*
#endif
#ifdef _IS_H_
    public:
        virtual Rectangle update(Graphics* g, int x, int y);
#else
        Rectangle JavaPanel::ItemValue::update(Graphics* g, int x, int y) {
            JMEMBER(JavaPanel, panel);
/**/
            Rectangle r;
            r = panel.drawString(g, COLOR_ITEM_TITLE, title, x, y, false);
            int color1 = (item_cur == max) ? COLOR_ARROW_DISABLED : COLOR_ARROW;
            int color2 = (item_cur == min) ? COLOR_ARROW_DISABLED : COLOR_ARROW;
            r = draw_arrow(g, color1, r.x + r.width, y, +1, false, time_start1, time_span_begin1, time_span_end1);
            r = draw_arrow(g, color2, r.x          , y, -1, false, time_start2, time_span_begin2, time_span_end2);
            r = panel.drawString(g, COLOR_ITEM, "" + item_cur, r.x + r.width, y, false);
            return r;
        }
/*J*/
    }
}
/*C*
#endif
#ifdef _IS_H_
    };
};
#endif
/**/

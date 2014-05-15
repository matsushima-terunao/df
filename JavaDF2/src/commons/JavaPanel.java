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
 * �p�l���̊�{�N���X�B
 * 
 * @since   1.0 2000 matsushima
 * @author  1.0 2000 matsushima
 * @version $Id: JavaPanel.java,v 1.13 2008/03/06 16:44:00 matsushima Exp $
 * 
 * $Log: JavaPanel.java,v $
 * Revision 1.13  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen �Ή�
 *
 * Revision 1.12  2008/03/06 15:39:50  matsushima
 * h/cpp ���ʉ�
 *
 * Revision 1.11  2008/03/04 17:21:01  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.10  2007/12/01 22:14:14  matsushima
 * �ēo�^
 *
 * Revision 1.12  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.11  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.10  2007/05/14 13:38:20  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.7  2007/05/10 22:29:39  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * ���v���[�X
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
     * �p�l�����\�z����B
     * 
     * @param   left        �p�l���̍��㑤�� x ���W�B
     * @param   top         �p�l���̍��㑤�� y ���W�B
     * @param   width       �p�l���̕��B
     * @param   height      �p�l���̍����B
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
     * �p�l����j������B
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
     * ���ڂ�ݒ肷��B
     * 
     * @param   items       ���ڂ̔z��B
     * @param   item_cnt    items �̐��B
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
     * �p�l�����J���B
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
     * �p�l�����J����Ă��邩��Ԃ��B
     * 
     * @return  �p�l�����J����Ă���Ƃ� true�B
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
     * �p�l�������B
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
     * �p�l����̃L�[�C�x���g����������B
     * 
     * @param   e   �L�[�C�x���g�B
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
     * ���ڂ̃J�[�\���� y �����Ɉړ�����B
     * 
     * @param   d   �ړ��ʁB
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
                break; // �s���ڂ��񍀖ڂ������Ă���̂Ŏ~�܂�
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
     * �p�l�����ĕ`�悷��B
     * 
     * @param   g   �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
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
                // close() ���Ăяo����Ă��� time_span_close �̊Ԃ͕���A�N�V������
            }
        }
        if (null != graphOff)
        {
            g = graphOff; // �I�t�X�N���[���o�b�t�@�ɕ`��
        }
        long span_open = System.currentTimeMillis() - time_open;
        long span_close = System.currentTimeMillis() - time_close;
        if (span_close < time_span_close)
        {
            // close() ���Ăяo����Ă��� time_span_close �̊Ԃ͕���A�N�V������
            int h = (int)(height - height * span_close / time_span_close);
            drawBackground(g, COLOR_BACKGROUND, left, top + (height - h) / 2, width, h, false);
        }
        else
        if (span_open < time_span_open)
        {
            // open() ���Ăяo����Ă��� time_span_open �̊Ԃ͊J���A�N�V������
            int h = (int)(height * span_open / time_span_open);
            drawBackground(g, COLOR_BACKGROUND, left, top + (height - h) / 2, width, h, false);
        }
        else
        {
            drawBackground(g, COLOR_BACKGROUND, left, top, width, height, false);
        }
        // ���ڂ�`��
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
     * �J�[�\����`�悷��B
     * 
     * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     * @param   color   �F�B
     * @param   x       x ���W�B
     * @param   y       y ���W�B
     * @param   calc    �`�悹���ɗ̈�̌v�Z�̂ݍs���ꍇ true�B
     * @return  �`��̈�B
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
     * �w�i��`�悷��B
     * 
     * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     * @param   color   �F�B
     * @param   x       x ���W�B
     * @param   y       y ���W�B
     * @param   width   ���B
     * @param   height  �����B
     * @param   calc    �`�悹���ɗ̈�̌v�Z�̂ݍs���ꍇ true�B
     * @return  �`��̈�B
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
     * �������`�悷��B
     * 
     * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     * @param   color   �F�B
     * @param   str     ������B
     * @param   x       x ���W�B
     * @param   y       y ���W�B
     * @param   calc    �`�悹���ɗ̈�̌v�Z�̂ݍs���ꍇ true�B
     * @return  �`��̈�B
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
     * �J�[�\����`�悷��B
     * 
     * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     * @param   color   �F�B
     * @param   x       x ���W�B
     * @param   y       y ���W�B
     * @param   calc    �`�悹���ɗ̈�̌v�Z�̂ݍs���ꍇ true�B
     * @return  �`��̈�B
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
     * ����`�悷��B
     * 
     * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
     * @param   color   �F�B
     * @param   x       x ���W�B
     * @param   y       y ���W�B
     * @param   d       ���̌����B
     * @param   calc    �`�悹���ɗ̈�̌v�Z�̂ݍs���ꍇ true�B
     * @return  �`��̈�B
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
     * �p�l���̍��ڂ̒��ۃN���X�B
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
         * ���̍��ڂ����݂���p�l���B
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
         * ���ڂ��\�z����B
         * 
         * @param   panel   ���̍��ڂ����݂���p�l���B
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
         * ���ڂ�j������B
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
         * �J�[�\�����ړ�����B
         * 
         * @param   cur
         * @return  ���������Ƃ� true�B
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
         * �J�[�\�����ړ�����B
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
         * ���ڂ�`�悷��B
         * 
         * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
         * @param   x       x ���W�B
         * @param   y       y ���W�B
         * @return  ���ڂ̍��W�B
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
         * �J�[�\����`�悷��B
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
         * @return  ���ڂ̍��W�B
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
     * �^�C�g�����ځB
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
         * �^�C�g��������B
         */
/*J*/
        protected String title;
/*C*
    protected:
        String title;
/**/

        /**
         * �^�C�g�����ڂ��\�z����B
         * 
         * @param   panel   ���̍��ڂ����݂���p�l���B
         * @param   title   �^�C�g��������B
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
         * ���ڂ�`�悷��B
         * 
         * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
         * @param   x       x ���W�B
         * @param   y       y ���W�B
         * @return  ���ڂ̍��W�B
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
     * �I�����ځB
     */
/*J*/
    public static class ItemSelect extends Item
    {
/*C*
public:
    class ItemSelect : public JBase<ItemSelect>, public Item
    {
/**/
        /** �^�C�g��������B */
/*J*/
        protected String title;
/*C*
    protected:
        String title;
/**/
        /** �񍀖ځB */
/*J*/
        protected String[] items;
/*C*
    protected:
        String* items;
/**/
        /** �񍀖ڂ̐��B */
/*J*/
        protected int item_cnt;
/*C*
    protected:
        int item_cnt;
/**/
        /** ���ԁB */
/*J*/
        protected long time, time_span_begin, time_span_end;
/*C*
    protected:
        long time, time_span_begin, time_span_end;
/**/

        /**
         * �I�����ڂ��\�z����B
         * 
         * @param   panel       ���̍��ڂ����݂���p�l���B
         * @param   title       �^�C�g��������B
         * @param   items       �񍀖ڂ̔z��B
         * @param   item_cnt    �񍀖ڂ̐��B
         * @param   item_cur    ���ݑI������Ă���񍀖ڂ̃C���f�b�N�X�B
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
         * ���ڂ�j������B
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
         * �J�[�\�����ړ�����B
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
         * �J�[�\�����ړ�����B
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
         * ���ڂ�`�悷��B
         * 
         * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
         * @param   x       x ���W�B
         * @param   y       y ���W�B
         * @return  ���ڂ̍��W�B
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
     * �l�͈͍��ځB
     */
/*J*/
    public static class ItemValue extends Item
    {
/*C*
public:
    class ItemValue : public JBase<ItemValue>, public Item
    {
/**/
        /** �^�C�g��������B */
/*J*/
        protected String title;
/*C*
    protected:
        String title;
/**/
        /** �l�͈́B */
/*J*/
        protected int min, max;
/*C*
    protected:
        int min, max;
/**/
        /** ���ԁB */
/*J*/
        protected long time_start1, time_span_begin1, time_span_end1;
/*C*
    protected:
        long time_start1, time_span_begin1, time_span_end1;
/**/
        /** ���ԁB */
/*J*/
        protected long time_start2, time_span_begin2, time_span_end2;
/*C*
    protected:
        long time_start2, time_span_begin2, time_span_end2;
/**/

        /**
         * �l�͈͍��ڂ��\�z����B
         * 
         * @param   panel   ���̍��ڂ����݂���p�l���B
         * @param   title   �^�C�g��������B
         * @param   min     �ŏ��l�B
         * @param   max     �ő�l�B
         * @param   item_cur    ���ݑI������Ă���񍀖ڂ̃C���f�b�N�X�B
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
         * �J�[�\�����ړ�����B
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
         * �J�[�\�����ړ�����B
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
         * ���ڂ�`�悷��B
         * 
         * @param   g       �`��Ɏg�p����O���t�B�b�N�R���e�L�X�g�B
         * @param   x       x ���W�B
         * @param   y       y ���W�B
         * @return  ���ڂ̍��W�B
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

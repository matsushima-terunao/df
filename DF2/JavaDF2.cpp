/*
 * $Id: JavaDF2.cpp,v 1.34 2008/04/11 22:52:31 matsushima Exp $
 */

/*J*
package javadf2;

import java.awt.Graphics;
import java.awt.event.KeyEvent;

import Java3D::Java3D;
import Java3D::Java3DModel;
import Java3D::Java3DWorld;

import commons.JavaApplet;
import commons.JavaPanel;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/awt/Graphics"
#include "../cpp2javalib/java/awt/event/KeyEvent"

#include "Java3D.cpp"
#include "Java3DModel.cpp"
#include "Java3Dworld.cpp"

#include "JavaApplet.cpp"
#include "JavaPanel.cpp"

#include "JavaDF2Models.cpp"
#include "JavaDF2Panel.cpp"

#else // cpp

#define _IS_H_
#include "JavaDF2.cpp"
#undef _IS_H_

#endif
/**/

/**
 * メインアプレット。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: JavaDF2.cpp,v 1.34 2008/04/11 22:52:31 matsushima Exp $
 * 
 * $Log: JavaDF2.cpp,v $
 * Revision 1.34  2008/04/11 22:52:31  matsushima
 * gound 修正
 *
 * Revision 1.33  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.32  2008/03/11 16:20:59  matsushima
 * RenderBuffer マルチスレッド化
 *
 * Revision 1.13  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.30  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.29  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.28  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.27  2007/05/28 00:43:04  matsushima
 * no message
 *
 * Revision 1.26  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.25  2007/05/23 18:30:21  matsushima
 * JavaRender カプセル化
 *
 * Revision 1.19  2007/05/16 20:57:58  matsushima
 * テクスチャマッピング
 *
 * Revision 1.15  2007/05/11 09:01:40  matsushima
 * パフォーマンス測定
 *
 * Revision 1.13  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.11  2007/05/09 20:54:38  matsushima
 * パフォーマンス測定
 *
 * Revision 1.9  2007/05/07 21:24:08  matsushima
 * staticメンバアクセス :: -> .
 *
 * Revision 1.8  2007/05/07 18:53:16  matsushima
 * gouraud_alpha アセンブラ
 *
 * Revision 1.6  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.4  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 * Revision 1.2  2006/08/18 11:40:23  matsushima
 * mode
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*
public class JavaDF2 extends JavaApplet
{
/*C*/
#ifdef _IS_H_
class JavaDF2 : public JavaApplet
{
/**/
/*J*
    public static final int
/*C*/
public:
    enum {
/**/
        RUN_TIME = 30
/*J*
    ;
/*C*/
    };
/**/

    /**
     * 
     */
/*J*
    private static final long serialVersionUID = 2209484151691700689L;
/**/

    /** 設定パネル。 */
/*J*
    private JavaDF2Panel panel;
/*C*/
private:
    JavaDF2Panel* panel;
/**/
    /** 3D 空間。 */
/*J*
    private Java3DWorld world;
/*C*/
private:
    Java3DWorld* world;
/**/
    /** 3D モデル。 */
/*J*
    private JavaDF2Models models;
/*C*/
private:
    JavaDF2Models* models;
/**/
    /** デバッグ用 3D モデル。 */
/*J*
    private Java3DModel model_view;
/*C*/
private:
    Java3DModel* model_view;
/**/

    /** キー。 */
/*J*
    boolean key_f1, key_f2, key_f3, key_f4, key_f5, key_f6, key_f7, key_f8, key_f9, key_f10, key_f11, key_f12;
/*C*/
    boolean key_f1, key_f2, key_f3, key_f4, key_f5, key_f6, key_f7, key_f8, key_f9, key_f10, key_f11, key_f12;
/**/
    /** キー。 */
/*J*
    boolean key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9, key_0;
/*C*/
    boolean key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9, key_0;
/**/
    /** キー。 */
/*J*
    boolean key_left, key_right, key_up, key_down, key_pageup, key_pagedown, key_home, key_end, key_insert, key_delete;
/*C*/
    boolean key_left, key_right, key_up, key_down, key_pageup, key_pagedown, key_home, key_end, key_insert, key_delete;
/**/
    /** キー。 */
/*J*
    boolean key_p, key_s, key_v;
/*C*/
    boolean key_p, key_s, key_v;
/**/
    /** キー。 */
/*J*
    boolean key_minus, key_circum; // - ^
/*C*/
    boolean key_minus, key_circum; // - ^
#endif
/**/

    /**
     * メインアプレットを作成する。
     */
/*J*
    public JavaDF2() {
/*C*/
#ifdef _IS_H_
public:
    JavaDF2();
#else
    JavaDF2::JavaDF2() {
/**/
        panel = null;
        world = null;
        models = null;
        model_view = null;
        key_f1 = key_f2 = key_f3 = key_f4 = key_f5 = key_f6 = key_f7 = key_f8 = key_f9 = key_f10 = key_f11 = key_f12 = false;
        key_1 = key_2 = key_3 = key_4 = key_5 = key_6 = key_7 = key_8 = key_9 = key_0 = false;
        key_left = key_right = key_up = key_down = key_pageup = key_pagedown = key_home = key_end = key_insert = key_delete = false;
        key_p = key_s = key_v = false;
        key_minus = key_circum = false;
    }
/*C*/
#endif
/**/

    /**
     * メインアプレットを破棄する。
     */
/*C*/
#ifdef _IS_H_
public:
    virtual ~JavaDF2();
#else
    JavaDF2::~JavaDF2() {
        delete world;
        if (NULL != models)
        {
            delete models;
        }
        if (NULL != panel)
        {
            delete panel;
        }
    }
#endif
/**/

    /**
     * アプレット初期化時に呼び出される。
     */
/*J*
    @Override // JavaApplet
    public void init() {
/*C*/
#ifdef _IS_H_
public:
    void init();
#else
    void JavaDF2::init() {
/**/
        /*C*/JavaApplet::/**/init(false); // オフスクリーンイメージを作成しない
        // 空間
        world = new Java3DWorld(this, this, imageOff,
            getBounds().width, getBounds().height,
            getBounds().width / 2, getBounds().height / 2);
        world->setViewport(getBounds().width / 2, getBounds().height / 2);
        world->setPerspective(60, world->max_z, world->clip_z, (int)(0.1 * world->eye_z), 0);
        // モデル
        models = new JavaDF2Models(world, world);
        // 背景
  //      _R(models).init_background(JavaDF2Models/*J*./*C*/::/**/KIND_BG_GROUND);
        _R(models).init_background(JavaDF2Models/*J*./*C*/::/**/KIND_BG_EARTH);
        //model_view = models;
        // 設定パネル
        panel = new JavaDF2Panel((getBounds().width - 480) / 2, (getBounds().height - 320) / 2, 480, 320,
            this, null/*((JavaRenderGraphics)world->render.render_draw).graphOff*/,
            *world);
    }
/*C*/
#endif
/**/

    /**
     * アプレット破棄時に呼び出される。
     */
/*J*
    @Override // JavaApplet
    public void destroy() {
        super.destroy();
/*C*/
#ifdef _IS_H_
public:
    void destroy();
#else
    void JavaDF2::destroy() {
        JavaApplet::destroy();
/**/
        world->destroy();
    }
/*C*/
#endif
/**/

/*J*
    protected long run_each() {
/*C*/
#ifdef _IS_H_
protected:
    long run_each();
#else
    long JavaDF2::run_each() {
/**/
        translate();
        int mode_bak = world->render_mode;
        if (rest_time >= RUN_TIME)
        {
            ++ skip_cnt;
            run_each_time->skip_count = true;
//showStatus("skip");
        }
        else
        {
//showStatus("");
            models->transform();
            panel->update(null);
            //world->render->clear(); render() 内
            world->render->render();
int y = 0;
world->get_render_paint().drawString(0x00ffffff, 10, y+=12, String("run        : ") + (int)run_time->span_ave + " : " + run_time->toString(), false, world->render->render_font);
world->get_render_paint().drawString(0x00ffffff, 10, y+=12, String("run_each   : ") + (int)run_each_time->span_ave + " : " + run_each_time->toString(), false, world->render->render_font);
if (null != model_view) {
Java3D/*C*/* /**/ m = model_view;
world->get_render_paint().drawString(0x00ffffff, 10, y+=12, String(m->ma) + "," + m->mb + ";" + m->mx + "," + m->my + "," + m->mz, false, _R(world->render).render_font);
    }
Java3D/*C*/* /**/ m = world;
world->get_render_paint().drawString(0x00ffffff, 10, y+=12, String("mabc=") + m->ma + "," + m->mb + "," + m->mc + ";mxyz=" + m->mx + "," + m->my + "," + m->mz + ";vab=" + m->va + "," + m->vb + ";vxyz" + m->vx + "," + m->vy + "," + m->vz, false, _R(world->render).render_font);
String s;
s = Integer::toHexString(world->render_mode);
if (null != models->model_bg_earth)
{
s += String(", ") + Integer::toHexString(models->model_bg_earth->render_mode) + ", " + Integer::toHexString(models->model_bg_earth->get_render_mode());
}
world->get_render_paint().drawString(0x00ffffff, 10, y+=12, s, false, _R(world->render).render_font);
world->get_render_paint().drawString(0x00ffffff, 10, y+=12, String("e_cnt = ") + models->e_cnt + ", f_cnt = " + (models->f1_cnt + models->f2_cnt) + ", f1_cnt = " + models->f1_cnt + ", f2_cnt = " + models->f2_cnt, false, _R(world->render).render_font);
world->get_render_paint().drawString(0x00ffffff, 10, getBounds().height - 32, "F1:Default F2:Polyline F3:Polyframe F4:Polygon", true, _R(world->render).render_fontp);
int r = world->render_mode;
world->get_render_paint().drawString(0x00ffffff, 10, getBounds().height - 16,
String("F5:Texture") + ((0 != (Java3D::SHADING_TEXTURE & r)) ? "+" : "-")
+ " F6:Gouraud" + ((0 != (Java3D::SHADING_GOURAUD & r)) ? "+" : "-")
+ " F7:Alpha" + ((0 != (Java3D::SHADING_ALPHA & r)) ? "+" : "-")
+ " F8:Diffuse" + ((0 != (Java3D::LIGHTING_DIFFUSE & r)) ? "+" : "-")
+ " F9:Fog" + ((0 != (Java3D::LIGHTING_FOG & r)) ? "+" : "-")
+ " F11:Append" + ((0 != (Java3D::APPEND_SORT & r)) ? "+" : "-")
+ " 4-8:Unit" + models->get_background_unit(),
true, _R(world->render).render_fontp);

            _R(world->render).repaint();
            world->render_mode = mode_bak;
            _R(world->translate_time).count();
            _R(world->transform_time).count();
            _R(world->append_time).count();
        }
        return -RUN_TIME;
    }
/*C*/
#endif
/**/

/*J*
    public void update(Graphics g) {
/*C*/
#ifdef _IS_H_
public:
    void update(Graphics* g);
#else
    void JavaDF2::update(Graphics* g) {
/**/
        paint(g);
    }
/*C*/
#endif
/**/

/*J*
    public void paint(Graphics g) {
/*C*/
#ifdef _IS_H_
public:
    void paint(Graphics* g);
#else
    void JavaDF2::paint(Graphics* g) {
/**/
        world->render->paint(g, this);
    }
/*C*/
#endif
/**/

/*J*
    public boolean isDoubleBuffered() {
/*C*/
#ifdef _IS_H_
public:
    bool isDoubleBuffered();
#else
    bool JavaDF2::isDoubleBuffered() {
/**/
        return true;
    }
/*C*/
#endif
/**/

/*J*
    public void keyPressed(KeyEvent e) {
/*C*/
#ifdef _IS_H_
public:
    void keyPressed(KeyEvent* e);
#else
    void JavaDF2::keyPressed(KeyEvent* e) {
/**/
        key_common(e, true);
    }
/*C*/
#endif
/**/

/*J*
    public void keyReleased(KeyEvent e) {
/*C*/
#ifdef _IS_H_
public:
    void keyReleased(KeyEvent* e);
#else
    void JavaDF2::keyReleased(KeyEvent* e) {
/**/
        key_common(e, false);
    }
/*C*/
#endif
/**/

/*J*
    private void key_common(KeyEvent e, boolean key_pressed) {
/*C*/
#ifdef _IS_H_
private:
    void key_common(KeyEvent* e, boolean key_pressed);
#else
    void JavaDF2::key_common(KeyEvent* e, boolean key_pressed) {
/**/
        if (null != panel)
        {
            panel->processKeyEvent(e);
        }
        switch (e->getKeyCode())
        {
        case KeyEvent::VK_F1: key_f1 |= key_pressed; break;
        case KeyEvent::VK_F2: key_f2 |= key_pressed; break;
        case KeyEvent::VK_F3: key_f3 |= key_pressed; break;
        case KeyEvent::VK_F4: key_f4 |= key_pressed; break;
        case KeyEvent::VK_F5: key_f5 |= key_pressed; break;
        case KeyEvent::VK_F6: key_f6 |= key_pressed; break;
        case KeyEvent::VK_F7: key_f7 |= key_pressed; break;
        case KeyEvent::VK_F8: key_f8 |= key_pressed; break;
        case KeyEvent::VK_F9: key_f9 |= key_pressed; break;
        case KeyEvent::VK_F10: key_f10 |= key_pressed; break;
        case KeyEvent::VK_F11: key_f11 |= key_pressed; break;
        case KeyEvent::VK_F12: key_f12 |= key_pressed; break;
        case KeyEvent::VK_1: key_1 |= key_pressed; break;
        case KeyEvent::VK_2: key_2 |= key_pressed; break;
        case KeyEvent::VK_3: key_3 |= key_pressed; break;
        case KeyEvent::VK_4: key_4 |= key_pressed; break;
        case KeyEvent::VK_5: key_5 |= key_pressed; break;
        case KeyEvent::VK_6: key_6 |= key_pressed; break;
        case KeyEvent::VK_7: key_7 |= key_pressed; break;
        case KeyEvent::VK_8: key_8 |= key_pressed; break;
        case KeyEvent::VK_9: key_9 |= key_pressed; break;
        case KeyEvent::VK_0: key_0 |= key_pressed; break;
        case KeyEvent::VK_LEFT : key_left  = key_pressed; break;
        case KeyEvent::VK_RIGHT: key_right = key_pressed; break;
        case KeyEvent::VK_UP   : key_up    = key_pressed; break;
        case KeyEvent::VK_DOWN : key_down  = key_pressed; break;
        case KeyEvent::VK_PAGE_UP   : key_pageup    = key_pressed; break;
        case KeyEvent::VK_PAGE_DOWN : key_pagedown  = key_pressed; break;
        case KeyEvent::VK_HOME: key_home  = key_pressed; break;
        case KeyEvent::VK_END : key_end   = key_pressed; break;
        case KeyEvent::VK_INSERT: key_insert = key_pressed; break;
        case KeyEvent::VK_DELETE: key_delete = key_pressed; break;
        case '-': key_minus = key_pressed; break;
        case '^': key_circum = key_pressed; break;
        //case KeyEvent::VK_P: key_p |= key_pressed; break;
        case KeyEvent::VK_P: if (false != key_pressed) { world->is_pause = ! world->is_pause; } break;
        case KeyEvent::VK_S: if (false != key_pressed) { world->is_stop  = ! world->is_stop; } break;
        case KeyEvent::VK_V: if (false != key_pressed) { world->is_view  = ! world->is_view; } break;
        }
    }
/*C*/
#endif
/**/

/*J*
    private void translate() {
/*C*/
#ifdef _IS_H_
private:
    void translate();
#else
    void JavaDF2::translate() {
/**/
        // モード変更
        //                   def       line      frame     poly
        boolean is_render = key_f1 || key_f2 || key_f3 || key_f4;
        boolean is_resolution = key_4 || key_5 || key_6 || key_7 || key_8;
        boolean is_texture = key_f5;
        boolean is_gouraud = key_f6;
        boolean is_alpha = key_f7;
        boolean is_diffuse = key_f8;
        boolean is_fog = key_f9;
        boolean is_sort = key_f11;
        int mode_exc_render = world->render_mode & ~Java3D::RENDER_MASK;
        if (key_f1) { key_f1 = false; world->render_mode = mode_exc_render | (Java3D::RENDER_DEFAULT & Java3D::RENDER_MASK); }
        if (key_f2) { key_f2 = false; world->render_mode = mode_exc_render | Java3D::RENDER_POLYLINE; }
        if (key_f3) { key_f3 = false; world->render_mode = mode_exc_render | Java3D::RENDER_POLYFRAME; }
        if (key_f4) { key_f4 = false; world->render_mode = mode_exc_render | Java3D::RENDER_POLYGON; }
        if (key_f5) { key_f5 = false; world->render_mode ^= Java3D::SHADING_TEXTURE; }
        if (key_f6) { key_f6 = false; world->render_mode ^= Java3D::SHADING_GOURAUD; }
        if (key_f7) { key_f7 = false; world->render_mode ^= Java3D::SHADING_ALPHA; }
        if (key_f8) { key_f8 = false; world->render_mode ^= Java3D::LIGHTING_DIFFUSE; }
        if (key_f9) { key_f9 = false; world->render_mode ^= Java3D::LIGHTING_FOG; }
        if (key_f11) { key_f11 = false; world->render_mode ^= Java3D::APPEND_SORT | Java3D::APPEND_BACK; }
        if (key_4) { key_4 = false; models->set_background_unit(4); }
        if (key_5) { key_5 = false; models->set_background_unit(5); }
        if (key_6) { key_6 = false; models->set_background_unit(6); }
        if (key_7) { key_7 = false; models->set_background_unit(7); }
        if (key_8) { key_8 = false; models->set_background_unit(8); }
        // 移動
        int dx = 0, dy = 0;
        if (key_left ) { dx += 1; }
        if (key_right) { dx -= 1; }
        if (key_up   ) { dy += 1; }
        if (key_down ) { dy -= 1; }
        if (key_home)
        {
            world->setViewport(getBounds().width / 2, getBounds().height / 2);
            world->setPerspective(60, world->max_z, world->clip_z, (int)(0.1 * world->eye_z), 0);
        }
        // ショット
        models->shot_on = ((mouseButton1) && (0 == (frame_cnt & 0x0001)));
        //
        if (key_end)
        {
//            world->setViewport(world->viewport_width / 2, world->viewport_height * 6 / 5);
//            int angle = 75;//75;//120;
//            world->setPerspective(angle, world->max_z, world->clip_z, (int)(world->max_z * 1.0), - (int)(angle * Java3D::ANGLE_MAX / 360 / 2.0));
            world->setViewport(world->viewport_width / 2, world->viewport_height * 6 / 5);
            int angle = 75;//75;//120;
            world->setPerspective(angle, world->max_z, world->max_z, (int)(world->max_z * 1.0), - (int)(angle * Java3D::ANGLE_MAX / 360 / 2.0));
        }
/*model*
if (model_view)
{
model_view.ma -= dx * 10;
model_view.mb -= dy * 10;
if (key_pageup  ) { model_view.mz += 10; }
if (key_pagedown) { model_view.mz -= 10; }
}
if (key_home    ) { world->lz += 10; }
if (key_end     ) { world->lz -= 10; }
if (key_insert  ) { world->lx += 10; }
if (key_delete  ) { world->lx -= 10; }
return;
/**/
        if (false == world->is_pause)
        {
            if (false != panel->opened())
            {
                panel->close();
            }
            world->translate(dx, dy, 1);
            if (0 == run_time->count1 % 3)
            {
                models->init_enemy(JavaDF2Models::KIND_ROCK1);
            }
            models->translate(mouseX, mouseY);
        }
        else
        {
            if (false == panel->opened())
            {
                panel->open();
                is_render = is_resolution = is_texture = is_gouraud = is_alpha = is_diffuse = is_fog = is_sort = true;
            }
        }
        // モード変更
        if (panel->opened())
        {
            int items[]     = { JavaDF2Panel::ITEM_RENDER, JavaDF2Panel::ITEM_RESOLUTION, JavaDF2Panel::ITEM_SHADING_TEXTURE, JavaDF2Panel::ITEM_SHADING_GOURAUD, JavaDF2Panel::ITEM_SHADING_ALPHA, JavaDF2Panel::ITEM_LIGHTING_DIFFUSE, JavaDF2Panel::ITEM_LIGHTING_FOG, JavaDF2Panel::ITEM_APPEND_SORT, -1 };
            int masks[]     = { Java3D::RENDER_MASK      , -1                          , Java3D::SHADING_TEXTURE           , Java3D::SHADING_GOURAUD           , Java3D::SHADING_ALPHA           , Java3D::LIGHTING_DIFFUSE           , Java3D::LIGHTING_FOG           , Java3D::APPEND_SORT };
            boolean flags[] = { is_render               , is_resolution               , is_texture                       , is_gouraud                       , is_alpha                       , is_diffuse                        , is_fog                        , is_sort };
            int i;
            for (i = 0; -1 != items[i]; ++ i)
            {
                /*J*JavaPanel.Item item = panel.items[items[i]];/**/
                /*C*/JavaPanel::Item* item = panel->items[items[i]];/**/
                switch (items[i])
                {
                case JavaDF2Panel::ITEM_RENDER:
                    if (flags[i])
                    {
                        if ((Java3D::RENDER_DEFAULT & Java3D::RENDER_MASK) == (world->render_mode & Java3D::RENDER_MASK))
                        {
                            item->item_cur = 0;
                        }
                        else
                        {
                            switch (world->render_mode & Java3D::RENDER_MASK)
                            {
                            case Java3D::RENDER_POLYLINE:   item->item_cur = 1; break;
                            case Java3D::RENDER_POLYFRAME:  item->item_cur = 2; break;
                            case Java3D::RENDER_POLYGON:    item->item_cur = 3; break;
                            }
                        }
                    }
                    else
                    {
                        switch (item->item_cur)
                        {
                        case 0: world->render_mode = mode_exc_render | (Java3D::RENDER_DEFAULT & Java3D::RENDER_MASK); break;
                        case 1: world->render_mode = mode_exc_render | Java3D::RENDER_POLYLINE; break;
                        case 2: world->render_mode = mode_exc_render | Java3D::RENDER_POLYFRAME; break;
                        case 3: world->render_mode = mode_exc_render | Java3D::RENDER_POLYGON; break;
                        }
                    }
                    break;
                case JavaDF2Panel::ITEM_RESOLUTION:
                    if (flags[i])
                    {
                        item->item_cur = models->get_background_unit();
                    }
                    else
                    {
                        models->set_background_unit(item->item_cur);
                    }
                    break;
                default:
                    if (flags[i])
                    {
                        item->item_cur = (0 != (world->render_mode & masks[i])) ? 0 : 1;
                    }
                    else
                    {
                        world->render_mode = (0 == item->item_cur)
                            ? world->render_mode | masks[i] : world->render_mode & ~masks[i];
                    }
                    break;
                }
            }
        }
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/

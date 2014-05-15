/*
 * $Id: JavaDF2Panel.java,v 1.11 2008/03/06 16:44:00 matsushima Exp $
 */

/*J*/
package javadf2;

import java.awt.Component;
import java.awt.Graphics;
import java.awt.Rectangle;
import java3d.Java3D;
import java3d.Java3DModel;
import java3d.Java3DWorld;

import commons.JavaPanel;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java.awt.Component"
#include "../cpp2javalib/java.awt.Graphics"
#include "../cpp2javalib/java.awt.Rectangle"

#include "JavaPanel.cpp"

#include "Java3D.cpp"
#include "Java3DModel.cpp"
#include "Java3DWorld.cpp"

class JavaDF2PanelStatic;
extern JavaDF2PanelStatic _JavaDF2PanelStatic;

#else // cpp

#define _IS_H_
#include "JavaDF2Panel.cpp"
#undef _IS_H_

JavaDF2PanelStatic _JavaDF2PanelStatic;

#endif
/**/

/**
 * JavaDF2Panel
 * 
 * @since   1.0 2005/03/29 matsushima
 * @author  1.0 2005/03/29 matsushima
 * @author  1.1 2006/08/01 matsushima
 * @version $Id: JavaDF2Panel.java,v 1.11 2008/03/06 16:44:00 matsushima Exp $
 * 
 * $Log: JavaDF2Panel.java,v $
 * Revision 1.11  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.21  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.20  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.19  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.18  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.17  2007/05/23 18:30:22  matsushima
 * JavaRender カプセル化
 *
 * Revision 1.12  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.9  2007/05/08 15:25:01  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.7  2007/05/07 18:53:16  matsushima
 * gouraud_alpha アセンブラ
 *
 * Revision 1.5  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.3  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 * Revision 1.2  2006/08/18 11:40:23  matsushima
 * mode
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*/
public class JavaDF2Panel extends JavaPanel
{
/*C*
#ifdef _IS_H_
class JavaDF2PanelStatic
{
/**/
/*J*/
    public static final int
/*C*
public:
    enum {
/**/
        ITEM_TITLE              = 0,
        ITEM_RENDER             = 1,
        ITEM_SHADING_TEXTURE    = 2,
        ITEM_SHADING_GOURAUD    = 3,
        ITEM_SHADING_ALPHA      = 4,
        ITEM_LIGHTING_DIFFUSE   = 5,
        ITEM_LIGHTING_FOG       = 6,
        ITEM_APPEND_SORT        = 7,
        ITEM_RESOLUTION         = 8,
        ITEM_COUNT              = 9
/*J*/
    ;
/*C*
    };
/**/
/*C*
};

class JavaDF2Panel : public JBase<JavaDF2Panel>, public JavaPanel, public JavaDF2PanelStatic
{
/**/

/*J*/
    protected Java3DWorld world;
    protected Java3DModel modelBackground;
    protected Java3DModel modelTitle;
    protected Java3DModel modelCursor;
    protected Java3DModel modelArrow;
/*C*
protected:
    Java3DWorld* world;
    Java3DModel* modelBackground;
    Java3DModel* modelTitle;
    Java3DModel* modelCursor;
    Java3DModel* modelArrow;
/**/

/*J*/
    public JavaDF2Panel(int left, int top, int width, int height, Component component, Graphics graphics,
        Java3DWorld world) {
        //super(left, top, width, height, component, graphics);
        super(left, top, width, height, null, null);
/*C*
#endif
#ifdef _IS_H_
public:
    JavaDF2Panel(int left, int top, int width, int height, Component* component, Graphics* graphics,
        Java3DWorld& world);
#else
    JavaDF2Panel::JavaDF2Panel(int left, int top, int width, int height, Component* component, Graphics* graphics,
        Java3DWorld& world)
        //: JavaPanel(left, top, width, height, component, graphics) {
        : JavaPanel(left, top, width, height, null, null) {
#define this (*this)
#define final static
        JSTATIC(Java3D);
/**/
        this.world = world;
        final int EOD = Java3D.EOD;
        final int verts_bg[] = { 0xc0000000,0,0,0, 0x80000000,0,0,0, 0x20000000,0,0,0, 0x80000000,0,0,0, EOD };
//        final int verts_bg[] = { 0xfffffffe,0,0,0, 0x80ffffff,0,0,0, 0x00ffffff,0,0,0, 0x80ffffff,0,0,0, EOD };
        final int polys_bg[] = { 0,1,2,3, EOD, EOD };
        final int lines_bg[] = { 0,1,2,3,0, EOD, EOD };
        final int verts_str[] = { 0,0,-8,0, EOD };
        final int polys_str[] = { 0, EOD, EOD };
        final int verts_cursor[] = { 0,0,-4,0, 0,-4,4,0, 0,4,4,0, EOD };
        final int polys_cursor[] = { 0,1,2, EOD, EOD };
        final int lines_cursor[] = { 0,1,2,0, EOD, EOD };
        final int verts_arrow[] = { 0,0,-6,0, 0,0,0,-6, 0,0,6,0, 0,0,0,6, 0,10,0,0, EOD };
        final int polys_arrow[] = { 0,1,4,EOD, 1,2,4,EOD, 2,3,4,EOD, 3,0,4,EOD, EOD };
        final int lines_arrow[] = { 0,1,4,0,3,4,2,EOD, 1,2,3,EOD, EOD };
        int mask;
        Java3DModel/*C** /**/ model;
        // bg
        mask = Java3D.APPEND_MASK;
        model = new Java3DModel(world, null);
        _R(model).init(Java3DModel/*J*/./*C*::/**/KIND_USED, 0, 0,
            (Java3D.RENDER_DEFAULT & ~mask & ~Java3D.LIGHTING_DIFFUSE/* & ~Java3D.LIGHTING_FOG*/) | Java3D.APPEND_BACK,
            verts_bg, polys_bg, lines_bg);
        modelBackground = model;
        // Title
        mask = Java3D.RENDER_SHADING_MASK | Java3D.APPEND_MASK;
        model = new Java3DModel(world, null);
        _R(model).init(Java3DModel/*J*/./*C*::/**/KIND_USED, 0, 0,
            (Java3D.RENDER_DEFAULT & ~mask) | Java3D.RENDER_STRING | Java3D.APPEND_BACK,
            verts_str, polys_str, null);
        modelTitle = model;
        // Cursor
        mask = Java3D.APPEND_MASK;
        model = new Java3DModel(world, null);
        _R(model).init(Java3DModel/*J*/./*C*::/**/KIND_USED, 0, 0,
            (Java3D.RENDER_DEFAULT & ~mask) | Java3D.APPEND_BACK,
            verts_cursor, polys_cursor, lines_cursor);
        modelCursor = model;
        // Arrow
        mask = Java3D.APPEND_MASK;
        model = new Java3DModel(world, null);
        _R(model).init(Java3DModel/*J*/./*C*::/**/KIND_USED, 0, 0,
            (Java3D.RENDER_DEFAULT & ~mask) | Java3D.APPEND_BACK,
            verts_arrow, polys_arrow, lines_arrow);
        modelArrow = model;
        //
        Item/*J*/[]/*C*** /**/ items = new Item/*C** /**/[ITEM_COUNT];
        int i = 0;
        items[i ++] = new ItemTitle(this, "title");
        final String s1[] = { "Default(F1)", "Polyline(F2)", "Polyframe(F3)", "Polygon(F4)" };
        final String s2[] = { "On", "Off" };
        items[i ++] = new ItemSelect(this, "Render Mode", s1, 4, 0);
        items[i ++] = new ItemSelect(this, "Shading Texture(F5)", s2, 2, 0);
        items[i ++] = new ItemSelect(this, "Shading Gouraud(F6)", s2, 2, 0);
        items[i ++] = new ItemSelect(this, "Shading Alpha(F7)", s2, 2, 0);
        items[i ++] = new ItemSelect(this, "Lighting Diffuse(F8)", s2, 2, 0);
        items[i ++] = new ItemSelect(this, "Lighting Fog(F9)", s2, 2, 0);
        items[i ++] = new ItemSelect(this, "Polygon Sort(F10)", s2, 2, 0);
        items[i ++] = new ItemValue(this, "Background Resolution(4-8)", 4, 8, 8);
        setItems(items, ITEM_COUNT);
    }

/*C*
#endif
#ifdef _IS_H_
public:
    virtual ~JavaDF2Panel();
#else
    JavaDF2Panel::~JavaDF2Panel() {
        delete modelBackground;
        delete modelTitle;
        delete modelCursor;
        delete modelArrow;
    }
/**/

/*J*/
    public Rectangle drawBackground(Graphics g, int color, int x, int y, int width, int height, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawBackground(Graphics* g, int color, int x, int y, int width, int height, boolean calc);
#else
    Rectangle JavaDF2Panel::drawBackground(Graphics* g, int color, int x, int y, int width, int height, boolean calc) {
        JMEMBER(Java3DWorld, world);
        JMEMBER(Java3DModel, modelBackground);
        JSTATIC(Java3DModel);
/**/
        if (false == calc)
        {
            modelBackground.setPosition2D(- world.viewport_x, - world.viewport_y, -10, 1.0);
            Java3DModel.set_vert_xyz(modelBackground.verts, 0, x, y, 0);
            Java3DModel.set_vert_xyz(modelBackground.verts, 1, x, y + height, 0);
            Java3DModel.set_vert_xyz(modelBackground.verts, 2, x + width, y + height, 0);
            Java3DModel.set_vert_xyz(modelBackground.verts, 3, x + width, y, 0);
            modelBackground.transform();
            modelBackground.append();
        }
        return /*J*/new /**/Rectangle(x, y, width, height);
    }

/*J*/
    public Rectangle drawString(Graphics g, int color, String str, int x, int y, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual Rectangle drawString(Graphics* g, int color, _String str, int x, int y, boolean calc);
#else
    Rectangle JavaDF2Panel::drawString(Graphics* g, int color, _String str, int x, int y, boolean calc) {
        JMEMBER(Java3DWorld, world);
        JMEMBER(Java3DModel, modelTitle);
        JSTATIC(Java3DModel);
/**/
        if (false == calc)
        {
            modelTitle.setPosition2D(x - world.viewport_x, y - world.viewport_y, -10, 1.0);
            modelTitle.string = str;
            Java3DModel.set_vert_color(modelTitle.verts, 0, color);
            modelTitle.transform();
            modelTitle.append();
        }
        Rectangle r = world.get_render_draw().calcString(color, 0, 0, 65536 / 4, modelTitle.string, true, _R(world.render).render_fontp);
        return /*J*/new /**/Rectangle(x, y, r.width, r.height);
    }

/*J*/
    public Rectangle drawCursor(Graphics g, int color, int x, int y, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawCursor(Graphics* g, int color, int x, int y, boolean calc);
#else
    Rectangle JavaDF2Panel::drawCursor(Graphics* g, int color, int x, int y, boolean calc) {
        JMEMBER(Java3DWorld, world);
        JMEMBER(Java3DModel, modelCursor);
        JSTATIC(Java3DModel);
/**/
        if (false == calc)
        {
            modelCursor.setPosition2D(x - world.viewport_x, y - world.viewport_y, -10, 1.0);
            Java3DModel.set_vert_color(modelCursor.verts, -1, color);
            modelCursor.transform();
            modelCursor.append();
        }
        return /*J*/new /**/Rectangle(x, y, 10, 10);
    }

/*J*/
    public Rectangle drawArrow(Graphics g, int color, int x, int y, int d, boolean calc) {
/*C*
#endif
#ifdef _IS_H_
public:
    Rectangle drawArrow(Graphics* g, int color, int x, int y, int d, boolean calc);
#else
    Rectangle JavaDF2Panel::drawArrow(Graphics* g, int color, int x, int y, int d, boolean calc) {
        JMEMBER(Java3DWorld, world);
        JMEMBER(Java3DModel, modelArrow);
        JSTATIC(Java3DModel);
/**/
        if (false == calc)
        {
            modelArrow.setPosition2D(x - world.viewport_x, y - world.viewport_y, -10, 1.0);
            modelArrow.ma = (d >= 0) ? 0 : Java3D.ANGLE_MAX / 2;
            modelArrow.mb += 100;
            Java3DModel.set_vert_color(modelArrow.verts, -1, color);
            modelArrow.transform();
            modelArrow.append();
        }
        return /*J*/new /**/Rectangle(x, y, 10, 10);
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
};

static boolean operator !=(JavaDF2Panel& panel, void* p) { return &panel == p ? false : true; }
static boolean operator !=(void* p, JavaDF2Panel& panel) { return &panel == p ? false : true; }
#endif
/**/

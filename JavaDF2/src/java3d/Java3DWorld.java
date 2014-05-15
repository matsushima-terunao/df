/*
 * $Id: Java3DWorld.java,v 1.14 2008/03/11 16:24:17 matsushima Exp $
 */

/*J*/
package java3d;

import java.applet.Applet;
import java.awt.Component;
import java.awt.Image;
import java.util.Random;

import javarender.JavaRenderAbstract;
import javarender.JavaRenderBuffer;

import commons.Log;
import commons.Perf;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java.applet.Applet"
#include "../cpp2javalib/java.awt.Component"
#include "../cpp2javalib/java.awt.Graphics"
#include "../cpp2javalib/java.awt.Image"
#include "../cpp2javalib/java.awt.image.ImageObserver"
#include "../cpp2javalib/java.util.Random"
#include "Java3D.cpp"
#include "JavaRenderBuffer.cpp"

#else // cpp

#define _IS_H_
#include "Java3DWorld.cpp"
#include "Log.cpp"
#undef _IS_H_

#endif
/**/

/**
 * 3D 空間の基本クラス。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: Java3DWorld.java,v 1.14 2008/03/11 16:24:17 matsushima Exp $
 * 
 * $Log: Java3DWorld.java,v $
 * Revision 1.14  2008/03/11 16:24:17  matsushima
 * RenderBuffer マルチスレッド化
 *
 * Revision 1.13  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.34  2008/03/06 15:39:49  matsushima
 * h/cpp 共通化
 *
 * Revision 1.33  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.32  2008/02/24 05:52:06  matsushima
 * JavaRenderInterface -> JavaRender
 * JavaRender -> JavaRenderBuffer
 *
 * Revision 1.31  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.30  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.29  2007/05/23 18:30:21  matsushima
 * JavaRender カプセル化
 *
 * Revision 1.28  2007/05/23 15:41:43  matsushima
 * JavaRender, JavaRenderInterface を Java3D から分離
 *
 * Revision 1.19  2007/05/14 15:58:36  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.18  2007/05/14 13:38:19  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.16  2007/05/11 09:01:40  matsushima
 * パフォーマンス測定
 *
 * Revision 1.15  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.13  2007/05/09 20:54:38  matsushima
 * パフォーマンス測定
 *
 * Revision 1.11  2007/05/08 22:13:37  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.10  2007/05/08 08:33:25  matsushima
 * JavaRenderMemory から JavaRenderMemorySSE2 を分離
 *
 * Revision 1.9  2007/05/07 21:24:08  matsushima
 * staticメンバアクセス :: -> .
 *
 * Revision 1.7  2007/05/07 18:53:16  matsushima
 * gouraud_alpha アセンブラ
 *
 * Revision 1.6  2007/05/05 18:06:03  matsushima
 * clear アセンブラ
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
public class Java3DWorld extends Java3D
{
/*C*
#ifdef _IS_H_
class Java3DWorld : public JBase<Java3DWorld>, public Java3D
{
/**/
/*J*/
    // Parameters
    public int viewport_width, viewport_height;
    public int viewport_x, viewport_y;
    public int fov_angle, max_z, clip_z, eye_z;
    public int pers_scale, pers_distance;
    public int mb0;

    // Status
    public boolean is_pause, is_stop, is_view;

    // Render
    public JavaRenderBuffer render;

    // Perf
    public Perf translate_time;
    public Perf transform_time;
    public Perf append_time;
    public Perf temp1_time;
    public Perf temp2_time;
    public Perf temp3_time;
    public Perf temp4_time;
    public Perf temp5_time;
/*C*
    // Parameters
public:
    int viewport_width, viewport_height;
    int viewport_x, viewport_y;
    int fov_angle, max_z, clip_z, eye_z;
    int pers_scale, pers_distance;
    int mb0;

    // Status
public:
    boolean is_pause, is_stop, is_view;

    // Render
public:
    JavaRenderBuffer* render;

    Perf* translate_time;
    Perf* transform_time;
    Perf* append_time;
    Perf* temp1_time;
    Perf* temp2_time;
    Perf* temp3_time;
    Perf* temp4_time;
    Perf* temp5_time;
/**/

    /**
     * Java3DWorld オブジェクトを構築する。
     */
/*J*/
    private void construct() {
/*C*
#endif
#ifdef _IS_H_
private:
    void construct();
#else
    void Java3DWorld::construct() {
/**/
        // Parameters
        viewport_width  = 640;
        viewport_height = 320;
        viewport_x      = viewport_width / 2;
        viewport_y      = viewport_height / 2;
        fov_angle       = 60;
        max_z           = 4096;
        clip_z          = (int)(max_z * 0.8);
        eye_z           = (int)(max_z * 1.0);
        fog_z           = (int)(max_z * 0.6);//0.6);
        pers_scale      = (int)((viewport_width / 0.5) * (max_z + eye_z) / max_z);
        pers_distance   = 256 * eye_z;
        mb0             = 0;
        //lz              = -300;
        render_mode     = RENDER_INITIAL;

        // Status
        is_pause = is_stop = is_view = false;

        // Render
        render = null;
    }

    /**
     * Java3DWorld オブジェクトを構築する。
     */
/*J*/
    public Java3DWorld() {
/*C*
#endif
#ifdef _IS_H_
public:
    Java3DWorld();
#else
    Java3DWorld::Java3DWorld() {
/**/
        construct();
    }

    /**
     * Java3DWorld オブジェクトを構築する。
     * 
     * @param   applet
     * @param   component
     * @param   image
     * @param   viewport_width
     * @param   viewport_height
     * @param   viewport_x
     * @param   viewport_y
     */
/*J*/
    public Java3DWorld(Applet applet, Component component, Image image,
        int viewport_width, int viewport_height, int viewport_x, int viewport_y) {
/*C*
#endif
#ifdef _IS_H_
public:
    Java3DWorld(Applet* applet, Component* component, Image* image,
        int viewport_width, int viewport_height, int viewport_x, int viewport_y);
#else
    Java3DWorld::Java3DWorld(Applet* applet, Component* component, Image* image,
        int viewport_width, int viewport_height, int viewport_x, int viewport_y) {
#define this (*this)
/**/
        construct();

        random = new Random();
        translate_time    = new Perf();
        transform_time    = new Perf();
        append_time       = new Perf();
        temp1_time        = new Perf();
        temp2_time        = new Perf();
        temp3_time        = new Perf();
        temp4_time        = new Perf();
        temp5_time        = new Perf();

        this.viewport_width    = viewport_width;
        this.viewport_height   = viewport_height;
        this.viewport_x        = viewport_x;
        this.viewport_y        = viewport_y;

        render = new JavaRenderBuffer(applet, component, viewport_width, viewport_height);
    }

    /**
     * Java3DWorld オブジェクトを破棄する。
     */
/*C*
#endif
#ifdef _IS_H_
public:
    virtual ~Java3DWorld();
#else
    Java3DWorld::~Java3DWorld()
    {
        delete random;
        delete translate_time;
        delete transform_time;
        delete append_time;
        delete temp1_time;
        delete temp2_time;
        delete temp3_time;
        delete temp4_time;
        delete temp5_time;

        // Render
        delete render;
    }
/**/

    /**
     * 終了処理。
     */
/*J*/
    public void destroy() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void destroy();
#else
    void Java3DWorld::destroy() {
        JMEMBER(Perf, translate_time);
        JMEMBER(Perf, transform_time);
        JMEMBER(Perf, append_time);
        JMEMBER(JavaRenderBuffer, render);
        JMEMBER(Perf, temp1_time);
        JMEMBER(Perf, temp2_time);
        JMEMBER(Perf, temp3_time);
        JMEMBER(Perf, temp4_time);
        JMEMBER(Perf, temp5_time);
        JSTATIC(Log);
/**/
        Log.out("translate :" + translate_time);
        Log.out("transform :" + transform_time);
        Log.out("append    :" + append_time);
        Log.out("render    :" + _R(render.render_time));
        Log.out("clear     :" + _R(render.clear_time));
        Log.out("repaint   :" + _R(render.repaint_time));
        Log.out("paint     :" + _R(render.paint_time));
        Log.out("temp1     :" + temp1_time);
        Log.out("temp2     :" + temp2_time);
        Log.out("temp3     :" + temp3_time);
        Log.out("temp4     :" + temp4_time);
        Log.out("temp5     :" + temp5_time);

        render.free_buffer();
Log.out(_R(render.render_time));
    }

/*J*/
    public String toString() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual String toString();
#else
    String Java3DWorld::toString() {
        JSTATIC(Math);
/**/
        String s = /*J*/super./*C*Java3D::/**/toString() + "\n";
        s += String("viewport(w,h,x,y):") + viewport_width + "," + viewport_height + "," + viewport_x + "," + viewport_y + "\n";
        s += String("max_z:") + max_z + ",clip_z:" + clip_z + ",eye_z:" + eye_z + ",mb0:" + mb0 + "\n";
        s += String("fov_angle:") + fov_angle + ",fov_x:" + (Math.tan(((double)fov_angle / 2) * (Math.PI / 180))) + "\n";
        s += String("pers_scale:") + pers_scale + ",pers_distance/256:" + (pers_distance / 256) + "\n";
        return s;
    }

    /**
     *  透視投影変換の係数を指定する。
     *  <pre>
     *  x-z 座標系
     *   max_z +-------+ max_z * tan(fov_angle / 2)
     *         |      /
     *  clip_z +     /
     *         |    + 投影点 viewport_x + viewport_width / 2
     *         |   /
     *         |  /
     *        <->/ fov_angle
     *         |/
     *       0 +
     *         |
     *  -eye_z +
     *  </pre>
     * 
     * @param   fov_angle   視界(Field of view)の角度(度)。
     * @param   max_z
     * @param   clip_z
     * @param   eye_z
     * @param   mb0
     */
/*J*/
    public void setPerspective(int fov_angle, int max_z, int clip_z, int eye_z, int mb0) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void setPerspective(int fov_angle, int max_z, int clip_z, int eye_z, int mb0);
#else
    void Java3DWorld::setPerspective(int fov_angle, int max_z, int clip_z, int eye_z, int mb0) {
        JSTATIC(Math);
        JSTATIC(Log);
/**/
        this.fov_angle = fov_angle;
        this.max_z     = max_z;
        this.clip_z    = clip_z;
        this.eye_z     = eye_z;
        double fov_x   = Math.tan(((double)fov_angle / 2) * (Math.PI / 180));
        pers_scale     = (int)((viewport_width / fov_x) * (max_z + eye_z) / max_z);
        pers_distance  = 256 * eye_z;
Log.out(String("Java3DWorld.setPerspective() : pers_scale = ") + pers_scale + ", pers_distance = " + pers_distance);
        this.mb0       = mb0;
    }

    /**
     * ビューポートの座標を設定する。
     * 
     * @param viewport_x
     * @param viewport_y
     */
/*J*/
    public void setViewport(int viewport_x, int viewport_y) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void setViewport(int viewport_x, int viewport_y);
#else
    void Java3DWorld::setViewport(int viewport_x, int viewport_y) {
/**/
        this.viewport_x = viewport_x;
        this.viewport_y = viewport_y;
    }

    /**
     * この空間を移動する。
     * dx, dy に ({@link Java3D#ANGLE_MAX} / 4096) に掛けた値が
     * {@link Java3D#va}, {@link Java3D#vb} に加えられる。
     * {@link Java3D#va}, {@link Java3D#vb} が {@link Java3D#ma}, {@link Java3D#mb} に加えられる。
     * 16 を {@link Java3D#ma}, {@link Java3D#mb} で回転した値が
     * {@link Java3D#vx}, {@link Java3D#vy}, {@link Java3D#vx} になる。
     * {@link Java3D#vx}, {@link Java3D#vy}, {@link Java3D#vx} を d で掛けた値が
     * {@link Java3D#mx}, {@link Java3D#my}, {@link Java3D#mx} に加えられる。
     * 
     * @param   dx  x 方向の加速度。
     * @param   dy  y 方向の加速度。
     * @param   d   移動量。
     */
/*J*/
    public void translate(int dx, int dy, int d) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void translate(int dx, int dy, int d);
#else
    void Java3DWorld::translate(int dx, int dy, int d) {
/**/
        if (false != is_view)
        {
            // View mode: not rotate
            va = vb = 0;
            vx = dx * cos(ma) + dy * sin(ma);
            vz = dy * cos(ma) - dx * sin(ma);
            mx -= vx >> 4;
            mz += vz >> 4;
        }
        else
        {
            // va, vb 増減
            va += dx * ANGLE_MAX / 4096;
            vb += dy * ANGLE_MAX / 4096;
            // va, vb 収束
            if ((0 == dx) && (0 != va))
            {
                int dir = (va > 0) ? 1 : -1;
                va += -dir * ANGLE_MAX / 4096;
                if (dir * va < 0)
                {
                    va = 0;
                }
            }
            if ((0 == dy) && (0 != vb))
            {
                int dir = (vb > 0) ? 1 : -1;
                vb += -dir * ANGLE_MAX / 4096;
                if (dir * vb < 0)
                {
                    vb = 0;
                }
            }
            // va, vb リミット
            if (va >  ANGLE_MAX / 128)
            {
                va =  ANGLE_MAX / 128;
            }
            if (va < -ANGLE_MAX / 128)
            {
                va = -ANGLE_MAX / 128;
            }
            if (vb >  ANGLE_MAX / 256)
            {
                vb =  ANGLE_MAX / 256;
            }
            if (vb < -ANGLE_MAX / 256)
            {
                vb = -ANGLE_MAX / 256;
            }
            // ma, mb, mc 増減
            ma += va;
            mb += vb;
            mc = va * 4;
            // mb 収束
            if (0 != mb)
            {
                int dir = (mb > 0) ? 1 : -1;
                int v = (dir * mb / 4 < ANGLE_MAX / 512)
                    ? mb / 4 : dir * ANGLE_MAX / 512;
                mb = (0 == v) ? 0 : mb - v;
            }
            // mb リミット
            if (mb > ANGLE_MAX / 16)
            {
                mb = ANGLE_MAX / 16;
            }
            else
            if (mb < -ANGLE_MAX / 16)
            {
                mb = -ANGLE_MAX / 16;
            }
            // 移動
            vx = sin(- ma) >> 4;
            vy = sin(- mb) >> 4;
            vz = cos(- ma) >> 4;
            if (false != is_stop)
            {
                // Stop mode: not move
            }
            else
            {
                mx += d * vx;
                my += d * vy;
                mz += d * vz;
            }
        }
    }

    /*J*/
    public JavaRenderAbstract get_render_draw() {
/*C*
#endif
#ifdef _IS_H_
    JavaRenderAbstract& get_render_draw();
#else
    JavaRenderAbstract& Java3DWorld::get_render_draw() {
        JMEMBER(JavaRenderBuffer, render);
/**/
        return _R(render.render_draw);
    }

/*J*/
    public JavaRenderAbstract get_render_paint() {
/*C*
#endif
#ifdef _IS_H_
    JavaRenderAbstract& get_render_paint();
#else
    JavaRenderAbstract& Java3DWorld::get_render_paint() {
        JMEMBER(JavaRenderBuffer, render);
/**/
        return _R(render.render_paint);
    }

/*J*/
    public Vertex get_trvert(int index) {
/*C*
#endif
#ifdef _IS_H_
    Vertex& get_trvert(int index);
#else
    Java3DWorld::Vertex& Java3DWorld::get_trvert(int index) {
        JMEMBER(JavaRenderBuffer, render);
/**/
        return render.get_trvert(index);
    }

/*J*/
    public Vertex get_trpolyvert(int index) {
/*C*
#endif
#ifdef _IS_H_
    Vertex& get_trpolyvert(int index);
#else
    Java3DWorld::Vertex& Java3DWorld::get_trpolyvert(int index) {
        JMEMBER(JavaRenderBuffer, render);
/**/
        return render.get_trpolyvert(index);
    }

/*J*/
    public void set_trpolyvert(int index, Vertex trvert) {
/*C*
#endif
#ifdef _IS_H_
    void set_trpolyvert(int index, Vertex* trvert);
#else
    void Java3DWorld::set_trpolyvert(int index, Vertex* trvert) {
        JMEMBER(JavaRenderBuffer, render);
/**/
        render.set_trpolyvert(index, trvert);
    }

/*J*/
    public Polygon get_trpoly(int index) {
/*C*
#endif
#ifdef _IS_H_
    Polygon& get_trpoly(int index);
#else
    Java3DWorld::Polygon& Java3DWorld::get_trpoly(int index) {
        JMEMBER(JavaRenderBuffer, render);
/**/
        return render.get_trpoly(index);
    }

/*J*/
    public void append_buffer(Polygon trpoly, int z_order, int vert_cnt, int mode) {
/*C*
#endif
#ifdef _IS_H_
    void append_buffer(Polygon* trpoly, int z_order, int vert_cnt, int mode);
#else
    void Java3DWorld::append_buffer(Polygon* trpoly, int z_order, int vert_cnt, int mode) {
        JMEMBER(JavaRenderBuffer, render);
/**/
        render.append_buffer(trpoly, z_order, vert_cnt, mode);
    }

/*J*/
    public void advance_trvert(int trcount) {
/*C*
#endif
#ifdef _IS_H_
    void advance_trvert(int trcount);
#else
    void Java3DWorld::advance_trvert(int trcount) {
        JMEMBER(JavaRenderBuffer, render);
/**/
        render.advance_trvert(trcount);
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
};
#endif
/**/

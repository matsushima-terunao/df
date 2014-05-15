/*
 * $Id: Java3D.cpp,v 1.24 2008/04/11 22:52:31 matsushima Exp $
 */

/*J*
package java3d;

import java.util.Random;

import javarender.JavaRender;

import commons.JavaObject;

/*C*/
#ifdef _IS_H_ // h
#pragma once

class Java3DWorld;

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/util/Random"
#include "Perf.cpp"
#include "JavaRender.cpp"

class Java3DStatic;
extern Java3DStatic _Java3DStatic;

#else // cpp

#define _IS_H_
#include "Java3D.cpp"
#undef _IS_H_

Random* Java3D::random;

#endif
/**/

/**
 * 3D オブジェクト(空間 {@link Java3DWorld}, モデル {@link Java3DModel})の抽象クラス。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: Java3D.cpp,v 1.24 2008/04/11 22:52:31 matsushima Exp $
 * 
 * $Log: Java3D.cpp,v $
 * Revision 1.24  2008/04/11 22:52:31  matsushima
 * gound 修正
 *
 * Revision 1.23  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.22  2008/03/06 16:42:45  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.21  2008/03/06 15:39:49  matsushima
 * h/cpp 共通化
 *
 * Revision 1.20  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.19  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.14  2007/05/14 13:38:18  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.12  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.10  2007/05/08 22:13:37  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.9  2007/05/08 15:25:01  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.8  2007/05/07 21:40:04  matsushima
 * staticメンバアクセス :: -> .
 *
 * Revision 1.7  2007/05/07 21:24:08  matsushima
 * staticメンバアクセス :: -> .
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
public abstract class Java3D extends JavaObject implements JavaRender
{
/*C*/
#ifdef _IS_H_
class Java3D : public JavaRenderStatic
{
/**/
/*J*
    public static final int
/*C*/
public:
    enum {
/**/
        RENDER_DEFAULT = RENDER_POLYLINE | RENDER_POLYFRAME | RENDER_POLYGON
                       | SHADING_TEXTURE | SHADING_GOURAUD | SHADING_ALPHA
                       | LIGHTING_DIFFUSE | LIGHTING_FOG
                       | APPEND_SORT,

        RENDER_INITIAL = RENDER_POLYLINE | RENDER_POLYFRAME | RENDER_POLYGON
                       | SHADING_TEXTURE | SHADING_GOURAUD | SHADING_ALPHA
                       | 0*LIGHTING_DIFFUSE | 0*LIGHTING_FOG
                       | APPEND_SORT,
                   //    | APPEND_BACK,

        /** 1周(2PI)の角度の最大値。 */
        ANGLE_MAX          = 65536,
        /** 1周(2PI)の角度のマスク値。 */
        ANGLE_MASK         = ANGLE_MAX - 1,
        /** sin(), cos() の最大値。 */
        TRIFUNC_MAX        = 256,
        /** オブジェクトデータ定義時の、頂点あるいは多角形あるいは連続線データの終わりを表す。 */
        EOD = -1
/*J*
    ;
/*C*/
    };
/**/

    // Tooles
/*J*
    public static Random random;
/*C*/
public:
    static Random* random;
#endif
/**/

    /**
     * 指定された角度の cos を返す。
     * 
     * @param   a   1周を {@link #ANGLE_MAX} とした角度。
     * @return  最大値を {@link #TRIFUNC_MAX} とした cos。
     */
/*J*
    public static int cos(int a) {
/*C*/
#ifdef _IS_H_
public:
    static int cos(int a);
#else
    int Java3D::cos(int a) {
/**/
        a &= ANGLE_MASK;
        return (int)(TRIFUNC_MAX * Math::cos(2 * Math::PI * a / ANGLE_MAX));
    }
/*C*/
#endif
/**/

    /**
     * 指定された角度の sin を返す。
     * 
     * @param   a   1周を {@link #ANGLE_MAX} とした角度。
     * @return  最大値を {@link #TRIFUNC_MAX} とした sin。
     */
/*J*
    public static int sin(int a) {
/*C*/
#ifdef _IS_H_
public:
    static int sin(int a);
#else
    int Java3D::sin(int a) {
/**/
        a &= ANGLE_MASK;
        return (int)(TRIFUNC_MAX * Math::sin(2 * Math::PI * a / ANGLE_MAX));
    }
/*C*/
#endif
#ifdef _IS_H_
/**/

    /**
     * このオブジェクトが参照する空間。
     */
/*J*
    public Java3DWorld world;
/*C*/
public:
    Java3DWorld* world;
/**/

    /**
     * このオブジェクトが参照するオブジェクト。
     * このオブジェクトの座標は parent からの相対座標になる。
     */
/*J*
    public Java3D parent;
/*C*/
public:
    Java3D* parent;
/**/

    /**
     * このオブジェクトの y, x, z 軸回りの回転角度。
     */
/*J*
    public int ma, mb, mc;
/*C*/
public:
    int ma, mb, mc;
/**/

    /**
     * このオブジェクトの x, y, z 座標。
     */
/*J*
    public int mx, my, mz;
/*C*/
public:
    int mx, my, mz;
/**/
    /**
     * このオブジェクトの y, x 軸回りの回転角度の移動量。
     */
/*J*
    public int va, vb;
/*C*/
public:
    int va, vb;
/**/

    /**
     * このオブジェクトの x, y, z 座標の移動量。
     */
/*J*
    public int vx, vy, vz;
/*C*/
public:
    int vx, vy, vz;
/**/

    /**
     * このオブジェクトの光源の x, y, z 座標。
     */
/*J*
    public int lx, ly, lz;
/*C*/
public:
    int lx, ly, lz;
/**/

    /**
     * このオブジェクトのフォグのしきい値。
     */
/*J*
    public int fog_z;
/*C*/
public:
    int fog_z;
/**/

    /**
     * このオブジェクトの描画方法のフラグ。
     * <p>
     * 以下の描画フラグのいずれかを指定する。
     * <br>{@link #RENDER_POLYLINE} : ワイヤーフレームを描画。
     * <br>{@link #RENDER_POLYFRAME} : ポリゴンの枠を描画。
     * <br>{@link #RENDER_POLYGON} : ポリゴンを描画。
     * <br>{@link #RENDER_STRING} : 文字列を描画。
     * <p>
     * 以下のシェーディングフラグを1つ以上指定できる。
     * <br>{@link #SHADING_GOURAUD} : 各頂点の色で変化させる。
     * <br>{@link #SHADING_ALPHA} : 透過。
     * <p>
     * 以下のライティングフラグを1つ以上指定できる。
     * <br>{@link #LIGHTING_DIFFUSE} : ライティング。
     * <br>{@link #LIGHTING_FOG} : 遠くに行くほど暗くなる。
     * <p>
     * 以下のポリゴンバッファへの追加方法のフラグのいずれかを指定する。
     * <br>{@link #APPEND_NONE} : ポリゴンバッファへの追加方法。
     * <br>{@link #APPEND_FRONT} : ポリゴンバッファへの追加方法。
     * <br>{@link #APPEND_BACK} : ポリゴンバッファへの追加方法。
     * <br>{@link #APPEND_SORT} : ポリゴンバッファへの追加方法。
     */
/*J*
    public int render_mode;
/*C*/
public:
    int render_mode;
#endif
/**/

    /**
     * オブジェクトを構築する。
     */
/*J*
    protected Java3D() {
/*C*/
#ifdef _IS_H_
protected:
    Java3D();
#else
    Java3D::Java3D() {
/**/
        world = null;
        parent = null;
        ma = mb = mc = 0;
        mx = my = mz = 0;
        va = vb = 0;
        vx = vy = vz = 0;
        lx = ly = lz = 0;
        render_mode = RENDER_DEFAULT;
    }
/*C*/
#endif
/**/

    /**
     * オブジェクトを破棄する。
     */
/*C*/
#ifdef _IS_H_
public:
    virtual ~Java3D();
#else
    Java3D::~Java3D() {
    }
#endif
/**/

/*J*
    public String toString() {
/*C*/
#ifdef _IS_H_
public:
    virtual String toString();
#else
    String Java3D::toString() {
/**/
        String s = String("m:") + ma + "," + mb + "," + mc + ";" + mx + "," + my + "," + mz + "; " +
        "v:"  + va + "," + vb + ";" + vx + "," + vy + "," + vz + "\n";
s += render_string(render_mode) + "\n";
s += render_string(render_mode);
        return s;
    }
/*C*/
#endif
/**/

/*J*
    protected String render_string(int r) {
/*C*/
#ifdef _IS_H_
protected:
    virtual String render_string(int r);
#else
    String Java3D::render_string(int r) {
/**/
        String s = "";
        if (RENDER_POLYLINE                 == (r & RENDER_MASK)) s += "POLYLINE | ";
        if (RENDER_POLYFRAME                == (r & RENDER_MASK)) s += "POLYFRAME | ";
        if (RENDER_POLYGON                  == (r & RENDER_MASK)) s += "POLYGON | ";
        /*if (RENDER_SHADING_SOLID            == (r & RENDER_SHADING_MASK)) s += "SHADING_SOLID";
        if (RENDER_SHADING_GOURAUD          == (r & RENDER_SHADING_MASK)) s += "SHADING_GOURAUD";
        if (RENDER_SHADING_GOURAUD_ALPHA    == (r & RENDER_SHADING_MASK)) s += "SHADING_GOURAUD_ALPHA";*/
        return s;
    }
/*C*/
#endif
/**/

/*J*
    public void set_render_mode(int mode) {
/*C*/
#ifdef _IS_H_
public:
    virtual void set_render_mode(int mode);
#else
    void Java3D::set_render_mode(int mode) {
/**/
        render_mode = mode;
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/

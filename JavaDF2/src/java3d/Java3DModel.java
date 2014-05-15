/*
 * $Id: Java3DModel.java,v 1.14 2008/03/06 16:43:59 matsushima Exp $
 */

/*J*/
package java3d;

import javarender.JavaRenderTexture;

import commons.Log;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "Java3D.cpp"

class Java3DModelStatic;
extern Java3DModelStatic _Java3DModelStatic;

#else // cpp

#define _IS_H_
#include "Java3DModel.cpp"
#include "Java3DWorld.cpp"
#include "Log.cpp"
#undef _IS_H_

Java3DModelStatic _Java3DModelStatic;

#endif
/**/

/**
 * 3D モデルの基本クラス。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: Java3DModel.java,v 1.14 2008/03/06 16:43:59 matsushima Exp $
 * 
 * $Log: Java3DModel.java,v $
 * Revision 1.14  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.31  2008/03/06 15:39:49  matsushima
 * h/cpp 共通化
 *
 * Revision 1.30  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.29  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.28  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.27  2007/05/24 01:01:35  matsushima
 * no message
 *
 * Revision 1.26  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRenderInterface を Java3D から分離
 *
 * Revision 1.19  2007/05/16 20:57:58  matsushima
 * テクスチャマッピング
 *
 * Revision 1.15  2007/05/14 15:58:36  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.14  2007/05/14 13:38:18  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.12  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.9  2007/05/08 22:13:37  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.8  2007/05/08 15:25:01  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.7  2007/05/07 21:40:04  matsushima
 * staticメンバアクセス :: -> .
 *
 * Revision 1.6  2007/05/06 18:00:09  matsushima
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
public class Java3DModel extends Java3D
{
/*C*
#ifdef _IS_H_
class Java3DModelStatic : public virtual Java3DStatic
{
/**/
    /**
     * 予約済みのモデルの種類。
     */
/*J*/
    public static final int
/*C*
public:
    enum {
/**/
        KIND_UNUSED     = 0,
        KIND_FRAGMENT   = -2,
        KIND_FRAGMENT2  = -3,
        KIND_USED       = 1,//-1,
        KIND_ENEMY1     = 2
/*J*/
    ;
/*C*
    };
/**/

    /**
     * グラデーションカラーテーブルの作成。
     * 
     * @param cnt
     * @param t
     * @return  作成されたカラーテーブル。
     */
/*J*/
    public static int[] create_color_table(int cnt, final int[] t) {
/*C*
#endif
#ifdef _IS_H_
public:
    static int* create_color_table(int cnt, const int* t);
#else
    int* Java3DModelStatic::create_color_table(int cnt, const int* t) {
/**/
        int/*C** /*J*/[]/**/ table = new int[cnt];
        int i, index = 0;
        for (i = 0; i < cnt; ++ i)
        {
            if (i >= t[(index + 1) * 4 + 0] * cnt / 256)
            {
                ++ index;
            }
            int d0 = i - t[ index      * 4 + 0] * cnt / 256;
            int d1 = i - t[(index + 1) * 4 + 0] * cnt / 256;
            int d = (t[(index + 1) * 4 + 0] - t[index * 4 + 0]) * cnt / 256;
            int r = (d0 * t[(index + 1) * 4 + 1] - d1 * t[index * 4 + 1]) / d;
            int g = (d0 * t[(index + 1) * 4 + 2] - d1 * t[index * 4 + 2]) / d;
            int b = (d0 * t[(index + 1) * 4 + 3] - d1 * t[index * 4 + 3]) / d;
            table[i] = 0xff000000 | (r << 16) | (g << 8) | b;
        }
        return table;
    }

    /**
     * 色インデックスの配列を ARGB に変換する。
     * 
     * @param dst
     * @param verts
     * @param cnt
     * @param vert_colors
     * @param mul
     * @param div
     * @return  変換後の配列。
     */
/*J*/
    public static int[] index_to_color(int[] dst, final int[] verts, int cnt, int[] vert_colors, int mul, int div) {
/*C*
#endif
#ifdef _IS_H_
public:
    static int* index_to_color(int* dst, const int* verts, int cnt, int* vert_colors, int mul, int div);
#else
    int* Java3DModelStatic::index_to_color(int* dst, const int* verts, int cnt, int* vert_colors, int mul, int div) {
/**/
        if (null == dst)
        {
            dst = new int[cnt];
        }
        int i;
        for (i = 0; i < cnt; ++ i)
        {
            dst[i] = vert_colors[verts[i] * mul / div];
        }
        return dst;
    }

    /**
     * テクスチャを拡大する。
     * バイリニアフィルタ(線形補完)。
     * 
     * @param src
     * @param width
     * @param height
     * @param mul_w
     * @param mul_h
     * @return  拡大後のテクスチャ。
     */
/*J*/
    public static int[] zoom_texture(final int[] src, int width, int height, int mul_w, int mul_h) {
/*C*
#endif
#ifdef _IS_H_
public:
    static int* zoom_texture(const int* src, int width, int height, int mul_w, int mul_h);
#else
    int* Java3DModelStatic::zoom_texture(const int* src, int width, int height, int mul_w, int mul_h) {
        JSTATIC(Log);
        JSTATIC(System);
/**/
Log.out(String("Java3DModel.zoom_texture() : width = ") + width + ", mul_w = " + mul_w);
long t = System.currentTimeMillis();
        int/*J*/[]/*C** /**/ dst = new int[(width * mul_w) * (height * mul_h)];
        int x, y;
        for (y = 0; y < height; ++ y)
        {
            for (x = 0; x < width; ++ x)
            {
                int x2 = (x + 1) % width;
                int y2 = (y + 1) % height;
                int c11 = src[x  + y  * width];
                int c21 = src[x2 + y  * width];
                int c12 = src[x  + y2 * width];
                int c22 = src[x2 + y2 * width];
                int r11 = (c11 >> 16) & 0xff;
                int g11 = (c11 >>  8) & 0xff;
                int b11 = (c11 >>  0) & 0xff;
                int r21 = (c21 >> 16) & 0xff;
                int g21 = (c21 >>  8) & 0xff;
                int b21 = (c21 >>  0) & 0xff;
                int r12 = (c12 >> 16) & 0xff;
                int g12 = (c12 >>  8) & 0xff;
                int b12 = (c12 >>  0) & 0xff;
                int r22 = (c22 >> 16) & 0xff;
                int g22 = (c22 >>  8) & 0xff;
                int b22 = (c22 >>  0) & 0xff;
                int u, v;
                for (u = 0; u < mul_w; ++ u)
                {
                    for (v = 0; v < mul_h; ++ v)
                    {
                        int r = (r11 * ((mul_w - 1) - u) + r21 * u) * ((mul_h - 1) - v)
                              + (r12 * ((mul_w - 1) - u) + r22 * u) * v;
                        int g = (g11 * ((mul_w - 1) - u) + g21 * u) * ((mul_h - 1) - v)
                              + (g12 * ((mul_w - 1) - u) + g22 * u) * v;
                        int b = (b11 * ((mul_w - 1) - u) + b21 * u) * ((mul_h - 1) - v)
                              + (b12 * ((mul_w - 1) - u) + b22 * u) * v;
                        r /= (mul_w - 1) * (mul_h - 1);
                        g /= (mul_w - 1) * (mul_h - 1);
                        b /= (mul_w - 1) * (mul_h - 1);
                        dst[(x * mul_w + u) + (y * mul_h + v) * (width * mul_w)]
                            = 0xff000000 | (r << 16) | (g << 8) | b;
                    }
                }
            }
        }
t = System.currentTimeMillis() - t;
Log.out(String("> time = ") + t + " ms");
        return dst;
    }

    /**
     * 指定された明るさで色を正規化。
     * 
     * @param   color       正規化する元の色(RGB)。
     * @param   brightness  明るさ。
     * @return  正規化された色。
     * <pre>
     *              brightness &lt= 0: 0xff000000
     *              brightness &gt= {@link #BRIGHTNESS_MAX} - 1: 0xffffffe
     *              brightness &lt= {@link #BRIGHTNESS_BORDER}: color * brightness / {@link #BRIGHTNESS_BORDER}
     *              brightness &gt {@link #BRIGHTNESS_BORDER}:
     *                  color + (256 - color) * (brightness / {@link #BRIGHTNESS_BORDER}) ^ 2
     *                                        / ({@link #BRIGHTNESS_MAX} / {@link #BRIGHTNESS_BORDER}) ^ 2
     * </pre>
     */
/*J*/
    public static int get_brightness_color(int color, int brightness) {
/*C*
#endif
#ifdef _IS_H_
public:
    static int get_brightness_color(int color, int brightness);
#else
    int Java3DModelStatic::get_brightness_color(int color, int brightness) {
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

    /**
     * ポリゴン配列の現在のポリゴンの頂点数を数える。
     * 
     * @param   polys   ポリゴン配列。
     * @param   s       ポリゴン配列内のインデックス。
     * @return  頂点数。
     */
/*J*/
    public static int get_vert_cnt(int[] polys, int s) {
/*C*
#endif
#ifdef _IS_H_
public:
    static int get_vert_cnt(int* polys, int s);
#else
    int Java3DModelStatic::get_vert_cnt(int* polys, int s) {
/**/
        int i;
        for (i = 0; EOD != polys[s + i]; ++ i)
        {
        }
        return i;
    }

    /**
     * 頂点座標配列のメンバを設定。
     * 
     * @param   verts   頂点座標配列。
     * @param   index   頂点座標配列内のインデックス。
     * @param   color   設定する色(ARGB)。
     * @param   x       設定する x 座標。
     * @param   y       設定する y 座標。
     * @param   z       設定する z 座標。
     */
/*J*/
    public static void set_vert(int[] verts, int index, int color, int x, int y, int z) {
/*C*
#endif
#ifdef _IS_H_
public:
    static void set_vert(int* verts, int index, int color, int x, int y, int z);
#else
    void Java3DModelStatic::set_vert(int* verts, int index, int color, int x, int y, int z) {
/**/
        if (-1 == index)
        {
            for (index = 0; EOD != verts[index * 4 + 0]; ++ index)
            {
                verts[index * 4 + 0] = color;
                verts[index * 4 + 1] = x;
                verts[index * 4 + 2] = y;
                verts[index * 4 + 3] = z;
            }
        }
        else
        {
            verts[index * 4 + 0] = color;
            verts[index * 4 + 1] = x;
            verts[index * 4 + 2] = y;
            verts[index * 4 + 3] = z;
        }
    }

    /**
     * 頂点座標配列の色を設定。
     * 
     * @param   verts   頂点座標配列。
     * @param   index   頂点座標配列内のインデックス。-1 のときは全てのインデックス。
     * @param   value   設定する色(ARGB)。
     */
/*J*/
    public static void set_vert_color(int[] verts, int index, int value) {
/*C*
#endif
#ifdef _IS_H_
public:
    static void set_vert_color(int* verts, int index, int value);
#else
    void Java3DModelStatic::set_vert_color(int* verts, int index, int value) {
/**/
        if (-1 == index)
        {
            for (index = 0; EOD != verts[index * 4 + 0]; ++ index)
            {
                verts[index * 4 + 0] = value;
            }
        }
        else
        {
            verts[index * 4 + 0] = value;
        }
    }

    /**
     * 頂点座標配列の x, y, z 座標を設定。
     * 
     * @param   verts   頂点座標配列。
     * @param   index   頂点座標配列内のインデックス。
     * @param   x       設定する x 座標。
     * @param   y       設定する y 座標。
     * @param   z       設定する z 座標。
     */
/*J*/
    public static void set_vert_xyz(int[] verts, int index, int x, int y, int z) {
/*C*
#endif
#ifdef _IS_H_
public:
    static void set_vert_xyz(int* verts, int index, int x, int y, int z);
#else
    void Java3DModelStatic::set_vert_xyz(int* verts, int index, int x, int y, int z) {
/**/
        if (-1 == index)
        {
            for (index = 0; EOD != verts[index * 4 + 0]; ++ index)
            {
                verts[index * 4 + 1] = x;
                verts[index * 4 + 2] = y;
                verts[index * 4 + 3] = z;
            }
        }
        else
        {
            verts[index * 4 + 1] = x;
            verts[index * 4 + 2] = y;
            verts[index * 4 + 3] = z;
        }
    }
/*C*
#endif
#ifdef _IS_H_
};

class Java3DModel : public JBase<Java3DModel>, public Java3D, public virtual Java3DModelStatic
{
/**/

    /** モデルの種類。 */
/*J*/
    public int kind;
    public int count;
    public int count_max;
    public int damage;
    public int damage_max;
/*C*
public:
    int kind;
    int count;
    int count_max;
    int damage;
    int damage_max;
/**/

    /** モデルのポリゴンデータ。 */
/*J*/
    public int[] verts;
    public int[] polys;
    public int[] lines;
    public JavaRenderTexture texture;
    public String string;
/*C*
public:
    int* verts;
    int* polys;
    int* lines;
    JavaRenderTexture* texture;
    String string;
/**/

    /** 変換後の座標。 */
/*J*/
    public boolean trshown;
    public int trcount;
    public int trmx3, trmy3, trmz3;
    public int trmx21, trmx22, trmy21, trmy22;
    public int trmx31, trmx32, trmy31, trmy32, trmz31, trmz32;
/*C*
public:
    boolean trshown;
    int trcount;
    int trmx3, trmy3, trmz3;
    int trmx21, trmx22, trmy21, trmy22;
    int trmx31, trmx32, trmy31, trmy32, trmz31, trmz32;
/**/

    /**
     * Java3DModel オブジェクトを構築する。
     * 
     * @param   world   このモデルが参照する空間。
     * @param   parent  このオブジェクトが参照するオブジェクト。
     *                  このオブジェクトの座標は parent からの相対座標になる。
     */
/*J*/
    public Java3DModel(Java3DWorld world, Java3D parent) {
/*C*
#endif
#ifdef _IS_H_
public:
    Java3DModel(Java3DWorld* world, Java3D* parent);
#else
    Java3DModel::Java3DModel(Java3DWorld* _world, Java3D* parent) {
#define this (*this)
        JPARAM(Java3DWorld, world);
/**/
        this.world = world;
        this.parent = parent;
        init(KIND_UNUSED, -1, 0, 0,  null, null, null);
        setPosition(0, 0, 0, 0, 0,  0, 0, 0, 0, 0);
        this.fog_z = (null != world) ? world.fog_z : 0;
    }

    /**
     * モデルを初期化する。
     * 
     * @param kind
     * @param count
     * @param damage
     * @param render_mode
     * @param verts
     * @param polys
     * @param lines
     */
/*J*/
    public void init(
        int kind, int count, int damage, int render_mode,
        int[] verts, int[] polys, int[] lines) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void init(
        int kind, int count, int damage, int render_mode,
        int* verts, int* polys, int* lines);
#else
    void Java3DModel::init(
        int kind, int count, int damage, int render_mode,
        int* verts, int* polys, int* lines) {
/**/
        this.kind       = kind;
        this.count      = 0;
        this.count_max  = count;
        this.damage     = 0;
        this.damage_max = damage;
        this.render_mode = render_mode;
        this.verts      = verts;
        this.polys      = polys;
        this.lines      = lines;
        this.texture    = null;
        this.string     = "";
        setPosition(0, 0, 0, 0, 0,  0, 0, 0, 0, 0);
    }

    /**
     * モデルのテクスチャを設定する。
     * 
     * @param texture
     */
/*J*/
    public void init_texture(JavaRenderTexture texture) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void init_texture(JavaRenderTexture* texture);
#else
    void Java3DModel::init_texture(JavaRenderTexture* texture) {
/**/
        this.texture = texture;
    }

    /**
     * モデルの文字列を設定する。
     * 
     * @param string
     */
/*J*/
    public void init_string(String string) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void init_string(_String string);
#else
    void Java3DModel::init_string(_String string) {
/**/
        this.string = string;
    }

    /**
     * モデルのデータを削除する。
     */
/*J*/
    public void destroy() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void destroy();
#else
    void Java3DModel::destroy() {
        if (null != verts)
        {
            delete[] verts;
        }
        if (null != polys)
        {
            delete[] polys;
        }
        if (null != lines)
        {
            delete[] lines;
        }
        if (null != texture)
        {
            delete texture;
        }
/**/
    }

    /**
     * モデルの座標を設定する。
     * 
     * @param ma
     * @param mb
     * @param mx
     * @param my
     * @param mz
     * @param va
     * @param vb
     * @param vx
     * @param vy
     * @param vz
     */
/*J*/
    public void setPosition(
        int ma, int mb, int mx, int my, int mz,
        int va, int vb, int vx, int vy, int vz) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void setPosition(
        int ma, int mb, int mx, int my, int mz,
        int va, int vb, int vx, int vy, int vz);
#else
    void Java3DModel::setPosition(
        int ma, int mb, int mx, int my, int mz,
        int va, int vb, int vx, int vy, int vz) {
/**/
        this.ma = ma;
        this.mb = mb;
        this.mc = 0;
        this.mx = mx;
        this.my = my;
        this.mz = mz;
        this.va = va;
        this.vb = vb;
        this.vx = vx;
        this.vy = vy;
        this.vz = vz;
        lx = ly = lz = 0;
    }

    /**
     * 2D 表示用にモデルの座標を設定する。
     * 
     * @param mx
     * @param my
     * @param lz
     * @param scale256
     */
/*J*/
    public void setPosition2D(int mx, int my, int lz, double scale256) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void setPosition2D(int mx, int my, int lz, double scale256);
#else
    void Java3DModel::setPosition2D(int mx, int my, int lz, double scale256) {
/**/
        this.mx = mx;
        this.my = my;
        this.mz = (int)(256 / scale256);
        this.lx = 0;
        this.ly = 0;
        this.lz = lz;
    }

    /**
     * このモデルが使用されているか。
     * 
     * {@link #kind} が {@link #KIND_UNUSED} でなく、
     * {@link #count} が {@link #count_max} 未満か {@link #count_max} が 0 なら使用されている。
     * 
     * @return  使用されていれば true。
     */
/*J*/
    public boolean used() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual boolean used();
#else
    boolean Java3DModel::used() {
/**/
        if ((count < count_max) || (0 == count_max))
        {
        }
        else
        {
            return false;
        }
        return ((KIND_UNUSED == kind) ? false : true);
    }

    /**
     * このモデルを未使用にする。
     */
/*J*/
    public void unuse() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void unuse();
#else
    void Java3DModel::unuse() {
/**/
        kind = KIND_UNUSED;
    }

    /**
     * このモデルを移動する。
     * 
     * {@link #count} を +1 し、
     * {@link #ma}, {@link #mb}, {@link #mx}, {@link #my}, {@link #mz} に
     * {@link #va}, {@link #vb}, {@link #vx}, {@link #vy}, {@link #vz} を加える。
     * 
     * @return  {@link #count} を +1 した結果未使用になった場合 true。
     */
/*J*/
    public boolean translate() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual boolean translate();
#else
    boolean Java3DModel::translate() {
/**/
        ++ count;
        ma += va;
        mb += vb;
        mx += vx;
        my += vy;
        mz += vz;
        return (count < count_max) || (0 == count_max) ? false : true;
    }

    /**
     * 複数モデルを座標変換・投影する。
     * 
     * @param   models
     * @param   length
     * @see     #transform()
     */
/*J*/
    public static void transform_models(Java3DModel[] models, int length) {
/*C*
#endif
#ifdef _IS_H_
public:
    static void transform_models(Java3DModel** models, int length);
#else
    void Java3DModel::transform_models(Java3DModel** models, int length) {
/**/
        int i;
        for (i = 0; i < length; ++ i)
        {
            if (false != _R(models[i]).used())
            {
                _R(models[i]).transform();
            }
        }
    }

    /**
     * このモデルを座標変換・投影する。
     * 
     * モデルの座標変換:
     * {@link #parent} が null である場合は、モデルの座標を絶対座標として、座標変換を行わない。
     * {@link #parent} が null でない場合は、{@link #parent} からの相対座標・角度を
     * 絶対座標・角度として座標変換を行う。
     * 変換後の座標の情報は trxxxx に設定される。
     * 
     * 各頂点の座標変換・投影:
     * @see #transform_vertexes(int, int, int)
     */
/*J*/
    public void transform() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void transform();
#else
    void Java3DModel::transform() {
        JMEMBER(Java3DWorld, world);
/**/
_R(world.transform_time).start();
        if (null == parent)
        {
            trmx3 = mx;
            trmy3 = my;
            trmz3 = mz;
            transform_vertexes(mx << 8, my << 8, mz << 8);
        }
        else
        {
/**/
            int cos_a = cos(- world.ma);
            int sin_a = sin(- world.ma);
            int cos_b = cos(- (world.mb + world.mb0));
            int sin_b = sin(- (world.mb + world.mb0));
/**
            double cos_a = 256.0 * Math.cos(2.0 * Math.PI / ANGLE_MAX * -world.ma);
            double sin_a = 256.0 * Math.sin(2.0 * Math.PI / ANGLE_MAX * -world.ma);
            double cos_b = 256.0 * Math.cos(2.0 * Math.PI / ANGLE_MAX * -(world.mb + world.mb0));
            double sin_b = 256.0 * Math.sin(2.0 * Math.PI / ANGLE_MAX * -(world.mb + world.mb0));
/**/
            int x = get_x();
            int y = get_y();
            int z = get_z();
            int z11 = (int)(z   * cos_a + x   * sin_a);
            int x11 = (int)(x   * cos_a - z   * sin_a);
            int y11 = (int)(y   * 256);
            int z12 = (int)(z11 * cos_b + y11 * sin_b);
            int y12 = (int)(y11 * cos_b - z11 * sin_b);
            int x12 = (int)(x11 * 256);
            int x1 = (int)(x12 >> 8);
            int y1 = (int)(y12 >> 8);
            int z1 = (int)(z12 >> 8);
            trmx3 = x1 >> 8;
            trmy3 = y1 >> 8;
            trmz3 = z1 >> 8;
            transform_vertexes(x1, y1, z1);
        }
_R(world.transform_time).end();
    }

    /**
     * このモデルの各頂点を座標変換・投影する。
     * 
     * @param x1
     * @param y1
     * @param z1
     */
/*J*/
    protected void transform_vertexes(int x1, int y1, int z1) {
/*C*
#endif
#ifdef _IS_H_
protected:
    virtual void transform_vertexes(int x1, int y1, int z1);
#else
    void Java3DModel::transform_vertexes(int x1, int y1, int z1) {
        JMEMBER(Java3DWorld, world);
/**/
        int render_actual = get_render_mode();
        int pers_scale    = (null == parent) ? 256 : world.pers_scale;
        int pers_distance = (null == parent) ? 0 : world.pers_distance;
        int lx = get_lx();
        int ly = get_ly();
        int lz = get_lz();
        int cos_a = cos(get_a());
        int sin_a = sin(get_a());
        int cos_b = cos(get_b());
        int sin_b = sin(get_b());
        int cos_c = cos(get_c());
        int sin_c = sin(get_c());
        transform_vertexes(x1, y1, z1,
            render_actual, pers_distance, pers_scale, lx, ly, lz,
            cos_a, sin_a, cos_b, sin_b, cos_c, sin_c);
    }

    /**
     * このモデルの各頂点を座標変換・投影する。
     * 
     * @param x1
     * @param y1
     * @param z1
     * @param render_actual
     * @param pers_distance
     * @param pers_scale
     * @param lx
     * @param ly
     * @param lz
     * @param cos_a
     * @param sin_a
     * @param cos_b
     * @param sin_b
     * @param cos_c
     * @param sin_c
     */
/*J*/
    protected void transform_vertexes(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c) {
/*C*
#endif
#ifdef _IS_H_
protected:
    virtual void transform_vertexes(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c);
#else
    void Java3DModel::transform_vertexes(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c) {
/**/
        int s, d;
        for (s = 0, d = 0; EOD != verts[s]; s += 4, ++ d)
        {
            transform_vertex(x1, y1, z1,
                render_actual, pers_distance, pers_scale, lx, ly, lz,
                cos_a, sin_a, cos_b, sin_b, cos_c, sin_c,
                d, verts[s], verts[s + 1], verts[s + 2], verts[s + 3]);
        }
        trcount = d;
    }

    /**
     * このモデルの各頂点を座標変換・投影する。
     * 
     * @param x1
     * @param y1
     * @param z1
     * @param render_actual
     * @param pers_distance
     * @param pers_scale
     * @param lx
     * @param ly
     * @param lz
     * @param cos_a
     * @param sin_a
     * @param cos_b
     * @param sin_b
     * @param cos_c
     * @param sin_c
     * @param   index
     * @param   color
     * @param   x
     * @param   y
     * @param   z
     */
/*J*/
    protected void transform_vertex(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c,
        int index, int color, int x, int y, int z) {
/*C*
#endif
#ifdef _IS_H_
protected:
    virtual void transform_vertex(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c,
        int index, int color, int x, int y, int z);
#else
    void Java3DModel::transform_vertex(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c,
        int index, int color, int x, int y, int z) {
        JTYPEDEF_R(Vertex);
        JMEMBER(Java3DWorld, world);
/**/
        Vertex trvert = get_trvert(index);
        if ((null != texture) && (null != _R(texture).ptx))
        {
            trvert.tx = _R(texture).ptx[index];
            trvert.ty = _R(texture).pty[index];
        }
        trvert.color = color;
        int zz = z * cos_a + x * sin_a; // ^8
        int xx = x * cos_a - z * sin_a;
        int yy = y * 256;
        trvert.z3 = zz * cos_b + yy * sin_b; // ^16
        trvert.y3 = yy * cos_b - zz * sin_b;
        trvert.x3 = xx * 256;
        int x2 = x1 + (trvert.x3 >> 8); // ^8
        int y2 = y1 + (trvert.y3 >> 8);
        int z2 = z1 + (trvert.z3 >> 8);
        trvert.in_clip = false;
        trvert.z_order = (z2 + pers_distance) * 256 / pers_scale;
        if (trvert.z_order > 0)
        {
            trvert.in_clip = (z2 < (world.clip_z << 8)) ? true : false;
            trvert.x2 = (x2 * cos_c + y2 * sin_c) / trvert.z_order + world.viewport_x;
            trvert.y2 = (y2 * cos_c - x2 * sin_c) / trvert.z_order + world.viewport_y;
            if (0 == index)
            {
                trmx21 = trvert.x2;
                trmx22 = trvert.x2;
                trmy21 = trvert.y2;
                trmy22 = trvert.y2;
                trmx31 = trvert.x3;
                trmx32 = trvert.x3;
                trmy31 = trvert.y3;
                trmy32 = trvert.y3;
                trmz31 = trvert.z3;
                trmz32 = trvert.z3;
            }
            else
            {
                if (trmx21 > trvert.x2) trmx21 = trvert.x2;
                if (trmx22 < trvert.x2) trmx22 = trvert.x2;
                if (trmy21 > trvert.y2) trmy21 = trvert.y2;
                if (trmy22 < trvert.y2) trmy22 = trvert.y2;
                if (trmx31 > trvert.x3) trmx31 = trvert.x3;
                if (trmx32 < trvert.x3) trmx32 = trvert.x3;
                if (trmy31 > trvert.y3) trmy31 = trvert.y3;
                if (trmy32 < trvert.y3) trmy32 = trvert.y3;
                if (trmz31 > trvert.z3) trmz31 = trvert.z3;
                if (trmz32 < trvert.z3) trmz32 = trvert.z3;
            }
            trvert.brightness = BRIGHTNESS_BORDER1;
            if (LIGHTING_DIFFUSE == (LIGHTING_DIFFUSE & render_actual))
            {
                //trvert.color = get_brightness_color(trvert.color, get_vertex_angle(trvert, lx, ly, lz));
                int b = get_vertex_angle(trvert, lx, ly, lz);
                trvert.brightness = trvert.brightness * b / BRIGHTNESS_BORDER1;
            }
            if (LIGHTING_FOG == (LIGHTING_FOG & render_actual))
            {
                //trvert.color = get_fog_color(z2 >> 8, trvert.color);
                int b = get_fog_brightness(z2 >> 8);
                trvert.brightness = trvert.brightness * b / BRIGHTNESS_BORDER1;
                trvert.color = (trvert.color & 0x00fffffe) | (get_fog_alpha(z2 >> 8) << 24);
            }
            trvert.color = get_brightness_color(trvert.color, trvert.brightness);
        }
    }

    /**
     * {@link #transform()} で変換した各頂点座標を {@link #polys} のインデックスでつなげて
     * ポリゴンを作成し、ポリゴンバッファに追加する。
     */
/*J*/
    public void append() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void append();
#else
    void Java3DModel::append() {
        JTYPEDEF_R(Vertex);
        JTYPEDEF_R(Polygon);
        JMEMBER(Java3DWorld, world);
/**/
_R(world.append_time).start();
        int render_actual = -123;
        int/*C** /*J*/[]/**/ polys_actual = null;
        int s = -123, d = -123;
        trshown = false; // このモデルがビューポート内に存在するか

        // polys_actual or lines を選択
        int render_org = render_actual = get_render_mode();
        boolean is_poly = (RENDER_POLYLINE == (RENDER_MASK & render_actual)) ? false : true;
        polys_actual = (RENDER_POLYLINE == (RENDER_MASK & render_actual)) ? lines : polys;
        if (null == polys_actual)
        {
            // RENDER_POLYLINE でも lines が null なので RENDER_POLYFRAME にし polys_actual を選択
            polys_actual = polys;
            render_actual = (render_actual & ~RENDER_MASK) | RENDER_POLYFRAME;
        }
        // 描画モードが APPEND_NONE の場合はポリゴンを作成せずに終了
        if (APPEND_NONE == (APPEND_MASK & render_actual))
        {
            return;
        }

        // 変換後頂点をつなげてポリゴンを作成する
/*J*/label_polys:/**/
        for (s = 0; EOD != polys_actual[s]; ) // ポリゴンごと
        {
            // このポリゴンの各変換後頂点をコピーする
            boolean in_clip = false;
            int x_min, x_max, y_min, y_max, y_min_p, z_order_min;
            x_min = x_max = y_min = y_max = y_min_p = z_order_min = -123;
            for (d = 0; EOD != polys_actual[s]; ++ d, ++ s) // このポリゴン内の各頂点ごと
            {
                // 変換後頂点バッファの現在位置
                Vertex trvert = get_trvert(polys_actual[s]);
                in_clip |= trvert.in_clip;
                // 変換後頂点が画面上か手前にある場合はこのポリゴンをスキップする
                if (trvert.z_order <= 0)
                {
                    s += get_vert_cnt(polys_actual, s) + 1;
                    /*C*goto/*J*/continue/**/ label_polys;
                }
                // このポリゴンの変換後頂点バッファの現在位置
                set_trpolyvert(d, trvert);
                // このポリゴンの外接四角形と Z-order を計算
                if (0 == d)
                {
                    // このポリゴンの最初の変換後頂点
                    x_min = trvert.x2;
                    x_max = trvert.x2;
                    y_min = trvert.y2;
                    y_min_p = d;
                    y_max = trvert.y2;
                    z_order_min = trvert.z_order;
                }
                else
                {
                    // このポリゴンの次の変換後頂点
                    if (x_min > trvert.x2)   x_min = trvert.x2;
                    if (x_max < trvert.x2)   x_max = trvert.x2;
                    if (y_min > trvert.y2) { y_min = trvert.y2; y_min_p = d; }
                    if (y_max < trvert.y2)   y_max = trvert.y2;
                    if (z_order_min < trvert.z_order) z_order_min = trvert.z_order;
                }
            }
            ++ s; // 次の頂点

            // このポリゴンが有効化のチェック
            // 変換後頂点が 1 つもクリップ内になければこのポリゴンをスキップ
            if (false == in_clip)
            {
                continue;
            }
            // 変換後頂点が 1 つもビューポート内になければこのポリゴンをスキップ
            if ((x_max < 0) || (x_min >= world.viewport_width)
             || (y_max < 0) || (y_min >= world.viewport_height))
            {
                continue;
            }
            // 直線でない(RENDER_POLYLINE でない、かつ 3 角形以上)かつ幅 0 のポリゴンはスキップ
            if ((false != is_poly) && (d >= 3))
            {
                if ((x_max == x_min) || (y_max == y_min))
                {
                    continue;
                }
            }
            // 裏側を向いた RENDER_POLYGON | RENDER_POLYFRAME のポリゴンはスキップ
            if (0 != ((RENDER_POLYGON | RENDER_POLYFRAME) & render_org))
            {
                Vertex p0 = get_trpolyvert(y_min_p);
                Vertex p1 = get_trpolyvert((y_min_p + d - 1) % d);
                Vertex p2 = get_trpolyvert((y_min_p     + 1) % d);
                if ((p1.x2 - p0.x2) * (p2.y2 - p0.y2)
                  < (p1.y2 - p0.y2) * (p2.x2 - p0.x2))
                {
                    continue;
                }
            }

            // ポリゴンをポリゴンバッファに追加する
            {
                trshown = true;
                Polygon trpoly = get_trpoly(0);
                trpoly.render_mode = render_actual;
                //trpoly.vert_idx    = trpolyvert_cnt; append_buffer() で設定
                trpoly.vert_cnt     = d;
                trpoly.z_order      = z_order_min;
                trpoly.string       = string;
                trpoly.texture      = null;
                if (SHADING_TEXTURE == (SHADING_TEXTURE & render_actual))
                {
                    trpoly.texture      = texture;
                }
                append_buffer(trpoly, z_order_min, d, render_actual);
            }
/*C*label_polys: ;/**/
        }
        // 変換後頂点バッファの現在位置
        advance_trvert(trcount);
_R(world.append_time).end();
    }

/*------------------------------------------------------------*/

    /**
     * フォグの明るさを取得。
     * 
     * @param   z       z 座標。
     * @return  フォグの明るさ[0, {@link #BRIGHTNESS_BORDER}]。
     */
/*J*/
    public int get_fog_brightness(int z) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_fog_brightness(int z);
#else
    int Java3DModel::get_fog_brightness(int z) {
        JMEMBER(Java3DWorld, world);
/**/
        if (0 == fog_z)
        {
            return BRIGHTNESS_BORDER1;
        }
        int z2 = (z - fog_z) * 5 / 4;
        int c2 = world.clip_z - fog_z;
        if (z2 >= c2)
        {
            return 0;
        }
        if (z2 <= 0)
        {
            return BRIGHTNESS_BORDER1;
        }
        return BRIGHTNESS_BORDER1 - BRIGHTNESS_BORDER1 * z2 / c2;
    }

    /**
     * フォグのアルファ成分を取得。
     * 
     * @param   z       z 座標。
     * @return  フォグのアルファ成分。
     */
/*J*/
    public int get_fog_alpha(int z) {
/*C*
#endif
#ifdef _IS_H_
public:
    int get_fog_alpha(int z);
#else
    int Java3DModel::get_fog_alpha(int z) {
        JMEMBER(Java3DWorld, world);
/**/
        if (0 == fog_z)
        {
            return 255;
        }
        int z2 = (z - fog_z) * 6 / 4;
        int c2 = world.clip_z - fog_z;
        if (z2 >= c2)
        {
            int res = 255 - (z2 - c2) * 255 * 2 / c2;
            return (res <= 0) ? 0 : res;
        }
        return 255;
    }

    /**
     * フォグの色を取得。
     * 
     * @param   z       z 座標。
     * @param   color   元の色(RGB)。
     * @return  フォグの明るさ[0, {@link #BRIGHTNESS_BORDER}] で正規化された色。
     * @see     #get_brightness_color(int, int)
     */
/*J*/
    public int get_fog_color(int z, int color) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_fog_color(int z, int color);
#else
    int Java3DModel::get_fog_color(int z, int color) {
/**/
        int fog = get_fog_brightness(z);
        return (fog < BRIGHTNESS_BORDER2) ? get_brightness_color(color, fog) : color;
    }

    /**
     * ベクトルのライティングの明るさを取得。
     * 
     * @param   vert
     * @param   lx
     * @param   ly
     * @param   lz
     * @return  ベクトルのライティングの明るさ[0, {@link #BRIGHTNESS_MAX}]。
     */
/*J*/
    public int get_vertex_angle(Vertex vert, int lx, int ly, int lz) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_vertex_angle(Vertex& vert, int lx, int ly, int lz);
#else
    int Java3DModel::get_vertex_angle(Vertex& vert, int lx, int ly, int lz) {
/**/
        int angle = (int)get_cosine_angle(
/*int*
            vert.x3 + (lx << 16),
            vert.y3 + (ly << 16),
            vert.z3 + (lz << 16));
/*double*/
            vert.x3 + (lx * 65536.0),
            vert.y3 + (ly * 65536.0),
            vert.z3 + (lz * 65536.0));
/**/
        return angle;
    }

    /**
     * ポリゴンの法線ベクトルのライティングの明るさを取得。
     * 
     * @param   verts       頂点座標配列。
     * @param   vert_idx    y 座標が最小の頂点のインデックス。
     * @return  ポリゴンの法線ベクトルのライティングの明るさ[0, {@link #BRIGHTNESS_MAX}]。
     */
/*J*/
    public int get_polygon_angle(Vertex[] verts, int vert_idx) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_polygon_angle(Vertex* verts, int vert_idx);
#else
    int Java3DModel::get_polygon_angle(Vertex* verts, int vert_idx) {
/**/
        if (KIND_FRAGMENT2 == kind)
        {
            return BRIGHTNESS_BORDER1;
        }
/*ANGLE_INT*
        // Direction vectors : 方向ベクトル ; ^16 -> ^4
        long vx1 = (verts[vert_idx + 1].x3 - verts[vert_idx].x3) >> 12;
        long vx2 = (verts[vert_idx + 2].x3 - verts[vert_idx].x3) >> 12;
        long vy1 = (verts[vert_idx + 1].y3 - verts[vert_idx].y3) >> 12;
        long vy2 = (verts[vert_idx + 2].y3 - verts[vert_idx].y3) >> 12;
        long vz1 = (verts[vert_idx + 1].z3 - verts[vert_idx].z3) >> 12;
        long vz2 = (verts[vert_idx + 2].z3 - verts[vert_idx].z3) >> 12;
        // Normal vector : 法線ベクトル ; ^4 * ^4 -> ~8
        long nx = vy1 * vz2 - vy2 * vz1;
        long ny = vz1 * vx2 - vz2 * vx1;
        long nz = vx1 * vy2 - vx2 * vy1;
        return get_cosine_angle(nx, ny, nz);
/*ANGLE_DOUBLE*/
        // Direction vectors : 方向ベクトル ; ^16 -> ^8
        double vx1 = (verts[vert_idx + 1].x3 - verts[vert_idx].x3) / 4096.0;
        double vx2 = (verts[vert_idx + 2].x3 - verts[vert_idx].x3) / 4096.0;
        double vy1 = (verts[vert_idx + 1].y3 - verts[vert_idx].y3) / 4096.0;
        double vy2 = (verts[vert_idx + 2].y3 - verts[vert_idx].y3) / 4096.0;
        double vz1 = (verts[vert_idx + 1].z3 - verts[vert_idx].z3) / 4096.0;
        double vz2 = (verts[vert_idx + 2].z3 - verts[vert_idx].z3) / 4096.0;
        // Normal vector : 法線ベクトル ; ^8 * ^8 -> ^16
        double nx = vy1 * vz2 - vy2 * vz1;
        double ny = vz1 * vx2 - vz2 * vx1;
        double nz = vx1 * vy2 - vx2 * vy1;
        return (int)get_cosine_angle(nx, ny, nz);
/**/
    }

    /**
     * 法線ベクトルの角度を取得。
     * 
     * @param   nx  法線ベクトルの x 座標。
     * @param   ny  法線ベクトルの y 座標。
     * @param   nz  法線ベクトルの z 座標。
     * @return  法線ベクトルのライティングの明るさ[0, {@link #BRIGHTNESS_MAX}]。
     */
/*J*/
    public static double get_cosine_angle(double nx, double ny, double nz) {
/*C*
#endif
#ifdef _IS_H_
public:
    static double get_cosine_angle(double nx, double ny, double nz);
#else
    double Java3DModel::get_cosine_angle(double nx, double ny, double nz) {
        JSTATIC(Math);
/**/
        // Normal vector : 法線ベクトル ; ^16 -> ^8
        nx /= 256;
        ny /= 256;
        nz /= 256;
        // nr = abs(nx + ny + nz * 2) ; ^8 + ^2
        double nr = nx + ny + nz * 2;
        if (nr < 0)
        {
            nr = -nr;
        }
        // nr2 = sqrt((nx * nx) + (ny * ny) + (nz * nz)) ; ^8 + ^2
        double nr2 = Math.sqrt((nx * nx) + (ny * ny) + (nz * nz));
        if (0 == nr2)
        {
            return BRIGHTNESS_BORDER1;
        }
        // Cosine angle : 余弦角 = acos(nr / nr2)
        //                  近似 = nr / sqrt((1 * 1) + (1 * 1) + (2 * 2)) / nr2 ; (^8 + ^2) + ^16 - (^8 + ^2) => ^16
        // 65536 / sqrt((1 * 1) + (1 * 1) + (2 * 2)) = 65536 / sqrt(6) = 26755
        double na = nr * 26500 / nr2;
        na = na / (65536 / BRIGHTNESS_MAX);
        if (na > BRIGHTNESS_MAX - 1)
        {
            na = BRIGHTNESS_MAX - 1;
        }
        return na;
    }

    /**
     * モデルの角度を取得。
     * 
     * @return  モデルの角度。
     *              {@link Java3D#parent} が null のとき、このモデルの角度。
     *              {@link Java3D#parent} が null でないとき、
     *                  このモデルの角度 +  {@link Java3D#parent} の角度、
     *                  ただし {@link Java3D#parent} が {@link Java3D#world} のときは -。
     */
/*J*/
    public int get_a() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_a();
#else
    int Java3DModel::get_a() {
/**/
        int a = ma;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            a += (p == world) ? -_R(p).ma : _R(p).ma;
        }
        return a;
    }

    /**
     * モデルの角度を取得。
     * 
     * @return  モデルの角度。
     *              {@link Java3D#parent} が null のとき、このモデルの角度。
     *              {@link Java3D#parent} が null でないとき、
     *                  このモデルの角度 +  {@link Java3D#parent} の角度、
     *                  ただし {@link Java3D#parent} が {@link Java3D#world} のときは -。
     */
/*J*/
    public int get_b() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_b();
#else
    int Java3DModel::get_b() {
/**/
        int b = mb;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            b += (p == world) ? -(_R(p).mb + _R(world).mb0) : _R(p).mb;
        }
        return b;
    }

    /**
     * モデルの角度を取得。
     * 
     * @return  モデルの角度。
     *              {@link Java3D#parent} が null のとき、このモデルの角度。
     *              {@link Java3D#parent} が null でないとき、
     *                  このモデルの角度 +  {@link Java3D#parent} の角度、
     *                  ただし {@link Java3D#parent} が {@link Java3D#world} のときは -。
     */
/*J*/
    public int get_c() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_c();
#else
    int Java3DModel::get_c() {
/**/
        int c = mc;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            c += (p == world) ? -_R(p).mc : _R(p).mc;
        }
        return c;
    }

    /**
     * モデルの座標を取得。
     * 
     * @return  モデルの座標。
     *              {@link Java3D#parent} が null のとき、このモデルの座標。
     *              {@link Java3D#parent} が null でないとき、
     *                  このモデルの座標 +  {@link Java3D#parent} の座標、
     *                  ただし {@link Java3D#parent} が {@link Java3D#world} のときは -。
     */
/*J*/
    public int get_x() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_x();
#else
    int Java3DModel::get_x() {
/**/
        int x = mx;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            x += (p == world) ? -_R(p).mx : _R(p).mx;
        }
        return x;
    }

    /**
     * モデルの座標を取得。
     * 
     * @return  モデルの座標。
     *              {@link Java3D#parent} が null のとき、このモデルの座標。
     *              {@link Java3D#parent} が null でないとき、
     *                  このモデルの座標 +  {@link Java3D#parent} の座標、
     *                  ただし {@link Java3D#parent} が {@link Java3D#world} のときは -。
     */
/*J*/
    public int get_y() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_y();
#else
    int Java3DModel::get_y() {
/**/
        int y = my;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            y += (p == world) ? - _R(p).my : _R(p).my;
        }
        return y;
    }

    /**
     * モデルの座標を取得。
     * 
     * @return  モデルの座標。
     *              {@link Java3D#parent} が null のとき、このモデルの座標。
     *              {@link Java3D#parent} が null でないとき、
     *                  このモデルの座標 +  {@link Java3D#parent} の座標、
     *                  ただし {@link Java3D#parent} が {@link Java3D#world} のときは -。
     */
/*J*/
    public int get_z() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_z();
#else
    int Java3DModel::get_z() {
/**/
        int z = mz;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            z += (p == world) ? -_R(p).mz : _R(p).mz;
        }
        return z;
    }

    /**
     * モデルの角度・座標を取得。
     * 
     * @return  モデルの角度・座標。
     */
/*J*/
    public int get_lx() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_lx();
#else
    int Java3DModel::get_lx() {
/**/
        int x = lx;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            x += _R(p).lx;
        }
        return x;
    }

    /**
     * モデルの角度・座標を取得。
     * 
     * @return  モデルの角度・座標。
     */
/*J*/
    public int get_ly() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_ly();
#else
    int Java3DModel::get_ly() {
/**/
        int y = ly;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            y += _R(p).ly;
        }
        return y;
    }

    /**
     * モデルの角度・座標を取得。
     * 
     * @return  モデルの角度・座標。
     */
/*J*/
    public int get_lz() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_lz();
#else
    int Java3DModel::get_lz() {
/**/
        int z = lz;
        for (Java3D/*C** /**/ p = parent; null != p; p = _R(p).parent)
        {
            z += _R(p).lz;
        }
        return z;
    }

    /**
     * モデルの描画モードを取得。
     * 
     * @return  モデルの描画モード。
     */
/*J*/
    public int get_render_mode() {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual int get_render_mode();
#else
    int Java3DModel::get_render_mode() {
        JMEMBER(Java3DWorld, world);
/**/
        int result = (render_mode & world.render_mode) & ~RENDER_MASK & ~APPEND_MASK;
        if (RENDER_STRING == (RENDER_STRING & render_mode))
        {
            result |= RENDER_STRING;
        }
        else
        if (RENDER_POLYGON == (RENDER_POLYGON & render_mode & world.render_mode))
        {
            result |= RENDER_POLYGON;
        }
        else
        if (RENDER_POLYFRAME == (RENDER_POLYFRAME & render_mode & world.render_mode))
        {
            result |= RENDER_POLYFRAME;
        }
        else
        if (RENDER_POLYLINE == (RENDER_POLYLINE & render_mode & world.render_mode))
        {
            result |= RENDER_POLYLINE;
        }
        if (APPEND_SORT == (APPEND_SORT & render_mode & world.render_mode))
        {
            result |= APPEND_SORT;
        }
        else
        {
            result |= (APPEND_SORT == (APPEND_SORT & render_mode))
                ? APPEND_BACK : render_mode & APPEND_MASK;
        }
        return result;
    }

/*J*/
    public Vertex get_trvert(int index) {
/*C*
#endif
#ifdef _IS_H_
    Vertex& get_trvert(int index);
#else
    Java3DModel::Vertex& Java3DModel::get_trvert(int index) {
        JMEMBER(Java3DWorld, world);
/**/
        return world.get_trvert(index);
    }

/*J*/
    public Vertex get_trpolyvert(int index) {
/*C*
#endif
#ifdef _IS_H_
    Vertex& get_trpolyvert(int index);
#else
    Java3DModel::Vertex& Java3DModel::get_trpolyvert(int index) {
        JMEMBER(Java3DWorld, world);
/**/
        return world.get_trpolyvert(index);
    }

/*J*/
    public void set_trpolyvert(int index, Vertex trvert) {
/*C*
#endif
#ifdef _IS_H_
    void set_trpolyvert(int index, Vertex* trvert);
#else
    void Java3DModel::set_trpolyvert(int index, Vertex* trvert) {
        JMEMBER(Java3DWorld, world);
/**/
        world.set_trpolyvert(index, trvert);
    }

/*J*/
    public Polygon get_trpoly(int index) {
/*C*
#endif
#ifdef _IS_H_
    Polygon& get_trpoly(int index);
#else
    Java3DModel::Polygon& Java3DModel::get_trpoly(int index) {
        JMEMBER(Java3DWorld, world);
/**/
        return world.get_trpoly(index);
    }

/*J*/
    public void append_buffer(Polygon trpoly, int z_order, int vert_cnt, int mode) {
/*C*
#endif
#ifdef _IS_H_
    void append_buffer(Polygon* trpoly, int z_order, int vert_cnt, int mode);
#else
    void Java3DModel::append_buffer(Polygon* trpoly, int z_order, int vert_cnt, int mode) {
        JMEMBER(Java3DWorld, world);
/**/
        world.append_buffer(trpoly, z_order, vert_cnt, mode);
    }

/*J*/
    public void advance_trvert(int trcount) {
/*C*
#endif
#ifdef _IS_H_
    void advance_trvert(int trcount);
#else
    void Java3DModel::advance_trvert(int trcount) {
        JMEMBER(Java3DWorld, world);
/**/
        world.advance_trvert(trcount);
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
};
#endif
/**/

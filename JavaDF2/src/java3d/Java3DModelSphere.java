/*
 * $Id: Java3DModelSphere.java,v 1.13 2008/03/06 16:43:59 matsushima Exp $
 */

/*J*/
package java3d;

import javarender.JavaRenderTexture;

/*C*
#ifdef _IS_H_
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "Java3DModel.cpp"

class Java3DModelSphere;

#else

#define _IS_H_

#include "Java3DModelSphere.cpp"
#include "Java3DWorld.cpp"
#include <math.h>

#undef _IS_H_
#endif
/**/

/**
 * 球体モデルの基本クラス。
 * 
 * @since   1.0 2006/08/04 matsushima
 * @author  1.0 2006/08/04 matsushima
 * @version $Id: Java3DModelSphere.java,v 1.13 2008/03/06 16:43:59 matsushima Exp $
 * 
 * $Log: Java3DModelSphere.java,v $
 * Revision 1.13  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.27  2008/03/06 15:39:49  matsushima
 * h/cpp 共通化
 *
 * Revision 1.26  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.25  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.24  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.23  2007/05/24 01:01:36  matsushima
 * no message
 *
 * Revision 1.22  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRenderInterface を Java3D から分離
 *
 * Revision 1.16  2007/05/16 20:57:58  matsushima
 * テクスチャマッピング
 *
 * Revision 1.12  2007/05/14 13:38:19  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.10  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.7  2007/05/08 22:13:37  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.6  2007/05/08 15:25:01  matsushima
 * スタティックメンバアクセス :: -> .
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
public class Java3DModelSphere extends Java3DModel
{
/*C*
#ifdef _IS_H_
class Java3DModelSphereStatic : public virtual Java3DModelStatic
{
/**/
/*J*/
    public static final int
/*C*
public:
    enum {
/**/
        DIV_A0 = 16,
        DIV_DA = 4,
        DIV_B = 16
/*J*/
     ;
/*C*
     };
/**/

    /**
     * 球体モデルを初期化する。
     * 
     * @param model
     * @param kind
     * @param count
     * @param damage
     * @param render_mode
     * @param width
     * @param height
     * @param unit
     * @param surfaces
     * @param texture
     * @param texture_color_tbl
     * @param texture_colors
     * @param vert_colors
     * @param vert_height
     * @param div_a0
     * @param div_da
     * @param div_b
     */
/*J*/
    public static void init(
        Java3DModel model, int kind, int count, int damage, int render_mode,
        int width, int height, int unit, int surfaces,
        int[] texture, int[] texture_color_tbl, int texture_colors, int vert_colors, int vert_height,
        int div_a0, int div_da, int div_b) {
/*C*
#endif
#ifdef _IS_H_
public:
    static void init(
        Java3DModel* model, int kind, int count, int damage, int render_mode,
        int width, int height, int unit, int surfaces,
        int* texture, int* texture_color_tbl, int texture_colors, int vert_colors, int vert_height,
        int div_a0, int div_da, int div_b);
#else
    void Java3DModelSphereStatic::init(
        Java3DModel* model, int kind, int count, int damage, int render_mode,
        int width, int height, int unit, int surfaces,
        int* texture, int* texture_color_tbl, int texture_colors, int vert_colors, int vert_height,
        int div_a0, int div_da, int div_b) {
        JSTATIC(Math);
/**/
//Log.out("Java3DModelSphere.init() :");
//Log.out("< div_a0 = " + div_a0 + ", div_da = " + div_da + ", div_b = " + div_b);
        int p, d, a, b, div_a;

        // 頂点バッファを確保する
        p = 0;
        for (b = 0; b <= div_b; ++ b)
        {
            p += surfaces * 4 * get_div_a(b, div_a0, div_da); // d = -1,1: color, x, y, z
        }
        int/*C** /*J*/[]/**/ verts = new int[p + 1];
//Log.out("> verts.length = " + (p + 1) + ", vert_cnt = " + (p / 4));
        int/*C** /*J*/[]/**/ texture_xs = new int[p / 4 + 1];
        int/*C** /*J*/[]/**/ texture_ys = new int[p / 4 + 1];

        // 頂点バッファを初期化する
        p = 0;
        int pt = 0;
        for (d = -1; d < surfaces; d += 2)
        {
            for (b = 0; b <= div_b; ++ b)
            {
                double y = height / 2.0 * Math.cos(Math.PI / 2.0 * b / div_b) * d;
                double r = width  / 2.0 * Math.sin(Math.PI / 2.0 * b / div_b);
                div_a = get_div_a(b, div_a0, div_da);
                for (a = 0; a < div_a; ++ a)
                {
                    double x = r * Math.cos(2.0 * Math.PI * a / div_a);
                    double z = r * Math.sin(2.0 * Math.PI * a / div_a);
                    int c = get_vert_color(
                        1 << unit, 2.0 * Math.PI * a / div_a, (double)b / div_b, surfaces,
                        texture, texture_color_tbl, texture_xs, texture_ys, pt ++);
                    double h;
                    if (null != texture_color_tbl)
                    {
                        verts[p ++] = texture_color_tbl[c * vert_colors / texture_colors];
                        h = 1.0 + (double)c * vert_height / texture_colors / (width / 2);
                    }
                    else
                    {
                        verts[p ++] = c;
                        c = ((c >> 16) & 0xff) + ((c >> 8) & 0xff) + (c & 0xff);
                        h = 1.0 + (double)c * vert_height / (256 * 3);
                    }
                    verts[p ++] = (int)(x * h);
                    verts[p ++] = (int)(y * h);
                    verts[p ++] = (int)(z * h);
                }
            }
        }
        verts[p ++] = EOD;
//Log.out("> p = " + p);

        // ポリゴンバッファを確保する
        p = 0;
        b = 1;
        p += surfaces * 4 * get_div_a(b, div_a0, div_da); // d = 0,1: p0, p1, p2, EOD
        for (b = 1; b < div_b; ++ b)
        {
            p += surfaces * 4 * (2 * get_div_a(b, div_a0, div_da) + div_da); // d = 0,1
        }
        int/*C** /*J*/[]/**/ polys = new int[p + 1];
//Log.out("> polys.length = " + (p + 1) + ", poly_cnt = " + p / 4);

        // ポリゴンバッファを初期化する
        p = 0;
        int p0, p1 = 0;
        for (d = 0; d < surfaces; ++ d)
        {
            p0 = p1;
            p1 = p0 + get_div_a(0, div_a0, div_da);
            b = 1;
            div_a = get_div_a(b, div_a0, div_da);
            for (a = 0; a < div_a; ++ a)
            {
                polys[p + 0] = p0;
                polys[p + 1 + d] = p1 + a;
                polys[p + 2 - d] = p1 + (a + 1) % div_a;
                polys[p + 3] = EOD;
                p += 4;
            }
            p0 += get_div_a(0, div_a0, div_da);
            p1 += get_div_a(1, div_a0, div_da);
            for (b = 1; b < div_b; ++ b)
            {
////Log.out("> " + p + "," + p0 + "," + p1);
                div_a = get_div_a(b, div_a0, div_da);
                for (a = 0; a < div_a; ++ a, ++ p0, ++ p1)
                {
                    polys[p + 0 + d] = p0;
                    polys[p + 1 - d] = p1;
                    polys[p + 2] = p1 + 1;
                    polys[p + 3] = EOD;
                    p += 4;
                    polys[p + 0] = p0;
                    polys[p + 1 + d] = p1 + 1;
                    polys[p + 2 - d] = (div_a - 1 != a) ? p0 + 1 : p0 + 1 - div_a;
                    polys[p + 3] = EOD;
                    p += 4;
                    if (0 == (a + 1) % (div_a / div_da))
                    {
                        polys[p + 0] = (div_a - 1 != a) ? p0 + 1 : p0 + 1 - div_a;
                        polys[p + 1 + d] = p1 + 1;
                        polys[p + 2 - d] = (div_a - 1 != a) ? p1 + 2 : p0 + 1;
                        polys[p + 3] = EOD;
                        p += 4;
                        ++ p1;
                    }
                }
            }
        }
        polys[p] = EOD;
        ++ p;
//Log.out("> p = " + p);

        _R(model).init(kind, count, damage, render_mode, verts, polys, null);
        _R(model).init_texture(new JavaRenderTexture(texture, 1 << unit, 1 << unit, texture_xs, texture_ys));
    }

    /**
     * y 軸周りの分割数を返す。
     * 
     * @param b
     * @param div_a0
     * @param div_da
     * @return  y 軸周りの分割数。
     */
/*J*/
    private static int get_div_a(int b, int div_a0, int div_da) {
/*C*
#endif
#ifdef _IS_H_
private:
    static int get_div_a(int b, int div_a0, int div_da);
#else
    int Java3DModelSphereStatic::get_div_a(int b, int div_a0, int div_da) {
/**/
        // div_a0 =  8, div_da = 4 : 1  8 12 ...
        // div_a0 = 16, div_da = 4 : 1 16 20 ...
        return (0 == b) ? 1 : div_a0 + (b - 1) * div_da;
    }

    /**
     * a-r 座標から x-z 座標に変換し、頂点の色を返す。
     * 
     * @param width
     * @param a
     * @param r
     * @param surfaces
     * @param verts
     * @param vert_colors
     * @return  頂点の色。
     */
/*J*/
    private static int get_vert_color(int width, double a, double r, int surfaces,
        int[] verts, int[] vert_colors, int[] texture_xs, int[] texture_ys, int p) {
/*C*
#endif
#ifdef _IS_H_
private:
    static int get_vert_color(int width, double a, double r, int surfaces,
        int* verts, int* vert_colors, int* texture_xs, int* texture_ys, int p);
#else
    int Java3DModelSphereStatic::get_vert_color(int width, double a, double r, int surfaces,
        int* verts, int* vert_colors, int* texture_xs, int* texture_ys, int p) {
        JSTATIC(Math);
/**/
        double ra = 1.0;
        if (2 == surfaces)
        {
            // 円から矩形へ伸張
            ra = fmod(a, Math.PI / 2);
            if (ra > Math.PI / 4)
            {
                ra = Math.PI / 2 - ra;
            }
            ra = Math.cos(ra);
        }
        int x = (int)((r / ra * Math.cos(a) + 1) * width / 2);
        int y = (int)((r / ra * Math.sin(a) + 1) * width / 2);
        int color = 0, i;
        for (i = 0; i < 4; ++ i)
        {
            int xx = (2 == i) ? x + 1 : x;
            int yy = (3 == i) ? y + 1 : y;
            if (xx < 0        ) xx = 0;
            if (xx > width - 1) xx = width - 1;
            if (yy < 0        ) yy = 0;
            if (yy > width - 1) yy = width - 1;
            color += (null != vert_colors)
                ? verts[xx + width * yy]
                : (verts[xx + width * yy] >> 2) & 0x003f3f3f;
            if (0 == i)
            {
                texture_xs[p] = xx;
                texture_ys[p] = yy;
            }
        }
        return (null != vert_colors) ? color / 4 : color | 0xff000000;
    }
/*C*
#endif
#ifdef _IS_H_
};

class Java3DModelSphere : public Java3DModel, public Java3DModelSphereStatic
{
/**/

    /**
     * 球体モデルを構築する。
     * 
     * @param   world   このモデルが参照する空間。
     * @param   parent  このオブジェクトが参照するオブジェクト。
     *                  このオブジェクトの座標は parent からの相対座標になる。
     */
/*J*/
    public Java3DModelSphere(Java3DWorld world, Java3D parent) {
        super(world, parent);
/*C*
#endif
#ifdef _IS_H_
public:
    Java3DModelSphere(Java3DWorld* world, Java3D* parent);
#else
    Java3DModelSphere::Java3DModelSphere(Java3DWorld* world, Java3D* parent)
        : Java3DModel(world, parent) {
/**/
    }

    /**
     * 球体モデルを破棄する。
     */
/*C*
#endif
#ifdef _IS_H_
public:
    virtual ~Java3DModelSphere();
#else
    Java3DModelSphere::~Java3DModelSphere() {
       // delete[] verts;
       // delete[] polys;
    }
/**/

    /**
     * 球体モデルを初期化する。
     * 
     * @param kind
     * @param count
     * @param damage
     * @param render_mode
     * @param width
     * @param height
     * @param unit
     * @param surfaces
     * @param texture
     * @param texture_color_tbl
     * @param texture_colors
     * @param vert_colors
     * @param vert_height
     * @param div_a0
     * @param div_da
     * @param div_b
     */
/*J*/
    public void init(
        int kind, int count, int damage, int render_mode,
        int width, int height, int unit, int surfaces,
        int[] texture, int[] texture_color_tbl, int texture_colors, int vert_colors, int vert_height,
        int div_a0, int div_da, int div_b) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void init(
        int kind, int count, int damage, int render_mode,
        int width, int height, int unit, int surfaces,
        int* texture, int* texture_color_tbl, int texture_colors, int vert_colors, int vert_height,
        int div_a0, int div_da, int div_b);
#else
    void Java3DModelSphere::init(
        int kind, int count, int damage, int render_mode,
        int width, int height, int unit, int surfaces,
        int* texture, int* texture_color_tbl, int texture_colors, int vert_colors, int vert_height,
        int div_a0, int div_da, int div_b) {
    Java3DModelSphereStatic::
/**/
        init(this, kind, count, damage, render_mode,
            width, height, unit, surfaces,
            texture, texture_color_tbl, texture_colors, vert_colors, vert_height,
            div_a0, div_da, div_b);
    }

    /**
     * 球体モデルを初期化する。
     * 
     * @param world
     * @param parent
     * @param width
     * @param height
     * @param unit_min
     * @param unit_max
     * @param surfaces
     * @param frac
     * @param frac_height
     * @param frac_unit
     * @param color_tbl
     * @param frac2
     * @param rate2
     * @param unit_mul
     * @return 球体モデル。
     */
/*J*/
    public Java3DModelSphere[] init_models(
        int width, int height, int unit_min, int unit_max, int surfaces,
        int[] frac, int frac_height, int frac_unit, final int[] color_tbl,
        int[] frac2, int rate2, int unit_mul) {
/*C*
#endif
#ifdef _IS_H_
public:
    Java3DModelSphere** init_models(
        int width, int height, int unit_min, int unit_max, int surfaces,
        int* frac, int frac_height, int frac_unit, const int* color_tbl,
        int* frac2, int rate2, int unit_mul);
#else
    Java3DModelSphere** Java3DModelSphere::init_models(
        int width, int height, int unit_min, int unit_max, int surfaces,
        int* frac, int frac_height, int frac_unit, const int* color_tbl,
        int* frac2, int rate2, int unit_mul) {
#define this (*this)
#define final static const
        JSTATIC(Java3D);
        JSTATIC(Math);
/**/
        int/*J*/[]/*C** /**/ vert_colors = create_color_table(height, color_tbl);
        int div_count_max = 1 << frac_unit;
        // テクスチャの合成
        if (null != frac2)
        {
            int thre = frac_height * (rate2 - 1) / rate2;
            int i;
            for (i = 0; i < div_count_max * div_count_max; ++ i)
            {
                frac[i] = vert_colors[frac[i] * height / frac_height];
                if (frac2[i] > thre)
                {
                    int c = (frac2[i] - thre) * 256 / frac_height * rate2;
                    int r = (frac[i] >> 16) & 0xff;
                    int g = (frac[i] >>  8) & 0xff;
                    int b = (frac[i] >>  0) & 0xff;
                    int c2 = 256 - c * 2;
                    if (c2 < 0) c2 = 0;
                    r = (r * c2 / 256) + c;
                    g = (g * c2 / 256) + c;
                    b = (b * c2 / 256) + c;
                    frac[i] = 0xff000000 | (r << 16) | (g << 8) | b;
                }
            }
            jdelete(frac2);
        }
        // 赤道付近の縁を暗くする
        if (1 == surfaces)
        {
            int thre = div_count_max / 8;
            int x, y;
            for (y = 0; y < div_count_max; ++ y)
            {
                for (x = 0; x < div_count_max; ++ x)
                {
                    int px, py, p;
                    if (2 == surfaces)
                    {
                        // 円から矩形へ伸張
                        px = (x < thre) ? x : div_count_max - 1 - x;
                        py = (y < thre) ? y : div_count_max - 1 - y;
                        p = (px < py) ? px : py;
                    }
                    else
                    {
                        // 円から円へ
                        px = x - div_count_max / 2;
                        py = y - div_count_max / 2;
                        p = (int)(div_count_max / 2 - Math.sqrt((px * px) + (py * py)));
                    }
                    if (p < thre)
                    {
                        int brightness = BRIGHTNESS_BORDER2 * p / thre;
                        frac[x + y * div_count_max]
                            = get_brightness_color(frac[x + y * div_count_max], brightness);
                    }
                }
            }
        }
        // 色インデックスの配列を ARGB に変換する
        if (null == frac2)
        {
            index_to_color(frac, frac, div_count_max * div_count_max, vert_colors, height, frac_height);
        }
        // バイリニアフィルタ(線形補完)
        if (unit_mul > 0)
        {
            int mul = 1 << unit_mul;
            frac2 = zoom_texture(frac, div_count_max, div_count_max, mul, mul);
            jdelete(frac);
            frac = frac2;
            frac_unit += unit_mul;
            div_count_max *= mul;
        }
        // モデルを作成する
        Java3DModelSphere/*J*/[]/*C*** /**/ models = new Java3DModelSphere/*C** /**/[unit_max + 1 - unit_min]/**/;
        int unit;
        for (unit = unit_min; unit <= unit_max; ++ unit)
        {
            int div = 1 << (unit - 1);
            models[unit - unit_min] = new Java3DModelSphere(world, parent);
            _R(models[unit - unit_min]).init(kind, count, damage, render_mode,
                width, width, frac_unit, 1,
                frac, null, frac_height, height, 0,
                16, 4, div);
        }
        jdelete(vert_colors);
        return models;
    }

    /**
     * このモデルの各頂点を座標変換・投影する。
     * 
     * @param x1
     * @param y1
     * @param z1
     */
/*J*/
    @Override // Java3DModel
    public void transform_vertexes(int x1, int y1, int z1) {
/*C*
#endif
#ifdef _IS_H_
public:
    virtual void transform_vertexes(int x1, int y1, int z1);
#else
    void Java3DModelSphere::transform_vertexes(int x1, int y1, int z1) {
        JTYPEDEF_R(Vertex);
        JSTATIC(Math);
        JMEMBER(Java3DWorld, world);
/**/
        int render_actual = get_render_mode();
        //3D のみint pers_scale    = (NULL == parent) ? 256 : world.pers_scale;
        //3D のみint pers_distance = (NULL == parent) ? 0 : world.pers_distance;
        int pers_scale    = world.pers_scale;
        int pers_distance = world.pers_distance;
        int lx = get_lx();
        int ly = get_ly();
        int lz = get_lz();
        // 精度 256 -> 4096
        int cos_a = (int)(4096.0 * Math.cos(2.0 * Math.PI / ANGLE_MAX * get_a()));
        int sin_a = (int)(4096.0 * Math.sin(2.0 * Math.PI / ANGLE_MAX * get_a()));
        int cos_b = (int)(4096.0 * Math.cos(2.0 * Math.PI / ANGLE_MAX * get_b()));
        int sin_b = (int)(4096.0 * Math.sin(2.0 * Math.PI / ANGLE_MAX * get_b()));
        int cos_c = (int)(256.0 * Math.cos(2.0 * Math.PI / ANGLE_MAX * -world.mc));
        int sin_c = (int)(256.0 * Math.sin(2.0 * Math.PI / ANGLE_MAX * -world.mc));
        int s, d;
        for (s = 0, d = 0; EOD != verts[s]; s += 4, ++ d)
        {
            int color = verts[s];
            int x = verts[s + 1];
            int y = verts[s + 2];
            int z = verts[s + 3];
            Vertex trvert = get_trvert(d);
        if ((null != texture) && (null != _R(texture).ptx))
        {
            trvert.tx = _R(texture).ptx[d];
            trvert.ty = _R(texture).pty[d];
        }
            trvert.color = color;
            int zz = (z * cos_a + x * sin_a) >> 4; // 8
            int xx = (x * cos_a - z * sin_a) >> 4;
            int yy = y * 256;
            trvert.z3 = zz * cos_b + yy * sin_b; // 16 + 4
            trvert.y3 = yy * cos_b - zz * sin_b;
            trvert.x3 = xx * 4096;
            int x2 = x1 + (trvert.x3 >> 12); // 8
            int y2 = y1 + (trvert.y3 >> 12);
            int z2 = z1 + (trvert.z3 >> 12);
            trvert.in_clip = false;
            trvert.z_order = (z2 + pers_distance) * 256 / pers_scale;
            if (trvert.z_order > 0)
            {
                trvert.in_clip = (z2 < (world.clip_z << 8)) ? true : false;
                trvert.x2 = (x2 * cos_c + y2 * sin_c) / trvert.z_order + world.viewport_x;
                trvert.y2 = (y2 * cos_c - x2 * sin_c) / trvert.z_order + world.viewport_y;
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
                }
                trvert.color = get_brightness_color(trvert.color, trvert.brightness);
            }
        }
        trcount = d;
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
};
#endif
/**/

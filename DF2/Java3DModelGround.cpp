/*
 * $Id: Java3DModelGround.cpp,v 1.24 2008/04/11 22:52:31 matsushima Exp $
 */

/*J*
package java3d;

import javarender.JavaRenderTexture;

import commons.Log;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "Log.cpp"
#include "Java3DModel.cpp"
#include "Java3DWorld.cpp"

#else // cpp

#define _IS_H_
#include "Java3DModelGround.cpp"
#undef _IS_H_

#endif
/**/

/**
 * 地形モデルの基本クラス。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: Java3DModelGround.cpp,v 1.24 2008/04/11 22:52:31 matsushima Exp $
 * 
 * <pre>
 *  <-- width ---------------------->
 *  div_width
 *  <------->
 *  0       1       2  ...       div_count - 1
 *  +-------+-------+- - - -+-------+ 0 ^           ^
 *  |       |       |       |       |   |           |
 *  |       |       |       |       |  div_width   width
 *  |       |       |       |       |   |           |
 *  +-------+-------+- - - -+-------+ 1 v           |
 *  |       |       |       |       |               |
 *  :       :       :       :       :   :           |
 *  |       |       |       |       |               |
 *  +-------+-------+- - - -+-------+ div_count - 1 v
 *  </pre>
 * 
 * $Log: Java3DModelGround.cpp,v $
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
 * Revision 1.19  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.18  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.17  2007/05/24 01:01:35  matsushima
 * no message
 *
 * Revision 1.16  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRenderInterface を Java3D から分離
 *
 * Revision 1.12  2007/05/16 20:57:58  matsushima
 * テクスチャマッピング
 *
 * Revision 1.9  2007/05/14 13:38:18  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.7  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.5  2007/05/08 22:13:37  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.4  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*
public class Java3DModelGround extends Java3DModel
{
/*C*/
#ifdef _IS_H_
class Java3DModelGround : public Java3DModel
{
/**/
    /** 地形モデルの幅・高さ。 */
/*J*
    protected int width, height, init_ground_height;
/*C*/
protected:
    int width, height, init_ground_height;
/**/
    /** 頂点の色パレット。 */
/*J*
    protected int[] vert_colors;
/*C*/
protected:
    int* vert_colors;
/**/
    /** 分解能。 */
/*J*
    public int unit, unit_max;
/*C*/
public:
    int unit, unit_max;
#endif
/**/

    /**
     * 地形モデルを構築する。
     * 
     * @param   world   このモデルが参照する空間。
     * @param   parent  このオブジェクトが参照するオブジェクト。
     *                  このオブジェクトの座標は parent からの相対座標になる。
     */
/*J*
    public Java3DModelGround(Java3DWorld world, Java3D parent) {
        super(world, parent);
/*C*/
#ifdef _IS_H_
public:
    Java3DModelGround(Java3DWorld* world, Java3D* parent);
#else
    Java3DModelGround::Java3DModelGround(Java3DWorld* world, Java3D* parent)
        : Java3DModel(world, parent) {
/**/
        vert_colors = null;
    }
/*C*/
#endif
/**/

    /**
     * 地形モデルを破棄する。
     */
/*C*/
#ifdef _IS_H_
public:
    virtual ~Java3DModelGround();
#else
    Java3DModelGround::~Java3DModelGround() {
    }
#endif
/**/

    /**
     * 地形モデルを初期化する。
     * 
     * @param   width
     * @param   height
     * @param   init_ground_height
     * @param   unit
     * @param   unit_max
     * @param   render_mode
     * @param   verts
     * @param   vert_colors
     */
/*J*
    public void init(
        int width, int height, int init_ground_height, int unit, int unit_max, int render_mode,
        int[] verts, int[] vert_colors) {
/*C*/
#ifdef _IS_H_
public:
    virtual void init(
        int width, int height, int init_ground_height, int unit, int unit_max, int render_mode,
        int* verts, int* vert_colors);
#else
    void Java3DModelGround::init(
        int width, int height, int init_ground_height, int unit, int unit_max, int render_mode,
        int* verts, int* vert_colors) {
/**/
Log::out("Java3DModelGround.init() :");
/*ground_flat*
_R(world).setPerspective(120, _R(world).max_z, _R(world).max_z, _R(world).eye_z, _R(world).mb0);
/**/
        this->width = width;
        this->height = height;
        this->init_ground_height = init_ground_height;
        this->unit = unit;
        this->unit_max = unit_max;
        this->vert_colors = vert_colors;
        if (-1 != unit)
        {
            int div_count = 1 << unit;
            int div_width = width / div_count;
/*rotate_full*/
            int div_count_2 = div_count;
/*rotate_half*
            int div_count_2 = div_count / 2;
/**/
Log::out(String("< width = ") + width + ", height = " + height + ", unit = " + unit);
Log::out(String("> div_count = ") + div_count + ", div_width = " + div_width);

            // Polygons
            int zx_cnt = (div_count_2 - 1) * (div_count_2 - 1); // z * x
            int poly_cnt = 4 * 2 * zx_cnt + 1; // [p0, p1, p2, EOD] * 2 * zx_cnt + EOD
            polys = new int[poly_cnt]; // [p0, p1, p2, EOD] * 2 * zx_cnt + EOD
            int x, z, p = 0;
            for (z = 0; z < div_count_2 - 1; ++ z)
            {
                int z1 = z + 1;
                for (x = 0; x < div_count_2 - 1; ++ x)
                {
                    int x1 = x + 1;
                    if (0 == z % 2)
                    {
                        polys[p ++] = x  + div_count_2 * z;
                        polys[p ++] = x1 + div_count_2 * z;
                        polys[p ++] = x  + div_count_2 * z1;
                        polys[p ++] = EOD;
                        polys[p ++] = x1 + div_count_2 * z;
                        polys[p ++] = x1 + div_count_2 * z1;
                        polys[p ++] = x  + div_count_2 * z1;
                        polys[p ++] = EOD;
                    }
                    else
                    {
                        x1 = x + 1;
                        polys[p ++] = x  + div_count_2 * z;
                        polys[p ++] = x1 + div_count_2 * z1;
                        polys[p ++] = x  + div_count_2 * z1;
                        polys[p ++] = EOD;
                        polys[p ++] = x  + div_count_2 * z;
                        polys[p ++] = x1 + div_count_2 * z;
                        polys[p ++] = x1 + div_count_2 * z1;
                        polys[p ++] = EOD;
                    }
                }
            }
            polys[p ++] = EOD;
Log::out(String() + "> poly_cnt = " + poly_cnt + ", p = " + p);

            // Lines
            int z_cnt = div_count_2; // z = [0 .. div_count_2)
            int l1_cnt =     div_count_2 + 1; // x =     [0, div_count_2) + EOD
            int l2_cnt = 2 * div_count_2 + 1; // x = 2 * [0, div_count_2) + EOD
            int line_cnt = (z_cnt * l1_cnt) + ((z_cnt - 1) * l2_cnt) + 1; // l1 + l2 + EOD
            lines = new int[line_cnt];
            p = 0;
            for (z = 0; z < div_count_2; ++ z)
            {
                for (x = 0; x < div_count_2; ++ x) // l1
                {
                    lines[p ++] = x + div_count_2 * z;
                }
                lines[p ++] = EOD;
                if (z == div_count_2 - 1)
                {
                    break;
                }
                for (x = 0; x < div_count_2; ++ x) // l2
                {
                    lines[p ++] = x + div_count_2 * (z     + (z % 2));
                    lines[p ++] = x + div_count_2 * (z + 1 - (z % 2));
                }
                lines[p ++] = EOD;
            }
            lines[p ++] = EOD;
Log::out(String() + "> line_cnt = " + line_cnt + ", p = " + p);
        }

        /*J*super./*C*/Java3DModel::/**/init(KIND_USED, 0, 0, render_mode, verts, polys, lines);
//        setTexture(new JavaRenderTexture(verts, 1 << unit_max, 1 << unit_max, null, null));
        lx = -2000;
        ly = -000;
        lz = -2000;
    }
/*C*/
#endif
/**/

    /**
     * 地形モデルを初期化する。
     * 
     * @param world
     * @param parent
     * @param width
     * @param height
     * @param init_ground_height
     * @param unit_min
     * @param unit_max
     * @param render_mode
     * @param verts
     * @param vert_colors
     * @return  地形モデル。
     */
/*J*
    public Java3DModelGround[] init_models(int unit_min) {
/*C*/
#ifdef _IS_H_
public:
    virtual Java3DModelGround** init_models(int unit_min);
#else
    Java3DModelGround** Java3DModelGround::init_models(int unit_min) {
/**/
        Java3DModelGround/*J*[]/*C*/** /**/ models = new Java3DModelGround/*C*/* /**/[unit_max + 1 - unit_min];
        int unit;
        for (unit = unit_min; unit <= unit_max; ++ unit)
        {
            models[unit - unit_min] = new Java3DModelGround(world, parent);
            int mask = Java3D::SHADING_ALPHA;
            models[unit - unit_min]->init(world->max_z * 2, height, init_ground_height, unit, unit_max, Java3D::RENDER_DEFAULT & ~mask,
                verts, vert_colors);
        }
        return models;
    }
/*C*/
#endif
/**/

    /**
     * このモデルを座標変換・投影する。
     * 
     * @see     Java3DModel#transform()
     */
/*J*
    //@Override // Java3DModel
    public void transform() {
        super.transform_vertexes(0, 0, 0);
/*C*/
#ifdef _IS_H_
public:
    virtual void transform();
#else
    void Java3DModelGround::transform() {
        Java3DModel::transform_vertexes(0, 0, 0);
/**/
        //append();
        //world.trvert_cnt += vert_cnt; // update vertex buffer count
    }
/*C*/
#endif
/**/

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
/*J*
    @Override // Java3DModel
    public void transform_vertexes(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c) {
/*C*/
#ifdef _IS_H_
protected:
    virtual void transform_vertexes(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c);
#else
    void Java3DModelGround::transform_vertexes(int x1, int y1, int z1,
        int render_actual, int pers_distance, int pers_scale, int lx, int ly, int lz,
        int cos_a, int sin_a, int cos_b, int sin_b, int cos_c, int sin_c) {
/**/
        int div_count_max = 1 << unit_max;
        int div_count = 1 << unit;
        int div_width = width / div_count;
/*rotate_full*/
        int div_count_2 = div_count;
        int wz0 = - (width / 2);
        int wx0 = - (width / 2);
/*rotate_half*
        int div_count_2 = div_count / 2;
        int wz0 = - (width / 4) + ((width / 4 * cos_a) >> 8);
        int wx0 = - (width / 4) + ((width / 4 * sin_a) >> 8);
/**/
        // Left-bottom corner round by div_width * 2
        wz0 &= - div_width * 2;
        wx0 &= - div_width * 2;
        // Left-bottom corner mod. by div_width * 2
        int z0 = wz0 - (parent->mz & (div_width * 2 - 1));
        int x0 = wx0 - (parent->mx & (div_width * 2 - 1));
        // Left-bottom corner div. by div_width * 2
        wz0 = ((wz0 + parent->mz) & (- div_width * 2)) / (div_width * 2) * 2;
        wx0 = ((wx0 + parent->mx) & (- div_width * 2)) / (div_width * 2) * 2;
        int d = 0;
        int i, j, z, x, wz, wx;
        for (i = 0, z = z0, wz = wz0; i < div_count_2; ++ i, z += div_width, ++ wz)
        {
        for (j = 0, x = x0 + (i % 2) * div_width / 2,
                            wx = wx0; j < div_count_2; ++ j, x += div_width, ++ wx, ++ d)
            {
                int p = div_count_max * (wz & (div_count - 1)) + (wx & (div_count - 1));
                p *= div_count_max / div_count;
                int c = verts[p] * height / init_ground_height;
                int y = (c <= 220 * height / 256) ? c : 220 * height / 256;
/*ground_flat*/
//y = height / 4 * 256;
y = 0;
//y = height - 1;
/**/
                transform_vertex(x1, y1, z1,
                    render_actual, pers_distance, pers_scale, lx, ly, lz,
                    cos_a, sin_a, cos_b, sin_b, cos_c, sin_c,
                    d, vert_colors[c], x, y, z);
                Vertex trvert = get_trvert(d);
                trvert.tx = (wx /*& (div_count - 1)*/) * _R(texture).width / div_count;
                trvert.ty = (wz /*& (div_count - 1)*/) * _R(texture).width / div_count;
            }
        }
        trcount = d;
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/

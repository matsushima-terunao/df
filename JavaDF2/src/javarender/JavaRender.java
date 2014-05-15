/*
 * $Id: JavaRender.java,v 1.12 2008/03/06 16:44:00 matsushima Exp $
 */

/*J*/
package javarender;

import java3d.Java3D;
import java3d.Java3DWorld;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "JavaRenderTexture.cpp"

class JavaRenderStatic;
extern JavaRenderStatic _JavaRenderStatic;

#else // cpp

#define _IS_H_
#include "JavaRender.cpp"
#undef _IS_H_

JavaRenderStatic _JavaRenderStatic;

#endif
/**/

/**
 * JavaRender
 * 
 * @since   1.0 2007/05/23 matsushima
 * @author  1.0 2007/05/23 matsushima
 * @version $Id: JavaRender.java,v 1.12 2008/03/06 16:44:00 matsushima Exp $
 * 
 * $Log: JavaRender.java,v $
 * Revision 1.12  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.17  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.16  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.15  2008/02/24 05:52:06  matsushima
 * JavaRenderInterface -> JavaRender
 * JavaRender -> JavaRenderBuffer
 *
 * Revision 1.9  2007/05/23 18:30:22  matsushima
 * JavaRender カプセル化
 *
 * Revision 1.1  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRender を Java3D から分離
 *
 */
/*J*/
public interface JavaRender
{
/*C*
#ifdef _IS_H_
class JavaRenderStatic : public Object
{
/**/
    /**
     * 変換後の頂点。
     */
/*J*/
    public static class Vertex
    {
/*C*
public:
    class Vertex : public Object, public JBase<Vertex>
    {
    public:
/**/
        /** 頂点が {@link Java3DWorld#clip_z} より手前にあるか。 */
/*J*/
        public boolean in_clip;
/*C*
        boolean in_clip;
/**/
        /** 変換後の座標。 */
/*J*/
        public int x3, y3, z3;
/*C*
        int x3, y3, z3;
/**/
        /** 投影後の座標。 */
/*J*/
        public int x2, y2;
/*C*
        int x2, y2;
/**/
        /** 奥行き。 */
/*J*/
        public int z_order;
/*C*
        int z_order;
/**/
        /** 色。 */
/*J*/
        public int color;
/*C*
        int color;
/**/
        /** 明るさ。 */
/*J*/
        public int brightness;
/*C*
        int brightness;
/**/
        /** テクスチャ上の座標。 */
/*J*/
        public int tx, ty;
/*C*
        int tx, ty;
/**/
/*J*/
    };
/*C*
    };
/**/

    /**
     * 変換後のポリゴン。
     */
/*J*/
    public static class Polygon
    {
/*C*
public:
    class Polygon : public Object, public JBase<Polygon>
    {
    public:
/**/
        /** 手前のポリゴン。 */
/*J*/
        public Polygon next;
/*C*
        Polygon* next;
/**/
        /** 奥のポリゴン。 */
/*J*/
        public Polygon prev;
/*C*
        Polygon* prev;
/**/
        /** このポリゴンの描画方法のフラグ。
         * @see Java3D#render_mode */
/*J*/
        public int render_mode;
        public int vert_idx;
        public int vert_cnt;
        public int z_order;
/*C*
        int render_mode;
        int vert_idx;
        int vert_cnt;
        int z_order;
/**/
        /** テクスチャ。 */
/*J*/
        public JavaRenderTexture texture;
/*C*
        JavaRenderTexture* texture;
/**/
        /** render_mode が {@link #RENDER_STRING} のときに描画する文字列。 */
/*J*/
        public String string;
/*C*
        String string;
/**/
/*J*/
    };
/*C*
    };
/**/

/*J*/
    public static final int
/*C*
public:
    enum {
/**/
        /** 描画方法のマスク。 */
        RENDER_MASK             = 0xff,
        /** ワイヤーフレームを描画。 */
        RENDER_POLYLINE         = 1,
        /** ポリゴンの枠を描画。 */
        RENDER_POLYFRAME        = 2,
        /** ポリゴンを描画。 */
        RENDER_POLYGON          = 4,//3,
        /** 文字列を描画。 */
        RENDER_STRING           = 8,//4,

        /** シェーディング方法のマスク。 */
        SHADING_MASK            = 0x07 << 8,
        /** テクスチャマッピング。 */
        SHADING_TEXTURE         = 1 << 8,
        /** 各頂点の色で変化させる。 */
        SHADING_GOURAUD         = 1 << 9,
        /** 透過。 */
        SHADING_ALPHA           = 1 << 10,

        /** 描画方法とシェーディング方法のマスク。 */
        RENDER_SHADING_MASK     = RENDER_MASK | SHADING_MASK,

        /** ライティング。 */
        LIGHTING_DIFFUSE        = 1 << 11,
        /** 遠くに行くほど暗くなる。 */
        LIGHTING_FOG            = 1 << 12,

        /** ポリゴンバッファへの追加方法のフラグのマスク。 */
        APPEND_MASK             = 0xff << 16,
        /** ポリゴンバッファへの追加方法のフラグ。 */
        APPEND_NONE             = 1 << 16,
        /** ポリゴンバッファへの追加方法のフラグ。 */
        APPEND_FRONT            = 1 << 17,
        /** ポリゴンバッファへの追加方法のフラグ。 */
        APPEND_BACK             = 1 << 18,
        /** ポリゴンバッファへの追加方法のフラグ。 */
        APPEND_SORT             = 1 << 19,

        /** 明るさのしきい値。 */
        BRIGHTNESS_BORDER2 = 2048,
        /** 明るさのしきい値。 */
        BRIGHTNESS_BORDER1 = 4096,
        /** 明るさの最大値。 */
        BRIGHTNESS_MAX     = BRIGHTNESS_BORDER1 + (BRIGHTNESS_BORDER1 / 8)
/*J*/
    ;
}
/*C*
    };
};

class JavaRender : public virtual JavaRenderStatic
{
};
#endif
/**/

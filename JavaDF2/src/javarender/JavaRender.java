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
 * JavaDoc/Doxygen �Ή�
 *
 * Revision 1.17  2008/03/06 15:39:50  matsushima
 * h/cpp ���ʉ�
 *
 * Revision 1.16  2008/03/04 17:21:01  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.15  2008/02/24 05:52:06  matsushima
 * JavaRenderInterface -> JavaRender
 * JavaRender -> JavaRenderBuffer
 *
 * Revision 1.9  2007/05/23 18:30:22  matsushima
 * JavaRender �J�v�Z����
 *
 * Revision 1.1  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRender �� Java3D ���番��
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
     * �ϊ���̒��_�B
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
        /** ���_�� {@link Java3DWorld#clip_z} ����O�ɂ��邩�B */
/*J*/
        public boolean in_clip;
/*C*
        boolean in_clip;
/**/
        /** �ϊ���̍��W�B */
/*J*/
        public int x3, y3, z3;
/*C*
        int x3, y3, z3;
/**/
        /** ���e��̍��W�B */
/*J*/
        public int x2, y2;
/*C*
        int x2, y2;
/**/
        /** ���s���B */
/*J*/
        public int z_order;
/*C*
        int z_order;
/**/
        /** �F�B */
/*J*/
        public int color;
/*C*
        int color;
/**/
        /** ���邳�B */
/*J*/
        public int brightness;
/*C*
        int brightness;
/**/
        /** �e�N�X�`����̍��W�B */
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
     * �ϊ���̃|���S���B
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
        /** ��O�̃|���S���B */
/*J*/
        public Polygon next;
/*C*
        Polygon* next;
/**/
        /** ���̃|���S���B */
/*J*/
        public Polygon prev;
/*C*
        Polygon* prev;
/**/
        /** ���̃|���S���̕`����@�̃t���O�B
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
        /** �e�N�X�`���B */
/*J*/
        public JavaRenderTexture texture;
/*C*
        JavaRenderTexture* texture;
/**/
        /** render_mode �� {@link #RENDER_STRING} �̂Ƃ��ɕ`�悷�镶����B */
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
        /** �`����@�̃}�X�N�B */
        RENDER_MASK             = 0xff,
        /** ���C���[�t���[����`��B */
        RENDER_POLYLINE         = 1,
        /** �|���S���̘g��`��B */
        RENDER_POLYFRAME        = 2,
        /** �|���S����`��B */
        RENDER_POLYGON          = 4,//3,
        /** �������`��B */
        RENDER_STRING           = 8,//4,

        /** �V�F�[�f�B���O���@�̃}�X�N�B */
        SHADING_MASK            = 0x07 << 8,
        /** �e�N�X�`���}�b�s���O�B */
        SHADING_TEXTURE         = 1 << 8,
        /** �e���_�̐F�ŕω�������B */
        SHADING_GOURAUD         = 1 << 9,
        /** ���߁B */
        SHADING_ALPHA           = 1 << 10,

        /** �`����@�ƃV�F�[�f�B���O���@�̃}�X�N�B */
        RENDER_SHADING_MASK     = RENDER_MASK | SHADING_MASK,

        /** ���C�e�B���O�B */
        LIGHTING_DIFFUSE        = 1 << 11,
        /** �����ɍs���قǈÂ��Ȃ�B */
        LIGHTING_FOG            = 1 << 12,

        /** �|���S���o�b�t�@�ւ̒ǉ����@�̃t���O�̃}�X�N�B */
        APPEND_MASK             = 0xff << 16,
        /** �|���S���o�b�t�@�ւ̒ǉ����@�̃t���O�B */
        APPEND_NONE             = 1 << 16,
        /** �|���S���o�b�t�@�ւ̒ǉ����@�̃t���O�B */
        APPEND_FRONT            = 1 << 17,
        /** �|���S���o�b�t�@�ւ̒ǉ����@�̃t���O�B */
        APPEND_BACK             = 1 << 18,
        /** �|���S���o�b�t�@�ւ̒ǉ����@�̃t���O�B */
        APPEND_SORT             = 1 << 19,

        /** ���邳�̂������l�B */
        BRIGHTNESS_BORDER2 = 2048,
        /** ���邳�̂������l�B */
        BRIGHTNESS_BORDER1 = 4096,
        /** ���邳�̍ő�l�B */
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

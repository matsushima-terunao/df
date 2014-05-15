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
 * 3D �I�u�W�F�N�g(��� {@link Java3DWorld}, ���f�� {@link Java3DModel})�̒��ۃN���X�B
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: Java3D.cpp,v 1.24 2008/04/11 22:52:31 matsushima Exp $
 * 
 * $Log: Java3D.cpp,v $
 * Revision 1.24  2008/04/11 22:52:31  matsushima
 * gound �C��
 *
 * Revision 1.23  2008/03/12 16:30:47  matsushima
 * Doxygen �Ή�
 *
 * Revision 1.22  2008/03/06 16:42:45  matsushima
 * JavaDoc/Doxygen �Ή�
 *
 * Revision 1.21  2008/03/06 15:39:49  matsushima
 * h/cpp ���ʉ�
 *
 * Revision 1.20  2008/03/04 17:21:01  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.19  2007/12/01 22:14:14  matsushima
 * �ēo�^
 *
 * Revision 1.14  2007/05/14 13:38:18  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.12  2007/05/10 22:29:39  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.10  2007/05/08 22:13:37  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.9  2007/05/08 15:25:01  matsushima
 * �X�^�e�B�b�N�����o�A�N�Z�X :: -> .
 *
 * Revision 1.8  2007/05/07 21:40:04  matsushima
 * static�����o�A�N�Z�X :: -> .
 *
 * Revision 1.7  2007/05/07 21:24:08  matsushima
 * static�����o�A�N�Z�X :: -> .
 *
 * Revision 1.6  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.4  2007/04/23 17:05:48  matsushima
 * ���v���[�X
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

        /** 1��(2PI)�̊p�x�̍ő�l�B */
        ANGLE_MAX          = 65536,
        /** 1��(2PI)�̊p�x�̃}�X�N�l�B */
        ANGLE_MASK         = ANGLE_MAX - 1,
        /** sin(), cos() �̍ő�l�B */
        TRIFUNC_MAX        = 256,
        /** �I�u�W�F�N�g�f�[�^��`���́A���_���邢�͑��p�`���邢�͘A�����f�[�^�̏I����\���B */
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
     * �w�肳�ꂽ�p�x�� cos ��Ԃ��B
     * 
     * @param   a   1���� {@link #ANGLE_MAX} �Ƃ����p�x�B
     * @return  �ő�l�� {@link #TRIFUNC_MAX} �Ƃ��� cos�B
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
     * �w�肳�ꂽ�p�x�� sin ��Ԃ��B
     * 
     * @param   a   1���� {@link #ANGLE_MAX} �Ƃ����p�x�B
     * @return  �ő�l�� {@link #TRIFUNC_MAX} �Ƃ��� sin�B
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
     * ���̃I�u�W�F�N�g���Q�Ƃ����ԁB
     */
/*J*
    public Java3DWorld world;
/*C*/
public:
    Java3DWorld* world;
/**/

    /**
     * ���̃I�u�W�F�N�g���Q�Ƃ���I�u�W�F�N�g�B
     * ���̃I�u�W�F�N�g�̍��W�� parent ����̑��΍��W�ɂȂ�B
     */
/*J*
    public Java3D parent;
/*C*/
public:
    Java3D* parent;
/**/

    /**
     * ���̃I�u�W�F�N�g�� y, x, z �����̉�]�p�x�B
     */
/*J*
    public int ma, mb, mc;
/*C*/
public:
    int ma, mb, mc;
/**/

    /**
     * ���̃I�u�W�F�N�g�� x, y, z ���W�B
     */
/*J*
    public int mx, my, mz;
/*C*/
public:
    int mx, my, mz;
/**/
    /**
     * ���̃I�u�W�F�N�g�� y, x �����̉�]�p�x�̈ړ��ʁB
     */
/*J*
    public int va, vb;
/*C*/
public:
    int va, vb;
/**/

    /**
     * ���̃I�u�W�F�N�g�� x, y, z ���W�̈ړ��ʁB
     */
/*J*
    public int vx, vy, vz;
/*C*/
public:
    int vx, vy, vz;
/**/

    /**
     * ���̃I�u�W�F�N�g�̌����� x, y, z ���W�B
     */
/*J*
    public int lx, ly, lz;
/*C*/
public:
    int lx, ly, lz;
/**/

    /**
     * ���̃I�u�W�F�N�g�̃t�H�O�̂������l�B
     */
/*J*
    public int fog_z;
/*C*/
public:
    int fog_z;
/**/

    /**
     * ���̃I�u�W�F�N�g�̕`����@�̃t���O�B
     * <p>
     * �ȉ��̕`��t���O�̂����ꂩ���w�肷��B
     * <br>{@link #RENDER_POLYLINE} : ���C���[�t���[����`��B
     * <br>{@link #RENDER_POLYFRAME} : �|���S���̘g��`��B
     * <br>{@link #RENDER_POLYGON} : �|���S����`��B
     * <br>{@link #RENDER_STRING} : �������`��B
     * <p>
     * �ȉ��̃V�F�[�f�B���O�t���O��1�ȏ�w��ł���B
     * <br>{@link #SHADING_GOURAUD} : �e���_�̐F�ŕω�������B
     * <br>{@link #SHADING_ALPHA} : ���߁B
     * <p>
     * �ȉ��̃��C�e�B���O�t���O��1�ȏ�w��ł���B
     * <br>{@link #LIGHTING_DIFFUSE} : ���C�e�B���O�B
     * <br>{@link #LIGHTING_FOG} : �����ɍs���قǈÂ��Ȃ�B
     * <p>
     * �ȉ��̃|���S���o�b�t�@�ւ̒ǉ����@�̃t���O�̂����ꂩ���w�肷��B
     * <br>{@link #APPEND_NONE} : �|���S���o�b�t�@�ւ̒ǉ����@�B
     * <br>{@link #APPEND_FRONT} : �|���S���o�b�t�@�ւ̒ǉ����@�B
     * <br>{@link #APPEND_BACK} : �|���S���o�b�t�@�ւ̒ǉ����@�B
     * <br>{@link #APPEND_SORT} : �|���S���o�b�t�@�ւ̒ǉ����@�B
     */
/*J*
    public int render_mode;
/*C*/
public:
    int render_mode;
#endif
/**/

    /**
     * �I�u�W�F�N�g���\�z����B
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
     * �I�u�W�F�N�g��j������B
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

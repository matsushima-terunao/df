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
 * 3D ���f���̊�{�N���X�B
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: Java3DModel.java,v 1.14 2008/03/06 16:43:59 matsushima Exp $
 * 
 * $Log: Java3DModel.java,v $
 * Revision 1.14  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen �Ή�
 *
 * Revision 1.31  2008/03/06 15:39:49  matsushima
 * h/cpp ���ʉ�
 *
 * Revision 1.30  2008/03/04 17:21:01  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.29  2008/03/03 02:10:50  matsushima
 * render �ӂ�킯�� JavaRenderBuffer -> JavaRenderXxx
 * �e�N�X�`���� int[] -> JavaRenderTexture
 *
 * Revision 1.28  2007/12/01 22:14:14  matsushima
 * �ēo�^
 *
 * Revision 1.27  2007/05/24 01:01:35  matsushima
 * no message
 *
 * Revision 1.26  2007/05/23 15:41:43  matsushima
 * JavaRenderBuffer, JavaRenderInterface �� Java3D ���番��
 *
 * Revision 1.19  2007/05/16 20:57:58  matsushima
 * �e�N�X�`���}�b�s���O
 *
 * Revision 1.15  2007/05/14 15:58:36  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.14  2007/05/14 13:38:18  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.12  2007/05/10 22:29:39  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.9  2007/05/08 22:13:37  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.8  2007/05/08 15:25:01  matsushima
 * �X�^�e�B�b�N�����o�A�N�Z�X :: -> .
 *
 * Revision 1.7  2007/05/07 21:40:04  matsushima
 * static�����o�A�N�Z�X :: -> .
 *
 * Revision 1.6  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.3  2007/04/23 17:05:48  matsushima
 * ���v���[�X
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
     * �\��ς݂̃��f���̎�ށB
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
     * �O���f�[�V�����J���[�e�[�u���̍쐬�B
     * 
     * @param cnt
     * @param t
     * @return  �쐬���ꂽ�J���[�e�[�u���B
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
     * �F�C���f�b�N�X�̔z��� ARGB �ɕϊ�����B
     * 
     * @param dst
     * @param verts
     * @param cnt
     * @param vert_colors
     * @param mul
     * @param div
     * @return  �ϊ���̔z��B
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
     * �e�N�X�`�����g�傷��B
     * �o�C���j�A�t�B���^(���`�⊮)�B
     * 
     * @param src
     * @param width
     * @param height
     * @param mul_w
     * @param mul_h
     * @return  �g���̃e�N�X�`���B
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
     * �w�肳�ꂽ���邳�ŐF�𐳋K���B
     * 
     * @param   color       ���K�����錳�̐F(RGB)�B
     * @param   brightness  ���邳�B
     * @return  ���K�����ꂽ�F�B
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
            // ����`
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
     * �|���S���z��̌��݂̃|���S���̒��_���𐔂���B
     * 
     * @param   polys   �|���S���z��B
     * @param   s       �|���S���z����̃C���f�b�N�X�B
     * @return  ���_���B
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
     * ���_���W�z��̃����o��ݒ�B
     * 
     * @param   verts   ���_���W�z��B
     * @param   index   ���_���W�z����̃C���f�b�N�X�B
     * @param   color   �ݒ肷��F(ARGB)�B
     * @param   x       �ݒ肷�� x ���W�B
     * @param   y       �ݒ肷�� y ���W�B
     * @param   z       �ݒ肷�� z ���W�B
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
     * ���_���W�z��̐F��ݒ�B
     * 
     * @param   verts   ���_���W�z��B
     * @param   index   ���_���W�z����̃C���f�b�N�X�B-1 �̂Ƃ��͑S�ẴC���f�b�N�X�B
     * @param   value   �ݒ肷��F(ARGB)�B
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
     * ���_���W�z��� x, y, z ���W��ݒ�B
     * 
     * @param   verts   ���_���W�z��B
     * @param   index   ���_���W�z����̃C���f�b�N�X�B
     * @param   x       �ݒ肷�� x ���W�B
     * @param   y       �ݒ肷�� y ���W�B
     * @param   z       �ݒ肷�� z ���W�B
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

    /** ���f���̎�ށB */
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

    /** ���f���̃|���S���f�[�^�B */
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

    /** �ϊ���̍��W�B */
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
     * Java3DModel �I�u�W�F�N�g���\�z����B
     * 
     * @param   world   ���̃��f�����Q�Ƃ����ԁB
     * @param   parent  ���̃I�u�W�F�N�g���Q�Ƃ���I�u�W�F�N�g�B
     *                  ���̃I�u�W�F�N�g�̍��W�� parent ����̑��΍��W�ɂȂ�B
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
     * ���f��������������B
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
     * ���f���̃e�N�X�`����ݒ肷��B
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
     * ���f���̕������ݒ肷��B
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
     * ���f���̃f�[�^���폜����B
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
     * ���f���̍��W��ݒ肷��B
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
     * 2D �\���p�Ƀ��f���̍��W��ݒ肷��B
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
     * ���̃��f�����g�p����Ă��邩�B
     * 
     * {@link #kind} �� {@link #KIND_UNUSED} �łȂ��A
     * {@link #count} �� {@link #count_max} ������ {@link #count_max} �� 0 �Ȃ�g�p����Ă���B
     * 
     * @return  �g�p����Ă���� true�B
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
     * ���̃��f���𖢎g�p�ɂ���B
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
     * ���̃��f�����ړ�����B
     * 
     * {@link #count} �� +1 ���A
     * {@link #ma}, {@link #mb}, {@link #mx}, {@link #my}, {@link #mz} ��
     * {@link #va}, {@link #vb}, {@link #vx}, {@link #vy}, {@link #vz} ��������B
     * 
     * @return  {@link #count} �� +1 �������ʖ��g�p�ɂȂ����ꍇ true�B
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
     * �������f�������W�ϊ��E���e����B
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
     * ���̃��f�������W�ϊ��E���e����B
     * 
     * ���f���̍��W�ϊ�:
     * {@link #parent} �� null �ł���ꍇ�́A���f���̍��W���΍��W�Ƃ��āA���W�ϊ����s��Ȃ��B
     * {@link #parent} �� null �łȂ��ꍇ�́A{@link #parent} ����̑��΍��W�E�p�x��
     * ��΍��W�E�p�x�Ƃ��č��W�ϊ����s���B
     * �ϊ���̍��W�̏��� trxxxx �ɐݒ肳���B
     * 
     * �e���_�̍��W�ϊ��E���e:
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
     * ���̃��f���̊e���_�����W�ϊ��E���e����B
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
     * ���̃��f���̊e���_�����W�ϊ��E���e����B
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
     * ���̃��f���̊e���_�����W�ϊ��E���e����B
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
     * {@link #transform()} �ŕϊ������e���_���W�� {@link #polys} �̃C���f�b�N�X�łȂ���
     * �|���S�����쐬���A�|���S���o�b�t�@�ɒǉ�����B
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
        trshown = false; // ���̃��f�����r���[�|�[�g���ɑ��݂��邩

        // polys_actual or lines ��I��
        int render_org = render_actual = get_render_mode();
        boolean is_poly = (RENDER_POLYLINE == (RENDER_MASK & render_actual)) ? false : true;
        polys_actual = (RENDER_POLYLINE == (RENDER_MASK & render_actual)) ? lines : polys;
        if (null == polys_actual)
        {
            // RENDER_POLYLINE �ł� lines �� null �Ȃ̂� RENDER_POLYFRAME �ɂ� polys_actual ��I��
            polys_actual = polys;
            render_actual = (render_actual & ~RENDER_MASK) | RENDER_POLYFRAME;
        }
        // �`�惂�[�h�� APPEND_NONE �̏ꍇ�̓|���S�����쐬�����ɏI��
        if (APPEND_NONE == (APPEND_MASK & render_actual))
        {
            return;
        }

        // �ϊ��㒸�_���Ȃ��ă|���S�����쐬����
/*J*/label_polys:/**/
        for (s = 0; EOD != polys_actual[s]; ) // �|���S������
        {
            // ���̃|���S���̊e�ϊ��㒸�_���R�s�[����
            boolean in_clip = false;
            int x_min, x_max, y_min, y_max, y_min_p, z_order_min;
            x_min = x_max = y_min = y_max = y_min_p = z_order_min = -123;
            for (d = 0; EOD != polys_actual[s]; ++ d, ++ s) // ���̃|���S�����̊e���_����
            {
                // �ϊ��㒸�_�o�b�t�@�̌��݈ʒu
                Vertex trvert = get_trvert(polys_actual[s]);
                in_clip |= trvert.in_clip;
                // �ϊ��㒸�_����ʏォ��O�ɂ���ꍇ�͂��̃|���S�����X�L�b�v����
                if (trvert.z_order <= 0)
                {
                    s += get_vert_cnt(polys_actual, s) + 1;
                    /*C*goto/*J*/continue/**/ label_polys;
                }
                // ���̃|���S���̕ϊ��㒸�_�o�b�t�@�̌��݈ʒu
                set_trpolyvert(d, trvert);
                // ���̃|���S���̊O�ڎl�p�`�� Z-order ���v�Z
                if (0 == d)
                {
                    // ���̃|���S���̍ŏ��̕ϊ��㒸�_
                    x_min = trvert.x2;
                    x_max = trvert.x2;
                    y_min = trvert.y2;
                    y_min_p = d;
                    y_max = trvert.y2;
                    z_order_min = trvert.z_order;
                }
                else
                {
                    // ���̃|���S���̎��̕ϊ��㒸�_
                    if (x_min > trvert.x2)   x_min = trvert.x2;
                    if (x_max < trvert.x2)   x_max = trvert.x2;
                    if (y_min > trvert.y2) { y_min = trvert.y2; y_min_p = d; }
                    if (y_max < trvert.y2)   y_max = trvert.y2;
                    if (z_order_min < trvert.z_order) z_order_min = trvert.z_order;
                }
            }
            ++ s; // ���̒��_

            // ���̃|���S�����L�����̃`�F�b�N
            // �ϊ��㒸�_�� 1 ���N���b�v���ɂȂ���΂��̃|���S�����X�L�b�v
            if (false == in_clip)
            {
                continue;
            }
            // �ϊ��㒸�_�� 1 ���r���[�|�[�g���ɂȂ���΂��̃|���S�����X�L�b�v
            if ((x_max < 0) || (x_min >= world.viewport_width)
             || (y_max < 0) || (y_min >= world.viewport_height))
            {
                continue;
            }
            // �����łȂ�(RENDER_POLYLINE �łȂ��A���� 3 �p�`�ȏ�)���� 0 �̃|���S���̓X�L�b�v
            if ((false != is_poly) && (d >= 3))
            {
                if ((x_max == x_min) || (y_max == y_min))
                {
                    continue;
                }
            }
            // ������������ RENDER_POLYGON | RENDER_POLYFRAME �̃|���S���̓X�L�b�v
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

            // �|���S�����|���S���o�b�t�@�ɒǉ�����
            {
                trshown = true;
                Polygon trpoly = get_trpoly(0);
                trpoly.render_mode = render_actual;
                //trpoly.vert_idx    = trpolyvert_cnt; append_buffer() �Őݒ�
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
        // �ϊ��㒸�_�o�b�t�@�̌��݈ʒu
        advance_trvert(trcount);
_R(world.append_time).end();
    }

/*------------------------------------------------------------*/

    /**
     * �t�H�O�̖��邳���擾�B
     * 
     * @param   z       z ���W�B
     * @return  �t�H�O�̖��邳[0, {@link #BRIGHTNESS_BORDER}]�B
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
     * �t�H�O�̃A���t�@�������擾�B
     * 
     * @param   z       z ���W�B
     * @return  �t�H�O�̃A���t�@�����B
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
     * �t�H�O�̐F���擾�B
     * 
     * @param   z       z ���W�B
     * @param   color   ���̐F(RGB)�B
     * @return  �t�H�O�̖��邳[0, {@link #BRIGHTNESS_BORDER}] �Ő��K�����ꂽ�F�B
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
     * �x�N�g���̃��C�e�B���O�̖��邳���擾�B
     * 
     * @param   vert
     * @param   lx
     * @param   ly
     * @param   lz
     * @return  �x�N�g���̃��C�e�B���O�̖��邳[0, {@link #BRIGHTNESS_MAX}]�B
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
     * �|���S���̖@���x�N�g���̃��C�e�B���O�̖��邳���擾�B
     * 
     * @param   verts       ���_���W�z��B
     * @param   vert_idx    y ���W���ŏ��̒��_�̃C���f�b�N�X�B
     * @return  �|���S���̖@���x�N�g���̃��C�e�B���O�̖��邳[0, {@link #BRIGHTNESS_MAX}]�B
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
        // Direction vectors : �����x�N�g�� ; ^16 -> ^4
        long vx1 = (verts[vert_idx + 1].x3 - verts[vert_idx].x3) >> 12;
        long vx2 = (verts[vert_idx + 2].x3 - verts[vert_idx].x3) >> 12;
        long vy1 = (verts[vert_idx + 1].y3 - verts[vert_idx].y3) >> 12;
        long vy2 = (verts[vert_idx + 2].y3 - verts[vert_idx].y3) >> 12;
        long vz1 = (verts[vert_idx + 1].z3 - verts[vert_idx].z3) >> 12;
        long vz2 = (verts[vert_idx + 2].z3 - verts[vert_idx].z3) >> 12;
        // Normal vector : �@���x�N�g�� ; ^4 * ^4 -> ~8
        long nx = vy1 * vz2 - vy2 * vz1;
        long ny = vz1 * vx2 - vz2 * vx1;
        long nz = vx1 * vy2 - vx2 * vy1;
        return get_cosine_angle(nx, ny, nz);
/*ANGLE_DOUBLE*/
        // Direction vectors : �����x�N�g�� ; ^16 -> ^8
        double vx1 = (verts[vert_idx + 1].x3 - verts[vert_idx].x3) / 4096.0;
        double vx2 = (verts[vert_idx + 2].x3 - verts[vert_idx].x3) / 4096.0;
        double vy1 = (verts[vert_idx + 1].y3 - verts[vert_idx].y3) / 4096.0;
        double vy2 = (verts[vert_idx + 2].y3 - verts[vert_idx].y3) / 4096.0;
        double vz1 = (verts[vert_idx + 1].z3 - verts[vert_idx].z3) / 4096.0;
        double vz2 = (verts[vert_idx + 2].z3 - verts[vert_idx].z3) / 4096.0;
        // Normal vector : �@���x�N�g�� ; ^8 * ^8 -> ^16
        double nx = vy1 * vz2 - vy2 * vz1;
        double ny = vz1 * vx2 - vz2 * vx1;
        double nz = vx1 * vy2 - vx2 * vy1;
        return (int)get_cosine_angle(nx, ny, nz);
/**/
    }

    /**
     * �@���x�N�g���̊p�x���擾�B
     * 
     * @param   nx  �@���x�N�g���� x ���W�B
     * @param   ny  �@���x�N�g���� y ���W�B
     * @param   nz  �@���x�N�g���� z ���W�B
     * @return  �@���x�N�g���̃��C�e�B���O�̖��邳[0, {@link #BRIGHTNESS_MAX}]�B
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
        // Normal vector : �@���x�N�g�� ; ^16 -> ^8
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
        // Cosine angle : �]���p = acos(nr / nr2)
        //                  �ߎ� = nr / sqrt((1 * 1) + (1 * 1) + (2 * 2)) / nr2 ; (^8 + ^2) + ^16 - (^8 + ^2) => ^16
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
     * ���f���̊p�x���擾�B
     * 
     * @return  ���f���̊p�x�B
     *              {@link Java3D#parent} �� null �̂Ƃ��A���̃��f���̊p�x�B
     *              {@link Java3D#parent} �� null �łȂ��Ƃ��A
     *                  ���̃��f���̊p�x +  {@link Java3D#parent} �̊p�x�A
     *                  ������ {@link Java3D#parent} �� {@link Java3D#world} �̂Ƃ��� -�B
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
     * ���f���̊p�x���擾�B
     * 
     * @return  ���f���̊p�x�B
     *              {@link Java3D#parent} �� null �̂Ƃ��A���̃��f���̊p�x�B
     *              {@link Java3D#parent} �� null �łȂ��Ƃ��A
     *                  ���̃��f���̊p�x +  {@link Java3D#parent} �̊p�x�A
     *                  ������ {@link Java3D#parent} �� {@link Java3D#world} �̂Ƃ��� -�B
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
     * ���f���̊p�x���擾�B
     * 
     * @return  ���f���̊p�x�B
     *              {@link Java3D#parent} �� null �̂Ƃ��A���̃��f���̊p�x�B
     *              {@link Java3D#parent} �� null �łȂ��Ƃ��A
     *                  ���̃��f���̊p�x +  {@link Java3D#parent} �̊p�x�A
     *                  ������ {@link Java3D#parent} �� {@link Java3D#world} �̂Ƃ��� -�B
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
     * ���f���̍��W���擾�B
     * 
     * @return  ���f���̍��W�B
     *              {@link Java3D#parent} �� null �̂Ƃ��A���̃��f���̍��W�B
     *              {@link Java3D#parent} �� null �łȂ��Ƃ��A
     *                  ���̃��f���̍��W +  {@link Java3D#parent} �̍��W�A
     *                  ������ {@link Java3D#parent} �� {@link Java3D#world} �̂Ƃ��� -�B
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
     * ���f���̍��W���擾�B
     * 
     * @return  ���f���̍��W�B
     *              {@link Java3D#parent} �� null �̂Ƃ��A���̃��f���̍��W�B
     *              {@link Java3D#parent} �� null �łȂ��Ƃ��A
     *                  ���̃��f���̍��W +  {@link Java3D#parent} �̍��W�A
     *                  ������ {@link Java3D#parent} �� {@link Java3D#world} �̂Ƃ��� -�B
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
     * ���f���̍��W���擾�B
     * 
     * @return  ���f���̍��W�B
     *              {@link Java3D#parent} �� null �̂Ƃ��A���̃��f���̍��W�B
     *              {@link Java3D#parent} �� null �łȂ��Ƃ��A
     *                  ���̃��f���̍��W +  {@link Java3D#parent} �̍��W�A
     *                  ������ {@link Java3D#parent} �� {@link Java3D#world} �̂Ƃ��� -�B
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
     * ���f���̊p�x�E���W���擾�B
     * 
     * @return  ���f���̊p�x�E���W�B
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
     * ���f���̊p�x�E���W���擾�B
     * 
     * @return  ���f���̊p�x�E���W�B
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
     * ���f���̊p�x�E���W���擾�B
     * 
     * @return  ���f���̊p�x�E���W�B
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
     * ���f���̕`�惂�[�h���擾�B
     * 
     * @return  ���f���̕`�惂�[�h�B
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

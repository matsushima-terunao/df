/*
 * $Id: JavaRenderMemory.cpp,v 1.51 2008/03/12 16:30:47 matsushima Exp $
 */

/*J*
package javarender;

import java/awt/Component;
import java/awt/Graphics;
import java/awt/Image;
import java/awt/Rectangle;
import java/awt/image.DirectColorModel;
import java/awt/image.ImageObserver;
import java/awt/image.MemoryImageSource;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java/awt/Component"
#include "../cpp2javalib/java/awt/Graphics"
#include "../cpp2javalib/java/awt/Image"
#include "../cpp2javalib/java/awt/Rectangle"
#include "../cpp2javalib/java/awt/image/DirectColorModel"
#include "../cpp2javalib/java/awt/image/ImageObserver"
#include "../cpp2javalib/java/awt/image/MemoryImageSource"
#include "JavaRenderAbstract.cpp"

#else // cpp

#define _IS_H_
#include "JavaRenderMemory.cpp"
#include "Log.cpp"
#undef _IS_H_

#endif
/**/

/**
 * 配列を使用したレンダ。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: JavaRenderMemory.cpp,v 1.51 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: JavaRenderMemory.cpp,v $
 * Revision 1.51  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.50  2008/03/06 16:42:45  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.49  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.48  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.47  2008/03/03 02:10:50  matsushima
 * render ふりわけを JavaRenderBuffer -> JavaRenderXxx
 * テクスチャを int[] -> JavaRenderTexture
 *
 * Revision 1.46  2008/02/26 07:59:42  matsushima
 * no message
 *
 * Revision 1.45  2008/02/24 05:52:06  matsushima
 * JavaRenderInterface -> JavaRender
 * JavaRender -> JavaRenderBuffer
 *
 * Revision 1.44  2008/02/23 23:45:19  matsushima
 * 高速化
 *
 * Revision 1.43  2007/12/01 22:14:14  matsushima
 * 再登録
 *
 * Revision 1.39  2007/05/23 18:30:22  matsushima
 * JavaRender カプセル化
 *
 * Revision 1.30  2007/05/14 13:38:20  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.28  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.26  2007/05/08 08:33:25  matsushima
 * JavaRenderMemory から JavaRenderMemorySSE2 を分離
 *
 * Revision 1.25  2007/05/07 18:53:16  matsushima
 * gouraud_alpha アセンブラ
 *
 * Revision 1.22  2007/05/06 18:00:09  matsushima
 * render_mode
 *
 * Revision 1.20  2007/05/05 18:06:03  matsushima
 * clear アセンブラ
 *
 * Revision 1.18  2007/05/04 08:08:55  matsushima
 * drawLine アセンブラ
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
/*J*
public class JavaRenderMemory extends JavaRenderAbstract
{
/*C*/
#ifdef _IS_H_
class JavaRenderMemory : public JavaRenderAbstract
{
/**/
/*J*
    // Off screen buffer
    protected int[] pixOff;
    protected MemoryImageSource misOff;
    protected Image imageOff;
    protected int[][] b_tbl;

    private FillPolygon fill_solid;
    private FillPolygon fill_alpha;
    private FillPolygon fill_gouraud;
    private FillPolygon fill_gouraud_alpha;
    private FillPolygon fill_texture;
    private FillPolygon fill_texture_alpha;
    private FillPolygon fill_texture_gouraud;
    private FillPolygon fill_texture_gouraud_alpha;

    /**
     * 一時頂点バッファ。
     */
/*J*
    public static class VERT
    {
        public int x;
        public int y;
        public int c;
        public int tx;
        public int ty;
    };

    public static VERT[] verts;// = new VERT[100];
/*C*/
public:
    class FillPolygon;
protected:
    friend class FillPolygon;

    // Off screen buffer
protected:
    int* pixOff;
    MemoryImageSource* misOff;
    Image* imageOff;
    int (*b_tbl)[256];

protected:
    FillPolygon* fill_solid;
    FillPolygon* fill_alpha;
    FillPolygon* fill_gouraud;
    FillPolygon* fill_gouraud_alpha;
    FillPolygon* fill_texture;
    FillPolygon* fill_texture_alpha;
    FillPolygon* fill_texture_gouraud;
    FillPolygon* fill_texture_gouraud_alpha;

    /**
     * 一時頂点バッファ。
     */
/*C*/
public:
    class VERT
    {
    public:
        int x;
        int y;
        int c;
        int tx;
        int ty;
    };

    static VERT verts[100];
#else
    JavaRenderMemory::VERT JavaRenderMemory::verts[100];
#endif
/**/

/*J*
    public JavaRenderMemory(int width, int height, Component component) {
        super(width, height);
        boolean is_create_polygon_class = true;
        if (null == verts)
        {
            verts = new VERT[100];
            for (int i = 0; i < 100; ++ i)
            {
                verts[i] = new VERT();
            }
        }
/*C*/
#ifdef _IS_H_
public:
    JavaRenderMemory(int width, int height, Component* component, boolean is_create_polygon_class = true);
#else
    JavaRenderMemory::JavaRenderMemory(int width, int height, Component* component, boolean is_create_polygon_class /*= true*//*C*/)
        : JavaRenderAbstract(width, height) {
/**/
        if (width == 0)
        {
            height = 0xff;
        }
        this->width = width = (width + 3) - (width + 3) % 4;
        b_tbl = new int[JavaRender::BRIGHTNESS_MAX][256];
        int b, c;
        for (b = 0; b < JavaRender::BRIGHTNESS_MAX; ++ b)
        {
            for (c = 0; c < 256; ++ c)
            {
                int color = get_brightness_color(c, b);
                b_tbl[b][c] = color & 0x000000ff;
            }
        }

        // オフスクリーンバッファを作成する
        DirectColorModel cm /*J*= new DirectColorModel/**/(32, 0x00ff0000, 0x0000ff00, 0x000000ff);
        pixOff = new int[width * height];
        misOff = new MemoryImageSource(width, height, &cm, pixOff, 0, width);
        _R(misOff).setAnimated(true);
        imageOff = _R(component).createImage(misOff);

        // FillPolygonXxx クラスを作成する。
        fill_solid = null;
        if (is_create_polygon_class)
        {
            create_polygon_class();
        }
    }
/*C*/
#endif
/**/

/*C*/
#ifdef _IS_H_
public:
    virtual ~JavaRenderMemory();
#else
    JavaRenderMemory::~JavaRenderMemory() {
        delete imageOff;
        delete[] pixOff;
        delete misOff;
        delete[] b_tbl;
        if (null != fill_solid)
        {
            delete fill_solid;
            delete fill_alpha;
            delete fill_gouraud;
            delete fill_gouraud_alpha;
            delete fill_texture;
            delete fill_texture_alpha;
            delete fill_texture_gouraud;
            delete fill_texture_gouraud_alpha;
        }
    }
#endif
/**/

/*J*
    public void clear() {
/*C*/
#ifdef _IS_H_
public:
    virtual void clear();
#else
    void JavaRenderMemory::clear() {
/**/
        int/*C*/* /*J*[]/**/ p = pixOff;
/*J*
        int i = 0;
        for ( ; i < width * height - 7; i += 8)
        {
            p[i + 0] = 0xff000000;
            p[i + 1] = 0xff000000;
            p[i + 2] = 0xff000000;
            p[i + 3] = 0xff000000;
            p[i + 4] = 0xff000000;
            p[i + 5] = 0xff000000;
            p[i + 6] = 0xff000000;
            p[i + 7] = 0xff000000;
        }
        for ( ; i < width * height; ++ i)
        {
            p[i] = 0xff000000;
        }
/*C*/
        memset(p, 0, width * height * 4);
/**/
    }
/*C*/
#endif
/**/

/*J*
    public void repaint() {
/*C*/
#ifdef _IS_H_
public:
    virtual void repaint();
#else
    void JavaRenderMemory::repaint() {
/**/
        _R(misOff).newPixels(); // component.imageUpdate() -> component.repaint()
    }
/*C*/
#endif
/**/

/*J*
    public void paint(Graphics graphics, ImageObserver observer) {
/*C*/
#ifdef _IS_H_
public:
    virtual void paint(Graphics* _graphics, ImageObserver* observer);
#else
    void JavaRenderMemory::paint(Graphics* _graphics, ImageObserver* observer) {
        JPARAM(Graphics, graphics);
/**/
        graphics.drawImage(imageOff, 0, 0, observer);
    }
/*C*/
#endif
/**/

/*J*
    private int _y(int y) {
        return y;
/*C*/
#ifdef _IS_H_
private:
    int _y(int y);
#else
    int JavaRenderMemory::_y(int y) {
        return height - 1 - y;
/**/
    }
/*C*/
#endif
/**/

/*J*
    public int getPixel(int x, int y) {
/*C*/
#ifdef _IS_H_
public:
    virtual int getPixel(int x, int y);
#else
    int JavaRenderMemory::getPixel(int x, int y) {
/**/
        if ((x >= 0) && (x < width - 1) && (y >= 0) && (y < height - 1))
        {
            int p = x + _y(y) * width;
            return pixOff[p];
        }
        return 0;
    }
/*C*/
#endif
/**/

/*J*
    public void setPixel(int color, int x, int y) {
/*C*/
#ifdef _IS_H_
public:
    virtual void setPixel(int color, int x, int y);
#else
    void JavaRenderMemory::setPixel(int color, int x, int y) {
/**/
        if ((x >= 0) && (x < width - 1) && (y >= 0) && (y < height - 1))
        {
            int p = x + _y(y) * width;
            pixOff[p] = color;
        }
    }
/*C*/
#endif
/**/

/*J*
    public void drawLine(int color, int x1, int y1, int x2, int y2) {
/*C*/
#ifdef _IS_H_
public:
    virtual void drawLine(int color, int x1, int y1, int x2, int y2);
#else
    void JavaRenderMemory::drawLine(int color, int x1, int y1, int x2, int y2) {
/**/
        y1 = _y(y1);
        y2 = _y(y2);
        // 垂直
        if (x1 == x2)
        {
            // スクリーンの外なら終了
            if ((x1 >= width) || (x1 < 0))
            {
                return;
            }
            // 点なら終了
            if (y1 == y2)
            {
                return;
            }
            // 上 -> 下
            int y = y1;
            if (y1 > y2)
            {
                y = y2;
                y2 = y1;
            }
            // クリップ 上
            if (y < 0)
            {
                y = 0;
            }
            // クリップ 下
            if (y2 > height)
            {
                y2 = height;
            }
            // 描画
            for (int p = x1 + y * width; y < y2; ++ y, p += width)
            {
                pixOff[p] = color;
            }
        }
        // 水平
        else if (y1 == y2)
        {
            // スクリーンの外なら終了
            if ((y1 >= height) || (y1 < 0))
            {
                return;
            }
            // 左 -> 右
            int x = x1;
            if (x1 > x2)
            {
                x = x2;
                x2 = x1;
            }
            // クリップ 左
            if (x < 0)
            {
                x = 0;
            }
            // クリップ 右
            if (x2 > width)
            {
                x2 = width;
            }
            // 描画
            for (int p = x + y1 * width; x < x2; ++ x, ++ p)
            {
                pixOff[p] = color;
            }
        }
        // 垂直・水平以外
        else
        {
            // 範囲チェック x
            // x1 > x2 なら入れ替え
            if (x1 > x2)
            {
                int x = x1;
                x1 = x2;
                x2 = x;
                int y = y1;
                y1 = y2;
                y2 = y;
            }
            // スクリーンの外なら終了
            if (x2 < 0)
            {
                return;
            }
            if (x1 > width - 1)
            {
                return;
            }
            // クリップ 左
            if (x1 < 0)
            {
                y1 -= x1 * (y2 - y1) / (x2 - x1);
                x1 = 0;
            }
            // クリップ 右
            if (x2 > width - 1)
            {
                y2 -= (x2 - (width - 1)) * (y2 - y1) / (x2 - x1);
                x2 = width - 1;
            }
            // 範囲チェック y
            // y1 > y2 なら入れ替え
            if (y1 > y2)
            {
                int x = x1;
                x1 = x2;
                x2 = x;
                int y = y1;
                y1 = y2;
                y2 = y;
            }
            // スクリーンの外なら終了
            if (y2 < 0)
            {
                return;
            }
            if (y1 > height - 1)
            {
                return;
            }
            // クリップ 上
            if (y1 < 0)
            {
                x1 -= y1 * (x2 - x1) / (y2 - y1);
                y1 = 0;
            }
            // クリップ 下
            if (y2 > height - 1)
            {
                x2 -= (y2 - (height - 1)) * (x2 - x1) / (y2 - y1);
                y2 = height - 1;
            }
            // 描画
            int sx = (x1 < x2 ? 1 : -1);
            int dx = (x2 - x1) * sx;
            int sy = (y1 < y2 ? 1 : -1);
            int dy = (y2 - y1) * sy;
            int p = x1 + y1 * width;
            if (dx >= dy) // 45 度以下
            {
                int s = -dx;
                for (int x = 0; x <= dx; ++ x)
                {
                    pixOff[p] = color;
                    s += 2 * dy;
                    if (s >= 0)
                    {
                        s -= 2 * dx;
                        //y1 += sy;
                        p += sy * width;
                    }
                    //x1 += sx;
                    p += sx;
                }
            }
            else // 45 度より上
            {
                int s = -dy;
                for (int y = 0; y <= dy; ++ y)
                {
                    pixOff[p] = color;
                    s += 2 * dx;
                    if (s >= 0)
                    {
                        s -= 2 * dy;
                        //x1 += sx;
                        p += sx;
                    }
                    //y1 += sy;
                    p += sy * width;
                }
            }
        }
    }
/*C*/
#endif
/**/

/*J*
    public void drawPolygon(int[] px, int[] py, int[] pc, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void drawPolygon(int* px, int* py, int* pc, int cnt);
#else
    void JavaRenderMemory::drawPolygon(int* px, int* py, int* pc, int cnt) {
/**/
        if (cnt <= 1)
        {
            return;
        }
        drawPolyline(px, py, pc, cnt);
        if (cnt >= 3)
        {
            drawLine(pc[cnt - 1], px[cnt - 1], py[cnt - 1], px[0], py[0]);
        }
    }
/*C*/
#endif
/**/

/*J*
    public void drawPolyline(int[] px, int[] py, int[] pc, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void drawPolyline(int* px, int* py, int* pc, int cnt);
#else
    void JavaRenderMemory::drawPolyline(int* px, int* py, int* pc, int cnt) {
/**/
        if (cnt <= 1)
        {
            return;
        }
        for (int i = 0; i < cnt - 1; ++ i)
        {
            drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
        }
    }
/*C*/
#endif
/**/

/*J*
    public void fillPolygon(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void fillPolygon(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderMemory::fillPolygon(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
/**/
        render(RENDER_POLYGON,
            px, py, pc, texture, ptx, pty, null, cnt);
    }
/*C*/
#endif
/**/

/*J*
    public void fillPolygonAlpha(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void fillPolygonAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderMemory::fillPolygonAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
/**/
        render(RENDER_POLYGON | SHADING_ALPHA,
            px, py, pc, texture, ptx, pty, null, cnt);
    }
/*C*/
#endif
/**/

/*J*
    public void fillPolygonGouraud(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void fillPolygonGouraud(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderMemory::fillPolygonGouraud(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
/**/
        render(RENDER_POLYGON | SHADING_GOURAUD,
            px, py, pc, texture, ptx, pty, null, cnt);
    }
/*C*/
#endif
/**/

/*J*
    public void fillPolygonGouraudAlpha(int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void fillPolygonGouraudAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt);
#else
    void JavaRenderMemory::fillPolygonGouraudAlpha(int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, int cnt) {
/**/
        render(RENDER_POLYGON | SHADING_GOURAUD | SHADING_ALPHA,
            px, py, pc, texture, ptx, pty, null, cnt);
    }
/*C*/
#endif
/**/

/*J*
    public void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture render_font) {
/*C*/
#ifdef _IS_H_
public:
    virtual void drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture* render_font);
#else
    void JavaRenderMemory::drawString(int color, int x, int y, String string, boolean proportional, JavaRenderTexture* render_font) {
/**/
        int unit16 = 65536 / 4;
        draw_string(color, x, y, unit16, string, proportional, render_font, false);
    }
/*C*/
#endif
/**/

/*J*
    public void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture render_font) {
/*C*/
#ifdef _IS_H_
public:
    virtual void drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font);
#else
    void JavaRenderMemory::drawString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font) {
/**/
        draw_string(color, x, y, unit16, string, proportional, render_font, false);
    }
/*C*/
#endif
/**/

/*J*
    public Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture render_font) {
/*C*/
#ifdef _IS_H_
public:
    virtual Rectangle calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font);
#else
    Rectangle JavaRenderMemory::calcString(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font) {
/**/
        return draw_string(color, x, y, unit16, string, proportional, render_font, true);
    }
/*C*/
#endif
/**/

/*J*
    private Rectangle draw_string(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture render_font, boolean calc) {
/*C*/
#ifdef _IS_H_
private:
    Rectangle draw_string(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font, boolean calc);
#else
    Rectangle JavaRenderMemory::draw_string(int color, int x, int y, int unit16, String string, boolean proportional, JavaRenderTexture* render_font, boolean calc) {
/**/
        int color_r = (color >> 16) & 0xff;
        int color_g = (color >>  8) & 0xff;
        int color_b = (color      ) & 0xff;
        int x0 = x, y0 = y;
        int w_max = (render_font->font_w_max * unit16) >> 16;
        int h_max = 0;
        int i;
        int string_len = string.length();
        for (i = 0; i < string_len; ++ i)
        {
            int c = string.charAt(i);
            if ('\n' == c)
            {
                x = x0;
                y += h_max + 2;
                h_max = 0;
                continue;
            }
            c -= ' ';
            int w = ((render_font->font_ws[c] * unit16) >> 16) + 1;
            int h = ((render_font->font_hs[c] * unit16) >> 16) + 1;
            if (h_max < h)
            {
                h_max = h;
            }
            if (x >= width)
            {
                continue;
            }
            if (y >= height)
            {
                break;
            }
            if (false == calc)
            {
                if (x + w > width)
                {
                    w = width - x;
                }
                if (y + h > height)
                {
                    h = height - y;
                }
                int px0 = (c % 16) * render_font->font_w;
                int py0 = (c / 16) * render_font->font_h;
                int p = (int)(px0 + py0 * render_font->width) << 8;
                int px, py;
                int px_inc = (((1                    ) << 16) / unit16) << 8;
                int py_inc = (((render_font->width - w) << 16) / unit16) << 8;
                for (py = y; py < y + h; ++ py, p += py_inc)
                {
                for (px = x; px < x + w; ++ px, p += px_inc)
                    {
                        if (0 != render_font->pix[p >> 8])
                        {
                            int pc = render_font->pix[p >> 8];
                            if (pc >= 192)
                            {
                                setPixel(color, px, py);
                            }
                            else
                            {
                                // Alpha blending
                                int color2 = getPixel(px, py);
                                int r = (color_r * pc) + ((color2 >> 16) & 0xff) * (255 - pc);
                                int g = (color_g * pc) + ((color2 >>  8) & 0xff) * (255 - pc);
                                int b = (color_b * pc) + ((color2      ) & 0xff) * (255 - pc);
                                r = (r >= 256 * 256) ? 255 : r / 256;
                                g = (g >= 256 * 256) ? 255 : g / 256;
                                b = (b >= 256 * 256) ? 255 : b / 256;
                                setPixel((r << 16) | (g << 8) | b, px, py);
                            }
                        }
                    }
                }
            }
            x += (false != proportional) ? w + 1 : w_max - 1;
            if (string_len - 1 == i)
            {
                y += h_max + 2;
            }
        }
        return /*J*new /**/Rectangle(x0, y0, x - x0, y - y0);
    }
/*C*/
#endif
/**/

/*J*
    public void render(int render_mode, int[] px, int[] py, int[] pc, JavaRenderTexture texture, int[] ptx, int[] pty, String string, int cnt) {
/*C*/
#ifdef _IS_H_
public:
    virtual void render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt);
#else
    void JavaRenderMemory::render(int render_mode, int* px, int* py, int* pc, JavaRenderTexture* texture, int* ptx, int* pty, const char* string, int cnt) {
/**/
        int idx = 0;
        int i = idx;
        if (2 == cnt)
        {
            drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
        }
        else
        {
            switch (render_mode & RENDER_MASK)
            {
            case RENDER_POLYLINE:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
                    }
                    break;
                }
            case RENDER_POLYFRAME:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(pc[i], px[i], py[i], px[i + 1], py[i + 1]);
                    }
                    drawLine(pc[i], px[i], py[i], px[idx], py[idx]);
                    break;
                }
            case RENDER_POLYGON:
                {
                    // 頂点を二重化、外接四角形
                    int x_min = px[i], x_max = x_min;
                    int y_min = py[i], y_max = y_min, y_min_p = 0;
                    // brightness, alpha
                    boolean f_brightness = (null != texture) ? true : false; // 明るさ [BRIGHTNESS_BORDER2, BRIGHTNESS_BORDER1]
                    int f_alpha = 0xff000000; // アルファ成分が全て最大
                    for (i = 0; i < cnt; ++ i)
                    {
                        // 頂点を二重化
                        verts[i].x = verts[i + cnt].x = px[idx + i];
                        verts[i].y = verts[i + cnt].y = py[idx + i];
                        if (null == texture)
                        {
                            verts[i].c = verts[i + cnt].c = pc[idx + i];    // solid:   |  a|  r|  g|  b|
                        }
                        else
                        {
                            verts[i].c = verts[i + cnt].c = pc[idx + i];    // texture: |  a| brightness|
                            verts[i].tx = verts[i + cnt].tx = ptx[idx + i];
                            verts[i].ty = verts[i + cnt].ty = pty[idx + i];
                        }
                        // 外接四角形
                        if (x_min > verts[i].x) { x_min = verts[i].x; }
                        if (x_max < verts[i].x) { x_max = verts[i].x; }
                        if (y_min > verts[i].y) { y_min = verts[i].y; y_min_p = i; }
                        if (y_max < verts[i].y) { y_max = verts[i].y; }
                        // brightness, alpha
                        f_brightness = f_brightness &&
                              (((verts[i].c & 0x00ffffff) <= BRIGHTNESS_BORDER1)
                            && ((verts[i].c & 0x00ffffff) >= BRIGHTNESS_BORDER2));
                        f_alpha &= verts[i].c;
                    }
                    int render_shading = render_mode & SHADING_MASK & ~SHADING_TEXTURE;
                    if (false != f_brightness) // 明るさ [BRIGHTNESS_BORDER2, BRIGHTNESS_BORDER1]
                    {
                        render_shading &= ~SHADING_GOURAUD;
                    }
                    if (0xff000000 == f_alpha) // アルファ成分が全て最大
                    {
                        render_shading &= ~SHADING_ALPHA;
                    }
                    FillPolygon/*C*/* /**/ fill = null;
                    switch (render_shading)
                    {
                    case 0:
                        fill = (null != texture) ? fill_texture : fill_solid;
                        break;
                    case SHADING_ALPHA:
                        fill = (null != texture) ? fill_texture_alpha : fill_alpha;
                        break;
                    case SHADING_GOURAUD:
                        fill = (null != texture) ? fill_texture_gouraud : fill_gouraud;
                        break;
                    case SHADING_GOURAUD | SHADING_ALPHA:
                        fill = (null != texture) ? fill_texture_gouraud_alpha : fill_gouraud_alpha;
                        break;
                    }
                    if (null != fill)
                    {
                        _R(fill).fillPolygon(cnt, x_min, x_max, y_min, y_max, y_min_p, texture);
                    }
                    break;
                }
            case RENDER_STRING:
                {
                    drawString(pc[i], px[i], py[i], string, true, texture);
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }
/*C*/
#endif
/**/

/*J*
    public void render(Polygon poly, Vertex[] vert) {
/*C*/
#ifdef _IS_H_
public:
    virtual void render(Polygon* _poly, Vertex** vert);
#else
    void JavaRenderMemory::render(Polygon* _poly, Vertex** vert) {
        Polygon& poly = *_poly;
/**/
        int render_mode = poly.render_mode;
        JavaRenderTexture/*C*/* /**/ texture = poly.texture;
        int idx = poly.vert_idx;
        int cnt = poly.vert_cnt;
        int i = idx;
        if (2 == cnt)
        {
            drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
        }
        else
        {
            switch (render_mode & RENDER_MASK)
            {
            case RENDER_POLYLINE:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
                    }
                    break;
                }
            case RENDER_POLYFRAME:
                {
                    for (i = idx; i < idx + cnt - 1; ++ i)
                    {
                        drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[i + 1]).x2, _R(vert[i + 1]).y2);
                    }
                    drawLine(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, _R(vert[idx]).x2, _R(vert[idx]).y2);
                    break;
                }
            case RENDER_POLYGON:
                {
                    // 頂点を二重化、外接四角形
                    int x_min = _R(vert[i]).x2, x_max = x_min;
                    int y_min = _R(vert[i]).y2, y_max = y_min, y_min_p = 0;
                    // brightness, alpha
                    boolean f_brightness = (null != texture) ? true : false; // 明るさ [BRIGHTNESS_BORDER2, BRIGHTNESS_BORDER1]
                    int f_alpha = 0xff000000; // アルファ成分が全て最大
                    for (i = 0; i < cnt; ++ i)
                    {
                        // 頂点を二重化
                        verts[i].x = verts[i + cnt].x = _R(vert[idx + i]).x2;
                        verts[i].y = verts[i + cnt].y = _R(vert[idx + i]).y2;
                        if (null == texture)
                        {
                            verts[i].c = verts[i + cnt].c = _R(vert[idx + i]).color;    // solid:   |  a|  r|  g|  b|
                        }
                        else
                        {
                            verts[i].c = verts[i + cnt].c
                                = (_R(vert[idx + i]).color & 0xff000000)
                                | (_R(vert[idx + i]).brightness & 0x00ffffff);          // texture: |  a| brightness|
                            verts[i].tx = verts[i + cnt].tx = _R(vert[idx + i]).tx;
                            verts[i].ty = verts[i + cnt].ty = _R(vert[idx + i]).ty;
                        }
                        // 外接四角形
                        if (x_min > verts[i].x) { x_min = verts[i].x; }
                        if (x_max < verts[i].x) { x_max = verts[i].x; }
                        if (y_min > verts[i].y) { y_min = verts[i].y; y_min_p = i; }
                        if (y_max < verts[i].y) { y_max = verts[i].y; }
                        // brightness, alpha
                        f_brightness = f_brightness &&
                              (((verts[i].c & 0x00ffffff) <= BRIGHTNESS_BORDER1)
                            && ((verts[i].c & 0x00ffffff) >= BRIGHTNESS_BORDER2));
                        f_alpha &= verts[i].c;
                    }
                    int render_shading = render_mode & SHADING_MASK & ~SHADING_TEXTURE;
                    if (false != f_brightness) // 明るさ [BRIGHTNESS_BORDER2, BRIGHTNESS_BORDER1]
                    {
                        render_shading &= ~SHADING_GOURAUD;
                    }
                    if (0xff000000 == f_alpha) // アルファ成分が全て最大
                    {
                        render_shading &= ~SHADING_ALPHA;
                    }
                    FillPolygon/*C*/* /**/ fill = null;
                    switch (render_shading)
                    {
                    case 0:
                        fill = (null != texture) ? fill_texture : fill_solid;
                        break;
                    case SHADING_ALPHA:
                        fill = (null != texture) ? fill_texture_alpha : fill_alpha;
                        break;
                    case SHADING_GOURAUD:
                        fill = (null != texture) ? fill_texture_gouraud : fill_gouraud;
                        break;
                    case SHADING_GOURAUD | SHADING_ALPHA:
                        fill = (null != texture) ? fill_texture_gouraud_alpha : fill_gouraud_alpha;
                        break;
                    }
                    if (null != fill)
                    {
                        _R(fill).fillPolygon(cnt, x_min, x_max, y_min, y_max, y_min_p, texture);
                    }
                    break;
                }
            case RENDER_STRING:
                {
                    drawString(_R(vert[i]).color, _R(vert[i]).x2, _R(vert[i]).y2, poly.string, true, poly.texture);
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }
/*C*/
#endif
/**/

    /**
     * ポリゴン塗りつぶしの基本クラス。
     */
/*J*
    private abstract class FillPolygon
    {
        // Java: パラメータ渡しは遅いのでメンバ変数でアクセス
        int color;
        int[] texture; // T
        int tw, th; // T
        int x1, x2, dx1, dx2;
        int r1, r2, dr1, dr2; // G
        int g1, g2, dg1, dg2; // G
        int b1, b2, db1, db2; // blue or brightness // G
        int bn1, bn2, dbn1, dbn2; // brightness // G
        int a1, a2, da1, da2; // A
        int an1, an2, dan1, dan2; // A
        int tx1, tx2, dtx1, dtx2; // T
        int ty1, ty2, dty1, dty2; // T
        int y, px1, px2, pdx, p1, p2;

        protected void new_point_left(int i1, int dy) {}
        protected void new_point_right(int i2, int dy) {}
        protected abstract void draw_scan_line();
/*C*/
#ifdef _IS_H_
public:
    class FillPolygon
    {
    protected:
        // Java: パラメータ渡しは遅いのでメンバ変数でアクセス
        int color;
        int* texture; // T
        int tw, th; // T
        int x1, x2, dx1, dx2;
        int r1, r2, dr1, dr2; // G
        int g1, g2, dg1, dg2; // G
        int b1, b2, db1, db2; // blue or brightness // G
        int bn1, bn2, dbn1, dbn2; // brightness // G
        int a1, a2, da1, da2; // A
        int an1, an2, dan1, dan2; // A
        int tx1, tx2, dtx1, dtx2; // T
        int ty1, ty2, dty1, dty2; // T
        int y, px1, px2, pdx, p1, p2;

    protected:
        virtual void new_point_left(int i1, int dy) {}
        virtual void new_point_right(int i2, int dy) {}
        virtual void draw_scan_line() = 0;

    public:
        int &width, &height, *&pixOff, (*&b_tbl)[256];

    protected:
        int _y(int y) { return height - 1 - y; }
#endif
/**/

/*J*
        public FillPolygon() {
/*C*/
#ifdef _IS_H_
    public:
        FillPolygon(JavaRenderMemory* render);
#else
        JavaRenderMemory::FillPolygon::FillPolygon(JavaRenderMemory* render)
            : width(render->width), height(render->height), pixOff(render->pixOff), b_tbl(render->b_tbl) {
/**/
        }
/*C*/
#endif
/**/

/*J*
        public void fillPolygon(int cnt, int x_min, int x_max, int y_min, int y_max, int y_min_p, JavaRenderTexture texture) {
/*C*/
#ifdef _IS_H_
    public:
        virtual void fillPolygon(int cnt, int x_min, int x_max, int y_min, int y_max, int y_min_p, JavaRenderTexture* texture);
#else
        void JavaRenderMemory::FillPolygon::fillPolygon(int cnt, int x_min, int x_max, int y_min, int y_max, int y_min_p, JavaRenderTexture* texture) {
/**/
            this->color = color;
            if (null != texture)
            {
                this->texture = _R(texture).pix;
                this->tw = _R(texture).width;
                this->th = _R(texture).height;
            }

            // 位置と大きさ
            if ((x_max < 0) || (x_min >= width) || (y_max < 0) || (y_min >= height)) // スクリーンの外
            {
                return;
            }
            else
            if ((x_max == x_min) || (y_max == y_min)) // 空
            {
                return;
            }

            // スクリーンの上と下の頂点をスキップ
            int i1 = y_min_p;
            int i2 = y_min_p + cnt;
            while (verts[i1 + 1].y < 0)
            {
                ++ i1;
            }
            while (verts[i2 - 1].y < 0)
            {
                -- i2;
            }
            y_min = (verts[i1].y < verts[i2].y) ? verts[i1].y : verts[i2].y;
            y_max = (y_max < height) ? y_max : height;

            // スキャンラインを描画
            for (y = y_min; y < y_max; ++ y)
            {
                if (y >= verts[i1].y) // 左: 新しい頂点に到達
                {
                    do
                    {
                        ++ i1;
                    } while (y >= verts[i1].y); // y 方向に変化しないならスキップ
                    int dy = verts[i1].y - verts[i1 - 1].y;
                    x1 = verts[i1 - 1].x << 16;
                    dx1 = ((verts[i1].x - verts[i1 - 1].x) << 16) / dy;
                    new_point_left(i1, dy);
                }
                if (y >= verts[i2].y) // 右: 新しい頂点に到達
                {
                    do
                    {
                        -- i2;
                    } while (y >= verts[i2].y); // y 方向に変化しないならスキップ
                    int dy = verts[i2].y - verts[i2 + 1].y;
                    x2 = verts[i2 + 1].x << 16;
                    dx2 = ((verts[i2].x - verts[i2 + 1].x) << 16) / dy;
                    new_point_right(i2, dy);
                }
                if (y >= 0)
                {
                    px1 = x1 >> 16;
                    px2 = x2 >> 16;
                    pdx = px2 - px1;
                    if (pdx > 0)
                    {
                        p1 = (px1 > 0) ? px1 : 0;
                        p2 = (px2 < width) ? px2 : width;
                        if (p1 < p2)
                        {
                            int off = _y(y) * width;
                            p1 += off;
                            p2 += off;
                            // スキャンラインを描画
                            draw_scan_line();
                        }
                    }
                }
                x1 += dx1;
                x2 += dx2;
                r1 += dr1; // G
                r2 += dr2; // G
                g1 += dg1; // G
                g2 += dg2; // G
                b1 += db1; // G
                b2 += db2; // G
                a1 += da1; // A
                a2 += da2; // A
                an1 += dan1; // A
                an2 += dan2; // A
                if (null != texture)
                {
                    tx1 += dtx1; // T
                    tx2 += dtx2; // T
                    ty1 += dty1; // T
                    ty2 += dty2; // T
                    bn1 += dbn1; // G
                    bn2 += dbn2; // G
                }
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * 単色ポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonSolid extends FillPolygon
    {
/*C*/
private:
    class FillPolygonSolid : public FillPolygon
    {
    public:
        FillPolygonSolid(JavaRenderMemory* render) : FillPolygon(render) {}
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonSolid::draw_scan_line() {
/**/
            for (int p = p1; p < p2; ++ p)
            {
                pixOff[p] = color; // S
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * アルファブレンドポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonAlpha extends FillPolygon
    {
/*C*/
private:
    class FillPolygonAlpha : public FillPolygon
    {
    public:
        FillPolygonAlpha(JavaRenderMemory* render) : FillPolygon(render) {}
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#endif
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonAlpha::new_point_left(int i1, int dy) {
/**/
            a1 = (color >> 24) & 0xff;
            r1 = ((color & 0x00ff0000) * a1) & 0xff000000;
            g1 = ((color & 0x0000ff00) * a1) & 0x00ff0000;
            b1 = ((color & 0x000000ff) * a1) & 0x0000ff00;
            an1 = 255 - a1; // A
            a1 = 0xff000000 | ((r1 | g1 | b1) >> 8); // A
            da1 = dan1 = 0; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonAlpha::draw_scan_line() {
/**/
            for (int p = p1; p < p2; ++ p)
            {
                int r = ((pixOff[p] & 0x00ff0000) * an1) & 0xff000000; // A
                int g = ((pixOff[p] & 0x0000ff00) * an1) & 0x00ff0000; // A
                int b = ((pixOff[p] & 0x000000ff) * an1) & 0x0000ff00; // A
                pixOff[p] = a1 | ((r | g | b) >> 8); // A
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * グラデーションポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonGouraud extends FillPolygon
    {
/*C*/
private:
    class FillPolygonGouraud : public FillPolygon
    {
    public:
        FillPolygonGouraud(JavaRenderMemory* render) : FillPolygon(render) {}
#endif
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonGouraud::new_point_left(int i1, int dy) {
/**/
            a1 = (verts[i1 - 1].c >>  8) & 0x00ff0000; // A
            r1 = (verts[i1 - 1].c      ) & 0x00ff0000; // G
            g1 = (verts[i1 - 1].c <<  8) & 0x00ff0000; // G
            b1 = (verts[i1 - 1].c << 16) & 0x00ff0000; // G
            dr1 = (((verts[i1].c      ) & 0x00ff0000) - r1) / dy; // G
            dg1 = (((verts[i1].c <<  8) & 0x00ff0000) - g1) / dy; // G
            db1 = (((verts[i1].c << 16) & 0x00ff0000) - b1) / dy; // G
        }
/*C*/
#endif
/**/

/*J*
        protected void new_point_right(int i2, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_right(int i2, int dy);
#else
        void JavaRenderMemory::FillPolygonGouraud::new_point_right(int i2, int dy) {
/**/
            a2 = (verts[i2 + 1].c >>  8) & 0x00ff0000; // A
            r2 = (verts[i2 + 1].c      ) & 0x00ff0000; // G
            g2 = (verts[i2 + 1].c <<  8) & 0x00ff0000; // G
            b2 = (verts[i2 + 1].c << 16) & 0x00ff0000; // G
            dr2 = (((verts[i2].c      ) & 0x00ff0000) - r2) / dy; // G
            dg2 = (((verts[i2].c <<  8) & 0x00ff0000) - g2) / dy; // G
            db2 = (((verts[i2].c << 16) & 0x00ff0000) - b2) / dy; // G
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonGouraud::draw_scan_line() {
/**/
            int r = r1; // G
            int g = g1; // G
            int b = b1; // G
            int dr = (r2 - r1) / pdx; // G
            int dg = (g2 - g1) / pdx; // G
            int db = (b2 - b1) / pdx; // G
            if (px1 < 0)
            {
                // 左にはみ出した分をスキップ
                r -= dr * px1; // G
                g -= dg * px1; // G
                b -= db * px1; // G
            }
            for (int p = p1; p < p2; ++ p)
            {
                pixOff[p] // G
                    = 0xff000000 // G
                    | ( r        & 0x00ff0000) // G
                    | ((g >>  8) & 0x0000ff00) // G
                    | ((b >> 16) & 0x000000ff); // G
                r += dr; // G
                g += dg; // G
                b += db; // G
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * グラデーション + アルファブレンドポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonGouraudAlpha extends FillPolygon
    {
/*C*/
private:
    class FillPolygonGouraudAlpha : public FillPolygon
    {
    public:
        FillPolygonGouraudAlpha(JavaRenderMemory* render) : FillPolygon(render) {}
#endif
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonGouraudAlpha::new_point_left(int i1, int dy) {
/**/
            int a11 = (verts[i1 - 1].c >> 24) & 0x000000ff; // A
            int r11 = (verts[i1 - 1].c >> 16) & 0x000000ff; // G
            int g11 = (verts[i1 - 1].c >>  8) & 0x000000ff; // G
            int b11 = (verts[i1 - 1].c      ) & 0x000000ff; // G
            int a12 = (verts[i1    ].c >> 24) & 0x000000ff; // A
            int r12 = (verts[i1    ].c >> 16) & 0x000000ff; // G
            int g12 = (verts[i1    ].c >>  8) & 0x000000ff; // G
            int b12 = (verts[i1    ].c      ) & 0x000000ff; // G
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            r1 = r11 * a11;
            g1 = g11 * a11;
            b1 = b11 * a11;
            dr1 = ((r12 * a12) - r1) / dy; // ffffff
            dg1 = ((g12 * a12) - g1) / dy; // ffffff
            db1 = ((b12 * a12) - b1) / dy; // ffffff
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            an1 = 0x00ffffff - a11; // 255 - a11 // A
            dan1 = ((-a12) - (-a11)) / dy; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void new_point_right(int i2, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_right(int i2, int dy);
#else
        void JavaRenderMemory::FillPolygonGouraudAlpha::new_point_right(int i2, int dy) {
/**/
            int a11 = (verts[i2 + 1].c >> 24) & 0x000000ff; // A
            int r11 = (verts[i2 + 1].c >> 16) & 0x000000ff; // G
            int g11 = (verts[i2 + 1].c >>  8) & 0x000000ff; // G
            int b11 = (verts[i2 + 1].c      ) & 0x000000ff; // G
            int a12 = (verts[i2    ].c >> 24) & 0x000000ff; // A
            int r12 = (verts[i2    ].c >> 16) & 0x000000ff; // G
            int g12 = (verts[i2    ].c >>  8) & 0x000000ff; // G
            int b12 = (verts[i2    ].c      ) & 0x000000ff; // G
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            r2 = r11 * a11;
            g2 = g11 * a11;
            b2 = b11 * a11;
            dr2 = ((r12 * a12) - r1) / dy; // ffffff
            dg2 = ((g12 * a12) - g1) / dy; // ffffff
            db2 = ((b12 * a12) - b1) / dy; // ffffff
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            an2 = 0x00ffffff - a11; // 255 - a11 // A
            dan2 = ((-a12) - (-a11)) / dy; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonGouraudAlpha::draw_scan_line() {
/**/
            int r = r1; // G
            int g = g1; // G
            int b = b1; // G
            int an = an1; // A
            int dr = (r2 - r1) / pdx; // G
            int dg = (g2 - g1) / pdx; // G
            int db = (b2 - b1) / pdx; // G
            int dan = (an2 - an1) / pdx; // A
            if (px1 < 0)
            {
                // 左にはみ出した分をスキップ
                r -= dr * px1; // G
                g -= dg * px1; // G
                b -= db * px1; // G
                an -= dan * px1; // A
            }
            for (int p = p1; p < p2; ++ p)
            {
                int _an = an >> 8; // 0000ffff <- 00ffffff // A
                int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // GA
                int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // GA
                int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // GA
                pixOff[p] // GA
                    = 0xff000000 // GA
                    | ((_r      ) & 0x00ff0000) // GA
                    | ((_g >>  8) & 0x0000ff00) // GA
                    | ((_b >> 16) & 0x000000ff); // GA
                r += dr; // G
                g += dg; // G
                b += db; // G
                an += dan; // A
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * テクスチャポリゴン塗りつぶしの基本クラス。
     */
/*J*
    protected abstract class FillPolygonTextureCommon extends FillPolygon
    {
/*C*/
protected:
    class FillPolygonTextureCommon : public FillPolygon
    {
    public:
        FillPolygonTextureCommon(JavaRenderMemory* render) : FillPolygon(render) {}
/**/

/*J*
        // パラメータ渡しは遅いのでメンバ変数でアクセス
        protected int tx; //= tx1; // T
        protected int ty; //= ty1; // T
        protected int dtx; //= (tx2 - tx1) / pdx; // T
        protected int dty; //= (ty2 - ty1) / pdx; // T
        protected int tw16; //= tw << 16;
        protected int th16; //= th << 16;
        protected int a; //= a1; // A
        protected int da; //= (a2 - a1) / pdx; // A
        protected int an; //= an1; // A
        protected int dan; //= (an2 - an1) / pdx; // A
        protected int b; //= b1; // G
        protected int db; //= (b2 - b1) / pdx; // G
        protected int bn; //= bn1; // G
        protected int dbn; //= (bn2 - bn1) / pdx; // G
        protected boolean f;
/*C*/
    protected:
        // パラメータ渡しは遅いのでメンバ変数でアクセス
        int tx; //= tx1; // T
        int ty; //= ty1; // T
        int dtx; //= (tx2 - tx1) / pdx; // T
        int dty; //= (ty2 - ty1) / pdx; // T
        int tw16; //= tw << 16;
        int th16; //= th << 16;
        int a; //= a1; // A
        int da; //= (a2 - a1) / pdx; // A
        int an; //= an1; // A
        int dan; //= (an2 - an1) / pdx; // A
        int b; //= b1; // G
        int db; //= (b2 - b1) / pdx; // G
        int bn; //= bn1; // G
        int dbn; //= (bn2 - bn1) / pdx; // G
        boolean f;
#endif
/**/

/*J*
        public void draw_scan_line_texture_common(boolean is_g, boolean is_a) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line_texture_common(boolean is_g, boolean is_a);
#else
        void JavaRenderMemory::FillPolygonTextureCommon::draw_scan_line_texture_common(boolean is_g, boolean is_a) {
/**/
            tx = tx1; // T
            ty = ty1; // T
            int tx2t = tx2; // T
            int ty2t = ty2; // T
            dtx = (tx2 - tx1) / pdx; // T
            dty = (ty2 - ty1) / pdx; // T
            if (is_a) // A
            {
                a = a1; // A
                da = (a2 - a1) / pdx; // A
                an = an1; // A
                dan = (an2 - an1) / pdx; // A
            }
            if (is_g) // G
            {
                b = b1; // G
                bn = bn1; // G
                db = (b2 - b1) / pdx; // G
                dbn = (bn2 - bn1) / pdx; // G
            }
            if (px1 < 0)
            {
                // 左にはみ出した分をスキップ
                tx += dtx * -px1; // T
                ty += dty * -px1; // T
                if (is_a) // A
                {
                    a -= da * px1; // A
                    an -= dan * px1; // A
                }
                if (is_g) // G
                {
                    b -= db * px1; // G
                    bn -= dbn * px1; // G
                }
            }
            tw16 = tw << 16;
            th16 = th << 16;
            // tx, ty の正規化
            // tx = [0, tw16)
            // ty = [0, th16)
            if ((tx < -tw16) || (tx >= tw16))
            {
                tx2t -= tx;
                tx %= tw16;
                tx2t += tx;
            }
            if (tx < 0)
            {
                tx += tw16;
                tx2t += tw16;
            }
            if ((ty < -th16) || (ty >= th16))
            {
                ty2t -= ty;
                ty %= th16;
                ty2t += ty;
            }
            if (ty < 0)
            {
                ty += th16;
                ty2t += th16;
            }
            // 境界線をまたぐか
            f = ((tx2t < 0) || (tx2t >= tw16)
              || (ty2t < 0) || (ty2t >= th16));
            if (f)
            {
                // dtx, dty の正規化
                // dtx = [0, tw16)
                // dty = [0, th16)
                boolean fx = false;
                boolean fy = false;
                if ((dtx < -tw16) || (dtx >= tw16))
                {
                    dtx %= tw16;
                    fx = true;
                }
                if (dtx < 0)
                {
                    dtx += tw16;
                    fx = true;
                }
                if ((dty < -th16) || (dty >= th16))
                {
                    dty %= th16;
                    fy = true;
                }
                if (dty < 0)
                {
                    dty += th16;
                    fy = true;
                }
                if (fx)
                {
                    tx2t = tx + dtx * pdx;
                }
                if (fy)
                {
                    ty2t = ty + dty * pdx;
                }
                // 境界線をまたぐか
                f = ((tx2t < 0) || (tx2t >= tw16)
                  || (ty2t < 0) || (ty2t >= th16));
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * テクスチャポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonTexture extends FillPolygonTextureCommon
    {
/*C*/
private:
    class FillPolygonTexture : public FillPolygonTextureCommon
    {
    public:
        FillPolygonTexture(JavaRenderMemory* render) : FillPolygonTextureCommon(render) {}
#endif
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonTexture::new_point_left(int i1, int dy) {
/**/
            tx1 = verts[i1 - 1].tx << 16; // T
            ty1 = verts[i1 - 1].ty << 16; // T
            dtx1 = ((verts[i1].tx - verts[i1 - 1].tx) << 16) / dy; // T
            dty1 = ((verts[i1].ty - verts[i1 - 1].ty) << 16) / dy; // T
        }
/*C*/
#endif
/**/

/*J*
        protected void new_point_right(int i2, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_right(int i2, int dy);
#else
        void JavaRenderMemory::FillPolygonTexture::new_point_right(int i2, int dy) {
/**/
            tx2 = verts[i2 + 1].tx << 16; // T
            ty2 = verts[i2 + 1].ty << 16; // T
            dtx2 = ((verts[i2].tx - verts[i2 + 1].tx) << 16) / dy; // T
            dty2 = ((verts[i2].ty - verts[i2 + 1].ty) << 16) / dy; // T
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonTexture::draw_scan_line() {
/**/
            draw_scan_line_texture_common(false, false);
            // ループ
            if (false == f) // 境界線をまたぐか
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    pixOff[p] = texture[x + y * tw]; // T
                    tx += dtx; // T
                    ty += dty; // T
                }
            }
            else
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    pixOff[p] = texture[x + y * tw]; // T
                    tx += dtx; // T
                    ty += dty; // T
                    if (tx >= tw16) // T
                    {
                        tx -= tw16; // T
                    }
                    if (ty >= th16) // T
                    {
                        ty -= th16; // T
                    }
                }
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * テクスチャ + アルファブレンドポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonTextureAlpha extends FillPolygonTextureCommon
    {
/*C*/
private:
    class FillPolygonTextureAlpha : public FillPolygonTextureCommon
    {
    public:
        FillPolygonTextureAlpha(JavaRenderMemory* render) : FillPolygonTextureCommon(render) {}
#endif
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonTextureAlpha::new_point_left(int i1, int dy) {
/**/
            tx1 = verts[i1 - 1].tx << 16; // T
            ty1 = verts[i1 - 1].ty << 16; // T
            dtx1 = ((verts[i1].tx - verts[i1 - 1].tx) << 16) / dy; // T
            dty1 = ((verts[i1].ty - verts[i1 - 1].ty) << 16) / dy; // T
            int a11 = (verts[i1 - 1].c >> 24) & 0x000000ff; // A
            int a12 = (verts[i1    ].c >> 24) & 0x000000ff; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a1 = a11; // A
            da1 = (a12 - a11) / dy; // A
            an1 = 0x00ffffff - a11; // 255 - a11 // A
            dan1 = ((-a12) - (-a11)) / dy; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void new_point_right(int i2, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_right(int i2, int dy);
#else
        void JavaRenderMemory::FillPolygonTextureAlpha::new_point_right(int i2, int dy) {
/**/
            tx2 = verts[i2 + 1].tx << 16; // T
            ty2 = verts[i2 + 1].ty << 16; // T
            dtx2 = ((verts[i2].tx - verts[i2 + 1].tx) << 16) / dy; // T
            dty2 = ((verts[i2].ty - verts[i2 + 1].ty) << 16) / dy; // T
            int a11 = (verts[i2 + 1].c >> 24) & 0x000000ff; // A
            int a12 = (verts[i2    ].c >> 24) & 0x000000ff; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a2 = a11; // A
            da2 = (a12 - a11) / dy; // A
            an2 = 0x00ffffff - a11; // 255 - a11 // A
            dan2 = ((-a12) - (-a11)) / dy; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonTextureAlpha::draw_scan_line() {
/**/
            draw_scan_line_texture_common(false, true);
            // ループ
            if (false == f) // 境界線をまたぐか
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    int color = texture[x + y * tw]; // A
                    int r = (color >> 16) & 0xff; // A
                    int g = (color >> 8) & 0xff; // A
                    int b = (color >> 0) & 0xff; // A
                    // s = s * _a
                    int _a = a >> 8; // 0000ffff <- 00ffffff // A
                    int _an = an >> 8; // 0000ffff <- 00ffffff // A
                    r = r * _a; // 00ffffff <- 000000ff * 0000ffff // A
                    g = g * _a; // 00ffffff <- 000000ff * 0000ffff // A
                    b = b * _a; // 00ffffff <- 000000ff * 0000ffff // A
                    // d = s + (d * _an)
                    int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // A
                    int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // A
                    int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // A
                    pixOff[p] // A
                        = 0xff000000 // A
                        | ((_r      ) & 0x00ff0000) // A
                        | ((_g >>  8) & 0x0000ff00) // A
                        | ((_b >> 16) & 0x000000ff); // A
                    tx += dtx; // T
                    ty += dty; // T
                    a += da; // A
                    an += dan; // A
                }
            }
            else
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16;
                    int y = ty >> 16;
                    int color = texture[x + y * tw]; // A
                    int r = (color >> 16) & 0xff; // A
                    int g = (color >> 8) & 0xff; // A
                    int b = (color >> 0) & 0xff; // A
                    // s = s * _a
                    int _a = a >> 8; // 0000ffff <- 00ffffff // A
                    int _an = an >> 8; // 0000ffff <- 00ffffff // A
                    r = r * _a; // 00ffffff <- 000000ff * 0000ffff // A
                    g = g * _a; // 00ffffff <- 000000ff * 0000ffff // A
                    b = b * _a; // 00ffffff <- 000000ff * 0000ffff // A
                    // d = s + (d * _an)
                    int _r = r + ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // A
                    int _g = g + ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // A
                    int _b = b + ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // A
                    pixOff[p] // A
                        = 0xff000000 // A
                        | ((_r      ) & 0x00ff0000) // A
                        | ((_g >>  8) & 0x0000ff00) // A
                        | ((_b >> 16) & 0x000000ff); // A
                    tx += dtx; // T
                    ty += dty; // T
                    a += da; // A
                    an += dan; // A
                    if (tx >= tw16) // T
                    {
                        tx -= tw16; // T
                    }
                    if (ty >= th16) // T
                    {
                        ty -= th16; // T
                    }
                }
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * テクスチャ + グラデーションポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonTextureGouraud extends FillPolygonTextureCommon
    {
/*C*/
private:
    class FillPolygonTextureGouraud : public FillPolygonTextureCommon
    {
    public:
        FillPolygonTextureGouraud(JavaRenderMemory* render) : FillPolygonTextureCommon(render) {}
#endif
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonTextureGouraud::new_point_left(int i1, int dy) {
/**/
            tx1 = verts[i1 - 1].tx << 16; // T
            ty1 = verts[i1 - 1].ty << 16; // T
            dtx1 = ((verts[i1].tx - verts[i1 - 1].tx) << 16) / dy; // T
            dty1 = ((verts[i1].ty - verts[i1 - 1].ty) << 16) / dy; // T
            b1   =   b_tbl[verts[i1 - 1].c & 0x00ffffff][255] << 8; // G
            bn1  =   b_tbl[verts[i1 - 1].c & 0x00ffffff][  0] << 8; // G
            db1  = ((b_tbl[verts[i1    ].c & 0x00ffffff][255] << 8) - b1 ) / dy; // G
            dbn1 = ((b_tbl[verts[i1    ].c & 0x00ffffff][  0] << 8) - bn1) / dy; // G
        }
/*C*/
#endif
/**/

/*J*
        protected void new_point_right(int i2, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_right(int i2, int dy);
#else
        void JavaRenderMemory::FillPolygonTextureGouraud::new_point_right(int i2, int dy) {
/**/
            tx2 = verts[i2 + 1].tx << 16; // T
            ty2 = verts[i2 + 1].ty << 16; // T
            dtx2 = ((verts[i2].tx - verts[i2 + 1].tx) << 16) / dy; // T
            dty2 = ((verts[i2].ty - verts[i2 + 1].ty) << 16) / dy; // T
            b2   =   b_tbl[verts[i2 + 1].c & 0x00ffffff][255] << 8; // G
            bn2  =   b_tbl[verts[i2 + 1].c & 0x00ffffff][  0] << 8; // G
            db2  = ((b_tbl[verts[i2    ].c & 0x00ffffff][255] << 8) - b2 ) / dy; // G
            dbn2 = ((b_tbl[verts[i2    ].c & 0x00ffffff][  0] << 8) - bn2) / dy; // G
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonTextureGouraud::draw_scan_line() {
/**/
            draw_scan_line_texture_common(true, false);
            // ループ
            if (false == f) // 境界線をまたぐか
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    int color = texture[x + y * tw]; // G
                    int _r = (color >> 16) & 0xff; // G
                    int _g = (color >> 8) & 0xff; // G
                    int _b = (color >> 0) & 0xff; // G
                    // s = (s * b) + ((255 - s) * bn)
                    _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
                    _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
                    _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
                    pixOff[p] = 0xff000000 | (_r << 16) | (_g << 8) | _b; // G
                    tx += dtx; // T
                    ty += dty; // T
                    b += db; // G
                    bn += dbn; // G
                }
            }
            else
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    int color = texture[x + y * tw]; // G
                    int _r = (color >> 16) & 0xff; // G
                    int _g = (color >> 8) & 0xff; // G
                    int _b = (color >> 0) & 0xff; // G
                    // s = (s * b) + ((255 - s) * bn)
                    _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
                    _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
                    _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
                    pixOff[p] = 0xff000000 | (_r << 16) | (_g << 8) | _b; // G
                    tx += dtx; // T
                    ty += dty; // T
                    if (tx >= tw16) // T
                    {
                        tx -= tw16; // T
                    }
                    if (ty >= th16) // T
                    {
                        ty -= th16; // T
                    }
                    b += db; // G
                    bn += dbn; // G
                }
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

    /**
     * テクスチャ + グラデーション + アルファブレンドポリゴン塗りつぶしクラス。
     */
/*J*
    private class FillPolygonTextureGouraudAlpha extends FillPolygonTextureCommon
    {
/*C*/
private:
    class FillPolygonTextureGouraudAlpha : public FillPolygonTextureCommon
    {
    public:
        FillPolygonTextureGouraudAlpha(JavaRenderMemory* render) : FillPolygonTextureCommon(render) {}
#endif
/**/

/*J*
        protected void new_point_left(int i1, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_left(int i1, int dy);
#else
        void JavaRenderMemory::FillPolygonTextureGouraudAlpha::new_point_left(int i1, int dy) {
/**/
            tx1 = verts[i1 - 1].tx << 16; // T
            ty1 = verts[i1 - 1].ty << 16; // T
            dtx1 = ((verts[i1].tx - verts[i1 - 1].tx) << 16) / dy; // T
            dty1 = ((verts[i1].ty - verts[i1 - 1].ty) << 16) / dy; // T
            b1   =   b_tbl[verts[i1 - 1].c & 0x00ffffff][255] << 8; // G
            bn1  =   b_tbl[verts[i1 - 1].c & 0x00ffffff][  0] << 8; // G
            db1  = ((b_tbl[verts[i1    ].c & 0x00ffffff][255] << 8) - b1 ) / dy; // G
            dbn1 = ((b_tbl[verts[i1    ].c & 0x00ffffff][  0] << 8) - bn1) / dy; // G
            int a11 = (verts[i1 - 1].c >> 24) & 0x000000ff; // A
            int a12 = (verts[i1    ].c >> 24) & 0x000000ff; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a1 = a11; // A
            da1 = (a12 - a11) / dy; // A
            an1 = 0x00ffffff - a11; // 255 - a11 // A
            dan1 = ((-a12) - (-a11)) / dy; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void new_point_right(int i2, int dy) {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void new_point_right(int i2, int dy);
#else
        void JavaRenderMemory::FillPolygonTextureGouraudAlpha::new_point_right(int i2, int dy) {
/**/
            tx2 = verts[i2 + 1].tx << 16; // T
            ty2 = verts[i2 + 1].ty << 16; // T
            dtx2 = ((verts[i2].tx - verts[i2 + 1].tx) << 16) / dy; // T
            dty2 = ((verts[i2].ty - verts[i2 + 1].ty) << 16) / dy; // T
            b2   =   b_tbl[verts[i2 + 1].c & 0x00ffffff][255] << 8; // G
            bn2  =   b_tbl[verts[i2 + 1].c & 0x00ffffff][  0] << 8; // G
            db2  = ((b_tbl[verts[i2    ].c & 0x00ffffff][255] << 8) - b2 ) / dy; // G
            dbn2 = ((b_tbl[verts[i2    ].c & 0x00ffffff][  0] << 8) - bn2) / dy; // G
            int a11 = (verts[i2 + 1].c >> 24) & 0x000000ff; // A
            int a12 = (verts[i2    ].c >> 24) & 0x000000ff; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a11 = (a11 << 8) | a11; // A
            a12 = (a12 << 8) | a12; // A
            a2 = a11; // A
            da2 = (a12 - a11) / dy; // A
            an2 = 0x00ffffff - a11; // 255 - a11 // A
            dan2 = ((-a12) - (-a11)) / dy; // A
        }
/*C*/
#endif
/**/

/*J*
        protected void draw_scan_line() {
/*C*/
#ifdef _IS_H_
    protected:
        virtual void draw_scan_line();
#else
        void JavaRenderMemory::FillPolygonTextureGouraudAlpha::draw_scan_line() {
/**/
            draw_scan_line_texture_common(true, true);
            // ループ
            if (false == f) // 境界線をまたぐか
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    int color = texture[x + y * tw]; // GA
                    int _r = (color >> 16) & 0xff; // G
                    int _g = (color >> 8) & 0xff; // G
                    int _b = (color >> 0) & 0xff; // G
                    // s = (s * b) + ((255 - s) * bn)
                    _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
                    _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
                    _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
                    // s = s * _a
                    int _a = a >> 8; // 0000ffff <- 00ffffff // A
                    int _an = an >> 8; // 0000ffff <- 00ffffff // A
                    _r *= _a; // 00ffffff <- 000000ff * 0000ffff // A
                    _g *= _a; // 00ffffff <- 000000ff * 0000ffff // A
                    _b *= _a; // 00ffffff <- 000000ff * 0000ffff // A
                    // d = s + (d * _an)
                    _r += ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // A
                    _g += ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // A
                    _b += ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // A
                    pixOff[p] // GA
                        = 0xff000000 // GA
                        | ((_r      ) & 0x00ff0000) // GA
                        | ((_g >>  8) & 0x0000ff00) // GA
                        | ((_b >> 16) & 0x000000ff); // GA
                    tx += dtx; // T
                    ty += dty; // T
                    b += db; // G
                    bn += dbn; // G
                    a += da; // A
                    an += dan; // A
                }
            }
            else
            {
                for (int p = p1; p < p2; ++ p)
                {
                    int x = tx >> 16; // T
                    int y = ty >> 16; // T
                    int color = texture[x + y * tw]; // GA
                    int _r = (color >> 16) & 0xff; // G
                    int _g = (color >> 8) & 0xff; // G
                    int _b = (color >> 0) & 0xff; // G
                    // s = (s * b) + ((255 - s) * bn)
                    _r = (_r * b + (255 - _r) * bn) >> 16 & 0xff; // G
                    _g = (_g * b + (255 - _g) * bn) >> 16 & 0xff; // G
                    _b = (_b * b + (255 - _b) * bn) >> 16 & 0xff; // G
                    // s = s * _a
                    int _a = a >> 8; // 0000ffff <- 00ffffff // A
                    int _an = an >> 8; // 0000ffff <- 00ffffff // A
                    _r *= _a; // 00ffffff <- 000000ff * 0000ffff // A
                    _g *= _a; // 00ffffff <- 000000ff * 0000ffff // A
                    _b *= _a; // 00ffffff <- 000000ff * 0000ffff // A
                    // d = s + (d * _an)
                    _r += ((pixOff[p] >> 16) & 0x000000ff) * _an; // 00ffffff // A
                    _g += ((pixOff[p] >>  8) & 0x000000ff) * _an; // 00ffffff // A
                    _b += ((pixOff[p]      ) & 0x000000ff) * _an; // 00ffffff // A
                    pixOff[p] // GA
                        = 0xff000000 // GA
                        | ((_r      ) & 0x00ff0000) // GA
                        | ((_g >>  8) & 0x0000ff00) // GA
                        | ((_b >> 16) & 0x000000ff); // GA
                    tx += dtx; // T
                    ty += dty; // T
                    if (tx >= tw16) // T
                    {
                        tx -= tw16; // T
                    }
                    if (ty >= th16) // T
                    {
                        ty -= th16; // T
                    }
                    b += db; // G
                    bn += dbn; // G
                    a += da; // A
                    an += dan; // A
                }
            }
        }
/*J*
    }
/*C*/
#endif
#ifdef _IS_H_
    };
/**/

/*J*
    protected void create_polygon_class() {
        fill_solid = new FillPolygonSolid();
        fill_alpha = new FillPolygonAlpha();
        fill_gouraud = new FillPolygonGouraud();
        fill_gouraud_alpha = new FillPolygonGouraudAlpha();
        fill_texture = new FillPolygonTexture();
        fill_texture_alpha = new FillPolygonTextureAlpha();
        fill_texture_gouraud = new FillPolygonTextureGouraud();
        fill_texture_gouraud_alpha = new FillPolygonTextureGouraudAlpha();
    }
/*C*/
#endif
#ifdef _IS_H_
protected:
    void create_polygon_class();
#else
    void JavaRenderMemory::create_polygon_class() {
        fill_solid = new FillPolygonSolid(this);
        fill_alpha = new FillPolygonAlpha(this);
        fill_gouraud = new FillPolygonGouraud(this);
        fill_gouraud_alpha = new FillPolygonGouraudAlpha(this);
        fill_texture = new FillPolygonTexture(this);
        fill_texture_alpha = new FillPolygonTextureAlpha(this);
        fill_texture_gouraud = new FillPolygonTextureGouraud(this);
        fill_texture_gouraud_alpha = new FillPolygonTextureGouraudAlpha(this);
    }
/**/
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
};
#endif
/**/

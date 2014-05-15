/**
 * @file
 *
 * $Id: Color.cpp,v 1.5 2007/11/30 22:42:27 matsushima Exp $
 *
 * Color.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/22 matsushima cpp2javalib
 * @version $Revision: 1.5 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Color.cpp,v $
 * Revision 1.5  2007/11/30 22:42:27  matsushima
 * 再登録
 *
 * Revision 1.4  2007/05/10 22:29:47  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.3  2007/05/09 12:45:23  matsushima
 * no message
 *
 * Revision 1.2  2007/05/08 15:24:46  matsushima
 * スタティックメンバアクセス :: -> .
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Color"

/*------------------------------------------------------------*/

static const Color _black(0, 0, 0);
const Color* Color::BLACK = &_black;
const Color* Color::black = &_black;
static const Color _blue(0, 0, 0);
const Color* Color::BLUE = &_blue;
const Color* Color::blue = &_blue;

Color::Color(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(int rgb)
{
    this->r = (rgb >> 16) & 0xff;
    this->g = (rgb >> 8) & 0xff;
    this->b = rgb & 0xff;
}

int Color::getRed() const
{
    return r;
}

int Color::getGreen() const
{
    return g;
}

int Color::getBlue() const
{
    return b;
}

Color Color::getHSBColor(float h, float s, float b)
{
    return Color(HSBtoRGB(h, s, b));
}

int Color::HSBtoRGB(float h, float s, float b)
{
    if (0 == s)
    {
        return 0xff000000 | ((int)(b * 255.5f) * 0x00010101);
    }
    h = (h >= 0) ? h - (int)h : 1 - (h - (int)h);
    //s = (s >= 0) ? s - (int)s : 1 - (s - (int)s);
    //b = (b >= 0) ? b - (int)b : 1 - (b - (int)b);
    float bmax = b;
    float bdif = b * s;
    float bmin = b - bdif;
    int max = (int)(bmax * 255.5f);
    int min = (int)(bmin * 255.5f);
    float h1 = h * 6 - (int)(h * 6);
    float h2 = 1.0f - h1;
    int dif1 = (int)((h1 * bdif + bmin) * 255.5f);
    int dif2 = (int)((h2 * bdif + bmin) * 255.5f);
    switch ((int)(h * 6))
    {
    case 0: return 0xff000000 | (max  << 16) | (dif1 << 8) | min;
    case 1: return 0xff000000 | (dif2 << 16) | (max  << 8) | min;
    case 2: return 0xff000000 | (min  << 16) | (max  << 8) | dif1;
    case 3: return 0xff000000 | (min  << 16) | (dif2 << 8) | max;
    case 4: return 0xff000000 | (dif1 << 16) | (min  << 8) | max;
    case 5: return 0xff000000 | (max  << 16) | (min  << 8) | dif2;
    }
    return 0xff000000;
}

float* Color::RGBtoHSB(int r, int g, int b, float hsbvals[])
{
    if (NULL == hsbvals)
    {
        hsbvals = new float[3];
    }
    int max = (r > g) ? r : g;
    max = (b > max) ? b : max;
    int min = (r < g) ? r : g;
    min = (b < min) ? b : min;
    float brightness = max / 255.0f;
    float saturation = (0 == max) ? 0.0f : (float)(max - min) / max;
    float hue = 0.0f;
    if (0.0f != saturation)
    {
        float fr = (float)(max - r) / (max - min);
        float fg = (float)(max - g) / (max - min);
        float fb = (float)(max - b) / (max - min);
        if (r == max)
        {
            hue = fb - fg;
        }
        else
        if (g == max)
        {
            hue = fr - fb + 2.0f;
        }
        else
        //if (b == max)
        {
            hue = fg - fr + 4.0f;
        }
        hue = (hue + 6.0f) / 6.0f;
        hue -= (int)hue;
    }
    hsbvals[0] = hue;
    hsbvals[1] = saturation;
    hsbvals[2] = brightness;
    return hsbvals;
}

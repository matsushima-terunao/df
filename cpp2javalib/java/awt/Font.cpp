/**
 * @file
 *
 * $Id: Font.cpp,v 1.1.1.1 2006/08/17 20:26:01 matsushima Exp $
 *
 * Font.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/30 matsushima cpp2javalib
 * @version $Revision: 1.1.1.1 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Font.cpp,v $
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Font"
#include <windows.h>

/*------------------------------------------------------------*/

static int _cmpstr(const char* s1, const char* s2)
{
    for (; '\0' != *s1; ++ s1, ++ s2)
    {
        if (*s1 != *s2)
        {
            return 1;
        }
    }
    return ('\0' != *s2) ? 1 : 0;
}

Font::Font(const char* name, int style, int size)
{
    this->name = name;
    this->style = style;
    this->size = size;
    int pitch = DEFAULT_PITCH;
    int family = FF_DONTCARE;
    if (0 == _cmpstr(name, "Serif"))
    {
        pitch = VARIABLE_PITCH; // proportional
        family = FF_ROMAN; // proportional, serif
    }
    else
    if (0 == _cmpstr(name, "SansSerif"))
    {
        pitch = VARIABLE_PITCH; // proportional
        family = FF_SWISS; // proportional, sans serif
    }
    else
    if (0 == _cmpstr(name, "Monospaced"))
    {
        pitch = FIXED_PITCH; // monospace
        family = FF_MODERN; // monospace
    }
    else
    if (0 == _cmpstr(name, "Dialog"))
    {
        pitch = VARIABLE_PITCH; // proportional
        family = FF_SWISS; // proportional, sans serif
    }
    else
    if (0 == _cmpstr(name, "DialogInput"))
    {
        pitch = FIXED_PITCH; // monospace
        family = FF_ROMAN; // serif
    }
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight = -size;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = (Font::BOLD == (Font::BOLD & style)) ? FW_BOLD : FW_NORMAL;
    lf.lfItalic = (Font::ITALIC == (Font::ITALIC & style)) ? TRUE : FALSE;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = pitch | family;
    //lf.lfFaceName;
    hfont = CreateFontIndirect(&lf);
}

Font::~Font()
{
    DeleteObject((HFONT)hfont);
}

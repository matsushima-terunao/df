/**
 * @file
 *
 * $Id: Component.cpp,v 1.5 2007/11/30 22:42:27 matsushima Exp $
 *
 * Component.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/21 matsushima cpp2javalib
 * @version $Revision: 1.5 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Component.cpp,v $
 * Revision 1.5  2007/11/30 22:42:27  matsushima
 * çƒìoò^
 *
 * Revision 1.4  2007/05/09 21:17:24  matsushima
 * no message
 *
 * Revision 1.3  2007/05/09 12:41:18  matsushima
 * Component.repaint() ÇÃìØä˙
 *
 * Revision 1.2  2006/08/18 11:39:55  matsushima
 * no message
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Component"
#include "Color"
#include "Font"
#include "FontMetrics"
#include "Graphics"
#include "Image_"
typedef class Rectangle _Rectangle; // same as WINGDIAPI BOOL WINAPI Rectangle(HDC, int, int, int, int);
#include "Rectangle"
#include "event/KeyEvent"
#include "event/KeyListener"
#include "event/MouseEvent"
#include "event/MouseListener"
#include "event/MouseMotionListener"
#include "image/ImageConsumer"
#include "image/ImageProducer"
#include <windows.h>

/*------------------------------------------------------------*/

static CRITICAL_SECTION cs;
static bool init_cs = false;

/*
 * ComponentFontMetrics
 *
 * @see ComponentGraphics
 */
class ComponentFontMetrics : public FontMetrics
{
private:
    Font* font;
    ComponentGraphics* graphics;
    HDC hdc;
    HFONT hfont;
public:
    Font*& _font()
    {
        return font;
    }
    ComponentFontMetrics(Font* font, ComponentGraphics* graphics, HDC hdc, HFONT hfont)
        : FontMetrics(font)
    {
        this->font = font;
        this->graphics = graphics;
        this->hdc = hdc;
        this->hfont = hfont;
        LOGFONT lf;
        memset(&lf, 0, sizeof(lf));
        _ASSERTE(GetObject(hfont, sizeof(lf), &lf));
        _ASSERTE(this->hfont = CreateFontIndirect(&lf));
    }
    ~ComponentFontMetrics()
    {
        _ASSERTE(DeleteObject(hfont));
    }
    void get_tm(TEXTMETRIC& tm)
    {
        memset(&tm, 0, sizeof(tm));
EnterCriticalSection(&cs);
        HGDIOBJ hfont_old;
        _ASSERTE(hfont_old = SelectObject(hdc, hfont));
        _ASSERTE(GetTextMetrics(hdc, &tm));
        _ASSERTE((hfont == SelectObject(hdc, hfont_old)));
LeaveCriticalSection(&cs);
    }
    int getAscent()
    {
        TEXTMETRIC tm;
        get_tm(tm);
        return tm.tmAscent;
    }
    int getDescent()
    {
        TEXTMETRIC tm;
        get_tm(tm);
        return tm.tmDescent;
    }
    int stringWidth(const char* str)
    {
EnterCriticalSection(&cs);
        HGDIOBJ hfont_old;
        _ASSERTE(hfont_old = SelectObject(hdc, hfont));
        SIZE sz;
        _ASSERTE(GetTextExtentPoint32(hdc, str, strlen(str), &sz));
        _ASSERTE((hfont == SelectObject(hdc, hfont_old)));
LeaveCriticalSection(&cs);
        return sz.cx;
    }
};
 
/*
 * ComponentGraphics
 *
 * @see OffScrrenImage.getGraphics()
 * @see java.awt.Component._WindowProc(WM_PAINT)
 */
class ComponentGraphics : public Graphics, public ImageConsumer
{
    friend class ComponentFontMetrics;
private:
    int width, height;
    HDC hdc;
    HPEN hpen;
    HGDIOBJ hpen_old;
    HBRUSH hbr;
    HGDIOBJ hbr_old;
    HFONT hfont;
    HGDIOBJ hfont_old;
    Font* font;
public:
    ComponentGraphics(HDC hdc, int width, int height)
    {
        _ASSERTE(this->hdc = hdc);
        SaveDC(hdc);
        this->width = width;
        this->height = height;
        hpen = NULL;
        hpen_old = NULL;
        hbr = NULL;
        hbr_old = NULL;
        setColor(&Color(0, 0, 0));
        hfont = NULL;
        hfont_old = NULL;
        _ASSERTE(SetBkMode((HDC)hdc, TRANSPARENT));
        font = new Font("", Font::PLAIN, 16);
    }
    ~ComponentGraphics()
    {
        RestoreDC(hdc, -1);
        if (NULL != hpen)
        {
            //SelectObject((HDC)hdc, hpen_old);
            _ASSERTE(DeleteObject(hpen));
        }
        if (NULL != hbr)
        {
            //SelectObject((HDC)hdc, hbr_old);
            _ASSERTE(DeleteObject(hbr));
        }
        if (NULL != hfont)
        {
            //SelectObject((HDC)hdc, hfont_old);
            _ASSERTE(DeleteObject(hfont));
        }
        delete font;
    }
    void setColor(const Color* c)
    {
EnterCriticalSection(&cs);
        _ASSERTE((CLR_INVALID != SetTextColor((HDC)hdc, RGB(c->getRed(), c->getGreen(), c->getBlue()))));
        HPEN hpen_new;
        _ASSERTE(hpen_new = CreatePen(PS_SOLID, 1, RGB(c->getRed(), c->getGreen(), c->getBlue())));
        _ASSERTE(hpen_old = SelectObject((HDC)hdc, hpen_new));
        if (NULL != hpen)
        {
            _ASSERTE(DeleteObject(hpen));
        }
        hpen = hpen_new;
        HBRUSH hbr_new;
        _ASSERTE(hbr_new = CreateSolidBrush(RGB(c->getRed(), c->getGreen(), c->getBlue())));
        _ASSERTE(hbr_old = SelectObject((HDC)hdc, hbr_new));
        if (NULL != hbr)
        {
            _ASSERTE(DeleteObject(hbr));
        }
        hbr = hbr_new;
LeaveCriticalSection(&cs);
    }
    Font*& getFont()
    {
        return font;
    }
    void setFont(const Font* font)
    {
EnterCriticalSection(&cs);
        _ASSERTE(font);
        _ASSERTE(hfont = (HFONT)font->hfont);
        _ASSERTE(hfont_old = SelectObject((HDC)hdc, hfont));
        *this->font = *font;
LeaveCriticalSection(&cs);
    }
    FontMetrics* getFontMetrics()
    {
        ComponentFontMetrics* fm;
        _ASSERTE(fm = new ComponentFontMetrics(font, this, hdc, hfont));
        return fm;
    }
    void drawLine(int x1, int y1, int x2, int y2)
    {
EnterCriticalSection(&cs);
        _ASSERTE(MoveToEx((HDC)hdc, x1, y1, NULL));
        _ASSERTE(LineTo((HDC)hdc, x2, y2));
LeaveCriticalSection(&cs);
    }
    void fillRect(int x, int y, int width, int height)
    {
EnterCriticalSection(&cs);
        RECT rc = { x, y, x + width, y + height };
        _ASSERTE(FillRect((HDC)hdc, &rc, hbr));
LeaveCriticalSection(&cs);
    }
    POINT* copy_point(POINT pt[100], int* xPoints, int* yPoints, int nPoints, int nPoints_alloc)
    {
        if (nPoints_alloc > 100)
        {
            _ASSERTE(pt = new POINT[nPoints_alloc]);
        }
        int i;
        for (i = 0; i < nPoints; ++ i)
        {
            pt[i].x = xPoints[i];
            pt[i].y = yPoints[i];
        }
        return pt;
    }
    void free_point(POINT pt_buf[100], POINT* pt)
    {
        if (pt != pt_buf)
        {
            delete[] pt;
        }
    }
    void drawPolygon(int* xPoints, int* yPoints, int nPoints)
    {
        POINT pt_buf[100];
        POINT* pt = copy_point(pt_buf, xPoints, yPoints, nPoints, nPoints + 1);
        pt[nPoints].x = xPoints[0];
        pt[nPoints].y = yPoints[0];
EnterCriticalSection(&cs);
        _ASSERTE(Polyline((HDC)hdc, pt, nPoints + 1));
LeaveCriticalSection(&cs);
        free_point(pt_buf, pt);
    }
    void fillPolygon(int* xPoints, int* yPoints, int nPoints)
    {
        POINT pt_buf[100];
        POINT* pt = copy_point(pt_buf, xPoints, yPoints, nPoints, nPoints);
EnterCriticalSection(&cs);
        _ASSERTE(Polygon((HDC)hdc, pt, nPoints));
LeaveCriticalSection(&cs);
        free_point(pt_buf, pt);
    }
    void fillArc(int x, int y, int width, int height, int startAngle, int endAngle)
    {
EnterCriticalSection(&cs);
        x -= width / 2 - 1;
        y -= height  / 2 - 1;
        Chord((HDC)hdc, x, y, x + width + 1, y + height + 1,
            (int)(100 * Math::sin(startAngle * Math::PI / 180)),
            (int)(100 * Math::cos(startAngle * Math::PI / 180)),
            (int)(100 * Math::sin(endAngle * Math::PI / 180)),
            (int)(100 * Math::cos(endAngle * Math::PI / 180)));
LeaveCriticalSection(&cs);
    }
    void drawImage(Image* img, int x, int y, ImageObserver* observer)
    {
        if (NULL != img->_hdc)
        {
EnterCriticalSection(&cs);
            BOOL result;
            /*_ASSERTE*/(result = BitBlt((HDC)hdc, 0, 0, width, height, (HDC)img->_hdc, 0, 0, SRCCOPY));
            DWORD e = GetLastError();
            _ASSERTE(result);
LeaveCriticalSection(&cs);
        }
        else
        {
            // img: Produced image
            // java.awt.Component.ProducedImage.setPixels()
            // java.awt.Component.repaint()
            // java.awt.Component.update()
            // java.awt.Component.paint()
            // java.awt.Component.ComponentGraphics.drawImage(java.awt.Component.ProducedImage)
            // java.awt.Component.ProducedImage.startProduction(java.awt.Component.ComponentGraphics)
            // java.awt.Component.ComponentGraphics.setPixels()
            // -> draw
            _ASSERTE(img->getSource());
            img->getSource()->startProduction(this);
        }
    }
    void drawString(const char* str, int x, int y)
    {
EnterCriticalSection(&cs);
        _ASSERTE(TextOut((HDC)hdc, x, y, str, strlen(str)));
LeaveCriticalSection(&cs);
    }
    // ImageConsumer
    virtual void setPixels(int x, int y, int w, int h, ColorModel* model, unsigned char* pixels, int off, int scansize)
    {
        BITMAPINFOHEADER bmih;
        BITMAPINFO* bmi = (BITMAPINFO*)&bmih;
        bmih.biSize           = sizeof(BITMAPINFOHEADER);
        bmih.biWidth          = w;
        bmih.biHeight         = h;
        bmih.biPlanes         = 1;
        bmih.biBitCount       = 32;
        bmih.biCompression    = BI_RGB;
        bmih.biSizeImage      = 0;
        bmih.biXPelsPerMeter  = 0;
        bmih.biYPelsPerMeter  = 0;
        bmih.biClrUsed        = 0;
        bmih.biClrImportant   = 0;
/**/
        _ASSERTE(SetDIBitsToDevice(
            (HDC)hdc,
            0, 0, w, h,
            0, 0, 0, h,
            pixels, bmi, DIB_RGB_COLORS));
/**
        _ASSERTE((GDI_ERROR != StretchDIBits(
            (HDC)hdc,
            0, 0, w, h,
            0, h - 1, w, -h,
            pixels, bmi, DIB_RGB_COLORS, SRCCOPY));
/**/
    }
    virtual void setPixels(int x, int y, int w, int h, ColorModel* model, int* pixels, int off, int scansize)
    {
        setPixels(x, y, w, h, model, (unsigned char*)pixels, off * sizeof(int), scansize * sizeof(int));
    }
};

/*------------------------------------------------------------*/

/*
 * OffScreenImage
 *
 * @see java.awt.Component.createImage(int width, int height)
 */
class OffScreenImage : public Image
{
private:
    ImageProducer* producer;
    int width, height;
    HDC hdc;
    HBITMAP hbmp;
    HGDIOBJ hbmp_old;
public:
    OffScreenImage(int width, int height, HWND hWnd)
    {
        producer = NULL;
        this->width = width;
        this->height = height;
        HDC hdc;
        _ASSERTE(hdc = GetDC(hWnd));
        _ASSERTE(this->_hdc = this->hdc = CreateCompatibleDC(hdc));
        _ASSERTE(hbmp = CreateCompatibleBitmap(hdc, width, height));
        _ASSERTE(ReleaseDC(hWnd, hdc));
        _ASSERTE(this->hbmp_old = SelectObject(this->hdc, hbmp));
        _ASSERTE(graphics = new ComponentGraphics(this->hdc, width, height));
    }
    ~OffScreenImage()
    {
        flush();
    }
    virtual ImageProducer*& getSource()
    {
        return producer; // NULL
    }
    virtual Graphics*& getGraphics()
    {
        return graphics;
    }
    virtual int getWidth(ImageObserver* observer)
    {
        return width;
    }
    virtual int getHeight(ImageObserver* observer)
    {
        return height;
    }
    virtual void flush()
    {
        if (NULL != graphics)
        {
            if (NULL != hdc)
            {
                if (NULL != hbmp_old)
                {
                    _ASSERTE(SelectObject((HDC)hdc, (HGDIOBJ)hbmp_old));
                }
                _ASSERTE(DeleteDC((HDC)hdc));
            }
            if (NULL != hbmp)
            {
                _ASSERTE(DeleteObject((HBITMAP)hbmp));
            }
            delete graphics;
        }
    }
};

/*------------------------------------------------------------*/

/*
 * ProducedImage
 *
 * @see java.awt.Component.createImage(ImageProducer* producer)
 */
class ProducedImage : public Image, public ImageConsumer
{
private:
    int width, height;
    ImageProducer* producer;
    Component* component;
public:
    ProducedImage(ImageProducer* producer, Component* component)
    {
        this->producer = producer;
        producer->addConsumer(this);
        this->component = component;
    }
    virtual ImageProducer*& getSource()
    {
        return producer;
    }
    virtual Graphics*& getGraphics()
    {
        return graphics;
    }
    virtual int getWidth(ImageObserver* observer)
    {
        return width;
    }
    virtual int getHeight(ImageObserver* observer)
    {
        return height;
    }
    virtual void flush()
    {
    }
    // ImageConsumer
    virtual void setPixels(int x, int y, int w, int h, ColorModel* model, unsigned char* pixels, int off, int scansize)
    {
        component->repaint();
    }
    virtual void setPixels(int x, int y, int w, int h, ColorModel* model, int* pixels, int off, int scansize)
    {
        component->repaint();
    }
};

/*------------------------------------------------------------*/

Image* Component::createImage(ImageProducer* producer)
{
    Image* image = new ProducedImage(producer, this);
    objstack.stack.push_back(image);
    return image;
}

Image* Component::createImage(int width, int height)
{
    Image* image = new OffScreenImage(width, height, (HWND)hwnd);
    objstack.stack.push_back(image);
    return image;
}

bool Component::prepareImage(Image* image, ImageObserver* observer)
{
    return true;
}

void Component::addKeyListener(KeyListener* l)
{
    keylisteners.push_back(l);
}

void Component::addMouseListener(MouseListener* l)
{
    mouselisteners.push_back(l);
}

void Component::addMouseMotionListener(MouseMotionListener* l)
{
    mousemotionlisteners.push_back(l);
}

void Component::removeKeyListener(KeyListener* l)
{
    keylisteners.remove(l);
}

void Component::removeMouseListener(MouseListener* l)
{
    mouselisteners.remove(l);
}

void Component::removeMouseMotionListener(MouseMotionListener* l)
{
    mousemotionlisteners.remove(l);
}

void Component::requestFocus()
{
    SetFocus((HWND)hwnd);
}

void Component::setSize(int width, int height)
{
    _ASSERT(SetWindowPos((HWND)hwnd, NULL, 0, 0, width, height,
        SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER));
}

_Rectangle Component::getBounds()
{
    RECT rc;
    _ASSERTE(GetWindowRect((HWND)hwnd, &rc));
    return _Rectangle(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
}

bool Component::isDoubleBuffered()
{
    return false;
}

HWND hwnd_update;
extern volatile boolean in_destroy, in_update;
HANDLE hevent;

void Component::repaint()
{
//OutputDebugString("\nr");
//    InvalidateRect((HWND)hwnd, NULL, FALSE);
//    UpdateWindow((HWND)hwnd);
//    return;
hwnd_update = (HWND)hwnd;
InvalidateRect((HWND)hwnd, NULL, FALSE);
//SendNotifyMessage((HWND)hwnd, WM_PAINT, 0, 0);
while (true)
{
    if ((NULL != hwnd_update) && (false == in_destroy))
    {
    }
    else
    {
        break;
    }
    DWORD res = WaitForSingleObject(hevent, 100);
    if (WAIT_OBJECT_0 == res)
    {
//OutputDebugString("get\n");
        break;
    }
}
}

void Component::update(Graphics* g)
{
    paint(g);
}

void Component::paint(Graphics* g)
{
}

long Component::_WindowProc(
    void* _hWnd,
    unsigned int _uMsg,
    unsigned int _wParam,
    long _lParam)
{
    HWND hWnd = (HWND)_hWnd;
    UINT uMsg = _uMsg;
    WPARAM wParam = _wParam;
    LPARAM lParam = _lParam;
    switch (uMsg)
    {
    case WM_CREATE:
        {
            return 0;
        }
    case WM_KEYDOWN:
        {
//            UINT vk = MapVirtualKey(wParam, 2);
//System::out.println(String("down: ") + (int)wParam + ", vk=" + (long)vk);
            int key = wParam;
            switch (wParam)
            {
            case VK_SHIFT: modifiers |= KeyEvent::SHIFT_MASK; break;
            case VK_CONTROL: modifiers |= KeyEvent::CTRL_MASK; break;
            case VK_INSERT: key = KeyEvent::_VK_INSERT; break;
            case VK_DELETE: key = KeyEvent::_VK_DELETE; break;
            }
            modifiers = 0;
            modifiers = (modifiers & ~KeyEvent::ALT_MASK) | ((0 != (wParam & (1 << 24))) ? KeyEvent::ALT_MASK : 0);
            KeyEvent e(this, KeyEvent::KEY_PRESSED, System::currentTimeMillis(), modifiers, key, key);
            std::list<KeyListener*>::iterator it;
            for (it = keylisteners.begin(); it != keylisteners.end(); ++ it)
            {
                (*it)->keyPressed(&e);
            }
            break;
        }
    case WM_KEYUP:
        {
            int key = wParam;
            switch (wParam)
            {
            case VK_SHIFT: modifiers &= ~KeyEvent::SHIFT_MASK; break;
            case VK_CONTROL: modifiers &= ~KeyEvent::CTRL_MASK; break;
            case VK_INSERT: key = KeyEvent::_VK_INSERT; break;
            case VK_DELETE: key = KeyEvent::_VK_DELETE; break;
            }
            modifiers = 0;
            modifiers = (modifiers & ~KeyEvent::ALT_MASK) | ((0 != (wParam & (1 << 24))) ? KeyEvent::ALT_MASK : 0);
            KeyEvent e(this, KeyEvent::KEY_RELEASED, System::currentTimeMillis(), modifiers, key, key);
            std::list<KeyListener*>::iterator it;
            for (it = keylisteners.begin(); it != keylisteners.end(); ++ it)
            {
                (*it)->keyReleased(&e);
            }
            break;
        }
    case WM_CHAR:
        {
//            switch (wParam)
//            {
//            case VK_SHIFT: modifiers |= KeyEvent::SHIFT_MASK; break;
//            case VK_CONTROL: modifiers |= KeyEvent::CTRL_MASK; break;
//            }
            modifiers = 0;
            modifiers = (modifiers & ~KeyEvent::ALT_MASK) | ((0 != (wParam & (1 << 24))) ? KeyEvent::ALT_MASK : 0);
            KeyEvent e(this, KeyEvent::KEY_TYPED, System::currentTimeMillis(), modifiers, wParam, wParam);
            std::list<KeyListener*>::iterator it;
            for (it = keylisteners.begin(); it != keylisteners.end(); ++ it)
            {
                (*it)->keyTyped(&e);
            }
            break;
        }
    case WM_MOUSEMOVE:
        {
            MouseEvent e(this, MouseEvent::_MOUSE_MOVED, System::currentTimeMillis(), modifiers,
                (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), 0, 0, 0);
            std::list<MouseMotionListener*>::iterator it;
            for (it = mousemotionlisteners.begin(); it != mousemotionlisteners.end(); ++ it)
            {
                (*it)->mouseMoved(&e);
            }
            break;
        }
    case WM_LBUTTONDOWN:
        {
            modifiers |= MouseEvent::BUTTON1_MASK;
            MouseEvent e(this, MouseEvent::_MOUSE_PRESSED, System::currentTimeMillis(), modifiers,
                (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), 0, 0, 0);
            std::list<MouseListener*>::iterator it;
            for (it = mouselisteners.begin(); it != mouselisteners.end(); ++ it)
            {
                (*it)->mousePressed(&e);
            }
            break;
        }
    case WM_LBUTTONUP:
        {
            modifiers |= MouseEvent::BUTTON1_MASK;
            MouseEvent e(this, MouseEvent::_MOUSE_RELEASED, System::currentTimeMillis(), modifiers,
                (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), 0, 0, 0);
            std::list<MouseListener*>::iterator it;
            for (it = mouselisteners.begin(); it != mouselisteners.end(); ++ it)
            {
                (*it)->mouseReleased(&e);
            }
            break;
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            ComponentGraphics graphics(hdc, ps.rcPaint.right, ps.rcPaint.bottom);
//char buf[111];
//sprintf(buf, ";%d,%d,%d,%d", ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom);
//OutputDebugString(buf);
            (false != is_update)
                ? update(&graphics) : paint(&graphics);
            is_update = false;
            EndPaint(hWnd, &ps);
hwnd_update = null;
SetEvent(hevent);
            return 0;
        }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static LRESULT CALLBACK WindowProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    Component* component;
    if (WM_CREATE == uMsg)
    {
        CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
        component = (Component*)cs->lpCreateParams;
        SetWindowLong(hWnd, GWL_USERDATA, (LPARAM)component);
    }
    else
    {
        component = (Component*)GetWindowLong(hWnd, GWL_USERDATA);
    }
    return (NULL == component)
        ? DefWindowProc(hWnd, uMsg, wParam, lParam)
        : component->_WindowProc(hWnd, uMsg, wParam, lParam);
}

Component::Component()
{
    if (false == init_cs)
    {
        init_cs = true;
InitializeCriticalSection(&cs);
hevent = CreateEvent(NULL, FALSE, TRUE, "awt.component.update");
    }
    modifiers = 0;
    hwnd = NULL;
    is_update = false;

    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(wc);
    if (FALSE == GetClassInfoEx(hInstance, "cpp2java.Component", &wc))
    {
        memset(&wc, 0, sizeof(wc));
        wc.cbSize        = sizeof(wc);
        wc.style         = CS_VREDRAW | CS_HREDRAW;
        wc.lpfnWndProc   = WindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = NULL;
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszMenuName  = NULL;//MAKEINTRESOURCE(IDR_MENU);
        wc.lpszClassName = "cpp2java.Component";
        //_ASSERTE(wc.hIconSm       = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_APP), IMAGE_ICON,
        //    GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR)*/);
        ATOM atom;
        _ASSERTE(atom = RegisterClassEx(&wc));
    }
    _ASSERTE(hwnd = CreateWindowEx(
        0,
        "cpp2java.Component", NULL,
        WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, this));
}

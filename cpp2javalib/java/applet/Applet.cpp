/**
 * @file
 *
 * $Id: Applet.cpp,v 1.3 2007/11/30 22:42:27 matsushima Exp $
 *
 * Applet.cpp : 
 *
 * @author  0.0 2005/03/19 matsushima h2java
 * @author  0.1 2006/07/20 matsushima cpp2javalib
 * @version $Revision: 1.3 $
 * @since   0.0 2005/03/19 matsushima h2java
 *
 * $Log: Applet.cpp,v $
 * Revision 1.3  2007/11/30 22:42:27  matsushima
 * çƒìoò^
 *
 * Revision 1.2  2007/04/23 17:06:33  matsushima
 * ÉäÉvÉåÅ[ÉX
 *
 * Revision 1.1.1.1  2006/08/17 20:26:01  matsushima
 * new
 *
 */

#include "stdafx.h"
#include "Applet"
#include "java/awt/Image_"
#include "java/awt/image/DirectColorModel"
#include "java/awt/image/ImageConsumer"
#include "java/awt/image/ImageProducer"
#include "java/awt/image/IndexColorModel"
#include "java/net/URL"
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <string.h>
#include "png/png.h"
/**/
#ifdef _DEBUG
#pragma comment(lib, "../cpp2javalib/png/libpngd.lib")
#else
#pragma comment(lib, "../cpp2javalib/png/libpng.lib")
#endif
/**/

/*------------------------------------------------------------*/

/*
 * FileImage
 *
 * @see java.applet.Applet.getImage(String name)
 */
class FileImage : public Image, public ImageProducer
{
private:
    ImageProducer* producer;
    ImageConsumer* consumer;
    BITMAPFILEHEADER bmfh;
    unsigned char* bmi_buf;
    BITMAPINFO* bmi;
    BITMAPINFOHEADER* bmih;
    unsigned char* bits;
    int width_bytes, size_image, height;
public:
    FileImage(const char* name)
    {
        producer = this;
        FILE* fp;
        _ASSERTE(fp = fopen(name, "rb"));
        char ext[_MAX_EXT] = "";
        _splitpath(name, NULL, NULL, NULL, ext);
        strlwr(ext);
        if (0 == strcmp(ext, ".bmp"))
        {
            _ASSERTE((sizeof(bmfh) == fread(&bmfh, 1, sizeof(bmfh), fp)));
            int size = bmfh.bfOffBits - sizeof(bmfh);
            _ASSERTE(bmi_buf = new unsigned char[size]);
            bmi = (BITMAPINFO*)bmi_buf;
            bmih = &bmi->bmiHeader;
            _ASSERTE((size == fread(bmi, 1, size, fp)));
            int width = bmih->biWidth * bmih->biPlanes * bmih->biBitCount;
            width_bytes = ((width + 31) - (width + 31) % 32) / 8;
            size_image = (0 != bmih->biSizeImage) ? bmih->biSizeImage : width_bytes * bmih->biHeight;
            _ASSERTE(bits = new unsigned char[size_image]);
            _ASSERTE((size_image == fread(bits, 1, size_image, fp)));
            height = -bmih->biHeight; // bottom-up
        }
        else
        if (0 == strcmp(ext, ".png"))
        {
            png_structp png_ptr;
            _ASSERTE(png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL));
            png_infop info_ptr;
            _ASSERTE(info_ptr = png_create_info_struct(png_ptr));
            png_init_io(png_ptr, fp);
            png_read_info(png_ptr, info_ptr);
            unsigned long width = 0, height = 0;
            int bit_depth = 0, color_type = 0, interlace_type = 0;
            _ASSERTE(png_get_IHDR(png_ptr, info_ptr,
                &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL));
            _ASSERTE(width_bytes = png_get_rowbytes(png_ptr, info_ptr));
            unsigned char** image;
            _ASSERTE(image = (png_bytepp)malloc(height * sizeof(png_bytep)));
            unsigned int i;
            for (i = 0; i < height; ++ i)
            {
                _ASSERTE(image[i] = (png_bytep)malloc(width_bytes));
            }
            png_read_image(png_ptr, image);

            // bmi, bmih
            int bmi_size = sizeof(BITMAPINFOHEADER) + info_ptr->num_palette * sizeof(RGBQUAD);
            _ASSERTE(bmi_buf = new unsigned char[bmi_size]);
            memset(bmi_buf, 0, bmi_size);
            bmi = (BITMAPINFO*)bmi_buf;
            bmih = &bmi->bmiHeader;
            bmih->biSize        = sizeof(BITMAPINFOHEADER);
            bmih->biWidth       = info_ptr->width;
            bmih->biHeight      = info_ptr->height;
            bmih->biPlanes      = 1;
            bmih->biBitCount    = info_ptr->bit_depth;
            bmih->biClrUsed     = info_ptr->num_palette;
            bmih->biCompression = BI_RGB;//4;//BI_PNG;
            RGBQUAD* colors = (RGBQUAD*)((LPSTR)bmi + (WORD)(bmi->bmiHeader.biSize));
            for (i = 0; i < info_ptr->num_palette; ++ i)
            {
                colors[i].rgbRed   = info_ptr->palette[i].red;
                colors[i].rgbGreen = info_ptr->palette[i].green;
                colors[i].rgbBlue  = info_ptr->palette[i].blue;
            }

            // bits
            int size_image = width_bytes * bmih->biHeight;
            bits = new unsigned char[size_image];
            for (i = 0; i < height; ++ i)
            {
                memcpy(&bits[width_bytes * i], image[i], width_bytes);
                free(image[i]);
            }
            free(image);
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
            this->height = bmih->biHeight;
        }
        else
        {
            _ASSERT(0);
        }
        _ASSERTE((0 == fclose(fp)));
    }
    ~FileImage()
    {
        delete[] bmi_buf;
        delete[] bits;
    }
    Graphics*& getGraphics()
    {
        return graphics;
    }
    int getWidth(ImageObserver* observer)
    {
        return bmih->biWidth;
    }
    int getHeight(ImageObserver* observer)
    {
        return bmih->biHeight;
    }
    ImageProducer*& getSource()
    {
        return producer; // this
    }
    void flush()
    {
    }
    // ImageProducer
    virtual void addConsumer(ImageConsumer* ic)
    {
        this->consumer = ic;
    }
    virtual void startProduction(ImageConsumer* ic)
    {
        addConsumer(ic);
        if ((1 == bmih->biPlanes) && (24 == bmih->biBitCount))
        {
            DirectColorModel cm(24, 0x00ff0000, 0x0000ff00, 0x000000ff);
            ic->setPixels(0, 0, bmih->biWidth, height, &cm, bits, 0, width_bytes);
        }
        else
        if ((1 == bmih->biPlanes) && (8 == bmih->biBitCount))
        {
            int r[256], g[256], b[256];
            int i, cnt = (0 != bmih->biClrUsed) ? bmih->biClrUsed : bmih->biPlanes * bmih->biBitCount;
            for (i = 0; i < cnt; ++ i)
            {
                r[i] = bmi->bmiColors[i].rgbRed;
                g[i] = bmi->bmiColors[i].rgbGreen;
                b[i] = bmi->bmiColors[i].rgbBlue;
            }
            IndexColorModel cm(8, cnt, r, g, b);
            ic->setPixels(0, 0, bmih->biWidth, height, &cm, bits, 0, width_bytes);
        }
        else
        {
            _ASSERT(0);
        }
    }
};

/*------------------------------------------------------------*/

URL Applet::getCodeBase()
{
    char path[_MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR];
    GetModuleFileName(NULL, path, sizeof(path));
    _splitpath(path, drive, dir, NULL, NULL);
    _makepath(path, drive, dir, NULL, NULL);
    return URL(path);
}

Image* Applet::getImage(URL* url, const char* name)
{
    return new FileImage(url->toString() + name);
}

void Applet::init()
{
}

void Applet::start()
{
}

void Applet::stop()
{
}

void Applet::destroy()
{
}

/*
 * $Id: JavaDF2Fractal.java,v 1.12 2008/03/06 16:43:59 matsushima Exp $
 */

/*J*/
package javadf2;

import java.util.Random;

import commons.JavaObject;
import commons.Log;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"
#include "../cpp2javalib/java.util.Random"
#include "Log.cpp"

class JavaDF2FractalStatic;
extern JavaDF2FractalStatic _JavaDF2FractalStatic;

#else // cpp

#define _IS_H_
#include "JavaDF2Fractal.cpp"
#undef _IS_H_

JavaDF2FractalStatic _JavaDF2FractalStatic;

#endif
/**/

/**
 * JavaDF2Fractal
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @version $Id: JavaDF2Fractal.java,v 1.12 2008/03/06 16:43:59 matsushima Exp $
 * 
 * $Log: JavaDF2Fractal.java,v $
 * Revision 1.12  2008/03/06 16:43:59  matsushima
 * JavaDoc/Doxygen ëŒâû
 *
 * Revision 1.14  2008/03/06 15:39:50  matsushima
 * h/cpp ã§í âª
 *
 * Revision 1.13  2008/03/04 17:21:01  matsushima
 * Java/C++ ã§í âª
 *
 * Revision 1.12  2007/12/01 22:14:14  matsushima
 * çƒìoò^
 *
 * Revision 1.11  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.10  2007/05/15 20:47:34  matsushima
 * no message
 *
 * Revision 1.9  2007/05/15 20:00:14  matsushima
 * çÇë¨âª
 *
 * Revision 1.7  2007/05/14 13:38:19  matsushima
 * Java/C++ ã§í âª
 *
 * Revision 1.5  2007/05/10 22:29:39  matsushima
 * Java/C++ ã§í âª
 *
 * Revision 1.2  2007/04/23 17:05:48  matsushima
 * ÉäÉvÉåÅ[ÉX
 *
 * Revision 1.1.1.1  2006/08/17 20:26:48  matsushima
 * new
 *
 */
/*J*/
public class JavaDF2Fractal extends JavaObject
{
/*C*
#ifdef _IS_H_
class JavaDF2FractalStatic
{
/**/
/*J*/
    public static int[] create(int m, double h, int max) {
/*C*
#endif
#ifdef _IS_H_
public:
    static int* create(int m, double h, int max);
#else
    int* JavaDF2FractalStatic::create(int m, double h, int max) {
        JSTATIC(System);
        JSTATIC(Math);
        JSTATIC(Log);
/**/
        long time = System.currentTimeMillis();
        int n = 1 << m;
Log.out(String("JavaDF2Fractal.create() : m = ") + m + ", max = " + max + ", n = 1 << m = " + n);
        int x, y;
        double/*C** /*J*/[]/**/ buf_real = new double[n * n];
        double/*C** /*J*/[]/**/ buf_imag = new double[n * n];
        double/*C** /*J*/[]/**/ tmp_real = new double[n * n];
        double/*C** /*J*/[]/**/ tmp_imag = new double[n * n];
        Random random/*J*/ = new Random()/**/;
        double phase, elem;

int YY=64;
        // Generate gauss
        int n_rand = 4;
        double gauss_add = Math.sqrt(3 * n_rand);
        double gauss_fac = 2 * gauss_add / n_rand;
        for (x = 0; x < n * n; ++ x)
        {
            buf_real[x] = 0;
            buf_imag[x] = 0;
        }
        for (x = 0; x <= n / 2; ++ x)
        {
            for (y = 0; y <= n / 2; ++ y)
            {
                phase = 2.0 * Math.PI * random.nextDouble();
                elem = ((x > 0) && (y > 0))
                    ? Math.pow((x * x) + (y * y), - (h + 1) / 2) * gauss(random, n_rand, gauss_add, gauss_fac)
                    : 0;
                double cos = elem * Math.cos(phase);
                double sin = elem * Math.sin(phase);
                if ((x <= YY) && (y <= YY))
                {
                    buf_real[x + y * n] = cos;
                    buf_imag[x + y * n] = sin;
//chkbuf*/buf_real[x + y * n] = 1;
                    int x2 = (0 == x) ? 0 : n - x;
                    int y2 = (0 == y) ? 0 : n - y;
                    buf_real[x2 + y2 * n] = cos;
                    buf_imag[x2 + y2 * n] = - sin;
//chkbuf*/buf_real[x2 + y2 * n] = 1;
                }
            }
        }
        for (x = 1; x < n / 2; ++ x)
        {
            for (y = 1; y < n / 2; ++ y)
            {
                phase = 2.0 * Math.PI * random.nextDouble();
                elem = Math.pow((x * x) + (y * y), - (h + 1) / 2) * gauss(random, n_rand, gauss_add, gauss_fac);
                double cos = elem * Math.cos(phase);
                double sin = elem * Math.sin(phase);
                if ((x < YY) && (y < YY))
                {
                    buf_real[x + (n - y) * n] = cos;
                    buf_imag[x + (n - y) * n] = sin;
//chkbuf*/buf_real[x + (n - y) * n] = 1;
                    buf_real[(n - x) + y * n] = cos;
                    buf_imag[(n - x) + y * n] = - sin;
//chkbuf*/buf_real[(n - x) + y * n] = 1;
                }
            }
        }
//chkbuf*/for (x = 0; x < n * n; ++ x)
//chkbuf*/{
//chkbuf*/    if (0 == buf_real[x])
//chkbuf*/    {
//chkbuf*/        Log.out(String("") + (x % n) + "," + (x / n));
//chkbuf*/    }
//chkbuf*/}

        // FFT
        fft2(buf_real, buf_imag, tmp_real, tmp_imag, n, m);

        // Output
        double elem_max = 0, elem_min = 0;
        for (x = 0; x < n; ++ x)
        {
            for (y = 0; y < n; ++ y)
            {
                double elem_real = buf_real[x + y * n];
                //double elem_imag = buf_imag[x + y * n];
//                    double elem = Math.sqrt(elem_real * elem_real + elem_imag * elem_imag);
//                    double elem = Math.pow(elem_real, 1.1);
                elem = elem_real;
                if ((0 == x) && (0 == y))
                {
                    elem_max = elem_min = 0;
                }
                else
                {
                    if (elem_max < elem)
                    {
                        elem_max = elem;
                    }
                    if (elem_min > elem)
                    {
                        elem_min = elem;
                    }
                }
                buf_real[x + y * n] = elem;
            }
        }
        int/*C** /*J*/[]/**/ buf = new int[n * n];
        for (x = 0; x < n; ++ x)
        {
            for (y = 0; y < n; ++ y)
            {
                elem = buf_real[x + y * n];
                elem = (elem - elem_min) * max / (elem_max - elem_min);
                buf[x + y * n] = (int)elem;
            }
        }
        jdelete(buf_real);
        jdelete(buf_imag);
        jdelete(tmp_real);
        jdelete(tmp_imag);
time = System.currentTimeMillis() - time;
Log.out(String("> elem_max = ") + elem_max + ", elem_min = " + elem_min + ", time = " + time + "ms");
        return buf;
    }

/*J*/
    private static double gauss(Random random, int n_rand, double gauss_add, double gauss_fac) {
/*C*
#endif
#ifdef _IS_H_
private:
    static double gauss(Random& random, int n_rand, double gauss_add, double gauss_fac);
#else
    double JavaDF2FractalStatic::gauss(Random& random, int n_rand, double gauss_add, double gauss_fac) {
/**/
        double sum = 0;
        int i;
        for (i = 0; i < n_rand; ++ i)
        {
            sum += random.nextDouble();
        }
        return gauss_fac * sum - gauss_add;
    }

/*J*/
    private static void fft1(double[] buf1_real, double[] buf1_imag, double[] tmp1_real, double[] tmp1_imag, int n, int m) {
/*C*
#endif
#ifdef _IS_H_
private:
    static void fft1(double* buf1_real, double* buf1_imag, double* tmp1_real, double* tmp1_imag, int n, int m);
#else
    void JavaDF2FractalStatic::fft1(double* buf1_real, double* buf1_imag, double* tmp1_real, double* tmp1_imag, int n, int m) {
        JSTATIC(Math);
/**/
        int i, j, x, y;
        for (i = 1, j = n / 2; i <= n / 2; i *= 2, j /= 2)
        {
            for (x = 0; x < j; ++ x)
            {
                double cos = Math.cos(2 * Math.PI * i * x / n);
                double sin = Math.sin(2 * Math.PI * i * x / n);
                for (y = 0; y < i; ++ y)
                {
                    double a_real = buf1_real[x + j * 2 * y];
                    double a_imag = buf1_imag[x + j * 2 * y];
                    double b_real = buf1_real[x + j * 2 * y + j];
                    double b_imag = buf1_imag[x + j * 2 * y + j];
                    buf1_real[x + j * 2 * y] = a_real + b_real;
                    buf1_imag[x + j * 2 * y] = a_imag + b_imag;
                    buf1_real[x + j * 2 * y + j] = (a_real - b_real) * cos - (a_imag - b_imag) * sin;
                    buf1_imag[x + j * 2 * y + j] = (a_imag - b_imag) * cos + (a_real - b_real) * sin;
                }
            }
        }
        for (i = 0; i < n; ++ i)
        {
            int k = 0;
            for (j = 0; j < m; j ++)
            {
                k = (k << 1) | ((i >> j) & 1);
            }
            tmp1_real[i] = buf1_real[k];
            tmp1_imag[i] = buf1_imag[k];
        }
        for (i = 0; i < n; ++ i)
        {
            buf1_real[i] = tmp1_real[i] / n;
            buf1_imag[i] = tmp1_imag[i] / n;
        }
    }

/*J*/
    private static void fft2(double[] buf_real, double[] buf_imag, double[] tmp_real, double[] tmp_imag, int n, int m) {
/*C*
#endif
#ifdef _IS_H_
private:
    static void fft2(double* buf_real, double* buf_imag, double* tmp_real, double* tmp_imag, int n, int m);
#else
    void JavaDF2FractalStatic::fft2(double* buf_real, double* buf_imag, double* tmp_real, double* tmp_imag, int n, int m) {
/**/
        double/*C** /*J*/[]/**/ buf1_real = new double[n];
        double/*C** /*J*/[]/**/ buf1_imag = new double[n];
        double/*C** /*J*/[]/**/ tmp1_real = new double[n];
        double/*C** /*J*/[]/**/ tmp1_imag = new double[n];
        int x, y;
//chkbuf*/for (x = 0; x < n; ++ x)
//chkbuf*/{
//chkbuf*/    buf1_real[x] = 0;
//chkbuf*/    buf1_imag[x] = 0;
//chkbuf*/    tmp1_real[x] = 0;
//chkbuf*/    tmp1_imag[x] = 0;
//chkbuf*/}
        for (x = 0; x < n; ++ x)
        {
            for (y = 0; y < n; ++ y)
            {
                buf1_real[y] = buf_real[x + y * n];
                buf1_imag[y] = buf_imag[x + y * n];
            }
            fft1(buf1_real, buf1_imag, tmp1_real, tmp1_imag, n, m);
            for (y = 0; y < n; ++ y)
            {
                tmp_real[x + y * n] = buf1_real[y];
                tmp_imag[x + y * n] = buf1_imag[y];
            }
        }
//chkbuf*/for (x = 0; x < n; ++ x)
//chkbuf*/{
//chkbuf*/    buf1_real[x] = 0;
//chkbuf*/    buf1_imag[x] = 0;
//chkbuf*/    tmp1_real[x] = 0;
//chkbuf*/    tmp1_imag[x] = 0;
//chkbuf*/}
        for (y = 0; y < n; ++ y)
        {
            for (x = 0; x < n; ++ x)
            {
                buf1_real[x] = tmp_real[x + y * n];
                buf1_imag[x] = tmp_imag[x + y * n];
            }
            fft1(buf1_real, buf1_imag, tmp1_real, tmp1_imag, n, m);
            for (x = 0; x < n; ++ x)
            {
                buf_real[x + y * n] = buf1_real[x];
                buf_imag[x + y * n] = buf1_imag[x];
            }
        }
        jdelete(buf1_real);
        jdelete(buf1_imag);
        jdelete(tmp1_real);
        jdelete(tmp1_imag);
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
};

class JavaDF2Fractal : public JavaDF2FractalStatic
{
};
#endif
/**/

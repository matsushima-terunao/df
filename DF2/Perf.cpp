/*
 * $Id: Perf.cpp,v 1.19 2008/03/12 16:30:47 matsushima Exp $
 */

/*J*
package commons;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"

class PerfStatic;
extern PerfStatic _PerfStatic;

#else // cpp

#define _IS_H_
#include "Perf.cpp"
#include "Log.cpp"
#include <windows.h>
#undef _IS_H_

PerfStatic _PerfStatic;

#endif
/**/

/**
 * パフォーマンス計測。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @author  1.1 2007/04/17 matsushima Perf
 * @version $Id: Perf.cpp,v 1.19 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: Perf.cpp,v $
 * Revision 1.19  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.18  2008/03/06 16:42:46  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.17  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.16  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.15  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.14  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.13  2007/05/14 13:38:21  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.10  2007/05/11 09:01:40  matsushima
 * パフォーマンス測定
 *
 * Revision 1.8  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.5  2007/05/09 20:54:38  matsushima
 * パフォーマンス測定
 *
 * Revision 1.3  2007/05/05 18:06:03  matsushima
 * clear アセンブラ
 *
 * Revision 1.1  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 */
/*J*
public class Perf extends JavaObject
{
/*C*/
#ifdef _IS_H_
class PerfStatic : public Object
{
#endif
/**/
/*J*
    public static String getTitle() {
/*C*/
#ifdef _IS_H_
public:
    static String getTitle();
#else
    String PerfStatic::getTitle() {
/**/
        return
            format("time ms", 8) + "," +
            format("span us", 8) +
            format("count", 8) + "," +
            format("span ns", 8) +
            format("count", 8);
    }
/*C*/
#endif
/**/

/*J*
    private static String format(long count, long time) {
/*C*/
#ifdef _IS_H_
protected:
    static String format(long count, __int64 time);
#else
    String PerfStatic::format(long count, __int64 time) {
/**/
        return
            format((0 == count) ? "-" : String((long)(time / count)), 8) +
            format(String(count), 8);
    }
/*C*/
#endif
/**/

/*J*
    private static String format(String str, int len) {
/*C*/
#ifdef _IS_H_
protected:
    static String format(String str, int len);
#else
    String PerfStatic::format(String str, int len) {
/**/
        if (str.length() >= len)
        {
            return str;
        }
        String res = "                    " + str;
        return res.substring(res.length() - len);
    }

/*J*
    public long time, count1, count2, start_time, start_count, span;
    public double span_ave;
    public boolean skip_count;
/*C*/
#endif
#ifdef _IS_H_
};

/**
 * パフォーマンス計測。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @author  1.1 2007/04/17 matsushima Perf
 * @version $Id: Perf.cpp,v 1.19 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: Perf.cpp,v $
 * Revision 1.19  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.18  2008/03/06 16:42:46  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.17  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.16  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.15  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.14  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.13  2007/05/14 13:38:21  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.10  2007/05/11 09:01:40  matsushima
 * パフォーマンス測定
 *
 * Revision 1.8  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.5  2007/05/09 20:54:38  matsushima
 * パフォーマンス測定
 *
 * Revision 1.3  2007/05/05 18:06:03  matsushima
 * clear アセンブラ
 *
 * Revision 1.1  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 */
class Perf : public PerfStatic
{
public:
    long time, count1, count2, start_time, start_count, span;
    __int64 pc_time, pc_start_time, pc_freq;
    double span_ave;
    boolean skip_count;
#endif
/**/

/*J*
    public Perf() {
/*C*/
#ifdef _IS_H_
public:
    Perf();
#else
    Perf::Perf() {
        pc_time = pc_start_time = 0;
        QueryPerformanceFrequency((LARGE_INTEGER*)&pc_freq);
/**/
        time = count1 = count2 = start_time = start_count = span = 0;
        span_ave = 0;
        skip_count = false;
    }
/*C*/
#endif
/**/

/*J*
    public void start() {
/*C*/
#ifdef _IS_H_
public:
    virtual void start();
#else
    void Perf::start() {
        QueryPerformanceCounter((LARGE_INTEGER*)&pc_start_time);
/**/
        start_time = System::currentTimeMillis();
        ++ start_count;
    }
/*C*/
#endif
/**/

/*J*
    public void end() {
/*C*/
#ifdef _IS_H_
public:
    virtual void end();
#else
    void Perf::end() {
/**/
        if (false != skip_count)
        {
            skip_count = false;
            return;
        }
/*C*/
        __int64 pc_t;
        QueryPerformanceCounter((LARGE_INTEGER*)&pc_t);
        pc_time += pc_t - pc_start_time;
        pc_start_time = pc_t;
/**/
        long t = System::currentTimeMillis();
        span = t - start_time;
        double rate = (double)(30 - count1) / 30;
        rate = (rate >= 0.05) ? rate : 0.05;
        span_ave = span_ave * (1 - rate) + span * rate;
        time += span;
        start_time = t;
        ++ count1;
    }
/*C*/
#endif
/**/

/*J*
    public void count() {
/*C*/
#ifdef _IS_H_
public:
    virtual void count();
#else
    void Perf::count() {
/**/
        ++ count2;
    }
/*C*/
#endif
/**/

/*J*
    public String toString() {
/*C*/
#ifdef _IS_H_
public:
    virtual String toString();
#else
    String Perf::toString() {
/**/
/*C*/
        __int64 pc_time2 = (__int64)pc_time * 1000000000 / pc_freq;
        String result = format(String((long)(pc_time2 / 1000000)), 8) + ";";
        if ((0 != count2) && (count2 != count1))
        {
            if (count1 < count2)
            {
                result += format(count1, pc_time2 / 1000) + ",";
                result += format(count2, pc_time2);
            }
            else
            {
                result += format(count2, pc_time2 / 1000) + ",";
                result += format(count1, pc_time2);
            }
        }
        else
        {
            result += format(count1, pc_time2 / 1000) + ",";
            result += format("", 16);
        }
        result += ";";
/*J*
        long time2 = time * 1000000;
        String result = format(String(time2 / 1000000), 8) + ";";
/*C*/
        __int64 time2 = (__int64)time * 1000000;
/**/
        if ((0 != count2) && (count2 != count1))
        {
            if (count1 < count2)
            {
                result += format(count1, time2 / 1000) + ",";
                result += format(count2, time2);
            }
            else
            {
                result += format(count2, time2 / 1000) + ",";
                result += format(count1, time2);
            }
        }
        else
        {
            result += format(count1, time2 / 1000) + ",";
            result += format("", 16);
        }
        return result;
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
//public:
//    operator String() { return toString(); }
};
//
//static String operator+(String& value, Perf& perf)
//{
//    return value + (String)perf;
//}
#endif
/**/

/*
 * $Id: Log.cpp,v 1.10 2008/03/12 16:30:47 matsushima Exp $
 */

/*J*
package commons;

/*C*/
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"

#else // cpp

#define _IS_H_
#include "Log.cpp"
#include <windows.h>
#undef _IS_H_

#endif
/**/

/**
 * ログ出力。
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @author  1.1 2007/04/17 matsushima Log
 * @version $Id: Log.cpp,v 1.10 2008/03/12 16:30:47 matsushima Exp $
 * 
 * $Log: Log.cpp,v $
 * Revision 1.10  2008/03/12 16:30:47  matsushima
 * Doxygen 対応
 *
 * Revision 1.9  2008/03/06 16:42:46  matsushima
 * JavaDoc/Doxygen 対応
 *
 * Revision 1.8  2008/03/06 15:39:50  matsushima
 * h/cpp 共通化
 *
 * Revision 1.7  2008/03/04 17:21:01  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.6  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.5  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.4  2007/05/14 13:38:21  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.3  2007/05/10 22:29:39  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.1  2007/04/23 17:05:48  matsushima
 * リプレース
 *
 */
/*J*
public class Log
{
/*C*/
#ifdef _IS_H_
class Log
{
#else
#define fopen my_fopen
static FILE* my_fopen(const char* fname, const char* mode)
{
	FILE* fp;
	fopen_s(&fp, fname, mode);
	return fp;
}
#endif
/**/
/*J*
    public static void out(Object s) {
/*C*/
#ifdef _IS_H_
public:
    static void out(const char* s);
#else
    void Log::out(const char* s) {
/**/
/*J*
        try
        {
            throw new Exception();
        }
        catch (Exception e)
        {
            String line = e.getStackTrace()[1].toString();
            int l = (63 - line.length()) / 8;
            if (l > 0)
            {
                line += "\t\t\t\t\t\t\t\t".substring(0, l);
            }
            //String line = e.getStackTrace()[1].getFileName() + ":" + e.getStackTrace()[1].getLineNumber();
            System.out.println(line + ": " + s);
        }
/*C*/
OutputDebugString(s);
OutputDebugString("\n");
        //FILE* fp = fopen("log.txt", "at");
        //fprintf(fp, "%s\n", s);
        //fclose(fp);
/**/
    }
/*J*
}
/*C*/
#endif
#ifdef _IS_H_
    static void out(Object o) { out((const char*)o.toString()); }
    static void out(String s) { out((const char*)s); }
};
#endif
/**/

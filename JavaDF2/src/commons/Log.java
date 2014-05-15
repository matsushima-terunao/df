/*
 * $Id: Log.java,v 1.9 2008/03/06 16:44:00 matsushima Exp $
 */

/*J*/
package commons;

/*C*
#ifdef _IS_H_ // h
#pragma once

#include "../cpp2javalib/cpp2javalib.h"

class LogStatic;
extern LogStatic _LogStatic;

#else // cpp

#define _IS_H_
#include "Log.cpp"
#include <windows.h>
#undef _IS_H_

LogStatic _LogStatic;

#endif
/**/

/**
 * ���O�o�́B
 * 
 * @since   1.0 matsushima
 * @author  1.0 matsushima
 * @author  1.1 2007/04/17 matsushima Log
 * @version $Id: Log.java,v 1.9 2008/03/06 16:44:00 matsushima Exp $
 * 
 * $Log: Log.java,v $
 * Revision 1.9  2008/03/06 16:44:00  matsushima
 * JavaDoc/Doxygen �Ή�
 *
 * Revision 1.8  2008/03/06 15:39:50  matsushima
 * h/cpp ���ʉ�
 *
 * Revision 1.7  2008/03/04 17:21:01  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.6  2007/05/23 09:57:53  matsushima
 * no message
 *
 * Revision 1.5  2007/05/14 18:47:52  matsushima
 * no message
 *
 * Revision 1.4  2007/05/14 13:38:21  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.3  2007/05/10 22:29:39  matsushima
 * Java/C++ ���ʉ�
 *
 * Revision 1.1  2007/04/23 17:05:48  matsushima
 * ���v���[�X
 *
 */
/*J*/
public class Log
{
/*C*
#ifdef _IS_H_
class LogStatic
{
/*J*/
    public static void out(Object s) {
/*C*
#endif
#ifdef _IS_H_
public:
    static void out(_String s);
#else
    void LogStatic::out(_String s) {
/**/
/*J*/
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
/*C*
OutputDebugString(s);
OutputDebugString("\n");
        FILE* fp = fopen("log.txt", "at");
        fprintf(fp, "%s\n", s);
        fclose(fp);
/**/
    }
/*J*/
}
/*C*
#endif
#ifdef _IS_H_
    static void out(Object o) { out((_String)o.toString()); }
    static void out(String s) { out((_String)s); }
};

class Log : public LogStatic
{
};
#endif
/**/

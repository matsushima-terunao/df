/**
 * $Id: JavaObject.java,v 1.6 2007/11/29 17:32:54 matsushima Exp $
 */

package commons;

/**
 * JavaObject
 * 
 * @author  1.0 2007/05/09 matsushima
 * @version $Id: JavaObject.java,v 1.6 2007/11/29 17:32:54 matsushima Exp $
 * @since   1.0 2007/05/09 matsushima
 * 
 * $Log: JavaObject.java,v $
 * Revision 1.6  2007/11/29 17:32:54  matsushima
 * 再登録
 * ディレクトリ構成変更
 *
 * Revision 1.5  2007/05/14 13:38:44  matsushima
 * Java/C++ 共通化
 *
 * Revision 1.4  2007/05/14 05:22:04  matsushima
 * no message
 *
 * Revision 1.3  2007/05/11 03:36:16  matsushima
 * no message
 *
 * Revision 1.2  2007/05/09 21:17:17  matsushima
 * no message
 *
 * Revision 1.1  2007/05/09 12:58:29  matsushima
 * new
 *
 */
public class JavaObject
{
/*J*/
    public static <T> void jdelete(T p) { }
    public static <T> T _R(T p) { return p; }
    public static String String() { return ""; }
    public static String String(String s) { return s; }
    public static String String(Object o) { return o.toString(); }
    public static double fmod(double d, double s) { return d % s; }
/**/
}

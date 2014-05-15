package matsushima.java2cppc;

/**
 * Java -> C++ 変換 テストクラス。
 * 
 * @author  0.0.1.001 2010/05/07 matsushima
 * @version 0.0.1.001 2010/05/07 matsushima
 * @since   0.0.1.001 2010/05/07 matsushima
 * 
 * $Id: TestJava.java,v 1.5 2010/05/23 18:36:37 matsushima Exp $
 * $Log: TestJava.java,v $
 * Revision 1.5  2010/05/23 18:36:37  matsushima
 * 検索
 *
 * Revision 1.4  2010/05/20 14:05:15  matsushima
 * 解析定義の読み込み共通化
 *
 * Revision 1.2  2010/05/13 13:41:14  matsushima
 * 構文解析定義読み込み
 *
 * Revision 1.1  2010/05/06 16:05:54  matsushima
 * 構文解析
 *
 */
public class TestJava {

    protected static class MyClass {
        
    }

    public static void main(String[] args) {
        for (int i = 0; i < 10; ++ i) ;
        System.out.println("abc");
//        int result = args.length == 1 ? 1 : 2;
//        assert result == 1;
//        if (result == 1) return;
    }
}

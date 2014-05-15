package matsushima.java2cppc;

import java.io.File;
import java.io.FileReader;
import java.io.OutputStreamWriter;

import matsushima.common.cc.Lexer;
import matsushima.common.cc.Parser;
import matsushima.common.cc.Parser.TokenNode;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Java -> C++ 変換。
 * 
 * @author  1.0 2005/03/16 matsushima h2javac
 * @author  1.1 2006/07/12 matsushima cpp2javac
 * @author  0.0.1.001 2010/04/29 matsushima
 * @version 0.0.1.001 2010/04/29 matsushima
 * @since   0.0.1.001 2010/04/29 matsushima
 * 
 * $Id: Java2CppC.java,v 1.5 2010/05/14 19:59:41 matsushima Exp $
 * $Log: Java2CppC.java,v $
 * Revision 1.5  2010/05/14 19:59:41  matsushima
 * *** empty log message ***
 *
 * Revision 1.4  2010/05/06 16:05:54  matsushima
 * 構文解析
 *
 * Revision 1.3  2010/05/05 15:25:20  matsushima
 * 構文解析完了
 *
 * Revision 1.2  2010/05/03 19:25:27  matsushima
 * 構文解析
 *
 * Revision 1.1  2010/05/01 20:20:41  matsushima
 * 新規
 * 字句解析
 * 構文解析(ハードコーディング)
 *
 */
public class Java2CppC {

    enum A {
        _PackageDeclaration
    }

    /*
     * ログ。
     */
    private static final Log log = LogFactory.getLog(Java2CppC.class);

    private static Parser.TraceNodeCallback callback = new Parser.TraceNodeCallback() {
        @Override
        protected void traceNode(
                final TokenNode node,
                final int indent) {
            if (null == node.def) {
            } else if (node.def.ref) {
//            } else if (node.def.key.equals("_PackageDeclaration")) {
            } else {
                switch (A.valueOf("_PackageDeclaration")) {
                case _PackageDeclaration:
                    log.debug(node);
                }
            }
        }
    };

    /**
     * @param args
     */
    public static void main(String[] args) {
        try {
            String path = System.getProperty("user.dir");
            Lexer lexer = new Lexer();
            lexer.lex(
                    new FileReader(new File(path, "bin/matsushima/java2cppc/lexer.txt")),
                    new FileReader(new File(path, "src/matsushima/java2cppc/TestJava.java")));
            Parser parser = new Parser();
            parser.parse(
                    new FileReader(new File(path, "src/matsushima/java2cppc/parser.txt")),
                    lexer);
            parser.traceNode(callback);
            parser.outputNode(
                    //new OutputStreamWriter(new FileOutputStream(new File("C:/", "parser.txt")), "UTF-8"));
                    new OutputStreamWriter(System.out));
        } catch (Throwable e) {
            log.error("Java2CppC", e);
        }
    }
}

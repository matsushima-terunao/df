package matsushima.common.cc;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * 字句解析。
 * 
 * @author  1.0 2005/03/16 matsushima h2javac
 * @author  1.1 2006/07/19 matsushima cpp2javac
 * @author  0.0.1.001 2010/04/29 matsushima
 * @version 0.0.1.001 2010/04/29 matsushima
 * @since   0.0.1.001 2010/04/29 matsushima
 * 
 * $Id: Lexer.java,v 1.7 2010/05/21 16:56:49 matsushima Exp $
 * $Log: Lexer.java,v $
 * Revision 1.7  2010/05/21 16:56:49  matsushima
 * ノードの共通化
 *
 * Revision 1.6  2010/05/20 14:05:15  matsushima
 * 解析定義の読み込み共通化
 *
 * Revision 1.5  2010/05/19 14:59:02  matsushima
 * 字句解析定義を読み込み修正
 *
 * Revision 1.4  2010/05/13 13:41:15  matsushima
 * 構文解析定義読み込み
 *
 * Revision 1.3  2010/05/05 15:25:20  matsushima
 * 構文解析完了
 *
 * Revision 1.2  2010/05/03 19:25:27  matsushima
 * 構文解析
 *
 * Revision 1.1  2010/05/01 20:20:40  matsushima
 * 新規
 * 字句解析
 * 構文解析(ハードコーディング)
 *
 */
public class Lexer {

    /*
     * ログ。
     */
    private final Log log_readdef = getLog("readTokenDefinition");
    private final Log log_lexsrc = getLog("lexSource");
    private final Log log_gettoken = getLog("getNextTokenIndex");
    private final Log log_gettoken_skip = getLog("skip_getNextTokenIndex");

    private Log getLog(final String name) {
        return LogFactory.getLog("$" + getClass().getName() + "." + name);
    }

    /**
     * 字句解析定義。
     */
    public static class TokenDefinition extends Node<TokenDefinition> {
        public String key;
        public String value;
        public String comment;
        public Pattern pattern;
        @Override
        public String toString() {
            return key + ", " + value + ", " + comment;
        }
    }

    /**
     * 字句解析定義にマッチしたトークン。
     */
    public static class Token extends Node<Token> {
        public TokenDefinition tokendef;
        public String text;
        @Override
        public String toString() {
            //return String.format("%-16s,%3d, %s", tokendef.key, text.length(), text);
            return tokendef.key + "\"" + text + "\"";
        }
    }

    /** 字句解析定義のリスト。 */
    private final TokenDefinition tokendefs = new TokenDefinition();

    /** 字句解析定義にマッチしたトークンのリスト。 */
    private Token tokens = new Token();

    /**
     * 次の有効なトークンを取得する。
     * 
     * @param token
     * @return
     */
    public Token getNextToken(
            Token token) {
        if (null == token) {
            token = tokens.getChild();
        } else {
            token = token.getNext();
        }
        for (; null != token; token = token.getNext()) {
            if ("space".equals(token.tokendef.key)
                    || "comment_block".equals(token.tokendef.key)
                    || "comment_line".equals(token.tokendef.key)) {
log_gettoken_skip.debug("> skip: " + token);
            } else {
log_gettoken.debug("> " + token);
                return token;
            }
        }
//log_gettoken.error(token);
//        throw new RuntimeException();
        return token;
    }

    /**
     * 字句解析を行う。
     * 
     * @param lexer
     * @param src
     * @throws IOException
     */
    public void lex(
            final Reader lexer,
            final Reader src)
            throws IOException {
        readTokenDefinition(lexer);
        lexSource(src);
    }

    /**
     * 字句解析定義を読み込む。
     * 
     * @param in
     * @throws IOException
     */
    public void readTokenDefinition(
            final Reader in)
            throws IOException {
        // 解析定義を読み込み。
        DefinitionReader reader = new DefinitionReader() {

            TokenDefinition def_key = null;

            /**
             * 行の key と value を解析する。
             * 
             * @param line
             * @param index
             * @param comment
             * @param p_key
             * @param p_value
             * @return
             */
            @Override
            protected boolean parseKeyAndValueLine(
                    String line,
                    int index,
                    String comment,
                    Pattern p_key,
                    Pattern p_value) {
                // key
                Matcher m = p_key.matcher(line); // [key : ]value // line_comment
                boolean b = m.lookingAt();
                if (b) {
                    def_key = new TokenDefinition(); // [(key) : ]value // line_comment
                    def_key.key = m.group(1);
                    def_key.comment = comment;
                    comment = null;
                    index = m.end();
                } else {
log_readdef.debug("skip key");
                    if (null == def_key) {
                        // key: の行に到達していない
log_readdef.debug("skip key, continue");
                        return true;//continue line;
                    }
                }
                // value
                m = p_value.matcher(line); // key : [value ]// line_comment
                m.region(index, line.length());
                b = m.lookingAt();
                if (b) {
                    String value_str = m.group(1);
log_readdef.debug("< matcher.group(1): " + value_str);
                    def_key.value = value_str;
                    def_key.pattern = Pattern.compile(value_str);
                    tokendefs.add(def_key);
log_readdef.debug("> " + def_key);
                    String key = def_key.key;
                    def_key = new TokenDefinition();
                    def_key.key = key;
                }
                return true;//continue line;
            }
        };
log_readdef.debug("---> Lexer.readTokenDefinition(): begin");
        reader.readDefinition(in, log_readdef);
log_readdef.debug("<--- Lexer.readTokenDefinition(): end");
}

    /**
     * 字句解析を行う。
     * 
     * @param in
     * @throws IOException
     */
    public void lexSource(
            final Reader in)
            throws IOException {
        try {
log_lexsrc.debug("---> Lexer.lexSource(): start");

            // read src
            BufferedReader bin = null;
            StringBuilder src = new StringBuilder();
            try {
                bin = new BufferedReader(in);
                String line;
                while (null != (line = bin.readLine())) {
                    src.append(line).append("\n");
                }
            } finally {
                if (null != bin) {
                    bin.close();
                }
                in.close();
            }

            // lex
            int index = 0;
            loop:
            while (true) {
                if (index >= src.length()) {
                    break;
                }
                for (TokenDefinition tokendef: tokendefs) {
                    Matcher m = tokendef.pattern.matcher(src);
                    m.region(index, src.length());
                    boolean b = m.lookingAt();
                    if (b) {
                        index = readSrcCallback(src, tokendef, m.start(), m.end());
                        Token token = new Token();
                        token.tokendef = tokendef;
                        token.text = src.substring(m.start(), index);
                        tokens.add(token);
                        log_lexsrc.debug(token);
                        continue loop;
                    }
                }
                break;
            }
        } finally {
log_lexsrc.debug("<--- Lexer.lexSource(): end");
        }
    }

    /**
     * 字句解析のコールバック。
     * 
     * @param src
     * @param tokendef
     * @param start
     * @param end
     * @return
     */
    protected int readSrcCallback(
            final StringBuilder src,
            final TokenDefinition tokendef,
            final int start,
            final int end) {
        return end;
    }
}

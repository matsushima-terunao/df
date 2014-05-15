package matsushima.common.cc;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.Reader;
import java.io.Writer;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import matsushima.common.cc.Lexer.Token;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * 構文解析。
 * 
 * @author  1.0 2005/03/24 matsushima h2javac
 * @author  1.1 2006/07/19 matsushima cpp2javac
 * @author  0.0.1.001 2010/05/01 matsushima
 * @version 0.0.1.001 2010/05/01 matsushima
 * @since   0.0.1.001 2010/05/01 matsushima
 * 
 * $Id: Parser.java,v 1.13 2010/05/23 18:36:42 matsushima Exp $
 * $Log: Parser.java,v $
 * Revision 1.13  2010/05/23 18:36:42  matsushima
 * 検索
 *
 * Revision 1.12  2010/05/22 17:05:04  matsushima
 * Node の AbstractSequentialList 派生
 *
 * Revision 1.11  2010/05/21 16:56:49  matsushima
 * ノードの共通化
 *
 * Revision 1.10  2010/05/20 14:05:15  matsushima
 * 解析定義の読み込み共通化
 *
 * Revision 1.9  2010/05/19 14:59:02  matsushima
 * 字句解析定義を読み込み修正
 *
 * Revision 1.6  2010/05/14 18:42:42  matsushima
 * 構文解析とノード出力
 *
 * Revision 1.5  2010/05/13 13:41:15  matsushima
 * 構文解析定義読み込み
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
public class Parser {

    /*
     * ログ。
     */
    private final Log log_readdef = getLog("readSyntaxDefinition");
    private final Log log_readdef_trace = getLog("trace_readSyntaxDefinition");
    private final Log log_parsesrc = getLog("parseSource");
    private final Log log_tracenode = getLog("traceNode");

    private Log getLog(final String name) {
        return LogFactory.getLog("$" + getClass().getName() + "." + name);
    }

    private StringBuilder spc(int indent) {
        StringBuilder s = new StringBuilder();
        s.append(indent);
        for (int j = 0; j < indent; ++ j) {
            s.append(" ");
        }
        return s;
    }

    /**
     * 構文解析定義。
     */
    public static class SyntaxDefinition extends Node<SyntaxDefinition> {
        public String key;
        public String comment;
        public boolean ref;
        @Override
        public String toString() {
            StringBuilder s = new StringBuilder(key);
            if (size() > 0) {
                s.append(": ").append(size());
                if (! ref) {
                    if (size() > 0) {
                        s.append("[");
                    }
                    int i = 0;
                    for (SyntaxDefinition node: this) {
                        ++ i;
                        s.append(node);
                    }
                    if (size() > 0) {
                        s.append("]");
                    }
                    if (size() != i) {
                        throw new AssertionError("if (getChildCount() != i): i = " + i + "; s = "+ s);
                    }
                }
            }
            return s.append((null == comment) ? "" : comment).toString();
        }
        public SyntaxDefinition(
                final SyntaxDefinition def,
                final String key) {
            super(def);
            this.key = key;
        }
    }

    /**
     * 構文解析定義にマッチしたノード。
     */
    public static class TokenNode extends Node<TokenNode> {
        public Lexer.Token token;
        public List<Lexer.Token> tokens = new LinkedList<Lexer.Token>();
        public SyntaxDefinition def;
        public String toString() {
            return "token = " + token + ", def = " + def;
        }
    }

    /**
     * 字句解析オブジェクト。
     */
    public Lexer lexer;

    /**
     * 構文解析定義。
     */
    private final SyntaxDefinition syntaxdef = new SyntaxDefinition(null, "root");

    /**
     * 構文解析定義にマッチしたノード。
     */
    public TokenNode node = null;

    /**
     * 構文解析を行う。
     * 
     * @param parser
     * @param lexer
     * @throws IOException
     */
    public void parse(
        final Reader parser,
        final Lexer lexer)
        throws IOException {
        this.lexer = lexer;
        readSyntaxDefinition(parser);
        parseSource();
    }

    /**
     * 構文解析定義を読み込む。
     * 
     * @param in
     * @throws IOException
     */
    public void readSyntaxDefinition(
            final Reader in)
            throws IOException {
        // 解析定義を読み込み。
        DefinitionReader reader = new DefinitionReader() {

            SyntaxDefinition def_key = null;
            SyntaxDefinition def1or = null;
            SyntaxDefinition def1and = null;
            SyntaxDefinition def = null;

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
                Matcher m = p_key.matcher(line); // [key : ]value value ... // line_comment
                boolean b = m.lookingAt();
                if (b) {
                    def_key = new SyntaxDefinition(syntaxdef, m.group(1)); // [(key) : ]value value ... // line_comment
                    def_key.comment = comment;
                    comment = null;
                    index = m.end();
                    def1or = null;
                    def = def_key;
                } else {
log_readdef.debug("skip key");
                    if (null == def_key) {
                        // key: の行に到達していない
log_readdef.debug("skip key, continue");
                        return true;//continue line;
                    }
                }
                def1and = new SyntaxDefinition(null, "(1");
                def = def1and;
                // value
                for (int value_col = 0; ; ++ value_col) {
                    m = p_value.matcher(line); // key : [value ]value ... // line_comment
                    m.region(index, line.length());
                    b = m.lookingAt();
                    if (b) {
log_readdef.trace("matcher: " + m);
                        // add new SyntaxDefinition
                        index = m.end();
                        String value_str = m.group(1);
log_readdef.debug("< matcher.group(1): " + value_str);
                        if (("(".equals(value_str)) || ("[".equals(value_str)) || ("{".equals(value_str))) {
                            // def <([{>
                            def = new SyntaxDefinition(def, value_str);
log_readdef.debug("added to def: " + def.getParent());
                        } else if ((")".equals(value_str)) || ("]".equals(value_str)) || ("}".equals(value_str))) {
                            // return to parent
                            def = def.getParent();
                            if ("|".equals(def.key)) {
                                def = def.getParent().getParent();
                            }
log_readdef.debug("def.getParent(): " + def);
                        } else if ("|".equals(value_str)) {
                            // def.getParent() <def2or|> def
                            //                      <def(2>
                            // aaa bbb |(1) ccc (ddd eee |(2) fff) |(3) ggg
                            if ((null == def.getParent()) // (1) values 直下(1 の初回 |
                                    || (! "|".equals(def.getParent().key))) { // (2) values 直下(1 より下の初回 |
                                // def <def2or|> <def2and(2> def.values
                                SyntaxDefinition def2or = new SyntaxDefinition(null, "|");
                                SyntaxDefinition def2and = new SyntaxDefinition(def2or, "(2");
                                for (SyntaxDefinition value: def) {
                                    def2and.add(value);
                                }
                                def.clear();
                                def.add(def2or);
log_readdef.debug("def <def2or|> <def2and(2> def.values: " + def);
                                def = def2and;
                            }
                            // def.getParent() <def((2)>
                            def = new SyntaxDefinition(def.getParent(), "(2");
log_readdef.debug("added to def.getParent(): " + def.getParent());
                        } else {
                            // add value
                            if ('"' == value_str.charAt(0)) {
                                value_str = m.group(2); // key : ["(value)" ]value ... // line_comment
                            }
                            new SyntaxDefinition(def, value_str);
log_readdef.debug("added to def: " + def);
                        }
                    } else {
                        // value loop end
                        if (0 == value_col) {
log_readdef.debug("skip values");
                        } else {
log_readdef.debug("def: " + def);
log_readdef.debug("def1and: " + def1and);
                            // add value list
                            // def_key def1or def1and def1and.value[0]
                            // parent  parent child   child
                            SyntaxDefinition parent = def_key;
                            if (def_key.size() >= 1) {
                                parent = def_key.getChild();
                                if (! "|1".equals(parent.key)) {
                                    // def_key [def1or] def1and
                                    def_key.clear();
                                    def1or = new SyntaxDefinition(def_key, "|1");
                                    def1or.add(parent);
                                }
                                parent = def_key.getChild();
                            }
                            //SyntaxDefinition child = (1 == def1and.values.size()) ? def1and.getChild() : def1and;
                            SyntaxDefinition child = def1and;
                            parent.add(child);
log_readdef.debug("added child to parent: " + parent);
                        }
                        return true;//continue line;
                    }
                }
            }
        };
log_readdef.debug("---> Parser.readSyntaxDefinition(): begin");
        reader.readDefinition(in, log_readdef);
        traceSyntaxDefinition();
log_readdef.debug("<--- Parser.readSyntaxDefinition(): end");
    }

    /**
     * 構文解析定義をトレースする。
     * 最適化とログ出力。
     */
    public void traceSyntaxDefinition() {
        traceSyntaxDefinition(syntaxdef, 0);
    }

    /**
     * 構文解析定義をトレースする。
     * 最適化とログ出力。
     * 
     * @param definition
     * @param indent
     */
    private void traceSyntaxDefinition(
            final SyntaxDefinition definition,
            final int indent) {
        // def.child が 1つなら def と置き換え
        SyntaxDefinition def = definition;
        if (! def.ref) {
            if (1 == def.size()) {
                if (("(1".equals(def.key)) || ("(2".equals(def.key))) {
                    SyntaxDefinition value = def.getChild();
                    def.getParent().set(def, value);
                    def = value;
                }
            }
        }
        // find reference
        if (indent >= 2) { // top(root, RootDeclaration:, Xxx:, ...) は除外
            for (SyntaxDefinition ref: syntaxdef) {
                if (def.key.equals(ref.key)) {
                    if (0 != def.size()) {
                        throw new AssertionError("if (0 != def.getChildCount()): def = " + def);
                    }
                    def.addNotSetParent(ref);
                    def.ref = true;
                    break;
                }
            }
        }
if (log_readdef_trace.isDebugEnabled()) {
log_readdef_trace.debug(spc(indent).append(def));
}
        // trace children
        if (! def.ref) {
            for (SyntaxDefinition value: def) {
            	
                traceSyntaxDefinition(value, indent + 1);
            }
        }
    }

    /**
     * 構文解析状態。
     */
    public static class ParseContext {
        public SyntaxDefinition def;
        public Lexer.Token token;
    }

    /**
     * 構文解析を行う。
     */
    private void parseSource() {
        try {
log_parsesrc.debug("---> Parser.parseSource(): begin");

            node = new TokenNode();
            ParseContext context = new ParseContext();
            context.token = lexer.getNextToken(context.token);
            LinkedList<ParseContext> context_stack = new LinkedList<ParseContext>();
            // token fragments: [token, token], token, ..., EOF
syntax:
            while (null != context.token) {
log_parsesrc.debug("<<< " + context.token);
                // try match token fragments vs any syntaxdef: syntaxdef: [def, def], def, ...
                SyntaxDefinition defs = syntaxdef.getChild();
                if ((defs.size() >= 1) && ("|1".equals(defs.getChild().key))) {
                    defs = defs.getChild();
                }
                for (SyntaxDefinition def: defs) {
                    // try match token fragments vs this syntaxdef.values.get("RootDeclaration").values
                    context.def = def;
                    Lexer.Token token0 = context.token;
                    if (parseSourceFragment(context, context_stack, 0, node)) {
                        if (def != context.def) {
                            throw new AssertionError("if (def != context.def): def = " + def + "; " + context.def);
                        }
                        if (context.token == token0) {
                            // match but no tokens: next def
log_parsesrc.debug(">>> match but no tokens: " + token0 + "; " + def);
                        } else {
                            // match: next token fragments
log_parsesrc.debug(">>> MATCHED: " + token0 + "; " + def);
                            continue syntax;
                        }
                    }
log_parsesrc.debug(">>> not matched: " + token0 + "; " + def);
                }
                // none of these token fragments vs any syntaxdef matched
                throw new RuntimeException("parse: token = " + context.token + "; def = " + context.def);
            }
        } finally {
log_parsesrc.debug("<--- Parser.parseSource(): end");
            traceNode(
                    new TraceNodeCallback() {
                        @Override
                        protected void traceNode(
                                final TokenNode node,
                                final int indent) {
                            if (log_tracenode.isDebugEnabled()) {
log_tracenode.debug(spc(indent).append(node.token).append("; ").append(node.def));
                            }
                            if (log_tracenode.isInfoEnabled()) {
                                if ((null != node.def) && (! node.def.ref)) {
                                    info:
                                    for (SyntaxDefinition ref1: syntaxdef) {
                                        if ("TraceDeclaration".equals(ref1.key)) {
                                            if ((1 == ref1.size()) && ('|' == ref1.getChild().key.charAt(0))) {
                                                ref1 = ref1.getChild();
                                            }
                                            for (SyntaxDefinition ref: ref1) {
                                                if (node.def.key.equals(ref.key)) {
                                                    String text = "???";
                                                    for (Lexer.Token token = node.token; ; token = token.getNext()) {
                                                        if ("IDENTIFIER".equals(token.tokendef.key)) {
                                                            text = token.text;
                                                            break;
                                                        }
                                                    }
log_tracenode.info(spc(indent).append(node.token.text).append("; ").append(text).append("; ").append(node.def));
                                                    break info;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    });
        }
    }

    /**
     * 構文解析を行う。
     * context.def.key または context.def.values の fragment と
     * token 以降の fragment との比較を行う。
     * tokens: [token, token, ...]
     *      token: key, value
     * syntaxdef: def, def, ...
     *      def: values
     *          values: [value, value, ...]
     *              value: key, value
     * 
     * @param context
     * @param context_stack
     * @param indent
     * @param node
     * @return
     */
    private boolean parseSourceFragment(
            final ParseContext context,
            final LinkedList<ParseContext> context_stack,
            final int indent,
            final TokenNode node) {
log_parsesrc.trace("< " + indent + ": " + context.token + "; " + context.def);
        if (null == context.token) {
            return false;
        }
        // 無限ループチェック
        Iterator<ParseContext> it = context_stack.iterator(); // last
        for (int i = 0; it.hasNext(); ++ i) { // last -> top
            ParseContext c = it.next();
            if ((i >= 1) && (c.token == context.token) && (c.def == context.def)) {
log_parsesrc.debug("loop detected: " + indent + ": " + context.token + "; " + context.def);
                return false;
            }
        }
        ParseContext c = new ParseContext();
        c.def = context.def;
        c.token = context.token;
        context_stack.push(c);
        // match
        boolean result = false;
        TokenNode new_node = new TokenNode();
        if (0 == context.def.size()) {
            // context.def_value.value vs token
            if (null == context.token) {
            } else if ((context.def.key.equals(context.token.tokendef.key))
                    || (context.def.key.equals(context.token.text))) {
                // matched
log_parsesrc.debug(">> accept: " + indent + ": " + context.token + "; " + context.def);
                Lexer.Token token = context.token;
                context.token = lexer.getNextToken(context.token);
                for (; token != context.token; token = token.getNext()) {
                    new_node.tokens.add(token);
                }
                result = true;
            }
        } else {
            // match values
            ParseContext context2 = new ParseContext();
            context2.token = context.token;
            boolean next_token = false;
            do {
                for (SyntaxDefinition def: context.def) { 
                    context2.def = def;
                    boolean res = parseSourceFragment(context2, context_stack, indent + 1, new_node);
                    if (res) {
                        if ('|' == context.def.key.charAt(0)) {
                            result = next_token = true;
                            break;
                        }
                    } else {
                        if ('(' == context.def.key.charAt(0)) {
                            result = next_token = false;
                            break;
                        } else if ("[".equals(context.def.key)) {
                            result = true;
                            next_token = false;
                            break;
                        } else if ("{".equals(context.def.key)) {
                            result = true;
                            next_token = false;
                            break;
                        }
                    }
                    result = next_token = (result || res);
                    // ref なら 1 回のみ
                    if (context.def.ref) {
                        break;
                    }
                }
                if (next_token) {
                    context.token = context2.token;
                }
            } while (("{".equals(context.def.key)) && (next_token));
        }
        context_stack.pop();
        if (result) {
if (log_parsesrc.isDebugEnabled()) {
log_parsesrc.debug(spc(indent).append(c.token).append("; ").append(c.def));
}
            new_node.token = c.token;
            new_node.def = c.def;
            node.add(new_node);
        } else {
if (log_parsesrc.isTraceEnabled()) {
log_parsesrc.trace(spc(indent).append(result).append(": ").append(c.token).append("; ").append(c.def));
}
        }
        return result;
    }

    /**
     * 構文解析結果をトレースする。
     * ログ出力。
     */
    public void traceNode(
            final TraceNodeCallback callback) {
log_tracenode.info("---> Parser.traceNode(): begin");
        traceNode(node, 0, callback);
log_tracenode.info("<--- Parser.traceNode(): end");
    }

    /**
     * 構文解析結果をトレースする。
     * ログ出力。
     * 
     * @param node
     * @param indent
     */
    private void traceNode(
            final TokenNode node,
            final int indent,
            final TraceNodeCallback callback) {
        callback.traceNode(node, indent);
        for (TokenNode child: node) {
            traceNode(child, indent + 1, callback);
        }
    }

    public static class TraceNodeCallback {
        protected void traceNode(
                final TokenNode node,
                final int indent) {
        }
    }

    /**
     * 構文解析結果を出力する。
     * 
     * @param out
     * @throws IOException
     */
    public void outputNode(
            final Writer out)
            throws IOException {
        Writer bout = null;
        try {
            bout = new BufferedWriter(out);
            outputNode(node, bout, 0);
        } finally {
            try {
                if (null != bout) {
                    bout.close();
                }
            } finally {
                out.close();
            }
        }
    }

    /**
     * 構文解析結果を出力する。
     * 
     * @param node
     * @param out
     * @param indent
     * @throws IOException
     */
    private void outputNode(
            final TokenNode node,
            final Writer out,
            final int indent)
            throws IOException {
        for (Token token: node.tokens) {
            out.write("[" + token.text.replace("\n", "\r\n") + "]");
        }
        for (TokenNode child: node) {
            outputNode(child, out, indent + 1);
        }
    }
}

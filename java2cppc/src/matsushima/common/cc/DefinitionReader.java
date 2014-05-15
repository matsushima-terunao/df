package matsushima.common.cc;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.logging.Log;

/**
 * 解析定義読み込み。
 * 
 * @author  0.0.1.001 2010/05/20 matsushima
 * @version 0.0.1.001 2010/05/20 matsushima
 * @since   0.0.1.001 2010/05/20 matsushima
 * 
 * $Id: DefinitionReader.java,v 1.2 2010/05/23 18:36:43 matsushima Exp $
 * $Log: DefinitionReader.java,v $
 * Revision 1.2  2010/05/23 18:36:43  matsushima
 * 検索
 *
 */
public abstract class DefinitionReader {

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
    protected abstract boolean parseKeyAndValueLine(
            String line,
            int index,
            String comment,
            Pattern p_key,
            Pattern p_value);

    /**
     * 定義を読み込む。
     * 
     * @param in
     * @throws IOException
     */
    public void readDefinition(
            final Reader in,
            final Log log_readdef)
            throws IOException {
        BufferedReader bin = null;
        try {
            // read
            bin = new BufferedReader(in);
            // read key, value, comment pattern
            Pattern p_key = null;
            Pattern p_value = null;
            Pattern p_line_comment = null;
            Pattern p_block_comment_in = null;
            Pattern p_block_comment_out = null;
            String line = bin.readLine();
            Pattern p = Pattern.compile(line);
            while (null != (line = bin.readLine())) {
                Matcher m = p.matcher(line); // [key : ]value value ... // line_comment
                boolean b = m.lookingAt();
                if (b) {
                    String key = m.group(1);
                    String value = m.group(2);
log_readdef.debug(key + ": " + value);
                    if ("key".equals(key)) {
                        p_key = Pattern.compile(value);
                    } else if ("value".equals(key)) {
                        p_value = Pattern.compile(value);
                    } else if ("LineComment".equals(key)) {
                        p_line_comment = Pattern.compile(value);
                    } else if ("BlockCommentIn".equals(key)) {
                        p_block_comment_in = Pattern.compile(value);
                    } else if ("BlockCommentOut".equals(key)) {
                        p_block_comment_out = Pattern.compile(value);
                    }
                    if ((null != p_key) && (null != p_value) && (null != p_line_comment)
                            && (null != p_block_comment_in) && (null != p_block_comment_out)) {
                        break;
                    }
                }
            }
            // read key, value, comment
            boolean in_block_comment = false;
            while (null != (line = bin.readLine())) {
                int index = 0;
log_readdef.debug("< line: " + line);
                // block_comment
                if (! in_block_comment) {
                    Matcher m = p_block_comment_in.matcher(line); // [...][/* block_comment]
                    boolean b = m.lookingAt();
                    if (b) {
                        in_block_comment = true;
                        line = m.group(1);
                        String comment = m.group(2);
log_readdef.debug("new line: " + line);
log_readdef.debug("comment: " + comment);
                    }
                } else {
                    Matcher m = p_block_comment_out.matcher(line); // [block_comment */][...]
                    boolean b = m.lookingAt();
                    if (b) {
                        in_block_comment = false;
                        line = m.group(2);
                        String comment = m.group(1);
log_readdef.debug("new line: " + line);
log_readdef.debug("comment: " + comment);
                    } else {
log_readdef.debug("in_block_comment");
                        continue;
                    }
                }
                // line_comment
                String comment = null;
                Matcher m = p_line_comment.matcher(line); // key : value value ... [// line_comment]
                boolean b = m.lookingAt();
                if (b) {
                    line = m.group(1);
                    comment = m.group(2);
log_readdef.debug("new line: " + line);
log_readdef.debug("comment: " + comment);
                }
                // key, value
                if (! parseKeyAndValueLine(line, index, comment, p_key, p_value)) {
                    break;
                }
            }
        } finally {
            try {
                if (null != bin) {
                    bin.close();
                }
            } finally {
                in.close();
            }
        }
    }
}

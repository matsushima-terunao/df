#include "StdAfx.h"
#include "Lexer.h"

Lexer::Lexer(void)
{
}

Lexer::~Lexer(void)
{
}

/**
 * 字句解析を行う。
 * 
 * @param def
 * @param src
 * @throws IOException
 */
void Lexer::lex(
	Reader& def,
	Reader& src)
{
	// 字句解析定義を読み込む。
	readTokenDefinition(def);
	// 字句解析を行う。
	lexSource(src);
}

//// 字句解析定義

/**
 * 字句解析定義を読み込む。
 * 
 * @param in
 * @throws IOException
 */
void Lexer::readTokenDefinition(
	Reader& in)
{
	// 解析定義読み込み。
	class MyDefinitionReader : public DefinitionReader
	{
	private:
		TokenDefinition& tokendefs;
		LogE log_readdef;// = getLog("readTokenDefinition");
		TokenDefinition def_key;
	public:
		MyDefinitionReader(TokenDefinition& tokendefs)
			: tokendefs(tokendefs)
		{
		}

		/**
		 * 行の key と value を解析する。
		 * 
		 * @param line
		 * @param index
		 * @param comment
		 * @param pattern_key
		 * @param pattern_value
		 * @return
		 */
	protected:
		virtual bool parseKeyAndValueLine(
			std::string& line,
			int index,
			std::string& comment,
			std::tr1::regex& pattern_key,
			std::tr1::regex& pattern_value)
		{
			std::string::const_iterator line_begin = line.cbegin() + index;
			std::string::const_iterator line_end = line.cend();
			std::tr1::smatch match;
			// key
			if (std::tr1::regex_search(line_begin, line_end, match, pattern_key, std::tr1::regex_constants::match_continuous)) // [key : ]value // line_comment
			{
				/*J*def_key = new TokenDefinition();/**/ // [(key) : ]value // line_comment
				def_key.key = match.str(1); // [(key) : ]value // line_comment
				def_key.comment = comment;
				comment.clear();
				line_begin += match.length();
			}
			else
			{
				if (def_key.key.empty())
				{
					// key: の行に到達していない
					log_readdef.debug("no key, continue");
					return true;
				}
				else
				{
					log_readdef.debug("use prev key: " + def_key.key);
				}
			}
			// value
			if (std::tr1::regex_search(line_begin, line_end, match, pattern_value, std::tr1::regex_constants::match_continuous)) // key : [value ]// line_comment
			{
				def_key.value = match.str(1);
				def_key.pattern = std::tr1::regex(match.str(1));
				def_key.comment += comment;
				comment.clear();
				tokendefs.add(def_key);
				log_readdef.debug("> " + def_key.toString());
				std::string key = def_key.key;
				/*J*def_key = new TokenDefinition();/**/
				def_key.key = key;
				def_key.comment.clear();
			}
			return true;
		}
	};
	// 解析定義読み込み。
	MyDefinitionReader reader(tokendefs);
	log_readdef.debug(">>> Lexer.readTokenDefinition()");
	// 定義を読み込む。
	reader.readDefinition(in, log_readdef);
	log_readdef.debug("<<< Lexer.readTokenDefinition()");
}

//// 字句解析

/**
 * 次の有効なトークンを取得する。
 * 
 * @param token
 * @return
 */
Lexer::Token* Lexer::getNextToken(
	Token* token)
{
	if (NULL == token)
	{
		// 最初
		token = tokens.children.empty() ? NULL : &tokens.children.front();
	}
	else
	{
		token = token->next;
	}
	for (; NULL != token; token = token->next)
	{
		if ((0 == token->tokendef->key.compare("space"))
			|| (0 == token->tokendef->key.compare("comment_block"))
			|| (0 == token->tokendef->key.compare("comment_line")))
		{
			log_gettoken_skip.debug("> skip: " + token->toString());
		}
		else
		{
			log_gettoken.debug("> " + token->toString());
			return token;
		}
	}
	log_gettoken.debug("> end of token");
	return token;
}

/**
 * 字句解析を行う。
 * 
 * @param in
 * @throws IOException
 */
void Lexer::lexSource(
	Reader& in)
{
	log_lexsrc.debug(">>> Lexer.lexSource()");

	// read src
	std::string src;
	std::string line;
	while (NULL != in.readLine(line))
	{
		src.append(line).append("\n");
	}
	in.close();

	// lex
	std::string::const_iterator src_begin = src.cbegin();
	std::string::const_iterator src_end = src.cend();
	std::tr1::smatch match;
	while (src_begin < src_end) // src
	{
		loop:
		for (std::list<TokenDefinition>::iterator
			tokendef = tokendefs.children.begin();
			tokendef != tokendefs.children.end();
			++ tokendef) // 字句解析定義。
		{
			if (std::tr1::regex_search(src_begin, src_end, match, tokendef->pattern, std::tr1::regex_constants::match_continuous)) // key : [value] // line_comment
			{
				// 字句解析のコールバック。
				int index = readSrcCallback(src, *tokendef, src_begin - src.cbegin(), src_begin - src.cbegin() + match.length());
				// 字句解析定義にマッチしたトークン。に追加
				Token token;
				token.tokendef = &*tokendef;
				token.text = std::string(src_begin, src.cbegin() + index);
				tokens.add(token);
				log_lexsrc.debug("> " + str(index) + ", " + token.toString());
				src_begin = src.cbegin() + index;
				goto loop;
			}
		}
		break; // 一致なし -> 中断
	}
	log_lexsrc.debug("<<< Lexer.lexSource()");
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
int Lexer::readSrcCallback(
	std::string& src,
	TokenDefinition& tokendef,
	int start,
	int end)
{
	return end;
}

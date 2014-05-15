#include "StdAfx.h"
#include "Parser.h"

Parser::Parser(void)
	: syntaxdefs(SyntaxDefinition(NULL, "root"))
{
}

Parser::~Parser(void)
{
}

/**
 * 構文解析を行う。
 * 
 * @param def
 * @param lexer
 * @throws IOException
 */
void Parser::parse(
	Reader& def,
	Lexer* lexer)
{
	// 字句解析。
	this->lexer = lexer;
	// 構文解析定義を読み込む。
	readSyntaxDefinition(def);
	// 構文解析を行う。
	parseSource();
}

//// 構文解析定義

/**
 * 構文解析定義を読み込む。
 * 
 * @param in
 * @throws IOException
 */
void Parser::readSyntaxDefinition(
	Reader& in)
{
	// 解析定義読み込み。
	class MyDefinitionReader : public DefinitionReader
	{
	private:
		SyntaxDefinition& syntaxdefs;
		LogE log_readdef;// = getLog("readTokenDefinition");
		SyntaxDefinition* def_key;// = null;

	public:
		MyDefinitionReader(SyntaxDefinition& syntaxdefs)
			: syntaxdefs(syntaxdefs)
		{
			def_key = NULL;
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
		bool parseKeyAndValueLine(
			std::string& line,
			int index,
			std::string& comment,
			std::tr1::regex& pattern_key,
			std::tr1::regex& pattern_value)
		{
			// 	syntaxdefs: root
			// 		def_key: key, comment <- key:
			// 			def_lines: ||,  <- 各行のいずれかが一致
			// 				def_values: &&, comment <- 行内の全てが一致
			// 				def_values: &&, comment <- 行内の全てが一致

			// key
			std::string::const_iterator line_begin = line.cbegin() + index;
			std::string::const_iterator line_end = line.cend();
			std::tr1::smatch match;
			if (std::tr1::regex_search(line_begin, line_end, match, pattern_key)) // [ key :] value value ...
			{
				/*J*def_key = new SyntaxDefinition(syntaxdef, m.group(1));/**/ // [ (key) :] value value ...
				SyntaxDefinition def;
				def.key = match.str(1); // [ (key) :] value value ...
				def.comment = comment;
				log_readdef.debug("> " + def.toString());
				comment.clear();
				line_begin += match.position(2);
				def_key = syntaxdefs.add(def); // syntaxdefs <- def_key(=def)
				SyntaxDefinition def_lines(def_key, "||"); // def_key <- def_lines
			}
			else
			{
				if (NULL == def_key)
				{
					// key: の行に到達していない
					log_readdef.debug("no key, continue");
					return true;
				}
				else
				{
					log_readdef.debug("use prev key: " + def_key->key);
				}
			}
			// value ...
			SyntaxDefinition def_values;
			def_values.key ="&&";
			def_values.comment = comment;
			SyntaxDefinition* def_parent = &def_values;
			while (std::tr1::regex_search(line_begin, line_end, match, pattern_value)) //  key :[ value] value ...
			{
				SyntaxDefinition def;
				def.key = match.str(1); //  key :[ (value)] value ...
				log_readdef.debug("> " + def.toString());
				line_begin += match.position(1) + match.length(1); //  key :[ (value)]< value ...>
				if ((1 == def.key.size()) && (NULL != strchr("([{", def.key[0])))
				{
					// ([{ を追加して、以降を1段下げる
					def_parent = def_parent->add(def);
				}
				else if ((1 == def.key.size()) && (NULL != strchr(")]}", def.key[0])))
				{
					// 1段戻る
					def_parent = def_parent->parent;
					if (0 == def_parent->key.compare("|"))
					{
						def_parent = def_parent->parent->parent;
					}
				}
				else if (0 == def.key.compare("|"))
				{
					if ((NULL == def_parent->parent) // value | value
						|| (0 != def_parent->parent->key.compare("|"))) // (value | value)
					{
						// 既存を2段下げる
						std::list<SyntaxDefinition> children = def_parent->children;
						def_parent->children.clear();
						def_parent = def_parent->add(SyntaxDefinition(NULL, "|"));
						def_parent = def_parent->add(SyntaxDefinition(NULL, "&&"));
						def_parent->add(children);
					}
					def_parent = def_parent->parent;
					def.key = "&&";
					def_parent = def_parent->add(def);
				}
				else if ('"' == def.key[0])
				{
					// "" の中を追加
					def.key = match.str(2);
					def_parent->add(def);
				}
				else if ('\'' == def.key[0])
				{
					// '' の中を追加
					def.key = match.str(3);
					def_parent->add(def);
				}
				else
				{
					// そのまま追加
					def_parent->add(def);
				}
			}
			// 子供があれば親に追加
			if (!def_values.children.empty())
			{
				def_key->children.front().add(def_values);
			}
			return true;
		}
	};
	// 解析定義読み込み。
	MyDefinitionReader reader(syntaxdefs);
	log_readdef.debug(">>> Parser.readSyntaxDefinition()");
	// 定義を読み込む。
	reader.readDefinition(in, log_readdef);
	log_readdef.debug("<<< Parser.readSyntaxDefinition()");
	log_readdef.debug(">>> Parser.traceSyntaxDefinition()");
	// 構文解析定義をトレースする。
	// 最適化とログ出力。
	traceSyntaxDefinition();
	log_readdef.debug("<<< Parser.traceSyntaxDefinition()");
}

/**
 * 構文解析定義をトレースする。
 * 最適化とログ出力。
 */
void Parser::traceSyntaxDefinition()
{
	traceSyntaxDefinitionImpl(syntaxdefs, 0);
}

/**
 * 構文解析定義をトレースする。
 * 最適化とログ出力。
 * 
 * @param defs
 * @param indent
 */
void Parser::traceSyntaxDefinitionImpl(
	SyntaxDefinition& defs,
	int indent)
{
	if (indent < 2)
	{
		// key: は自身が定義なので除外
		goto find_ref_end;
	}
	// 構文解析定義または字句解析定義
	// Parser::syntaxdefs から定義を探す
	for (std::list<SyntaxDefinition>::iterator
		ref = syntaxdefs.children.begin();
		ref != syntaxdefs.children.end();
		++ ref)
	{
		if (0 == defs.key.compare(ref->key))
		{
			defs.syntaxdef = &*ref;
			goto find_ref_end;
		}
	}
	// Lexer::tokendefs から定義を探す
	for (std::list<Lexer::TokenDefinition>::iterator
		ref = lexer->tokendefs.children.begin();
		ref != lexer->tokendefs.children.end();
		++ ref)
	{
		if (0 == defs.key.compare(ref->key))
		{
			defs.tokendef = &*ref;
			goto find_ref_end;
		}
	}
find_ref_end:
	// ログ出力
	log_readdef_trace.debug(defs.spc(indent) + defs.toString());
	// 子供を実行
	for (std::list<SyntaxDefinition>::iterator
		def = defs.children.begin();
		def != defs.children.end();
		++ def)
	{
		traceSyntaxDefinitionImpl(*def, indent + 1);
	}
}

//// 構文解析定義

/**
 * 構文解析を行う。
 */
void Parser::parseSource()
{
	log_parsesrc.debug(">>> Parser.parseSource()");
	ParseContext context;
	context.token = lexer->getNextToken(NULL); // 次の有効なトークンを取得する。
	SyntaxDefinition* def = &syntaxdefs.children.front(); // root 配下の最初の key が対象
	parseSourceImpl(&context, def, &tokens, 0);
	log_parsesrc.debug("<<< Parser.parseSource()");
	log_parsesrc.debug(">>> Parser.traceParseSource");

	for (Token* token = tokens.getTraceNext(); NULL != token; token = token->getTraceNext())
	{
		log_parsesrc.debug(token->spc(token->indent) + token->toString());
	}
	log_parsesrc.debug("<<< Parser.traceParseSource");
}

/**
 * 構文解析を行う。
 */
bool Parser::parseSourceImpl(
	ParseContext* context,
	SyntaxDefinition* def,
	Token* token,
	int indent)
{
	log_parsesrc.debug(def->spc(indent) + "< " + def->key);
	if (NULL == context->token)
	{
		return false;
	}
	bool result = false;
	bool next_token = false; // 次の token に進めるか
	bool apply_token = false; // 移動後の token を適用するか
	// 構文解析状態。
	// compare_end: 後 apply_token == true だったら context に反映
	ParseContext context2;
	context2.token = context->token;
	// 構文解析定義にマッチしたトークン。
	// 仮追加、compare_end: 後 result == false だったら削除
	Token* token_cur = token->add(Token());
	token_cur->token = context->token;
	token_cur->def = def;
	token_cur->indent = indent;
	if (def->children.empty())
	{
		// 自分を比較
		// syntaxdef から比較
		if (NULL != def->syntaxdef)
		{
			log_parsesrc.debug(def->spc(indent) + "syntaxdef から比較");
			result = apply_token = parseSourceImpl(&context2, def->syntaxdef, token_cur, indent + 1);
			goto compare_end;
		}
		// tokendef から比較
		if (NULL != def->tokendef)
		{
			log_parsesrc.debug(def->spc(indent) + "tokendef から比較");
			result = apply_token = next_token = (0 == context2.token->tokendef->key.compare(def->tokendef->key));
			if (result)
			{
				log_parsesrc.debug(def->spc(indent) + "> tokendef に一致");
			}
			goto compare_end;
		}
		// 一致比較: > Lexer::Token : < Parser::SyntaxDefinition
		result = apply_token = next_token = (0 == context2.token->text.compare(def->key));
		if (result)
		{
			log_parsesrc.debug(def->spc(indent) + "> 一致");
		}
		else
		{
			log_parsesrc.debug(def->spc(indent) + "> 不一致");
		}
	}
	else
	{
		// 子供を比較
		Lexer::Token* token_bak = context2.token; // { で成功ループ終了の位置を保存
		do // { は成立している間繰り返し
		{
			for (std::list<SyntaxDefinition>::iterator
				def_it = def->children.begin();
				def_it != def->children.end();
				++ def_it)
			{
				result = apply_token = parseSourceImpl(&context2, &*def_it, token_cur, indent + 1);
				if (result)
				{
					if ((0 == def->key.compare("|"))
						|| (0 == def->key.compare("||")))
					{
						// result = true の時点で true 確定
						goto compare_end;
					}
				}
				else
				{
					if ((0 == def->key.compare("&&"))
						|| (0 == def->key.compare("(")))
					{
						// result = false の時点で false 確定
						goto compare_end;
					}
					else if (0 == def->key.compare("["))
					{
						// result = false の時点で false 確定、0回以上なので result = true
						result = true;
						goto compare_end;
					}
					else if (0 == def->key.compare("{"))
					{
						// res = false の時点で false 確定、0回以上なので result = true
						result = apply_token = true;
						context2.token = token_bak; // { で成功ループ終了の位置を復帰
						goto compare_end;
					}
				}
			}
			token_bak = context2.token; // { で成功ループ終了の位置を保存
		} while (0 == def->key.compare("{")); // { は成立している間繰り返し
	}
compare_end:
	log_parsesrc.debug(def->spc(indent) + ">> " + (result ? "result, " : "") + (next_token ? "next_token, " : "") + (apply_token ? "apply_token" : "") + ": " + context->token->toString() + "; " + def->toString());
	if (!result)
	{
		// 構文解析定義にマッチしたトークン。
		// 仮追加、compare_end: 後 result == false だったら削除
		token->remove(token_cur);
	}
	if (next_token) // 次の token に進めるか
	{
		context2.token = lexer->getNextToken(context2.token); // 次の有効なトークンを取得する。
	}
	if (apply_token) // 移動後の token を適用するか
	{
		// 構文解析状態。
		// compare_end: 後 apply_token == true だったら context に反映
		context->token = context2.token;
	}
	return result;
}

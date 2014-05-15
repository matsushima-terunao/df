#pragma once

#include "Node.h"
#include "DefinitionReader.h"
#include "Lexer.h"

class Reader;

/**
 * 構文解析。
 * 
 * @author  1.0 2005/03/24 matsushima h2javac
 * @author  1.1 2006/07/19 matsushima cpp2javac
 * @author  0.0.1.001 2010/05/01 matsushima
 * @author  0.0.1.002 2012/08/16 matsushima
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
class Parser
{
public:
	Parser(void);
	~Parser(void);

	/*
	 * ログ。
	 */
private:
	LogE log_readdef;// = getLog("readSyntaxDefinition");
	LogE log_readdef_trace;// = getLog("trace_readSyntaxDefinition");
	LogE log_parsesrc;// = getLog("parseSource");
	LogE log_tracenode;// = getLog("traceNode");

	/**
	 * 構文解析を行う。
	 * 
	 * @param def
	 * @param lexer
	 * @throws IOException
	 */
public:
	void parse(
		Reader& def,
		Lexer* lexer);

	//// 構文解析定義

	/**
	 * 構文解析定義。
	 */
public:
	class SyntaxDefinition : public Node<SyntaxDefinition>
	{
	public:
		std::string key;
		std::string comment;
		SyntaxDefinition* syntaxdef;
		Lexer::TokenDefinition* tokendef;
		SyntaxDefinition()
		{
			this->syntaxdef = NULL;
			this->tokendef = NULL;
		}
		SyntaxDefinition(
			SyntaxDefinition* def,
			const char* key)
		{
			this->key = key;
			if (NULL != def)
			{
				def->add(*this);
			}
		}
		std::string toString()
		{
			return key + ", " + (NULL == syntaxdef ? "" : "syntaxdef, ") + (NULL == tokendef ? "" : "tokendef, ") + comment;
		}
	};

	/**
	 * 構文解析定義。
	 */
private:
	SyntaxDefinition syntaxdefs;// = new SyntaxDefinition(null, "root");

	/**
	 * 構文解析定義を読み込む。
	 * 
	 * @param in
	 * @throws IOException
	 */
public:
	void readSyntaxDefinition(
		Reader& in);

	/**
	 * 構文解析定義をトレースする。
	 * 最適化とログ出力。
	 */
public:
	void traceSyntaxDefinition();

	/**
	 * 構文解析定義をトレースする。
	 * 最適化とログ出力。
	 * 
	 * @param defs
	 * @param indent
	 */
private:
	void traceSyntaxDefinitionImpl(
		SyntaxDefinition& defs,
		int indent);

	//// 構文解析

	/**
	 * 構文解析定義にマッチしたトークン。
	 */
public:
	class Token : public Node<Token>
	{
	public:
		Lexer::Token* token;
		SyntaxDefinition* def;
		int indent;
		std::string toString()
		{
			return "token = " + (NULL == token ? "NULL" : token->toString()) + ", def = " + def->toString();
		}

	public:
		Token* getTraceNext()
		{
			return Node::getTraceNext();
		}

	public:
		Token* getTraceNext(Token* node, const char* key)
		{
			while (NULL != node)
			{
				node = Node::getTraceNext(node);
				if (NULL == node)
				{
					return NULL;
				}
				if (0 == node->def->key.compare(key))
				{
					return node;
				}
			}
		}
	};

	/**
	 * 構文解析定義にマッチしたトークン。
	 */
public:
	Token tokens;// = null;

	/**
	 * 字句解析。
	 */
public:
	Lexer* lexer;

	/**
	 * 構文解析状態。
	 */
public:
	class ParseContext
	{
	public:
		Lexer::Token* token;
	};

	/**
	 * 構文解析を行う。
	 */
private:
	void parseSource();

	/**
	 * 構文解析を行う。
	 */
private:
	bool parseSourceImpl(
		ParseContext* context,
		SyntaxDefinition* def,
		Token* token,
		int indent);
};

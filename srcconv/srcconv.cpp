// srcconv.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"
#include "Converter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// 字句解析。
	Lexer lexer;
	// 字句解析を行う。
	lexer.lex(
		Reader("cpplexer.txt"),
		Reader("test.cpp"));
	// 構文解析。
	Parser parser;
	// 構文解析を行う。
	parser.parse(
		Reader("cppparser.txt"),
		&lexer);
	// コンバータ。
	Converter converter;
	// 解析したソースをコンバートする。
	converter.convert(&parser);
	// 出力
	for (Lexer::Token* token = lexer.tokens.getTraceNext(); NULL != token; token = token->getTraceNext())
	{
		printf("%s", token->text.c_str());
	}
	getchar();
	return 0;
}

#include "StdAfx.h"
#include "Converter.h"

Converter::Converter(void)
{
}

Converter::~Converter(void)
{
}

/**
 * 解析したソースをコンバートする。
 */
void Converter::convert(Parser* parser)
{
	Parser::Token* root;
	Parser::Token* node;

	root = parser->tokens.getTraceNext(&parser->tokens, "include-declaration");
	node = root->getTraceNext(root, "#");
	node->token->text = "";
	node = root->getTraceNext(root, "include");
	node->token->text = "import";
	node = root->getTraceNext(root, "<");
	node->token->text = "";
	node = root->getTraceNext(root, ">");
	node->token->text = ";";

	root = parser->tokens.getTraceNext(&parser->tokens, "function-declaration");
	node = root->getTraceNext(root, "(");
	node->token->text = "public class Program {\n"
		"\tpublic static " + node->token->text;
	node = root->getTraceNext(root, "}");
	node->token->text = "}\n}";
}

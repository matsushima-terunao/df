// srcconv.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "Lexer.h"
#include "Parser.h"
#include "Converter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// �����́B
	Lexer lexer;
	// �����͂��s���B
	lexer.lex(
		Reader("cpplexer.txt"),
		Reader("test.cpp"));
	// �\����́B
	Parser parser;
	// �\����͂��s���B
	parser.parse(
		Reader("cppparser.txt"),
		&lexer);
	// �R���o�[�^�B
	Converter converter;
	// ��͂����\�[�X���R���o�[�g����B
	converter.convert(&parser);
	// �o��
	for (Lexer::Token* token = lexer.tokens.getTraceNext(); NULL != token; token = token->getTraceNext())
	{
		printf("%s", token->text.c_str());
	}
	getchar();
	return 0;
}

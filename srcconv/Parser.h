#pragma once

#include "Node.h"
#include "DefinitionReader.h"
#include "Lexer.h"

class Reader;

/**
 * �\����́B
 * 
 * @author  1.0 2005/03/24 matsushima h2javac
 * @author  1.1 2006/07/19 matsushima cpp2javac
 * @author  0.0.1.001 2010/05/01 matsushima
 * @author  0.0.1.002 2012/08/16 matsushima
 * 
 * $Id: Parser.java,v 1.13 2010/05/23 18:36:42 matsushima Exp $
 * $Log: Parser.java,v $
 * Revision 1.13  2010/05/23 18:36:42  matsushima
 * ����
 *
 * Revision 1.12  2010/05/22 17:05:04  matsushima
 * Node �� AbstractSequentialList �h��
 *
 * Revision 1.11  2010/05/21 16:56:49  matsushima
 * �m�[�h�̋��ʉ�
 *
 * Revision 1.10  2010/05/20 14:05:15  matsushima
 * ��͒�`�̓ǂݍ��݋��ʉ�
 *
 * Revision 1.9  2010/05/19 14:59:02  matsushima
 * �����͒�`��ǂݍ��ݏC��
 *
 * Revision 1.6  2010/05/14 18:42:42  matsushima
 * �\����͂ƃm�[�h�o��
 *
 * Revision 1.5  2010/05/13 13:41:15  matsushima
 * �\����͒�`�ǂݍ���
 *
 * Revision 1.2  2010/05/03 19:25:27  matsushima
 * �\�����
 *
 * Revision 1.1  2010/05/01 20:20:41  matsushima
 * �V�K
 * ������
 * �\�����(�n�[�h�R�[�f�B���O)
 *
 */
class Parser
{
public:
	Parser(void);
	~Parser(void);

	/*
	 * ���O�B
	 */
private:
	LogE log_readdef;// = getLog("readSyntaxDefinition");
	LogE log_readdef_trace;// = getLog("trace_readSyntaxDefinition");
	LogE log_parsesrc;// = getLog("parseSource");
	LogE log_tracenode;// = getLog("traceNode");

	/**
	 * �\����͂��s���B
	 * 
	 * @param def
	 * @param lexer
	 * @throws IOException
	 */
public:
	void parse(
		Reader& def,
		Lexer* lexer);

	//// �\����͒�`

	/**
	 * �\����͒�`�B
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
	 * �\����͒�`�B
	 */
private:
	SyntaxDefinition syntaxdefs;// = new SyntaxDefinition(null, "root");

	/**
	 * �\����͒�`��ǂݍ��ށB
	 * 
	 * @param in
	 * @throws IOException
	 */
public:
	void readSyntaxDefinition(
		Reader& in);

	/**
	 * �\����͒�`���g���[�X����B
	 * �œK���ƃ��O�o�́B
	 */
public:
	void traceSyntaxDefinition();

	/**
	 * �\����͒�`���g���[�X����B
	 * �œK���ƃ��O�o�́B
	 * 
	 * @param defs
	 * @param indent
	 */
private:
	void traceSyntaxDefinitionImpl(
		SyntaxDefinition& defs,
		int indent);

	//// �\�����

	/**
	 * �\����͒�`�Ƀ}�b�`�����g�[�N���B
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
	 * �\����͒�`�Ƀ}�b�`�����g�[�N���B
	 */
public:
	Token tokens;// = null;

	/**
	 * �����́B
	 */
public:
	Lexer* lexer;

	/**
	 * �\����͏�ԁB
	 */
public:
	class ParseContext
	{
	public:
		Lexer::Token* token;
	};

	/**
	 * �\����͂��s���B
	 */
private:
	void parseSource();

	/**
	 * �\����͂��s���B
	 */
private:
	bool parseSourceImpl(
		ParseContext* context,
		SyntaxDefinition* def,
		Token* token,
		int indent);
};

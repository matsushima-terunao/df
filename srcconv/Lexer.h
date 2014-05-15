#pragma once

#include "Node.h"
#include "DefinitionReader.h"
#include <string>
#include <regex>

class Reader;

/**
 * �����́B
 * 
 * @author  1.0 2005/03/16 matsushima h2javac
 * @author  1.1 2006/07/19 matsushima cpp2javac
 * @author  0.0.1.001 2010/04/29 matsushima java2cppc
 * @author  0.0.2.002 2012/08/15 matsushima
 * @version 0.0.2.002 2012/08/15 matsushima
 * @since   0.0.2.002 2012/08/15 matsushima
 * 
 * $Id: Lexer.java,v 1.7 2010/05/21 16:56:49 matsushima Exp $
 * $Log: Lexer.java,v $
 * Revision 1.7  2010/05/21 16:56:49  matsushima
 * �m�[�h�̋��ʉ�
 *
 * Revision 1.6  2010/05/20 14:05:15  matsushima
 * ��͒�`�̓ǂݍ��݋��ʉ�
 *
 * Revision 1.5  2010/05/19 14:59:02  matsushima
 * �����͒�`��ǂݍ��ݏC��
 *
 * Revision 1.4  2010/05/13 13:41:15  matsushima
 * �\����͒�`�ǂݍ���
 *
 * Revision 1.3  2010/05/05 15:25:20  matsushima
 * �\����͊���
 *
 * Revision 1.2  2010/05/03 19:25:27  matsushima
 * �\�����
 *
 * Revision 1.1  2010/05/01 20:20:40  matsushima
 * �V�K
 * ������
 * �\�����(�n�[�h�R�[�f�B���O)
 *
 */
class Lexer
{
	/*
	 * ���O�B
	 */
private:
	LogE log_readdef;// = getLog("readTokenDefinition");
	LogE log_lexsrc;// = getLog("lexSource");
	LogE log_gettoken;// = getLog("getNextTokenIndex");
	LogE log_gettoken_skip;// = getLog("skip_getNextTokenIndex");

public:
	Lexer(void);
	~Lexer(void);

	/**
	 * �����͂��s���B
	 * 
	 * @param def
	 * @param src
	 * @throws IOException
	 */
public:
	void lex(
		Reader& def,
		Reader& src);

	//// �����͒�`

	/**
	 * �����͒�`�B
	 */
public:
	class TokenDefinition : public Node<TokenDefinition>
	{
	public:
		std::string key;
		std::string value;
		std::string comment;
		std::tr1::regex pattern;
		std::string toString()
		{
			return key + ", " + value + ", " + comment;
		}
	};

	/**
	 * �����͒�`�B
	 */
public:
	TokenDefinition tokendefs;

	/**
	 * �����͒�`��ǂݍ��ށB
	 * 
	 * @param in
	 * @throws IOException
	 */
public:
	void readTokenDefinition(
		Reader& in);

	//// ������

	/**
	 * �����͒�`�Ƀ}�b�`�����g�[�N���B
	 */
public:
	class Token : public Node<Token>
	{
	public:
		TokenDefinition* tokendef;
		std::string text;
		std::string toString()
		{
			return tokendef->key + ", " + text;
		}
	};

	/**
	 * �����͒�`�Ƀ}�b�`�����g�[�N���B
	 */
public:
	Token tokens;

	/**
	 * ���̗L���ȃg�[�N�����擾����B
	 * 
	 * @param token
	 * @return
	 */
public:
	Token* getNextToken(
		Token* token);

	/**
	 * �����͂��s���B
	 * 
	 * @param in
	 * @throws IOException
	 */
public:
	void lexSource(
		Reader& in);

	/**
	 * �����͂̃R�[���o�b�N�B
	 * 
	 * @param src
	 * @param tokendef
	 * @param start
	 * @param end
	 * @return
	 */
protected:
	virtual int readSrcCallback(
		std::string& src,
		TokenDefinition& tokendef,
		int start,
		int end);
};

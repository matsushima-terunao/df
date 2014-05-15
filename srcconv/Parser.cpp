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
 * �\����͂��s���B
 * 
 * @param def
 * @param lexer
 * @throws IOException
 */
void Parser::parse(
	Reader& def,
	Lexer* lexer)
{
	// �����́B
	this->lexer = lexer;
	// �\����͒�`��ǂݍ��ށB
	readSyntaxDefinition(def);
	// �\����͂��s���B
	parseSource();
}

//// �\����͒�`

/**
 * �\����͒�`��ǂݍ��ށB
 * 
 * @param in
 * @throws IOException
 */
void Parser::readSyntaxDefinition(
	Reader& in)
{
	// ��͒�`�ǂݍ��݁B
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
		 * �s�� key �� value ����͂���B
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
			// 			def_lines: ||,  <- �e�s�̂����ꂩ����v
			// 				def_values: &&, comment <- �s���̑S�Ă���v
			// 				def_values: &&, comment <- �s���̑S�Ă���v

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
					// key: �̍s�ɓ��B���Ă��Ȃ�
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
					// ([{ ��ǉ����āA�ȍ~��1�i������
					def_parent = def_parent->add(def);
				}
				else if ((1 == def.key.size()) && (NULL != strchr(")]}", def.key[0])))
				{
					// 1�i�߂�
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
						// ������2�i������
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
					// "" �̒���ǉ�
					def.key = match.str(2);
					def_parent->add(def);
				}
				else if ('\'' == def.key[0])
				{
					// '' �̒���ǉ�
					def.key = match.str(3);
					def_parent->add(def);
				}
				else
				{
					// ���̂܂ܒǉ�
					def_parent->add(def);
				}
			}
			// �q��������ΐe�ɒǉ�
			if (!def_values.children.empty())
			{
				def_key->children.front().add(def_values);
			}
			return true;
		}
	};
	// ��͒�`�ǂݍ��݁B
	MyDefinitionReader reader(syntaxdefs);
	log_readdef.debug(">>> Parser.readSyntaxDefinition()");
	// ��`��ǂݍ��ށB
	reader.readDefinition(in, log_readdef);
	log_readdef.debug("<<< Parser.readSyntaxDefinition()");
	log_readdef.debug(">>> Parser.traceSyntaxDefinition()");
	// �\����͒�`���g���[�X����B
	// �œK���ƃ��O�o�́B
	traceSyntaxDefinition();
	log_readdef.debug("<<< Parser.traceSyntaxDefinition()");
}

/**
 * �\����͒�`���g���[�X����B
 * �œK���ƃ��O�o�́B
 */
void Parser::traceSyntaxDefinition()
{
	traceSyntaxDefinitionImpl(syntaxdefs, 0);
}

/**
 * �\����͒�`���g���[�X����B
 * �œK���ƃ��O�o�́B
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
		// key: �͎��g����`�Ȃ̂ŏ��O
		goto find_ref_end;
	}
	// �\����͒�`�܂��͎����͒�`
	// Parser::syntaxdefs �����`��T��
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
	// Lexer::tokendefs �����`��T��
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
	// ���O�o��
	log_readdef_trace.debug(defs.spc(indent) + defs.toString());
	// �q�������s
	for (std::list<SyntaxDefinition>::iterator
		def = defs.children.begin();
		def != defs.children.end();
		++ def)
	{
		traceSyntaxDefinitionImpl(*def, indent + 1);
	}
}

//// �\����͒�`

/**
 * �\����͂��s���B
 */
void Parser::parseSource()
{
	log_parsesrc.debug(">>> Parser.parseSource()");
	ParseContext context;
	context.token = lexer->getNextToken(NULL); // ���̗L���ȃg�[�N�����擾����B
	SyntaxDefinition* def = &syntaxdefs.children.front(); // root �z���̍ŏ��� key ���Ώ�
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
 * �\����͂��s���B
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
	bool next_token = false; // ���� token �ɐi�߂邩
	bool apply_token = false; // �ړ���� token ��K�p���邩
	// �\����͏�ԁB
	// compare_end: �� apply_token == true �������� context �ɔ��f
	ParseContext context2;
	context2.token = context->token;
	// �\����͒�`�Ƀ}�b�`�����g�[�N���B
	// ���ǉ��Acompare_end: �� result == false ��������폜
	Token* token_cur = token->add(Token());
	token_cur->token = context->token;
	token_cur->def = def;
	token_cur->indent = indent;
	if (def->children.empty())
	{
		// �������r
		// syntaxdef �����r
		if (NULL != def->syntaxdef)
		{
			log_parsesrc.debug(def->spc(indent) + "syntaxdef �����r");
			result = apply_token = parseSourceImpl(&context2, def->syntaxdef, token_cur, indent + 1);
			goto compare_end;
		}
		// tokendef �����r
		if (NULL != def->tokendef)
		{
			log_parsesrc.debug(def->spc(indent) + "tokendef �����r");
			result = apply_token = next_token = (0 == context2.token->tokendef->key.compare(def->tokendef->key));
			if (result)
			{
				log_parsesrc.debug(def->spc(indent) + "> tokendef �Ɉ�v");
			}
			goto compare_end;
		}
		// ��v��r: > Lexer::Token : < Parser::SyntaxDefinition
		result = apply_token = next_token = (0 == context2.token->text.compare(def->key));
		if (result)
		{
			log_parsesrc.debug(def->spc(indent) + "> ��v");
		}
		else
		{
			log_parsesrc.debug(def->spc(indent) + "> �s��v");
		}
	}
	else
	{
		// �q�����r
		Lexer::Token* token_bak = context2.token; // { �Ő������[�v�I���̈ʒu��ۑ�
		do // { �͐������Ă���ԌJ��Ԃ�
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
						// result = true �̎��_�� true �m��
						goto compare_end;
					}
				}
				else
				{
					if ((0 == def->key.compare("&&"))
						|| (0 == def->key.compare("(")))
					{
						// result = false �̎��_�� false �m��
						goto compare_end;
					}
					else if (0 == def->key.compare("["))
					{
						// result = false �̎��_�� false �m��A0��ȏ�Ȃ̂� result = true
						result = true;
						goto compare_end;
					}
					else if (0 == def->key.compare("{"))
					{
						// res = false �̎��_�� false �m��A0��ȏ�Ȃ̂� result = true
						result = apply_token = true;
						context2.token = token_bak; // { �Ő������[�v�I���̈ʒu�𕜋A
						goto compare_end;
					}
				}
			}
			token_bak = context2.token; // { �Ő������[�v�I���̈ʒu��ۑ�
		} while (0 == def->key.compare("{")); // { �͐������Ă���ԌJ��Ԃ�
	}
compare_end:
	log_parsesrc.debug(def->spc(indent) + ">> " + (result ? "result, " : "") + (next_token ? "next_token, " : "") + (apply_token ? "apply_token" : "") + ": " + context->token->toString() + "; " + def->toString());
	if (!result)
	{
		// �\����͒�`�Ƀ}�b�`�����g�[�N���B
		// ���ǉ��Acompare_end: �� result == false ��������폜
		token->remove(token_cur);
	}
	if (next_token) // ���� token �ɐi�߂邩
	{
		context2.token = lexer->getNextToken(context2.token); // ���̗L���ȃg�[�N�����擾����B
	}
	if (apply_token) // �ړ���� token ��K�p���邩
	{
		// �\����͏�ԁB
		// compare_end: �� apply_token == true �������� context �ɔ��f
		context->token = context2.token;
	}
	return result;
}

#pragma once

#include <string>
#include <regex>

class Reader;

/**
 * ��͒�`�ǂݍ��݁B
 * 
 * @author  0.0.1.001 2010/05/20 matsushima
 * @author  0.0.2.002 2012/08/15 matsushima
 * 
 * $Id: DefinitionReader.java,v 1.2 2010/05/23 18:36:43 matsushima Exp $
 * $Log: DefinitionReader.java,v $
 * Revision 1.2  2010/05/23 18:36:43  matsushima
 * ����
 *
 */
class DefinitionReader
{
public:
	DefinitionReader(void);
	~DefinitionReader(void);

	/**
	 * ��`��ǂݍ��ށB
	 * 
	 * @param in
	 * @throws IOException
	 */
public:
	void readDefinition(
		Reader& in,
		Log& log_readdef);

	/**
	 * �s�� key �� value ����͂���R�[���o�b�N�B
	 * 
	 * @param line
	 * @param index
	 * @param comment
	 * @param p_key
	 * @param p_value
	 * @return
	 */
protected:
	virtual bool parseKeyAndValueLine(
		std::string& line,
		int index,
		std::string& comment,
		std::tr1::regex& p_key,
		std::tr1::regex& p_value) = 0;
};

#pragma once

//2012/08/20

#include "Parser.h"

/**
 * �R���o�[�^�B
 */
class Converter
{
public:
	Converter(void);
	virtual ~Converter(void);

	/**
	 * ��͂����\�[�X���R���o�[�g����B
	 */
public:
	void convert(Parser* parser);
};

#pragma once

//2012/08/20

#include "Parser.h"

/**
 * コンバータ。
 */
class Converter
{
public:
	Converter(void);
	virtual ~Converter(void);

	/**
	 * 解析したソースをコンバートする。
	 */
public:
	void convert(Parser* parser);
};

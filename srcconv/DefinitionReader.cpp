#include "StdAfx.h"
#include "DefinitionReader.h"

DefinitionReader::DefinitionReader(void)
{
}


DefinitionReader::~DefinitionReader(void)
{
}

/**
 * 定義を読み込む。
 * 
 * @param in
 * @throws IOException
 */
void DefinitionReader::readDefinition(
	Reader& in,
	Log& log_readdef)
{
	// read key:value, key, value, xxxcommentxxx pattern
	std::tr1::regex pattern_key;
	std::tr1::regex pattern_value;
	std::tr1::regex pattern_line_comment;
	std::tr1::regex pattern_block_comment_in;
	std::tr1::regex pattern_block_comment_out;
	std::tr1::smatch match;
	std::string line;
	if (NULL == in.readLine(line))
	{
		return;
	}
	std::tr1::regex pattern_key_value(line);
	int pattern_flags = 0;
	while (NULL != in.readLine(line))
	{
		log_readdef.debug("< " + line);
		if (std::tr1::regex_search(line, match, pattern_key_value)) // [key : ]value value ... // line_comment
		{
			std::string key = match.str(1);
			std::string value = match.str(2);
			log_readdef.debug("> " + key + ": " + value);
			if (0 == key.compare("key"))
			{
				pattern_key = value;
				pattern_flags |= 1;
			}
			else if (0 == key.compare("value"))
			{
				pattern_value = value;
				pattern_flags |= 2;
			}
			else if (0 == key.compare("LineComment"))
			{
				pattern_line_comment = value;
				pattern_flags |= 4;
			}
			else if (0 == key.compare("BlockCommentIn"))
			{
				pattern_block_comment_in = value;
				pattern_flags |= 8;
			}
			else if (0 == key.compare("BlockCommentOut"))
			{
				pattern_block_comment_out = value;
				pattern_flags |= 16;
			}
			if (31 == pattern_flags)
			{
				break;
			}
		}
	}
	// read key, value, comment
	bool in_block_comment = false;
	std::string comment;
	while (NULL != in.readLine(line))
	{
		log_readdef.debug("< " + line);
		std::string::const_iterator line_begin = line.cbegin();
		std::string::const_iterator line_end = line.cend();
		// block_comment
		if (!in_block_comment)
		{
			if (std::tr1::regex_search(line_begin, line_end, match, pattern_block_comment_in, std::tr1::regex_constants::match_continuous)) // [...][/* block_comment]
			{
				in_block_comment = true;
				comment = match.str(2);
				line_end = line_begin + match.position(2);
				log_readdef.debug("new line(comment in): " + std::string(line_begin, line_end));
				log_readdef.debug("comment: " + comment);
			}
		}
		else
		{
			if (std::tr1::regex_search(line_begin, line_end, match, pattern_block_comment_out, std::tr1::regex_constants::match_continuous)) // [block_comment */][...]
			{
				in_block_comment = false;
				comment = match.str(1);
				line_begin += match.position(1) + match.length(1);
				log_readdef.debug("new line(comment out): " + std::string(line_begin, line_end));
				log_readdef.debug("comment: " + comment);
			}
			else
			{
				log_readdef.debug("in_block_comment");
				continue;
			}
		}
		// line_comment
		comment.clear(); // block comment は捨てる
		if (std::tr1::regex_search(line_begin, line_end, match, pattern_line_comment, std::tr1::regex_constants::match_continuous)) // key : value value ... [// line_comment]
		{
			comment = match.str(2);
			line_end = line_begin + match.position(2);
			log_readdef.debug("new line(line comment): " + std::string(line_begin, line_end));
			log_readdef.debug("comment: " + comment);
		}
		// key and/or value
		// 行の key と value を解析する。
		if (!parseKeyAndValueLine(std::string(line_begin, line_end), 0, comment, pattern_key, pattern_value))
		{
			break;
		}
	}
}

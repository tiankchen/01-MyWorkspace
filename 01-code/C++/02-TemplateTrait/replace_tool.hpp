
#ifndef TEST_TOKENIZER_INCLUDE_H
#define TEST_TOKENIZER_INCLUDE_H

#include <boost/regex.hpp>

class ReplaceTool
{
public:
	ReplaceTool(const std::string& str)
		: m_str(str)
	{
	}

	operator std::string()
	{
		boost::regex reg("(\t)|(\n)|(\r)");
		return boost::regex_replace(m_str, reg, " ");
	}

private:
	std::string m_str;
};


#endif


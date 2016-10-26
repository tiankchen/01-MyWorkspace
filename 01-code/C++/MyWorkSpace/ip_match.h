
// class ip_match
// author chenchen
// used to test if input is ipv4 address

#ifndef SSCC_UMP_IP_MATCH_H
#define SSCC_UMP_IP_MATCH_H

#include <string>
#include <boost/regex.hpp>

namespace std {

class ip_match
{
public:
	ip_match()
	{}

	ip_match(const std::string& str)
		: m_str(str)
	{}

	void set_value(const std::string& str)
	{
		m_str = str;
	}

	bool validate()
	{
		/*
		IP地址的分类：
		1. 0-9：一位，个位是0-9，正则表达式：\d
		2. 10-99:  两位，十位是1-9，个位是0-9，正则表达式：[1-9]\d
		3. 100-199: 三位，百位是1，十位是0-9，个位是0-9，正则表达式：1\d{2}
		4. 200-249: 三位，百位是2，十位是0-4，个位是0-9，正则表达式：2[0-4]\d
		5. 250-255: 三位，百位是2，十位是5，个位是0-5，正则表达式：25[0-5]

		综上：
		0-99的正则表达式：[1-9]?\d
		0-199的正则表达式：(1\d{2})|([1-9]?\d)
		0-255的正则表达式：(1\d{2}) | ([1-9]?\d) | (2[0-4]\d) | (25[0-5])
		IP地址的表达式为：
		((1\d{2}) | ([1-9]?\d) | (2[0-4]\d) | (25[0-5]) \.){3} ((1\d{2}) | ([1-9]?\d) | (2[0-4]\d) | (25[0-5]) \.)

		备注：
		？		匹配前面的表达式1次或者0次
		*		表示前面的表达式可以重复，可以重复0次
		+		表示前面的表达式可以重复，并且至少重复一次
		\d 匹配单个数字，c++中使用\\d，来抵消转义
		*/
		boost::regex allReg("(\\d+)\.(\\d+)\.(\\d+)\.(\\d+)");
		boost::regex ipReg("([1-9]?\\d)|(1\\d{2})|(2[0-4]\\d)|(25[0-5])");
		boost::smatch mDot;
		if (boost::regex_match(m_str, mDot, allReg))
		{
			int TOTAL = 4;
			for (int i = 1; i <= TOTAL; ++i)
			{
				std::string str = mDot[i];
				if (boost::regex_match(str, ipReg) == false)
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

private:
	std::string m_str;
};

}

#endif



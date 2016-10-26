/*
 * @brief 本文件用来测试正则表达式
 */

#pragma once

#include <boost/regex.hpp>

#include "util.hpp"

class TestRegex
{
public:
	TestRegex()
	{}

	void Test()
	{
		using namespace std;
		string str = "Calls to new must be followed by delete. Calling simply new results in a leak!";
		Cout(str);
		string::const_iterator it = str.begin();
		string::const_iterator end = str.end();

		boost::smatch m;
		boost::regex reg("(n.w)|(dele.e)");
		while (boost::regex_search(it, end, m, reg))
		{
			if (m[1].matched)
			{
				Cout(m[1].str());
				Cout("new Matched!");
			}
			else if(m[2].matched)
			{
				Cout("delete Matched!");
			}

			it = m[0].second;
		}
	}

	void Test2()
	{
		using namespace std;
		typedef vector<string> VecType;
		VecType vec = boost::assign::list_of
			("10.10.24.78/8")
			("10.10.34.1/2")
			("111.11.1.1")
			("")
			("111")
			("nihao")
			("10.10.24.78\\23")	//注意字符串转义
			("11/78")
			;
		
		//boost::regex reg("((\\d+\.){3}\\d+)(\/)((\\d+))");
		boost::regex reg("(\\d+\.\\d+\.\\d+\.\\d+)/(\\d+)");
		BOOST_FOREACH(const string& value, vec)
		{
			std::cout << "TestItem: " << value << std::endl;
			boost::smatch m;
			if (boost::regex_match(value, m, reg))
			{
				cout << "Matched!" << "IP: " << m[1].str() << " network: " << m[2].str() << std::endl;
			}
			else
			{
				Cout("Not Matched!");
			}
			Cout("================");
		}

	}


};



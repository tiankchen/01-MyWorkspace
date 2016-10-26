

#include "replace_tool.hpp"
#include "network.hpp"
#include "regex.hpp"
#include <iostream>
#include <fstream>

#include <boost/assign.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

typedef bool(*PfType)(const std::string&, const std::string&);

bool Test(const std::string& str1, const std::string& str2)
{
	std::cout << str1 << str2 << std::endl;
	return true;
}

//int main()
//{
//	if (std::cin)
//	{
//		std::cout << "cin is ok..." << std::endl;
//	}
//
//	int j = 0;
//	std::cin >> j;
//	if (!std::cin)
//	{
//		std::cout << "cin is not ok..." << std::endl;
//	}
//	std::cin.clear(std::istream::failbit);		//没有效果？
//	int i = 0;
//	while (std::cin >> i)
//	{
//		std::cout << "your print is : " << i << std::endl;
//	}
//	std::cout << "error cin, break" << std::endl;
//	return 0;
//}

//int main()
//{
//	using namespace std;
//
//	int iVal = 0;
//	while (cin >> iVal, !cin.eof())
//	{
//		if(cin.bad())
//		{
//			throw runtime_error("IO stream corrupted");
//		}
//
//		if (cin.fail())
//		{
//			istream::iostate oldState = cin.rdstate();
//			oldState = istream::failbit;
//
//			cerr << "bad data, try again";
//			//cin.clear(istream::failbit);		//？为什么治不好呢？
//			cin.clear();
//			continue;
//		}
//
//		std::cout << "your input is: " << iVal << std::endl;
//	}
//}

//
//int main()
//{
//	using namespace std;
//	
//	std::vector<string> files = boost::assign::list_of("test1.txt")("test2.txt");
//
//	ifstream ifs;
//	vector<string>::const_iterator it = files.begin();
//	while (it != files.end())
//	{
//		string fileName = *it;
//		ifs.open(fileName);
//		if (!ifs)
//		{
//			Cout(fileName + " open failed...");
//		}
//		else
//		{
//			Cout(fileName + " open success");
//			string str;
//			while (ifs >> str)
//			{
//				Cout(str);
//			}
//
//			ifs.close();
//			//ifs.clear();
//		}
//
//		++it;
//	}
//	
//	return 0;
//}


template<typename T>
struct print
{
	void operator()(const T& elem)
	{
		Cout(elem);
	}
};

class Int
{
public:

	Int()
		: m_i(2)
	{

	}

	int& operator*() const
	{
		return (int&)m_i;
	}

	int m_i;

};

class CC
{
public:
	CC(int i=111)
	{
		m_i = i;
	}

	~CC()
	{
		static int count = 0;
		count++;
		std::cout << count << std::endl;
	}


	int m_i;

};

int main()
{
	CC* c = new CC;
	c = new(c) CC(2);
	
	CC  aaa;

	return 0;
}



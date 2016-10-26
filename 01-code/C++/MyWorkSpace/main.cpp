
//test xml read and write

#include <util/config.hpp>

#include <boost/regex.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/locale.hpp>	//±àÂë×ª»»

#include <boost/date_time/posix_time/posix_time.hpp>	
#include <boost/date_time/gregorian/gregorian.hpp>

#include <boost/filesystem/fstream.hpp>

std::string UTF8ToGBK(const std::string& src)
{
	return boost::locale::conv::between(src, "GBK", "UTF-8");
}

std::string GBKToUTF8(const std::string& src)
{
	return boost::locale::conv::between(src, "UTF-8", "GBK");
}

void Test5(std::string& str = std::string())
{
	if ("20001" < "20002")
	{
		std::cout << "xiaoyu" << std::endl;
	}
}


class Test
{
public:
	Test()
		: str("1222")
	{}

	std::string str;
};

std::ostream& operator<<(std::ostream& out, const Test& t)
{
	out << t.str;
	return out;
}


void Test2()
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	boost::gregorian::date nowDate = now.date();
	boost::posix_time::time_duration nowTd = now.time_of_day();
	std::string str = boost::str(boost::format("%d%02d%02d-%02d:%02d:%02d")
		% nowDate.year()
		% nowDate.month().as_number()
		% nowDate.day()
		% nowTd.hours()
		% nowTd.minutes()
		% nowTd.seconds());
	std::cout << str << std::endl;
}

template<typename ConType>
int Size(const ConType& cons)
{
	return cons.size();
}

typedef std::map<std::string, std::string> MapType;
MapType CC()
{
	MapType cc;
	return cc;
}

void Test3()
{
	const std::string TEMPLATE = "Template";
	const std::string str = "TemplateItems[22][ItemId]";

	boost::smatch m;
	boost::regex reg("(TemplateItems\\[)(\\d*)(\\]\\[)([a-zA-Z]*)(\\])");
	if (boost::regex_match(str, m, reg))
	{
		std::cout << "Match!" << std::endl
			<< m[1].str() << std::endl
			<< m[2].str() << std::endl
			<< m[3].str() << std::endl
			<< m[4].str() << std::endl;
	}
	else
	{
		std::cout << "Not Match!" << std::endl;
	}

}

struct T
{
	std::string t1;
	std::string t2;

};

template <typename T>
struct CCC
{
	void Print()
	{
		std::cout << "Single T" << std::endl;
	}
};


template <typename T>
struct CCC<T*>
{
	void Print()
	{
		std::cout << "Pointor to T" << std::endl;
	}
};


class A
{
public:
	typedef int value_type;
};

template<typename T>
struct trait
{
	typedef typename T::value_type value_type;
};

//template<typename T>
//struct trait<T *>
//{
//	typedef ptrdiff_t value_type;
//};


struct hq {};
struct tw {};

template<typename T>
struct traits;

template<>
struct traits<hq>
{
	typedef int T;
};


int main()
{
	traits<hq>::T i;
	i = 4;

	/*using namespace boost;
	using namespace boost::property_tree;
	using namespace boost::property_tree::xml_parser;
	
	using std::string;

	ptree ptRoot;
	ptree& ptUser = ptRoot.add_child("plugin", ptree());
	ptUser.add("aaa", "nihao");
	ptUser.add("aaa", "helloworld");
	write_xml("test.xml", ptRoot);*/
	

	/*
	Test t;
	boost::format fmt("test %1%");
	Cout(fmt%t);

	string filename = "config.xml";
	boost::property_tree::ptree ptRoot;
	read_xml(filename, ptRoot);

	ptree ptConfigItems = ptRoot.get_child("config_items");
	BOOST_FOREACH(ptree::value_type ptChild, ptConfigItems)
	{
		Cout(ptChild.first);
		string id = ptChild.second.get<string>("<xmlattr>.id");
		string name = ptChild.second.get<string>("<xmlattr>.name");
		std::cout << ptChild.first << ": id " << UTF8ToGBK(id) << " , name " << UTF8ToGBK(name) << std::endl;
	}

	{
		ptree ptRoot;
		ptree& ptConfigItems = ptRoot.add_child("config_items", ptree());
		ptree pt;
		pt.put("<xmlattr>.id", "id");
		pt.put("<xmlattr>.name", GBKToUTF8("Íø¹ØºÅ"));
		ptConfigItems.add_child("config_item", pt);
		write_xml(filename, ptRoot);
	}*/

	return 0;
}



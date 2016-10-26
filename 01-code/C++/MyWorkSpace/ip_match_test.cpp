
// test boost regex use ip address match
// author chenchen

#include "ip_match.h"

#include <string>
#include <vector>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

typedef std::pair<std::string, bool>	PairType;
typedef std::vector<PairType>			PairVec;

PairVec Load()
{
	using namespace boost;
	using boost::property_tree::ptree;

	PairVec vec;

	ptree pt;
	property_tree::xml_parser::read_xml("cc.xml", pt);
	if (pt.get_child_optional("datas"))
	{
		ptree ptDatas = pt.get_child("datas");
		BOOST_FOREACH(const ptree::value_type& data, ptDatas)
		{
			std::string ip = data.second.get<std::string>("<xmlattr>.ip");
			bool match = data.second.get<bool>("<xmlattr>.match");
			vec.push_back(PairType(ip, match));
		}
	}

	return vec;
}

int main()
{
	PairVec vec = Load();

	boost::format fmt("%-20s%-9s%-6s");
	fmt %"IP" %"Result" %"Result";
	std::cout << fmt << std::endl;

	std::ip_match match;
	BOOST_FOREACH(PairType value, vec)
	{
		std::string str = value.first;
		bool isIp = value.second;
		match.set_value(str);

		fmt % str;
		fmt % (isIp == true ? "" : "FALSE");
		fmt % (match.validate() == true ? "" : "FALSE");
	
		std::cout << fmt << std::endl;
	}

	return 0;
}
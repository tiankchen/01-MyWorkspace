/*
 * ���ļ������������ε�ƥ�书��
 */

#pragma once

#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/address.hpp>

#include "util.hpp"

class NetWork
{
public:
	NetWork()
	{}

	/**
	 * @brief �����ʮ�����ַ�����ʽ��IP��ַת��������
	 */
	static unsigned long IP2Int(const std::string& ip)
	{
		boost::asio::ip::address addr;
		addr = addr.from_string(ip);
		boost::asio::ip::address_v4 addrV4 = addr.to_v4();
		return addrV4.to_ulong();
	}

	/**
	 * @brief ��������ʽ��IP��ַת���ɵ��ʮ�����ַ�����ʽ
	 * @param ul ������ʽ��IP��ַ
	 * @return ���ʮ������ʽ��IP��ַ
	 */
	static std::string Int2IP(unsigned long ul)
	{
		std::vector<int> con(4, 0);
		for (int i = 3; i >= 0; --i)
		{
			unsigned long temp = 1;
			for(int j = 0; j < i; ++j)
			{
				temp = temp * 256;
			} 
			con[i] = ul / temp;
			ul = ul % temp;
		}

		return boost::str(boost::format("%1%.%2%.%3%.%4%")
			% con[3] % con[2] % con[1] % con[0]);
	}

	/**
	 * @brief ����������Ϣ�ж����Ӧ��IP��ַ������
	 * @param ip �����
	 * @param netmask �������볤��
	 * @param lowIP��highIP �����еĵ�λ�͸�λIP��ַ
	 */
	static void ConvertNetBand(const std::string& ip, int netmask, unsigned long& lowIP, unsigned long& highIP)
	{
		using namespace std;

		unsigned long ip_i = IP2Int(ip);
		if (netmask == 0)
		{
			lowIP = 0;
			highIP = IP2Int("255.255.255.255");
		}
		else if (netmask == 32)
		{
			lowIP = ip_i;
			highIP = ip_i;
		}
		else
		{
			int shiftCount = 32 - netmask;
			unsigned long temp = ip_i >> shiftCount;
			lowIP = temp << shiftCount;
			highIP = lowIP + (0xFFFFFFFF >> netmask);
		}
	}
	static void ConvertNetBand(const std::string& ip, const std::string& netmask, unsigned long& lowIP, unsigned long& highIP)
	{
		int iNetmask = boost::lexical_cast<int>(netmask);
		ConvertNetBand(ip, iNetmask, lowIP, highIP);
	}

	/**
	 * @brief ��֤IP��ַ����������������Ƿ���ȷ
	 */
	static std::string ConvertToSQL(const std::string& str)
	{
		if (str.empty())
			return "";

		//1. ��һ��������ʽ�����β�ѯ������10.10.24.78/8��
		boost::regex rIPBand("(\\d+\.\\d+\.\\d+\.\\d+)/(\\d+)");
		boost::smatch mIPBand;
		if (boost::regex_match(str, mIPBand, rIPBand))
		{
			std::string ip = mIPBand[1].str();
			std::string netmask = mIPBand[2].str();
			unsigned long lowIP = 0, highIP = 0;
			ConvertNetBand(ip, netmask, lowIP, highIP);
			std::cout << "ip >= " + Int2IP(lowIP) + " AND <= " + Int2IP(highIP) << std::endl;
			return boost::str(
				boost::format("ip >= %1% AND ip <= %2%") % lowIP %highIP);
		}
		else
		{//�ڶ��֣�ǰ��ƥ�伴��
			return "ip like '" + str + "%'";
		}

		return "";
	}

	//Test

	void TestIP2Int()
	{
		using namespace std;
		typedef map<unsigned long, string> IPMapType;
	
		vector<string> vec = boost::assign::list_of
		("0.0.0.0")
			("0.0.0.1")
			("0.0.0.2")
			("0.0.0.3")
			("0.0.0.255")
			("0.0.1.0")
			("0.0.1.1")
			("0.0.1.255")
			("0.0.2.0")
			("0.0.2.1")
			("0.0.2.255")
			("10.10.24.78")
			("255.255.255.255")
			;

		BOOST_FOREACH(const string& ip, vec)
		{
			std::cout << "IP: " << ip;
			unsigned long i = IP2Int(ip);
			std::cout << " Number Type: " << i << " IP Type: " << Int2IP(i) << std::endl;
		}

	}

	void TestConvertToSQL()
	{
		using namespace std;
		
		StringVec vec = boost::assign::list_of("10.10")
			("aaa")
			("10.10.24.78/24")
			;

		BOOST_FOREACH(const std::string& str, vec)
		{
			std::cout << "Value is: " << str << ", Convert to SQL: " << ConvertToSQL(str) << std::endl;
		}

	}

	void Test3(int netmask)
	{
		std::cout << "netmask is: " << netmask << std::endl;
		using namespace std;
		string ip = "10.10.24.78";
		//int netmask = 24;
		unsigned long ip_i = IP2Int(ip);
		unsigned long ip_low = 0, ip_high = 0;
		if (netmask == 0)
		{
			ip_low = 0;
			ip_high = IP2Int("255.255.255.255");
		}	
		else if(netmask == 32)
		{
			ip_low = ip_i;
			ip_high = ip_i;
		}
		else
		{
			int shiftCount = 32 - netmask;
			unsigned long temp = ip_i >> shiftCount;
			ip_low = temp << shiftCount;
			ip_high = ip_low + (0xFFFFFFFF >> netmask);
		}
		std::cout << Int2IP(ip_low) << "-" << Int2IP(ip_high) << std::endl;	
	}



};

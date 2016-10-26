
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
		IP��ַ�ķ��ࣺ
		1. 0-9��һλ����λ��0-9��������ʽ��\d
		2. 10-99:  ��λ��ʮλ��1-9����λ��0-9��������ʽ��[1-9]\d
		3. 100-199: ��λ����λ��1��ʮλ��0-9����λ��0-9��������ʽ��1\d{2}
		4. 200-249: ��λ����λ��2��ʮλ��0-4����λ��0-9��������ʽ��2[0-4]\d
		5. 250-255: ��λ����λ��2��ʮλ��5����λ��0-5��������ʽ��25[0-5]

		���ϣ�
		0-99��������ʽ��[1-9]?\d
		0-199��������ʽ��(1\d{2})|([1-9]?\d)
		0-255��������ʽ��(1\d{2}) | ([1-9]?\d) | (2[0-4]\d) | (25[0-5])
		IP��ַ�ı��ʽΪ��
		((1\d{2}) | ([1-9]?\d) | (2[0-4]\d) | (25[0-5]) \.){3} ((1\d{2}) | ([1-9]?\d) | (2[0-4]\d) | (25[0-5]) \.)

		��ע��
		��		ƥ��ǰ��ı��ʽ1�λ���0��
		*		��ʾǰ��ı��ʽ�����ظ��������ظ�0��
		+		��ʾǰ��ı��ʽ�����ظ������������ظ�һ��
		\d ƥ�䵥�����֣�c++��ʹ��\\d��������ת��
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



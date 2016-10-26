/*
 * this file is used to test boost regex
 *
 * author: chenchen
 */


#include <util/config.hpp>
#include <boost/regex.hpp>
 //下面是一个异步模式的简单的Tcp echo服务器
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

#include <algorithm>

//int main()
//{
//	boost::regex reg("abc.*");
//	std::string strToMatch = "abc is matched!";
//	if (boost::regex_match(strToMatch, reg))
//	{
//		Cout("Matched!");
//	}
//	else
//	{
//		Cout("Not Matched!");
//	}
//
//	return 0;
//}

//电芯的编码规则
//void TestBatteryCore()
//{
//	boost::regex core_reg("AG\\d\\d{2}[0-6]\\d\\d{2}\\d{5}");
//
//	//<测试数据-是否合标>关系对
//	typedef std::pair<std::string, bool> TestValueType;
//	typedef std::vector<TestValueType> ValueVecType;
//
//	ValueVecType values = boost::assign::list_of
//	(std::make_pair("AG212420900130", true))
//		(std::make_pair("CG212420900130", false))
//		(std::make_pair("AG21242090013", false))
//		(std::make_pair("AG212720900130", false))
//		;
//
//	BOOST_FOREACH(ValueVecType::value_type value, values)
//	{
//		std::string test_value = value.first;
//		bool test_result = value.second;
//		bool result = boost::regex_match(test_value, core_reg);
//	
//		std::cout << "Test Value: " << test_value
//			<< ", Hope Result: " << test_result
//			<< ", Real Result: " << result
//			<< (test_result == result ? " Yes!" : " No!") << std::endl;
//	}
//
//}
//
////电池的编码规则
//void TestBattery()
//{
//	boost::regex battery_reg("N[A-Z]\\d{2}K[A-Z]\\d{2}B\\d{4}");
//
//	//<测试数据-是否合标>关系对
//	typedef std::pair<std::string, bool> TestValueType;
//	typedef std::vector<TestValueType> ValueVecType;
//
//	ValueVecType values = boost::assign::list_of
//	(std::make_pair("NJ26KJ26B0001", true))
//		(std::make_pair("NJ26KJ26B000", false))
//		(std::make_pair("CJ26CJ26B0001", false))
//		;
//
//
//	BOOST_FOREACH(ValueVecType::value_type value, values)
//	{
//		std::string test_value = value.first;
//		bool test_result = value.second;
//		bool result = boost::regex_match(test_value, battery_reg);
//
//		std::cout << "Test Value: " << test_value
//			<< ", Hope Result: " << test_result
//			<< ", Real Result: " << result
//			<< (test_result == result ? " Yes!" : " No!") << std::endl;
//	}
//
//}

//
///*
// `@brief 电芯检测
// */
//bool CheckBatteryCore(const std::string& barCode, const std::string& type, std::string date,)
//{
//
//}



using namespace boost::asio;
using boost::system::error_code;
using ip::tcp;

struct CHelloWorld_Service
{
	//类的初始化创建：设置io_service, 设置1000端口
	CHelloWorld_Service(io_service &iosev)
		:m_iosev(iosev), m_acceptor(iosev, tcp::endpoint(tcp::v4(), 1000))
	{
	}

	//创建一个tcp的socket；且还是侦听
	void start()
	{
		// 开始等待连接（非阻塞）
		boost::shared_ptr<tcp::socket> psocket(new tcp::socket(m_iosev));

		// 触发的事件只有error_code参数，所以用boost::bind把socket绑定进去
		m_acceptor.async_accept(*psocket, boost::bind(&CHelloWorld_Service::accept_handler, this, psocket, _1));
	}

	// 有客户端连接时accept_handler触发
	void accept_handler(boost::shared_ptr<tcp::socket> psocket, error_code ec)
	{
		if (ec) return;

		// 继续等待连接
		start();

		// 显示远程IP
		std::cout << psocket->remote_endpoint().address() << std::endl;

		// 发送信息(非阻塞)
		boost::shared_ptr<std::string> pstr(new std::string("hello async world!"));
		psocket->async_write_some(buffer(*pstr),
			boost::bind(&CHelloWorld_Service::write_handler, this, pstr, _1, _2)
		);
	}

	// 异步写操作完成后write_handler触发
	void write_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred)
	{
		if (ec)
			std::cout << "发送失败!" << std::endl;
		else
			std::cout << *pstr << " 已发送" << std::endl;
	}

private:
	io_service &m_iosev;
	ip::tcp::acceptor m_acceptor;
};



int main(int argc, char* argv[])
{
	boost::format fmt("%02d");
	std::string str("4");

	std::cout << boost::str(fmt%str) << std::endl;

	return 0;
}
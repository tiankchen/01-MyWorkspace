#include <vector>

#include <iostream>
#include <boost/format.hpp>
#include <boost/any.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>

namespace config
{
	class cc
	{};

	namespace config2
	{
		class bb
		{};
	}
}

class Test
{
public:
	template<typename T>
	Test(const std::string& key, const T& t)
		: m_key(key)
		, m_value(t)
	{
		
	}

	template<typename T>
	bool GetValue(T& t)
	{
		try
		{
			t = boost::any_cast<T>(m_value);
		}
		catch (boost::bad_any_cast& castError)
		{
			std::cout << "cast error: " << castError.what() << std::endl;
			return false;
		}

		return true;
	}

private:
	std::string m_key;
	boost::any m_value;
};


void Trim(std::string& str, const std::string& tag)
{
	std::size_t pos = str.find_last_not_of(tag);
	if (pos != str.npos)
	{
		str.erase(pos + 1);
	}

	pos = str.find_first_not_of(tag);
	if (pos != str.npos)
	{
		str.erase(0, pos);
	}
}



void TestTime()
{
	using namespace boost::posix_time;
	using namespace boost::gregorian;

	typedef std::vector<time_duration> TimeVec;

	time_duration t(8, 0, 0);

	time_duration begin(9, 30, 0);
	time_duration end(15, 30, 0);
	time_duration INTERVAL(0, 15, 0);

	time_duration MAX(16, 0, 0);
	
	while (t < MAX)
	{
		if (t < begin)
		{
			std::cout << t << std::endl;
		}
		else
		{
			int i = (t - begin).total_seconds();
			int interval = INTERVAL.total_seconds();
			int count = (i / interval) + 1;
			time_duration result = begin + seconds(count*interval);
			std::cout << t << " | " << result << " | " << count << std::endl;
		}

		t = t + minutes(10);
	}

}

int main()
{
	TestTime();

	return 0;
}

#include "test_array.hpp"
#include "func_template.hpp"

#include <boost/config.hpp>

#define Cout1(str) std::cout << str << std::endl;
#define Cout2(str) std::cout << str << std::endl;
#define Cout12(str) Cout1(str) Cout2(str)

int main()
{
	Cout12(BOOST_VERSION)

	return 0;
}
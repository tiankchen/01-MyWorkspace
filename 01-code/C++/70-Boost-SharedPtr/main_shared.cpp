// test boost shared_ptr
// author chenchen

#include <util/config.hpp>
#include <70-Boost-SharedPtr/test_sp_element.hpp>

void Test1()
{
	using namespace boost;

	typedef shared_ptr<int> IntPtr;
	IntPtr pInt(new int(2));
	IntPtr pInt2(pInt);
}


int main()
{
	Test1();
	return 0;
}
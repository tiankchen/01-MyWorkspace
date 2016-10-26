// this file is used to test sp_element

namespace chenchen
{

//sp is short form of smart pointor

template<class T> struct sp_element
{
	typedef T type;
};

//class Test, used to test some features
template<class T> class Test
{
public:

	Test() noexcept
	{
	}

	template<class Y>
	Test(Y* p)
	{
	}

};

}
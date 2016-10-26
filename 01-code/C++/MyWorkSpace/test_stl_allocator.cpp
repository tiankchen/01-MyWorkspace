
#include <util/config.hpp>

// author chenchen
// to test std::allocator some functions

class __default_alloc_template
{
public:
	enum { __ALIGN = 8 };					//小型区块的上调边界
	enum { __MAX_BYTES = 128 };		//小型区块的上限
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };	//free-list 个数

	//将bytes上调至8的倍数
	static size_t RoundUp(size_t bytes)
	{
		return ((bytes + (__ALIGN - 1)) & ~(__ALIGN - 1));
	}

	//根据区块大小，决定使用第n号区块，n从0开始计算
	static size_t FreeListIndex(size_t bytes)
	{
		return (bytes + __ALIGN - 1) / __ALIGN - 1;

	}
};


int main()
{
	std::vector<int> vec;
	for (int i = 0; i < 50; ++i)
	{
		vec.push_back(i);
	}

	BOOST_FOREACH(int i, vec)
	{
		std::cout << "Num: " << i << ", " << __default_alloc_template::FreeListIndex(i) << std::endl;
	}
	
	return 0;
}

#include <util/config.hpp>

// author chenchen
// to test std::allocator some functions

class __default_alloc_template
{
public:
	enum { __ALIGN = 8 };					//С��������ϵ��߽�
	enum { __MAX_BYTES = 128 };		//С�����������
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };	//free-list ����

	//��bytes�ϵ���8�ı���
	static size_t RoundUp(size_t bytes)
	{
		return ((bytes + (__ALIGN - 1)) & ~(__ALIGN - 1));
	}

	//���������С������ʹ�õ�n�����飬n��0��ʼ����
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
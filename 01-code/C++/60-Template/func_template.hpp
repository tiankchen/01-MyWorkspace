// this file is used to test func template

#ifndef FUNC_TEMPLATE_INCLUDE_H
#define FUNC_TEMPLATE_INCLUDE_H

namespace chenchen
{

template <typename T>
class stack
{
public:
	stack(int i)
		: m_i(i)
	{}

	template<typename T2>
	stack<T>& swap(stack<T2>& op2)
	{
		if ((void*)this == (void*)&op2)
		{
			return *this;
		}

		int tmp = m_i;
		m_i = op2.m_i;
		op2.m_i = tmp;
		return *this;
	}

private:
	int m_i;
};

}

#endif
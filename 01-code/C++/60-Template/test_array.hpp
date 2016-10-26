// test int a[], int a*

#pragma once

#include <util/config.hpp>

template<typename T> struct ArrayTest
{
	void Print()
	{
		Cout("I am normal");
	}
};

//template<typename T> struct ArrayTest<T[]>
//{
//	void Print()
//	{
//		Cout("T [] template");
//	}
//};
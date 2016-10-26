

#ifndef CHEN_CHEN_TRAIT_INCLUDE
#define CHEN_CHEN_TRAIT_INCLUDE

#include <string>
#include <iostream>

class Gateway
{};

class Member
{};

class ExUnit
{};

template<typename T>
class MonObjectTrait;

template<>
class MonObjectTrait<Gateway>
{
public:
	static std::string GetLoginRecordType()
	{
		return "TWCJXGateway";
	}
};

template<>
class MonObjectTrait<Member>
{
public:
	static std::string GetLoginRecordType()
	{
		return "TWCJXMember";
	}
};

template<>
class MonObjectTrait<ExUnit>
{
public:
	static std::string GetLoginRecordType()
	{
		return "TWCJXExUnit";
	}
};

template<typename T>
class MonObjectTrait
{
public:
	static std::string GetLoginRecordType()
	{
		return "UNKNOWN TYPE";
	}
};


#endif
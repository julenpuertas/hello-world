#include <sstream>
#include <algorithm>
#include "String.h"

namespace Engine
{
	void String::to_uppercase()
	{
		const iterator it_begin = begin();
		std::transform(it_begin, end(), it_begin, &toupper);
	}

	String String::get_to_uppercase() const
	{
		String copy = *this;
		copy.to_uppercase();
		return copy;
	}

	void String::to_lowercase()
	{
		const iterator it_begin = begin();
		std::transform(it_begin, end(), it_begin, &tolower);
	}

	String String::get_to_lowercase() const
	{
		String copy = *this;
		copy.to_lowercase();
		return copy;
	}

	String& String::operator+=(const std::string& rhs)
	{
		std::string& ref_this = *this;
		ref_this += rhs;
		return *this;
	}

	String String::operator+(const std::string& rhs)
	{
		std::string& ref_this = *this;
		return ref_this + rhs;
	}

#define STRING_OP_IMPL(type)					\
String& String::operator+=(type rhs)			\
{												\
	*this += std::to_string(rhs);				\
	return *this;								\
}												\
String String::operator+(type rhs) const		\
{												\
	return *this + std::to_string(rhs);			\
}												\
String operator+(type lhs, const String& rhs)	\
{												\
	return std::to_string(lhs) + rhs;			\
}												\
String::operator type() const					\
{												\
	std::stringstream ss(*this);				\
	type result;								\
	ss >> result;								\
	return result;								\
}

	STRING_OP_IMPL(bool);
	STRING_OP_IMPL(short);
	STRING_OP_IMPL(unsigned short);
	STRING_OP_IMPL(int);
	STRING_OP_IMPL(unsigned);
	STRING_OP_IMPL(long);
	STRING_OP_IMPL(unsigned long);
	STRING_OP_IMPL(long long);
	STRING_OP_IMPL(unsigned long long);
	STRING_OP_IMPL(float);
	STRING_OP_IMPL(double);
	STRING_OP_IMPL(long double);
}

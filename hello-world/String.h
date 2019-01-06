#pragma once
#include <string_view>

namespace Engine
{
	class String : public std::string
	{
	public:
		using View = std::string_view;

		template <typename ... Args> String(Args&& ... arguments);

		void to_uppercase();
		String get_to_uppercase() const;

		void to_lowercase();
		String get_to_lowercase() const;

		String& operator+=(const std::string& rhs);
		String operator+(const std::string& rhs);

#define	STRING_OP_DECL(type)		\
String& operator+=(type rhs);		\
String operator+(type rhs) const;	\
explicit operator type() const

		STRING_OP_DECL(bool);
		STRING_OP_DECL(short);
		STRING_OP_DECL(unsigned short);
		STRING_OP_DECL(int);
		STRING_OP_DECL(unsigned);
		STRING_OP_DECL(long);
		STRING_OP_DECL(unsigned long);
		STRING_OP_DECL(long long);
		STRING_OP_DECL(unsigned long long);
		STRING_OP_DECL(float);
		STRING_OP_DECL(double);
		STRING_OP_DECL(long double);

#undef STRING_OP_DECL
	};

#define	STRING_OP_DECL(type) String operator+(type lhs, const String& rhs)

	STRING_OP_DECL(bool);
	STRING_OP_DECL(short);
	STRING_OP_DECL(unsigned short);
	STRING_OP_DECL(int);
	STRING_OP_DECL(unsigned);
	STRING_OP_DECL(long);
	STRING_OP_DECL(unsigned long);
	STRING_OP_DECL(long long);
	STRING_OP_DECL(unsigned long long);
	STRING_OP_DECL(float);
	STRING_OP_DECL(double);
	STRING_OP_DECL(long double);

#undef STRING_OP_DECL
}

#include "String.inl"

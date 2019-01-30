#pragma once
#include "Byte.h"

namespace Engine
{
	namespace Random
	{
		template<typename T> T get();
		template<> bool get<bool>();

#define RANDOM_FUNCTION_DECLARATION(type)				\
		template<> type get<type>();					\
		template<> type get<type>(type min, type max)

		namespace Uniform
		{
			template<typename T> T get();
			template<typename T> T get(T min, T max);

			RANDOM_FUNCTION_DECLARATION(char);
			RANDOM_FUNCTION_DECLARATION(unsigned char);
			RANDOM_FUNCTION_DECLARATION(short);
			RANDOM_FUNCTION_DECLARATION(unsigned short);
			RANDOM_FUNCTION_DECLARATION(int);
			RANDOM_FUNCTION_DECLARATION(unsigned);
			RANDOM_FUNCTION_DECLARATION(long);
			RANDOM_FUNCTION_DECLARATION(unsigned long);
			RANDOM_FUNCTION_DECLARATION(long long);
			RANDOM_FUNCTION_DECLARATION(unsigned long long);
			RANDOM_FUNCTION_DECLARATION(float);
			RANDOM_FUNCTION_DECLARATION(double);
			RANDOM_FUNCTION_DECLARATION(long double);
		}

		namespace Normal
		{
			template<typename T> T get();
			template<typename T> T get(T min, T max);

			RANDOM_FUNCTION_DECLARATION(float);
			RANDOM_FUNCTION_DECLARATION(double);
			RANDOM_FUNCTION_DECLARATION(long double);
		}

#undef RANDOM_FUNCTION_DECLARATION
	}
}

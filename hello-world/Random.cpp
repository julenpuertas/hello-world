#include <chrono>
#include <random>
#include "Random.h"

namespace
{
	std::default_random_engine g_rng(static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

namespace Engine
{
	namespace Random
	{
		template<> bool get<bool>()
		{
			return Uniform::get<int>() % 2 == 0;
		}

#define CHAR_RANDOM_FUNCTION_IMPLEMENTATION(type)												\
		template<> type get<type>()																\
		{																						\
			return get(std::numeric_limits<type>::lowest(), std::numeric_limits<type>::max());	\
		}																						\
																								\
		template<> type get<type>(type min, type max)											\
		{																						\
			return static_cast<type>(get(static_cast<int>(min), static_cast<int>(max)));		\
		}

#define RANDOM_FUNCTION_IMPLEMENTATION(distribution_fn, type)									\
		template<> type get<type>()																\
		{																						\
			return get(std::numeric_limits<type>::lowest(), std::numeric_limits<type>::max());	\
		}																						\
																								\
		template<> type get<type>(type min, type max)											\
		{																						\
			return distribution_fn<type>(min, max)(g_rng);										\
		}

#define FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(distribution_fn, type)	\
		template<> type get<type>()									\
		{															\
			return get(static_cast<type>(0), static_cast<type>(1));	\
		}															\
																	\
		template<> type get<type>(type min, type max)				\
		{															\
			return distribution_fn<type>(min, max)(g_rng);			\
		}

		namespace Uniform
		{
			CHAR_RANDOM_FUNCTION_IMPLEMENTATION(char);
			CHAR_RANDOM_FUNCTION_IMPLEMENTATION(unsigned char);

			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, short);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, unsigned short);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, int);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, unsigned);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, long);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, unsigned long);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, long long);
			RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_int_distribution, unsigned long long);

			FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_real_distribution, float);
			FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_real_distribution, double);
			FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(std::uniform_real_distribution, long double);
		}

		namespace Normal
		{
			FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(std::normal_distribution, float);
			FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(std::normal_distribution, double);
			FLOAT_RANDOM_FUNCTION_IMPLEMENTATION(std::normal_distribution, long double);
		}
	}
}

#pragma once

namespace Engine
{
	namespace Math
	{
		namespace Division
		{
			template <typename T> class Result
			{
				int dividend_;
				T reminder_;

			public:
				constexpr Result(T quotient, T divisor);

				constexpr int get_dividend() const;
				constexpr T get_reminder() const;
			};

			template <typename T> constexpr Result<T> compute(T quotient, T divisor);
		}
	}
}

#include "Division.inl"

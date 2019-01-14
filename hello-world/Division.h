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
				Result(T quotient, T divisor);

				int get_dividend() const;
				T get_reminder() const;
			};

			template <typename T> Result<T> compute(T quotient, T divisor);
		}
	}
}

#include "Division.inl"

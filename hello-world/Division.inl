
namespace Engine
{
	namespace Math
	{
		namespace Division
		{
			template<typename T> Result<T>::Result(T quotient, T divisor)
				: dividend_(static_cast<int>(quotient / divisor))
				, reminder_(quotient - divisor * dividend_)
			{}

			template<typename T> int Result<T>::get_dividend() const
			{
				return dividend_;
			}

			template<typename T> T Result<T>::get_reminder() const
			{
				return reminder_;
			}

			template<typename T> Result<T> compute(T quotient, T divisor)
			{
				return Result<T>(quotient, divisor);
			}
		}
	}
}

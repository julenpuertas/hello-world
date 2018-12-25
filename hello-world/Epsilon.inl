#include <glm/gtc/epsilon.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> constexpr T get_epsilon()
		{
			return static_cast<T>(EPSILON);
		}

		template <typename T> bool is_zero(const T& number, const T& epsilon)
		{
			return is_equal(number, static_cast<T>(0), epsilon);
		}

		template <typename T> bool is_equal(const T& lhs, const T& rhs, const T& epsilon)
		{
			return glm::epsilonEqual(lhs, rhs, epsilon);
		}
	}
}

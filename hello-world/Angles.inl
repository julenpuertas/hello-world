#include <glm/trigonometric.hpp>

namespace Engine
{
	namespace Math
	{
		namespace Angle
		{
			template<typename T> constexpr T degrees_to_radians(T degrees)
			{
				return glm::radians(degrees);
			}

			template<typename T> constexpr T radians_to_degrees(T radians)
			{
				return glm::degrees(radians);
			}
		}
	}
}

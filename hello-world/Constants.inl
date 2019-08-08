#include <glm/gtc/constants.hpp>

namespace Engine
{
	namespace Math
	{
		template<typename T> constexpr T sqrt_2()
		{
			return glm::root_two<T>();
		}
	}
}

#pragma once

namespace Engine
{
	namespace Math
	{
		namespace Angle
		{
			template <typename T> constexpr T degrees_to_radians(T degrees);
			template <typename T> constexpr T radians_to_degrees(T radians);
		}
	}
}

#include "Angles.inl"

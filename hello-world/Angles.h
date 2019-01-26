#pragma once

namespace Engine
{
	namespace Math
	{
		namespace Angle
		{
			template <typename T> T degrees_to_radians(T degrees);
			template <typename T> T radians_to_degrees(T radians);
			template<typename T>
			T degrees_to_radians(T degrees)
			{
				return T();
			}
			template<typename T>
			T radians_to_degrees(T radians)
			{
				return T();
			}
		}
	}
}

#include "Angles.inl"

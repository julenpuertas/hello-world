#pragma once

namespace Engine
{
	namespace Math
	{
		constexpr float EPSILON = 1e-4f;

		template <typename T> constexpr T get_epsilon();
		template <typename T> bool is_zero(const T& number, const T& epsilon = get_epsilon<T>());
		template <typename T> bool is_equal(const T& lhs, const T& rhs, const T& epsilon = get_epsilon<T>());
	}
}

#include "Epsilon.inl"

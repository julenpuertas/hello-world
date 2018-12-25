#pragma once
#include "Vector.h"
#include "VectorAdapter.h"
#include <glm/vec2.hpp>

namespace Engine
{
	namespace Math
	{
		template<typename T> struct Vector<T, 2> : public VectorAdapter<Vector, T, 2, glm::tvec2>
		{
			static const Vector<T, 2> RIGHT;
			static const Vector<T, 2> UP;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <typename U, glm::precision P> Vector(glm::tvec2<U, P>&& rhs);
		};
	}
}

#include "Vector2.inl"

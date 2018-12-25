#pragma once
#include "Vector.h"
#include "ExtendedGLMVector.h"
#include <glm/vec4.hpp>

namespace Engine
{
	namespace Math
	{
		template<typename T> struct Vector<T, 4> : public ExtendedGLMVector<Vector, T, 4, glm::tvec4>
		{
			static const Vector<T, 4> RIGHT;
			static const Vector<T, 4> UP;
			static const Vector<T, 4> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <typename U, glm::precision P> Vector(glm::tvec4<U, P>&& rhs);
		};
	}
}

#include "Vector4.inl"

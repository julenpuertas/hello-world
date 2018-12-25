#pragma once
#include "Vector.h"
#include "ExtendedGLMVector.h"
#include <glm/vec3.hpp>

namespace Engine
{
	namespace Math
	{
		template<typename T> struct Vector<T, 3> : public ExtendedGLMVector<Vector, T, 3, glm::tvec3>
		{
			static const Vector<T, 3> RIGHT;
			static const Vector<T, 3> UP;
			static const Vector<T, 3> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <typename U, glm::precision P> Vector(glm::tvec3<U, P>&& rhs);

			Vector<T, 3> cross(const Vector<T, 3>& rhs) const;
		};
	}

	using FVector3 = Math::Vector<float, 3>;
}

#include "Vector3.inl"

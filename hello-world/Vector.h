#pragma once

#include "Array.h"
#include "ExtendedGLMVector.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T, size_t N> class Vector : public Array<T, N>
		{
			explicit Vector(glm::ctor uninitialize_flag);

		public:
			template <typename U> explicit Vector(const U& default_value = U());
			Vector operator+(const Vector& rhs) const;
		};

		template<typename T> struct Vector<T, 2> : public ExtendedGLMVector<Vector, T, 2, glm::tvec2>
		{
			static const Vector<T, 2> RIGHT;
			static const Vector<T, 2> UP;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <typename U, glm::precision P> Vector(glm::tvec2<U, P>&& rhs);
		};

		template<typename T> struct Vector<T, 3> : public ExtendedGLMVector<Vector, T, 3, glm::tvec3>
		{
			static const Vector<T, 3> RIGHT;
			static const Vector<T, 3> UP;
			static const Vector<T, 3> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <typename U, glm::precision P> Vector(glm::tvec3<U, P>&& rhs);

			Vector<T, 3> cross(const Vector<T, 3>& rhs) const;
		};

		template<typename T> struct Vector<T, 4> : public ExtendedGLMVector<Vector, T, 4, glm::tvec4>
		{
			static const Vector<T, 4> RIGHT;
			static const Vector<T, 4> UP;
			static const Vector<T, 4> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <typename U, glm::precision P> Vector(glm::tvec4<U, P>&& rhs);
		};
	}

	using FVector3 = Math::Vector<float, 3>;
	using FVector4 = Math::Vector<float, 4>;
}

#include "Vector.inl"

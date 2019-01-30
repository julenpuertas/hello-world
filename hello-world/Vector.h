#pragma once

#include "GLMVectorWrapper.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T, size_t N> class Vector
		{
		};

		template<typename T> struct Vector<T, 2> : public GLMVectorWrapper<Vector, T, 2, glm::tvec2>
		{
			static const Vector<T, 2> RIGHT;
			static const Vector<T, 2> UP;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <glm::precision P> Vector(const glm::tvec2<T, P>& rhs);
		};

		template<typename T> struct Vector<T, 3> : public GLMVectorWrapper<Vector, T, 3, glm::tvec3>
		{
			static const Vector<T, 3> RIGHT;
			static const Vector<T, 3> UP;
			static const Vector<T, 3> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <glm::precision P> Vector(const glm::tvec3<T, P>& rhs);

			Vector<T, 3> cross(const Vector<T, 3>& rhs) const;
		};

		template<typename T> struct Vector<T, 4> : public GLMVectorWrapper<Vector, T, 4, glm::tvec4>
		{
			static const Vector<T, 4> RIGHT;
			static const Vector<T, 4> UP;
			static const Vector<T, 4> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			template <glm::precision P> Vector(const glm::tvec4<T, P>& rhs);
		};
	}

	using SVector2 = Math::Vector<size_t, 2>;
	using FVector2 = Math::Vector<float, 2>;
	using FVector3 = Math::Vector<float, 3>;
	using FVector4 = Math::Vector<float, 4>;
}

#include "Vector.inl"

#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include <glm/mat4x3.hpp>

namespace Engine
{
	namespace Math
	{
		template <typename T> struct Matrix<T, 3, 4> : public glm::tmat4x3<T>
		{
			template <typename ... Args> explicit Matrix(Args&& ... args);
			template <typename U, glm::precision P> Matrix(glm::tmat4x3<U, P>&& rhs);
			Vector<T, 3> operator*(const Vector<T, 3>& rhs) const;
		};
	}
}

#include "Matrix3x4.inl"

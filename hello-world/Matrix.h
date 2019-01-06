#pragma once

#include "ExtendedGLMMatrix.h"
#include "Vector.h"

namespace Engine
{
	namespace Math
	{
		template<typename T, size_t ROW_COUNT, size_t COLUMN_COUNT> class Matrix
		{
		};

		template <typename T> struct Matrix<T, 3, 3> : public ExtendedGLMMatrix<Matrix, T, 3, 3, glm::tmat3x3>
		{
			template <typename ... Args> explicit Matrix(Args&& ... args);
			template <glm::precision P> Matrix(glm::tmat3x3<T, P>&& rhs);
		};

		template <typename T> struct Matrix<T, 3, 4> : public ExtendedGLMMatrix<Matrix, T, 3, 4, glm::tmat4x3>
		{
			template <typename ... Args> explicit Matrix(Args&& ... args);
			template <glm::precision P> Matrix(glm::tmat4x3<T, P>&& rhs);
			Vector<T, 3> operator*(const Vector<T, 3>& rhs) const;
		};
	}

	using FMatrix3 = Math::Matrix<float, 3, 3>;
	using FMatrix3x4 = Math::Matrix<float, 3, 4>;
}

#include "Matrix.inl"

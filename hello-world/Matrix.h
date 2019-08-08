#pragma once
#include "GLMMatrixWrapper.h"
#include "Vector.h"

namespace Engine
{
	namespace Math
	{
		template<typename T, size_t ROW_COUNT, size_t COLUMN_COUNT> class Matrix
		{};

		template <typename T> struct Matrix<T, 3, 3> : public GLMMatrixWrapper<Matrix, T, 3, 3, glm::tmat3x3>
		{
			template <typename ... Args> explicit Matrix(Args&& ... args);
			template <glm::precision P> Matrix(const glm::tmat3x3<T, P>& rhs);
		};

		template <typename T> struct Matrix<T, 3, 4> : public GLMMatrixWrapper<Matrix, T, 3, 4, glm::tmat4x3>
		{
			template <typename ... Args> explicit Matrix(Args&& ... args);
			template <glm::precision P> Matrix(const glm::tmat4x3<T, P>& rhs);
			Vector<T, 3> operator*(const Vector<T, 3>& rhs) const;
		};

		template <typename T> struct Matrix<T, 4, 4> : public GLMMatrixWrapper<Matrix, T, 4, 4, glm::tmat4x4>
		{
			template <typename ... Args> explicit Matrix(Args&& ... args);
			template <glm::precision P> Matrix(const glm::tmat4x4<T, P>& rhs);
		};
	}

	using FMatrix3 = Math::Matrix<float, 3, 3>;
	using FMatrix3x4 = Math::Matrix<float, 3, 4>;
	using FMatrix4 = Math::Matrix<float, 4, 4>;
}

#include "Matrix.inl"

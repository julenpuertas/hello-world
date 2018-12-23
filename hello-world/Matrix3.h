#pragma once
#include "Matrix.h"
#include <glm/mat3x3.hpp>

template <typename T> struct Matrix<T, 3, 3> : public glm::tmat3x3<T>
{
	template <typename ... Args> explicit Matrix(Args&& ... args);
	template <typename U, glm::precision P> Matrix(glm::tmat3x3<U, P>&& rhs);
};

#include "Matrix3.inl"

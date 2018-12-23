#include "Vector4.h"

template <typename T> template <typename ... Args> Matrix<T, 3, 4>::Matrix(Args&& ... args)
	: glm::tmat4x3<T>(std::forward<Args>(args)...)
{}

template <typename T> template <typename U, glm::precision P> Matrix<T, 3, 4>::Matrix(glm::tmat4x3<U, P>&& rhs)
	: glm::tmat4x3<T>(std::forward<glm::tmat4x3<U, P> >(rhs))
{}

template <typename T> Vector<T, 3> Matrix<T, 3, 4>::operator*(const Vector<T, 3>& rhs) const
{
	return *this * Vector<T, 4>(rhs, 1);
}

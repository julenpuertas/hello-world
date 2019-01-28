#include "GLMMatrixWrapper.h"

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		template <typename ... Args> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::GLMMatrixWrapper(Args&& ... args)
			: matrix_(std::forward<Args>(args)...)
		{}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixT<T, P>::col_type& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator[](size_t column_index)
		{
			return matrix_[column_index];
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		const typename GLMMatrixT<T, P>::col_type& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator[](size_t column_index) const
		{
			return matrix_[column_index];
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator-() const
		{
			return -matrix_;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator+(const MatrixT<T, M, N>& rhs) const
		{
			return matrix_ + rhs.matrix_;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator+=(const MatrixT<T, M, N>& rhs)
		{
			matrix_ += rhs.matrix_;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator-(const MatrixT<T, M, N>& rhs) const
		{
			return matrix_ + rhs.matrix_;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator-=(const MatrixT<T, M, N>& rhs)
		{
			matrix_ -= rhs.matrix_;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		template<size_t O> MatrixT<T, M, O> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*(const MatrixT<T, N, O>& rhs) const
		{
			return matrix_ * rhs.matrix_;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*=(const MatrixT<T, M, N>& rhs)
		{
			matrix_ *= rhs.matrix_;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*(const T & rhs) const
		{
			return matrix_ * rhs;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N>& GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*=(const T & rhs)
		{
			matrix_ *= rhs;
			return *reinterpret_cast<MatrixT<T, M, N>*>(this);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		Vector<T, M> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::operator*(const Vector<T, N>& rhs) const
		{
			return matrix_ * rhs.vector_;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		T GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_trace() const
		{
			T trace(0);
			for (size_t i = 0; i < WIDTH; ++i)
				trace += matrix_[i][i];

			return trace;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		T GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_determinant() const
		{
			return glm::determinant(matrix_);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::scalar_product(const MatrixT<T, M, N>& rhs) const
		{
			return glm::matrixCompMult(matrix_, rhs.matrix_);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, N, M> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_transpose() const
		{
			return glm::transpose(matrix_);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_inverse() const
		{
			return glm::inverse(matrix_);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::get_absolute() const
		{
			MatrixT<T, M, N> result(glm::ctor::uninitialize);

			for (size_t i = 0; i < WIDTH; ++i)
				result[i] = glm::abs(matrix_[i]);

			return result;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		bool GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::is_zero(const T& epsilon) const
		{
			return is_equal(glm::zero<GLMMatrixT<T, P> >(), epsilon);
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		bool GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::equals(const MatrixT<T, M, N>& rhs, const T& epsilon) const
		{
			bool equal = true;
			for (size_t i = 0; equal && i < WIDTH; ++i)
				equal &= glm::all(glm::epsilonEqual(matrix_[i], rhs.matrix_[i], epsilon));

			return equal;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::begin()
		{
			return &matrix_[0][0];
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::end()
		{
			return begin() + WIDTH * HEIGTH;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::begin() const
		{
			return &matrix_[0][0];
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::end() const
		{
			return begin() + WIDTH * HEIGTH;
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::cbegin() const
		{
			return begin();
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		typename GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::const_iterator GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>::cend() const
		{
			return end();
		}

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> operator*(const T & lhs, const GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>& rhs)
		{
			return rhs * lhs;
		}
	}
}

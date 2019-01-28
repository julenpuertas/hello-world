#pragma once

#include "Vector.h"

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P = glm::defaultp>
		class GLMMatrixWrapper
		{
		protected:
			GLMMatrixT<T, P> matrix_;

			template <typename ... Args> explicit GLMMatrixWrapper(Args&& ... args);

		public:
			using iterator = T*;
			using const_iterator = const T*;

			static constexpr size_t WIDTH = N;
			static constexpr size_t HEIGTH = M;

			typename GLMMatrixT<T, P>::col_type& operator[](size_t column_index);
			const typename GLMMatrixT<T, P>::col_type& operator[](size_t column_index) const;

			MatrixT<T, M, N> operator-() const;

			MatrixT<T, M, N> operator+(const MatrixT<T, M, N>& rhs) const;
			MatrixT<T, M, N>& operator+=(const MatrixT<T, M, N>& rhs);

			MatrixT<T, M, N> operator-(const MatrixT<T, M, N>& rhs) const;
			MatrixT<T, M, N>& operator-=(const MatrixT<T, M, N>& rhs);

			template <size_t O> MatrixT<T, M, O> operator*(const MatrixT<T, N, O>& rhs) const;
			MatrixT<T, M, N>& operator*=(const MatrixT<T, M, N>& rhs);

			MatrixT<T, M, N> operator*(const T& rhs) const;
			MatrixT<T, M, N>& operator*=(const T& rhs);
			Vector<T, M> operator*(const Vector<T, N>& rhs) const;

			T get_trace() const;
			T get_determinant() const;
			MatrixT<T, M, N> scalar_product(const MatrixT<T, M, N>& rhs) const;
			MatrixT<T, N, M> get_transpose() const;
			MatrixT<T, M, N> get_inverse() const;
			MatrixT<T, M, N> get_absolute() const;

			bool is_zero(const T& epsilon = get_epsilon<T>()) const;
			bool equals(const MatrixT<T, M, N>& rhs, const T& epsilon = get_epsilon<T>()) const;

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			const_iterator cbegin() const;
			const_iterator cend() const;
		};

		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename GLMMatrixT, glm::precision P>
		MatrixT<T, M, N> operator*(const T& lhs, const GLMMatrixWrapper<MatrixT, T, M, N, GLMMatrixT, P>& rhs);
	}
}

#include "GLMMatrixWrapper.inl"

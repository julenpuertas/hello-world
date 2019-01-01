#pragma once

#include "Epsilon.h"

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t, size_t> typename MatrixT, typename T, size_t M, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P = glm::defaultp>
		class ExtendedGLMMatrix : public BaseT<T, P>
		{
		protected:
			template <typename ... Args> explicit ExtendedGLMMatrix(Args&& ... args);

		public:
			using iterator = T * ;
			using const_iterator = const T *;

			static constexpr size_t WIDTH = N;
			static constexpr size_t HEIGTH = M;

			T get_trace() const;
			T get_determinant() const;
			MatrixT<T, M, N> scalar_product(const MatrixT<T, M, N>& rhs) const;
			MatrixT<T, N, M> get_transpose() const;
			MatrixT<T, M, N> get_inverse() const;
			MatrixT<T, M, N> get_absolute() const;

			bool is_zero(const T& epsilon = get_epsilon<T>()) const;
			bool is_equal(const MatrixT<T, M, N>& rhs, const T& epsilon = get_epsilon<T>()) const;

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			const_iterator cbegin() const;
			const_iterator cend() const;
		};
	}
}

#include "ExtendedGLMMatrix.inl"

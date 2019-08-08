#pragma once
#include "Axis.h"
#include "Epsilon.h"

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P = glm::defaultp>
		class GLMVectorWrapper : public GLMVectorT<T, P>
		{
		protected:
			template <typename ... Args> explicit GLMVectorWrapper(Args&& ... args);
			explicit GLMVectorWrapper(Axis axis);

		public:
			using iterator = T * ;
			using const_iterator = const T*;

			static constexpr size_t SIZE = N;

			T& operator[](size_t index);
			const T& operator[](size_t index) const;
			T& operator[](Axis axis);
			const T& operator[](Axis axis) const;

			bool operator==(const VectorT<T, N>& rhs) const;
			bool operator!=(const VectorT<T, N>& rhs) const;
			VectorT<T, N> operator-() const;

			VectorT<T, N> operator+(const VectorT<T, N>& rhs) const;
			template <typename U> VectorT<T, N>& operator+=(const VectorT<U, N>& rhs);
			VectorT<T, N> operator+(const T& rhs) const;
			VectorT<T, N>& operator+=(const T& rhs);

			VectorT<T, N> operator-(const VectorT<T, N>& rhs) const;
			template <typename U> VectorT<T, N>& operator-=(const VectorT<U, N>& rhs);
			VectorT<T, N> operator-(const T& rhs) const;
			VectorT<T, N>& operator-=(const T& rhs);

			VectorT<T, N> operator*(const VectorT<T, N>& rhs) const;
			template <typename U> VectorT<T, N>& operator*=(const VectorT<U, N>& rhs);
			VectorT<T, N> operator*(const T& rhs) const;
			VectorT<T, N>& operator*=(const T& rhs);

			VectorT<T, N> operator/(const VectorT<T, N>& rhs) const;
			template <typename U> VectorT<T, N>& operator/=(const VectorT<U, N>& rhs);
			VectorT<T, N> operator/(const T& rhs) const;
			VectorT<T, N>& operator/=(const T& rhs);

			T get_square_length() const;
			T get_length() const;
			T dot(const VectorT<T, N>& rhs) const;
			void normalize();
			VectorT<T, N> get_normalized() const;
			VectorT<T, N> get_absolute() const;

			bool is_all_true() const;
			bool is_zero(const T& epsilon = get_epsilon<T>()) const;
			bool equals(const VectorT<T, N>& rhs, const T& epsilon = get_epsilon<T>()) const;

			constexpr iterator begin();
			constexpr iterator end();
			constexpr const_iterator begin() const;
			constexpr const_iterator end() const;
			constexpr const_iterator cbegin() const;
			constexpr const_iterator cend() const;
		};

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator+(const T& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs);

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator-(const T& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs);

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator*(const T& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs);

		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename GLMVectorT, glm::precision P>
		VectorT<T, N> operator/(const T& lhs, const GLMVectorWrapper<VectorT, T, N, GLMVectorT, P>& rhs);
	}
}

#include "GLMVectorWrapper.inl"

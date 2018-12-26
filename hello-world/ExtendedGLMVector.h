#pragma once

#include "Axis.h"
#include "Epsilon.h"

namespace Engine
{
	namespace Math
	{
		template <template <typename, size_t> typename VectorT, typename T, size_t N, template <typename, glm::precision> typename BaseT, glm::precision P = glm::defaultp>
		class ExtendedGLMVector : public BaseT<T, P>
		{
		protected:
			template <typename ... Args> explicit ExtendedGLMVector(Args&& ... args);
			explicit ExtendedGLMVector(Axis axis);

		public:
			using iterator = T * ;
			using const_iterator = const T *;

			static constexpr size_t SIZE = N;

			T& operator[](size_t index);
			const T& operator[](size_t index) const;
			T& operator[](Axis axis);
			const T& operator[](Axis axis) const;

			T get_square_length() const;
			T get_length() const;
			T dot(const VectorT<T, N>& rhs) const;
			void normalize();
			VectorT<T, N> get_normalized() const;
			VectorT<T, N> get_absolute() const;

			bool is_all_true() const;
			bool is_zero(const T& epsilon = get_epsilon<T>()) const;
			bool is_equal(const VectorT<T, N>& rhs, const T& epsilon = get_epsilon<T>()) const;

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			const_iterator cbegin() const;
			const_iterator cend() const;
		};
	}
}

#include "ExtendedGLMVector.inl"

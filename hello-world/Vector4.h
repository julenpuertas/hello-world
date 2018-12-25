#pragma once
#include "Vector.h"
#include "Epsilon.h"
#include "Axis.h"
#include <glm/vec4.hpp>

namespace Engine
{
	namespace Math
	{
		template<typename T> struct Vector<T, 4> : public glm::tvec4<T>
		{
			using iterator = T * ;
			using const_iterator = const T *;

			static const size_t SIZE = 4;
			static const Vector<T, 4> RIGHT;
			static const Vector<T, 4> UP;
			static const Vector<T, 4> FORWARD;

			template <typename ... Args> explicit Vector(Args&& ... args);
			explicit Vector(Axis axis);
			template <typename U, glm::precision P> Vector(glm::tvec4<U, P>&& rhs);

			T& operator[](size_t index);
			const T& operator[](size_t index) const;
			T& operator[](Axis axis);
			const T& operator[](Axis axis) const;

			T get_square_length() const;
			T get_length() const;
			T dot(const Vector<T, 4>& rhs) const;
			void normalize();
			Vector<T, 4> get_normalized() const;

			bool is_all_true() const;
			bool is_zero(const T& epsilon = get_epsilon<T>()) const;
			bool is_equal(const Vector<T, 4>& rhs, const T& epsilon = get_epsilon<T>()) const;

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			const_iterator cbegin() const;
			const_iterator cend() const;
		};
	}
}

#include "Vector4.inl"

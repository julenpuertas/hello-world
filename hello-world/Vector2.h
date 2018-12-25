#pragma once
#include "Vector.h"
#include "Epsilon.h"
#include "Axis.h"
#include <glm/vec2.hpp>

namespace Engine
{
	namespace Math
	{
		template<typename T> struct Vector<T, 2> : public glm::tvec2<T>
		{
			using iterator = T * ;
			using const_iterator = const T *;

			static const size_t SIZE = 2;
			static const Vector<T, 2> RIGHT;
			static const Vector<T, 2> UP;

			template <typename ... Args> explicit Vector(Args&& ... args);
			explicit Vector(Axis axis);
			template <typename U, glm::precision P> Vector(glm::tvec2<U, P>&& rhs);

			T& operator[](size_t index);
			const T& operator[](size_t index) const;
			T& operator[](Axis axis);
			const T& operator[](Axis axis) const;

			T get_square_length() const;
			T get_length() const;
			T dot(const Vector<T, 2>& rhs) const;
			void normalize();
			Vector<T, 2> get_normalized() const;

			bool is_all_true() const;
			bool is_zero(const T& epsilon = get_epsilon<T>()) const;
			bool is_equal(const Vector<T, 2>& rhs, const T& epsilon = get_epsilon<T>()) const;

			iterator begin();
			iterator end();
			const_iterator begin() const;
			const_iterator end() const;
			const_iterator cbegin() const;
			const_iterator cend() const;
		};
	}
}

#include "Vector2.inl"

#pragma once
#include "Vector.h"
#include <glm/vec2.hpp>

template<typename T> struct Vector<T, 2> : public glm::tvec2<T>
{
	using iterator = T *;
	using const_iterator = const T *;

	template <typename ... Args> explicit Vector(Args&& ... args);
	template <typename U, glm::precision P> Vector(glm::tvec2<U, P>&& rhs);

	T square_modulus() const;
	T modulus() const;
	T dot(const Vector<T, 2>& rhs) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
};

#include "Vector2.inl"

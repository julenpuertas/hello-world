#pragma once
#include "Vector.h"
#include <glm/vec3.hpp>

template<typename T> struct Vector<T, 3> : public glm::tvec3<T>
{
	using iterator = T * ;
	using const_iterator = const T *;

	template <typename ... Args> explicit Vector(Args&& ... args);
	template <typename U, glm::precision P> Vector(glm::tvec3<U, P>&& rhs);

	T square_modulus() const;
	T modulus() const;
	T dot(const Vector<T, 3>& rhs) const;
	Vector<T, 3> cross(const Vector<T, 3>& rhs) const;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
};

#include "Vector3.inl"

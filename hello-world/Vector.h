#pragma once

#include "Array.h"

template <typename T, size_t N>
class Vector : public Array<T, N>
{
public:
	Vector() = default;
	template <typename U> explicit Vector(const U& default_value);
	Vector operator+(const Vector& rhs) const;
};

#include "Vector.inl"

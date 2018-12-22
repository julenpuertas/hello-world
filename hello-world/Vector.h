#pragma once

#include "Array.h"

template <typename T, size_t N>
class Vector : Array<T, N>
{
public:
	Vector operator+(const Vector& rhs) const;
};

#include "Vector.inl"

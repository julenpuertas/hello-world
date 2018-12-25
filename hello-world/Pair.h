#pragma once
#include <utility>

namespace Engine
{
	template<typename T, typename U = T> using Pair = std::pair<T, U>;
	template<typename T> Pair<T> make_pair(const T& value);
}

#include "Pair.inl"

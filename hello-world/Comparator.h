#pragma once
#include <functional>

namespace Engine
{
	template <typename T, typename U = T> using Comparator = std::function<bool(const T&, const U&)>;
}

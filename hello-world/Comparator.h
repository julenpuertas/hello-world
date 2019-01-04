#pragma once
#include <functional>

namespace Engine
{
	template <typename T> using Comparator = std::function<bool(const T&, const T&)>;
}

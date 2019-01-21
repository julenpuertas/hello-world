#pragma once
#include <functional>

namespace Engine
{
	template <typename T, typename U = T> using Requirement = std::function<bool(const T&)>;
}

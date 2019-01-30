#pragma once
#include <functional>

namespace Engine
{
	template <typename T> using Requirement = std::function<bool(const T&)>;
}

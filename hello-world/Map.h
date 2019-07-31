#pragma once
#include <map>

namespace Engine
{
	template <typename KeyT, typename T = KeyT, typename LessFunctionT = std::less<KeyT> >
	using Map = std::pmr::map<KeyT, T, LessFunctionT>;

	template <typename KeyT, typename T = KeyT, typename LessFunctionT = std::less<KeyT> >
	using MultiMap = std::pmr::multimap<KeyT, T, LessFunctionT>;
}

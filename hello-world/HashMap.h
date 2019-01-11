#pragma once
#include <unordered_map>

namespace Engine
{
	template <typename KeyT, typename T = KeyT, typename HashFunctionT = std::hash<KeyT>, typename EqualsFunctionT = std::equal_to<KeyT> >
	using HashMap = std::pmr::unordered_map<KeyT, T, HashFunctionT, EqualsFunctionT>;

	template <typename KeyT, typename T = KeyT, typename HashFunctionT = std::hash<KeyT>, typename EqualsFunctionT = std::equal_to<KeyT> >
	using MultiHashMap = std::pmr::unordered_multimap<KeyT, T, HashFunctionT, EqualsFunctionT>;
}

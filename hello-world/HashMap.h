#pragma once
#include <unordered_map>

namespace Engine
{
	template <typename KeyT, typename T = KeyT, typename HashFunctionT = std::hash<KeyT>, typename EqualFunctionT = std::equal_to<KeyT> >
	using HashMap = std::pmr::unordered_map<KeyT, T, HashFunctionT, EqualFunctionT>;

	template <typename KeyT, typename T = KeyT, typename HashFunctionT = std::hash<KeyT>, typename EqualFunctionT = std::equal_to<KeyT> >
	using MultiHashMap = std::pmr::unordered_multimap<KeyT, T, HashFunctionT, EqualFunctionT>;
}
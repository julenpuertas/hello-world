#pragma once
#include <unordered_set>

namespace Engine
{
	template <typename T, typename HashFunctionT = std::hash<T>, typename EqualsFunctionT = std::equal_to<T> >
	using HashTable = std::pmr::unordered_set<T, HashFunctionT, EqualsFunctionT>;

	template <typename T, typename HashFunctionT = std::hash<T>, typename EqualsFunctionT = std::equal_to<T> >
	using MultiHashTable = std::pmr::unordered_multiset<T, HashFunctionT, EqualsFunctionT>;
}

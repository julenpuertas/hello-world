#pragma once
#include "HashTable.h"
#include "HashMap.h"

namespace Engine
{
	class IHasheable
	{
	public:
		virtual size_t get_hash() const = 0;

		template <typename T, typename EqualFunctionT = std::equal_to<T> >
		using Table = HashTable<T, std::hash<IHasheable>, EqualFunctionT>;

		template <typename T, typename EqualFunctionT = std::equal_to<T> >
		using MultiTable = MultiHashTable<T, std::hash<IHasheable>, EqualFunctionT>;

		template <typename KeyT, typename T = KeyT, typename EqualFunctionT = std::equal_to<KeyT> >
		using Map = HashMap<KeyT, T, std::hash<IHasheable>, EqualFunctionT>;

		template <typename KeyT, typename T = KeyT, typename EqualFunctionT = std::equal_to<KeyT> >
		using MultiMap = MultiHashMap<KeyT, T, std::hash<IHasheable>, EqualFunctionT>;
	};
}

namespace std
{
	template <> struct hash<Engine::IHasheable>
	{
		size_t operator()(const Engine::IHasheable& element) const;
	};
}

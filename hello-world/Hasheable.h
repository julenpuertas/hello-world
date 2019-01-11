#pragma once
#include "HashTable.h"
#include "HashMap.h"

namespace Engine
{
	class IHasheable
	{
	public:
		virtual size_t get_hash() const = 0;

		template <typename T, typename EqualsFunctionT = std::equal_to<T> >
		using Table = HashTable<T, std::hash<IHasheable>, EqualsFunctionT>;

		template <typename T, typename EqualsFunctionT = std::equal_to<T> >
		using MultiTable = MultiHashTable<T, std::hash<IHasheable>, EqualsFunctionT>;

		template <typename KeyT, typename T = KeyT, typename EqualsFunctionT = std::equal_to<KeyT> >
		using Map = HashMap<KeyT, T, std::hash<IHasheable>, EqualsFunctionT>;

		template <typename KeyT, typename T = KeyT, typename EqualsFunctionT = std::equal_to<KeyT> >
		using MultiMap = MultiHashMap<KeyT, T, std::hash<IHasheable>, EqualsFunctionT>;
	};
}

namespace std
{
	template <> struct hash<Engine::IHasheable>
	{
		size_t operator()(const Engine::IHasheable& hasheable) const;
	};
}

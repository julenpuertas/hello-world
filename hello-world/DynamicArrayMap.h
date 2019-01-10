#pragma once

#include "DynamicArray.h"
#include "Pair.h"

namespace Engine
{
	template<typename KeyT, typename T = KeyT> class DynamicArrayMap
	{
		DynamicArray<Pair<const KeyT, T> > elements_;
		Comparator<KeyT> equals_fn_;
		Comparator<KeyT> less_fn_;

		Comparator<Pair<KeyT, T> > get_less_fn() const;

	public:
		using const_iterator = DynamicArray<Pair<const KeyT, T> >::const_iterator;
		using iterator = DynamicArray<Pair<const KeyT, T> >::iterator;

		explicit DynamicArrayMap(const Comparator<KeyT>& equals_fn = std::equal_to<KeyT>(), const Comparator<T>& less_fn = std::less<KeyT>());
		template <typename ... Args> void emplace(Args&& ... arguments);
		template <typename ... Args> bool emplace_if_unique(Args&& ... arguments);
		Pair<const_iterator> get_equal_range(const T& element) const;

		bool erase(const KeyT& element);
		size_t erase_multiple(const KeyT& element, size_t max_element_count_to_erase = std::numeric_limits<size_t>::max());

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
	};
}

#include "DynamicArrayMap.inl"

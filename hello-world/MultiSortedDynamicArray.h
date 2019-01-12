#pragma once
#include "AssociativeDynamicArray.h"
#include "Pair.h"

namespace Engine
{
	template<typename T> class MultiSortedDynamicArray
		: public AssociativeDynamicArray<T>
	{
	public:
		template <typename ... Args> explicit MultiSortedDynamicArray(Args&& ... arguments);
		template <typename ... Args> void emplace(Args&& ... arguments);
		template <typename ... Args> void emplace_multiple(size_t copies_to_emplace, Args&& ... arguments);
		Pair<AssociativeDynamicArray<T>::const_iterator> get_equal_range(const T& element) const;
		size_t erase(const T& element, size_t max_element_count_to_erase = std::numeric_limits<size_t>::max());
	};
}

#include "MultiSortedDynamicArray.inl"

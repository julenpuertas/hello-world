#pragma once

#include "DynamicArray.h"
#include "Pair.h"

namespace Engine
{
	template<typename T> class SortedDynamicArray
	{
		DynamicArray<T> elements_;
		Comparator<T> equals_fn_;
		Comparator<T> less_fn_;

	public:
		using const_iterator = DynamicArray<T>::const_iterator;

		explicit SortedDynamicArray(const Comparator<T>& equals_fn = std::equal_to<T>(), const Comparator<T>& less_fn = std::less<T>());
		template <typename ... Args> void emplace(Args&& ... arguments);
		template <typename ... Args> bool emplace_if_unique(Args&& ... arguments);
		Pair<const_iterator> get_equal_range(const T& element) const;

		bool erase(const T& element);
		size_t erase_multiple(const T& element, size_t max_element_count_to_erase = std::numeric_limits<size_t>::max());
		size_t erase_multiple(const std::function<bool(const T&)>& requirement_to_satisty_fn, size_t max_element_count_to_erase = std::numeric_limits<size_t>::max());

		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
	};
}

#include "SortedDynamicArray.inl"

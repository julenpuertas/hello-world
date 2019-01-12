#pragma once
#include "DynamicArray.h"

namespace Engine
{
	template<typename T> class AssociativeDynamicArray
	{
	protected:
		DynamicArray<T> elements_;
		Comparator<T> equals_fn_;
		Comparator<T> less_fn_;
		explicit AssociativeDynamicArray(const Comparator<T>& equals_fn = std::equal_to<T>(), const Comparator<T>& less_fn = std::less<T>());

	public:
		size_t erase(const std::function<bool(const T&)>& requirement_to_satisty_fn, size_t max_element_count_to_erase = std::numeric_limits<size_t>::max());

		using const_iterator = DynamicArray<T>::const_iterator;
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
	};
}

#include "AssociativeDynamicArray.inl"

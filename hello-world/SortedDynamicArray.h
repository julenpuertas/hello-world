#pragma once

#include "DynamicArray.h"

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
		template <typename ... Args> emplace(Args ... arguments);
		template <typename ... Args> emplace_if_unique(Args ... arguments);


		const_iterator begin() const;
		const_iterator end() const;
	};
}

#include "SortedDynamicArray.inl"

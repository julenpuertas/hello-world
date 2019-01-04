#pragma once
#include "Comparator.h"
#include <vector>

namespace Engine
{
	template<typename T> class DynamicArray : public std::pmr::vector<T>
	{
		static std::function<bool(const T&)> make_equal_to_element_fn(const T& element, const Comparator<T>& equal_fn);

	public:
		template <typename ... Args> DynamicArray(Args&& ... arguments);

		template <typename ... Args> bool emplace_back_if_unique(Args&& ... arguments);
		template <typename ... Args> bool emplace_back_if_unique(const Comparator<T>& equal_fn, Args&& ... arguments);

		bool erase(const T& element, bool preserve_order = false, const Comparator<T>& equal_fn = std::equal_to<T>());
		bool erase(const std::function<bool(const T&)>& requirement_to_satisty_fn, bool preserve_order = false);

		size_t sort_and_erase_duplicates(const Comparator<T>& sort_fn = std::less<T>(), const Comparator<T>& equal_fn = std::equal_to<T>());
	};
}

#include "DynamicArray.inl"

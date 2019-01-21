#pragma once
#include "Comparator.h"
#include "Requirement.h"
#include <vector>

namespace Engine
{
	template<typename T> class DynamicArray : public std::pmr::vector<T>
	{
		static std::function<bool(const T&)> make_equal_to_element_fn(const T& element, const Comparator<T>& equal_fn);

	public:
		template <typename ... Args> DynamicArray(Args&& ... arguments);

		void reserve_for(size_t new_extra_capacity);

		template <typename ... Args> bool emplace_back_if_unique(Args&& ... arguments);
		template <typename ... Args> bool emplace_back_if_unique(const Comparator<T>& equal_fn, Args&& ... arguments);

		bool erase_single(const T& element, const Comparator<T>& equal_fn = std::equal_to<T>());
		bool erase_single(const std::function<bool(const T&)>& requirement_to_satisty_fn);

		bool erase_fast(const T& element, const Comparator<T>& equal_fn = std::equal_to<T>());
		bool erase_fast(const std::function<bool(const T&)>& requirement_to_satisty_fn);

		size_t erase_multiple(const T& element, const Comparator<T>& equal_fn = std::equal_to<T>(), size_t max_erase_count = std::numeric_limits<size_t>::max());
		size_t erase_multiple(const std::function<bool(const T&)>& requirement_to_satisty_fn, size_t max_erase_count = std::numeric_limits<size_t>::max());

		size_t sort_and_erase_duplicates(const Comparator<T>& sort_fn = std::less<T>(), const Comparator<T>& equal_fn = std::equal_to<T>());
	};
}

#include "DynamicArray.inl"

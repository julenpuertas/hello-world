#include <algorithm>
#include "SortedDynamicArray.h"

namespace Engine
{
	template<typename T> SortedDynamicArray<T>::SortedDynamicArray(const Comparator<T>& equals_fn, const Comparator<T>& less_fn)
		: equals_fn_(equals_fn)
		, less_fn_(less_fn)
	{}

	template<typename T> template<typename ...Args> void SortedDynamicArray<T>::emplace(Args&& ...arguments)
	{
		T element(std::forward<Args>(arguments) ...);
		const const_iterator it = std::upper_bound(elements_.cbegin(), elements_.cend(), element, less_fn_);
		elements_.insert(it, std::move(element));
	}

	template<typename T> template<typename ...Args> bool SortedDynamicArray<T>::emplace_if_unique(Args&& ...arguments)
	{
		T element(std::forward<Args>(arguments) ...);
		const const_iterator it_end = elements_.cend();
		const const_iterator it = std::lower_bound(elements_.cbegin(), it_end, element, less_fn_);

		if (it != it_end && equals_fn_(element, *it))
			return false;

		elements_.insert(it, std::move(element));
		return true;
	}

	template<typename T> Pair<typename SortedDynamicArray<T>::const_iterator> SortedDynamicArray<T>::get_equal_range(const T & element) const
	{
		return std::equal_range(elements_.cbegin(), elements_.cend(), element, less_fn_);
	}

	template<typename T> bool SortedDynamicArray<T>::erase(const T& element)
	{
		return erase_multiple(element, 1) != 0;
	}

	template<typename T> size_t SortedDynamicArray<T>::erase_multiple(const T& element, size_t max_element_count_to_erase)
	{
		const Pair<const_iterator> range = get_equal_range(element);
		const size_t element_count_to_erase = std::min(range.second - range.first, max_element_count_to_erase);
		elements_.erase(range.first, range.first + element_count_to_erase);
		return element_count_to_erase;
	}

	template<typename T> typename SortedDynamicArray<T>::const_iterator SortedDynamicArray<T>::begin() const
	{
		return cbegin();
	}

	template<typename T> typename SortedDynamicArray<T>::const_iterator SortedDynamicArray<T>::end() const
	{
		return cend();
	}

	template<typename T> typename SortedDynamicArray<T>::const_iterator SortedDynamicArray<T>::cbegin() const
	{
		return elements_.cbegin();
	}

	template<typename T> typename SortedDynamicArray<T>::const_iterator SortedDynamicArray<T>::cend() const
	{
		return elements_.cend();
	}
}

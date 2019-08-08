#include <algorithm>

namespace Engine
{
	template<typename T> template<typename ...Args> SortedDynamicArray<T>::SortedDynamicArray(Args&& ... arguments)
		: SortedDynamicArray<T>(std::forward<Args>(arguments) ...)
	{}

	template<typename T> template<typename ...Args> bool SortedDynamicArray<T>::emplace(Args&& ...arguments)
	{
		T element(std::forward<Args>(arguments) ...);
		const const_iterator it_end = elements_.cend();
		const const_iterator it = std::lower_bound(elements_.cbegin(), it_end, element, less_fn_);

		const bool element_can_be_inserted = it == it_end || !equals_fn_(element, *it);
		if (element_can_be_inserted)
			elements_.insert(it, std::move(element));

		return element_can_be_inserted;
	}

	template<typename T> bool SortedDynamicArray<T>::contains(const T& element) const
	{
		return std::binary_search(elements_.cbegin(), elements_.cend(), element, less_fn_);
	}

	template<typename T> bool SortedDynamicArray<T>::erase(const T& element)
	{
		const const_iterator it_end = elements_.cend();
		const const_iterator it = std::lower_bound(elements_.cbegin(), it_end, element, less_fn_);

		const bool element_can_be_erased = it != it_end && equals_fn_(element, *it);

		if (element_can_be_erased)
			elements_.erase(it);

		return element_can_be_erased;
	}
}

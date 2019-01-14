
namespace Engine
{
	template<typename T> template<typename ...Args> MultiSortedDynamicArray<T>::MultiSortedDynamicArray(Args&& ... arguments)
		: SortedDynamicArray<T>(std::forward<Args>(arguments) ...)
	{}

	template<typename T> template<typename ...Args> void MultiSortedDynamicArray<T>::emplace(Args&& ...arguments)
	{
		emplace_multiple(1, std::forward<Args>(arguments) ...);
	}

	template<typename T> template<typename ...Args> void MultiSortedDynamicArray<T>::emplace_multiple(size_t copies_to_emplace, Args&& ... arguments)
	{
		const const_iterator it = std::upper_bound(elements_.cbegin(), elements_.cend(), element, less_fn_);
		elements_.insert(it, copies_to_emplace, T(std::forward<Args>(arguments) ...));
	}

	template<typename T> Pair<typename MultiSortedDynamicArray<T>::const_iterator> MultiSortedDynamicArray<T>::get_equal_range(const T& element) const
	{
		return std::equal_range(elements_.cbegin(), elements_.cend(), element, less_fn_);
	}

	template<typename T> size_t MultiSortedDynamicArray<T>::erase(const T& element, size_t max_element_count_to_erase)
	{
		const Pair<const_iterator> range = get_equal_range(element);
		const size_t element_count_to_erase = std::min(range.second - range.first, max_element_count_to_erase);
		elements_.erase(range.first, range.first + element_count_to_erase);
		return element_count_to_erase;
	}
}

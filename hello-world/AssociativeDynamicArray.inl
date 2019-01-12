
namespace Engine
{
	template<typename T> AssociativeDynamicArray<T>::AssociativeDynamicArray(const Comparator<T>& equals_fn, const Comparator<T>& less_fn)
		: equals_fn_(equals_fn)
		, less_fn_(less_fn)
	{}

	template<typename T> size_t AssociativeDynamicArray<T>::erase(const std::function<bool(const T&)>& requirement_to_satisty_fn, size_t max_element_count_to_erase)
	{
		return elements_.erase_multiple(requirement_to_satisty_fn, max_element_count_to_erase);
	}

	template<typename T> typename AssociativeDynamicArray<T>::const_iterator AssociativeDynamicArray<T>::begin() const
	{
		return cbegin();
	}

	template<typename T> typename AssociativeDynamicArray<T>::const_iterator AssociativeDynamicArray<T>::end() const
	{
		return cend();
	}

	template<typename T> typename AssociativeDynamicArray<T>::const_iterator AssociativeDynamicArray<T>::cbegin() const
	{
		return elements_.cbegin();
	}

	template<typename T> typename AssociativeDynamicArray<T>::const_iterator AssociativeDynamicArray<T>::cend() const
	{
		return elements_.cend();
	}
}

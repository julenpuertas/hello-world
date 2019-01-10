
namespace Engine
{
	template<typename KeyT, typename T> Comparator<Pair<const KeyT, T> > DynamicArrayMap<KeyT, T>::get_less_fn() const
	{
		return Comparator<Pair<KeyT, T> >([this](const Pair<const KeyT, T>& lhs, const Pair<const KeyT, T>& rhs)
		{
			return less_fn_(lhs, rhs);
		});
	}

	template<typename KeyT, typename T> DynamicArrayMap<KeyT, T>::DynamicArrayMap(const Comparator<KeyT>& equals_fn, const Comparator<KeyT>& less_fn)
		: equals_fn_(equals_fn)
		, less_fn_(less_fn)
	{}

	template<typename KeyT, typename T> template<typename ...Args> void DynamicArrayMap<KeyT, T>::emplace(Args&& ...arguments)
	{
		Pair<KeyT, T> element(std::forward<Args>(arguments) ...);
		const const_iterator it = std::upper_bound(elements_.cbegin(), elements_.cend(), element, get_less_fn());
		elements_.insert(it, std::move(element));
	}

	template<typename KeyT, typename T> template<typename ...Args> bool DynamicArrayMap<KeyT, T>::emplace_if_unique(Args&& ...arguments)
	{
		Pair<KeyT, T> element(std::forward<Args>(arguments) ...);
		const const_iterator it_end = elements_.cend();
		const const_iterator it = std::lower_bound(elements_.cbegin(), it_end, element, , get_less_fn());

		if (it != it_end && equals_fn_(element, *it))
			return false;

		elements_.insert(it, std::move(element));
		return true;
	}

	template<typename KeyT, typename T> Pair<typename DynamicArrayMap<KeyT, T>::const_iterator> DynamicArrayMap<KeyT, T>::get_equal_range(const T & element) const
	{
		return std::equal_range(elements_.cbegin(), elements_.cend(), element, get_less_fn());
	}

	template<typename KeyT, typename T> bool DynamicArrayMap<KeyT, T>::erase(const KeyT& element)
	{
		return erase_multiple(element, 1) != 0;
	}

	template<typename KeyT, typename T> size_t DynamicArrayMap<KeyT, T>::erase_multiple(const KeyT& element, size_t max_element_count_to_erase)
	{
		const Pair<const_iterator> range = get_equal_range(element);
		const size_t element_count_to_erase = std::min(range.second - range.first, max_element_count_to_erase);
		elements_.erase(range.first, range.first + element_count_to_erase);
		return element_count_to_erase;
	}

	template<typename KeyT, typename T> typename DynamicArrayMap<KeyT, T>::iterator DynamicArrayMap<KeyT, T>::begin()
	{
		return elements_.begin();
	}

	template<typename KeyT, typename T> typename DynamicArrayMap<KeyT, T>::iterator DynamicArrayMap<KeyT, T>::end()
	{
		return elements_.end();
	}

	template<typename KeyT, typename T> typename DynamicArrayMap<KeyT, T>::const_iterator DynamicArrayMap<KeyT, T>::begin() const
	{
		return cbegin();
	}

	template<typename KeyT, typename T> typename DynamicArrayMap<KeyT, T>::const_iterator DynamicArrayMap<KeyT, T>::end() const
	{
		return cend();
	}

	template<typename KeyT, typename T> typename DynamicArrayMap<KeyT, T>::const_iterator DynamicArrayMap<KeyT, T>::cbegin() const
	{
		return elements_.cbegin();
	}

	template<typename KeyT, typename T> typename DynamicArrayMap<KeyT, T>::const_iterator DynamicArrayMap<KeyT, T>::cend() const
	{
		return elements_.cend();
	}
}

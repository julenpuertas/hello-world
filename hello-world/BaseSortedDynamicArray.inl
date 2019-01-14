
namespace Engine
{
	namespace Base
	{
		template<typename T> SortedDynamicArray<T>::SortedDynamicArray(const Comparator<T>& equals_fn, const Comparator<T>& less_fn)
			: equals_fn_(equals_fn)
			, less_fn_(less_fn)
		{}

		template<typename T> size_t SortedDynamicArray<T>::erase(const std::function<bool(const T&)>& requirement_to_satisty_fn, size_t max_element_count_to_erase)
		{
			return elements_.erase_multiple(requirement_to_satisty_fn, max_element_count_to_erase);
		}

		template<typename T> void SortedDynamicArray<T>::reserve(size_t new_capacity)
		{
			elements_.reserve(new_capacity);
		}

		template<typename T> void SortedDynamicArray<T>::reserve_for(size_t new_extra_capacity)
		{
			elements_.reserve_for(new_extra_capacity);
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
}

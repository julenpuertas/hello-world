#include <algorithm>

namespace Engine
{
	template<typename T> std::function<bool(const T&)> DynamicArray<T>::make_equal_to_element_fn(const T& element, const Comparator<T>& equal_fn)
	{
		return [&element, &equal_fn](const T& rhs)
		{
			return equal_fn(element, rhs);
		};
	}

	template<typename T> template<typename ...Args> DynamicArray<T>::DynamicArray(Args&& ...arguments)
		: std::pmr::vector<T>(std::forward<Args>(arguments) ...)
	{}

	template<typename T> void DynamicArray<T>::reserve_for(size_t new_extra_capacity)
	{
		this->reserve(this->size() + new_extra_capacity);
	}

	template<typename T> template<typename ...Args> bool DynamicArray<T>::emplace_back_if_unique(Args&& ...arguments)
	{
		return emplace_back_if_unique(std::equal_to<T>(), std::forward<Args>(arguments) ...);
	}

	template<typename T> template<typename ...Args> bool DynamicArray<T>::emplace_back_if_unique(const Comparator<T>& equal_fn, Args&& ...arguments)
	{
		if (!equal_fn)
			return false;

		T element(std::forward<Args>(arguments) ...);
		const std::function<bool(const T&)> equal_to_element_fn = make_equal_to_element_fn(element, equal_fn);

		const std::pmr::vector<T>::const_iterator it_end = this->cend();
		const bool insert_element = std::find_if(this->cbegin(), it_end, equal_to_element_fn) == it_end;
		if (insert_element)
			this->push_back(std::move(element));

		return insert_element;
	}

	template<typename T> bool DynamicArray<T>::erase(const T& element, const Comparator<T>& equal_fn)
	{
		return erase(make_equal_to_element_fn(element, equal_fn));
	}

	template<typename T> bool DynamicArray<T>::erase(const std::function<bool(const T&)>& requirement_to_satisty_fn)
	{
		if (!requirement_to_satisty_fn)
			return false;

		typename std::pmr::vector<T>::iterator it_end = this->end();
		const std::pmr::vector<T>::iterator it = std::find_if(this->begin(), it_end, requirement_to_satisty_fn);

		const bool element_erased = it != it_end;
		if (element_erased)
			this->erase(it);

		return element_erased;
	}

	template<typename T> bool DynamicArray<T>::erase_fast(const T& element, const Comparator<T>& equal_fn)
	{
		return erase_fast(make_equal_to_element_fn(element, equal_fn));
	}

	template<typename T> bool DynamicArray<T>::erase_fast(const std::function<bool(const T&)>& requirement_to_satisty_fn)
	{
		if (!requirement_to_satisty_fn)
			return false;

		typename std::pmr::vector<T>::iterator it_end = this->end();
		const std::pmr::vector<T>::iterator it = std::find_if(this->begin(), it_end, requirement_to_satisty_fn);

		const bool element_can_be_erased = it != it_end;
		if (element_can_be_erased)
		{
			std::iter_swap(it, --it_end);
			this->pop_back();
		}

		return element_can_be_erased;
	}

	template<typename T> size_t DynamicArray<T>::erase_multiple(const T& element, const Comparator<T>& equal_fn, size_t max_erase_count)
	{
		return erase_multiple(make_equal_to_element_fn(element, equal_fn), max_erase_count);
	}

	template<typename T> size_t DynamicArray<T>::erase_multiple(const std::function<bool(const T&)>& requirement_to_satisty_fn, size_t max_erase_count)
	{
		if (!requirement_to_satisty_fn)
			return false;

		size_t erased_element_count = 0;
		typename std::pmr::vector<T>::iterator it_end = this->end();
		const std::pmr::vector<T>::iterator it_new_end = std::remove_if(this->begin(), it_end, [erased_element_count, max_erase_count](const T& element)
		{
			return erased_element_count++ < max_erase_count && requirement_to_satisty_fn(element);
		});

		this->erase(it_new_end, it_end);
		return erased_element_count;
	}

	template<typename T> size_t DynamicArray<T>::sort_and_erase_duplicates(const Comparator<T>& sort_fn, const Comparator<T>& equal_fn)
	{
		if (!sort_fn || !equal_fn)
			return 0;

		std::sort(this->begin(), this->end(), sort_fn);
		const std::pmr::vector<T>::const_iterator it_new_end = std::unique(this->begin(), this->end(), equal_fn);
		const std::pmr::vector<T>::const_iterator it_end = this->cend();

		const size_t erased_element_count = it_end - it_new_end;
		this->erase(it_new_end, it_end);

		return erased_element_count;
	}
}

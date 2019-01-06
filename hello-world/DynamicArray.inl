#include "DynamicArray.h"
#pragma once

namespace Engine
{
	template<typename T> std::function<bool(const T&)> DynamicArray<T>::make_equal_to_element_fn(const T & element, const Comparator<T>& equal_fn)
	{
		return [&element](const T& rhs)
		{
			return equal_fn(element, rhs);
		};
	}

	template<typename T> template<typename ...Args> DynamicArray<T>::DynamicArray(Args&& ...arguments)
		: std::pmr::vector<T>(std::forward<Args>(arguments) ...)
	{}

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

	template<typename T> bool DynamicArray<T>::erase(const T& element, bool preserve_order, const Comparator<T>& equal_fn)
	{
		return erase(make_equal_to_element_fn(element, equal_fn), preserve_order);
	}

	template<typename T> bool DynamicArray<T>::erase(const std::function<bool(const T&)>& requirement_to_satisty_fn, bool preserve_order)
	{
		if (!requirement_to_satisty_fn)
			return false;

		typename std::pmr::vector<T>::iterator it_end = this->end();
		const std::pmr::vector<T>::iterator it = std::find_if(this->begin(), it_end, requirement_to_satisty_fn);
		if (it == it_end)
			return false;

		if (preserve_order)
		{
			this->erase(it);
			return true;
		}

		std::iter_swap(it, --it_end);
		this->pop_back();

		return true;
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

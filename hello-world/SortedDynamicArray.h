#pragma once

#include "BaseSortedDynamicArray.h"

namespace Engine
{
	template<typename T> class SortedDynamicArray
		: public Base::SortedDynamicArray<T>
	{
	public:
		template <typename ... Args> explicit SortedDynamicArray(Args&& ... arguments);
		template <typename ... Args> bool emplace(Args&& ... arguments);
		bool contains(const T& element) const;
		bool erase(const T& element);
	};
}

#include "SortedDynamicArray.inl"

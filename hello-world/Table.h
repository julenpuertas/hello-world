#pragma once

#include "DynamicArray.h"
#include "Vector.h"
#include "Swapable.h"

namespace Engine
{
	template <typename T> class Table
		: public ISwapable<Table<T> >
	{
		DynamicArray<T> table_;
		size_t width_ = 0;

		size_t convert(const SVector2& indices) const;
		SVector2 convert(size_t index) const;
		size_t get_height() const;

	public:
		Table() = default;
		explicit Table(const SVector2& dimensions, const T& element = T());

		typename DynamicArray<T>::const_reference operator[](const SVector2& indices) const;
		typename DynamicArray<T>::reference operator[](const SVector2& indices);

		void resize(const SVector2& dimensions, const T& element = T());
		void clear();
		SVector2 get_dimensions() const;
		bool is_empty() const;

		typename DynamicArray<T>::const_pointer get() const;

		void add_rows(size_t row_index, size_t row_count = 1, const T& element = T());
		void add_columns(size_t column_index, size_t column_count = 1, const T& element = T());

		void erase_rows(size_t row_index, size_t row_count = 1);
		void erase_columns(size_t column_index, size_t column_count = 1);

		void for_row(size_t row_index, size_t row_count, const std::function<void(T&)>& fn);
		void for_row(size_t row_index, size_t row_count, const std::function<void(const T&)>& fn) const;

		void for_column(size_t column_index, size_t column_count, const std::function<void(T&)>& fn);
		void for_column(size_t column_index, size_t column_count, const std::function<void(const T&)>& fn) const;

		void for_area(const SVector2& position, const SVector2& dimensions, const std::function<void(T&)>& fn);
		void for_area(const SVector2& position, const SVector2& dimensions, const std::function<void(const T&)>& fn) const;

		void swap(Table& rhs) override;

		using iterator = DynamicArray<T>::iterator;
		using const_iterator = DynamicArray<T>::const_iterator;
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
	};
}

#include "Table.inl"

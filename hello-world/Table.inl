#include "Table.h"

namespace Engine
{
	template <typename T> size_t Table<T>::convert(const SVector2& indices) const
	{
		return indices.x + width_ * indices.y;
	}

	template <typename T> SVector2 Table<T>::convert(size_t index) const
	{
		return SVector2(index / width_, index % width_);
	}

	template <typename T> size_t Table<T>::get_height() const
	{
		if (width_)
			return table_.size() / width_;

		return 0;
	}

	template <typename T> Table<T>::Table(const SVector2& dimensions, const T& element)
		: width_(dimensions.x)
		, table_(dimensions.x * dimensions.y, element)
	{}

	template <typename T> typename Table<T>::const_reference Table<T>::operator[](const SVector2& indices) const
	{
		return table_.at(convert(indices));
	}

	template <typename T> typename Table<T>::reference Table<T>::operator[](const SVector2& indices)
	{
		return table_.at(convert(indices));
	}

	template <typename T> void Table<T>::resize(const SVector2& dimensions, const T& element)
	{
		const size_t max_uint = std::numeric_limits<size_t>::max();
		if (dimensions.x < width_)
			erase_columns(dimensions.x, max_uint);

		size_t height = get_height();
		if (dimensions.y < height)
			erase_rows(dimensions.y, max_uint);

		if (dimensions.x > width_)
			add_columns(max_uint, dimensions.x - width_, element);

		height = get_height();
		if (dimensions.y > height)
			add_rows(max_uint, dimensions.y - height, element);
	}

	template <typename T> void Table<T>::clear()
	{
		width_ = 0;
		table_.clear();
	}

	template <typename T> SVector2 Table<T>::get_dimensions() const
	{
		return SVector2(width_, get_height());
	}

	template <typename T> bool Table<T>::is_empty() const
	{
		return table_.empty();
	}

	template <typename T> typename Table<T>::const_pointer Table<T>::get() const
	{
		if (table_.empty())
			return nullptr;

		return table_.data();
	}

	template <typename T> void Table<T>::add_rows(size_t row_index, size_t row_count, const T& element)
	{
		if (!row_count)
			return;

		if (table_.empty())
		{
			table_.resize(row_count, element);
			width_ = 1;
		}

		else
		{
			const size_t old_height = get_height();
			if (row_index > old_height)
				row_index = old_height;

			table_.insert(table_.cbegin() + width_ * row_index, width_ * row_count, element);
		}
	}

	template <typename T> void Table<T>::add_columns(size_t column_index, size_t column_count, const T& element)
	{
		if (!column_count)
			return;

		if (table_.empty())
		{
			table_.resize(column_count, element);
			width_ = column_count;
			return;
		}

		if (column_index > width_)
			column_index = width_;

		const size_t height = get_height();
		size_t element_shift_offset = height * column_count;
		const size_t table_size = table_.size() + element_shift_offset;
		table_.resize(table_size, element);

		size_t decrease_offset_cool_down = width_ - column_index;
		const DynamicArray<T>::reverse_iterator it_end = table_.rend();
		for (DynamicArray<T>::reverse_iterator it = table_.rbegin() + element_shift_offset; element_shift_offset && it != it_end; ++it)
		{
			if (!decrease_offset_cool_down)
			{
				element_shift_offset -= column_count;
				decrease_offset_cool_down = width_;
			}

			std::iter_swap(it, it - element_shift_offset);
			--decrease_offset_cool_down;
		}

		width_ = table_size / height;
	}

	template <typename T> void Table<T>::erase_rows(size_t row_index, size_t row_count)
	{
		const size_t height = get_height();
		if (row_index >= height)
			return;

		row_count = std::min(row_count, height - row_index);

		const DynamicArray<T>::const_iterator it = table_.cbegin() + width_ * row_index;
		table_.erase(it, it + width_ * row_count);

		if (table_.empty())
			width_ = 0;
	}

	template <typename T> void Table<T>::erase_columns(size_t column_index, size_t column_count)
	{
		if (column_index >= width_)
			return;

		column_count = std::min(column_count, width_ - column_index);

		size_t element_shift_offset = 0;
		size_t increase_offset_cool_down = 0;

		const size_t height = get_height();
		width_ -= column_count;

		DynamicArray<T>::iterator it = table_.begin();
		const DynamicArray<T>::iterator it_end = it + width_ * height;
		for (it += column_index; it != it_end; ++it)
		{
			if (!increase_offset_cool_down)
			{
				increase_offset_cool_down = width_;
				element_shift_offset += column_count;
			}

			*it = std::move(it[element_shift_offset]);

			--increase_offset_cool_down;
		}

		table_.erase(it_end, table_.cend());
		if (table_.empty())
			width_ = 0;
	}

	template <typename T> void Table<T>::for_row(size_t row_index, size_t row_count, const std::function<void(T&)>& fn)
	{
		if (!fn)
			return;

		const size_t height = get_height();
		if (row_index >= height)
			return;

		row_count = std::min(row_count, height - row_index);
		const DynamicArray<T>::iterator it = table_.begin() + width_ * row_index;
		std::for_each(it, it + width_ * row_count, fn);
	}

	template <typename T> void Table<T>::for_row(size_t row_index, size_t row_count, const std::function<void(const T&)>& fn) const
	{
		if (!fn)
			return;

		const size_t height = get_height();
		if (row_index >= height)
			return;

		row_count = std::min(row_count, height - row_index);
		const DynamicArray<T>::const_iterator it = table_.begin() + width_ * row_index;
		std::for_each(it, it + width_ * row_count, fn);
	}

	template <typename T> void Table<T>::for_column(size_t column_index, size_t column_count, const std::function<void(T&)>& fn)
	{
		for_area(SVector2(column_index, 0), SVector2(column_count, std::numeric_limits<size_t>::max()), fn);
	}

	template <typename T> void Table<T>::for_column(size_t column_index, size_t column_count, const std::function<void(const T&)>& fn) const
	{
		for_area(SVector2(column_index, 0), SVector2(column_count, std::numeric_limits<size_t>::max()), fn);
	}

	template <typename T> void Table<T>::for_area(const SVector2& position, const SVector2& dimensions, const std::function<void(T&)>& fn)
	{
		if (!fn)
			return;

		const size_t height = get_height();
		SVector2 index_vec;
		size_t dimensions_y = dimensions.y;

		for (index_vec.y = position.y; dimensions_y-- && index_vec.y < height; ++index_vec.y)
		{
			size_t dimensions_x = dimensions.x;
			for (index_vec.x = position.x; dimensions_x-- && index_vec.x < width_; ++index_vec.x)
				fn((*this)[index_vec]);
		}
	}

	template <typename T> void Table<T>::for_area(const SVector2& position, const SVector2& dimensions, const std::function<void(const T&)>& fn) const
	{
		if (!fn)
			return;

		const size_t height = get_height();
		SVector2 index_vec;
		size_t dimensions_y = dimensions.y;

		for (index_vec.y = position.y; dimensions_y-- && index_vec.y < height; ++index_vec.y)
		{
			size_t dimensions_x = dimensions.x;
			for (index_vec.x = position.x; dimensions_x-- && index_vec.x < width_; ++index_vec.x)
				fn((*this)[index_vec]);
		}
	}

	template <typename T> void Table<T>::swap(Table& rhs)
	{
		table_.swap(rhs.table_);
		std::swap(width_, rhs.width_);
	}

	template<typename T> typename Table<T>::iterator Table<T>::begin()
	{
		return table_.begin();
	}

	template<typename T> typename Table<T>::iterator Table<T>::end()
	{
		return table_.end();
	}

	template<typename T> typename Table<T>::const_iterator Table<T>::begin() const
	{
		return cbegin();
	}

	template<typename T> typename Table<T>::const_iterator Table<T>::end() const
	{
		return cend();
	}

	template<typename T> typename Table<T>::const_iterator Table<T>::cbegin() const
	{
		return table_.cbegin();
	}

	template<typename T> typename Table<T>::const_iterator Table<T>::cend() const
	{
		return table_.cend();
	}
}

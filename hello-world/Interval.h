#pragma once

#include "Readable.h"
#include "Writable.h"

namespace Engine
{
	template <typename T> class Interval
		: public IO::IWritable
		, public IO::IReadable
	{
		T min_;
		T max_;
		bool min_open_ = false;
		bool max_open_ = false;

	public:
		constexpr Interval(const T& min, const T& max);
		constexpr Interval(const T& min, bool min_open, const T& max, bool max_open);

		constexpr const T& get_min() const;
		constexpr void set_min(const T& min);
		constexpr const T& get_max() const;
		constexpr void set_max(const T& max);

		constexpr bool is_min_open() const;
		constexpr void set_min_open(bool min_open);
		constexpr bool is_max_open() const;
		constexpr void set_max_open(bool max_open);

		void extend_min(const T& min);
		void extend_max(const T& max);
		void extend(const T& value);
		template <typename Iterator_T> void extend(Iterator_T it_first, const Iterator_T& it_last);

		bool intersects(const T& value) const;
		bool intersects(const Interval& rhs) const;

		void write(std::ostream& os) const override;
		void read(std::istream& is) override;
	};
}

#include "Interval.inl"

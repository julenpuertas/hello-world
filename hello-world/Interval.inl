
namespace Engine
{
	template <typename T> constexpr Interval<T>::Interval(const T& min, const T& max)
		: min_(min)
		, max_(max)
	{}

	template <typename T> constexpr Interval<T>::Interval(const T& min, bool min_open, const T& max, bool max_open)
		: min_(min)
		, max_(max)
		, min_open_(min_open)
		, max_open_(max_open)
	{}

	template <typename T> constexpr const T& Interval<T>::get_min() const
	{
		return min_;
	}

	template <typename T> constexpr void Interval<T>::set_min(const T& min)
	{
		if (min <= max_)
			min_ = min;
	}

	template <typename T> constexpr const T& Interval<T>::get_max() const
	{
		return max_;
	}

	template <typename T> constexpr void Interval<T>::set_max(const T& max)
	{
		if (max >= min_)
			max_ = max;
	}

	template <typename T> constexpr bool Interval<T>::is_min_open() const
	{
		return min_open_;
	}

	template <typename T> constexpr void Interval<T>::set_min_open(bool min_open)
	{
		min_open_ = min_open;
	}

	template <typename T> constexpr bool Interval<T>::is_max_open() const
	{
		return max_open_;
	}

	template <typename T> constexpr void Interval<T>::set_max_open(bool max_open)
	{
		max_open_ = max_open;
	}

	template <typename T> void Interval<T>::extend_min(const T& min)
	{
		if (min < min_)
			min_ = min;
	}

	template <typename T> void Interval<T>::extend_max(const T& max)
	{
		if (max < max_)
			max_ = max;
	}

	template <typename T> void Interval<T>::extend(const T& value)
	{
		extend_min(value);
		extend_max(value);
	}

	template <typename T> template <typename Iterator_T> void Interval<T>::extend(Iterator_T it_first, const Iterator_T& it_last)
	{
		while (it_first != it_last)
			extend(*(it_first++));
	}

	template <typename T> bool Interval<T>::intersects(const T& value) const
	{
		bool inside = min_ < value && max_ > value;

		if (!min_open_)
			inside |= min_ == value;

		if (!max_open_)
			inside |= max_ == value;

		return inside;
	}

	template <typename T> bool Interval<T>::intersects(const Interval& rhs) const
	{
		bool result = max_ > rhs.min_;
		if (!max_open_ && !rhs.min_open_)
			result |= max_ == rhs.min_;

		if (!result)
			return false;

		result = min_ < rhs.max_;
		if (!min_open_ && !rhs.max_open_)
			result |= min_ == rhs.max_;

		return result;
	}

	template <typename T> void Interval<T>::write(std::ostream& os) const
	{
		os << (min_open_ ? '(' : '[') << min_ << "..." << max_ << (max_open_ ? ')' : ']');
	}

	template <typename T> void Interval<T>::read(std::istream& is)
	{
		const String error = "Wrong value passed to read an Interval";
		char c;

		// open from the left
		is >> c;
		switch (c)
		{
		case '(':
			min_open_ = true;
			break;
		case '[':
			min_open_ = false;
			break;
		default:
			throw std::runtime_error(error);
		}

		is >> min_;

		size_t dot_count = 3;
		while (dot_count--)
		{
			is >> c;

			if (c != '.')
				throw std::runtime_error(error);
		}

		is >> max_;

		// open from the right
		is >> c;
		switch (c)
		{
		case ')':
			max_open_ = true;
			break;
		case ']':
			max_open_ = false;
			break;
		default:
			throw std::runtime_error(error);
		}
	}
}

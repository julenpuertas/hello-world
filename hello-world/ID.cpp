#include "ID.h"

namespace Engine
{
	size_t ID::Provider::request(size_t min_id)
	{
		if (used_ids_.empty())
		{
			used_ids_.emplace_back(min_id, min_id);
			return min_id;
		}

		// requested index is the smallest one
		Pair<size_t>& first_element = used_ids_.front();
		if (min_id < first_element.first)
		{
			if (min_id + 1 == first_element.first)
				--first_element.first;

			else used_ids_.insert(used_ids_.cbegin(), make_pair(min_id));

			return min_id;
		}

		// requested id is the largest one
		Pair<size_t>& last_element = used_ids_.back();
		if (last_element.second < min_id)
		{
			if (last_element.second + 1 == min_id)
				++last_element.second;

			else used_ids_.emplace_back(min_id, min_id);

			return min_id;
		}

		// goes between existing ranges
		const DynamicArray<Pair<size_t> >::iterator it_begin = used_ids_.begin();
		const DynamicArray<Pair<size_t> >::iterator it_end = used_ids_.end();
		const DynamicArray<Pair<size_t> >::iterator it = std::find_if(it_begin, it_end, [min_id](const Pair<size_t>& range)
		{
			return min_id <= range.second;
		});

		// inside range
		Pair<size_t>& found_element = *it;
		if (found_element.first <= min_id)
		{
			min_id = ++found_element.second;
			const DynamicArray<Pair<size_t> >::iterator it_next = it + 1;

			// there is a range after this one
			if (it_next != it_end)
			{
				Pair<size_t>& next_element = *it_next;
				if (found_element.second + 1 == next_element.first)
				{
					found_element.second = next_element.second;
					used_ids_.erase(it_next);
				}
			}

			return min_id;
		}

		const bool prev_range_exists = it != it_begin;
		const DynamicArray<Pair<size_t> >::iterator it_prev = it - 1;

		// just before the range
		if (min_id + 1 == found_element.first)
		{
			--found_element.first;

			Pair<size_t>& prev_element = *it_prev;
			if (prev_element.second + 1 == found_element.first)
			{
				prev_element.second = found_element.second;
				used_ids_.erase(it);
			}

			return min_id;
		}

		Pair<size_t>& prev_element = *it_prev;
		if (prev_element.second + 1 == min_id)
		{
			++prev_element.second;
			return min_id;
		}

		used_ids_.insert(it, make_pair(min_id));
		return min_id;
	}

	void ID::Provider::release(size_t id)
	{
		const DynamicArray<Pair<size_t> >::iterator it_end = used_ids_.end();
		const DynamicArray<Pair<size_t> >::iterator it = std::find_if(used_ids_.begin(), it_end, [id](const Pair<size_t>& range)
		{
			return id >= range.first && id <= range.second;
		});

		if (it == it_end)
			return;

		Pair<size_t>& range = *it;
		if (range.first == range.second)
			used_ids_.erase(it);

		else if (id == range.first)
			++range.first;

		else if (id == range.second)
			--range.second;

		else
		{
			const size_t range_largest = range.second;
			range.second = id - 1;
			used_ids_.emplace(it + 1, id + 1, range_largest);
		}
	}

	ID::ID(Provider& provider, size_t starting_id)
		: p_provider_(&provider)
	{
		if (starting_id != INVALID)
			id_ = provider.request(starting_id);
	}

	ID::ID(ID && rhs)
		: p_provider_(rhs.p_provider_)
		, id_(rhs.id_)
	{
		rhs.id_ = INVALID;
	}

	ID::~ID()
	{
		release();
	}

	ID & ID::operator=(ID&& rhs)
	{
		p_provider_ = rhs.p_provider_;
		id_ = rhs.id_;
		rhs.id_ = INVALID;

		return *this;
	}

	bool ID::is_assigned() const
	{
		return id_ != INVALID;
	}

	void ID::assign(size_t min_possible_id)
	{
		if (is_assigned())
			return;

		id_ = p_provider_->request(min_possible_id);
	}

	void ID::reassign(size_t min_possible_id)
	{
		if (is_assigned())
			p_provider_->release(id_);

		id_ = p_provider_->request(min_possible_id);
	}

	void ID::release()
	{
		if (is_assigned())
			p_provider_->release(id_);

		id_ = INVALID;
	}

	void ID::set_provider(Provider& provider)
	{
		p_provider_ = &provider;
	}

	ID::operator size_t() const
	{
		return id_;
	}
}

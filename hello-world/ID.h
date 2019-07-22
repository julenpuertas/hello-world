#pragma once
#include "Pair.h"
#include "DynamicArray.h"

namespace Engine
{
	class ID
	{
	public:
		class Provider
		{
			DynamicArray<Pair<size_t> > used_ids_;

		public:
			size_t request(size_t min_id = 0);
			void release(size_t id);
		};

		static constexpr size_t INVALID = std::numeric_limits<size_t>::max();

		ID(Provider& provider, size_t starting_id = 0);
		ID(const ID& rhs) = delete;
		ID(ID&& rhs);
		~ID();

		ID& operator=(const ID& rhs) = delete;
		ID& operator=(ID&& rhs);

		bool is_assigned() const;
		void assign(size_t min_possible_id = 0);
		void reassign(size_t min_possible_id);
		void release();

		void set_provider(Provider& provider);
		operator size_t() const;

	private:
		Provider* p_provider_ = nullptr;
		size_t id_ = INVALID;
	};
}

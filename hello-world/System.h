#pragma once
#include <functional>
#include "Singleton.h"

namespace Engine
{
	namespace Systems
	{
		template <typename T> class System
			: public ISingleton<T>
		{
			double frame_time_ = 0;

			double update_wait_time_ = 0;
			double waited_time_ = 0;

			size_t update_wait_frame_count_ = 0;
			size_t waited_frame_count_ = 0;

			bool time_forward_ = true;
			bool updating_ = true;
			bool stepping_ = false;

		public:
			void update();
			template <typename U> U get_frame_time() const;

			bool is_waiting_time_for_update() const;
			void stop_waiting_time_for_update();
			void set_update_wait_time(double update_wait_time);

			bool is_waiting_frame_count_for_update() const;
			void stop_waiting_frame_count_for_update();
			void set_update_wait_frame_count(size_t update_wait_frame_count);

			bool is_time_forward() const;
			void set_time_forward(bool time_forward);

			bool is_updating() const;
			void set_updating(bool updating);

			void give_step();
		};
	}
}

#include "System.inl"

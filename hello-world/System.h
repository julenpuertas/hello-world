#pragma once

namespace Engine
{
	namespace Systems
	{
		class System
		{
			double frame_time_ = 0;

			double update_wait_time_ = 0;
			double waited_time_ = 0;

			size_t frame_count_to_update_after_ = 0;
			size_t frame_count_since_last_update_ = 0;

			bool time_forward_ = true;
			bool updating_ = true;
			bool stepping_ = false;

			double get_last_frame_duration() const;

		protected:
			virtual void on_update() = 0;

		public:
			void update();
			template <typename T> T get_last_frame_seconds() const;

			bool is_waiting_time_for_update() const;
			void stop_waiting_time_for_update();
			void set_update_wait_time(double update_wait_time);

			bool is_waiting_frame_for_update() const;
			void set_frame_count_to_update_after(size_t frame_count_to_update_after);

			bool is_time_forward() const;
			void set_time_forward(bool time_forward);

			bool is_updating() const;
			void set_updating(bool updating);

			void give_step();
		};

		void update();
	}
}

#include "System.inl"

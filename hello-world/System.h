#pragma once
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
			double current_waited_time_ = 0;

			size_t frames_to_wait_for_update_ = 0;
			size_t current_waited_frames_ = 0;

			bool time_forward_ = true;
			bool updating_ = true;
			bool time_advance = false;

		public:
			void update();
			template <typename U> U get_frame_time() const;
			void set_frames_to_wait_for_update(size_t frames_to_wait_for_update);
			void set_update_wait_time(double update_wait_time_);
		};

		void update();
	}
}

#include "System.inl"

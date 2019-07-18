#include <chrono>
#include <thread>
#include "DynamicArray.h"
#include "System.h"

namespace
{
	const size_t OPTIMAL_FRAME_COUNT_PER_SECOND = 60;
	double g_max_frame_duration = 1. / OPTIMAL_FRAME_COUNT_PER_SECOND;
	double g_last_frame_duration = 0;

	Engine::DynamicArray<std::unique_ptr<Engine::Systems::System> > g_systems;
}

namespace Engine
{
	namespace Systems
	{
		double System::get_last_frame_duration() const
		{
			if (stepping_)
				return g_last_frame_duration;

			if (!updating_)
				return 0;

			if (update_wait_time_ == 0)
				return waited_time_;

			const size_t waited_frame_count = static_cast<size_t>(waited_time_ / update_wait_time_);
			return update_wait_time_ * waited_frame_count;
		}

		void System::update()
		{
			if (!updating_ && !stepping_)
				return;

			const bool needs_to_wait_more_frames = frame_count_since_last_update_ < frame_count_to_update_after_;
			const bool needs_to_wait_more_time = waited_time_ < update_wait_time_;

			waited_time_ += g_last_frame_duration;
			++frame_count_since_last_update_;

			if (needs_to_wait_more_frames || needs_to_wait_more_time)
				return;

			on_update();

			if (stepping_)
				waited_time_ = 0;
			else waited_time_ -= get_last_frame_duration();

			frame_count_since_last_update_ = 0;
			stepping_ = false;
		}

		bool System::is_waiting_time_for_update() const
		{
			return update_wait_time_ > 0;
		}

		void System::stop_waiting_time_for_update()
		{
			update_wait_time_ = 0;
		}

		void System::set_update_wait_time(double update_wait_time)
		{
			if (update_wait_time < 0)
				return;

			if (update_wait_time > 0)
				stepping_ = false;

			update_wait_time_ = update_wait_time;
		}

		bool System::is_waiting_frame_for_update() const
		{
			return frame_count_to_update_after_ > 0;
		}

		void System::set_frame_count_to_update_after(size_t frame_count_to_update_after)
		{
			if (frame_count_to_update_after > 0)
				stepping_ = false;

			frame_count_to_update_after_ = frame_count_to_update_after;
		}

		bool System::is_time_forward() const
		{
			return time_forward_;
		}

		void System::set_time_forward(bool time_forward)
		{
			time_forward_ = time_forward;
		}

		bool System::is_updating() const
		{
			return updating_;
		}

		void System::set_updating(bool updating)
		{
			updating_ = updating;
		}

		void System::give_step()
		{
			updating_ = false;
			stepping_ = true;
			update_wait_time_ = 0;
			frame_count_since_last_update_ = 0;
		}

		void update()
		{
			using Clock = std::chrono::high_resolution_clock;
			using Seconds = std::chrono::duration<double, std::chrono::seconds::period>;

			const Clock::time_point frame_start = Clock::now();

			for (const std::unique_ptr<System>& p_system : g_systems)
				p_system->update();

			Seconds frame_duration = Clock::now() - frame_start;
			const Seconds max_frame_duration(g_max_frame_duration);
			if (frame_duration < max_frame_duration)
			{
				std::this_thread::sleep_for(max_frame_duration - frame_duration);
				frame_duration = max_frame_duration;
			}

			g_last_frame_duration = frame_duration.count();
		}
	}
}

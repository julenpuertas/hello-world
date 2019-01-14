#include <chrono>
#include <thread>
#include "DynamicArray.h"
#include "BaseSystem.h"

namespace
{
	bool g_use_controlled_frame_duration = true;
	double g_last_frame_duration = 0;
	double g_max_frame_duration = 1. / 60;

	Engine::DynamicArray<std::shared_ptr<Engine::Systems::Base::System> > g_systems;
}

namespace Engine
{
	namespace Systems
	{
		namespace Base
		{
			void System::update()
			{
				const bool needs_to_wait_more_frames = frame_count_since_last_update_ < frame_count_to_update_after_;
				const bool needs_to_wait_more_time = waited_time_ < update_wait_time_;

				waited_time_ += g_last_frame_duration;
				++frame_count_since_last_update_;

				if (!needs_to_wait_more_frames && !needs_to_wait_more_time)
				{
					on_update();

					waited_time_ = 0;
					frame_count_since_last_update_ = 0;
				}

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
				update_wait_time_ = std::max(0., update_wait_time);
			}

			void System::set_frame_count_to_update_after(size_t frame_count_to_update_after)
			{
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
			}
		}

		void update()
		{
			using Clock = std::chrono::high_resolution_clock;
			using Seconds = std::chrono::duration<double, std::chrono::seconds::period>;

			const Clock::time_point frame_start = Clock::now();

			for (const std::shared_ptr<Base::System>& p_system : g_systems)
				p_system->update();

			Clock::duration frame_duration = Clock::now() - frame_start;
			const Seconds max_frame_duration(g_max_frame_duration);

			if (g_use_controlled_frame_duration && frame_duration < max_frame_duration)
			{
				std::this_thread::sleep_for(max_frame_duration - frame_duration);
				frame_duration = Clock::now() - frame_start;
			}

			const Seconds frame_seconds = frame_duration;
			g_last_frame_duration = frame_seconds.count();
		}
	}
}

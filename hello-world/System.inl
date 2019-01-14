
namespace Engine
{
	namespace Systems
	{
		template<typename T> void System<T>::update()
		{
			stepping_ = false;
		}

		template<typename T> template<typename U> U System<T>::get_frame_time() const
		{
			return U();
		}

		template<typename T> bool System<T>::is_waiting_time_for_update() const
		{
			return update_wait_time_ > 0;
		}

		template<typename T> void System<T>::stop_waiting_time_for_update()
		{
			update_wait_time_ = 0;
		}

		template<typename T> void System<T>::set_update_wait_time(double update_wait_time)
		{
			update_wait_time_ = update_wait_time;
		}

		template<typename T> bool System<T>::is_waiting_frame_count_for_update() const
		{
			return update_wait_frame_count_ > 0;
		}

		template<typename T> void System<T>::stop_waiting_frame_count_for_update()
		{
			update_wait_frame_count_ = 0;
		}

		template<typename T> void System<T>::set_update_wait_frame_count(size_t update_wait_frame_count)
		{
			update_wait_frame_count_ = update_wait_frame_count;
		}

		template<typename T> bool System<T>::is_time_forward() const
		{
			return time_forward_;
		}

		template<typename T> void System<T>::set_time_forward(bool time_forward)
		{
			time_forward_ = time_forward;
		}

		template<typename T> bool System<T>::is_updating() const
		{
			return updating_;
		}

		template<typename T> void System<T>::set_updating(bool updating)
		{
			updating_ = updating;
		}

		template<typename T> void System<T>::give_step()
		{
			updating_ = false;
			stepping_ = true;
		}
	}
}

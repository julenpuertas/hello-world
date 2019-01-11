
namespace Engine
{
	namespace Systems
	{
		template<typename T> void System<T>::update()
		{
		}

		template<typename T> template<typename U> U System<T>::get_frame_time() const
		{
			return U();
		}

		template<typename T>
		inline void System<T>::set_frames_to_wait_for_update(size_t frames_to_wait_for_update)
		{

		}

		template<typename T>
		inline void System<T>::set_update_wait_time(double update_wait_time_)
		{

		}
	}
}

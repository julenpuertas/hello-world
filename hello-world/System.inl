
namespace Engine
{
	namespace Systems
	{
		template<typename T> T System::get_frame_duration() const
		{
			return static_cast<T>(compute_frame_duration());
		}
	}
}

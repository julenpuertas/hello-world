
namespace Engine
{
	namespace Systems
	{
		template<typename T> T System::get_last_frame_seconds() const
		{
			return static_cast<T>(get_last_frame_duration());
		}
	}
}

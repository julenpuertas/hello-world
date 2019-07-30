
namespace Engine
{
	namespace Volumes
	{
		template <typename T> bool Frustrum::is_point_set_culled(T it, const T& it_end) const
		{
			BitArray<PLANE_COUNT> planes_with_all_points_culled;
			planes_with_all_points_culled.set();

			while (planes_with_all_points_culled.any() && it != it_end)
				planes_with_all_points_culled &= is_point_outside_planes(*(it++));

			return planes_with_all_points_culled.any();
		}
	}
}

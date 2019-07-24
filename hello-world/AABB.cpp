#include "Interval.h"
#include "AABB.h"

namespace Engine
{
	namespace BoundingVolumes
	{
		constexpr AABB::AABB(const FVector3& center, const FVector3& extend)
			: center_(center)
			, extend_(extend)
		{}

		AABB::AABB(const Pair<FVector3>& min_max_points)
		{
			set_min_max_points(min_max_points);
		}

		constexpr const FVector3& AABB::get_center() const
		{
			return center_;
		}

		constexpr void AABB::set_center(const FVector3& center)
		{
			center_ = center;
		}

		constexpr const FVector3& AABB::get_extend() const
		{
			return extend_;
		}

		constexpr void AABB::set_extend(const FVector3& extend)
		{
			extend_ = extend;
		}

		FVector3 AABB::get_scale() const
		{
			return extend_;
		}

		void AABB::set_scale(const FVector3& scale)
		{
			extend_ = scale;
		}

		Transform AABB::get_transform() const
		{
			return Transform(center_, get_scale());
		}

		constexpr float AABB::get_area() const
		{
			return 4 * (extend_.x * extend_.y + extend_.x * extend_.z + extend_.y * extend_.z);
		}

		constexpr float AABB::get_volume() const
		{
			return 8 * extend_.x * extend_.y * extend_.z;
		}

		Pair<FVector3> AABB::get_min_max_points() const
		{
			return std::make_pair(center_ - extend_, center_ + extend_);
		}

		void AABB::set_min_max_points(const FVector3& min_point, const FVector3& max_point)
		{
			center_ = (min_point + max_point) * .5f;
			extend_ = (max_point - min_point) * .5f;
		}

		void AABB::set_min_max_points(const Pair<FVector3>& min_max_points)
		{
			set_min_max_points(min_max_points.first, min_max_points.second);
		}

		FVector3 AABB::get_vertex(size_t index) const
		{
			if (index >= 8)
				return FVector3(std::numeric_limits<float>::quiet_NaN());

			FVector3 vertex = center_;
			for (size_t i = 0; i < FVector3::SIZE; ++i)
			{
				float extend_val = extend_[i];
				if (!(index & (static_cast<size_t>(1) << i)))
					extend_val *= -1;

				vertex[i] += extend_val;
			}

			return vertex;
		}

		AABB AABB::get_copy_of_half_size() const
		{
			return AABB(center_, extend_ * .5f);
		}

		AABB AABB::get_copy_at_vertex(size_t index) const
		{
			return AABB(get_vertex(index), extend_);
		}

		bool AABB::is_inside(const FVector3& point) const
		{
			const Pair<FVector3> min_max_points = get_min_max_points();

			bool inside = true;
			for (size_t i = 0; inside && i < FVector3::SIZE; ++i)
			{
				const Interval<float> interval = { min_max_points.first[i], true, min_max_points.second[i], true };
				inside &= interval.intersects(point[i]);
			}

			return inside;
		}

		bool AABB::intersects(const AABB& rhs) const
		{
			Pair<FVector3> min_max_points = get_min_max_points();
			Pair<FVector3> rhs_min_max_points = rhs.get_min_max_points();

			bool colliding = true;
			for (size_t i = 0; colliding && i < FVector3::SIZE; ++i)
			{
				const Interval<float> interval = { min_max_points.first[i], true, min_max_points.second[i], true };
				const Interval<float> rhs_interval = { rhs_min_max_points.first[i], true, rhs_min_max_points.second[i], true };
				colliding &= interval.intersects(rhs_interval);
			}

			return colliding;
		}
	}
}

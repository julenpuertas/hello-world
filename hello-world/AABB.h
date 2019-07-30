#pragma once
#include "Transform.h"

namespace Engine
{
	namespace Volumes
	{
		class AABB
		{
			FVector3 center_;
			FVector3 extend_{ .5f };

		public:
			static constexpr size_t VERTEX_COUNT = 8;

			AABB() = default;
			constexpr AABB(const FVector3& center, const FVector3& extend);
			AABB(const Pair<FVector3>& min_max_points);

			constexpr const FVector3& get_center() const;
			constexpr void set_center(const FVector3& center);

			constexpr const FVector3& get_extend() const;
			constexpr void set_extend(const FVector3& extend);

			FVector3 get_scale() const;
			void set_scale(const FVector3& scale);

			Transform get_transform() const;

			constexpr float get_area() const;
			constexpr float get_volume() const;

			Pair<FVector3> get_min_max_points() const;
			void set_min_max_points(const FVector3& min_point, const FVector3& max_point);
			void set_min_max_points(const Pair<FVector3>& min_max_points);

			FVector3 get_vertex(size_t index) const;

			AABB get_copy_of_half_size() const;
			AABB get_copy_at_vertex(size_t index) const;

			bool is_inside(const FVector3& point) const;
			bool intersects(const AABB& rhs) const;
		};
	}
}

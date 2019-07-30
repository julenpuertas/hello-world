#include "AABB.h"
#include "Frustrum.h"

namespace Engine
{
	namespace Volumes
	{
		Frustrum::Frustrum(const FMatrix4& perspective_matrix)
		{
			const size_t size = planes_.size();
			const FMatrix4 transpose = perspective_matrix.get_transpose();
			const FVector4 neg_last_row = -transpose[FMatrix4::WIDTH - 1];

			for (size_t i = 0; i < FVector3::SIZE; ++i)
			{
				const size_t index = i * 2;
				const FVector4& i_row = transpose[i];

				planes_[index] = neg_last_row - i_row;
				planes_[index + 1] = neg_last_row + i_row;
			}
		}

		bool Frustrum::is_culled(const AABB& aabb) const
		{
			Array<FVector3, AABB::VERTEX_COUNT> vertices;
			for (size_t i = 0; i < AABB::VERTEX_COUNT; ++i)
				vertices[i] = aabb.get_vertex(i);

			return is_point_set_culled(vertices.cbegin(), vertices.cend());
		}

		BitArray<Frustrum::PLANE_COUNT> Frustrum::is_point_outside_planes(const FVector3& world_pos) const
		{
			BitArray<PLANE_COUNT> outside;
			const FVector4 augmented_pos(world_pos, 1);

			for (size_t i = 0; i < PLANE_COUNT; ++i)
				outside[i] = augmented_pos.dot(planes_[i]) > 0;

			return outside;
		}
	}
}

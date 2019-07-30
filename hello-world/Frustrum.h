#pragma once
#include "Matrix.h"
#include "Array.h"
#include "BitArray.h"
#include "DynamicArray.h"

namespace Engine
{
	namespace Volumes
	{
		class AABB;

		class Frustrum
		{
		public:
			static constexpr size_t PLANE_COUNT = FVector3::SIZE * 2;

			explicit Frustrum(const FMatrix4& perspective_matrix);

			template <typename T> bool is_point_set_culled(T it, const T& it_end) const;
			bool is_culled(const AABB& aabb) const;

		private:
			Array<FVector4, PLANE_COUNT> planes_;

			BitArray<PLANE_COUNT> is_point_outside_planes(const FVector3& world_pos) const;
		};
	}
}

#include "Frustrum.inl"

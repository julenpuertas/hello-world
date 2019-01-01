#pragma once
#include "Rotation.h"

namespace Engine
{
	class Transform
	{
		FMatrix3 get_vector_transformation_inverse_matrix() const;

	public:
		FVector3 translation_;
		FVector3 scale_{ 1.f };
		Rotation rotation_;

		Transform() = default;
		template <typename ... Args>
		Transform(const FVector3& translation, const FVector3& scale, Args&& ... arguments);

		Transform operator*(const Transform& rhs) const;
		Transform operator/(const Transform& rhs) const;

		FMatrix3x4 get_matrix() const;
		FMatrix3x4 get_inverse_matrix() const;
		FMatrix3 get_normal_matrix() const;

		FVector3 parent_to_local(const FVector3& point) const;
		FVector3 local_to_parent(const FVector3& point) const;
	};
}

#include "Transform.inl"

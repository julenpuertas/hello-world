#include "Transform.h"

namespace Engine
{
	template<typename ...Args> Transform Transform::Transformation::operator()(const Transform& transform, Args&& ...arguments) const
	{
		const ParenthoodPolicy parenthood_policy(std::forward<Args>(arguments) ...);
		Transform result = transform;

		if (parenthood_policy.is_translation_affected())
			result.translation_ = translation_transformer_ * result.translation_;

		if (parenthood_policy.is_scale_affected())
			result.scale_ = scale_transformer_ * result.scale_;

		if (parenthood_policy.is_rotation_affected())
			result.rotation_ = rotation_transformer_ * result.rotation_;

		return result;
	}

	template <typename ... Args> Transform::Transform(const FVector3& translation, const FVector3& scale, Args&& ... arguments)
		: translation_(translation)
		, scale_(scale)
		, rotation_(std::forward<Args>(arguments) ...)
	{}

	template<typename ...Args> void Transform::set_rotation(Args&& ...arguments)
	{
		rotation_ = Rotation(std::forward<Args>(arguments) ...);
	}
}

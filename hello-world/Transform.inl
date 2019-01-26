#include "Transform.h"

namespace Engine
{
	template <typename ... Args> Transform::Transform(const FVector3& translation, const FVector3& scale, Args&& ... arguments)
		: translation_(translation)
		, scale_(scale)
		, rotation_(std::forward<Args>(arguments) ...)
	{}

	template<typename ...Args> void Transform::set_rotation(Args&& ... arguments)
	{
		rotation_ = Rotation(std::forward<Args>(arguments) ...);
	}

	template<typename ...Args> const FVector3& Transform::translate(Args&& ... arguments)
	{
		translation_ += FVector3(std::forward<Args>(arguments) ...);
		return translation_;
	}

	template<typename ...Args> const FVector3& Transform::scale(Args&& ... arguments)
	{
		scale_ *= FVector3(std::forward<Args>(arguments) ...);
		return scale_;
	}

	template<typename ...Args> const Rotation& Transform::rotate(Args&& ... arguments)
	{
		return rotation_ = Rotation(std::forward<Args>(arguments) ...) * rotation_;
	}
}

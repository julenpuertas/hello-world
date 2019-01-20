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
}

#pragma once

namespace Engine
{
	class GameObject;

	namespace ComponentTraits
	{
		template <typename T> bool can_have_component_of_type(const GameObject& gameobject);
	}
}

#include "ComponentTraits.inl"

#pragma once

namespace Engine
{
	namespace ComponentTraits
	{
		template<typename T> bool can_have_component_of_type(const GameObject&)
		{
			return true;
		}
	}
}

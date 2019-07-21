#pragma once
#include <functional>
#include "Vector.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			bool is_area_clear(const SVector2& corner_1, const SVector2& corner_2, const std::function<bool(const SVector2&)>& is_tile_walkable_fn);
		}
	}
}

#include <algorithm>
#include "Pair.h"
#include "IsAreaClear.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			bool is_area_clear(const SVector2& corner_1, const SVector2& corner_2, const std::function<bool(const SVector2&)>& is_tile_walkable_fn)
			{
				if (!is_tile_walkable_fn)
					return false;

				bool valid = true;
				const Pair<size_t> col_limits = std::minmax(corner_1.x, corner_2.x);
				const Pair<size_t> row_limits = std::minmax(corner_1.y, corner_2.y);

				for (SVector2 indices(col_limits.first, row_limits.first); valid && indices.y <= row_limits.second; ++indices.y)
					for (indices.x = col_limits.first; valid && indices.x <= col_limits.second; ++indices.x)
						valid &= is_tile_walkable_fn(indices);

				return valid;
			}
		}
	}
}

#pragma once

#include "Table.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			class FloydWarshall
			{
				SVector2 grid_dimensions_;
				Table<SVector2> parent_matrix_;
				std::function<bool(const SVector2&)> is_tile_walkable_fn_;

			public:
				explicit FloydWarshall(const std::function<bool(const SVector2&)>& is_tile_walkable_fn);
				void compute_paths(const SVector2& grid_dimensions);
				DynamicArray<SVector2> get_path(const SVector2& start_pos, const SVector2& end_pos) const;
			};
		}
	}
}

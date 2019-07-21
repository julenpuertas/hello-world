#pragma once
#include "AStar.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			class JumpPointSearch : public AStar
			{
				SVector2 jump(const SVector2& indices, const IVector2& direction) const;
				bool can_jump_diagonaly(const SVector2& indices, const IVector2& direction) const;

			public:
				explicit JumpPointSearch(const std::function<bool(const SVector2&)>& is_tile_walkable_fn, const std::function<float(const SVector2&)>& get_visibility_fn);
				void iterate() override;
				void initialize(const SVector2& init_coords) override;
			};
		}
	}
}

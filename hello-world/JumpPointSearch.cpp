#include "IsAreaClear.h"
#include "JumpPointSearch.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			JumpPointSearch::JumpPointSearch(const std::function<bool(const SVector2&)>& is_tile_walkable_fn, const std::function<float(const SVector2&)>& get_visibility_fn)
				: AStar(is_tile_walkable_fn, get_visibility_fn)
			{}

			SVector2 JumpPointSearch::jump(const SVector2& parent_indices, const IVector2& direction) const
			{
				SVector2 indices = parent_indices;
				indices += direction;

				// obstacle
				const SVector2 invalid_jump(-1);
				if (!is_tile_walkable_fn_ || !is_tile_walkable_fn_(indices))
					return invalid_jump;

				// goal reached
				if (indices == goal_coords_)
					return indices;

				// cardinal movement
				if (!is_diagonal(direction))
				{
					const auto has_forced_cardinal_neighbour = [this, &indices, &parent_indices](const SVector2& dir_normal)
					{
						return is_tile_walkable_fn_(indices + dir_normal) && !is_tile_walkable_fn_(parent_indices + dir_normal);
					};

					const IVector2 direction_normal(direction.y, direction.x);
					if (has_forced_cardinal_neighbour(direction_normal) || has_forced_cardinal_neighbour(-direction_normal))
						return indices;
				}

				else	// diagonal movement
				{
					// can jump cardinaly
					if (jump(indices, IVector2(direction.x, 0)) != invalid_jump || jump(indices, IVector2(0, direction.y)) != invalid_jump)
						return indices;

					else if (!can_jump_diagonaly(indices, direction))
						return invalid_jump;
				}

				return jump(indices, direction);
			}

			bool JumpPointSearch::can_jump_diagonaly(const SVector2& indices, const IVector2& direction) const
			{
				return is_tile_walkable_fn_(SVector2(indices.x + direction.x, indices.y)) && is_tile_walkable_fn_(SVector2(indices.x, indices.y + direction.y));
			}

			void JumpPointSearch::initialize(const SVector2& init_coords)
			{
				const Node init_node(init_coords);
				for (IVector2 direction(-1); direction.y < 2; ++direction.y)
				{
					for (direction.x = -1; direction.x < 2; ++direction.x)
					{
						if (direction.x || direction.y)
						{
							SVector2 adjacent_coords = init_coords;
							adjacent_coords += direction;

							if (is_area_clear(init_coords, adjacent_coords, is_tile_walkable_fn_))
								open_list_.emplace_back(init_node, adjacent_coords, *this);
						}
					}
				}

				std::make_heap(open_list_.begin(), open_list_.end(), &node_greater);
			}

			void JumpPointSearch::iterate()
			{
				// While (Open List is not empty)
				if (!is_finished())
				{
					// Pop cheapest node of Open List (parent node)
					const Node parent_node = pop_cheapest_node();

					// If node is the Goal Node, then path found(RETURN “found”)
					const SVector2& parent_node_coords = parent_node.get_coords();
					finished_ = parent_node_coords == goal_coords_;
					if (!finished_)
					{
						const auto insert_successor = [this, &parent_node](const IVector2& direction)
						{
							const SVector2 coords = jump(parent_node.get_coords(), direction);
							if (coords != SVector2(-1))
								insert(Node(parent_node, coords, *this));
						};

						const IVector2 parent_direction = parent_node.get_direction();

						// is diagonal
						if (is_diagonal(parent_direction))
						{
							insert_successor(IVector2(parent_direction.x, 0));
							insert_successor(IVector2(0, parent_direction.y));

							if (can_jump_diagonaly(parent_node_coords, parent_direction))
								insert_successor(parent_direction);
						}

						// cardinal
						else if (is_tile_walkable_fn_)
						{
							SVector2 prev_pos = parent_node_coords;
							prev_pos -= parent_direction;
							const IVector2 direction_normal(parent_direction.y, parent_direction.x);

							const auto evaluate_sides = [this, &parent_node_coords, &parent_direction, &insert_successor, &prev_pos, &direction_normal](const IVector2& direction_normal)
							{
								const SVector2 u_direction_normal = direction_normal;
								if (!is_tile_walkable_fn_(prev_pos + u_direction_normal))
								{
									insert_successor(direction_normal);
									const IVector2 diagonal_dir = parent_direction + direction_normal;
									if (can_jump_diagonaly(parent_node_coords, diagonal_dir))
										insert_successor(diagonal_dir);
								}
							};

							evaluate_sides(direction_normal);
							evaluate_sides(-direction_normal);
							insert_successor(parent_direction);
						}
					}

					// place parent node on the Closed List (we’re done with it)
					closed_list_.push_back(parent_node);
				}
			}
		}
	}
}

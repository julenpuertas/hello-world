#include "Constants.h"
#include "IsAreaClear.h"
#include "FloydWarshall.h"

namespace
{
	static constexpr size_t INVALID_INDEX = std::numeric_limits<size_t>::max();
}

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			FloydWarshall::FloydWarshall(const std::function<bool(const SVector2&)>& is_tile_walkable_fn)
				: is_tile_walkable_fn_(is_tile_walkable_fn)
			{}

			void FloydWarshall::compute_paths(const SVector2& grid_dimensions)
			{
				grid_dimensions_ = grid_dimensions;

				// weight matrix
				const SVector2 matrix_dimensions(grid_dimensions.x * grid_dimensions.y);
				Table<float> cost_matrix(matrix_dimensions, std::numeric_limits<float>::infinity());

				parent_matrix_.clear();
				parent_matrix_.resize(matrix_dimensions, SVector2(INVALID_INDEX));

				// initialize matrix
				const SVector2 invalid_offset(1, 1);
				const float sqrt_2 = Math::sqrt_2<float>();
				for (SVector2 start_tile_pos; start_tile_pos.y < grid_dimensions.y; ++start_tile_pos.y)
				{
					for (start_tile_pos.x = 0; start_tile_pos.x < grid_dimensions.x; ++start_tile_pos.x)
					{
						// for each neighbour
						const size_t start_tile_index = start_tile_pos.x + grid_dimensions.x * start_tile_pos.y;
						for (SVector2 neighbour_offset; neighbour_offset.y < 3; ++neighbour_offset.y)
						{
							for (neighbour_offset.x = 0; neighbour_offset.x < 3; ++neighbour_offset.x)
							{
								// from start node to start node
								if (neighbour_offset == invalid_offset)
								{
									const SVector2 start_tile_indices(start_tile_index);
									cost_matrix[start_tile_indices] = .0f;
									parent_matrix_[start_tile_indices] = start_tile_pos;
								}

								else
								{
									// walk from parent to neighbour is doable
									const SVector2 neighbour_tile_pos = start_tile_pos + neighbour_offset - invalid_offset;
									if (is_area_clear(start_tile_pos, neighbour_tile_pos, is_tile_walkable_fn_))
									{
										const size_t neighbour_tile_index = neighbour_tile_pos.x + grid_dimensions.x * neighbour_tile_pos.y;
										const SVector2 start_to_neighbour(neighbour_tile_index, start_tile_index);
										cost_matrix[start_to_neighbour] = neighbour_offset.x == 1 || neighbour_offset.y == 1 ? 1 : sqrt_2;
										parent_matrix_[start_to_neighbour] = start_tile_pos;
									}
								}
							}
						}
					}
				}

				// compute costs and parents
				for (SVector2 inter_tile_pos; inter_tile_pos.y < grid_dimensions.y; ++inter_tile_pos.y)
				{
					for (inter_tile_pos.x = 0; inter_tile_pos.x < grid_dimensions.x; ++inter_tile_pos.x)
					{
						// intermediate tile
						const size_t inter_tile_index = inter_tile_pos.x + grid_dimensions.x * inter_tile_pos.y;
						for (SVector2 start_tile_pos; start_tile_pos.y < grid_dimensions.y; ++start_tile_pos.y)
						{
							for (start_tile_pos.x = 0; start_tile_pos.x < grid_dimensions.x; ++start_tile_pos.x)
							{
								// start tile
								const size_t start_tile_index = start_tile_pos.x + grid_dimensions.x * start_tile_pos.y;
								for (SVector2 end_tile_pos; end_tile_pos.y < grid_dimensions.y; ++end_tile_pos.y)
								{
									for (end_tile_pos.x = 0; end_tile_pos.x < grid_dimensions.x; ++end_tile_pos.x)
									{
										// end tile
										const size_t end_tile_index = end_tile_pos.x + grid_dimensions.x * end_tile_pos.y;
										const SVector2 start_to_end(end_tile_index, start_tile_index);
										const SVector2 inter_to_end(end_tile_index, inter_tile_index);

										// update if necessary
										float new_cost = cost_matrix[SVector2(inter_tile_index, start_tile_index)] + cost_matrix[inter_to_end];
										float& old_cost = cost_matrix[start_to_end];
										if (new_cost < old_cost)
										{
											old_cost = new_cost;
											parent_matrix_[start_to_end] = parent_matrix_[inter_to_end];
										}
									}
								}
							}
						}
					}
				}
			}

			DynamicArray<SVector2> FloydWarshall::get_path(const SVector2& start_pos, const SVector2& end_pos) const
			{
				if (start_pos.x >= grid_dimensions_.x || start_pos.y >= grid_dimensions_.y || end_pos.x >= grid_dimensions_.x || end_pos.y >= grid_dimensions_.y)
					return DynamicArray<SVector2>();

				DynamicArray<SVector2> path;
				path.reserve(grid_dimensions_.x * grid_dimensions_.y);

				const size_t end_index = end_pos.x + grid_dimensions_.x * end_pos.y;
				SVector2 current_pos = start_pos;

				while (current_pos != end_pos)
				{
					path.push_back(current_pos);
					const size_t parent_index = current_pos.x + grid_dimensions_.x * current_pos.y;
					current_pos = parent_matrix_[SVector2(parent_index, end_index)];

					// path not found
					if (current_pos.x == INVALID_INDEX || current_pos.y == INVALID_INDEX)
						return DynamicArray<SVector2>();
				}

				path.push_back(end_pos);

				return path;
			}
		}
	}
}

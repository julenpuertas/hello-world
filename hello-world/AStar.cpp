#include "Pair.h"
#include "IsAreaClear.h"
#include "AStar.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			float AStar::get_cost(const FVector2& point_1, const FVector2& point_2) const
			{
				Pair<float> diff = { abs(point_2.x - point_1.x), abs(point_2.y - point_1.y) };

				float cost = std::numeric_limits<float>::quiet_NaN();
				switch (heuristic_)
				{
				case Heuristic::EUCLIDEAN:
					cost = sqrt(diff.first * diff.first + diff.second * diff.second);
					break;

				case Heuristic::OCTILE:
					diff = std::minmax(diff.first, diff.second);
					cost = diff.first * sqrt(2.f) + diff.second - diff.first;
					break;

				case Heuristic::CHEBYSHEV:
					cost = std::max(diff.first, diff.second);
					break;

				case Heuristic::MANHATTAN:
					cost = diff.first + diff.second;
					break;
				}

				return cost;
			}

			AStar::Node::Node(const SVector2& coords)
				: coords_(coords)
				, parent_coords_(static_cast<size_t>(-1))
			{}

			AStar::Node::Node(const Node& parent, const SVector2& coords, const AStar& algorithm)
				: coords_(coords)
				, parent_coords_(parent.coords_)
			{
				const IVector2 direction = coords_ - parent_coords_;

				// given cost
				given_cost_ = static_cast<float>(std::max(abs(direction.x), abs(direction.y)));
				if (is_diagonal(direction))
					given_cost_ *= sqrt(2.f);
				given_cost_ += parent.given_cost_;

				if (algorithm.get_visibility_fn_)
					given_cost_ += 20 * algorithm.get_visibility_fn_(coords_);

				// heuristic cost
				heuristic_cost_ = algorithm.get_cost(algorithm.goal_coords_, coords_) * algorithm.weight_;
			}

			const SVector2& AStar::Node::get_coords() const
			{
				return coords_;
			}

			AStar::Node AStar::Node::get_neighbour(const IVector2& direction, const AStar& algorithm) const
			{
				SVector2 neighbour_coords = coords_;
				neighbour_coords += direction;
				return Node(*this, neighbour_coords, algorithm);
			}

			bool AStar::Node::operator<(const Node& rhs) const
			{
				return given_cost_ + heuristic_cost_ < rhs.given_cost_ + rhs.heuristic_cost_;;
			}

			bool AStar::Node::operator==(const Node& rhs) const
			{
				return coords_ == rhs.coords_;
			}

			bool AStar::Node::is_parent_of(const Node& node) const
			{
				return coords_ == node.parent_coords_;
			}

			IVector2 AStar::Node::get_direction() const
			{
				const auto normalize_int = [](int i)
				{
					if (i > 1)
						return 1;

					if (i < -1)
						return -1;

					return i;
				};

				const IVector2 result = coords_ - parent_coords_;
				return IVector2(normalize_int(result.x), normalize_int(result.y));
			}

			bool AStar::node_greater(const Node& lhs, const Node& rhs)
			{
				return rhs < lhs;
			}

			void AStar::insert(const Node& new_node)
			{
				// look for neighbour in open list
				DynamicArray<Node>::const_iterator it_end = open_list_.cend();
				DynamicArray<Node>::const_iterator it = std::find(open_list_.cbegin(), it_end, new_node);

				if (it != it_end)
				{
					if (new_node < *it)
					{
						open_list_.erase(it);
						open_list_.push_back(new_node);
						std::make_heap(open_list_.begin(), open_list_.end(), &node_greater);
					}
				}

				else
				{
					const auto push_neighbour_to_open_list = [this, &new_node]()
					{
						open_list_.push_back(new_node);
						std::push_heap(open_list_.begin(), open_list_.end(), &node_greater);
					};

					// look for neighbour in closed list
					it_end = closed_list_.cend();
					it = std::find(closed_list_.cbegin(), it_end, new_node);

					if (it != it_end)
					{
						if (new_node < *it)
						{
							closed_list_.erase(it);
							push_neighbour_to_open_list();
						}
					}

					else push_neighbour_to_open_list();
				}
			}

			bool AStar::is_diagonal(const IVector2& direction)
			{
				return direction.x && direction.y;
			}

			AStar::AStar(const std::function<bool(const SVector2&)>& is_tile_walkable_fn, const std::function<float(const SVector2&)>& get_visibility_fn)
				: is_tile_walkable_fn_(is_tile_walkable_fn)
				, get_visibility_fn_(get_visibility_fn)
			{}

			DynamicArray<SVector2> AStar::get_open_list() const
			{
				DynamicArray<SVector2> result;
				result.reserve(open_list_.size());

				for (const Node& node : open_list_)
					result.push_back(node.get_coords());

				return result;
			}

			DynamicArray<SVector2 > AStar::get_closed_list() const
			{
				DynamicArray<SVector2> result;
				result.reserve(closed_list_.size());

				for (const Node& node : closed_list_)
					result.push_back(node.get_coords());

				return result;
			}

			DynamicArray<SVector2> AStar::get_path() const
			{
				DynamicArray<SVector2> path;

				if (finished_)
				{
					const size_t closed_list_size = closed_list_.size();
					if (closed_list_size)
					{
						path.reserve(closed_list_size);

						const DynamicArray<Node>::const_iterator it_begin = closed_list_.cbegin();
						const DynamicArray<Node>::const_iterator it_end = closed_list_.cend();
						DynamicArray<Node>::const_iterator it = it_end - 1;
						while (it != it_end)
						{
							const Node& node = *it;
							path.push_back(node.get_coords());

							it = std::find_if(it_begin, it_end, [&node](const Node& parent_node)
							{
								return parent_node.is_parent_of(node);
							});
						}

						std::reverse(path.begin(), path.end());
					}
				}

				return path;
			}

			bool AStar::is_finished() const
			{
				return finished_ || open_list_.empty();
			}

			void AStar::reset(const SVector2& init_coords, const SVector2& goal_coords, Heuristic heuristic, float weight)
			{
				// clear lists
				open_list_.clear();
				closed_list_.clear();

				// save new configuration
				goal_coords_ = goal_coords;
				heuristic_ = heuristic;
				weight_ = weight;

				// stright line optimization
				finished_ = false;
				initialize(init_coords);
			}

			AStar::Node AStar::pop_cheapest_node()
			{
				std::pop_heap(open_list_.begin(), open_list_.end(), &node_greater);
				const Node node = open_list_.back();
				open_list_.pop_back();

				return node;
			}

			void AStar::initialize(const SVector2& init_coords)
			{
				if (is_tile_walkable_fn_ && is_tile_walkable_fn_(init_coords))
					open_list_.emplace_back(init_coords);
			}

			void AStar::iterate()
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
						// For (all neighboring child nodes)
						for (IVector2 neighbour_direction(-1); neighbour_direction.y < 2; ++neighbour_direction.y)
						{
							for (neighbour_direction.x = -1; neighbour_direction.x < 2; ++neighbour_direction.x)
							{
								// skip parent
								if (neighbour_direction.x || neighbour_direction.y)
								{
									// check if both and its diagonals are walkable
									const Node neighbour_node = parent_node.get_neighbour(neighbour_direction, *this);
									if (is_area_clear(parent_node_coords, neighbour_node.get_coords(), is_tile_walkable_fn_))
										insert(neighbour_node);
								}
							}
						}
					}

					// place parent node on the Closed List (we’re done with it)
					closed_list_.push_back(parent_node);
				}
			}
		}
	}
}

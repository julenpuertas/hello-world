#pragma once
#include "DynamicArray.h"
#include "Vector.h"

namespace Engine
{
	namespace AI
	{
		namespace Pathfinding
		{
			class AStar
			{
			public:
				enum class Heuristic : Byte
				{
					EUCLIDEAN,
					OCTILE,
					CHEBYSHEV,
					MANHATTAN,
					DEFAULT = CHEBYSHEV
				};

				explicit AStar(const std::function<bool(const SVector2&)>& is_tile_walkable_fn, const std::function<float(const SVector2&)>& get_visibility_fn);

				DynamicArray<SVector2> get_open_list() const;
				DynamicArray<SVector2> get_closed_list() const;
				DynamicArray<SVector2> get_path() const;
				bool is_finished() const;

				void reset(const SVector2& init_coords, const SVector2& goal_coords, Heuristic heuristic, float weight);
				virtual void iterate();

			protected:
				class Node
				{
					SVector2 coords_;
					SVector2 parent_coords_;
					float given_cost_ = 0;
					float heuristic_cost_ = 0;

				public:
					explicit Node(const SVector2& coords);
					Node(const Node& parent, const SVector2& coords, const AStar& algorithm);

					bool operator==(const Node& rhs) const;
					bool operator<(const Node& rhs) const;
					const SVector2& get_coords() const;
					Node get_neighbour(const IVector2& direction, const AStar& algorithm) const;
					bool is_parent_of(const Node& node) const;
					IVector2 get_direction() const;
				};

				float get_cost(const FVector2& point_1, const FVector2& point_2) const;
				static bool is_diagonal(const IVector2& direction);
				static bool node_greater(const Node& lhs, const Node& rhs);
				void insert(const Node& new_node);
				virtual void initialize(const SVector2& init_coords);
				Node pop_cheapest_node();

				// callbacks
				std::function<bool(const SVector2&)> is_tile_walkable_fn_;
				std::function<float(const SVector2&)> get_visibility_fn_;

				// current state
				DynamicArray<Node> open_list_;
				DynamicArray<Node> closed_list_;
				bool finished_ = false;

				// configuration
				SVector2 goal_coords_;
				Heuristic heuristic_ = Heuristic::DEFAULT;
				float weight_ = 1;
			};
		}
	}
}

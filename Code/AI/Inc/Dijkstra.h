#pragma once
#include "GridBasedGraph.h"

namespace AI
{
	using GetCost = std::function<float(const Node*, const Node*)>;

	class Dijkstra
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost);
		const NodeList GetClosedList() const { return mClosedList; }
	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}
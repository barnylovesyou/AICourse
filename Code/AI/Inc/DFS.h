#pragma once

#include "GridBasedGraph.h"

namespace AI
{
	class DFS
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY);
		//TODO check correct
		const NodeList GetClosedList() const { return mClosedList; }
	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}
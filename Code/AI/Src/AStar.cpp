#include "Precompiled.h"
#include "AStar.h"

using namespace AI;

bool AStar::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetHeuristic getHeuristic)
{
	bool found = false;
	graph.ResetSearchParams();
	mOpenList.clear();
	mClosedList.clear();

	GridBasedGraph::Node* node = graph.GetNode(startX, startY);
	GridBasedGraph::Node* endNode = graph.GetNode(endX, endY);
	node->opened = true;
	mOpenList.push_back(node);

	auto sortCost = [](const GridBasedGraph::Node* a, const GridBasedGraph::Node* b)
	{
		return a->cost + a->heuristic < b->cost + b->heuristic;
	};

	//I can add a check for if the endNode is not nullptr. This will not garuntee fastest path but it will be a lot quicker and still fairly efficient
	while (!found &&!mOpenList.empty())
	{
		node = mOpenList.front();
		mOpenList.pop_front();

		if (node->column == endX && node->row == endY)
		{
			found = true;
		}
		else
		{
			for (GridBasedGraph::Node* neighbor : node->neighbors)
			{
				if (neighbor == nullptr || neighbor->closed)
				{
					continue;
				}
				float cost = node->cost + getCost(node, neighbor);
				if (!neighbor->opened)
				{
					mOpenList.push_back(neighbor);
					neighbor->opened = true;
					neighbor->parent = node;
					neighbor->cost = cost;
					neighbor->heuristic = getHeuristic(neighbor,endNode);
				}
				else if (cost < neighbor->cost)
				{
					neighbor->parent = node;
					neighbor->cost = cost;
				}
			}
		}
		mOpenList.sort(sortCost);

		mClosedList.push_back(node);
		node->closed = true;
	}

	return found;
}

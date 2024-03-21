#include "HWCompTravelTo.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"
#include "HWArriveAtPos.h"
#include "HWGoToPos.h"

auto Diagonal = [](const AI::Node* neighbor, const AI::Node* endNode)->float
{
	float D1 = 1.0f;
	float D2 = 1.0f;
	float dx = abs(neighbor->column - endNode->column);
	float dy = abs(neighbor->row - endNode->row);
	return D1 * sqrt(dx + dy) + (D2 - 2 * D1) * std::min(dx, dy);
};

HWCompTravelTo::HWCompTravelTo()
{
}

void HWCompTravelTo::Activate(HumanWorker& agent)
{
	mStatus = HWCompTravelTo::Status::Active;
	auto* world = MyAIWorld::GetInstance();
	auto& map = *(world->GetMap());
	RemoveAllSubGoals(agent);
	float distanceSqr = X::Math::DistanceSqr(agent.position, mDestination);
	X::Math::Vector2 start = agent.position;
	X::Math::Vector2 end = mDestination;
	if (distanceSqr > map.GetTileHeight()*map.GetTileWidth())
	{
		Path path = map.FindPathAStar(map.GetRow(start.x), map.GetColumn(start.y), map.GetRow(end.x), map.GetColumn(end.y), Diagonal);
		for(int i  = 0; i<path.size(); ++i)
		{
			if (i == path.size() - 1)
			{
				auto newGoal = AddSubGoal<HWArriveAtPos>();
				newGoal->SetDestination(path[i]);
			}
			else
			{
				auto newGoal = AddSubGoal<HWGoToPos>();
				newGoal->SetDestination(path[i]);
			}
		}
	}
}

HWCompTravelTo::Status HWCompTravelTo::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactiveIfFailed(agent);
	return mStatus;
}

void HWCompTravelTo::Terminate(HumanWorker& agent)
{
}

void HWCompTravelTo::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

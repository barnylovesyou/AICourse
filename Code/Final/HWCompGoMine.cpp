#include "HWCompGoMine.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"
#include "HWArriveAtPos.h"
#include "HWGoToPos.h"
#include "HWMining.h"
#include "HWDeposit.h"
#include "HumanBase.h"
#include "ImGui/Inc/imgui.h"

auto GoMineDiagonal = [](const AI::Node* neighbor, const AI::Node* endNode)->float
	{
		float D1 = 1.0f;
		float D2 = 1.0f;
		float dx = abs(neighbor->column - endNode->column);
		float dy = abs(neighbor->row - endNode->row);
		return D1 * sqrt(dx + dy) + (D2 - 2 * D1) * std::min(dx, dy);
	};
HWCompGoMine::HWCompGoMine()
{
}

void HWCompGoMine::Activate(HumanWorker& agent)
{
	mStatus = HWCompGoMine::Status::Active;
	RemoveAllSubGoals(agent);
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	float distanceSqr = X::Math::DistanceSqr(mDestination, world->GetHumanBase()->position);
	//Deposit at end
	auto newDepGoal = AddSubGoal<HWDeposit>();
	X::Math::Vector2 start = mDestination;
	X::Math::Vector2 end = world->GetHumanBase()->position;
	//Return to base
	if (distanceSqr > map->GetTileHeight() * map->GetTileWidth())
	{
		Path path = map->FindPathAStar(map->GetColumn(start.x), map->GetRow(start.y), map->GetColumn(end.x), map->GetRow(end.y), GoMineDiagonal);
		for (int i = 0; i < path.size(); ++i)
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
	auto newMineGoal = AddSubGoal<HWMining>();
	distanceSqr = X::Math::DistanceSqr(agent.position, mDestination);
	start = agent.position;
	end = mDestination;
	if (distanceSqr > map->GetTileHeight() * map->GetTileWidth())
	{
		Path path = map->FindPathAStar(map->GetColumn(start.x), map->GetRow(start.y), map->GetColumn(end.x), map->GetRow(end.y), GoMineDiagonal);
		for (int i = 0; i < path.size(); ++i)
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

HWCompGoMine::Status HWCompGoMine::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactiveIfFailed(agent);
	return mStatus;
}

void HWCompGoMine::Terminate(HumanWorker& agent)
{
}

void HWCompGoMine::Debug(HumanWorker& agent)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	ImGui::Text("GoalComposite: GoMine: FinalDestination X:%f  Y:%f", mDestination.x, mDestination.y);
	X::DrawScreenCircle(map->GetPixelPositionFromLocation(mDestination), 7.5f, X::Colors::Red);
	mSubGoals.back()->Debug(agent);
}

void HWCompGoMine::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

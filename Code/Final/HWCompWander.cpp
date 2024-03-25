#include "HWCompWander.h"
#include "MyAIWorld.h"
#include "HWCompTravelTo.h"
#include "MyTileMap.h"
#include "ImGui/Inc/imgui.h"

HWCompWander::HWCompWander()
{
}

void HWCompWander::Activate(HumanWorker& agent)
{
	mStatus = HWCompWander::Status::Active;
	RemoveAllSubGoals(agent);
	X::Math::Vector2 destination = GetRandomDestination(agent.position);;
	auto travelGoal = AddSubGoal<HWCompTravelTo>();
	travelGoal->SetDestination(destination);
	for (int i = 1; i < mCount; ++i)
	{
		destination = GetRandomDestination(destination);
		auto travelGoal = AddSubGoal<HWCompTravelTo>();
		travelGoal->SetDestination(destination);
	}
	std::reverse(mSubGoals.begin(), mSubGoals.end());

}

HWCompWander::Status HWCompWander::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactiveIfFailed(agent);
	return mStatus;

	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactiveIfFailed(agent);
	return mStatus;
}

void HWCompWander::Terminate(HumanWorker& agent)
{
}

void HWCompWander::Debug(HumanWorker& agent)
{
	ImGui::Text("GoalComposite: Wander: Count:%i", mCount);
	mSubGoals.back()->Debug(agent);
}

X::Math::Vector2 HWCompWander::GetRandomDestination(X::Math::Vector2 start)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	X::Math::Vector2 dir = X::RandomUnitCircle();
	if (map->GetRow(start.y) <= 2)
	{
		dir.y = X::Math::Abs(dir.y);
	}
	else if (map->GetRow(start.y) >= map->GetRows() - 3)
	{
		dir.y = (dir.y < 0) ? -dir.y : dir.y;
	}
	if (map->GetColumn(start.x)<=2)
	{
		dir.x = X::Math::Abs(dir.x);
	}
	else if (map->GetColumn(start.x)>=map->GetColumns()-3)
	{
		dir.x = (dir.x > 0) ? -dir.x : dir.x;
	}
	X::Math::Vector2 destination = start + dir * X::RandomFloat(40.0f, 120.0f);
	destination.x = X::Math::Clamp(destination.x, 0.0f, map->GetMax().x);
	destination.y = X::Math::Clamp(destination.y, 0.0f, map->GetMax().y);
	return destination;
}

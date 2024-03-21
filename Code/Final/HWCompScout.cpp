#include "HWCompScout.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"
#include "HWCompTravelTo.h"
#include "HWWander.h"

HWCompScout::HWCompScout()
{
}

void HWCompScout::Activate(HumanWorker& agent)
{
	mStatus = HWCompScout::Status::Active;
	RemoveAllSubGoals(agent);
	AddSubGoal<HWWander>();
	auto newGoal = AddSubGoal<HWCompTravelTo>();
	newGoal->SetDestination(mDestination);
}

HWCompScout::Status HWCompScout::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactiveIfFailed(agent);
	return mStatus;
}

void HWCompScout::Terminate(HumanWorker& agent)
{
}

void HWCompScout::SetDestination(const X::Math::Vector2& destination)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	mDestination = map->GetPixelPosition(map->GetRow(destination.x), map->GetColumn(destination.y));
}

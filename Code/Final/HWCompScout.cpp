#include "HWCompScout.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"
#include "HWCompTravelTo.h"
#include "HWCompWander.h"
#include "ImGui/Inc/imgui.h"
#include "HumanBase.h"

HWCompScout::HWCompScout()
{
}

void HWCompScout::Activate(HumanWorker& agent)
{
	mStatus = HWCompScout::Status::Active;
	RemoveAllSubGoals(agent);
	auto newTravel = AddSubGoal<HWCompTravelTo>();
	newTravel->SetDestination(mDestination);
}

HWCompScout::Status HWCompScout::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	mStatus = ProcessSubGoals(agent);
	ReactiveIfFailed(agent);
	if (mStatus == HWCompScout::Status::Completed)
	{
		MyAIWorld::GetInstance()->GetHumanBase()->DoneScouting(agent);
	}
	return mStatus;
}

void HWCompScout::Terminate(HumanWorker& agent)
{
}

void HWCompScout::Debug(HumanWorker& agent)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	ImGui::Text("GoalComposite: Scout: FinalDestination X:%f  Y:%f", mDestination.x, mDestination.y);
	X::DrawScreenCircle(map->GetPixelPositionFromLocation(mDestination), 7.5f, X::Colors::Red);
	mSubGoals.back()->Debug(agent);
}

void HWCompScout::SetDestination(const X::Math::Vector2& destination)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	mDestination = map->GetPixelPosition(map->GetColumn(destination.x), map->GetRow(destination.y));
}

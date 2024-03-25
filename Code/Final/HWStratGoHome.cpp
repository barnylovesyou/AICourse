#include "HWStratGoHome.h"

#include "HWCompTravelTo.h"
#include "MyAIWorld.h"
#include "HumanBase.h"
#include "ImGui/Inc/imgui.h"

void HWStratGoHome::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratGoHome::CalculateDesirability(HumanWorker& agent) const
{
	switch (static_cast<HumanWorkerState>(agent.GetState()))
	{
	case HumanWorkerState::Mine:
		return 0.0f;
		break;
	case HumanWorkerState::GoHome:
		return 100.0f;
		break;
	case HumanWorkerState::Scout:
		return 0.0f;
		break;
	}
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratGoHome::CreateGoal(HumanWorker& agent) const
{
	auto newGoal = std::make_unique<HWCompTravelTo>();
	newGoal->SetDestination(MyAIWorld::GetInstance()->GetHumanBase()->position);
	return newGoal;
}

void HWStratGoHome::Debug(HumanWorker& agent) const
{
	ImGui::Text("Current Strategy: GoHome");
}

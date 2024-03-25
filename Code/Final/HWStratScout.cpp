#include "HWStratScout.h"

#include "HWCompScout.h"
#include "MyAIWorld.h"
#include "HumanBase.h"
#include "ImGui/Inc/imgui.h"

void HWStratScout::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratScout::CalculateDesirability(HumanWorker& agent) const
{
	switch (static_cast<HumanWorkerState>(agent.GetState()))
	{
	case HumanWorkerState::Mine:
		return 0.0f;
		break;
	case HumanWorkerState::GoHome:
		return 0.0f;
		break;
	case HumanWorkerState::Scout:
		return 100.0f;
		break;
	}
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratScout::CreateGoal(HumanWorker& agent) const
{
	auto newGoal = std::make_unique<HWCompScout>();
	newGoal->SetDestination(agent.GetScoutDestination());
	return newGoal;
}

void HWStratScout::Debug(HumanWorker& agent) const
{
	ImGui::Text("Current Strategy: Scout");
}

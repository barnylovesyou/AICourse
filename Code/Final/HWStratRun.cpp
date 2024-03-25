#include "HWStratRun.h"

#include "HWCompScout.h"
#include "ImGui/Inc/imgui.h"

void HWStratRun::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratRun::CalculateDesirability(HumanWorker& agent) const
{
	//if(agent.GetPerceptionModule()->GetMemoryRecords())
	return 0.0f;
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratRun::CreateGoal(HumanWorker& agent) const
{
	auto newGoal = std::make_unique<HWCompScout>();
	newGoal->SetDestination(mTargetDestination);
	return newGoal;
}

void HWStratRun::Debug(HumanWorker& agent) const
{
	ImGui::Text("Current Strategy: Run");
}

#include "HWDeposit.h"
#include "TypeIds.h"
#include "MyAIWorld.h"
#include "ImGui/Inc/imgui.h"

HWDeposit::HWDeposit()
{
}

void HWDeposit::Activate(HumanWorker& agent)
{
	mStatus = HWDeposit::Status::Active;
}

HWDeposit::Status HWDeposit::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	agent.Dump();
	mStatus = HWDeposit::Status::Completed;
	return mStatus;
}

void HWDeposit::Terminate(HumanWorker& agent)
{
}

void HWDeposit::Debug(HumanWorker& agent)
{
	ImGui::Text("Goal: Deposit");
}

void HWDeposit::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

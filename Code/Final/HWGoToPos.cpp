#include "HWGoToPos.h"
#include "ImGui/Inc/imgui.h"

HWGoToPos::HWGoToPos()
{
}

void HWGoToPos::Activate(HumanWorker& agent)
{
	mStatus = HWGoToPos::Status::Active;
	agent.destination = mDestination;
}

HWGoToPos::Status HWGoToPos::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	if (X::Math::DistanceSqr(agent.position, mDestination) < 25.0f)
	{
		mStatus = HWGoToPos::Status::Completed;
	}
	return mStatus;
}

void HWGoToPos::Terminate(HumanWorker& agent)
{
}

void HWGoToPos::Debug(HumanWorker& agent)
{
	ImGui::Text("Goal: GoToPos: X:%f  Y:%f", mDestination.x, mDestination.y);
	X::DrawScreenLine(agent.position, mDestination, X::Colors::Red);
}

void HWGoToPos::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

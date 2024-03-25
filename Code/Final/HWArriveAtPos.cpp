#include "HWArriveAtPos.h"
#include "ImGui/Inc/imgui.h"

HWArriveAtPos::HWArriveAtPos()
{
}

void HWArriveAtPos::Activate(HumanWorker& agent)
{
	mStatus = HWArriveAtPos::Status::Active;
	agent.destination = mDestination;
	agent.SetArrive(true);
	agent.SetSeek(false);
}

HWArriveAtPos::Status HWArriveAtPos::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	if (X::Math::DistanceSqr(agent.position, mDestination) < 16.0f)
	{
		mStatus = HWArriveAtPos::Status::Completed;
	}
	return mStatus;
}

void HWArriveAtPos::Terminate(HumanWorker& agent)
{
	agent.SetArrive(false);
	agent.SetSeek(true);
}

void HWArriveAtPos::Debug(HumanWorker& agent)
{
	ImGui::Text("Goal: Arrive At: X:%f  Y:%f" , mDestination.x, mDestination.y);
	X::DrawScreenLine(agent.position, mDestination, X::Colors::Red);
}

void HWArriveAtPos::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

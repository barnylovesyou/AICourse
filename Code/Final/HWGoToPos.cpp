#include "HWGoToPos.h"

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
	if (X::Math::DistanceSqr(agent.position, mDestination) < 16.0f)
	{
		mStatus = HWGoToPos::Status::Completed;
	}
	return mStatus;
}

void HWGoToPos::Terminate(HumanWorker& agent)
{
}

void HWGoToPos::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

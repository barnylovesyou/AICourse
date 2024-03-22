#include "HWStratRun.h"

#include "HWCompScout.h"

void HWStratRun::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratRun::CalculateDesirability(HumanWorker& agent) const
{
	return 100.0f;
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratRun::CreateGoal() const
{
	auto newGoal = std::make_unique<HWCompScout>();
	newGoal->SetDestination(mTargetDestination);
	return newGoal;
}

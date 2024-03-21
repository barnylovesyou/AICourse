#include "HWStratScout.h"

#include "HWCompScout.h"

void HWStratScout::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratScout::CalculateDesirability(HumanWorker& agent) const
{
	return 100.0f;
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratScout::CreateGoal() const
{
	auto newGoal = std::make_unique<HWCompScout>();
	newGoal->SetDestination(mTargetDestination);
	return newGoal;
}

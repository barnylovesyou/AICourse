#include "HWStratScout.h"

#include "HWCompScout.h"
#include "MyAIWorld.h"
#include "HumanBase.h"

void HWStratScout::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratScout::CalculateDesirability(HumanWorker& agent) const
{
	return MyAIWorld::GetInstance()->GetHumanBase()->GetWDesirability(agent, WStrats::Scout);
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratScout::CreateGoal() const
{
	auto newGoal = std::make_unique<HWCompScout>();
	newGoal->SetDestination(mTargetDestination);
	return newGoal;
}

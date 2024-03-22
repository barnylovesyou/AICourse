#include "HWStratGoHome.h"

#include "HWCompTravelTo.h"
#include "MyAIWorld.h"
#include "HumanBase.h"

void HWStratGoHome::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratGoHome::CalculateDesirability(HumanWorker& agent) const
{
	return MyAIWorld::GetInstance()->GetHumanBase()->GetWDesirability(agent, WStrats::Home);
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratGoHome::CreateGoal() const
{
	auto newGoal = std::make_unique<HWCompTravelTo>();
	newGoal->SetDestination(MyAIWorld::GetInstance()->GetHumanBase()->position);
	return newGoal;
}

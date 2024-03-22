#include "HWStratMine.h"

#include "HWCompGoMine.h"
#include "MyAIWorld.h"
#include "HumanBase.h"


void HWStratMine::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratMine::CalculateDesirability(HumanWorker& agent) const
{
	return MyAIWorld::GetInstance()->GetHumanBase()->GetWDesirability(agent, WStrats::Mine);
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratMine::CreateGoal() const
{
	auto newGoal = std::make_unique<HWCompGoMine>();
	newGoal->SetDestination(mTargetDestination);
	return newGoal;
}

#include "HWMining.h"
#include "TypeIds.h"
#include "MyAIWorld.h"

HWMining::HWMining()
{
}

void HWMining::Activate(HumanWorker& agent)
{
	mStatus = HWMining::Status::Active;
	agent.ChangeState(HumanWorkerState::Mine);
	auto world = MyAIWorld::GetInstance();
	auto entities = world->GetEntitiesInRange(X::Math::Circle(agent.position, 5.0f), static_cast<uint32_t>(AgentType::Mineral));
	float distance = 30.0f;
	float newDist;
	for (auto mineral : entities)
	{
		newDist = X::Math::DistanceSqr(agent.position, mineral->position);
		if (newDist < distance)
		{
			mMineral = (Mineral*)mineral;
		}
	}
}

HWMining::Status HWMining::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	if (agent.GetState()!=static_cast<uint32_t>(HumanWorkerState::Mine))
	{
		agent.Carry(mMineral->GetValue());
		mStatus = HWMining::Status::Completed;
	}
	return mStatus;
}

void HWMining::Terminate(HumanWorker& agent)
{
}

void HWMining::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

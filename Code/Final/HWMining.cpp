#include "HWMining.h"
#include "TypeIds.h"
#include "MyAIWorld.h"
#include "ImGui/Inc/imgui.h"

HWMining::HWMining()
{
}

void HWMining::Activate(HumanWorker& agent)
{
	mStatus = HWMining::Status::Active;
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
	float startTime = X::GetTime();
	agent.destination = agent.position;
}

HWMining::Status HWMining::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	if (X::GetTime()-startTime>5.0f)
	{
		agent.Carry(mMineral->GetValue());
		mStatus = HWMining::Status::Completed;
	}
	return mStatus;
}

void HWMining::Terminate(HumanWorker& agent)
{
}

void HWMining::Debug(HumanWorker& agent)
{
	ImGui::Text("Goal: Mining: IsMining: %s", (agent.GetState() != static_cast<uint32_t>(HumanWorkerState::Mine))? "true" : "false");
}

void HWMining::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

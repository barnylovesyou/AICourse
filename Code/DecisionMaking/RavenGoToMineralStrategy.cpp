#include "RavenGoToMineralStrategy.h"

#include "TypeIDs.h"
#include "GoalMoveToPosition.h"

void RavenGoToMineralStrategy::SetPerception(const AI::PerceptionModule* perception)
{
	mPerception = perception;
}

float RavenGoToMineralStrategy::CalculateDesirability(Raven& agent) const
{
	const auto& memoryRecords = mPerception->GetMemoryRecords();
	float highestImportance = 0.0f;
	X::Math::Vector2 targetDestination = X::Math::Vector2::Zero()
	for (auto& record : memoryRecords)
	{
		AgentType agentType = static_cast<AgentType>(record.GetProperty<int>("type", 0));
		if (agentType == AgentType::Mineral)
		{
			if (record.importance > highestImportance)
			{
				highestImportance = record.importance;
				mTargetDestination = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
			}
		}
	}
	return highestImportance;
}

std::unique_ptr<AI::Goal<Raven>> RavenGoToMineralStrategy::CreateGoal() const
{
	auto newGoal = std::make_unique<GoalMoveToPosition>();
	newGoal->SetDestination(mTargetDestination);
	return newGoal;
}

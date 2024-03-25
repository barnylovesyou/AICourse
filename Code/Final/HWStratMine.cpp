#include "HWStratMine.h"

#include "HWCompGoMine.h"
#include "MyAIWorld.h"
#include "HumanBase.h"
#include "ImGui/Inc/imgui.h"


void HWStratMine::SetTargetDestination(const X::Math::Vector2& destination)
{
	mTargetDestination = destination;
}

float HWStratMine::CalculateDesirability(HumanWorker& agent) const
{
	switch(static_cast<HumanWorkerState>(agent.GetState()))
	{
	case HumanWorkerState::Mine:
		return 100.0f;
		break;
	case HumanWorkerState::GoHome:
	{
		auto base = MyAIWorld::GetInstance()->GetHumanBase();
		auto minerals = base->GetMineralInfo();
		for (auto m : minerals)
		{
			if (m.CanMine())
			{
				float dotProduct = X::Math::Dot(base->position - m.mineral->position, base->position - agent.position);

				float angle = std::acos(dotProduct);

				if (angle <= X::Math::kPi / 6)
				{
					agent.SetMineralTarget(m.mineral);
					return 150.0f;
				}
			}
		}
		return 0.0f;
		break;
	}
	case HumanWorkerState::Scout:
		return 0.0f;
		break;
	}
}

std::unique_ptr<AI::Goal<HumanWorker>> HWStratMine::CreateGoal(HumanWorker& agent) const
{
	auto newGoal = std::make_unique<HWCompGoMine>();
	newGoal->SetDestination(agent.GetMineralTarget()->position);
	return newGoal;
}

void HWStratMine::Debug(HumanWorker& agent) const
{
	ImGui::Text("Current Strategy: Mine");
}

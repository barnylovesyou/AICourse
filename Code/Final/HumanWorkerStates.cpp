#include "HumanWorkerStates.h"
#include "HumanWorker.h"

void Mine::Enter(HumanWorker& agent)
{
}

void Mine::Update(HumanWorker& agent, float deltaTime)
{
	mineTimer += deltaTime;
	if (mineTimer > 5.0f)
	{
		agent.ChangeState(HumanWorkerState::Move);
	}
}

void Mine::Exit(HumanWorker& agent)
{
}

void Mine::DebugUI(HumanWorker& agent)
{
}

void Move::Enter(HumanWorker& agent)
{
}

void Move::Update(HumanWorker& agent, float deltaTime)
{
	agent.GetPerceptionModule()->Update(deltaTime);
	agent.GetDecisionModule()->Update();
	const X::Math::Vector2 force = agent.GetSteeringModule()->Calculate();
	const X::Math::Vector2 acceleration = force / agent.mass;
	agent.velocity += acceleration * deltaTime;
	agent.position += agent.velocity * deltaTime;
}

void Move::Exit(HumanWorker& agent)
{
}

void Move::DebugUI(HumanWorker& agent)
{
}

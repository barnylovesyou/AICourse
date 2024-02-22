#include "Precompiled.h"
#include "PursuitBehavior.h"

#include "Agent.h"

X::Math::Vector2 AI::PursuitBehavior::Calculate(Agent& agent)
{
	if (agent.target == nullptr)
	{
		return X::Math::Vector2();
	}

	const X::Math::Vector2& targetPosition = agent.target->position;
	X::Math::Vector2 agentToTarget =  targetPosition - agent.position;
	float distToTarget = X::Math::Magnitude(agentToTarget);

	if (distToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}

	const float timeToTarget = distToTarget / agent.maxSpeed;
	const X::Math::Vector2& targetVelocity = agent.target->velocity;
	const X::Math::Vector2 predictedPosition = targetPosition + targetVelocity * timeToTarget;

	agentToTarget = predictedPosition - agent.position;
	distToTarget = X::Math::Magnitude(agentToTarget);

	if(distToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}

	const X::Math::Vector2 desiredVelocity = agentToTarget / distToTarget * agent.maxSpeed;
	const X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenCircle(targetPosition, 20.0f, X::Colors::Red);
		X::DrawScreenLine(agent.position, agent.position +agent.velocity, X::Colors::Green);
		X::DrawScreenLine(agent.position, agent.position +desiredVelocity, X::Colors::Yellow);
	}
	return seekForce;
}

X::Math::Vector2 AI::EvadeBehavior::Calculate(Agent& agent)
{
	if (agent.target == nullptr)
	{
		return X::Math::Vector2();
	}

	const X::Math::Vector2& targetPosition = agent.target->position;
	X::Math::Vector2 agentToTarget = targetPosition - agent.position;
	float distToTarget = X::Math::Magnitude(agentToTarget);

	if (distToTarget > maxDistance)
	{
		return X::Math::Vector2();
	}

	const float timeToTarget = distToTarget / agent.maxSpeed;
	const X::Math::Vector2& targetVelocity = agent.target->velocity;
	const X::Math::Vector2 predictedPosition = targetPosition + targetVelocity * timeToTarget;

	agentToTarget = predictedPosition - agent.position;
	distToTarget = X::Math::Magnitude(agentToTarget);

	if (distToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}
	//opposite velocity as in pursuit
	const X::Math::Vector2 desiredVelocity = -(agentToTarget / distToTarget * agent.maxSpeed);
	const X::Math::Vector2 evadeForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenCircle(agent.target->position, maxDistance, X::Colors::Red);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
	}
	return evadeForce;
}

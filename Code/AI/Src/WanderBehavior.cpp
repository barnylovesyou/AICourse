#include "Precompiled.h"
#include "WanderBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	//apply a random jitter to wander target
	X::Math::Vector2 newWanderTarget = mLocalWanderTarget + (X::RandomUnitCircle() * mWanderJitter);
	newWanderTarget = X::Math::Normalize(newWanderTarget) * mWanderRadius;
	mLocalWanderTarget = newWanderTarget;

	//project infront of agent
	newWanderTarget += X::Math::Vector2(0.0f, mWanderDistance);

	//transform target into world space
	const X::Math::Matrix3 worldTransform = agent.GetWorldTransform();
	const X::Math::Vector2 worldWanderTarget = X::Math::TransformCoord(newWanderTarget, worldTransform);

	//now seek to target
	const X::Math::Vector2 agentToDest = worldWanderTarget - agent.position;
	const float distance = X::Math::Magnitude(agentToDest);
	X::Math::Vector2 desiredVelocity= X::Math::Vector2::Zero();
	if (distance > 1.0f)
	{
		desiredVelocity = agentToDest/distance * agent.maxSpeed;
	}
	const X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		const X::Math::Vector2 wanderCenter = X::Math::TransformCoord({ 0.0f, mWanderDistance }, worldTransform);
		X::DrawScreenCircle(wanderCenter, mWanderRadius, X::Colors::Yellow);
		X::DrawScreenDiamond(worldWanderTarget, 3.0f, X::Colors::Orange);
		X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Green);
	}

	return seekForce;
}

void WanderBehavior::Setup(float radius, float distance, float jitter)
{
	mWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}

#include "Precompiled.h"
#include "SeekBehavior.h"
#include "Agent.h"

X::Math::Vector2 AI::SeekBehavior::Calculate(Agent& agent)
{
    const X::Math::Vector2 agentToDest = agent.destination - agent.position;
    if (X::Math::MagnitudeSqr(agentToDest) <= 1.0f)
    {
        return X::Math::Vector2::Zero();
    }
    return X::Math::Vector2();

    const X::Math::Vector2 desiredVelocity = X::Math::Normalize(agentToDest) * agent.maxSpeed;
    const X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
    if (IsDebug())
    {
        X::DrawScreenLine();
    }
    return seekForce;
}

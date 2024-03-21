#include "Precompiled.h"
#include "SeekBehavior.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 SeekBehavior::Calculate(Agent& agent)
{
    X::Math::Vector2 desiredVelocity = X::Math::Vector2::Zero();
    const X::Math::Vector2 agentToDest = agent.destination - agent.position;
    //min distance to target is 1
    if (X::Math::MagnitudeSqr(agentToDest) > 1.0f)
    {
        desiredVelocity = X::Math::Normalize(agentToDest) * agent.maxSpeed;
    }
    const X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;
    if (IsDebug())
    {
        X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
        X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
        X::DrawScreenCircle(agent.destination, 20.0f, X::Colors::Red);
    }
    return seekForce;
}

X::Math::Vector2 FleeBehavior::Calculate(Agent& agent)
{
    X::Math::Vector2 desiredVelocity = X::Math::Vector2::Zero();
    const X::Math::Vector2 agentToDest = agent.destination - agent.position;
    //min distance to target is 1
    if (X::Math::MagnitudeSqr(agentToDest) <= panicDistance*panicDistance)
    {
        desiredVelocity = -X::Math::Normalize(agentToDest) * agent.maxSpeed;
    }
    const X::Math::Vector2 fleeForce = desiredVelocity - agent.velocity;
    if (IsDebug())
    {
        X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
        X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
        X::DrawScreenCircle(agent.destination, 20.0f, X::Colors::Red);
        X::DrawScreenCircle(agent.destination, panicDistance, X::Colors::Orange);
    }
    return fleeForce;
}

X::Math::Vector2 ArriveBehavior::Calculate(Agent& agent)
{
    X::Math::Vector2 desiredVelocity = X::Math::Vector2::Zero();
    const X::Math::Vector2 agentToDest = agent.destination - agent.position;
    const float distance = X::Math::Magnitude(agentToDest);
    //min distance to target is 1
    if (distance > 1.0f)
    {
        float  speed = distance;
        if (distance < 10.0f)
        {
            const float decelTweaker = agent.mass * decelTweak;
            //NOTE deceleration is an enum assuming that its from fast to slow order
            const float decelerationScale = (static_cast<float>(deceleration) + 1.0f) * decelTweaker;
            speed = speed / decelerationScale;
        }
        speed = X::Math::Min(speed, agent.maxSpeed);
        desiredVelocity = agentToDest/distance * speed;
    }
    const X::Math::Vector2 arriveForce = desiredVelocity - agent.velocity;
    if (IsDebug())
    {
        X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
        X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
        X::DrawScreenCircle(agent.destination, 20.0f, X::Colors::Red);
    }
    return arriveForce;
}

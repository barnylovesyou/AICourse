#include "Precompiled.h"
#include "GroupBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 SeperationBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 seperationForce = X::Math::Vector2::Zero();
	for(auto& n : agent.neighbors)
	{
		if (n != agent.target)
		{
			X::Math::Vector2 dirToNeighbor = n->position - agent.position;
			float distance = X::Math::Magnitude(dirToNeighbor);
			float overLapDistance = (n->radius + agent.radius) - distance;
			if (overLapDistance > 0.0f)
			{
				dirToNeighbor /= distance;
				if (X::Math::Dot(dirToNeighbor, agent.heading)>0.0f)
				{
					float desiredSpeed = (overLapDistance/agent.radius)*forceMultiplier*agent.maxSpeed;
					desiredSpeed = X::Math::Min(desiredSpeed, agent.maxSpeed);
					seperationForce += (-dirToNeighbor * desiredSpeed);
					seperationForce -= agent.velocity;
				}
			}
		}
	}

	if (IsDebug())
	{
		X::DrawScreenCircle(agent.position, agent.radius, X::Colors::Honeydew);
		X::DrawScreenLine(agent.position, agent.position + seperationForce, X::Colors::White);
	}

	return seperationForce;
}

X::Math::Vector2 AlignmentBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 alignmentForce;
	X::Math::Vector2 averageHeading;
	float totalAgents = 0;
	for (auto& n : agent.neighbors) 
	{
		if (n != agent.target)
		{
			if (X::Math::Dot(agent.heading, n->heading) > 0.0f)
			{
				averageHeading += n->heading;
				++totalAgents;
			}
		}
	}

	if (totalAgents > 0.0f)
	{
		averageHeading /= totalAgents;
		alignmentForce = (averageHeading - agent.heading) * agent.maxSpeed;
	}
	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + alignmentForce, X::Colors::Pink);
	}
	return alignmentForce;
}

X::Math::Vector2 CohesionBehavior::Calculate(Agent& agent)
{
	X::Math::Vector2 cohesionForce;
	X::Math::Vector2 centerOfMass;
	float totalAgents = 0.0f;
	for (auto& n : agent.neighbors)
	{
		if (n != agent.target)
		{
			centerOfMass += n->position;
			++totalAgents;
		}
	}
	if (totalAgents > 0.0f)
	{
		centerOfMass /= totalAgents;
		const X::Math::Vector2 desiredVelocity = X::Math::Normalize(centerOfMass-agent.position) * agent.maxSpeed;
		cohesionForce = desiredVelocity - agent.velocity;
	}
	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + cohesionForce, X::Colors::Teal);
	}
	return cohesionForce;
}

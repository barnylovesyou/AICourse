#pragma once

#include <AI.h>
#include <XEngine.h>

class MyMovementBehaviorBehavior : public AI::SteeringBehavior
{
public:
	X::Math::Vector2 Calculate(Agent& agent) override;
};
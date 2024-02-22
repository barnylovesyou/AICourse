#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class PursuitBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};

	class EvadeBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		void SetMaxDistance(float distance) {maxDistance= distance ; }
	private:
		float maxDistance = 500.0f;
	};
}
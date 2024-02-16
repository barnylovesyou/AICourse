#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class SeperationBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
		void SetForceMultiplier(float multiplier) { forceMultiplier = multiplier; }
	private: 
		float forceMultiplier = 5.0f;
	};

	class AlignmentBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};

	class CohesionBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}
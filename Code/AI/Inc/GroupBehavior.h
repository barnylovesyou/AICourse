#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class SeperationBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;
	};
}
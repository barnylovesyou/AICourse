#pragma once

#include <AI.h>

#include "HumanWorker.h"

class HWStratScout : public AI::Strategy<HumanWorker>
{
public:
	void SetTargetDestination(const X::Math::Vector2& destination);

	float CalculateDesirability(HumanWorker& agent) const override;
	std::unique_ptr<AI::Goal<HumanWorker>> CreateGoal() const override;

private:
	X::Math::Vector2 mTargetDestination;
	bool destinationReached;
};
#pragma once
#include <AI.h>

#include "HumanWorker.h"

class HWCompTravelTo : public AI::GoalComposite<HumanWorker>
{
public:
	using Status = AI::Goal<HumanWorker>::Status;
	HWCompTravelTo();

	void Activate(HumanWorker& agent) override;
	Status Process(HumanWorker& agent) override;
	void Terminate(HumanWorker& agent) override;

	void SetDestination(const X::Math::Vector2& destination);

private:
	X::Math::Vector2 mDestination;
};
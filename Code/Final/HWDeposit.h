#pragma once
#include <AI.h>

#include "HumanWorker.h"

class HWDeposit : public AI::Goal<HumanWorker>
{
public:
	using Status = AI::Goal<HumanWorker>::Status;
	HWDeposit();

	void Activate(HumanWorker& agent) override;
	Status Process(HumanWorker& agent) override;
	void Terminate(HumanWorker& agent) override;

	void SetDestination(const X::Math::Vector2& destination);

private:
	X::Math::Vector2 mDestination;
};
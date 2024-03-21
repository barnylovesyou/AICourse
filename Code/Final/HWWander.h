#pragma once
#include <AI.h>

#include "HumanWorker.h"

class HWWander : public AI::Goal<HumanWorker>
{
public:
	using Status = AI::Goal<HumanWorker>::Status;
	HWWander();

	void Activate(HumanWorker& agent) override;
	Status Process(HumanWorker& agent) override;
	void Terminate(HumanWorker& agent) override;

	void SetDestination(const X::Math::Vector2& destination);

private:
	X::Math::Vector2 GetRandomDestination(HumanWorker& agent);
	X::Math::Vector2 mDestination;
	int mCount;
};
#pragma once
#include <AI.h>

#include "HumanWorker.h"

class HWCompWander : public AI::GoalComposite<HumanWorker>
{
public:
	using Status = AI::Goal<HumanWorker>::Status;
	HWCompWander();

	void Activate(HumanWorker& agent) override;
	Status Process(HumanWorker& agent) override;
	void Terminate(HumanWorker& agent) override;
	void Debug(HumanWorker& agent) override;

	void SetCount(const int count) { mCount = count; }

private:
	X::Math::Vector2 GetRandomDestination(X::Math::Vector2 start);
	X::Math::Vector2 mDestination;
	int mCount = 3;
};
#pragma once
#include <AI.h>

#include "HumanWorker.h"

class HWMining : public AI::Goal<HumanWorker>
{
public:
	using Status = AI::Goal<HumanWorker>::Status;
	HWMining();

	void Activate(HumanWorker& agent) override;
	Status Process(HumanWorker& agent) override;
	void Terminate(HumanWorker& agent) override;
	void Debug(HumanWorker& agent) override;

	void SetDestination(const X::Math::Vector2& destination);

private:
	X::Math::Vector2 mDestination;
	Mineral* mMineral = nullptr;
	float startTime;
};
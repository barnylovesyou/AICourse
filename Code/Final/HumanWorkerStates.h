#pragma once
#include <AI.h>

class HumanWorker;

class Mine : public AI::State<HumanWorker>
{
public:
	void Enter(HumanWorker& agent) override;
	void Update(HumanWorker& agent, float deltaTime) override;
	void Exit(HumanWorker& agent) override;
	void DebugUI(HumanWorker& agent) override;
private:
	float mineTimer = 0;
};
class Move : public AI::State<HumanWorker>
{
public:
	void Enter(HumanWorker& agent) override;
	void Update(HumanWorker& agent, float deltaTime) override;
	void Exit(HumanWorker& agent) override;
	void DebugUI(HumanWorker& agent) override;
};
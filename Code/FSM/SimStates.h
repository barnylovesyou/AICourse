#pragma once

#include <AI.h>
#include "Sim.h"

class GoHomeAndSleepUntilRestedState : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class GoMineAndDigForNugget : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class QuenchThirst : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class DepositGold : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
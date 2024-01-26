#pragma once

#include <AI.h>
#include "Miner.h"

class GoHomeAndSleepUntilRestedState : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI(Miner& agent) override;
};
class GoMineAndDigForNugget : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI(Miner& agent) override;
};
class QuenchThirst : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI(Miner& agent) override;
};
class DepositGold : public AI::State<Miner>
{
public:
	void Enter(Miner& agent) override;
	void Update(Miner& agent, float deltaTime) override;
	void Exit(Miner& agent) override;
	void DebugUI(Miner& agent) override;
};
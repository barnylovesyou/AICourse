#pragma once

#include <AI.h>
#include "Sim.h"

//GoToWork,
//Work,
//TakeBreak,
//GoToWashroom,
//GoToHome,
//GoHome,
//MakeDinner,
//Relax,
//PutOutFire,
//Shower,
//Sleep,
//GoToBank,
//DepositMoney

class GoToWork : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class Work : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class TakeBreak : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class GoToWashroom : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class GoToHome : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class MakeDinner : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class Relax : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class PutOutFire : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class Shower : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class Sleep : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class GoToBank : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class DepositMoney : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
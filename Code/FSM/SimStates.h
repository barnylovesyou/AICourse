#pragma once

#include <AI.h>
#include "Sim.h"


class GoToWork : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mTravelTime;
};
class Work : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mPayCheck;
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
private:
	int mWashroomTime;
};
class GoToHome : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mTravelTime;
};
class AtHome : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class MakeFood : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mCookTime;
};
class Hobby : public AI::State<Sim>
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
private:
	int mFireTime;
	int mFireStart;
};
class Shower : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mShowerTime;
	int mShowerStart;
};
class GoToBank : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mTravelTime;
};
class DepositMoney : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mDepositTime;
};
class AtBank : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class Snack : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
private:
	int mSnackTime;
};
class Dead : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
class Win : public AI::State<Sim>
{
public:
	void Enter(Sim& agent) override;
	void Update(Sim& agent, float deltaTime) override;
	void Exit(Sim& agent) override;
	void DebugUI(Sim& agent) override;
};
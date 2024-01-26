#pragma once

#include<AI.h>

enum Location
{
	Home,
	Mine,
	Saloon,
	Bank
};
enum class MinerState
{
	GoHomeAndSleepTillRested,
	GoMineAndDigForNugget,
	QuenchThirst,
	DepositGold
};

class Miner
{
public:
	Miner() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeState(MinerState newState);
	void DebugUI();

	//check miner status
	Location GetLocation() const;
	bool IsPocketFull() const;
	bool IsWealthy() const;
	bool IsRested() const;
	bool IsThirsty() const;

	//update status functions
	void SetLocation(Location location);
	void AddGoldCarried(int amount);
	void AddGoldToBank();
	void IncreaseFatigue();

	void ResetFatigue();
	void ResetThirst();

private:
	AI::StateMachine<Miner> mStateMachine;
	Location mLocation;
	int mGoldCarried;
	int mGoldInBank;
	int mFatigue;
	int mThirst;
};

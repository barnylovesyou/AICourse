#pragma once

#include<AI.h>

enum Location
{
	Home,
	Job,
	Travelling,
	Bank
};
enum Location
{
	Home,
	Mine,
	Saloon,
	Bank
};
enum class SimState
{
	GoToWork,
	Work,
	TakeBreak,
	GoToWashroom,
	GoHome,
	MakeDinner,
	Relax,
	PutOutFire,
	Shower,
	Sleep,
	GoToBank,
	DepositMoney
};

class Sim
{
public:
	Sim() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeState(SimState newState);
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


	//Stat Changes
	void Life();
	void AddFatigue(int fatigue);
	void AddFood(int food);
	void AddHappiness(int happiness);
	void AddMoney(int money);
	void AddWashroom(int washroom);
	void AddClean(int clean);
	void ResetWashroom();
	void ResetHealth();

private:
	AI::StateMachine<Sim> mStateMachine;
	Location mLocation;
	int mMoney;
	int mHappiness;
	int mFood;
	int mWashroom;
	int mClean;
	int mHealth;
	int mFatigue;
	float tick;

	int mGoldCarried;
	int mGoldInBank;
	int mFatigue;
	int mThirst;
};

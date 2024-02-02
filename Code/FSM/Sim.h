#pragma once

#include<AI.h>

enum Location
{
	Home,
	Job,
	Travelling,
	Bank
};
enum class SimState
{
	GoToWork,
	Work,
	TakeBreak,
	GoToWashroom,
	GoToHome,
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


	//update status functions
	void SetLocation(Location location);
	void AddMoneyToBank();


	//Stat Changes
	void Life();
	void AddFatigue(int fatigue);
	void AddFood(int food);
	void AddHappiness(int happiness);
	void AddMoney(int money);
	void AddWashroom(int washroom);
	void AddClean(int clean);
	void AddLife(int life);
	void ResetWashroom();
	void ResetHealth();
	void StartFire();
	void PutOutFire();

private:
	AI::StateMachine<Sim> mStateMachine;
	Location mLocation;
	int mMoney;
	int mHappiness;
	int mFood;
	int mWashroom;
	int mClean;
	int mLife;
	int mFatigue;
	int mMoneyInBank;
	int mHour;
	int mMinutes;
	int mFireTimer;
	float tick;
	bool mBurning;

	int mGoldCarried;
	int mGoldInBank;
	int mFatigue;
	int mThirst;
};

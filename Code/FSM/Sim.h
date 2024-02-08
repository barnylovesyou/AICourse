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
	AtHome,
	MakeFood,
	Hobby,
	PutOutFire,
	Shower,
	GoToBank,
	DepositMoney,
	AtBank,
	Snack,
	Dead,
	Win
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

	//update status functions
	void Reset();
	void SetLocation(Location location);
	void AddMoneyToBank();
	void SetBreak(bool onBreak);
	void GoesToWork();
	void Tick(int ticks);
	void AddFatigue(int fatigue);
	void AddFood(int food);
	void AddHappiness(int happiness);
	void AddMoney(int money);
	void AddWashroom(int washroom);
	void AddClean(int clean);
	void AddLife(int life);
	void ResetWashroom();
	void ResetHealth();
	void ResetClean();
	void StartFire();
	void StopFire();
	void Sleep(int ticks);
	void TimeSpeed(float multiplier);
	void AddToPayCheck(int change);
	void Pay();
	
	#pragma region GetFunctions
	Location GetLocation() const;
	int GetHour() { return mHour; }
	int GetClean() { return mClean; }
	int GetLife() { return mLife; }
	int GetFireTime() { return mFireTimer; }
	int GetBreak() { return mBreakTime; }

	bool HouseOnFire() { return mBurning; }
	bool OnBreak() { return mOnBreak; }
	bool BeenToWork() { return mBeenToWork; }
	#pragma endregion

private:
	void ForwardTime(int ticks);
	int GetTicksTillMorning();
	void ResetDailyValues();
	void SleepTick(int ticks);

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
	int mBreakTime;
	int mPayCheck;

	float mTick;
	float mSpeedMultiplier;


	bool mBurning;
	bool mOnBreak;
	bool mBeenToWork;
	bool mDailyCheck;
};

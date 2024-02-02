#include "Sim.h"

#include <ImGui/Inc/ImGui.h>
#include"SimStates.h"

void Sim::Initialize()
{
	mLocation = Location::Home;
	int mMoney=0;
	int mHappiness=100;
	int mFood=100;
	int mWashroom=0;
	int mClean=100;
	int mHealth=100;
	int mFatigue=0;
	float tick=0;

	mStateMachine.Initialize(this);
	mStateMachine.AddState<GoHomeAndSleepUntilRestedState>();
	mStateMachine.AddState<GoMineAndDigForNugget>();
	mStateMachine.AddState<QuenchThirst>();
	mStateMachine.AddState<DepositGold>();
	ChangeState(SimState::GoHomeAndSleepTillRested);
}

void Sim::Terminate()
{
	mStateMachine.Terminate();
}

void Sim::Update(float deltaTime)
{
	tick += deltaTime;
	if (tick>=1)
	{
		tick = 0;
		mStateMachine.Update(deltaTime);
	}
}

void Sim::ChangeState(SimState newState)
{
	mStateMachine.ChangeState((int)newState);
}

void Sim::DebugUI()
{
	mStateMachine.DebugUI();
	ImGui::Text("Status: Bank[%d] Gold[%d] Thirst[%d], Fatigue[%d]", mGoldInBank, mGoldCarried, mThirst, mFatigue);
}

Location Sim::GetLocation() const
{
	return mLocation;
}

bool Sim::IsThirsty() const
{
	return mThirst >= 5;
}

bool Sim::IsPocketFull() const
{
	return mGoldCarried >= 10;
}

bool Sim::IsWealthy() const
{
	return mGoldInBank >= 100;
}

bool Sim::IsRested() const
{
	return mFatigue == 0;
}

void Sim::SetLocation(Location location)
{
	mLocation = location;
}

void Sim::IncreaseFatigue()
{
	++mFatigue;
	++mThirst;
}
void Sim::AddGoldCarried(int amount)
{
	mGoldCarried += amount;
}

void Sim::AddGoldToBank()
{
	mGoldInBank += mGoldCarried;
	mGoldCarried = 0;
}

void Sim::Life()
{
	AddFood(-1);
	AddWashroom(2);
	AddClean(-1);
}

void Sim::AddFatigue(int fatigue)
{
	mFatigue += fatigue;
}

void Sim::AddFood(int food)
{
	mFood += food;
	if (food > 100)
	{
		mHappiness -= food - 100;
		food = 100;
	}
}

void Sim::AddHappiness(int happiness)
{
	mHappiness += happiness;
}

void Sim::AddMoney(int money)
{
	mMoney += money;
}

void Sim::AddWashroom(int washroom)
{
	mWashroom += washroom;
}

void Sim::AddClean(int clean)
{
	mClean += clean;
}

void Sim::ResetWashroom()
{
	mWashroom = 0;
}

void Sim::ResetHealth()
{
	mHealth = 100;
}


#include "Miner.h"

#include <ImGui/Inc/ImGui.h>
#include"MinerStates.h"

void Miner::Initialize()
{
	mLocation = Location::Home;
	mGoldCarried = 0;
	mGoldInBank = 0;
	mThirst = 0;
	mFatigue = 0;

	mStateMachine.Initialize(this);
	mStateMachine.AddState<GoHomeAndSleepUntilRestedState>();
	mStateMachine.AddState<GoMineAndDigForNugget>();
	mStateMachine.AddState<QuenchThirst>();
	mStateMachine.AddState<DepositGold>();
	ChangeState(MinerState::GoHomeAndSleepTillRested);
}

void Miner::Terminate()
{
	mStateMachine.Terminate();
}

void Miner::Update(float deltaTime)
{
	mStateMachine.Update(deltaTime);
}

void Miner::ChangeState(MinerState newState)
{
	mStateMachine.ChangeState((int)newState);
}

void Miner::DebugUI()
{
	mStateMachine.DebugUI();
	ImGui::Text("Status: Bank[%d] Gold[%d] Thirst[%d], Fatigue[%d]", mGoldInBank, mGoldCarried, mThirst, mFatigue);
}

Location Miner::GetLocation() const
{
	return mLocation;
}

bool Miner::IsThirsty() const
{
	return mThirst>=5;
}

bool Miner::IsPocketFull() const
{
	return mGoldCarried >= 10;
}

bool Miner::IsWealthy() const
{
	return mGoldInBank >=100;
}

bool Miner::IsRested() const
{
	return mFatigue == 0;
}

void Miner::SetLocation(Location location)
{
	mLocation = location;
}

void Miner::IncreaseFatigue()
{
	++mFatigue;
	++mThirst;
}

void Miner::AddGoldCarried(int amount)
{
	mGoldCarried += amount;
}

void Miner::AddGoldToBank()
{
	mGoldInBank += mGoldCarried;
	mGoldCarried = 0;
}

void Miner::ResetFatigue()
{
	mFatigue = 0;
}

void Miner::ResetThirst()
{
	mThirst = 0;
}

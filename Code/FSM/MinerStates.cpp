#include "MinerStates.h"
#include <ImGui/Inc/ImGui.h>

#pragma region GoHomeAndSleepUntilRestedState
void GoHomeAndSleepUntilRestedState::Enter(Miner& agent)
{
	agent.SetLocation(Location::Home);
}

void GoHomeAndSleepUntilRestedState::Update(Miner& agent, float deltaTime)
{
	agent.ResetFatigue();
	if (agent.IsRested())
	{
		if (!agent.IsWealthy())
		{
			agent.ChangeState(MinerState::GoMineAndDigForNugget);
		}
		else
		{
			//We Are Done
		}
	}
}

void GoHomeAndSleepUntilRestedState::Exit(Miner& agent)
{
}

void GoHomeAndSleepUntilRestedState::DebugUI(Miner& agent)
{
	ImGui::Text("GoHomeAndSleepUntilRestedState: Miner is resting");
}
#pragma endregion

#pragma region GoMineAndDigForNugget
void GoMineAndDigForNugget::Enter(Miner& agent)
{
	agent.SetLocation(Location::Mine);
}

void GoMineAndDigForNugget::Update(Miner& agent, float deltaTime)
{
	agent.IncreaseFatigue();
	agent.AddGoldCarried(5);
	if (agent.IsPocketFull())
	{
		agent.ChangeState(MinerState::DepositGold);
	}
	if (agent.IsThirsty())
	{
		agent.ChangeState(MinerState::QuenchThirst);
	}
	
}

void GoMineAndDigForNugget::Exit(Miner& agent)
{
}

void GoMineAndDigForNugget::DebugUI(Miner& agent)
{
	ImGui::Text("MineAndDigForNugget: Miner is Digging for gold");
}
#pragma endregion

#pragma region QuenchThirst
void QuenchThirst::Enter(Miner& agent)
{
	agent.SetLocation(Location::Saloon);
}

void QuenchThirst::Update(Miner& agent, float deltaTime)
{
	agent.ResetThirst();
	if(!agent.IsThirsty())
	{
		agent.ChangeState(MinerState::GoMineAndDigForNugget);
	}
}

void QuenchThirst::Exit(Miner& agent)
{
}

void QuenchThirst::DebugUI(Miner& agent)
{
	ImGui::Text("QuenchThirst: Miner is drinking");
}
#pragma endregion

#pragma region DepositGold
void DepositGold::Enter(Miner& agent)
{
	agent.SetLocation(Location::Bank);
}

void DepositGold::Update(Miner& agent, float deltaTime)
{
	agent.AddGoldToBank();
	if (agent.IsWealthy())
	{
		agent.ChangeState(MinerState::GoHomeAndSleepTillRested);
	}
	else
	{
		agent.ChangeState(MinerState::GoMineAndDigForNugget);
	}
}

void DepositGold::Exit(Miner& agent)
{
}

void DepositGold::DebugUI(Miner& agent)
{
	ImGui::Text("DepositGold: Miner is deposition gold");
}
#pragma endregion

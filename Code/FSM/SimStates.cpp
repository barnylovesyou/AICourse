#include "SimStates.h"
#include <ImGui/Inc/ImGui.h>

#pragma region GoHomeAndSleepUntilRestedState
void GoHomeAndSleepUntilRestedState::Enter(Sim& agent)
{
	agent.SetLocation(Location::Home);
}

void GoHomeAndSleepUntilRestedState::Update(Sim& agent, float deltaTime)
{
	agent.ResetFatigue();
	if (agent.IsRested())
	{
		if (!agent.IsWealthy())
		{
			agent.ChangeState(SimState::GoMineAndDigForNugget);
		}
		else
		{
			//We Are Done
		}
	}
}

void GoHomeAndSleepUntilRestedState::Exit(Sim& agent)
{
}

void GoHomeAndSleepUntilRestedState::DebugUI(Sim& agent)
{
	ImGui::Text("GoHomeAndSleepUntilRestedState: Sim is resting");
}
#pragma endregion

#pragma region GoMineAndDigForNugget
void GoMineAndDigForNugget::Enter(Sim& agent)
{
	agent.SetLocation(Location::Mine);
}

void GoMineAndDigForNugget::Update(Sim& agent, float deltaTime)
{
	agent.IncreaseFatigue();
	agent.AddGoldCarried(5);
	if (agent.IsPocketFull())
	{
		agent.ChangeState(SimState::DepositGold);
	}
	if (agent.IsThirsty())
	{
		agent.ChangeState(SimState::QuenchThirst);
	}

}

void GoMineAndDigForNugget::Exit(Sim& agent)
{
}

void GoMineAndDigForNugget::DebugUI(Sim& agent)
{
	ImGui::Text("MineAndDigForNugget: Sim is Digging for gold");
}
#pragma endregion

#pragma region QuenchThirst
void QuenchThirst::Enter(Sim& agent)
{
	agent.SetLocation(Location::Saloon);
}

void QuenchThirst::Update(Sim& agent, float deltaTime)
{
	agent.ResetThirst();
	if (!agent.IsThirsty())
	{
		agent.ChangeState(SimState::GoMineAndDigForNugget);
	}
}

void QuenchThirst::Exit(Sim& agent)
{
}

void QuenchThirst::DebugUI(Sim& agent)
{
	ImGui::Text("QuenchThirst: Sim is drinking");
}
#pragma endregion

#pragma region DepositGold
void DepositGold::Enter(Sim& agent)
{
	agent.SetLocation(Location::Bank);
}

void DepositGold::Update(Sim& agent, float deltaTime)
{
	agent.AddGoldToBank();
	if (agent.IsWealthy())
	{
		agent.ChangeState(SimState::GoHomeAndSleepTillRested);
	}
	else
	{
		agent.ChangeState(SimState::GoMineAndDigForNugget);
	}
}

void DepositGold::Exit(Sim& agent)
{
}

void DepositGold::DebugUI(Sim& agent)
{
	ImGui::Text("DepositGold: Sim is deposition gold");
}
#pragma endregion

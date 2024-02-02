#include "SimStates.h"
#include <ImGui/Inc/ImGui.h>


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

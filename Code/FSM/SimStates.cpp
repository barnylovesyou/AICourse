#include "SimStates.h"
#include "ImGuiAdditions.h"

#pragma region GoToWork
void GoToWork::Enter(Sim& agent)
{
	agent.SetLocation(Location::Travelling);
	mTravelTime = 6;
}

void GoToWork::Update(Sim& agent, float deltaTime)
{
	if (mTravelTime <= 0)
	{
		agent.ChangeState(SimState::Work);
	}
	mTravelTime--;
}

void GoToWork::Exit(Sim& agent)
{
}

void GoToWork::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Travelling To Work");
	ImGui::SameLine();
	MyGui::ProgressBar(6-mTravelTime,6, ImVec2(45.0f, 15.0f), MyGui::Green, MyGui::Grey, MyGui::Green);
}
#pragma endregion

#pragma region Work
void Work::Enter(Sim& agent)
{
	agent.SetLocation(Location::Job);
	agent.GoesToWork();
	agent.SetBreak(false);
}

void Work::Update(Sim& agent, float deltaTime)
{
	if (agent.GetHour()>=17)
	{
		agent.ChangeState(SimState::GoToHome);
	}
}

void Work::Exit(Sim& agent)
{
}

void Work::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Working");
	ImGui::SameLine();
	MyGui::ProgressBar(17-agent.GetHour(), 17 , ImVec2(45.0f, 15.0f), MyGui::SlateBlue, MyGui::Black, MyGui::SlateBlue);
	if (ImGui::Button("Go On Break"))
	{
		agent.ChangeState(SimState::TakeBreak);
	}
	ImGui::SameLine();
	if (ImGui::Button("Go To Washroom"))
	{
		agent.ChangeState(SimState::GoToWashroom);
	}
	if (ImGui::Button("Go Home"))
	{
		if (agent.GetHour() < 17)
		{
			agent.AddToPayCheck(-10 * agent.GetHour());
		}
		if (agent.GetBreak() > 12)
		{
			agent.AddToPayCheck(-3 * (agent.GetBreak() - 12));
		}
		agent.Pay();
		agent.ChangeState(SimState::GoToHome);
	}
}
#pragma endregion

#pragma region TakeBreak
void TakeBreak::Enter(Sim& agent)
{
	agent.SetBreak(true);
}

void TakeBreak::Update(Sim& agent, float deltaTime)
{

}
void TakeBreak::Exit(Sim& agent)
{
}

void TakeBreak::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Working");
	ImGui::SameLine();
	MyGui::ProgressBar(17 - agent.GetHour(), 17, ImVec2(45.0f, 15.0f), MyGui::SlateBlue, MyGui::Black, MyGui::SlateBlue);
	if (agent.GetBreak() > 12)
	{
		ImGui::SameLine();
		ImGui::Text("CAREFUL YOU ARE OVER YOUR BREAK TIME");
	}
	else
	{
		ImGui::SameLine();
		ImGui::Text("Break Taken");
		ImGui::SameLine();
		MyGui::ProgressBar(agent.GetBreak(), 12, ImVec2(45.0f, 15.0f), MyGui::Black, MyGui::Blue, MyGui::Black);
	}

	if (ImGui::Button("Go Back To Work"))
	{
		agent.ChangeState(SimState::Work);
	}
	if (ImGui::Button("Go To Washroom"))
	{
		agent.ChangeState(SimState::GoToWashroom);
	}
	if (ImGui::Button("Eat Snack"))
	{
		agent.ChangeState(SimState::Snack);
	}
}
#pragma endregion

#pragma region GoToWashroom
void GoToWashroom::Enter(Sim& agent)
{
	mWashroomTime = 2;
}

void GoToWashroom::Update(Sim& agent, float deltaTime)
{
	if (mWashroomTime <= 0)
	{
		agent.ResetWashroom();
		if (agent.GetLocation() == Location::Job)
		{
			if (agent.OnBreak())
			{
				agent.ChangeState(SimState::TakeBreak);
			}
			else
			{
				agent.ChangeState(SimState::Work);
			}
		}
		else if (agent.GetLocation() == Location::Home)
		{
			agent.ChangeState(SimState::AtHome);
		}
	}
	mWashroomTime--;
}

void GoToWashroom::Exit(Sim& agent)
{
}

void GoToWashroom::DebugUI(Sim& agent)
{
	if (agent.GetLocation() == Location::Job)
	{
		ImGui::SameLine();
		ImGui::Text("Working");
		ImGui::SameLine();
		MyGui::ProgressBar(17 - agent.GetHour(), 17, ImVec2(45.0f, 15.0f), MyGui::SlateBlue, MyGui::Black, MyGui::SlateBlue);
	}
	if (agent.OnBreak())
	{
		if (agent.GetBreak() > 12)
		{
			ImGui::SameLine();
			ImGui::Text("CAREFUL YOU ARE OVER YOUR BREAK TIME");
		}
		else
		{
			ImGui::SameLine();
			ImGui::Text("Break Taken");
			ImGui::SameLine();
			MyGui::ProgressBar(agent.GetBreak(), 12, ImVec2(45.0f, 15.0f), MyGui::Black, MyGui::Blue, MyGui::Black);
		}
	}
	ImGui::SameLine();
	ImGui::Text("Using Washroom");
	ImGui::SameLine();
	MyGui::ProgressBar(2-mWashroomTime, 2, ImVec2(45.0f, 15.0f), MyGui::Chocolate, MyGui::Olive, MyGui::Chocolate);
}
#pragma endregion

#pragma region GoToHome
void GoToHome::Enter(Sim& agent)
{
	agent.SetLocation(Location::Travelling);
	mTravelTime = 6;
}

void GoToHome::Update(Sim& agent, float deltaTime)
{
	if(mTravelTime<=0)
	{
		agent.ChangeState(SimState::AtHome);
	}
	mTravelTime--;
}

void GoToHome::Exit(Sim& agent)
{
}

void GoToHome::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Travelling To Home");
	ImGui::SameLine();
	MyGui::ProgressBar(6 - mTravelTime, 6, ImVec2(45.0f, 15.0f), MyGui::Green, MyGui::Grey, MyGui::Green);
}
#pragma endregion

#pragma region AtHome
void AtHome::Enter(Sim& agent)
{
	agent.SetLocation(Location::Home);
}

void AtHome::Update(Sim& agent, float deltaTime)
{
}

void AtHome::Exit(Sim& agent)
{
}

void AtHome::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Sitting At Home");
	if (ImGui::Button("Do Hobby"))
	{
		agent.ChangeState(SimState::Hobby);
	}
	ImGui::SameLine();
	if (ImGui::Button("Go To Washroom"))
	{
		agent.ChangeState(SimState::GoToWashroom);
	}
	ImGui::SameLine();
	if (ImGui::Button("Make Food"))
	{
		agent.ChangeState(SimState::MakeFood);
	}
	ImGui::SameLine();
	if (ImGui::Button("Shower"))
	{
		agent.ChangeState(SimState::Shower);
	}
	ImGui::SameLine();
	if (ImGui::Button("TakeNap"))
	{
		agent.ChangeState(SimState::Shower);
	}
	ImGui::SameLine();
	if (ImGui::Button("Sleep"))
	{
		agent.ChangeState(SimState::Shower);
	}

	if (!agent.BeenToWork()&&(agent.GetHour()>=8||agent.GetHour()<=16))
	{
		if (ImGui::Button("Go To Work"))
		{
			agent.ChangeState(SimState::GoToWork);
		}
		ImGui::SameLine();
	}
	if (ImGui::Button("Go To Bank"))
	{
		agent.ChangeState(SimState::GoToBank);
	}
}
#pragma endregion

#pragma region MakeFood
void MakeFood::Enter(Sim& agent)
{
	mCookTime = 9;
}

void MakeFood::Update(Sim& agent, float deltaTime)
{
	if (mCookTime <= 0&&!agent.HouseOnFire())
	{
		agent.AddFood(126);
		agent.ChangeState(SimState::AtHome);
	}
	if (agent.HouseOnFire())
	{
		agent.ChangeState(SimState::AtHome);
	}
	if (X::Random(1, 27)==1)
	{
		agent.StartFire();
	}
	mCookTime--;
}

void MakeFood::Exit(Sim& agent)
{
}

void MakeFood::DebugUI(Sim& agent)
{
	if (!agent.HouseOnFire())
	{
		ImGui::SameLine();
		ImGui::Text("Making Food");
		ImGui::SameLine();
		MyGui::ProgressBar(9 - mCookTime, 9, ImVec2(45.0f, 15.0f), MyGui::Tomato, MyGui::Lime, MyGui::Tomato);
	}
}
#pragma endregion

#pragma region Hobby
void Hobby::Enter(Sim& agent)
{
}

void Hobby::Update(Sim& agent, float deltaTime)
{
}

void Hobby::Exit(Sim& agent)
{
}

void Hobby::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Hobbying");
	if (ImGui::Button("Go To Washroom"))
	{
		agent.ChangeState(SimState::GoToWashroom);
	}
	ImGui::SameLine();
	if (ImGui::Button("Make Food"))
	{
		agent.ChangeState(SimState::MakeFood);
	}
	ImGui::SameLine();
	if (ImGui::Button("Shower"))
	{
		agent.ChangeState(SimState::Shower);
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		agent.ChangeState(SimState::AtHome);
	}
}
#pragma endregion

#pragma region PutOutFire
void PutOutFire::Enter(Sim& agent)
{
	mFireStart = agent.GetFireTime() + 2;
	mFireTime = mFireStart;
}

void PutOutFire::Update(Sim& agent, float deltaTime)
{
	if (mFireTime <= 0)
	{
		agent.ChangeState(SimState::AtHome);
	}
	mFireTime--;
}

void PutOutFire::Exit(Sim& agent)
{
}

void PutOutFire::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Putting Out Fire");
	ImGui::SameLine();
	MyGui::ProgressBar(mFireStart - mFireTime, mFireStart, ImVec2(45.0f, 15.0f), MyGui::LightGrey, MyGui::Red, MyGui::LightGrey);
}
#pragma endregion

#pragma region Shower
void Shower::Enter(Sim& agent)
{
	mShowerStart = 3 + agent.GetClean() / 40;
	mShowerTime = mShowerStart;
}

void Shower::Update(Sim& agent, float deltaTime)
{
	if (mShowerTime <= 0)
	{
		agent.ResetClean();
		agent.ChangeState(SimState::AtHome);
	}
	mShowerTime--;
}

void Shower::Exit(Sim& agent)
{
}

void Shower::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Showering");
	ImGui::SameLine();
	MyGui::ProgressBar(mShowerStart - mShowerTime, mShowerStart, ImVec2(45.0f, 15.0f), MyGui::Aqua, MyGui::Chocolate, MyGui::Aqua);
}
#pragma endregion

#pragma region GoToBank
void GoToBank::Enter(Sim& agent)
{
	agent.SetLocation(Location::Travelling);
	mTravelTime = 6;
}

void GoToBank::Update(Sim& agent, float deltaTime)
{
	if (mTravelTime <= 0)
	{
		agent.ChangeState(SimState::AtBank);
	}
	mTravelTime--;
}

void GoToBank::Exit(Sim& agent)
{
}

void GoToBank::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Travelling To Bank");
	ImGui::SameLine();
	MyGui::ProgressBar(6 - mTravelTime, 6, ImVec2(45.0f, 15.0f), MyGui::Green, MyGui::Grey, MyGui::Green);
}
#pragma endregion

#pragma region DepositMoney
void DepositMoney::Enter(Sim& agent)
{
	mDepositTime = X::Random(1,3);
}

void DepositMoney::Update(Sim& agent, float deltaTime)
{
	if (mDepositTime <= 0)
	{
		agent.AddMoneyToBank();
		agent.ChangeState(SimState::AtBank);
	}
	mDepositTime--;
	
}

void DepositMoney::Exit(Sim& agent)
{
}

void DepositMoney::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Depositing Money");
}
#pragma endregion

#pragma region AtBank
void AtBank::Enter(Sim& agent)
{
}

void AtBank::Update(Sim& agent, float deltaTime)
{
}

void AtBank::Exit(Sim& agent)
{
}

void AtBank::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("You are sitting in the bank");
	if (ImGui::Button("Go To Home"))
	{
		agent.ChangeState(SimState::GoToHome);
	}
}
#pragma endregion

#pragma region Snack
void Snack::Enter(Sim& agent)
{
	mSnackTime = 3;
}

void Snack::Update(Sim& agent, float deltaTime)
{
	if (mSnackTime <= 0)
	{
		agent.AddFood(36);
		agent.ChangeState(SimState::TakeBreak);
	}
	mSnackTime--;
}

void Snack::Exit(Sim& agent)
{
}

void Snack::DebugUI(Sim& agent)
{
	ImGui::SameLine();
	ImGui::Text("Working");
	ImGui::SameLine();
	MyGui::ProgressBar(17 - agent.GetHour(), 17, ImVec2(45.0f, 15.0f), MyGui::SlateBlue, MyGui::Black, MyGui::SlateBlue);

	if (agent.GetBreak() > 12)
	{
		ImGui::SameLine();
		ImGui::Text("CAREFUL YOU ARE OVER YOUR BREAK TIME");
	}
	else
	{
		ImGui::SameLine();
		ImGui::Text("Break Taken");
		ImGui::SameLine();
		MyGui::ProgressBar(agent.GetBreak(), 12, ImVec2(45.0f, 15.0f), MyGui::Black, MyGui::Blue, MyGui::Black);
	}
	ImGui::SameLine();
	ImGui::Text("Snacking");
	ImGui::SameLine();
	MyGui::ProgressBar(3-mSnackTime, 3, ImVec2(45.0f, 15.0f), MyGui::Salmon, MyGui::Maroon, MyGui::Salmon);
}
#pragma endregion

#pragma region Dead
void Dead::Enter(Sim& agent)
{
}

void Dead::Update(Sim& agent, float deltaTime)
{
}

void Dead::Exit(Sim& agent)
{
}

void Dead::DebugUI(Sim& agent)
{
	if (agent.GetLife() <= 0)
	{
		ImGui::Text("You Have Died!");
	}
	else
	{
		ImGui::Text("Your House Burned Down!");
	}
	if (ImGui::Button("Retry"))
	{
		agent.Reset();
	}
}
#pragma endregion

#pragma region Win
void Win::Enter(Sim& agent)
{
}

void Win::Update(Sim& agent, float deltaTime)
{
}

void Win::Exit(Sim& agent)
{
}

void Win::DebugUI(Sim& agent)
{
	ImGui::Text("You Have Won!");
	if (ImGui::Button("Replay"))
	{
		agent.Reset();
	}
}
#pragma endregion
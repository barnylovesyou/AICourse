#include "Sim.h"
#include"SimStates.h"
#include "ImGuiAdditions.h"

namespace
{
	int maxHappiness = 100;
	int maxFood = 100;
	int maxWashroom = 100;	
	int maxClean = 140;
	int maxLife = 100;
	int maxFatigue = 192;
	int maxMoneyInBank = 2000;
	int maxFireTimer = 10;
	int maxBreakTime = 12;
	int maxPayCheck = 100;
	int goodSleepTime = 72;
	int fullSleepTime = 96;
	int minFatigueRestore = 8;
	int fullDeposit = 400;
}
void Sim::Initialize()
{
	mLocation = Location::Home;
	mMoney=0;
	mHappiness= maxHappiness;
	mFood= maxFood;
	mWashroom= 0;
	mClean= maxClean;
	mLife= maxLife;
	mFatigue= 0;
	mMoneyInBank = 0;
	mHour= 7;
	mMinutes= 0;
	mFireTimer = 0;
	mBreakTime = maxBreakTime;
	mPayCheck = maxPayCheck;

	mTick=0;
	mSpeedMultiplier = 1;

	mBurning = false;
	mOnBreak = false;
	mBeenToWork = false;
	mDailyCheck = true;

	mStateMachine.Initialize(this);
	mStateMachine.AddState<GoToWork>();
	mStateMachine.AddState<Work>();
	mStateMachine.AddState<TakeBreak>();
	mStateMachine.AddState<GoToWashroom>();
	mStateMachine.AddState<GoToHome>();
	mStateMachine.AddState<AtHome>();
	mStateMachine.AddState<MakeFood>();
	mStateMachine.AddState<Hobby>();
	mStateMachine.AddState<PutOutFire>();
	mStateMachine.AddState<Shower>();
	mStateMachine.AddState<GoToBank>();
	mStateMachine.AddState<DepositMoney>();
	mStateMachine.AddState<AtBank>();
	mStateMachine.AddState<Snack>();
	mStateMachine.AddState<Dead>();
	mStateMachine.AddState<Win>();
	ChangeState(SimState::AtHome);
}

void Sim::Terminate()
{
	mStateMachine.Terminate();
}

void Sim::Update(float deltaTime)
{
	mTick += deltaTime * mSpeedMultiplier;
	if (mTick>=2)
	{
		mTick = 0;
		Tick(1);
		mStateMachine.Update(deltaTime);
	}
}

void Sim::ChangeState(SimState newState)
{
	mStateMachine.ChangeState((int)newState);
}

void Sim::DebugUI()
{
	if (mLife >= 0&&mMoneyInBank<maxMoneyInBank)
	{
		ImGui::Text("Life");
		ImGui::SameLine();
		MyGui::ProgressBar(mLife, maxLife, ImVec2(45.0f, 15.0f), MyGui::Green, MyGui::Red, MyGui::Green);
		ImGui::SameLine();
		ImGui::Text("Happiness");
		ImGui::SameLine();
		MyGui::ProgressBar(mHappiness,maxHappiness, ImVec2(45.0f, 15.0f), MyGui::Gold, MyGui::Red, MyGui::Gold);
		ImGui::SameLine();
		ImGui::Text("Food");
		ImGui::SameLine();
		MyGui::ProgressBar(mFood, maxFood, ImVec2(45.0f, 15.0f), MyGui::Salmon, MyGui::Maroon, MyGui::Salmon);
		ImGui::SameLine();
		ImGui::Text("Washroom");
		ImGui::SameLine();
		MyGui::ProgressBar(mWashroom, maxWashroom, ImVec2(45.0f, 15.0f), MyGui::Chocolate, MyGui::Olive, MyGui::Chocolate);
		ImGui::SameLine();
		ImGui::Text("Clean");
		ImGui::SameLine();
		MyGui::ProgressBar(mClean, maxClean, ImVec2(45.0f, 15.0f), MyGui::Aqua, MyGui::DarkBrown, MyGui::Aqua);
		ImGui::SameLine();
		ImGui::Text("Fatigue");
		ImGui::SameLine();
		MyGui::ProgressBar(mFatigue, maxFatigue, ImVec2(45.0f, 15.0f), MyGui::LightGrey, MyGui::Black, MyGui::LightGrey);
		ImGui::SameLine();
		ImGui::Text("Cash $%d", mMoney);
		ImGui::SameLine();
		ImGui::Text("Bank Account");
		ImGui::SameLine();
		MyGui::ProgressBar(mMoneyInBank, maxMoneyInBank, ImVec2(45.0f, 15.0f), MyGui::Gold, MyGui::Green, MyGui::Gold);
		ImGui::Text("");
		if (mBurning)
		{
			ImGui::SameLine();
			ImGui::Text("House Burning");
			ImGui::SameLine();
			MyGui::ProgressBar(mFireTimer, maxFireTimer, ImVec2(45.0f, 15.0f), MyGui::Red, MyGui::Brown, MyGui::Red);
		}
		mStateMachine.DebugUI();
		if (mBurning && (mLocation == Location::Home)&&(mStateMachine.GetCurrentStateAsEnumValue()!=(int)SimState::PutOutFire))
		{
			if (ImGui::Button("Put Out Fire"))
			{
				ChangeState(SimState::PutOutFire);
			}
		}	
		if (ImGui::Button("Stop"))
		{
			mSpeedMultiplier = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Normal Speed"))
		{
			mSpeedMultiplier = 1;
		}
		ImGui::SameLine();
		if (ImGui::Button("Fast Forward"))
		{
			mSpeedMultiplier = 2;
		}
	}
	else
	{
		mStateMachine.DebugUI();
	}

}

Location Sim::GetLocation() const
{
	return mLocation;
}

void Sim::Reset()
{
	ChangeState(SimState::AtHome);
	mLocation = Location::Home;
	mMoney = 0;
	mHappiness = maxHappiness;
	mFood = maxFood;
	mWashroom = 0;
	mClean = maxClean;
	mLife = maxLife;
	mFatigue = 0;
	mMoneyInBank = 0;
	mHour = 7;
	mMinutes = 0;
	mFireTimer = 0;
	mBreakTime = maxBreakTime;
	mPayCheck = maxPayCheck;

	mTick = 0;
	mSpeedMultiplier = 1;

	mBurning = false;
	mOnBreak = false;
	mBeenToWork = false;
	mDailyCheck = true;
}

void Sim::SetLocation(Location location)
{
	mLocation = location;
}

void Sim::AddMoneyToBank()
{
	mMoneyInBank += mMoney;
	if (mMoneyInBank >= maxMoneyInBank)
	{
		ChangeState(SimState::Win);
	}
	if (mMoney >= fullDeposit)
	{
		AddHappiness(maxHappiness/5);
	}
	else
	{
		AddHappiness((int)((float)(maxHappiness / 5)*(float)(mMoney/fullDeposit)));
	}
	mMoney = 0;
}

void Sim::Tick(int ticks)
{
	ForwardTime(1 * ticks);
	AddFood(-1*ticks);
	AddWashroom(1*ticks);
	if (mStateMachine.GetCurrentStateAsEnumValue() == (int)SimState::PutOutFire)
	{
		AddFatigue(1 * ticks);
		AddClean(-3 * ticks);
	}
	else if (mLocation == Location::Job)
	{
		if (!mOnBreak)
		{
			AddHappiness(-2 * ticks);
			AddFatigue(2 * ticks);
		}
		AddHappiness(-1 * ticks);
		AddFatigue(-1 * ticks);
		AddClean(-1 * ticks);
	}
	else
	{
		AddClean(-1 * ticks);
		AddFatigue(1 * ticks);
		if (mStateMachine.GetCurrentStateAsEnumValue() == (int)SimState::Hobby)
		{
			AddHappiness(3 * ticks);
		}
	}
	if (mOnBreak)
	{
		mBreakTime--;
	}
	if (mBurning)
	{
		if (mLocation== Location::Home)
		{
			AddLife(-2 * ticks);
		}
		mFireTimer+=ticks;
		if (mFireTimer >= maxFireTimer)
		{
			ChangeState(SimState::Dead);
		}
	}
}

void Sim::AddFatigue(int fatigue)
{
	mFatigue += fatigue;
	if (mFatigue > maxFatigue)
	{
		mFatigue = maxFatigue;
		int sleepTime = 0;
		switch (mLocation)
		{
		case Home:
			sleepTime = X::Random(48, goodSleepTime);
			break;
		case Bank:
			sleepTime = X::Random(10,18);
			break;
		case Job:
			sleepTime = X::Random(12, 36);
			break;
		case Travelling:
			sleepTime = X::Random(18,48);
			break;
		}
		Sleep(sleepTime);
	}
}

void Sim::AddFood(int food)
{
	mFood += food;
	if (mFood > maxFood)
	{
		if (mFood > 1.2 * maxFood)
		{
			AddHappiness(maxFood - mFood);
		}
		else
		{
			AddHappiness(mFood-maxFood);
		}
		mFood = maxFood;
	}
	else if (mFood < 0)
	{
		AddHappiness(mFood);
		AddLife(mFood);
		mFood = 0;
	}
}

void Sim::AddHappiness(int happiness)
{
	mHappiness += happiness;
	if (mHappiness > maxHappiness)
	{
		mHappiness = maxHappiness;
	}
	else if (mHappiness < 0)
	{
		AddLife(mHappiness);
		mHappiness = 0;
	}
}

void Sim::AddMoney(int money)
{
	mMoney += money;
}

void Sim::AddWashroom(int washroom)
{
	mWashroom += washroom;
	if (mWashroom > maxWashroom)
	{
		mWashroom = maxWashroom;
		ResetWashroom();
		AddHappiness(-(maxHappiness / 5));
		AddClean(-maxClean);
	}
}

void Sim::AddClean(int clean)
{
	mClean += clean;
	if (mClean > maxClean)
	{
		mClean = maxClean;
	}
	if (mClean < 0)
	{
		AddHappiness(mClean);
		mClean = 0;
	}
}

void Sim::AddLife(int life)
{
	mLife += life;
	if (mLife <= 0)
	{
		ChangeState(SimState::Dead);
	}
	else if (mLife > maxLife)
	{
		mLife = maxLife;
	}
}

void Sim::ResetWashroom()
{
	mWashroom = 0;
}

void Sim::ResetHealth()
{
	mLife = maxLife;
}

void Sim::ResetClean()
{
	mClean = maxClean;
}

void Sim::StartFire()
{
	mBurning = true;
}

void Sim::StopFire()
{
	mFireTimer = 0;
	mBurning = false;
}

void Sim::Sleep(int ticks)
{
	if (ticks <= 0)
	{
		ticks = GetTicksTillMorning();
	}
	if (ticks >= goodSleepTime)
	{
		AddLife(maxLife/5);
		mFatigue = 0;
	}
	else if (ticks >= fullSleepTime)
	{
		ResetHealth();
		AddHappiness(maxHappiness/5);
		mFatigue = 0;
	}
	else
	{
		int fatigueRestore = (int)((float)ticks / (float)fullSleepTime) * maxFatigue;
		fatigueRestore = fatigueRestore > minFatigueRestore ? fatigueRestore : minFatigueRestore;
		AddFatigue(-fatigueRestore);
	}
	SleepTick(ticks);
}

void Sim::TimeSpeed(float multiplier)
{
	mSpeedMultiplier = multiplier;
}

void Sim::AddToPayCheck(int change)
{
	mPayCheck += change;
	if (mPayCheck < 0)
	{
		mPayCheck = 0;
	}
}

void Sim::Pay()
{
	mMoney += mPayCheck;
}

void Sim::SetBreak(bool onBreak)
{
	mOnBreak = onBreak;
}

void Sim::GoesToWork()
{
	mBeenToWork = true;
}

void Sim::ForwardTime(int ticks)
{
	while (ticks > 0)
	{
		ticks--;
		mMinutes += 5;
		if (mMinutes >= 60)
		{
			mMinutes = 0;
			mHour += 1;
			if (mHour>=24)
			{
				mHour = 0;
				mDailyCheck = false;
			}
		}
	}
	if (!mDailyCheck)
	{
		ResetDailyValues();
	}
}

int Sim::GetTicksTillMorning()
{
	int ticks = 0;
	if (mHour >= 7)
	{
		//Remaing hours in the day + 7 hours due to 7am wakeup - minutes spent in the current hour
		//12 ticks are in an hour, 1 tick per 5 minutes
		ticks += (24-mHour)*12 + 7*12 - (mMinutes/5);
	}
	else
	{
		ticks += (7 - mHour)*12 - (mMinutes/5);
	}
	return ticks;
}

void Sim::ResetDailyValues()
{
	mBreakTime = 12;
	mPayCheck = 100;
	mBeenToWork = false;
	mDailyCheck = true;	
}

void Sim::SleepTick(int ticks)
{
	ForwardTime(1 * ticks);
	AddFood(-1 * ticks);
	AddWashroom(1 * ticks);
	AddClean(-1 * ticks);
	if (mBurning)
	{
		if (mLocation == Location::Home)
		{
			AddLife(-2 * ticks);
		}
		mFireTimer+=ticks;
		if (mFireTimer >= maxFireTimer)
		{
			ChangeState(SimState::Dead);
		}
	}
}


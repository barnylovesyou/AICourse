#include "SimsGameManager.h"
#include "Player.h"
#include "ImGuiAdditions.h"

SimsGameManager* SimsGameManager::sInstance;
void SimsGameManager::StaticInitialize()
{
	if (sInstance == nullptr)
	{
		sInstance = new SimsGameManager();
		sInstance->Initialize();
	}
}

void SimsGameManager::StaticTerminate()
{
	sInstance->Terminate();
	if (sInstance != nullptr)
	{
		delete sInstance;
	}
}

void SimsGameManager::Initialize()
{
	mPlayer = new Sim();
	mPlayer->Initialize();
}

void SimsGameManager::Terminate()
{
	mPlayer->Terminate();
	delete mPlayer;
}
SimsGameManager* SimsGameManager::Get()
{
	return sInstance;
}


void SimsGameManager::Update(float deltaTime)
{
	mPlayer->Update(deltaTime);

}

void SimsGameManager::Render()
{
}

void SimsGameManager::DebugUI()
{
	mPlayer->DebugUI();
}

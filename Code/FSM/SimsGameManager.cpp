#include "SimsGameManager.h"
#include "Player.h"
#include <ImGui/Inc/ImGui.h>

SimsGameManager* SimsGameManager::sInstance;
void SimsGameManager::StaticInitialize()
{
	if (sInstance != nullptr)
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
	sInstance->mPlayer = new Sim();
}

void SimsGameManager::Terminate()
{
	delete sInstance->mPlayer;
}
SimsGameManager* SimsGameManager::Get()
{
	return sInstance;
}


void SimsGameManager::Update(float deltaTime)
{
}

void SimsGameManager::Render()
{
}

void SimsGameManager::DebugUI()
{
}

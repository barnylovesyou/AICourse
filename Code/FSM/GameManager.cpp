#include "GameManager.h"

void GameManager::StaticInitialize()
{
	if (sInstance != nullptr)
	{
		sInstance = new GameManager();
		sInstance->Initialize();
	}
}

void GameManager::StaticTerminate()
{
}

GameManager* GameManager::Get()
{
	return sInstance;
}

void GameManager::Initialize()
{
}

void GameManager::Terminate()
{
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}

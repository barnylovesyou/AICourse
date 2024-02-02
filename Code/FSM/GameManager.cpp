#include "GameManager.h"
#include "Player.h"

GameManager* GameManager::sInstance = nullptr;
void GameManager::StaticInitialize()
{
	if (sInstance == nullptr)
	{
		sInstance = new GameManager();
		sInstance->Initialize();
	}
}

void GameManager::StaticTerminate()
{
	sInstance->Terminate();
	if (sInstance != nullptr)
	{
		delete sInstance;
	}
}

void GameManager::Initialize()
{
	Player* newPlayer = new Player();
	newPlayer->Initialize();
	mEntities.push_back(newPlayer);
}

void GameManager::Terminate()
{
	for (Entity* entity : mEntities)
	{
		delete entity;
	}
	mEntities.clear();
}
GameManager* GameManager::Get()
{
	return sInstance;
}


void GameManager::Update(float deltaTime)
{
	for (int i = 0; i < mEntities.size(); ++i)
	{
		mEntities[i]->Update(deltaTime);
	}
	//for (Entity* entity : mEntities)
	//{
	//	entity->Update(deltaTime);
	//}
}

void GameManager::Render()
{
	//for (Entity* entity : mEntities)
	//{
	//	entity->Render();
	//}
}

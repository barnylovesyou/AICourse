#include "MyAIWorld.h"

#include "HumanBase.h"

MyAIWorld* MyAIWorld::sInstance;
void MyAIWorld::StaticInitialize()
{
	if (sInstance == nullptr)
	{
		sInstance = new MyAIWorld();
		sInstance->Initialize();
	}
}

void MyAIWorld::StaticTerminate()
{
	if (sInstance != nullptr)
	{
		sInstance->Terminate();
		delete sInstance;
	}
}

MyAIWorld* MyAIWorld::GetInstance()
{
	return sInstance;
}


void MyAIWorld::Update(float deltaTime)
{
	mTileMap->Update(deltaTime);
	mHumanBase->Update(deltaTime);
}

void MyAIWorld::Render()
{
	mTileMap->Render();
	mHumanBase->Render();
}

void MyAIWorld::DebugUI()
{
	if (mDebug)
	{
		mTileMap->DebugUI();
		mHumanBase->DebugUI();
	}
}

AI::EntityPtrs MyAIWorld::GetEntitiesInRange(const int distance, uint32_t typeId)
{
	return AI::EntityPtrs();
}

void MyAIWorld::Initialize()
{
	mTileMap = std::make_unique<MyTileMap>();
	mTileMap->LoadTiles("tiles.txt");
	mTileMap->LoadMap("map.txt");
	mHumanBase = std::make_unique<HumanBase>();
	mHumanBase->Initialize();
}
void MyAIWorld::Terminate()
{
	mHumanBase->Terminate();
}

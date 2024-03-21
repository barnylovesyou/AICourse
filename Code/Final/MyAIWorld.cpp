#include "MyAIWorld.h"

#include "ImGui/Inc/imgui.h"

#include "HumanBase.h"
#include "MyTileMap.h"

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
	X::Zoom(mZoom);
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
		ImGui::Begin("Debug Menu");
		ImGui::DragFloat("Zoom", &mZoom, 0.01f, 0.5f, 1.1f);
		mTileMap->DebugUI();
		mHumanBase->DebugUI();
		ImGui::End();
	}
}

AI::EntityPtrs MyAIWorld::GetEntitiesInRange(const int distance, uint32_t typeId)
{
	return AI::EntityPtrs();
}

void MyAIWorld::Initialize()
{
	auto& world = *MyAIWorld::GetInstance();
	mTileMap = std::make_unique<MyTileMap>();
	mTileMap->LoadTiles("tiles.txt");
	mTileMap->LoadMap("map.txt");
	mHumanBase = std::make_unique<HumanBase>(world);
	mHumanBase->Initialize();
}
void MyAIWorld::Terminate()
{
	mHumanBase->Terminate();
}

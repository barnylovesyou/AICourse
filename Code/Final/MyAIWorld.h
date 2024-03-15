#pragma once
#include <AI.h>
#include "AIWorld.h"
#include "MyTileMap.h"

class HumanBase;

class MyAIWorld : AI::AIWorld
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static MyAIWorld* GetInstance();
	void Update(float deltaTime);
	void Render();
	void DebugUI();

	void SetDebug(bool debug) {mDebug=debug ; }
	bool GetDebug() {return mDebug; }

	AI::EntityPtrs GetEntitiesInRange(const int distance, uint32_t typeId);
private:
	void Initialize();
	void Terminate();

	MyAIWorld() = default;
	MyAIWorld& operator=(MyAIWorld& world) = delete;
	MyAIWorld& operator=(const MyAIWorld& world) const = delete;
	MyAIWorld(const MyAIWorld& world) = delete;

	static MyAIWorld* sInstance;
	std::unique_ptr<MyTileMap> mTileMap = nullptr;
	std::unique_ptr<HumanBase> mHumanBase = nullptr;
	bool mDebug;
};
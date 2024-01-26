#pragma once
#include "Entity.h"

class GameManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static GameManager* Get();
	void Initialize();
	void Terminate();
	void Update();
	void Render();

private:
	static GameManager* sInstance;
	std::vector<Entity> mEntities;
	GameManager();
	GameManager& operator=(GameManager& gm) = delete;
	GameManager(GameManager& gm) = delete;
};
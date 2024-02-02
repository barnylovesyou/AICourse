#pragma once
#include "Entity.h"
#include <vector>

class GameManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static GameManager* Get();
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void Render();

private:
	static GameManager* sInstance;
	std::vector<Entity*> mEntities;
	GameManager() = default;
	GameManager& operator=(GameManager& gm) = delete;
	GameManager(GameManager& gm) = delete;
};
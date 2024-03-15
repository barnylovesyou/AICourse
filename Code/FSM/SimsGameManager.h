#pragma once
#include "Sim.h"
class SimsGameManager
{
public:
	static void StaticInitialize();
	static void StaticTerminate();
	static SimsGameManager* Get();
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void Render();
	void DebugUI();

private:
	static SimsGameManager* sInstance;
	Sim* mPlayer;
	SimsGameManager() = default;
	SimsGameManager& operator=(SimsGameManager& gm) = delete;
	SimsGameManager& operator=(const SimsGameManager& gm) const = delete;
	SimsGameManager(const SimsGameManager& gm) = delete;
};
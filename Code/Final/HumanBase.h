#pragma once
#include "AI.h"

using namespace AI;

class HumanBase
{
public:
	HumanBase();
	~HumanBase() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void Render();
	void DebugUI();
	void Despawn(Agent* agent);
private:
	void Spawn();
	int mLife = 100;
	int mResources = 20;
	std::vector<Agent*> deadWorkers = std::vector<Agent*>();
	std::vector<Agent*> deadFighters = std::vector<Agent*>();
	std::vector<Agent*> liveAgents = std::vector<Agent*>();
};
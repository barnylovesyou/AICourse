#pragma once
#include "AI.h"
#include "HumanWorker.h"

using namespace AI;

class HumanBase : Entity
{
public:
	HumanBase(AI::AIWorld& world);
	~HumanBase() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void Render();
	void DebugUI();
	void Despawn(Agent* agent);
private:
	void SpawnWorker();
	int mLife = 100;
	int mResources = 20;
	std::vector<std::unique_ptr<HumanWorker>> mWorkers = std::vector<std::unique_ptr<HumanWorker>>();
	std::vector<Agent*> mFighters = std::vector<Agent*>();
	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;
};
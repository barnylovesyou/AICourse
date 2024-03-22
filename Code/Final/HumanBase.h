#pragma once
#include "AI.h"
#include "HumanWorker.h"
#include "PerceptionModule.h"
#include "StrategyList.h"

using namespace AI;

struct MineralStat
{
	X::Math::Vector2 pos;
	int farming;
	int defending;
};

class HumanBase : public Entity
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

	float GetWDesirability(HumanWorker& agent, WStrats strat);
	//float GetFDesirability(Agent& agent, FStrats strat);
	AI::PerceptionModule* GetPerception() { return mPerceptionModule.get();}
	int GetMinerals() { return mMinerals; }

	void Dump(int minerals) { mMinerals += minerals; }
private:
	void SpawnWorker();
	int mMinerals = 20;
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::vector<std::unique_ptr<HumanWorker>> mWorkers = std::vector<std::unique_ptr<HumanWorker>>();
	std::vector<Agent*> mFighters = std::vector<Agent*>();
	X::TextureId mTextureId;
	std::vector<MineralStat> mMineralInfo;
};
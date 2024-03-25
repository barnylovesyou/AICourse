#pragma once
#include "AI.h"
#include "HumanWorker.h"
#include "PerceptionModule.h"
#include "StrategyList.h"
#include "ScoutMap.h"

using namespace AI;
class ScoutMap;

struct MineralStat
{
	bool CanMine() { return farming < 3;}
	Mineral* mineral;
	int farming=0;
	int defending=0;
	float distanceSqr=0;
	float GetWeight()
	{
		return distanceSqr;
	}
	bool operator<(const MineralStat& other) const {
		return distanceSqr < other.distanceSqr;
	}
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

	float GetWDesirability(HumanWorker& agent, HumanWorkerState state);
	//float GetFDesirability(Agent& agent, FStrats strat);
	AI::PerceptionModule* GetPerception() { return mPerceptionModule.get();}
	int GetMinerals() { return mMinerals; }
	std::vector<MineralStat> GetMineralInfo() { return mMineralInfo; }
	MineralStat* GetMineralStat(Mineral* mineral) { for (MineralStat& m : mMineralInfo) {
		if (m.mineral = mineral) { return &m; }
	} }

	void Dump(int minerals) { mMinerals += minerals; }

	void Scout(X::Math::Vector2 loc, float radius);
	void DoneScouting(HumanWorker& agent);
	void AssignWorker(HumanWorker* agent);
	void SpotMineral(Mineral* mineral);
private:
	void SpawnWorker();
	int WorkersNeeded(float weight);
	int mMinerals = 20;
	float workerSpawn = 0.0f;
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<ScoutMap> mScoutMap;
	std::vector<Sector*> mCurScouted;
	std::vector<std::unique_ptr<HumanWorker>> mWorkers = std::vector<std::unique_ptr<HumanWorker>>();
	std::vector<Agent*> mFighters = std::vector<Agent*>();
	X::TextureId mTextureId;
	std::vector<MineralStat> mMineralInfo;
};
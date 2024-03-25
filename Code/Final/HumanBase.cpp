#include "HumanBase.h"

#include "TypeIds.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"
#include "ImGui/Inc/imgui.h"

HumanBase::HumanBase(AI::AIWorld& world)
	:AI::Entity(world, static_cast<uint32_t>(AgentType::HumanBase))
{
}

void HumanBase::Initialize()
{
	auto world = MyAIWorld::GetInstance();
	position = X::Math::Vector2(world->GetMap()->GetTileWidth()*0.5f, world->GetMap()->GetTileHeight() * 0.5f);
	mTextureId = X::LoadTexture("refinery_05final.png");
	mScoutMap = std::make_unique<ScoutMap>(position);
	SpawnWorker();
}

void HumanBase::Terminate()
{

}

void HumanBase::Update(float deltaTime)
{
	workerSpawn += deltaTime;
	if (workerSpawn > 20)
	{
		workerSpawn = 0;
		SpawnWorker();
	}
	for (auto& worker : mWorkers)
	{
		AssignWorker(worker.get());
		worker->Update(deltaTime);
	}
}

void HumanBase::Render()
{
	X::DrawSprite(mTextureId, position);
	for (auto& worker : mWorkers)
	{
		worker->Render();
	}
}

void HumanBase::DebugUI()
{
	int i = 1;
	for(auto& m : mMineralInfo)
	{
		ImGui::Text("Mineral#%i, X: %f  Y: %f", i, m.mineral->position.x, m.mineral->position.y);
		i++;
	}
	ImGui::Text("MineralCount = %i", mMineralInfo.size());
	ImGui::Text("WorkersNeeded = %i", WorkersNeeded(0.0f));
	for (auto& a : mWorkers)
	{
		a->Debug();
	}
}

void HumanBase::Despawn(Agent* agent)
{
	int id = agent->GetUniqueId();
	uint32_t type = agent->GetTypeId();
	if (type == static_cast<uint32_t>(AgentType::HumanWorker))
	{
		for (int i = 0; i < mWorkers.size(); ++i)
		{
			if (mWorkers[i]->GetUniqueId() == id)
			{
				mWorkers.erase(mWorkers.begin() + i);
			}
		}
	}
}

float HumanBase::GetWDesirability(HumanWorker& agent, HumanWorkerState state)
{
	return 0.0f;
}

void HumanBase::Scout(X::Math::Vector2 loc, float radius)
{
	mScoutMap->Search(loc, radius);
}

void HumanBase::DoneScouting(HumanWorker& agent)
{
	int workersNeeded = WorkersNeeded(100000000.0f);
	auto sector = mScoutMap->GetHighestWeightSector(agent.position);
	if (workersNeeded < 6 && sector->PercentSearched() < 0.75f)
	{
		if (!sector->FullyExplored())
		{
			if (!sector->GetCenterExplored())
			{
				agent.SetScoutDestination(sector->GetCenter());
			}
			else
			{
				std::vector<X::Math::Vector2> unkown = sector->GetUnkown();
				int index = 0 + (std::rand() % (unkown.size()));
				agent.SetScoutDestination(unkown[index]);
			}
			sector->currentlyScouted = true;
			mScoutMap->GetSector(agent.GetScoutDestination().x, agent.GetScoutDestination().y)->currentlyScouted = false;
			agent.ChangeState(HumanWorkerState::Scout);
		}
	}
	else
	{
		agent.ChangeState(HumanWorkerState::GoHome);
	}
}

void HumanBase::AssignWorker(HumanWorker* agent)
{
	switch (static_cast<HumanWorkerState>(agent->GetState()))
	{
	case HumanWorkerState::Mine:
	{
		for (auto& mineral : mMineralInfo)
		{
			if (mineral.mineral == agent->GetMineralTarget())
			{
				if (X::Math::DistanceSqr(agent->position, agent->GetMineralTarget()->position) > mineral.distanceSqr + 625)
				{
					mineral.farming--;
					agent->ChangeState(HumanWorkerState::GoHome);
				}
				break;
			}
		}
		break;
	}
	case HumanWorkerState::GoHome:
	{
		//16384 is equal to 32*32*4*4 so approx 4 tiles down and 4 tiles to the right used to judge if the worker has returned home
		int workersNeeded = WorkersNeeded(100000000.0f);
		if (X::Math::DistanceSqr(position, agent->position) < 16384)
		{
			auto sector = mScoutMap->GetHighestWeightSector(agent->position);
			if (workersNeeded ==0 && sector->PercentSearched() < 0.75f)
			{
				if (!sector->FullyExplored())
				{
					if (!sector->GetCenterExplored())
					{
						agent->SetScoutDestination(sector->GetCenter());
					}
					else
					{
						std::vector<X::Math::Vector2> unkown = sector->GetUnkown();
						int index = 0 + (std::rand() % (unkown.size()));
						agent->SetScoutDestination(unkown[index]);
					}
					sector->currentlyScouted = true;
					agent->ChangeState(HumanWorkerState::Scout);
				}
			}
			else if(workersNeeded>0)
			{
				for (auto& mineral : mMineralInfo)
				{
					if (mineral.CanMine())
					{
						mineral.farming++;
						agent->SetMineralTarget(mineral.mineral);
						continue;
					}
				}
				agent->ChangeState(HumanWorkerState::Mine);
			}
		}
		break;
	}
	case HumanWorkerState::Scout:
	{
		int workersNeeded = WorkersNeeded(100000000.0f);
		if (workersNeeded >0)
		{
			mScoutMap->GetSector(agent->GetScoutDestination().x, agent->GetScoutDestination().y)->currentlyScouted = false;
			agent->ChangeState(HumanWorkerState::GoHome);
		}
		break;
	}
	}
}


void HumanBase::SpawnWorker()
{
	auto& world = *MyAIWorld::GetInstance();
	auto& worker  = mWorkers.emplace_back(std::make_unique<HumanWorker>(world));
	worker->Load(position);
}

void HumanBase::SpotMineral(Mineral* mineral)
{
	bool found = false;
	for (auto& m : mMineralInfo)
	{
		if (m.mineral = mineral)
		{
			found = true;
			continue;
		}
	}
	if (!found)
	{
		MineralStat newMineral = MineralStat();
		newMineral.mineral = mineral;
		newMineral.distanceSqr = X::Math::DistanceSqr(mineral->position, position);
		auto it = std::lower_bound(mMineralInfo.begin(), mMineralInfo.end(), newMineral);
		mMineralInfo.insert(it, newMineral);
	}
}

int HumanBase::WorkersNeeded(float weight)
{
	int workers = 0;
	for (auto info : mMineralInfo)
	{
		workers += 3-info.farming;
	}
	return workers;
}
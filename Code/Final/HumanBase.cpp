#include "HumanBase.h"

#include "TypeIds.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"

HumanBase::HumanBase(AI::AIWorld& world)
	:AI::Entity(world, static_cast<uint32_t>(AgentType::HumanBase))
{
}

void HumanBase::Initialize()
{
	auto world = MyAIWorld::GetInstance();
	position = X::Math::Vector2(world->GetMap()->GetTileWidth()*0.5f, world->GetMap()->GetTileHeight() * 0.5f);
	mTextureId = X::LoadTexture("refinery_05final.png");
	SpawnWorker();
}

void HumanBase::Terminate()
{

}

void HumanBase::Update(float deltaTime)
{
	for (auto& worker : mWorkers)
	{
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

float HumanBase::GetWDesirability(HumanWorker& agent, WStrats strat)
{
	switch(strat)
	{
	case WStrats::Scout:
		return 100;
		break;
	case WStrats::Run:
		return 10;
		break;
	case WStrats::Mine:
		if (mMinerals < 23)
		{
			return 1000.0f;
		}
		break;
	case WStrats::Home:
		if (X::Math::DistanceSqr(agent.position, position) > 90000 &&!agent.scouting)
		{
			return 1000.0f;
		}
		else
		{
			return 0.0f;
		}
		break;
	default:
		break;
	}
}

void HumanBase::SpawnWorker()
{
	auto& world = *MyAIWorld::GetInstance();
	auto& worker  = mWorkers.emplace_back(std::make_unique<HumanWorker>(world));
	worker->Load(position);
}

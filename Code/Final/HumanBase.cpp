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
	mPosition = X::Math::Vector2(world->GetMap()->GetTileWidth()*0.5f, world->GetMap()->GetTileHeight() * 0.5f);
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
	X::DrawSprite(mTextureId, mPosition);
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

}

void HumanBase::SpawnWorker()
{
	auto& world = *MyAIWorld::GetInstance();
	auto& worker  = mWorkers.emplace_back(std::make_unique<HumanWorker>(world));
	worker->Load(mPosition);
}

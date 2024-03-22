#include "HWWander.h"
#include "MyAIWorld.h"
#include "MyTileMap.h"

HWWander::HWWander()
{
}

void HWWander::Activate(HumanWorker& agent)
{
	mStatus = HWWander::Status::Active;
	mDestination = GetRandomDestination(agent);
	agent.destination = mDestination;
	mCount = 2;
}

HWWander::Status HWWander::Process(HumanWorker& agent)
{
	ActivateIfInactive(agent);
	if (X::Math::DistanceSqr(agent.position, mDestination) < 16.0f)
	{
		if (mCount <= 0)
		{
			mStatus = HWWander::Status::Completed;
		}
		mCount--;
		mDestination = GetRandomDestination(agent);
		agent.destination = mDestination;
	}
	return mStatus;
}

void HWWander::Terminate(HumanWorker& agent)
{
}

void HWWander::SetDestination(const X::Math::Vector2& destination)
{
	mDestination = destination;
}

X::Math::Vector2 HWWander::GetRandomDestination(HumanWorker& agent)
{
	auto world = MyAIWorld::GetInstance();
	auto map = world->GetMap();
	X::Math::Vector2 destination = agent.position;
	float x = X::RandomFloat(-100.0f, 100.0f);
	float y = X::RandomFloat(-100.0f, 100.0f);
	destination.x += x;
	destination.y += y;
	X::Math::Vector2 min = X::Math::Vector2::Zero();
	X::Math::Vector2 max = MyAIWorld::GetInstance()->GetMap()->GetMax();
	destination.x = X::Math::Clamp(destination.x, min.x, max.x);
	destination.y = X::Math::Clamp(destination.y, min.y, max.y);
	int ix = map->GetRow(destination.x);
	int iy = map->GetColumn(destination.y);
	if (map->IsBlocked(ix,iy))
	{
		return map->GetApplicableNeighborPosition(ix,iy);
	}
	else
	{
		return map->GetPixelPosition(ix, iy);
	}
}

#include "HWVisualSensor.h"
#include "MyAIWorld.h"
#include "HumanBase.h"
#include "Mineral.h"

using namespace AI;

void HWVisualSensor::Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime)
{
	bool isTarget = false;
	const float viewRangeSqr = viewRange * viewRange;
	const EntityPtrs entities = agent.world.GetEntities();
	for (const Entity* entity : entities)
	{
		//ignore self
		if (entity == &agent)
		{
			continue;
		}
		isTarget = false;
		//filter by type
		if (!targetTypes.empty())
		{
			for (AgentType a : targetTypes)
			{
				isTarget = static_cast<uint32_t>(a) != entity->GetTypeId();
				if (!isTarget)
				{
					continue;
				}
			}

			if (!isTarget)
			{
				continue;
			}
		}

		X::Math::Vector2 posToTarget = entity->position - agent.position;
		if (X::Math::MagnitudeSqr(posToTarget) > viewRangeSqr)
		{
			continue;
		}

		//line of sight
		X::Math::LineSegment lineToTarget(agent.position, entity->position);
		if (!agent.world.HasLineOfSight(lineToTarget))
		{
			continue;
		}
		if (entity->GetTypeId() == static_cast<uint32_t>(AgentType::Mineral))
		{
			MyAIWorld::GetInstance()->GetHumanBase()->SpotMineral(dynamic_cast<Mineral*>(const_cast<Entity*>(entity)));
		}
		//if()
		//auto iter = std::find_if(memory.begin(), memory.end(), 
		//	[&](const MemoryRecord& m)
		//	{
		//		return entity->GetUniqueId() == m.uniqueId;
		//	});
		//if (iter != memory.end())
		//{
		//	iter->properties["lastSeenPosition"] = entity->position;
		//	iter->lastRecordedTime = X::GetTime();
		//	if (entity->GetTypeId() == static_cast<uint32_t>(AgentType::Mineral))
		//	{
		//		const Mineral* mineral= static_cast<const Mineral*>(entity);
		//		//iter->properties["health"] = mineral->GetHealth();
		//	}
		//}
		//else
		//{
		//	auto& newRecord = memory.emplace_back();
		//	newRecord.uniqueId = entity->GetUniqueId();
		//	newRecord.properties["lastSeenPosition"] = entity->position;
		//	newRecord.properties["type"] = static_cast<int>(entity->GetTypeId());
		//	newRecord.lastRecordedTime = X::GetTime();
		//	if (entity->GetTypeId() == static_cast<uint32_t>(AgentType::Mineral))
		//	{
		//		const Mineral* mineral = static_cast<const Mineral*>(entity);
		//		//newRecord.properties["health"] = mineral->GetHealth();
		//	}
		//}
	}
}

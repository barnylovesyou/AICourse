#include "MovementSensor.h"
#include <typeinfo>

using namespace AI;

void MovementSensor::Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime)
{
	const EntityPtrs entities = agent.world.GetEntities();
	for (const Entity* entity : entities)
	{
		//ignore self
		if (entity == &agent)
		{
			continue;
		}
		//filter by type
		if (targetType != AgentType::Invalid && static_cast<uint32_t>(targetType) != entity->GetTypeId())
		{
			continue;
		}
		//Ensures entity derives from agent and then checks if the speed is fast enough to be detected
		auto entityAgent = dynamic_cast<const Agent*>(entity);
		if (entityAgent != nullptr)
		{
			if (X::Math::MagnitudeSqr(entityAgent->velocity) < (detectionSpeed * detectionSpeed))
			{
				continue;
			}
		}
		else
		{
			continue;
		}
		//line of sight
		X::Math::LineSegment lineToTarget(agent.position, entity->position);
		if (!agent.world.HasLineOfSight(lineToTarget))
		{
			X::DrawScreenLine(agent.position, entity->position, X::Colors::LightPink);
			continue;
		}

		//have I seen this before
		auto iter = std::find_if(memory.begin(), memory.end(),
			[&](const MemoryRecord& m)
			{
				return entity->GetUniqueId() == m.uniqueId;
			});
		if (iter != memory.end())
		{
			iter->properties["lastSeenPosition"] = entity->position;
			iter->lastRecordedTime = X::GetTime();
		}
		else
		{
			auto& newRecord = memory.emplace_back();
			newRecord.uniqueId = entity->GetUniqueId();
			newRecord.properties["lastSeenPosition"] = entity->position;
			newRecord.properties["type"] = static_cast<int>(entity->GetTypeId());
			newRecord.lastRecordedTime = X::GetTime();
		}
	}
}

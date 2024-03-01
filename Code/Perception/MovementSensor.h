#pragma once

#include<AI.h>

#include "TypeIds.h"
class MovementSensor : public AI::Sensor
{
public:
	virtual void Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime) override;

	AgentType targetType = AgentType::Invalid;
	float detectionSpeed = 0.0f;

};
#pragma once

#include<AI.h>

#include "TypeIds.h"
class HWVisualSensor : public AI::Sensor
{
public:
	virtual void Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltaTime) override;

	std::vector<AgentType> targetTypes;
	float viewRange = 0.0f;
};
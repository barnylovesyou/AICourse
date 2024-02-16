#include "Precompiled.h"
#include "PerceptionModule.h"

using namespace AI;

PerceptionModule::PerceptionModule(Agent& agent, ImportanceCalculator calculator)
	:mAgent(agent)
	,mComputeImportance(calculator)
{
}

void PerceptionModule::Update(float deltaTime)
{
	//update Sensors
	for (auto& sensor : mSensors)
	{
		sensor->Update(mAgent, mMemoryRecords, deltaTime);
	}
	//Remove old memory records
	mMemoryRecords.erase(
		std::remove_if(
			mMemoryRecords.begin(),
			mMemoryRecords.end(),
			[span = mMemorySpan](const auto& record)
			{
				return record.lastRecordedTime + span < X::GetTime();
			}),
		mMemoryRecords.end());

	//calculate improtance of records
	for (auto& record : mMemoryRecords)
	{
		record.importance = mComputeImportance(mAgent, record);
	}

	//sort by importance
	mMemoryRecords.sort(
		[](const auto& a, const auto& b)
		{
			return a.importance > b.importance;
		});
}

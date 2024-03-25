#pragma once
#include <AI.h>
#include "MyTileMap.h"

class HWVisualSensor;

enum class HumanWorkerState
{
	Mine,
	GoHome,
	Scout
};

class HumanWorker : public AI::Agent {
public:
	HumanWorker(AI::AIWorld& world);
	~HumanWorker() override = default;

	void Load(X::Math::Vector2 spawn);
	void Unload();

	void Update(float deltaTime);
	void Render();
	void Debug();

	void ShowDebug(bool debug);

	void ChangeState(HumanWorkerState state);
	void SetSeek(bool seek) { mSeekBehavior->SetActive(seek); }
	void SetArrive(bool arrive) { mArriveBehavior->SetActive(arrive); }
	void Carry(int minerals) { mValue = minerals; }
	void SetMineralTarget(Mineral* mineral) { mMineralTarget = mineral; }
	void SetScoutDestination(X::Math::Vector2 scout) { mScoutDestination = scout; }

	AI::SteeringModule* GetSteeringModule() const { return mSteeringModule.get();}
	AI::PerceptionModule* GetPerceptionModule() { return mPerceptionModule.get(); }
	AI::DecisionModule<HumanWorker>* GetDecisionModule() { return mDecisionModule.get(); }
	uint32_t GetState() { return mStateMachine->GetCurrentStateAsEnumValue();}
	Mineral* GetMineralTarget() { return mMineralTarget;}
	X::Math::Vector2 GetScoutDestination() { return mScoutDestination; }

	void Dump();
private:
	std::unique_ptr<AI::StateMachine<HumanWorker>> mStateMachine;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::unique_ptr < AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::DecisionModule<HumanWorker>> mDecisionModule;

	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;

	HWVisualSensor* mVisualSensor = nullptr;

	int mValue = 0.0f;
	float mVisionRadius = 130.0f;
	Mineral* mMineralTarget = nullptr;
	X::Math::Vector2 mScoutDestination;
	std::array<X::TextureId, 16> mTextureIds;

};
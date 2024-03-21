#pragma once
#include <AI.h>
#include "MyTileMap.h"

class VisualSensor;
class MovementSensor;

enum class HumanWorkerState
{
	Mine,
	Move
};

class HumanWorker : public AI::Agent {
public:
	HumanWorker(AI::AIWorld& world);
	~HumanWorker() override = default;

	void Load(X::Math::Vector2 spawn);
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void ChangeState(HumanWorkerState state);

	void SetSeek(bool seek) { mSeekBehavior->SetActive(seek); }
	void SetArrive(bool arrive) { mArriveBehavior->SetActive(arrive); }

	AI::SteeringModule* GetSteeringModule() const { return mSteeringModule.get();}
	AI::PerceptionModule* GetPerceptionModule() { return mPerceptionModule.get(); }
	AI::DecisionModule<HumanWorker>* GetDecisionModule() { return mDecisionModule.get(); }

private:
	std::unique_ptr<AI::StateMachine<HumanWorker>> mStateMachine;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::DecisionModule<HumanWorker>> mDecisionModule;

	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;

	VisualSensor* mVisualSensor = nullptr;
	VisualSensor* mVisualSensor2 = nullptr;

	MovementSensor* mMovementSensor = nullptr;
	MovementSensor* mMovementSensor2 = nullptr;

	std::array<X::TextureId, 16> mTextureIds;

};
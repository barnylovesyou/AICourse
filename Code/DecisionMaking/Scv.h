#pragma once
#include <AI.h>

class VisualSensor;
class MovementSensor;

class SCV : public AI::Agent {
public:
	SCV(AI::AIWorld& world);
	~SCV() override = default;

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void SetSeek(bool active);
	void SetFlee(bool active);
	void SetArrive(bool active);
	void SetWander(bool active);
	void SetPursuit(bool active);
	void SetSeperation(bool active);
	void SetAlignment(bool active);
	void SetCohesion(bool active);

	void SetSeekWeight(float weight);
	void SetFleeWeight(float weight);
	void SetArriveWeight(float weight);
	void SetWanderWeight(float weight);
	void SetPursuitWeight(float weight);
	void SetSeperationWeight(float weight);
	void SetAlignmentWeight(float weight);
	void SetCohesionWeight(float weight);
private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;

	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	AI::PursuitBehavior* mPursuitBehavior = nullptr;
	AI::SeperationBehavior* mSeperationBehavior = nullptr;
	AI::AlignmentBehavior* mAlignmentBehavior = nullptr;
	AI::CohesionBehavior* mCohesionBehavior = nullptr;

	VisualSensor* mVisualSensor = nullptr;
	VisualSensor* mVisualSensor2 = nullptr;

	MovementSensor* mMovementSensor = nullptr;
	MovementSensor* mMovementSensor2 = nullptr;

	std::array<X::TextureId, 16> mTextureIds;
};
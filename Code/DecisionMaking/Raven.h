#pragma once

#include <AI.h>
class VisualSensor;

class Raven : public AI::Agent 
{
public:
	Raven(AI::AIWorld& world);
	
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void SetSeek(bool active);
	void SetWander(bool active);
	void SetArrive(bool active);
	void SetTargetDestination(const X::Math::Vector2& targetDestination);

private:
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::unique_ptr<AI::DecisionModule<Raven>> mDecisionModule;

	VisualSensor* mVisualSensor = nullptr;
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;

	std::array<X::TextureId, 16> mTextureIds;
};
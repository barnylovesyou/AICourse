#pragma once
#include <AI.h>
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
private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	AI::PursuitBehavior* mPursuitBehavior = nullptr;
	AI::SeperationBehavior* mSeperationBehavior = nullptr;

	std::array<X::TextureId, 16> mTextureIds;
};
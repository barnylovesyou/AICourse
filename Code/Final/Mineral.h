#pragma once
#include <XEngine.h>
#include <AI.h>


class Mineral : public AI::Entity
{
public:
	Mineral(AI::AIWorld& world);
	~Mineral() = default;

	void Initialize(X::Math::Vector2 position);
	void Render();
	int GetValue() { return mValue; }

private:
	X::TextureId mTextureId;
	int mValue = 5;
};
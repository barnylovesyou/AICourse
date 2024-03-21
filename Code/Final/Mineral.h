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

private:
	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;
};
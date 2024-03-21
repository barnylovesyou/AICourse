#include "Mineral.h"

#include "TypeIds.h"

Mineral::Mineral(AI::AIWorld& world)
	:AI::Entity(world, static_cast<uint32_t>(AgentType::Mineral))
{
}

void Mineral::Initialize(X::Math::Vector2 position)
{
	mPosition = position;
	mTextureId = X::LoadTexture("mineralsfinal.png");
}

void Mineral::Render()
{
	X::DrawSprite(mTextureId, mPosition);
}

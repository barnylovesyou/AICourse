#include "Mineral.h"

#include "TypeIds.h"

Mineral::Mineral(AI::AIWorld& world)
	:AI::Entity(world, static_cast<uint32_t>(AgentType::Mineral))
{
}

void Mineral::Initialize(X::Math::Vector2 pos)
{
	position = pos;
	mTextureId = X::LoadTexture("mineralsfinal.png");
}

void Mineral::Render()
{
	X::DrawSprite(mTextureId, position);
}

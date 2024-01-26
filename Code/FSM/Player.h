#pragma once
#include <XEngine.h>
#include "Entity.h"

class Player : Entity
{
public:
	Player() {Initialize();};
	void Initialize();
	void Terminate();

	void Update() override;
	void Render() override;

	bool Collision(Colliders collider) override;
	void Collided(Entity collided) override;
	void Hit(int damage) override;
private:
	void Move();
	void Shoot();
	void Reload();

	X::Math::Vector2 mVelocity = (0,0);
	X::Math::Vector2 mPosition = (640, 100);
	int mAmmo = 10;
	int mMaxAmmo = 10;
	float mReloadTimer = 2;
	float mReloadTime = 2;
	int mHealth = 100;
	Colliders collider = Colliders::PlayerShip;
};
#pragma once

enum Colliders
{
	PlayerShip =   1 << 0,
	EnemyShip =    1 << 1,
	PlayerBullet = 1 << 2,
	EnemyBullet =  1 << 3,
	None =         1 << 4
};

class Entity
{
public:
	virtual void Update(float deltaTime)= 0;
	virtual void Render()= 0;
	virtual bool Collision(Colliders collider)= 0;
	virtual void Collided(Entity* collided)= 0;
	virtual void Hit(int damage)= 0;
	void ChangeCollider(Colliders newCollider)
	{

	}
};
#pragma once

enum Colliders
{
	PlayerShip =   1 << 0,
	EnemyShip =    1 << 1,
	PlayerBullet = 1 << 2,
	EnemyBullet =  1 << 3
	

};

class Entity
{
public:
	virtual void Update();
	virtual void Render();
	virtual bool Collision(Colliders collider);
	virtual void Collided(Entity collided);
	virtual void Hit(int damage);
};
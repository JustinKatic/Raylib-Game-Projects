#pragma once
#include "raylib.h"
class Projectile
{

public:
	Projectile();
	Projectile(Rectangle projectileRec);
	~Projectile();


	void MoveProjectile();
	void MoveEnemyProjectile();
	void DrawProjectile();
	Rectangle m_projectileRec;
	

private:
	float m_projectileSpeed;
	float m_playerProjectileSpeed;



};


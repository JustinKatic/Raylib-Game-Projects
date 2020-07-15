#pragma once
#include "raylib.h"
class Enemy
{
public:
	Enemy();
	Enemy(Rectangle EnemyRec);
	Rectangle m_enemyRec;
	~Enemy();
	void DrawEnemies();
	bool activeShooter = false;


	float m_enemySpeed = 0.5f;
};


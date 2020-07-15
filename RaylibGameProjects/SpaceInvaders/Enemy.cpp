#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(Rectangle enemyRec)
{
	m_enemyRec = enemyRec;
}

Enemy::~Enemy()
{

}

void Enemy::DrawEnemies()
{
	DrawRectangle(m_enemyRec.x,m_enemyRec.y,m_enemyRec.width,m_enemyRec.height, Color(RED));
}

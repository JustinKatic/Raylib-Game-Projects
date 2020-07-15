#include "Projectile.h"


Projectile::Projectile()
{

}

Projectile::Projectile(Rectangle projectileRec)
{
	m_projectileRec = projectileRec;
	m_projectileSpeed = 15;
	m_playerProjectileSpeed = 10;
}


Projectile::~Projectile()
{

}

void Projectile::MoveProjectile()
{
	m_projectileRec.y -= m_playerProjectileSpeed;
}

void Projectile::MoveEnemyProjectile()
{
	m_projectileRec.y += m_projectileSpeed;
}



void Projectile::DrawProjectile()
{
	DrawRectangle(m_projectileRec.x, m_projectileRec.y, m_projectileRec.width, m_projectileRec.height, Color(GREEN));
}

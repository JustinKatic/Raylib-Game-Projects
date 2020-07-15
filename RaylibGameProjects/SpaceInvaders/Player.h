#pragma once
#include "raylib.h";
class Player
{
public:
	Player();
	Player(Rectangle PlayerRec);
	~Player();

	void PlayerMovement();

	bool PlayerShoot();

	void DrawPlayer();

	float m_health;
	float m_damage;

	Rectangle m_PlayerRec;

	float m_speed;

	float m_shootTimer = 0;

private:
};


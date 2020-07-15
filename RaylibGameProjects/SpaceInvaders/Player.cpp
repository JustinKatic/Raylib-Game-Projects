#include "Player.h"
#include <iostream>

Player::Player()
{

}

Player::Player(Rectangle PlayerRec)
{
	m_health = 3;
	m_damage = 1;
	m_PlayerRec = PlayerRec;
	m_speed = 10;
}

Player::~Player()
{
	
}

void Player::PlayerMovement()
{
	if ( m_PlayerRec.x >= 5 && IsKeyDown(KEY_A) )
	{
		m_PlayerRec.x -= m_speed;
	}
	if (m_PlayerRec.x <= GetScreenWidth() - m_PlayerRec.width -5 && IsKeyDown(KEY_D))
	{
		m_PlayerRec.x += m_speed;
	}
}

bool Player::PlayerShoot()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		return true;
	}
	return false;
}

void Player::DrawPlayer()
{
	DrawRectangle(m_PlayerRec.x, m_PlayerRec.y, m_PlayerRec.width, m_PlayerRec.height, Color(WHITE));
	DrawRectangle(m_PlayerRec.x + m_PlayerRec.width /2, m_PlayerRec.y - 10, 10, 10, Color(WHITE));
}

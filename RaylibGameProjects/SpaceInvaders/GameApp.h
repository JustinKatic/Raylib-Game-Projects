#include <list>
#include "StopWatch.h"

class Player;
class Projectile;
class Enemy;
class Barriers;

class GameApp
{
public:

	GameApp();
	~GameApp();

	Player* player;
	Projectile* projectile[4];
	Projectile* enemyProjecile[10];
	Enemy* enemy[50];
	Barriers* barrierLeft[50];
	Barriers* barrierMiddle[50];
	Barriers* barrierRight[50];


	void Startup();
	void Shutdown();
	void Run();

	void Update();
	void Draw();

	StopWatch stopwatch;
	long currentTime = 0;
	long lastTime = 0;
	float timer = 0;
	int fps = 1;
	int frames;

	float deltaTime = 0.005f;

	float m_enemyXPos = -5;
	float m_enemyYPos = 50;

	float m_leftBarrierStartX = 50;
	float m_leftBarrierStartY = 700;

	float m_middleBarrierStartX = 350;
	float m_middleBarrierStartY = 700;

	float m_RightBarrierStartX = 650;
	float m_RightBarrierStartY = 700;

	bool m_shouldMoveLeft = false;

	float m_senemyShootTimer = 0;

	int m_activeShooters[10];
	


private:
	int m_screenWidth;
	int m_screenHeight;

};
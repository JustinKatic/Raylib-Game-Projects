#include "GameApp.h"
#include "raylib.h"
#include <iostream>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include"Barriers.h"

#include <chrono>




GameApp::GameApp()
{

}
GameApp::~GameApp()
{

}

//happens before anything else once project opens up
void GameApp::Startup()
{
	//screen size
	m_screenWidth = 900;
	m_screenHeight = 900;
	//creates raylib screen
	InitWindow(m_screenWidth, m_screenHeight, "Space Invaders");
	//sets fps to lock at 60
	SetTargetFPS(60);

	player = new Player({ 10, 830, 150, 50 });

	m_activeShooters[0] = 40;
	m_activeShooters[1] = 41;
	m_activeShooters[2] = 42;
	m_activeShooters[3] = 43;
	m_activeShooters[4] = 44;
	m_activeShooters[5] = 45;
	m_activeShooters[6] = 46;
	m_activeShooters[7] = 47;
	m_activeShooters[8] = 48;
	m_activeShooters[9] = 49;

	for (int i = 0; i < 50; i++)
	{
		m_enemyXPos += 70;
		enemy[i] = new Enemy({ m_enemyXPos, m_enemyYPos,30,30 });

		if (i == 9 || i == 19 || i == 29 || i == 39)
		{
			m_enemyYPos += 60;
			m_enemyXPos = -5;
		}
		if (i >= 40)
		{
			enemy[i]->activeShooter = true;
		}
	}

	for (int i = 0; i < 50; i++)
	{
		barrierLeft[i] = new Barriers({ m_leftBarrierStartX,m_leftBarrierStartY,15,15 });
		m_leftBarrierStartX += 20;

		if (i == 9 || i == 19 || i == 29 || i == 39)
		{
			m_leftBarrierStartX = 50;
			m_leftBarrierStartY -= 20;
		}
	}

	for (int i = 0; i < 50; i++)
	{
		barrierMiddle[i] = new Barriers({ m_middleBarrierStartX,m_middleBarrierStartY,15,15 });
		m_middleBarrierStartX += 20;

		if (i == 9 || i == 19 || i == 29 || i == 39)
		{
			m_middleBarrierStartX = 350;
			m_middleBarrierStartY -= 20;
		}
	}

	for (int i = 0; i < 50; i++)
	{
		barrierRight[i] = new Barriers({ m_RightBarrierStartX,m_RightBarrierStartY,15,15 });
		m_RightBarrierStartX += 20;

		if (i == 9 || i == 19 || i == 29 || i == 39)
		{
			m_RightBarrierStartX = 650;
			m_RightBarrierStartY -= 20;
		}
	}
}

//happens right before project finishs use for clean up
void GameApp::Shutdown()
{
	CloseWindow();
}

//Game loop
void GameApp::Run()
{
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//functionality every frame
		Update();
		//drawing every frame
		Draw();
	}
}

//use to update functionality every frame
void GameApp::Update()
{
	currentTime = stopwatch.GetCurrentTime();
	deltaTime = (currentTime - lastTime) / 1000.0f;

	timer += deltaTime;
	if (timer >= 1)
	{
		fps = frames;
		frames = 0;
		timer -= 1;
	}
	frames++;
	lastTime = currentTime;

	//increasing enemy and players shooter timer +1 every second
	player->m_shootTimer += deltaTime;
	m_senemyShootTimer += deltaTime;

	//moving player
	player->PlayerMovement();

	int ProjectileIndex = 0;
	int enemyProjectileIndex = 0;

	//player shoot add new projectile 
	if (player->PlayerShoot() && player->m_shootTimer > 0.5f)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (projectile[i] == nullptr)
			{
				ProjectileIndex = i;
				break;
			}
		}
		projectile[ProjectileIndex] = new Projectile({ player->m_PlayerRec.x + player->m_PlayerRec.width / 2, player->m_PlayerRec.y - 40, 10, 10 });
		player->m_shootTimer = 0;
	}

	//players projectile collision with barriers
	for (int i = 0; i < 4; i++)
	{
		if (projectile[i] != nullptr)
		{
			for (int j = 0; j < 50; j++)
			{
				if (projectile[i] == nullptr)
				{
					break;
				}
				if (barrierLeft[j] != nullptr && projectile[i] != nullptr && CheckCollisionRecs(projectile[i]->m_projectileRec, barrierLeft[j]->m_barrierRec))
				{
					projectile[i] = nullptr;
					barrierLeft[j] = nullptr;

				}
				if (barrierMiddle[j] != nullptr && projectile[i] != nullptr && CheckCollisionRecs(projectile[i]->m_projectileRec, barrierMiddle[j]->m_barrierRec))
				{
					projectile[i] = nullptr;
					barrierMiddle[j] = nullptr;
				}
				if (barrierRight[j] != nullptr && projectile[i] != nullptr && CheckCollisionRecs(projectile[i]->m_projectileRec, barrierRight[j]->m_barrierRec))
				{
					projectile[i] = nullptr;
					barrierRight[j] = nullptr;
				}

			}
		}
	}
	//enemey projectile collision with player and barriers
	for (int i = 0; i < 10; i++)
	{
		if (enemyProjecile[i] != nullptr)
		{
			if (player != nullptr && enemyProjecile[i] != nullptr && CheckCollisionRecs(enemyProjecile[i]->m_projectileRec, player->m_PlayerRec))
			{
				std::cout << "player hit" << std::endl;
				enemyProjecile[i] = nullptr;
			}
			for (int j = 0; j < 50; j++)
			{
				if (barrierLeft[j] != nullptr && enemyProjecile[i] != nullptr && CheckCollisionRecs(enemyProjecile[i]->m_projectileRec, barrierLeft[j]->m_barrierRec))
				{
					enemyProjecile[i] = nullptr;
					barrierLeft[j] = nullptr;
				}
				if (barrierMiddle[j] != nullptr && enemyProjecile[i] != nullptr && CheckCollisionRecs(enemyProjecile[i]->m_projectileRec, barrierMiddle[j]->m_barrierRec))
				{
					enemyProjecile[i] = nullptr;
					barrierMiddle[j] = nullptr;
				}
				if (barrierRight[j] != nullptr && enemyProjecile[i] != nullptr && CheckCollisionRecs(enemyProjecile[i]->m_projectileRec, barrierRight[j]->m_barrierRec))
				{
					enemyProjecile[i] = nullptr;
					barrierRight[j] = nullptr;
				}
			}
		}
	}
	//move projectiles forward
	for (size_t i = 0; i < 4; i++)
	{
		if (projectile[i] != nullptr)
		{
			projectile[i]->MoveProjectile();
		}
		//delete projecitle if screen bound
		if (projectile[i] != nullptr && projectile[i]->m_projectileRec.y <= 0)
		{
			projectile[i] = nullptr;
		}
	}

	//move enemy projectiles forward
	for (int i = 0; i < 10; i++)
	{
		if (enemyProjecile[i] != nullptr)
		{
			enemyProjecile[i]->MoveEnemyProjectile();
		}
		//delete projecitle if screen bound
		if (enemyProjecile[i] != nullptr && enemyProjecile[i]->m_projectileRec.y >= GetScreenHeight())
		{
			enemyProjecile[i] = nullptr;
		}
	}

	for (int i = 0; i < 50; i++)
	{
		if (m_shouldMoveLeft == false)
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->m_enemyRec.x += enemy[i]->m_enemySpeed;
				if (enemy[i]->m_enemyRec.x > m_screenWidth - 80)
				{
					for (int enemyNum = 0; enemyNum < 50; enemyNum++)
					{
						if (enemy[enemyNum] != nullptr)
						{
							enemy[enemyNum]->m_enemyRec.y += 3;
						}
					}
					m_shouldMoveLeft = true;
				}
			}
		}
		else
		{
			if (enemy[i] != nullptr)
			{
				enemy[i]->m_enemyRec.x -= enemy[i]->m_enemySpeed;
				if (enemy[i]->m_enemyRec.x < +60)
				{
					for (int enemyNum = 0; enemyNum < 50; enemyNum++)
					{
						if (enemy[enemyNum] != nullptr)
						{
							enemy[enemyNum]->m_enemyRec.y += 3;
						}
					}
					m_shouldMoveLeft = false;
				}
			}
		}
	}

	for (int i = 0; i < 50; i++)
	{
		//players bullet collision with enemy 
		for (int bullet = 0; bullet < 4; bullet++)
		{
			if (enemy[i] != nullptr && projectile[bullet] != nullptr && CheckCollisionRecs(enemy[i]->m_enemyRec, projectile[bullet]->m_projectileRec))
			{
				if (enemy[i]->activeShooter != true)
				{
					continue;
				}
				else if (enemy[i - 10] != nullptr)
				{
					enemy[i - 10]->activeShooter = true;
				}
 				else if (enemy[i - 20] != nullptr)
				{
 					enemy[i - 20]->activeShooter = true;
				}
				else if (enemy[i - 30] != nullptr)
				{
					enemy[i - 30]->activeShooter = true;
				}
				else if (enemy[i - 40] != nullptr)
				{
					enemy[i - 40]->activeShooter = true;
				}

				enemy[i] = nullptr;
				projectile[bullet] = nullptr;
			}
		}
	}

	int currentActiveShooter = 0;
	for (int i = 0; i < 50; i++)
	{
		//store all current active shooters inside of m_activeshooter array
		if (enemy[i] != nullptr && enemy[i]->activeShooter == true)
		{
			m_activeShooters[currentActiveShooter] = i;
			currentActiveShooter++;
		}
	}

	//enemies shoot every 1 second choosing a random enemy from active shooter array
	if (m_senemyShootTimer >= 1)
	{
		int randNum = rand() % 10;

		if (enemy[m_activeShooters[randNum]] != nullptr)
		{
			enemyProjecile[enemyProjectileIndex] = new Projectile({ enemy[m_activeShooters[randNum]]->m_enemyRec.x + enemy[m_activeShooters[randNum]]->m_enemyRec.width / 2, enemy[m_activeShooters[randNum]]->m_enemyRec.y + 40, 10, 10 });
			m_senemyShootTimer = 0;
		}
	}
}


//use to draw to screen every frame
void GameApp::Draw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	for (size_t i = 0; i < 4; i++)
	{
		if (projectile[i] != nullptr)
		{
			projectile[i]->DrawProjectile();
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		if (enemyProjecile[i] != nullptr)
		{
			enemyProjecile[i]->DrawProjectile();
		}
	}

	for (int i = 0; i < 50; i++)
	{
		if (barrierLeft[i] != nullptr)
		{
			barrierLeft[i]->DrawBarriers();
		}
		if (barrierMiddle[i] != nullptr)
		{
			barrierMiddle[i]->DrawBarriers();
		}
		if (barrierRight[i] != nullptr)
		{
			barrierRight[i]->DrawBarriers();
		}



	}
	for (size_t i = 0; i < 50; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->DrawEnemies();
		}
	}

	player->DrawPlayer();

	EndDrawing();
}


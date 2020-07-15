#include "GameApp.h"
#include "raylib.h"
#include <iostream>


GameApp::GameApp()
{

}
GameApp::~GameApp()
{

}

void GameApp::Startup()
{
	m_screenWidth = MAP_COLS * 30;
	m_screenHeight = MAP_ROWS * 30;

	m_tileWidth = m_screenWidth / MAP_COLS;
	m_tileHeight = m_screenHeight / MAP_ROWS;

	for (int i = 0; i < MAP_COLS; i++)
		m_map[0][i] = WALL;
	for (int i = 1; i < MAP_ROWS; i++)
		m_map[i][MAP_COLS - 1] = WALL;
	for (int i = 1; i < MAP_ROWS; i++)
		m_map[i][0] = WALL;
	for (int i = 1; i < MAP_COLS - 1; i++)
		m_map[MAP_ROWS - 1][i] = WALL;

	for (int i = 0; i < 4; i++)
	{
		int Y = rand() % MAP_ROWS;
		int X = rand() % MAP_COLS;
		while (m_map[Y][X] == FOOD || m_map[Y][X] == WALL || m_map[Y][X] == BODY)
		{
			Y = rand() % MAP_ROWS;
			X = rand() % MAP_COLS;
		}
		m_map[Y][X] = FOOD;
	}


	InitWindow(m_screenWidth, m_screenHeight, "Snake");
	SetTargetFPS(60);

	m_snakePos.x = 0;
	m_snakePos.y = 0;
	m_snakeDir.x = 0;
	m_snakeDir.y = 0;
	m_snakeWidth = 20;
	m_snakeHeight = 20;


	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLS; x++)
		{
			/*	if (m_map[y][x] == START)
				{
					m_snakePos.x = x * m_tileWidth;
					m_snakePos.y = y * m_tileHeight;
				}*/
			if (m_map[y][x] == FOOD)
			{
				m_foodPos.x = x * m_tileWidth;
				m_foodPos.y = y * m_tileHeight;
			}
		}
	}
	m_snakeBodyList.push_front({ 3.0f * m_tileWidth,4.0f * m_tileHeight });
	m_snakeBodyList.push_front({ 4.0f * m_tileWidth,4.0f * m_tileHeight });
	m_snakeBodyList.push_front({ 5.0f * m_tileWidth,4.0f * m_tileHeight });
	m_snakeBodyList.push_front({ 6.0f * m_tileWidth,4.0f * m_tileHeight });
	m_snakeBodyList.push_front({ 7.0f * m_tileWidth,4.0f * m_tileHeight });

	m_snakePos = m_snakeBodyList.front();
}


void GameApp::Shutdown()
{
	CloseWindow();
}

void GameApp::Run()
{
	// Main game loop
	while (!WindowShouldClose() && !gameOver)    // Detect window close button or ESC key
	{
		Update();
		Draw();
	}
}
void GameApp::Update()
{
	if (IsKeyPressed(KEY_W) && m_snakeDir.y != 1)
	{
		m_snakeDir = { 0, -1 };
	}
	if (IsKeyPressed(KEY_S) && m_snakeDir.y != -1)
	{
		m_snakeDir = { 0, 1 };
	}
	if (IsKeyPressed(KEY_A) && m_snakeDir.x != 1)
	{
		m_snakeDir = { -1, 0 };
	}
	if (IsKeyPressed(KEY_D) && m_snakeDir.x != -1)
	{
		m_snakeDir = { 1, 0 };
	}

	// what tile index is snake on?
	int currentIndexX = (m_snakePos.x + m_tileWidth * 0.5f) / m_tileWidth;
	int currentIndexY = (m_snakePos.y + m_tileHeight * 0.5f) / m_tileHeight;


	if (m_map[currentIndexY][currentIndexX] == FOOD)
	{
		m_score += 1;
		m_map[currentIndexY][currentIndexX] = EMPTY;
		hitFood = true;
		int randX = rand() % MAP_COLS;
		int randY = rand() % MAP_ROWS;

		while (m_map[randY][randX] != EMPTY)
		{
			randX = rand() % MAP_COLS;
			randY = rand() % MAP_ROWS;
		}
		m_map[randY][randX] = FOOD;
	}
	if (m_map[currentIndexY][currentIndexX] == WALL)
	{
		gameOver = true;
	}

	if (m_map[currentIndexY][currentIndexX] == BODY)
	{
		gameOver = true;
	}

	m_snakeSubPos.x += m_snakeDir.x * m_tileWidth * GetFrameTime() * 0.3f;
	m_snakeSubPos.y += m_snakeDir.y * m_tileHeight * GetFrameTime() * 0.3f;

	if (abs(m_snakeSubPos.x - 1) <= 0.1f)
	{
		m_snakePos.x += m_tileWidth;
		m_snakeSubPos = { 0.5f,0.5f };
		if (!hitFood)
		{
			int backIndexX = m_snakeBodyList.back().x / m_tileWidth;
			int backIndexY = m_snakeBodyList.back().y / m_tileHeight;
			m_map[backIndexY][backIndexX] = EMPTY;
			m_snakeBodyList.pop_back();
		}
		else
		{
			hitFood = false;
		}
		int frontIndexX = m_snakeBodyList.front().x / m_tileWidth;
		int frontIndexY = m_snakeBodyList.front().y / m_tileHeight;
		m_map[frontIndexY][frontIndexX] = BODY;
		m_snakeBodyList.push_front(m_snakePos);
	}
	if (abs(m_snakeSubPos.x) <= 0.1f)
	{
		m_snakePos.x -= m_tileWidth;
		m_snakeSubPos = { 0.5f,0.5f };
		if (!hitFood)
		{
			int backIndexX = m_snakeBodyList.back().x / m_tileWidth;
			int backIndexY = m_snakeBodyList.back().y / m_tileHeight;
			m_map[backIndexY][backIndexX] = EMPTY;
			m_snakeBodyList.pop_back();
		}
		else
		{
			hitFood = false;
		}
		int frontIndexX = m_snakeBodyList.front().x / m_tileWidth;
		int frontIndexY = m_snakeBodyList.front().y / m_tileHeight;
		m_map[frontIndexY][frontIndexX] = BODY;
		m_snakeBodyList.push_front(m_snakePos);
	}
	if (abs(m_snakeSubPos.y - 1) <= 0.1f)
	{
		m_snakePos.y += m_tileHeight;
		m_snakeSubPos = { 0.5f,0.5f };
		if (!hitFood)
		{
			int backIndexX = m_snakeBodyList.back().x / m_tileWidth;
			int backIndexY = m_snakeBodyList.back().y / m_tileHeight;
			m_map[backIndexY][backIndexX] = EMPTY;
			m_snakeBodyList.pop_back();
		}
		else
		{
			hitFood = false;
		}
		int frontIndexX = m_snakeBodyList.front().x / m_tileWidth;
		int frontIndexY = m_snakeBodyList.front().y / m_tileHeight;
		m_map[frontIndexY][frontIndexX] = BODY;
		m_snakeBodyList.push_front(m_snakePos);
	}
	if (abs(m_snakeSubPos.y) <= 0.1f)
	{
		m_snakePos.y -= m_tileHeight;
		m_snakeSubPos = { 0.5f,0.5f };
		if (!hitFood)
		{
			int backIndexX = m_snakeBodyList.back().x / m_tileWidth;
			int backIndexY = m_snakeBodyList.back().y / m_tileHeight;
			m_map[backIndexY][backIndexX] = EMPTY;
			m_snakeBodyList.pop_back();
		}
		else
		{
			hitFood = false;
		}
		int frontIndexX = m_snakeBodyList.front().x / m_tileWidth;
		int frontIndexY = m_snakeBodyList.front().y / m_tileHeight;
		m_map[frontIndexY][frontIndexX] = BODY;
		m_snakeBodyList.push_front(m_snakePos);
	}
	// what tile index is snake on next tile?
	int nextIndexX = currentIndexX + m_snakeDir.x * m_tileWidth;
	int nextIndexY = currentIndexY + m_snakeDir.y * m_tileHeight;

}
void GameApp::Draw()
{
	int tw = m_tileWidth;
	int th = m_tileHeight;


	BeginDrawing();


	for (int y = 0; y < MAP_ROWS; y++)
	{
		for (int x = 0; x < MAP_COLS; x++)
		{
			int xPos = x * tw;
			int yPos = y * th;
			int tileID = m_map[y][x];

			if (tileID == WALL)
			{
				DrawRectangle(xPos, yPos, tw, th, Color(PINK));
			}
			if (tileID == FOOD)
			{
				DrawRectangle(xPos, yPos, tw, th, Color({ 255, 255, 0, 255 }));
			}
		}
	}
	for (auto& b : m_snakeBodyList)
	{
		DrawRectangle(b.x, b.y, tw, th, Color(GREEN));
	}
	char a[20];
	sprintf_s(a, "%d", m_score);
	DrawText(a, 50, 50, 50, ORANGE);
	ClearBackground(BLACK);

	EndDrawing();
}



#pragma once
#include <vector>
#include "raymath.h"
#include <list>

enum MAP_ITEMS
{
	EMPTY = 0,
	WALL = 1,
	FOOD = 2,
	BODY = 3,
};

enum Directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

class GameApp
{
public:

	GameApp();
	~GameApp();

	bool gameOver = false;
	static const int MAP_ROWS = 32;
	static const int MAP_COLS = 50;

	void Startup();
	void Shutdown();
	void Run();

	void Update();
	void Draw();

	bool hitFood = false;

	Vector2 m_snakeSubPos = { 0.5f,0.5f };

	int m_score = 0;
	Vector2 m_snakePos;
	Vector2 m_snakeDir;
	Vector2 m_foodPos;
	float m_snakeWidth;
	float m_snakeHeight;
	Rectangle m_snakeCol;
	Rectangle m_foodCol;



	std::list<Vector2> m_snakeBodyList;

private:

	int m_screenWidth;
	int m_screenHeight;

	int m_tileWidth;
	int m_tileHeight;
	int m_map[MAP_ROWS][MAP_COLS];


};







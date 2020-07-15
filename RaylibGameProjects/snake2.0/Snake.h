#pragma once

#include <list>

#include "raylib.h"

struct SnakeSegment
{
	int posX;
	int posY;
};

struct Apple
{
	int posX;
	int posY;
};

class Snake
{
public:
	Snake();
	~Snake();

	void Update(Vector2 bounds);

	void Draw(int size);

	bool GetAlive() { return isAlive; };

	int GetScore() { return score; };

private:

	void EatApple(Vector2 bounds);

	SnakeSegment head;

	std::list<SnakeSegment> body;

	Vector2 direction = { 1,0 };

	static const int SNAKE_SPEED = 6;
	int timer;

	int score;

	Apple apple;

	bool isAlive;
};


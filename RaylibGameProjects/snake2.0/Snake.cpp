#include "Snake.h"

Snake::Snake()
{
	//snake start pos
	head = SnakeSegment{20,20 };
	timer = SNAKE_SPEED;
	apple.posX = 10;
	apple.posY = 10;
	isAlive = true;
	score = 0;
}

Snake::~Snake()
{

}

void Snake::Update(Vector2 bounds)
{
	//Movement
	if (timer <= 0)
	{
		if (!body.empty())
		{
			body.pop_front();
		}
		body.push_back({ head.posX,head.posY });

		head.posX += direction.x;
		head.posY += direction.y;
		timer = SNAKE_SPEED - score / 10;
	}
	else
	{
		timer--;
	}

#pragma region PlayerInput
	if (IsKeyPressed(KEY_LEFT) && direction.x != 1)
	{
		direction = { -1, 0 };
	}
	else if (IsKeyPressed(KEY_RIGHT) && direction.x != -1)
	{
		direction = { 1,0 };
	}
	else if (IsKeyPressed(KEY_UP) && direction.y != 1)
	{
		direction = { 0,-1 };
	}
	else if (IsKeyPressed(KEY_DOWN) && direction.y != -1)
	{
		direction = { 0,1 };
	}
#pragma endregion

	//Check collision
	for (auto iter = body.begin(); iter != body.end(); iter++)
	{
		if (head.posX == iter->posX && head.posY == iter->posY)
		{
			//Game over
			isAlive = false;
			break;
		}
	}

	//Eat apple
	if (head.posX == apple.posX && head.posY == apple.posY)
	{
		EatApple(bounds);
	}

	//Wrap around
	if (head.posX > bounds.x)
	{
		head.posX = 0;
	}
	if (head.posX < 0)
	{
		head.posX = bounds.x;
	}
	if (head.posY > bounds.y)
	{
		head.posY = 0;
	}
	if (head.posY < 0)
	{
		head.posY = bounds.y;
	}
}

void Snake::Draw(int size)
{
	for (auto iter = body.begin(); iter != body.end(); iter++)
	{
		DrawRectangle(iter->posX * size, iter->posY * size, size, size, BLUE);
	}
	DrawRectangle(head.posX * size, head.posY * size, size, size, DARKBLUE);

	DrawRectangle(apple.posX * size, apple.posY * size, size, size, RED);
}

void Snake::EatApple(Vector2 bounds)
{
	apple.posX = GetRandomValue(0, bounds.x);
	apple.posY = GetRandomValue(0, bounds.y);
	body.push_front({ body.begin()->posX, body.begin()->posY });
	score++;
}

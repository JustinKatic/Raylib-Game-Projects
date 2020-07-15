#include "GameApp.h"
#include "raylib.h"
#include <iostream>


GameApp::GameApp()
{
	m_screenWidth = BOARD_WIDTH * SQUARE_SIZE;
	m_screenHeight = BOARD_HEIGHT * SQUARE_SIZE;

	InitWindow(m_screenWidth, m_screenHeight, "Snake");

	snake = nullptr;

	SetTargetFPS(60);
}
GameApp::~GameApp()
{

}

//happens before anything else once project opens up
void GameApp::Startup()
{
	snake = new Snake();
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
	if (snake->GetAlive())
	{
		snake->Update({ BOARD_WIDTH - 1,BOARD_HEIGHT - 1 });
	}
	else if (IsKeyPressed(KEY_ENTER))
	{
		delete snake;
		snake = new Snake();
	}
}
//use to draw to screen every frame
void GameApp::Draw()
{
	BeginDrawing();
	ClearBackground(WHITE);

	snake->Draw(SQUARE_SIZE);

	for (size_t i = 0; i < BOARD_WIDTH; i++)
	{
		for (size_t j = 0; j < BOARD_HEIGHT; j++)
		{
			DrawRectangleLines(i * SQUARE_SIZE, j * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, RAYWHITE);
		}
	}

	if (!snake->GetAlive())
	{
		DrawText("GAME OVER", m_screenWidth / 2 - MeasureText("GAME OVER", 32) / 2, 32, 32, RED);
		DrawText("Press ENTER to play again", m_screenWidth / 2 - MeasureText("Press ENTER to play again", 22) / 2, 60, 22, GRAY);
	}
	EndDrawing();
}


#include "Snake.h"

const int BOARD_WIDTH = 40;
const int BOARD_HEIGHT = 40;
const int SQUARE_SIZE = 20;


class GameApp
{
public:



	GameApp();
	~GameApp();

	void Startup();
	void Shutdown();
	void Run();

	void Update();
	void Draw();

private:
	int m_screenWidth;
	int m_screenHeight;

	Snake* snake;
};
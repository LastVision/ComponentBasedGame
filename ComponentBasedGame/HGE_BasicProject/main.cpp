#include <Windows.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	srand(static_cast<unsigned int>(GetTickCount()));

	Game myGame;
	
	myGame.Init(1280, 720);

	myGame.Run();
}
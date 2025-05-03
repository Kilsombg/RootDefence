#include "../include/Game.h"

#include "../include/Constants/SettingsConsts.h"

#include<Windows.h>
#include<iostream>

int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;


	// remove before sharing
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CON", "w", stdout);

	std::cout << "game init attempt...\n";
	if (TheGame::Instance()->init("Chapter 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, true))
	{
		std::cout << "game init success!\n";
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "game closing...\n";
	TheGame::Instance()->clean();
	return 0;
}
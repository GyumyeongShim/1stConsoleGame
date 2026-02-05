#include <iostream>
#define _CRTDBG_MAP_ALLOC

#include "Engine/Engine.h"
#include "Game/Game.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.Run();
}
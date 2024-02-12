#include <iostream>
#include "Game.h"

int main()
{
	Game::GetGame()->Run();
	Game::DestroyGame();
	return 0;
}
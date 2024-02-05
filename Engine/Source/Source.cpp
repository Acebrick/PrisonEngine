#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game::GetGame()->Run();
	Game::DestroyGame();
	return 0;
}
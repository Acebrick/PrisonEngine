#include "Game.h"
#include <iostream>

Game* Game::GetGame()
{
	// static = only run initialisation once
	//this is thread safe
	static Game* GameSingleton = new Game();
	return GameSingleton;
}

void Game::DestroyGame()
{
	delete GetGame();
}

Game::Game()
{
	printf("Game created\n");

	isGameOpen = true;
}

Game::~Game()
{
	printf("Game destroyed\n");
}

void Game::Initialise()
{
	printf("Initialise game\n");
	
	// TO DO: Run initialisation of dependencies

	Start();
}

void Game::Start()
{
	printf("Start game\n");

	// Launch the game window

	GameLoop();
}

void Game::GameLoop()
{
	while (isGameOpen)
	{
		ProcessInput();

		Update();

		Render();

		CollectGarbage();
	}

	Cleanup();
}

void Game::Cleanup()
{
	printf("Cleanup game\n");
}

void Game::ProcessInput()
{
	printf("Process input\n");
}

void Game::Update()
{
	printf("Update game logic\n");

	static int frames = 0;

	if (frames >= 30)
	{
		isGameOpen = false;
	}
	else
	{
		++frames;
	}
}

void Game::Render()
{
	printf("Render graphics\n");
}

void Game::CollectGarbage()
{
	printf("Collect garbage\n");
}

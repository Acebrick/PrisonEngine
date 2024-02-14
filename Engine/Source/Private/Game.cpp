#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"

Game* Game::GetGame()
{
	// static = only run initialisation once
	// this is thread safe
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
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	// Debug variables
	testTexture1 = nullptr;
	testTexture2 = nullptr;
	testTexture3 = nullptr;
	testTexture4 = nullptr;
	testTexture5 = nullptr;
	testTexture6 = nullptr;
	testTexture7 = nullptr;
	testTexture8 = nullptr;
	testTexture9 = nullptr;
	testTexture10 = nullptr;
}

Game::~Game()
{
	printf("Game destroyed\n");
}

void Game::Initialise()
{
	// TO DO: Run initialisation of dependencies
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		EE_LOG("Game", "SDL failed to init: " << SDL_GetError());
		return;
	}

	EE_LOG("Game", "Game successfully initialised all libraries");

	Start();
}

void Game::Start()
{
	// Launch the game window

	m_WindowRef = SDL_CreateWindow("Prison Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720,
		0);

	// Did the window successfully create
	if (m_WindowRef == nullptr)
	{
		EE_LOG("Game", "SDL window failed to create: " << SDL_GetError());
		
		// Deallocate everything that's been allocated
		Cleanup();
		return;
	}

	m_RendererRef = SDL_CreateRenderer(m_WindowRef, -1, 0);

	// Did the renderer fail
	if (m_RendererRef == nullptr)
	{
		EE_LOG("Game", "Renderer failed to create: " << SDL_GetError());
		Cleanup();
		return;
	}
	
	// DEBUG
	printHelloWorld();

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
	// Does the renderer exist
	if (m_RendererRef != nullptr)
	{
		SDL_DestroyRenderer(m_RendererRef);
		EE_LOG("Game", "Game renderer has been destroyed");
	}

	// Does the window exist
	if (m_WindowRef != nullptr)
	{
		SDL_DestroyWindow(m_WindowRef);
		EE_LOG("Game", "Game window has been destroyed");
	}

	SDL_Quit();
	EE_LOG("Game", "Game has deallocated all memory");
}

void Game::ProcessInput()
{
	// Data type that reads the SDL input events for the window
	SDL_Event inputEvent;

	// Run through each input in that frame
	while (SDL_PollEvent(&inputEvent))
	{
		// If cross button is pressed on the window ,close the app
		if (inputEvent.type == SDL_QUIT)
		{
			QuitApp();
		}
	}
}

void Game::Update()
{
	static float angle = 0.0f;

	if (testTexture1 != nullptr)
	{
		testTexture1->m_Angle = angle;
	}
	if (testTexture2 != nullptr)
	{
		testTexture2->m_Angle = angle;
	}
	if (testTexture3 != nullptr)
	{
		testTexture3->m_Angle = angle;
	}
	if (testTexture4 != nullptr)
	{
		testTexture4->m_Angle = angle;
	}
	if (testTexture5 != nullptr)
	{
		testTexture5->m_Angle = angle;
	}
	if (testTexture6 != nullptr)
	{
		testTexture6->m_Angle = angle;
	}
	if (testTexture7 != nullptr)
	{
		testTexture7->m_Angle = angle;
	}
	if (testTexture8 != nullptr)
	{
		testTexture8->m_Angle = angle;
	}
	if (testTexture9 != nullptr)
	{
		testTexture9->m_Angle = angle;
	}
	if (testTexture10 != nullptr)
	{
		testTexture10->m_Angle = angle;
	}

	angle += 0.5f;
}

void Game::Render()
{
	// Tell renderer what colour to use next
	SDL_SetRenderDrawColor(m_RendererRef, 150, 150, 150, 255);

	// Use the colour just stated to clear the previous frame and fill in with that colour
	SDL_RenderClear(m_RendererRef);

	// DEBUG
	if (testTexture1 != nullptr)
	{
		testTexture1->Draw();
	}	
	if (testTexture2 != nullptr)
	{
		testTexture2->Draw();
	}
	if (testTexture3 != nullptr)
	{
		testTexture3->Draw();
	}
	if (testTexture4 != nullptr)
	{
		testTexture4->Draw();
	}
	if (testTexture5 != nullptr)
	{
		testTexture5->Draw();
	}
	if (testTexture6 != nullptr)
	{
		testTexture6->Draw();
	}
	if (testTexture7 != nullptr)
	{
		testTexture7->Draw();
	}
	if (testTexture8 != nullptr)
	{
		testTexture8->Draw();
	}
	if (testTexture9 != nullptr)
	{
		testTexture9->Draw();
	}
	if (testTexture10 != nullptr)
	{
		testTexture10->Draw();
	}

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	
}

void Game::printHelloWorld()
{
	// Debug
	//H
	testTexture1 = new Texture(m_RendererRef);
	if (!testTexture1->ImportTexture("Content/Letters/HBlue.png"))
	{
		testTexture1->Cleanup();
		delete testTexture1;
		testTexture1 = nullptr;
	}
	else
	{
		testTexture1->m_PosX = 50.0f;
		testTexture1->m_PosY = 190.0f;
		testTexture1->m_Scale = 1.5f;
	}

	//E
	testTexture2 = new Texture(m_RendererRef);
	if (!testTexture2->ImportTexture("Content/Letters/ERed.png"))
	{
		testTexture2->Cleanup();
		delete testTexture2;
		testTexture2 = nullptr;
	}
	else
	{
		testTexture2->m_PosX = 250.0f;
		testTexture2->m_PosY = 285.0f;
		testTexture2->m_Scale = 0.7f;
	}

	//L
	testTexture3 = new Texture(m_RendererRef);
	if (!testTexture3->ImportTexture("Content/Letters/LRed.png"))
	{
		testTexture3->Cleanup();
		delete testTexture3;
		testTexture3 = nullptr;
	}
	else
	{
		testTexture3->m_PosX = 350.0f;
		testTexture3->m_PosY = 285.0f;
		testTexture3->m_Scale = 0.7f;
	}

	//L2
	testTexture4 = new Texture(m_RendererRef);
	if (!testTexture4->ImportTexture("Content/Letters/LRed.png"))
	{
		testTexture4->Cleanup();
		delete testTexture4;
		testTexture4 = nullptr;
	}
	else
	{
		testTexture4->m_PosX = 450.0f;
		testTexture4->m_PosY = 285.0f;
		testTexture4->m_Scale = 0.7f;
	}

	//O
	testTexture5 = new Texture(m_RendererRef);
	if (!testTexture5->ImportTexture("Content/Letters/ORed.png"))
	{
		testTexture5->Cleanup();
		delete testTexture5;
		testTexture5 = nullptr;
	}
	else
	{
		testTexture5->m_PosX = 550.0f;
		testTexture5->m_PosY = 285.0f;
		testTexture5->m_Scale = 0.7f;
	}

	//W
	testTexture6 = new Texture(m_RendererRef);
	if (!testTexture6->ImportTexture("Content/Letters/WBlue.png"))
	{
		testTexture6->Cleanup();
		delete testTexture6;
		testTexture6 = nullptr;
	}
	else
	{
		testTexture6->m_PosX = 550.0f;
		testTexture6->m_PosY = 500.0f;
		testTexture6->m_Scale = 1.5f;
	}

	//O
	testTexture7 = new Texture(m_RendererRef);
	if (!testTexture7->ImportTexture("Content/Letters/ORed.png"))
	{
		testTexture7->Cleanup();
		delete testTexture7;
		testTexture7 = nullptr;
	}
	else
	{
		testTexture7->m_PosX = 750.0f;
		testTexture7->m_PosY = 585.0f;
		testTexture7->m_Scale = 0.7f;
	}

	//R
	testTexture8 = new Texture(m_RendererRef);
	if (!testTexture8->ImportTexture("Content/Letters/RRed.png"))
	{
		testTexture8->Cleanup();
		delete testTexture8;
		testTexture8 = nullptr;
	}
	else
	{
		testTexture8->m_PosX = 850.0f;
		testTexture8->m_PosY = 585.0f;
		testTexture8->m_Scale = 0.7f;
	}

	//L
	testTexture9 = new Texture(m_RendererRef);
	if (!testTexture9->ImportTexture("Content/Letters/LRed.png"))
	{
		testTexture9->Cleanup();
		delete testTexture9;
		testTexture9 = nullptr;
	}
	else
	{
		testTexture9->m_PosX = 950.0f;
		testTexture9->m_PosY = 585.0f;
		testTexture9->m_Scale = 0.7f;
	}

	//D
	testTexture10 = new Texture(m_RendererRef);
	if (!testTexture10->ImportTexture("Content/Letters/DRed.png"))
	{
		testTexture10->Cleanup();
		delete testTexture10;
		testTexture10 = nullptr;
	}
	else
	{
		testTexture10->m_PosX = 1050.0f;
		testTexture10->m_PosY = 585.0f;
		testTexture10->m_Scale = 0.7f;
	}
}

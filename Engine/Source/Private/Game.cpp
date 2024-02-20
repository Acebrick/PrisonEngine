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

Texture* Game::ImportTexture(const char* pathToFile)
{
	Texture* newTexture = new Texture(m_RendererRef);

	// Loop through all the textures in the game
	for (Texture* texRef : m_TextureStack)
	{
		// Check if texture already been imported
		if (std::strcmp(texRef->GetPath(), pathToFile) == 0)
		{
			// If there was a mtach, copy successfully matched element
			newTexture->CopyTexture(texRef);

			// Add it to the texture stack
			m_TextureStack.push_back(newTexture);
			return newTexture;
		}
	}

	// Attempt to import the texture
	if (newTexture->ImportTexture(pathToFile))
	{
		delete newTexture;
		newTexture = nullptr;
	}
	else
	{
		m_TextureStack.push_back(newTexture);
	}

	return newTexture;
}

void Game::DestroyTexture(Texture* textureToDestroy)
{
	// 10:00
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
	// Clean up and remove all texturesz from hte texture sdtack
	for (Texture* texRef : m_TextureStack)
	{
		texRef->Cleanup();
		delete texRef;
		texRef = nullptr;
	}

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

	angle += 0.1f;
}

void Game::Render()
{
	// Tell renderer what colour to use next
	SDL_SetRenderDrawColor(m_RendererRef, 150, 150, 150, 255);

	// Use the colour just stated to clear the previous frame and fill in with that colour
	SDL_RenderClear(m_RendererRef);

	for (Texture* texRef : m_TextureStack)
	{
		texRef->Draw();
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
	testTexture1 = ImportTexture("Content/Letters/ERed.png"); // correct
	if (testTexture1 != nullptr)
	{
		m_TextureStack.push_back(testTexture1);
		testTexture1->m_PosX = 0.0f;
		testTexture1->m_PosY = 0.0f;
		testTexture1->m_Scale = 1.5f;
	}
}

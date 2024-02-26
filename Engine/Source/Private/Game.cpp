#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include "Input.h"

// DEBUG
#include "Graphics/Animation.h"
#include "Math/Vector2.h"

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

	// Loop through all of the textures in the game
	for (Texture * texRef : m_TextureStack)
	{
		if (std::strcmp(texRef->GetPath(), pathToFile) == 0)
		{
			// If there was a matching path, copt the successfully matched element
			newTexture->CopyTexture(texRef);

			// Add it to the texture stack
			m_TextureStack.push_back(newTexture);
			
			// Return the new texture here to ignore the rest of the function
			return newTexture;
		}
	}

	// Attempt to import the texture
	if (!newTexture->ImportTexture(pathToFile))
	{
		// If it failed then delete and update new texture to nullptr
		delete newTexture;
		newTexture = nullptr;
	}
	else
	{
		// If the import was successful
		m_TextureStack.push_back(newTexture);
	}

	return newTexture;
}

void Game::DestroyTexture(Texture* textureToDestroy)
{
	int texturesFound = 0;

	 // Loop through all of the textures
	for (Texture* texRef : m_TextureStack)
	{
		// If the texture has a matching path
		if (std::strcmp(textureToDestroy->GetPath(), texRef->GetPath()) == 0)
		{
			++texturesFound;

			if (texturesFound > 1)
			{
				break;
			}
		}
	}

	// If there is not a copy, deallocate all memory related to the texture
	if (texturesFound <= 1)
	{
		textureToDestroy->Cleanup();
	}

	// Find the texture in the array
	TArray<Texture*>::iterator it = std::find(m_TextureStack.begin(), m_TextureStack.end(), textureToDestroy);

	// If we find the texture
	if (it != m_TextureStack.end()) 
	{
		m_TextureStack.erase(it);
	}

	// Remove the texture object from memory
	delete textureToDestroy;
	textureToDestroy = nullptr;

	EE_LOG("Game", "Texture has been destroyed");
}

Game::Game()
{
	printf("Game created\n");

	isGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	// Debug variables
	m_TestAnim1 = nullptr;
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

	// Create the game input
	m_GameInput = new Input();
	
	// DEBUG
	AnimationParams AnimParams;
	AnimParams.fps = 12.0f;
	AnimParams.maxFrames = 5;
	AnimParams.endFrame = 4;
	AnimParams.frameHeight = 48;
	AnimParams.frameWidth = 48;


	// DEBUG
	m_TestAnim1 = new Animation();

	m_TestAnim1->CreateAnimation("Content/Sprites/SpaceGunner/CharacterSprites/Red/Gunner_Red_Idle.png",
		&AnimParams);
	m_TestAnim1->SetScale(3.0f);
	m_TestAnim1->SetPosition(640, 360);

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
	for (int i = m_TextureStack.size() - 1; i > -1; --i)
	{
		DestroyTexture(m_TextureStack[i]);
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
	m_GameInput->ProcessInput();
}

void Game::Update()
{
	// Record the previous frame time
	static double lastTickTime = 0.0;
	// Record the current frame
	double currentTickTime = (double)SDL_GetTicks64();
	// Get the delta time - how much time has passed since the last frame
	double longDelta = currentTickTime - lastTickTime;
	// Convert from milliseconds to seconds
	double deltaTime = longDelta / 1000.0;
	// Set the last tick time
	lastTickTime = currentTickTime;

	// DEBUG

	// Position of the animation on the screen
	static Vector2 position(640.0f, 360.0f); // same as variable = value

	// Speed of movement
	float speed = 100.0f * (float)deltaTime;

	// Direction to move
	Vector2 movementDirection = 0.0f;

	if (m_GameInput->IsKeyDown(EE_KEY_W))
	{
		movementDirection.y += -1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_S))
	{
		movementDirection.y += 1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_A))
	{
		movementDirection.x += -1.0f;
	}
	if (m_GameInput->IsKeyDown(EE_KEY_D))
	{
		movementDirection.x += 1.0f;
	}

	// Move animation to the right
	position += movementDirection * speed;

	if (m_TestAnim1 != nullptr)
	{
		m_TestAnim1->SetPosition(position.x, position.y);
		m_TestAnim1->Update((float)deltaTime);
	}

	if (m_GameInput->IsMouseButtonDown(EE_MOUSE_LEFT))
	{
		m_GameInput->GetMousePos().Log();
	}
}

void Game::Render()
{
	// Tell renderer what colour to use next
	SDL_SetRenderDrawColor(m_RendererRef, 150, 150, 150, 255);

	// Use the colour just stated to clear the previous frame and fill in with that colour
	SDL_RenderClear(m_RendererRef);

	// TODO: Render custom graphics
	for (Texture* texRef : m_TextureStack) // for each loop syntax "(dataType iteratorName : array/vector to iterate) auto iterates array/vector and executes loops code
	{
		if (texRef != nullptr)
		{
			texRef->Draw();
		}
	}

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	
}

void Game::printHelloWorld()
{

}

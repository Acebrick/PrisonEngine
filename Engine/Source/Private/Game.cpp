#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"

// DEBUG
#include "Graphics/Animation.h"

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
	m_GunnerBlackRun = nullptr;
	m_JetpackGunner = nullptr;
	m_PlatformTop = nullptr;
	m_PlatformMid = nullptr;
	m_PlatformBottom = nullptr;
	m_JetpackEffect = nullptr;
	m_Bullet = nullptr;
	m_MuzzleFlash = nullptr;
	m_GunnerBlackDead = nullptr;
	m_GunnerGreenIdle = nullptr;
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

	// Display background/Static textures
	m_PlatformTop = new Animation();
	m_PlatformTop->CreateAnimation("Content/Sprites/SpaceGunner/Extras/PlatformLong.png");
	m_PlatformTop->SetPosition(500, 140);
	m_PlatformTop->SetScale(2.0f);

	m_PlatformMid = new Animation();
	m_PlatformMid->CreateAnimation("Content/Sprites/SpaceGunner/Extras/PlatformLong.png");
	m_PlatformMid->SetPosition(500, 340);
	m_PlatformMid->SetScale(2.0f);

	m_PlatformBottom = new Animation();
	m_PlatformBottom->CreateAnimation("Content/Sprites/SpaceGunner/Extras/PlatformLong.png");
	m_PlatformBottom->SetPosition(500, 540);
	m_PlatformBottom->SetScale(2.0f);

	// Declare different animation parameters
	AnimationParams gunnerRun;
	AnimationParams gunnerIdle;
	AnimationParams gunnerJump;
	AnimationParams jetpackBoots;
	AnimationParams gunnerDead;
	
	// Get values for animation parameters
	m_GunnerBlackRun->AnimTypeDefinitions(0, gunnerIdle);
	m_GunnerBlackRun->AnimTypeDefinitions(1, gunnerRun);
	m_GunnerBlackRun->AnimTypeDefinitions(2, gunnerJump);
	m_GunnerBlackRun->AnimTypeDefinitions(3, jetpackBoots);
	m_GunnerBlackRun->AnimTypeDefinitions(5, gunnerDead);
	
	// Animations
	m_GunnerBlackRun = new Animation();
	m_GunnerBlackRun->CreateAnimation("Content/Sprites/SpaceGunner/CharacterSprites/Black/Gunner_Black_Run.png",
		&gunnerRun);
	m_GunnerBlackRun->SetScale(3.0f);
	m_GunnerBlackRun->SetPosition(640, 90);

	m_GunnerBlackDead = new Animation();
	m_GunnerBlackDead->CreateAnimation("Content/Sprites/SpaceGunner/CharacterSprites/Black/Gunner_Black_Death.png",
		&gunnerDead);

	m_JetpackGunner = new Animation();
	m_JetpackGunner->CreateAnimation("Content/Sprites/SpaceGunner/CharacterSprites/Yellow/Gunner_Yellow_Jump.png",
		&gunnerJump);
	m_JetpackGunner->SetScale(3.0f);
	m_JetpackGunner->SetPosition(1050, 1000);

	m_JetpackEffect = new Animation();
	m_JetpackEffect->CreateAnimation("Content/Sprites/MainShip/Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&jetpackBoots);
	m_JetpackEffect->SetScale(1.7f);

	m_Bullet = new Animation();
	m_Bullet->CreateAnimation("Content/Sprites/SpaceGunner/Extras/SpongeBullet.png", nullptr);
	m_Bullet->SetScale(3.0f);

	m_MuzzleFlash = new Animation();
	m_MuzzleFlash->CreateAnimation("Content/Sprites/SpaceGunner/Extras/MuzzleFlash.png", nullptr);
	m_MuzzleFlash->SetScale(3.0f);

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

	static bool gunRunnerShot = false; // Trigger to play death animation
	static bool gunRunnerDead = false; // Stop all gun runner animations/movement (look dead)

	if (m_GunnerBlackRun != nullptr)
	{
		if (!gunRunnerShot)
		{
			m_GunnerBlackRun->Update((float)deltaTime);
			m_GunnerBlackRun->gunnerRunning(m_GunnerBlackRun, m_Bullet, (float)deltaTime);
		}
		else if (gunRunnerShot && !gunRunnerDead)
		{
			m_GunnerBlackRun->Update((float)deltaTime);
			gunRunnerDead = m_GunnerBlackRun->gunnerDead(m_GunnerBlackRun);
		}
	}
	if (m_JetpackGunner != nullptr)
	{
		m_JetpackGunner->Update((float)deltaTime);
		gunRunnerShot = m_JetpackGunner->jetpackGunner(m_JetpackGunner, m_JetpackEffect, m_Bullet, m_GunnerBlackRun, m_MuzzleFlash, (float)deltaTime);
	}
	if (m_JetpackEffect != nullptr)
	{
		m_JetpackEffect->Update((float)deltaTime);
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
			if (!texRef->imageFlipped)
			{
				texRef->Draw(false);
			}
			else
			{
				texRef->Draw(true);
			}
		}
	}

	// Present the graphics to the renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	
}
#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include "Input.h"
#include "GameObjects/GameObject.h"

// DEBUG
#include "Graphics/Animation.h"
#include "Math/Vector2.h"
#include "GameObjects/PhysicsObject.h"

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

template<typename T>
T* Game::AddGameObject()
{
	// Create the game object
	T* newObject = new T();

	// Add the object to our pending spawn array
	m_GameOjectPendingSpawn.push_back(newObject);

	return newObject;
}

Game::Game()
{
	printf("Game created\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;
	m_GameInput = nullptr;

	// Debug variables
	m_TestAnim1 = nullptr;
	m_TestObject = nullptr;
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



	// DEBUG
	//m_TestAnim1 = new Animation();

	//m_TestAnim1->CreateAnimation("",
	//	&AnimParams);
	//m_TestAnim1->SetScale(3.0f);
	//m_TestAnim1->SetPosition(640, 360);

	m_TestObject = AddGameObject<PhysicsObject>();

	GameLoop();
}

void Game::GameLoop()
{
	while (m_IsGameOpen)
	{
		PreLoop();

		ProcessInput();

		Update();

		Render();

		CollectGarbage();
	}

	Cleanup();
}

void Game::Cleanup()
{
	// Destory any objects pending spawn
	for (auto GO : m_GameOjectPendingSpawn)
	{
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}

	// Destroy any remaining game objects
	for (auto GO : m_GameObjectStack)
	{
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}
	
	// Clean up and remove all textures from the texture stack
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

void Game::PreLoop()
{
	// Add all game object pending spawn to the game object stack
	for (auto GO : m_GameOjectPendingSpawn)
	{
		m_GameObjectStack.push_back(GO);
		GO->Start();
	}

	// Resize the array to 0
	m_GameOjectPendingSpawn.clear();
}

void Game::ProcessInput()
{
	// Process the inputs for the game
	m_GameInput->ProcessInput();

	// Run the input listener function for all game objects
	for (auto GO : m_GameObjectStack)
	{
		if (GO != nullptr)
		{
			GO->ProcessInput(m_GameInput);
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

	// DEBUG

	// Position of the animation on the screen
	static Vector2 position(640.0f, 360.0f); // same as variable = value

	// Speed of movement
	float speed = 1000.0f * (float)deltaTime;

	// Direction to move
	Vector2 movementDirection = 0.0f;

	//movePlayerWithMouse(position.x, position.y, movementDirection);

	// Move player with WASD
	//if (m_GameInput->IsKeyDown(EE_KEY_W))
	//{
	//	movementDirection.y += -1.0f;
	//}
	//if (m_GameInput->IsKeyDown(EE_KEY_S))
	//{
	//	movementDirection.y += 1.0f;
	//}
	//if (m_GameInput->IsKeyDown(EE_KEY_A))
	//{
	//	movementDirection.x += -1.0f;
	//}
	//if (m_GameInput->IsKeyDown(EE_KEY_D))
	//{
	//	movementDirection.x += 1.0f;
	//}

	//if (m_GameInput->IsKeyDown(EE_KEY_SPACE))
	//{
	//	if (m_TestObject != nullptr)
	//	{
	//		m_TestObject->DestroyObject();
	//		m_TestObject = nullptr;
	//	}
	//}

	//// Move animation to the right
	//position += movementDirection * speed;

	//if (m_TestAnim1 != nullptr)
	//{
	//	m_TestAnim1->SetPosition(position.x, position.y);
	//	m_TestAnim1->Update((float)deltaTime);
	//}

	for (auto GO : m_GameObjectStack)
	{
		if (GO != nullptr)
		{
			GO->Update((float)deltaTime);
			GO->PostUpdate((float)deltaTime);
		}
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
	// Delete objects at the end of each frame
	for (int i = m_GameObjectStack.size() - 1; i >= 0; i--) // i-- may cause issues
	{
		if (m_GameObjectStack[i]->isPendingDestroy() == false)
		{
			continue;
		}

		if (m_GameObjectStack[i] != nullptr)
		{
			m_GameObjectStack[i]->Cleanup();
			delete m_GameObjectStack[i];
		}

		// Remove from and resize the array
		m_GameObjectStack.erase(m_GameObjectStack.begin() + i);
	}
}

void Game::movePlayerWithMouse(float xPos, float yPos, Vector2 &direction)
{
	// FOLLOW MOUSE VARIABLES

	Vector2 mousePos = m_GameInput->GetMousePos(); // Maintain mouse position
	static Vector2 triangleSideLength; // Sides of hypothetical right angled triangle to get angles

	// Angle closest to horizontal/x axis
	static float angleOfX;

	// Angle closest to vertical/y axis
	static float angleOfY;

	// Percentage out of 100 these angles make up out of 90 degrees
	static float xAnglePercent = 0;
	static float yAnglePercent = 0;

	// Get the length of the two sides excluding the hypotenuse
	triangleSideLength.x = mousePos.x - xPos;
	triangleSideLength.y = mousePos.y - yPos;

	// Convert any negative lengths to positive to allow for proper angle calculations
	if (triangleSideLength.x < 0)
	{
		triangleSideLength.x = -triangleSideLength.x;
	}
	if (triangleSideLength.y < 0)
	{
		triangleSideLength.y = -triangleSideLength.y;
	}

	// Calculate the angle connecting the side parellel to the x axis and the hypotenuse (angle closest to player)
	angleOfX = atan(triangleSideLength.y / triangleSideLength.x) / (3.14f / 180.0f);
	angleOfY = (90.0f - angleOfX);

	// Converted to be a percentage out of 100 that these angles make up out of 90 degrees (in decimal format, so 1 = 100%)
	// Minused by 1 as angle distance is at its lowest when mouse is positioned in desired movement direction
	// This just reverses the two and makes code easier to read when used as x is now used with x movement and y is used with y movement
	xAnglePercent = 1 - angleOfX / 90.0f;
	yAnglePercent = 1 - angleOfY / 90.0f;

	// Move the player in the direction of the mouse
	if (m_GameInput->IsMouseButtonDown(EE_MOUSE_LEFT))
	{
		if (mousePos.x > xPos) // Go right
		{
			direction.x += 1.0f * xAnglePercent;
		}
		else // Go left
		{
			direction.x += -1.0f * xAnglePercent;
		}
		if (mousePos.y > yPos) // Go down
		{
			direction.y += 1.0f * yAnglePercent;
		}
		else // Go up
		{
			direction.y += -1.0f * yAnglePercent;
		}
	}

	// Rotate the player based on the mouse position
	if (mousePos.x > xPos && mousePos.y < yPos) // Top right of circle
	{
		m_TestAnim1->SetRotation(angleOfY);
	}
	if (mousePos.x > xPos && mousePos.y > yPos) // Bottom right of circle
	{
		m_TestAnim1->SetRotation(angleOfX + 90);
	}
	if (mousePos.x < xPos && mousePos.y > yPos) // Bottom left of circle
	{
		m_TestAnim1->SetRotation(angleOfY + 180);
	}
	if (mousePos.x < xPos && mousePos.y < yPos) // Top left of circle
	{
		m_TestAnim1->SetRotation(angleOfX + 270);
	}

	// DEBUG VARIABLES
	//std::cout << "triangleSideLength.x: " << triangleSideLength.x << std::endl;
	//std::cout << "triangleSideLength.y: " << triangleSideLength.y << std::endl;
	//std::cout << "angleOfX: " << angleOfX << std::endl;
	//std::cout << "angleOfY: " << angleOfY << std::endl;
	//std::cout << "xAnglePercent: " << xAnglePercent << std::endl;
	//std::cout << "yAnglePercent: " << yAnglePercent << std::endl;
}

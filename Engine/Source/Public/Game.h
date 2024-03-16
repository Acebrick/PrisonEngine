#pragma once
#include "EngineTypes.h"

// Forward declaration
struct SDL_Window;
struct SDL_Renderer;
class Texture;
class Input;
class GameObject;

struct Vector2;

class Game
{
public:
	// Get the game singleton or create one if it doesn't exist
	static Game* GetGame();

	// Deallocacte the game from memory
	static void DestroyGame();

	// Run the game
	void Run() { Initialise(); };

	void QuitApp() { m_IsGameOpen = false; }

	// Import a texture to the game
	Texture* ImportTexture(const char* pathToFile);

	void DestroyTexture(Texture* textureToDestroy);

	// Add a game object to the game
	template<typename T>
	T* AddGameObject();

	TArray<GameObject*> GetGameObject()
	{
		return m_GameObjectStack;
	}

private:
	// Functions

// Flag that decides when the game loop ends
	bool m_IsGameOpen;

	Game();
	~Game();

	// Core game functions

	// Initialise the dependencies/external libraries
	// This will exit the game if any fail
	void Initialise();

	// This will run the post-initialise functions that rely on dependencies
	// Load the window and any start game functions
	void Start();

	// Run the game loop functions of the game until the app closes
	void GameLoop();

	// Deallocate memory after the game loop has been exited
	void Cleanup();

	// Game loop

	// Checks if any objects ned to be spawned
	void PreLoop();

	// Listen for user input and process
	void ProcessInput();

	// Update the game logic, no rendering logic updates first then display the results
	void Update();

	// Display the results and render the graphics to the screen based on the logic
	void Render();

	// Any objects that are marked for delete will be deallocated from memory here
	void CollectGarbage();

	// Stores the window for the app/game
	SDL_Window* m_WindowRef;

	// Stores the renderer
	SDL_Renderer* m_RendererRef;

	TArray<Texture*> m_TextureStack;

	// Store the input handler for the game
	Input* m_GameInput;

	// Store all game objects that need to be spawned on the next loop
	TArray<GameObject*> m_GameOjectPendingSpawn;

	// Store all of the game objects in the game
	TArray<GameObject*> m_GameObjectStack;
};



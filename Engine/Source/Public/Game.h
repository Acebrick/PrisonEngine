#pragma once
#include "EngineTypes.h"

// Forward declaration
struct SDL_Window;
struct SDL_Renderer;
class Texture;

// DEBUG
class Animation;

class Game
{
public:
	// Get the game singleton or create one if it doesn't exist
	static Game* GetGame();

	// Deallocacte the game from memory
	static void DestroyGame();

	// Run the game
	void Run() { Initialise(); };

	void QuitApp() { isGameOpen = false; }

	// Import a texture to the game
	Texture* ImportTexture(const char* pathToFile);

	void DestroyTexture(Texture* textureToDestroy);

private:
	// Functions

// Flag that decides when the game loop ends
	bool isGameOpen;

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

	// DEBUG TESTING VARIABLES
	Animation* m_SpaceBackground;
	Animation* m_GunnerBlack;
	Animation* m_JetpackGunner;
	Animation* m_PlatformTop;
	Animation* m_PlatformMid;
	Animation* m_PlatformBottom;
	Animation* m_JetpackEffect;
	Animation* m_Bullet;
	Animation* m_MuzzleFlash;
	Animation* m_GunnerGreen;
	Animation* m_GunnerRed;
	Animation* m_Explosion;
	Animation* m_SawTrap;
	Animation* m_LightningTrap;
	Animation* m_PlatformVertical1;
	Animation* m_PlatformVertical2;
	Animation* m_ToxicTrap;
};
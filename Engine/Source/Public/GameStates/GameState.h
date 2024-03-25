#pragma once
#include "EngineTypes.h"

class Input;
struct SDL_Renderer;
class GameObject;

class GameState
{
public:
	GameState() : m_ShouldDestroy(false) {}
	virtual ~GameState() = default;

	// Run when the game state starts
	void Start();

	// Clean up and deallocate the memory for the state
	void Cleanup();

	// Runs every frame at the start of a game loop
	void PreLoop();

	// Detects input of the game
	void ProcessInput(Input* gameInput);

	// Update each frame after input
	void Update(float deltaTime);

	// Render game object bounds
	void Render(SDL_Renderer* renderer);

	// Runs at the end of the frame and deallocates memory as needed
	void GarbageCollection();

	// Add a game object to the game (RUN TEMPLATE FUNCTIONS IN THE HEADER)
	template<typename T>
	T* AddGameObject()
	{
		// Create the game object
		T* newObject = new T();

		// Add the object to our pending spawn array
		m_GameOjectPendingSpawn.push_back(newObject);

		return newObject;
	}

	// Mark the game for destroy at the end of the loop
	void DestroyGameState() { m_ShouldDestroy = true; }

	// Check if the game state is to be destroyed
	bool IsPendingDestroy() const { return m_ShouldDestroy; }

protected:
	virtual void OnStart() {}

	virtual void OnCleanup() {}

	virtual void OnPreLoop() {}

	virtual void OnProcessInput(Input* gameInput) {}

	virtual void OnUpdate(float deltaTime) {}

	virtual void OnGarbageCollection() {}

private:
	// Store all game objects that need to be spawned on the next loop
	TArray<GameObject*> m_GameOjectPendingSpawn;

	// Store all of the game objects in the game
	TArray<GameObject*> m_GameObjectStack;

	// Mark for deletion
	bool m_ShouldDestroy;
};


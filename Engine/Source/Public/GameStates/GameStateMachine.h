#pragma once
#include "EngineTypes.h"
#include "GameStates/GameState.h"
#include "GameStates/PlayState.h"

class GameStateMachine
{
public: 
	GameStateMachine(GameState* defaultGameState = new GameState());
	~GameStateMachine() = default;

	// Return the current active game state
	GameState* GetActiveGameState() const;

	// Cleanup the game state machine and remove all gamestates
	void Cleanup();

	// Add or switch a game state
	void SetNewGameState(GameState* newGameState = new GameState(), bool isAdditive = false);

	// Collect garbage at the end of each frame
	void GarbageCollection();

	// Run at the start of each frame
	void PreLoop();

	// Detects input of the game
	void ProcessInput(Input* gameInput);

	// Update each frame after input
	void Update(float deltaTime);

	// Render game object bounds
	void Render(SDL_Renderer* renderer);

private:
	// Store all active game states
	TArray<GameState*> m_ActiveGameStateStack;

	// Store all game states ready for spawn on next loop
	TArray<GameState*> m_PendingGameStateStack;

};
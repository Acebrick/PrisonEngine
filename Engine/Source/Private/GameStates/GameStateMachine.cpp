#include "GameStates/GameStateMachine.h"

GameStateMachine::GameStateMachine(GameState* defaultGameState)
{
	SetNewGameState(defaultGameState);
}

GameState* GameStateMachine::GetActiveGameState() const
{
	return m_ActiveGameStateStack.back();
}

void GameStateMachine::Cleanup()
{
	// Delete all pending game stacks
	for (const auto GS : m_PendingGameStateStack)
	{
		GS->Cleanup();
		delete GS;
	}

	// Delete all active game stacks
	for (const auto GS : m_ActiveGameStateStack)
	{
		GS->Cleanup();
		delete GS;
	}
}

void GameStateMachine::SetNewGameState(GameState* newGameState, bool isAdditive)
{
	if (isAdditive)
	{
		return;
	}

	// Clear all of the current game states
	for (const auto GS : m_ActiveGameStateStack)
	{
		GS->DestroyGameState();
	}

	if (newGameState != nullptr)
	{
		// Adding it to the spawn on the next loop
		m_PendingGameStateStack.push_back(newGameState);
	}	
}

void GameStateMachine::GarbageCollection()
{
	GetActiveGameState()->GarbageCollection();

	if (m_ActiveGameStateStack.size() < 2)
	{
		return;
	}

	std::erase_if(m_ActiveGameStateStack,
		[](GameState* GS) {
			if (!GS->IsPendingDestroy())
			{
				return false;
			}

			GS->Cleanup();
			delete GS;

			return true;
		}
	);
}

void GameStateMachine::PreLoop()
{
	for (const auto GS : m_PendingGameStateStack)
	{
		m_ActiveGameStateStack.push_back(GS);
		GS->Start();
	}

	m_PendingGameStateStack.clear();

	GetActiveGameState()->PreLoop();
}

void GameStateMachine::ProcessInput(Input* gameInput)
{
	GetActiveGameState()->ProcessInput(gameInput);
}

void GameStateMachine::Update(float deltaTime)
{
	GetActiveGameState()->Update(deltaTime);
}

void GameStateMachine::Render(SDL_Renderer* renderer)
{
	GetActiveGameState()->Render(renderer);
}

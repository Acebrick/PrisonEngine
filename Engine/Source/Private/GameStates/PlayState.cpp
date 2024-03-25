#include "GameStates/PlayState.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/Player.h"
#include "Input.h"
#include "Game.h"
#include "GameStates/GameStateMachine.h"

void PlayState::OnStart()
{
	AddGameObject<Player>();
	AddGameObject<Enemy>();
}

void PlayState::OnProcessInput(Input* gameInput)
{
	if (gameInput->IsKeyDown(EE_KEY_SPACE))
	{
		GameState* newState = new PlayState();
		Game::GetGame()->GetGameStateMachine()->SetNewGameState(newState);
	}
}

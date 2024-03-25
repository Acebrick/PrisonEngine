#pragma once
#include "GameStates/GameState.h"

class PlayState : public GameState
{
public:
	PlayState() = default;

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* gameInput) override;
};
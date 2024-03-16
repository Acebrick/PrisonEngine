#pragma once
#include "GameObjects/Character.h"

class Player : public Character
{
public:
	Player();

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* gameInput) override;

	virtual void OnUpdate(float deltaTime) override;

	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

private:

};
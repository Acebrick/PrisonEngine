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

	// Change the engine effect animations
	void SetPoweredEngine(bool powered);

	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;
};
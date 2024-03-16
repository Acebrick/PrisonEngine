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

	void ActivateBoost(bool boosting);

	// Store the different effects for the engine effects
	TArray<Sprite*> m_EngineEffects;

	// Store the ship damage levels
	TArray<Sprite*> m_ShipHealth;

private:

};
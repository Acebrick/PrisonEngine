#pragma once
#include "GameObjects/Character.h"

class Enemy : public Character
{
public:
	Enemy();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;

private:
	

};

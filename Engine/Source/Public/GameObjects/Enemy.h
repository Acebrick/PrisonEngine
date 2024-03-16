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
	// Direction the enemy is moving
	Vector2 direction;

	bool m_FollowingPlayer = false;
};

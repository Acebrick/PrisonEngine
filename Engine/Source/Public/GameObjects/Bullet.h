#pragma once
#include "Character.h"

class Bullet : public Character
{
public:
	Bullet();

	virtual void OnStart() override;

	virtual void OnProcessInput(Input* gameInput) override;

	virtual void OnUpdate(float deltaTime) override;

	void ShootBullet(Vector2 playerPos);

private:

};
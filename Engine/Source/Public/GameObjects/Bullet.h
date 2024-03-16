#pragma once
#include "Character.h"

class Bullet : public Character
{
public:
	Bullet();

	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;

	virtual void OnProcessInput(Input* gameInput) override;

private:
	Vector2 direction;

	void GetDirectionToShoot(Input* gameInput);

	// Stop millions of bullets instantiating while clicking/holding down mouse button
	bool canShoot = true;

	void ChargeGun();
};
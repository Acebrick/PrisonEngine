#pragma once
#include "PhysicsObject.h"

class Character : public PhysicsObject
{
public:
	Character();

	// Move the character in this direction based on the acceleration speed and max speed
	void AddMovementInput(Vector2 direction, float scale = 1.0f);

protected:
	// Main sprite that represents the character
	Sprite* m_MainSprite;

	// Speed the character will move to max speed
	float m_AccelerationSpeed;

	virtual void OnPostUpdate(float deltaTime) override;

	// The direction to move the character in
	Vector2 m_MoveDirection;

	void bounceOffWall();

private:

};
#pragma once
#include "SpriteObject.h"

class Input;

class PhysicsObject : public SpriteObject
{
public:
	PhysicsObject();

	// Add force to the object
	void AddForce(Vector2 direction, float force);

	// Function not done in lecture
	void movePlayerWithMouse(float xPos, float yPos, Vector2& direction, Input* gameInput);

protected:
	virtual void OnPostUpdate(float deltaTime) override;

	// Direction and speed of the physics object
	Vector2 m_Velocity;

	// Maximum velocity that we can travel
	float m_MaxSpeed;

	// How heavy the object is
	float m_Mass;

	// Constant wind force against the physics
	float m_Drag;

	// After stopped moving then slow down (brake speed)
	float m_Deceleration;

private:
	// The hidden force changing velocity
	Vector2 m_Acceleration;

	// Custom force that pushes our object in physics
	Vector2 m_AccelerationForce;

	// Previous velocity on the last tick
	Vector2 m_LastTickVelocity;
};
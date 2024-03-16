#include "GameObjects/PhysicsObject.h"
#include "Input.h" // Added for movement task in module 5
#include "Debug.h"

#define Super SpriteObject

void PhysicsObject::OnPostUpdate(float deltaTime)
{
	// The constant wind force against the object
	Vector2 dragForce = m_Velocity * -m_Drag;

	// Combined forces for the velocity
	// Acceleration force being a custom additive force
	Vector2 fullForce = dragForce + m_AccelerationForce;

	// Physics force algorithm F = ma : (a = F / m)
	m_Acceleration = fullForce / std::max(m_Mass, 0.00001f);
	
	// Apply acceleration and multiply it by time
	m_Velocity += m_Acceleration * deltaTime;

	// Cap the velocity at the maximum value (m_Velocity.Length() = Current speed/velocity)
	if (m_Velocity.Length() > m_MaxSpeed)
	{
		m_Velocity = Vector2::Normalised(m_Velocity) * m_MaxSpeed;
	}

	// The force that should stop the object faster
	Vector2 decelForce;

	// Set deceleration force only if we need to decelerate
	if (m_Velocity.Length() < m_LastTickVelocity.Length())
	{
		decelForce = m_Velocity * -m_Deceleration;
	}

	// Apply deceleration
	m_Velocity += decelForce * deltaTime;

	// The amount to move from the position based on time
	Vector2 timeVelocity = m_Velocity * deltaTime;

	// Move the object based on velocity
	SetPosition(GetTransform().position + timeVelocity);

	// Reset the push force (Vector2 initialises at 0)
	m_AccelerationForce = Vector2();

	// Update the last tick velocity
	m_LastTickVelocity = m_Velocity;
	
	// Runs the sprite stuff after physics has applied
	Super::OnPostUpdate(deltaTime);
}

PhysicsObject::PhysicsObject() : 
	m_Deceleration(0.0f), 
	m_Drag(1.0f), 
	m_Mass(1.0f), 
	m_MaxSpeed(600.0f) {}

void PhysicsObject::AddForce(Vector2 direction, float force) 
{
	m_AccelerationForce = direction * force;
}
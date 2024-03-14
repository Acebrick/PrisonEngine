#include "GameObjects/Character.h"
#include "Debug.h"
#define Super PhysicsObject

Character::Character() : m_MainSprite(nullptr), m_AccelerationSpeed(2000.0f) {}

void Character::AddMovementInput(Vector2 direction, float scale)
{
	// Increase our movement direction based on a direction and scale
	m_MoveDirection += direction.Normalise() * scale;
}

void Character::OnPostUpdate(float deltaTime)
{
	// If we have a movement direction set then move the object using physics 
	if (m_MoveDirection.Length() > 0.0f)
	{
		AddForce(m_MoveDirection, m_AccelerationSpeed);
	}
	
	// Reset move direction for the next frame
	m_MoveDirection = Vector2();

	Super::OnPostUpdate(deltaTime);
}

void Character::bounceOffWall()
{	
	// Check if the character has reached the window boundary
	if (this->GetTransform().position.x < 0 + 36)
	{
		EE_LOG("Character", "Player has reached the window boundary");
	}
}
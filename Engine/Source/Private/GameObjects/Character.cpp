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

void Character::bounceOffWall(Vector2& moveDirection, int spriteSize)
{
	// Check if the character has reached the window boundary
	if (GetTransform().position.x <= 0 + spriteSize) // Left side of screen
	{
		moveDirection.x = 1.0f;
		SetRotation(90.0f);
	}

	if (GetTransform().position.y >= 720 - spriteSize) // Bottom of screen
	{
		moveDirection.y = -1.0f;
		SetRotation(0.0f);
	}

	if (GetTransform().position.x >= 1280 - spriteSize) // Right side of screen
	{
		moveDirection.x = -1.0f;
		SetRotation(270.0f);
	}

	if (GetTransform().position.y <= 0 + spriteSize) // Top of screen
	{
		moveDirection.y = 1.0f;
		SetRotation(180.0f);
	}
}


#include "GameObjects/Character.h"
#include "Debug.h"
#include "Game.h"

#define Super PhysicsObject

Character::Character() : m_MainSprite(nullptr), m_AccelerationSpeed(2000.0f), m_Player(nullptr) {}

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

	GetPlayerObject();

	EE_LOG("Character", "X: " << m_Player->GetTransform().position.x);

	Super::OnPostUpdate(deltaTime);
}

void Character::BounceOffWall(Vector2& moveDirection, int spriteSize)
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

void Character::GetPlayerObject()
{
	m_Player = Game::GetGame()->GetPlayer();
}

void Character::FollowPlayer()
{
	static Vector2 triangleSideLength; // Sides of hypothetical right angled triangle to get angles between player and enemy object

	// Angle closest to x axis from enemy
	static float angleOfX;

	// Angle closest to y axis from enemy
	static float angleOfY;

	// Percentages out of 100 these angles make up of 90 degrees
	static float xAnglePercent = 0;
	static float yAnglePercent = 0;

	// Get the length of the two sides (excluding the hypotenuse)
	triangleSideLength.x = m_Player->GetTransform().position.x - GetTransform().position.x;
	triangleSideLength.y = m_Player->GetTransform().position.y - GetTransform().position.y;

	// Convert any negative lengths to positive to allow for proper angle calculations
	if (triangleSideLength.x < 0)
	{
		triangleSideLength.x = -triangleSideLength.x;
	}
	if (triangleSideLength.y < 0)
	{
		triangleSideLength.y = -triangleSideLength.y;
	}

	// Calculate the angles closest to the enemy
	angleOfX = atan(triangleSideLength.y / triangleSideLength.x) / (3.14f / 180.0f);
	angleOfY = (90.0f - angleOfX);

	// Converted to be a percentage out of 100 that these angles make up of 90 degrees (in decimal format, so 1 = 100%)
	// Minused by 1 as angle value is at its lowest when mouse is positioned in desired movement direction, when it should closest to 1
	// This just switches the two and makes code easier to read when used as x is now used with x direction and y is used with y direction
	xAnglePercent = 1 - angleOfX / 90.0f;
	yAnglePercent = 1 - angleOfY / 90.0f;

	//Move the enemy in the direction of the player
	if (m_Player->GetTransform().position.x > GetTransform().position.x) // Go right
	{
		m_MoveDirection.x = 1.0f * xAnglePercent;
	}
	else // Go left
	{
		m_MoveDirection.x = -1.0f * xAnglePercent;
	}
	if (m_Player->GetTransform().position.y > GetTransform().position.y) // Go down
	{
		m_MoveDirection.y = 1.0f * yAnglePercent;
	}
	else // Go up
	{
		m_MoveDirection.y = -1.0f * yAnglePercent;
	}

	// Rotate the enemy based on the players position
	if (m_Player->GetTransform().position.x > GetTransform().position.x && m_Player->GetTransform().position.y < GetTransform().position.y) // Top right of circle/corner of enemy
	{
		this->SetRotation(angleOfY);
	}
	if (m_Player->GetTransform().position.x > GetTransform().position.x && m_Player->GetTransform().position.y > GetTransform().position.y) // Bottom right of circle/corner of enemy
	{
		this->SetRotation(angleOfX + 90);
	}
	if (m_Player->GetTransform().position.x < GetTransform().position.x && m_Player->GetTransform().position.y > GetTransform().position.y) // Bottom left of circle/corner of enemy
	{
		this->SetRotation(angleOfY + 180);
	}
	if (m_Player->GetTransform().position.x < GetTransform().position.x && m_Player->GetTransform().position.y < GetTransform().position.y) // Top left of circle/corner of enemy
	{
		this->SetRotation(angleOfX + 270);
	}

	// DEBUG VARIABLES
	//std::cout << "triangleSideLength.x: " << triangleSideLength.x << std::endl;
	//std::cout << "triangleSideLength.y: " << triangleSideLength.y << std::endl;
	//std::cout << "angleOfX: " << angleOfX << std::endl;
	//std::cout << "angleOfY: " << angleOfY << std::endl;
	//std::cout << "xAnglePercent: " << xAnglePercent << std::endl;
	//std::cout << "yAnglePercent: " << yAnglePercent << std::endl;
}


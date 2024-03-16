#include "GameObjects/Bullet.h"
#include "Input.h"
#include "Debug.h"
#include "Game.h"

#define Super Character
#define SIZE_BULLET 32

Bullet::Bullet()
{
	m_Mass = 0.0f;
	m_MaxSpeed = 500.0f;

	AnimationParams animParams;
	animParams.fps = 12.0f;
	animParams.maxFrames = 10;
	animParams.endFrame = 9;
	animParams.frameHeight = SIZE_BULLET;
	animParams.frameWidth = SIZE_BULLET;

	m_MainSprite = AddSprite(
		"Content/Sprites/MainShipWeapons/PNGs/Main ship weapon - Projectile - Big Space Gun.png",
		&animParams
	);

	// Start hidden until player shoots
	m_MainSprite->SetActive(false);
}

void Bullet::OnStart()
{
	Super::OnStart();

	SetScale(1.5f);
}

void Bullet::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	if (canShoot)
	{
		AddMovementInput(direction);
	}
	
	BounceOffWall(direction, SIZE_BULLET);

	if (!canShoot)
	{
		this->ChargeGun();
	}
}

void Bullet::OnProcessInput(Input* gameInput)
{
	// Shoot bullet
	if (gameInput->IsMouseButtonDown(EE_MOUSE_LEFT) && m_Player != nullptr)
	{
		if (canShoot)
		{
			m_MainSprite->SetActive(true);

			// Reset bullet attributes
			m_Drag = 0.0f;
			m_MaxSpeed = 1000.0f;
			SetScale(1.0f);
			
			GetDirectionToShoot(gameInput);

			canShoot = false;
		}
	}
	else
	{
		canShoot = true;
	}
}

void Bullet::GetDirectionToShoot(Input* gameInput)
{
	static Vector2 triangleSideLength; // Sides of hypothetical right angled triangle to get angles between player and mouse

	// Angle closest to x axis from player
	static float angleOfX;

	// Angle closest to y axis from player
	static float angleOfY;

	// Percentages out of 100 these angles make up of 90 degrees
	static float xAnglePercent = 0;
	static float yAnglePercent = 0;

	// Get the length of the two sides (excluding the hypotenuse)
	triangleSideLength.x = m_Player->GetTransform().position.x - gameInput->GetMousePos().x;
	triangleSideLength.y = m_Player->GetTransform().position.y - gameInput->GetMousePos().y;

	// Convert any negative lengths to positive to allow for proper angle calculations
	if (triangleSideLength.x < 0)
	{
		triangleSideLength.x = -triangleSideLength.x;
	}
	if (triangleSideLength.y < 0)
	{
		triangleSideLength.y = -triangleSideLength.y;
	}

	// Calculate the angles closest to the player
	angleOfX = atan(triangleSideLength.y / triangleSideLength.x) / (3.14f / 180.0f);
	angleOfY = (90.0f - angleOfX);

	// Converted to be a percentage out of 100 that these angles make up of 90 degrees (in decimal format, so 1 = 100%)
	// Minused by 1 as angle value is at its lowest when mouse is positioned in desired movement direction, when it should closest to 1
	// This just switches the two and makes code easier to read when used as x is now used with x direction and y is used with y direction
	xAnglePercent = 1 - angleOfX / 90.0f;
	yAnglePercent = 1 - angleOfY / 90.0f;

	//Shoot the bullet in the direction of the mouse
	if (gameInput->GetMousePos().x > m_Player->GetTransform().position.x) // Go right
	{
		direction.x = 1.0f * xAnglePercent;
	}
	else // Go left
	{
		direction.x = -1.0f * xAnglePercent;
	}
	if (gameInput->GetMousePos().y > m_Player->GetTransform().position.y) // Go down
	{
		direction.y = 1.0f * yAnglePercent;
	}
	else // Go up
	{
		direction.y = -1.0f * yAnglePercent;
	}
}

void Bullet::ChargeGun()
{
	SetPosition(m_Player->GetTransform().position);
	SetScale(GetTransform().scale += 0.05f);
	m_Drag += 0.01f;
	m_MaxSpeed -= 0.40f;
}

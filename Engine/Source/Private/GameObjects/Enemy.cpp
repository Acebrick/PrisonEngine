#include "GameObjects/Enemy.h"
#include "Debug.h"
#include "GameObjects/Player.h"

#define Super Character

Enemy::Enemy()
{
	m_MaxSpeed = 500.0f;
	m_Drag = 0.0f;

	AnimationParams bulletParams;
	bulletParams.fps = 12.0f;
	bulletParams.maxFrames = 10;
	bulletParams.endFrame = 9;
	bulletParams.frameHeight = 32.0f;
	bulletParams.frameWidth = 32.0f;

	m_MainSprite = AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Very damaged.png"
	);
}

void Enemy::OnStart()
{
	Super::OnStart();

	static float positionX = 300.0f;
	positionX += 300.0f;

	EE_LOG("Enemy", positionX);

	// Start the enemy above the screen
	SetPosition({ positionX, 360.0f });

	// Flip it to look down
	SetRotation(180.0f);

	SetScale(2.0f);

	static Vector2 startHorizontal = { -1.0f, 2.0f };
	startHorizontal.x += 1.0f;
	startHorizontal.y -= 1.0f;
	direction = startHorizontal;
}

void Enemy::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	//EE_LOG("Enemy", "\nX: " << direction.x << "\nY: " << direction.y);

	AddMovementInput(direction);

	bounceOffWall(direction, 96);
}

//void Enemy::FollowPlayer(float xPos, float yPos, Vector2& playerPosition)
//{
//	static Vector2 triangleSideLength; // Sides of hypothetical right angled triangle to get angles
//
//	// Angle closest to x axis
//	static float angleOfX;
//
//	// Angle closest to y axis
//	static float angleOfY;
//
//	// Percentage out of 100 these angles make up of 90 degrees
//	static float xAnglePercent = 0;
//	static float yAnglePercent = 0;
//
//	// Get the length of the two sides excluding the hypotenuse
//	//triangleSideLength.x = gameInput->GetMousePos().x - xPos;
//	//triangleSideLength.y = gameInput->GetMousePos().y - yPos;
//
//	// Convert any negative lengths to positive to allow for proper angle calculations
//	if (triangleSideLength.x < 0)
//	{
//		triangleSideLength.x = -triangleSideLength.x;
//	}
//	if (triangleSideLength.y < 0)
//	{
//		triangleSideLength.y = -triangleSideLength.y;
//	}
//
//	// Calculate the angles closest to the player
//	angleOfX = atan(triangleSideLength.y / triangleSideLength.x) / (3.14f / 180.0f);
//	angleOfY = (90.0f - angleOfX);
//
//	// Converted to be a percentage out of 100 that these angles make up of 90 degrees (in decimal format, so 1 = 100%)
//	// Minused by 1 as angle value is at its lowest when mouse is positioned in desired movement direction
//	// This just reverses the two and makes code easier to read when used as x is now used with x movement and y is used with y movement
//	xAnglePercent = 1 - angleOfX / 90.0f;
//	yAnglePercent = 1 - angleOfY / 90.0f;
//
//	// Move the player in the direction of the mouse
//	if (gameInput->IsMouseButtonDown(EE_MOUSE_LEFT))
//	{
//		if (gameInput->GetMousePos().x > xPos) // Go right
//		{
//			direction.x += 1.0f * xAnglePercent;
//		}
//		else // Go left
//		{
//			direction.x += -1.0f * xAnglePercent;
//		}
//		if (gameInput->GetMousePos().y > yPos) // Go down
//		{
//			direction.y += 1.0f * yAnglePercent;
//		}
//		else // Go up
//		{
//			direction.y += -1.0f * yAnglePercent;
//		}
//	}
//
//	// Rotate the player based on the mouse position
//	if (gameInput->GetMousePos().x > xPos && gameInput->GetMousePos().y < yPos) // Top right of circle
//	{
//		this->SetRotation(angleOfY);
//	}
//	if (gameInput->GetMousePos().x > xPos && gameInput->GetMousePos().y > yPos) // Bottom right of circle
//	{
//		this->SetRotation(angleOfX + 90);
//	}
//	if (gameInput->GetMousePos().x < xPos && gameInput->GetMousePos().y > yPos) // Bottom left of circle
//	{
//		this->SetRotation(angleOfY + 180);
//	}
//	if (gameInput->GetMousePos().x < xPos && gameInput->GetMousePos().y < yPos) // Top left of circle
//	{
//		this->SetRotation(angleOfX + 270);
//	}
//
//	// DEBUG VARIABLES
//	//std::cout << "triangleSideLength.x: " << triangleSideLength.x << std::endl;
//	//std::cout << "triangleSideLength.y: " << triangleSideLength.y << std::endl;
//	//std::cout << "angleOfX: " << angleOfX << std::endl;
//	//std::cout << "angleOfY: " << angleOfY << std::endl;
//	//std::cout << "xAnglePercent: " << xAnglePercent << std::endl;
//	//std::cout << "yAnglePercent: " << yAnglePercent << std::endl;
//}
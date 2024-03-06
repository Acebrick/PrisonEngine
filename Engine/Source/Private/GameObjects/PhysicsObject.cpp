#include "GameObjects/PhysicsObject.h"
#include "Input.h"
#include "Debug.h"

void PhysicsObject::OnStart()
{
	SetPosition(Vector2(640.0f, 360.0f));
	SetScale({ 2.0f, 2.0f });

	AnimationParams animParams;
	animParams.fps = 24.0f;
	animParams.maxFrames = 10;
	animParams.endFrame = 9;
	animParams.frameHeight = 64;
	animParams.frameWidth = 64;

	m_Sprite = AddSprite("Content/Sprites/MainShip/Shields/PNGs/Main Ship - Shields - Invincibility Shield.png", &animParams);
}

void PhysicsObject::OnProcessInput(Input* gameInput)
{
	m_MovementDirection = 0.0f;

	// Move player with mouse
	//movePlayerWithMouse(GetTransform().position.x, GetTransform().position.y, m_MovementDirection, gameInput);

	// Move player with keyboard
	//if (gameInput->IsKeyDown(EE_KEY_W))
	//{
	//	m_MovementDirection.y += -1.0f;
	//}
	//if (gameInput->IsKeyDown(EE_KEY_S))
	//{
	//	m_MovementDirection.y += 1.0f;
	//}
	//if (gameInput->IsKeyDown(EE_KEY_A))
	//{
	//	m_MovementDirection.x += -1.0f;
	//}
	//if (gameInput->IsKeyDown(EE_KEY_D))
	//{
	//	m_MovementDirection.x += 1.0f;
	//}
}

void PhysicsObject::OnUpdate(float deltaTime)
{
	// Speed of movement
	m_Speed = 1000.0f * (float)deltaTime;

	// Update the position
	SetPosition(GetTransform().position += m_MovementDirection * m_Speed);
	

	if (m_Sprite != nullptr)
	{
		m_Sprite->Update(deltaTime);
	}
}

void PhysicsObject::movePlayerWithMouse(float xPos, float yPos, Vector2& direction, Input* gameInput)
{
	// FOLLOW MOUSE VARIABLES

	Vector2 mousePos = gameInput->GetMousePos(); // Maintain mouse position
	static Vector2 triangleSideLength; // Sides of hypothetical right angled triangle to get angles

	// Angle closest to horizontal/x axis
	static float angleOfX;

	// Angle closest to vertical/y axis
	static float angleOfY;

	// Percentage out of 100 these angles make up out of 90 degrees
	static float xAnglePercent = 0;
	static float yAnglePercent = 0;

	// Get the length of the two sides excluding the hypotenuse
	triangleSideLength.x = mousePos.x - xPos;
	triangleSideLength.y = mousePos.y - yPos;

	// Convert any negative lengths to positive to allow for proper angle calculations
	if (triangleSideLength.x < 0)
	{
		triangleSideLength.x = -triangleSideLength.x;
	}
	if (triangleSideLength.y < 0)
	{
		triangleSideLength.y = -triangleSideLength.y;
	}

	// Calculate the angle connecting the side parellel to the x axis and the hypotenuse (angle closest to player)
	angleOfX = atan(triangleSideLength.y / triangleSideLength.x) / (3.14f / 180.0f);
	angleOfY = (90.0f - angleOfX);

	// Converted to be a percentage out of 100 that these angles make up out of 90 degrees (in decimal format, so 1 = 100%)
	// Minused by 1 as angle distance is at its lowest when mouse is positioned in desired movement direction
	// This just reverses the two and makes code easier to read when used as x is now used with x movement and y is used with y movement
	xAnglePercent = 1 - angleOfX / 90.0f;
	yAnglePercent = 1 - angleOfY / 90.0f;

	// Move the player in the direction of the mouse
	if (gameInput->IsMouseButtonDown(EE_MOUSE_LEFT))
	{
		if (mousePos.x > xPos) // Go right
		{
			direction.x += 1.0f * xAnglePercent;
		}
		else // Go left
		{
			direction.x += -1.0f * xAnglePercent;
		}
		if (mousePos.y > yPos) // Go down
		{
			direction.y += 1.0f * yAnglePercent;
		}
		else // Go up
		{
			direction.y += -1.0f * yAnglePercent;
		}
	}

	// Rotate the player based on the mouse position
	if (mousePos.x > xPos && mousePos.y < yPos) // Top right of circle
	{
		this->SetRotation(angleOfY);
	}
	if (mousePos.x > xPos && mousePos.y > yPos) // Bottom right of circle
	{
		this->SetRotation(angleOfX + 90);
	}
	if (mousePos.x < xPos && mousePos.y > yPos) // Bottom left of circle
	{
		this->SetRotation(angleOfY + 180);
	}
	if (mousePos.x < xPos && mousePos.y < yPos) // Top left of circle
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

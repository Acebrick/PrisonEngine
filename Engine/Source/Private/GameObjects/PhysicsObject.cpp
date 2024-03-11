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

void PhysicsObject::movePlayerWithMouse(float xPos, float yPos, Vector2& direction, Input* gameInput)
{
	static Vector2 triangleSideLength; // Sides of hypothetical right angled triangle to get angles

	// Angle closest to x axis
	static float angleOfX;

	// Angle closest to y axis
	static float angleOfY;

	// Percentage out of 100 these angles make up of 90 degrees
	static float xAnglePercent = 0;
	static float yAnglePercent = 0;

	// Get the length of the two sides excluding the hypotenuse
	triangleSideLength.x = gameInput->GetMousePos().x - xPos;
	triangleSideLength.y = gameInput->GetMousePos().y - yPos;

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
	// Minused by 1 as angle value is at its lowest when mouse is positioned in desired movement direction
	// This just reverses the two and makes code easier to read when used as x is now used with x movement and y is used with y movement
	xAnglePercent = 1 - angleOfX / 90.0f;
	yAnglePercent = 1 - angleOfY / 90.0f;

	// Move the player in the direction of the mouse
	if (gameInput->IsMouseButtonDown(EE_MOUSE_LEFT))
	{
		if (gameInput->GetMousePos().x > xPos) // Go right
		{
			direction.x += 1.0f * xAnglePercent;
		}
		else // Go left
		{
			direction.x += -1.0f * xAnglePercent;
		}
		if (gameInput->GetMousePos().y > yPos) // Go down
		{
			direction.y += 1.0f * yAnglePercent;
		}
		else // Go up
		{
			direction.y += -1.0f * yAnglePercent;
		}
	}

	// Rotate the player based on the mouse position
	if (gameInput->GetMousePos().x > xPos && gameInput->GetMousePos().y < yPos) // Top right of circle
	{
		this->SetRotation(angleOfY);
	}
	if (gameInput->GetMousePos().x > xPos && gameInput->GetMousePos().y > yPos) // Bottom right of circle
	{
		this->SetRotation(angleOfX + 90);
	}
	if (gameInput->GetMousePos().x < xPos && gameInput->GetMousePos().y > yPos) // Bottom left of circle
	{
		this->SetRotation(angleOfY + 180);
	}
	if (gameInput->GetMousePos().x < xPos && gameInput->GetMousePos().y < yPos) // Top left of circle
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

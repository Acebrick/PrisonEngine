#include "GameObjects/PhysicsObject.h"

void PhysicsObject::OnStart()
{
	SetPosition(Vector2(640.0f, 360.0f));

	AnimationParams animParams;
	animParams.fps = 0.0f;
	animParams.maxFrames = 5;
	animParams.endFrame = 4;
	animParams.frameHeight = 48;
	animParams.frameWidth = 48;

	m_Sprite = AddSprite("Content/Sprites/MainShip/Shields/PNGs/Main Ship - Shields - Invincibility Shield.png", &animParams);
}

void PhysicsObject::OnProcessInput(Input* gameInput)
{
	// Make this object move
}

void PhysicsObject::OnUpdate(float deltaTime)
{
	if (m_Sprite != nullptr)
	{
		m_Sprite->Update(deltaTime);
	}
}

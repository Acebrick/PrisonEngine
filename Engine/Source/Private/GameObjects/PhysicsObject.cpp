#include "GameObjects/PhysicsObject.h"

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
	// Make this object move
}

void PhysicsObject::OnUpdate(float deltaTime)
{
	if (m_Sprite != nullptr)
	{
		m_Sprite->Update(deltaTime);
	}
}

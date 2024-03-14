#include "GameObjects/Enemy.h"

#define Super Character

#define SCALE 3.0f
#define SIZE (48.0f * SCALE)
#define HALF_SIZE (SIZE / 2.0f) 

Enemy::Enemy()
{
	m_MaxSpeed = 100.0f;

	m_MainSprite = AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Very damaged.png"
	);
}

void Enemy::OnStart()
{
	Super::OnStart();

	// Start the enemy above the screen
	SetPosition({ 640.0f, -HALF_SIZE });

	// Flip it to look down
	SetRotation(180.0f);

	SetScale(SCALE);
}

void Enemy::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	AddMovementInput(Vector2(0.0f, 1.0f));

	if (GetTransform().position.y - HALF_SIZE > 720.0f)
	{
		SetPosition({ 640.0f, -HALF_SIZE });
	}
}



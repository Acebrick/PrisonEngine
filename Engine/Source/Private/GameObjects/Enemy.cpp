#include "GameObjects/Enemy.h"
#include "Debug.h"
#include "GameObjects/Player.h"

#define Super Character
#define SIZE_ENEMY 32

Enemy::Enemy()
{
	m_MaxSpeed = 500.0f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams bulletParams;
	bulletParams.fps = 12.0f;
	bulletParams.maxFrames = 10;
	bulletParams.endFrame = 9;
	bulletParams.frameHeight = SIZE_ENEMY;
	bulletParams.frameWidth = SIZE_ENEMY;

	m_MainSprite = AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Very damaged.png"
	);
}

void Enemy::OnStart()
{
	Super::OnStart();

	static float positionX = 300.0f;
	positionX += 300.0f;

	// Start the enemy above the screen
	SetPosition({ positionX, 360.0f });

	// Flip it to look down
	SetRotation(180.0f);

	SetScale(2.0f);

	static Vector2 startDirection = { -1.0f, 2.0f };

	// Move enemy up and down first instantiation and then left and right the second instantiation
	startDirection.x += 1.0f;
	startDirection.y -= 1.0f;
	direction = startDirection;

	// Third instantiation have enemy follow/chase the player
	if (startDirection.x == 2.0f)
	{
		m_FollowingPlayer = true;
	}
}

void Enemy::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	AddMovementInput(direction);

	BounceOffWall(direction, SIZE_ENEMY * 2);

	if (m_FollowingPlayer && m_Player != nullptr)
	{
		FollowPlayer();
	}
}
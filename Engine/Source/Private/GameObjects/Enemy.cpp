#include "GameObjects/Enemy.h"
#include "Debug.h"
#include "GameObjects/Player.h"

#define Super Character
#define SIZE_ENEMY 32

#define DAMAGE_SLIGHT 0
#define DAMAGE_VERY 1

#define WEAPON_ZAPPER 0
#define WEAPON_ROCKETS 1	

Enemy::Enemy()
{
	m_MaxSpeed = 500.0f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams zapperAnim;
	zapperAnim.fps = 20.0f;
	zapperAnim.maxFrames = 14;
	zapperAnim.endFrame = 13;
	zapperAnim.frameHeight = 48.0f;
	zapperAnim.frameWidth = 48.0f;

	AnimationParams rocketAnim;
	rocketAnim.fps = 20.0f;
	rocketAnim.maxFrames = 16;
	rocketAnim.endFrame = 15;
	rocketAnim.frameHeight = 48.0f;
	rocketAnim.frameWidth = 48.0f;

	// Enemy weapon sprites
	m_EnemyWeapons.push_back(AddSprite(
		"Content/Sprites/MainShip/Weapons/PNGs/Main Ship - Weapons - Zapper.png",
		&zapperAnim
	));

	m_EnemyWeapons.push_back(AddSprite(
		"Content/Sprites/MainShip/Weapons/PNGs/Main Ship - Weapons - Rockets.png",
		&rocketAnim
	));

	// Enemy ship sprites
	m_ShipTypes.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Slight damage.png"
	));

	m_ShipTypes.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Very damaged.png"
	));

	// Hide initially and only turn on to selected ships
	if (m_EnemyWeapons[WEAPON_ZAPPER] != nullptr)
	{
		m_EnemyWeapons[WEAPON_ZAPPER]->SetActive(false);
	}
	if (m_ShipTypes[DAMAGE_VERY] != nullptr)
	{
		m_ShipTypes[DAMAGE_VERY]->SetActive(false);
	}
}

void Enemy::OnStart()
{
	Super::OnStart();

	static float positionX = 220.0f;
	positionX += 300.0f;

	// Start the enemy above the screen
	SetPosition({ positionX, 100.0f });

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
		m_MaxSpeed = 450.0f;
		m_EnemyWeapons[WEAPON_ROCKETS]->SetActive(false);
		m_EnemyWeapons[WEAPON_ZAPPER]->SetActive(true);
		m_ShipTypes[DAMAGE_SLIGHT]->SetActive(false);
		m_ShipTypes[DAMAGE_VERY]->SetActive(true);
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
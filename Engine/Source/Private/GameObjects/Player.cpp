#include "GameObjects/Player.h"
#include "Input.h"
#include "Debug.h"
#include "GameObjects/Bullet.h"

// TEST
#include "Game.h"

#define Super Character

#define ENGINE_NORMAL 0
#define ENGINE_BOOST 1
#define SIZE_PLAYER 64

#define SHIP_BOOSTING 2

Player::Player()
{
	m_MaxSpeed = 500.0f;
	m_Deceleration = 2.5f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams shipAnim;
	shipAnim.fps = 24.0f;
	shipAnim.maxFrames = 10;
	shipAnim.endFrame = 9;
	shipAnim.frameHeight = SIZE_PLAYER;
	shipAnim.frameWidth = SIZE_PLAYER;

	 //Add the high damaged ship sprite
	m_ShipTypes.push_back(AddSprite(
		"Content/Sprites/MainShip/Engines/PNGs/Main Ship - Engines - Supercharged Engine.png"));

	m_ShipTypes.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Full health.png"));

	m_ShipTypes.push_back(AddSprite(
		"Content/Sprites/MainShip/Shields/PNGs/Main Ship - Shields - Invincibility Shield.png",
		&shipAnim));

	AnimationParams engineAnim;
	engineAnim.fps = 24.0f;
	engineAnim.maxFrames = 4;
	engineAnim.endFrame = 3;
	engineAnim.frameHeight = 48.0f;
	engineAnim.frameWidth = 48.0f;	

	// Add the idle engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/MainShip/Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&engineAnim
	));

	// Add the powered engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/MainShip/Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&engineAnim
	));

	

	// Hide the engine effect sprites by default
	if (m_EngineEffects.size() > 1 && m_EngineEffects[ENGINE_BOOST] != nullptr)
	{
		m_EngineEffects[ENGINE_BOOST]->SetActive(false);
	}

	if (m_ShipTypes[SHIP_BOOSTING] != nullptr)
	{
		m_ShipTypes[SHIP_BOOSTING]->SetActive(false);
	}
}

void Player::OnStart()
{
	Super::OnStart();

	SetPosition({ 640.0f, 360.0f });
	SetScale(2.0f);
}

void Player::OnProcessInput(Input* gameInput)
{
	Super::OnProcessInput(gameInput);
	
	// Move the player
	if (gameInput->IsKeyDown(EE_KEY_W))
	{
		AddMovementInput(Vector2(0.0f, -1.0f));
		SetRotation(0);
	}
	if (gameInput->IsKeyDown(EE_KEY_S))
	{
		AddMovementInput(Vector2(0.0f, 1.0f));
		SetRotation(180);
	}
	if (gameInput->IsKeyDown(EE_KEY_A))
	{
		AddMovementInput(Vector2(-1.0f, 0.0f));
		SetRotation(270);
	}
	if (gameInput->IsKeyDown(EE_KEY_D))
	{
		AddMovementInput(Vector2(1.0f, 0.0f));
		SetRotation(90);
	}

	// Use boost
	if (gameInput->IsKeyDown(EE_KEY_LSHIFT))
	{
		ActivateBoost(true);
	}
	else
	{
		ActivateBoost(false);
	}
}

void Player::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	BounceOffWall(m_MoveDirection, SIZE_PLAYER);
}

void Player::ActivateBoost(bool boosting)
{
	// Turn on normal engines when moving
	if (m_MoveDirection.Length() > 0.0f)
	{
		m_EngineEffects[ENGINE_NORMAL]->SetActive(true);
	}
	// Deactivate engines when not moving
	else
	{
		m_EngineEffects[ENGINE_NORMAL]->SetActive(false);
	}

	// Turn on booster engines when boosting and increase speed
	if (boosting)
	{
		m_MaxSpeed = 1000.0f;
		m_EngineEffects[ENGINE_NORMAL]->SetActive(false);
		m_EngineEffects[ENGINE_BOOST]->SetActive(true);
		m_ShipTypes[SHIP_BOOSTING]->SetActive(true);
	}
	// Turn off booster engines when boosting and decrease speed
	else
	{
		m_MaxSpeed = 500.0f;
		m_EngineEffects[ENGINE_BOOST]->SetActive(false);
		m_ShipTypes[SHIP_BOOSTING]->SetActive(false);
	}
}

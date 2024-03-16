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

#define DAMAGE_NONE 0
#define DAMAGE_LOW 1
#define DAMAGE_MED 2
#define DAMAGE_HIGH 3


Player::Player()
{
	m_MaxSpeed = 500.0f;
	m_Deceleration = 2.5f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams shipAnimParams;
	shipAnimParams.fps = 24.0f;
	shipAnimParams.maxFrames = 10;
	shipAnimParams.endFrame = 9;
	shipAnimParams.frameHeight = SIZE_PLAYER;
	shipAnimParams.frameWidth = SIZE_PLAYER;

	// Add the full health ship sprite
	m_ShipHealth.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Full health.png"));

	// Add the low damaged ship sprite
	m_ShipHealth.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Slight damage.png"));

	// Add the medium damaged ship sprite
	m_ShipHealth.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Damaged.png"));

	// Add the high damaged ship sprite
	m_ShipHealth.push_back(AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Very damaged.png"));

	AnimationParams animParams;
	animParams.fps = 24.0f;
	animParams.maxFrames = 4;
	animParams.endFrame = 3;
	animParams.frameHeight = 48.0f;
	animParams.frameWidth = 48.0f;	

	// Add the idle engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/MainShip/Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Idle.png",
		&animParams
	));

	// Add the powered engine effect
	m_EngineEffects.push_back(AddSprite(
		"Content/Sprites/MainShip/Engine Effects/PNGs/Main Ship - Engines - Supercharged Engine - Powering.png",
		&animParams
	));

	// Hide the engine effect sprites by default
	if (m_EngineEffects.size() > 1 && m_EngineEffects[ENGINE_BOOST] != nullptr)
	{
		m_EngineEffects[ENGINE_BOOST]->SetActive(false);
	}

	// Hide the ship sprites by default
	for (int i = 1; i < m_ShipHealth.size(); i++)
	{
		if (m_ShipHealth[i] != nullptr)
		{
			m_ShipHealth[i]->SetActive(false);
		}
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
	}
	// Turn off booster engines when boosting and decrease speed
	else
	{
		m_MaxSpeed = 500.0f;
		m_EngineEffects[ENGINE_BOOST]->SetActive(false);
	}
}

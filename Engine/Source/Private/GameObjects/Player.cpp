#include "GameObjects/Player.h"
#include "Input.h"
#include "Debug.h"
#include "GameObjects/Bullet.h"

// TEST
#include "Game.h"

#define Super Character

#define ENGINE_IDLE 0
#define ENGINE_POWERED 1
#define PLAYER_WIDTH 64


Player::Player()
{
	m_IsPlayer = true;
	m_MaxSpeed = 500.0f;
	m_Deceleration = 2.5f;
	m_AccelerationSpeed = 5000.0f;

	AnimationParams shipAnimParams;
	shipAnimParams.fps = 24.0f;
	shipAnimParams.maxFrames = 10;
	shipAnimParams.endFrame = 9;
	shipAnimParams.frameHeight = 64.0f;
	shipAnimParams.frameWidth = 64.0f;

	// Add the ship base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/MainShip/Shields/PNGs/Main Ship - Shields - Invincibility Shield.png",
		&shipAnimParams);

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

	// Hide the sprite by default
	if (m_EngineEffects.size() > 1 && m_EngineEffects[ENGINE_POWERED] != nullptr)
	{
		m_EngineEffects[ENGINE_POWERED]->SetActive(false);
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

	// Boost
	if (gameInput->IsKeyDown(EE_KEY_LSHIFT))
	{
		m_MaxSpeed = 1000.0f;
		m_EngineEffects[ENGINE_IDLE]->SetActive(false);
		m_EngineEffects[ENGINE_POWERED]->SetActive(true);
	}
	else
	{
		m_MaxSpeed = 500.0f;
		m_EngineEffects[ENGINE_POWERED]->SetActive(false);
	}
}

void Player::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	if (m_MoveDirection.Length() > 0.0f)
	{
		m_EngineEffects[ENGINE_IDLE]->SetActive(true);
	}
	else
	{
		m_EngineEffects[ENGINE_IDLE]->SetActive(false);
	}

	bounceOffWall(m_MoveDirection, PLAYER_WIDTH);
}

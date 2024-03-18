#include "GameObjects/Player.h"
#include "Input.h"
#include "GameObjects/Enemy.h"

#define Super Character

#define ENGINE_IDLE 0
#define ENGINE_POWERED 1
#define SCALE 3.0f
#define SCALE_BOUNDS (SCALE * 0.65f)

Player::Player()
{
	m_MaxSpeed = 600.0f;
	m_Deceleration = 5.0f;
	m_AccelerationSpeed = 5000.0f;

	// Add engine sprite
	AddSprite(
		"Content/Sprites/MainShip/Engines/PNGs/Main Ship - Engines - Supercharged Engine.png"
	);

	// Add the ship base sprite
	m_MainSprite = AddSprite(
		"Content/Sprites/MainShip/Bases/PNGs/Main Ship - Base - Full health.png");

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

	Bounds* playerBounds = AddBounds( {640.0f, 360.0f }, 48.0f * SCALE_BOUNDS);
	playerBounds->m_OriginOffset = -24.0f * SCALE_BOUNDS;
}

void Player::OnStart()
{
	Super::OnStart();

	SetPosition({ 640.0f, 360.0f });
	SetScale(SCALE);
}

void Player::OnProcessInput(Input* gameInput)
{
	Super::OnProcessInput(gameInput);
	
	if (gameInput->IsKeyDown(EE_KEY_W))
	{
		AddMovementInput(Vector2(0.0f, -1.0f));
	}
	if (gameInput->IsKeyDown(EE_KEY_S))
	{
		AddMovementInput(Vector2(0.0f, 1.0f));
	}
	if (gameInput->IsKeyDown(EE_KEY_A))
	{
		AddMovementInput(Vector2(-1.0f, 0.0f));
	}
	if (gameInput->IsKeyDown(EE_KEY_D))
	{
		AddMovementInput(Vector2(1.0f, 0.0f));
	}

}

void Player::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	if (m_MoveDirection.Length() > 0.0f)
	{
		SetPoweredEngine(true);		
	}
	else
	{
		SetPoweredEngine(false);
	}
}

void Player::OnOverlapEnter(Bounds* overlapBounds, Bounds* hitBounds)
{
	// Destroy by tag
	//if (overlapBounds->m_Tag == "ENEMY")
	//{
	//	
	//}

	// Destroy by object type detection
	//if (dynamic_cast<Enemy*>(overlapBounds->GetOwner()))
	//{
	//	overlapBounds->GetOwner()->DestroyObject();
	//}
	//
}


void Player::SetPoweredEngine(bool powered)
{
	if (m_EngineEffects.size() > 1)
	{
		if (m_EngineEffects[ENGINE_IDLE] != nullptr || m_EngineEffects[ENGINE_POWERED] != nullptr)
		{
			m_EngineEffects[ENGINE_IDLE]->SetActive(!powered);
			m_EngineEffects[ENGINE_POWERED]->SetActive(powered);
		}
	}
}

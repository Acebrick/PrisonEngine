#include "GameObjects/Bullet.h"
#include "Input.h"
#include "Game.h"

#define Super Character

Bullet::Bullet()
{
	m_Mass = 0.0f;
	m_MaxSpeed = 500.0f;

	AnimationParams animParams;
	animParams.fps = 12.0f;
	animParams.maxFrames = 10;
	animParams.endFrame = 9;
	animParams.frameHeight = 32.0f;
	animParams.frameWidth = 32.0f;

	m_MainSprite = AddSprite(
		"Content/Sprites/MainShipWeapons/PNGs/Main ship weapon - Projectile - Big Space Gun.png",
		&animParams
	);
}

void Bullet::OnStart()
{
	Super::OnStart();

	SetPosition({ 100.0f, 500.0f });
	
	SetScale(2.0f);

	m_MoveDirection = { 0.3f, 0.7f };
}

void Bullet::OnProcessInput(Input* gameInput)
{
	Super::OnProcessInput(gameInput);
	

}

void Bullet::OnUpdate(float deltaTime)
{
	Super::OnUpdate(deltaTime);

	static Vector2 direction({ 0.3f, 0.7f });

	AddMovementInput(direction);

	bounceOffWall(direction, 32);
}

void Bullet::ShootBullet(Vector2 playerPos)
{

}

#include "Graphics/Animation.h"
#include "Game.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include <windows.h>


Animation::Animation()
{
	m_TextureRef = nullptr;
	m_AnimParams = nullptr;
	m_CurrentFrame = 0;
	m_FrameTimer = 0.0f;
}

Animation::~Animation()
{
	if (m_AnimParams != nullptr)
	{
		delete m_AnimParams;
	}

	if (m_TextureRef != nullptr)
	{
		Game::GetGame()->DestroyTexture(m_TextureRef);
	}
}

bool Animation::CreateAnimation(const char* pathToFile, AnimationParams* params)
{
	m_TextureRef = Game::GetGame()->ImportTexture(pathToFile);

	// If the import failed
	if (m_TextureRef == nullptr)
	{
		EE_LOG("Animation", "Animation failed to import texture: " << pathToFile);
		return false;
	}

	// Set the parameters
	m_AnimParams = params;

	// If animation parameters were set
	if (m_AnimParams != nullptr)
	{
		m_CurrentFrame = m_AnimParams->startFrame;

		// Update the clip to start on the first frame
		m_TextureRef->SetClip(
		m_AnimParams->frameWidth * m_CurrentFrame, 
			0,
			m_AnimParams->frameWidth, 
			m_AnimParams->frameHeight, 0);
	}

	return true;
}

void Animation::Update(float deltaTime)
{
	if (m_AnimParams == nullptr || m_AnimParams->fps == 0.0f)
	{
		return;
	}

	// Increase the frame timer each frame to get time passed
	m_FrameTimer += deltaTime;

	// Check if the frame timer has reached the time to update to the next frame
	if (m_FrameTimer >= 1.0f / m_AnimParams->fps)
	{
		m_CurrentFrame++;

		if (m_CurrentFrame > m_AnimParams->endFrame)
		{
			m_CurrentFrame = 0;
		}

		// Update the clip to start on the next frame
		m_TextureRef->SetClip(
			m_AnimParams->frameWidth * m_CurrentFrame,
			0,
			m_AnimParams->frameWidth, 
			m_AnimParams->frameHeight, 0);

		// Reset the timer so we can go to the next frame
		m_FrameTimer = 0.0f;
	}
}

void Animation::SetPosition(int x, int y)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_PosX = x;
	m_TextureRef->m_PosY = y;
}

void Animation::SetRotation(float angle)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_Angle = angle;
}

void Animation::SetScale(float scale)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_Scale = scale;
}

void Animation::GunnerRunning(Animation* gunner, float deltaTime)
{
	// Turn around and run other way when right side of screen is reached
	if (gunner->m_TextureRef->m_PosX >= 950.0f)
	{
		gunner->moveSpeed = -400;
		gunner->m_TextureRef->imageFlipped = true;
	}
	// Turn around and run other way when left side of screen is reached
	if (gunner->m_TextureRef->m_PosX <= 50.0f)
	{
		gunner->moveSpeed = 400;
		gunner->m_TextureRef->imageFlipped = false;
	}

	// Move the sprite
	gunner->m_TextureRef->m_PosX += gunner->moveSpeed * deltaTime;
}

bool Animation::JetpackGunner(Animation* JetpackGunner, Animation* jetpackEffect, Animation* bullet, Animation* blackGunner, Animation* muzzleFlash, float deltaTime)
{
	// Start character flipped to face towards other space gunners
	JetpackGunner->m_TextureRef->imageFlipped = true;

	static int jetpackSpeed = -250;

	// Ascend when reaching the bottom of the screen
	if (JetpackGunner->m_TextureRef->m_PosY >= 680.0f)
	{
		jetpackSpeed = -250;
		// Restart jetpack effect when ascending
		jetpackEffect->SetScale(1.5f);
		
	} 
	// Descend when reaching the top of the screen
	if (JetpackGunner->m_TextureRef->m_PosY <= 50.0f)
	{
		jetpackSpeed = 500;

		// Stop jetpack effect when falling
		jetpackEffect->SetScale(0.0f);
	}
	
	// Lock the jetpack effect to the space gunner
	jetpackEffect->SetPosition(JetpackGunner->m_TextureRef->m_PosX + 5, JetpackGunner->m_TextureRef->m_PosY + 23);

	// Move character sprite
	JetpackGunner->m_TextureRef->m_PosY += jetpackSpeed * deltaTime;

	static bool killConfirmed = false;

	 // Enemy has been killed
	if (ShootBullet(bullet, JetpackGunner, blackGunner, muzzleFlash, deltaTime))
	{
		return true;
	}
	
	return false;
}

bool Animation::ShootBullet(Animation* bullet, Animation* JetpackGunner, Animation* blackGunner, Animation* muzzleFlash, float deltaTime)
{
	float bulletSpeed = -800.0f;

	// Only set position to character if a shot is taking place
	if (JetpackGunner->m_TextureRef->m_PosY < 60)
	{
		// Position and scale of muzzle flash
		muzzleFlash->SetPosition(JetpackGunner->m_TextureRef->m_PosX - 50, JetpackGunner->m_TextureRef->m_PosY);
		muzzleFlash->SetScale(3.0f); 
		// Starting position and scale of bullet
		bullet->SetPosition(JetpackGunner->m_TextureRef->m_PosX - 50, JetpackGunner->m_TextureRef->m_PosY);
		bullet->SetScale(1.0f);
	}

	// Move the bullet
	bullet->m_TextureRef->m_PosX += bulletSpeed * deltaTime;

	// Hide muzzle flash
	if (bullet->m_TextureRef->m_PosX < JetpackGunner->m_TextureRef->m_PosX - 100)
	{
		muzzleFlash->SetScale(0);
	}

	// Detect collision with black gunner
	if (bullet->m_TextureRef->m_PosX <= blackGunner->m_TextureRef->m_PosX &&
		bullet->m_TextureRef->m_PosY >= blackGunner->m_TextureRef->m_PosY - 48 && bullet->m_TextureRef->m_PosY <= blackGunner->m_TextureRef->m_PosY + 48
		&& blackGunner->m_TextureRef->GetPath() != "Content/Sprites/SpaceGunner/CharacterSprites/Black/Gunner_Black_Death.png")
	{		
		bullet->SetScale(0.0f);
		return true;
	}
	return false;
}

bool Animation::GunnerDead(Animation* character, Animation* explosion)
{
	static bool textureImported = false;

	// Only import texture if it has not yet been imported
	if (!textureImported)
	{
		AnimationParams GunnerDead;
		character->AnimTypeDefinitions(5, GunnerDead);
		character->m_TextureRef->ImportTexture("Content/Sprites/SpaceGunner/CharacterSprites/Black/Gunner_Black_Death.png");
		explosion->SetPosition(character->m_TextureRef->m_PosX, character->m_TextureRef->m_PosY);
		explosion->m_CurrentFrame = 0;

		textureImported = true;
	}

	// Stop animating explosion when last frame is reached
	if (explosion->m_CurrentFrame >= explosion->m_AnimParams->endFrame)
	{
		explosion->SetScale(0.0f);
	}

	// Force death animation to play only once
	if (character->m_CurrentFrame == character->m_AnimParams->endFrame)
	{
		return true;
	}
	return false;
}

void Animation::DodgeSaw(Animation* saw, Animation* redGunner)
{
	static bool isDodgingSaw = false;

	// Dodge/crouch the saw when it's in range
	if (saw->m_TextureRef->m_PosX >= redGunner->m_TextureRef->m_PosX - 150 &&
		saw->m_TextureRef->m_PosX <= redGunner->m_TextureRef->m_PosX + 150)
	{
		isDodgingSaw = true;

		if (redGunner->m_CurrentFrame == redGunner->m_AnimParams->startFrame)
		{
			// Start crouch animation
			redGunner->m_AnimParams->fps = 6.0f;
		}

		// Maintain crouched position until saw has passed
		if (redGunner->m_CurrentFrame == redGunner->m_AnimParams->endFrame)
		{
			redGunner->m_CurrentFrame = redGunner->m_AnimParams->endFrame;
			redGunner->m_AnimParams->fps = 0.0f;
		}
	}
	else
	{
		isDodgingSaw = false;
	}

	if (!isDodgingSaw && redGunner->m_CurrentFrame == redGunner->m_AnimParams->endFrame)
	{
		// Return gunner to standing position
		redGunner->m_AnimParams->fps = 6.0f;
	}
	else if (!isDodgingSaw && redGunner->m_CurrentFrame == redGunner->m_AnimParams->startFrame)
	{
		// Stop crouch animation from looping
		redGunner->m_AnimParams->fps = 0.0f;
	}
}

void Animation::AnimTypeDefinitions(int animType, AnimationParams& anim)
{
	switch (animType) {
	case 0: // Gunner idle
		anim.fps = 12.0f;
		anim.maxFrames = 5;
		anim.endFrame = 4;
		anim.frameHeight = 48;
		anim.frameWidth = 48;
		break;
	case 1: // Gunner run
		anim.fps = 6.0f;
		anim.maxFrames = 6;
		anim.endFrame = 5;
		anim.frameHeight = 48;
		anim.frameWidth = 48;
		break;
	case 2: // Gunner jumping/flying
		anim.fps = 6.0f;
		anim.maxFrames = 2;
		anim.endFrame = 1;
		anim.frameHeight = 48;
		anim.frameWidth = 48;
		break;
	case 3: // Jetback boots effect
		anim.fps = 6.0f;
		anim.maxFrames = 4;
		anim.endFrame = 3;
		anim.frameHeight = 48;
		anim.frameWidth = 48;
		break;
	case 4: // Gunner crouch
		anim.fps = 0.0f;
		anim.maxFrames = 3;
		anim.endFrame = 2;
		anim.frameHeight = 48;
		anim.frameWidth = 48;
		break;
	case 5: // Gunner death
		anim.fps = 2.0f;
		anim.maxFrames = 8;
		anim.endFrame = 7;
		anim.frameHeight = 48;
		anim.frameWidth = 48;
		break;
	case 6: // Bullets
		anim.fps = 12.0f;
		anim.maxFrames = 10;
		anim.endFrame = 9;
		anim.frameHeight = 32;
		anim.frameWidth = 32;
		break;
	case 7: // Explosion
		anim.fps = 12.0f;
		anim.maxFrames = 8;
		anim.endFrame = 7;
		anim.frameHeight = 32;
		anim.frameWidth = 32;
		break;
	case 8: // Saw trap
		anim.fps = 9.0f;
		anim.maxFrames = 16;
		anim.endFrame = 15;
		anim.frameHeight = 64;
		anim.frameWidth = 64;
		break;
	case 9: // Lightning trap
		anim.fps = 12.0f;
		anim.maxFrames = 22;
		anim.endFrame = 21;
		anim.frameHeight = 96;
		anim.frameWidth = 96;
		break;
	case 10: // Toxic trap
		anim.fps = 12.0f;
		anim.maxFrames = 40;
		anim.endFrame = 39;
		anim.frameHeight = 64;
		anim.frameWidth = 96;
		break;
	default:
		break;
	};
}

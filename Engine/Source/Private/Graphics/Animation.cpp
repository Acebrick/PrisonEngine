#include "Graphics/Animation.h"
#include "Game.h"
#include "Debug.h"
#include "Graphics/Texture.h"

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
	m_AnimParams = new AnimationParams();
	m_AnimParams->endFrame = params->endFrame;
	m_AnimParams->fps = params->fps;
	m_AnimParams->frameHeight = params->frameHeight;
	m_AnimParams->frameWidth = params->frameWidth;
	m_AnimParams->maxFrames = params->maxFrames;
	m_AnimParams->startFrame = params->startFrame;

	// If animation parameters were set
	if (m_AnimParams != nullptr)
	{
		m_CurrentFrame = m_AnimParams->startFrame;

		// Update the clip to start on the first frame
		m_TextureRef->SetClip(
		m_AnimParams->frameWidth * m_CurrentFrame, 
			0,
			m_AnimParams->frameWidth, 
			m_AnimParams->frameHeight);
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
			m_AnimParams->frameHeight);

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

void Animation::SetScale(float x, float y)
{
	if (m_TextureRef == nullptr)
	{
		return;
	}

	m_TextureRef->m_ScaleX = x;
	m_TextureRef->m_ScaleY = y;
}

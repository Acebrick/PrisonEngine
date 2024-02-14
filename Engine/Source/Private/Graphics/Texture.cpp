#include "Graphics/Texture.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Debug.h"

Texture::Texture(SDL_Renderer* renderer)
{
	m_RendererRef = renderer;
	m_Angle = 0.0f;
	m_Path = "";
	m_PosX = m_PosY = 0;
	m_SurfaceData = nullptr;
	m_TextureRef = nullptr;
	m_Scale = 1;
}

bool Texture::ImportTexture(const char* pathToFile)
{
	// Store path file
	m_Path = pathToFile;
	 
	// Import image and convert to surface
	// Fill in object with data for the image
	m_SurfaceData = IMG_Load(pathToFile);

	// Did the import fail
	if (m_SurfaceData == nullptr)
	{
		EE_LOG("Texture", "Image failed to import: " << SDL_GetError());

		return false;
	}

	// create texture from surface
	m_TextureRef = SDL_CreateTextureFromSurface(m_RendererRef, m_SurfaceData);

	// Did the conversion fail
	if (m_TextureRef == nullptr)
	{
		EE_LOG("Texture", "Image failed to convert to texture: " << SDL_GetError());
		Cleanup();
		return false;
	}

	EE_LOG("Texture", "Successfully imported texture: " << m_Path);

	return true;
}

void Texture::Draw()
{
	float imageWidth = (float)m_SurfaceData->w;
	float imageHeight = (float)m_SurfaceData->h;

	SDL_FRect destRect = {
		(float)m_PosX, (float)m_PosY,
		imageWidth * m_Scale, imageHeight * m_Scale
	};

	SDL_FPoint center{
		1920 / 2,
		1080 / 2
	};

	SDL_RenderCopyExF(
		m_RendererRef, // Render to draw to
		m_TextureRef, // The texture to draw to the renderer
		NULL, // Clip rect
		&destRect, // Position and scale on the screen
		m_Angle, // rotation of the texture
		&center, // center point for the rotation
		SDL_FLIP_NONE); // flip the texture vertical or horizontal
}

void Texture::Cleanup()
{
	// Clean up the surface
	if (m_SurfaceData != nullptr)
	{
		SDL_FreeSurface(m_SurfaceData);
	}

	// Clean up the texture
	if (m_TextureRef != nullptr)
	{
		SDL_DestroyTexture(m_TextureRef);
	}

	EE_LOG("Texture", "Successfully destroyed image: " << m_Path);
}

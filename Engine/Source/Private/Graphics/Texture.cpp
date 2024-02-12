#include "Graphics/Texture.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Debug.h"

Texture::Texture(SDL_Renderer* renderer)
{
	m_RendererRef = renderer;
	angle = 0.0f;
	path = "";
	posX = posY = 0;
	m_SurfaceData = nullptr;
	m_TextureRef = nullptr;
	scale = 1;
}

bool Texture::ImportTexture(const char* pathToFile)
{
	// Store path file
	path = pathToTile;

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

	EE_LOG("Texture", "Successfully imported texture: " << path);

	return true;
}

void Texture::Draw()
{
	float imageWidth = (float)m_SurfaceData->w;
	float imageHeight = (float)m_SurfaceData->h;

	SDL_FRect destRect = {
		(float)posX, (float)posY,
		imageWidth * scale, imageHeight * scale
	};

	SDL_FPoint center{
		destRect.w / 2,
		destRect.h / 2
	};

	SDL_RenderCopyExF(
		m_RendererRef, // Render to draw to
		m_TextureRef, // The texture to draw to the renderer
		NULL, // Clip rect
		&destRect, // Position and scale on the screen
		angle, // rotation of the texture
		&center, // center point for the rotation
		SDL_FLIP_NONE); // flip the texture vertical or horizontal
}

void Texture::Cleanup()
{
	// Clean up the surface
	if (m_surfaceData != nullptr)
	{
		SDL_FreeSurface(m_SurfaceData);
	}

	// Clean up the texture
	if (m_TextureRef != nullptr)
	{
		SDL_DestroyTexture(m_TextureRef);
	}

	EE_LOG("Texture", "Successfully destroyed image: " << path);
}

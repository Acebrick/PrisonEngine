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
	m_ClipRect = nullptr;
}

Texture::~Texture()
{
	if (m_ClipRect != nullptr)
	{
		delete m_ClipRect;
	}
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

void Texture::CopyTexture(Texture* copyTexture)
{
	m_Path = copyTexture->m_Path;
	m_SurfaceData = copyTexture->m_SurfaceData;
	m_TextureRef = copyTexture->m_TextureRef;
}

void Texture::Draw()
{
	float imageWidth = (float)m_SurfaceData->w;
	float imageHeight = (float)m_SurfaceData->h;

	SDL_FRect destRect = {
		(float)m_PosX, (float)m_PosY,
		imageWidth * m_Scale, imageHeight * m_Scale
	};

	// If we have a set clip then update the width and height of the texture
	if (m_ClipRect != nullptr)
	{
		destRect.w = m_ClipRect->w * m_Scale;
		destRect.h = m_ClipRect->h * m_Scale;
	}

	// Move the texture to be centered at the middle point of the image
	destRect.x -= destRect.w / 2;
	destRect.y -= destRect.h / 2;

	SDL_FPoint center{
		destRect.w / 2,
		destRect.h / 2
	};

	SDL_RenderCopyExF(
		m_RendererRef, // Render to draw to
		m_TextureRef, // The texture to draw to the renderer
		m_ClipRect, // Clip rect
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

void Texture::SetClip(int x, int y, int w, int h)
{

	if (m_ClipRect == nullptr)
	{
		// Create the SDL rect object
		m_ClipRect = new SDL_Rect();
	}

	// Set the rect values
	m_ClipRect->x = x;
	m_ClipRect->y = y;
	m_ClipRect->w = w;
	m_ClipRect->h = h;
}

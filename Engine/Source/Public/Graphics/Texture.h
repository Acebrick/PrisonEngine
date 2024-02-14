#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

class Texture
{
public:
	// Variables
	int m_PosX, m_PosY;
	float m_Scale;

	// Rotation of the image
	float m_Angle;

	// Functions
	Texture(SDL_Renderer* renderer);
	~Texture() = default;
	// Import and create a texture
	bool ImportTexture(const char* pathToFile);

	// Draw the texture to the renderer
	void Draw();

	// Deallocate memory
	void Cleanup();

	// Get the original image path
	const char* GetPath() const { return m_Path; }

private:
	// Variables
		// Texture that SDL understands
	SDL_Texture* m_TextureRef;

	// Store the assigned renderer
	SDL_Renderer* m_RendererRef;

	// Surface data for the original image
	SDL_Surface* m_SurfaceData;

	// Path to the original image
	const char* m_Path;

	// Functions
};


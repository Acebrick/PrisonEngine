#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

class Texture
{
public:
	// Variables
	int m_PosX, m_PosY;
	float m_ScaleX, m_ScaleY;

	// Rotation of the image
	float m_Angle;

	// Determine whether or not to render the texture
	bool m_IsVisible;

	// Functions
	Texture(SDL_Renderer* renderer);
	~Texture();
	// Import and create a texture
	bool ImportTexture(const char* pathToFile);
	
	void CopyTexture(Texture* copyTexture);

	// Draw the texture to the renderer
	void Draw();

	// Deallocate memory
	void Cleanup();

	// Get the original image path
	const char* GetPath() const { return m_Path; }

	// Set the clip for the texture
	void SetClip(int x, int y, int w, int h);

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

	// Store the for the texture
	SDL_Rect* m_ClipRect;

	// Functions
};


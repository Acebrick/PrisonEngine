#pragma once

class Texture;

struct AnimationParams
{
	AnimationParams()
	{
		frameWidth = frameHeight = 0;
		fps = 0.0f;
		startFrame = endFrame = 0;
		maxFrames = 0;
	}

	// Width and height of each frame
	unsigned int frameWidth, frameHeight;

	// Frames per second
	float fps;

	// Start and end frame that the animation will play
	unsigned int startFrame, endFrame;

	// Amount of frames in the sprite
	unsigned int maxFrames;
};

class Animation
{
private:
	// Stores the texture to render
	Texture* m_TextureRef;

	// Stores the animation data
	AnimationParams* m_AnimParams;

	// The current playing frame of the animation
	unsigned int m_CurrentFrame;

	// How much time has passed since the last animation frame
	float m_FrameTimer;

	int moveSpeed = 400;

public:
	Animation();
	~Animation();

	// Imports the animation and add animation parameters
	bool CreateAnimation(const char* pathToFile, AnimationParams* params = nullptr);

	// Update the animation logic each frame
	void Update(float deltaTime);

	void SetPosition(int x, int y);

	void SetRotation(float angle);

	void SetScale(float scale);

	void GunnerRunning(Animation* gunner, float deltaTime);

	bool JetpackGunner(Animation* JetpackGunner, Animation* jetpackEffect, Animation* bullet, Animation* blackGunner, Animation* muzzleFlash, float deltaTime);

	void AnimTypeDefinitions(int animType, AnimationParams& anim);

	bool ShootBullet(Animation* bullet, Animation* JetpackGunner, Animation* blackGunner, Animation* muzzleFlash, float deltaTime);

	static bool GunnerDead(Animation* character, Animation* explosion);

	void DodgeSaw(Animation* saw, Animation* redGunner);
};
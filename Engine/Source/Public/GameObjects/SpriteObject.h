#pragma once
#include "GameObjects/GameObject.h"
#include "Graphics/Animation.h"

class SpriteObject : public GameObject
{
public:
	SpriteObject() = default;
	virtual ~SpriteObject() = default;

	virtual void Cleanup() override;

protected:
	// Add an animation/sprite to the sprite stack
	Animation* AddSprite(const char* pathToFile, AnimationParams* params = nullptr);

	virtual void OnPostUpdate(float deltaTime) override;

private:
	// Store all sprites related to this object
	TArray<Animation*> m_SpriteStack;
};
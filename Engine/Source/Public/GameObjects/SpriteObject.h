#pragma once
#include "GameObjects/GameObject.h"
#include "Graphics/Animation.h"

class Sprite
{
public:
	// Default constructor
	Sprite() : m_Sprite(nullptr), m_IsActive(true) {
		m_Offset.scale = 0.0f;
	}

	// Sprite assign constructor
	Sprite(Animation* anim) : m_Sprite(anim), m_IsActive(true) {
		m_Offset.scale = 0.0f;
	}

	~Sprite()
	{
		delete m_Sprite;
		m_Sprite = nullptr;
	}

	void SetActive(bool isActive)
	{
		m_IsActive = isActive;
		m_Sprite->SetVisible(isActive);
	}

	Animation* m_Sprite;
	EETransform m_Offset;

private:
	bool m_IsActive;
};

class SpriteObject : public GameObject
{
public:
	SpriteObject() = default;

	virtual void Cleanup() override;

protected:
	// Add an animation/sprite to the sprite stack
	Sprite* AddSprite(const char* pathToFile, AnimationParams* params = nullptr);

	virtual void OnPostUpdate(float deltaTime) override;

private:
	// Store all sprites related to this object
	TArray<Sprite*> m_SpriteStack;

	void SpriteFollowObject(Sprite* spriteToFollow);

	
};
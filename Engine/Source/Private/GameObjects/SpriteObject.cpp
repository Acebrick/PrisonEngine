#include "GameObjects/SpriteObject.h"
#include "Debug.h"

#define Super GameObject

void SpriteObject::Cleanup()
{
	for (auto sprite : m_SpriteStack)
	{
		delete sprite;
		sprite = nullptr;
	}
}

Sprite* SpriteObject::AddSprite(const char* pathToFile, AnimationParams* params)
{
	Animation* newAnim = new Animation();

	if (!newAnim->CreateAnimation(pathToFile, params))
	{
		return nullptr;
	}

	Sprite* newSprite = new Sprite(newAnim);

	// Set the sprite to the object transforms
	SpriteFollowObject(newSprite);

	// Add it to the sprite stack
	m_SpriteStack.push_back(newSprite);

	return newSprite;
}

void SpriteObject::OnPostUpdate(float deltaTime)
{
	Super::OnPostUpdate(deltaTime);

	// Loop through each sprite and set it to matchj the objects transform
	for (auto sprite : m_SpriteStack)
	{
		if (sprite == nullptr)
		{
			continue;
		}

		// Move thte sprite to the location of the object
		SpriteFollowObject(sprite);

		// Update the sprites animation
		sprite->m_Sprite->Update(deltaTime);
	}
}

void SpriteObject::SpriteFollowObject(Sprite* spriteToFollow)
{
	// Set sprite position to match objects
	spriteToFollow->m_Sprite->SetPosition(
		(int)GetTransform().position.x + spriteToFollow->m_Offset.position.x, 
		(int)GetTransform().position.y + spriteToFollow->m_Offset.position.y);

	// Set sprite rotation to match objects
	spriteToFollow->m_Sprite->SetRotation(GetTransform().rotation + spriteToFollow->m_Offset.rotation);

	// Set sprite scale to match objects
	spriteToFollow->m_Sprite->SetScale(
		GetTransform().scale.x + spriteToFollow->m_Offset.scale.x,
		GetTransform().scale.y + spriteToFollow->m_Offset.scale.y);
}

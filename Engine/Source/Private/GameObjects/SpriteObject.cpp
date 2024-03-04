#include "GameObjects/SpriteObject.h"
#include "Debug.h"
void SpriteObject::Cleanup()
{
	for (auto sprite : m_SpriteStack)
	{
		delete sprite;
		sprite = nullptr;
	}
}

Animation* SpriteObject::AddSprite(const char* pathToFile, AnimationParams* params)
{
	Animation* newAnim = new Animation();

	if (!newAnim->CreateAnimation(pathToFile, params))
	{
		return nullptr;
	}

	// Set sprite position to match objects
	newAnim->SetPosition((int)GetTransform().position.x, (int)GetTransform().position.y);
	// Set sprite rotation to match objects
	newAnim->SetRotation(GetTransform().rotation);
	// Set sprite scale to match objects
	newAnim->SetScale(GetTransform().scale.x, GetTransform().scale.y);

	m_SpriteStack.push_back(newAnim);

	return newAnim;
}

void SpriteObject::OnPostUpdate(float deltaTime)
{
	// Loop through each sprite and set it to matchj the objects transform
	for (auto sprite : m_SpriteStack)
	{
		if (sprite == nullptr)
		{
			continue;
		}

		// Set sprite position to match objects
		sprite->SetPosition((int)GetTransform().position.x, (int)GetTransform().position.y);
		// Set sprite rotation to match objects
		sprite->SetRotation(GetTransform().rotation);
		// Set sprite scale to match objects
		sprite->SetScale(GetTransform().scale.x, GetTransform().scale.y);
	}
}

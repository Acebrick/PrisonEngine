#pragma once
#include "GameObjects/Character.h"

class Enemy : public Character
{
public:
	Enemy();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate(float deltaTime) override;

	void FollowPlayer(float xPos, float yPos, Vector2& playerPosition);

	TArray<Sprite*> m_EnemySprite;

private:
	Vector2 direction;
};

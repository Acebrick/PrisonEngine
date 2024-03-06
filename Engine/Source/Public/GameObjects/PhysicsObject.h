#pragma once
#include "SpriteObject.h"

class Input;

class PhysicsObject : public SpriteObject
{
public:
	PhysicsObject() : m_Sprite(nullptr) {}
	~PhysicsObject() = default;
	void movePlayerWithMouse(float xPos, float yPos, Vector2& direction, Input* gameInput);

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* gameInput) override;

	virtual void OnUpdate(float deltaTime) override;

private:
	Animation* m_Sprite;
	Vector2 m_MovementDirection;
	float m_Speed = 0.0f;
};
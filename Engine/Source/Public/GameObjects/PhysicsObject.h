#pragma once
#include "SpriteObject.h"

class PhysicsObject : public SpriteObject
{
public:
	PhysicsObject() : m_Sprite(nullptr) {}
	~PhysicsObject() = default;

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* gameInput) override;

	virtual void OnUpdate(float deltaTime) override;

private:
	Animation* m_Sprite;
};
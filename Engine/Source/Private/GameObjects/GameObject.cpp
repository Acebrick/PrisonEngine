#include "GameObjects/GameObject.h"
#include "Debug.h"

void GameObject::Start()
{
	if (isPendingDestroy())
	{
		return;
	}

	OnStart(); 
	//EE_LOG("GameObject", "GameObject has spawned into the game");
}

void GameObject::ProcessInput(Input* gameInput)
{
	if (isPendingDestroy())
	{
		return;
	}

	OnProcessInput(gameInput);
}

void GameObject::Update(float deltaTime)
{
	if (isPendingDestroy())
	{
		return;
	}

	OnUpdate(deltaTime);
}

void GameObject::PostUpdate(float deltaTime)
{
	if (isPendingDestroy())
	{
		return;
	}

	OnPostUpdate(deltaTime);
}

void GameObject::OnDestroy()
{
	EE_LOG("GameObject", "GameObject has been destroyed");
}

void GameObject::DestroyObject()
{
	// Ensure the OnDestroy only runs once
	if (!m_ShouldDestroy)
	{
		OnDestroy();
	}

	m_ShouldDestroy = true;
}

void GameObject::SetTransform(EETransform transform)
{
	m_Transform = transform;
}

void GameObject::SetPosition(Vector2 position)
{
	EETransform newTransform(
		position,
		m_Transform.rotation,
		m_Transform.scale
	);
	
	SetTransform(newTransform);
}

void GameObject::SetRotation(float rotation)
{
	EETransform newTransform(
		m_Transform.position,
		rotation,
		m_Transform.scale
	);

	SetTransform(newTransform);
}

void GameObject::SetScale(Vector2 scale)
{
	EETransform newTransform(
		m_Transform.position,
		m_Transform.rotation,
		scale
	);

	SetTransform(newTransform);
}

#include "GameObjects/GameObject.h"
#include "Debug.h"
#include "Math/Bounds.h"

void GameObject::Start()
{
	if (isPendingDestroy())
	{
		return;
	}

	OnStart(); 
	//EE_LOG("GameObject", "GameObject has spawned into the game");

	BoundsMatchObjectPosition();
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

Bounds* GameObject::AddBounds(Vector2 center, Vector2 extent)
{
	Bounds* newBounds = new Bounds(this, center, extent);

	m_BoundsStack.push_back(newBounds);

	return newBounds;
}

void GameObject::BoundsMatchObjectPosition()
{
	// Move any bounds to the same position as the object
	for (auto testBounds : m_BoundsStack)
	{
		if (testBounds == nullptr)
		{
			continue;
		}

		testBounds->m_Rect.origin = GetTransform().position;
	}
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

void GameObject::Cleanup()
{
	for (auto testBounds : m_BoundsStack)
	{
		delete testBounds;
	}
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

	BoundsMatchObjectPosition();
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

void GameObject::TestOverlapEvent(Bounds* otherBounds)
{
	// Make sure the other bounds is set to detect collisions
	if (otherBounds->m_CollisionType == CT_NONE)
	{
		return;
	}
	
	// Loop through all the collisions bounds
	for (auto testBounds : m_BoundsStack)
	{
		// Make sure the objects bounds is set to detect collisions
		if (testBounds->m_CollisionType == CT_NONE) 
		{
			continue;
		}

		// Make sure the bounds is not this one
		if (otherBounds->GetOwner() == this)
		{
			continue;
		}

		// Search through the overlapped array to detect if we've already overlapped
		auto it = std::find(testBounds->m_Overlapped.begin(), testBounds->m_Overlapped.end(), otherBounds);

		// Detect if bounds are intersecting
		bool isIntersecting = Bounds::BoundsIntersect(*testBounds, *otherBounds);

		// Is the bounds already overlapped
		bool isOverlapped = it != testBounds->m_Overlapped.end();

		if (isOverlapped)
		{
			if (!isIntersecting)
			{
				// Removes the other bounds from the overlapped array
				testBounds->m_Overlapped.erase(it);

				OnOverlapExit(otherBounds, testBounds);

				EE_LOG("GameObject", "Exited");
			}
		}
		else
		{
			if (isIntersecting)
			{
				//  Add the other vounds to the overlap array
				testBounds->m_Overlapped.push_back(otherBounds);

				OnOverlapEnter(otherBounds, testBounds);

				EE_LOG("GameObject", "Entered");
			}
		}

		// Change the colour if there is anything overlapping this bounds
		if (testBounds->m_Overlapped.size() > 0)
		{
			testBounds->m_RenderColour = STBoundsColour(0, 255, 0); // Green
		}
		else
		{
			testBounds->m_RenderColour = STBoundsColour(255, 0, 0); // Red
		}
	}
}
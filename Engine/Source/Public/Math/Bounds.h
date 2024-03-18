#pragma once
#include "Math/Vector2.h"
#include <cstdint>
#include "EngineTypes.h"

class GameObject;

struct EERect
{
	// Simple constructor
	EERect() : origin(0.0f), extent(1.0f) {}

	// Complex constructor
	EERect(Vector2 origin, Vector2 extent) : origin(origin), extent(extent) {}

	// Min value position of the rect relative to the screen
	Vector2 Min() const { return origin - extent; }

	// Max value position of the rect relative to the screen
	Vector2 Max() const { return origin + extent; }

	// Center of the rectangle
	Vector2 origin;

	// Half width/height of the box
	Vector2 extent;
};

enum EECollisionType : unsigned int
{
	CT_NONE = 0,
	CT_OVERLAP
};

struct STBoundsColour
{
	// Default constructor
	STBoundsColour() : r(255), g(0), b(0) {}

	// Colour set constructor
	STBoundsColour(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

	uint8_t r;
	uint8_t g;
	uint8_t b;
};

class Bounds
{
public:
	
	Bounds(GameObject* owner, Vector2 origin = 0.0f, Vector2 extent = 1.0f);

	// Off set of the original position
	Vector2 m_OriginOffset;

	// Collision type
	EECollisionType m_CollisionType;

	// Colour of the bounds if debug is active
	STBoundsColour m_RenderColour;

	// All currently overlapping bounds
	TArray<Bounds*> m_Overlapped;

	// Rectangle that defines the bounds
	EERect m_Rect;

	// Name of the collision
	const char* m_Tag;

	// Detect if 2 bounds are intersecting
	static bool BoundsIntersect(const Bounds& boundsA, const Bounds& boundsB);

	// The center equals the origin + the offset
	Vector2 GetCenter() { return m_Rect.origin + m_OriginOffset; }

	// Get the game object that owns the bounds
	GameObject* GetOwner() const { return m_Owner; }

	

private:

	// Owner object the bounds is attached to
	GameObject* m_Owner;
};
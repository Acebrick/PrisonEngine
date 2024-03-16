#pragma once
#include "Math/Vector2.h"
#include "EngineTypes.h"

class Input;

struct EETransform 
{
	// Default constructor
	EETransform() : position(0.0f), rotation(0.0f), scale(1.0f) {}
	
	// Assignment constructor
	EETransform(Vector2 position, float rotation, Vector2 scale) : 
	position(position), rotation(rotation), scale(scale) {}
	
	// Transform constructor
	EETransform(const EETransform& other) : 
	position(other.position), rotation(other.rotation), scale(other.scale) {}

	Vector2 position;
	float rotation;
	Vector2 scale;
};

class GameObject
{
public:
	GameObject() : m_ShouldDestroy(false) {}

	virtual ~GameObject() = default;

	// Runs when this object spawns into the game
	void Start();

	// Listen for input events
	void ProcessInput(Input* gameInput);

	// Run every frame
	void Update(float deltaTime);

	// Runs every frame after the update
	void PostUpdate(float deltaTime);

	// Destroy game object
	void DestroyObject();

	// Is the object pending destroy at the end of the loop
	bool isPendingDestroy() const { return m_ShouldDestroy; }

	// Remove any memory references
	virtual void Cleanup() {}

	// Get the transform of the object
	EETransform GetTransform() const { return m_Transform; }

	// Set the transform of the object
	virtual void SetTransform(EETransform transform);

	// Set the position of the object
	void SetPosition(Vector2 position);

	// Set the rotation of the object
	void SetRotation(float rotation);

	// Set the scale of the object
	void SetScale(Vector2 scale);

protected:
	// Run when the game object has been marked for destroy
	virtual void OnDestroy();

	// Runs when the game object spawns into the game
	virtual void OnStart() {}

	// Run on the game objects process input (before each update frame)
	virtual void OnProcessInput(Input* gameInput) {}

	// Run on the game objects update (each frame)
	virtual void OnUpdate(float deltaTime) {}

	// Run on the game objects post update (each frame after the update)
	virtual void OnPostUpdate(float deltaTime) {}

private:
	// Determine if the object should be destroyed at the end of the loop
	bool m_ShouldDestroy;

	// Store the transform location for the object
	EETransform m_Transform;
};
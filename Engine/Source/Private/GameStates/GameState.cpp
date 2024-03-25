#include "GameStates/GameState.h"
#include "GameObjects/GameObject.h"
#include "Math/Bounds.h"
#include "SDL2/SDL_render.h"



void GameState::Start()
{
	OnStart();
}

void GameState::Cleanup()
{
	OnCleanup();

	// Destory any objects pending spawn
	for (auto GO : m_GameOjectPendingSpawn)
	{
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}

	// Destroy any remaining game objects
	for (auto GO : m_GameObjectStack)
	{
		GO->Cleanup();
		delete GO;
		GO = nullptr;
	}
}

void GameState::PreLoop()
{
	// Add all game object pending spawn to the game object stack
	for (auto GO : m_GameOjectPendingSpawn)
	{
		m_GameObjectStack.push_back(GO);
		GO->Start();
	}

	// Resize the array to 0
	m_GameOjectPendingSpawn.clear();

	OnPreLoop();
}

void GameState::ProcessInput(Input* gameInput)
{
		// Run the input listener function for all game objects
	for (auto GO : m_GameObjectStack)
	{
		if (GO != nullptr)
		{
			GO->ProcessInput(gameInput);
		}
	}

	OnProcessInput(gameInput);

	
}

void GameState::Update(float deltaTime)
{
	// Run the update logic for all game objects
	for (auto GO : m_GameObjectStack)
	{
		if (GO != nullptr)
		{
			GO->Update(deltaTime);
			GO->PostUpdate(deltaTime);

			// Looking through all of the other game objects
			for (auto otherGO : m_GameObjectStack)
			{
				for (auto otherBounds : otherGO->GetAllBounds())
				{
					GO->TestOverlapEvent(otherBounds);
				}
			}
		}
	}

	OnUpdate(deltaTime);
}

void GameState::Render(SDL_Renderer* renderer)
{
	// Render bounds if marked debug
	for (auto GO : m_GameObjectStack)
	{
		if (GO == nullptr)
		{
			continue;
		}

		// Loop through all the game object bounds
		for (auto testBounds : GO->GetAllBounds())
		{
			// If debug is false then skip to the next bounds
			if (!testBounds->m_Debug)
			{
				continue;
			}

			// Set the colour of the next drawn thing in SDL, in this cacse the bounds
			SDL_SetRenderDrawColor(
				renderer,
				testBounds->m_RenderColour.r,
				testBounds->m_RenderColour.g,
				testBounds->m_RenderColour.b,
				255
			);

			// Converting the EERect to an SDL_FRect
			SDL_FRect boundsRect
			{
				testBounds->GetCenter().x,
				testBounds->GetCenter().y,
				testBounds->m_Rect.extent.x,
				testBounds->m_Rect.extent.y
			};

			// Draws a rectangle to the window
			SDL_RenderDrawRectF(renderer, &boundsRect);
		}
	}
}

void GameState::GarbageCollection()
{
	OnGarbageCollection();

	// Collect the garbage on a game object level
	for (const auto GO : m_GameObjectStack)
	{
		GO->CollectGarbage();
	}

	// Delete objects at the end of each frame
	for (int i = m_GameObjectStack.size() - 1; i >= 0; i--) // i-- may cause issues
	{
		if (m_GameObjectStack[i]->isPendingDestroy() == false)
		{
			continue;
		}

		if (m_GameObjectStack[i] != nullptr)
		{
			m_GameObjectStack[i]->Cleanup();
			delete m_GameObjectStack[i];
		}

		// Remove from and resize the array
		m_GameObjectStack.erase(m_GameObjectStack.begin() + i);
	}
}
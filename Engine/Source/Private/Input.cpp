#include"Input.h"
#include "SDL2/SDL.h"
#include "Game.h"
#include "Math/Vector2.h"

void Input::ProcessInput()
{
	// Data type that reads the SDL input events for the window
	SDL_Event inputEvent;

	// Run through each input in that frame
	while (SDL_PollEvent(&inputEvent))
	{
		// Was the input that was pressed a mouse button and is it pressed down
		if (inputEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			DetectMouseButtonState(inputEvent.button.button, true);
		}
		// Was the input that was pressed a mouse button and was it released
		if (inputEvent.type == SDL_MOUSEBUTTONUP)
		{
			DetectMouseButtonState(inputEvent.button.button, false);
		}
		// If cross button is pressed on the window ,close the app
		if (inputEvent.type == SDL_QUIT)
		{
			Game::GetGame()->QuitApp();
		}
	}
}

bool Input::IsKeyDown(EE_Key key)
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	if (keyStates == nullptr)
	{
		return false;
	}

	return keyStates[key];
}

bool Input::IsMouseButtonDown(EE_MouseButton button)
{
	if (button >= EE_NUM_BUTTONS)
	{
		return false;
	}
	return m_MouseState[button];
}

Vector2 Input::GetMousePos() const
{
	int x = 0;
	int y = 0;

	// This function will change x and y variables with the location of the mouse
	SDL_GetMouseState(&x, &y);

	return Vector2((float)x, (float)y);
}

void Input::DetectMouseButtonState(unsigned int event, bool value)
{
	switch (event)
	{
	case SDL_BUTTON_LEFT:
		m_MouseState[EE_MOUSE_LEFT] = value;
		break;
	case SDL_BUTTON_MIDDLE:
		m_MouseState[EE_MOUSE_MIDDLE] = value;
		break;
	case SDL_BUTTON_RIGHT:
		m_MouseState[EE_MOUSE_RIGHT] = value;
		break;
	default:
		break;
	}
}

#include "Input.h"
#include <SDL.h>
#include <stdio.h>

bool Input::KeyIsPressed(SDL_KeyCode key)
{
	return _keysPressed[key];
}

void Input::EventKeyPressed(SDL_Keycode key)
{
	_keysPressed.insert_or_assign(key, true);// Any key that is pressed = true
}

void Input::EventKeyReleased(SDL_Keycode key)
{
	_keysPressed.insert_or_assign(key, false);// Any key release = true
}




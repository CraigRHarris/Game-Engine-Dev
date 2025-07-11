#include "Input.h"
#include <SDL.h>
#include <stdio.h>



bool Input::KeyIsPressed(SDL_KeyCode key) const
{
	if (!_keysDown.contains(key)) return false;

	return _keysDown.at(key);
}

void Input::EventKeyPressed(SDL_Keycode key)
{
	_keysDown.insert_or_assign(key, true);// Any key that is pressed = true
}

void Input::EventKeyReleased(SDL_Keycode key)
{
	_keysDown.insert_or_assign(key, false);
}

Input::Input()
{
}

Input::~Input()
{
}




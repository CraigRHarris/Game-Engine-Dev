#include "Input.h"
#include <SDL.h>
#include <stdio.h>

bool Input::KeyIsPressed(SDL_KeyCode key)
{
	return _keysPressed[key];
}

void Input::EventKeyPressed(SDL_Keycode key)
{
	_keysPressed.insert_or_assign(key, true);
}

void Input::EventKeyReleased(SDL_Keycode key)
{
	_keysPressed.insert_or_assign(key, false);
}


Input::Input() //constructor
{

}

Input::~Input() //destroy to clear code
{

}



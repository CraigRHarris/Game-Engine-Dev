#include "Input.h"
#include <SDL.h>
#include <stdio.h>

void Input::Update(void)
{
	SDL_Event m_Event;
	//loop through all the events in the event list
	while (SDL_PollEvent(&m_Event) != NULL)
	{
		//got an event. let's process it

		//check for keydown
		if (m_Event.type == SDL_KEYDOWN)
		{
			//cache the code of key we pressed for easier debugging
			SDL_Keycode keyPressed = m_Event.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				m_KeysPressed[KEY_ESCAPE] = true;
				break;

			case SDLK_r:
				m_KeysPressed[KEY_R] = true;
				break;

			case SDLK_g:
				m_KeysPressed[KEY_G] = true;
				break;

			case SDLK_b:
				m_KeysPressed[KEY_B] = true;
				break;

			}
		}
		//check for key up
		else if (m_Event.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = m_Event.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_r:
				m_KeysPressed[KEY_R] = false;
				break;

			case SDLK_g:
				m_KeysPressed[KEY_G] = false;
				break;

			case SDLK_b:
				m_KeysPressed[KEY_B] = false;
				break;
			}
		}
	}
}



bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_KeysPressed[key];
}


Input::Input() //constructor
{

}

Input::~Input() //destroy to clear code
{

}



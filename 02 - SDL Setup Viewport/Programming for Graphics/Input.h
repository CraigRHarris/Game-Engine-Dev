#pragma once
#include "SDL.h"
#include <map>

//Global vars
enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_R, KEY_G, KEY_B, SIZE_OF_KEYS_PRESSD_ENUM
};

class Input
{
public:
	bool KeyIsPressed(SDL_KeyCode key);

	void EventKeyPressed(SDL_Keycode key);
	void EventKeyReleased(SDL_Keycode key);

	Input();
	~Input();

private:
	std::map<SDL_Keycode, bool> _keysDown;
};
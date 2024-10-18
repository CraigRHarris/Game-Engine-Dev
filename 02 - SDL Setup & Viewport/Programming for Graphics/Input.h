#pragma once
//#include "SDL.h"

//Global vars
enum KEYS_PRESSED_LIST
{
	KEY_ESCAPE, KEY_R, KEY_G, KEY_B, SIZE_OF_KEYS_PRESSD_ENUM
};

class Input
{
public:
	void Update(void);
	bool KeyIsPressed(KEYS_PRESSED_LIST key);

	Input();
	~Input();

private: 
	;
	bool m_KeysPressed[SIZE_OF_KEYS_PRESSD_ENUM]{false};
};
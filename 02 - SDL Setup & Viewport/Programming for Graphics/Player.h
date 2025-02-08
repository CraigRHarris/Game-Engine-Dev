#pragma once
#include "Bitmaps.h"
#include "Logger.h"

class Player : public Bitmap
{
public:
	Player(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos, useTransparency) {
		Logger::Info("Player constructor");
	}

	void Update();

	void FixGroundCollision(Bitmap* ground);

	void Jump();

	void addKey() { KeysCollected++; }
	int getKeys() const { return KeysCollected; }

private:
	int KeysCollected = 0;

	float yVelocity;

	const float jumpForce = 20.0f;

};
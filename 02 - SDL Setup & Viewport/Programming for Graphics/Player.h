#pragma once
#include "Bitmaps.h"
#include "Logger.h"

class Player : public Bitmap
{
public:
	Player(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false) : Bitmap(renderer, fileName, xpos, ypos, useTransparency) {
		Logger::Info("Player constructor");
	}

	void Update();

	void FixGroundCollision(Bitmap* ground);

	void Jump();

private:
	float yVelocity;

	const float jumpForce = 30.0f;

};
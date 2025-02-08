#pragma once
#include <iostream>
#include "Bitmaps.h"
#include "Logger.h"

class Enemy : public Bitmap
{
public:
	Enemy(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, int left, int right, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos, useTransparency) {
		Logger::Info("Enemy constructor");
		point_l = left;
		point_r = right;
		direction = -1; //start moving left
	};

	void Update();

	void FixGroundCollision(Bitmap* ground);

	void MoveAI();

private:
	float movementSpeed;
	float yVelocity;
	float xVelocity;
	float direction;
	int point_l, point_r;
};


#pragma once
#include <iostream>

#include "Bitmaps.h"
#include "Logger.h"

class Enemy : public Bitmap
{
public:
	Enemy(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, int left, int right, const std::string ObjectName, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos,ObjectName, useTransparency) {
		Logger::Info("Enemy ");
		point_l = left;
		point_r = right;
		direction = -1; //start moving left
	};

	void Update();

	void FixGroundCollision(Bitmap* ground);

	void MoveAI();

	virtual void GUIDraw() override;

	int getLeftBound() { return point_l; }
	int getRightBound() { return point_r; }

private:
	float movementSpeed{ 3.0f };
	float yVelocity;
	float xVelocity;
	float direction;
	int point_l, point_r;
};


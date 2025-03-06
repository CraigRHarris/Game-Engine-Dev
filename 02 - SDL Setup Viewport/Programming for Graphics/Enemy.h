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

	/**
	Setting the gravity and helps add collion to the floor.
	*/
	void Update();

	void FixGroundCollision(Bitmap* ground);

	/**
	Setting the postitions of the AI going left and right.
	*/
	void MoveAI();

	/**
	Draw the ajustable paramaters for the selectable when you select it on the hierarchy
	*/
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


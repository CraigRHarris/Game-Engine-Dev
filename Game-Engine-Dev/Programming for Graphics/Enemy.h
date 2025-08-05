#pragma once
#include <iostream>

#include "Bitmaps.h"
#include "Logger.h"
#include "Phyics.h"

class Enemy : public Bitmap
{
public:
	Enemy(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, int left, int right, const std::string ObjectName, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos,ObjectName, useTransparency) {
		Logger::Info("Enemy ");
		point_l = left;
		point_r = right;
		direction = -1; //start moving left
		physics = new Physics(static_cast<float>(m_w), static_cast<float>(m_h));
		physics->UpdatePosition(xpos, ypos);
	};

	void draw() override;
	/**
	Setting the gravity and the moving of the enemy.
	*/
	void Update(const std::vector<Bitmap*>& platforms);

	void FixGroundCollision(Bitmap* ground);

	bool IsGrounded() const { return physics->GetGrounded(); }

	/**
	Draw the enemy when needed.
	*/
	virtual void GUIDraw() override;

	/**
	The point of the enemy that it will move to the left.
	*/
	int getLeftBound() { return point_l; }
	/**
	The point of the enemy that it will move to the right.
	*/
	int getRightBound() { return point_r; }

private:
	float moveSpeed{ 3.0f };
	float yVelocity{ 0.0f };
	float xVelocity{ 0.0f };
	float direction{ 1.0f };
	int point_l{ 1 }, point_r{ 1 };
	Physics* physics;
};


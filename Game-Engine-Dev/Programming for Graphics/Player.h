#pragma once
#include "Bitmaps.h"
#include "Logger.h"
#include "Phyics.h"
class Player : public Bitmap
{
public:

	
	Player(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, const std::string ObjectName, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos,ObjectName, useTransparency) {
		Logger::Info("Player");
		physics = new Physics(m_w, m_h);
		physics->UpdatePosition(xpos, ypos);
	}


	/**
	Added gravity to player with velocity.
	*/
	void Update();

	/**
	Added the fix ground is colliding with the player
	*/
	void FixGroundCollision(Bitmap* ground);

	bool IsGrounded() const { return physics->GetGrounded(); }

	void Jump();

	void addKey() { KeysCollected++; }
	int getKeys() const { return KeysCollected; }

	/**
	Output to check if key is collected
	*/
	void GUIDraw() override;

private:
	int KeysCollected = 0;

	const float jumpForce = 20.0f;
	Physics* physics;

};
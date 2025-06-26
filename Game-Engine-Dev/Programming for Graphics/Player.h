#pragma once
#include "Bitmaps.h"
#include "Logger.h"
#include "Phyics.h"

class Input;
class Pickup;

class Player : public Bitmap
{
public:

	
	Player(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, const std::string ObjectName, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos,ObjectName, useTransparency) {
		Logger::Info("Player");
		physics = new Physics(static_cast<float>(m_w), static_cast<float>(m_h));
		physics->UpdatePosition(xpos, ypos);
	}

	void draw() override;

	/**
	Added gravity to player with velocity.
	*/
	void Update(const std::vector<Bitmap*>& platforms, std::vector<Pickup*>& pickups);
	void HandleInput(const Input& input);

	//add collicion for player to emeny and damange if needed (use key collider code bellow)
	//physics->IsColliding(pickup->GetTransformRect())

	int GetScore() const { return _score; }// score for when key is pickup

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

	int _score{ 0 };
	bool jumpedThisFrame{ false };

};
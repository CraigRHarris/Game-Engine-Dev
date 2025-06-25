#pragma once
#include "SDL.h"
class Physics
{
private:
	bool isGrounded;
	SDL_FRect CollisionRect;
	float yVelocity;
public:
	Physics(float W, float H) : CollisionRect{ 0.0f, 0.0f, W, H }, isGrounded{ false }, yVelocity{ 0.0f } {}

	SDL_FRect GetCollisionRect() const { return CollisionRect; }

	virtual void HandleGravity(float& Ypos);
	void UpdatePosition(float x, float y);

	virtual bool IsColliding(SDL_FRect Other);
	void CheckForGroundCollision(SDL_FRect Ground, float& yPos);

	void SetGrounded(bool grounded) { isGrounded = grounded; }
	bool GetGrounded() const { return isGrounded; }

	void SetYVelocity(float newYVel) { yVelocity = newYVel; }
};


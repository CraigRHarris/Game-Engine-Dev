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

	void UpdatePosition(float x, float y);
	virtual bool IsColliding(Physics* Other);
	void SetGrounded(bool grounded) { isGrounded = grounded; }

	void CheckForGroundCollision(Physics* Ground);

	virtual void HandleGravity(float & Ypos);
};


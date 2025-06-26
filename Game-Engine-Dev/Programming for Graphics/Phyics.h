#pragma once
#include "SDL.h"
class Physics
{
private:
	bool isGrounded;
	SDL_FRect CollisionRect;
	SDL_FRect _intersection;
	float yVelocity;

public:
	Physics(float W, float H) : CollisionRect{ 0.0f, 0.0f, W, H }, isGrounded{ false }, yVelocity{ 0.0f }, _intersection{ 0.0f, 0.0f, W, H } {}

	SDL_FRect GetCollisionRect() const { return CollisionRect; }
	SDL_FRect GetIntersectionRect() const { return _intersection; }


	virtual void HandleGravity(float& Ypos);
	void UpdatePosition(float x, float y);

	virtual bool IsColliding(SDL_FRect Other);
	virtual bool IsColliding(SDL_Rect Other);

	void CheckForGroundCollision(SDL_FRect Ground, float& yPos);

	void SetGrounded(bool grounded) { isGrounded = grounded; }
	bool GetGrounded() const { return isGrounded; }

	void SetYVelocity(float newYVel) { yVelocity = newYVel; }
};


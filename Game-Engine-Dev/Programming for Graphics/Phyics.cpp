#include "Phyics.h"

void Physics::UpdatePosition(float x, float y)
{
	CollisionRect.x = x;
	CollisionRect.y = y;
}

bool Physics::IsColliding(SDL_FRect Other)
{
	return SDL_HasIntersectionF(&CollisionRect, &Other);
}

void Physics::CheckForGroundCollision(SDL_FRect Ground, float& yPos)
{
	if (IsColliding(Ground))
	{
		isGrounded = true;
;
		SDL_FRect intersection;

		SDL_IntersectFRect(&Ground, &CollisionRect, &intersection);

		int yDiff = CollisionRect.y - Ground.y;
		if (yDiff < 0)
		{
			//yPos -= intersection.h;
		}
	}
	else
	{
		isGrounded = false;
	}
}

void Physics::HandleGravity(float& Ypos)
{
	if (!isGrounded)
	{
		const float gravity = 0.98;

		yVelocity += gravity;

		Ypos += yVelocity;
	}
	else {
		yVelocity = 0.0f;// velocity is 0 if grounded
	}
}

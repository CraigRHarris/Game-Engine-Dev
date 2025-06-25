#include "Phyics.h"

void Physics::UpdatePosition(float x, float y)
{
	CollisionRect.x = x;
	CollisionRect.y = y;
}

bool Physics::IsColliding(Physics* Other)
{
	return SDL_HasIntersectionF(&CollisionRect, &Other->GetCollisionRect());
}

void Physics::CheckForGroundCollision(Physics* Ground)
{
	if (IsColliding(Ground))
	{
		isGrounded = true;


		SDL_FRect groundRect = Ground->GetCollisionRect();
		SDL_FRect intersection;

		SDL_IntersectFRect(&groundRect, &CollisionRect, &intersection);

		int yDiff = CollisionRect.y - groundRect.y;
		if (yDiff < 0)
		{
			//m_y -= intersection.h;
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

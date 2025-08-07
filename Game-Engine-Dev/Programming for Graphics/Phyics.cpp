#include "Phyics.h"
#include "Bitmaps.h"

void Physics::UpdatePosition(float x, float y)
{
	CollisionRect.x = x;
	CollisionRect.y = y;
}

bool Physics::IsColliding(SDL_FRect Other)//this is for the box that the player hits on the ground collision box
{
	return SDL_HasIntersectionF(&CollisionRect, &Other);
}

bool Physics::IsColliding(SDL_Rect Other)// this is for the player collision box
{
	SDL_FRect otherRect = SDL_FRect{ static_cast<float>(Other.x), static_cast<float>(Other.y),
									 static_cast<float>(Other.w) ,static_cast<float>(Other.h) };
	return SDL_HasIntersectionF(&CollisionRect, &otherRect);
}

void Physics::CheckForGroundCollision(SDL_FRect Ground, float& yPos)
{
	// add the side collision on the left for obects to drip of the side
	float startX = CollisionRect.x;
	float startY = CollisionRect.y + CollisionRect.h;
	float endX = startX;
	float endY = startY + 3.0f;
	auto leftRayCheck = SDL_IntersectFRectAndLine(&Ground, &startX, &startY, &endX, &endY);

	// add the side collision on the right for obects to drip of the side
	startX = CollisionRect.x + CollisionRect.w;
	startY = CollisionRect.y + CollisionRect.h;
	endX = startX;
	endY = startY + 3.0f;
	auto rightRayCheck = SDL_IntersectFRectAndLine(&Ground, &startX, &startY, &endX, &endY);

	if (leftRayCheck || rightRayCheck)// checking the if object is interacting with rays
	{
		isGrounded = true;

		while (SDL_IntersectFRect(&Ground, &CollisionRect, &_intersection)) {
			yPos -= _intersection.h;
			CollisionRect.y = yPos;
		}
	}
	else if (!leftRayCheck && !rightRayCheck) {
		isGrounded = false;
	}

}

void Physics::HandleGravity(Bitmap* object)//making the gravity
{
	if (!isGrounded)
	{
		const float gravity = 0.98;

		yVelocity += gravity;

		object->UpdateY(yVelocity);
	}
	else {
		yVelocity = 0.0f;// velocity is 0 if grounded
	}
}

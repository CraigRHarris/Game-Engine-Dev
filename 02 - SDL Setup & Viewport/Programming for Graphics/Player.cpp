#include "Player.h"
#include "Bitmaps.h"
#include <format>
#include <iostream>

void Player::Update() {
	if (!isGrounded)
	{
		const float gravity = 0.98;

		yVelocity += gravity;

		m_y += yVelocity;
	}
	else {
		yVelocity = 0.0f;// velocity is 0 if grounded
	}
}

void Player::FixGroundCollision(Bitmap* ground)
{
	if (IsColliding(ground))
	{
		isGrounded = true;
		

		SDL_Rect groundRect = ground->GetTransformRect();
		SDL_Rect playerRect = GetTransformRect();
		SDL_Rect intersection;

		SDL_IntersectRect(&groundRect, &playerRect, &intersection);

		int yDiff = playerRect.y - groundRect.y;
		if (yDiff < 0)
		{
			m_y -= intersection.h;
		}

	}
	else
	{
		isGrounded = false;
	}
}

void Player::Jump()
{
	isGrounded = false;
	yVelocity = -jumpForce;

	/*if (isGrounded)
	{
		yVelocity = -jumpForce;
		isGrounded = false;
	}*/
}

void Player::GUIDraw()
{
	Bitmap::GUIDraw();

	ImGui::Begin("Selection");

	ImGui::InputInt("Keys:", &KeysCollected);


	ImGui::End();
}


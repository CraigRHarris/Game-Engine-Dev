#include "Player.h"
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
		yVelocity = 0.0f;
	}
}

void Player::FixGroundCollision(Bitmap* ground)
{
	if (IsColliding(ground))
	{
		isGrounded = true;
		int cx = m_x + (m_w / 2); // generating center point
		int cy = m_y + (m_h / 2);

		SDL_Rect groundRect = ground->GetTransformRect();

		int ground_cx = groundRect.x + (groundRect.w / 2); // generating center point
		int ground_cy = groundRect.x + (groundRect.h / 2);

		int DistBetween = ground_cy - cy;

		int OverlapAmount = (groundRect.h + m_h) / 2;
		int AmountToMove = 0;
		if (DistBetween < OverlapAmount)
		{
			AmountToMove = DistBetween - OverlapAmount;
		}

		m_y += AmountToMove;

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
}

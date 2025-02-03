#include "Player.h"
#include <format>

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
	if (CheckCollision(ground))
	{
		isGrounded = true;
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

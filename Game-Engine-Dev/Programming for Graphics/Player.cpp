#include "Player.h"
#include "Bitmaps.h"
#include <format>
#include <iostream>

void Player::Update() 
{
	physics->UpdatePosition(m_x, m_y);
	physics->HandleGravity(m_y);
}

void Player::FixGroundCollision(Bitmap* ground)
{
	SDL_Rect groundRect = ground->GetTransformRect();

	physics->CheckForGroundCollision(SDL_FRect{ static_cast<float>(groundRect.x), static_cast<float>(groundRect.y), 
												static_cast<float>(groundRect.w) ,static_cast<float>(groundRect.h) }, m_y);
}

void Player::Jump()
{
	physics->SetGrounded(false);
	physics->SetYVelocity(-jumpForce);

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


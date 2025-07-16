#include "Player.h"
#include "Bitmaps.h"
#include "Input.h"
#include "Pickup.h"
#include "Enemy.h"
#include <format>
#include <iostream>

void Player::draw()
{
	Bitmap::draw();

	auto intersectionRect = physics->GetIntersectionRect();// the red box that corllides with groung
	auto collisionRect = physics->GetCollisionRect();// player collision box

	SDL_SetRenderDrawColor(_pRenderer, 255, 0, 255, 255);
	SDL_RenderDrawRectF(_pRenderer, &collisionRect);
	SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);

	SDL_SetRenderDrawColor(_pRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRectF(_pRenderer, &intersectionRect);
	SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);
}

void Player::Update(const std::vector<Bitmap*>& platforms, std::vector<Pickup*>& pickups, std::vector<Enemy*>& enemies)
{
	if (!jumpedThisFrame) {
		for (const auto& platform : platforms) {
			FixGroundCollision(platform);
			if (physics->GetGrounded()) break;
		}
	}

	if (physics->GetGrounded() && isStunned) {
		isStunned = false;
	}

	for (auto pickup : pickups) { // player colliding with key
		if (physics->IsColliding(pickup->GetTransformRect())) {
			_score++;
			pickups.erase(find(pickups.begin(), pickups.end(), pickup));
			break;
		}
	}

	if (!isStunned) {
		for (auto enemy : enemies)
		{
			if (physics->IsColliding(enemy->GetTransformRect())) //trying to get the enemy to collid with player
			{
				auto enemyxPos = enemy->GetPosition().x;
				float diff = enemyxPos - m_x;

				if ((diff < 0 && stunForce < 0.0f) || (diff > 0 && stunForce > 0.0f)) {
					stunForce *= -1.0f;
				}

				isStunned = true;
				Jump();

				_health--;
				break;
			}
		}
	}

	if (_health <= 0) {
		// handle dead
	}

	if (isStunned) {
		m_x += stunForce;
	}

	physics->HandleGravity(m_y);
	physics->UpdatePosition(m_x, m_y);
	

	jumpedThisFrame = false;
}

void Player::HandleInput(const Input& input)
{
	if (isStunned) return;

	if (input.KeyIsPressed(SDLK_a) || input.KeyIsPressed(SDLK_LEFT))
	{
		UpdateX(-4);// if key A is pressed, player will move left
		//Logger::Info("Left");
	}
	if (input.KeyIsPressed(SDLK_d) || input.KeyIsPressed(SDLK_RIGHT))
	{
		UpdateX(4);
		//Logger::Info("Right");
	}
	if (input.KeyIsPressed(SDLK_SPACE))
	{
		Jump();
		//Logger::Info("Jump");
	}
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
	jumpedThisFrame = true;

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
	ImGui::InputInt("Health", &_health);

	ImGui::End();
}


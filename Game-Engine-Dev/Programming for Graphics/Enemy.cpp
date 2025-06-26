#include "Enemy.h"


void Enemy::Update(const std::vector<Bitmap*>& platforms)
{
	for (const auto& platform : platforms) {
		FixGroundCollision(platform);
		if (physics->GetGrounded()) break;
	}

	physics->UpdatePosition(m_x, m_y);
	physics->HandleGravity(m_y);

	position EnemyPosition = GetPosition();
	moveSpeed = 3;

	//Left point
	if (EnemyPosition.x <= point_l && direction == -1)
	{
		direction = 1;
	}
	//Right point
	if (EnemyPosition.x >= point_r && direction == 1)
	{
		direction = -1;
	}
	xVelocity = moveSpeed * direction;
	UpdateX(xVelocity);
}

void Enemy::FixGroundCollision(Bitmap* ground)
{
	SDL_Rect groundRect = ground->GetTransformRect();

	physics->CheckForGroundCollision(SDL_FRect{ static_cast<float>(groundRect.x), static_cast<float>(groundRect.y),
												static_cast<float>(groundRect.w) ,static_cast<float>(groundRect.h) }, m_y);

}

void Enemy::GUIDraw()
{
	Bitmap::GUIDraw();

	ImGui::Begin("Selection");

	int* TempPosAddressArry[2] = { &point_l, &point_r };
	ImGui::InputInt2("Bounds:", *TempPosAddressArry);

	ImGui::SliderFloat("Movement Speed:", &moveSpeed, 0, 10);
	ImGui::End();
}
#include "Enemy.h"


void Enemy::Update()
{
	//Gravity
	if (!isGrounded)
	{
		const float gravity = 2;

		yVelocity = +gravity;

		m_y += yVelocity;
		isGrounded = false;
	}
	//floor
	else
	{
		isGrounded = true;
		yVelocity = 0.0f;
	}

}

void Enemy::FixGroundCollision(Bitmap* ground)
{
	while (IsColliding(ground))
	{
		m_y -= 1;
	}
}

void Enemy::MoveAI()
{
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

void Enemy::GUIDraw()
{
	Bitmap::GUIDraw();

	ImGui::Begin("Selection");

	int* TempPosAddressArry[2] = { &point_l, &point_r };
	ImGui::InputInt2("Bounds:", *TempPosAddressArry);

	ImGui::SliderFloat("Movement Speed:", &moveSpeed, 0, 10);
	ImGui::End();
}
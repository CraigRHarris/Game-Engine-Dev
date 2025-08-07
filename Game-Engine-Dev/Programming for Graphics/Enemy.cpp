#include "Enemy.h"


void Enemy::draw()
{
	Bitmap::draw();

	auto collisionRect = physics->GetCollisionRect();//drawing the box around the enemy to show collction hit boxs

	SDL_SetRenderDrawColor(_pRenderer, 0, 255, 0, 255);//green
	SDL_RenderDrawRectF(_pRenderer, &collisionRect);
	SDL_SetRenderDrawColor(_pRenderer, 255, 255, 255, 255);
}

void Enemy::Update(const std::vector<Bitmap*>& platforms)
{
	for (const auto& platform : platforms) //making the enemy and ground collid
	{
		FixGroundCollision(platform);
		if (physics->GetGrounded()) break;
	}

	physics->UpdatePosition(m_x, m_y);
	physics->HandleGravity(this);//gravity

	position EnemyPosition = GetPosition();//point of the enemy movment
	moveSpeed = 3;//speed of enemy

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

void Enemy::FixGroundCollision(Bitmap* ground)//making sure that the ground is colliding correctly
{
	SDL_Rect groundRect = ground->GetTransformRect();

	physics->CheckForGroundCollision(SDL_FRect{ static_cast<float>(groundRect.x), static_cast<float>(groundRect.y),
												static_cast<float>(groundRect.w) ,static_cast<float>(groundRect.h) }, m_y);

}

void Enemy::GUIDraw()
{
	Bitmap::GUIDraw();

	ImGui::Begin("Selection");

	int* TempPosAddressArry[2] = { &point_l, &point_r };//for position of enemy in hierarchy tools
	ImGui::InputInt2("Bounds:", *TempPosAddressArry);

	ImGui::SliderFloat("Movement Speed:", &moveSpeed, 0, 10);//for movement of enemy in hierarchy tools
	ImGui::End();
}
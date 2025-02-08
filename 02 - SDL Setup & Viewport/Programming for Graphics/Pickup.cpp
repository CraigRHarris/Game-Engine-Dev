#include "Pickup.h"
#include "Player.h"

#include <iostream>

bool Pickup::IsColliding(Bitmap* other)
{
	if (!enabled) return false;

	Player* player = dynamic_cast<Player*>(other);
	if (player == nullptr)
	{
		return false;
	}

	bool playerCol = Bitmap::IsColliding(other);

	if (playerCol)
	{
		player->addKey();
		enabled = false;
	}

	return true;
}
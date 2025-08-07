#include "Pickup.h"
#include "Player.h"
#include "Phyics.h"

#include <iostream>

bool Pickup::IsColliding(Bitmap* other)// is player colliding with object
{
	if (!enabled) return false;

	Player* player = dynamic_cast<Player*>(other);
	if (player == nullptr)
	{
		return false;
	}

	bool playerCol = Bitmap::IsColliding(other);

	if (playerCol) //collecting the key
	{
		player->addKey();
		enabled = false;
		Logger::Info("Key Collected.");
		return true;
	}

	return false;
}
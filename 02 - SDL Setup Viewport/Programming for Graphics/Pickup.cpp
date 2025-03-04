#include "Pickup.h"
#include "Player.h"

#include <iostream>

bool Pickup::IsColliding(Bitmap* other)
{
	if (!enabled) return false;

	Player* player = dynamic_cast<Player*>(other);// checks if we're colliding with the player
	if (player == nullptr)
	{
		return false;
	}

	bool playerCol = Bitmap::IsColliding(other);

	if (playerCol)
	{
		player->addKey();// add a Key to the total if player is colliding
		enabled = false;
		Logger::Info("Key Collected.");
		return true;
	}

	return false;
}
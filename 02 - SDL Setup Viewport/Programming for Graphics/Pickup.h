#pragma once
#include "Bitmaps.h"
#include "Logger.h"

class Pickup : public Bitmap
{
public:
	Pickup(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, const std::string ObjectName, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos,ObjectName, useTransparency) {
		Logger::Info("Pickup ");
	}

	bool IsColliding(Bitmap* other) override;

private:
	bool enabled{ true };

};


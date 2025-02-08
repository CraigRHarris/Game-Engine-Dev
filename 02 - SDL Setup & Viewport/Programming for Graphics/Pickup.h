#pragma once
#include "Bitmaps.h"
#include "Logger.h"

class Pickup : public Bitmap
{
public:
	Pickup(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos, useTransparency) {
		Logger::Info("Pickup constructor");
	}

	bool IsColliding(Bitmap* other) override;

private:
	bool enabled{ true };

};


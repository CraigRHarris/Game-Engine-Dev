#pragma once
#include "Bitmaps.h"
#include "Logger.h"

class Goal : public Bitmap
{
public:
	Goal(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, const std::string ObjectName, bool useTransparency = false) : Bitmap(renderer, texManager, fileName, xpos, ypos, ObjectName, useTransparency) {
		Logger::Info("Goal");
	}
};


#pragma once

#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Bitmap
{
private:

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	int m_x, m_y;

public:
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);
	~Bitmap();

	void draw();

	SDL_Texture* GetTextureRef()
	{
		return m_pbitmapTexture;
	}

	std::string FileName;

};


//Bitmaps and Fonts Tatorial on page 9 (but got a bit confused)
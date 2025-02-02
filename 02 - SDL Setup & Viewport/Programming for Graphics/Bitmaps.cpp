#include <string>
#include "Bitmaps.h"

#include "SDL.h"
#include "SDL_render.h"

using namespace std;

bool Bitmap::CheckCollision(Bitmap* Other)
{
	if (
		(m_x + m_w >= Other->m_x) && (m_x <= Other->m_x + Other->m_w) &&
		(m_y + m_h >= Other->m_y) && (m_y <= Other->m_y + Other->m_h)
		)
	{
		return true;
	}
	return false;
}



Bitmap::Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency)
{
	FileName = fileName;
	
	//store the rander for future configuring and drawing
	m_pRenderer = renderer;

	m_pbitmapTexture = NULL;
	// create the bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());

	if (!m_pbitmapSurface)
	{
		//bitmap not loaded? Output the error
		printf("SURFACE for bitmap '%s' not loaded! \n", fileName.c_str());
		printf("%\n", SDL_GetError());
	}
	else
	{
		//if we are to use the transparency, going to assume
		//the colour key is magenta (r=255, g=0, b=255)
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		// create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture)
		{
			//texture not loaded? Output the error
			printf("TEXTURE for bitmap '%s' not loaded! \n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
	}
	//store the position vals
	m_x = xpos;
	m_y = ypos;

	m_h = m_pbitmapSurface->h;
	m_w = m_pbitmapSurface->w;
}

void Bitmap::draw()
{
	//render the bitmap at the x/y coords
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x, m_y, m_pbitmapSurface->w, m_pbitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}
void Bitmap::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}
Bitmap::~Bitmap()
{
	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);

	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
}

// forward declare amd SDL stuff we need
struct SDL_Window;
struct SDL_Renderer;
class Bitmap;

class Game
{
private:

	//SDL stuff
	SDL_Window*   m_wondow;
	SDL_Renderer* m_renderer;
	bool          m_running;

	// bitmaps!
	Bitmap* m_monster;      //04-01
	Bitmap* m_monsterTrans; //04-01
	Bitmap* m_monsterTransKeyed; //04-01

	// void CheckEvents()  // will need this in the future
};
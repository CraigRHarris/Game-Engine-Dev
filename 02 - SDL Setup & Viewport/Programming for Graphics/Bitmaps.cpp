#include <string>
#include "Bitmaps.h"

#include "SDL.h"
#include "SDL_render.h"

using namespace std;

bool Bitmap::IsColliding(Bitmap* Other)
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



Bitmap::Bitmap(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, bool useTransparency)
{
	FileName = fileName;
	
	//store the rander for future configuring and drawing
	m_pRenderer = renderer;

	m_pbitmapTexture = texManager->Load(fileName, true, renderer, m_w, m_h);

	//store the position vals
	m_x = xpos;
	m_y = ypos;

}



void Bitmap::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}
Bitmap::~Bitmap()
{

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

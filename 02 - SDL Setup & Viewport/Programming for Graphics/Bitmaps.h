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


protected:
	float			 m_x, m_y, m_h, m_w;

	bool isGrounded{ false };

public:
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);
	~Bitmap();
	std::string FileName;

	void SetPosition(float x, float y);

	bool CheckCollision(Bitmap* Other);

	void UpdateX(float xDelta) { m_x += xDelta; }
	void UpdateY(float yDelta) { m_y += yDelta; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }

	float GetX() const { return m_x; }
	float GetY() const { return m_y; }

	void SetGrounded(bool grounded) { isGrounded = grounded; }

	//SDL_Rect GetTransformRect()
	//{
	//	SDL_Rect BitmapRect;
	//	BitmapRect.w = m_w;
	//	BitmapRect.y = m_y;
	//	BitmapRect.x = m_x;
	//	BitmapRect.h = m_h;
	//}

	void draw();

	SDL_Texture* GetTextureRef()
	{
		return m_pbitmapTexture;
	}

	std::string FileName;

};


//Bitmaps and Fonts Tatorial on page 9 (but got a bit confused)
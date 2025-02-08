#pragma once

#include <string>
#include "SDL.h"

#include "TextureManager.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
struct position { float x; float y; };

class Bitmap
{
private:

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;
	//SDL_Rect CollisionRect;

protected:
	float  m_x, m_y;
	int m_h, m_w;


public:
	
	bool isGrounded{ false };
	Bitmap(SDL_Renderer* renderer, TextureManager* texManager,std::string fileName, int xpos, int ypos, bool useTransparency = false);
	virtual ~Bitmap();
	std::string FileName;

	virtual bool IsColliding(Bitmap* Other);

	void SetPosition(float x, float y);
	position GetPosition();
	//bool CheckCollision(Bitmap* Other);

	void UpdateX(float xDelta) { m_x += xDelta; }
	void UpdateY(float yDelta) { m_y += yDelta; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }

	float GetX() const { return m_x; }
	float GetY() const { return m_y; }

	void SetGrounded(bool grounded) { isGrounded = grounded; }

	SDL_Rect GetTransformRect()
	{
		return SDL_Rect{ m_w , m_h, m_w, m_h };
	}

	void draw();

	SDL_Texture* GetTextureRef()
	{
		return m_pbitmapTexture;
	}
	

};


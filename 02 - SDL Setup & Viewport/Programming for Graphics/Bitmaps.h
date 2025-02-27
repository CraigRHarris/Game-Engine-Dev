#pragma once

#include <string>
#include "SDL.h"

#include "TextureManager.h"
#include "I_GuiWindow.h"
#include "I_SceneNode.h"


struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
struct position { float x; float y; };

class Bitmap : public I_SceneNode, public I_GuiWindow
{
private:

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;
	SDL_Rect CollisionRect;

protected:
	float  m_x, m_y;
	int m_h, m_w;


public:
	
	static int objectCount;
	bool isGrounded = false;
	std::string ObjectName = "Name Object";

	Bitmap(SDL_Renderer* renderer, TextureManager* texManager,std::string fileName, int xpos, int ypos, const std::string _ObjectName, bool useTransparency = false);
	virtual ~Bitmap();
	std::string FileName;
	
	virtual bool IsColliding(Bitmap* Other);

	void SetPosition(float x, float y);
	position GetPosition();

	void UpdateX(float xDelta) { m_x += xDelta; }
	void UpdateY(float yDelta) { m_y += yDelta; }

	virtual void GUIDraw();

	void GuiDrawChildGUI();

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }


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


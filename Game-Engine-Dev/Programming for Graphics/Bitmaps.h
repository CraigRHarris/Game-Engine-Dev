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

	SDL_Surface* _pbitmapSurface;
	SDL_Texture* _pbitmapTexture;
	SDL_Rect CollisionRect;

protected:
	float  m_x, m_y;
	int m_h, m_w;
	SDL_Renderer* _pRenderer;

public:
	
	static int objectCount;
	//bool isGrounded = false;
	std::string Object = "Name Object";


	/**
	* storing the render of assets to configurer later on.loading the texture for asessts.param checking the surface on the asesst.
	* Going tough each object.
	* @param renderer 
	* @param texManager loading the texture for asessts.
	* @param fileName checking the name of the asesst.
	* @param postion of assets.
	* @param object name of the asset.
	* @param transparent to see if it neededs background.
	*/
	Bitmap(SDL_Renderer* renderer, TextureManager* texManager,std::string fileName, int xpos, int ypos, const std::string _ObjectName, bool useTransparency = false);
	virtual ~Bitmap();
	std::string FileName;
	

	/**
	Checks if an object's point is inside another's.
	*/
	virtual bool IsColliding(Bitmap* Other);
	
	void SetPosition(float x, float y);
	
	position GetPosition();

	void UpdateX(float xDelta) { m_x += xDelta; }
	void UpdateY(float yDelta) { m_y += yDelta; }

	virtual void GUIDraw();

	/**
	Its for the Hierarchy to add the objects to a different object(parent) in the hierarchy list.
	*/
	void GuiDrawChildGUI();

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }

	SDL_Rect GetTransformRect()
	{
		return SDL_Rect{ static_cast<int>(m_x) , static_cast<int>(m_y), m_w, m_h };
	}

	virtual void draw();

	SDL_Texture* GetTextureRef()
	{
		return _pbitmapTexture;
	}
};


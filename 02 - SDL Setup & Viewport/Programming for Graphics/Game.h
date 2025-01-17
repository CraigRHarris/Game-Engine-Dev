#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "Bit"

#include "AssetEditor.h"


using namespace std;


class SDL_Window;
class SDL_Renderer;
class Bitmap;

class Game
{
private:
	

	void CheckEvents();
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);
	AssetEditor* assetEditor;

public:
	//SDL Stuff
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool		  m_running;

	//bitmaps!
	Bitmap* m_monster;
	Bitmap* m_monsterTrans;
	Bitmap* m_monsterTransKeyed;

	TTF_Font* m_pSmallFont;
	TTF_Font* m_pBigFont;
	
	Game();
	~Game();

	void SetDisplayColour(int red,int green, int blue, int alpha);
	void Update();

	

};
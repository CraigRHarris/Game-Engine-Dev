#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "Bit"

#include "AssetEditor.h"
#include "Player.h"
#include "Input.h"


using namespace std;


class SDL_Window;
class SDL_Renderer;
class Bitmap;

class Game
{
private:
	
	//Bitmaps
	Player* player{ nullptr };
	Bitmap* m_monsterTrans{ nullptr };
	Bitmap* m_monsterTransKeyed{ nullptr };
	Bitmap* m_ground{ nullptr };

	TTF_Font* m_pSmallFont{ nullptr };
	TTF_Font* m_pBigFont{ nullptr };

	void CheckEvents();
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);
	AssetEditor* assetEditor;
	Input input;
	bool _isRunning{ true };

public:
	//SDL Stuff
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool		  m_running;

	//bitmaps!
	//Bitmap* m_monster;
	//Bitmap* m_monsterTrans;
	//Bitmap* m_monsterTransKeyed;
	
	Game();
	~Game();

	void SetDisplayColour(int red,int green, int blue, int alpha);
	void Update();

	bool isRunning() { return _isRunning; }

};
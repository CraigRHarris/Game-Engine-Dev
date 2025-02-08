#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "Bit"
#include <cstdint>

#include "AssetEditor.h"
#include "Player.h"
#include "Input.h"
#include "TextureManager.h"
#include "Pickup.h"


using namespace std;

class SDL_Window;
class SDL_Renderer;
class AssetEditor;
class Enemy;


class Game
{
private:
	
	//Bitmaps
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Bitmap* m_ground{ nullptr };
	Pickup* pickup{ nullptr };

	TTF_Font* m_pSmallFont{ nullptr };
	TTF_Font* m_pBigFont{ nullptr };

	void CheckEvents();
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);
	AssetEditor* assetEditor{ nullptr };
	Input input;
	bool _isRunning{ true };

	TextureManager* _texManager;

	SDL_Window* m_Window{ nullptr }; // Tells the compiler that there will be a struct named SDL_Window defined.
	SDL_Renderer* m_Renderer{ nullptr };
	


public:
	
	Game();
	~Game();
	void Update(void);
	void SetDisplayColour(int r, int g, int b, int a);

	bool isRunning() { return _isRunning; }
	void addKey();
};
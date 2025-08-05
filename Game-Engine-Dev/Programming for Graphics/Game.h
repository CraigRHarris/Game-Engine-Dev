#pragma once
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "Bit"
#include <cstdint>

#include "AssetEditor.h"
#include "Input.h"
#include "TextureManager.h"
#include "Pickup.h"
#include "SceneManager.h"
#include "ProfilerSystem.h"
#include "Goal.h"

using namespace std;

struct SDL_Window;
struct SDL_Renderer;
class AssetEditor;
class Enemy;
class Hierarchy;
class Player;// can change the includes to this but needed to include in the game.ccp

class Game
{
private:

	std::vector<Bitmap*> Content;

	int mouseDownCount{ 0 };
	bool checkMouseJustPressed();

	void startDragObject();
	void endDragObject();

	bool isMouseDown{ false };

	SceneManager _sceneManager;
	
	//Bitmaps
	std::vector<Bitmap*> AllObjects;
	std::vector<Enemy*> enemies;
	std::vector<Bitmap*> platforms;
	std::vector<Pickup*> pickups;

	Hierarchy* hierarchy{ nullptr };
	I_SceneNode* Root{ nullptr };

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Bitmap* m_ground{ nullptr };
	Pickup* pickup{ nullptr };
	Bitmap* SelectedObject{ nullptr };
	Goal* goal{ nullptr };

	TTF_Font* m_pSmallFont{ nullptr };
	TTF_Font* m_pBigFont{ nullptr };

	/**
	This is for the inputs function for them to work 
	*/
	void CheckEvents();


	/**
	* Loading the font assets. Then creating the surface render for the the text with a copy.
	* @ param msg
	* @ param Position
	* @ param font
	* @ param colour
	*/
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);
	
	Bitmap* currentAsset;

	AssetEditor* assetEditor{ nullptr };
	Input input;
	bool _isRunning{ true };

	TextureManager* _texManager{ nullptr };
	Profiler* profiler{ nullptr };

	SDL_Window* _Window{ nullptr }; // Tells the compiler that there will be a struct named SDL_Window defined.
	SDL_Renderer* _Renderer{ nullptr };
	
	void loadScene(Scene& scene);

	void clearExistingObjects();

	Scene newScene;
	string levels[2] = { "assets/Level1.json", "assets/Level2.json" };
	int currentLV = 0;

public:
	

	Game();
	~Game();

	void addPlayer(const position& pos);
	void addGoal(const position& pos, const std::string& file);
	void addGround(int x, int y, const std::string& file);
	void addEnemy(int x, int y, const std::string& file, int leftBound, int rightBound);
	void addPickup(int x, int y, const std::string& file);


	/**
	Updating fuctions every frame in this fuction.
	*/
	void Update(void);
	
	void SetDisplayColour(int r, int g, int b, int a);

	bool isRunning() { return _isRunning; }
	
};
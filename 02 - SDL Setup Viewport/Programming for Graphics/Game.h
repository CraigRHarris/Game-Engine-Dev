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
#include "SceneManager.h"
#include "ProfilerSystem.h"
#include "Goal.h"


using namespace std;

class SDL_Window;
class SDL_Renderer;
class AssetEditor;
class Enemy;
class Hierarchy;

class Game
{
private:

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
	std::vector<Goal*> goals;
	Hierarchy* hierarchy;
	I_SceneNode* Root;

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
	
	AssetEditor* assetEditor{ nullptr };
	Input input;
	bool _isRunning{ true };

	TextureManager* _texManager;
	Profiler* profiler;

	SDL_Window* m_Window{ nullptr }; // Tells the compiler that there will be a struct named SDL_Window defined.
	SDL_Renderer* m_Renderer{ nullptr };
	
	void loadScene(Scene& scene);

	void clearExistingObjects();

	Scene newScene;
	string levels[2] = { "assets/Level1.json", "assets/Level2.json" };
	int currentLV = 0;

public:
	
	/**
	All of the fuctions in the game scene.
	*/
	Game();
	~Game();

	/**
	* Going though each object to get the bitmap of that object. Sets the object, then add it to the hierarchy for each object. 
	* @ param type
	* @ param file
	* @ param positon
	* @ param name
	* @ param Transparency
	* @ param isNew
	* @ param left
	* @ param right
	*/
	void addEntity(EntityType type, const std::string& file, int x, int y, const std::string& name, bool trans, bool isNew = false, int left = 0, int right = 0);
	
	/**
	Updating fuctions every frame in this fuction.
	*/
	void Update(void);
	
	void SetDisplayColour(int r, int g, int b, int a);

	bool isRunning() { return _isRunning; }
	
};
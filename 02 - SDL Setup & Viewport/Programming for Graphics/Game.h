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

	Hierarchy* hierarchy;
	I_SceneNode* Root;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Bitmap* m_ground{ nullptr };
	Pickup* pickup{ nullptr };
	Bitmap* SelectedObject{ nullptr };

	TTF_Font* m_pSmallFont{ nullptr };
	TTF_Font* m_pBigFont{ nullptr };

	void CheckEvents();
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
public:
	
	Game();
	~Game();
	void addEntity(EntityType type, const std::string& file, int x, int y, const std::string& name, bool trans, bool isNew = false, int left = 0, int right = 0);
	void Update(void);
	void SetDisplayColour(int r, int g, int b, int a);

	bool isRunning() { return _isRunning; }
	
};
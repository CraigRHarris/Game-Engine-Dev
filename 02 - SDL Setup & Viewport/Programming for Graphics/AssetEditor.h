#pragma once
#include <SDL.h>
#include <vector>
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "Bitmaps.h"

class Bitmap;
class Game;

class AssetEditor
{
public:
	bool hasSelected{ false };
	Bitmap* AssetMouseDrag = nullptr;
	AssetEditor(SDL_Renderer* renderer, SDL_Window* window, TextureManager* texManager);

	//std::vector<Bitmap*> content;
	SDL_Renderer* p_Renderer;
	SDL_Window* p_Window;

	void Update(); 
	std::vector<Bitmap*> content;
	std::vector<Bitmap*> Dragables;

private:
	Game* _game;
	TextureManager* _texManager;

};


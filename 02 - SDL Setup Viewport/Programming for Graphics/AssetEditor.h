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
	bool _selected{ false };
	Bitmap* AssetMouseDrag = nullptr;
	
	/**
	This is finding the assets in the files and putting them into a bitmap.
	*/
	AssetEditor(SDL_Renderer* renderer, SDL_Window* window, TextureManager* texManager, Game* game );

	//std::vector<Bitmap*> content;
	SDL_Renderer* _Renderer;
	SDL_Window* _Window;

	/**
	Finding the file for each asset to use when mouse is pressed down to drag onto the scene.
	*/
	void Update(); 
	std::vector<Bitmap*> content;
	

private:
	Game* _game;
	TextureManager* _tManager;

};


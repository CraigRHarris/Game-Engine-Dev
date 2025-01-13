#pragma once
#include <SDL.h>
#include <vector>

class Bitmap;

class AssetEditor
{
public:

	AssetEditor(SDL_Renderer* renderer);

	Bitmap* AssetMousDrag =nullptr;
	std::vector<Bitmap*> content;
	SDL_Renderer* p_Renderer;


	void Update();
};


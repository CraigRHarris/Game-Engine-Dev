#pragma once
#include <map>
#include <SDL.h>
#include <string>

struct TextureData
{
	SDL_Texture* tex;
	int width;
	int height;
};


class TextureManager
{
public:
	std::map<std::string, TextureData> m_textureMap;
	TextureManager();
	~TextureManager();

	SDL_Texture* Load(const std::string fileName, bool useTransparancy, SDL_Renderer* PRenderer, int& width, int& height);
	void Unload(const std::string fileName);
};


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

	SDL_Surface* _surface;

	/**
	* Loading the texture by giving it a width and height. Print error if it didn't load.
	* @param fileName finding the file.
	* @param Transparancy If it needs to have a background.
	* @param renderer try to render the asset.
	* @param width 
	* @param height
	*/
	SDL_Texture* Load(const std::string fileName, bool useTransparancy, SDL_Renderer* PRenderer, int& width, int& height);
	
	/**
	* Unload texture by finding texture. After that destroy texture.
	* @param filename finding the file.
	*/
	void Unload(const std::string fileName);
};


#include "TextureManager.h"

TextureManager::TextureManager() { }


TextureManager::~TextureManager()
{
	for (auto value : m_textureMap)
	{
		SDL_DestroyTexture(value.second.tex);
		value.second.tex = nullptr;
	}
}

void TextureManager::Unload(const std::string fileName)
{
	auto searchResult = m_textureMap.find(fileName);
	if (searchResult != m_textureMap.end())
	{
		SDL_DestroyTexture(m_textureMap[fileName].tex);
		m_textureMap[fileName].tex = nullptr;
		m_textureMap.erase(searchResult);
	}
}

SDL_Texture* TextureManager::Load(const std::string fileName, bool useTransparancy, SDL_Renderer* PRenderer, int& width, int& height)
{
	SDL_Texture* m_pbitmapTexture = nullptr;

	//check map for file name existance
	auto searchresult = m_textureMap.find(fileName);
	if (searchresult != m_textureMap.end())
	{
		TextureData texData = m_textureMap[fileName];
		width = texData.width;
		height = texData.height;
		m_pbitmapTexture = texData.tex;
	}
	else // not found, load, save and return
	{

		//if file does not exist in map
		_surface = SDL_LoadBMP(fileName.c_str());
		
		if (!_surface)
		{
			printf("SURFACE for bitmap '%s' not loaded\n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
		else
		{
			if (useTransparancy)
			{
				Uint32 colourKey = SDL_MapRGB(_surface->format, 255, 0, 255);
				SDL_SetColorKey(_surface, SDL_TRUE, colourKey);
			}
			m_pbitmapTexture = SDL_CreateTextureFromSurface(PRenderer, _surface);
			if (!m_pbitmapTexture)
			{
				printf("TEXTURE for bitmap '%s' not loaded!\n", fileName.c_str());
				printf("%s\n", SDL_GetError());
			}

			width = _surface->w;
			height = _surface->h;

			SDL_FreeSurface(_surface);

			TextureData texData{ m_pbitmapTexture , width, height };

			m_textureMap[fileName] = texData;
		}
	}
	return m_pbitmapTexture;
}
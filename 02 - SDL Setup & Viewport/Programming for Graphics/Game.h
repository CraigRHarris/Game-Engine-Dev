#pragma once


class SDL_Window;
class SDL_Renderer;
class Game
{
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

public:
	Game();
	~Game();

	void SetDisplayColour(void);

};
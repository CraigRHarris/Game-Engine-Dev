#ifndef GAME_H
#define GAME_H
#include "Game.h"

#include <SDL.h>
#include <stdio.h>


#endif




Game::Game()
{
	m_Window = nullptr;
	m_Renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_VIDEO);

	//create the window
	m_Window = SDL_CreateWindow(
		"My First Window", //title
		250,               // inital x psition
		50,                //        y
		640,               // width, in pixels
		480,               // height
		0                  // window behaviour flags (ignore for now)
	);

	if (!m_Window)
	{
		printf("WINDOW initialistion failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();
		return;
	}

	//now create the renderer
	m_Renderer = SDL_CreateRenderer(
		m_Window,        // link the renderer to our newly created win 
		-1,              // index rendering driver (igoree for now)
		0                // renderer behaviuor flags (igoree for now)
	);

	if (!m_Renderer)
	{
		printf("ENDERER initialistion failed: %\n", SDL_GetError());
		printf("Press any key to cintinue\n");
		getchar();

		return;
	}


	//clean up.
	//don't gorget - we destroy in the REVERSE order they were created 

	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window)
	{
		SDL_DestroyWindow(m_Window);
	}

	if (m_Renderer)
	{
		//render in a pretty red colour
		int result = SDL_SetRenderDrawColor(
			m_Renderer,       //target render
			255,              //r
			0,                //g
			0,                //b
			255               //alpha
		);

		//wipe the display to the colour we just set.
		SDL_RenderClear(m_Renderer);

		//show what we've drawn (i.e. a red screen).
		SDL_RenderPresent(m_Renderer);

		//pause for 5secs
		SDL_Delay(5000);     //SDL_Delay takes millisecs
	}
}

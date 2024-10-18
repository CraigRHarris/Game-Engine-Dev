#ifndef GAME_H
#define GAME_H
#include "Game.h"
#include "Bitmaps.h"   //04-01

#include <SDL.h>
#include <stdio.h>


#endif




Game::Game()
{
	m_running = true;

	m_Window = nullptr;
	m_Renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

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

	//creating some bitmaps
	m_monster = new Bitmap(m_Renderer, "assets/monster.bmp", 100, 100);                      //04-01
	m_monsterTrans = new Bitmap(m_Renderer, "assets/monsterTrans.bmp", 200, 100);            //04-01
	m_monsterTransKeyed = new Bitmap(m_Renderer, "assets/monsterTrans.bmp", 300, 100, true); //04-01

	// read in the font
	m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15); // font size
	m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50);
};

Game::~Game() //destoy with the symbol ~ in front of fuction
{
	//destroy the bitmaps
	if (m_monsterTransKeyed) //04-01
		delete m_monsterTransKeyed;

	if (m_monsterTrans)          //04-01
		delete m_monsterTrans;

	if (m_monster)       //04-01
		delete m_monster;

	// drstroy the font
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);
}

void Game::SetDisplayColour(int red, int green, int blue, int alpha)
{

}

void Game::Update()
{
	CheckEvents();

	//wipe the display to the currently set colour.
	m_monster->draw();
	m_monsterTrans->draw();
	m_monsterTransKeyed->draw();

	//show what we're drawn
	SDL_RenderPresent(m_Renderer);

	//pause for 1/60th sec (ish)
	SDL_Delay(16); //SDLDelay takes millisecs
}
#ifndef GAME_H
#define GAME_H
#include "Game.h"
#include "Bitmaps.h"   //04-01
#include "Logger.h"

#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include "SDL_ttf.h"
#include "Bitmaps.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "AssetEditor.h"


//#include "imgui_internal.h"

#endif




void Game::CheckEvents()
{
	SDL_Event event;
	//loop throuh all the events in the event list
	while (SDL_PollEvent(&event) != NULL)
	{
	//	// Check for keydown
	//	if (event.type == SDL_KEYDOWN)
	//	{
	//		input.EventKeyPressed(event.key.keysym.sym);
	//	}
	//	//check for key up
	//	else if (event.type == SDL_KEYUP)
	//	{
	//		input.EventKeyReleased(event.key.keysym.sym);
	//	}
	//	else if (event.type == SDL_QUIT)
	//	{
	//		_isRunning = false;
	//	}
	//}

	//if (input.KeyIsPressed(SDLK_ESCAPE))
	//{
	//	_isRunning = false;
	//}

}

void Game::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour)
{

	
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int texW = 0;
	int texH = 0;

	//SDL_Color color = { 0, 0, 0 };

	//char msg[100];
	//sprintf_s(msg, "Checks: %d", m_checkTally);

	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);
	if (!surface)
	{
		//surface not loaded? Output the error
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		if (!texture)
		{
			//surface not loaded? Output the error
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };

			SDL_RenderCopy(m_Renderer, texture, NULL, &textRect);
		}
	}

	if (texture)
		SDL_DestroyTexture(texture);
	if (surface)
		SDL_FreeSurface(surface);
}

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


	
	assetEditor = new AssetEditor(m_Renderer);
	

	

	//creating some bitmaps
	m_monster = new Bitmap(m_Renderer, "assets/monster.bmp", 100, 100);                      //04-01
	m_monsterTrans = new Bitmap(m_Renderer, "assets/monsterTrans.bmp", 200, 100);            //04-01
	m_monsterTransKeyed = new Bitmap(m_Renderer, "assets/monsterTrans.bmp", 300, 100, true); //04-01

	// read in the font
	m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15); // font size
	m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50);


	// inGUI Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	SDL_DisplayMode DisplayMode;
	SDL_GetCurrentDisplayMode(0, &DisplayMode);
	ImGuiSDL::Initialize(game->m_Renderer, DisplayMode.w, DisplayMode.h);
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnble;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(game->m_Window, SDL_GL_GetCurrentContext());
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

	if (player)
		delete player;

	if (m_ground)
		delete m_ground;

	// destroy the font
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);


	//clean up.
	//don't gorget - we destroy in the REVERSE order they were created 

	if (m_Renderer)
	{
		SDL_DestroyRenderer(m_Renderer);
	}


}

void Game::SetDisplayColour(int red, int green, int blue, int alpha)
{
	int result = SDL_SetRenderDrawColor(
		m_Renderer,       //target render
		red,              //r
		green,                //g
		blue,                //b
		alpha		//alpha
	);
}

void Game::Update()
{
	SDL_RenderClear(m_Renderer);

	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	bool show = true;
	//ShowExampleAppDockSpace(&show);

	ImGui::ShowDemoWindow(nullptr);

	assetEditor->Update();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	



	CheckEvents();



	//m_monster->update(&input);

	player->SetGrounded(player->CheckCollision(m_ground));

	if (input.KeyIsPressed(SDLK_a) || input.KeyIsPressed(SDLK_LEFT))
	{
		player->UpdateX(-1);
	}
	if (input.KeyIsPressed(SDLK_d) || input.KeyIsPressed(SDLK_RIGHT))
	{
		player->UpdateX(1);
	}
	if (input.KeyIsPressed(SDLK_SPACE))
	{
		player->Jump();
	}


	//wipe the display to the currently set colour.
	m_monster->draw();
	m_monsterTrans->draw();
	m_monsterTransKeyed->draw();
	//vector assests  - push onto the game  - loop for drawing draw for object
	

	//draw the text
	UpdateText("Small Red", 50, 10, m_pSmallFont, { 255, 0, 0 });
	UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0, 0, 255 });

	char char_array[] = "Big White";
	UpdateText(char_array, 50, 140, m_pBigFont, { 255, 255, 255});

	int testNumber = 1234;
	string testString = "Test Number: ";
	testString += to_string(testNumber);
	UpdateText(testString, 50, 210, m_pBigFont, { 255, 255, 255 });

	//show what we've drawn
	SDL_RenderPresent(m_Renderer);

	// pause for 1/60th second (ish)
	SDL_Delay(16);    //SDL_Delay takes millisecs
	
}


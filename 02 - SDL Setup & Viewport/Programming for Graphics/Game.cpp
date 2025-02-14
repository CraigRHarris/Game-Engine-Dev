#ifndef GAME_H
#define GAME_H
#include "Game.h"
#include "Bitmaps.h"  
#include "Logger.h"
#include "AssetEditor.h"
#include "Enemy.h"

#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include "SDL_ttf.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"


#endif




void Game::CheckEvents()
{
	SDL_Event event;
	//loop throuh all the events in the event list
	while (SDL_PollEvent(&event) != NULL)
	{
		// Check for keydown
		if (event.type == SDL_KEYDOWN)
		{
			input.EventKeyPressed(event.key.keysym.sym);
		}
		//check for key up
		else if (event.type == SDL_KEYUP)
		{
			input.EventKeyReleased(event.key.keysym.sym);
		}
		else if (event.type == SDL_QUIT)
		{
			_isRunning = false;
		}
	}

	if (input.KeyIsPressed(SDLK_ESCAPE))
	{
		_isRunning = false;
	}

}

void Game::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour)
{
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int texW = 0;
	int texH = 0;

	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);
	if (!surface)
	{
		//surface not loaded? Output the error
		Logger::Error("SURFACE for font not loaded! \n");
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
		1024,               // width, in pixels
		768,               // height
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

	_texManager = new TextureManager();
	

	////creating some bitmaps
 //   player = new Player (m_Renderer, _texManager, "assets/monstertrans.bmp", 100, 100, true);                      
	//m_ground = new Bitmap(m_Renderer, _texManager, "assets/ground.bmp", 100, 300);
	//enemy = new Enemy(m_Renderer, _texManager, "assets/Alian.bmp", 400, 200, 100, 500);
	//pickup = new Pickup(m_Renderer, _texManager, "assets/Key.bmp", 500, 200);

	// read in the font
	m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15); // font size
	m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50);
	
	assetEditor = new AssetEditor(m_Renderer, m_Window, _texManager);

	// inGUI Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	SDL_DisplayMode DisplayMode;
	SDL_GetCurrentDisplayMode(0, &DisplayMode);
	ImGuiSDL::Initialize(m_Renderer, DisplayMode.w, DisplayMode.h);
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnble;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
};

Game::~Game() //destoy with the symbol ~ in front of fuction
{

	// destroy the font
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);

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

}

void Game::loadScene(Scene& scene)
{
	clearExistingObjects();

	for (auto ent : scene.entities)
	{
		switch (ent.type)
		{
		case EntityType::Ground:
			platforms.push_back(new Bitmap(m_Renderer, _texManager, ent.filename, ent.xPos, ent.yPos, ent.isTransparent));//creating the bitmap
			break;
		case EntityType::Player:
			player = new Player(m_Renderer, _texManager, ent.filename, ent.xPos, ent.yPos, ent.isTransparent);
			break;
		case EntityType::Enemy:
			enemies.push_back(new Enemy(m_Renderer, _texManager, ent.filename, ent.xPos, ent.yPos, ent.leftBound, ent.rightBound, ent.isTransparent));
			break;
		case EntityType::Pickup:
			pickups.push_back(new Pickup(m_Renderer, _texManager, ent.filename, ent.xPos, ent.yPos, ent.isTransparent));
			break;
		}
	}
}
void Game::clearExistingObjects()
{
	if (player)
		delete player;

	for (auto platform : platforms) {
		delete platform;
	}

	platforms.clear();

	for (auto pickup : pickups) {
		delete pickup;
	}

	pickups.clear();

	for (auto enemy : enemies) {
		delete enemy;
	}

	enemies.clear();
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

	//ImGui::NewFrame();
	//ImGui_ImplSDL2_NewFrame(m_Window);
	//bool show = true;
	////ShowExampleAppDockSpace(&show);

	//ImGui::ShowDemoWindow(nullptr);

	//assetEditor->Update();

	//ImGui::Render();
	//ImGuiSDL::Render(ImGui::GetDrawData());

	CheckEvents();

	for (auto enemy : enemies)
	{
		for (auto platform : platforms)
		{
			enemy->FixGroundCollision(platform);
			bool isGrounded = enemy->IsColliding(platform);
			if (isGrounded)
			{
				enemy->SetGrounded(true);
				break;
			}
		}
	}

	for (auto platform : platforms)
	{
		player->FixGroundCollision(platform);
		bool playerGrounded = player->IsColliding(platform);
		player->SetGrounded(playerGrounded);
		if (playerGrounded) break;
	}

	

	if (input.KeyIsPressed(SDLK_a) || input.KeyIsPressed(SDLK_LEFT))
	{
		player->UpdateX(-1);// if key A is pressed, player will move left
		Logger::Info("Left");
	}
	if (input.KeyIsPressed(SDLK_d) || input.KeyIsPressed(SDLK_RIGHT))
	{
		player->UpdateX(1);
		Logger::Info("Right");
	}
	if (input.KeyIsPressed(SDLK_SPACE))
	{
		player->Jump();
		Logger::Info("Jump");
	}


	char char_array[] = "Big White";
	//UpdateText(char_array, 50, 140, m_pBigFont, { 255, 255, 255});

	int testNumber = 1234;
	string testString = "Test Number: ";
	testString += to_string(testNumber);
	//UpdateText(testString, 50, 210, m_pBigFont, { 255, 255, 255 });


	player->Update();

	for (auto enemy : enemies) {
		enemy->Update();
		enemy->MoveAI();
	}

	for (auto pickup : pickups) {
		pickup->IsColliding(player);
	}

	for (auto platform : platforms) {
		platform->draw();
	}

	player->draw();

	for (auto pickup : pickups) {
		pickup->draw();
	}

	for (auto enemy : enemies) {
		enemy->draw();
	}


	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	bool show = true;

	assetEditor->Update();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	//show what we've drawn
	SDL_RenderPresent(m_Renderer);

	// pause for 1/60th second (ish)
	SDL_Delay(16);    //SDL_Delay takes millisecs
	
}


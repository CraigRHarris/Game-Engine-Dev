#ifndef GAME_H
#define GAME_H
#include "Game.h"
#include "Bitmaps.h"  
#include "Logger.h"
#include "AssetEditor.h"
#include "Enemy.h"
#include "Hierarchy.h"
#include "ProfilerSystem.h"
#include "Goal.h"
#include "Player.h"

#include <SDL.h>
#include <stdio.h>
#include <stdint.h>
#include "SDL_ttf.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"


#endif

bool Game::checkMouseJustPressed()
{
	return (isMouseDown && mouseDownCount >= 5);
}

void Game::startDragObject()
{
	if (!checkMouseJustPressed() || assetEditor->_selected || assetEditor->AssetMouseDrag != nullptr) return;

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	for (auto object : AllObjects)
	{
		SDL_Rect RectBounds = object->GetTransformRect();// look at asset drag on brightspace in tools
		if (mouseX > RectBounds.x && mouseX < RectBounds.x + RectBounds.w && mouseY > RectBounds.y && mouseY < RectBounds.y + RectBounds.h)
		{
			SelectedObject = object;
			break;
		}
	}
}

void Game::endDragObject()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (SelectedObject != nullptr)
	{
		SelectedObject->SetX(mouseX);
		SelectedObject->SetY(mouseY);
		platforms.push_back(SelectedObject);
		SelectedObject = nullptr;
		
	}
}


void Game::CheckEvents()
{
	SDL_Event event;
	//loop throuh all the events in the event list
	while (SDL_PollEvent(&event) != NULL)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		// Check for keydown
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RETURN)
			{
				_sceneManager.savescene("assets\\level1.json", player->GetPosition(), goal, enemies, platforms, pickups);
			}

			input.EventKeyPressed(event.key.keysym.sym);
		}
		//check for key up
		else if (event.type == SDL_KEYUP)// inputs
		{
			input.EventKeyReleased(event.key.keysym.sym);
		}
		else if (event.type == SDL_QUIT)
		{
			_isRunning = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (!isMouseDown)
			{
				mouseDownCount = 0;
				isMouseDown = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			isMouseDown = false;
			mouseDownCount = 0;
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
		//Logger::Error("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(_Renderer, surface);
		if (!texture)
		{
			//surface not loaded? Output the error
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(_Renderer, surface);
			if (!texture)
			{
				//surface not loaded, output error
				Logger::Error("SURFACE for font not loaded! \n");
				printf("%s\n", SDL_GetError());
			}
			else
			{
				SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
				SDL_Rect textRect = { x,y, texW, texH };

				SDL_RenderCopy(_Renderer, texture, NULL, &textRect);
			}
		}
	}

	if (texture)
		SDL_DestroyTexture(texture);
	if (surface)
		SDL_FreeSurface(surface);
}

Game::Game()
{
	
	_Window = nullptr;
	_Renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	//create the window
	_Window = SDL_CreateWindow(
		"My First Window", //title
		250,               // inital x psition
		50,                //        y
		1024,               // width, in pixels
		768,               // height
		0                  // window behaviour flags (ignore for now)
	);

	if (!_Window)
	{
		printf("WINDOW initialistion failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		int c = getchar();
		return;
	}

	//now create the renderer
	_Renderer = SDL_CreateRenderer(
		_Window,        // link the renderer to our newly created win 
		-1,              // index rendering driver (igoree for now)
		0                // renderer behaviuor flags (igoree for now)
	);

	if (!_Renderer)
	{
		printf("ENDERER initialistion failed: %\n", SDL_GetError());
		printf("Press any key to cintinue\n");
		int c = getchar();

		return;
	}

	_texManager = new TextureManager();
	Root = new I_SceneNode();
	hierarchy = new Hierarchy(Root);

	profiler = new Profiler();

	newScene = _sceneManager.readscene("assets/Level1.json");
	loadScene(newScene);

	if(!player)
		player = new Player(_Renderer, _texManager, "assets/monstertrans.bmp", 100, 100, "player", true);

	// read in the font
	m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15); // font size
	m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50);
	
	assetEditor = new AssetEditor(_Renderer, _Window, _texManager, this);

	// inGUI Setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	SDL_DisplayMode DisplayMode;
	SDL_GetCurrentDisplayMode(0, &DisplayMode);
	ImGuiSDL::Initialize(_Renderer, DisplayMode.w, DisplayMode.h);
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(_Window, SDL_GL_GetCurrentContext());
};

Game::~Game() //destoy with the symbol ~ in front of fuction
{

	// destroy the font
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);

	//clean up.
	//don't gorget - we destroy in the REVERSE order they were created 

	if (_Renderer)
	{
		SDL_DestroyRenderer(_Renderer);
	}
	if (_Window)
	{
		SDL_DestroyWindow(_Window);
	}

}

void Game::loadScene(Scene& scene)
{
	clearExistingObjects();

	addPlayer(scene.playerPosition);

	addGoal(scene.goal.pos, scene.goal.spriteFile);

	for (auto enemy : scene.enemies) {
		addEnemy(enemy.pos.x, enemy.pos.y, enemy.spriteFile, enemy.patrolData.x, enemy.patrolData.y);
	}

	for (auto platform : scene.platforms) {
		addGround(platform.pos.x, platform.pos.y, platform.spriteFile);
	}

	for (auto pickup : scene.pickups) {
		addPickup(pickup.pos.x, pickup.pos.y, pickup.spriteFile);
	}
}

void Game::addPlayer(const position& pos)
{
	player = new Player(_Renderer, _texManager, "assets//monstertrans.bmp", pos.x, pos.y, "player", true);
	AllObjects.push_back(player);
	Root->addchild(player);
}

void Game::addGoal(const position& pos, const std::string& file)
{
	goal = new Goal(_Renderer, _texManager, file, pos.x, pos.y, "goal", false);
	AllObjects.push_back(goal);
	Root->addchild(goal);
}

void Game::addGround(int x, int y, const std::string& file)
{
	platforms.push_back(new Bitmap(_Renderer, _texManager, file, x, y, "ground", false));
	AllObjects.push_back(platforms[platforms.size() - 1]);
	Root->addchild(platforms[platforms.size() - 1]);
}

void Game::addEnemy(int x, int y, const std::string& file, int leftBound, int rightBound)
{
	enemies.push_back(new Enemy(_Renderer, _texManager, file, x, y, leftBound, rightBound, "enemy", true));
	AllObjects.push_back(enemies[enemies.size() - 1]);
	Root->addchild(enemies[enemies.size() - 1]);
}

void Game::addPickup(int x, int y, const std::string& file)
{
	pickups.push_back(new Pickup(_Renderer, _texManager, file, x, y, "key", false));
	AllObjects.push_back(pickups[pickups.size() - 1]);
	Root->addchild(pickups[pickups.size() - 1]);
}

void Game::clearExistingObjects()
{
	SelectedObject = nullptr;
	if (player)
	{
		delete player;
		player = nullptr;
	}

	for (auto platform : platforms) 
	{
		delete platform;
		platform = nullptr;
	}

	platforms.clear();

	for (auto pickup : pickups) 
	{
		delete pickup;
		pickup = nullptr;
	}

	pickups.clear();

	for (auto enemy : enemies) 
	{
		delete enemy;
		enemy = nullptr;
	}

	enemies.clear();

	if (goal) 
	{
		delete goal;
		goal = nullptr;
	}
}

void Game::SetDisplayColour(int red, int green, int blue, int alpha)
{
	int result = SDL_SetRenderDrawColor(
		_Renderer,       //target render
		red,              //r
		green,                //g
		blue,                //b
		alpha		//alpha
	);
}

void Game::Update()
{
	SDL_RenderClear(_Renderer);

	CheckEvents();

	ProfilerSystem::Instance().StartFrame();

	ImGuiIO& io = ImGui::GetIO();

	profiler->push(io.DeltaTime * 1000);

	if (goal->IsColliding(player))
	{
		Root = new I_SceneNode();
		currentLV++;
		if (currentLV >= 2)
			currentLV = 0;
		newScene = _sceneManager.readscene(levels[currentLV]);

		loadScene(newScene);
		//Recreate hierarchy when loading a new scene (how?)
		if (Root)
		{
			hierarchy = new Hierarchy(Root);
		}
	}


	char char_array[] = "Big White";
	//UpdateText(char_array, 50, 140, m_pBigFont, { 255, 255, 255});

	int testNumber = 1234;
	string testString = "Test Number: ";
	testString += to_string(testNumber);
	//UpdateText(testString, 50, 210, m_pBigFont, { 255, 255, 255 });

	player->HandleInput(input);
	player->Update(platforms, pickups, enemies);

	for (auto enemy : enemies) {
		enemy->Update(platforms);
	}

	for (auto platform : platforms) {
		platform->draw();
	}

	player->draw();

	for (auto pickup : pickups) {
		pickup->draw();
	}

	

	goal->draw();

	ImGui::NewFrame();
	ImGui_ImplSDL2_NewFrame(_Window);
	bool show = true;
	int  selectFrame = -1;

	if (I_GuiWindow::SelectedObject != nullptr)
	{
		static_cast<Bitmap*>(I_GuiWindow::SelectedObject)->GUIDraw();
	}

	{
		PROFILE("Flame Graph");
		ImGui::Begin("Profiler");

		static FrameMap* Snapshot;
		static vector<float>* FrameTimes;
		//take snapshot of all current frame data.
		if (ImGui::Button("take snapshot"))
		{
			//mem copy?
			Snapshot = &(ProfilerSystem::Instance().GetFrameData());
			FrameTimes = &(ProfilerSystem::Instance().GetFrameTimes());
		}
		ImGui::SameLine();
		static bool LiveFlameGraph = true;
		ImGui::Checkbox("Live Flame Graph", &LiveFlameGraph);
		if (LiveFlameGraph)
		{
			selectFrame = -1;
		}
		static int range[2] = { 0, 100 };

		if (FrameTimes && FrameTimes->size() > 100)
		{
			ImGui::SliderInt2("Frame Range", range, 0, FrameTimes->size());
			if (range[0] >= range[1])
				range[0] = range[1] - 1;
			
			vector<float> subData(FrameTimes->cbegin() + range[0], FrameTimes->cbegin() + range[1]);
			

			int tempHistSelection = ImGui::MyPlotHistogram("Frame data", subData.data(), subData.size());
			if (tempHistSelection != -1)
			{
				LiveFlameGraph = false;
				selectFrame = tempHistSelection;
			}

			ImRect rect = { ImGui::GetItemRectMin(), ImGui::GetItemRectMax() };
			if (rect.Contains(io.MousePos))
			{
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					cout << selectFrame << endl;
				}
			}

		}

		FrameMap& previousFrame = ProfilerSystem::Instance().GetLastFrameData();
		if (!LiveFlameGraph && selectFrame != -1)
		{
			previousFrame.clear();
			for (auto const [SampleName, samples] : *Snapshot)
			{
				previousFrame[SampleName].push_back(samples[range[0] + selectFrame]);
			}
		}
		else
		{
			LiveFlameGraph = false;
		}
		
		ImGui::LabelText("Frame Date Count", std::to_string(previousFrame.size()).c_str());
		ImDrawList* drawlist = ImGui::GetCurrentWindow()->DrawList;
		ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();//pos of screen top left
		ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
		if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
		if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
		drawlist->PushClipRect(canvas_p0, canvas_p1, true);


		uint64_t totalframeTime = 0;
		vector<uint64_t> SampleTimes;
		vector<float> SampleWidths;
		vector<string> SampleNames;
		for (auto const& [SampleName, samples] : previousFrame)
		{
			totalframeTime += samples[0]->frameTime + 1;
			SampleTimes.push_back(samples[0]->frameTime + 1);
			SampleNames.push_back(SampleName);
		}

		float MinBlockWith = canvas_sz.x / totalframeTime;// GraphWindowWidth / totalframeTime;
		for (int i = 0; i < SampleTimes.size(); i++)
		{
			SampleWidths.push_back(SampleTimes[i] * MinBlockWith);
		}

		ImGui::LabelText("Total Frame Time", std::to_string(totalframeTime).c_str());
		ImGui::LabelText("Window Width / total frame Time", std::to_string(MinBlockWith).c_str());
		float TotalBlockWidthSoFar = 0;

		int sampleCount = previousFrame.size();

		const ImU32 col_outline_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x7FFFFFFF;
		const ImU32 col_base = ImGui::GetColorU32(ImGuiCol_PlotHistogram) & 0x77FFFFFF;

		for (int i = 0; i < sampleCount; i++)
		{
			float ThisBlockWidth = SampleWidths[i];

			const ImVec2 minPos = ImVec2(canvas_p0.x + TotalBlockWidthSoFar, canvas_p0.y + 100);
			const ImVec2 maxPos = ImVec2(canvas_p0.x + TotalBlockWidthSoFar + ThisBlockWidth, canvas_p0.y + 200);
			drawlist->AddRectFilled(minPos,maxPos,col_base,GImGui->Style.FrameRounding);

			drawlist->AddRect(minPos, maxPos, col_outline_base);

			ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 10), SampleNames[i].c_str());
			ImGui::RenderText(ImVec2(minPos.x + 10, minPos.y + 20), std::to_string(SampleTimes[i] - 1).c_str());


			TotalBlockWidthSoFar += ThisBlockWidth;
		}
		drawlist->PopClipRect();

		ImGui::End();
	}

	{
		PROFILE("ProfilerFrameTime");
		ImGui::Begin("Frame Time");
		ImGui::PlotLines(" Frames", profiler->FrameTimeQueue.data(), profiler->Capacity);
		char buffer[64];
		float averageFrameTime = profiler->AverageTime();
		snprintf(buffer, sizeof buffer, "%f ms", averageFrameTime);
		ImGui::Text(buffer);
		char buffer2[64];
		snprintf(buffer2, sizeof buffer2, "%f fps", profiler->CalculateFPSValue(averageFrameTime));
		ImGui::Text(buffer2);
		ImGui::End();
	}

	assetEditor->Update();
	hierarchy->Update();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

	if (isMouseDown)
	{
		mouseDownCount++;

		std::cout << "mouseDownCount: " << mouseDownCount << '\n';
		startDragObject();
	}


	std::cout << "isMouseDown : " << isMouseDown << '\n';
	std::cout << "SelectedObject : " << (SelectedObject != nullptr) << '\n';
	if (isMouseDown && SelectedObject != nullptr)
	{
		endDragObject();
	}
	//show what we've drawn
	SDL_RenderPresent(_Renderer);

	// pause for 1/60th second (ish)
	SDL_Delay(8);    //SDL_Delay takes millisecs
	ProfilerSystem::Instance().EndFrame();
	
}


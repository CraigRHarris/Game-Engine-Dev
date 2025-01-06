#include "SDL.h"
#undef main
#include "Game.h"
#include "Input.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"

//void main (void)
//{
	//start up
	//SDL_Init(SDL_INIT_EVERYTHING);

	//clean up
	//SDL_Quit();
//}

int main(int argc, char* argv[])
{
	Game* game = new Game();      //create a new Game object
	Input* input = new Input();   // create an input object

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


	if (game && input)
	{
		//game->SetDisplayColour();  //set and show our coloured display
		
		Uint8 r = 127, g = 127, b = 127, a = 255; // declare and int variables used for colour background
		
		//check keys pressed to update variables
		while (!input->KeyIsPressed(KEY_ESCAPE))
		{

			input->Update();

			//increase r
			if (input->KeyIsPressed(KEY_R))
			{
				if (++r > 255) r = 0;
			}
			//increase g
			if (input->KeyIsPressed(KEY_G))
			{
				if (++g > 255) g = 0;
			}
			//increase b
			if (input->KeyIsPressed(KEY_B))
			{
				if (++b > 255) b = 0;
			}

			game->SetDisplayColour(r, g, b, a);  //set coloured display
			game->Update();  //update the game

		}

		delete input;            //clean up input
		input = nullptr;


		delete game;             //clean up game
		game = nullptr;

	}

	return 0;                     //exit nicely
}
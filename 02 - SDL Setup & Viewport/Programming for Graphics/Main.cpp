#include "SDL.h"
#undef main
#include "Game.h"
#include "Input.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"


int main(int argc, char* argv[])
{
	Game* game = new Game();      //create a new Game object
	Input* input = new Input();   // create an input object



	while(game->isRunning())
	{
	
		Uint8 r = 137, g = 207, b = 240, a = 255; // declare and int variables used for colour background
		
		game->SetDisplayColour(r, g, b, a);  //set coloured display
		game->Update();  //update the game

	}

	return 0;                     //exit nicely
}
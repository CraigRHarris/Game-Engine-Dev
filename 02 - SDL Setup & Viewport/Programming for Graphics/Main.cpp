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

	//Game game; // Create a game object
	//// imGUI setup

	//	//check keys pressed to update variables
	//while (game.isRunning())
	//{
	//	game.Update(); //Update the game
	//}

	//return 0;				//exit nicely


	while(game)
	{
		//game->SetDisplayColour();  //set and show our coloured display
		
		Uint8 r = 137, g = 207, b = 240, a = 255; // declare and int variables used for colour background
		

		game->SetDisplayColour(r, g, b, a);  //set coloured display
		game->Update();  //update the game

	}

	delete game;             //clean up game
	game = nullptr;

	return 0;                     //exit nicely
}
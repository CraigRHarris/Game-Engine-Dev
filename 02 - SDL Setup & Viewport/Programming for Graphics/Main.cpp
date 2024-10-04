#include "SDL.h"
#undef main
#include "Game.h"

//void main (void)
//{
	//start up
	//SDL_Init(SDL_INIT_EVERYTHING);

	//clean up
	//SDL_Quit();
//}

int main(int argc, char* argv[])
{
	Game* game = new Game();      //create a new Game objetct

	if (game)
	{
		game->SetDisplayColour();  //set and show our coloured display
		delete game;
		game = nullptr;
	}

	return 0;                     //exit nicely
}
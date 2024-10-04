#include "SDL.h"
#undef main
#include "Game.h"
#include "Input.h"

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
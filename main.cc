#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "classes.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Game.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900

int main(int argc, char* argv[])
{	
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "Initialization of SDL failed.";
	}
	else if( TTF_Init() == -1 )
	{
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
	}
	else
	{
		//SDL_Event e;
		
		Window window{"testing", WINDOW_HEIGHT, WINDOW_WIDTH};
		bool done{false};
		Game game{window};

		game.run();

	}
	

}
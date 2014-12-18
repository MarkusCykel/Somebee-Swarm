#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "MapEditclasses.h"
#include "Window.h"
#include "MapEditEntity.h"
#include "MapEditTimer.h"
#include "Edit.h"
#include "MapEditMap.h"

#define WINDOW_HEIGHT 1280
#define WINDOW_WIDTH 720

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
		SDL_Event e;
		Window window{"testing", WINDOW_HEIGHT, WINDOW_WIDTH};
		Edit gameState{2000,2000,window};
		
		gameState.run(e);
	}
}
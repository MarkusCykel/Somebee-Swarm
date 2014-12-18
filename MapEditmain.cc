#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "MapEditclasses.h"
#include "MapEditWindow.h"
#include "MapEditEntity.h"
#include "MapEditTimer.h"
#include "MapEditGameState.h"
#include "MapEditMap.h"

#define WINDOW_HEIGHT 1280
#define WINDOW_WIDTH 720

int main(int argc, char* argv[])
{	
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "Initialization of SDL failed.";
	}
	else
	{
		SDL_Event e;
		MapEditWindow window{"testing", WINDOW_HEIGHT, WINDOW_WIDTH};
		MapEditGameState gameState{2000,2000,window};
		
		gameState.run(e);
	}
}
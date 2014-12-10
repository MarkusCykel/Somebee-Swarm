#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "classes.h"
#include "Window.h"
#include "Entity.h"
#include "Timer.h"
#include "GameState.h"
#include "Map.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS + 1;

int main(int argc, char* argv[])
{	
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "Initialization of SDL failed.";
	}
	else
	{
		Window window{"testing", WINDOW_HEIGHT, WINDOW_WIDTH};
		GameState gameState{2000,2000,window};
		
		gameState.run();
	}
}
#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "SDLWindow.h"
#include "SDLSurface.h"
#include "Entity.h"
#include "Timer.h"
#include "LTexture.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


int main(int argc, char* argv[])
{	
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		std::cerr << "Initialization of SDL failed.";
	}
	else
	{
		// The Window
		SDLWindow window{"testing", 500, 500};
		
		// Main loop Flag
		bool quit{false};
		
		// Event Handler
		SDL_Event e;
		
		// Test entity
		std::pair<unsigned,unsigned> derp = std::make_pair(0,0);
		Player player{std::make_pair(0,0)};
		
		SDLSurface picture;
		if(picture.loadBMP("../Somebee-Swarm/instruction.bmp", window.get_format()))
		{
			std::cout << "Error loading media";
		}
		else
		{
			window.blitSurface(picture,500,500);
		}
		
		////////////////////////////////////////////////////////
		// FPS STUFF
		//The frames per second timer 
		Timer fpsTimer; 
		
		//The frames per second cap timer 
		Timer capTimer;
		
		//Start counting frames per second
		int countedFrames = 0;
		fpsTimer.start();
		// END FPS STUFF
		////////////////////////////////////////////////////////
		
		while(!quit)
		{		
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			
			////////////////////////////////////////////////////////
			// FPS STUFF
			float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}
			
			std::cout << std::setw(13) << "Avg (w/cap) " << std::setw(12) << avgFPS;

			++countedFrames;	
			// END FPS STUFF
			////////////////////////////////////////////////////////
			
			// other stuff
			player.read_input();
			auto pos = player.get_position();
			
			std::cout << std::setw(25) << std::right << "x: " << pos.first << " y: " << pos.second << std::endl;
			
			////////////////////////////////////////////////////////
			// FPS STUFF
			int frameTicks = capTimer.getTicks();
			if( frameTicks < SCREEN_TICKS_PER_FRAME )
			{
				SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
			}
			// END FPS STUFF
			////////////////////////////////////////////////////////
		}
	}
}
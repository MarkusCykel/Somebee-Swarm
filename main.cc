#include <SDL.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "classes.h"
#include "SDLWindow.h"
#include "SDLSurface.h"
#include "Entity.h"
#include "Timer.h"
#include "Map.h"

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
		////////////////////////////////////////////////////////
		// The window and a picture
		SDLWindow window{"testing", 500, 500};
		
		SDLSurface picture;
		if(picture.loadBMP("../Somebee-Swarm/instruction.bmp", window.get_format()))
		{
			std::cout << "Error loading media";
		}
		else
		{
			window.blitSurface(picture,500,500);
		}
		//
		////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// Stuff that is needed
		// Quit flag
		bool quit{false};
		
		// Event Handler
		SDL_Event e;
		//
		////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// Stuff I'm testing
		Map map{500,500};
		map.spawnEntity("PLAYER",250,250);
		Controller controller;
		//
		////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////
		// TIMERS AND COUNTERS FOR FPS STUFF
		//The frames per second timer 
		Timer fpsTimer; 
		
		//The frames per second cap timer 
		Timer capTimer;
		
		//Start counting frames per second
		int countedFrames = 0;
		fpsTimer.start();
		//
		////////////////////////////////////////////////////////
		
		while(!quit)
		{
			capTimer.start();
			
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		
			
			// other stuff
			//player.readInput();
			//auto pos = player.getPosition();
			map.readInput();
			map.update();
			controller.update(map);
			auto pos = map.getPlayer()->getPosition();
			
			std::cout << std::setw(25) << std::right << "x: " << pos.first << " y: " << pos.second << std::endl;
			
			////////////////////////////////////////////////////////
			// CALCULATING FPS
			float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}
			
			std::cout << std::setw(13) << "Avg (w/cap) " << countedFrames << std::setw(12) << avgFPS;

			++countedFrames;	
			//
			////////////////////////////////////////////////////////
			
			////////////////////////////////////////////////////////
			// LIMIT FPS
			int frameTicks = capTimer.getTicks();
			if( frameTicks < SCREEN_TICKS_PER_FRAME )
			{
				SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
			}
			//
			////////////////////////////////////////////////////////
		}
	}
}